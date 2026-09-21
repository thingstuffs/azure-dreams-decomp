#!/usr/bin/env python3
"""lab.py - THE lane harness: erase, build, screen, score, log.  Do not write your own.

Sixteen of sixteen astra lanes and most sol lanes rebuilt this exact loop from scratch, and two
lanes went digging through other lanes' directories to copy one.  This is that loop, with the
regression guards the best of them had (`work/native_lane/r63_astra_movemove/lab.py`) and the
admission gate seven lanes re-derived (`work/native_lane/r62_astra_big/publish_local.py`).

    cd work/native_lane/<lane>
    python3 <repo>/tools/lanes/lanekit/lab.py baseline dungeon/func_8009612C --score
    python3 <repo>/tools/lanes/lanekit/lab.py dungeon/func_8009612C v1.c v2.c --score
    python3 <repo>/tools/lanes/lanekit/lab.py dungeon/func_8009612C --subs shapes1.json --score
    python3 <repo>/tools/lanes/lanekit/lab.py report

STEP 1 IS `baseline <row> --score`.  It scores the row's OWN pinned text.  A pinned row is
byte-exact, so the scorer must say `exact=True, total=0`; if it does not, your adapter or your base
copy is wrong and every later number is noise.  One lane caught a silent mis-scoring bug this way
in its first fifteen minutes; no other lane checked.

TWO-TIER SCREEN.  The cc1 listing (~15 ms) is compared with the PINNED text's listing, which is
retail's instruction order on a byte-exact row: distance 0 is listing-exact and nearly always
byte-exact.  `--score` sends only the distance-0 variants to the byte scorer (~5-20 s each);
`--score-top N` also scores the N nearest.  In the lanes that solved rows, 1-6% of variants reached
the scorer.  Scoring everything is how a lane runs out of time.

VARIANTS.  Either `.c` files (the variant's name is the file stem) or a `variants.json` of
`{"name": [["old","new"], ...]}` applied to the pin-erased base - byte-compatible with
`tools/xform/variant_screen.py`, including `@name` for "start from the PINNED text".  A miss prints
the nearest lines in the text instead of a bare AssertionError.

EVERY measurement, including refusals and failed builds, is appended to `lab_log.jsonl` in the lane,
and `lab.py report` turns that file into the REPORT.md table - so the table is derived from what was
measured, never typed by hand.  A row with ZERO measurements is printed as such: one sol lane in
fourteen left two of its five rows with no attempt at all and nothing in the report showed it.

CAP.  More than 60 variants for one row needs `--more`.  One lane produced 209 probe files for two
of its five rows and left the other three nearly untouched.
"""
from __future__ import annotations

import argparse
import json
import shutil
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402


