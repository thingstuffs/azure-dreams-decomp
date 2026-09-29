#!/usr/bin/env python3
"""why.py - what the compiler DECIDED, and what changed its mind.  The tool the lanes asked for.

Thirteen of sixteen mined astra lanes and most sol duck lanes end at the same sentence: "what is
needed next is the allocno/lifetime/dependence evidence for this pass", and then guess another C
shape instead, because no tool below the cc1 listing existed.  Two lanes traced a `combine.c` /
`sched.c` mechanism by hand-reading `-da` dumps and ran out of levers.  Zero of nine sol duck lanes
ever ran `sched_trace.py` or `reg_state.py`.  This is that missing level.

    cd work/native_lane/<lane>
    python3 <repo>/tools/lanes/lanekit/why.py <row> --pass sched
    python3 <repo>/tools/lanes/lanekit/why.py <row> --pass greg --around target_x
    python3 <repo>/tools/lanes/lanekit/why.py <row> --pass loop
    python3 <repo>/tools/lanes/lanekit/why.py <row> --pass combine --variant experiments/f/v7.c --vs pinned
    python3 <repo>/tools/lanes/lanekit/why.py <row> --pass greg --variant cand.c --cfg "2.7.2-cdk-G0"

It compiles TWO texts with `-da` (one compile each, every pass from it) and prints the decisions
that differ:

  sched, sched2  per basic block: each insn's priority and ref_count, the scheduler's ready lists,
                 the SOURCE order (LUID order, what the C wrote) and the EMITTED order, and the
                 dependence links of the insns that moved.  gcc 2.x `sched.c` fills a block from the
                 end, priority = longest dependence path, ties broken by `INSN_LUID` = original
                 order - so an order change with equal priorities is a TIE broken by the C's
                 statement order, and an order change with different priorities is a dependence
                 change.  The printout says which.
  greg           the allocno table: pseudo -> variable name, n_refs, live_length, calls crossed,
                 `global.c allocno_compare` priority, the allocno ORDER, and the hard register each
                 one got.  A `register x ASM_REG("$19")` pin is a MISSING allocno: erase it and
                 every lower-priority allocno slides one register down the callee-saved sequence.
                 Allocnos present in one text and not the other are printed first, under `MISSING
                 ALLOCNO`, because that is usually the whole answer.
  lreg           the same flow state as local allocation sees it: refs / live length / calls per
                 named pseudo, and which ones changed.
  loop           each loop's real insn count and every movable's verdict (`moved` / `not desirable`
                 / `not safe`), plus the biv/giv/unrolling diagnostics, aligned by position - the
                 `loop.c:1631` `threshold * savings * lifetime >= insn_count` decision that one lane
                 used to take a row from 37 pins to 2.
  cse, cse2, combine, flow, jump, jump2, rtl, dbr
                 a filtered insn-pattern diff of that pass's dump, pseudos anonymised (their numbers
                 shift when a pin is erased, so raw UIDs and regnos never align) - and `--around`
                 narrows it to the insns that mention one variable, pseudo or hard register.

`--around` accepts a C variable name (resolved to its pseudo through `alloc_sim.decl_pseudos`), a
hard register (`$19`, `a0`, `s3`), a bare pseudo number, `L<n>` for a source line (its identifiers
are used), or any substring of an RTL pattern.  Mapping an ASSEMBLY line back to RTL is not
supported: name the register or the variable instead.

`--cfg CFG` compiles BOTH texts as if the row were registered at CFG (an in-memory row override,
`kitlib.row_at_cfg`; nothing under `ledger/` is written) - `--vs pinned --variant cand.c --cfg X` is
"what does the cell do to my candidate", the WHY_CFG wrapper two round-80 lanes wrote.

Texts: `--vs` is the reference (default `pinned`, the row's own text) and `--variant` the subject
(default `erased`, every pin erased).  Either may be a path to a candidate `.c`.

ONE text (`--variant`), one `-dap` compile (round 80, the r80_fable_n1 harvest):

    why.py <row> --pass sched2 --block <N|bN|uN|rN> --trace [--variant F] [--cfg X] [--retail] [--insn N]
    why.py <row> --deps <uid> [--pass sched2] [--variant F] [--cfg X]

`--trace` prints one block's priority/ref_count table in emitted order and, tick by tick, the ready list
with dynamic priorities and WHY the pick won (sole / priority [launched, tail] / hazard / LUID tie /
class/stale-sort / tie / stall); `--insn N` only that insn's history (ready when, lost to whom and why,
picked when); `--retail` byte-scores the text and adds uid -> generated word -> retail word.  `--block N` is
a uid when a block holds it, else a block number; `bN` block, `uN` uid, `rN` retail word.  `--deps` prints
an insn's LOG_LINKS with their kind and the insns that depend on it.
"""
from __future__ import annotations

import argparse
import collections
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402

PASSES = ("rtl", "jump", "cse", "loop", "cse2", "flow", "combine", "sched",
          "lreg", "greg", "sched2", "jump2", "dbr")

PSEUDO_RE = re.compile(r"\(reg(/\w+)*:(\w+) (\d+)\)")       # `(reg:SI 80)` - no hard-register name
HARD_RE = re.compile(r"\(reg(?:/\w+)*:(\w+) (\d+) (\$?\w+)\)")
BLOCK_RE = re.compile(r"^;;\s+-- basic block number (\d+) from (\d+) to (\d+) --", re.M)
PRIO_RE = re.compile(r"^;; insn\[\s*(\d+)\]: priority =\s*(-?\d+), ref_count =\s*(-?\d+)", re.M)
READY_RE = re.compile(r"^;; ready list at T-(\d+): (.*)$", re.M)
TOTAL_RE = re.compile(r"^;; total time = (\d+)", re.M)


# ------------------------------------------------------------------------------ pattern helpers

def anon(pat, table):
    """Pattern with pseudo numbers renamed by first appearance (hard registers keep their names)."""
    def sub(m):
        return "(reg:%s %s)" % (m.group(2), table.setdefault(m.group(3), "p%d" % len(table)))
    return PSEUDO_RE.sub(sub, pat)


