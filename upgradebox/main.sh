#!/bin/bash

UV_CHAMBER_DIR=/home/pi/private/git/uv_chamber_release
FLASH_DIR=/home/pi/oss/tools/jtag/stm32

log() {
    curl http://127.0.0.1:8080/log/$1
}


cd $UV_CHAMBER_DIR

TAG=$(git describe --tags `git rev-list --tags --max-count=1`)

SSID=$(iwgetid -r)
IP=$(hostname -I)

log "SSID:$SSID"
log "IP:$IP"
log "UV_CHAMBER"
log "VER:$TAG"

log "------READY--------"

while [ 1 ]; do

    REQ_UPGRADE=$(gpio read 7)
    if [ ${REQ_UPGRADE} -eq 0 ]; then
        log "us"
        $FLASH_DIR/flash_write.sh ${UV_CHAMBER_DIR}/flash_image.bin
        if [ $? -eq 0 ]; then
            #log "ue"
            log "SUCC"
        else
            #log "ue"
            log "FAIL"
        fi

        REQ_RESTART=$(gpio read 7)
        echo $REQ_RESTART
        if [ ${REQ_RESTART} -eq 0 ]; then
            log "restart..."
            log "-------------------"
            exit 0
        fi
        log "-RDY-"
    fi

done
