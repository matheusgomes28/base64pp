#!/usr/bin/env bash

set -euo pipefail

: ' This is the build helper script. This script will invoke
    the Conan installation, followed by CMake configuration
    then the build command.
'

# we want to expand the variables here
# to pass onto cmake
# shellcheck disable=SC2068
cmake --preset "unix-deb" $@

cmake --build --preset "unix-deb" -j"$(nproc)"
  
