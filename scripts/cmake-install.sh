#!/usr/bin/env bash

set -euo pipefail

: ' This script preprares the environment for a
    cmake installation. This assumes that we are
    using one of the config/build presets given
    by CMakePresets.json, given as an input in
    this script.

    Usage: ./cmake-install.sh PRESET_NAME
'

if [ "$#" -lt 1 ]; then
    echo "Call the script with build preset"
    exit 1
fi

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_DIR}/${1}"

cmake install "${BUILD_DIR}" --install-prefix "${BUILD_DIR}/install"
