#!/bin/bash

./pad USART.bin 8192
./build_cmd USART.bin 0x20002000 > USART.txt
