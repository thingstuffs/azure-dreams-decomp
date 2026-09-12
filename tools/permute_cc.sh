#!/usr/bin/env bash
# One TU through the scorer's pipeline, for decomp-permuter's compile.sh (tools/permute_pins.py):
#   gcc <cell> -O2 -S <flags>  ->  ccproc  ->  maspsx (aspsx 2.56) + as  ->  <out.o>
# the same pipeline tools/verify.py::compile_slus runs.  The permuter only compares a candidate's
# object with a target object built HERE from the row's pinned (byte-exact) text, so the two always
# share this pipeline; the final verdict on any candidate is still tools/verify.py.
#
# Usage: tools/permute_cc.sh <in.c> <out.o> <cell> "<gcc flags>" "<maspsx flags>"
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
IN="$1"; OUT="$2"; CELL="$3"; FLAGS="${4:-}"; ASFLAGS="${5:-}"
CC_DIR="$ROOT/toolchain/compilers/gcc-$CELL"
TMP="$(mktemp --suffix=.s)"
trap 'rm -f "$TMP"' EXIT
# $FLAGS / $ASFLAGS are intentionally unquoted: a multi-flag string word-splits.
"$CC_DIR/gcc" -B"$CC_DIR/" -S -O2 $FLAGS -I"$ROOT/include" -w "$IN" -o "$TMP"
python3 "$ROOT/tools/build/ccproc.py" < "$TMP" \
  | "$ROOT/.venv/bin/python" "$ROOT/tools/maspsx/maspsx.py" --aspsx-version=2.56 --dont-force-G0 \
      --run-assembler --gnu-as-path=mipsel-linux-gnu-as \
      -I"$ROOT" -I"$ROOT/include" -EL -march=r3000 -G8 $ASFLAGS -o "$OUT"
