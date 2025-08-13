#!/bin/sh

rm -rf build
mkdir -p build/
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake -DCMAKE_BUILD_TYPE=Debug
make -C build VERBOSE=1