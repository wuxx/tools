#!/bin/bash

#avrdude -p m2560 -P /dev/ttyUSB0 -c avrisp -U flash:w:Blink.ino-1000.hex

#avrdude -p m2560 -P /dev/ttyUSB0 -c avrisp -U flash:w:Blink.ino-1000.hex

if [ ${#1} -eq 0 ]; then
    #HEX_FILE=Blink.ino-100.hex
    HEX_FILE=Blink.ino-1000.hex
else
    HEX_FILE=$1
fi

echo "${HEX_FILE}"

#avrdude -v -p m2560 -C avrdude_gpio.conf -c pi_1 -D -U flash:w:${HEX_FILE}:i


#FIXME: arduino IO is 5V ??? but rpi IO is 3.3V

#sudo avrdude -v -p m2560 -C avrdude.conf -c pi_1 -D -U flash:w:${HEX_FILE}:i

sudo avrdude -v -p m2560 -C avrdude.conf -c pi_1 -U flash:w:${HEX_FILE}:i

#sudo avrdude -v -p atmega2560 -C avrdude.conf -c pi_1 -t

#ok!
#sudo avrdude -c linuxgpio -p m2560 -v -U flash:w:/home/pi/oss/tools/jtag/atmega2560/Blink.ino-100.hex:i
