#!/bin/bash

# https://linuxhint.com/return-string-bash-functions/

function F1()
{
    retval='I like programming'
}


retval='I hate programming'
echo $retval
F1
echo $retval
