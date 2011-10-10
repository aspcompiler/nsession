<%
    dim key
    for each key in request.ServerVariables
        Response.Write key & "=" & request.ServerVariables(key) & "<br/>"
    next
 %>