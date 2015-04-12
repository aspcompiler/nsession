using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using ASPTypeLibrary;
using System.EnterpriseServices;
using System.Reflection;
using System.Web;
using System.Collections.Specialized;
using System.Web.SessionState;
using System.Configuration;
using System.Web.Configuration;

namespace NSession
{
    [ComVisible(true)]
    [Guid("B3EB0C5E-5D25-453F-9080-33D3A5CBDB5A")]
    [ClassInterface(ClassInterfaceType.None)]
    public class SessionStateClient : ISessionStateClient, IDisposable
    {
        protected bool _isExclusive = false;
        protected IRequest _request;
        protected ISessionObject _session;
        protected HttpContext _context;
        protected string _sessionId;

        protected bool _locked;
        protected TimeSpan _lockAge;
        protected object _lockId;
        protected SessionStateActions _actionFlags;
        protected bool _newItem;

        protected TimeSpan _executionTimeout = new TimeSpan(0, 1, 50);
        protected int _sessionTimeout = 1200;

        private bool _disposed;
        private dynamic _store;

        #region ISessionStateClient Members

        public void GetItem()
        {
            GetItemInternal(false);
        }

        public void GetItemExclusive()
        {
            GetItemInternal(true);
        }

        public void SetAndReleaseItemExclusive()
        {
            //Init();

            if (_isExclusive)
            {
                SessionStateItemCollection sessionItems = new SessionStateItemCollection();
                foreach (string key in _session.Contents)
                {
                    sessionItems[key] = _session[key];
                }

                SessionStateStoreData data = new SessionStateStoreData(sessionItems, null, 20);
                _store.SetAndReleaseItemExclusive(_context, _sessionId, data, _lockId, _newItem);
                _isExclusive = false;
            }
        }

        #endregion

