#!/usr/bin/env python3
"""What has the running pin sweep actually removed?

    python3 tools/pin_watch.py              # one snapshot
    python3 tools/pin_watch.py --follow     # refresh every 60s until the sweep exits

Answers the two questions worth asking of a long run: how far has it got, and what has it
actually taken off the tree.  A landing is either a row gone completely pin-free or a partial
removal (ten pins down to one still counts - the row comes back to the next sweep smaller).

Everything here reads append-only journals; nothing recursive, nothing that touches src/.
"""
import argparse, collections, json, os, re, subprocess, sys, time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
JOURNAL = ROOT / "ledger/sweeps/t15_shapes.jsonl"


def live_totals():
    """Rows still carrying pins, and total sites, from the working tree."""
    from common import rows, clean_path
    from pin_census import sites_of
    n = s = 0
    for r in rows():
        if r["container"] == "ovmovie":
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        k = len(sites_of(p.read_text(errors="replace")))
        if k:
            n += 1
            s += k
    return n, s


def running():
    r = subprocess.run(["pgrep", "-f", "[s]weep.py t15_shapes"], capture_output=True, text=True)
    return bool(r.stdout.strip())


def snapshot(args):
    recs = []
    if JOURNAL.exists():
        for line in JOURNAL.read_text(errors="replace").splitlines():
            if line.strip():
                try:
                    recs.append(json.loads(line))
                except json.JSONDecodeError:
                    pass
    # the current run is the tail whose rows were re-served; use the log for progress
    log = ROOT / "work/t15_full.log"
    prog = ""
    if log.exists():
        for l in reversed(log.read_text(errors="replace").splitlines()):
            if "/" in l and ("applied" in l or "rows to process" in l):
                prog = l.strip()
                break

    landed = [j for j in recs if j.get("outcome") == "applied"]
    full = [j for j in landed if (j.get("pins_out") or 0) == 0]
    part = [j for j in landed if (j.get("pins_out") or 0) > 0]
    removed = sum((j.get("pins_in") or 0) - (j.get("pins_out") or 0) for j in landed)

    by_gen = collections.Counter()
    for j in landed:
        st = str(j.get("step") or "?")
        by_gen[st.split(":")[0].split("+")[0]] += 1

    print(f"=== pin sweep {'RUNNING' if running() else 'not running'} ===")
    if prog:
        print(f"  progress : {prog}")
    print(f"  landed   : {len(landed)} rows  ({len(full)} fully pin-free, {len(part)} partial)")
    print(f"  pins off : {removed}")
    if by_gen:
        print("  by shape : " + ", ".join(f"{k} {v}" for k, v in by_gen.most_common()))

    if args.rows:
        print("\n  most recent landings:")
        for j in landed[-args.rows:]:
            pi, po = j.get("pins_in"), j.get("pins_out")
            print(f"    {j['id']:34s} {pi}->{po} pins   via {j.get('step')}")

    if args.totals:
        n, s = live_totals()
        print(f"\n  tree now : {n} rows still carry pins, {s} sites "
              f"(session start 1968 rows / 12543 sites)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--follow", action="store_true", help="refresh until the sweep exits")
    ap.add_argument("--every", type=int, default=60)
    ap.add_argument("--rows", type=int, default=8, help="how many recent landings to list")
    ap.add_argument("--totals", action="store_true",
                    help="also count the working tree (a few seconds; skip when following often)")
    a = ap.parse_args()
    while True:
        os.system("clear") if a.follow else None
        snapshot(a)
        if not a.follow or not running():
            return
        time.sleep(a.every)


if __name__ == "__main__":
    main()
