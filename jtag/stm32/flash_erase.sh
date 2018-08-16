#!/bin/bash

#xxx.hex or xxx.bin

FLASH_ADDR=0x08000000
FLASH_SIZE=0x00020000 #128KB

CURRENT_DIR=$(cd $(dirname $0); pwd)

sudo openocd -f ${CURRENT_DIR}/tcl/target/stm32f1x_sysfsgpio.cfg -c \
"   init;
    halt;
    reset halt;
    flash erase_address ${FLASH_ADDR} ${FLASH_SIZE};
    shutdown;
"

#128K
#flash erase_address 0x08000000 0x00020000
#mdw 0x08000000 0x00008000
