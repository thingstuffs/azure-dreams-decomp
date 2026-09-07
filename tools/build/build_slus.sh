#!/usr/bin/env bash
# The SLUS gate: split the executable, generate the per-TU recipe, build, compare SHA-1.
#
#   tools/build/build_slus.sh [--fresh] [-j N]
#
# --fresh wipes the generated split and objects first (a pin-era rebuild from nothing).  The
# recipe (build.ninja) is what tools/build/configure.py generates from config/ and src/slus/;
# ledger/splits/slus.build.ninja is the pinned copy and the two are diffed.  Verdict appended to
# ledger/gate_slus.jsonl.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
B="$ROOT/build_slus"; FRESH=0; J=6
while [ $# -gt 0 ]; do case "$1" in --fresh) FRESH=1;; -j) J="$2"; shift;; esac; shift; done
bash "$ROOT/tools/build/mk_slus_root.sh" >/dev/null
if [ $FRESH = 1 ] || [ ! -f "$B/build.ninja" ]; then
  rm -rf "$B/asm" "$B/assets" "$B/build" "$B/config/generated"; mkdir -p "$B/config/generated"
  (cd "$B" && .venv/bin/splat split config/slus_006.14.yaml > "$B/splat.log" 2>&1)
  (cd "$B" && python3 tools/configure.py > "$B/configure.log" 2>&1)
fi
recipe_sha="$(sha256sum "$B/build.ninja" | cut -d' ' -f1)"
pinned="$ROOT/ledger/splits/slus.build.ninja"
same="unknown"; [ -f "$pinned" ] && { cmp -s "$pinned" "$B/build.ninja" && same="identical" || same="DIFFERS"; }
t0=$(date +%s); ok=1
nice -n10 ninja -C "$B" -j "$J" > "$B/ninja.log" 2>&1 || ok=0
secs=$(( $(date +%s) - t0 ))
tus=$(grep -c '^build .*: cc ' "$B/build.ninja" || true)
(cd "$ROOT" && python3 - "$ok" "$tus" "$recipe_sha" "$same" "$secs" <<'PY'
import json, sys, time, pathlib
ok, tus, sha, same, secs = int(sys.argv[1]), int(sys.argv[2]), sys.argv[3], sys.argv[4], int(sys.argv[5])
rec = {"at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), "result": "MATCH" if ok else "NO MATCH", "tus": tus,
       "recipe_sha256": sha, "recipe_vs_pinned": same, "secs": secs, "gate": "sha1sum -c config/slus_006.14.sha1 (ninja)"}
with open("ledger/gate_slus.jsonl", "a") as fh: fh.write(json.dumps(rec, separators=(",", ":")) + "\n")
print(f"SLUS SHA-1 gate: {rec['result']} ({tus} TUs, recipe {same} to the pinned copy, {secs}s)")
PY
)
[ $ok = 1 ] || { grep -E 'FAILED|sha1' "$B/ninja.log" | head -20; exit 1; }
