#!/bin/sh

# Set build directory
BUILD_DIR=".build/release"

# Create build directory
mkdir -p "$BUILD_DIR"

# Run CMake in Debug mode
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release -DENABLE_ROS2=ON

# Build the library
cmake --build "$BUILD_DIR"
