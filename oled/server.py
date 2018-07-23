# coding:utf-8
from bottle import route, run

import os
import time
from demo_opts import get_device
from luma.core.virtual import terminal
from PIL import ImageFont

global term

device = get_device()
#font = make_font("tiny.ttf", 12)
#term = terminal(device, font)
term = terminal(device, None)

@route('/log/<log_string>')
def log(log_string='Stranger'):
    log_str = "%s" %(log_string)
    term.println("log")
    term.println(log_str)
    return ("log %s ok" %(log_str))

@route('/hello/<name>')
def greet(name='Stranger'):
    return ("hello world %s" %(name))


def make_font(name, size):
    font_path = os.path.abspath(os.path.join(os.path.dirname(__file__), 'fonts', name))
    return ImageFont.truetype(font_path, size)

def oled_init():
    term.println("oled_init")


if __name__ == "__main__":
    try:
	    oled_init()
	    run(host="0.0.0.0", port=8080, debug=True)
    except KeyboardInterrupt:
        pass

