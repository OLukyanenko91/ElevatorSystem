#! /bin/bash

cd ../
mkdir -p build
cd build
cmake ..
make -j$(nproc)

chmod -R 777 ../build
