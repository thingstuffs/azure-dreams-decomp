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
    python3 <repo>/tools/lanes/lanekit/lab.py dungeon/func_8009612C --grid grid1.json --score
    python3 <repo>/tools/lanes/lanekit/lab.py dungeon/func_8009612C v7.c --cfg "2.8.1-G0" --score
    python3 <repo>/tools/lanes/lanekit/lab.py cellscore dungeon/func_8009612C v7.c --cfg "2.8.1-G0"
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

GRID.  `--grid grid.json` = `{"axis": {"label": [["old","new"], ...], ...}, ...}`: one label per
axis, every combination (the cartesian product, axes in file order), the variant named by its labels
joined with '+' (`keep+late+s16`), the chosen lists applied in axis order through the same
substitution machinery as `--subs` (nearest-line message on a miss, logged `pattern-missing`).  A
label may map to `[]` ("leave it").  A top-level `"@base": "pinned"` starts from the pinned text.
About 21 lanes hand-wrote this as `itertools.product` scripts whose misses were never logged.

ANOTHER CFG.  `--cfg CFG` compiles and scores the variants as if the row were registered at CFG
(the row-dict override `land_coherence.sh` uses); the listing distance is still against the PINNED
text at the REGISTERED cfg (retail's order), so it is information only: with `--score` every
variant that builds is scored, and nothing is staged.  `cellscore <row> <cand.c> --cfg CFG` scores
one candidate that way, checks rule 2 (is the pinned text also exact at CFG?) and, when exact,
prints the `cells.jsonl` line and the `land_coherence.sh` command.  The row's registered cfg is
never changed and nothing under `ledger/` or `config/` is written.

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

    def __init__(self, row_id, lane=None, stage=True, cfg=None):
        self.lane = kitlib.bootstrap(lane)
        self.row = kitlib.row_of(row_id)
        if cfg and cfg != self.row["cfg"]:
            kitlib.row_at_cfg(self.row, cfg)   # grouped SLUS rows require a full-cohort recipe trial
        self.id = self.row["id"]
        self.context_fingerprint = kitlib.module_fingerprint(self.row)
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
        self.cfg = cfg if cfg and cfg != self.row["cfg"] else None
        self.xscreen = None
        if self.cfg:                  # target: pinned at the REGISTERED cfg; candidates at self.cfg
            self.xscreen = kitlib.screen_for(self.row, self.base)
            self.xscreen.row = kitlib.row_at_cfg(self.row, self.cfg)

    # ------------------------------------------------------------------ measurement

    def log(self, rec):
        rec = dict(rec, row=self.id)
        if getattr(self, "context_fingerprint", None) is not None:
            rec["module_fingerprint"] = self.context_fingerprint
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
        scr = self.xscreen or self.screen
        p = self.dir / (name + ".c")
        p.write_text(text)
        d = scr.diff(text, 4)
        dist = None if d is None else sum(1 for l in d if l[:1] in "+-")
        (self.dir / (name + ".diff")).write_text("\n".join(d or ["DOES NOT BUILD"]) + "\n")
        rec = {"variant": name, "distance": dist, "score": None, "note": note,
               "status": "no-build" if d is None else "measured", "pins": len(kitlib.sites(text))}
        if self.cfg:
            rec["cfg"] = self.cfg
        if score and (dist == 0 or (self.cfg and d is not None)):
            v = scr.exact(text)
            rec["score"] = kitlib.score_fields(v)
            rec["status"] = "exact" if v.get("exact") else "scored"
            if v.get("exact") and self.cfg:
                print("  exact at %s - NOT staged (registered cfg %s unchanged); hand over with "
                      "`lab.py cellscore %s %s --cfg %s`" % (self.cfg, self.row["cfg"], self.id, p, json.dumps(self.cfg)))
            elif v.get("exact") and (self.stage if stage is None else stage):
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
            msg = e.args[0] if e.args else str(e)          # str(KeyError) is a repr: quotes and escapes
            self.log({"variant": name, "distance": None, "score": None, "note": note,
                      "status": "pattern-missing", "why": msg[:400]})
            print("%-28s SKIP  %s" % (name, msg.splitlines()[0]))
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
        expected = getattr(self, "context_fingerprint", None)
        if expected is not None and kitlib.module_fingerprint(self.row) != expected:
            raise RuntimeError("module context changed during the lane; remeasure before publication")
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


# --------------------------------------------------------------------------------------- grid

def expand_grid(grid):
    """`{"axis": {"label": [[old,new],...]}, ...}` -> [(name, reps)], the cartesian product.

    Axes in file order, labels in file order; the name is the chosen labels joined with '+'; reps is
    the chosen lists concatenated in axis order.  `"@base": "pinned"` prefixes every name with '@'
    (`Lab.test_subs`: start from the pinned text)."""
    import itertools
    grid = dict(grid)
    at = "@" if str(grid.pop("@base", "erased")) == "pinned" else ""
    axes = []
    for ax, choices in grid.items():
        if not isinstance(choices, dict) or not choices:
            raise SystemExit("lab: grid axis %r must map label -> [[old,new],...]" % ax)
        for lab_, reps in choices.items():
            if not isinstance(reps, list) or any(not isinstance(p, (list, tuple)) or len(p) != 2 for p in reps):
                raise SystemExit("lab: grid %s/%s must be a list of [old, new] pairs" % (ax, lab_))
            if "+" in lab_:
                raise SystemExit("lab: grid label %r contains '+', the name separator" % lab_)
        axes.append(list(choices.items()))
    out = []
    for combo in itertools.product(*axes):
        out.append((at + "+".join(l for l, _ in combo), [list(p) for _, reps in combo for p in reps]))
    return out


def grid_misses(grid, base):
    """Each axis/label whose own substitutions do not apply to the base ALONE, with the nearest
    lines - said once, instead of once per combination.  (A label that only applies after another
    axis's edit is listed too; the combinations still run and log what they find.)"""
    out = []
    for ax, choices in grid.items():
        if ax == "@base" or not isinstance(choices, dict):
            continue
        for lab_, reps in choices.items():
            try:
                kitlib.apply_subs(base, reps, label="%s=%s" % (ax, lab_))
            except KeyError as e:
                out.append(e.args[0] if e.args else str(e))
    return out


# ---------------------------------------------------------------------------------- cellscore

def cellscore(row, cand, cfg, lane, name="candidate", base=None, verify=None, rule2=True, out=print):
    """Byte-score `cand` as `row` at `cfg` WITHOUT touching the ledger; say what the hand-over is.

    Returns the record journalled (the caller appends it to `lab_log.jsonl`)."""
    if not cfg:
        raise SystemExit("lab: cellscore needs --cfg CFG")
    if cfg == row["cfg"]:
        raise SystemExit("lab: %s is the row's registered cfg - use `lab.py %s cand.c --score`" % (cfg, row["id"]))
    kitlib.row_at_cfg(row, cfg)  # reject per-row recipe trials for grouped SLUS members
    lane = Path(lane)
    v = kitlib.score_at(row, cand, cfg, verify=verify)
    sc = kitlib.score_fields(v)
    pins_c = len(kitlib.sites(cand))
    pins_b = len(kitlib.sites(base)) if base is not None else None
    out("cellscore %s  %s" % (row["id"], name))
    out("  registered cfg : %s   (UNCHANGED - nothing under ledger/ or config/ is written)" % row["cfg"])
    out("  scored at      : %s" % cfg)
    out("  candidate      : %s   pins %s -> %s" % (json.dumps(sc), "?" if pins_b is None else pins_b, pins_c))
    rec = {"row": row["id"], "variant": name, "kind": "cellscore", "cfg": cfg, "distance": None,
           "score": sc, "pins": pins_c, "status": "exact" if sc.get("exact") else "scored",
           "note": "at %s (registered %s)" % (cfg, row["cfg"])}
    if not sc.get("exact"):
        out("  NOT exact at %s: nothing to hand over." % cfg)
        return rec
    holds = None
    if rule2 and base is not None:
        vb = kitlib.score_at(row, base, cfg, verify=verify)
        holds = bool(vb.get("exact"))
        rec["rule2"] = holds
        out("  pinned text    : %s at %s -> rule 2 %s" % (
            "EXACT" if holds else "not exact (total %s)" % vb.get("total"), cfg,
            "HOLDS: byte-neutral switch; the trade's kind is recipe-switch / pin-for-flag, not coherence "
            "(land_coherence.sh stamps kind \"coherence\" - correct the ledger line by hand)" if holds else
            "does NOT hold: a genuine coherence trade (charter clause 4b)"))
    cont, fn = row["container"], Path(row["c_path"]).name
    try:
        lane_name = str(lane.resolve().relative_to(kitlib.ROOT / "work/native_lane"))
    except ValueError:
        lane_name = "<lane under work/native_lane>"
    mech = "<mechanism: which pass / cell signature does what at %s>; %s" % (
        cfg, "rule 2 holds (pinned text also exact at target: byte-neutral)" if holds else
        "rule 2 does not hold (pinned text not exact at target)" if holds is False else "rule 2 not checked")
    line = json.dumps({"id": row["id"], "to": cfg, "coherence": mech})
    out("  EXACT at %s.  Hand-over for the orchestrator (the lane does not run these):" % cfg)
    out("    1. the candidate staged as out/%s/%s with its .base_sha (the pinned base's sha)" % (cont, fn))
    out("    2. this line in %s/cells.jsonl (fill in the mechanism):" % lane)
    out("       " + line)
    out("    3. LAND_ISOLATED=1 bash tools/lanes/land_coherence.sh <tag> %s" % lane_name)
    rec["cells_line"] = line
    return rec


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
            at = " @" + r["cfg"] if r.get("cfg") else ""      # scored at ANOTHER cfg: not a solve here
            body.append([r.get("variant"), r.get("status"),
                         "-" if r.get("distance") is None else r["distance"],
                         r.get("pins", "-"),
                         "" if not s else ("exact" if s.get("exact") else "total %s" % s.get("total")) + at,
                         (r.get("note") or r.get("why") or "")[:60]])
        best = min((r["distance"] for r in real if r.get("distance") is not None), default=None)
        out.append("")
        xc = sum(1 for r in real if r.get("cfg") and (r.get("score") or {}).get("exact"))
        out.append("%d variants measured, best listing distance %s, %d scored, %d exact%s."
                   % (len({r.get("variant") for r in real}), best,
                      sum(1 for r in real if r.get("score")),
                      sum(1 for r in real if (r.get("score") or {}).get("exact") and not r.get("cfg")),
                      " (+%d exact only at another cfg: a trade, not a solve)" % xc if xc else ""))
        out.append("")
        out.append("```")
        out.append(kitlib.fmt_table(["variant", "status", "dist", "pins", "score", "note"], body))
        out.append("```")
        out.append("")
    return "\n".join(out)


# ---------------------------------------------------------------------------------------- CLI

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id", help="row id, or 'report', 'baseline' or 'cellscore'")
    ap.add_argument("rest", nargs="*", help="variant .c files (after 'baseline': row ids; after 'cellscore': row cand.c)")
    ap.add_argument("--subs", help="variants.json: {name: [[old,new],...]} on the pin-erased base")
    ap.add_argument("--grid", help="grid.json: {axis: {label: [[old,new],...]}} -> every combination, named label+label")
    ap.add_argument("--cfg", help="compile/score at this cfg instead of the registered one (no ledger write, no staging)")
    ap.add_argument("--no-rule2", action="store_true", help="cellscore: skip scoring the pinned text at --cfg")
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

    if a.row_id == "cellscore":
        if len(a.rest) != 2 or not a.cfg:
            raise SystemExit('lab.py cellscore <row_id> <candidate.c> --cfg "CFG"')
        lane = kitlib.bootstrap()
        row = kitlib.row_of(a.rest[0])
        cp = Path(a.rest[1])
        rec = cellscore(row, cp.read_text(errors="replace"), a.cfg, lane, name=cp.stem,
                        base=kitlib.base_text(row, lane), rule2=not a.no_rule2)
        kitlib.log_append(lane, rec)
        return

    lab = Lab(a.row_id, stage=not a.no_stage, cfg=a.cfg)
    if lab.cfg:
        print("scoring at %s; registered cfg %s UNCHANGED; distance is vs the pinned listing at the "
              "registered cfg (information only); nothing is staged" % (lab.cfg, lab.row["cfg"]))
    jobs = []
    for f in a.rest:
        jobs.append(("file", f))
    if a.subs:
        for name, reps in json.load(open(a.subs)).items():
            jobs.append(("subs", (name, reps)))
    if a.grid:
        grid = json.load(open(a.grid))
        for msg in grid_misses(grid, lab.base if str(grid.get("@base")) == "pinned" else lab.erased):
            print("grid WARNING " + msg)
        for name, reps in expand_grid(grid):
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
            v = (lab.xscreen or lab.screen).exact(text)
            lab.log({"variant": r["variant"], "distance": r["distance"], "status": "scored-near",
                     **({"cfg": lab.cfg} if lab.cfg else {}),
                     "score": {k: v.get(k) for k in ("exact", "total", "subs", "indels", "status")}})
            print("%-28s dist %-5s scored total=%s exact=%s"
                  % (r["variant"], r["distance"], v.get("total"), v.get("exact")))


if __name__ == "__main__":
    main()
