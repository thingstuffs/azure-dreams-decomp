#!/usr/bin/env python3
"""lreg_explain.py - local-alloc.c replayed from the `.lreg` dump: the per-block quantity order, why each qty got
its register, and the inequality that would give a block-local pseudo retail's register.

    cd work/native_lane/<lane>
    python3 <KIT>/lreg_explain.py <row> <candidate.c|erased|pinned> [--cfg CFG] [--block B] [--pseudo P ...]
                                  [--retail listing|none] [--all] [--json OUT.json]

`why.py --pass lreg` prints refs / live per pseudo and `alloc_need.py` stops at "LOCAL" for a block-local
pseudo, because local-alloc's own numbers (qty_birth / qty_death, the copy/arith suggestions, the qty order)
are in no dump.  They are all DERIVABLE from the `.lreg` dump, which holds the insn stream local-alloc saw
(printed after local_alloc: update_equiv_regs has already run), the flow stats, the basic blocks with the hard
registers live at their start, and the result (`;; Register N in R.`).  This tool re-runs block_alloc
(gcc 2.7.2 local-alloc.c; 2.8.1 differs only in spelling - QTY_CMP_PRI / QTY_CMP_SUGG macros and
losing_caller_save_reg_set) on that stream and checks itself against the result line for every pseudo:

1. SCAN (block_alloc's insn loop, verbatim order per insn): tie operand 0 with a dying input (combine_regs,
   operands from the insn's mips.md template - the dump prints `{pattern}` names; the md of the cell's backend
   gives the constraints: `=` / `&`, matching digits, `%`, `p`), or record a hard-register SUGGESTION (a copy
   from/to $a0, $v0 ... -> qty_phys_copy_sugg; an arithmetic one -> qty_phys_sugg); wipe REG_DEAD regs
   (death = 2n); note_stores births (SET 2n, CLOBBER 2n-1; a qty is numbered at its birth); REG_UNUSED
   deaths (2n+1); SCRATCH qtys (mode size in BYTES, 2n-1 .. 2n+1); hard registers live at each index.
   `n` counts every non-NOTE object of the block (code labels and barriers too).
2. ORDER: the suggestion pass (qty_sugg_compare: copy-suggestion count, else arith count * FIRST_PSEUDO, then
   priority) and the priority pass (qty_compare: `int(floor_log2(refs) * refs * size / (death - birth) *
   10000)`, descending; ties by qty number).  For 2 or 3 qtys block_alloc does not qsort: it calls
   qty_compare(0, 1), (1, 2), (0, 1) on the literal qty NUMBERS with positional exchanges - replayed verbatim
   (the result is not always sorted).
3. ALLOCATE: find_free_reg - the lowest-numbered register of the class (MIPS has no REG_ALLOC_ORDER) not
   fixed, not call-used when the qty crosses calls, not $fp, not live over [birth, death) (hard registers and
   qtys placed before it); a suggested qty first tries only its copy suggestions, then its arith ones; the
   caller-save retry when 4 * calls < refs.
4. FIDELITY: every simulated register is compared with the dump's `;; Register N in R.` line (and every
   pseudo the model leaves to global with the absence of one).  Only reproduced qtys are explained as fact.
5. THE INVERSE, given retail's register per pseudo (`--retail listing`: alloc_need's listing votes): for a
   mis-coloured qty, who held retail's register over its life (a qty placed earlier - in which pass and by
   which priority - a hard register set by which insn, a fixed/call-used rule), then two searches, each
   re-running the exact order + allocation:
     PRIORITY  one qty's refs or life length in the KEY moved (geometry held) until the block colours like
               retail: `qty 3 (p 118 link) refs >= 4 (now 3)`, `qty 5 (p 121 speed) length >= 23 (now 20)`,
               with the pair it crosses (`must outrank`, prio a vs b).  A suggestion-pass winner cannot be
               outranked this way - the tool says so.
     GEOMETRY  one qty's birth or death moved (key follows): `p 121 must die by index 36 (insn 412)`.
   Each is NECESSARY in the model, not sufficient in the source: re-run the tool on the candidate.

`alloc_need.py` calls `explain()` for its LOCAL verdicts (and narrows BLOCKED holders to the blocks where the
global pseudo lives).  2.91.66 / 2.95.2 are refused (no FIRST_PSEUDO_REGISTER in alloc_sim).
"""
from __future__ import annotations

import argparse
import collections
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

REGNAME = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
           "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra").split()
MODE_BYTES = {"QI": 1, "HI": 2, "SI": 4, "DI": 8, "TI": 16, "SF": 4, "DF": 8, "CC": 4, "CCFP": 4,
              "BLK": 0, "VOID": 0, "PSI": 4, "PDI": 8, "CCEQ": 4, "CCmode": 4}
FLOATISH = {"SF", "DF", "SC", "DC", "XF", "TF"}
# md backends: 2.7.2-cdk carries the 76-register (2.8-era) mips backend, so its patterns are read from 2.8.1's md
MD_FOR = {"2.6.3": ["2.6.3", "2.7.2"], "2.7.2": ["2.7.2", "2.8.1"], "2.7.2-cdk": ["2.8.1", "2.8.0", "2.7.2"],
          "2.8.0": ["2.8.0", "2.8.1"], "2.8.1": ["2.8.1", "2.8.0"]}
FIXED_GPR = {0, 1, 26, 27, 28, 29, 31}
CALL_USED_GPR = set(range(16)) | {24, 25, 26, 27, 28, 29, 31}
FP_REGNUM = 30                                               # ELIMINABLE_REGS from: arg pointer ($0), frame pointer ($fp)


def rname(n):
    if n is None:
        return "?"
    if n < 0:
        return "none"
    if n < 32:
        return "$" + REGNAME[n]
    return {64: "hi", 65: "lo", 66: "hilo"}.get(n, "r%d" % n)


def floor_log2(n):
    return -1 if n <= 0 else n.bit_length() - 1                # floor_log2_wide(0) = -1


def qty_pri(refs, length, size):
    """QTY_CMP_PRI verbatim: (int) ((double) (floor_log2 (refs) * refs * size) / (death - birth) * 10000)."""
    num = floor_log2(refs) * refs * size
    if length == 0:
        return 2 ** 31 - 1 if num > 0 else (-(2 ** 31) if num < 0 else 0)
    return int(num / float(length) * 10000)


# ------------------------------------------------------------------------------------------ s-expressions

class Vec(list):
    """An rtvec: `[ ... ]` in the dump (`parallel[ ... ]`, asm operands) and in the md."""


TOK = re.compile(r'"(?:\\.|[^"\\])*"|[()\[\]]|[^\s()\[\]"]+')


def parse_sexprs(text):
    top, stack = [], []
    for m in TOK.finditer(text):
        t = m.group(0)
        if t in ("(", "["):
            stack.append([] if t == "(" else Vec())
        elif t in (")", "]"):
            if not stack:
                continue
            node = stack.pop()
            (stack[-1] if stack else top).append(node)
        else:
            (stack[-1] if stack else top).append(t)
    while stack:                                             # a truncated dump: close what is open
        node = stack.pop()
        (stack[-1] if stack else top).append(node)
    return top


def strip_md_comments(text):
    out, i, n, instr = [], 0, len(text), False
    while i < n:
        c = text[i]
        if instr:
            out.append(c)
            if c == "\\" and i + 1 < n:
                out.append(text[i + 1])
                i += 2
                continue
            if c == '"':
                instr = False
        elif c == '"':
            instr = True
            out.append(c)
        elif c == ";":
            while i < n and text[i] != "\n":
                i += 1
            continue
        else:
            out.append(c)
        i += 1
    return "".join(out)


def code_of(x):
    if isinstance(x, list) and not isinstance(x, Vec) and x and isinstance(x[0], str):
        return x[0].split(":")[0].split("/")[0]
    return None


def mode_of(x):
    h = x[0] if isinstance(x, list) and x and isinstance(x[0], str) else ""
    return h.split(":", 1)[1] if ":" in h else "VOID"


def mode_bytes(m):
    return MODE_BYTES.get(m, 4)


