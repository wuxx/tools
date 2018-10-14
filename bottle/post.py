from bottle import route,run,request

htmlstr = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>bottle</title>
</head>
<body>
    <form action="/get" method="get">
        label>name</label>
        <input type="text" name = "name"/>
        <label>num</label>
        <input type="text" name = "telephone"/>
        <label>mail</label>
        <input type="text" name = "email"/>
        <input type="submit" />
    </form>
</body>
</html>
"""


@route('/')
def index():
    return htmlstr

@route('/get')
def getpara():
    name = request.query.name
    telephone = request.query.telephone
    email = request.query.email
    return '%s %s %s '%(name,telephone,email)

run(host='0.0.0.0',port=80,debug=True,reloader=True)
