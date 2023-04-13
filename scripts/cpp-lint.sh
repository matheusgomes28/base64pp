#!/usr/bin/env bash

set -euo pipefail

: ' This script will find all the cpp files
    and lint them using clang-format
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"

# Create the exclude regex by replacing spaces
# with the | (for or), and wrap the text in regex
# brackets
FILES_TO_EXCLUDE="base64pp_export.h"
FILE_EXCLUDE_REGEX="(${FILES_TO_EXCLUDE/ /|})"

# Find all cpp files and exclide the files
ALL_CPP_FILES="$(find "${PROJECT_DIR}" -iname "*.cpp" -o -iname "*.h")"
CPP_FILES_TO_LINT="$(echo "${ALL_CPP_FILES}" | grep -Ev "${FILE_EXCLUDE_REGEX}")"
echo "${CPP_FILES_TO_LINT}" | xargs clang-format -Werror --dry-run
