#!/usr/bin/env python3
"""Cut-off outcomes: do caps, quota cuts, interruptions and budget checkpoints stop lanes that were close,
and does a fresh-eyes continuation from where a cut lane got to pay?  (Owner question, 2026-09-27.)

    python3 tools/lanes/cutoff_report.py                     # every lane with a lab_log.jsonl, r6x on
    python3 tools/lanes/cutoff_report.py --glob 'r7[78]_*'   # a subset
    python3 tools/lanes/cutoff_report.py --json ledger/cutoff_outcomes.jsonl   # also write the per-row records

Per (lane, row) it reads the lane's own `lab_log.jsonl` (lab.py appends one record per measured variant, in
order: row, variant, distance = listing distance to retail, pins = pins left in the variant) and records:

  end       how the lane ended: finished | checkpoint (Agent lane that used >= 80% of its tool budget) |
            cap (cap.txt: lane_cap.py killed it) | limit (provider quota/capacity cut) |
            interrupted (launched, not running, no last_message.txt) | running
  base      pins in the served text (base/<container>/<name>.c)
  staged    fewest pins among the lane's staged out/ candidates (None = nothing staged)
  best_near the closest non-exact state with fewer pins than base: (distance, pins)
  near      best_near distance <= 4 (the lanes' own "keep going" threshold)
  late      the lane's last improvement of best distance (at fewer pins) came in the final 25% of that row's
            trials - it was still converging when it stopped
  now       pins in the row's current src text; `later` = now < min(base, staged): someone removed more after
  continued_by  later lanes that served the row with a CONTINUES.txt naming this lane (continuation packs)

The summary splits rows by `end`: how many were near-and-unstaged when the lane stopped, how many of those
were still converging, and how many were later reduced further - by a continuation or by anything else.
Continuation packs write CONTINUES.txt (one prior lane name per line) so the fresh-eyes effect is measured,
not remembered.  Lab logs carry no timestamps: "late" is by trial order, not wall time.
"""
import argparse
import glob
import json
import os
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
from common import rows, clean_path          # noqa: E402
from pin_census import sites_of              # noqa: E402
import lane_limit                             # noqa: E402

LANES = ROOT / "work/native_lane"
AGENT_BUDGET = 150        # the agent prompt's tool-call checkpoint (tools/lanes/agent_lane_prompt.md)


def npins(text):
    return sum(1 for s in sites_of(text) if s[1].startswith("ASM_"))


def alive(d):
    try:
        os.kill(int((d / "lane.pid").read_text().split()[0]), 0)
        return True
    except (OSError, ValueError):
        return False


def lane_end(d):
    if (d / "cap.txt").exists():
        return "cap"
    if (d / "limit_cut.txt").exists() or lane_limit.lane_hit_limit(d):
        return "limit"
    if (d / "last_message.txt").exists():
        try:
            u = json.loads((d / "usage.json").read_text())
            if u.get("source") == "agent-tool-result" and (u.get("tool_uses") or 0) >= 0.8 * AGENT_BUDGET \
                    and "_opus_" in d.name and d.name >= "r78":
                return "checkpoint"
        except (OSError, ValueError):
            pass
        return "finished"
    if alive(d):
        return "running"
    try:                       # Agent-tool lanes have no pid: a codex.log touched in the last 90 min = running
        import time
        if time.time() - (d / "codex.log").stat().st_mtime < 5400 and not (d / "lane.pid").exists():
            return "running"
    except OSError:
        pass
    return "interrupted"


