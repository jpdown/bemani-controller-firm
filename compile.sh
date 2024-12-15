#!/bin/bash

DO_CLEAN=false

while getopts c flag
do
    case "${flag}" in
        c) DO_CLEAN=true
    esac
done

if [ $DO_CLEAN = true ]; then
    rm -rf build
fi

if [ ! -d build ]; then
    ./setup-env.sh
fi

cmake -B build
cd build
make -j$(nproc)
