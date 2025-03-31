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
        echo -e "\033[32m wait detach >>> [$DAP_INFO] \033[0m"

    else
        exit 0
    fi

done
