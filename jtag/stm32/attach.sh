#!/bin/bash

#sudo openocd -f tcl/target/stm32f1x_sysfsgpio.cfg -c 'init; halt; resume; '

sudo openocd -f tcl/target/stm32f1x_sysfsgpio.cfg -c \
"   init;
    halt;
    flash write_image erase /home/pi/oss/tools/jtag/stm32/LED_300.hex;
    reset;
    shutdown;
"


