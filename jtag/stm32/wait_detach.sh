#!/bin/bash

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 1
}

while [ 1 ]; do

    DAP_INFO=$(lsusb | grep "0d28:0204")

    /home/pi/oss/tools/jtag/stm32/probe.sh
    if [ $? -eq 0 ]; then
        echo "wait detach >>> [$DAP_INFO]"
    else
        exit 0
    fi

done