def insns_of(dump, modes=False):
    """[{uid, kind, pattern, links, anon}] for a `-da` dump, in the order the dump prints them.
    `modes=True` also reads reload's `(insn:HI N ...)` (the --trace/--deps/checks paths use it)."""
    kitlib.add_paths()
    from sched_trace import instructions                                 # noqa: E402
    table = {}
    out = []
    for rec in instructions(dump, modes=modes):
        rec = dict(rec)
        rec["anon"] = anon(rec["pattern"], table)
        out.append(rec)
    return out


def short(pat, width=96):
    s = re.sub(r"\s+", " ", pat).strip()
    return s if len(s) <= width else s[:width - 1] + "…"


class Around:
    """A filter over raw RTL patterns, built from one `--around` token."""

    def __init__(self, token, row, text, first_pseudo):
        self.token = token
        self.tests = []
        if not token:
            return
        kitlib.add_paths()
        import alloc_sim                                                 # noqa: E402
        dp = alloc_sim.decl_pseudos(text, first_pseudo) if first_pseudo else None
        mapping = (dp or {}).get("map", {})
        names = [token]
        m = re.fullmatch(r"[Ll](\d+)", token)
        if m:
            lines = text.splitlines()
            i = int(m.group(1)) - 1
            code = lines[i].split("/*")[0].split("//")[0] if 0 <= i < len(lines) else ""
            # only the identifiers that are really variables of this function: a pin's trailing
            # note is English prose and every word of it would otherwise become a substring filter
            names = [n for n in re.findall(r"[A-Za-z_]\w*", code) if n in mapping]
            if not names:
                raise SystemExit("why: source line %s names no variable of this function (%s)"
                                 % (token, code.strip()[:60] or "empty line"))
        self.explain = []
        for n in names:
            if n in mapping:
                p = mapping[n]
                self.tests.append(re.compile(r"\(reg(?:/\w+)*:\w+ %d\)" % p))
                self.explain.append("%s = pseudo %d" % (n, p))
            elif n.isdigit():
                self.tests.append(re.compile(r"\(reg(?:/\w+)*:\w+ %s\)" % n))
                self.explain.append("pseudo %s" % n)
            elif re.fullmatch(r"\$\w+|[astvk][0-9]|gp|ra|fp|sp|zero", n):
                self.tests.append(re.compile(r"\(reg(?:/\w+)*:\w+ \d+ \$?%s\)" % re.escape(n.lstrip("$"))))
                self.explain.append("hard register %s" % n)
            else:
                self.tests.append(re.compile(re.escape(n)))
                self.explain.append("substring %r" % n)

    def __bool__(self):
        return bool(self.tests)

    def hit(self, pat):
        return any(t.search(pat) for t in self.tests)


# ------------------------------------------------------------------------------------- sched

def sched_blocks(dump):
    """[{n, prio, ready, total, uids}] from the scheduler's own commentary, in block order."""
    head = dump[:dump.find("\n(")] if "\n(" in dump else dump
    marks = list(BLOCK_RE.finditer(head))
    out = []
    for i, m in enumerate(marks):
        seg = head[m.end():marks[i + 1].start() if i + 1 < len(marks) else len(head)]
        prio = {int(a): (int(b), int(c)) for a, b, c in PRIO_RE.findall(seg)}
        ready = [(int(t), body.strip()) for t, body in READY_RE.findall(seg)]
        tot = TOTAL_RE.search(seg)
        out.append({"n": int(m.group(1)), "from": int(m.group(2)), "to": int(m.group(3)),
                    "prio": prio, "ready": ready, "total": int(tot.group(1)) if tot else None})
    return out


PRE_PASS = {"sched": "combine", "sched2": "greg"}      # the pass whose chain order sets INSN_LUID


def pre_order(d, phase, modes=False):
    """{uid: position} from the dump of the pass BEFORE this scheduler runs.

    `sched.c` assigns INSN_LUID by walking the insn chain at pass entry, and that chain order is
    NOT UID order: `combine` creates insns with high UIDs and splices them where the combined insn
    was.  Reading the previous pass's dump is exact (UIDs are stable within one compile) and free,
    because that dump came out of the same `-da` compile."""
    src = d.get(PRE_PASS.get(phase, ""))
    if not src:
        return None
    return {x["uid"]: i for i, x in enumerate(insns_of(src, modes))}


def explain_sched(a, b, names, around, phase, top):
    out = []
    ba, bb = sched_blocks(a[phase]), sched_blocks(b[phase])
    if not ba and not bb:
        out.append("The `%s` dump carries no `;; insn[N]: priority` commentary - this cell's "
                   "scheduler is not the gcc 2.7/2.8 one (2.91.66 and 2.95.2 use haifa-sched.c, "
                   "which prints `;; Ready list (t = N)`).  Falling back to the filtered RTL diff "
                   "of the same pass." % phase)
        return out + explain_diff(a, b, names, around, phase, top, 2)
    pa_rank, pb_rank = pre_order(a, phase), pre_order(b, phase)
    ia = {x["uid"]: x for x in insns_of(a[phase])}
    ib = {x["uid"]: x for x in insns_of(b[phase])}
    oa = [x["uid"] for x in insns_of(a[phase])]
    ob = [x["uid"] for x in insns_of(b[phase])]
    if pa_rank is None or pb_rank is None:
        out.append("NOTE: no `.%s` dump, so the `src` column below is UID order, which is only "
                   "approximately the chain order INSN_LUID follows.  Read the tie rule with care."
                   % PRE_PASS.get(phase, "?"))
    if len(ba) != len(bb):
        out.append("Block count differs: %s %d blocks, %s %d blocks - the control flow changed, so "
                   "the scheduler is not the first difference. Look at `--pass jump` or `--pass flow`."
                   % (names[0], len(ba), names[1], len(bb)))
    shown = 0
    for ka, kb in zip(ba, bb):
        ua = [u for u in oa if u in ka["prio"]]
        ub = [u for u in ob if u in kb["prio"]]
        pa = [ia[u]["anon"] for u in ua if u in ia]
        pb = [ib[u]["anon"] for u in ub if u in ib]
        if pa == pb:
            continue
        if around and not any(around.hit(ia[u]["pattern"]) for u in ua if u in ia) \
                and not any(around.hit(ib[u]["pattern"]) for u in ub if u in ib):
            continue
        shown += 1
        if shown > top:
            out.append("... (%d more blocks differ; raise --top)" % (len(ba) - shown + 1))
            break
        out.append("")
        out.append("=== basic block %d   (%s: %d insns, %d ticks | %s: %d insns, %d ticks)"
                   % (ka["n"], names[0], len(ua), ka["total"] or 0, names[1], len(ub), kb["total"] or 0))
        for label, blk, order, imap, rank in ((names[0], ka, ua, ia, pa_rank),
                                              (names[1], kb, ub, ib, pb_rank)):
            # LUID order = the insn chain as the previous pass left it, NOT UID order
            src = sorted(order, key=lambda u: rank.get(u, 10 ** 9 + u)) if rank else sorted(order)
            body = []
            for pos, u in enumerate(order):
                pr, rc = blk["prio"].get(u, (None, None))
                rec = imap.get(u)
                links = (rec or {}).get("links", [])
                deps = ",".join("%d%s" % (k, "" if t == "true" else "(%s)" % t.replace("REG_DEP_", ""))
                                for k, t in links[:6]) or "-"
                if len(links) > 6:
                    deps += ",+%d" % (len(links) - 6)
                body.append([pos, u, src.index(u), pr, rc, deps,
                             short((rec or {}).get("anon", "?"), 58)])
            out.append("")
            out.append("-- %s" % label)
            out.append(kitlib.fmt_table(["emit", "uid", "src", "prio", "refs", "deps on", "insn"], body))
            if blk["ready"]:
                out.append("   ready lists: " + " | ".join("T-%d: %s" % (t, s) for t, s in blk["ready"][:6]))
        out.append("")
        out.append("   READ IT LIKE THIS: `emit` is the order the block came out, `src` the order the C "
                   "wrote it (INSN_LUID).")
        out.append("   Equal `prio` with a different `emit`/`src` relationship = a TIE broken by "
                   "statement order: move the statement in the C.")
        out.append("   Different `prio` = a different longest dependence path: the `deps on` column "
                   "says which edge appeared or vanished.")
    if not shown:
        out.append("No basic block's emitted insn sequence differs at `%s`%s. The two texts schedule "
                   "identically here; the difference is in another pass." % (phase, " (under --around)" if around else ""))
    return out


