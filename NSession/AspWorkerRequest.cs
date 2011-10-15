using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using ASPTypeLibrary;

namespace NSession
{
    class AspWorkerRequest : HttpWorkerRequest
    {
        protected IRequest _request;

        protected string GetServerVar(string name)
        {
            return _request.ServerVariables["URL"][1];
        }

        public AspWorkerRequest(IRequest request)
        {
            this._request = request;
        }

        public override void EndOfRequest()
        {
            throw new NotImplementedException();
        }

        public override void FlushResponse(bool finalFlush)
        {
            throw new NotImplementedException();
        }

        public override string GetHttpVerbName()
        {
            return GetServerVar("REQUEST_METHOD");
        }

        public override string GetHttpVersion()
        {
            return GetServerVar("SERVER_PROTOCOL");
        }

        public override string GetLocalAddress()
        {
            return GetServerVar("LOCAL_ADDR");
        }

        public override int GetLocalPort()
        {
            return Convert.ToInt32(GetServerVar("SERVER_PORT"));
        }

        public override string GetQueryString()
        {
            return GetServerVar("QUERY_STRING");
        }

        public override string GetRawUrl()
        {
            return GetServerVar("URL") + "?" + GetQueryString(); 
        }

        public override string GetRemoteAddress()
        {
            return GetServerVar("REMOTE_ADDR");
        }

        public override int GetRemotePort()
        {
            return 80;
        }

        public override string GetUriPath()
        {
            return GetServerVar("PATH_INFO");
        }

        public override void SendKnownResponseHeader(int index, string value)
        {
            throw new NotImplementedException();
        }

        public override void SendResponseFromFile(IntPtr handle, long offset, long length)
        {
            throw new NotImplementedException();
        }

        public override void SendResponseFromFile(string filename, long offset, long length)
        {
            throw new NotImplementedException();
        }

        public override void SendResponseFromMemory(byte[] data, int length)
        {
            throw new NotImplementedException();
        }

        public override void SendStatus(int statusCode, string statusDescription)
        {
            throw new NotImplementedException();
        }

        public override void SendUnknownResponseHeader(string name, string value)
        {
            throw new NotImplementedException();
        }
    }
}
