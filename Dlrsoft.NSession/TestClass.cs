using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using ASPTypeLibrary;
//using COMSVCSLib;
using System.EnterpriseServices;
using System.Reflection;
using System.Web;
using System.Collections.Specialized;
using System.Web.SessionState;

namespace Dlrsoft.NSession
{
    [ComVisible(true)]
    [Guid("8DC028E0-27E4-4e2b-A2EC-5C0DDAC71D3E")]
    [ClassInterface(ClassInterfaceType.None)]
    public class TestClass : ITestInterface
    {
        #region ITestInterface Members

        public string getSessionVariable(string key)
        {
            //AppServer server = new AppServer();
            //ObjectContext ctx = server.GetObjectContext();
            //IRequest request = (IRequest)ctx["Request"];
            IRequest request = (IRequest)ContextUtil.GetNamedProperty("Request");

            IReadCookie cookie = (IReadCookie)request.Cookies["ASP.NET_SessionId"] ;
            //http://msdn.microsoft.com/en-us/library/ms525056(VS.90).aspx
            string sessionId = cookie[Missing.Value]; //VR_ERROR with DISP_E_PARAMNOTFOUND, http://www.informit.com/articles/article.aspx?p=27219&seqNum=8

            AspWorkerRequest wr = new AspWorkerRequest(request);
            HttpContext context = new HttpContext(wr);

            Type storeType = Type.GetType("System.Web.SessionState.OutOfProcSessionStateStore, System.Web, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a");
            FieldInfo uribaseInfo = storeType.GetField("s_uribase", BindingFlags.Static | BindingFlags.NonPublic);
            uribaseInfo.SetValue(storeType, "MyAppId");

            dynamic store = Activator.CreateInstance(storeType);
            //store.Initialize(string.Empty, new NameValueCollection());
            MethodInfo createPartionInfo = storeType.GetMethod("CreatePartitionInfo", BindingFlags.Instance | BindingFlags.NonPublic);
            dynamic partitionInfo = createPartionInfo.Invoke(store, new object[] { "tcpip=127.0.0.1:42424" });

            FieldInfo partitionInfoInfo = storeType.GetField("_partitionInfo", BindingFlags.Instance | BindingFlags.NonPublic);
            partitionInfoInfo.SetValue(store, partitionInfo);
            
            bool locked;
            TimeSpan lockAge;
            object lockId;
            SessionStateActions actionFlags;
            SessionStateStoreData data = store.GetItem(context, sessionId, out locked, out lockAge, out lockId, out actionFlags);
            
            return (string)data.Items["myVar"];
        }

        #endregion
    }

    [ComVisible(true)]
    [Guid("E2E0ABDB-4EB3-4180-944F-24E4FD2944EA")]
    public interface ITestInterface
    {
        string getSessionVariable(string key);
    }
}
