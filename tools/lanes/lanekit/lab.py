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
    python3 <repo>/tools/lanes/lanekit/lab.py stage-cell dungeon/func_8009612C v7.c --cfg "2.8.1-G0" --note "why"
    python3 <repo>/tools/lanes/lanekit/lab.py stage-cell dungeon/func_8009612C v7.c --cfg "2.7.2-cdk-G0" --note "why" --equal-pins
    python3 <repo>/tools/lanes/lanekit/lab.py dungeon/func_8009612C --base cand/best.c --subs s.json --score
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

BASE FILE.  `--base FILE` makes `--subs` / `--grid` start from FILE instead of the pin-erased text (round 80:
three lanes wrote `gen.py base.c subs.json outdir` to substitute on a candidate they had already
half-built).  `@name` / `"@base": "pinned"` still mean the pinned text; guards and the staging gate are
unchanged (admissible vs the lane's base/ copy), so a `--base` result stages exactly like any other.

STAGE-CELL.  `stage-cell <row> cand.c --cfg CFG --note "mechanism"` is `cellscore`'s hand-over done for
you: when `cand.c` scores exact at CFG (and is admissible vs base/) it is copied to
`out/<container>/<file>.c` with the base's `.base_sha` and one line
`{"id","to","coherence","pins_before","pins_after","rule2","kind"}` goes to `cells.jsonl` (what
`tools/fidelity/land_recipe_move.py` reads; a re-stage of the same id+cfg replaces its line).  The pinned base is
scored at CFG too: `kind` is `recipe-switch` when it is exact there (rule 2, byte-neutral), else `coherence`, and
`land_coherence.sh` records the trade under that kind (re-checking rule 2 at landing).  It
refuses, exit 1, when the candidate is not exact at CFG or not admissible.  Nothing else is written.
`--equal-pins` also stages a candidate whose pin count is UNCHANGED (round 81: lanes hand-staged three such
moves); the kind still follows rule 2, and a candidate identical to the pinned text (a pure recipe switch) is
handed to `tools/fidelity/land_recipe_move.py`, not `land_coherence.sh` (which would restore its recipe).

NO-BUILD.  A candidate that does not compile prints the first 20 lines of the preprocessor / cc1 stderr
under its `no-build` line and keeps them in its lab_log record (field `stderr`; round 93, `ccerr.py`'s job
built in).  The compile is the screen's own (the row's cell and flags, `-w`).

