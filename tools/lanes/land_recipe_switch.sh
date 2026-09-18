#!/bin/bash
# Byte-neutral recipe switches: rows whose CURRENT text is byte-exact at their module census recipe but are recorded
# at another recipe.  Nothing in src/ changes; only the recorded recipe (common.set_row_cfg), then one gate.
# Rules 1-2 of pin_cells_land hold trivially (the same text is exact at both).  Owner 2026-09-18: reducing flags and
# compilers is a goal; "if we can do it now let's make sure we don't lose it".  Every switch is recorded in
# ledger/recipe_trades.jsonl with kind "recipe-reduction" so it can be reverted from the ledger.
#   bash tools/lanes/land_recipe_switch.sh <tag> <switches.json>     # [{id, to, pins, from}, ...]
# Run only when no lane, sweep or gate is running.
set -u
cd "$(dirname "$0")/../.."
TAG=${1:?tag}; J=${2:?switches.json}
if pgrep -f "[c]odex exec" >/dev/null || pgrep -f "[s]weep.py " >/dev/null; then echo "a lane or sweep is running: wait"; exit 1; fi
python3 - "$J" "$TAG" <<'EOF'
import json, sys, tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, "tools")
from common import rows, clean_path, set_row_cfg, sha_text, parse_cfg
from verify import verify
from pin_census import sites_of
J, tag = sys.argv[1], sys.argv[2]
by = {r["id"]: r for r in rows()}
todo = [e for e in json.load(open(J)) if e["id"] in by and by[e["id"]]["cfg"] != e["to"] and clean_path(by[e["id"]]).exists()]
def check(e):
    row = by[e["id"]]; p = clean_path(row); text = p.read_text(errors="replace")
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / p.name; f.write_text(text)
        v = verify(dict(row, cfg=e["to"], cell=parse_cfg(e["to"])[0], flags=" ".join(parse_cfg(e["to"])[1])), f, include_root=Path("include").resolve())
    return e, bool(v.get("exact")), sha_text(text), len(sites_of(text))
switched = []; skipped = 0
with ThreadPoolExecutor(12) as ex, open("ledger/recipe_trades.jsonl", "a") as led:
    for e, ok, sha, npins in ex.map(check, todo):
        if not ok:
            skipped += 1; continue
        row = by[e["id"]]
        set_row_cfg(e["id"], e["to"], note=f"{tag}: byte-neutral recipe reduction toward the module census recipe")
        led.write(json.dumps({"round": 56, "date": "2026-09-18", "id": e["id"], "cfg_from": row["cfg"], "cfg_to": e["to"], "kind": "recipe-reduction",
                              "pins": npins, "source_sha": sha, "why": "current text byte-exact at both recipes; recorded recipe moved to the module census recipe (owner goal: fewer flags/compilers)"}) + "\n")
        switched.append(e["id"])
print(f"switched {len(switched)} rows, skipped (not exact at target now) {skipped}")
EOF
echo "== gate"; bash tools/build/mk_ovl_root.sh && python3 tools/build/gate_all.py --workers 8 && bash tools/build/build_slus.sh -j 8
echo "GATE_RC=$?"
python3 tools/levels.py >/dev/null; python3 tools/status.py >/dev/null; grep -o "Pin sites now: [0-9,]* in [0-9,]* rows" STATUS.md
echo "== done"
