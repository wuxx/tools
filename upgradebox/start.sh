#!/bin/bash

OLED_DIR=/home/pi/oss/tools/oled

CURRENT_DIR=$(cd $(dirname $0); pwd)

cd ${OLED_DIR}
python server.py &

sleep 5
cd ${CURRENT_DIR}
while [ 1 ]; do
    ./main.sh
done

