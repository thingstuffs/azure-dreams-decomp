#!/usr/bin/env python3
"""Join the split-address fingerprint into the module recipe census (fidelity plan, owner decision 2026-09-24).

    python3 tools/fidelity/census_join.py            # after tools/fidelity/split_fingerprint.py --report

Inputs: work/fidelity/module_fingerprint.jsonl (split_fingerprint.py, one record per module, regenerable from its
hash-keyed per-row journal) and ledger/module_recipe_census.jsonl (round-55 compile census).
Outputs:
  ledger/module_split_fingerprint.jsonl  every module's fingerprint summary (the committed record; small)
  ledger/module_recipe_census.jsonl      each census record gains `split_fingerprint`:
      {addr, fp, pinfree_addr, pinfree_fp, verdict, requires_splitting, contradiction}
      requires_splitting: the module's pin-free addressing rows show the fingerprint (retail was built by an
      address-splitting cell: 2.7.2-cdk or 2.8.x - 2.6.3/2.7.2 have no split path);
      contradiction: requires_splitting but best_recipe does not split.
Coherence tools that read the census (tools/lanes/coherence_*.py) thereby see the retail evidence next to the
compile evidence; a contradiction means the census best_recipe must be re-derived before any repair toward it.
Idempotent: re-running replaces the field.
"""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
FP = ROOT / "work/fidelity/module_fingerprint.jsonl"
CEN = ROOT / "ledger/module_recipe_census.jsonl"
OUT = ROOT / "ledger/module_split_fingerprint.jsonl"
SPLITTING = ("2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2")


def splits(recipe):
    toks = (recipe or "").split()
    return bool(toks) and toks[0].startswith(SPLITTING) and "-mmips-as" not in toks and "-mno-split-addresses" not in toks


def main():
    fps = [json.loads(l) for l in open(FP)]
    OUT.write_text("".join(json.dumps(r, sort_keys=True) + "\n" for r in fps))
    by = {(r["container"], r["module"]): r for r in fps}
    out, n, contra = [], 0, []
    for l in open(CEN):
        c = json.loads(l)
        f = by.get((c["container"], c["module"]))
        if f:
            req = f.get("pinfree_fp", 0) > 0
            c["split_fingerprint"] = {k: f.get(k) for k in ("addr", "fp", "pinfree_addr", "pinfree_fp", "verdict")}
            c["split_fingerprint"]["requires_splitting"] = req
            c["split_fingerprint"]["contradiction"] = req and not splits(c.get("best_recipe"))
            n += 1
            if c["split_fingerprint"]["contradiction"]:
                contra.append(f'{c["container"]}/{c["module"]} best={c.get("best_recipe")}')
        out.append(json.dumps(c) + "\n")
    CEN.write_text("".join(out))
    print(f"{len(fps)} module fingerprints -> {OUT.name}; {n} census records joined; contradictions: {len(contra)}")
    for x in contra:
        print("  ", x)


if __name__ == "__main__":
    main()
