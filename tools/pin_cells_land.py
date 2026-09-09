#!/usr/bin/env python3
"""Land the rows whose pins are an artefact of the wrong compiler cell.

    python3 tools/pin_cells_land.py                 # report
    python3 tools/pin_cells_land.py --apply         # correct the cell and land the pin-free text

`tools/pin_probe.py --cells` scores each pinned row's *stripped* text at every stock cell in one
scorer run.  When the pin-free text is exact at some cell B and not at the row's recorded cell A,
the pins were never describing the source: they were describing the wrong compiler.

The rule for accepting the correction, so that a cell stays a claim about the original build and
not a knob:

  1. the **pin-free** text must be exact at B (that is the finding), and
  2. the row's **pinned** text must also be exact at B - the shipped bytes must not depend on the
     change, so no byte evidence is lost, and
  3. the module's other rows are reported alongside.  A row whose module already sits at B is
     corroborated; a row that would be alone at B is landed too, but the report says so, because
     the pin-free text reproducing retail at B and nowhere else is itself the stronger evidence.

Landing writes the row's new cell through `common.set_row_cfg` (splits, rows.jsonl and the build
roots' row tables) and the stripped text through `tools/apply_candidates.py`'s path, then the
caller must run the window gate: `python3 tools/build/gate_all.py`.
"""
import argparse, collections, json, sys, tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows as ROWS, read_jsonl, append_jsonl, clean_path, sha_text, set_row_cfg
from pin_census import sites_of
from verify import verify
sys.path.insert(0, str(ROOT / "tools" / "xform"))
from xform.t12_stmtorder import strip_pins

INCLUDE = ROOT / "include"
JOURNAL = LEDGER / "sweeps" / "t13_cellfix.jsonl"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--apply", action="store_true")
    a = ap.parse_args()

    by = {r["id"]: r for r in ROWS()}
    mod = {}
    p = LEDGER / "modules.jsonl"
    if p.exists():
        for r in read_jsonl(p):
            mod[r["id"]] = r.get("module")
    cells_by_module = collections.defaultdict(collections.Counter)
    for rid, m in mod.items():
        if rid in by:
            cells_by_module[m][by[rid]["cfg"]] += 1

    hits = []
    for rec in read_jsonl(LEDGER / "pins_cells.jsonl"):
        if not rec.get("best_exact") or not rec.get("cell"):
            continue
        if not rec.get("pinned_exact_at_cell"):
            continue                      # rule 2: the shipped bytes must not depend on the change
        row = by.get(rec["id"])
        if row is None or rec["cell"] == row["cfg"]:
            continue
        p = clean_path(row)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        if sha_text(text) != rec.get("in_sha") or not sites_of(text):
            continue                      # the probe is stale for this text
        hits.append((rec, row, text))

    print(f"{len(hits)} rows go pin-free at another stock cell (pinned text exact there too)\n")
    print("| row | size | recorded cell | pin-free at | pins | module | module cells |")
    print("|---|---:|---|---|---:|---|---|")
    for rec, row, text in hits:
        m = mod.get(row["id"]) or "-"
        dist = ", ".join(f"{k}x{v}" for k, v in cells_by_module[m].most_common(3))
        print(f"| {row['id']} | {row['size']} | {row['cfg']} | {rec['cell']} | "
              f"{len(sites_of(text))} | {m} | {dist} |")
    if not a.apply:
        print("\n(--apply to correct the cells and land the pin-free text)")
        return

    out = ROOT / "work/pin_cellfix/out"
    n = 0
    for rec, row, text in hits:
        cand = strip_pins(text)
        note = (f"pin-free text is exact at {rec['cell']} and not at {row['cfg']}; "
                f"the pinned text is exact at both (tools/pin_cells_land.py)")
        set_row_cfg(row["id"], rec["cell"], note)
        row2 = dict(row, cfg=rec["cell"])
        with tempfile.TemporaryDirectory() as td:
            f = Path(td) / Path(row["c_path"]).name
            f.write_text(cand)
            v = verify(row2, f, include_root=INCLUDE)
        if not v.get("exact"):
            set_row_cfg(row["id"], row["cfg"], "reverted: pin-free text not exact after all")
            print(f"REVERTED {row['id']}: {v.get('total')} at {rec['cell']}")
            continue
        clean_path(row).write_text(cand)
        append_jsonl(JOURNAL, {"id": row["id"], "transform": "t13_cellfix",
                               "in_sha": sha_text(text), "out_sha": sha_text(cand),
                               "cfg_was": row["cfg"], "cfg": rec["cell"],
                               "pins_out": 0, "outcome": "applied", "note": note})
        n += 1
        print(f"applied {row['id']}: {row['cfg']} -> {rec['cell']}, pin-free")
    print(f"\n{n} rows landed.  Run: python3 tools/build/gate_all.py")


if __name__ == "__main__":
    main()
