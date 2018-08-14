#!/bin/bash

files=$(ls *.png)
echo $files

mkdir out

for file in $files
do
    convert $file  -define png:color-type=2  -rotate 270 out/$file
done