# --------------------------------------------------------------------------------- allocation

def alloc_read(d, row, text):
    """alloc_sim's reading, built from dumps already in hand (no second compile)."""
    kitlib.add_paths()
    import alloc_sim                                                     # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    cell, _ = parse_cfg(row["cfg"])
    fp = alloc_sim.FIRST.get(cell)
    if fp is None:
        return "no-first-pseudo:%s" % cell
    if "greg" not in d or "lreg" not in d:
        return "no-dump"
    order, disp = alloc_sim.parse_greg(d["greg"])
    stats = alloc_sim.parse_lreg(d["lreg"])
    conf, pref = alloc_sim.parse_conflicts(d["greg"], fp)
    dp = alloc_sim.decl_pseudos(text, fp)
    names = {v: k for k, v in ((dp or {}).get("map") or {}).items()}
    return {"order": order, "disp": disp, "stats": stats, "conf": conf, "pref": pref,
            "first": fp, "names": names, "sim": alloc_sim, "lreg": d["lreg"]}


def alloc_excuse(code, row):
    """Say WHICH of the two allocation prerequisites is missing - they have different fixes."""
    if code.startswith("no-first-pseudo"):
        cell = code.split(":", 1)[1]
        return ("why: the dumps are there, but `alloc_sim.FIRST` has no FIRST_PSEUDO_REGISTER for "
                "cell %s (known: %s). The allocno numbering cannot be read without it - add the "
                "cell to tools/alloc_sim.py (FIRST_PSEUDO_REGISTER), or read the allocation as a stream "
                "with `--pass greg` disabled and `--pass flow`/`--pass combine` instead. "
                "19 of the ~1,117 pinned rows sit on such a cell." % (cell, "2.6.3, "
                "2.7.2, 2.7.2-cdk, 2.8.0, 2.8.1"))
    return ("why: this recipe produced no .greg/.lreg dump (%s) - the allocation passes did not "
            "run or the dump was not written." % row["cfg"])


def alloc_rows(rd, around):
    body, by_name = [], {}
    for rank, p in enumerate(rd["order"]):
        st = rd["stats"].get(p, {})
        nm = rd["names"].get(p, "")
        pr = rd["sim"].priority(st.get("n_refs", 0), st.get("live_length", -1))
        hard = rd["disp"].get(p)
        rec = [rank, p, nm, st.get("n_refs"), st.get("live_length"), st.get("calls_crossed"), pr,
               rd["sim"].reg_name(hard) if hard is not None and hard >= 0 else "spilled"]
        if around and not around.hit("(reg:SI %d)" % p) and (not nm or not around.hit(nm)):
            continue
        body.append(rec)
        if nm:
            by_name[nm] = rec
    return body, by_name


