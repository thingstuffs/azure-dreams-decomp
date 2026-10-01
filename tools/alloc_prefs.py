#!/usr/bin/env python3
"""alloc_prefs.py - gcc 2.7.2-cdk / 2.8.x global.c replayed EXACTLY from the -da dumps, preferences included.

`alloc_sim.allocate` hands registers out in allocno order and uses the greg dump's `;; N preferences:` line as if
it were the whole preference story.  It is not: that line is hard_reg_preferences AFTER prune_preferences, while
find_reg decides with three sets the dump never prints (global.c of toolchain/gcc-src/2.7.2-cdk):

  set_preference (1545)    every SET whose source - or the source's first operand (plus, mem address, extend,
                           shift, ...) - and destination are one hard register and one global pseudo:
                           hard_reg_preferences, + hard_reg_copy_preferences when the source is the bare register
                           (a COPY), + hard_reg_full_preferences.  A local-alloc'd pseudo counts as its hard register.
  expand_preferences (783) in insn order, an insn whose single_set sets allocno A1 while allocno A2 DIES in it
                           (REG_DEAD) and A1/A2 do not conflict: their preference sets are OR-ed into each other
                           (copy sets too when the insn is the bare copy A1 = A2).  A later merge sees what earlier
                           merges brought, so the insn ORDER matters.
  prune_preferences (836)  per allocno, lowest priority first: drop conflicting / fixed (call-used when it crosses
                           calls) / out-of-class registers; regs_someone_prefers[A] = the full preferences of every
                           LOWER-priority allocno that conflicts with A (minus A's own unless that one is bigger).
  find_reg (907)           pass 0 skips regs_someone_prefers[A] and every register not used yet (regs_used_so_far =
                           call-used + flow's regs_ever_live + local-alloc's registers + earlier allocations); pass 1
                           takes the lowest free register.  THEN a free COPY preference overrides the scan's choice,
                           else a free plain preference does (lowest register number first).  Then caller-saves
                           (4*calls < refs) and the local-alloc eviction, as global.c.

Inputs are the three dumps of ONE -da compile: .lreg (RTL + flow statistics + `;; Register N in R.` local
dispositions), .greg (allocno order, conflict lists, dumped preferences, dispositions), .flow (the RTL flow's
regs_ever_live is read from).  `Problem(lreg, greg, flow, fname)` reads them, `Replay(problem)` runs
set_preference -> expand -> prune -> find_reg and keeps the provenance of every preference bit and the trace of
every find_reg call; `Replay(problem, drop_events=, drop_merges=, add=, order=)` is the counterfactual form.
`fidelity()` checks a replay against the dumps and (optionally) against cc1's memory read under gdb
(tools/lanes/lanekit/prefs_gdb.py).  Measured exact at every stage on 89 texts / 1,563 allocnos at 2.7.2-cdk,
2.8.0 and 2.8.1 (r85_opus_preftool fidelity*.md).

FIRST_PSEUDO_REGISTER = 76 cells only (2.7.2-cdk, 2.8.0, 2.8.1: the soft-float R3000 register file below).
Modelled from global.c but not exercised by the validation set: DI-mode (two-register) allocnos, local-alloc
eviction, shared (`+N`) allocnos (caller-saves: 2 allocations, exact).  Reload's retry_global_alloc is NOT modelled: an allocno global.c
leaves in hi/lo or unallocated can end up elsewhere in the greg dispositions (fidelity() reports those apart).
"""
from __future__ import annotations

import collections
import re

# ------------------------------------------------------------------------------------------ target (mips.h)

FIRST = 76
# FIXED_REGISTERS / CALL_USED_REGISTERS after CONDITIONAL_REGISTER_USAGE for the soft-float R3000 (every FP and
# FP-status register fixed + call-used; checked against cc1's regs_used_so_far / fixed_reg_set under gdb)
FIXED = set([0, 1, 26, 27, 28, 29, 31, 75]) | set(range(32, 64)) | set(range(67, 75))
CALL_USED = set(list(range(0, 16)) + [24, 25, 26, 27, 28, 29, 31] + list(range(32, 64)) + list(range(64, 76)))
CLASSES = {"NO_REGS": set(), "GR_REGS": set(range(32)), "FP_REGS": set(range(32, 64)), "HI_REG": {64},
           "LO_REG": {65}, "HILO_REG": {66}, "MD_REGS": {64, 65}, "ST_REGS": set(range(67, 75)),
           "ALL_REGS": set(range(76))}
CLASSES["GENERAL_REGS"] = CLASSES["GR_REGS"]
ELIMINABLE = {0, 30, 75}          # ELIMINABLE_REGS from-registers (arg pointer $0, RAP 75, frame pointer $30)
GPRN = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra").split()
MODE_BYTES = {"QI": 1, "HI": 2, "SI": 4, "DI": 8, "TI": 16, "SF": 4, "DF": 8, "CC": 4, "CCFP": 4, "CCEQ": 4,
              "BLK": 4, "VOID": 4, "PSI": 4}


