#!/bin/bash

# Set build directory
BUILD_DIR=".build/release"

# Create build directory
mkdir -p "$BUILD_DIR"

# Run CMake in Release mode
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

# Build the library
cmake --build "$BUILD_DIR"

