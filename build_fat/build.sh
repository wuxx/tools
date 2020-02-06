#!/bin/bash

rm fat-test.img
rm -rf ./mnt

mkfs.fat -S 512 -F 16 -C fat-test.img 10240
mkdir ./mnt
sudo mount -t vfat fat-test.img ./mnt
sudo cp *.txt ./mnt
sudo umount ./mnt
