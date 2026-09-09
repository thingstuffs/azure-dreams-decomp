#!/usr/bin/env python3
"""Row files for the campaign plan's lane tiers, from the live census.

    python3 tools/campaign_rows.py [--out work]

Writes:
  work/fidelity_rows_small.txt   rows with a live blocking fidelity site (LABEL_AS_CALL / PASSTHRU_NO_ARGS), <= 200 B
                                 -> served in batches of five (measured 2026-09-09: 20 s and 190k tokens per row vs 80 s and 232k per row)
  work/fidelity_rows_large.txt   the same, > 200 B -> served one per session
  work/fields_rows.txt           rows at L1 whose M2C_FIELD accesses the T4 sweep could not type (fields lane)
Rows a lane journal has finished (accepted and landed, or unchanged) are left in: agent_task.py filters them itself in
campaign mode; rows refused twice at their current text are skipped there too.
"""
import argparse, json, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, raw_path
from census import live_audit

def main():
    ap = argparse.ArgumentParser(); ap.add_argument("--out", default="work"); ap.add_argument("--small", type=int, default=200)
    a = ap.parse_args()
    out = ROOT / a.out; out.mkdir(exist_ok=True)
    lv = {x["id"]: x for x in read_jsonl(LEDGER / "levels.jsonl")}
    small, large, fields = [], [], []
    for r in rows():
        if not r["stock"]: continue
        cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
        text = (cp if cp.exists() else raw_path(r)).read_text(errors="replace")
        live = live_audit(r, text)
        if sum(live.get(k, 0) for k in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS")):
            (small if r["size"] <= a.small else large).append((r["size"], r["id"]))
        L = lv.get(r["id"], {})
        if L.get("level") == 1 and L.get("m2c_field"): fields.append((r["size"], r["id"]))
    for name, data in (("fidelity_rows_small.txt", small), ("fidelity_rows_large.txt", large), ("fields_rows.txt", fields)):
        data.sort(); (out / name).write_text("".join(i + "\n" for _, i in data))
        print(f"{name}: {len(data)} rows, {sum(s for s, _ in data):,} B")

if __name__ == "__main__":
    main()