def explain_greg(a, b, names, around, row, texts, top):
    ra, rb = alloc_read(a, row, texts[0]), alloc_read(b, row, texts[1])
    out = []
    bad = next((x for x in (ra, rb) if isinstance(x, str)), None)
    if bad:
        return [alloc_excuse(bad, row)]
    ba, na = alloc_rows(ra, around)
    bb, nb = alloc_rows(rb, around)
    out.append("allocnos: %s %d, %s %d   (`;; N regs to allocate` after global.c's qsort)"
               % (names[0], len(ra["order"]), names[1], len(rb["order"])))
    only_a = [n for n in na if n not in nb]
    only_b = [n for n in nb if n not in na]
    # unnamed allocnos (compiler temporaries, and anything decl_pseudos cannot name) are matched by
    # pseudo NUMBER, which is stable for the temporaries later passes create; without this an added
    # or removed temporary - which is exactly what a pin can be - would be invisible here
    def unnamed(body):
        return {r[1]: r for r in body if not r[2]}
    ua, ub = unnamed(ba), unnamed(bb)
    extra_a = {k: v for k, v in ua.items() if k not in ub}
    extra_b = {k: v for k, v in ub.items() if k not in ua}
    if only_a or only_b or extra_a or extra_b:
        out.append("")
        out.append("MISSING ALLOCNO - the usual whole answer on a register row:")
        for n in only_a:
            out.append("  only in %s: %s (pseudo %s, %s)" % (names[0], n, na[n][1], na[n][7]))
        for n in only_b:
            out.append("  only in %s: %s (pseudo %s, %s)" % (names[1], n, nb[n][1], nb[n][7]))
        for label, extra in ((names[0], extra_a), (names[1], extra_b)):
            for pseudo, rec in sorted(extra.items())[:6]:
                out.append("  only in %s: unnamed allocno pseudo %s (rank %s, refs/live/calls "
                           "%s/%s/%s, %s) - a compiler temporary, matched by pseudo number"
                           % (label, pseudo, rec[0], rec[3], rec[4], rec[5], rec[7]))
        out.append("  Every allocno of lower priority slides one register down the callee-saved "
                   "sequence ($s0,$s1,... in allocno order): that is the recolouring you see.")
    head = ["rank", "pseudo", "variable", "refs", "live", "calls", "priority", "got"]
    for label, body in ((names[0], ba), (names[1], bb)):
        out.append("")
        out.append("-- %s" % label)
        out.append(kitlib.fmt_table(head, body[:top]))
        if len(body) > top:
            out.append("   ... %d more (raise --top or use --around)" % (len(body) - top))
    moved = [(n, na[n], nb[n]) for n in na if n in nb and (na[n][0] != nb[n][0] or na[n][7] != nb[n][7])]
    if moved:
        out.append("")
        out.append("changed:")
        out.append(kitlib.fmt_table(
            ["variable", "rank %s" % names[0], "rank %s" % names[1], "got %s" % names[0], "got %s" % names[1],
             "refs/live/calls %s" % names[0], "refs/live/calls %s" % names[1]],
            [[n, x[0], y[0], x[7], y[7], "%s/%s/%s" % tuple(x[3:6]), "%s/%s/%s" % tuple(y[3:6])]
             for n, x, y in moved][:top]))
    for label, rd in ((names[0], ra), (names[1], rb)):
        sim = rd["sim"].simulate({"order": rd["order"], "stats": rd["stats"], "conf": rd["conf"],
                                  "pref": rd["pref"], "first": rd["first"]})
        agree = sum(1 for p in rd["order"] if sim.get(p) == rd["disp"].get(p))
        out.append("   alloc_sim model agrees with the real dispositions on %d of %d allocnos in %s%s"
                   % (agree, len(rd["order"]), label,
                      " - trust the `got` column (the dump), not the model, where they disagree"
                      if agree < len(rd["order"]) else ""))
    return out


def explain_lreg(a, b, names, around, row, texts, top):
    ra, rb = alloc_read(a, row, texts[0]), alloc_read(b, row, texts[1])
    bad = next((x for x in (ra, rb) if isinstance(x, str)), None)
    if bad:
        return [alloc_excuse(bad, row)]
    out = ["local allocation's view: refs / live length / calls crossed per pseudo, by variable name."]
    keys = sorted(set(ra["names"].values()) | set(rb["names"].values()))
    inv_a = {v: k for k, v in ra["names"].items()}
    inv_b = {v: k for k, v in rb["names"].items()}
    body = []
    for n in keys:
        if around and not around.hit(n) and not (
                inv_a.get(n) and around.hit("(reg:SI %d)" % inv_a[n])):
            continue
        sa = ra["stats"].get(inv_a.get(n, -1), {})
        sb = rb["stats"].get(inv_b.get(n, -1), {})
        if not sa and not sb:
            continue
        flag = "" if (sa.get("n_refs"), sa.get("live_length"), sa.get("calls_crossed")) == \
                     (sb.get("n_refs"), sb.get("live_length"), sb.get("calls_crossed")) else "<-- changed"
        body.append([n, inv_a.get(n, "-"), "%s/%s/%s" % (sa.get("n_refs"), sa.get("live_length"), sa.get("calls_crossed")),
                     inv_b.get(n, "-"), "%s/%s/%s" % (sb.get("n_refs"), sb.get("live_length"), sb.get("calls_crossed")), flag])
    out.append("")
    out.append(kitlib.fmt_table(["variable", "pseudo " + names[0], names[0], "pseudo " + names[1], names[1], ""], body[:top]))
    va = tuple(sorted((ra["stats"].get(p, {}).get("n_refs"), ra["stats"].get(p, {}).get("live_length"),
                       ra["stats"].get(p, {}).get("calls_crossed")) for p in ra["order"]))
    vb = tuple(sorted((rb["stats"].get(p, {}).get("n_refs"), rb["stats"].get(p, {}).get("live_length"),
                       rb["stats"].get(p, {}).get("calls_crossed")) for p in rb["order"]))
    out.append("")
    out.append("flow vector (the allocator-visible state, sorted): %s"
               % ("IDENTICAL - the two texts pose the SAME allocation problem, so any register "
                  "difference comes from allocno ORDER, not from lifetimes" if va == vb
                  else "DIFFERENT - a lifetime or reference count really moved"))
    return out


# ------------------------------------------------------------------------------------- loop

def explain_loop(a, b, names, top):
    kitlib.add_paths()
    import loop_census as LC                                             # noqa: E402
    if "loop" not in a or "loop" not in b:
        return ["why: no .loop dump (the row's recipe may disable the loop pass)"]
    fa, fb = LC.split_functions(a["loop"]), LC.split_functions(b["loop"])
    out = ["real insn counts per loop (`loop.c` hoists an invariant only when "
           "threshold * savings * lifetime >= insn_count, 2.7.2 loop.c:1631):",
           "  %-10s %s" % (names[0], LC.loop_counts(fa)),
           "  %-10s %s" % (names[1], LC.loop_counts(fb))]
    trans, refusal = LC.compare(fa, fb)
    if refusal:
        out.append("")
        out.append("loops could not be aligned: %s - the structure itself changed, which is the "
                   "finding." % refusal)
        return out
    if not trans:
        out.append("")
        out.append("No loop DECISION differs: every movable has the same verdict and the biv/giv/"
                   "unrolling diagnostics are equal. A changed insn COUNT without a changed decision "
                   "is not evidence (work/native_lane/r64_loop_study/NOTE.md).")
        return out
    body = [[t["fn"], t["loop"], t["kind"], (t["pinned"] or "")[:34], (t["erased"] or "")[:34],
             (t.get("expr") or "")[:40], "%s->%s" % tuple(t["insns"])] for t in trans[:top]]
    out.append("")
    out.append(kitlib.fmt_table(["function", "loop", "decision", names[0], names[1], "expr", "insns"], body))
    if len(trans) > top:
        out.append("... %d more" % (len(trans) - top))
    return out


