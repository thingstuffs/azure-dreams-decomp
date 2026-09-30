#!/usr/bin/env python3
"""alloc_need.py - the allocation INVERSE: from retail's colours to the priority inequalities that give them.

    cd work/native_lane/<lane>
    python3 <KIT>/alloc_need.py <row> <candidate.c|erased|pinned> [--ref pinned|FILE|none] [--cfg CFG]
                                [--json OUT.json] [--all]

`prio.py` prints who outranks whom in ONE text and `regcmp.py` which named variables sit in another register
than a reference; both leave the inverse question to the lane: "what would the numbers have to be for
retail's colouring to come out?".  Round-80 lanes answered it by hand (r80_opus_r2 "distance >= 3858 needs
live <= 77 at 10 refs", r80_opus_r10 "saved_a live <= 19 or position live >= 80").  This tool does it:

1. One `-dap` compile (`kitlib.dumps`) and one byte score (`kitlib.score_at`, diff listing).
2. RETAIL'S REGISTER PER PSEUDO, from the listing, not from names: `.lreg` RTL gives insn uid -> the pseudos
   it mentions; the `-dap` annotations give uid -> generated words (`retailmap.uid_map`); the scorer's
   alignment (`retailmap.align` + the COLOUR/OPCODE pairs of `retailmap.classify`) gives generated word ->
   retail word; the operand at the position where the generated word has the pseudo's hard register is a
   VOTE for the pseudo's retail register.  Unmoved identical words vote "same".  Insns where two pseudos (or
   a pseudo and an explicit hard register) share the register are skipped.  Works for temporaries too.
   Cross-check (`--ref`, default the row's pinned text, byte-exact by definition): the named variables'
   registers there (allocno dispositions + `ASM_REG("$N")` declarations).  Printed side by side.
3. A VERDICT per mis-coloured pseudo, before any order search:
     BLOCKED   retail's register is in the allocno's HARD conflicts (`;; N conflicts:` < FIRST_PSEUDO): a
               local-alloc qty, an explicit hard-register set or a remaining ASM_REG pin holds it across
               the allocno's life - no priority change can give it that register (global vs local lever).
     CLASS     retail has it in a call-clobbered register but it crosses calls here (calls lever).
     SPILLED   no hard register here.
     LOCAL     a block-local qty (local-alloc.c, `in block N`): qty order, approximate numbers.
     ORDER     everything else: an allocno_compare order question - the search below.
4. THE INVERSE.  `alloc_sim.allocate` (global.c find_reg model) is first run on the dump's own order and its
   agreement with the real dispositions printed (only allocnos it reproduces are targets).  Then every
   SINGLE-MOVER reorder (one allocno to every other slot) is simulated; a mover whose slot range colours
   every target like retail is a solution, and its crossings become inequalities on `allocno_compare`
   (global.c:587, verbatim: `int(floor_log2(refs) * refs / live * 10000 * size)`, descending, ties by
   allocno index = pseudo order):
       "pseudo 88 (entity) must outrank 91 (object_or_kind) [prio 2560 vs 2574]:
            88 refs >= 22 at live 82 | 88 live <= 81 at refs 21 | 91 refs <= 25 | 91 live >= 102"
   Two-mover beam when no single mover suffices.  An inequality is NECESSARY, not sufficient: the source
   change that moves a term also moves conflicts and live ranges of others - re-run the tool on it.
5. LEVERS per term (gcc 2.7.2 sources): refs are weighted by loop depth (flow.c `reg_n_refs += loop_depth`:
   a ref inside a real loop counts 2); live is REG_LIVE_LENGTH after sched1's recount and after
   local-alloc `update_equiv_regs`, which DOUBLES it for a single-set pseudo with REG_EQUIV (a second set
   halves it); calls crossed pick the class; a pseudo whose refs are all in one block is a local qty.

Variable names come from `alloc_sim.decl_pseudos` (declaration order; exact for function-scope locals and
parameters, approximate for inner-block locals, whose pseudos are made when the block is expanded): trust the
pseudo numbers and the listing evidence, and read a `ref disagrees` flag on a pseudo with >= 3 listing votes
as a naming miss, not a colour.

`--all` also prints the unchanged allocnos.  `--json` writes the analysis for batch use (`analyse()` is the
Python API).  Needs `alloc_sim.FIRST` for the cell (2.6.3 .. 2.8.1); 2.91.66 / 2.95.2 are refused.
"""
from __future__ import annotations

