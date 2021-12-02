#!/usr/bin/env bash

set -euo pipefail

: ' This file will install all the conan dependencies for the
    x86_64 architecture. In the future, this should use the
    Conan profiles.
'
PROJECT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

# Get the profile and save to file
PROFILE_FILE="${BUILD_DIR}/ubuntu_x86-64_gcc10"
if [ -f "${PROFILE_FILE}" ]; then
  rm "${PROFILE_FILE}"
fi

conan profile new "${PROFILE_FILE}"  --detect
conan profile update settings.compiler.libcxx=libstdc++11 "${PROFILE_FILE}"
conan profile update settings.build_type=Debug "${PROFILE_FILE}"

# Install all dependencies
conan install \
  --install-folder="${BUILD_DIR}" \
  --build=missing \
  --profile="${PROFILE_FILE}" \
  "${PROJECT_DIR}"
