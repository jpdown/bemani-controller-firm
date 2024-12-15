#!/bin/bash

DO_CLEAN=false
NUKE_SDK=false

while getopts csn flag
do
    case "${flag}" in
        c) 
            DO_CLEAN=true
            ;;
        s) 
            NUKE_SDK=true
            ;;
        n)
            DO_CLEAN=true
            NUKE_SDK=true
            ;;
    esac
done

if [ $DO_CLEAN = true ]; then
    rm -rf build
fi

if [ $NUKE_SDK = true ]; then
    rm -rf pico
fi

if [ ! -d build ]; then
    ./setup-env.sh
fi

cmake -B build
cd build
make -j$(nproc)
