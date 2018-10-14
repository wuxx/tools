#!/bin/bash

/home/share/oss/CuraEngine/build/CuraEngine slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -o ./banshou.gcode -l ./banshou.stl > banshou.log 2>&1
