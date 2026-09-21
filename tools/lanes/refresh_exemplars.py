#!/usr/bin/env python3
"""Rebuild the solved-exemplar index the pack builder cites: ledger/pack_inputs/solved_exemplars.json.

    python3 tools/lanes/refresh_exemplars.py                 # rebuild, backup the old file next to it
    python3 tools/lanes/refresh_exemplars.py --dry-run       # count only, write nothing
    python3 tools/lanes/refresh_exemplars.py --no-git        # skip the git recovery of lost base texts
    python3 tools/lanes/refresh_exemplars.py --lint          # also run the port front end on each candidate

`build_class_pack.py --exemplars N` picks from this file the shortest landed diffs whose residue
classes match the pack's, and the brief tells the model to try each exemplar's move on every row
before anything else.  It is the strongest single lever in a pack, and until round 68 it was
maintained by a scratchpad script (`add_exemplars.py`, which scraped `keep <lane> <row> pins a -> b`
lines out of ONE chain's logs).  It had not been refreshed since the morning of 2026-09-20 although
about 250 rows were solved after that: packs were being briefed with a week-old set.

WHAT IT READS.  Every lane directory `work/native_lane/r5*_*`, `r6*_*` (os.scandir, one level, then
`base/<container>/` and `out/<container>/` only - never a recursive walk: the lane directories hold
the models' own dumps and are the reason `work/` is off limits to recursive search).  A lane's
candidate is `out/<container>/<name>.c`; the text it was written from is, in order:

  1. the lane's own `base/<container>/<name>.c`      - model lanes (build_class_pack.py writes it);
  2. any other lane's base file whose sha256 equals this candidate's `.c.base_sha` sidecar - covers
     the generator lanes (`gen_drive.py` stages out/ and the sha but never keeps the input text) and
     the `_arms` twins, whenever a model lane held the same text;
  3. the blob of `src/<id>.c` in this repo's history with that sha256 (`git log` + `git cat-file
     --batch`, a few seconds) - covers the rest, since a generator's input WAS the landed src text.

A candidate whose base cannot be recovered is skipped and counted: an exemplar without its diff
teaches nothing.  So is a candidate the lane's `cells.jsonl` names: it was byte-exact at another
stock recipe, which is a recipe switch rather than a C move.

WHAT IT KEEPS.  A candidate counts as a solved exemplar when its pin sites fell, no scaffolding kind
grew (land_lanes.sh's rule), and it does not edit a NON_MATCHING/#if 0 arm - the refusal that caught
five of eight re-audited lane wins on 2026-09-19.  That last check is `unscored_text` equality here,
the cheap textual half of `pin_census.landing_refusal`; `--lint` runs the full check, including the
port front end (~16 ms a row, a real compile, so it is off by default).  One record per row: the
largest pin drop wins, then the newest lane.  Records of the previous file whose row no lane covers
are carried forward with `lane: "legacy"` - a rebuild must not shrink the set the live pools read.

RECORD.  `id`, `pins` [in, out], `classes` and `L0` (the erase-census fingerprints of the row in
ledger/pack_inputs/erase_r56.jsonl, when it is known there), `cfg`, `diff` (base -> candidate,
4 lines of context, capped), and new in round 68:
  `lane`  the lane directory the diff came from - so a brief can send the model to its REPORT.md;
  `move`  one line: the generator's own step string from the lane journal (`move`/`step`/`label`),
          else the first sentence of the row's section in the lane REPORT.md, else "".
"""
from __future__ import annotations

import argparse
import difflib
import json
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))

from common import rows, sha_text, read_jsonl  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

LANE_DIR = ROOT / "work/native_lane"
LANE_RE = re.compile(r"^r[56]\d*_")
OUT = ROOT / "ledger/pack_inputs/solved_exemplars.json"
CENSUS = ROOT / "ledger/pack_inputs/erase_r56.jsonl"
DIFF_MAX_LINES = 300
MOVE_MAX = 240

