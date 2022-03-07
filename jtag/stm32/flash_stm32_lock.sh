#!/bin/bash

#set -o errexit

trap 'onCtrlC' INT
function onCtrlC () {
    echo 'exit'
    exit 1
}

CURRENT_DIR=$(cd $(dirname $0); pwd)

#/home/pi/oss/tools/jtag/stm32/unlock.sh

$CURRENT_DIR/wait_and_probe.sh

#/home/pi/oss/tools/jtag/stm32/probe.sh
#if [ $? -ne 0 ]; then
#echo "probe fail!"
#exit 1
#fi

#BUZZER_GPIO=4 #wiringPi
BUZZER_GPIO=23 #BCM

#gpio mode $BUZZER_GPIO out
raspi-gpio set $BUZZER_GPIO op

function buzzer_succ () {
    #gpio write $BUZZER_GPIO 1
    raspi-gpio set $BUZZER_GPIO dh
    sleep 0.1
    raspi-gpio set $BUZZER_GPIO dl
    sleep 0.1
}

function buzzer_fail () {
    for((i=0;i<3;i++)); do
        raspi-gpio set $BUZZER_GPIO dh
        sleep 0.1
        raspi-gpio set $BUZZER_GPIO dl
        sleep 0.1
    done

}


/home/pi/oss/tools/jtag/stm32/flash_write.sh $1
if [ $? -ne 0 ]; then
    echo -e "\033[31m---------- write fail! ----------\033[0m"
    buzzer_fail
    exit 1
else
    echo -e "\033[32m---------- write succ! ----------\033[0m"
fi

/home/pi/oss/tools/jtag/stm32/lock.sh
if [ $? -ne 0 ]; then
    echo -e "\033[31m---------- lock fail! ----------\033[0m"
    buzzer_fail
    exit 1
else
    echo -e "\033[32m---------- lock succ! ----------\033[0m"
    buzzer_succ
fi

$CURRENT_DIR/wait_detach.sh
