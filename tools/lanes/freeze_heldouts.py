#!/usr/bin/env python3
"""Freeze a blocker lane's held-out sets from the CURRENT tree (after landing, before launch).

    python3 tools/lanes/freeze_heldouts.py --lane work/native_lane/<lane> --population ROWS.txt \\
        --census CENSUS.jsonl --quota ops=16,wiring=12,late=8,order=4 [--h2 40] [--seed 20260915] [--dry]

H1: census rows in the population, stratified by class at combine (the quota); H2: a random --h2 of the
population outside the census; development: the rest. Writes population_rows.txt,
heldout_h1_census_rows.txt, heldout_h2_population_rows.txt, development_rows.txt and
evidence/heldout_manifest.json (each selection rule, and a sha over the row texts) into the lane
(docs/LANE_KIT.md, "Before launch" item 6). Generalised in round 24 from keep_astra's freeze script.
"""
import argparse
import datetime
import hashlib
import json
import random
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from phase_census import classify


def text(rid):
    return (ROOT / "src" / (rid + ".c")).read_text(errors="replace")


def sha(ids):
    return hashlib.sha256("".join(hashlib.sha256(text(r).encode()).hexdigest() for r in ids).encode()).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lane", required=True)
    ap.add_argument("--population", required=True, help="file of row ids")
    ap.add_argument("--census", required=True, help="phase_census.py run output")
    ap.add_argument("--quota", default="ops=16,wiring=12,late=8,order=4")
    ap.add_argument("--h2", type=int, default=40)
    ap.add_argument("--seed", type=int, default=20260915)
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()
    L = Path(a.lane)
    rng = random.Random(a.seed)
    pop = sorted({l.strip() for l in open(a.population) if l.strip()})
    popset = set(pop)
    census = [json.loads(l) for l in open(a.census)]
    by_cls = {}
    for c in census:
        if c["id"] in popset and "phases" in c:
            by_cls.setdefault(classify(c), set()).add(c["id"])
    quota = dict((k, int(v)) for k, v in (x.split("=") for x in a.quota.split(",")))
    h1 = []
    for k, n in quota.items():
        cand = sorted(by_cls.get(k, set()) - set(h1))
        rng.shuffle(cand)
        h1 += cand[:n]
    rest = sorted(popset - set(h1) - {c["id"] for c in census})
    rng.shuffle(rest)
    h2, h1 = sorted(rest[:a.h2]), sorted(h1)
    dev = sorted(popset - set(h1) - set(h2))
    got = {k: sum(1 for r in h1 if r in by_cls.get(k, ())) for k in quota}
    if a.dry:
        print("DRY: population", len(pop), "H1", len(h1), got, "H2", len(h2), "dev", len(dev))
        return
    (L / "evidence").mkdir(parents=True, exist_ok=True)
    for name, ids in (("population_rows.txt", pop), ("heldout_h1_census_rows.txt", h1),
                      ("heldout_h2_population_rows.txt", h2), ("development_rows.txt", dev)):
        (L / name).write_text("\n".join(ids) + "\n")
    man = dict(frozen=datetime.datetime.now(datetime.timezone.utc).isoformat(), seed=a.seed,
               population=dict(rows=len(pop), rule="rows listed in %s" % a.population),
               h1=dict(rows=len(h1), rule="census rows (%s) stratified by class at combine: %s" % (a.census, a.quota),
                       by_class=got, text_sha=sha(h1)),
               h2=dict(rows=len(h2), rule="random %d of the population outside the census" % a.h2, text_sha=sha(h2)),
               development=dict(rows=len(dev), rule="population minus H1 and H2"))
    (L / "evidence/heldout_manifest.json").write_text(json.dumps(man, indent=1))
    print(json.dumps(man, indent=1))


if __name__ == "__main__":
    main()
