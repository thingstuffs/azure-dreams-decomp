#!/usr/bin/env bash
# Create build_slus/: a view root in which the unmodified upstream SLUS build scripts run with
# src/ -> src/slus, tools/ -> tools/build, and the toolchain, venv and baserom from this tree
# (tools/setup.sh provisions them).  Everything generated (asm/, assets/, build/, build.ninja,
# config/generated) stays inside build_slus/ (gitignored).
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
B="$ROOT/build_slus"; mkdir -p "$B/config"
for need in toolchain/compilers/gcc-2.7.2/cc1 .venv/bin/splat baserom/slus_006.14 tools/maspsx/maspsx.py; do
  [ -e "$ROOT/$need" ] || { echo "missing $need: run tools/setup.sh" >&2; exit 1; }
done
ln -sfn "$ROOT/src/slus"      "$B/src"
ln -sfn "$ROOT/include"       "$B/include"
ln -sfn "$ROOT/tools/build"   "$B/tools"
ln -sfn "$ROOT/toolchain"     "$B/toolchain"
ln -sfn "$ROOT/.venv"         "$B/.venv"
ln -sfn "$ROOT/baserom"       "$B/baserom"
for f in slus_006.14.yaml slus_006.14.symbols.txt slus_006.14.sha1 names.tsv; do ln -sfn "$ROOT/config/$f" "$B/config/$f"; done
mkdir -p "$B/config/generated"
echo "build root: $B"