def regclass_of(r):
    if r < 32:
        return "GR_REGS"
    if r < 64:
        return "FP_REGS"
    return {64: "HI_REG", 65: "LO_REG", 66: "HILO_REG"}.get(r, "ST_REGS" if r < 75 else "GR_REGS")


def nregs(r, mode):
    b = MODE_BYTES.get(mode, 4)
    return max(1, (b + 3) // 4)


SI_OK = set(range(32)) | {64, 65}
ALLR = frozenset(range(76))
_BASE = {}            # mode_ok(r, "SI") for the soft-float register file


def mode_ok(r, mode):
    """mips.c mips_hard_regno_mode_ok, 32-bit target (R3000): good enough for the integer/MD allocnos we see."""
    b = MODE_BYTES.get(mode, 4)
    if mode.startswith("CC"):
        return 67 <= r <= 74 if mode == "CCFP" else r < 32
    if r < 32:
        return b <= 4 or r % 2 == 0
    if r < 64:
        return mode in ("SF", "DF") and r % 2 == 0
    if r in (64, 65):
        return b <= 4 or (r == 64 and b == 8)
    return False


def rname(r):
    if r is None:
        return "?"
    if r < 0:
        return "spill"
    if r < 32:
        return "$" + GPRN[r]
    if r < 64:
        return "$f%d" % (r - 32)
    return {64: "hi", 65: "lo", 66: "hilo"}.get(r, "r%d" % r)


def regset(s):
    return "{%s}" % " ".join(rname(r) for r in sorted(s)) if s else "{}"


# ------------------------------------------------------------------------------------------ RTL reader

TOK = re.compile(r'\(|\)|\[|\]|"(?:[^"\\]|\\.)*"|\{[^}]*\}|[^\s()\[\]"]+')


class X:
    """One rtx: code, mode (or note kind), flags, operands (X, str, int, or list for a vector)."""
    __slots__ = ("code", "mode", "flags", "ops")

    def __init__(self, head, ops):
        code, _, mode = head.partition(":")
        code, *flags = code.split("/")
        self.code, self.mode, self.flags, self.ops = code, mode, flags, ops

    def __repr__(self):
        return "(%s%s %s)" % (self.code, ":" + self.mode if self.mode else "", " ".join(map(repr, self.ops)))

    def regno(self):
        return int(self.ops[0]) if self.code == "reg" else None


def _parse(tokens, i):
    """tokens[i] == '(' -> (X, next index)."""
    head = tokens[i + 1]
    if head == ")":
        return X("nil", []), i + 2
    i += 2
    ops = []
    while tokens[i] != ")":
        t = tokens[i]
        if t == "(":
            x, i = _parse(tokens, i)
            ops.append(x)
        elif t == "[":
            vec, i = [], i + 1
            while tokens[i] != "]":
                if tokens[i] == "(":
                    x, i = _parse(tokens, i)
                    vec.append(x)
                else:
                    i += 1
            ops.append(vec)
            i += 1
        else:
            ops.append(int(t) if re.fullmatch(r"-?\d+", t) else t)
            i += 1
    return X(head, ops), i + 1


Insn = collections.namedtuple("Insn", "uid kind pattern notes prologue")


def read_insns(rtl):
    """[Insn] for the insn/call_insn/jump_insn forms of one function's RTL dump text."""
    lines = [ln for ln in rtl.split("\n") if not ln.startswith(";;")]
    k = next((i for i, ln in enumerate(lines) if ln.startswith("(")), len(lines))
    toks = TOK.findall("\n".join(lines[k:]))
    out, i, prologue = [], 0, True
    while i < len(toks):
        if toks[i] != "(":
            i += 1
            continue
        x, i = _parse(toks, i)
        if x.code == "note" and "NOTE_INSN_FUNCTION_BEG" in x.ops:
            prologue = False                     # the parameter copies come before this note
        if x.code not in ("insn", "call_insn", "jump_insn"):
            continue
        pat = next((o for o in x.ops[3:] if isinstance(o, X)), None)
        notes = []
        for o in x.ops[3:]:
            if isinstance(o, X) and o.code == "expr_list" and o.mode.startswith("REG_"):
                n = o
                while isinstance(n, X) and n.code == "expr_list":
                    notes.append((n.mode, n.ops[0] if n.ops else None))
                    n = n.ops[1] if len(n.ops) > 1 else None
        out.append(Insn(int(x.ops[0]), x.code, pat, notes, prologue))
    return out


def walk_regs(x, acc):
    if isinstance(x, X):
        if x.code == "reg":
            acc.append((x.regno(), x.mode))
        for o in x.ops:
            walk_regs(o, acc)
    elif isinstance(x, list):
        for o in x:
            walk_regs(o, acc)
    return acc


def side_effects(x):
    if isinstance(x, X):
        if x.code in ("call", "unspec_volatile", "pre_inc", "pre_dec", "post_inc", "post_dec", "volatile") or \
                (x.code in ("mem", "asm_operands", "asm_input") and "v" in x.flags):
            return True
        return any(side_effects(o) for o in x.ops)
    if isinstance(x, list):
        return any(side_effects(o) for o in x)
    return False


def same_reg(a, b):
    return isinstance(a, X) and isinstance(b, X) and a.code == b.code == "reg" and a.regno() == b.regno()


def single_set(ins):
    p = ins.pattern
    if p is None:
        return None
    if p.code == "set":
        return p
    if p.code == "parallel":
        found = None
        for y in p.ops[0]:
            if y.code != "set":
                continue
            d = y.ops[0]
            unused = any(k == "REG_UNUSED" and same_reg(r, d) for k, r in ins.notes)
            if not unused or side_effects(y):
                if found is not None:
                    return None
                found = y
        return found
    return None


def stores(pattern):
    """note_stores: [(dest after SUBREG-of-pseudo / STRICT_LOW_PART stripping, setter X)]."""
    out = []
    elems = pattern.ops[0] if pattern is not None and pattern.code == "parallel" else [pattern]
    for y in elems:
        if not isinstance(y, X) or y.code not in ("set", "clobber"):
            continue
        d = y.ops[0]
        while isinstance(d, X) and ((d.code == "subreg" and not (isinstance(d.ops[0], X) and d.ops[0].code == "reg"
                                                                  and d.ops[0].regno() < FIRST))
                                    or d.code in ("zero_extract", "sign_extract", "strict_low_part")):
            d = d.ops[0]
        out.append((d, y))
    return out


# rtl.def formats whose first operand is an expression ('e'): set_preference looks through these
FIRST_E = {"mem", "subreg", "plus", "minus", "neg", "mult", "div", "mod", "udiv", "umod", "and", "ior", "xor",
           "not", "ashift", "ashiftrt", "lshiftrt", "rotate", "rotatert", "smin", "smax", "umin", "umax",
           "sign_extend", "zero_extend", "truncate", "float_extend", "float_truncate", "float", "fix",
           "unsigned_float", "unsigned_fix", "abs", "sqrt", "ffs", "compare", "ne", "eq", "ge", "gt", "le", "lt",
           "geu", "gtu", "leu", "ltu", "if_then_else", "call", "const", "high", "lo_sum", "strict_low_part",
           "zero_extract", "sign_extract", "pre_dec", "pre_inc", "post_dec", "post_inc", "use", "clobber",
           "set", "cond_exec", "addressof", "queued", "label_ref"}
FIRST_E.discard("label_ref")


# ------------------------------------------------------------------------------------------ dumps

STAT = re.compile(r"^Register (\d+) used (\d+) times across (-?\d+) insns(.*)\.$", re.M)


def fn_sections(text):
    """{function name: section text} of a multi-function dump."""
    parts = re.split(r"^;; Function (\S+)\s*$", text, flags=re.M)
    return {parts[i]: parts[i + 1] for i in range(1, len(parts) - 1, 2)}


def pick(sections, fname):
    if not sections:
        return None, ""
    if fname and fname in sections:
        return fname, sections[fname]
    if fname:
        tail = re.sub(r"^func_", "", fname)
        for k in sections:
            if k.endswith(tail):
                return k, sections[k]
    k = next(iter(sections))
    return k, sections[k]


def parse_stats(lreg):
    out = {}
    for m in STAT.finditer(lreg):
        p, rest = int(m.group(1)), m.group(4)
        cc = re.search(r"crosses (\d+) calls?", rest)
        by = re.search(r"; (\d+) bytes", rest)
        blk = re.search(r" in block (\d+)", rest)
        cls, alt = "GR_REGS", "ALL_REGS"
        m1 = re.search(r"; pref (\w+), else (\w+)", rest)
        m2 = re.search(r"; (\w+) or none", rest)
        m3 = re.search(r"; pref (\w+)(?!,)", rest)
        if m1:
            cls, alt = m1.group(1), m1.group(2)
        elif m2:
            cls, alt = m2.group(1), "NO_REGS"
        elif m3:
            cls = m3.group(1)
        out[p] = {"refs": int(m.group(2)), "live": int(m.group(3)), "calls": int(cc.group(1)) if cc else 0,
                  "bytes": int(by.group(1)) if by else 4, "block": int(blk.group(1)) if blk else None,
                  "class": cls, "alt": alt}
    return out


def parse_greg(greg, first=FIRST):
    order, shared = [], {}
    m = re.search(r"^;; (\d+) regs to allocate:(.*)$", greg, re.M)
    if m:
        for tok in m.group(2).split():
            if tok.startswith("("):
                continue
            ps = [int(t) for t in tok.split("+")]
            order.append(ps[0])
            for q in ps[1:]:
                shared[q] = ps[0]
    conf, hconf, dpref = {}, {}, {}
    for m in re.finditer(r"^;; (\d+) conflicts:(.*)$", greg, re.M):
        p = int(m.group(1))
        vals = [int(t) for t in m.group(2).split()]
        conf[p] = {v for v in vals if v >= first}
        hconf[p] = {v for v in vals if v < first}
    for m in re.finditer(r"^;; (\d+) preferences:(.*)$", greg, re.M):
        dpref[int(m.group(1))] = {int(t) for t in m.group(2).split()}
    disp = {}
    m2 = re.search(r"Register dispositions:\n(.*?)\n\n", greg, re.S)
    if m2:
        for mm in re.finditer(r"(\d+) in (-?\d+)", m2.group(1)):
            disp[int(mm.group(1))] = int(mm.group(2))
    return order, shared, conf, hconf, dpref, disp


def ever_live_from_flow(flow, first=FIRST):
    """regs_ever_live as flow.c leaves it: every hard register an insn sets or uses (the frame pointer, which
    flow does not mark while it may be eliminated, excluded)."""
    live = set()
    for ins in read_insns(flow):
        for r, _m in walk_regs(ins.pattern, []):
            if r is not None and r < first:
                live.add(r)
    live.discard(30)
    return live


# ------------------------------------------------------------------------------------------ the model

class Problem:
    """Everything global_alloc reads, for one function, from the dumps."""

    def __init__(self, lreg, greg, flow, fname=None, first=FIRST, caller_saves=True):
        self.first = first
        self.fname, lsec = pick(fn_sections(lreg), fname)
        _, gsec = pick(fn_sections(greg), self.fname)
        _, fsec = pick(fn_sections(flow), self.fname) if flow else (None, "")
        self.stats = parse_stats(lsec)
        self.local = {int(a): int(b) for a, b in re.findall(r"^;; Register (\d+) in (\d+)\.$", lsec, re.M)}
        (self.order, self.shared, self.conf, self.hconf0, self.dumped_pref, self.disp) = parse_greg(gsec, first)
        self.insns = read_insns(lsec)
        self.ever_live = ever_live_from_flow(fsec, first) if fsec else None
        self.allocnos = sorted(self.order)
        self.index = {p: i for i, p in enumerate(self.allocnos)}            # allocno number = pseudo order
        for q, p in self.shared.items():
            self.index[q] = self.index[p]
        self.caller_saves = caller_saves
        self.adj = {p: set() for p in self.allocnos}                       # CONFLICTP(a,b) || CONFLICTP(b,a)
        for p in self.allocnos:
            for q in self.conf.get(p, ()):
                if q in self.adj:
                    self.adj[p].add(q)
                    self.adj[q].add(p)
        self.events = self._events()

    # --- helpers
    def allocno_of(self, regno):
        """The allocno pseudo a register belongs to (shared pseudos map to their head), or None."""
        if regno is None or regno < self.first:
            return None
        if regno in self.shared:
            return self.shared[regno]
        return regno if regno in self.index else None

    def hardno(self, regno):
        if regno is None:
            return None
        if regno < self.first:
            return regno
        return self.local.get(regno)

    def conflict(self, a, b):
        return b in self.adj.get(a, ()) or b in self.conf.get(a, ()) or a in self.conf.get(b, ())

    def size(self, p):
        sz = self.__dict__.setdefault("_size", {})
        if p not in sz:
            sz[p] = max(1, (self.stats.get(p, {}).get("bytes", 4) + 3) // 4)
        return sz[p]

    def mode(self, p):
        return "DI" if self.size(p) > 1 else "SI"

    # --- set_preference events (global_conflicts -> mark_reg_store -> set_preference)
    def _events(self):
        ev = []
        for ins in self.insns:
            setters = stores(ins.pattern)
            for dest, setter in setters:
                if setter.code != "set":
                    continue
                e = self._set_preference(ins, dest, setter.ops[1])
                if e:
                    e["set"] = setter
                    ev.append(e)
        return ev

    def _set_preference(self, ins, dest, src):
        copy = True
        if isinstance(src, X) and src.code in FIRST_E and src.ops:
            src, copy = src.ops[0], False
        offset = 0
        if isinstance(src, X) and src.code == "reg":
            sreg, smode = src.regno(), src.mode
        elif isinstance(src, X) and src.code == "subreg" and isinstance(src.ops[0], X) and src.ops[0].code == "reg":
            sreg, smode = src.ops[0].regno(), src.mode
            offset += int(src.ops[1])
        else:
            return None
        if isinstance(dest, X) and dest.code == "reg":
            dreg, dmode = dest.regno(), dest.mode
        elif isinstance(dest, X) and dest.code == "subreg" and isinstance(dest.ops[0], X) and dest.ops[0].code == "reg":
            dreg, dmode = dest.ops[0].regno(), dest.mode
            offset -= int(dest.ops[1])
        else:
            return None
        srx = src if src.code == "reg" else src.ops[0]
        drx = dest if dest.code == "reg" else dest.ops[0]
        s_h = self.hardno(sreg) if sreg >= self.first and sreg in self.local else sreg
        d_h = self.hardno(dreg) if dreg >= self.first and dreg in self.local else dreg
        if d_h < self.first and s_h >= self.first and self.allocno_of(s_h) is not None:
            h = d_h - offset
            if 0 <= h < self.first:
                return {"uid": ins.uid, "pseudo": self.allocno_of(s_h), "hard": h, "copy": copy,
                        "full": set(range(h, h + nregs(h, dmode))), "side": "dest", "other": dreg,
                        "via_local": dreg >= self.first, "ins": ins, "user_hard": "v" in drx.flags}
        if s_h < self.first and d_h >= self.first and self.allocno_of(d_h) is not None:
            h = s_h + offset
            if 0 <= h < self.first:
                return {"uid": ins.uid, "pseudo": self.allocno_of(d_h), "hard": h, "copy": copy,
                        "full": set(range(h, h + nregs(h, smode))), "side": "src", "other": sreg,
                        "via_local": sreg >= self.first, "ins": ins, "user_hard": "v" in srx.flags}
        return None

    # --- expand_preferences merge candidates (insn order)
    def merges(self):
        out = []
        for ins in self.insns:
            st = single_set(ins)
            if st is None or not isinstance(st.ops[0], X) or st.ops[0].code != "reg":
                continue
            a1 = self.allocno_of(st.ops[0].regno())
            if a1 is None:
                continue
            for kind, r in ins.notes:
                if kind != "REG_DEAD" or not isinstance(r, X) or r.code != "reg":
                    continue
                a2 = self.allocno_of(r.regno())
                if a2 is None or self.conflict(a1, a2):
                    continue
                out.append({"uid": ins.uid, "a1": a1, "a2": a2, "copy": same_reg(r, st.ops[1]), "ins": ins})
        return out

    def regs_used_init(self):
        s = set(r for r in range(self.first) if r in CALL_USED)
        s |= self.ever_live if self.ever_live is not None else set()
        s |= {h for p, h in self.local.items() if h >= 0 and p not in self.index}
        return s

    def local_reg_counts(self):
        nref = collections.Counter()
        live = collections.Counter()
        for p, h in self.local.items():
            if p in self.index or h < 0:
                continue
            st = self.stats.get(p, {})
            for j in range(h, h + nregs(h, "DI" if st.get("bytes", 4) == 8 else "SI")):
                nref[j] += st.get("refs", 0)
                live[j] += st.get("live", 0)
        for r in (self.ever_live or ()):
            nref[r] = 0
        return nref, live


class Replay:
    """One run of prefs + find_reg over a Problem, with knobs for the counterfactuals."""

    def __init__(self, pb, drop_events=(), drop_merges=(), add=(), order=None, light=False):
        self.pb = pb
        self.light = light                       # search mode: results only, no explanation state
        P = pb.allocnos
        key = (frozenset(drop_events), frozenset(drop_merges), tuple(add))
        cache = pb.__dict__.setdefault("_exp_cache", {})
        if key not in cache:
            self._expand(drop_events, drop_merges, add)
            cache[key] = (self.direct, self.expanded, self.why, self.merge_list)
        self.direct, self.expanded, self.why, self.merge_list = cache[key]
        self.pref = {p: set(self.expanded[p][0]) for p in P}
        self.copy = {p: set(self.expanded[p][1]) for p in P}
        self.full = {p: set(self.expanded[p][2]) for p in P}
        self._prune(order)
        self.run()

    def _expand(self, drop_events, drop_merges, add):
        pb = self.pb
        P = pb.allocnos
        self.pref = {p: set() for p in P}
        self.copy = {p: set() for p in P}
        self.full = {p: set() for p in P}
        # provenance: (pseudo, set name, reg) -> [origin]
        self.why = collections.defaultdict(list)
        for k, e in enumerate(pb.events):
            if k in drop_events:
                continue
            p = e["pseudo"]
            org = ("direct", k)
            if e["copy"]:
                self.copy[p].add(e["hard"])
                self.why[(p, "copy", e["hard"])].append(org)
            self.pref[p].add(e["hard"])
            self.why[(p, "pref", e["hard"])].append(org)
            for h in e["full"]:
                self.full[p].add(h)
                self.why[(p, "full", h)].append(org)
        for p, h, cp in add:
            if cp:
                self.copy[p].add(h)
                self.why[(p, "copy", h)].append(("added",))
            self.pref[p].add(h)
            self.full[p].add(h)
            self.why[(p, "pref", h)].append(("added",))
            self.why[(p, "full", h)].append(("added",))
        for p in P:
            self.copy[p] -= ELIMINABLE
            self.pref[p] -= ELIMINABLE
        self.direct = {p: (set(self.pref[p]), set(self.copy[p]), set(self.full[p])) for p in P}
        if not hasattr(pb, "_merges"):
            pb._merges = pb.merges()
        self.merge_list = pb._merges
        for k, m in enumerate(self.merge_list):
            if k in drop_merges:
                continue
            a1, a2 = m["a1"], m["a2"]
            sets = (["copy"] if m["copy"] else []) + ["pref", "full"]
            for nm in sets:
                S = getattr(self, nm)
                new1, new2 = S[a2] - S[a1], S[a1] - S[a2]
                for h in new1:
                    self.why[(a1, nm, h)].append(("merge", k, a2))
                for h in new2:
                    self.why[(a2, nm, h)].append(("merge", k, a1))
                u = S[a1] | S[a2]
                S[a1], S[a2] = set(u), set(u)
        self.expanded = {p: (set(self.pref[p]), set(self.copy[p]), set(self.full[p])) for p in P}

    def _prune(self, order):
        pb, P, st = self.pb, self.pb.allocnos, self.pb.stats
        self.order = list(order) if order is not None else list(pb.order)
        # prune_preferences
        self.someone = {}
        self.someone_src = {}
        rank = {p: i for i, p in enumerate(self.order)}
        allr = set(range(pb.first))
        for i in range(len(self.order) - 1, -1, -1):
            a = self.order[i]
            calls = st.get(a, {}).get("calls", 0)
            temp = set(pb.hconf0.get(a, ())) | (CALL_USED if calls else FIXED) | \
                (allr - CLASSES[st.get(a, {}).get("class", "GR_REGS")])
            self.pref[a] -= temp
            self.copy[a] -= temp
            self.full[a] -= temp
            s, src = set(), collections.defaultdict(list)
            sa = pb.size(a)
            for b in (pb.adj[a] if self.light else sorted(pb.adj[a], key=rank.get)):
                if rank.get(b, -1) > i:
                    t = self.full[b]
                    if not t:
                        continue
                    if pb.size(b) <= sa:
                        t = t - self.full[a]
                    s |= t
                    if not self.light:
                        for h in t:
                            src[h].append(b)
            self.someone[a] = s
            self.someone_src[a] = src

    def run(self):
        pb, st = self.pb, self.pb.stats
        self.pref_after_prune = {p: set(s) for p, s in self.pref.items()}
        self.copy_after_prune = {p: set(s) for p, s in self.copy.items()}
        self.full_after_prune = {p: set(s) for p, s in self.full.items()}
        if not hasattr(pb, "_used_init"):
            pb._used_init = pb.regs_used_init()
            pb._local_counts = pb.local_reg_counts()
        self.used_so_far = set(pb._used_init)
        self.used_init = set(self.used_so_far)
        self.hconf = {p: set(pb.hconf0.get(p, ())) for p in pb.allocnos}
        self.hconf_by = collections.defaultdict(dict)      # p -> {reg: allocno that took it}
        self.lref, self.llive = collections.Counter(pb._local_counts[0]), pb._local_counts[1]
        self.result, self.trace = {}, {}
        for a in self.order:
            if st.get(a, {}).get("live", 1) < 0:
                self.result[a] = -1
                self.trace[a] = {"skipped": "live length < 0"}
                continue
            cls, alt = st.get(a, {}).get("class", "GR_REGS"), st.get(a, {}).get("alt", "ALL_REGS")
            tr = self.find_reg(a, cls, set(), False, False)
            if tr["best"] < 0 and alt != "NO_REGS":
                tr2 = self.find_reg(a, alt, set(), False, False)
                tr2["first_try"] = tr
                tr = tr2
            self.result[a] = tr["best"]
            self.trace[a] = tr

    def find_reg(self, a, cls, losers, accept, retrying):
        pb, st = self.pb, self.pb.stats
        calls = st.get(a, {}).get("calls", 0)
        mode = pb.mode(a)
        key = (cls, bool(calls), accept)
        base = _BASE.get(key)
        if base is None:
            base = _BASE[key] = frozenset((FIXED if accept else (FIXED if calls == 0 else CALL_USED)) |
                                          (set(range(76)) - CLASSES.get(cls, CLASSES["GR_REGS"])))
        used2 = base | losers if losers else base
        used1 = used2 | self.hconf[a]
        unused = ALLR - self.used_so_far
        used = used1 | unused | self.someone[a]
        if self.light:
            tr = {"pass": None}
        else:
            tr = {"class": cls, "accept": accept, "calls": calls, "used1": set(used1), "pass": None, "scan": -1,
                  "someone": set(self.someone[a]), "unused": unused, "how": None}
        best = -1
        for ps in (0, 1):
            if ps == 1:
                used = set(used1)
            if mode == "SI":                                         # one-register fast path: the lowest free OK reg
                free = SI_OK - used
                if free:
                    best = min(free)
                    tr["pass"] = ps
                    break
                continue
            i = 0
            while i < pb.first:
                r = i
                if r not in used and mode_ok(r, mode):
                    lim = r + nregs(r, mode)
                    j = r + 1
                    while j < lim and j not in used:
                        j += 1
                    if j == lim:
                        best = r
                        break
                    i = j
                i += 1
            if best >= 0:
                tr["pass"] = ps
                break
        tr["scan"] = best
        if not self.light:
            tr["used_final"] = set(used)
            tr["taken_by"] = dict(self.hconf_by.get(a, {}))      # who had taken which register when a's turn came
        cp = self.copy[a] - used
        self.copy[a] = cp
        how = "scan pass %s" % tr["pass"] if best >= 0 else None
        took = False
        if cp and best >= 0:
            for i in range(pb.first):
                if i in cp and mode_ok(i, mode) and regclass_of(i) == regclass_of(best):
                    lim = i + nregs(i, mode)
                    j = i + 1
                    while j < lim and j not in used and regclass_of(j) == regclass_of(best + (j - i)):
                        j += 1
                    if j == lim:
                        best, how, took = i, "copy-preference", True
                        break
        if not took:
            pr = self.pref[a] - used
            self.pref[a] = pr
            if pr and best >= 0:
                for i in range(pb.first):
                    if i in pr and mode_ok(i, mode) and regclass_of(i) == regclass_of(best):
                        lim = i + nregs(i, mode)
                        j = i + 1
                        while j < lim and j not in used and regclass_of(j) == regclass_of(best + (j - i)):
                            j += 1
                        if j == lim:
                            best, how = i, "preference"
                            break
        if self.pb.caller_saves and best < 0 and not accept and calls and 4 * calls < st.get(a, {}).get("refs", 0):
            t2 = self.find_reg(a, cls, losers, True, retrying)
            if t2["best"] >= 0:
                t2["via"] = "caller-saves"
                return t2
        if best < 0 and not retrying and pb.size(a) == 1:
            ratio = st.get(a, {}).get("refs", 0) / float(st.get(a, {}).get("live", 1) or -1)
            for r in range(pb.first - 1, -1, -1):
                if self.lref.get(r) and r not in used2 and mode_ok(r, mode) and \
                        self.lref[r] / float(self.llive[r] or 1) < ratio:
                    best, how = r, "evicts local-alloc's %s" % rname(r)
                    break
        tr["best"], tr["how"] = best, how
        if best >= 0:
            span = range(best, best + (1 if mode == "SI" else nregs(best, mode)))
            for j in span:
                self.used_so_far.add(j)
                self.lref[j] = 0
            light = self.light
            for q in pb.adj[a] | {a}:
                hq = self.hconf[q]
                for j in span:
                    if not light and j not in hq:
                        self.hconf_by[q][j] = a
                    hq.add(j)
        return tr


BINOP = {"plus": "+", "minus": "-", "mult": "*", "div": "/", "mod": "%", "and": "&", "ior": "|", "xor": "^",
         "ashift": "<<", "ashiftrt": ">>", "lshiftrt": ">>>", "udiv": "/u", "umod": "%u"}


def show(x, pb, names, depth=0):
    """A compact C-ish rendering of an rtx with pseudo names: `r101 pixel_offset`, `$v0`, `[r106 + 42]`."""
    if isinstance(x, list):
        return "; ".join(show(y, pb, names, depth) for y in x)
    if not isinstance(x, X):
        return str(x)
    c = x.code
    if c == "reg":
        r = x.regno()
        if r < pb.first:
            return rname(r)
        a = pb.allocno_of(r)
        loc = pb.local.get(r)
        return "r%d%s%s" % (r, ":" + names[r] if r in names else "", "@" + rname(loc) if a is None and loc is not None
                            else "")
    if c == "const_int":
        return str(x.ops[0])
    if c == "symbol_ref":
        return str(x.ops[0]).strip('"()')
    if depth > 3:
        return "..."
    if c == "mem":
        return "[%s]" % show(x.ops[0], pb, names, depth + 1)
    if c in BINOP and len(x.ops) == 2:
        return "(%s %s %s)" % (show(x.ops[0], pb, names, depth + 1), BINOP[c], show(x.ops[1], pb, names, depth + 1))
    if c == "set":
        return "%s = %s" % (show(x.ops[0], pb, names, depth), show(x.ops[1], pb, names, depth))
    if c == "parallel":
        return show(next((y for y in x.ops[0] if y.code == "set"), x.ops[0][0]), pb, names, depth)
    if c in ("subreg", "zero_extend", "sign_extend", "truncate", "neg", "not", "high"):
        return "%s(%s)" % (c, show(x.ops[0], pb, names, depth + 1))
    return "%s(%s)" % (c, ", ".join(show(o, pb, names, depth + 1) for o in x.ops if isinstance(o, X)))



# ------------------------------------------------------------------------------------------ fidelity

def fidelity(pb, rp, oracle=None):
    """{check: (agree, total, [mismatch notes])}."""
    out = {}
    P = pb.allocnos
    # the dumped `;; N preferences:` = hard_reg_preferences after prune
    bad = [p for p in P if rp.pref_after_prune.get(p, set()) != pb.dumped_pref.get(p, set())] \
        if hasattr(rp, "pref_after_prune") else []
    out["dumped preferences"] = (len(P) - len(bad), len(P), ["%d model %s dump %s" % (
        p, regset(rp.pref_after_prune.get(p, set())), regset(pb.dumped_pref.get(p, set()))) for p in bad[:6]])
    # dispositions (reload may move a spilled allocno; those are marked)
    agree, tot, notes, rl = 0, 0, [], 0
    for p in rp.order:
        d = pb.disp.get(p, -1)
        tot += 1
        m = rp.result.get(p)
        if m == d:
            agree += 1
        elif m is None or m < 0 or m >= 32:
            rl += 1                       # global left it in hi/lo or unallocated: reload's retry_global_alloc moved it
            notes.append("%d model %s greg %s (reload retry)" % (p, rname(m), rname(d)))
        else:
            notes.insert(0, "%d model %s greg %s" % (p, rname(m), rname(d)))
    out["greg dispositions"] = (agree, tot - rl, notes)
    if rl:
        out["greg: reload-retried (excluded)"] = (rl, rl, [])
    if oracle:
        st = {s["stage"]: s for s in oracle.get("stages", []) if s["function"] == pb.fname}
        if "dump" in st:
            ar = st["dump"]["allocno_reg"]
            idx = {p: i for i, p in enumerate(ar)}

            def cmp(label, mine, stage, key):
                if stage not in st:
                    return
                o = st[stage][key]
                bad = [p for p in P if set(o[idx[p]]) != mine[p]]
                out[label] = (len(P) - len(bad), len(P), ["%d model %s cc1 %s" % (
                    p, regset(mine[p]), regset(set(o[idx[p]]))) for p in bad[:6]])
            cmp("set_preference: preferences", {p: rp.direct[p][0] for p in P}, "expand", "hard_reg_preferences")
            cmp("set_preference: copy", {p: rp.direct[p][1] for p in P}, "expand", "hard_reg_copy_preferences")
            cmp("set_preference: full", {p: rp.direct[p][2] for p in P}, "expand", "hard_reg_full_preferences")
            cmp("expand: preferences", {p: rp.expanded[p][0] for p in P}, "prune", "hard_reg_preferences")
            cmp("expand: copy", {p: rp.expanded[p][1] for p in P}, "prune", "hard_reg_copy_preferences")
            cmp("expand: full", {p: rp.expanded[p][2] for p in P}, "prune", "hard_reg_full_preferences")
            cmp("prune: full", {p: rp.full_after_prune[p] for p in P}, "dump", "hard_reg_full_preferences")
            cmp("prune: copy", {p: rp.copy_after_prune[p] for p in P}, "dump", "hard_reg_copy_preferences")
            cmp("regs_someone_prefers", rp.someone, "dump", "regs_someone_prefers")
            o_used = set(st["dump"]["regs_used_so_far"])
            out["regs_used_so_far (initial)"] = (int(o_used == rp.used_init), 1, [] if o_used == rp.used_init else [
                "model-only %s cc1-only %s" % (regset(rp.used_init - o_used), regset(o_used - rp.used_init))])
            fr = {}
            for e in oracle.get("find_reg", []):
                if e["function"] == pb.fname and not e["retrying"]:
                    fr[e["pseudo"]] = e["result"]
            bad = [p for p in rp.order if fr.get(p, -1) != rp.result.get(p)]
            out["find_reg results (cc1)"] = (len(rp.order) - len(bad), len(rp.order), [
                "%d model %s cc1 %s" % (p, rname(rp.result.get(p)), rname(fr.get(p, -1))) for p in bad[:8]])
    return out