        protected void GetItemInternal(bool isExclusive)
        {
            Init();

            SessionStateStoreData data;
            if (isExclusive)
            {
                _isExclusive = isExclusive;
                while (true)
                { 
                    data = _store.GetItemExclusive(_context, _sessionId, out _locked, out _lockAge, out _lockId, out _actionFlags);
                    if (data == null)
                    {
                        if (_locked)
                        {
                            if (_lockAge > _executionTimeout)
                            {
                                _store.ReleaseItemExclusive(_context, _sessionId, _lockId);
                            }
                            else
                            {
                                System.Threading.Thread.Sleep(500);
                            }
                        }
                        else
                        {
                            data = _store.CreateNewStoreData(_context, _sessionTimeout);
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            { 
                data = _store.GetItem(_context, _sessionId, out _locked, out _lockAge, out _lockId, out _actionFlags);
            }

            if (data != null)
            {
                _newItem = false;
                ISessionStateItemCollection sessionItems = data.Items;

                foreach (string key in sessionItems.Keys)
                {
                    _session[key] = sessionItems[key];
                }
            }
            else
            {
                _newItem = true;
            }
        }

        protected void Init()
        {
            if (_request == null)
            { 
                _request = (IRequest)ContextUtil.GetNamedProperty("Request");
                _session = (ISessionObject)ContextUtil.GetNamedProperty("Session");

                IReadCookie cookie = (IReadCookie)_request.Cookies["ASP.NET_SessionId"];
                //http://msdn.microsoft.com/en-us/library/ms525056(VS.90).aspx
                _sessionId = cookie[Missing.Value]; //VR_ERROR with DISP_E_PARAMNOTFOUND, http://www.informit.com/articles/article.aspx?p=27219&seqNum=8

                AspWorkerRequest wr = new AspWorkerRequest(_request);
                _context = new HttpContext(wr);

                string appPhysPath = _request.ServerVariables["APPL_PHYSICAL_PATH"][1];
                string appDomainAppId = _request.ServerVariables["APPL_MD_PATH"][1];
                ExeConfigurationFileMap map = new ExeConfigurationFileMap();
                map.ExeConfigFilename = appPhysPath + "web.config";
                Configuration config = ConfigurationManager.OpenMappedExeConfiguration(map, ConfigurationUserLevel.None);

                SessionStateSection section = (SessionStateSection)config.GetSection("system.web/sessionState");
                Type storeType = null;
                string connstr = null;
                switch(section.Mode)
                { 
                    case SessionStateMode.StateServer:
                        string uriBaseKey = string.Format("{0}_OUTOFPROCSESSIONSTATESTORE_URIBASE", appDomainAppId);
                        string uribase = Environment.GetEnvironmentVariable(uriBaseKey, EnvironmentVariableTarget.Process);

                        storeType = Type.GetType("System.Web.SessionState.OutOfProcSessionStateStore, System.Web, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a");
                        SetPrivateStaticField(storeType, "s_uribase", uribase);
                        connstr = section.StateConnectionString;
                        _store = Activator.CreateInstance(storeType);

                        break;
                    case SessionStateMode.SQLServer:
                        storeType = Type.GetType("System.Web.SessionState.SqlSessionStateStore, System.Web, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a");
                        SetPrivateStaticField(storeType, "s_commandTimeout", (int)section.SqlCommandTimeout.TotalSeconds);
                        //SetPrivateStaticField(storeType, "s_configSqlConnectionFileName", section.ElementInformation.Properties["sqlConnectionString"].Source);
                        //SetPrivateStaticField(storeType, "s_configSqlConnectionLineNumber", section.ElementInformation.Properties["sqlConnectionString"].LineNumber);
                        SetPrivateStaticField(storeType, "s_configAllowCustomSqlDatabase", section.AllowCustomSqlDatabase);
                        connstr = section.SqlConnectionString;

                        //http://blogs.msdn.com/b/kirillosenkov/archive/2009/07/21/instantiating-types-with-no-public-constructors.aspx
                        var ctor = storeType.GetConstructor(BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Instance, null, new Type[0], null);
                        _store = ctor.Invoke(null);

                        Type httpRunTimeType = typeof(HttpRuntime);
                        HttpRuntime theRunTime = (HttpRuntime)GetPrivateStaticField(httpRunTimeType, "_theRuntime");
                        SetPrivateInstanceField(httpRunTimeType, "_appDomainAppId", theRunTime, appDomainAppId);

                        break;
                }

                
                MethodInfo createPartionInfo = storeType.GetMethod("CreatePartitionInfo", BindingFlags.Instance | BindingFlags.NonPublic);
                dynamic partitionInfo = createPartionInfo.Invoke(_store, new object[] { connstr });

                SetPrivateInstanceField(storeType, "_partitionInfo", _store, partitionInfo);

                _sessionTimeout = (int)section.Timeout.TotalSeconds;

                HttpRuntimeSection httpRuntimeSection = config.GetSection("httpRuntime") as HttpRuntimeSection;
                if (httpRuntimeSection != null)
                {
                    _executionTimeout = httpRuntimeSection.ExecutionTimeout;
                }
            }
        }

        #region IDisposable Members

        public void Dispose()
        {
            Dispose(true);

            // Use SupressFinalize in case a subclass
            // of this type implements a finalizer.
            GC.SuppressFinalize(this);
        }

        #endregion

        protected virtual void Dispose(bool disposing)
        {
            // If you need thread safety, use a lock around these 
            // operations, as well as in your methods that use the resource.
            if (!_disposed)
            {
                if (disposing)
                {
                    if (_isExclusive)
                    {
                        SetAndReleaseItemExclusive();
                    }
                }

                // Indicate that the instance has been disposed.
                _isExclusive = false;
                _disposed = true;
            }
        }

        private static void SetPrivateStaticField(Type type, string member, object value)
        {
            FieldInfo fi = type.GetField(member, BindingFlags.Static | BindingFlags.NonPublic);
            fi.SetValue(type, value);
        }

        private static object GetPrivateStaticField(Type type, string member)
        {
            FieldInfo fi = type.GetField(member, BindingFlags.Static | BindingFlags.NonPublic);
            return fi.GetValue(type);
        }

        private static void SetPrivateInstanceField(Type type, string member, object instance, object value)
        {
            FieldInfo fi = type.GetField(member, BindingFlags.Instance | BindingFlags.NonPublic);
            fi.SetValue(instance, value);
        }

    }
}
