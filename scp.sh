#!/bin/bash

remote_dir=root@1.2.3.4:/home/share/oss/CuraEngine

local_files=$(git status | grep modified | awk '{print $2}')

echo "[$local_files]"

for file in $local_files
do
    echo "copy $file..."
    scp $file ${remote_dir}/${file}
done
