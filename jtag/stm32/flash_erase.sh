#!/bin/bash

#xxx.hex or xxx.bin

#stm32f103c8t6
FLASH_ADDR=0x08000000
FLASH_SIZE=0x00010000 #128KB

#stm32f103cbt6
#FLASH_ADDR=0x08000000
#FLASH_SIZE=0x00020000 #128KB

CURRENT_DIR=$(cd $(dirname $0); pwd)

CONFIG=${CURRENT_DIR}/tcl/target/stm32f1x_bcm2835gpio_swd.cfg

sudo openocd -s ${CURRENT_DIR}/tcl -f ${CONFIG} -c \
"   init;
    halt;
    reset halt;
    flash erase_address ${FLASH_ADDR} ${FLASH_SIZE};
    shutdown;
"

#128K
#flash erase_address 0x08000000 0x00020000
#mdw 0x08000000 0x00008000
