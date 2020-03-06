#!/bin/bash

rm fat-test.img
rm -rf ./mnt

#mkfs.fat -R 1 -S 512 -F 16 -C fat-test.img 10240
mkfs.fat -F 12 -S 512 -f 1 -s 1 -r 16 -C fat-test.img 64 #ok on linux, fail on windows
#mkfs.fat -F 12 -S 512 -f 2 -s 1 -r 32 -C fat-test.img 64 #fail on windows
#mkfs.fat -F 12 -S 4096 -f 1 -s 1 -r 16 -C fat-test.img 64
#mkfs.fat -F 12 -S 512 -f1 -r 16 fat-test.img

mkdir ./mnt
sudo mount -t vfat fat-test.img ./mnt
sudo cp *.txt ./mnt
sudo umount ./mnt
