#!/bin/bash

STLFILE=screw.stl

/home/share/oss/CuraEngine/build/CuraEngine slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -o ${STLFILE%%stl}gcode -l ${STLFILE} > ${STLFILE%%stl}log 2>&1
