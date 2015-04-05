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
    'o.GetItems() 'Get items without locking the session. Things you write to session will not propagate. No need to call SetAndReleaseItemExclusive.
    Response.Write "The secret is "
    Response.Write Session("MyVar")
    Session("MyVar2") = "This is the secret saved by the asp classic page."
    o.SetAndReleaseItemExclusive() 'Unlock session
 %>
<br />
I added my secret to the MyVar2 variable. Go back to the <a href="Default.aspx">default page</a> to see my secret. 
</body>
</html>
