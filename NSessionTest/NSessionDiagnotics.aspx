<%@ Page Language="C#" %>
<%@ Import Namespace="System.Web.Configuration" %>
<%@ Import Namespace="System.Reflection" %>

<!DOCTYPE html>

<script runat="server">
    protected string GetSessionStateUriBase()
    {
        foreach (string moduleName in Context.ApplicationInstance.Modules)
        {
            IHttpModule module = Context.ApplicationInstance.Modules[moduleName];
            SessionStateModule ssm = module as SessionStateModule;
            if (ssm != null)
            {
                FieldInfo storeInfo = typeof(SessionStateModule).GetField("_store", BindingFlags.Instance | BindingFlags.NonPublic);
                SessionStateStoreProviderBase store = (SessionStateStoreProviderBase)storeInfo.GetValue(ssm);
                Type storeType = store.GetType();
                if (storeType.Name.Equals("OutOfProcSessionStateStore"))
                {
                    FieldInfo uribaseInfo = storeType.GetField("s_uribase", BindingFlags.Static | BindingFlags.NonPublic);
                    return (string)uribaseInfo.GetValue(null);
                }
            }
        }
        throw new Exception("Unable to determine UriBase.");
    }
</script>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <% 
        bool is32bit = IntPtr.Size == 4; 
    %>
        <h1>NSession diagnostic page</h1>
        <p>You are running <% = IntPtr.Size * 8 %> bit .net framework version <%= System.Environment.Version %>.</p>

        <%
            //Checking session state provider
            SessionStateSection sessionStateSection = (SessionStateSection)ConfigurationManager.GetSection("system.web/sessionState");
            switch(sessionStateSection.Mode)
            {
                case SessionStateMode.Off:
                    Response.Write("<p>The session state has been turned off.</p>");
                    break;
                    
                case SessionStateMode.InProc:
                    Response.Write("<p>You are using In-Proc session state. NSession does not support In-Proc session state.</p>");
                    break;
                    
                case SessionStateMode.SQLServer:
                    Response.Write("<p>You are using SQL Server session state. You just need to register NSession DLLs normally.</p>");
                    Response.Write(string.Format("<p>The SQL Server session state connection string is: {0}.</p>/r/n", sessionStateSection.SqlConnectionString));
                    break;
                    
                case SessionStateMode.StateServer:
                    Response.Write("<p>You are using ASP.NET State Server session state.</p>");
                    Response.Write(string.Format("<p>The ASP.NET State Server session state connection string is: {0}.</p>", sessionStateSection.StateConnectionString));
                    Response.Write("<p>NSession needs you to set the computed UriBase to the process environment variable.</p>");
                    Response.Write("<p>You can compute the value once for your application and then add the following code to the Application_Start in your global.aspx or set it as system environment variable:</p>");
                    try
                    {
                        Response.Write(string.Format(@"<pre>
Environment.SetEnvironmentVariable(""{0}_OUTOFPROCSESSIONSTATESTORE_URIBASE"", ""{1}"", EnvironmentVariableTarget.Process);
</pre>", HttpRuntime.AppDomainAppId, GetSessionStateUriBase()));
                    }
                    catch (Exception ex)
                    {
                        Response.Write(string.Format("<p>Unable to determine UriBase due to: {0}</p>", ex.Message));
                    }
%>
        <p>You can also compute the value dynamically by adding the following code to the Session_Start in your global.aspx:</p>
        <pre>
    protected void Session_Start(object sender, EventArgs e)
    {
        string appDomainAppId = HttpRuntime.AppDomainAppId;
        string uriBaseKey = string.Format("{0}_OUTOFPROCSESSIONSTATESTORE_URIBASE", appDomainAppId);
        string uribase = Environment.GetEnvironmentVariable(uriBaseKey, EnvironmentVariableTarget.Process);

        if (string.IsNullOrEmpty(uribase))
        { 
            foreach (string moduleName in this.Modules)
            {
                IHttpModule module = this.Modules[moduleName];
                SessionStateModule ssm = module as SessionStateModule;
                if (ssm != null)
                {
                    FieldInfo storeInfo = typeof(SessionStateModule).GetField("_store", BindingFlags.Instance | BindingFlags.NonPublic);
                    SessionStateStoreProviderBase store = (SessionStateStoreProviderBase)storeInfo.GetValue(ssm);
                    Type storeType = store.GetType();
                    if (storeType.Name.Equals("OutOfProcSessionStateStore"))
                    {
                        FieldInfo uribaseInfo = storeType.GetField("s_uribase", BindingFlags.Static | BindingFlags.NonPublic);
                        uribase = (string)uribaseInfo.GetValue(null);
                        Environment.SetEnvironmentVariable(uriBaseKey, uribase, 
                            EnvironmentVariableTarget.Process);
                    }
                }
            }
        }
    }
        </pre>
<%
                    break;
                    
                case SessionStateMode.Custom:
                    Response.Write("<p>You are using custom session state. Custom session state will be supported in the future. Please visit <a href=\"https://nsession.codeplex.com/workitem/list/basic\">add a workitem</a>.</p>");
                    break;
            }
            
            //Checking DLL registeration
            Type managedNSessionType = Type.GetTypeFromProgID("NSession.SessionStateClient");
            if (managedNSessionType == null)
            {
                Response.Write("<p>Managed NSession.dll is not registered correctly. Please run the following command to register it:</p>");
                if (is32bit)
                {
                    Response.Write(@"<pre>C:\Windows\Microsoft.NET\Framework\v4.0.30319\regasm /tlb /codebase NSession.dll</pre>");
                }
                else
                {
                    Response.Write(@"<pre>C:\Windows\Microsoft.NET\Framework64\v4.0.30319\regasm /tlb /codebase NSession.dll</pre>");
                }
            }
            else
            {
                try
                { 
                    Object o = Activator.CreateInstance(managedNSessionType);
                    var versionInfo = System.Diagnostics.FileVersionInfo.GetVersionInfo(managedNSessionType.Assembly.Location);
                    Response.Write(String.Format("<p>Managed NSession.dll v{0} registered correctly.</p>", versionInfo.FileVersion));
                }
                catch(Exception ex)
                {
                    Response.Write(string.Format("<p>Unable to instantiate managed NSesson.dll due to: {0}</p>", ex.Message));
                }
            }

            Type nativeNSessionType = Type.GetTypeFromProgID("NSession.Session");
            if (nativeNSessionType == null)
            {
                Response.Write("<p>Native NSession.dll is not registered correctly. Please run the following command to register it for the bitness of your app pool:</p>");
                if (is32bit)
                {
                    Response.Write(@"<pre>C:\Windows\SysWOW64\regsvr32 x86\NSessionNative.dll</pre>");
                }
                else
                {
                    Response.Write(@"<pre>C:\Windows\system32\regsvr32 x86\NSessionNative.dll</pre>");
                }
            }
            else
            {
                Response.Write("<p>Native NSessionNative.dll registered correctly.</p>");
            }
%>
    </div>
    </form>
</body>
</html>
