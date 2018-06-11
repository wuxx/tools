#!/bin/bash


export DESKTOP_SESSION=LXDE

while [ 1 ]; do
    date
    timeout 300 /usr/local/bin/himawaripy

    if [ $? -ne 0 ]; then
        echo "download fail: timeout!"
    else
        echo "download succ!"
        sleep 300
    fi


done