class Lab:
    """One row, ready to measure.  `Lab(row_id).test(name, text)` is the whole interface."""

    def __init__(self, row_id, lane=None, stage=True):
        self.lane = kitlib.bootstrap(lane)
        self.row = kitlib.row_of(row_id)
        self.id = self.row["id"]
        self.base_path = kitlib.base_path(self.row, self.lane)
        self.base = self.base_path.read_text(errors="replace")
        self.sites = kitlib.sites(self.base)
        self.erased = kitlib.erased_text(self.base)
        self.screen = kitlib.screen_for(self.row, self.base)
        self.stage = stage
        self.dir = self.lane / "experiments" / self.row["func"]
        self.dir.mkdir(parents=True, exist_ok=True)
        if self.screen.target is None:
            raise SystemExit("lab: the row's own pinned text does not build - check base/ and the recipe")
        (self.dir / "pinned.s").write_text("\n".join(self.screen.target) + "\n")

    # ------------------------------------------------------------------ measurement

    def log(self, rec):
        rec = dict(rec, row=self.id)
        kitlib.log_append(self.lane, rec)
        return rec

    def count(self):
        return kitlib.variant_count(kitlib.log_read(self.lane), self.id)

    def guards(self, text):
        """The two regression guards worth keeping from the best lane harness."""
        bad = []
        if len(kitlib.sites(text)) > len(self.sites):
            bad.append("more pin sites than the base")
        if text.count("volatile") > self.base.count("volatile"):
            bad.append("adds volatile")
        return bad

    def test(self, name, text, note="", score=False, stage=None):
        bad = self.guards(text)
        if bad:
            rec = self.log({"variant": name, "distance": None, "score": None, "note": note,
                            "status": "refused", "why": "; ".join(bad)})
            print("%-28s REFUSED  %s" % (name, rec["why"]))
            return rec
        p = self.dir / (name + ".c")
        p.write_text(text)
        d = self.screen.diff(text, 4)
        dist = None if d is None else sum(1 for l in d if l[:1] in "+-")
        (self.dir / (name + ".diff")).write_text("\n".join(d or ["DOES NOT BUILD"]) + "\n")
        rec = {"variant": name, "distance": dist, "score": None, "note": note,
               "status": "no-build" if d is None else "measured", "pins": len(kitlib.sites(text))}
        if score and dist == 0:
            v = self.screen.exact(text)
            rec["score"] = {k: v.get(k) for k in ("exact", "total", "subs", "indels", "status")}
            rec["status"] = "exact" if v.get("exact") else "scored"
            if v.get("exact") and (self.stage if stage is None else stage):
                rec["staged"] = self.publish(name, text)
        self.log(rec)
        print("%-28s dist %-5s pins %-3s %s%s"
              % (name, "-" if dist is None else dist, rec.get("pins", "-"),
                 json.dumps(rec["score"]) if rec["score"] else "",
                 "  -> " + rec["staged"] if rec.get("staged") else ""))
        return rec

    def test_file(self, path, score=False, note=""):
        path = Path(path)
        return self.test(path.stem, path.read_text(errors="replace"), note=note, score=score)

    def test_subs(self, name, reps, score=False, note=""):
        base = self.base if name.startswith("@") else self.erased
        try:
            text = kitlib.apply_subs(base, reps, label=name)
        except KeyError as e:
            self.log({"variant": name, "distance": None, "score": None, "note": note,
                      "status": "pattern-missing", "why": str(e)[:400]})
            print("%-28s SKIP  %s" % (name, str(e).splitlines()[0]))
            return None
        return self.test(name.lstrip("@"), text, note=note, score=score)

    # ------------------------------------------------------------------ baseline + staging

    def baseline(self, score=False):
        """Calibration: the pinned control, and the all-pins-erased reference distance."""
        rec = {"variant": "pinned_control", "kind": "baseline", "distance": 0,
               "pins": len(self.sites), "status": "measured", "score": None}
        if score:
            v = self.screen.exact(self.base)
            rec["score"] = {k: v.get(k) for k in ("exact", "total", "subs", "indels", "status")}
            rec["status"] = "calibrated" if v.get("exact") else "CALIBRATION-FAILED"
        self.log(rec)
        ed = self.screen.distance(self.erased)
        self.log({"variant": "all_pins_erased", "kind": "baseline", "distance": ed,
                  "pins": len(kitlib.sites(self.erased)), "status": "measured", "score": None})
        print("%-28s %s" % ("pinned_control", json.dumps(rec["score"]) if score else "distance 0"))
        if score and not (rec["score"] or {}).get("exact"):
            print("  *** the pinned text does NOT score exact: stop and fix the base/recipe ***")
        print("%-28s dist %s   (%d pins erased)" % ("all_pins_erased", ed, len(self.sites)))
        return rec

    def publish(self, name, text):
        """Copy an exact, admissible candidate to `out/<container>/<file>.c` with its base sha."""
        bad = kitlib.admissible(self.base, text)
        if bad:
            print("  NOT staged (%s)" % "; ".join(bad))
            return None
        out = self.lane / "out" / self.row["container"]
        out.mkdir(parents=True, exist_ok=True)
        dst = out / Path(self.row["c_path"]).name
        dst.write_text(text)
        sha = self.base_path.with_name(self.base_path.name + ".base_sha")
        if sha.is_file():
            shutil.copyfile(sha, dst.with_name(dst.name + ".base_sha"))
        else:
            import hashlib
            dst.with_name(dst.name + ".base_sha").write_text(
                hashlib.sha256(self.base.encode()).hexdigest() + "\n")
        return str(dst.relative_to(self.lane))


# ------------------------------------------------------------------------------------- report

