# coding:utf-8
from bottle import route, run

@route('/hello/<name>')
def greet(name='Stranger'):
    return ("hello world %s" %(name))

run(host="0.0.0.0", port=8080, debug=True)
