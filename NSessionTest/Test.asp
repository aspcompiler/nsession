<%
    dim o
    set o = Server.CreateObject("Dlrsoft.NSession.TestClass")
    Response.Write "The session key is "
    Response.Write o.getSessionVariable("")
 %>