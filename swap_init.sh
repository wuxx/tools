#!/bin/bash

#sudo swapoff /var/swap

#sudo dd if=/dev/zero of=swap bs=1M count=1024

sudo mkswap /var/swap

sudo swapon /var/swap

swapon -s

