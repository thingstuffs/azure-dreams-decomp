#!/bin/bash
# Land coherence repairs: rows whose NEW text is byte-exact at their MODULE recipe (round-55 census) while the
# current text is not.  pin_cells_land rule 2 (current text exact at the new recipe) does not hold, by design: the
# switch repays a per-row recipe deviation with a text that reproduces retail at the recipe the module's own
# pin-free rows prove.  Rationale: owner 2026-09-18 (flags/compilers to be reduced; "if we can do it now let's make
# sure we don't lose it"); byte evidence is kept (git + ledger/recipe_trades.jsonl).  Every row is recorded as a trade.
#   bash tools/lanes/land_coherence.sh <tag> <lane>      # lane: work/native_lane/<lane>/{out,cells.jsonl}
# Run only when no lane, sweep or gate is running (the gate shares build_ovl with verify) - UNLESS
# LAND_ISOLATED=1 (round 68 isolated landing, docs/LANE_KIT.md): then the codex/sweep refusal is
# skipped (the gate runs in its own root, build_ovl_gate, so it never touches build_ovl under a
# lane's running verify.py) and this landing takes the same cross-process lock the other landers
# take, the same way (build_ovl/work/land.lock), so two landings queue instead of racing.  See
# tools/lanes/land_lanes.sh and tools/lanes/land_gap.sh, which this mirrors.
set -u
cd "$(dirname "$0")/../.."
# one landing at a time: the same lock land_lanes.sh takes (2026-09-19), taken unconditionally
mkdir -p build_ovl/work; exec 9>build_ovl/work/land.lock; flock 9
TAG=${1:?tag}; L=${2:?lane}; D=work/native_lane/$L
ROUND=${ROUND:-73}
DATE=$(date -u +%F)
[ -f $D/cells.jsonl ] || { echo "no $D/cells.jsonl"; exit 1; }
ISO=${LAND_ISOLATED:-0}
if [ "$ISO" != 1 ]; then
  if pgrep -f "[c]odex exec" >/dev/null || pgrep -f "[s]weep.py " >/dev/null; then echo "a lane or sweep is running: wait"; exit 1; fi
fi
python3 - "$D" "$TAG" "$ROUND" "$DATE" <<'EOF'
import json, sys, hashlib
sys.path.insert(0, "tools")
from common import rows, clean_path, set_row_cfg, sha_text
from pin_census import sites_of
D, tag, round_arg, date_ = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
round_ = int(round_arg) if round_arg.isdigit() else round_arg
from pathlib import Path
by = {r["id"]: r for r in rows()}
trades = []; switched = []
for line in open(f"{D}/cells.jsonl"):
    e = json.loads(line); rid = e["id"]; row = by[rid]; c, n = rid.split("/")
    cand = open(f"{D}/out/{c}/{n}.c").read(); base = open(f"{D}/out/{c}/{n}.c.base_sha").read().strip()
    cur = clean_path(row).read_text(errors="replace")
    if sha_text(cur) != base:
        print("skip stale", rid); continue
    if row["cfg"] == e["to"]:
        print("skip same recipe", rid); continue
    # verify the candidate at the target recipe BEFORE touching the row's recipe: a refusal must leave the baseline exact
    import tempfile
    from verify import verify
    from pin_census import landing_refusal
    from common import parse_cfg
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / f"{n}.c"; f.write_text(cand)
        v = verify(dict(row, cfg=e["to"], cell=parse_cfg(e["to"])[0], flags=" ".join(parse_cfg(e["to"])[1])), f, include_root=Path("include").resolve())
    if not v.get("exact"):
        print("skip not exact at target", rid, e["to"], v.get("status"), v.get("total")); continue
    bad = landing_refusal(cand, cur, f"src/{rid}.c", row=row)
    if bad:
        print("skip landing refusal", rid, bad[:100]); continue
    set_row_cfg(rid, e["to"], note=f"{tag}: coherence repair - new text exact at the module recipe ({e.get('coherence')}); charter clause 4b")
    switched.append(rid)
    trades.append({"round": round_, "date": date_, "id": rid, "cfg_from": row["cfg"], "cfg_to": e["to"], "kind": "coherence",
                   "how": e.get("coherence"), "pins_before": len(sites_of(cur)), "pins_after": len(sites_of(cand)),
                   "source_sha_before": base, "candidate_sha": sha_text(cand),
                   "why": "recipe deviation repaid: the candidate is byte-exact at the module recipe the module's pin-free rows prove; "
                          "current text was NOT exact there (rule 2 waived by rationale, owner 2026-09-18)"})
    print("cfg", rid, row["cfg"], "->", e["to"])
with open("ledger/recipe_trades.jsonl", "a") as f:
    for t in trades: f.write(json.dumps(t) + "\n")
print("trades recorded", len(trades))
open(f"{D}/switched.txt", "w").write("\n".join(switched) + "\n")
EOF
python3 tools/apply_candidates.py $D/out --transform coherence_$TAG --workers 2 2>&1 | tail -2
# every switched row must have landed; otherwise restore its recipe so the baseline stays exact
python3 - "$D" "$TAG" <<'EOF'
import json, sys
sys.path.insert(0, "tools")
from common import rows, set_row_cfg, read_jsonl, LEDGER, clean_path, sha_text
D, tag = sys.argv[1], sys.argv[2]
by = {r["id"]: r for r in rows()}
applied = {r["id"] for r in read_jsonl(LEDGER / "sweeps" / f"coherence_{tag}.jsonl") if r.get("outcome") == "applied"}
for rid in [l.strip() for l in open(f"{D}/switched.txt") if l.strip()]:
    if rid not in applied:
        old = next(json.loads(l)["cfg_from"] for l in reversed(open("ledger/recipe_trades.jsonl").read().splitlines()) if json.loads(l)["id"] == rid and json.loads(l).get("kind") == "coherence")
        set_row_cfg(rid, old, note=f"{tag}: coherence candidate did not land; recipe restored")
        print("RESTORED recipe of", rid, "->", old)
print("switched", len(open(f"{D}/switched.txt").read().split()), "applied", len(applied))
EOF
IDS=$(git diff --name-only -- src | sed -E 's#^src/##; s#\.c$##' | paste -sd,)
if [ -n "$IDS" ]; then
  echo "== t2 on changed rows"; python3 tools/sweep.py t2_pins --only "$IDS" --workers 4 2>&1 | tail -1
  echo "== gate"
  if [ "$ISO" = 1 ]; then
    EXP=gate SRCROOT="$PWD/src" bash tools/build/mk_ovl_root.sh && GATE_BUILD_ROOT=build_ovl_gate python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
  else
    bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
  fi
  echo "GATE_RC=$?"
  if [ "$ISO" = 1 ] && ! diff -rq --exclude=__pycache__ tools/gate build_ovl/tools >/dev/null 2>&1; then
    echo "note: build_ovl/tools no longer mirrors tools/gate (an isolated landing never rebuilds the lanes' scorer root): run 'bash tools/build/mk_ovl_root.sh' in the next lane gap"
  fi
  python3 tools/levels.py >/dev/null; python3 tools/status.py >/dev/null; grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md
fi
echo "== done"
