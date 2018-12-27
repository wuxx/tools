#!/bin/bash

#watch directry, if the size of directory exceed SIZE, delete from the oldest file.
#until the directory size <= SIZE

if [ ${#1} -eq 0 ] || [ ${#2} -eq 0 ]; then
    echo "$0 [DIR] [SIZE]"
    exit 1
fi
DIR=$1
SIZE=$2

cd ${DIR}

while [ 1 ]; do

    DIR_SIZE=$(du -s  . | awk  '{print $1}')

    if [ ${DIR_SIZE} -gt ${SIZE} ]; then
        echo "dir size [${DIR_SIZE}] > [${SIZE}] start delete the oldest file"
        files=$(ls -tr | head -4)
        echo "delete [$files]"
        sleep 10
        rm ${files}
    else
        echo "dir size [${DIR_SIZE}] safe ( <= [$SIZE])"
    fi

    sleep 15
done
