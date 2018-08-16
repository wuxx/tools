#!/bin/bash

if [ ${#1} -eq 0 ]; then
	echo "usage: $0 image-file"
    exit 0
fi

CURRENT_DIR=$(cd $(dirname $0); pwd)

#xxx.hex or xxx.bin
IMAGE_FILE=$1
FLASH_ADDR=0x08000000
FLASH_SIZE=0x00020000

#flash write_image erase xxx.hex 0x08000000;
#flash write_image erase xxx.bin;

sudo openocd -f ${CURRENT_DIR}/tcl/target/stm32f1x_sysfsgpio.cfg -c \
"   init;
    halt;
    reset halt;
    flash write_image erase $IMAGE_FILE 0x08000000;
    reset;
    shutdown;
"
