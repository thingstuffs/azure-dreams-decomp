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
if [ -L "$B/raw" ]; then echo "unsafe symlink: $B/raw" >&2; exit 1; fi
mkdir -p "$B/raw"
if [ -e "$B/raw/slus" ] && [ ! -L "$B/raw/slus" ]; then
  echo "refusing to replace $B/raw/slus" >&2; exit 1
fi
ln -sfn "$ROOT/raw/slus" "$B/raw/slus"
# A directory symlink makes src/../build resolve outside this build root.
# Active partition aggregators include generated bodies there, so expose their
# canonical files through a managed real directory (as SlusView already does).
python3 - "$ROOT" "$B" <<'PY_SRC_VIEW'
import os, sys
from pathlib import Path
root, build = map(Path, sys.argv[1:])
canonical = root / "src/slus"
view = build / "src"
marker = build / ".partition_src_view"
active = (root / "config/slus_partitions.json").is_file()
if view.is_symlink():
    if view.resolve() != canonical.resolve():
        raise SystemExit("refusing unrelated source symlink: " + str(view))
elif view.is_dir():
    if not marker.is_file():
        raise SystemExit("refusing unmanaged source directory: " + str(view))
    for entry in view.iterdir():
        if not entry.is_symlink() or os.readlink(entry) != str(canonical / entry.name):
            raise SystemExit("refusing modified source view entry: " + str(entry))
elif view.exists():
    raise SystemExit("refusing non-directory source view: " + str(view))
if active:
    if view.is_symlink():
        view.unlink()
    view.mkdir(exist_ok=True)
    wanted = {entry.name for entry in canonical.iterdir()}
    for entry in view.iterdir():
        if entry.name not in wanted:
            entry.unlink()
    for name in sorted(wanted):
        entry = view / name
        if not entry.is_symlink():
            entry.symlink_to(canonical / name)
    marker.write_text("canonical per-file symlinks for SLUS partitions\n")
else:
    if view.is_dir() and not view.is_symlink():
        for entry in view.iterdir():
            entry.unlink()
        view.rmdir()
    if not view.is_symlink():
        view.symlink_to(canonical)
    marker.unlink(missing_ok=True)
PY_SRC_VIEW
ln -sfn "$ROOT/include"       "$B/include"
ln -sfn "$ROOT/tools/build"   "$B/tools"
ln -sfn "$ROOT/toolchain"     "$B/toolchain"
ln -sfn "$ROOT/.venv"         "$B/.venv"
ln -sfn "$ROOT/baserom"       "$B/baserom"
for f in slus_006.14.yaml slus_006.14.symbols.txt slus_006.14.sha1 names.tsv slus_modules.json; do ln -sfn "$ROOT/config/$f" "$B/config/$f"; done
plan="$B/config/slus_partitions.json"
if [ -f "$ROOT/config/slus_partitions.json" ]; then
  if [ -e "$plan" ] && [ ! -L "$plan" ]; then
    echo "refusing to replace $plan" >&2; exit 1
  fi
  ln -sfn "$ROOT/config/slus_partitions.json" "$plan"
elif [ -L "$plan" ]; then
  rm "$plan"
elif [ -e "$plan" ]; then
  echo "stale partition plan at $plan" >&2; exit 1
fi
mkdir -p "$B/config/generated"
echo "build root: $B"
