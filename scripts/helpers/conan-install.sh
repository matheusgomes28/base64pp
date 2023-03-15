#!/usr/bin/env bash

set -euo pipefail

: ' This file will install all the conan dependencies for the
    x86_64 architecture. In the future, this should use the
    Conan profiles.
'
PROJECT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

BUILD_TYPE=${1-Debug}

conan profile detect --force
echo "!!!profile: $(conan profile show)"
sed -i "s/build_type=Release/build_type=${BUILD_TYPE}/g" "$(conan profile show)"


CONAN_DIR="conan-deb"
if [ "${BUILD_TYPE}" = "release" ]; then
  CONAN_DIR="conan-rel"
fi

# Install all dependencies
conan install \
  --output-folder="${CONAN_DIR}" \
  --build=missing \
  "${PROJECT_DIR}"
