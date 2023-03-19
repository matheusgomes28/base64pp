#!/usr/bin/env bash

set -euo pipefail

: ' This script will find all the shell files
    and run shellcheck on them.
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"

SHELL_FILES="$(find "${PROJECT_DIR}" -name "*.sh")"
echo "${SHELL_FILES}" | xargs shellcheck
