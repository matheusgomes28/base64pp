#!/usr/bin/env bash

set -euo pipefail

: ' This file will install all the conan dependencies for the
    x86_64 architecture. In the future, this should use the
    Conan profiles.
'
PROJECT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_TYPE=${1-Debug}

conan profile detect --force
sed -i "s/build_type=Release/build_type=${BUILD_TYPE}/g" "$(conan profile path default)"


CONAN_DIR="${PROJECT_DIR}/conan/deb"
if [ "${BUILD_TYPE}" = "Release" ]; then
  CONAN_DIR="${PROJECT_DIR}/conan/rel"
fi

# Install all dependencies
conan install \
  --output-folder="${CONAN_DIR}" \
  --build=missing \
  "${PROJECT_DIR}"
