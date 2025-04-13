#!/bin/bash

set -x

pushd "$(find out -type d | awk -F/ '{print NF, $0}' | sort -nr | head -n1 | cut -d' ' -f2-)"
./SpaceInvaders
popd
