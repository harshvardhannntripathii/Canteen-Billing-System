#!/bin/bash
# Smart Canteen Billing System - Compile and Run Script
# This script compiles the C program and runs it
# Usage: ./compile_and_run.sh

echo "=========================================="
echo "Smart Canteen Billing System - Build Script"
echo "=========================================="
echo

# Check if GCC is available
if ! command -v gcc &> /dev/null; then
    echo "ERROR: GCC compiler not found"
    echo "Please install GCC:"
    echo "  Ubuntu/Debian: sudo apt-get install gcc"
    echo "  Mac: xcode-select --install"
    echo "  Fedora: sudo dnf install gcc"
    exit 1
fi

echo "Compiling canteen_billing.c..."
gcc canteen_billing.c -o canteen_billing

if [ $? -ne 0 ]; then
    echo
    echo "ERROR: Compilation failed!"
    echo "Please check the code for errors."
    exit 1
fi

echo
echo "Compilation successful!"
echo
echo "Running Smart Canteen Billing System..."
echo "=========================================="
echo

./canteen_billing

echo
echo "=========================================="
echo "Program finished."