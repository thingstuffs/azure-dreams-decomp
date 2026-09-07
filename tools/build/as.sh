#!/usr/bin/env bash
# Assemble one split .s file (psyq libs / not-yet-decompiled data) -> .o.
# Runs the shiftjis preprocessor first so GNU as understands splat's directives.
# Usage: tools/as.sh <in.s> <out.o>
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
python3 "$ROOT/tools/asproc.py" < "$1" \
  | mipsel-linux-gnu-as -I"$ROOT/include" -march=r3000 -mtune=r3000 \
      -no-pad-sections -O1 -G0 -EL -o "$2" -
