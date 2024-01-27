#!/usr/bin/env bash

set -euo pipefail

: ' This file will install all the conan dependencies for the
    x86_64 architecture. In the future, this should use the
    Conan profiles.
'
PROJECT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_TYPE=${BUILD_TYPE-Debug}
COMPILER=${COMPILER-"gcc"}
COMPILER_STD=${COMPILER_STD-"17"}
COMPILER_LIBCXX=${COMPILER_LIBCXX-"libstdc++11"}
COMPILER_VERSION=${COMPILER_VERSION-"11"}

conan profile detect --force
sed -i "s/build_type=Release/build_type=${BUILD_TYPE}/g" "$(conan profile path default)"
sed -i "s/compiler=.*/compiler=${COMPILER}/g" "$(conan profile path default)"
sed -i "s/compiler.cppstd=.*/compiler.cppstd=${COMPILER_STD}/g" "$(conan profile path default)"
sed -i "s/compiler.libcxx=.*/compiler.libcxx=${COMPILER_LIBCXX}/g" "$(conan profile path default)"
sed -i "s/compiler.version=.*/compiler.version=${COMPILER_VERSION}/g" "$(conan profile path default)"


CONAN_DIR="${PROJECT_DIR}/conan/deb"
if [ "${BUILD_TYPE}" = "Release" ]; then
  CONAN_DIR="${PROJECT_DIR}/conan/rel"
fi

# Install all dependencies
CXX="${COMPILER}" CC="${COMPILER}" conan install \
  --output-folder="${CONAN_DIR}" \
  --build=missing \
  "${PROJECT_DIR}"
