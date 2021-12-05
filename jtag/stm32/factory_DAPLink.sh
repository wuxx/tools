#!/bin/bash

succ_count=0
fail_count=0

#target_image=/home/pi/oss/nanoDAP/firmware/v2.3/CMSIS-DAP/flash_image_cmsisdap_20191007.bin
#target_image=/home/pi/oss/nanoDAP/firmware/v2.3/DAPLink/flash_image_128k_bl_if_hid.bin
#target_image=/home/pi/test/flash_image_128k_bl_if_hid_for_rak.bin
target_image=/home/pi/oss/nanoDAP/firmware/v2.3/DAPLink/flash_image_20210104.bin

cd /home/pi/oss/tools/jtag/stm32

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 0
}

while [ 1 ]; do
    ./probe.sh
    if [ $? -eq 0 ]; then

        ./flash_write.sh ${target_image}
            
        if [ $? -eq 0 ]; then
            succ_count=$(($succ_count+1))  
            echo -e "\033[32m---------- SUCC [$succ_count] ----------\033[0m"

        else
            fail_count=$(($fail_count+1))  
            echo -e "\033[31m---------- FAIL [$fail_count] ----------\033[0m"

        fi

        while [ 1 ]; do
            ./probe.sh
            if [ $? -eq 1 ]; then
                break;
            else
                echo "wait detach..."
                sleep 0.1
            fi
        done

    else
        echo "wait attach..."
        sleep 0.1

    fi

done
