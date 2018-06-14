#!/bin/bash


export DESKTOP_SESSION=LXDE

while [ 1 ]; do
    date
    #rm /homm/pi/.cache/himawaripy/*.png

    find . -type f -newermt `date -d '1 days ago' +%F` | xargs rm

    timeout 300 /usr/local/bin/himawaripy

    if [ $? -ne 0 ]; then
        echo "download fail: timeout!"
    else
        echo "download succ!"
        sleep 300
    fi


done


