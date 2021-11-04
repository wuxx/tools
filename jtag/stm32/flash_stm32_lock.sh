#!/bin/bash

#set -o errexit

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 1
}

CURRENT_DIR=$(cd $(dirname $0); pwd)

#/home/pi/oss/tools/jtag/stm32/unlock.sh

$CURRENT_DIR/wait_and_probe.sh

#/home/pi/oss/tools/jtag/stm32/probe.sh
#if [ $? -ne 0 ]; then
#echo "probe fail!"
#exit 1
#fi

/home/pi/oss/tools/jtag/stm32/flash_write.sh $1
if [ $? -ne 0 ]; then
    echo "write fail!"
    exit 1
fi

/home/pi/oss/tools/jtag/stm32/lock.sh

$CURRENT_DIR/wait_detach.sh