import argparse
import collections
import difflib
import json
import math
import re
import sys
from pathlib import Path

_HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(_HERE))
if not (_HERE / "kitlib.py").is_file():                      # a lane copy: use the repository's kit
    _root = next(p for p in _HERE.parents if (p / "tools/common.py").is_file())
    sys.path.insert(0, str(_root / "tools/lanes/lanekit"))
import kitlib                                                             # noqa: E402
import retailmap as RM                                                    # noqa: E402

REGNUM = {n: i for i, n in enumerate("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
                                     "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra".split())}
REGNUM["s8"] = 30
REGNAME = {v: k for k, v in REGNUM.items() if k != "s8"}
INSN = re.compile(r"^\((?:insn|call_insn|jump_insn) (\d+) ", re.M)
REG = re.compile(r"\(reg(?:/\w+)*:\w+ (\d+)(?: \w+)?\)")
ASMREG = re.compile(r"\b([A-Za-z_]\w*)\s+ASM_REG\(\s*\"\$(\w+)\"\s*\)")
TOK = re.compile(r"[,()\s]+")

LEVERS = {
    "refs+": "more refs: a use inside a REAL loop counts loop_depth (2 at depth 1: goto loop -> do/while/for); "
             "read a field through this variable instead of another pointer/copy; use it where a copy is used",
    "refs-": "fewer refs: read that value through another variable/copy or re-load it; split one role into a "
             "fresh local; a use moved out of a loop body",
    "live-": "shorter live: set it later / last use earlier (statement position, post-sched1 count); split the "
             "late role into a second variable; a single-set+REG_EQUIV pseudo is live-DOUBLED - a second set halves it",
    "live+": "longer live: set it earlier (top of the function) / use it later; a single set from a constant/"
             "memory with REG_EQUIV doubles live",
}


def rname(n):
    if n is None:
        return "?"
    if n < 0:
        return "spill"
    return "$" + REGNAME.get(n, str(n)) if n < 32 else "r%d" % n


def floor_log2(n):
    return 0 if n <= 0 else int(math.floor(math.log2(n)))


def prio(n, L, size=1):
    """global.c allocno_compare's key, verbatim (int truncation of the double; live 0 -> -1 as alloc_sim)."""
    if L == 0:
        L = -1
    return int((float(floor_log2(n) * n) / L) * 10000 * size)


def outranks(a, b):
    """allocno a sorts before b: (refs, live, size, pseudo) tuples."""
    pa, pb = prio(a[0], a[1], a[2]), prio(b[0], b[1], b[2])
    return pa > pb or (pa == pb and a[3] < b[3])


def thresholds(hi, lo):
    """`hi` must outrank `lo` (both (refs, live, size, pseudo)).  The four single-term ways, or None each:
    hi refs >= N, hi live <= L, lo refs <= N, lo live >= L (the other terms held)."""
    out = {}
    n, L, s, p = hi
    out["hi_refs"] = next((k for k in range(n, 4 * n + 64) if outranks((k, L, s, p), lo)), None)
    out["hi_live"] = next((k for k in range(L, 0, -1) if outranks((n, k, s, p), lo)), None)
    n2, L2, s2, p2 = lo
    out["lo_refs"] = next((k for k in range(n2, 0, -1) if outranks(hi, (k, L2, s2, p2))), None)
    out["lo_live"] = next((k for k in range(L2, 40 * L2 + 4000) if outranks(hi, (n2, k, s2, p2))), None)
    return out


def cost(th, hi, lo):
    """(cheapest single-term delta description, score) - refs deltas count 1 each, live deltas 1 per 8 insns."""
    opts = []
    if th["hi_refs"] is not None:
        opts.append((th["hi_refs"] - hi[0], "refs", "hi"))
    if th["hi_live"] is not None:
        opts.append(((hi[1] - th["hi_live"]) / 8.0, "live", "hi"))
    if th["lo_refs"] is not None:
        opts.append((lo[0] - th["lo_refs"], "refs", "lo"))
    if th["lo_live"] is not None:
        opts.append(((th["lo_live"] - lo[1]) / 8.0, "live", "lo"))
    return min(opts) if opts else (99.0, "-", "-")


