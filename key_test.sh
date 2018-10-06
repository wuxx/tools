#!/bin/bash

UART_SEND=./uart_send
DEVICE=/dev/ttyACM1

COUNT=0

while [ 1 ]; do
    echo "[$COUNT]"
    ${UART_SEND} ${DEVICE} "G1 Z10"
    sleep 5
    ${UART_SEND} ${DEVICE} "G1 Z0.0"
    sleep 1

    ((COUNT++));

done
