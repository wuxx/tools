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
        echo "target connected [$DAP_INFO]"
        exit 0
    else
        echo -e "\033[31m wait attach <<< [$DAP_INFO] \033[0m"

    fi

done