# land_lanes.sh's scaffolding rule, verbatim: a candidate may not GROW a scaffolding kind.
BAD = re.compile(r"ASM_[A-Z0-9_]+(?=\()|while\s*\(\s*0\s*\)|__asm__|\bvolatile\b")


def kinds(text):
    import collections
    stripped = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return collections.Counter(m.group(0).replace(" ", "") for m in BAD.finditer(stripped))


def scaffolding_grew(cand, base):
    kc, kb = kinds(cand), kinds(base)
    return [k for k in kc if kc[k] > kb[k]]


def lane_names(root=LANE_DIR):
    """The r5*/r6* lane directories, one scandir, no recursion."""
    if not Path(root).is_dir():
        return []
    return sorted(e.name for e in os.scandir(root) if e.is_dir() and LANE_RE.match(e.name))


def _c_files(d):
    """<dir>/<container>/<name>.c - exactly two levels, the layout apply_candidates.py expects."""
    out = []
    if not Path(d).is_dir():
        return out
    for c in os.scandir(d):
        if not c.is_dir():
            continue
        for f in os.scandir(c.path):
            if f.name.endswith(".c") and f.is_file():
                out.append((c.name + "/" + f.name[:-2], Path(f.path)))
    return out


def read_text(p):
    return Path(p).read_text(errors="replace")


def base_index(lanes, root=LANE_DIR):
    """sha256 -> a base text holding it, over every lane's base/ directory."""
    idx = {}
    for lane in lanes:
        for rid, p in _c_files(Path(root) / lane / "base"):
            t = read_text(p)
            idx.setdefault(sha_text(t), t)
    return idx


def git_texts(want, root=ROOT, limit_commits=80):
    """{(id, sha): text} recovered from the history of src/<id>.c for the shas we still need."""
    found = {}
    by_row = {}
    for rid, sha in want:
        by_row.setdefault(rid, set()).add(sha)
    reqs = []
    for rid in sorted(by_row):
        path = "src/%s.c" % rid
        try:
            log = subprocess.run(["git", "log", "--format=%H", "-%d" % limit_commits, "--", path],
                                 cwd=root, capture_output=True, text=True, timeout=60)
        except Exception:
            continue
        for commit in log.stdout.split():
            reqs.append((rid, "%s:%s" % (commit, path)))
    for i in range(0, len(reqs), 200):                      # stdin closed before reading: no deadlock
        chunk = reqs[i:i + 200]
        try:
            p = subprocess.run(["git", "cat-file", "--batch"], cwd=root, timeout=300,
                               input="\n".join(r[1] for r in chunk) + "\n",
                               capture_output=True, text=True, errors="replace")
        except Exception:
            continue
        buf, pos = p.stdout, 0
        for rid, _ in chunk:
            nl = buf.find("\n", pos)
            if nl < 0:
                break
            head = buf[pos:nl]
            pos = nl + 1
            parts = head.split()
            if len(parts) != 3:                             # "<oid> missing"
                continue
            size = int(parts[2])
            body = buf[pos:pos + size]                      # sizes are bytes; these blobs are ASCII C
            pos += size + 1
            sha = sha_text(body)
            if sha in by_row.get(rid, ()):
                found[(rid, sha)] = body
    return found


def census_classes(path=CENSUS):
    """id -> (classes [L1], L0) from the erase census."""
    cls, l0 = {}, {}
    if not Path(path).exists():
        return cls, l0
    with open(path) as fh:
        for line in fh:
            if not line.strip():
                continue
            r = json.loads(line)
            fp = r.get("fp") or {}
            if fp.get("L1"):
                cls.setdefault(r["id"], set()).add(fp["L1"])
            if fp.get("L0"):
                l0.setdefault(r["id"], set()).add(fp["L0"])
    return cls, l0


