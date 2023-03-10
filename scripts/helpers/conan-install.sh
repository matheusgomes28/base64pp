#!/usr/bin/env bash

set -euo pipefail

: ' This file will install all the conan dependencies for the
    x86_64 architecture. In the future, this should use the
    Conan profiles.
'
PROJECT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"


conan profile detect --force
sudo sed -i 's/build_type=Release/build_type=Debug/g' /home/vsts_azpcontainer/.conan2/profiles/default


# Install all dependencies
conan install \
  --output-folder="${BUILD_DIR}" \
  --build=missing \
  "${PROJECT_DIR}"
