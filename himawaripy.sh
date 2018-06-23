#!/bin/bash


export DESKTOP_SESSION=LXDE

while [ 1 ]; do
    date
    #rm /homm/pi/.cache/himawaripy/*.png

    YESTERDAY=`date -d '1 days ago' +%F`
    find /home/pi/.cache/himawaripy/ -type f -newermt "${YESTERDAY} 00:00:00" ! -newermt "${YESTERDAY} 23:59:59" | xargs rm
    #find /home/pi/.cache/himawaripy/ -type f -newermt "2018-06-14 00:00:00" ! -newermt "2018-06-14 23:59:59"
    #find /home/pi/.cache/himawaripy/ -type f -newermt `date -d '1 days ago' +%F` | xargs rm

    timeout 300 /usr/local/bin/himawaripy

    if [ $? -ne 0 ]; then
        echo "download fail: timeout!"
    else
        echo "download succ!"
        sleep 300
    fi


done