def make_diff(base, cand, max_lines=DIFF_MAX_LINES):
    d = [x for x in difflib.unified_diff(base.splitlines(), cand.splitlines(), lineterm="", n=4)
         if not x.startswith(("---", "+++"))]
    if len(d) > max_lines:
        rest = len(d) - max_lines
        d = d[:max_lines] + ["... %d more diff lines (the whole rewrite is in the lane's out/)" % rest]
    return "\n".join(d)


def journal_moves(lane, root=LANE_DIR):
    """(id, in_sha) -> the generator's own step string, from a gen_drive journal."""
    j = Path(root) / lane / "journal.jsonl"
    out = {}
    for r in read_jsonl(j):
        if r.get("outcome") != "exact":
            continue
        for k in ("move", "step", "label"):
            if r.get(k):
                out[(r["id"], r.get("in_sha", ""))] = str(r[k])[:MOVE_MAX]
                break
    return out


_FIRST_SENTENCE = re.compile(r"(?<=[.;])\s")
_VERDICT = re.compile(r"^(Result|Status|Verdict|Output|Score)\b|^(EXACT|MATCH|OPEN)\b|exact: true", re.I)


def report_move(lane, rid, root=LANE_DIR):
    """The first sentence of the row's section in the lane REPORT.md, when it parses cheaply."""
    p = Path(root) / lane / "REPORT.md"
    if not p.exists():
        return ""
    try:
        import duck_brief
    except Exception:
        return ""
    try:
        sec = duck_brief.report_section(p.read_text(errors="replace"), rid)
    except Exception:
        return ""
    if not sec:
        return ""
    body = [ln for ln in sec.splitlines() if not ln.startswith("#")]
    flat = " ".join(" ".join(body).split()).replace("**", "")
    flat = re.sub(r"^[-*|\s]*", "", flat)
    if not flat:
        return ""
    sentences = [s.strip(" -|*") for s in _FIRST_SENTENCE.split(flat) if s.strip(" -|*")]
    # the scoring verdict ("Result: MATCH (exact: true, 0 subs ...)") is in every report and says
    # nothing about the move: take the first sentence that is not one.
    for s in sentences:
        if not _VERDICT.match(s):
            return s[:MOVE_MAX]
    return sentences[0][:MOVE_MAX] if sentences else ""


def build(lanes=None, root=LANE_DIR, use_git=True, lint=False, verbose=True):
    """[(record, sort key)] for every legitimate solved candidate, plus a stats dict."""
    lanes = list(lanes if lanes is not None else lane_names(root))
    idx = base_index(lanes, root)
    cls, l0 = census_classes()
    by = {r["id"]: r for r in rows()}
    stats = {"lanes": len(lanes), "candidates": 0, "no_base": 0, "not_better": 0, "arm_edit": 0,
             "grew": 0, "cell_switch": 0, "lint_refused": 0, "kept": 0, "git_recovered": 0}
    jobs, want = [], set()
    for lane in lanes:
        # gen_drive writes cells.jsonl when a candidate is byte-exact only at ANOTHER stock recipe:
        # that is a recipe switch, not a C move, and briefing a model to "try this first" at the
        # row's own recipe would mislead it.
        switched = {r["id"] for r in read_jsonl(Path(root) / lane / "cells.jsonl")}
        own = {rid: p for rid, p in _c_files(Path(root) / lane / "base")}
        for rid, p in _c_files(Path(root) / lane / "out"):
            stats["candidates"] += 1
            if rid in switched:
                stats["cell_switch"] += 1
                continue
            sidecar = Path(str(p) + ".base_sha")
            sha = sidecar.read_text().strip() if sidecar.exists() else ""
            base = None
            if rid in own:
                t = read_text(own[rid])
                if not sha or sha_text(t) == sha:
                    base = t
            if base is None and sha and sha in idx:
                base = idx[sha]
            if base is None and sha:
                want.add((rid, sha))
            jobs.append((lane, rid, p, sha, base))
    recovered = git_texts(want) if (use_git and want) else {}
    stats["git_recovered"] = len(recovered)
    out = []
    for lane, rid, p, sha, base in jobs:
        if base is None:
            base = recovered.get((rid, sha))
        if base is None:
            stats["no_base"] += 1
            continue
        cand = read_text(p)
        pin_in, pin_out = len(sites_of(base)), len(sites_of(cand))
        if pin_out >= pin_in:
            stats["not_better"] += 1
            continue
        grew = scaffolding_grew(cand, base)
        if grew:
            stats["grew"] += 1
            continue
        if unscored_text(cand) != unscored_text(base):
            stats["arm_edit"] += 1
            continue
        if lint:
            from pin_census import landing_refusal
            if landing_refusal(cand, base, "src/%s.c" % rid, row=by.get(rid)):
                stats["lint_refused"] += 1
                continue
        mv = journal_moves(lane, root).get((rid, sha), "") if (Path(root) / lane / "journal.jsonl").exists() else ""
        if not mv:
            mv = report_move(lane, rid, root)
        rec = {"id": rid, "pins": [pin_in, pin_out],
               "classes": sorted(cls.get(rid, ())), "L0": sorted(l0.get(rid, ())),
               "cfg": (by.get(rid) or {}).get("cfg", ""), "diff": make_diff(base, cand),
               "lane": lane, "move": mv}
        out.append((rec, (pin_in - pin_out, p.stat().st_mtime)))
        stats["kept"] += 1
    if verbose:
        print(stats, flush=True)
    return out, stats


