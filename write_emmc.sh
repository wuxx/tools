#!/bin/bash

cd ~/oss/usbboot

while [ 1 ]; do
    sudo timeout 20 ./rpiboot
    if [ $? -ne 0 ]; then
        echo "cm3 not detect.."
    else
        echo "cm3 detected ..."
        sleep 100
        DEVICE=$(sudo fdisk -l | grep 3909091328 | awk '{print $2}' | awk -F: '{print $1}')
        
        if [ ${#DEVICE} -eq 0 ]; then
            echo "usb enum fail"
        else
            echo "usb enum succ, dev: ${DEVICE}"
            sleep 2
            sudo dd if=/mnt/cm3_20181012.img of=${DEVICE} status=progress
        fi
    fi
    

done