# ------------------------------------------------------------------------------------------ reading

def parse_insn_regs(lreg, first):
    """{uid: (pseudos, hard regs)} mentioned by each insn of the .lreg RTL (pseudos not yet renumbered)."""
    heads = [(m.start(), int(m.group(1))) for m in INSN.finditer(lreg)] + [(len(lreg), None)]
    out = {}
    for (a, uid), (b, _) in zip(heads, heads[1:]):
        body = lreg[a:b]
        body = body.split("(expr_list", 1)[0]          # notes (REG_DEAD ...) are not operands
        regs = [int(x) for x in REG.findall(body)]
        out[uid] = ({r for r in regs if r >= first}, {r for r in regs if r < first})
    return out


def block_of(note):
    m = re.search(r"in block (\d+)", note or "")
    return int(m.group(1)) if m else None


def size_of(note):
    m = re.search(r"(\d+) bytes", note or "")
    return max(1, (int(m.group(1)) + 3) // 4) if m else 1


SAVE = re.compile(r"^(sw|lw) (s[0-8]|fp|ra),-?\d+\(sp\)$")


def vkey(line):
    """`retailmap.colour_key` + callee-save slots masked: `sw s4,64(sp)` and `sw s3,60(sp)` are the same
    prologue word under another colour (the slot follows the register number)."""
    line = line.strip()
    m = SAVE.match(line)
    if m:
        return m.group(1) + " SAVE"
    return RM.colour_key(line)


def listing_votes(rows, asm, uid_regs, disp):
    """{pseudo: Counter(retail reg)} from the aligned scorer listing, plus the uid map coverage."""
    gen = [(i, g) for i, g, _ in rows if g]
    gt = dict(gen)
    rt = {i: t for i, _, t in rows if t}
    by_uid, by_gen, cov = RM.uid_map(asm, gen)
    # Pair words on the COLOUR key (allocatable registers anonymised), not on text: `retailmap.align` pairs an
    # identical-text word elsewhere as "moved", and on a rotation the identical text is ANOTHER pseudo's word
    # (80921B2C: gen `addu v0,v0,s4` (x) paired with retail's `addu v0,v0,s4` (y)).  Equal-length replace
    # hunks are paired one to one (an opcode change inside an aligned run).
    ret = [(i, t) for i, _, t in rows if t]
    sm = difflib.SequenceMatcher(None, [vkey(t) for _, t in gen], [vkey(t) for _, t in ret], autojunk=False)
    pair = {}
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal" or (tag == "replace" and i2 - i1 == j2 - j1):
            for k in range(i2 - i1):
                pair[gen[i1 + k][0]] = ret[j1 + k][0]
    obs = collections.defaultdict(list)            # uid -> [(gen reg, retail reg or None)]
    for g, u in by_gen.items():
        r = pair.get(g)
        if r is None or r not in rt:
            continue
        a, b = TOK.split(gt[g].strip()), TOK.split(rt[r].strip())
        if len(a) != len(b) or a[0] != b[0]:
            continue
        for x, y in zip(a[1:], b[1:]):
            if x in REGNUM:
                obs[u].append((REGNUM[x], REGNUM.get(y)))
    votes = collections.defaultdict(collections.Counter)
    for u, (ps, hs) in uid_regs.items():
        if u not in obs:
            continue
        for p in ps:
            h = disp.get(p)
            if h is None or h < 0:
                continue
            if h in hs or any(q != p and disp.get(q) == h for q in ps):
                continue                         # ambiguous: another operand shares the register
            for gr, rr in obs[u]:
                if gr == h and rr is not None:
                    votes[p][rr] += 1
    return votes, cov


def ref_registers(row, reftext, sim, fp):
    """{variable name: hard reg} of the reference text: its allocno/local dispositions + ASM_REG decls."""
    out = {}
    for name, reg in ASMREG.findall(reftext):
        n = REGNUM.get(reg) if not reg.isdigit() else int(reg)
        if n is not None:
            out[name] = n
    d = kitlib.dumps(row, reftext, want={"greg", "lreg"})
    if not d or d.get("error") or "greg" not in d:
        return out, False
    _order, disp = sim.parse_greg(d["greg"])
    dp = sim.decl_pseudos(reftext, fp)
    for name, p in ((dp or {}).get("map") or {}).items():
        if name not in out and disp.get(p) is not None and disp[p] >= 0:
            out[name] = disp[p]
    return out, True


# ------------------------------------------------------------------------------------------ analysis

def analyse(row, text, reftext=None, beam=6):
    """The whole analysis as a dict (see main() for the printout)."""
    kitlib.add_paths()
    if not (_HERE / "kitlib.py").is_file() and (_HERE.parents[1] / "alloc_sim.py").is_file():
        sys.path.insert(0, str(_HERE.parents[1]))                        # a lane patch copy: its own tools/alloc_sim.py
    import alloc_sim as sim                                              # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    cell = parse_cfg(row["cfg"])[0]
    fp = sim.FIRST.get(cell)
    if fp is None:
        return {"error": "no FIRST_PSEUDO_REGISTER for cell %s (2.91.66/2.95.2 are not modelled)" % cell}
    d = kitlib.dumps(row, text, want={"greg", "lreg"}, asm_names=True)
    if d is None or d.get("error"):
        return {"error": "does not build: %s" % ((d or {}).get("error") or "")[-300:]}
    order, disp = sim.parse_greg(d["greg"])
    stats = sim.parse_lreg(d["lreg"])
    conf, pref = sim.parse_conflicts(d["greg"], fp)
    rd = {"order": order, "stats": stats, "first": fp, "lreg": d["lreg"], "sets": sim.set_counts(d["lreg"], fp)}
    dbl = sim.doubled(rd)
    dp = sim.decl_pseudos(text, fp)
    names = {v: k for k, v in ((dp or {}).get("map") or {}).items()}
    uid_regs = parse_insn_regs(d["lreg"], fp)

    v = kitlib.score_at(row, text, diff=True)
    rows = RM.scorer_rows(v.get("text"))
    exact = bool(v.get("exact"))
    mt = re.search(r"TOTAL\s+(\d+)", v.get("text") or "")
    total = 0 if exact else (v.get("total") if v.get("total") is not None else int(mt.group(1)) if mt else None)
    votes, cov = (listing_votes(rows, d["asm"], uid_regs, disp) if rows else ({}, (0, 0, 0)))

    ref, ref_ok = ({}, False)
    if reftext is not None:
        ref, ref_ok = ref_registers(row, reftext, sim, fp)

    pins_in_text = {REGNUM.get(r) if not r.isdigit() else int(r): n for n, r in ASMREG.findall(text)}

    def info(p):
        st = stats.get(p, {})
        return {"pseudo": p, "name": names.get(p, ""), "refs": st.get("n_refs", 0), "live": st.get("live_length", -1),
                "calls": st.get("calls_crossed", 0), "size": size_of(st.get("note")), "block": block_of(st.get("note")),
                "doubled": bool(dbl.get(p)), "got": disp.get(p)}

    allp = sorted(set(order) | {p for p in disp if p >= fp})
    table = {}
    for p in allp:
        it = info(p)
        it["global"] = p in order
        it["prio"] = prio(it["refs"], it["live"], it["size"])
        vc = votes.get(p) or collections.Counter()
        tot = sum(vc.values())
        it["votes"] = dict((rname(k), c) for k, c in vc.most_common())
        retail, src = None, "-"
        if exact:
            retail, src = it["got"], "exact"
        elif tot:
            top, c = vc.most_common(1)[0]
            if c * 10 >= 6 * tot:
                retail, src = top, "listing %d/%d" % (c, tot)
            else:
                src = "split %s" % " ".join("%s:%d" % (rname(k), n) for k, n in vc.most_common(3))
        it["ref"] = ref.get(it["name"]) if it["name"] else None
        if retail is None and it["ref"] is not None:
            retail, src = it["ref"], "ref"
        it["retail"], it["src"] = retail, src
        table[p] = it

    # verdicts
    for p, it in table.items():
        h, r = it["got"], it["retail"]
        if r is None:
            it["verdict"] = "?"
        elif h is not None and h == r:
            it["verdict"] = "ok"
        elif h is None or h < 0:
            it["verdict"] = "SPILLED"
        elif not it["global"]:
            it["verdict"] = "LOCAL"
        elif r in conf.get(p, (set(), set()))[1]:
            it["verdict"] = "BLOCKED"
            holders = [q for q, t in table.items() if q != p and not t["global"] and t["got"] == r]
            it["blockers"] = holders
            it["blocker_pin"] = pins_in_text.get(r)
        elif sim.CALL_USED[r] and it["calls"] > 0:
            it["verdict"] = "CLASS"
        else:
            it["verdict"] = "ORDER"

    # simulation fidelity + single-mover search
    simd = sim.allocate(order, stats, conf, pref, fp)
    agree = [p for p in order if simd.get(p) == disp.get(p)]
    targets = [p for p in order if p in agree and table[p]["verdict"] in ("ok", "ORDER")]
    goal = {p: table[p]["retail"] for p in targets}
    order_mis = [p for p in targets if table[p]["verdict"] == "ORDER"]

    def score(o):
        s = sim.allocate(o, stats, conf, pref, fp)
        return sum(1 for p, r in goal.items() if s.get(p) == r)

    base = score(order)
    sols, best = [], (base, None)
    tried = {}
    if order_mis:
        for x in order:
            wo = [q for q in order if q != x]
            j0 = order.index(x)
            good = []
            for j in range(len(wo) + 1):
                if j == j0:
                    continue
                o = wo[:j] + [x] + wo[j:]
                sc = score(o)
                tried[(x, j)] = sc
                if sc > best[0]:
                    best = (sc, (x, j))
                if sc == len(goal):
                    good.append(j)
            if good:
                s1 = mover_solution(x, wo, j0, good, table)
                if len(s1["crossed"]) == 1 and any(len(o["crossed"]) == 1 and {o["hi"], o["lo"]} == {s1["hi"], s1["lo"]}
                                                   for o in sols):
                    continue                     # the same swap seen from its partner
                sols.append(s1)
    two = []
    if order_mis and not sols:
        firsts = sorted(tried.items(), key=lambda kv: -kv[1])[:beam]
        for (x, j), sc in firsts:
            wo = [q for q in order if q != x]
            o1 = wo[:j] + [x] + wo[j:]
            for y in order:
                if y == x:
                    continue
                wo2 = [q for q in o1 if q != y]
                for k in range(len(wo2) + 1):
                    o2 = wo2[:k] + [y] + wo2[k:]
                    if o2 == o1:
                        continue
                    s2 = score(o2)
                    if s2 == len(goal):
                        two.append({"first": mover_solution(x, wo, order.index(x), [j], table),
                                    "second": mover_solution(y, wo2, o1.index(y), [k], table)})
                        break
                if len(two) >= 4:
                    break
            if len(two) >= 4:
                break

    counts = collections.Counter(it["verdict"] for it in table.values())
    unmapped_global = sum(1 for p in order if table[p]["verdict"] == "?")
    one_vote = sum(1 for it in table.values() if it["verdict"] not in ("ok", "?") and it["src"].endswith(" 1/1"))
    cheapest = min((s for s in sols), key=lambda s: s["cost"][0], default=None)
    return {"row": row["id"], "cfg": row["cfg"], "exact": exact, "total": total,
            "coverage": cov, "ref_ok": ref_ok, "table": table, "order": order,
            "sim_agree": (len(agree), len(order)), "goal": len(goal), "base_score": base,
            "best": best, "solutions": sols, "two_movers": two, "counts": dict(counts),
            "unmapped_global": unmapped_global, "one_vote": one_vote,
            "cheapest": cheapest}


def mover_solution(x, wo, j0, good, table):
    """Inequalities for moving allocno x (currently slot j0 of `wo`, the order without x) into slots `good`."""
    # the contiguous run of good slots nearest the current position
    runs, cur = [], [good[0]]
    for j in good[1:]:
        if j == cur[-1] + 1:
            cur.append(j)
        else:
            runs.append(cur)
            cur = [j]
    runs.append(cur)
    run = min(runs, key=lambda r: min(abs(j - j0) for j in r))
    j1, j2 = run[0], run[-1]

    def key(p):
        t = table[p]
        return (t["refs"], t["live"], t["size"], p)

    ineq = []
    if j1 > j0:                                   # x goes down: the lowest crossed allocno must outrank x
        crossed = wo[j0:j1]
        h = wo[j1 - 1]
        ineq.append(("below", h, x, thresholds(key(h), key(x))))
        if j2 < len(wo):
            ineq.append(("keep-above", x, wo[j2], None))
    else:                                         # x goes up: x must outrank the highest crossed allocno
        crossed = wo[j2:j0]
        h = wo[j2]
        ineq.append(("above", x, h, thresholds(key(x), key(h))))
        if j1 > 0:
            ineq.append(("keep-below", wo[j1 - 1], x, None))
    kind, hi, lo, th = ineq[0]
    c = cost(th, key(hi), key(lo))
    return {"mover": x, "slots": (j1, j2), "from": j0, "crossed": crossed, "hi": hi, "lo": lo,
            "th": th, "cost": c, "keep": ineq[1:] and ineq[1][:3]}


# ------------------------------------------------------------------------------------------ printing

def label(t, p):
    n = t[p]["name"]
    return "%d%s" % (p, " (%s)" % n if n else "")


def fmt_ineq(t, s):
    hi, lo, th = s["hi"], s["lo"], s["th"]
    H, L = t[hi], t[lo]
    parts = []
    if th["hi_refs"] is not None:
        parts.append("%d refs >= %d at live %d" % (hi, th["hi_refs"], H["live"]))
    if th["hi_live"] is not None:
        parts.append("%d live <= %d at refs %d" % (hi, th["hi_live"], H["refs"]))
    if th["lo_refs"] is not None:
        parts.append("%d refs <= %d at live %d" % (lo, th["lo_refs"], L["live"]))
    if th["lo_live"] is not None:
        parts.append("%d live >= %d at refs %d" % (lo, th["lo_live"], L["refs"]))
    head = "%s must outrank %s  [prio %d (%d/%d, fl %d) vs %d (%d/%d, fl %d)]" % (
        label(t, hi), label(t, lo), H["prio"], H["refs"], H["live"], floor_log2(H["refs"]),
        L["prio"], L["refs"], L["live"], floor_log2(L["refs"]))
    return head, parts


def doubled_note(t, p):
    it = t[p]
    if not it["doubled"]:
        return None
    half = max(1, it["live"] // 2)
    return ("%s is live-DOUBLED (update_equiv_regs: single set + REG_EQUIV): undoubled it is live %d, prio %d "
            "(before a second set's own refs/live)"
            % (label(t, p), half, prio(it["refs"], half, it["size"])))


def render(res, show_all=False):
    out = []
    t = res["table"]
    out.append("# alloc_need %s at %s   scorer: %s" % (res["row"], res["cfg"],
               "EXACT" if res["exact"] else "total %s" % res["total"]))
    placed, pred, gen = res["coverage"]
    out.append("# retail map: uid map placed %d of %d predicted words on %d generated; reference cross-check %s"
               % (placed, pred, gen, "on" if res["ref_ok"] else "off"))
    head = ["pseudo", "variable", "refs", "live", "calls", "prio", "dbl", "got", "retail", "evidence", "ref", "verdict"]
    body = []
    for p in res["order"] + sorted(q for q in t if q not in res["order"]):
        it = t[p]
        weak = sum(it["votes"].values()) < 3           # a ref disagreement matters only against thin listing evidence
        if not show_all and it["verdict"] in ("ok", "?") and not (weak and it["ref"] is not None
                                                                  and it["retail"] is not None
                                                                  and it["ref"] != it["retail"]):
            continue
        body.append([p if it["global"] else "%d/b%s" % (p, it["block"]), it["name"], it["refs"], it["live"],
                     it["calls"], it["prio"], "D" if it["doubled"] else "", rname(it["got"]), rname(it["retail"]),
                     it["src"], rname(it["ref"]) if it["ref"] is not None else "",
                     it["verdict"] + ("" if it["ref"] is None or it["retail"] is None or it["ref"] == it["retail"]
                                      else " (ref disagrees)")])
    out.append(kitlib.fmt_table(head, body) if body else "(every mapped pseudo already has retail's register)")
    out.append("verdicts: " + ", ".join("%s %d" % kv for kv in sorted(res["counts"].items())))
    for p, it in t.items():
        if it["verdict"] == "BLOCKED":
            bl = ", ".join(label(t, q) + "/b%s" % t[q]["block"] for q in it.get("blockers", [])[:8]) or "none named"
            pin = it.get("blocker_pin")
            argreg = 2 <= it["retail"] <= 7
            out.append("BLOCKED %s: retail %s is a HARD conflict here%s; local qtys in %s anywhere in the function "
                       "(not filtered by overlap): %s%s.  Lever: make the holder global (a use in a second block / "
                       "function scope) or keep it out of %s's life; retail's %s is not a priority question."
                       % (label(t, p), rname(it["retail"]),
                          " (still pinned to %s in this text)" % pin if pin else "", rname(it["retail"]), bl,
                          "; or an explicit %s set (call argument / return value) inside its life - which call's "
                          "argument set or return lands inside it is the question" % rname(it["retail"])
                          if argreg else "", label(t, p), rname(it["retail"])))
        elif it["verdict"] == "CLASS":
            out.append("CLASS %s: retail keeps it in call-clobbered %s but it crosses %d call(s) here: retail's value "
                       "must not live across a call (move the set/use across the call, or split the variable at it)."
                       % (label(t, p), rname(it["retail"]), it["calls"]))
        elif it["verdict"] == "LOCAL":
            comp = [q for q, u in t.items() if q != p and not u["global"] and u["block"] == it["block"]
                    and u["got"] == it["retail"]]
            out.append("LOCAL %s (block %s, %d/%d approx qty prio %d): retail %s, held here by %s.  local-alloc "
                       "QTY_CMP_PRI uses qty_death-qty_birth (not dumped): numbers approximate."
                       % (label(t, p), it["block"], it["refs"], it["live"], it["prio"], rname(it["retail"]),
                          ", ".join("%s %d/%d=%d" % (label(t, q), t[q]["refs"], t[q]["live"], t[q]["prio"])
                                    for q in comp) or "nobody local"))
    a, n = res["sim_agree"]
    out.append("# find_reg model: reproduces %d of %d allocnos of the dump; %d targets (modelled + retail known), "
               "%d already right in this order" % (a, n, res["goal"], res["base_score"]))
    sols = sorted(res["solutions"], key=lambda s: s["cost"][0])
    if not sols and not res["two_movers"]:
        if any(it["verdict"] == "ORDER" for it in t.values()):
            b = res["best"]
            out.append("NO single- or two-mover reorder reproduces retail (best %d/%d%s): the mis-colouring is not "
                       "one priority flip" % (b[0], res["goal"], " by moving %s to slot %d" % (label(t, b[1][0]), b[1][1])
                                              if b[1] else ""))
        else:
            out.append("no ORDER problem to invert")
    for i, s in enumerate(sols):
        head, parts = fmt_ineq(t, s)
        out.append("")
        out.append("SOLUTION %d: %s %s past %d allocno(s) [%s]  (cheapest: %s)"
                   % (i + 1, label(t, s["mover"]), "down" if s["slots"][0] > s["from"] else "up", len(s["crossed"]),
                      " ".join(str(q) for q in s["crossed"]), cheapest_text(t, s)))
        out.append("  " + head)
        for ptxt in parts:
            out.append("    or " + ptxt)
        if s["keep"]:
            hi, lo = s["keep"][1], s["keep"][2]
            out.append("  and must still sort %s %s (prio %d vs %d)" % (
                "above" if hi == s["mover"] else "below", label(t, lo if hi == s["mover"] else hi),
                t[hi]["prio"], t[lo]["prio"]))
        for p in (s["hi"], s["lo"]):
            dn = doubled_note(t, p)
            if dn:
                out.append("  note: " + dn)
        who = "hi" if s["cost"][2] == "hi" else "lo"
        term = s["cost"][1]
        if term in ("refs", "live"):
            want = {("hi", "refs"): "refs+", ("hi", "live"): "live-", ("lo", "refs"): "refs-",
                    ("lo", "live"): "live+"}[(who, term)]
            out.append("  lever (%s of %s): %s" % (want, label(t, s[who]), LEVERS[want]))
    for k, tm in enumerate(res["two_movers"]):
        out.append("")
        out.append("TWO-MOVER %d:" % (k + 1))
        for s in (tm["first"], tm["second"]):
            head, parts = fmt_ineq(t, s)
            out.append("  " + head + (": " + " | ".join(parts) if parts else ""))
    out.append("")
    out.append("inequalities are NECESSARY, not sufficient: a source change that moves one term also moves others "
               "(re-run this tool on the candidate that meets it).")
    return "\n".join(out)


def cheapest_text(t, s):
    """The cheapest single-term way of one solution, as `88 (x) live >= 129 (now 98)`."""
    _c, term, who = s["cost"]
    p = s[who]
    v = s["th"]["%s_%s" % (who, term)]
    op = {("hi", "refs"): ">=", ("hi", "live"): "<=", ("lo", "refs"): "<=", ("lo", "live"): ">="}.get((who, term), "?")
    return "%s %s %s %s (now %s)" % (label(t, p), term, op, v, t[p][term])


def summary(res):
    """One line for batch tables."""
    if res.get("error"):
        return "ERROR " + res["error"]
    c = res["counts"]
    s = res["cheapest"]
    t = res["table"]
    ch = "-"
    if s:
        ch = "%s over %s: %s" % (label(t, s["hi"]), label(t, s["lo"]), cheapest_text(t, s))
    return ("ORDER %d BLOCKED %d CLASS %d LOCAL %d SPILLED %d | unmapped global %d, one-vote verdicts %d | "
            "single-mover solutions %d, two-mover %d | cheapest %s"
            % (c.get("ORDER", 0), c.get("BLOCKED", 0), c.get("CLASS", 0), c.get("LOCAL", 0), c.get("SPILLED", 0),
               res["unmapped_global"], res["one_vote"], len(res["solutions"]), len(res["two_movers"]), ch))


def jsonable(res):
    def conv(o):
        if isinstance(o, dict):
            return {str(k): conv(v) for k, v in o.items()}
        if isinstance(o, (list, tuple)):
            return [conv(v) for v in o]
        if isinstance(o, set):
            return sorted(o)
        return o
    return conv(res)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("text", help="candidate .c, or 'erased' / 'pinned'")
    ap.add_argument("--ref", default="pinned", help="cross-check text: 'pinned' (default), a file, or 'none'")
    ap.add_argument("--cfg", help="compile and score at this cfg (no ledger write)")
    ap.add_argument("--json", help="also write the analysis here (inside the lane)")
    ap.add_argument("--all", action="store_true", help="print every pseudo, not only the mis-coloured")
    a = ap.parse_args(argv)
    lane = kitlib.bootstrap()
    row = kitlib.row_at_cfg(kitlib.row_of(a.row_id), a.cfg)
    base = kitlib.base_text(row, lane)
    if a.text in ("pinned", "base"):
        text = base
    elif a.text == "erased":
        text = kitlib.erased_text(base)
    else:
        p = Path(a.text)
        if not p.is_file():
            raise SystemExit("alloc_need: %r is neither 'pinned', 'erased' nor a file" % a.text)
        text = p.read_text(errors="replace")
    reftext = None if a.ref == "none" else base if a.ref == "pinned" else Path(a.ref).read_text(errors="replace")
    res = analyse(row, text, reftext)
    if res.get("error"):
        raise SystemExit("alloc_need: " + res["error"])
    print(render(res, a.all))
    print("SUMMARY " + summary(res))
    if a.json:
        Path(a.json).write_text(json.dumps(jsonable(res), indent=1, sort_keys=True))


if __name__ == "__main__":
    main()
