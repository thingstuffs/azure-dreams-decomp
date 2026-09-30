#!/usr/bin/env python3
"""diff.py - the unified cc1-listing diff of a candidate against the pinned (or erased, or any) text.

    python3 <KIT>/diff.py <row> <candidate.c|erased|pinned> [--vs pinned|erased|FILE] [--ctx N] [--score]
                          [--cfg CFG] [--scorer [--norm-regs]] [--no-jtbl] [--no-log]

26 lanes of round 73 wrote this same 10-line wrapper (`ldiff.py`, `lst.py`, `sd.py`, `dd.py`, ...)
around `screen.compile_s` + `difflib.unified_diff`.  `lab.py` already computes it for every variant
(`experiments/<func>/<name>.diff`); this prints it for one file, on demand.

`-` lines are the reference listing (`--vs`, default the PINNED text = retail's order on a byte-exact
row), `+` lines the candidate's.  The last line is the distance `lab.py` logs (changed listing lines).
`--score` also runs the byte scorer (`tools/verify.py`) whatever the distance (see JOURNAL below).

`--cfg CFG` compiles/scores as if the row were registered at CFG (both texts, this run only; nothing
under `ledger/` or `config/`; a `--score` record carries `cfg` and is not a solve).  `--scorer` prints
the BYTE scorer's diff instead of the cc1 listing: the generated | retail disassembly at the row's cfg
(or `--cfg`) - what `cdkdiff.py` / `sd.py` did in round 80.  `--norm-regs` renames the registers of
each side by first appearance and masks branch targets before diffing, so a pure register renaming
($s1<->$s2 all through a function) vanishes and only the real differences stay (`adiff.py`).

JOURNAL (round 81).  Every run appends one record to the lane's `lab_log.jsonl` (`kitlib.record_score` /
`log_append`), tagged `"source": "diff.py ..."`, so `lab.py report` shows what was measured here: a listing run
as kind `diff-listing` (its distance when `--vs pinned`), a `--scorer` run as kind `diff-scorer` WITH its byte
score (`kitlib.score_at(diff=True)` returns the score and the listing), `--score` as `diff-score`.  diff.py
records do not count toward lab.py's 60-variant cap.  `--no-log` writes nothing (a pure viewer).

JUMP TABLES (round 82).  The scorer rejects a text whose `switch` table differs from retail (`jtbl:` error) and
prints NO listing; `--scorer` now says so as the status `jtbl-mismatch` with the word index and the got/retail
values (never `build-fail/no-hex`).  `--no-jtbl` (implies `--scorer`) scores and prints the listing with the
table-content check OFF: the totals are informational, a text-exact result prints "text exact, jump table NOT
checked", and the real scorer's verdict on the same text is printed below it.  Exactness is decided by the real
scorer only (`tools/verify.py` and the gate are unchanged).

`--scorer --classify` prints, instead of the diff, every differing region of the scorer's listing with a
label and counts: ORDER (the same instruction, moved: identical text outside the LCS, paired nearest
first), COLOUR (equal once the allocatable registers v/a/t/s/fp are renamed: allocation), OPCODE (a
different instruction or constant: cse/combine/loop territory) and COUNT (an insertion or deletion) -
`retailmap.classify`, the r80_fable_n1 "which pass is the residue" answer for a foreign-cfg score.
"""
from __future__ import annotations

import argparse
import difflib
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402
import nojtbl                                                             # noqa: E402


def render(ref, cand, ctx=3, ref_name="pinned", cand_name="candidate"):
    """Unified diff lines of two normalised listings; [] when identical; None if either failed."""
    if ref is None or cand is None:
        return None
    return list(difflib.unified_diff(ref, cand, ref_name, cand_name, lineterm="", n=ctx))


def distance(lines):
    return None if lines is None else sum(
        1 for l in lines if l[:1] in "+-" and not l.startswith(("+++", "---")))


