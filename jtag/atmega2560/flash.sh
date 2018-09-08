#!/bin/bash

#avrdude -p m2560 -P /dev/ttyUSB0 -c avrisp -U flash:w:Blink.ino-1000.hex

#avrdude -p m2560 -P /dev/ttyUSB0 -c avrisp -U flash:w:Blink.ino-1000.hex

if [ ${#1} -eq 0 ]; then
    HEX_FILE=Blink.ino-100.hex
    #HEX_FILE=Blink.ino-1000.hex
else
    HEX_FILE=$1
fi

echo "${HEX_FILE}"

avrdude -v -p m2560 -P /dev/ttyUSB0 -b 115200 -c wiring -D -U flash:w:${HEX_FILE}:i


