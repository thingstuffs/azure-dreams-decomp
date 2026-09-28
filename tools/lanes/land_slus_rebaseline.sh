#!/bin/bash
# Land a SLUS candidate that is byte-identical after LINKING but differs from the pinned object only by symbol
# relocations (a numeric page/address spelled as its data symbol, which build_slus resolves to the same address):
# verify.py's per-row object reference refuses it, the SLUS image gate proves it.  Round 78 (w_800589B8 by hand,
# then w_8004F330).
#   bash tools/lanes/land_slus_rebaseline.sh slus/<row> <candidate.c> [tag]
# Steps, under the shared landing lock (build_ovl/work/land.lock): the candidate must pass pin_census.landing_refusal
# and have fewer pins; the row's src text must still equal the candidate's .base_sha (if present); copy it in; full
# SLUS build + SHA-1 image gate (tools/build/build_slus.sh) must MATCH at the pinned recipe; re-derive ONLY this
# row's reference (verify.py --rebaseline-slus, which itself checks the gate record); verify.py must say exact.
# Any failure restores the original text and rebuilds.  Prints LANDED or REVERTED.
set -u; cd "$(dirname "$0")/../.."
ROW=${1:?slus/<row>}; CAND=${2:?candidate}; TAG=${3:-slus_rebaseline}
case "$ROW" in slus/*) ;; *) echo "slus rows only"; exit 1;; esac
SRC=src/$ROW.c; [ -f "$SRC" ] && [ -f "$CAND" ] || { echo "missing $SRC or $CAND"; exit 1; }
mkdir -p build_ovl/work; exec 9>build_ovl/work/land.lock; flock 9
if [ -f "$CAND.base_sha" ] && [ "$(sha256sum "$SRC" | cut -c1-64)" != "$(cat "$CAND.base_sha")" ]; then
  echo "stale: $SRC changed since the candidate was cut"; exit 1; fi
python3 - "$ROW" "$CAND" <<'PY' || exit 1
import sys; sys.path.insert(0, 'tools')
from common import rows, clean_path, ROOT
from pin_census import landing_refusal, sites_of
rid, cand = sys.argv[1:]
r = {x['id']: x for x in rows()}[rid]
new, cur = open(cand).read(), clean_path(r).read_text()
n = lambda t: sum(1 for s in sites_of(t) if s[1].startswith('ASM_'))
bad = landing_refusal(new, cur, str(clean_path(r).relative_to(ROOT)), row=r)
if bad or n(new) >= n(cur):
    print("refused:", bad or "pins did not fall (%d -> %d)" % (n(cur), n(new))); sys.exit(1)
print("pins %d -> %d" % (n(cur), n(new)))
PY
BK=$(mktemp); cp "$SRC" "$BK"; cp "$CAND" "$SRC"
if bash tools/build/build_slus.sh -j 8 && tail -1 ledger/gate_slus.jsonl | grep -q '"MATCH"' \
   && python3 tools/verify.py --rebaseline-slus "$ROW" \
   && python3 tools/verify.py "$ROW" "$SRC" | grep -q '"exact": true'; then
  python3 tools/levels.py >/dev/null; python3 tools/status.py >/dev/null
  echo "{\"tag\": \"$TAG\", \"row\": \"$ROW\", \"candidate\": \"$CAND\", \"how\": \"SLUS image SHA-1 MATCH + --rebaseline-slus\"}" >> ledger/slus_rebaseline_landings.jsonl
  grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md; rm -f "$BK"; echo LANDED
else
  cp "$BK" "$SRC"; rm -f "$BK"; bash tools/build/build_slus.sh -j 8 >/dev/null 2>&1; echo REVERTED; exit 1
fi
