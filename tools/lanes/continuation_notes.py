#!/usr/bin/env python3
"""Evidence notes for a FRESH-EYES continuation pack (cut-off experiment, tools/lanes/cutoff_report.py).

    python3 tools/lanes/continuation_notes.py <row> [--prior LANE ...] [--out DIR]
        -> DIR/<name>.md (default work/native_lane/r78_notes/), printed path

For each prior lane (default: every lane whose base/ holds the row, newest first, at most 6) it quotes the
paragraphs of REPORT.md / last_message.txt that name the row and lists the closest measured states from its
lab_log.jsonl (variant, listing distance, pins).  How the lane ended (cap, limit, interrupted, finished) is
stated so the next lane knows whether the prior stopped or was stopped.  Pass the notes to
build_class_pack.py --notes and add `--paragraphs fresh_eyes` to kit_pack.py; write CONTINUES.txt.
"""
import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
LANES = ROOT / "work/native_lane"
sys.path.insert(0, str(ROOT / "tools/lanes"))
from cutoff_report import lane_end   # noqa: E402


def notes(rid, priors):
    key = rid.split("_")[-1]
    out = [f"# Prior evidence for {rid} (fresh-eyes continuation)\n"]
    for L in priors:
        d = LANES / L
        out.append(f"\n## {L} (ended: {lane_end(d)})")
        for fn in ("REPORT.md", "last_message.txt"):
            p = d / fn
            if p.exists():
                paras = [x.strip() for x in re.split(r"\n\s*\n", p.read_text(errors="replace")) if key in x]
                if paras:
                    out.append(f"From {fn}:\n\n" + "\n\n".join(x[:3000] for x in paras[:5]))
                    break
        lg = d / "lab_log.jsonl"
        if lg.exists():
            ts = []
            for line in lg.open(errors="replace"):
                if key in line:
                    try:
                        t = json.loads(line)
                    except ValueError:
                        continue
                    if isinstance(t.get("distance"), int) and isinstance(t.get("pins"), int):
                        ts.append(t)
            if ts:
                near = sorted((t for t in ts if t["distance"] > 0), key=lambda t: (t["distance"], t["pins"]))[:6]
                few = sorted((t for t in ts if t["distance"] > 0), key=lambda t: (t["pins"], t["distance"]))[:3]
                out.append(f"lab_log: {len(ts)} trials. Closest (variant: distance, pins): "
                           + "; ".join(f"{t.get('variant')}: {t['distance']}, {t['pins']}" for t in near)
                           + ". Fewest pins: " + "; ".join(f"{t.get('variant')}: {t['distance']}, {t['pins']}" for t in few)
                           + f". Variant files live under {d}/ (cand/, cells/, experiments/, singles/ ...);"
                           " copy what you need, never grep recursively.")
    return "\n\n".join(out) + "\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("row")
    ap.add_argument("--prior", nargs="*")
    ap.add_argument("--out", default=str(LANES / "r78_notes"))
    a = ap.parse_args()
    c, n = a.row.split("/")
    priors = a.prior
    if not priors:
        hits = sorted((f.parent.parent.parent for f in LANES.glob(f"*/base/{c}/{n}.c")),
                      key=lambda p: p.stat().st_mtime, reverse=True)
        priors = [p.name for p in hits if (p / "lab_log.jsonl").exists()][:6]
    Path(a.out).mkdir(parents=True, exist_ok=True)
    path = Path(a.out) / f"{n}.md"
    path.write_text(notes(a.row, priors))
    print(path)


if __name__ == "__main__":
    main()
