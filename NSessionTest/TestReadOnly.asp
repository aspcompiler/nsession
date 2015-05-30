<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title></title>
</head>
<body>
<%
    dim o

    set o = Server.CreateObject("NSession.ReadOnlySession")
    Response.Write "The value from ASP.NET is: "
    Response.Write Session("ASPNetVar")
%>
</body>
</html>
