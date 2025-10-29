#!/bin/bash
echo "Compiling project.."
git pull
mkdir build
cd build
make clean
cmake ..
make
cd ../
# mv build/main ../main

