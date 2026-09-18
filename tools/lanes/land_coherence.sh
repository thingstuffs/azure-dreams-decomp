#!/bin/bash
# Land coherence repairs: rows whose NEW text is byte-exact at their MODULE recipe (round-55 census) while the
# current text is not.  pin_cells_land rule 2 (current text exact at the new recipe) does not hold, by design: the
# switch repays a per-row recipe deviation with a text that reproduces retail at the recipe the module's own
# pin-free rows prove.  Rationale: owner 2026-09-18 (flags/compilers to be reduced; "if we can do it now let's make
# sure we don't lose it"); byte evidence is kept (git + ledger/recipe_trades.jsonl).  Every row is recorded as a trade.
#   bash tools/lanes/land_coherence.sh <tag> <lane>      # lane: work/native_lane/<lane>/{out,cells.jsonl}
# Run only when no lane, sweep or gate is running (the gate shares build_ovl with verify).
set -u
cd "$(dirname "$0")/../.."
TAG=${1:?tag}; L=${2:?lane}; D=work/native_lane/$L
[ -f $D/cells.jsonl ] || { echo "no $D/cells.jsonl"; exit 1; }
if pgrep -f "[c]odex exec" >/dev/null || pgrep -f "[s]weep.py " >/dev/null; then echo "a lane or sweep is running: wait"; exit 1; fi
python3 - "$D" "$TAG" <<'EOF'
import json, sys, hashlib
sys.path.insert(0, "tools")
from common import rows, clean_path, set_row_cfg, sha_text
from pin_census import sites_of
D, tag = sys.argv[1], sys.argv[2]
by = {r["id"]: r for r in rows()}
trades = []
for line in open(f"{D}/cells.jsonl"):
    e = json.loads(line); rid = e["id"]; row = by[rid]; c, n = rid.split("/")
    cand = open(f"{D}/out/{c}/{n}.c").read(); base = open(f"{D}/out/{c}/{n}.c.base_sha").read().strip()
    cur = clean_path(row).read_text(errors="replace")
    if sha_text(cur) != base:
        print("skip stale", rid); continue
    if row["cfg"] == e["to"]:
        print("skip same recipe", rid); continue
    set_row_cfg(rid, e["to"], note=f"{tag}: coherence repair - new text exact at the module recipe ({e.get('coherence')})")
    trades.append({"round": 56, "date": "2026-09-18", "id": rid, "cfg_from": row["cfg"], "cfg_to": e["to"], "kind": "coherence",
                   "how": e.get("coherence"), "pins_before": len(sites_of(cur)), "pins_after": len(sites_of(cand)),
                   "source_sha_before": base, "candidate_sha": sha_text(cand),
                   "why": "recipe deviation repaid: the candidate is byte-exact at the module recipe the module's pin-free rows prove; "
                          "current text was NOT exact there (rule 2 waived by rationale, owner 2026-09-18)"})
    print("cfg", rid, row["cfg"], "->", e["to"])
with open("ledger/recipe_trades.jsonl", "a") as f:
    for t in trades: f.write(json.dumps(t) + "\n")
print("trades recorded", len(trades))
EOF
python3 tools/apply_candidates.py $D/out --transform coherence_$TAG --workers 2 2>&1 | tail -2
IDS=$(git diff --name-only -- src | sed -E 's#^src/##; s#\.c$##' | paste -sd,)
if [ -n "$IDS" ]; then
  echo "== t2 on changed rows"; python3 tools/sweep.py t2_pins --only "$IDS" --workers 4 2>&1 | tail -1
  echo "== gate"; bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
  echo "GATE_RC=$?"
  python3 tools/levels.py >/dev/null; python3 tools/status.py >/dev/null; grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md
fi
echo "== done"
