#!/bin/bash

MOTOR_CTRL=./actuator

while [ 1 ]; do
    $MOTOR_CTRL 0
    sleep 1
    $MOTOR_CTRL 5
    sleep 1
done
