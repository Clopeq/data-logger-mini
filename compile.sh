#!/bin/bash
echo "Compiling project..."
mkdir build
cd build
make clean
cmake ..
make
cd ../
mv build/main ../main

