#!/bin/bash

CURAENGINE=/home/share/private/DeepinDeviceClient/CuraEngine/build/CuraEngine
STLFILE=twist.stl

${CURAENGINE} slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -s didumplayer="true" -s didumpdirname="${STLFILE%%.stl}" -o ${STLFILE%%stl}gcode -l ${STLFILE} > ${STLFILE%%stl}log 2>&1
#${CURAENGINE} slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -s didumplayer="true" -s didumpdirname="test" -o ${STLFILE%%stl}gcode -l ${STLFILE} > ${STLFILE%%stl}log 2>&1

tar -zcvf  ${STLFILE%%.stl}.tar.gz  ${STLFILE%%.stl}
