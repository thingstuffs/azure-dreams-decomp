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
     LOCAL     a block-local qty (local-alloc.c, `in block N`): explained by `lreg_explain.py`, which replays
               block_alloc on the `.lreg` insn stream (qty birth/death, suggestions, the qty order; checked
               against the dump's `;; Register N in R.`) and prints who held retail's register and the
               PRIORITY / GEOMETRY change that gives it.
     ORDER     everything else: an allocno_compare order question - the search below.
     PREF      (2.7.2-cdk / 2.8.x) an ORDER pseudo whose register a hard-register PREFERENCE decided: a copy/plain
               preference overrode the scan, or pass 0 skipped retail's register because a lower-priority
               conflicting allocno prefers it (regs_someone_prefers).  The `# preference replay` block (prefs.py,
               tools/alloc_prefs.py: global.c replayed exactly) names the insn / merge chain behind it and the single
               preference changes that give retail's registers; on such rows the search below runs on that exact
               model.  Rows without a preference effect print exactly what they printed before.
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
    "refs+": "more refs: flow weights by loop_depth (base/goto depth 1; one real loop 2, nested loop 3); "
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


def ref_depths(flow):
    """Operand occurrences by flow loop-note depth (not an exact reg_n_refs replay).

    Flow weights reads, sets and address uses with different counting rules.
    Keep this provenance separate from the compiler's authoritative ref count.
    """
    depth = 1
    out = collections.defaultdict(collections.Counter)
    parts = re.split(r'(?=^\((?:note|insn|call_insn|jump_insn)\b)', flow, flags=re.M)
    for part in parts:
        if part.startswith('(note '):
            if 'NOTE_INSN_LOOP_BEG' in part:
                depth += 1
            elif 'NOTE_INSN_LOOP_END' in part:
                depth = max(1, depth - 1)
        elif re.match(r'^\((?:insn|call_insn|jump_insn) ', part):
            body = part.split('(expr_list', 1)[0].split('(insn_list', 1)[0]
            for reg in REG.findall(body):
                out[int(reg)][depth] += 1
    return dict(out)


def loop_threshold(it, target):
    """Conditional one-added-loop estimate, only when every observed ref shares a depth."""
    hist = it.get('ref_depths', {})
    depths = ', '.join('%s:%s' % (k, v) for k, v in sorted(hist.items())) or 'unknown'
    head = 'ref operand depths (depth:occurrences) %s' % depths
    if not hist or len(hist) != 1:
        return head + '; real-loop threshold UNKNOWN (missing or mixed-depth refs; select the body and recompile)'
    depth = int(next(iter(hist)))
    estimate = it['refs'] * (depth + 1) / depth
    return head + ('; one real loop around ALL these refs: %.1f weighted refs vs threshold %s -> %s '
           '(conditional, fixed live/conflicts; recompile)' % (estimate, target, 'reaches' if estimate >= target else 'short'))


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

def preference_effects(d, fp, names, dp, cflags, table, order, stats, conf, pref, sim):
    """The exact global.c replay (alloc_prefs.Problem/Replay, prefs.Explainer) and whether this row HAS a preference
    effect.  It fires on (a) a mis-coloured allocno whose register a copy/plain preference chose over the scan,
    (b) a mis-coloured allocno whose retail register the pass-0 scan skipped because a lower-priority conflicting
    allocno prefers it (regs_someone_prefers), or (c) any allocno where the exact replay and `alloc_sim.allocate`
    disagree on a GR_REGS allocno the replay puts in a GPR (LO/HI-class allocnos and reload-retried ones, which
    alloc_sim never modelled, do not count).  None for cells other than FIRST_PSEUDO_REGISTER 76 (2.7.2-cdk, 2.8.x)
    or when the dumps lack .flow."""
    if fp != 76 or not d.get("flow"):
        return None
    import alloc_prefs as AP                                              # noqa: E402
    import prefs as PX                                                    # noqa: E402
    pb = AP.Problem(d["lreg"], d["greg"], d["flow"], (dp or {}).get("fname"),
                    caller_saves="-fno-caller-saves" not in cflags)
    if sorted(pb.order) != sorted(order):
        return None                                                       # another function's section: do not guess
    ex = PX.Explainer(pb, names)
    rp = ex.base
    old = sim.allocate(order, stats, conf, pref, fp)
    # (c) GPR allocnos only, and against alloc_sim run WITHOUT the allocnos global.c keeps out of the GPRs (LO/HI
    # class): alloc_sim cannot place those (it hands them a GPR and displaces the next allocno) and does not model
    # reload's retry_global_alloc - neither is a preference effect, and neither may change the output
    gpr = [p for p in order if 0 <= rp.result.get(p, -1) < 32]
    old_gpr = sim.allocate(gpr, stats, conf, pref, fp)
    differs = [p for p in gpr if old_gpr.get(p) != rp.result.get(p)
               and pb.stats.get(p, {}).get("class", "GR_REGS") == "GR_REGS"]
    effects = {}
    for p, it in table.items():
        if not it["global"] or it["retail"] is None or it["got"] is None or it["got"] == it["retail"]:
            continue
        tr = rp.trace.get(p) or {}
        if rp.result.get(p) != it["got"] or "skipped" in tr:
            continue                                                      # not reproduced (reload retry): no claim
        why = []
        if tr.get("how") in ("copy-preference", "preference") and tr.get("scan") != rp.result.get(p):
            why.append("override")
        if tr.get("pass") == 0 and it["retail"] in tr.get("someone", ()):
            why.append("someone")
        if why:
            effects[p] = why
    # (c) counts only where there is something to search: a mis-coloured global allocno
    mis_global = any(it["global"] and it["verdict"] == "ORDER" for it in table.values())
    return {"ex": ex, "pb": pb, "fired": bool(effects or (differs and mis_global)), "effects": effects,
            "differs": differs,
            "old_agree": sum(1 for p in order if old.get(p) == table.get(p, {}).get("got")),
            "replay": lambda o: AP.Replay(pb, order=o, light=True).result}


def analyse(row, text, reftext=None, beam=6, explain_local=True, retail_set=None, prefs=True):
    """The whole analysis as a dict (see main() for the printout).  `explain_local=False` skips the
    lreg_explain replay (lreg_explain itself calls analyse() for the retail registers).  `prefs=False` skips the
    exact preference replay (prefs.py), which otherwise speaks only on rows with a preference effect."""
    kitlib.add_paths()
    if not (_HERE / "kitlib.py").is_file() and (_HERE.parents[1] / "alloc_sim.py").is_file():
        sys.path.insert(0, str(_HERE.parents[1]))                        # a lane patch copy: its own tools/alloc_sim.py
    import alloc_sim as sim                                              # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    cell, cflags = parse_cfg(row["cfg"])
    fp = sim.FIRST.get(cell)
    if fp is None:
        return {"error": "no FIRST_PSEUDO_REGISTER for cell %s (2.91.66/2.95.2 are not modelled)" % cell}
    d = kitlib.dumps(row, text, want={"greg", "lreg", "flow"}, asm_names=True)
    if d is None or d.get("error"):
        return {"error": "does not build: %s" % ((d or {}).get("error") or "")[-300:]}
    order, disp = sim.parse_greg(d["greg"])
    stats = sim.parse_lreg(d["lreg"])
    conf, pref = sim.parse_conflicts(d["greg"], fp)
    rd = {"order": order, "stats": stats, "first": fp, "lreg": d["lreg"], "sets": sim.set_counts(d["lreg"], fp)}
    dbl = sim.doubled(rd)
    dp = sim.decl_pseudos(text, fp)
    names = {v: k for k, v in ((dp or {}).get("map") or {}).items()}
    depths = ref_depths(d['flow'])
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
                "doubled": bool(dbl.get(p)), "got": disp.get(p), "ref_depths": dict(depths.get(p, {}))}

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
        hand = (retail_set or {}).get(p, (retail_set or {}).get(it["name"]) if it["name"] else None)
        if hand is not None:
            retail, src = hand, "hand"
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

    # PREFERENCES (global.c set_preference / expand_preferences / prune_preferences / find_reg, exact replay):
    # on a row with a preference effect the exact model replaces alloc_sim.allocate in the search below
    pinfo, pref_err = None, None
    if prefs:
        try:
            pinfo = preference_effects(d, fp, names, dp, cflags, table, order, stats, conf, pref, sim)
        except Exception as e:                                           # the replay must never cost the verdicts
            pref_err = "%s: %s" % (type(e).__name__, e)
    fired = bool(pinfo and pinfo["fired"])
    if fired:
        for p in pinfo["effects"]:
            if table[p]["verdict"] == "ORDER":
                table[p]["verdict"] = "PREF"
        allocate = pinfo["replay"]
    else:
        def allocate(o):
            return sim.allocate(o, stats, conf, pref, fp)

    # simulation fidelity + single-mover search
    simd = allocate(order)
    agree = [p for p in order if simd.get(p) == disp.get(p)]
    targets = [p for p in order if p in agree and table[p]["verdict"] in ("ok", "ORDER", "PREF")]
    goal = {p: table[p]["retail"] for p in targets}
    order_mis = [p for p in targets if table[p]["verdict"] in ("ORDER", "PREF")]

    def score(o):
        s = allocate(o)
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

    # LOCAL / BLOCKED: the local-alloc replay (lreg_explain.py) - who held retail's register, and what would flip it
    local_expl, local_fid, local_err = {}, None, None
    if explain_local and any(it["verdict"] in ("LOCAL", "BLOCKED") for it in table.values()):
        try:
            import lreg_explain as LX                                    # noqa: E402
            want = {p for p, it in table.items() if it["verdict"] == "LOCAL"}
            retail_map = {p: it["retail"] for p, it in table.items() if it["retail"] is not None}
            lx = LX.explain(d["lreg"], fp, cell, retail=retail_map, names=names, text=text, want=want,
                            caller_saves="-fno-caller-saves" not in cflags, search=bool(want))
            local_fid = lx["fidelity"]
            local_expl = LX.summary_lines(lx, names, want)
            for p, it in table.items():
                if it["verdict"] == "BLOCKED":
                    it["holders"] = [t for _b, _k, t in LX.global_holders(lx["fn"], lx["runs"], p, it["retail"],
                                                                         names)]
        except Exception as e:                                           # the explainer must never cost the verdicts
            local_err = "%s: %s" % (type(e).__name__, e)
    pref_out = None
    if fired:
        ex = pinfo["ex"]
        mis = {p: table[p]["retail"] for p in order_mis}
        explain = sorted(set(pinfo["effects"]) | set(mis), key=order.index)
        pref_out = {"effects": pinfo["effects"], "differs": pinfo["differs"], "old_agree": pinfo["old_agree"],
                    "lines": {p: ex.decision(p) + ["  retail %s: %s" % (rname(table[p]["retail"]),
                                                                       ex.blocked(p, table[p]["retail"]))]
                              for p in explain},
                    "changes": [ex.cf_text(c) for c in ex.counterfactuals(mis, keep=goal)] if mis else [],
                    "n_targets": len(mis)}
    counts = collections.Counter(it["verdict"] for it in table.values())
    unmapped_global = sum(1 for p in order if table[p]["verdict"] == "?")
    one_vote = sum(1 for it in table.values() if it["verdict"] not in ("ok", "?") and it["src"].endswith(" 1/1"))
    cheapest = min((s for s in sols), key=lambda s: s["cost"][0], default=None)
    return {"row": row["id"], "cfg": row["cfg"], "exact": exact, "total": total,
            "coverage": cov, "ref_ok": ref_ok, "table": table, "order": order,
            "sim_agree": (len(agree), len(order)), "goal": len(goal), "base_score": base,
            "best": best, "solutions": sols, "two_movers": two, "counts": dict(counts),
            "unmapped_global": unmapped_global, "one_vote": one_vote,
            "cheapest": cheapest, "local": local_expl, "local_fidelity": local_fid, "local_error": local_err,
            "prefs": pref_out, "prefs_error": pref_err}


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
    out.append('# flow.c:445-453,2122,2374: refs weighted by loop depth; base/goto loop = 1, '
               'real loop = 2, nested real loop = 3. Goto backedges alone add no loop notes.')
    placed, pred, gen = res["coverage"]
    out.append("# retail map: uid map placed %d of %d predicted words on %d generated; reference cross-check %s"
               % (placed, pred, gen, "on" if res["ref_ok"] else "off"))
    head = ["pseudo", "variable", "refs", "ref depths", "live", "calls", "prio", "dbl", "got", "retail", "evidence", "ref", "verdict"]
    body = []
    for p in res["order"] + sorted(q for q in t if q not in res["order"]):
        it = t[p]
        weak = sum(it["votes"].values()) < 3           # a ref disagreement matters only against thin listing evidence
        if not show_all and it["verdict"] in ("ok", "?") and not (weak and it["ref"] is not None
                                                                  and it["retail"] is not None
                                                                  and it["ref"] != it["retail"]):
            continue
        body.append([p if it["global"] else "%d/b%s" % (p, it["block"]), it["name"], it["refs"],
                     ','.join('%s:%s' % (depth,n) for depth,n in sorted(it.get('ref_depths',{}).items())) or '?', it["live"],
                     it["calls"], it["prio"], "D" if it["doubled"] else "", rname(it["got"]), rname(it["retail"]),
                     it["src"], rname(it["ref"]) if it["ref"] is not None else "",
                     it["verdict"] + ("" if it["ref"] is None or it["retail"] is None or it["ref"] == it["retail"]
                                      else " (ref disagrees)")])
    out.append(kitlib.fmt_table(head, body) if body else "(every mapped pseudo already has retail's register)")
    out.append("verdicts: " + ", ".join("%s %d" % kv for kv in sorted(res["counts"].items())))
    for p, it in t.items():
        if it["verdict"] == "BLOCKED":
            narrowed = False
            bl = ", ".join(label(t, q) + "/b%s" % t[q]["block"] for q in it.get("blockers", [])[:8]) or "none named"
            pin = it.get("blocker_pin")
            argreg = 2 <= it["retail"] <= 7
            out.append("BLOCKED %s: retail %s is a HARD conflict here%s; local qtys in %s %s: %s%s.  "
                       "Lever: make the holder global (a use in a second block / "
                       "function scope) or keep it out of %s's life; retail's %s is not a priority question."
                       % (label(t, p), rname(it["retail"]),
                          " (still pinned to %s in this text)" % pin if pin else "", rname(it["retail"]),
                          "in the blocks where it is live or mentioned (lreg_explain)" if narrowed
                          else "anywhere in the function (not filtered by overlap)", bl,
                          "; or an explicit %s set (call argument / return value) inside its life - which call's "
                          "argument set or return lands inside it is the question" % rname(it["retail"])
                          if argreg else "", label(t, p), rname(it["retail"])))
            if it.get("holders") is not None:
                out.append("  inside %s's life (lreg_explain; per block, local-alloc's index convention): %s" % (
                    label(t, p), "; ".join(it["holders"][:8]) if it["holders"] else
                    "no local qty or hard register holds %s - the conflict comes from another allocno's hard "
                    "register or a spill-class rule" % rname(it["retail"])))
        elif it["verdict"] == "CLASS":
            out.append("CLASS %s: retail keeps it in call-clobbered %s but it crosses %d call(s) here: retail's value "
                       "must not live across a call (move the set/use across the call, or split the variable at it)."
                       % (label(t, p), rname(it["retail"]), it["calls"]))
        elif it["verdict"] == "LOCAL" and p in (res.get("local") or {}):
            out.extend(res["local"][p])
        elif it["verdict"] == "LOCAL":
            comp = [q for q, u in t.items() if q != p and not u["global"] and u["block"] == it["block"]
                    and u["got"] == it["retail"]]
            out.append("LOCAL %s (block %s, %d/%d flow numbers, prio %d): retail %s, held here by %s.  lreg_explain "
                       "had no reproduced qty for it%s."
                       % (label(t, p), it["block"], it["refs"], it["live"], it["prio"], rname(it["retail"]),
                          ", ".join("%s %d/%d=%d" % (label(t, q), t[q]["refs"], t[q]["live"], t[q]["prio"])
                                    for q in comp) or "nobody local",
                          " (%s)" % res["local_error"] if res.get("local_error") else ""))
    if res.get("local_fidelity"):
        la, ln = res["local_fidelity"]
        out.append("# local-alloc replay (lreg_explain): reproduces %d of %d local pseudos" % (la, ln))
    pr = res.get("prefs")
    if pr:
        out.append("# preference replay (global.c set_preference/expand/prune/find_reg, exact; prefs.py): "
                   "alloc_sim.allocate reproduced %d of %d allocnos%s; preference-decided mis-colourings: %s"
                   % (pr["old_agree"], len(res["order"]), " (differs on %s)" % " ".join(map(str, pr["differs"][:8]))
                      if pr["differs"] else "", ", ".join("%s [%s]" % (label(t, p), "+".join(w))
                                                         for p, w in pr["effects"].items()) or "none"))
        for p, lines in pr["lines"].items():
            out.extend(("PREF " if t[p]["verdict"] == "PREF" and i == 0 else "  " if i == 0 else "") + ln
                       for i, ln in enumerate(lines))
        if pr["n_targets"]:
            out.append("# single preference changes that give retail's registers (event = one set_preference "
                       "insn or one expand merge; collateral = other allocnos that move):")
            out.extend("  " + c for c in pr["changes"]) if pr["changes"] else out.append(
                "  none: no single preference event removal (or added copy preference) does it - see the reorders")
    a, n = res["sim_agree"]
    out.append("# find_reg model%s: reproduces %d of %d allocnos of the dump; %d targets (modelled + retail known), "
               "%d already right in this order" % (" (exact preference replay)" if pr else "", a, n, res["goal"],
                                                   res["base_score"]))
    sols = sorted(res["solutions"], key=lambda s: s["cost"][0])
    if not sols and not res["two_movers"]:
        if any(it["verdict"] in ("ORDER", "PREF") for it in t.values()):
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
        if s['th'].get('hi_refs') is not None and s['th']['hi_refs'] > t[s['hi']]['refs']:
            out.append('  refs lever for %s: %s' % (label(t, s['hi']), loop_threshold(t[s['hi']], s['th']['hi_refs'])))
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
            if s['th'].get('hi_refs') is not None and s['th']['hi_refs'] > t[s['hi']]['refs']:
                out.append('  refs lever for %s: %s' % (label(t, s['hi']), loop_threshold(t[s['hi']], s['th']['hi_refs'])))
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
    lf = res.get("local_fidelity")
    lx = ""
    if res.get("local") is not None and c.get("LOCAL", 0):
        lx = " | LOCAL explained %d%s" % (len(res["local"]), " (local model %d/%d)" % tuple(lf) if lf else "")
    if res.get("prefs"):
        lx += " | PREF %d, preference changes %d" % (c.get("PREF", 0), len(res["prefs"]["changes"]))
    return ("ORDER %d BLOCKED %d CLASS %d LOCAL %d SPILLED %d | unmapped global %d, one-vote verdicts %d | "
            "single-mover solutions %d, two-mover %d | cheapest %s%s"
            % (c.get("ORDER", 0), c.get("BLOCKED", 0), c.get("CLASS", 0), c.get("LOCAL", 0), c.get("SPILLED", 0),
               res["unmapped_global"], res["one_vote"], len(res["solutions"]), len(res["two_movers"]), ch, lx))


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
    ap.add_argument("--no-prefs", action="store_true", help="skip the exact preference replay (prefs.py)")
    ap.add_argument("--retail-set", action="append", default=[], metavar="P=REG",
                    help="retail register of a pseudo or variable by hand (172=$v0, speed=v1; repeatable): for rows "
                         "whose candidate the scorer cannot score, from a lane's listing diff")
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
    hand = {}
    for item in a.retail_set:
        k, _, v = item.partition("=")
        v = v.strip().lstrip("$")
        reg = int(v) if v.isdigit() else REGNUM.get(v)
        if reg is None:
            raise SystemExit("alloc_need: --retail-set %r: need PSEUDO|VARIABLE=REG" % item)
        hand[int(k) if k.strip().isdigit() else k.strip()] = reg
    res = analyse(row, text, reftext, retail_set=hand, prefs=not a.no_prefs)
    if res.get("error"):
        raise SystemExit("alloc_need: " + res["error"])
    print(render(res, a.all))
    print("SUMMARY " + summary(res))
    if a.json:
        Path(a.json).write_text(json.dumps(jsonable(res), indent=1, sort_keys=True))


if __name__ == "__main__":
    main()
