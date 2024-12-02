#!/bin/bash

if [ "$1" == "Editor" ]; then
    echo "Building Editor..."

    cd Editor

    cmake -B build -S .
    cmake --build build

    for _ in {1..2}; do echo; done

    ./build/Editor

elif [ "$1" == "Runtime" ]; then
    echo "Building Runtime..."

    cd Runtime

    cmake -B build -S .
    cmake --build build
    
    for _ in {1..2}; do echo; done

    ./build/Runtime
else
    echo "Done."
fi