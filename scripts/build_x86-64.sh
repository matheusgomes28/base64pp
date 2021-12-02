#!/usr/bin/env bash

set -euo pipefail

: ' This is the build helper script. This script will invoke
    the Conan installation, followed by CMake configuration
    then the build command.
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"


# configure the project
cmake \
  -B "${BUILD_DIR}" \
  -DCMAKE_MODULE_PATH:FILEPATH="${BUILD_DIR}" \
  "${PROJECT_DIR}"


cmake \
  --build "${BUILD_DIR}" \
  -j"$(nproc)"
  
