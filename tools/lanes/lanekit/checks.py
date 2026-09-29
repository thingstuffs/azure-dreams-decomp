#!/usr/bin/env python3
"""checks.py - the four proof checks of `tools/learnings/pin_removal_possibilities.md`, run on ONE candidate.

    cd work/native_lane/<lane>
    python3 <KIT>/checks.py <row> cand.c [--cfg CFG]

Round 80's last-resort lane (r80_fable_n1) spent most of its budget proving by hand that two rows' prior
60-probe sweeps had varied an axis that could not move the residue.  These are its four checks, read
from one `-dap` compile of the candidate and one byte score (`--cfg`: at that cell, nothing written):

  (i)   sole-ready-at-stall (sched2).  An ORDER residue insn that retail has EARLIER than it is emitted
        needs a LATER tick of the backward list scheduler.  If, at the tick it was issued, it was the
        only ready insn or outranked every other on priority, no LUID (statement order) change can hold
        it back: NOT-REORDERABLE - retail's graph has a successor of it that this RTL lacks.  Issued on a
        LUID tie, or later losing LUID ties it would need to win: REORDERABLE.
  (ii)  launched vs early group (sched1).  Retail "non-launched N after launched H" (H got sched.c's
        birthing boost 0x7f000001, N did not) is reachable only if H has a non-launched consumer with a
        LUID below N's, or H is a load (a consumer link costing > 1).  Neither: NOT-REORDERABLE.
  (iii) known-constant base (combine).  An OPCODE residue `ori` where retail has `addiu`, made by
        combine's PLUS->IOR on a pseudo with exactly one set, from a CONST_INT (`nonzero_bits` is known
        when reg_n_sets == 1): OPAQUE-BASE - retail's base was opaque to combine; order is irrelevant.
  (iv)  barrier.  A volatile asm (`ASM_KEEP`, `ASM_SCHED_BARRIER`: `asm_operands/v`, `asm_input`) in the
        residue insn's block makes every earlier insn a predecessor of every later one (sched.c
        `reg_pending_sets_all`): BARRIER-GOVERNED - order experiments on it are inert while it stands.

Per residue insn (every item of `diff.py --scorer --classify`), one verdict, in this precedence:
OPAQUE-BASE, BARRIER-GOVERNED, NOT-REORDERABLE, REORDERABLE, UNKNOWN - with the evidence line of every
check that said something.  UNKNOWN is the honest answer when the dumps cannot decide: an insn the
`-dap` map could not place, a COUNT/COLOUR residue, a split insn with no known LUID, a pick decided by
`potential hazard` or the class rule.  The uid -> generated word map is a model of the assembler
(`retailmap.uid_map`); its coverage is printed first.  Nothing here stages, scores for the ledger, or
writes a file.
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib                                                             # noqa: E402
import retailmap as RM                                                    # noqa: E402
import why as W                                                           # noqa: E402

ORDER_OF = ("OPAQUE-BASE", "BARRIER-GOVERNED", "NOT-REORDERABLE", "REORDERABLE", "UNKNOWN")
CHAIN = {"sched": "sched1 LUIDs follow the C statement order after combine",
         "sched2": "sched2 LUIDs follow sched1's OUTPUT order, not the C directly - check (ii)"}
BARRIER_RE = re.compile(r"asm_operands/v|^\(asm_input|unspec_volatile|\(asm_input ")


class Pass:
    """One scheduler pass of one compile: its blocks (the row's function), insn records, LUIDs."""

    def __init__(self, d, phase, row):
        self.phase = phase
        self.ok = phase in d
        if not self.ok:
            return
        W.kitlib.add_paths()
        import sched_trace                                               # noqa: E402
        self.blocks, _ = W.main_function(sched_trace.block_traces(d[phase]), row)
        self.recs = {x["uid"]: x for x in W.insns_of(d[phase], True)}
        self.luid = W.pre_order(d, phase, True) or {}
        self.deps = W.dependents(self.recs)
        self.links = {u: r.get("links", []) for u, r in self.recs.items()}

    def block_of(self, uid):
        if not self.ok:
            return None
        for b in self.blocks:
            if uid in b["prio"] or any(uid == u for t in b["ticks"] for u, _ in t["ready"]):
                return b
        return None

    @staticmethod
    def uids(blk):
        return set(blk["prio"]) | {u for t in blk["ticks"] for u, _ in t["ready"]}


# ------------------------------------------------------------------------------ the four checks

def check_sole_ready(p, uid, direction):
    """(i) -> (verdict, evidence) or None when it does not apply."""
    blk = p.block_of(uid)
    if blk is None or direction is None:
        return None
    ticks = blk["ticks"]
    picked = next((t for t in ticks if t["pick"] == uid), None)
    if picked is None:
        return "UNKNOWN", "(i) %s block %d: insn %d is never issued by a traced tick" % (p.phase, blk["n"], uid)
    last = None
    for t in ticks:
        if t is picked:
            break
        last = t["pick"] if t["pick"] is not None else last
    lab, why = W.pick_reason(picked, p.luid, p.recs, p.links, last, p.phase)
    ready = next(t["t"] for t in ticks if any(u == uid for u, _ in t["ready"]))
    succ = [(v, W.pick_ticks(blk).get(v)) for v, _ in p.deps.get(uid, [])]
    succ = [(v, s) for v, s in succ if s is not None]
    head = "(i) %s block %d: ready from T-%d%s, issued at T-%d on %s (%s)" % (
        p.phase, blk["n"], ready, " after %d@T-%d" % max(succ, key=lambda x: x[1]) if succ else "",
        picked["t"], lab, why)
    if direction == "earlier":
        if lab in ("sole", "priority"):
            return "NOT-REORDERABLE", head + "; retail has it EARLIER, i.e. not issued at T-%d - no LUID " \
                   "change can hold back a %s insn: retail's graph has a successor of it this RTL lacks" % (
                       picked["t"], "lone ready" if lab == "sole" else "top-priority")
        if lab == "LUID tie":
            return "REORDERABLE", head + "; retail has it EARLIER: raising a tied insn's LUID above it flips " \
                                         "the tie (%s)" % CHAIN[p.phase]
        return "UNKNOWN", head + "; retail has it EARLIER, but the pick was not decided by the tie rule"
    losses = [(t["t"], t["pick"], W.loss_reason(t, uid, p.luid)) for t in ticks
              if t is not picked and t["t"] < picked["t"] and any(u == uid for u, _ in t["ready"])]
    tie = next((x for x in losses if x[2].startswith("LUID tie")), None)
    if tie:
        return "REORDERABLE", head + "; retail has it LATER and it lost a LUID tie to %d at T-%d: a LUID " \
                                     "change lets it win (%s)" % (tie[1], tie[0], CHAIN[p.phase])
    if not losses:
        return "UNKNOWN", head + "; retail has it LATER but it was issued the tick it became ready: its " \
                                 "dependents would have to be issued sooner"
    return "UNKNOWN", head + "; retail has it LATER; it lost T-%d..T-%d on %s, not on a LUID tie" % (
        losses[0][0], losses[-1][0], ", ".join(sorted({x[2].split(" ")[0] for x in losses})))


def launched_set(p, blk):
    out = set()
    for t in blk["ticks"]:
        for u, pr in t["ready"]:
            if W.is_launched(u, pr, p.recs, "sched"):
                out.add(u)
    return out


def check_launched(p, uid, gen_of, ret_of):
    """(ii) -> (verdict, evidence) or None.  `gen_of`/`ret_of`: uid -> word index (or None)."""
    blk = p.block_of(uid)
    if blk is None:
        return None
    L = launched_set(p, blk)
    gx, rx = gen_of(uid), ret_of(uid)
    if gx is None or rx is None:
        return None
    found = []
    for o in sorted(p.uids(blk) - {uid}):
        go, ro = gen_of(o), ret_of(o)
        if go is None or ro is None or (gx < go) == (rx < ro) or (uid in L) == (o in L):
            continue
        h, n = (uid, o) if uid in L else (o, uid)
        if not ret_of(n) > ret_of(h):
            continue                                 # the rule speaks of retail "N after H" only
        if n not in p.luid:
            found.append(("UNKNOWN", "(ii) sched block %d: retail has non-launched %d after launched %d, but %d "
                                     "has no known LUID" % (blk["n"], n, h, n)))
            continue
        cons = [c for c, _ in p.deps.get(h, []) if c not in L and c in p.luid and p.luid[c] < p.luid[n]]
        pat = p.recs.get(h, {}).get("pattern", "")
        if cons:
            found.append(("REORDERABLE", "(ii) sched block %d: retail has non-launched %d after launched %d, and %d "
                                         "has a non-launched consumer %s with a LUID below %d" % (
                                             blk["n"], n, h, h, ",".join(map(str, cons)), n)))
        elif re.match(r"\(set \(reg[^)]*\) \((?:zero_extend:\w+ |sign_extend:\w+ )?\(?mem", pat):
            found.append(("REORDERABLE", "(ii) sched block %d: retail has non-launched %d after launched %d; %d is "
                                         "a load, so a consumer link costs > 1" % (blk["n"], n, h, h)))
        else:
            allc = ", ".join("%d%s" % (c, "*" if c in L else "") for c, _ in p.deps.get(h, [])) or "none"
            found.append(("NOT-REORDERABLE", "(ii) sched block %d: retail has non-launched %d after launched %d, "
                                             "but no non-launched consumer of %d has a LUID below %d (consumers: %s; "
                                             "* = launched) and %d is not a load - statement order is inert" % (
                                                 blk["n"], n, h, h, n, allc, h)))
    if not found:
        return None
    return min(found, key=lambda x: ORDER_OF.index(x[0]))


def const_base(flow, combine, uid):
    """(iii) core: (base pseudo, its value, set count, ior constant) when insn `uid` of the .combine dump
    is `(ior (reg B) (const_int c))`, else None."""
    recs = {x["uid"]: x for x in W.insns_of(combine, True)}
    pat = recs.get(uid, {}).get("pattern", "")
    m = re.search(r"\(ior:SI \(reg(?:/\w+)*:SI (\d+)\) \(const_int (-?\d+)\)\)", pat)
    if not m:
        return None
    b, c = int(m.group(1)), int(m.group(2))
    sets = [x for x in W.insns_of(flow, True)
            if re.match(r"\(set \(reg(?:/\w+)*:\w+ %d\) " % b, x["pattern"])]
    val = None
    if len(sets) == 1:
        mv = re.match(r"\(set \(reg(?:/\w+)*:\w+ %d\) \(const_int (-?\d+)\)\)$" % b, sets[0]["pattern"])
        val = int(mv.group(1)) if mv else None
    return {"base": b, "value": val, "sets": len(sets), "c": c}


def check_const_base(d, uid, got, tgt):
    """(iii) -> (verdict, evidence) or None."""
    if not (got or "").startswith("ori ") or not (tgt or "").startswith("addiu "):
        return None
    if "combine" not in d or "flow" not in d:
        return "UNKNOWN", "(iii) no .combine/.flow dump"
    cb = const_base(d["flow"], d["combine"], uid)
    if cb is None:
        return "UNKNOWN", "(iii) `ori` where retail has `addiu`, but insn %d is no `(ior (reg B) (const_int c))` " \
                          "in the .combine dump" % uid
    if cb["sets"] == 1 and cb["value"] is not None:
        return "OPAQUE-BASE", "(iii) combine made insn %d `(ior (reg %d) (const_int %d))`: pseudo %d has ONE set, " \
               "from const_int %#x, so nonzero_bits knows its bits (reg_n_sets == 1) and PLUS->IOR fires; retail's " \
               "`addiu` means its base was opaque (multi-set, a parameter, a HIGH/load value) - order is " \
               "irrelevant" % (uid, cb["base"], cb["c"], cb["base"], cb["value"] & 0xffffffff)
    return "UNKNOWN", "(iii) insn %d is `(ior (reg %d) (const_int %d))` but pseudo %d has %d set(s)%s in .flow - " \
                      "not the single-set constant case" % (uid, cb["base"], cb["c"], cb["base"], cb["sets"],
                                                            "" if cb["value"] is None else " from %#x" % cb["value"])


def check_barrier(p, uid):
    """(iv) -> (verdict, evidence) or None."""
    blk = p.block_of(uid)
    if blk is None:
        return None
    bars = [u for u in p.uids(blk) if u != uid and BARRIER_RE.search(p.recs.get(u, {}).get("pattern", ""))]
    if not bars:
        return None
    pos = W.block_positions(blk)
    b = min(bars, key=lambda u: abs(pos.get(u, 0) - pos.get(uid, 0)))
    side = "after" if pos.get(uid, -1) > pos.get(b, -1) else "before"
    direct = [x for x in bars if x in {k for k, _ in p.links.get(uid, [])} or uid in {k for k, _ in p.links.get(x, [])}]
    return "BARRIER-GOVERNED", "(iv) %s block %d: volatile asm %s; insn %d is %s %d%s - every insn on one side " \
           "depends on every insn on the other while it stands" % (
               p.phase, blk["n"], ",".join(map(str, sorted(bars))), uid, side, b,
               " (direct LOG_LINK with %s)" % ",".join(map(str, direct)) if direct else "")


# --------------------------------------------------------------------------------------- driver

def residue(rows, asm):
    """[(item, uid)] for every residue item, plus the maps and the coverage line."""
    regions, tot = RM.classify(rows)
    gen = [(i, g) for i, g, _ in rows if g]
    by_uid, by_gen, cov = RM.uid_map(asm, gen)
    m, _regions, moved = RM.align(rows)
    items = [(x, by_gen.get(x["gen"]) if x["gen"] is not None else None) for r in regions for x in r["items"]]
    return items, by_uid, by_gen, m, moved, cov, tot


def verdicts(d, row, rows):
    """[{item, uid, verdict, evidence: [..]}] - the checks for every residue item of one scored text."""
    items, by_uid, by_gen, m, moved, cov, tot = residue(rows, d["asm"])
    s1, s2 = Pass(d, "sched", row), Pass(d, "sched2", row)

    def gen_of(u):
        g = by_uid.get(u)
        return None if not g else g[0]

    def ret_of(u):
        g = gen_of(u)
        return None if g is None else m.get(g)

    out = []
    for x, uid in items:
        ev = []
        if uid is None:
            why = ("an assembler word (`#nop` load-delay filler or macro half) - it moves because its neighbours do"
                   if x["gen"] is not None else "retail-only: this text has no such instruction")
            out.append({"item": x, "uid": None, "verdict": "UNKNOWN", "evidence": ["no insn: " + why]})
            continue
        if x["kind"] == "OPCODE":
            r = check_const_base(d, uid, x["got"], x["tgt"])
            ev.append(r or ("UNKNOWN", "opcode differs (not the ori/addiu case): read `why.py --pass combine` / cse"))
        elif x["kind"] == "COLOUR":
            ev.append(("UNKNOWN", "register colour only: read `why.py --pass greg` / `prio.py`"))
        elif x["kind"] == "COUNT":
            ev.append(("UNKNOWN", "an insertion: no order check applies"))
        else:
            e = x["gen"]
            exp = e + RM.drift_at(m, moved, e)
            direction = "earlier" if x["ret"] < exp else "later" if x["ret"] > exp else None
            for p in (s2, s1):
                r = check_barrier(p, uid)
                if r:
                    ev.append(r)
                    break
            r = check_sole_ready(s2, uid, direction)
            if r:
                ev.append(r)
            r = check_launched(s1, uid, gen_of, ret_of)
            if r:
                ev.append(r)
            if not ev:
                ev.append(("UNKNOWN", "insn %d is in no traced sched/sched2 block of this function" % uid))
        verdict = min((v for v, _ in ev), key=ORDER_OF.index)
        out.append({"item": x, "uid": uid, "verdict": verdict, "evidence": [t for _, t in ev]})
    return out, cov, tot


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("candidate", help="candidate .c, or 'pinned' / 'erased'")
    ap.add_argument("--cfg", help="compile and score at this cfg (no ledger write)")
    a = ap.parse_args(argv)

    lane = kitlib.bootstrap()
    row = kitlib.row_at_cfg(kitlib.row_of(a.row_id), a.cfg)
    base = kitlib.base_text(row, lane)
    text, name = W.resolve_text(a.candidate, row, lane, base)
    d = kitlib.dumps(row, text, asm_names=True)
    if d.get("error"):
        raise SystemExit("checks: %s does not build at %s: %s" % (name, row["cfg"], d["error"]))
    v = kitlib.score_at(row, text, diff=True)
    rows = RM.scorer_rows(v.get("text"))
    print("# checks %s  %s at %s" % (row["id"], name, row["cfg"]))
    if not rows:
        print("# the scorer printed no listing (exact, or no disassembly): no residue to check")
        return
    res, cov, tot = verdicts(d, row, rows)
    print("# residue: %s; uid map: %d of %d predicted words placed on %d generated words"
          % (", ".join("%s %d" % kv for kv in tot.items()), *cov))
    body = []
    for r in res:
        x = r["item"]
        body.append(["-" if x["gen"] is None else x["gen"], "-" if x["ret"] is None else x["ret"], x["kind"],
                     "-" if r["uid"] is None else r["uid"], W.short(x["got"] or x["tgt"] or "", 28), r["verdict"]])
    print(kitlib.fmt_table(["gen", "retail", "kind", "uid", "insn", "verdict"], body))
    print()
    for r in res:
        x = r["item"]
        print("[%s -> %s] %s %s: %s" % ("-" if x["gen"] is None else x["gen"], "-" if x["ret"] is None else x["ret"],
                                         "uid %s" % r["uid"] if r["uid"] is not None else "no uid", x["kind"], r["verdict"]))
        for e in r["evidence"]:
            print("    " + e)
    counts = {k: sum(1 for r in res if r["verdict"] == k) for k in ORDER_OF}
    print()
    print("verdicts: " + ", ".join("%s %d" % kv for kv in counts.items() if kv[1]))


if __name__ == "__main__":
    main()
