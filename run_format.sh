#!/bin/bash

set -x

find src/ -name '*.c' -o -name '*.h' | xargs clang-format -i
