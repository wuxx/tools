#!/bin/bash
 
DIR=/home/pi/tools
WLAN_IP=$(curl -s -u admin:admin http://192.168.1.1/userRpm/StatusRpm.htm | grep -A1 "6C-E8-73-6F-A6-D5" | tail -n 1 | sed 's/,//')

echo ${WLAN_IP}

if [ "$1" = "--commit" ]; then
    DATE=$(date)
    echo "${DATE} $WLAN_IP" >> ${DIR}/README.md
    cd ${DIR}
    git add -A
    git commit -m "update"
    git push origin master
fi12
