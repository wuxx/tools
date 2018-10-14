#!/bin/bash

#sudo openocd -f tcl/target/stm32f1x_sysfsgpio.cfg -c 'init; halt; resume; '

#sleep 1000
HEX_FILE=TOUCH.hex

sudo openocd -f tcl/target/stm32f1x_sysfsgpio.cfg -c \
"   init;
    halt;
    flash write_image erase /home/pi/oss/tools/jtag/stm32/$HEX_FILE;
    reset;
    shutdown;
"
