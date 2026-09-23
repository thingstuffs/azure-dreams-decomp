#!/usr/bin/env python3
"""Clone families over the CURRENT pinned rows: who is a clone of whom, what each member still pins,
which lanes served it, and whether any lane already holds a better text for any member.

APPEARS.  Round 76's scan: 19 families of near-identical pinned rows (identifier-normalised line
signatures, difflib ratio >= 0.9) hold 80 rows / 328 pins, ~249 of them beyond one representative per
family (dungeon/func_80C1B09C + 9 siblings = 110 pins alone).  One solved member is worth the family
through tools/lanes/clone_transfer.py; an unsolved family is ONE model-lane target, not ten.

WHAT IT WRITES.  ledger/clone_families.jsonl, one record per family (schema azure-clean.clone-families.v1):
  * members: id, pins, pin macros, code lines, served lanes (tools/lanes/served.py), and every lane
    out/ file for that row (glob work/native_lane/*/out/<container>/<name>.c per row - no tree grep)
    with its pin count, whether its .base_sha is still the row's current text, and - with --verify -
    whether it is byte-exact now;
  * exemplars: lane (base, out) pairs from --lanes-glob whose BASE is a family clone (>= --threshold)
    and whose out has fewer pins - including rows that already left the pinned set (landed), which
    are the family's proven partials;
  * representative: the member with the best byte-exact partial (fewest pins left), else the member
    with the fewest pins (unserved first, then the shortest text) - the one to hand a model lane;
  * residue: the pin macros and the 'removing it ...' reasons of the representative's pin comments.

    python3 tools/lanes/clone_families.py                       # census + ledger, no scorer runs
    python3 tools/lanes/clone_families.py --verify --workers 12 # also score every lane partial
    python3 tools/lanes/clone_families.py --report              # print the ledger as a table
"""
from __future__ import annotations

import argparse
import collections
import json
import re
import sys
import tempfile
import time
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
sys.path.insert(0, str(ROOT / "tools/xform"))

import clone_transfer as C  # noqa: E402
from common import rows, clean_path, sha_text  # noqa: E402
from pin_census import sites_of  # noqa: E402

LEDGER = ROOT / "ledger/clone_families.jsonl"
SCHEMA = "azure-clean.clone-families.v1"
REASON_RE = re.compile(r"removing it ([^;*]+?)[;*]")


def pinned_docs(skip=("ovmovie",)):
    """{row id: (row, Doc, pins)} for every pinned row outside the parked containers."""
    out = {}
    for r in rows():
        if r["container"] in skip:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        t = p.read_text(errors="replace")
        n = len(sites_of(t))
        if n:
            out[r["id"]] = (r, C.Doc(r["id"], t), n)
    return out


_DOCS = {}


def _pairs_for(args):
    """Clone pairs (i < j) of one row against the later rows, under the census prefilters."""
    i, ids, threshold, jac = args
    a = _DOCS[ids[i]]
    out = []
    for j in range(i + 1, len(ids)):
        b = _DOCS[ids[j]]
        lo, hi = sorted((a.nlines, b.nlines))
        if hi == 0 or 2 * lo / (lo + hi) < threshold:      # difflib ratio <= 2*min/(a+b)
            continue
        if C.jaccard(a.shingles, b.shingles) < jac:
            continue
        s = C.similarity(a, b)
        if s >= threshold:
            out.append((ids[i], ids[j], round(s, 4)))
    return out


def clone_pairs(docs, threshold=0.9, jac=0.4, workers=12):
    global _DOCS
    _DOCS = docs
    ids = sorted(docs)
    with ProcessPoolExecutor(workers) as ex:       # fork: the workers inherit _DOCS
        res = ex.map(_pairs_for, [(i, ids, threshold, jac) for i in range(len(ids))], chunksize=8)
        return [p for chunk in res for p in chunk]


def union_find(pairs):
    parent = {}

    def find(x):
        parent.setdefault(x, x)
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    for a, b, _ in pairs:
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[max(ra, rb)] = min(ra, rb)
    groups = collections.defaultdict(list)
    for x in parent:
        groups[find(x)].append(x)
    return [sorted(v) for v in groups.values()]