def continuations():
    out = defaultdict(set)
    for f in LANES.glob("*/CONTINUES.txt"):
        for prior in f.read_text().split():
            out[prior].add(f.parent.name)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--glob", default="r6*,r7*,r8*")
    ap.add_argument("--json")
    a = ap.parse_args()
    by = {r["id"]: r for r in rows()}
    now_cache = {}
    cont = continuations()
    recs = []
    lanes = sorted({p for g in a.glob.split(",") for p in glob.glob(str(LANES / g.strip()))})
    for ld in map(Path, lanes):
        log = ld / "lab_log.jsonl"
        if not log.exists() or not (ld / "base").is_dir():
            continue
        trials = defaultdict(list)
        for line in log.open(errors="replace"):
            try:
                t = json.loads(line)
            except ValueError:
                continue
            if t.get("row") and isinstance(t.get("distance"), int) and isinstance(t.get("pins"), int):
                trials[t["row"]].append((t["distance"], t["pins"]))
        end = lane_end(ld)
        try:
            ext = json.loads((ld / "extension.json").read_text())
        except (OSError, ValueError):
            ext = None
        order = []
        for line in log.open(errors="replace"):
            try:
                t = json.loads(line)
            except ValueError:
                continue
            order.append(t.get("row"))
        prior = [l for l in (ld / "CONTINUES.txt").read_text().split()] if (ld / "CONTINUES.txt").exists() else []
        for bf in sorted(ld.glob("base/*/*.c")):
            rid = bf.parent.name + "/" + bf.stem
            if rid not in by:
                continue
            base = npins(bf.read_text(errors="replace"))
            staged = [npins(f.read_text(errors="replace")) for f in ld.glob(f"out/{rid}.c")]
            staged = min(staged) if staged else None
            ts = trials.get(rid, [])
            best, last_imp = None, None
            for i, (dist, p) in enumerate(ts):
                if p < base and dist > 0 and (best is None or (dist, p) < best):
                    best, last_imp = (dist, p), i
            if rid not in now_cache:
                try:
                    now_cache[rid] = npins(clean_path(by[rid]).read_text(errors="replace"))
                except OSError:
                    now_cache[rid] = None
            now = now_cache[rid]
            floor = min(base, staged) if staged is not None else base
            extra = {}
            if ext:
                cut = ext.get("lab_trials_before", 0)
                idx = [i for i, r in enumerate(order) if r == rid]
                before, after = sum(1 for i in idx if i < cut), sum(1 for i in idx if i >= cut)
                sb = ext.get("staged_before", {}).get(rid)
                extra = {"arm": "extend", "trials_before": before, "trials_after": after, "staged_before": sb,
                         "gain": (min(base, sb if sb is not None else base) - floor)}
            elif prior:
                extra = {"arm": "fresh", "prior": prior}
            recs.append({**extra,
                "lane": ld.name, "row": rid, "end": end, "base": base, "staged": staged, "trials": len(ts),
                "best_near": list(best) if best else None,
                "near": bool(best and best[0] <= 4 and (staged is None or best[1] < staged)),
                "late": bool(best and len(ts) >= 4 and last_imp >= 0.75 * len(ts)),
                "now": now, "later": now is not None and now < floor,
                "continued_by": sorted(l for l in cont.get(ld.name, ()) if (LANES / l / "base" / (rid + ".c")).exists()),
            })
    # the arms: an extension is scored on its own before/after; a fresh continuation against the best floor
    # (fewest pins staged or landed-at-serve) any of its prior lanes reached on that row
    floors = defaultdict(dict)
    for r in recs:
        floors[r["lane"]][r["row"]] = r
    for r in recs:
        if r.get("arm") == "fresh":
            pf = [floors[p][r["row"]] for p in r["prior"] if r["row"] in floors.get(p, {})]
            pfloor = min([x["base"] if x["staged"] is None else min(x["base"], x["staged"]) for x in pf] or [r["base"]])
            mine = r["base"] if r["staged"] is None else min(r["base"], r["staged"])
            r["prior_near"] = any(x["near"] for x in pf)
            r["gain"] = min(pfloor, r["base"]) - mine
    if a.json:
        with open(a.json, "w") as fh:
            for r in recs:
                fh.write(json.dumps(r, sort_keys=True) + "\n")
    agg = defaultdict(lambda: defaultdict(int))
    for r in recs:
        g = agg[r["end"]]
        g["rows"] += 1
        g["staged"] += r["staged"] is not None and r["staged"] < r["base"]
        if r["near"]:
            g["near_unstaged"] += 1
            g["near_late"] += r["late"]
            g["near_later_reduced"] += r["later"]
            g["near_continued"] += bool(r["continued_by"])
            g["near_continued_reduced"] += bool(r["continued_by"]) and r["later"]
    cols = ["rows", "staged", "near_unstaged", "near_late", "near_later_reduced", "near_continued",
            "near_continued_reduced"]
    print("| end | " + " | ".join(cols) + " |")
    print("|---|" + "---:|" * len(cols))
    for end in sorted(agg):
        print(f"| {end} | " + " | ".join(str(agg[end][c]) for c in cols) + " |")
    arms = defaultdict(lambda: defaultdict(int))
    for r in recs:
        if r.get("arm"):
            g = arms[r["arm"]]
            g["rows"] += 1
            g["rows_gained"] += r.get("gain", 0) > 0
            g["pins_gained"] += max(r.get("gain", 0), 0)
            g["running"] += r["end"] == "running"
    if arms:
        print("\n| arm | rows | rows with fewer pins | pins removed beyond the prior floor | still running |\n|---|---:|---:|---:|---:|")
        for k, g in sorted(arms.items()):
            print(f"| {k} | {g['rows']} | {g['rows_gained']} | {g['pins_gained']} | {g['running']} |")
        print("(tokens per arm: python3 tools/lanes/ab_report.py --glob '<lane>'; an extension's usage is its session "
              "total minus extension.json prior_tokens)")
    print("\nnear = a non-exact state with fewer pins at listing distance <= 4 that the lane did not stage; "
          "late = still improving in the last 25% of that row's trials; later_reduced = the row has fewer pins now "
          "than the lane left it with.")


if __name__ == "__main__":
    main()
