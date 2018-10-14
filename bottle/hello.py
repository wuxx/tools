# coding:utf-8
from bottle import route, run

@route('/hello')
def hello():
    return "hello world"

run(host="0.0.0.0", port=8080, debug=True)
