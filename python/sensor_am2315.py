#!/usr/bin/python

import time
import smbus
from AM2315 import *

sensor_am2315 = AM2315()    # 0x5C

#print ("(humidity, temperature, 0)")
values = sensor_am2315.values()
humidity = values[0]
temperature = values[1]
#print (sensor_am2315.values())
print ("sensor_am2315:")
print ("\thumidity:    %.2f" % humidity)
print ("\ttemperature: %.2f" % (temperature))
