#!/bin/bash

while [ 1 ]; do

    echo "check ssh tunnel"
    ps aux | grep TCPKeepAlive | grep -v grep
    if [ $? -ne 0 ]; then
        echo "start ssh tunnel"
        ssh -N -f -o TCPKeepAlive=yes -R 2222:127.0.0.1:22  root@123.56.12.242
    else
        echo "ssh tunnel already open, sleep... "
        sleep 60
    fi

done
