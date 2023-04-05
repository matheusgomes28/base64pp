#!/usr/bin/env bash

set -euo pipefail

: ' This script will find run lcov to generate
    a report and then push it to codecov.

    TODO : Perhaps we should fail pipeline on
    a low coverage report!
'

THIS_DIR=$(cd "$(dirname "$0")" && pwd)
PROJECT_DIR="$(cd "${THIS_DIR}/.." && pwd)"

SYSTEM_DIR="/usr/"
CONAN_DIR="${HOME}/.conan2/"

lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info "${SYSTEM_DIR}*" --output-file coverage.info
lcov --remove coverage.info "${CONAN_DIR}*" --output-file coverage.info

# Assumes we have a secret
bash <(curl -s https://codecov.io/bash) -f coverage.info || $(echo "Codecov did not collect coverage reports" && exit 1)
