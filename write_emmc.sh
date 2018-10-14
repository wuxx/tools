#!/bin/bash

cd ~/oss/usbboot

sudo ./rpiboot

DEVICE=$(sudo fdisk -l | grep 3909091328 | awk '{print $2}' | awk -F: '{print $1}')

if [ ${#DEVICE} -eq 0 ]; then
    echo "usb enum fail"
else
    echo "usb enum succ, dev: ${DEVICE}"
    sleep 2
    sudo dd if=/mnt/cm3_20181012.img of=${DEVICE} status=progress
fi
