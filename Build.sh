#!/bin/bash

# Default values
BUILD_TARGET=""
CLEAN=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        --build)
            shift
            if [[ "$1" == "Editor" || "$1" == "Runtime" ]]; then
                BUILD_TARGET="$1"
            else
                echo "Invalid argument for --build: $1"
                exit 1
            fi
            ;;
        --clean)
            CLEAN=true
            ;;
        *)
            echo "Unknown argument: $1"
            exit 1
            ;;
    esac
    shift
done

if [[ -z "$BUILD_TARGET" && $CLEAN == false ]]; then
    echo "Usage: $0 [--clean] --build <Editor|Runtime>"
    exit 1
fi

if $CLEAN; then
    echo "Cleaning build directory..."
    rm -rf build
    echo "Build directory cleaned."
fi

if [[ -n "$BUILD_TARGET" ]]; then
    # Function to build the target
    build_target() {
        local target="$1"
        local run_after="$2"
        echo "Building $target..."

        # Remove previous build artifact
        rm -rf "build/$target/$target"

        # Run CMake commands
        start_time=$(date +%s)

        cmake -B build -S .
        if [[ $? -ne 0 ]]; then
            echo "CMake configuration failed."
            exit 1
        fi

        cmake --build build -- -j 8
        if [[ $? -ne 0 ]]; then
            echo "CMake build failed."
            exit 1
        fi

        end_time=$(date +%s)
        elapsed_time=$((end_time - start_time))
        echo "Build completed in $elapsed_time seconds."

        if [[ "$run_after" != "true" ]]; then
            return
        fi

        if [[ ! -x "./build/$target/$target" ]]; then
            echo "Executable not found or not executable: ./build/$target/$target"
            exit 1
        fi

        echo
        echo "Running $target..."
        for _ in {1..2}; do echo; done

        # Run the executable if the build was successful
        if [[ -x "./build/$target/$target" ]]; then
            "./build/$target/$target"
            exit_code=$?

            echo
            echo "Executable exited with code $exit_code."
        else
            echo "Executable not found or not executable: ./build/$target/$target"
            exit 1
        fi
    }

    # Execute the build based on the target
    if [[ "$BUILD_TARGET" == "Editor" ]]; then
        build_target "Editor" true
    elif [[ "$BUILD_TARGET" == "Runtime" ]]; then
        build_target "Runtime" true
    fi
fi