# --------------------------------------------------------------------------- filtered RTL diff

def explain_diff(a, b, names, around, phase, top, context):
    ia, ib = insns_of(a[phase]), insns_of(b[phase])
    pa, pb = [x["anon"] for x in ia], [x["anon"] for x in ib]
    out = ["%s: %d insns, %s: %d insns (pseudos anonymised by first appearance; UIDs and regnos "
           "shift when a pin is erased, so neither is comparable)" % (names[0], len(pa), names[1], len(pb))]
    if pa == pb:
        out.append("")
        out.append("The insn streams are IDENTICAL at `%s`. Whatever changed happens later - try the "
                   "next pass (%s)." % (phase, ", ".join(PASSES[PASSES.index(phase) + 1:PASSES.index(phase) + 3]) or "the assembly"))
        return out
    sm = difflib.SequenceMatcher(None, pa, pb, autojunk=False)
    shown = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        raw = [ia[k]["pattern"] for k in range(i1, i2)] + [ib[k]["pattern"] for k in range(j1, j2)]
        if around and not any(around.hit(r) for r in raw):
            continue
        shown += 1
        if shown > top:
            out.append("... (%d more hunks; raise --top or narrow with --around)"
                       % (sum(1 for t, *_ in sm.get_opcodes() if t != "equal") - top))
            break
        out.append("")
        out.append("--- hunk %d (%s at %s:%d / %s:%d)" % (shown, tag, names[0], i1, names[1], j1))
        for k in range(max(0, i1 - context), i1):
            out.append("   %s" % short(pa[k]))
        for k in range(i1, i2):
            out.append("  -%s   [uid %d]" % (short(pa[k]), ia[k]["uid"]))
        for k in range(j1, j2):
            out.append("  +%s   [uid %d]" % (short(pb[k]), ib[k]["uid"]))
        for k in range(i2, min(len(pa), i2 + context)):
            out.append("   %s" % short(pa[k]))
    if not shown:
        out.append("")
        out.append("The streams differ, but no hunk mentions %s. Widen or drop --around."
                   % (around.token if around else "the filter"))
    return out


# ------------------------------------------------------------ one block, tick by tick (--trace)

LAUNCH_BITS = 0x7f000000        # sched.c: LAUNCH_PRIORITY 0x7f000001, TAIL_PRIORITY 0x7ffffffe - i


def fmt_prio(p):
    return "%#x" % p if p is not None and p >= LAUNCH_BITS else str(p)


def boost_tag(uid, prio, recs, phase):
    """' [launched: birthing boost]' / ' [tail: kept at block end]' / '' for a dynamic priority.

    `adjust_priority` gives a birthing insn (a single-set register it makes live, sched1 only:
    `reload_completed` turns it off) `max_priority` = MAX(prio(ready[0]), LAUNCH_PRIORITY) - so a
    launched insn can inherit a TAIL value while a jump/call is still ready.  The kind decides."""
    if prio is None or not prio & LAUNCH_BITS:
        return ""
    rec = recs.get(uid) or {}
    if rec.get("kind") in ("jump_insn", "call_insn") or rec.get("pattern", "").startswith("(use"):
        return " [tail: kept at block end]"
    return " [launched: birthing boost]" if phase == "sched" else " [high priority]"


def is_launched(uid, prio, recs, phase):
    return phase == "sched" and "launched" in boost_tag(uid, prio, recs, phase)


def pick_reason(tick, luid, recs, links_of, last, phase):
    """(label, detail) - why `tick['pick']` was chosen, from the tick's own lines.

    Labels: sole, priority, hazard (schedule_select), LUID tie, class/stale-sort, stall (all blocked),
    tie (an insn of the tie is not in the previous pass's dump, so its LUID is not known).
    `class/stale-sort`: equal priority, no hazard line, and the pick has the LOWER LUID - either
    rank_for_schedule's class rule (a ready insn that the last-scheduled insn depends on with a cost > 1
    ranks below the others; the cost is not in the dump) or a list SCHED_SORT did not re-sort (it sorts
    only when two or more insns joined).  The one checkable fact - is the loser a LOG_LINK of the
    last-scheduled insn? - is printed; nothing more is claimed."""
    pick = tick["pick"]
    pr = dict(tick["ready"])
    blocked = dict(tick["blocked"])
    bl = ("; blocked: " + ", ".join("%d for %d" % b for b in tick["blocked"])) if blocked else ""
    if pick is None:
        return "stall", "every ready insn was blocked by a unit hazard - nothing issues this tick" + bl
    others = [u for u in pr if u != pick and u not in blocked]
    if not others:
        return "sole", "the only ready insn - sched.c always issues it" + bl
    top = max(pr[u] for u in others)
    if pr[pick] > top:
        return "priority", "%s > %s (%s)%s%s" % (
            fmt_prio(pr[pick]), fmt_prio(top), ",".join(str(u) for u in others if pr[u] == top),
            boost_tag(pick, pr[pick], recs, phase), bl)
    ties = [u for u in others if pr[u] == pr[pick]]
    if not ties:
        return "unexplained", "a lower priority than %s was issued - read the raw lines" % fmt_prio(top)
    if tick["hazard"] == pick:
        was = (tick["sorted"] or [None])[0]
        return "hazard", "equal priority %s with %s; schedule_select: `insn %d has a greater potential " \
                         "hazard`%s%s" % (fmt_prio(pr[pick]), ",".join(map(str, ties)), pick,
                                          " (the sort had %s first)" % was if was not in (None, pick) else "", bl)
    unknown = [u for u in ties + [pick] if u not in luid]
    if unknown:
        return "tie", "equal priority %s with %s; INSN_LUID unknown for %s (not in the .%s dump - " \
                      "prologue/epilogue insns are emitted after it), so the tie rule cannot be read" % (
                          fmt_prio(pr[pick]), ",".join(map(str, ties)), ",".join(map(str, unknown)),
                          PRE_PASS.get(phase, "?"))
    higher = [u for u in ties if luid[u] > luid[pick]]
    if not higher:
        return "LUID tie", "equal priority %s with %s; the higher INSN_LUID (later in the chain) goes " \
                           "first%s" % (fmt_prio(pr[pick]), ",".join(map(str, ties)), bl)
    fed = [u for u in higher if last is not None and u in {k for k, _ in links_of.get(last, [])}]
    return "class/stale-sort", "equal priority %s, but %s has a higher LUID; %s%s" % (
        fmt_prio(pr[pick]), ",".join(map(str, higher)),
        "%s is a LOG_LINK of the last-scheduled %d (class rule, cost > 1 if it is a load)" % (
            ",".join(map(str, fed)), last) if fed else
        "no loser is a LOG_LINK of the last-scheduled insn %s (stale sort order?)" % last, bl)


