#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)

ID1_ADDR="0x1ffff7e8"
ID2_ADDR="0x1ffff7ec"
ID3_ADDR="0x1ffff7f0"

#stm32f103c8t6
#FLASH_ADDR=0x08000000
#FLASH_SIZE=0x00010000

CONFIG=${CURRENT_DIR}/tcl/target/stm32f1x_cmsisdap.cfg

OUTPUT=$(sudo timeout 1 openocd -s ${CURRENT_DIR}/tcl -f ${CONFIG} -c \
"
    init;
    halt;
    mdw 0x1ffff7e8 3;

" 2>&1)
#")

#echo ${OUTPUT}

ID1_VALUE=$(echo $OUTPUT | grep ${ID1_ADDR} | awk -F ${ID1_ADDR} '{print $2}' | awk '{print $2}')
ID2_VALUE=$(echo $OUTPUT | grep ${ID1_ADDR} | awk -F ${ID1_ADDR} '{print $2}' | awk '{print $3}')
ID3_VALUE=$(echo $OUTPUT | grep ${ID1_ADDR} | awk -F ${ID1_ADDR} '{print $2}' | awk '{print $4}')

if  [ ${#ID1_VALUE} -eq 0 ] && [ ${#ID2_VALUE} -eq 0 ] &&[ ${#ID2_VALUE} -eq 0 ]; then
    echo "get idcode fail"
    exit 1
else
    ID_VALUE="0x${ID1_VALUE} 0x${ID2_VALUE} 0x${ID3_VALUE}"

    echo ${ID_VALUE}
    exit 0
fi
