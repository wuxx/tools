#!/bin/bash

#HEX_FILE=I2C_EEPROM_1.hex
HEX_FILE=I2C_EEPROM_10.hex

stm8gal -p /dev/ttyS0 -b 57600 -u 2 -w ${HEX_FILE} -R 3
