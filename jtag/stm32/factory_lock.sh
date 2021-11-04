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


CURRENT_DIR=$(cd $(dirname $0); pwd)

while [ 1 ];
do
    $CURRENT_DIR/flash_stm32_lock.sh $1
done

