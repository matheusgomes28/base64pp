#!/usr/bin/env bash

set -euo pipefail

: ' This is the build helper script. This script will invoke
    the Conan installation, followed by CMake configuration
    then the build command.
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

# upgrade cmake
wget https://github.com/Kitware/CMake/releases/download/v3.25.3/cmake-3.25.3-linux-x86_64.sh
bash cmake-3.25.3-linux-x86_64.sh --skip-license
sudo cp bin/* /usr/bin/
cmake --version

# configure the project
cmake \
  -B "${BUILD_DIR}" \
  -DCMAKE_MODULE_PATH:FILEPATH="${BUILD_DIR}" \
  "${PROJECT_DIR}"


cmake \
  --build "${BUILD_DIR}" \
  -j"$(nproc)"
  
