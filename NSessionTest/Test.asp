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
    Response.Write "The secret is "
    Response.Write Session("MyVar")
    Session("MyVar2") = "Secret saved by the asp classic page."
%>
<br />
I added my secret to the MyVar2 variable. Go back to the <a href="Default.aspx">default page</a> to see my secret. 
</body>
</html>