def report(lane, row_id=None):
    recs = kitlib.log_read(lane)
    served = kitlib.lane_rows(lane)
    ids = [row_id] if row_id else sorted({r.get("row") for r in recs if r.get("row")} | set(served))
    out = []
    for rid in ids:
        mine = [r for r in recs if r.get("row") == rid]
        real = [r for r in mine if r.get("kind") != "baseline"]
        out.append("### %s" % rid)
        if not real:
            out.append("")
            out.append("**ZERO MEASUREMENTS** - this row was never tried.  A row with no attempt is "
                       "not an open row; it is an unworked row.")
            out.append("")
            continue
        body = []
        for r in sorted(real, key=lambda r: (r.get("distance") is None, r.get("distance") or 0)):
            s = r.get("score") or {}
            body.append([r.get("variant"), r.get("status"),
                         "-" if r.get("distance") is None else r["distance"],
                         r.get("pins", "-"),
                         "" if not s else "exact" if s.get("exact") else "total %s" % s.get("total"),
                         (r.get("note") or r.get("why") or "")[:60]])
        best = min((r["distance"] for r in real if r.get("distance") is not None), default=None)
        out.append("")
        out.append("%d variants measured, best listing distance %s, %d scored, %d exact."
                   % (len({r.get("variant") for r in real}), best,
                      sum(1 for r in real if r.get("score")),
                      sum(1 for r in real if (r.get("score") or {}).get("exact"))))
        out.append("")
        out.append("```")
        out.append(kitlib.fmt_table(["variant", "status", "dist", "pins", "score", "note"], body))
        out.append("```")
        out.append("")
    return "\n".join(out)


# ---------------------------------------------------------------------------------------- CLI

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id", help="row id, or 'report', or 'baseline'")
    ap.add_argument("rest", nargs="*", help="variant .c files (or, after 'baseline', the row id)")
    ap.add_argument("--subs", help="variants.json: {name: [[old,new],...]} on the pin-erased base")
    ap.add_argument("--score", action="store_true", help="byte-score the listing-exact variants")
    ap.add_argument("--score-top", type=int, default=0, metavar="N",
                    help="also score the N nearest non-exact variants of this run")
    ap.add_argument("--note", default="", help="note recorded with every variant of this run")
    ap.add_argument("--more", action="store_true", help="allow more than %d variants for this row" % kitlib.VARIANT_CAP)
    ap.add_argument("--no-stage", action="store_true", help="do not copy an exact candidate to out/")
    ap.add_argument("--row", help="report: limit to one row")
    a = ap.parse_args()

    if a.row_id == "report":
        lane = kitlib.bootstrap()
        text = report(lane, a.row)
        print(text)
        (lane / "REPORT_TABLE.md").write_text(text + "\n")
        print("(written to %s)" % (lane / "REPORT_TABLE.md"), file=sys.stderr)
        return

    if a.row_id == "baseline":
        if not a.rest:
            raise SystemExit("lab.py baseline <row_id> [--score]")
        for rid in a.rest:
            Lab(rid, stage=not a.no_stage).baseline(score=a.score)
        return

    lab = Lab(a.row_id, stage=not a.no_stage)
    jobs = []
    for f in a.rest:
        jobs.append(("file", f))
    if a.subs:
        for name, reps in json.load(open(a.subs)).items():
            jobs.append(("subs", (name, reps)))
    if not jobs:
        lab.baseline(score=a.score)
        return

    have = lab.count()
    if have + len(jobs) > kitlib.VARIANT_CAP and not a.more:
        raise SystemExit(
            "lab: %s already has %d measured variants; this run adds %d, over the cap of %d.\n"
            "  Pass --more if that is really the next best use of the time.  (One lane spent its\n"
            "  session on 209 probes for two rows and left three rows nearly untouched.)"
            % (lab.id, have, len(jobs), kitlib.VARIANT_CAP))

    done = []
    for kind, job in jobs:
        if kind == "file":
            done.append(lab.test_file(job, score=a.score, note=a.note))
        else:
            done.append(lab.test_subs(job[0], job[1], score=a.score, note=a.note))
    if a.score_top:
        rest = sorted((r for r in done if r and r.get("distance") and not r.get("score")),
                      key=lambda r: r["distance"])[:a.score_top]
        for r in rest:
            text = (lab.dir / (r["variant"] + ".c")).read_text()
            v = lab.screen.exact(text)
            lab.log({"variant": r["variant"], "distance": r["distance"], "status": "scored-near",
                     "score": {k: v.get(k) for k in ("exact", "total", "subs", "indels", "status")}})
            print("%-28s dist %-5s scored total=%s exact=%s"
                  % (r["variant"], r["distance"], v.get("total"), v.get("exact")))


if __name__ == "__main__":
    main()
