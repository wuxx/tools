#!/bin/bash

UV_CHAMBER_DIR=/home/pi/private/git/uv_chamber
FLASH_DIR=/home/pi/oss/tools/jtag/stm32

log() {
    curl http://127.0.0.1:8080/log/$1
}


cd $UV_CHAMBER_DIR

git pull

TAG=$(git describe --tags `git rev-list --tags --max-count=1`)

SSID=$(iwgetid -r)
IP=$(hostname -I)

log "SSID:$SSID"
log "IP:$IP"

log "VER:$TAG"

while [ 1 ]; do


    REQ_UPGRADE=$(gpio read 7)
    if [ ${REQ_UPGRADE} -eq 0 ]; then
        log "upgrade%20start"
        $FLASH_DIR/flash.sh $FLASH_DIR/LED_1000.hex
        log "upgrade%20end"
        log "succ"

        REQ_RESTART=$(gpio read 7)
        echo $REQ_RESTART
        if [ ${REQ_RESTART} -eq 0 ]; then
            log "restart"
            exit 0
        fi
    fi

done
