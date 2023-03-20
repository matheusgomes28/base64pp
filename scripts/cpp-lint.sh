#!/usr/bin/env bash

set -euo pipefail

: ' This script will find all the cpp files
    and lint them using clang-format
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"

CPP_FILES="$(find "${PROJECT_DIR}" -iname "*.cpp" -o -iname "*.h")"
echo "${CPP_FILES}"
echo "${CPP_FILES}" | xargs clang-format -Werror --dry-run
