#!/bin/bash

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 1
}

while [ 1 ]; do

    DAP_INFO=$(lsusb | grep "0d28:0204")

    if [ ${#DAP_INFO} -ne 0 ]; then
        echo -n "downloader: $DAP_INFO "
    else
        echo -n "x"
    fi

    /home/pi/oss/tools/jtag/stm32/probe.sh
    if [ $? -eq 0 ]; then
        echo "target connected"
        exit 0
    else
        echo "."
    fi

done
