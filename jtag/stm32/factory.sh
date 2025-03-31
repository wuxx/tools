#!/bin/bash

if [ ${#1} -eq 0 ]; then
    echo "usage: $0 image-file"
    exit 0
fi

succ_count=0
fail_count=0

target_image=$1

CURRENT_DIR=$(cd $(dirname $0); pwd)

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 0
}

while [ 1 ]; do
    ${CURRENT_DIR}/probe.sh
    if [ $? -eq 0 ]; then

        echo "flash_write [${target_image}] "
        ${CURRENT_DIR}/flash_write.sh ${target_image}
            
        if [ $? -eq 0 ]; then
            succ_count=$(($succ_count+1))  
            echo -e "\033[32m---------- SUCC [$succ_count] ----------\033[0m"
            buzzer_succ

        else
            fail_count=$(($fail_count+1))  
            echo -e "\033[31m---------- FAIL [$fail_count] ----------\033[0m"
            buzzer_fail

        fi

        while [ 1 ]; do
            ${CURRENT_DIR}/probe.sh
            if [ $? -eq 1 ]; then
                break;
            else
                echo -e "\033[32m wait detach >>> \033[0m"

                sleep 0.1
            fi
        done

    else
        DAP_INFO=$(lsusb | grep "0d28:0204")
        echo -e "\033[31m wait attach <<< [$DAP_INFO] \033[0m"

        sleep 0.1

    fi

done
