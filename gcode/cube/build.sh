#!/bin/bash

/home/share/oss/CuraEngine/build/CuraEngine slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -s support_skip_some_zags=on -s support_enable=1 -s support_type=everywhere -s support_angle=30 -o ./cube1_support_everywhere.gcode -l ./cube1.stl > cube1_support_everywhere.slicelog 2>&1

/home/share/oss/CuraEngine/build/CuraEngine slice -vvvvv -p -j /home/share/oss/Cura/resources/definitions/prusa_i3.def.json -s support_skip_some_zags=on -s support_enable=1 -s support_type=buildplate -s support_angle=30 -o ./cube1_support_buildplate.gcode -l ./cube1.stl > cube1_support_buildplate.slicelog 2>&1
