#!/bin/bash

disasm_file=$1

machine_code=$(cat $disasm_file | awk '{print $2}' | tr -d "\n")
#echo $machine_code | sed 's/[[:space:]]//g'

echo $machine_code
echo $machine_code | sed 's/.\{2\}/\\x&/g'
