#!/bin/bash
# Land a SLUS candidate whose linked image matches despite a stale row object.
# Usage: land_slus_rebaseline.sh [--equal-pins] slus/<row> candidate.c [tag]
# Default: ASM pins must fall. --equal-pins: total pin count must stay equal,
# a land_lanes scaffolding/fidelity kind must fall, and no kind may grow.
# Both modes retain landing_refusal, stale-base, the pinned full-image SHA-1
# gate, single-row rebaseline and exact verification. Failures restore source,
# row reference and accounting, then rebuild the original image under the lock.
set -euo pipefail
cd "$(dirname "$0")/../.."
EQUAL=0
if [ "${1:-}" = --equal-pins ]; then EQUAL=1; shift; fi
ROW=${1:?slus/<row>}; CAND=${2:?candidate}; TAG=${3:-slus_rebaseline}
case "$ROW" in slus/*) ;; *) echo "slus rows only"; exit 1;; esac
SRC=$(python3 tools/source_layout.py path "$ROW")
[ -f "$SRC" ] && [ -f "$CAND" ] || { echo "missing $SRC or $CAND"; exit 1; }
mkdir -p build_ovl/work; exec 9>build_ovl/work/land.lock; flock 9
if [ -f "$CAND.base_sha" ] && [ "$(sha256sum "$SRC" | cut -c1-64)" != "$(cat "$CAND.base_sha")" ]; then
  echo "stale: $SRC changed since the candidate was cut"; exit 1
fi
python3 - "$ROW" "$CAND" "$EQUAL" <<'PY'
import sys; sys.path.insert(0, 'tools')
from common import rows, clean_path, ROOT
from pin_census import landing_refusal, sites_of
from land_admit import equal_pin_changes
rid, cand, equal = sys.argv[1:]
r = {x['id']: x for x in rows()}[rid]
new, cur = open(cand).read(), clean_path(r).read_text()
bad = landing_refusal(new, cur, str(clean_path(r).relative_to(ROOT)), row=r)
if bad:
    print('refused:', bad); sys.exit(1)
if equal == '1':
    nc, nu = len(sites_of(new)), len(sites_of(cur))
    if nc != nu:
        print('refused: --equal-pins requires unchanged pins (%d -> %d)' % (nu, nc)); sys.exit(1)
    fell, grew = equal_pin_changes(r, new, cur)
    if grew or not fell:
        print('refused: equal pins; fell', fell, 'grew', grew); sys.exit(1)
    print('pins %d -> %d; fell %s; grew %s' % (nu, nc, fell, grew))
else:
    n = lambda t: sum(1 for s in sites_of(t) if s[1].startswith('ASM_'))
    if n(new) >= n(cur):
        print('refused: pins did not fall (%d -> %d)' % (n(cur), n(new))); sys.exit(1)
    print('pins %d -> %d' % (n(cur), n(new)))
PY
BK=$(mktemp -d); DONE=0
# Snapshot all persistent files this script may replace; gate journals retain
# failed-attempt evidence. Never erase an unrelated row's reference update.
SAVED=("$SRC" ledger/cache/slus_obj.json "ledger/cache/slus_dis/${ROW#slus/}.txt" ledger/levels.jsonl STATUS.md ledger/slus_rebaseline_landings.jsonl)
for i in "${!SAVED[@]}"; do
  if [ -f "${SAVED[$i]}" ]; then cp -p "${SAVED[$i]}" "$BK/$i"; fi
done
rollback() {
  local rc=$?
  trap - EXIT INT TERM
  if [ "$DONE" != 1 ]; then
    for i in "${!SAVED[@]}"; do
      if [ -f "$BK/$i" ]; then cp -p "$BK/$i" "${SAVED[$i]}"; else rm -f "${SAVED[$i]}"; fi
    done
    if ! bash tools/build/build_slus.sh -j 8 >"$BK/rebuild.log" 2>&1; then
      cat "$BK/rebuild.log" >&2
      echo "REVERTED source/reference; original image rebuild failed" >&2
    else
      echo REVERTED
    fi
  fi
  rm -rf "$BK"
  exit "$rc"
}
trap rollback EXIT
trap 'exit 130' INT
trap 'exit 143' TERM
cp "$CAND" "$SRC"
bash tools/build/build_slus.sh -j 8
python3 - <<'PY'
import json
from pathlib import Path
r = json.loads(Path('ledger/gate_slus.jsonl').read_text().splitlines()[-1])
if r.get('result') != 'MATCH' or r.get('recipe_vs_pinned') != 'identical':
    raise SystemExit('refused: full SLUS gate must MATCH at the pinned recipe')
if Path('build_slus/build.ninja').read_bytes() != Path('ledger/splits/slus.build.ninja').read_bytes():
    raise SystemExit('refused: generated recipe differs from pinned recipe')
PY
python3 tools/verify.py --rebaseline-slus "$ROW"
python3 tools/verify.py "$ROW" "$SRC" >"$BK/verify.json"
cat "$BK/verify.json"
python3 - "$BK/verify.json" <<'PY'
import json, sys
if json.load(open(sys.argv[1])).get('exact') is not True:
    raise SystemExit('refused: rebaselined row is not exact')
PY
python3 tools/levels.py >/dev/null
python3 tools/status.py >/dev/null
python3 - "$TAG" "$ROW" "$CAND" "$EQUAL" <<'PY'
import json, sys
from pathlib import Path
with Path('ledger/slus_rebaseline_landings.jsonl').open('a') as f:
    f.write(json.dumps(dict(tag=sys.argv[1], row=sys.argv[2], candidate=sys.argv[3],
                           equal_pins=sys.argv[4] == '1', how='SLUS image SHA-1 MATCH + --rebaseline-slus')) + '\n')
PY
DONE=1
 grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md || true
echo LANDED
