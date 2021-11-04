#!/bin/bash

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 1
}

while [ 1 ]; do


    /home/pi/oss/tools/jtag/stm32/probe.sh
    if [ $? -eq 0 ]; then
        echo "wait detach"
    else
        exit 0
    fi

done