def loss_reason(tick, uid, luid):
    """Why `uid`, ready at this tick, lost to the pick."""
    pr, win = dict(tick["ready"]), tick["pick"]
    if uid in dict(tick["blocked"]):
        return "blocked for %d cycles (function-unit hazard)" % dict(tick["blocked"])[uid]
    if win is None:
        return "nothing issued (stall)"
    if pr[win] > pr[uid]:
        return "priority %s > %s" % (fmt_prio(pr[win]), fmt_prio(pr[uid]))
    if tick["hazard"] == win:
        return "potential hazard (equal priority %s)" % fmt_prio(pr[uid])
    if win not in luid or uid not in luid:
        return "tie (equal priority; INSN_LUID unknown for %s)" % ",".join(str(u) for u in (win, uid) if u not in luid)
    if luid[win] > luid[uid]:
        return "LUID tie (equal priority; %d is later in the chain)" % win
    return "class/stale-sort (equal priority; %d has the LOWER LUID)" % win


def dependents(recs):
    """{uid: [(dependent uid, kind)]} - the insns whose LOG_LINKS name each insn (its ref_count owners)."""
    out = collections.defaultdict(list)
    for r in recs.values():
        for k, t in r.get("links", []):
            out[k].append((r["uid"], t))
    return out


def dep_kind(t):
    return {"true": "true", "REG_DEP_ANTI": "anti", "REG_DEP_OUTPUT": "output"}.get(t, t)


def pick_ticks(blk):
    return {t["pick"]: t["t"] for t in blk["ticks"] if t["pick"] is not None}


def block_positions(blk):
    """{uid: forward position in the block} - the picks, reversed (the block is filled from its end)."""
    picks = [t["pick"] for t in blk["ticks"] if t["pick"] is not None]
    return {u: len(picks) - 1 - i for i, u in enumerate(picks)}


def main_function(blocks, row):
    """The blocks of the row's function (a text with static helpers dumps several functions)."""
    funcs = [b["function"] for b in blocks]
    names = {row.get("func"), row.get("true_name")}
    pick = next((f for f in reversed(funcs) if f in names), funcs[-1] if funcs else None)
    return [b for b in blocks if b["function"] == pick], sorted(set(funcs) - {pick}, key=str)


def resolve_block(blocks, spec, ret_to_uid=None):
    """(block, reading) for `--block`: `b<N>` block number, `u<N>` uid, `r<N>` retail word index,
    plain N = a uid when some block's priority table holds it, else the block number."""
    s = spec.strip().lower()
    by_uid = {u: b for b in blocks for u in b["prio"]}
    for b in blocks:                      # insns without a priority line (priority 0) still appear in ticks
        for t in b["ticks"]:
            for u, _ in t["ready"]:
                by_uid.setdefault(u, b)
    def by_n(n):
        hit = [b for b in blocks if b["n"] == n]
        if not hit:
            raise SystemExit("why: no basic block number %d (blocks %s)" % (n, ", ".join(str(b["n"]) for b in blocks)))
        return hit[0]
    m = re.fullmatch(r"([bur]?)(\d+)", s)
    if not m:
        raise SystemExit("why: --block takes N, bN (block number), uN (insn uid) or rN (retail word index)")
    kind, n = m.group(1), int(m.group(2))
    if kind == "b":
        return by_n(n), "basic block number %d" % n
    if kind == "u" or (kind == "" and n in by_uid):
        if n not in by_uid:
            raise SystemExit("why: no scheduled block holds insn uid %d" % n)
        return by_uid[n], "insn uid %d" % n
    if kind == "r":
        if ret_to_uid is None:
            raise SystemExit("why: --block r%d needs the retail map, and the scorer printed no listing "
                             "(the variant is exact: retail index == generated index). Give a uid or bN." % n)
        uid = ret_to_uid.get(n)
        if uid is None or uid not in by_uid:
            raise SystemExit("why: retail word [%d] maps to no scheduled insn of this text (%s)"
                             % (n, "uid %s" % uid if uid is not None else "unplaced or retail-only"))
        return by_uid[uid], "retail word [%d] = insn uid %d" % (n, uid)
    return by_n(n), "no insn uid %d; read as basic block number %d" % (n, n)


