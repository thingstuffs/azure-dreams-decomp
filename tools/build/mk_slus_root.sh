#!/usr/bin/env bash
# Create build_slus/: a view root in which the unmodified upstream SLUS build scripts run with
# src/ -> src/slus, tools/ -> tools/build, and the toolchain, venv and baserom taken from the
# upstream checkout named in .upstream (until they are provisioned here).  Everything generated
# (asm/, assets/, build/, build.ninja, config/generated) stays inside build_slus/ (gitignored).
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
UP="${AZURE_CLEAN_UPSTREAM:-$(cat "$ROOT/.upstream")}"
B="$ROOT/build_slus"; mkdir -p "$B/config"
ln -sfn "$ROOT/src/slus"      "$B/src"
ln -sfn "$ROOT/include"       "$B/include"
ln -sfn "$ROOT/tools/build"   "$B/tools"
ln -sfn "$UP/toolchain"       "$B/toolchain"
ln -sfn "$UP/.venv"           "$B/.venv"
ln -sfn "$UP/baserom"         "$B/baserom"
for f in slus_006.14.yaml slus_006.14.symbols.txt slus_006.14.sha1 names.tsv; do ln -sfn "$ROOT/config/$f" "$B/config/$f"; done
mkdir -p "$B/config/generated"
echo "build root: $B"
