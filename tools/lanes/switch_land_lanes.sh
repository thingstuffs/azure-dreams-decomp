#!/bin/bash
# Land ONE switch (computed-goto -> real switch) lane with an isolated gate, and self-heal a window link ERROR
# (round 80):  [KIND=pin WHAT='...'] bash tools/lanes/switch_land_lanes.sh <tag> <lane>   (any lane; KIND/WHAT set the commit text)
#
# Why.  A real `switch` makes cc1 emit its own .rodata jump table.  Most window builds keep it (MATCH), but some
# synthetic deep/truebase window builds discard the row object's .rodata, and the link fails:
#   `.rodata' referenced in section `.text.func_807AE960' ... defined in discarded section `.rodata'
# land_lanes.sh then ends with GATE_RC=1 and the landed texts still in src/.  This wrapper runs the normal isolated
# landing, and on GATE_RC != 0 reverts exactly the rows the failing windows name (`.text.func_XXXX` in the gate
# record, mapped to rows via their true_name), re-gates, and commits only a MATCH tree.  Any other failure reverts
# every row this landing touched; a SLUS SHA-1 NO MATCH reverts the touched slus rows.  The file name contains "land_lanes.sh" on purpose: autocommit.sh skips while a
# process with that name runs, so a failing tree is never snapshotted in between.
set -u
cd "$(dirname "$0")/../.."
TAG=${1:?tag}; LANE=${2:?lane}
START=$(date -u +%FT%TZ); BAD=""
BEFORE=$(git diff --name-only -- src | sort)
LAND_ISOLATED=1 bash tools/lanes/land_lanes.sh "$TAG" "$LANE" > work/native_lane/$LANE/landing.log 2>&1
RC=$(grep -o "GATE_RC=[0-9]*" work/native_lane/$LANE/landing.log | tail -1 | cut -d= -f2)
exec 9>build_ovl/work/land.lock; flock 9
TOUCHED=$(comm -13 <(echo "$BEFORE") <(git diff --name-only -- src | sort))
set -o pipefail
TRIES=0
while [ "${RC:-1}" != 0 ]; do
  # a window build reports ONE failing object per link, so revert, re-gate and repeat (8ece213c: func_8187BB80 hid
  # behind func_81875C70 in dungeon_deep_t8_187c).  Attribution: every row this landing touched whose gate windows
  # include a window that is not MATCH since START - covers link ERRORs and byte mismatches alike.
  TRIES=$((TRIES+1)); [ $TRIES -gt 6 ] && { echo "still failing after 6 re-gates: reverting all"; git checkout HEAD -- $TOUCHED; exit 1; }
  NEWBAD=$(python3 - "$START" $TOUCHED <<'PY'
import sys, json, importlib
sys.path.insert(0, "tools"); from common import rows
promote = importlib.import_module("promote")
start, touched = sys.argv[1], sys.argv[2:]
by = {r["id"]: r for r in rows()}
failing, last = set(), {}
for l in open("ledger/gate.jsonl"):
    d = json.loads(l)
    if d.get("at", "") >= start: last[d["window"]] = d.get("result")
failing = {w for w, r in last.items() if r != "MATCH"}
slus = [json.loads(l) for l in open("ledger/gate_slus.jsonl") if l.strip()]
slus_bad = bool(slus) and slus[-1].get("at", "") >= start and slus[-1].get("result") != "MATCH"
bad = []
for f in touched:
    rid = f[4:-2]
    if slus_bad and f.startswith("src/slus/"): bad.append(f); continue      # SLUS NO MATCH: its rows (a real
    # switch's own .rdata table shifts the linked SLUS data layout - sw23 08:53Z)
    if rid in by and failing & {w.replace(".overlay.yaml", "") for w in promote.windows_of(by[rid])}: bad.append(f)
print(" ".join(sorted(bad)))
PY
)
  if [ -z "$NEWBAD" ]; then echo "gate failed with no attributable row: reverting all"; git checkout HEAD -- $TOUCHED; exit 1; fi
  echo "reverting rows in failing windows: $NEWBAD"; git checkout HEAD -- $NEWBAD; BAD="$BAD $NEWBAD"
  TOUCHED=$(comm -13 <(echo "$BEFORE") <(git diff --name-only -- src | sort))
  EXP=gate SRCROOT="$PWD/src" bash tools/build/mk_ovl_root.sh >/dev/null 2>&1 && GATE_BUILD_ROOT=build_ovl_gate python3 tools/build/gate_all.py --workers 8 2>&1 | tail -1 && bash tools/build/build_slus.sh -j 8 2>&1 | tail -1
  RC=$?
done
python3 tools/status.py > /dev/null 2>&1
P=$(grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md)
git add src ledger STATUS.md
git commit -q -m "${KIND:-switch} lane $LANE landed via switch_land_lanes.sh ($TAG; ${WHAT:-computed-goto dispatches -> real switch}; isolated gate MATCH${BAD:+; reverted for discarded-.rodata windows: $BAD}) ($P)

Co-Authored-By: Claude Opus 5.5 (1M context) <noreply@anthropic.com>" && git log --oneline -1
