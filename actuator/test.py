# -*- coding: utf-8 -*-
import sys
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)
 
GPIO.output(25, GPIO.HIGH)
time.sleep(0.001*float(sys.argv[1]))
GPIO.output(25, GPIO.LOW)
GPIO.cleanup()

