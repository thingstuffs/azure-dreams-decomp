#!/usr/bin/env bash
# Provision everything that proves bytes, from tools/toolchain.lock.json.  Idempotent; no sudo.
#
#   tools/setup.sh            # provision what is missing, verify what is present
#   tools/setup.sh --check    # verify only (exit 1 on any gap)
#
# Pieces (all under this tree, nothing borrowed):
#   .venv/                     splat64 (the SLUS split) and its deps, pinned in the lock
#   toolchain/compilers/       the seven stock cc1 drops (downloaded from decompals, sha256-checked) and nothing else
#   toolchain/maspsx           -> tools/maspsx (vendored, function-blind assembler front end)
#   toolchain/bin/mkpsxiso,dumpsxiso   built from the pinned commit + tools/patches/ (disc round trip)
#   bin/<disc image>           supplied by the user, SHA-1 checked; work/disc/ extracted from it (tools/disc.py)
# Seed: if $AZURE_CLEAN_SEED names a directory with toolchain/compilers, toolchain/src/mkpsxiso or bin/
# already in place, they are copied from there instead of downloaded (still hash-checked).
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LOCK="$ROOT/tools/toolchain.lock.json"
TC="$ROOT/toolchain"
CHECK=0; [ "${1:-}" = "--check" ] && CHECK=1
fail=0
say() { printf '%s\n' "$*"; }
gap() { say "  GAP: $*"; fail=1; }
j() { python3 -c "import json,sys; d=json.load(open('$LOCK'))
for k in sys.argv[1].split('/'): d=d[k]
print(d if not isinstance(d,(list,dict)) else json.dumps(d))" "$1"; }

say "== host =="
for t in mipsel-linux-gnu-as ninja cmake python3 git curl; do
  command -v "$t" >/dev/null || gap "$t not on PATH (apt: $(j host_packages))"
done
python3 -c 'import yaml' 2>/dev/null || gap "python3 cannot import yaml (apt: python3-yaml)"
say "  as: $(mipsel-linux-gnu-as --version 2>/dev/null | head -1)"

say "== python venv =="
if [ ! -x "$ROOT/.venv/bin/splat" ]; then
  if [ $CHECK = 1 ]; then gap ".venv missing"; else
    python3 -m venv "$ROOT/.venv"
    "$ROOT/.venv/bin/pip" install -q -U pip wheel
    "$ROOT/.venv/bin/pip" install -q $(j python/requires | python3 -c 'import json,sys; print(" ".join(json.load(sys.stdin)))')
    "$ROOT/.venv/bin/pip" install -q $(j python/requires_dev | python3 -c 'import json,sys; print(" ".join(json.load(sys.stdin)))')
  fi
fi
[ -x "$ROOT/.venv/bin/splat" ] && say "  splat: $("$ROOT/.venv/bin/pip" show splat64 2>/dev/null | sed -n 's/^Version: //p')"

say "== compilers =="
mkdir -p "$TC/compilers"
BASE="$(j compilers/base_url)"
for v in $(python3 -c "import json; print(' '.join(json.load(open('$LOCK'))['compilers']['drops']))"); do
  d="$TC/compilers/gcc-$v"
  if [ ! -x "$d/cc1" ]; then
    if [ $CHECK = 1 ]; then gap "gcc-$v missing"; continue; fi
    if [ -n "${AZURE_CLEAN_SEED:-}" ] && [ -x "$AZURE_CLEAN_SEED/toolchain/compilers/gcc-$v/cc1" ]; then
      rm -rf "$d"; cp -r "$AZURE_CLEAN_SEED/toolchain/compilers/gcc-$v" "$d"
    else
      mkdir -p "$d"; curl -fsSL "$BASE/$(j compilers/drops/$v/asset)" | tar xz -C "$d"
    fi
  fi
  for f in cc1 gcc; do
    want="$(j compilers/drops/$v/$f)"; got="$(sha256sum "$d/$f" | cut -d' ' -f1)"
    [ "$want" = "$got" ] && say "  gcc-$v/$f OK" || gap "gcc-$v/$f sha256 $got != lock $want"
  done
  rm -f "$d"/cc1.pre-* 2>/dev/null || true
done
# the guard: nothing but the stock drops may live here (every compiler bridge ever built started as a directory here)
for d in "$TC"/compilers/*/; do
  n="$(basename "$d")"; v="${n#gcc-}"
  python3 -c "import json,sys; sys.exit(0 if '$v' in json.load(open('$LOCK'))['compilers']['drops'] else 1)" || gap "non-stock compiler directory $n"
done

say "== assembler =="
[ -f "$ROOT/tools/maspsx/maspsx.py" ] || gap "tools/maspsx missing (vendored)"
[ "$(readlink "$TC/maspsx" 2>/dev/null)" = "../tools/maspsx" ] || { [ $CHECK = 1 ] && gap "toolchain/maspsx link" || ln -sfn ../tools/maspsx "$TC/maspsx"; }
maspsx_line="$(python3 - <<EOF
import re, glob, ast
fs = ['$ROOT/tools/maspsx/maspsx.py'] + sorted(glob.glob('$ROOT/tools/maspsx/maspsx/*.py'))
class Strip(ast.NodeTransformer):   # drop docstrings; unparse drops comments: what is left is executable text
    def visit_Expr(self, n):
        return None if isinstance(n.value, ast.Constant) and isinstance(n.value.value, str) else n
n = sum(len(re.findall(r'func_[0-9A-F]{8}', ast.unparse(Strip().visit(ast.parse(open(f).read()))))) for f in fs)
lines = sum(len(open(f).read().splitlines()) for f in fs)
print(len(fs), 'files,', lines, 'lines,', n, 'executable func literals (must be 0: function-blind)')
raise SystemExit(1 if n else 0)
EOF
)" && say "  maspsx: $maspsx_line" || gap "maspsx carries executable function-name literals: $maspsx_line"

if [ -x "$ROOT/.venv/bin/python" ] && "$ROOT/.venv/bin/python" -c 'import pytest' 2>/dev/null; then
  (cd "$ROOT/tools/maspsx" && "$ROOT/.venv/bin/python" -m pytest tests -q --no-header -p no:cacheprovider > "$ROOT/work/maspsx_tests.log" 2>&1) \
    && say "  maspsx tests: $(tail -1 "$ROOT/work/maspsx_tests.log")" || gap "maspsx tests failed (work/maspsx_tests.log)"
fi

say "== mkpsxiso =="
if [ ! -x "$TC/bin/mkpsxiso" ] || [ ! -x "$TC/bin/dumpsxiso" ]; then
  if [ $CHECK = 1 ]; then gap "toolchain/bin/mkpsxiso missing"; else
    SRC="$TC/src/mkpsxiso"; C="$(j mkpsxiso/commit)"
    if [ ! -d "$SRC" ]; then
      if [ -n "${AZURE_CLEAN_SEED:-}" ] && [ -d "$AZURE_CLEAN_SEED/toolchain/src/mkpsxiso" ]; then
        mkdir -p "$TC/src"; rsync -a --exclude build "$AZURE_CLEAN_SEED/toolchain/src/mkpsxiso/" "$SRC/"
      else
        git clone "$(j mkpsxiso/repo)" "$SRC"; git -C "$SRC" checkout -q "$C"; git -C "$SRC" submodule update --init --recursive
        git -C "$SRC" apply "$ROOT/$(j mkpsxiso/patch)"
      fi
    fi
    [ "$(git -C "$SRC" rev-parse HEAD)" = "$C" ] || gap "mkpsxiso source is not at $C"
    cmake -S "$SRC" -B "$SRC/build" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$TC" >/dev/null
    cmake --build "$SRC/build" >/dev/null && cmake --install "$SRC/build" >/dev/null
  fi
fi
[ -x "$TC/bin/mkpsxiso" ] && say "  $("$TC/bin/mkpsxiso" -h 2>&1 | head -1)"

say "== disc =="
DISC="${AZURE_CLEAN_DISC:-$ROOT/bin/$(j disc/name)}"
if [ ! -f "$DISC" ]; then
  if [ -n "${AZURE_CLEAN_SEED:-}" ] && [ -f "$AZURE_CLEAN_SEED/bin/$(j disc/name)" ] && [ $CHECK = 0 ]; then
    mkdir -p "$ROOT/bin"; cp "$AZURE_CLEAN_SEED/bin/$(j disc/name)" "$AZURE_CLEAN_SEED/bin/$(j disc/cue)" "$ROOT/bin/"
  else
    gap "disc image not found: $DISC (copy the image and cue into bin/, or set AZURE_CLEAN_DISC); sha1 must be $(j disc/sha1)"
  fi
fi
if [ -f "$DISC" ]; then
  got="$(sha1sum "$DISC" | cut -d' ' -f1)"
  [ "$got" = "$(j disc/sha1)" ] && say "  image sha1 OK" || gap "image sha1 $got != lock $(j disc/sha1)"
  if [ ! -f "$ROOT/work/disc/containers/DUNGEON_DUNGEON.BIN" ] || [ ! -f "$ROOT/baserom/slus_006.14" ]; then
    [ $CHECK = 1 ] && gap "work/disc not extracted (tools/disc.py extract)" || python3 "$ROOT/tools/disc.py" extract --disc "$DISC"
  fi
fi

if [ $fail = 0 ]; then
  say "OK: toolchain, assembler, mkpsxiso, venv, disc and containers provisioned under $ROOT"
  say "next: tools/build/build_slus.sh (SLUS SHA-1 gate), tools/build/mk_ovl_root.sh + tools/build/gate_all.py (overlay windows)"
else
  say "setup incomplete (see GAP lines)"; exit 1
fi
