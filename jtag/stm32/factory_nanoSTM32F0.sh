#!/bin/bash

succ_count=0
fail_count=0

#target_image=/home/pi/oss/nanoDAP/firmware/v2.3/DAPLink/flash_image_128k_bl_if_hid.bin
target_image=/home/pi/oss/nanoSTM32F0/doc/demo.hex

while [ 1 ]; do
    ./probe_f0.sh
    if [ $? -eq 0 ]; then

        ./flash_write_f0.sh ${target_image}
            
        if [ $? -eq 0 ]; then
            succ_count=$(($succ_count+1))  
            echo -e "\033[32m---------- SUCC [$succ_count] ----------\033[0m"

        else
            fail_count=$(($fail_count+1))  
            echo -e "\033[31m---------- FAIL [$fail_count] ----------\033[0m"

        fi

        while [ 1 ]; do
            ./probe_f0.sh
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
