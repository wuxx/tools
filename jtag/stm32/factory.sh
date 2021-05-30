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

        ${CURRENT_DIR}/flash_write.sh ${target_image}
            
        if [ $? -eq 0 ]; then
            succ_count=$(($succ_count+1))  
            echo -e "\033[32m---------- SUCC [$succ_count] ----------\033[0m"

        else
            fail_count=$(($fail_count+1))  
            echo -e "\033[31m---------- FAIL [$fail_count] ----------\033[0m"

        fi

        while [ 1 ]; do
            ${CURRENT_DIR}/probe.sh
            if [ $? -eq 1 ]; then
                break;
            else
                echo "wait detach >>>"
                sleep 0.1
            fi
        done

    else
        echo "wait attach <<<"
        sleep 0.1

    fi

done
