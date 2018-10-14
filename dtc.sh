#!/bin/bash

#dtb -> dts

if [ ${#1} -eq 0 ]; then
    echo "$0 xxx.dtb"
    exit 1
fi

OBJ=${1%%.dtb}

dtc -I dtb -O dts ${OBJ}.dtb > ${OBJ}.dts
