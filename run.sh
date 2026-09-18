#!/bin/bash

# Default temperature setpoint
SETPOINT=65

# Use the first command-line argument if one was provided
if [ -n "$1" ]; then
    SETPOINT=$1
fi

echo "Building EAE Firmware..."

cmake --build build

if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

echo ""
echo "Running with temperature setpoint: $SETPOINT C"
echo ""

./build/eae_firmware.exe --setpoint "$SETPOINT"