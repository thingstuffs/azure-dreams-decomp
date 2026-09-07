#!/usr/bin/env bash
# Compile one C translation unit through the pinned Azure Dreams pipeline:
#   gcc 2.7.2 -O2 -S  ->  ccproc (per-function sections)  ->  maspsx (aspsx 2.56)  ->  mipsel as
# Usage: tools/cc.sh <in.c> <out.o>
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
# Azure Dreams is a multi-compiler binary — some TUs are gcc 2.8.x. The per-file
# version is passed as $3 (default 2.7.2); see tools/configure.py CC_VER.
IN="$1"; OUT="$2"; CCVER="${3:-2.7.2}"; CCFLAGS="${4:-}"; MASPSX_FLAGS="${5:-}"
CC_DIR="$ROOT/toolchain/compilers/gcc-$CCVER"
# $AZURE_MASPSX_COMPANION is the long-standing per-TU companion hook; $AZURE_MASPSX
# is the whole-pipeline override tools/match.py honours (name-blind measurement
# runs).  Companion wins when both are set; neither -> the live toolchain copy.
MASPSX_BIN="${AZURE_MASPSX_COMPANION:-${AZURE_MASPSX:-$ROOT/toolchain/maspsx/maspsx.py}}"
TMP="$(mktemp --suffix=.s)"
trap 'rm -f "$TMP"' EXIT
# $CCFLAGS is intentionally unquoted so a multi-flag string word-splits.
"$CC_DIR/gcc" -B"$CC_DIR/" -S -O2 $CCFLAGS -I"$ROOT/include" -w "$IN" -o "$TMP"
# $MASPSX_FLAGS is intentionally unquoted so a multi-flag string word-splits.
python3 "$ROOT/tools/ccproc.py" < "$TMP" \
  | "$ROOT/.venv/bin/python" "$MASPSX_BIN" --aspsx-version=2.56 --dont-force-G0 \
      --run-assembler --gnu-as-path=mipsel-linux-gnu-as \
      -I"$ROOT" -I"$ROOT/include" -EL -march=r3000 -G8 $MASPSX_FLAGS -o "$OUT"
