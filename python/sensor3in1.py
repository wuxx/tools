#!/usr/bin/python

import time
import smbus
from AM2315 import *
from Raspi_BMP085 import BMP085
from Raspi_TSL2561 import TSL2561

sensor_am2315 = AM2315()    # 0x5C
sensor_bmp085 = BMP085(0x77)
sensor_tsl2561 = TSL2561(0x39)

while True:
    #print ("(humidity, temperature, 0)")
    values = sensor_am2315.values()
    humidity = values[0]
    temperature = values[1]
    #print (sensor_am2315.values())
    print ("sensor_am2315:")
    print ("\thumidity:    %.2f" % humidity)
    print ("\ttemperature: %.2f" % (temperature))
    
    temp = sensor_bmp085.readTemperature()
    pressure = sensor_bmp085.readPressure()
    altitude = sensor_bmp085.readAltitude() 
    print ("sensor_bmp085:")
    print ("\tTemperature: %.2f C" % temp)
    print ("\tPressure:    %.2f hPa" % (pressure / 100.0))
    print ("\tAltitude:    %.2f" % altitude)
    
    print ("sensor_tsl2561:")
    print ("\tlight: %5d lux" %(sensor_tsl2561.readLux(0)))
    time.sleep(60)

