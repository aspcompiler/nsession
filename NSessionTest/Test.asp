<%
    dim o
    'set o = Server.CreateObject("NSession.TestClass")
    'Response.Write "The session key is "
    'Response.Write o.getSessionVariable("")

    //set o = Server.CreateObject("NSession.SessionStateClient")
    set o = Server.CreateObject("NSession.Session")
    //set o = Server.CreateObject("NSession.ReadOnlySession")
    //o.GetItemExclusive()
    Response.Write "The session key is "
    Response.Write Session("MyVar")
    Session("MyVar2") = "My secret too"
    //o.SetAndReleaseItemExclusive()
 %>