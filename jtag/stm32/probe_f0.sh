#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)

CONFIG=${CURRENT_DIR}/tcl/target/stm32f0x_cmsisdap.cfg

sudo openocd -s ${CURRENT_DIR}/tcl -f ${CONFIG} -c \
         "init;
          halt;
          reset halt;
          reset;
          shutdown; " > /dev/null 2>&1

