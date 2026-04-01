#!/bin/sh

# Set build directory
BUILD_DIR=".build/debug"

# Create build directory
mkdir -p "$BUILD_DIR"

# Run CMake in Debug mode
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug -DENABLE_STM32=ON -DCMAKE_TOOLCHAIN_FILE=toolchain-arm-none-eabi.cmake

# Build the library
cmake --build "$BUILD_DIR"
