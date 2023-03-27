#!/usr/bin/env bash

set -euo pipefail

: ' This is the build helper script. This script will invoke
    the Conan installation, followed by CMake configuration
    then the build command.

    Usage: build_x86-64.sh CMAKE_PRESET CMAKE_EXTRA_ARGS...
'

if [ "$#" -lt 1 ]; then
    echo "Call the script with build preset"
    exit 1
fi

# build unix-deb by default
CMAKE_PRESET="${1}"

# shellcheck disable=SC2068
CMAKE_EXTRA_ARGS=${@:2}

# we want to expand the variables here
# to pass onto cmake
# shellcheck disable=SC2068
cmake --preset "${CMAKE_PRESET}" -DCMAKE_EXPORT_COMPILE_COMMANDS=On ${CMAKE_EXTRA_ARGS}

cmake --build --preset "${CMAKE_PRESET}" -j"$(nproc)"
  