CAP.  More than 60 variants for one row needs `--more`.  One lane produced 209 probe files for two
of its five rows and left the other three nearly untouched.
"""
from __future__ import annotations

import argparse
import json
import os
import shutil
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402
import nojtbl                                                             # noqa: E402
import diff as listing_diff                                               # noqa: E402

JTBL_STATUSES = ("jtbl-mismatch",)
STDERR_LINES = 20          # a no-build candidate prints this many lines of preprocessor/cc1 stderr


def compile_stderr(row, text, lines=STDERR_LINES):
    """(first `lines` lines of stderr, was it cut) of compiling `text` with the row's cell, exactly as
    `screen.compile_s` does (what `ccerr.py` prints): cpp first, cc1 when cpp succeeds.  '' when nothing is
    said (e.g. the failure was a timeout or a toolchain wrapper error)."""
    import subprocess
    import tempfile
    kitlib.add_paths()
    import screen                                                         # noqa: E402
    from common import parse_cfg                                          # noqa: E402
    cell, flags = parse_cfg(row["cfg"])
    D = screen.ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="labcc_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        steps = [[str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(screen.INCLUDE), "-w", f.name, "-o", "f.i"],
                 [str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-o", "f.s"]]
        err = ""
        for cmd in steps:
            try:
                r = subprocess.run(cmd, cwd=d, capture_output=True, text=True, timeout=60)
            except Exception as e:                                        # noqa: BLE001  (a missing compiler, a timeout)
                return "(could not run %s: %s)" % (Path(cmd[0]).name, e), False
            err = r.stderr.strip()
            if r.returncode != 0:
                break
    ls = err.splitlines()
    return "\n".join(ls[:lines]), len(ls) > lines


def jtbl_note(sc):
    """Suffix for a printed score: the jump-table facts (`jtbl-mismatch` words, or the --no-jtbl caveat)."""
    sc = sc or {}
    if sc.get("status") == "jtbl-mismatch":
        return "  <- JUMP TABLE differs (%s); rerun with --no-jtbl for the listing" % nojtbl.jtbl_summary(sc.get("jtbl"))
    if sc.get("jtbl_checked") is False:
        return "  <- %s" % (nojtbl.EXACT_MSG if sc.get("text_exact") else "informational: jump table NOT checked")
    return ""


class Lab:
    """One row, ready to measure.  `Lab(row_id).test(name, text)` is the whole interface."""

    start = None          # `--base FILE` text for --subs/--grid (None: the pin-erased text)
    raw_only = False      # skip the default allocation-pin scorer view when explicitly requested

    def __init__(self, row_id, lane=None, stage=True, cfg=None, more=False, base_file=None, no_jtbl=False):
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
        self.no_jtbl = no_jtbl
        if no_jtbl and self.row.get("kind") == "slus":
            raise SystemExit("lab: --no-jtbl applies to overlay rows")
        self.more = more
        self.start = read_base_file(base_file)     # `--base FILE`: what --subs/--grid start from (None: erased text)
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

    def check_cap(self):
        have = self.count()
        if not getattr(self, "more", False) and have >= kitlib.VARIANT_CAP:
            raise SystemExit("lab: %s already has %d measured variants, the cap is %d.  "
                             "Pass --more or Lab(..., more=True) to continue."
                             % (self.id, have, kitlib.VARIANT_CAP))

    def guards(self, text):
        """The two regression guards worth keeping from the best lane harness."""
        bad = []
        if len(kitlib.sites(text)) > len(self.sites):
            bad.append("more pin sites than the base")
        if text.count("volatile") > self.base.count("volatile"):
            bad.append("adds volatile")
        return bad

    def score_text(self, text, scr=None):
        """One byte score of `text`: the real scorer (status `jtbl-mismatch` when only the switch table differs),
        or with `--no-jtbl` the informational score (`exact` False; `text_exact`, `jtbl_checked` False)."""
        if self.no_jtbl:
            return kitlib.score_at(self.xscreen.row if self.xscreen else self.row, text, no_jtbl=True)
        return nojtbl.jtbl_status(dict((scr or self.screen).exact(text)))

    def test(self, name, text, note="", score=False, stage=None):
        self.check_cap()
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
        allocation_score = None
        if d is not None and not self.raw_only and listing_diff.allocation_pins(self.base):
            allocation_score, norm_lines, norm_dist = listing_diff.allocation_view(scr.row, text)
            rec['normalised_distance'] = norm_dist
            rec['allocation_score'] = kitlib.score_fields(allocation_score)
            (self.dir / (name + '.norm.diff')).write_text('\n'.join(norm_lines or [
                'normalised listings identical' if norm_lines == [] else 'normalised listing unavailable']) + '\n')
            print('  --scorer --norm-regs: distance %s; raw byte score %s (display only)' %
                  (norm_dist, json.dumps(rec['allocation_score'])))
        if self.cfg:
            rec["cfg"] = self.cfg
        if d is None:                  # round 93: say WHY it does not build (cpp / cc1 stderr), in the log and on screen
            try:
                rec["stderr"], cut = compile_stderr(scr.row, text)
            except Exception as e:                                        # noqa: BLE001  (diagnostics must not stop a run)
                rec["stderr"], cut = "(stderr unavailable: %s)" % e, False
        # round 80: also byte-score near candidates - label ORDER (not numbering) can differ in a byte-identical
        # listing (r79_sonnet_g20 main/func_8000F524: dist 7, verify exact; the lane had to stage it by hand)
        near = int(os.environ.get("LANEKIT_SCORE_NEAR", "24"))
        if score and (dist == 0 or (dist is not None and dist <= near) or (self.cfg and d is not None)):
            v = allocation_score if allocation_score is not None and not self.no_jtbl else self.score_text(text, scr)
            rec["score"] = kitlib.score_fields(v)
            rec["status"] = "exact" if v.get("exact") else v["status"] if v.get("status") in JTBL_STATUSES else "scored"
            if self.no_jtbl:
                rec["status"] = "text-exact-nojtbl" if v.get("text_exact") else "scored-nojtbl"
                rec["note"] = (rec["note"] + " " if rec["note"] else "") + "[jump-table content check OFF]"
            if v.get("exact") and self.cfg:
                print("  exact at %s - NOT staged (registered cfg %s unchanged); hand over with "
                      "`lab.py cellscore %s %s --cfg %s`" % (self.cfg, self.row["cfg"], self.id, p, json.dumps(self.cfg)))
            elif v.get("exact") and (self.stage if stage is None else stage):
                rec["staged"] = self.publish(name, text)
        self.log(rec)
        print("%-28s dist %-5s pins %-3s %s%s"
              % (name, "-" if dist is None else dist, rec.get("pins", "-"),
                 (json.dumps(rec["score"]) + jtbl_note(rec["score"])) if rec["score"] else "",
                 "  -> " + rec["staged"] if rec.get("staged") else ""))
        if d is None:
            print("    does not build%s:" % (" (first %d stderr lines)" % STDERR_LINES if cut else ""))
            print("\n".join("      " + l for l in rec["stderr"].splitlines()) if rec["stderr"] else
                  "      (the compiler printed nothing; see %s)" % (self.dir / (name + ".diff")))
        return rec

    def test_file(self, path, score=False, note=""):
        path = Path(path)
        return self.test(path.stem, path.read_text(errors="replace"), note=note, score=score)

    def test_subs(self, name, reps, score=False, note=""):
        self.check_cap()
        base = start_text(name, self.base, self.erased, self.start)
        if self.start is not None and not name.startswith("@"):
            note = (note + " " if note else "") + "[--base file]"
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
            v = self.score_text(self.base)
            rec["score"] = kitlib.score_fields(v)
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
        return stage_file(self.lane, self.row, self.base_path, self.base, text)


def read_base_file(path):
    """The `--base FILE` text, or None when no file was named."""
    if not path:
        return None
    p = Path(path)
    if not p.is_file():
        raise SystemExit("lab: --base %s: no such file" % path)
    return p.read_text(errors="replace")


def start_text(name, pinned, erased, override=None):
    """The text a `--subs`/`--grid` variant starts from: `@name` -> the pinned text; else the `--base`
    file when given, else the pin-erased text."""
    if name.startswith("@"):
        return pinned
    return erased if override is None else override


def stage_file(lane, row, base_path, base, text, equal_pins=False):
    """Copy an exact, admissible candidate to `out/<container>/<file>.c` with its base sha.

    Returns the path relative to the lane, or None (after saying why).  `Lab.publish` and
    `stage-cell` share it (`equal_pins`: `stage-cell --equal-pins`, see `kitlib.admissible`)."""
    bad = kitlib.admissible(base, text, equal_pins=equal_pins)
    if bad:
        print("  NOT staged (%s)" % "; ".join(bad))
        return None
    out = Path(lane) / "out" / row["container"]
    out.mkdir(parents=True, exist_ok=True)
    dst = out / Path(row["c_path"]).name
    # round 80 (r79_sonnet_g45): never replace a staged candidate with a worse one - fewer pins first, then
    # fewer plain gotos; a later exact variant with more gotos overwrote a 0-goto candidate
    if dst.is_file():
        old = dst.read_text(errors="replace")
        key = lambda t: (len(kitlib.sites(t)), kitlib.goto_count(t))
        if key(text) > key(old):
            print("  NOT staged (the staged candidate is better: pins/gotos %s vs %s)" % (key(old), key(text)))
            return None
    dst.write_text(text)
    sha = base_path.with_name(base_path.name + ".base_sha")
    if sha.is_file():
        shutil.copyfile(sha, dst.with_name(dst.name + ".base_sha"))
    else:
        import hashlib
        dst.with_name(dst.name + ".base_sha").write_text(hashlib.sha256(base.encode()).hexdigest() + "\n")
    return str(dst.relative_to(lane))


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

def cellscore(row, cand, cfg, lane, name="candidate", base=None, verify=None, rule2=True, out=print, no_jtbl=False):
    """Byte-score `cand` as `row` at `cfg` WITHOUT touching the ledger; say what the hand-over is.

    Returns the record journalled (the caller appends it to `lab_log.jsonl`)."""
    if not cfg:
        raise SystemExit("lab: cellscore needs --cfg CFG")
    if cfg == row["cfg"]:
        raise SystemExit("lab: %s is the row's registered cfg - use `lab.py %s cand.c --score`" % (cfg, row["id"]))
    kitlib.row_at_cfg(row, cfg)  # reject per-row recipe trials for grouped SLUS members
    lane = Path(lane)
    v = kitlib.score_at(row, cand, cfg, verify=verify, no_jtbl=no_jtbl)
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
    if sc.get("status") == "jtbl-mismatch":
        rec["status"] = "jtbl-mismatch"
        out("  jtbl-mismatch at %s: %s (rerun with --no-jtbl to see the listing)" % (
            cfg, nojtbl.jtbl_summary(sc.get("jtbl"))))
    if no_jtbl:
        rec["status"] = "text-exact-nojtbl" if sc.get("text_exact") else "scored-nojtbl"
        out("  --no-jtbl: %s" % (nojtbl.EXACT_MSG if sc.get("text_exact") else "text NOT exact (jump table not checked)"))
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
            "HOLDS: byte-neutral switch; the trade's kind is recipe-switch, not coherence "
            "(`stage-cell` writes kind \"recipe-switch\" into cells.jsonl and land_coherence.sh records it)" if holds else
            "does NOT hold: a genuine coherence trade (charter clause 4b)"))
    cont, fn = row["container"], Path(row["c_path"]).name
    try:
        lane_name = str(lane.resolve().relative_to(kitlib.ROOT / "work/native_lane"))
    except ValueError:
        lane_name = "<lane under work/native_lane>"
    mech = "<mechanism: which pass / cell signature does what at %s>; %s" % (
        cfg, "rule 2 holds (pinned text also exact at target: byte-neutral)" if holds else
        "rule 2 does not hold (pinned text not exact at target)" if holds is False else "rule 2 not checked")
    line = json.dumps(dict({"id": row["id"], "to": cfg, "coherence": mech},
                           **({"rule2": holds, "kind": cell_kind(holds)} if holds is not None else {})))
    out("  EXACT at %s.  Hand-over for the orchestrator (the lane does not run these):" % cfg)
    out("    1. the candidate staged as out/%s/%s with its .base_sha (the pinned base's sha)" % (cont, fn))
    out("    2. this line in %s/cells.jsonl (fill in the mechanism):" % lane)
    out("       " + line)
    out("    3. LAND_ISOLATED=1 bash tools/lanes/land_coherence.sh <tag> %s" % lane_name)
    rec["cells_line"] = line
    return rec


# ---------------------------------------------------------------------------------- stage-cell

def cell_kind(rule2):
    """The trade kind of a recipe move: `recipe-switch` when rule 2 holds (the PINNED text is exact at the target
    too: byte-neutral), else `coherence` (charter clause 4b).  None (not checked) -> coherence."""
    return "recipe-switch" if rule2 else "coherence"


def cells_record(row_id, cfg, note, pins_before, pins_after, rule2=None):
    """The `cells.jsonl` line `tools/fidelity/land_recipe_move.py` reads (its docstring: `id`, `to`, `coherence`,
    `pins_before/after`; `rule2` is carried into the trade) and `tools/lanes/land_coherence.sh` stamps its trade
    `kind` from (r81_opus_kitgap: it always stamped "coherence", and the orchestrator hand-corrected rule-2 lines)."""
    rec = {"id": row_id, "to": cfg, "coherence": note, "pins_before": pins_before, "pins_after": pins_after}
    if rule2 is not None:
        rec.update(rule2=bool(rule2), kind=cell_kind(rule2))
    return rec


def cells_write(path, rec):
    """Append `rec` to `path`; an earlier line for the same id + cfg is replaced, not duplicated."""
    path = Path(path)
    keep = []
    if path.is_file():
        for line in path.read_text(errors="replace").splitlines():
            try:
                old = json.loads(line)
            except json.JSONDecodeError:
                old = None
            if line.strip() and not (old and old.get("id") == rec["id"] and old.get("to") == rec["to"]):
                keep.append(line)
    keep.append(json.dumps(rec))
    path.write_text("\n".join(keep) + "\n")
    return path


def stage_cell(row, cand, cfg, note, lane, base_path, base, name="candidate", verify=None, out=print, equal_pins=False):
    """Stage `cand` for a recipe move to `cfg`: score it there (`cellscore`, no ledger write), and when it is
    exact AND admissible vs `base`, copy it to `out/<container>/<file>.c` (+ `.base_sha`) and put the
    `cells_record` line in `<lane>/cells.jsonl`.  Returns the journal record; `rec["refused"]` says why not.

    `equal_pins=True` (`--equal-pins`) also stages a candidate with the SAME pin count as the base (the pins a
    subset of the base's, nothing banned added): the kind is still decided by rule 2 - `recipe-switch` when the
    pinned text is exact at `cfg` too, else `coherence` (r81_opus_fc4's 819C04E8: equal pins, rule 2 false).
    The candidate may be the pinned text itself (a pure recipe switch): `land_coherence.sh` would journal that
    as `noop` in apply_candidates and restore the recipe, so the hand-over names
    `tools/fidelity/land_recipe_move.py`, which lands an unchanged text as a pure switch."""
    if not note or not note.strip():
        raise SystemExit('lab: stage-cell needs --note "mechanism / coherence argument"')
    lane = Path(lane)
    # rule 2 is checked (the pinned base scored at `cfg` too) so the cells line carries the trade's kind
    rec = cellscore(row, cand, cfg, lane, name=name, base=base, verify=verify, rule2=True, out=lambda *a: None)
    rec["kind"] = "stage-cell"
    sc = rec["score"]
    if not sc.get("exact"):
        rec["refused"] = "not exact at %s (%s)" % (cfg, json.dumps(sc))
        out("stage-cell %s REFUSED: %s" % (row["id"], rec["refused"]))
        return rec
    bad = kitlib.admissible(base, cand, equal_pins=equal_pins)
    if bad:
        rec["refused"] = "not admissible vs base/: " + "; ".join(bad) + (
            "" if equal_pins or len(kitlib.sites(cand)) != len(kitlib.sites(base)) else
            "  (an exact-at-target move at EQUAL pins stages with --equal-pins)")
        out("stage-cell %s REFUSED: %s" % (row["id"], rec["refused"]))
        return rec
    staged = stage_file(lane, row, base_path, base, cand, equal_pins=equal_pins)
    if staged is None:
        rec["refused"] = "not staged (see the message above)"
        out("stage-cell %s REFUSED: %s" % (row["id"], rec["refused"]))
        return rec
    line = cells_record(row["id"], cfg, note.strip(), len(kitlib.sites(base)), len(kitlib.sites(cand)),
                        rule2=rec.get("rule2"))
    cells_write(lane / "cells.jsonl", line)
    pure = cand == base
    try:
        lane_name = str(lane.resolve().relative_to(kitlib.ROOT / "work/native_lane"))
    except ValueError:
        lane_name = "<lane under work/native_lane>"
    # an unchanged text is `noop` to apply_candidates, and land_coherence.sh then RESTORES the recipe it switched
    lander = ("python3 tools/fidelity/land_recipe_move.py <tag> work/native_lane/%s   (dry run; then --apply)" % lane_name
              if pure else "LAND_ISOLATED=1 bash tools/lanes/land_coherence.sh <tag> %s" % lane_name)
    rec.update(staged=staged, cells_line=json.dumps(line), lander=lander)
    if equal_pins:
        rec["equal_pins"] = True
    out("stage-cell %s  exact at %s (registered %s unchanged)%s" % (
        row["id"], cfg, row["cfg"], "  [equal pins %d -> %d]" % (line["pins_before"], line["pins_after"])
        if line["pins_before"] == line["pins_after"] else ""))
    out("  staged   : %s (+ .base_sha)%s" % (staged, "  = the pinned text: a PURE recipe switch" if pure else ""))
    out("  cells    : %s" % (lane / "cells.jsonl"))
    out("  " + json.dumps(line))
    out("  land     : " + lander)
    return rec


# ------------------------------------------------------------------------------------- report

VIA = {"cellscore": "lab cellscore", "stage-cell": "lab stage-cell", "diff-score": "diff.py --score",
       "diff-listing": "diff.py", "diff-scorer": "diff.py --scorer"}


def via(r):
    """Which tool took a journal record: its `source` tag (diff.py, `kitlib.record_score`), else its kind."""
    return r.get("source") or VIA.get(r.get("kind"), "lab.py")


def score_cell(s):
    """The report's score column: exact / total N, `jtbl-mismatch`, or an informational --no-jtbl score."""
    if s.get("status") == "jtbl-mismatch":
        return "jtbl-mismatch"
    if s.get("jtbl_checked") is False:
        return "text exact, jtbl NOT checked" if s.get("text_exact") else "total %s (jtbl NOT checked)" % s.get("total")
    return "exact" if s.get("exact") else "total %s" % s.get("total")


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
        body, seen = [], {}
        norm_active = any('normalised_distance' in r for r in real)
        for r in sorted(real, key=lambda r: (r.get("distance") is None, r.get("distance") or 0)):
            s = r.get("score") or {}
            at = " @" + r["cfg"] if r.get("cfg") else ""      # scored at ANOTHER cfg: not a solve here
            line = [r.get("variant"), r.get("status"), via(r),
                    "-" if r.get("distance") is None else r["distance"],
                    r.get("pins", "-"),
                    "" if not s else score_cell(s) + at,
                    (r.get("note") or r.get("why") or "")[:60]]
            if norm_active:
                line[4:4] = [r.get('normalised_distance', '-'), score_cell(r.get('allocation_score') or {})]
            key = json.dumps(line, default=str)
            if key in seen:                  # the same measurement repeated (a diff.py viewer run twice): one line
                seen[key][1] += 1
                continue
            seen[key] = [line, 1]
            body.append(line)
        for line, n in seen.values():
            if n > 1:
                line[-1] = ("%s (x%d)" % (line[-1], n)).strip()
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
        columns = ["variant", "status", "via", "dist", "pins", "score", "note"]
        if norm_active:
            columns[4:4] = ['norm dist', 'raw byte (view)']
        out.append(kitlib.fmt_table(columns, body))
        out.append("```")
        out.append("")
    return "\n".join(out)


# ---------------------------------------------------------------------------------------- CLI

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id", help="row id, or 'report', 'baseline', 'cellscore' or 'stage-cell'")
    ap.add_argument("rest", nargs="*", help="variant .c files (after 'baseline': row ids; after 'cellscore' / "
                                            "'stage-cell': row cand.c)")
    ap.add_argument("--base", help="--subs/--grid start from this file instead of the pin-erased text")
    ap.add_argument('--raw-only', action='store_true', help='skip the default allocation-pin scorer view')
    ap.add_argument("--subs", help="variants.json: {name: [[old,new],...]} on the pin-erased base; each pair replaces the FIRST occurrence, [old,new,\"all\"] every occurrence")
    ap.add_argument("--grid", help="grid.json: {axis: {label: [[old,new],...]}} -> every combination, named label+label")
    ap.add_argument("--cfg", help="compile/score at this cfg instead of the registered one (no ledger write, no staging)")
    ap.add_argument("--no-rule2", action="store_true", help="cellscore: skip scoring the pinned text at --cfg")
    ap.add_argument("--equal-pins", action="store_true",
                    help="stage-cell: also stage an exact-at-target candidate whose pin count is UNCHANGED "
                         "(kind by rule 2: recipe-switch or coherence; the pinned text itself = a pure switch)")
    ap.add_argument("--score", action="store_true", help="byte-score the listing-exact variants")
    ap.add_argument("--score-top", type=int, default=0, metavar="N",
                    help="also score the N nearest non-exact variants of this run")
    ap.add_argument("--note", default="", help="note recorded with every variant of this run "
                                               "(stage-cell: the coherence argument for cells.jsonl, required)")
    ap.add_argument("--more", action="store_true", help="allow more than %d variants for this row" % kitlib.VARIANT_CAP)
    ap.add_argument("--no-jtbl", action="store_true",
                    help="score with the switch jump-table CONTENT check OFF (informational: totals are marked, "
                         "nothing is exact or staged; a text-exact result prints 'text exact, jump table NOT checked'; "
                         "the real scorer still decides exactness). Overlay rows only.")
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
                        base=kitlib.base_text(row, lane), rule2=not a.no_rule2, no_jtbl=a.no_jtbl)
        kitlib.log_append(lane, rec)
        return

    if a.equal_pins and a.row_id != "stage-cell":
        raise SystemExit("lab: --equal-pins applies to stage-cell only")
    if a.row_id == "stage-cell":
        if a.no_jtbl:
            raise SystemExit("lab: --no-jtbl never stages: exactness is decided by the real scorer")
        if len(a.rest) != 2 or not a.cfg:
            raise SystemExit('lab.py stage-cell <row_id> <candidate.c> --cfg "CFG" --note "mechanism"')
        lane = kitlib.bootstrap()
        row = kitlib.row_of(a.rest[0])
        cp = Path(a.rest[1])
        if not cp.is_file():
            raise SystemExit("lab: stage-cell: no such file %s" % cp)
        rec = stage_cell(row, cp.read_text(errors="replace"), a.cfg, a.note, lane,
                         kitlib.base_path(row, lane), kitlib.base_text(row, lane), name=cp.stem,
                         equal_pins=a.equal_pins)
        kitlib.log_append(lane, rec)
        if rec.get("refused"):
            sys.exit(1)
        return

    lab = Lab(a.row_id, stage=not a.no_stage, cfg=a.cfg, more=a.more, base_file=a.base, no_jtbl=a.no_jtbl)
    lab.raw_only = a.raw_only
    if a.no_jtbl:
        print("--no-jtbl: the jump-table content check is OFF for every score below (informational; nothing is exact or staged)")
    if lab.start is not None:
        print("--subs/--grid start from %s (not the pin-erased text); @name still means the pinned text" % a.base)
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
        for msg in grid_misses(grid, lab.base if str(grid.get("@base")) == "pinned"
                               else lab.erased if lab.start is None else lab.start):
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
            v = lab.score_text(text, lab.xscreen or lab.screen)
            lab.log({"variant": r["variant"], "distance": r["distance"], "status": "scored-near",
                     **({"cfg": lab.cfg} if lab.cfg else {}),
                     "score": kitlib.score_fields(v)})
            print("%-28s dist %-5s scored total=%s exact=%s%s"
                  % (r["variant"], r["distance"], v.get("total"), v.get("exact"),
                     ("  [" + v["status"] + "]" if v.get("status") == "jtbl-mismatch" else "") + jtbl_note(v)))


if __name__ == "__main__":
    main()
