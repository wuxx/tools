#!/bin/bash

#IP=$(ifconfig wlan0 | grep "inet " | awk '{ print $2}')
#rm /home/pi/Desktop/ip_*.txt
#ifconfig wlan0 >> /home/pi/Desktop/test.txt
#touch /home/pi/Desktop/ip_${IP}.txt

while [ 1 ]; do

    echo "check ssh tunnel"
    #ps aux | grep TCPKeepAlive | grep -v grep
    ps aux | grep autossh | grep -v grep
    if [ $? -ne 0 ]; then
        echo "start ssh tunnel"
        #ssh -N -f -o TCPKeepAlive=yes -R 2222:127.0.0.1:22  root@123.56.12.242
        #ssh -N -f -o "StrictHostKeyChecking no" -R 2222:127.0.0.1:22  tester@123.56.12.242
        #autossh -M 2221 -NR 2222:localhost:22 tester@123.56.12.242 -p 22
        autossh -M 6661 -NR 6662:localhost:22 root@123.56.12.242 -p 22
    else
        echo "ssh tunnel already open, sleep... "
        sleep 60
    fi

done
