#!/bin/bash

if [ ${#1} -eq 0 ]; then
	echo "usage: $0 hex-file"
    exit 0
fi

CURRENT_DIR=$(cd $(dirname $0); pwd)

HEX_FILE=$1

sudo openocd -f ${CURRENT_DIR}/tcl/target/stm32f1x_sysfsgpio.cfg -c \
"   init;
    halt;
    reset halt;
    flash write_image erase $HEX_FILE;
    reset;
    shutdown;
"
