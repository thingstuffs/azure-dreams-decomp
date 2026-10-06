#!/usr/bin/env python3
"""Rebase a lane's staged candidates whose base went stale (round 93).

    python3 tools/lanes/rebase_staged.py <lane> [<lane> ...] [--dry-run]

Why: land_lanes.sh skips a staged row whose `.base_sha` no longer matches src ("stale base") - e.g. a CPU sweep
(t138_protodef) typed a prototype in a row a rename lane had staged.  Both edits are usually disjoint, so the lane's
change can be replayed onto the new src with a 3-way merge (`git merge-file`: base = lane base/<c>/<name>.c,
ours = current src, theirs = lane out/<c>/<name>.c).  A clean merge is re-scored (kitlib.score_at, the lane scorer)
and, only when exact, written back to out/ with a fresh `.base_sha` (the old pair is kept as *.pre_rebase).
Conflicts and non-exact merges are reported and left alone.  Pins must not grow (kitlib.admissible vs current src).
"""
import argparse, hashlib, shutil, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / "tools/lanes/lanekit"), str(ROOT / "tools")]
import kitlib


def sha(t):
    return hashlib.sha256(t.encode()).hexdigest()


def main():
    ap = argparse.ArgumentParser(); ap.add_argument("lanes", nargs="+"); ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args(); tot = {"ok": 0, "stale": 0, "rebased": 0, "conflict": 0, "inexact": 0, "refused": 0}
    for lane in a.lanes:
        L = ROOT / "work/native_lane" / lane
        for out in sorted(L.glob("out/*/*.c")):
            c, name = out.parent.name, out.name; rid = "%s/%s" % (c, name[:-2])
            src = ROOT / "src" / c / name; bs = out.with_name(name + ".base_sha"); base = L / "base" / c / name
            cur = src.read_text(errors="replace")
            if not bs.exists() or bs.read_text().split()[0] == sha(cur):
                tot["ok"] += 1; continue
            tot["stale"] += 1
            if not base.exists():
                print("%s %s: no base text" % (lane, rid)); tot["conflict"] += 1; continue
            with tempfile.TemporaryDirectory() as td:
                o = Path(td) / "ours.c"; o.write_text(cur)
                r = subprocess.run(["git", "merge-file", "-p", str(o), str(base), str(out)], capture_output=True, text=True)
            if r.returncode != 0:
                print("%s %s: merge conflict" % (lane, rid)); tot["conflict"] += 1; continue
            merged = r.stdout
            bad = kitlib.admissible(cur, merged)
            if bad:
                print("%s %s: refused (%s)" % (lane, rid, "; ".join(bad))); tot["refused"] += 1; continue
            v = kitlib.score_at(kitlib.row_of(rid), merged)
            if not v.get("exact"):
                print("%s %s: merged text not exact (%s)" % (lane, rid, v.get("status"))); tot["inexact"] += 1; continue
            print("%s %s: rebased" % (lane, rid)); tot["rebased"] += 1
            if not a.dry_run:
                shutil.copy(out, str(out) + ".pre_rebase"); shutil.copy(bs, str(bs) + ".pre_rebase")
                out.write_text(merged); bs.write_text(sha(cur) + "\n")
                (L / "base" / c / name).write_text(cur); (L / "base" / c / (name + ".base_sha")).write_text(sha(cur) + "\n")
    print(tot)


if __name__ == "__main__":
    main()
