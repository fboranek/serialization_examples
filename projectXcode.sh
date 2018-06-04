#!/bin/sh
mkdir -p build-xcode-debug

cd build-xcode-debug;
cmake .. -G "Xcode" -DCMAKE_BUILD_TYPE=Debug  
