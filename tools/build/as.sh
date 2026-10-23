#!/usr/bin/env bash
# Assemble one split .s file (psyq libs / not-yet-decompiled data) -> .o.
# Runs the shiftjis preprocessor first so GNU as understands splat's directives.
# Usage: tools/as.sh <in.s> <out.o>
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
# Standalone Ninja/gate compiles also use the shared pool. A make compile
# already owns a slot for the whole pipeline and passes its descriptor.
if [ -z "${AZURE_COMPILE_SLOT_FD:-}" ] && [ "${AZURE_COMPILE_LIMIT_ENABLED:-1}" != 0 ]; then
  exec python3 "$ROOT/tools/compile_slots.py" -- bash "${BASH_SOURCE[0]}" "$@"
fi
python3 "$ROOT/tools/asproc.py" < "$1" \
  | mipsel-linux-gnu-as -I"$ROOT/include" -march=r3000 -mtune=r3000 \
      -no-pad-sections -O1 -G0 -EL -o "$2" -