def text_of(arg, row, lane):
    """'pinned' / 'erased' / a path -> (name, text)."""
    if arg in ("pinned", "erased"):
        base = kitlib.base_text(row, lane)
        return arg, base if arg == "pinned" else kitlib.erased_text(base)
    p = Path(arg)
    if not p.is_file():
        raise SystemExit("diff.py: no such file %s (or say 'pinned' / 'erased')" % arg)
    return p.stem, p.read_text(errors="replace")


def run(row, ref_text, cand_text, ctx=3, ref_name="pinned", cand_name="candidate", listing=None):
    """(diff lines or None, distance).  `listing(row, text)` defaults to `variant_screen.row_listing`
    (`screen.compile_s`, with a slus module / partitioned row compiled in its module context)."""
    if listing is None:
        kitlib.add_paths()
        from variant_screen import row_listing as listing               # noqa: E402
    lines = render(listing(row, ref_text), listing(row, cand_text), ctx, ref_name, cand_name)
    return lines, distance(lines)


SCORER_LINE = re.compile(r"^\s*[!X~ ]?\s*\[\s*(\d+)\] (.*?)\s*\|\s*(.*?)(?:\s+raw .*)?$")
FIXED_REGS = {"zero", "at", "sp", "fp", "ra", "gp", "k0", "k1"}
# `$2`-style names (cc1 listings) and bare MIPS names (the scorer's objdump disassembly has no `$`)
REG_RE = re.compile(r"\$(\w+)|\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra)\b")
BRANCH_RE = re.compile(r"^(b\w*|j)\s")


def parse_scorer(text):
    """[(index, generated, retail)] from the byte scorer's `--diff` text (`[ idx] generated | retail`)."""
    out = []
    for line in (text or "").splitlines():
        m = SCORER_LINE.match(line.rstrip())
        if m:
            out.append((int(m.group(1)), m.group(2).strip(), m.group(3).strip()))
    return out


def canon_regs(lines):
    """Registers renamed `$r0, $r1, ...` by first appearance in `lines` (zero/at/sp/fp/ra/gp/k0/k1 stay)."""
    table = {}

    def sub(m):
        n = m.group(1) or m.group(2)
        return m.group(0) if n in FIXED_REGS else "$" + table.setdefault(n, "r%d" % len(table))
    return [REG_RE.sub(sub, l) for l in lines]


def mask_branch(line):
    """Branch/jump absolute targets are layout, not code: `b 0x8001f0` -> `b TGT` (`jal` targets stay)."""
    return re.sub(r"0x[0-9a-f]+$", "TGT", line) if BRANCH_RE.match(line) else line


def scorer_diff(text, ctx=3, norm_regs=False):
    """Diff lines (`-` retail, `+` generated) of the byte scorer's text; None when it has no
    `[idx] generated | retail` lines (a MATCH message, a SLUS region dump, a scorer error)."""
    rows = parse_scorer(text)
    if not rows:
        return None
    got, tgt = [r[1] for r in rows], [r[2] for r in rows]
    if norm_regs:
        got, tgt = canon_regs([mask_branch(l) for l in got]), canon_regs([mask_branch(l) for l in tgt])
    return list(difflib.unified_diff(tgt, got, "retail", "generated", lineterm="", n=ctx))


def _span(xs):
    return "-" if not xs else "[%d]" % xs[0] if len(xs) == 1 else "[%d..%d]" % (xs[0], xs[-1])


