<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title></title>
</head>
<body>
<%
    dim o

    set o = Server.CreateObject("NSession.SessionStateClient")
    o.GetItemExclusive() 'Get items and lock sesison for write
    'o.GetItem() 'Get items without locking the session. Things you write to session will not propagate. No need to call SetAndReleaseItemExclusive.
    Response.Write "The value from ASP.NET is: "
    Response.Write Session("ASPNetVar")
    Session("ASPClassicVar") = "Hello from ASP Classic."
    o.SetAndReleaseItemExclusive() 'Unlock session
 %>
<br />
I saved a value to to the ASPClassicVar variable. Go back to the <a href="Test.aspx">ASP.NET page</a> to see the value. 
</body>
</html>