def words(m):
    return max(1, (mode_bytes(m) + 3) // 4)


def regno(x):
    return int(x[1])


def unquote(s):
    return s[1:-1] if isinstance(s, str) and s.startswith('"') else (s or "")


# ------------------------------------------------------------------------------------------ mips.md

_MD_CACHE = {}


def load_md(version):
    """{pattern name: {'tmpl', 'cons' {opno: constraint}, 'kind' {opno: operand|scratch|operator}, 'nops',
    'nalts'}} for the named define_insns of toolchain/gcc-src/<version>/config/mips/mips.md."""
    if version in _MD_CACHE:
        return _MD_CACHE[version]
    p = kitlib.ROOT / "toolchain/gcc-src" / version / "config/mips/mips.md"
    out = {}
    if p.is_file():
        for node in parse_sexprs(strip_md_comments(p.read_text(errors="replace"))):
            if code_of(node) != "define_insn" or len(node) < 3 or not isinstance(node[2], Vec):
                continue
            name = unquote(node[1])
            if not name or name.startswith("*"):
                continue
            vec = node[2]
            tmpl = vec[0] if len(vec) == 1 else ["parallel", Vec(vec)]
            cons, kind = {}, {}

            def walk(t):
                c = code_of(t)
                if c in ("match_operand", "match_scratch", "match_operator", "match_parallel"):
                    k = int(t[1])
                    kind[k] = {"match_operand": "operand", "match_scratch": "scratch"}.get(c, "operator")
                    if c == "match_operand":
                        cons[k] = unquote(t[3]) if len(t) > 3 and isinstance(t[3], str) else ""
                    elif c == "match_scratch":
                        cons[k] = unquote(t[2]) if len(t) > 2 and isinstance(t[2], str) else ""
                    else:
                        cons[k] = ""
                if isinstance(t, list):
                    for s in t[1:] if not isinstance(t, Vec) else t:
                        if isinstance(s, list):
                            walk(s)
            walk(tmpl)
            nops = (max(kind) + 1) if kind else 0
            nalts = max([c.count(",") + 1 for c in cons.values() if c] or [1])
            out[name] = {"tmpl": tmpl, "cons": cons, "kind": kind, "nops": nops, "nalts": nalts}
    _MD_CACHE[version] = out
    return out


def md_lookup(name, cell):
    for v in MD_FOR.get(cell, ["2.8.1", "2.7.2"]):
        info = load_md(v).get(name)
        if info:
            return info
    return None


def match(t, x, ops):
    """Bind the template's match_* operands to the dump's rtx (recog_operand); False on a shape mismatch."""
    c = code_of(t)
    if c in ("match_operand", "match_scratch", "match_parallel"):
        ops[int(t[1])] = x
        return True
    if c == "match_operator":
        ops[int(t[1])] = x
        subs = t[3] if len(t) > 3 else []
        if not isinstance(x, list):
            return False
        xs = [e for e in x[1:]]
        return all(match(s, e, ops) for s, e in zip(subs, xs))
    if c in ("match_dup", "match_op_dup", "match_par_dup"):
        return True
    if isinstance(t, Vec):
        if not isinstance(x, Vec) or len(x) != len(t):
            return False
        return all(match(a, b, ops) for a, b in zip(t, x))
    if isinstance(t, str) or t is None:
        return True
    if not isinstance(x, list) or isinstance(x, Vec):
        return False
    if code_of(x) != c:
        return False
    for a, b in zip(t[1:], x[1:]):
        if isinstance(a, list):
            if not match(a, b, ops):
                return False
    return True


def requires_inout(p):
    """local-alloc.c requires_inout, verbatim: the alternatives in which this operand must match operand 0."""
    found_zero = reg_allowed = 0
    n = 0
    for c in p:
        if c in "=+?#&!*%1234mo<>VEFGHsinIJKLMNOPQRSTUX":
            continue
        if c == ",":
            if found_zero and not reg_allowed:
                n += 1
            found_zero = reg_allowed = 0
        elif c == "0":
            found_zero = 1
        else:
            reg_allowed = 1
    if found_zero and not reg_allowed:
        n += 1
    return n


# ------------------------------------------------------------------------------------------ the dump

STAT = re.compile(r"^Register (\d+) used (\d+) times across (-?\d+) insns(.*)$", re.M)
BLOCK = re.compile(r"^Basic block (\d+): first insn (\d+), last (\d+)\.\s*\n(?:\s*\n)?"
                   r"(?:Reached from blocks:[^\n]*\n\s*\n?)?Registers live at start:([^\n]*)", re.M)
RESULT = re.compile(r"^;; Register (\d+) in (\d+)\.$", re.M)
FUNC = re.compile(r"^;; Function (\S+)", re.M)
INSN_KINDS = ("insn", "jump_insn", "call_insn")


def split_functions(lreg):
    heads = [(m.start(), m.group(1)) for m in FUNC.finditer(lreg)]
    if not heads:
        return [("?", lreg)]
    heads.append((len(lreg), None))
    return [(n, lreg[a:b]) for (a, n), (b, _) in zip(heads, heads[1:])]


def pick_function(lreg, text=None, name=None):
    """The section of `lreg` for the candidate's function (a module row's dump holds its siblings too)."""
    secs = split_functions(lreg)
    if len(secs) == 1:
        return secs[0]
    if name:
        for n, s in secs:
            if n == name:
                return n, s
    if text:
        defined = set(re.findall(r"^[A-Za-z_][\w \t\*]*?\b(\w+)\s*\([^;{]*\)\s*\{", text, re.M))
        cands = [(n, s) for n, s in secs if n in defined]
        if len(cands) == 1:
            return cands[0]
        if cands:
            return max(cands, key=lambda ns: len(ns[1]))
    return max(secs, key=lambda ns: len(ns[1]))


def parse_stat_rest(rest):
    st = {"block": None, "deaths": 1, "calls": 0, "bytes": 4, "pref": "GR_REGS", "alt": "ALL_REGS"}
    m = re.search(r" in block (\d+)", rest)
    if m:
        st["block"] = int(m.group(1))
    m = re.search(r"dies in (\d+) places?", rest)
    if m:
        st["deaths"] = int(m.group(1))
    m = re.search(r"crosses (\d+) calls?", rest)
    if m:
        st["calls"] = int(m.group(1))
    m = re.search(r"; (\d+) bytes", rest)
    if m:
        st["bytes"] = int(m.group(1))
    m = re.search(r"; (\w+) or none", rest)
    if m:
        st["pref"], st["alt"] = m.group(1), "NO_REGS"
    m = re.search(r"; pref (\w+)(?:, else (\w+))?", rest)
    if m:
        st["pref"] = m.group(1)
        st["alt"] = m.group(2) or "ALL_REGS"
    return st


class Insn:
    __slots__ = ("kind", "uid", "pattern", "code", "name", "notes")

    def __init__(self, node):
        self.kind = node[0].split("/")[0]                     # 2.8.x prints flags on the head: note/i, insn/s
        self.uid = int(node[1])
        self.pattern = node[4] if self.kind in INSN_KINDS and len(node) > 4 else None
        self.code, self.name, self.notes = -1, None, []
        if self.kind in INSN_KINDS:
            rest = node[5:]
            if rest and isinstance(rest[0], str):
                try:
                    self.code = int(rest[0])
                except ValueError:
                    self.code = -1
                rest = rest[1:]
            if rest and isinstance(rest[0], str) and rest[0].startswith("{"):
                self.name = rest[0].strip("{}")
                rest = rest[1:]
            if len(rest) >= 2:                                   # LOG_LINKS, REG_NOTES
                self.notes = parse_notes(rest[1])

    def note(self, kind, rn=None):
        for k, x in self.notes:
            if k == kind and (rn is None or (code_of(x) == "reg" and regno(x) == rn)):
                return x
        return None


def parse_notes(x):
    out = []
    while isinstance(x, list) and code_of(x) in ("expr_list", "insn_list") and len(x) >= 3:
        h = x[0]
        kind = h.split(":", 1)[1] if ":" in h else "REG_DEP"
        out.append((kind, x[1]))
        x = x[2]
    return out


def parse_dump(sec, first):
    """{'stats', 'blocks', 'result', 'chain', 'pos'} of one function's `.lreg` section."""
    stats = {}
    for m in STAT.finditer(sec):
        st = parse_stat_rest(m.group(4))
        st["refs"], st["live"] = int(m.group(2)), int(m.group(3))
        stats[int(m.group(1))] = st
    blocks = []
    for m in BLOCK.finditer(sec):
        live = [int(v) for v in m.group(4).split() if v.isdigit()]
        blocks.append({"b": int(m.group(1)), "first": int(m.group(2)), "last": int(m.group(3)),
                       "live": {r for r in live if r < first}, "live_pseudos": {r for r in live if r >= first}})
    result = {int(a): int(b) for a, b in RESULT.findall(sec)}
    m = re.search(r"^\((?:note|insn|jump_insn|call_insn|code_label|barrier)[/ ]", sec, re.M)
    chain = []
    if m:
        for node in parse_sexprs(sec[m.start():]):
            if (isinstance(node, list) and node and isinstance(node[0], str)
                    and node[0].split("/")[0] in INSN_KINDS + ("note", "code_label", "barrier")):
                try:
                    chain.append(Insn(node))
                except (ValueError, IndexError):
                    continue
    pos = {o.uid: i for i, o in enumerate(chain)}
    return {"stats": stats, "blocks": blocks, "result": result, "chain": chain, "pos": pos}


# ------------------------------------------------------------------------------------------ classes

def class_mask(name, first):
    allm = (1 << first) - 1
    gr = (1 << 32) - 1
    st_hi = 75 if first >= 76 else 68
    return {"NO_REGS": 0, "GR_REGS": gr, "GENERAL_REGS": gr, "FP_REGS": gr << 32,
            "HI_REG": 1 << 64, "LO_REG": 1 << 65, "HILO_REG": 1 << 66, "MD_REGS": (1 << 64) | (1 << 65),
            "ST_REGS": sum(1 << r for r in range(67, st_hi)), "ALL_REGS": allm}.get(name, gr) & allm


LETTER_CLASS = {"d": "GR_REGS", "r": "GR_REGS", "g": "GR_REGS", "y": "GR_REGS", "f": "FP_REGS", "h": "HI_REG",
                "l": "LO_REG", "a": "HILO_REG", "x": "MD_REGS", "b": "ALL_REGS", "z": "ST_REGS"}


def likely_spilled(name, first):
    return bin(class_mask(name, first)).count("1") == 1


def class_subset(a, b, first):
    ma, mb = class_mask(a, first), class_mask(b, first)
    return ma & ~mb == 0


def scratch_class(cons):
    """alloc_qty_for_scratch's class for alternative 0 (None = no qty: 'X' or no register letter)."""
    alt = cons.split(",")[0]
    cls = None
    for c in alt:
        if c == "X":
            return None
        if c in LETTER_CLASS:
            cls = LETTER_CLASS[c] if cls is None else ("ALL_REGS" if cls != LETTER_CLASS[c] else cls)
    return cls


def mode_ok(r, mode):
    if mode_bytes(mode) > 4 and r < 32:
        return r % 2 == 0
    return True


# ------------------------------------------------------------------------------------------ the replay

class Qty:
    __slots__ = ("n", "regs", "size", "mode", "birth", "death", "calls", "min_class", "alt_class", "refs",
                 "copy", "sugg", "copy_src", "sugg_src", "scratch", "scratch_reg", "birth_uid", "offset")

    def __init__(self, **kw):
        self.copy, self.sugg, self.copy_src, self.sugg_src = set(), set(), {}, {}
        self.scratch, self.scratch_reg, self.offset = False, None, {}
        for k, v in kw.items():
            setattr(self, k, v)

    @property
    def length(self):
        return self.death - self.birth


class Block:
    """block_alloc's scan of one basic block: qtys + the hard registers live at every index."""

    def __init__(self, fn, blk):
        self.fn, self.b = fn, blk["b"]
        self.qtys, self.hard_at, self.hard_cause = [], collections.defaultdict(int), {}
        self.gspans = collections.defaultdict(list)          # global pseudo -> [(from, to)] inside this block
        self.numbers = {}                                    # insn number -> uid
        self.warnings = []


class Function:
    def __init__(self, lreg, first, cell, text=None, name=None, caller_saves=True):
        self.first, self.cell, self.caller_saves = first, cell, caller_saves
        self.name, sec = pick_function(lreg, text, name)
        self.d = parse_dump(sec, first)
        self.stats = self.d["stats"]
        self.reg_qty = {}
        for p, st in self.stats.items():
            if p < first:
                continue
            ok = (st["block"] is not None and st["deaths"] == 1
                  and (st["alt"] == "NO_REGS" or not likely_spilled(st["pref"], first)))
            self.reg_qty[p] = -2 if ok else -1
        self.blocks = []
        self.warnings = []
        for blk in self.d["blocks"]:
            self.blocks.append(self.scan(blk))

    # ---------------------------------------------------------------- scan (block_alloc's insn loop)
    def scan(self, blk):
        B = Block(self, blk)
        first = self.first
        chain, pos = self.d["chain"], self.d["pos"]
        if blk["first"] not in pos or blk["last"] not in pos:
            B.warnings.append("block %d: insn %s/%s not in the dump" % (blk["b"], blk["first"], blk["last"]))
            return B
        regs_live = 0
        born = {}
        for r in blk["live"]:
            regs_live |= 1 << r
            born[r] = "start"
        st = {"n": 0, "insn": None, "regs_live": regs_live, "born": born}
        gopen = {p: 0 for p in blk["live_pseudos"] if self.reg_qty.get(p, -1) == -1}

        def mark_life(r, mode, life):
            for j in range(words(mode) if r < 32 else 1):
                if life:
                    st["regs_live"] |= 1 << (r + j)
                    st["born"][r + j] = st["insn"].uid
                else:
                    st["regs_live"] &= ~(1 << (r + j))

        def post_mark_hard(r, mode, a, b):
            for j in range(words(mode) if r < 32 else 1):
                for i in range(a, b):
                    B.hard_at[i] |= 1 << (r + j)
                    B.hard_cause.setdefault((i, r + j), st["insn"].uid)

        def alloc_qty(p, mode, birth):
            s = self.stats.get(p, {})
            q = Qty(n=len(B.qtys), regs=[p], size=max(1, (s.get("bytes", 4) + 3) // 4), mode=mode, birth=birth,
                    death=-1, calls=s.get("calls", 0), min_class=s.get("pref", "GR_REGS"),
                    alt_class=s.get("alt", "ALL_REGS"), refs=s.get("refs", 0), birth_uid=st["insn"].uid)
            q.offset[p] = 0
            B.qtys.append(q)
            self.reg_qty[p] = q.n + 1000000 * (blk["b"] + 1)   # >= 0, block-tagged
            return q

        def qty_of(p):
            v = self.reg_qty.get(p, -1)
            return B.qtys[v % 1000000] if v >= 1000000 * (blk["b"] + 1) and v < 1000000 * (blk["b"] + 2) else None

        def rq(p):
            """reg_qty[p] as local-alloc sees it inside this block: -1, -2, or >= 0 (0 stands for 'has a qty')."""
            v = self.reg_qty.get(p, -1)
            return v if v < 0 else 0

        def reg_is_born(x, birth):
            if code_of(x) == "subreg":
                r = regno(x[1]) + int(x[2])
                mode = mode_of(x)
            else:
                r, mode = regno(x), mode_of(x)
            if r < first:
                mark_life(r, mode, 1)
                if birth < 2 * st["n"]:
                    post_mark_hard(r, mode, birth, 2 * st["n"])
            else:
                if rq(r) == -2:
                    alloc_qty(r, mode, birth)
                q = qty_of(r)
                if q is not None:
                    q.death = -1

        def single_set(insn):
            pat = insn.pattern
            if code_of(pat) == "set":
                return pat
            if code_of(pat) == "parallel":
                found = None
                for e in pat[1]:
                    if code_of(e) == "set":
                        dest = e[1]
                        if code_of(dest) == "reg" and insn.note("REG_UNUSED", regno(dest)) is not None:
                            continue
                        if found is not None:
                            return None
                        found = e
                return found
            return None

        def mentions(x, r):
            if code_of(x) == "reg":
                return regno(x) == r
            if isinstance(x, list):
                return any(mentions(e, r) for e in (x if isinstance(x, Vec) else x[1:]) if isinstance(e, list))
            return False

        def wipe_dead_reg(x, output_p):
            r = regno(x)
            insn = st["insn"]
            if code_of(insn.pattern) == "parallel" and single_set(insn) is None:
                for e in insn.pattern[1]:
                    if code_of(e) == "set" and code_of(e[1]) != "reg" and mentions(e[1], r):
                        output_p = 1
            n = st["n"]
            if r < first:
                mark_life(r, mode_of(x), 0)
                if output_p:
                    post_mark_hard(r, mode_of(x), 2 * n, 2 * n + 1)
            else:
                q = qty_of(r)
                if q is not None:
                    q.death = 2 * n + output_p
                elif self.reg_qty.get(r, -1) == -1 and r in gopen:
                    B.gspans[r].append((gopen.pop(r), 2 * n + output_p))

        def add_sugg(q, hard, may_save_copy):
            uid = st["insn"].uid
            if may_save_copy and hard not in q.copy:
                q.copy.add(hard)
                q.copy_src[hard] = uid
            elif hard not in q.sugg:
                q.sugg.add(hard)
                q.sugg_src[hard] = uid

        def combine_regs(used, setr, may_save_copy, already_dead=False):
            insn, n = st["insn"], st["n"]
            offset = 0
            while code_of(used) == "subreg":
                if mode_bytes(mode_of(used[1])) > 4:
                    may_save_copy = 0
                offset += int(used[2])
                used = used[1]
            if code_of(used) != "reg":
                return False
            ureg, usize = regno(used), words(mode_of(used))
            while code_of(setr) == "subreg":
                if mode_bytes(mode_of(setr[1])) > 4:
                    may_save_copy = 0
                offset -= int(setr[2])
                setr = setr[1]
            if code_of(setr) != "reg":
                return False
            sreg, ssize = regno(setr), words(mode_of(setr))
            uq = qty_of(ureg) if ureg >= first else None
            if ((ureg >= first and rq(ureg) < 0)
                    or (offset > 0 and usize + offset > ssize) or (offset < 0 and usize + offset < ssize)
                    or (ssize > usize and ureg >= first and uq is not None and usize < uq.size)
                    or (sreg >= first and rq(sreg) == -1)
                    or (ureg >= first and insn.note("REG_NO_CONFLICT", ureg) is not None)
                    or ureg == sreg
                    or (ureg < first and sreg < first)
                    or ((mode_of(used) in FLOATISH) != (mode_of(setr) in FLOATISH))):
                return False
            if ureg < first:
                if rq(sreg) == -2:
                    reg_is_born(setr, 2 * n)
                sq = qty_of(sreg)
                if sq is not None:
                    add_sugg(sq, ureg, may_save_copy)
                return False
            if sreg < first:
                if uq is not None:
                    add_sugg(uq, sreg, may_save_copy)
                return False
            if rq(sreg) >= -1:
                return False
            s = self.stats.get(sreg, {})
            if ((already_dead or insn.note("REG_DEAD", ureg) is not None)
                    and (class_subset(s.get("pref", "GR_REGS"), uq.min_class, first)
                         or class_subset(uq.min_class, s.get("pref", "GR_REGS"), first))):
                self.reg_qty[sreg] = self.reg_qty[ureg]
                uq.offset[sreg] = uq.offset.get(ureg, 0) + offset
                uq.regs.insert(0, sreg)
                if class_subset(s.get("pref", "GR_REGS"), uq.min_class, first):
                    uq.min_class = s.get("pref", "GR_REGS")
                if class_subset(s.get("alt", "ALL_REGS"), uq.alt_class, first):
                    uq.alt_class = s.get("alt", "ALL_REGS")
                uq.calls += s.get("calls", 0)
                uq.refs += s.get("refs", 0)
                if usize < ssize:
                    for p in uq.regs:
                        uq.offset[p] = uq.offset.get(p, 0) - offset
                    uq.size, uq.mode = ssize, mode_of(setr)
                return True
            return False

        def note_stores(pat, fn):
            def one(e):
                dest = e[1]
                while ((code_of(dest) == "subreg" and code_of(dest[1]) != "reg")
                       or code_of(dest) in ("zero_extract", "sign_extract", "strict_low_part")):
                    dest = dest[1]
                fn(dest, code_of(e) == "clobber")
            c = code_of(pat)
            if c in ("set", "clobber"):
                one(pat)
            elif c == "parallel":
                for e in pat[1]:
                    if code_of(e) in ("set", "clobber"):
                        one(e)

        def reg_is_set(dest, is_clobber):
            if code_of(dest) in ("reg", "subreg"):
                g = regno(dest[1] if code_of(dest) == "subreg" else dest)
                if g >= first and self.reg_qty.get(g, -1) == -1 and g not in gopen:
                    gopen[g] = 2 * st["n"] - (1 if is_clobber else 0)
                reg_is_born(dest, 2 * st["n"] - (1 if is_clobber else 0))

        def fallback_ops(pat):
            """Operands when the md has no such pattern: op 0 = SET_DEST, then the registers of SET_SRC in order
            (not inside a MEM)."""
            if code_of(pat) != "set":
                return None
            ops = {0: pat[1]}
            src = pat[2]
            if code_of(src) in ("reg", "subreg"):
                ops[1] = src
                return ops
            k = [1]

            def walk(x):
                if code_of(x) in ("reg", "subreg"):
                    ops[k[0]] = x
                    k[0] += 1
                elif code_of(x) == "mem":
                    ops[k[0]] = x
                    k[0] += 1
                elif isinstance(x, list) and not isinstance(x, Vec):
                    for e in x[1:]:
                        if isinstance(e, list):
                            walk(e)
            walk(src)
            return ops

        a, b = pos[blk["first"]], pos[blk["last"]]
        for obj in chain[a:b + 1]:
            if obj.kind != "note":
                st["n"] += 1
                B.numbers[st["n"]] = obj.uid
            st["insn"] = obj
            n = st["n"]
            if obj.kind in INSN_KINDS and obj.pattern is not None:
                pat = obj.pattern
                win, r1 = False, None
                combined = None
                info = md_lookup(obj.name, self.cell) if (obj.code >= 0 and obj.name) else None
                ops = {}
                if obj.code >= 0:
                    if info is not None:
                        if not match(info["tmpl"], pat, ops):
                            B.warnings.append("insn %d {%s}: template did not match; operands guessed"
                                              % (obj.uid, obj.name))
                            ops = fallback_ops(pat) or {}
                            cons = {0: "=d", 1: "d", 2: "d"}
                            nops, nalts = max(ops) + 1 if ops else 0, 1
                        else:
                            cons, nops, nalts = info["cons"], info["nops"], info["nalts"]
                    else:
                        ops = fallback_ops(pat) or {}
                        cons = {k: ("=d" if k == 0 else "d") for k in ops}
                        nops, nalts = (max(ops) + 1 if ops else 0), 1
                        if ops:
                            B.warnings.append("insn %d {%s}: no md pattern; operands guessed" % (obj.uid, obj.name))
                    c0 = cons.get(0, "")
                    if nops > 1 and c0[:1] == "=" and c0[1:2] != "&":
                        must0, nmatch = -1, 0
                        for i in range(1, nops):
                            m = requires_inout(cons.get(i, ""))
                            nmatch += m
                            if m == nalts:
                                must0 = i
                        r0 = ops.get(0)
                        for i in range(1, nops):
                            ci = cons.get(i, "")
                            if (must0 >= 0 and i != must0
                                    and not (i == must0 + 1 and cons.get(i - 1, "")[:1] == "%")
                                    and not (i == must0 - 1 and ci[:1] == "%")):
                                continue
                            if nmatch == nalts and requires_inout(ci) == 0:
                                continue
                            r1 = ops.get(i)
                            if r1 is None:
                                continue
                            if ci[:1] == "p":
                                while code_of(r1) in ("plus", "mult"):
                                    r1 = r1[1]
                            if code_of(r0) in ("reg", "subreg"):
                                msc = ((code_of(pat) == "set" and pat[1] is r0 and pat[2] is r1)
                                       or (r1 is ops.get(i) and must0 >= 0))
                                if code_of(r1) in ("reg", "subreg"):
                                    win = combine_regs(r1, r0, msc)
                            if win:
                                break
                if code_of(pat) == "clobber" and obj.note("REG_LIBCALL") is not None:
                    B.warnings.append("insn %d: REG_LIBCALL no-conflict block tie is not modelled" % obj.uid)
                if win:
                    while code_of(r1) == "subreg":
                        r1 = r1[1]
                    combined = regno(r1)
                for k, x in obj.notes:
                    if k == "REG_DEAD" and code_of(x) == "reg" and regno(x) != combined:
                        wipe_dead_reg(x, 0)
                note_stores(pat, reg_is_set)
                for k, x in obj.notes:
                    if k == "REG_UNUSED" and code_of(x) == "reg":
                        wipe_dead_reg(x, 1)
                if obj.code >= 0 and info is not None:
                    for i in range(info["nops"]):
                        if info["kind"].get(i) != "scratch" or i not in ops:
                            continue
                        cls = scratch_class(info["cons"].get(i, ""))
                        if cls is None:
                            continue
                        x = ops[i]
                        q = Qty(n=len(B.qtys), regs=[], size=mode_bytes(mode_of(x)), mode=mode_of(x),
                                birth=2 * n - 1, death=2 * n + 1, calls=0, min_class=cls, alt_class="NO_REGS",
                                refs=1, birth_uid=obj.uid)
                        q.scratch = True
                        q.scratch_reg = regno(x) if code_of(x) == "reg" else -1
                        B.qtys.append(q)
            for i in (2 * n, 2 * n + 1):
                B.hard_at[i] |= st["regs_live"]
                rl = st["regs_live"]
                while rl:
                    low = rl & -rl
                    r = low.bit_length() - 1
                    B.hard_cause.setdefault((i, r), st["born"].get(r, "start"))
                    rl ^= low
        B.count = st["n"]
        for g, a0 in gopen.items():
            B.gspans[g].append((a0, 2 * st["n"] + 2))
        for q in B.qtys:
            if q.death < 0:
                B.warnings.append("qty %d (%s) has no recorded death" % (q.n, qlabel(q)))
        return B


def qlabel(q, names=None):
    if q.scratch:
        return "scratch@%d" % q.birth_uid
    return "+".join("%d%s" % (p, " %s" % names[p] if names and names.get(p) else "") for p in q.regs)


# ------------------------------------------------------------------------------------------ order + allocation

def small_sort(nq, cmp):
    """block_alloc's hand-coded 2/3-qty ordering: compare the literal qty NUMBERS 0,1 / 1,2 / 0,1, exchange
    POSITIONS (local-alloc.c, the `switch (next_qty)` before each qsort)."""
    order = list(range(nq))
    if nq == 3:
        if cmp(0, 1) > 0:
            order[0], order[1] = order[1], order[0]
        if cmp(1, 2) > 0:
            order[2], order[1] = order[1], order[2]
    if nq in (2, 3):
        if cmp(0, 1) > 0:
            order[0], order[1] = order[1], order[0]
    return order


def orders(qtys, first, key=None):
    """(sugg order, priority order) as block_alloc computes them.  `key(q)` -> (refs, length, size) overrides."""
    key = key or (lambda q: (q.refs, q.length, q.size))
    pri = [qty_pri(*key(q)) for q in qtys]
    sug = [len(q.copy) if q.copy else len(q.sugg) * first for q in qtys]
    nq = len(qtys)

    def cmp_s(a, b):
        return (sug[a] - sug[b]) if sug[a] != sug[b] else (pri[b] - pri[a])

    def cmp_p(a, b):
        return pri[b] - pri[a]
    if nq <= 3:
        so, po = small_sort(nq, cmp_s), small_sort(nq, cmp_p)
    else:
        so = sorted(range(nq), key=lambda q: (sug[q], -pri[q], q))
        po = sorted(range(nq), key=lambda q: (-pri[q], q))
    return so, po, pri


def allocate(B, first, caller_saves=True, key=None, geom=None, order_override=None):
    """Run the two passes of block_alloc on block B.  `geom` {qty: (birth, death)} overrides life (and key);
    `key` overrides the priority numbers only.  Returns {'phys', 'how', 'so', 'po', 'pri', 'owners'}."""
    qtys = B.qtys
    life = {q.n: (geom.get(q.n) if geom and q.n in geom else (q.birth, q.death)) for q in qtys}
    kf = key
    if kf is None:
        def kf(q):
            b, d = life[q.n]
            return (q.refs, d - b, q.size)
    so, po, pri = orders(qtys, first, kf)
    if order_override is not None:
        po = order_override
    live = dict(B.hard_at)
    owners = collections.defaultdict(list)                   # reg -> [(birth, death, qty)]
    fixed = sum(1 << r for r in FIXED_GPR) | sum(1 << r for r in range(67, first))   # $0 $at k0 k1 gp sp ra, ST/RAP
    call_used = fixed | sum(1 << r for r in CALL_USED_GPR) | (((1 << first) - 1) & ~((1 << 32) - 1) & ~0)
    ncopy = {q.n: len(q.copy) for q in qtys}
    phys = {q.n: -1 for q in qtys}
    how = {}

    def ffr(cls, q, accept, just, born, dead):
        if born < 0 or born > dead:
            return -1
        used = fixed if (accept or q.calls == 0) else call_used
        for i in range(born, dead):
            used |= live.get(i, 0)
        used |= ((1 << first) - 1) & ~class_mask(cls, first)
        used |= (1 << FP_REGNUM) | 1
        first_used = used
        if just:
            sset = q.copy if ncopy[q.n] else q.sugg
            first_used |= ((1 << first) - 1) & ~sum(1 << r for r in sset)
        i = 0
        while i < first:
            r = i
            if not (first_used >> r) & 1 and mode_ok(r, q.mode):
                size1 = words(q.mode) if r < 32 else 1
                j = 1
                while j < size1 and not (used >> (r + j)) & 1:
                    j += 1
                if j == size1:
                    for k in range(size1):
                        for x in range(born, dead):
                            live[x] = live.get(x, 0) | (1 << (r + k))
                        owners[r + k].append((born, dead, q.n))
                    return r
                i += j
            i += 1
        if just and ncopy[q.n] and q.sugg:
            ncopy[q.n] = 0
            return ffr(cls, q, accept, 1, born, dead)
        if not accept and caller_saves and not just and q.calls and 4 * q.calls < q.refs:
            return ffr(cls, q, 1, 0, born, dead)
        return -1

    step = 0
    for qn in so:
        q = qtys[qn]
        b, d = life[qn]
        if q.sugg or q.copy:
            phys[qn] = ffr(q.min_class, q, 0, 1, b, d)
            how[qn] = ("sugg", step)
            step += 1
        else:
            phys[qn] = -1
    for qn in po:
        q = qtys[qn]
        b, d = life[qn]
        if phys[qn] < 0:
            r = ffr(q.min_class, q, 0, 0, b, d)
            if r < 0 and q.alt_class != "NO_REGS":
                r = ffr(q.alt_class, q, 0, 0, b, d)
            phys[qn] = r
            how[qn] = ("prio", step)
            step += 1
    return {"phys": phys, "how": how, "so": so, "po": po, "pri": pri, "owners": owners, "life": life}


# ------------------------------------------------------------------------------------------ fidelity

def fidelity(fn, runs):
    """Compare every simulated register with the dump's `;; Register N in R.`: (agree, total, misses)."""
    res = fn.d["result"]
    agree, total, miss = 0, 0, []
    simreg = {}
    for B, run in zip(fn.blocks, runs):
        for q in B.qtys:
            if q.scratch:
                continue
            for p in q.regs:
                r = run["phys"][q.n]
                simreg[p] = r + q.offset.get(p, 0) if r >= 0 else -1
    for p, v in fn.reg_qty.items():
        if v == -1:
            continue
        total += 1
        s = simreg.get(p, -1)
        d = res.get(p, -1)
        if s == d:
            agree += 1
        else:
            miss.append((p, s, d))
    # pseudos the model left to global that local-alloc did place
    for p, d in res.items():
        if fn.reg_qty.get(p, -1) == -1:
            total += 1
            miss.append((p, -1, d))
    return agree, total, miss, simreg


def block_presence(fn):
    """{pseudo: {blocks where it is live at the start or mentioned}} - narrows alloc_need's BLOCKED holders."""
    out = collections.defaultdict(set)
    chain, pos = fn.d["chain"], fn.d["pos"]

    def regs(x, acc):
        if code_of(x) == "reg":
            r = regno(x)
            if r >= fn.first:
                acc.add(r)
        elif isinstance(x, list):
            for e in (x if isinstance(x, Vec) else x[1:]):
                if isinstance(e, list):
                    regs(e, acc)
    for blk in fn.d["blocks"]:
        acc = set(blk["live_pseudos"])
        if blk["first"] in pos and blk["last"] in pos:
            for o in chain[pos[blk["first"]]:pos[blk["last"]] + 1]:
                if o.pattern is not None:
                    regs(o.pattern, acc)
        for p in acc:
            out[p].add(blk["b"])
    return out


# ------------------------------------------------------------------------------------------ explanation

def idx_insn(B, i, term="death"):
    """Index -> uid of its insn: a death at 2N / 2N+1 is insn N's; a birth at 2N / 2N-1 is insn N's."""
    n = i // 2 if term == "death" else (i + 1) // 2
    return B.numbers.get(n)


def why_not(B, run, q, r, first, names=None, limit=4):
    """Why qty q did not get register r in this run: a list of reasons."""
    out = []
    b, d = run["life"][q.n]
    if r in FIXED_GPR:
        out.append("%s is fixed" % rname(r))
    if r == FP_REGNUM:
        out.append("$fp is never given out by local-alloc (eliminable register)")
    if q.calls and r in CALL_USED_GPR:
        out.append("%s is call-clobbered and the qty crosses %d call(s)" % (rname(r), q.calls))
    hard = sorted({B.hard_cause.get((i, r)) for i in range(b, d) if (B.hard_at.get(i, 0) >> r) & 1},
                  key=lambda u: (isinstance(u, str), u))
    if hard:
        idxs = [i for i in range(b, d) if (B.hard_at.get(i, 0) >> r) & 1]
        out.append("hard %s live over index %d..%d of the qty's %d..%d (set by %s)"
                   % (rname(r), idxs[0], idxs[-1], b, d,
                      ", ".join("insn %s" % u if u != "start" else "block entry" for u in hard[:limit])))
    step = run["how"].get(q.n, ("?", 10 ** 9))[1]
    for (ob, od, qn) in run["owners"].get(r, []):
        if qn == q.n:
            continue
        if ob < d and b < od and run["how"].get(qn, ("?", 10 ** 9))[1] < step:
            o = B.qtys[qn]
            kind, _s = run["how"][qn]
            out.append("qty %d (%s) took %s first over %d..%d (%s pass%s)"
                       % (qn, qlabel(o, names), rname(r), ob, od, "suggestion" if kind == "sugg" else "priority",
                          ", prio %d vs %d" % (run["pri"][qn], run["pri"][q.n]) if kind == "prio" else
                          ", suggested %s by insn %s" % (rname(r), (o.copy_src.get(r) or o.sugg_src.get(r)))))
    if run["how"].get(q.n, ("",))[0] == "sugg":
        sset = q.copy or q.sugg
        if r not in sset:
            out.append("the qty was placed in the SUGGESTION pass and %s is not among its suggestions %s"
                       % (rname(r), "{%s}" % ", ".join(rname(x) for x in sorted(sset))))
    return out


CALLEE_SAVED = set(range(16, 24)) | {30}
NEAR = 4                     # a GEOMETRY move of <= 4 indices (two insns) counts as a local explanation


def global_holders(fn, runs, p, r, names=None, limit=12):
    """Who holds hard register `r` inside GLOBAL pseudo p's life, block by block: the index overlap (local-alloc's
    index convention applied to p's set..death spans, not global.c's own conflict pass) of p with local qtys placed
    in r and with hard-register lives - the answer to alloc_need's BLOCKED "which local qty / which argument or
    return set" question.  [(block, kind, text)]"""
    out = []
    for B, run in zip(fn.blocks, runs):
        for (a0, b0) in B.gspans.get(p, []):
            for q in B.qtys:
                if run["phys"][q.n] < 0:
                    continue
                lo = run["phys"][q.n]
                hi = lo + (words(q.mode) if lo < 32 else 1)
                if lo <= r < hi and q.birth < b0 and a0 < q.death:
                    out.append((B.b, "qty", "block %d qty %d (%s) in %s over %d..%d, inside %d's span %d..%d (%s pass)"
                                % (B.b, q.n, qlabel(q, names), rname(r), q.birth, q.death, p, a0, b0,
                                   run["how"].get(q.n, ("?",))[0])))
            idxs = [i for i in range(max(a0, 0), b0) if (B.hard_at.get(i, 0) >> r) & 1]
            if idxs:
                uids = sorted({B.hard_cause.get((i, r)) for i in idxs}, key=lambda u: (isinstance(u, str), u))
                out.append((B.b, "hard", "block %d: hard %s live over %d..%d inside %d's span %d..%d (set by %s)"
                            % (B.b, rname(r), idxs[0], idxs[-1], p, a0, b0,
                               ", ".join("insn %s" % u if u != "start" else "block entry" for u in uids[:4]))))
            if len(out) >= limit:
                return out
    return out


def free_below(B, run, q, r, first):
    """Call-clobbered GRs below `r` that are free over q's life once every other qty is placed (this run):
    local-alloc takes the lowest free one, so each is a register q would take before r."""
    b, d = run["life"][q.n]
    busy = 0
    for i in range(b, d):
        busy |= B.hard_at.get(i, 0)
    for reg, spans in run["owners"].items():
        if any(ob < d and b < od and qn != q.n for ob, od, qn in spans):
            busy |= 1 << reg
    out = []
    for x in range(2, min(r, 32)):
        if x in FIXED_GPR or x == FP_REGNUM or (q.calls and x in CALL_USED_GPR):
            continue
        if not (busy >> x) & 1:
            out.append(x)
    return out


def qty_goal(B, run, retail, sim_ok):
    """{qty: retail reg} for reproduced, retail-known, non-scratch qtys."""
    goal = {}
    for q in B.qtys:
        if q.scratch or not q.regs:
            continue
        rs = {retail.get(p) - q.offset.get(p, 0) for p in q.regs if retail.get(p) is not None}
        if len(rs) != 1:
            continue
        if not all(sim_ok.get(p, False) for p in q.regs):
            continue
        goal[q.n] = rs.pop()
    return goal


def search_priority(B, first, caller_saves, goal, targets, base_run, limit_movers=None):
    """One qty's refs / length (priority KEY only) moved until the block colours like retail on every goal qty.
    Returns [(qty, term, value, now, crossed pair)]."""
    out = []
    qtys = B.qtys
    movers = limit_movers if limit_movers is not None else [q.n for q in qtys if not q.scratch]
    cache = {}

    def ok_for(kf):
        so, po, _pri = orders(qtys, first, kf)
        k = (tuple(so), tuple(po))
        if k not in cache:
            run = allocate(B, first, caller_saves, key=kf)
            cache[k] = (all(run["phys"][q] == r for q, r in goal.items()),
                        all(run["phys"][q] == goal[q] for q in targets), run)
        return cache[k]

    def base_key(q):
        return (q.refs, q.length, q.size)
    for x in movers:
        X = qtys[x]
        for term, rng in (("refs", range(X.refs + 1, max(4 * X.refs + 64, 80))),
                          ("refs", range(X.refs - 1, 0, -1)),
                          ("length", range(X.length - 1, 0, -1)),
                          ("length", range(X.length + 1, X.length * 8 + 400))):
            for v in rng:
                def kf(q, x=x, term=term, v=v):
                    r, L, s = base_key(q)
                    if q.n == x:
                        return (v, L, s) if term == "refs" else (r, v, s)
                    return (r, L, s)
                strict, loose, run = ok_for(kf)
                if strict:
                    out.append({"qty": x, "term": term, "value": v, "now": X.refs if term == "refs" else X.length,
                                "crossed": crossed(base_run["po"], run["po"], x), "run": run})
                    break
    return out


def crossed(po0, po1, x):
    """The qtys x moved past between two priority orders."""
    a, b = po0.index(x), po1.index(x)
    before0 = set(po0[:a])
    before1 = set(po1[:b])
    return sorted((before0 - before1) | (before1 - before0))


def search_geometry(B, first, caller_saves, goal, targets, movers, span=80, base_run=None):
    """One qty's death (or birth) moved - its key follows - until the block colours like retail."""
    out = []
    changed = {}
    top = 2 * B.count + 1
    for x in movers:
        X = B.qtys[x]
        found = {}
        for label, cands in (("death", [X.death - k for k in range(1, span) if X.death - k > X.birth]),
                             ("death", [X.death + k for k in range(1, span) if X.death + k <= top]),
                             ("birth", [X.birth + k for k in range(1, span) if X.birth + k < X.death]),
                             ("birth", [X.birth - k for k in range(1, span) if X.birth - k >= 0])):
            for v in cands:
                g = {x: (X.birth, v) if label == "death" else (v, X.death)}
                run = allocate(B, first, caller_saves, geom=g)
                if all(run["phys"][q] == r for q, r in goal.items()):
                    k = (label, v < (X.death if label == "death" else X.birth))
                    if k not in found:
                        found[k] = v
                        changed[k] = ({q: run["phys"][q] for q in run["phys"]
                                       if base_run and run["phys"][q] != base_run["phys"][q] and q != x})
                    break
        for (label, earlier), v in found.items():
            out.append({"qty": x, "term": label, "value": v, "now": X.death if label == "death" else X.birth,
                        "earlier": earlier, "insn": idx_insn(B, v, label), "then": changed.get((label, earlier), {})})
    return out


def explain(lreg, first, cell, retail=None, names=None, text=None, want=None, caller_saves=True, search=True,
            fn_name=None, global_got=None):
    """The whole analysis as a dict.  `retail` {pseudo: hard reg}; `want` limits the inverse to these pseudos
    (default: every mis-coloured local pseudo)."""
    fn = Function(lreg, first, cell, text=text, name=fn_name, caller_saves=caller_saves)
    runs = [allocate(B, first, caller_saves) for B in fn.blocks]
    agree, total, miss, simreg = fidelity(fn, runs)
    missset = {p for p, _s, _d in miss}
    sim_ok = {p: p not in missset for p in simreg}
    retail = retail or {}
    names = names or {}
    blocks = []
    for B, run in zip(fn.blocks, runs):
        if not B.qtys:
            continue
        rows = []
        for rank, qn in enumerate(run["po"]):
            q = B.qtys[qn]
            regs = q.regs
            dump = ({fn.d["result"].get(p, -1) - q.offset.get(p, 0) for p in regs} if regs
                    else {q.scratch_reg if q.scratch_reg is not None else -1})
            dump = dump.pop() if len(dump) == 1 else None
            rt = {retail.get(p) - q.offset.get(p, 0) for p in regs if retail.get(p) is not None}
            rows.append({"qty": qn, "rank": rank, "pseudos": list(regs), "scratch": q.scratch,
                         "name": ",".join(names.get(p, "") for p in regs if names.get(p)),
                         "refs": q.refs, "birth": q.birth, "death": q.death, "length": q.length, "size": q.size,
                         "calls": q.calls, "prio": run["pri"][qn], "birth_uid": q.birth_uid,
                         "death_uid": idx_insn(B, q.death) if q.death >= 0 else None,
                         "copy": sorted(q.copy), "sugg": sorted(q.sugg),
                         "copy_src": {rname(k): v for k, v in q.copy_src.items()},
                         "sugg_src": {rname(k): v for k, v in q.sugg_src.items()},
                         "pass": run["how"].get(qn, ("none", 0))[0], "sim": run["phys"][qn], "dump": dump,
                         "retail": rt.pop() if len(rt) == 1 else None})
        blocks.append({"b": B.b, "count": B.count, "nq": len(B.qtys), "sugg_order": [q for q in run["so"]
                       if B.qtys[q].copy or B.qtys[q].sugg], "rows": rows, "warnings": B.warnings,
                       "block": B, "run": run})
    # the inverse
    findings = []
    for blk in blocks:
        B, run = blk["block"], blk["run"]
        goal = qty_goal(B, run, retail, sim_ok)
        mis = [q for q, r in goal.items() if run["phys"][q] != r
               and (want is None or any(p in want for p in B.qtys[q].regs))]
        if not mis:
            continue
        for qn in mis:
            q = B.qtys[qn]
            r, h = goal[qn], run["phys"][qn]
            f = {"b": B.b, "qty": qn, "pseudos": list(q.regs), "got": h, "retail": r,
                 "why_not": why_not(B, run, q, r, first, names), "priority": [], "geometry": [],
                 "occupy": []}
            if h >= 0 and r > h:
                # retail is HIGHER: h must be busy over q's life - who has h in retail and could overlap
                f["occupy"] = [o.n for o in B.qtys if o.n != qn and goal.get(o.n) == h]
            f["free_below"] = free_below(B, run, q, r, first) if (h < 0 or r > h) else []
            # for local-alloc to give r, every lower free register must be busy over the qty's life in retail:
            # a local qty or a hard register can do that; a GLOBAL allocno cannot (global-alloc runs later)
            f["below"] = []
            for x in f["free_below"]:
                loc = [o.n for o in B.qtys if o.n != qn and goal.get(o.n) == x
                       and o.birth < q.death and q.birth < o.death]
                glo = [g for g, spans in B.gspans.items() if retail.get(g) == x
                       and any(a0 < q.death and q.birth < b0 for a0, b0 in spans)]
                unk = [o.n for o in B.qtys if o.n != qn and not o.scratch and o.n not in goal
                       and o.birth < q.death and q.birth < o.death]
                f["below"].append({"reg": x, "local": loc, "global": glo, "unknown": unk})
            f["holders_same"] = sorted({o for (ob, od, o) in run["owners"].get(r, [])
                                        if o != qn and ob < q.death and q.birth < od and goal.get(o) == r})
            if search:
                others = [o for o in goal if o != qn]
                # the target right, and every goal qty that is already right kept right
                strict_goal = {o: g for o, g in goal.items() if o == qn or run["phys"][o] == g}
                rel = sorted({qn} | {o for o in others}
                             | {o for (_b, _d, o) in run["owners"].get(r, [])})
                f["priority"] = [dict(s, run=None) for s in
                                 search_priority(B, first, caller_saves, strict_goal, [qn], run, rel)]
                geo_movers = sorted({qn} | {o for (ob, od, o) in run["owners"].get(r, [])
                                           if ob < q.death and q.birth < od and o != qn})
                f["geometry"] = search_geometry(B, first, caller_saves, strict_goal, [qn], geo_movers, base_run=run)
            # "not a local qty in retail": some lower register has no local holder in retail, none of unknown colour,
            # and no single priority / life change of this block reaches retail
            f["not_local"] = (bool(f["below"]) and any(not e["local"] and not e["unknown"] for e in f["below"])
                              and not f["priority"]
                              and not any(abs(g["value"] - g["now"]) <= NEAR for g in f["geometry"]))
            findings.append(f)
    # global pseudos whose register differs from retail's: who holds retail's register inside their life
    gfind = {}
    for p, got in (global_got or {}).items():
        r = retail.get(p)
        if r is None or got == r or fn.reg_qty.get(p, -1) != -1 or (want is not None and p not in want):
            continue
        gfind[p] = {"got": got, "retail": r, "holders": global_holders(fn, runs, p, r, names)}
    return {"function": fn.name, "fidelity": (agree, total), "misses": miss, "blocks": blocks, "runs": runs,
            "global_findings": gfind,
            "findings": findings, "warnings": fn.warnings + [w for b in blocks for w in b["warnings"]],
            "simreg": simreg, "reg_qty": {p: v for p, v in fn.reg_qty.items()}, "fn": fn}


# ------------------------------------------------------------------------------------------ printing

def plabel(ps, names):
    return "+".join("%d%s" % (p, " (%s)" % names[p] if names.get(p) else "") for p in ps)


def index_words(v, uid, term):
    """block_alloc indices: 2N = insn N itself (a REG_DEAD death / a SET birth), 2N+1 = past insn N (a REG_UNUSED
    death), 2N-1 = just before insn N (a CLOBBER birth)."""
    if term == "death":
        return ("last use at insn #%d (uid %s)" % (v // 2, uid)) if v % 2 == 0 else \
            ("live past insn #%d (uid %s)" % (v // 2, uid))
    n = (v + 1) // 2
    return ("set by insn #%d (uid %s)" % (n, uid)) if v % 2 == 0 else ("clobbered before insn #%d (uid %s)" % (n, uid))


def fmt_finding(f, blk_rows, names):
    """Lines for one mis-coloured local qty."""
    rows = {r["qty"]: r for r in blk_rows}
    me = rows[f["qty"]]
    out = ["LOCAL %s (block %d, qty %d, rank %d; refs %d, life %d..%d = %d, prio %d, %s pass): got %s, retail %s"
           % (plabel(f["pseudos"], names), f["b"], f["qty"], me["rank"], me["refs"], me["birth"], me["death"],
              me["length"], me["prio"], me["pass"], rname(f["got"]), rname(f["retail"]))]
    for w in f["why_not"]:
        out.append("  %s not free: %s" % (rname(f["retail"]), w))
    if not f["why_not"]:
        out.append("  %s was free over the qty's life: the qty took %s because %s" % (
            rname(f["retail"]), rname(f["got"]),
            "a suggestion put it there" if me["pass"] == "sugg" else "%s is lower (lowest free register wins)"
            % rname(f["got"])))
    if f.get("below"):
        parts = []
        for e in f["below"][:8]:
            who = (["qty %d" % o for o in e["local"]] + ["GLOBAL %s" % plabel([g], names) for g in e["global"]]
                   + ["qty %d (retail unknown)" % o for o in e["unknown"][:3]])
            parts.append("%s: %s" % (rname(e["reg"]), ", ".join(who) if who else "nobody"))
        out.append("  retail %s is above %d register(s) free over the qty's life; local-alloc takes the lowest free, "
                   "so in retail each must be busy there - retail's holders: %s"
                   % (rname(f["retail"]), len(f["free_below"]), "; ".join(parts)))
    if f.get("not_local"):
        out.append("  NOT A LOCAL QTY IN RETAIL (likely): no local qty holds %s in retail over this life (a GLOBAL "
                   "allocno cannot: global-alloc runs after local-alloc)%s, and no priority change or life shift of "
                   "<= %d indices reaches retail.  Retail's value is a global allocno - a use in a second block, a "
                   "second death, or a call inside its life; lever: that, not a local order."
                   % (" ".join(rname(e["reg"]) for e in f["below"] if not e["local"]),
                      "; %s is callee-saved and the qty crosses no call" % rname(f["retail"])
                      if f["retail"] in CALLEE_SAVED else "", NEAR))
    if f["occupy"]:
        out.append("  retail is HIGHER than %s: %s must be busy over the qty's life - retail has %s in %s"
                   % (rname(f["got"]), rname(f["got"]), rname(f["got"]),
                      ", ".join("qty %d (%s)" % (o, plabel(rows[o]["pseudos"], names)) for o in f["occupy"])))
    for s in f["priority"]:
        o = rows[s["qty"]]
        op = ">=" if (s["term"] == "refs") == (s["value"] > s["now"]) else "<="
        if s["term"] == "length":
            op = "<=" if s["value"] < s["now"] else ">="
        pair = ", ".join("qty %d (%s, prio %d)" % (c, plabel(rows[c]["pseudos"], names), rows[c]["prio"])
                         for c in s["crossed"][:4])
        out.append("  PRIORITY: qty %d (%s) %s %s %d (now %d)%s" % (
            s["qty"], plabel(o["pseudos"], names), s["term"], op, s["value"], s["now"],
            "; it then crosses %s" % pair if pair else ""))
    for g in f["geometry"]:
        o = rows[g["qty"]]
        out.append("  GEOMETRY: qty %d (%s) %s at index %d instead of %d: %s" % (
            g["qty"], plabel(o["pseudos"], names), "dies" if g["term"] == "death" else "is born", g["value"],
            g["now"], index_words(g["value"], g["insn"], g["term"]))
                   + ("; then %s" % ", ".join("qty %d (%s) takes %s" % (k, plabel(rows[k]["pseudos"], names), rname(v))
                                             for k, v in sorted(g.get("then", {}).items())[:4])
                      if g.get("then") else ""))
    same = [o for o in f.get("holders_same", [])]
    if same:
        out.append("  retail gives %s the same register %s: in retail their lives do not overlap, so no priority "
                   "order can do it - a GEOMETRY question (whose last use comes first)"
                   % (", ".join("qty %d (%s)" % (o, plabel(rows[o]["pseudos"], names)) for o in same),
                      rname(f["retail"])))
    if not f["priority"] and not f["geometry"]:
        out.append("  no single priority or single life change of the block's qtys gives retail's colouring "
                   "(with every other reproduced qty kept at retail)")
    return out


def render(res, names=None, show_all=False, only_blocks=None):
    names = names or {}
    out = []
    a, t = res["fidelity"]
    out.append("# lreg_explain %s: local-alloc replay reproduces %d of %d local pseudos%s"
               % (res["function"], a, t, "" if a == t else " - misses: " + ", ".join(
                   "%d sim %s dump %s" % (p, rname(s), rname(d)) for p, s, d in res["misses"][:12])))
    for w in res["warnings"][:12]:
        out.append("# warning: " + w)
    fb = {f["b"] for f in res["findings"]}
    for blk in res["blocks"]:
        if only_blocks is not None and blk["b"] not in only_blocks:
            continue
        if not show_all and blk["b"] not in fb and only_blocks is None:
            continue
        out.append("")
        out.append("## block %d: %d insns, %d qtys; suggestion pass order: %s" % (
            blk["b"], blk["count"], blk["nq"], " ".join(str(q) for q in blk["sugg_order"]) or "-"))
        head = ["rank", "qty", "pseudos", "refs", "birth", "death", "len", "sz", "calls", "prio", "sugg", "pass",
                "sim", "dump", "retail"]
        body = []
        for r in blk["rows"]:
            sug = " ".join(["c" + rname(x) for x in r["copy"]] + ["a" + rname(x) for x in r["sugg"]])
            body.append([r["rank"], r["qty"], ("scratch@%d" % r["birth_uid"]) if r["scratch"] else
                         plabel(r["pseudos"], names), r["refs"], "%d/%s" % (r["birth"], r["birth_uid"]),
                         "%d/%s" % (r["death"], r["death_uid"]), r["length"], r["size"], r["calls"], r["prio"],
                         sug, r["pass"], rname(r["sim"]), rname(r["dump"]) + ("" if r["dump"] == r["sim"] else "!"),
                         rname(r["retail"]) if r["retail"] is not None else ""])
        out.append(kitlib.fmt_table(head, body))
        for f in res["findings"]:
            if f["b"] == blk["b"]:
                out.extend(fmt_finding(f, blk["rows"], names))
    for p, g in sorted(res.get("global_findings", {}).items()):
        out.append("")
        out.append("GLOBAL %s (not a local qty: several blocks, several deaths or a spilled class): got %s, retail %s; "
                   "%s inside its life:" % (plabel([p], names), rname(g["got"]),
                              rname(g["retail"]), rname(g["retail"])))
        for _b, _k, t in g["holders"] or [(None, None, "nothing local-alloc placed (nor a hard register) - a GLOBAL "
                                          "allocno holds it: alloc_need's ORDER / BLOCKED question")]:
            out.append("  " + t)
    if not res["findings"]:
        out.append("no mis-coloured local qty to invert (retail known and reproduced)")
    return "\n".join(out)


def summary_lines(res, names=None, pseudos=None):
    """Compact per-pseudo lines for alloc_need: {pseudo: [lines]}."""
    names = names or {}
    out = {}
    rowsb = {b["b"]: b["rows"] for b in res["blocks"]}
    for f in res["findings"]:
        lines = fmt_finding(f, rowsb[f["b"]], names)
        for p in f["pseudos"]:
            if pseudos is None or p in pseudos:
                out[p] = lines
    return out


def jsonable(res):
    def conv(o):
        if isinstance(o, dict):
            return {str(k): conv(v) for k, v in o.items() if k not in ("block", "run", "fn", "runs")}
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
    ap.add_argument("--cfg", help="compile at this cfg (no ledger write)")
    ap.add_argument("--retail", default="listing", choices=["listing", "none"],
                    help="retail registers from alloc_need's listing votes (one byte score), or none")
    ap.add_argument("--retail-set", action="append", default=[], metavar="P=REG",
                    help="retail register of a pseudo or variable by hand (118=$v0, speed=$v1; repeatable, "
                         "overrides the listing) - for rows the scorer cannot map")
    ap.add_argument("--block", type=int, action="append", help="print this block (repeatable)")
    ap.add_argument("--pseudo", type=int, action="append", help="invert only these pseudos")
    ap.add_argument("--all", action="store_true", help="print every block, not only those with a finding")
    ap.add_argument("--no-search", action="store_true", help="skip the priority / geometry searches")
    ap.add_argument("--json", help="also write the analysis here (inside the lane)")
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
            raise SystemExit("lreg_explain: %r is neither 'pinned', 'erased' nor a file" % a.text)
        text = p.read_text(errors="replace")
    kitlib.add_paths()
    if not (_HERE / "kitlib.py").is_file() and (_HERE.parents[1] / "alloc_sim.py").is_file():
        sys.path.insert(0, str(_HERE.parents[1]))
    import alloc_sim as sim                                              # noqa: E402
    from common import parse_cfg                                         # noqa: E402
    cell, flags = parse_cfg(row["cfg"])
    first = sim.FIRST.get(cell)
    if first is None:
        raise SystemExit("lreg_explain: no FIRST_PSEUDO_REGISTER for cell %s" % cell)
    caller_saves = "-fno-caller-saves" not in flags
    retail, names = {}, {}
    dp = sim.decl_pseudos(text, first)
    names = {v: k for k, v in ((dp or {}).get("map") or {}).items()}
    if a.retail == "listing":
        sys.path.insert(0, str(_HERE))                                   # this kit's alloc_need (a lane copy too)
        import alloc_need                                                # noqa: E402
        an = alloc_need.analyse(row, text, base, explain_local=False)
        if an.get("error"):
            raise SystemExit("lreg_explain: " + an["error"])
        retail = {p: it["retail"] for p, it in an["table"].items() if it["retail"] is not None}
        print("# retail registers: %d pseudos from the listing (%s)" % (
            len(retail), "EXACT text" if an["exact"] else "scorer total %s" % an["total"]))
    byname = {v: k for k, v in names.items()}
    for item in a.retail_set:
        k, _, v = item.partition("=")
        v = v.strip().lstrip("$")
        reg = int(v) if v.isdigit() else (REGNAME.index(v) if v in REGNAME else None)
        p = int(k) if k.strip().isdigit() else byname.get(k.strip())
        if reg is None or p is None:
            raise SystemExit("lreg_explain: --retail-set %r: need PSEUDO|VARIABLE=REG" % item)
        retail[p] = reg
    d = kitlib.dumps(row, text, want={"lreg", "greg"})
    if d is None or d.get("error"):
        raise SystemExit("lreg_explain: does not build: %s" % ((d or {}).get("error") or "")[-300:])
    _order, disp = sim.parse_greg(d.get("greg", ""))
    res = explain(d["lreg"], first, cell, retail=retail, names=names, text=text,
                  want=set(a.pseudo) if a.pseudo else None, caller_saves=caller_saves, search=not a.no_search,
                  global_got={p: h for p, h in disp.items() if p >= first})
    print(render(res, names, a.all, set(a.block) if a.block else None))
    if a.json:
        Path(a.json).write_text(json.dumps(jsonable(res), indent=1, sort_keys=True, default=str))


if __name__ == "__main__":
    main()
