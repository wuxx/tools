#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)

FLASH_WRITE=/home/pi/oss/tools/jtag/stm32/flash_write.sh
PROBE_SH=/home/pi/oss/tools/jtag/stm32/probe.sh

FACTORY_TEST_IMAGE=${CURRENT_DIR}/image/factory_test.hex

#DAP_IMAGE=${CURRENT_DIR}/image/flash_image_cmsisdap_20181227.bin
#DAP_IMAGE=${CURRENT_DIR}/image/flash_image_daplink_soft_reset_20190428.bin
DAP_IMAGE=${CURRENT_DIR}/image/flash_image_daplink_soft_reset_20190429.bin

FACTORY_TEST_SH=${CURRENT_DIR}/rpi/factory_test.sh
BUZZER_SH=${CURRENT_DIR}/buzzer.sh

GPIO_SWCLK=25
GPIO_SWDIO=24

while [ 1 ]; do
    ${PROBE_SH}

    if [ $? -eq 0 ]; then

        echo aa
        ${FLASH_WRITE} ${FACTORY_TEST_IMAGE}
        if [ $? -ne 0 ]; then
            echo "flash write factory_test.hex fail!"
            ${BUZZER_SH} "fail" &
            #exit 1
        fi

        ${FACTORY_TEST_SH}
        if [ $? -ne 0 ]; then
            echo "factory test fail!"
            ${BUZZER_SH} "fail" &
            #exit 1
        fi
        
        ${FLASH_WRITE} ${DAP_IMAGE}
        if [ $? -ne 0 ]; then
            echo "flash write ${DAP_IMAGE} fail!"
            ${BUZZER_SH} "fail" &
            #exit 1
        fi

        ${BUZZER_SH} "succ" &
        gpio mode ${GPIO_SWDIO} in

        while [ 1 ]; do
            b=$(gpio read ${GPIO_SWDIO})
            if [ ${b} -eq 1 ]; then
                echo "wait target detach"
                sleep 0.5
            elif [ ${b} -eq 0 ]; then
                echo "target detached"
                break;
            else
                echo "unknown error"
                exit 1
            fi
        done

    else
        #echo "probe..."
        echo -n "."
        sleep 0.2

    fi
done

exit 0
