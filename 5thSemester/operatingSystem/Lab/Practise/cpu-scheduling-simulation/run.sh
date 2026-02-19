#!/bin/bash

# Clean previous build artifacts
echo "Cleaning previous build..."
rm -f vibe-cpu
rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile

# Compile
echo "Compiling..."
g++ -o vibe-cpu main.cpp src/*.cpp -I include

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running..."
    ./vibe-cpu
else
    echo "Compilation failed."
fi
