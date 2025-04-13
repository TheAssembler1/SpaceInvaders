#!/bin/bash

set -x
set -e

pushd build
make -j 4
popd