def classify_lines(text, cfg, name="candidate"):
    """The `--classify` printout of one scorer text (pure: the tests feed it a fixture)."""
    import retailmap as RM                                               # noqa: E402
    rows = RM.scorer_rows(text)
    if not rows:
        return ["# %s at %s: the scorer printed no listing (exact, or no disassembly) - nothing to classify"
                % (name, cfg)] + [l for l in (text or "").splitlines() if l.startswith(("MATCH", "NO MATCH"))][:1]
    regions, tot = RM.classify(rows)
    out = ["# residue of %s at %s: %s   (%d regions)" % (
        name, cfg, ", ".join("%s %d" % (k, v) for k, v in tot.items()), len(regions))]
    for r in regions:
        out.append("")
        out.append("region %d  gen %s  retail %s  %s  (%s)" % (
            r["region"], _span(r["gen"]), _span(r["ret"]), r["label"],
            ", ".join("%s %d" % (k, v) for k, v in r["counts"].items() if v)))
        for x in r["items"]:
            g = "-" if x["gen"] is None else "[%d]" % x["gen"]
            t = "-" if x["ret"] is None else "[%d]" % x["ret"]
            txt = x["got"] if x["kind"] == "ORDER" else "%s | %s" % (x["got"] or "", x["tgt"] or "")
            out.append("   %-7s gen %-6s retail %-6s %s" % (x["kind"], g, t, txt))
    return out


