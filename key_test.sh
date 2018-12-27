#!/bin/bash

UART_SEND=./uart_send
<<<<<<< HEAD
DEVICE=/dev/ttyACM1

COUNT=0

=======
DEVICE=/dev/ttyACM0

COUNT=0

#${UART_SEND} ${DEVICE} "G90"

>>>>>>> 3fec14219e625d7cedd8624dd663a406bf7ad7c9
while [ 1 ]; do
    echo "[$COUNT]"
    ${UART_SEND} ${DEVICE} "G1 Z10"
    sleep 5
    ${UART_SEND} ${DEVICE} "G1 Z0.0"
<<<<<<< HEAD
    sleep 1

    ((COUNT++));
=======
    sleep 5

    #((COUNT++));
    COUNT=$(( $COUNT + 1 ))

>>>>>>> 3fec14219e625d7cedd8624dd663a406bf7ad7c9

done
