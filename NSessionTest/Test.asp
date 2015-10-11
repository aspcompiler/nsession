<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title></title>
</head>
<body>
<%
    dim o

    set o = Server.CreateObject("NSession.Session")
    'set o = Server.CreateObject("NSession.ReadOnlySession")
    Response.Write "The value from ASP.NET is: "
    Response.Write Session("ASPNetVar")
    Session("ASPClassicVar") = "Hello from ASP Classic."
%>
<br />
The session variable from MVC page is <%= Session("MVCSession") %>
<br />
I saved a value to to the ASPClassicVar variable. Go back to the <a href="Test.aspx">ASP.NET page</a> to see the value. 
</body>
</html>
