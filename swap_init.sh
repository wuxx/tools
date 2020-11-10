#!/bin/bash

sudo swapoff /var/swap

sudo dd if=/dev/zero of=/var/swap bs=1M count=4096

sudo mkswap /var/swap

sudo swapon /var/swap

swapon -s