def explain_trace(d, phase, blk, recs, luid, where, insn=None, retail=None):
    """The block's table and its ticks (or one insn's history with `insn`)."""
    links_of = {u: r.get("links", []) for u, r in recs.items()}
    deps = dependents(recs)
    picks = pick_ticks(blk)
    pos = block_positions(blk)
    first_ready = {}
    for t in blk["ticks"]:
        for u, _ in t["ready"]:
            first_ready.setdefault(u, t["t"])
    uids = sorted(set(blk["prio"]) | set(picks), key=lambda u: pos.get(u, 10 ** 6))
    src = {u: i for i, u in enumerate(sorted((u for u in uids if u in luid), key=luid.get))}
    by_uid, gen_ret = (retail or {}).get("by_uid", {}), (retail or {}).get("gen_ret", {})

    def gen_of(u):
        g = by_uid.get(u)
        return None if not g else g[0]

    def ret_of(u):
        g = gen_of(u)
        return None if g is None else gen_ret.get(g)

    reasons, last = {}, None
    for t in blk["ticks"]:                              # T-1 first: the order sched.c ran
        if t["pick"] is not None:
            reasons[t["pick"]] = pick_reason(t, luid, recs, links_of, last, phase)
            last = t["pick"]
    out = ["# block %d (%s .. %s) of %s: %d insns, %d ticks - %s"
           % (blk["n"], blk["from"], blk["to"], blk["function"], len(uids), blk["total"] or 0, where),
           "# the block is scheduled BACKWARDS: T-1 issues its LAST insn; `pos` is the forward position."]
    if retail:
        out.append("# retail map: %s" % retail["note"])
    body = []
    for u in uids:
        if insn is not None and u != insn:
            continue
        pr, rc = blk["prio"].get(u, (None, None))
        rec = recs.get(u, {})
        lab = reasons.get(u, ("-", ""))[0]
        g, r = gen_of(u), ret_of(u)
        row = [pos.get(u, "-"), u, src.get(u, "?"), fmt_prio(pr), rc,
               "T-%d" % first_ready[u] if u in first_ready else "-",
               "T-%d" % picks[u] if u in picks else "-", lab]
        if retail:
            row += ["-" if g is None else g, "-" if r is None else r]
        row.append(short(rec.get("pattern", "?"), 60))
        body.append(row)
    head = ["pos", "uid", "src", "prio", "refs", "ready", "picked", "why"] + (["gen", "retail"] if retail else []) + ["insn"]
    out.append(kitlib.fmt_table(head, body))
    out.append("   `src` = INSN_LUID rank in the block (chain order the previous pass left; `?` = not in that "
               "dump); `prio`/`refs` = sched.c's static table; `ready` = first tick on the ready list.")
    if insn is None:
        out.append("")
        out.append("## ticks")
        for t in blk["ticks"]:
            lab, why = pick_reason(t, luid, recs, links_of, None, phase) if t["pick"] is None else reasons[t["pick"]]
            ready = " ".join("%d(%s)" % (u, fmt_prio(p)) for u, p in t["ready"])
            extra = "".join(" [launch %d%s]" % (u, " +%d stalls" % s if s else "") for u, s in t["launched"])
            out.append("T-%-3d %-6s %-16s %s" % (t["t"], t["pick"] if t["pick"] is not None else "-", lab, why))
            out.append("       ready: %s%s" % (ready, extra))
        return out
    # one insn's history
    out.append("")
    out.append("## insn %d: %s" % (insn, short(recs.get(insn, {}).get("pattern", "?"), 110)))
    succ = [(v, dep_kind(k), picks.get(v)) for v, k in deps.get(insn, [])]
    if succ:
        out.append("   its dependents (it becomes ready when the last of these is scheduled): " +
                   ", ".join("%d %s%s" % (v, k, " @T-%d" % p if p else " (other block)") for v, k, p in succ))
    launches = [l for l in blk["launches"] if l["uid"] == insn]
    for l in launches:
        out.append("   queued, then launched before %d at T-%d%s" % (l["before"], l["t"],
                   " after %d stalls" % l["stalls"] if l["stalls"] else ""))
    seen = False
    for t in blk["ticks"]:
        pr = dict(t["ready"])
        if insn not in pr:
            continue
        if not seen:
            within = [p for v, _, p in succ if p is not None]
            out.append("   ready from T-%d%s" % (t["t"], " (last dependent picked at T-%d)" % max(within) if within else ""))
            seen = True
        if t["pick"] == insn:
            lab, why = reasons[insn]
            out.append("   T-%-3d PICKED  %s: %s" % (t["t"], lab, why))
            break
        out.append("   T-%-3d lost to %s: %s" % (t["t"], t["pick"] if t["pick"] is not None else "nothing (stall)", loss_reason(t, insn, luid)))
    if not seen:
        out.append("   never on a ready list of this block")
    return out


def explain_deps(d, phase, uid, prio=None):
    """LOG_LINKS of one insn (with dependence kind) and the insns that depend on it."""
    recs = {x["uid"]: x for x in insns_of(d[phase], True)}
    if uid not in recs:
        raise SystemExit("why: no insn uid %d in the .%s dump" % (uid, phase))
    rec = recs[uid]
    out = ["insn %d (%s): %s" % (uid, rec["kind"], short(rec["pattern"], 110))]
    if prio:
        out.append("   sched.c: priority %s, ref_count %s" % (fmt_prio(prio[0]), prio[1]))
    out.append("")
    out.append("depends on (its LOG_LINKS in the .%s dump):" % phase)
    rows_ = [[k, dep_kind(t), short(recs[k]["pattern"], 80) if k in recs else "(not in this dump)"]
             for k, t in rec.get("links", [])]
    out.append(kitlib.fmt_table(["uid", "kind", "insn"], rows_) if rows_ else "   (none)")
    out.append("")
    out.append("depended on by (insns whose LOG_LINKS name %d - its ref_count owners):" % uid)
    rows_ = [[v, dep_kind(t), short(recs[v]["pattern"], 80)] for v, t in dependents(recs).get(uid, [])]
    out.append(kitlib.fmt_table(["uid", "kind", "insn"], rows_) if rows_ else "   (none)")
    return out


def retail_for(row, text, asm):
    """{by_uid, gen_ret, note} - uid -> generated words -> retail words, or None on an exact text."""
    import retailmap as RM                                               # noqa: E402
    v = kitlib.score_at(row, text, diff=True)
    rows_ = RM.scorer_rows(v.get("text"))
    if not rows_:
        return None
    gen = [(i, g) for i, g, _ in rows_ if g]
    by_uid, by_gen, cov = RM.uid_map(asm, gen)
    m, _regions, moved = RM.align(rows_)
    return {"by_uid": by_uid, "by_gen": by_gen, "gen_ret": m, "moved": moved, "rows": rows_,
            "note": "%d of %d predicted words placed on %d generated words (the `-dap` assembly aligned "
                    "on mnemonic; `-` = not placed); gen -> retail by LCS + moved identical instructions"
                    % cov}


