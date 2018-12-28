#!/bin/bash

if [ ${#1} -eq 0 ]; then
    echo "usage: $0 [succ|fail]"
    exit 1
fi

GPIO_BUZZER=6
gpio mode ${GPIO_BUZZER} out

if [ "$1" == "succ" ]; then #beep one time

    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
elif [ "$1" == "fail" ]; then #beep two time
    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
    sleep 0.1
    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
else
    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
    sleep 0.1
    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
    sleep 0.1

    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
    sleep 0.1
    gpio write ${GPIO_BUZZER} 0
    sleep 0.05
    gpio write ${GPIO_BUZZER} 1
    sleep 0.1

fi

exit 0
