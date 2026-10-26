#!/usr/bin/env bash
# Reviewed patches -> scrub -> current registry -> make/check -> accounting -> one commit.
# land_make.py checks the per-function debt baseline after apply, before configure.
set -euo pipefail
exec nice -n 10 python3 "$(dirname "$0")/build/land_make.py" "$@"
