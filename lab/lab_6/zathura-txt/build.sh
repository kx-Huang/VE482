#!/bin/bash
meson build
cd build
ninja
ninja install
cd ..
zathura -p /usr/local/opt/zathura/lib/zathura demo/hello_world.txt
