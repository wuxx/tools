#!/bin/bash

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 1
}

if [ ${#1} -eq 0 ]; then
    echo "usage: $0 image-file"
    exit 0
fi

succ_count=0
fail_count=0


CURRENT_DIR=$(cd $(dirname $0); pwd)

while [ 1 ];
do

    $CURRENT_DIR/wait_and_probe.sh

    $CURRENT_DIR/flash_stm32_lock.sh $1

    if [ $? -eq 0 ]; then
        succ_count=$(($succ_count+1))
        echo -e "\033[32m---------- SUCC [$succ_count] ----------\033[0m"
    else
        fail_count=$(($fail_count+1))
        echo -e "\033[31m---------- FAIL [$fail_count] ----------\033[0m"
    fi

    $CURRENT_DIR/wait_detach.sh

done

