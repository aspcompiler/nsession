﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.SessionState;
using System.Reflection;
using System.Configuration;
using System.Web.Mvc;
using System.Web.Routing;

/// <summary>
/// Summary description for NSessionTestApplication
/// </summary>
public class NSessionTestApplication : HttpApplication
{
    public override void Init()
    {
        base.Init();
    }

    protected void Application_Start(object sender, EventArgs e)
    {
        RouteConfig.RegisterRoutes(RouteTable.Routes);
    }

    protected void Application_End(object sender, EventArgs e)
    {
        //  Code that runs on application shutdown

    }

    protected void Application_Error(object sender, EventArgs e)
    {
        // Code that runs when an unhandled error occurs

    }

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

    protected void Session_End(object sender, EventArgs e)
    {
        // Code that runs when a session ends. 
        // Note: The Session_End event is raised only when the sessionstate mode
        // is set to InProc in the Web.config file. If session mode is set to StateServer 
        // or SQLServer, the event is not raised.

    }
}