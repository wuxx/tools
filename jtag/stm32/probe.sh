#!/bin/bash

#sudo openocd -f tcl/target/stm32f1x_sysfsgpio_swd.cfg

#sudo openocd -f tcl/target/stm32f1x_bcm2835gpio_swd.cfg

CURRENT_DIR=$(cd $(dirname $0); pwd)

#CONFIG=${CURRENT_DIR}/tcl/target/stm32f2x_sysfsgpio_swd.cfg
CONFIG=${CURRENT_DIR}/tcl/target/stm32f1x_bcm2835gpio_swd.cfg

#sudo openocd -f tcl/target/stm32f2x_sysfsgpio_swd.cfg

sudo openocd -s ${CURRENT_DIR}/tcl -f ${CONFIG} -c \
         "init;
          halt;
          reset halt;
          reset;
          shutdown; " > /dev/null 2>&1

