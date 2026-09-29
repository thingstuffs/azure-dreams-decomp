#!/bin/bash
# Land ONE switch (computed-goto -> real switch) lane with an isolated gate, and self-heal a window link ERROR
# (round 80):  bash tools/lanes/switch_land_lanes.sh <tag> <lane>
#
# Why.  A real `switch` makes cc1 emit its own .rodata jump table.  Most window builds keep it (MATCH), but some
# synthetic deep/truebase window builds discard the row object's .rodata, and the link fails:
#   `.rodata' referenced in section `.text.func_807AE960' ... defined in discarded section `.rodata'
# land_lanes.sh then ends with GATE_RC=1 and the landed texts still in src/.  This wrapper runs the normal isolated
# landing, and on GATE_RC != 0 reverts exactly the rows the failing windows name (`.text.func_XXXX` in the gate
# record, mapped to rows via their true_name), re-gates, and commits only a MATCH tree.  Any other failure reverts
# every row this landing touched.  The file name contains "land_lanes.sh" on purpose: autocommit.sh skips while a
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
if [ "${RC:-1}" != 0 ]; then
  BAD=$(python3 - "$START" <<'PY'
import sys, json, re
sys.path.insert(0, "tools"); from common import rows
start = sys.argv[1]; by_true = {}
for r in rows():
    by_true[r.get("true_name") or r["func"]] = r["id"]; by_true[r["func"]] = r["id"]
bad = set()
for l in open("ledger/gate.jsonl"):
    d = json.loads(l)
    if d.get("at", "") < start or d.get("result") == "MATCH": continue
    for f in re.findall(r"\.text\.(func_[0-9A-F]{8})", d.get("detail", "")):
        if f in by_true: bad.add(by_true[f])
print(" ".join("src/%s.c" % b for b in sorted(bad)))
PY
)
  if [ -z "$BAD" ]; then echo "gate failed with no attributable row: reverting all"; git checkout HEAD -- $TOUCHED; exit 1; fi
  echo "reverting rows the failing windows name: $BAD"; git checkout HEAD -- $BAD
  EXP=gate SRCROOT="$PWD/src" bash tools/build/mk_ovl_root.sh >/dev/null 2>&1 && GATE_BUILD_ROOT=build_ovl_gate python3 tools/build/gate_all.py --workers 8 2>&1 | tail -1 && bash tools/build/build_slus.sh -j 8 2>&1 | tail -1
  RC=$?
  [ "$RC" = 0 ] || { echo "re-gate failed: reverting all"; git checkout HEAD -- $TOUCHED; exit 1; }
fi
python3 tools/status.py > /dev/null 2>&1
P=$(grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md)
git add src ledger STATUS.md
git commit -q -m "switch lane $LANE landed via switch_land_lanes.sh ($TAG; computed-goto dispatches -> real switch; isolated gate MATCH${BAD:+; reverted for discarded-.rodata windows: $BAD}) ($P)

Co-Authored-By: Claude Opus 5.5 (1M context) <noreply@anthropic.com>" && git log --oneline -1
