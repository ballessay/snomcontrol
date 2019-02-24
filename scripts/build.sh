#!/bin/bash

mkdir build
cd build

qmake ../snomcontrol.pro CONFIG+=release
make -j

cd -
