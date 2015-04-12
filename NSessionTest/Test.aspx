<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Test.aspx.cs" Inherits="Test" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        I save a value in the ASPNetVar session state variable. Go to <a href="Test.asp">an asp classic page</a> to see the variable.
        <br />
        <%= Session["ASPClassicVar"]%>
    </div>
    </form>
</body>
</html>