def jtbl_lines(v, no_jtbl=False, real=None):
    """The `# ...` lines that say what happened to the jump table (empty for an ordinary score).

    `v` is a `kitlib.score_at(diff=True)` result; `real` (with `no_jtbl`) the real scorer's result on the same text."""
    out = []
    if v.get("status") == "jtbl-mismatch":
        out.append("# JTBL-MISMATCH: the scorer rejected the text for its switch jump table (%s); no listing "
                   "exists at the real scorer - rerun with --no-jtbl to diff the code" % nojtbl.jtbl_summary(v.get("jtbl"), v.get("err")))
    if no_jtbl:
        if v.get("text_exact"):
            out.append("# " + nojtbl.EXACT_MSG)
        else:
            out.append("# jump-table content check OFF: totals are informational (exactness is the real scorer's call)")
        if real is not None:
            if real.get("status") == "jtbl-mismatch":
                out.append("# real scorer on this text: jtbl-mismatch (%s)" % nojtbl.jtbl_summary(real.get("jtbl"), real.get("err")))
            else:
                out.append("# real scorer on this text: %s" % json.dumps(kitlib.score_fields(real)))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("candidate", help="candidate .c, or 'erased' / 'pinned'")
    ap.add_argument("--vs", default="pinned", help="reference: pinned (default), erased, or a .c file")
    ap.add_argument("--ctx", type=int, default=3, help="context lines (default 3)")
    ap.add_argument("--score", action="store_true", help="also byte-score the candidate (journalled)")
    ap.add_argument("--cfg", help="compile/score as if the row were registered at this cfg (no ledger write)")
    ap.add_argument("--scorer", action="store_true",
                    help="print the byte scorer's retail-vs-generated disassembly diff (at --cfg) instead of the listing")
    ap.add_argument("--norm-regs", action="store_true",
                    help="--scorer: rename registers by first appearance + mask branch targets (pure renaming vanishes)")
    ap.add_argument("--classify", action="store_true",
                    help="--scorer: label each differing region ORDER / COLOUR / OPCODE / COUNT, with counts")
    ap.add_argument("--no-jtbl", action="store_true",
                    help="implies --scorer: score/print with the switch jump-table CONTENT check off (informational; "
                         "a text-exact result prints 'text exact, jump table NOT checked'; the real scorer decides exactness)")
    ap.add_argument("--no-log", action="store_true", help="write nothing to lab_log.jsonl (a pure viewer)")
    a = ap.parse_args(argv)
    if a.no_jtbl:
        a.scorer = True
    if a.norm_regs and not a.scorer:
        raise SystemExit("diff.py: --norm-regs applies to --scorer")
    if a.classify and not a.scorer:
        raise SystemExit("diff.py: --classify applies to --scorer")

    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    if a.cfg:
        row = kitlib.row_at_cfg(row, a.cfg)
    ref_name, ref = text_of(a.vs, row, lane)
    cand_name, cand = text_of(a.candidate, row, lane)
    pins = len(kitlib.sites(cand))
    v = None

    def journal(kind, source, v=None, dist=None, note=""):
        if a.no_log:
            return
        if v is None:
            kitlib.log_append(lane, dict({"row": row["id"], "variant": cand_name, "kind": kind, "source": source,
                                          "distance": dist, "score": None, "pins": pins,
                                          "status": "no-build" if dist is None and lines is None else "measured",
                                          "note": note}, **({"cfg": a.cfg} if a.cfg else {})))
        else:
            kitlib.record_score(lane, row, cand_name, v, source, cfg=a.cfg, distance=dist, pins=pins,
                                note=note, kind=kind)

    real = None
    if a.scorer and a.classify:
        v = kitlib.score_at(row, cand, diff=True, no_jtbl=a.no_jtbl)
        real = kitlib.score_at(row, cand) if a.no_jtbl else None
        print("\n".join(classify_lines(v.get("text"), row["cfg"], cand_name)))
        print("# score %s" % json.dumps(kitlib.score_fields(v)))
        for l in jtbl_lines(v, a.no_jtbl, real):
            print(l)
        journal("diff-scorer", "diff.py --scorer --classify" + (" --no-jtbl" if a.no_jtbl else ""), v)
        if not a.score:
            return
        lines, dist = [], None
    elif a.scorer:
        v = kitlib.score_at(row, cand, diff=True, no_jtbl=a.no_jtbl)
        real = kitlib.score_at(row, cand, cfg=None) if a.no_jtbl else None
        lines = scorer_diff(v.get("text"), a.ctx, a.norm_regs)
        print("# byte scorer at %s: - retail, + generated%s"
              % (row["cfg"], "  (registers/targets normalised)" if a.norm_regs else ""))
        if lines is None and v.get("status") == "jtbl-mismatch":
            print("(no listing: the scorer rejected the text for its jump table - see the JTBL-MISMATCH line below)")
        elif lines is None:
            print((v.get("text") or "").rstrip() or "(no scorer text: status %s)" % v.get("status"))
        else:
            print("\n".join(lines) if lines else "(scorer listings identical)")
        print("# score %s" % json.dumps(kitlib.score_fields(v)))
        for l in jtbl_lines(v, a.no_jtbl, real):
            print(l)
        journal("diff-scorer", "diff.py --scorer" + (" --norm-regs" if a.norm_regs else "") + (" --no-jtbl" if a.no_jtbl else ""), v)
        if not a.score:
            return
        lines, dist = [], None
    else:
        lines, dist = run(row, ref, cand, a.ctx, ref_name, cand_name)
        if not a.score:
            journal("diff-listing", "diff.py", dist=dist if ref_name == "pinned" else None,
                    note="" if ref_name == "pinned" or dist is None else "dist %s vs %s" % (dist, ref_name))
    if a.scorer:
        pass
    elif lines is None:
        print("DOES NOT BUILD (%s)" % ("the reference" if kitlib.screen_for(row, ref).target is None
                                       else "the candidate"))
    else:
        for l in lines:
            print(l)
        if not lines:
            print("(listings identical)")
    if not a.scorer:
        print("%-28s dist %-5s pins %-3s vs %s   [%s]"
              % (cand_name, "-" if dist is None else dist, len(kitlib.sites(cand)), ref_name, row["cfg"]))
    if a.score:
        if v is None:                    # a --scorer run already holds the score: journalled above, not twice
            v = kitlib.score_at(row, cand)
            journal("diff-score", "diff.py --score", v, dist=dist if ref_name == "pinned" else None,
                    note="diff.py --score" + ("" if ref_name == "pinned" else " (dist vs %s)" % ref_name))
        sc = kitlib.score_fields(v)
        print("%-28s score %s%s" % (cand_name, json.dumps(sc), "  @" + a.cfg if a.cfg else ""))


if __name__ == "__main__":
    main()
