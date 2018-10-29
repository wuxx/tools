#!/bin/bash

UART_SEND=./uart_send
DEVICE=/dev/ttyACM0

COUNT=0

#${UART_SEND} ${DEVICE} "G90"

while [ 1 ]; do
    echo "[$COUNT]"
    ${UART_SEND} ${DEVICE} "G1 Z10"
    sleep 5
    ${UART_SEND} ${DEVICE} "G1 Z0.0"
    sleep 5

    #((COUNT++));
    COUNT=$(( $COUNT + 1 ))


done
