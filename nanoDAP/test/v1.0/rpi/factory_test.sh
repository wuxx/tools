#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)

UART_SEND=${CURRENT_DIR}/tools/uart_send

STM32_GPIO_LED=PB13

STM32_GPIO_TCK_SWCLK=PA4
STM32_GPIO_TMS_SWDIO=PA0
STM32_GPIO_TDI=PA7
STM32_GPIO_TDO=PA5
STM32_GPIO_nRST=PA6

RPI3B_GPIO_TCK_SWCLK=2
RPI3B_GPIO_TMS_SWDIO=0
RPI3B_GPIO_TDI=3
RPI3B_GPIO_TDO=1
RPI3B_GPIO_nRST=4

GPIO_MAP=("TCK_SWCLK" "TMS_SWDIO" "TDI" "TDO" "nRST")

STM32_GPIO_MAP=("$STM32_GPIO_TCK_SWCLK" "$STM32_GPIO_TMS_SWDIO" "$STM32_GPIO_TDI" "$STM32_GPIO_TDO" "$STM32_GPIO_nRST")
RPI3B_GPIO_MAP=("$RPI3B_GPIO_TCK_SWCLK" "$RPI3B_GPIO_TMS_SWDIO" "$RPI3B_GPIO_TDI" "$RPI3B_GPIO_TDO" "$RPI3B_GPIO_nRST")

function stm32_gpio_write() {
    gpio_num=$1
    b=$2
    ${UART_SEND} "gpio init ${gpio_num} out"
    ${UART_SEND} "gpio write ${gpio_num} ${b}"
}

function rpi3b_gpio_read() {
    gpio_num=$1
    gpio mode ${gpio_num} in
    b=$(gpio read ${gpio_num})
    #echo "gpio read ${gpio_num} return ${b}"
    return ${b}
}

#1 uart basic test
RV=$($UART_SEND "r 0x08000000" "-d")
echo $RV | grep "ATE"
if [ $? -eq 0 ]; then
    echo "uart ok"
else
    echo "uart error"
    exit 1
fi


#2 light the led
stm32_gpio_write "${STM32_GPIO_LED}" "1"

#3 gpio test
for((i=0;i<${#STM32_GPIO_MAP[@]};i++))
do
    echo -n "gpio test: [${GPIO_MAP[i]}] "
    stm32_gpio_write "${STM32_GPIO_MAP[i]}" "0"
    rpi3b_gpio_read  "${RPI3B_GPIO_MAP[i]}"
    if [ $? -ne 0 ]; then
        echo "0 fail!"
        exit 1
    fi

    stm32_gpio_write "${STM32_GPIO_MAP[i]}" "1"
    rpi3b_gpio_read  "${RPI3B_GPIO_MAP[i]}"
    if [ $? -ne 1 ]; then
        echo "1 fail!"
        exit 1
    fi
    echo " succ"
done
