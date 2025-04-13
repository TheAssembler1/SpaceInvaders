#!/bin/bash

set -x
set -e

rm -rf build
rm -rf out

mkdir build
mkdir out

pushd build
cmake ..
make -j 4
popd