def run_single(a, row, lane, base):
    """--trace / --block / --insn / --deps: one text, one compile."""
    text, name = resolve_text(a.variant, row, lane, base)
    d = kitlib.dumps(row, text, asm_names=True)
    if d.get("error"):
        raise SystemExit("why: %s does not build: %s" % (name, d["error"]))
    phase = a.phase or "sched2"
    if phase not in d:
        raise SystemExit("why: this recipe produced no .%s dump" % phase)
    kitlib.add_paths()
    import sched_trace                                                   # noqa: E402
    print("# why %s  --pass %s  %s   (%s, recipe %s)" % (row["id"], phase, "--deps %d" % a.deps if a.deps is not None
          else "--trace", name, row["cfg"]))
    blocks, others = main_function(sched_trace.block_traces(d[phase]), row) if phase in ("sched", "sched2") else ([], [])
    if others:
        print("# (the dump also schedules %s; only %s is read)" % (", ".join(others), blocks[0]["function"]))
    if a.deps is not None:
        prio = next((b["prio"][a.deps] for b in blocks if a.deps in b["prio"]), None)
        print("\n".join(explain_deps(d, phase, a.deps, prio)))
        return
    if phase not in ("sched", "sched2"):
        raise SystemExit("why: --trace reads the scheduler: --pass sched or sched2")
    if not blocks:
        raise SystemExit("why: the .%s dump carries no `;; ready list` commentary (haifa-sched cells, 2.91.66/"
                         "2.95.2, print another format); use --pass %s without --trace" % (phase, phase))
    retail = retail_for(row, text, d["asm"]) if (a.retail or (a.block or "").lower().startswith("r")) else None
    if (a.retail or (a.block or "").lower().startswith("r")) and retail is None:
        print("# retail map: the scorer printed no listing for %s (exact at %s) - generated == retail" % (name, row["cfg"]))
    ret_to_uid = None
    if retail:
        inv = {r: g for g, r in retail["gen_ret"].items()}
        ret_to_uid = {r: retail["by_gen"].get(g) for r, g in inv.items()}
    if a.block:
        blk, where = resolve_block(blocks, a.block, ret_to_uid)
    else:
        blk, where = resolve_block(blocks, "u%d" % a.insn)
    recs = {x["uid"]: x for x in insns_of(d[phase], True)}
    luid = pre_order(d, phase, True) or {u: u for u in recs}
    if pre_order(d, phase, True) is None:
        print("# NOTE: no .%s dump: LUID = uid order (approximate)" % PRE_PASS[phase])
    if a.insn is not None and a.insn not in blk["prio"] and not any(a.insn == u for t in blk["ticks"] for u, _ in t["ready"]):
        raise SystemExit("why: insn %d is not in block %d" % (a.insn, blk["n"]))
    print("\n".join(explain_trace(d, phase, blk, recs, luid, where, a.insn, retail)))


# ---------------------------------------------------------------------------------------- CLI

def resolve_text(spec, row, lane, base):
    if spec in (None, "pinned", "base"):
        return base, "pinned"
    if spec == "erased":
        return kitlib.erased_text(base), "erased"
    p = Path(spec)
    if not p.is_file():
        raise SystemExit("why: %r is neither 'pinned', 'erased' nor a file" % spec)
    return p.read_text(errors="replace"), p.stem


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("--pass", dest="phase", choices=PASSES,
                    help="required, except with --deps (default sched2)")
    ap.add_argument("--variant", default="erased", help="the subject text (default: all pins erased)")
    ap.add_argument("--vs", default="pinned", help="the reference text (default: the row's pinned text)")
    ap.add_argument("--around", help="variable name, $reg, pseudo number, L<line> or an RTL substring")
    ap.add_argument("--top", type=int, default=12, help="most blocks/rows/hunks to print")
    ap.add_argument("--context", type=int, default=2, help="insns of context in a pass diff")
    ap.add_argument("--cfg", help="compile both texts as if the row were registered at this cfg (no ledger write)")
    ap.add_argument("--trace", action="store_true",
                    help="sched/sched2, ONE text (--variant): one block's table and every tick's pick + reason")
    ap.add_argument("--block", help="the block to trace: N (a uid, else a block number), bN, uN, rN (retail word)")
    ap.add_argument("--insn", type=int, help="with --trace: only this insn's history (ready, losses, pick)")
    ap.add_argument("--retail", action="store_true",
                    help="with --trace: byte-score the text and add uid -> generated -> retail word columns")
    ap.add_argument("--deps", type=int, metavar="UID",
                    help="ONE text (--variant): this insn's LOG_LINKS (kind) and its dependents, at --pass")
    a = ap.parse_args()
    single = a.trace or a.block or a.insn is not None or a.deps is not None
    if not a.phase and a.deps is None:
        ap.error("--pass is required (except with --deps)")
    if single and a.deps is None and a.block is None and a.insn is None:
        ap.error("--trace needs --block (N, bN, uN or rN) or --insn")

    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    if a.cfg:
        row = kitlib.row_at_cfg(row, a.cfg)
    base = kitlib.base_text(row, lane)
    if single:
        return run_single(a, row, lane, base)
    ta, na = resolve_text(a.vs, row, lane, base)
    tb, nb = resolve_text(a.variant, row, lane, base)
    names = (na, nb)

    da = kitlib.dumps(row, ta)
    db = kitlib.dumps(row, tb)
    for d, n in ((da, na), (db, nb)):
        if d.get("error"):
            raise SystemExit("why: %s does not build: %s" % (n, d["error"]))
    if a.phase not in da or a.phase not in db:
        raise SystemExit("why: this recipe produced no .%s dump (passes present: %s)"
                         % (a.phase, ", ".join(sorted(k for k in da if k in PASSES))))

    kitlib.add_paths()
    import alloc_sim                                                     # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    cell, _ = parse_cfg(row["cfg"])
    around = Around(a.around, row, ta, alloc_sim.FIRST.get(cell)) if a.around else None
    if around and not around:
        around = None

    print("# why %s  --pass %s   (%s vs %s, recipe %s)" % (row["id"], a.phase, na, nb, row["cfg"]))
    if around:
        print("# --around %r resolved to: %s" % (a.around, "; ".join(around.explain)))
    kitlib.add_paths()
    import screen as SCR                                                 # noqa: E402
    la, lb = SCR.normalise(da["asm"].splitlines()), SCR.normalise(db["asm"].splitlines())
    print("# listing distance %s -> %s: %d changed lines" % (na, nb, SCR.sdiff(la, lb)))

    if a.phase in ("sched", "sched2"):
        lines = explain_sched(da, db, names, around, a.phase, a.top)
    elif a.phase == "greg":
        lines = explain_greg(da, db, names, around, row, (ta, tb), a.top)
    elif a.phase == "lreg":
        lines = explain_lreg(da, db, names, around, row, (ta, tb), a.top)
    elif a.phase == "loop":
        lines = explain_loop(da, db, names, a.top)
    else:
        lines = explain_diff(da, db, names, around, a.phase, a.top, a.context)
    print("\n".join(lines))


if __name__ == "__main__":
    main()
