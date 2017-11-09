#!/bin/bash

STLFILE=guitar.stl

/home/share/oss/CuraEngine/build/CuraEngine slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -s wireframe_enabled="true" -o ${STLFILE%%stl}gcode -l ${STLFILE} > ${STLFILE%%stl}log 2>&1
