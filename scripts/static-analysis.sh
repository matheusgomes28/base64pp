#!/usr/bin/env bash

set -euo pipefail

: ' This script will run clang-tidy on the
    current build based on the compilation
    database compile_commands.json in the
    build dir
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/build/unix-deb"

# provided with the clang suite. this
# manages the calls to "clang-tidy" and
# runs things in parallel.
run-clang-tidy -p "${BUILD_DIR}"