def pick_best(scored):
    """One record per row: the largest pin drop, then the newest candidate."""
    best = {}
    for rec, key in scored:
        cur = best.get(rec["id"])
        if cur is None or key > cur[1]:
            best[rec["id"]] = (rec, key)
    return [best[k][0] for k in sorted(best)]


def carry_legacy(new_records, old_records):
    """Old exemplars no lane covers stay in, marked `legacy`: a rebuild must not shrink the pool.

    Only records with no lane attribution are carried - the hand-maintained ones from before round
    68.  A record an earlier REBUILD wrote names its lane, so if this run rejected that lane's
    candidate (a recipe switch, a flattened arm, a row whose pins no longer fall) the row is meant to
    be gone, and carrying it forward would quietly reinstate what was just refused."""
    have = {r["id"] for r in new_records}
    kept = []
    for r in old_records:
        if r["id"] in have or r.get("lane") not in (None, "", "legacy"):
            continue
        kept.append({**r, "lane": "legacy", "move": r.get("move", "")})
    return kept


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", default=str(OUT))
    ap.add_argument("--no-git", action="store_true", help="do not recover lost base texts from git history")
    ap.add_argument("--lint", action="store_true", help="also run pin_census.landing_refusal (compiles the port arm)")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--lane", action="append", help="only this lane (repeatable); default every r5*/r6* lane")
    a = ap.parse_args(argv)
    t0 = time.time()
    scored, stats = build(lanes=a.lane, use_git=not a.no_git, lint=a.lint)
    fresh = pick_best(scored)
    out = Path(a.out)
    old = json.loads(out.read_text()) if out.exists() else []
    legacy = carry_legacy(fresh, old)
    final = sorted(fresh + legacy, key=lambda r: r["id"])
    print("rows solved in lanes %d; carried from the old file %d; total %d (was %d) in %.0fs"
          % (len(fresh), len(legacy), len(final), len(old), time.time() - t0))
    if a.dry_run:
        return 0
    if out.exists():
        # one backup next to the file, overwritten each time: the older versions are in git, and a
        # timestamped copy per refresh would add a megabyte to the tree every round
        bak = out.with_suffix(".json.bak")
        shutil.copy2(out, bak)
        print("backup", bak)
    tmp = out.with_suffix(".json.new")                      # atomic: a pool may be building a pack now
    tmp.write_text(json.dumps(final, indent=1) + "\n")
    os.replace(tmp, out)
    print("wrote", out, len(final), "records")
    return 0


if __name__ == "__main__":
    sys.exit(main())
