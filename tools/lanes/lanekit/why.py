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

Texts: `--vs` is the reference (default `pinned`, the row's own text) and `--variant` the subject
(default `erased`, every pin erased).  Either may be a path to a candidate `.c`.
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


def insns_of(dump):
    """[{uid, kind, pattern, links, anon}] for a `-da` dump, in the order the dump prints them."""
    kitlib.add_paths()
    from sched_trace import instructions                                 # noqa: E402
    table = {}
    out = []
    for rec in instructions(dump):
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


def pre_order(d, phase):
    """{uid: position} from the dump of the pass BEFORE this scheduler runs.

    `sched.c` assigns INSN_LUID by walking the insn chain at pass entry, and that chain order is
    NOT UID order: `combine` creates insns with high UIDs and splices them where the combined insn
    was.  Reading the previous pass's dump is exact (UIDs are stable within one compile) and free,
    because that dump came out of the same `-da` compile."""
    src = d.get(PRE_PASS.get(phase, ""))
    if not src:
        return None
    return {x["uid"]: i for i, x in enumerate(insns_of(src))}


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
    ap.add_argument("--pass", dest="phase", required=True, choices=PASSES)
    ap.add_argument("--variant", default="erased", help="the subject text (default: all pins erased)")
    ap.add_argument("--vs", default="pinned", help="the reference text (default: the row's pinned text)")
    ap.add_argument("--around", help="variable name, $reg, pseudo number, L<line> or an RTL substring")
    ap.add_argument("--top", type=int, default=12, help="most blocks/rows/hunks to print")
    ap.add_argument("--context", type=int, default=2, help="insns of context in a pass diff")
    a = ap.parse_args()

    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    base = kitlib.base_text(row, lane)
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