def lane_outs(rid, row, cur_sha, cur_pins):
    """Every lane out/ file for this row: [{lane, path, pins, base_current}] (a glob per row)."""
    c, n = rid.split("/")
    out = []
    for f in sorted((ROOT / "work/native_lane").glob(f"*/out/{c}/{n}.c")):
        lane = f.parts[-4]
        t = f.read_text(errors="replace")
        bs = f.with_name(f.name + ".base_sha")
        base_current = bs.exists() and bs.read_text().strip() == cur_sha
        out.append({"lane": lane, "path": str(f.relative_to(ROOT)), "pins": len(sites_of(t)),
                    "base_current": base_current, "sha": sha_text(t)})
    return out


def verify_text(row, text):
    from verify import verify
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / Path(row["c_path"]).name
        p.write_text(text)
        res = verify(row, p, include_root=ROOT / "include")
    return bool(res.get("exact")), res.get("status")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--threshold", type=float, default=0.9)
    ap.add_argument("--jaccard", type=float, default=0.4)
    ap.add_argument("--lanes-glob", default="r5*,r6*,r7*", help="exemplar lanes (base/ + out/)")
    ap.add_argument("--exemplar-threshold", type=float, default=0.9)
    ap.add_argument("--verify", action="store_true", help="score lane partials with fewer pins than src")
    ap.add_argument("--workers", type=int, default=12)
    ap.add_argument("--out", default=str(LEDGER))
    ap.add_argument("--report", action="store_true", help="print the ledger and stop")
    ap.add_argument("--stage-partials", metavar="LANE",
                    help="stage every verified byte-exact lane partial with fewer pins than src (a stale "
                         ".base_sha is why the landing skipped it) into work/native_lane/LANE, re-based on "
                         "the row's current text; needs --verify")
    a = ap.parse_args()

    if a.report:
        report(Path(a.out))
        return
    t0 = time.time()
    P = pinned_docs()
    docs = {k: v[1] for k, v in P.items()}
    pairs = clone_pairs(docs, a.threshold, a.jaccard, a.workers)
    fams = [f for f in union_find(pairs) if len(f) > 1]
    print(f"{len(P)} pinned rows, {len(pairs)} clone pairs, {len(fams)} families ({time.time() - t0:.0f}s)",
          flush=True)
    sim = {}
    for x, y, s in pairs:
        sim[(x, y)] = sim[(y, x)] = s

    from served import served_rows
    served = served_rows()

    # exemplar pairs whose base is a clone of some family member
    lanes = C.lanes_matching(a.lanes_glob)
    exemplars = C.load_exemplars(lanes)
    print(f"{len(exemplars)} exemplar pairs from {len(lanes)} lanes ({time.time() - t0:.0f}s)", flush=True)

    recs = []
    verify_jobs = []
    for fi, fam in enumerate(sorted(fams, key=lambda f: -sum(P[m][2] for m in f))):
        members = []
        for m in fam:
            row, d, n = P[m]
            cur = d.text
            outs = [o for o in lane_outs(m, row, sha_text(cur), n)]
            for o in outs:
                if o["pins"] < n:
                    verify_jobs.append((fi, m, o))
            members.append({"id": m, "pins": n, "lines": d.nlines,
                            "macros": dict(collections.Counter(s[1] for s in sites_of(cur))),
                            "served": served.get(m, []), "lane_outs": outs})
        exs = []
        for ex in exemplars:
            best = 0.0
            eb = ex["base"]
            for m in fam:
                d = docs[m]
                lo, hi = sorted((eb.nlines, d.nlines))
                if hi == 0 or 2 * lo / (lo + hi) < a.exemplar_threshold:
                    continue
                if C.jaccard(eb.shingles, d.shingles) < a.jaccard:
                    continue
                best = max(best, C.similarity(eb, d))
            if best >= a.exemplar_threshold:
                exs.append({"lane": ex["lane"], "id": ex["id"], "proof": ex["proof"],
                            "similarity": round(best, 4), "pins_in": ex["pins_in"], "pins_out": ex["pins_out"]})
        exs.sort(key=lambda e: (C.PROOF_RANK[e["proof"]], -(e["pins_in"] - e["pins_out"]), -e["similarity"]))
        recs.append({"schema": SCHEMA, "family": fi, "members": members, "exemplars": exs,
                     "pins": sum(m["pins"] for m in members),
                     "min_similarity": min(sim.get((x, y), 1.0) for x in fam for y in fam if x < y
                                           and (x, y) in sim) if len(fam) > 1 else 1.0})
    print(f"families described; {len(verify_jobs)} lane partials with fewer pins ({time.time() - t0:.0f}s)",
          flush=True)

    if a.verify and verify_jobs:
        def job(j):
            fi, m, o = j
            row = P[m][0]
            t = (ROOT / o["path"]).read_text(errors="replace")
            ok, st = verify_text(row, t)
            return j, ok, st
        with ThreadPoolExecutor(a.workers) as ex:
            for (fi, m, o), ok, st in ex.map(job, verify_jobs):
                o["exact"] = ok
                o["status"] = st

    for r in recs:
        # effective pins: what the member would carry after its best byte-exact lane partial
        def eff(m):
            ex = [o["pins"] for o in m["lane_outs"] if o["pins"] < m["pins"] and o.get("exact")]
            return min(ex) if ex else m["pins"], bool(ex)
        rep = min(r["members"], key=lambda m: (eff(m)[0], not eff(m)[1], bool(m["served"]), m["lines"], m["id"]))
        r["representative"] = rep["id"]
        e, has = eff(rep)
        r["rep_reason"] = (f"byte-exact lane partial ({rep['pins']} -> {e} pins)" if has else
                           "fewest pins" + ("" if rep["served"] else ", unserved") + ", shortest")
        rep_pins = rep["pins"]
        r["pins_beyond_rep"] = r["pins"] - rep_pins
        text = P[r["representative"]][1].text
        r["residue"] = {
            "macros": dict(collections.Counter(s[1] for s in sites_of(text))),
            "reasons": dict(collections.Counter(m.group(1).strip() for m in REASON_RE.finditer(text))),
        }
        r["unserved_members"] = sum(1 for m in r["members"] if not m["served"])

    if a.stage_partials:
        from clone_transfer import stage
        lane = ROOT / "work/native_lane" / a.stage_partials
        J = lane / "journal.jsonl"
        for r in recs:
            for m in r["members"]:
                for o in m["lane_outs"]:
                    if o["pins"] < m["pins"] and o.get("exact") and not o["base_current"]:
                        row, d, _ = P[m["id"]]
                        text = (ROOT / o["path"]).read_text()
                        from pin_census import unscored_text
                        if unscored_text(text) != unscored_text(d.text) or C.scaffold_grew(text, d.text):
                            print(f"not staged {m['id']} from {o['lane']}: edits an unscored arm or grows scaffolding")
                            continue
                        stage(a.stage_partials, row, text, d.text)
                        with J.open("a") as f:
                            f.write(json.dumps({"id": m["id"], "outcome": "exact", "from": o["path"],
                                                "pins_in": m["pins"], "pins_out": o["pins"],
                                                "note": "stale base_sha re-based on the current text"}) + "\n")
                        print(f"staged {m['id']} {m['pins']} -> {o['pins']} from {o['lane']}")
        (lane / ".ignore").write_text("*\n")

    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    with open(a.out, "w") as f:
        for r in recs:
            f.write(json.dumps(r) + "\n")
    tot = sum(r["pins"] for r in recs)
    beyond = sum(r["pins_beyond_rep"] for r in recs)
    print(f"{len(recs)} families, {sum(len(r['members']) for r in recs)} rows, {tot} pins, "
          f"{beyond} beyond one representative -> {a.out} ({time.time() - t0:.0f}s)")
    report(Path(a.out))


def report(path):
    for r in (json.loads(l) for l in path.open()):
        ms = r["members"]
        partial = [(m["id"], o["lane"], o["pins"], o.get("exact")) for m in ms for o in m["lane_outs"]
                   if o["pins"] < m["pins"]]
        print(f"F{r['family']:<3d} {len(ms):2d} rows {r['pins']:4d} pins (+{r['pins_beyond_rep']:3d})  "
              f"rep {r['representative']} [{r['rep_reason']}]  served {len(ms) - r['unserved_members']}/{len(ms)}  "
              f"exemplars {len(r['exemplars'])} (proven {sum(1 for e in r['exemplars'] if e['proof'] != 'unproven')})  "
              f"partials {len(partial)} exact {sum(1 for p in partial if p[3])}")


if __name__ == "__main__":
    main()
