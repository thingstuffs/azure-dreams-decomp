#!/usr/bin/env python3
"""Apply r84_fable_build's proposed module patch (owner 10-01: groupings that move toward the real build are welcome):
27 row moves (modules_patch.jsonl) into 5 modules - existing targets keep their module_index and get their census counts
increased, new modules get a fresh index and census_patch.jsonl's record - plus 6 census recipe corrections
(census_recipe_changes.tsv rows whose new_best differs).  Source modules' census counts are decreased by the rows that
left.   python3 apply_fable_patch.py [--write]"""
import csv, json, sys, collections
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
D = ROOT / "work/native_lane/r84_fable_build"
mp = [json.loads(l) for l in open(D / "modules_patch.jsonl")]
cp = {(c["container"], c["module"]): c for c in map(json.loads, open(D / "census_patch.jsonl"))}
mods = [json.loads(l) for l in open(ROOT / "ledger/modules.jsonl")]
cen = [json.loads(l) for l in open(ROOT / "ledger/module_recipe_census.jsonl")]
byid = {m["id"]: m for m in mods}
cbykey = {(c["container"], c["module"]): c for c in cen}
idx = {}
for m in mods: idx.setdefault((m["container"], m["module"]), m["module_index"])
nxt = {c: max(m["module_index"] for m in mods if m["container"] == c) + 1 for c in ("main", "town", "dungeon")}
left = collections.Counter(); arrived = collections.Counter()
for p in mp:
    c = p["id"].split("/")[0]; key = (c, p["new_module"])
    assert byid[p["id"]]["module"] == p["old_module"], p
    if key not in idx: idx[key] = nxt[c]; nxt[c] += 1
    byid[p["id"]]["module"] = p["new_module"]; byid[p["id"]]["module_index"] = idx[key]
    left[(c, p["old_module"])] += 1; arrived[key] += 1
for key, n in arrived.items():
    rec = cp[key]
    if key in cbykey:      # existing module: add the arriving rows' counts
        o = cbykey[key]
        for f in ("rows", "pin_free", "pinned", "pins", "exact_at_best", "pin_free_exact_at_best"):
            o[f] = o.get(f, 0) + rec.get(f, 0)
        o["r84_moves"] = "%d rows joined from r84_fable_build (%s)" % (n, rec.get("modsplit", {}).get("evidence", "")[:200])
    else:
        cen.append(rec); cbykey[key] = rec
for key, n in left.items():
    o = cbykey.get(key)
    if o:
        o["rows"] = o.get("rows", 0) - n
        o["r84_moves"] = (o.get("r84_moves", "") + "; %d rows left for r84_fable_build modules (counts other than rows not re-derived)" % n).lstrip("; ")
changes = [r for r in csv.DictReader(open(D / "census_recipe_changes.tsv"), delimiter="\t") if r["old_best"] != r["new_best"]]
for r in changes:
    o = cbykey[(r["container"], r["module"])]
    assert o["best_recipe"] == r["old_best"], (r, o["best_recipe"])
    o["best_recipe"] = r["new_best"]; o["r84_recipe"] = "r84_fable_build: %s -> %s (%s)" % (r["old_best"], r["new_best"], r["evidence"])
print("rows moved", len(mp), "| new modules", [k for k in arrived if k not in {(c["container"], c["module"]) for c in map(json.loads, open(ROOT / "ledger/module_recipe_census.jsonl"))}],
      "| recipe changes", len(changes), "| census", len(cen))
if "--write" in sys.argv:
    (ROOT / "ledger/modules.jsonl").write_text("".join(json.dumps(m, separators=(",", ":")) + "\n" for m in mods))
    (ROOT / "ledger/module_recipe_census.jsonl").write_text("".join(json.dumps(c) + "\n" for c in cen))
    print("written")
