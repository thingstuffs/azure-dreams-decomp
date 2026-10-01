#!/usr/bin/env python3
"""fragclone - PARTIAL clones: pin-free rows that share a long RETAIL code fragment with a pinned row.

APPEARS.  clone_transfer.py replays a solved row onto WHOLE-function siblings; on the round-85 tree it
finds 0 siblings for the pinned rows.  Yet four rows went pin-free in round 85 by pasting a FRAGMENT of
a pin-free row (dungeon/func_818B1664's probe loop + destination block compile word for word to retail
inside 818C3B90, 818AAE60, 818B7F38 and 818BDEBC).  Nothing looked for such fragments.

WHAT IT DOES (CPU only, no scorer, nothing written outside the lane / --out):
  1. UNITS.  Every row's retail words: overlay rows from work/disc/containers/<C>.BIN at (foff, size);
     slus module rows split into their defs (address -> PS-X EXE offset, size from config/func_sizes.json).
     A unit is PINNED when pin_census.sites_of finds live sites in its src/ text (slus: in its def's body).
  2. TOKENS.  Each word is decoded (MIPS I + COP2) to a COARSE token: mnemonic (move/b/beqz/bnez/negu
     pseudo-forms recognised) + operand shape, with every allocatable register -> `r` ($zero/$sp/$ra/$gp/
     $at kept), immediates, offsets, branch and jump targets dropped.  A FINE key (immediates/offsets/
     shift amounts/jal targets kept, registers dropped) and the register operands are kept for scoring.
  3. MATCH.  Every k-gram (--seed, default 8) of a pin-free unit is indexed (grams found in more than
     --maxfreq units are not seeds: prologue/epilogue boilerplate); each pinned unit's grams look the
     index up, extend to MAXIMAL exact runs on each diagonal, and runs of one pair are CHAINED (gaps of at
     most --gap tokens on each side: a moved insn, a different constant load).  A pair is a candidate when
     its best chain matches >= --min tokens (default 12).
  4. PIN FOOTPRINT.  Each live pin of a pinned unit is erased alone (pin_sites.erase_many) and the cc1
     listing (xform.screen, ~30 ms) is diffed against the pinned listing; the changed listing insns are
     mapped to RETAIL word indices (the pinned listing is retail's insn order; class-level LCS alignment).
     A chain OVERLAPS a pin when it covers any of that pin's footprint words.
  5. C SPANS (top --spans pairs).  The source unit (and the pinned unit) is compiled with `-g`; `.loc`
     lines give each listing insn its C line; the chain's retail range maps to a C line span.

    cd work/native_lane/<lane> && source ../../../tools/lanes/lanekit/env.sh
    python3 tools/lanes/fragclone.py [--out candidates.tsv] [--json cands.jsonl] [--workers 8]
                         [--only dungeon/func_X ...] [--seed 8] [--min 12] [--gap 4] [--maxfreq 30]
                         [--trust 0.85] [--spans 60] [--no-footprint]
    python3 tools/lanes/fragclone.py --show dungeon/func_PINNED dungeon/func_SOURCE   # one pair, word by word

~15 s for the whole tree (7,037 units, 568k words; 185 pinned) on 8 workers.  Writes <out> (every pair) and
<out stem>_by_row.tsv (best source per pinned row); footprints are cached in <lane>/tmp/fragclone_cache.

ROUND 85 (r85_opus_fragclone).  Validation: it rediscovers the r85 fragment (818C3B90 <- 818B1664: a 178-word
chain, imm_eq 0.91 / reg_bij 0.93).  It found FOUR whole-function retail clones of pinned rows that
clone_transfer (C-text similarity) cannot see because the two C texts were written independently -
80F03000 <- 80EE5000 (438/438), 80A4B678 <- 80B9ADE0 (124/124, the clone at a stock cell), 818FECCC <-
818CEB58 (72/72, 2.6.3 -> cdk), 81976CB0 <- 81976F70 (176 words, near) - and fragments that carried a pin
site: 80283000 <- 804FE87C (an inline helper's parameter order), 80E64FF0 <- 81326D28 (interpolation block).
Read a pair with --show before porting: '*' rows are immediates (address deltas of an overlay copy, a sign),
'!' rows the words the chain bridged.

Ranked: chains overlapping pins first (by footprint words covered), then by matched length.
Columns: see HEADER.  imm_eq = share of matched words whose immediates/offsets/targets agree; reg_bij =
share whose registers fit ONE consistent renaming (a fragment of the same C has both near 1.0).
"""
from __future__ import annotations

import argparse
import collections
import difflib
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for sub in ("tools", "tools/xform", "tools/lanes", "tools/lanes/lanekit"):
    if str(ROOT / sub) not in sys.path:
        sys.path.insert(0, str(ROOT / sub))

from common import rows, clean_path, parse_cfg          # noqa: E402
from pin_census import sites_of                          # noqa: E402

CONTAINERS = {"dungeon": "DUNGEON_DUNGEON.BIN", "town": "TOWN_TOWN.BIN", "main": "MAIN_MAIN.BIN",
              "ovmovie": "OVMOVIE_OVMOVIE.BIN"}
SLUS_EXE = ROOT / "baserom/slus_006.14"

# ----------------------------------------------------------------------------------- decoder

SPECIAL = {0: "sll", 2: "srl", 3: "sra", 4: "sllv", 6: "srlv", 7: "srav", 8: "jr", 9: "jalr", 12: "syscall",
           13: "break", 16: "mfhi", 17: "mthi", 18: "mflo", 19: "mtlo", 24: "mult", 25: "multu", 26: "div",
           27: "divu", 32: "add", 33: "addu", 34: "sub", 35: "subu", 36: "and", 37: "or", 38: "xor",
           39: "nor", 42: "slt", 43: "sltu"}
REGIMM = {0: "bltz", 1: "bgez", 16: "bltzal", 17: "bgezal"}
IOPS = {8: "addi", 9: "addiu", 10: "slti", 11: "sltiu", 12: "andi", 13: "ori", 14: "xori"}
BR2 = {4: "beq", 5: "bne"}
BR1 = {6: "blez", 7: "bgtz"}
MEM = {32: "lb", 33: "lh", 34: "lwl", 35: "lw", 36: "lbu", 37: "lhu", 38: "lwr", 40: "sb", 41: "sh",
       42: "swl", 43: "sw", 46: "swr", 50: "lwc2", 58: "swc2"}
SPECIAL_REGS = {0: "0", 1: "at", 28: "gp", 29: "sp", 31: "ra"}


def rc(r):
    return SPECIAL_REGS.get(r, "r")


def decode(w):
    """(coarse, fine, regs, cls) for one word.  coarse: mnemonic + register shape; fine: immediates;
    regs: the allocatable register operands in order; cls: alignment class (ld/st/br/j/alu/nop)."""
    if w == 0:
        return "nop", "nop", (), "nop"
    op = w >> 26
    rs, rt, rd, sa, fn, imm = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, (w >> 6) & 31, w & 63, w & 0xFFFF
    simm = imm - 0x10000 if imm & 0x8000 else imm
    if op == 0:
        m = SPECIAL.get(fn, "sp%d" % fn)
        if m in ("addu", "or") and rt == 0:
            return "move %s,%s" % (rc(rd), rc(rs)), "move", (rd, rs), "alu"
        if m == "subu" and rs == 0:
            return "negu %s,%s" % (rc(rd), rc(rt)), "negu", (rd, rt), "alu"
        if m in ("sll", "srl", "sra"):
            return "%s %s,%s" % (m, rc(rd), rc(rt)), "%s %d" % (m, sa), (rd, rt), "alu"
        if m == "jr":
            return "jr %s" % rc(rs), "jr", (rs,), "j"
        if m == "jalr":
            return "jalr %s,%s" % (rc(rd), rc(rs)), "jalr", (rd, rs), "j"
        if m in ("mfhi", "mflo"):
            return "%s %s" % (m, rc(rd)), m, (rd,), "alu"
        if m in ("mthi", "mtlo"):
            return "%s %s" % (m, rc(rs)), m, (rs,), "alu"
        if m in ("mult", "multu", "div", "divu"):
            return "%s %s,%s" % (m, rc(rs), rc(rt)), m, (rs, rt), "alu"
        if m in ("syscall", "break"):
            return m, "%s %d" % (m, (w >> 6) & 0xFFFFF), (), "alu"
        return "%s %s,%s,%s" % (m, rc(rd), rc(rs), rc(rt)), m, (rd, rs, rt), "alu"
    if op == 1:
        m = REGIMM.get(rt, "regimm%d" % rt)
        return "%s %s" % (m, rc(rs)), m, (rs,), "br"
    if op in (2, 3):
        m = "j" if op == 2 else "jal"
        return m, "%s %07x" % (m, w & 0x3FFFFFF) if op == 3 else m, (), "j"
    if op in BR2:
        m = BR2[op]
        if rs == 0 and rt == 0 and op == 4:
            return "b", "b", (), "br"
        if rt == 0:
            return "%sz %s" % (m, rc(rs)), m + "z", (rs,), "br"
        return "%s %s,%s" % (m, rc(rs), rc(rt)), m, (rs, rt), "br"
    if op in BR1:
        return "%s %s" % (BR1[op], rc(rs)), BR1[op], (rs,), "br"
    if op in IOPS:
        m = IOPS[op]
        if rs == 0 and m in ("addiu", "ori"):
            return "li %s" % rc(rt), "li %d" % (simm if m == "addiu" else imm), (rt,), "alu"
        return "%s %s,%s" % (m, rc(rt), rc(rs)), "%s %d" % (m, simm if m in ("addi", "addiu", "slti", "sltiu") else imm), (rt, rs), "alu"
    if op == 15:
        return "lui %s" % rc(rt), "lui %d" % imm, (rt,), "lui"
    if op in MEM:
        m = MEM[op]
        cls = "st" if m.startswith("s") else "ld"
        return "%s %s,(%s)" % (m, rc(rt) if op < 48 else "c", rc(rs)), "%s %d" % (m, simm), \
            ((rt, rs) if op < 48 else (rs,)), cls
    if 16 <= op <= 19:
        z = op - 16
        sub = rs
        if sub in (0, 2, 4, 6):        # mfc / cfc / mtc / ctc
            m = {0: "mfc", 2: "cfc", 4: "mtc", 6: "ctc"}[sub] + str(z)
            return "%s %s" % (m, rc(rt)), "%s %d" % (m, rd), (rt,), "alu"
        return "cop%d" % z, "cop%d %07x" % (z, w & 0x1FFFFFF), (), "alu"
    return "op%d" % op, "op%d" % op, (), "alu"


# ------------------------------------------------------------------------------------- units

def slus_def_spans(text, defs):
    """{def: (start, end)} character spans of each def's body in a module text (start = its header)."""
    pos = []
    for d in defs:
        m = re.search(r"^[^\n;#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(d), text, re.M)
        if m:
            pos.append((m.start(), d))
    pos.sort()
    return {d: (s, pos[i + 1][0] if i + 1 < len(pos) else len(text)) for i, (s, d) in enumerate(pos)}


def load_units(only_pinned=None):
    """[{id, unit, row, func, words, pins, sites, cfg, text_path}]"""
    sizes = json.loads((ROOT / "config/func_sizes.json").read_text())
    blobs = {}
    exe = SLUS_EXE.read_bytes()
    t_addr = struct.unpack("<I", exe[0x18:0x1C])[0]
    out = []
    for r in rows():
        p = clean_path(r)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        sites = sites_of(text) if "ASM_" in text else []
        if r["kind"] == "overlay":
            if r.get("foff") is None or not r.get("size"):
                continue
            c = r["container"]
            if c not in blobs:
                blobs[c] = (ROOT / "work/disc/containers" / CONTAINERS[c]).read_bytes()
            b = blobs[c][int(r["foff"]):int(r["foff"]) + int(r["size"])]
            words = list(struct.unpack("<%dI" % (len(b) // 4), b[:len(b) // 4 * 4]))
            out.append(dict(unit=r["id"], row=r["id"], func=r.get("true_name") or r["func"], words=words,
                            loc=(c, int(r["foff"])),
                            pins=len(sites), sites=[s[:3] + (s[5],) for s in sites], cfg=r["cfg"]))
        elif r["kind"] == "slus":
            spans = slus_def_spans(text, r.get("defs") or [])
            for d in r.get("defs") or []:
                if d not in sizes or d not in spans or not re.match(r"func_[0-9A-F]{8}$", d):
                    continue            # `defs` also lists extern-declared callees: only bodies are units
                a = int(d[5:], 16)
                off = a - t_addr + 0x800
                b = exe[off:off + sizes[d]]
                words = list(struct.unpack("<%dI" % (len(b) // 4), b[:len(b) // 4 * 4]))
                s0, s1 = spans.get(d, (None, None))
                mine = [s for s in sites if s0 is not None and s0 <= s[3] < s1]
                out.append(dict(unit="%s:%s" % (r["id"], d), row=r["id"], func=d, words=words, pins=len(mine),
                                loc=("slus", off),
                                sites=[s[:3] + (s[5],) for s in mine], cfg=r["cfg"]))
    return out


# --------------------------------------------------------------------------------- matching

def tokenise(units):
    intern = {}
    for u in units:
        dec = [decode(w) for w in u["words"]]
        u["tok"] = [intern.setdefault(d[0], len(intern)) for d in dec]
        u["fine"] = [d[1] for d in dec]
        u["regs"] = [d[2] for d in dec]
        u["cls"] = [d[3] for d in dec]
    return intern


def build_index(units, free_idx, k):
    idx = collections.defaultdict(list)
    for ui in free_idx:
        t = units[ui]["tok"]
        for i in range(len(t) - k + 1):
            idx[hash(tuple(t[i:i + k]))].append((ui, i))
    return idx


def unit_freq(idx):
    return {h: len({u for u, _ in v}) for h, v in idx.items()}


def maximal_runs(a, b, seeds):
    """seeds: [(i, j)] equal k-grams; -> maximal exact runs [(i, j, n)] (dedup per diagonal)."""
    seen = {}
    runs = []
    for i, j in sorted(seeds):
        d = j - i
        if seen.get(d, -1) > i:
            continue
        s, t = i, j
        while s > 0 and t > 0 and a[s - 1] == b[t - 1]:
            s -= 1
            t -= 1
        e, f = i, j
        while e < len(a) and f < len(b) and a[e] == b[f]:
            e += 1
            f += 1
        seen[d] = e
        runs.append((s, t, e - s))
    return runs


def bridge_runs(a, b, runs, gap, minlen=3):
    """Short exact runs (>= minlen; too short to be seeded) in the gap windows just after / before each
    maximal run, offset by 0..gap on each side: they let a chain cross a moved insn or a changed load."""
    out = []
    for s0, t0, L in runs:
        for di in range(0, gap + 1):
            for dj in range(0, gap + 1):
                if di == dj == 0:
                    continue
                s, t = s0 + L + di, t0 + L + dj            # after
                n = 0
                while s + n < len(a) and t + n < len(b) and a[s + n] == b[t + n]:
                    n += 1
                if n >= minlen:
                    out.append((s, t, n))
                e, f = s0 - di, t0 - dj                    # before (run ends at e/f, exclusive)
                n = 0
                while e - n - 1 >= 0 and f - n - 1 >= 0 and a[e - n - 1] == b[f - n - 1]:
                    n += 1
                if n >= minlen:
                    out.append((e - n, f - n, n))
    return out


def chains(runs, gap, top=3):
    """Chain runs (increasing in both a and b, gaps <= gap on each side); greedy best-first, up to `top`
    disjoint chains -> [(matched, [runs])]."""
    runs = sorted(set(runs))
    used = set()
    out = []
    for _ in range(top):
        best = None
        n = len(runs)
        score = [0] * n
        prev = [-1] * n
        for x in range(n):
            if x in used:
                continue
            i, j, L = runs[x]
            score[x] = L
            for y in range(x):
                if y in used or score[y] == 0:
                    continue
                i2, j2, L2 = runs[y]
                gi, gj = i - (i2 + L2), j - (j2 + L2)
                if 0 <= gi <= gap and 0 <= gj <= gap and score[y] + L > score[x]:
                    score[x] = score[y] + L
                    prev[x] = y
            if best is None or score[x] > score[best]:
                best = x
        if best is None or score[best] == 0:
            break
        ch = []
        x = best
        while x >= 0:
            ch.append(runs[x])
            used.add(x)
            x = prev[x]
        ch.reverse()
        out.append((score[best], ch))
        # drop runs overlapping the chain in a (a fragment of `a` is claimed once)
        lo, hi = ch[0][0], ch[-1][0] + ch[-1][2]
        for x, (i, j, L) in enumerate(runs):
            if i < hi and i + L > lo:
                used.add(x)
    return out


def quality(ua, ub, ch):
    """(imm_eq, reg_bij) over the matched words of one chain."""
    eq = n = 0
    fwd, bwd = {}, {}
    ok = 0
    for i, j, L in ch:
        for k in range(L):
            a, b = i + k, j + k
            n += 1
            eq += ua["fine"][a] == ub["fine"][b]
            good = True
            for ra, rb in zip(ua["regs"][a], ub["regs"][b]):
                if ra in SPECIAL_REGS or rb in SPECIAL_REGS:
                    continue
                if fwd.get(ra, rb) != rb or bwd.get(rb, ra) != ra:
                    good = False
            if good:
                ok += 1
                for ra, rb in zip(ua["regs"][a], ub["regs"][b]):
                    if ra not in SPECIAL_REGS and rb not in SPECIAL_REGS:
                        fwd.setdefault(ra, rb)
                        bwd.setdefault(rb, ra)
    return (eq / n if n else 0.0), (ok / n if n else 0.0)


# ---------------------------------------------------------------------- listings and spans

LCLS = [(re.compile(r"^(lb|lbu|lh|lhu|lw|lwl|lwr|lwc2|ulw|ulh|ulhu)\b"), "ld"),
        (re.compile(r"^(sb|sh|sw|swl|swr|swc2|usw|ush)\b"), "st"),
        (re.compile(r"^(b|beq|bne|beqz|bnez|bgez|bgtz|blez|bltz|bgezal|bltzal|beql|bnel)\b"), "br"),
        (re.compile(r"^(j|jal|jr|jalr)\b"), "j"),
        (re.compile(r"^lui\b"), "lui"),
        (re.compile(r"^nop\b"), "nop")]


def lcls(s):
    for rx, c in LCLS:
        if rx.match(s):
            return c
    return "alu"


def raw_listing(row, text, g=False):
    """cc1's raw listing (screen._listing's commands, + -g when asked).  None when it does not build."""
    cell, flags = parse_cfg(row["cfg"])
    D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="fragclone_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(ROOT / "include"),
                            "-w", f.name, "-o", "f.i"], cwd=d, capture_output=True, text=True, timeout=60)
        if r.returncode:
            return None
        r = subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", *(["-g"] if g else []), *flags, "-w",
                            "-o", "f.s"], cwd=d, capture_output=True, text=True, timeout=60)
        if r.returncode:
            return None
        return (d / "f.s").read_text(errors="replace").splitlines(), f.name


def split_funcs(lines):
    """{name: [raw lines from .ent to .end]}"""
    out, cur, name = {}, None, None
    for ln in lines:
        s = ln.strip()
        if s.startswith(".ent"):
            name = s.split()[1]
            cur = [ln]
        elif cur is not None:
            cur.append(ln)
            if s.startswith(".end"):
                out[name] = cur
                cur = None
    return out


def insns_with_lines(chunk, mainfile):
    """[(insn text, C line)] from one function's -g listing; li/la expanded to the words they assemble to."""
    files, line, out = {}, None, []
    for ln in chunk:
        s = ln.split("#")[0].strip()
        if not s:
            continue
        m = re.match(r'\.file\s+(\d+)\s+"([^"]*)"', s)
        if m:
            files[m.group(1)] = m.group(2)
            continue
        m = re.match(r"\.loc\s+(\d+)\s+(\d+)", s)
        if m:
            if files.get(m.group(1), mainfile) == mainfile or m.group(1) not in files:
                line = int(m.group(2))
            continue
        if s.startswith(".") or s.endswith(":"):
            continue
        out.append((s, line))
    return out


def word_classes(insns):
    """listing insns -> per predicted word: (cls, index into insns).  la/li of 32-bit values = 2 words."""
    out = []
    for k, (s, _) in enumerate(insns):
        s = re.sub(r"\s+", " ", s)
        m = re.match(r"^li \$\w+,(-?(?:0x[0-9a-fA-F]+|\d+))$", s)
        if s.startswith("la ") or (m and not (-32768 <= int(m.group(1), 0) <= 65535)):
            v = int(m.group(1), 0) & 0xFFFFFFFF if m else None
            if v is not None and v & 0xFFFF == 0:
                out.append(("lui", k))
            else:
                out += [("lui", k), ("alu", k)]
            continue
        m = re.match(r"^(lw|sw|lh|lhu|sh|lb|lbu|sb) \$\w+,[A-Za-z_]", s)
        if m:                                   # symbolic load/store: lui + mem
            out += [("lui", k), (lcls(s), k)]
            continue
        if s.startswith(("ulw", "usw")):
            out += [(lcls(s), k), (lcls(s), k)]
            continue
        out.append((lcls(s), k))
    return out


def map_retail(retail_cls, wc):
    """{retail word idx: listing insn idx} by LCS over classes (nops dropped on both sides)."""
    ri = [i for i, c in enumerate(retail_cls) if c != "nop"]
    li = [i for i, (c, _) in enumerate(wc) if c != "nop"]
    a = [retail_cls[i] for i in ri]
    b = [wc[i][0] for i in li]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    m = {}
    for blk in sm.get_matching_blocks():
        for t in range(blk.size):
            m[ri[blk.a + t]] = wc[li[blk.b + t]][1]
    # unmatched retail words (nops, regions) take the nearest earlier mapped insn
    last = None
    for i in range(len(retail_cls)):
        if i in m:
            last = m[i]
        elif last is not None:
            m[i] = last
    return m


def unit_text(u):
    rowd = ROWS[u["row"]]
    return clean_path(rowd).read_text(errors="replace")


def func_chunk(lines, u):
    funcs = split_funcs(lines)
    if u["func"] in funcs:
        return funcs[u["func"]]
    if len(funcs) == 1:
        return next(iter(funcs.values()))
    return None


def line_map_job(job):
    """(unit idx, {retail word idx: C line}) from one -g compile of the unit's src/ text."""
    ui, rowd, func, cls = job
    try:
        res = raw_listing(rowd, clean_path(rowd).read_text(errors="replace"), g=True)
        if res is None:
            return ui, None
        lines, mainfile = res
        chunk = func_chunk(lines, dict(func=func))
        if chunk is None:
            return ui, None
        ins = insns_with_lines(chunk, mainfile)
        m = map_retail(cls, word_classes(ins))
        return ui, {i: ins[k][1] for i, k in m.items() if ins[k][1] is not None}
    except Exception:                         # noqa: BLE001
        return ui, None


def span_of(lmap, lo, hi):
    if not lmap:
        return "?"
    ls = sorted({lmap[i] for i in range(lo, hi) if i in lmap})
    return ("%d-%d" % (ls[0], ls[-1])) if ls else "?"


# ------------------------------------------------------------------------------ footprints

def footprint_job(job):
    """One pinned unit: per live pin, the retail word indices whose listing insns change when it is erased."""
    uid, rowd, func, cls, cachedir = job
    from pin_sites import erase_many
    import screen
    text = clean_path(rowd).read_text(errors="replace")
    key = hashlib.sha256((uid + "\0" + text).encode()).hexdigest()[:20]
    cf = Path(cachedir) / ("fp_%s.json" % key)
    if cf.exists():
        return uid, json.loads(cf.read_text())
    sites = sites_of(text)
    if rowd["kind"] == "slus":
        spans = slus_def_spans(text, rowd.get("defs") or [])
        s0, s1 = spans.get(func, (None, None))
        sites = [s for s in sites if s0 is not None and s0 <= s[3] < s1]

    def norm_func(t):
        res = raw_listing(rowd, t)
        if res is None:
            return None
        chunk = func_chunk(res[0], dict(func=func))
        if chunk is None:
            return None
        kr, lt = screen.options_for(rowd)
        return screen.normalise(chunk, keep_reorder=kr, la_token=lt)

    base = norm_func(text)
    if base is None:
        out = {"error": "pinned text does not build"}
        cf.write_text(json.dumps(out))
        return uid, out
    body = [(s, k) for k, s in enumerate(base) if s != ".ent" and not s.endswith(":")]
    ins = [(re.sub(r" \[nr\]$", "", s), None) for s, _ in body]
    wc = word_classes(ins)
    m = map_retail(cls, wc)
    inv = collections.defaultdict(list)       # body insn idx -> retail word idxs
    for r_, b_ in m.items():
        inv[b_].append(r_)
    pos_of = {k: n for n, (_, k) in enumerate(body)}
    res = []
    all_sites = sites_of(text)
    for s in sites:
        er = erase_many(text, [x for x in all_sites if x[:4] == s[:4]], clean_notes=True)
        cand = norm_func(er)
        rec = dict(macro=s[1], arg=s[2], line=s[5])
        if cand is None:
            rec["error"] = "erased text does not build"
            res.append(rec)
            continue
        changed = set()
        sm = difflib.SequenceMatcher(None, base, cand, autojunk=False)
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            if tag == "equal":
                continue
            span = range(i1, i2) if i2 > i1 else range(max(i1 - 1, 0), min(i1 + 1, len(base)))
            for k in span:
                if k in pos_of:
                    changed.update(inv.get(pos_of[k], []))
        rec["words"] = sorted(changed)
        res.append(rec)
    out = {"pins": res}
    cf.write_text(json.dumps(out))
    return uid, out


# ------------------------------------------------------------------------------------- main

def show(units, a):
    """--show PINNED SOURCE: the pair's chains, word by word ('*' = fine token differs, '!' = coarse)."""
    def find(x):
        for i, u in enumerate(units):
            if u["unit"] == x or u["row"] == x or u["row"].split("/")[-1] == x:
                return i
        raise SystemExit("no unit %r" % x)
    pi, si = find(a.show[0]), find(a.show[1])
    pu, su = units[pi], units[si]
    k = a.seed
    idx = collections.defaultdict(list)
    for j in range(len(su["tok"]) - k + 1):
        idx[tuple(su["tok"][j:j + k])].append(j)
    sd = [(i, j) for i in range(len(pu["tok"]) - k + 1) for j in idx.get(tuple(pu["tok"][i:i + k]), ())]
    runs = maximal_runs(pu["tok"], su["tok"], sd)
    runs += bridge_runs(pu["tok"], su["tok"], runs, a.gap)
    lp = line_map_job((pi, ROWS[pu["row"]], pu["func"], pu["cls"]))[1] or {}
    ls = line_map_job((si, ROWS[su["row"]], su["func"], su["cls"]))[1] or {}
    for score, ch in chains(runs, a.gap, a.chains):
        ie, rb = quality(pu, su, ch)
        print("== chain matched %d  pinned %d-%d  source %d-%d  imm_eq %.3f reg_bij %.3f" % (
            score, ch[0][0], ch[-1][0] + ch[-1][2], ch[0][1], ch[-1][1] + ch[-1][2], ie, rb))
        i, j = ch[0][0], ch[0][1]
        end_i, end_j = ch[-1][0] + ch[-1][2], ch[-1][1] + ch[-1][2]
        while i < end_i or j < end_j:
            inrun = any(r[0] <= i < r[0] + r[2] and j - i == r[1] - r[0] for r in ch)
            if inrun:
                mark = " " if pu["fine"][i] == su["fine"][j] else "*"
                print("%s %4d L%-4s %-34s %-22s | %4d L%-4s %-22s" % (mark, i, lp.get(i, "?"), decode(pu["words"][i])[0],
                      pu["fine"][i], j, ls.get(j, "?"), su["fine"][j]))
                i += 1
                j += 1
                continue
            nxt = [r for r in ch if r[0] >= i and r[1] >= j]
            ni, nj = (nxt[0][0], nxt[0][1]) if nxt else (end_i, end_j)
            while i < ni:
                print("! %4d L%-4s %-34s %-22s |" % (i, lp.get(i, "?"), decode(pu["words"][i])[0], pu["fine"][i]))
                i += 1
            while j < nj:
                print("! %4s  %-4s %-34s %-22s | %4d L%-4s %-22s" % ("", "", "", "", j, ls.get(j, "?"), su["fine"][j]))
                j += 1
    return 0


HEADER = ["rank", "pinned_row", "pins", "source_row", "same_func", "source_cfg_same", "matched", "longest_exact", "chain_runs",
          "pinned_words", "source_words", "imm_eq", "reg_bij", "trusted", "overlaps_pins", "pins_fully_covered", "pin_words_covered",
          "pins_overlapped", "source_c_lines", "pinned_c_lines"]

ROWS = {}


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--out", default="candidates.tsv", help="TSV (relative paths are inside the lane)")
    ap.add_argument("--json", default=None, help="also write every candidate as JSON lines")
    ap.add_argument("--only", nargs="*", default=None, help="pinned rows (ids) to search for")
    ap.add_argument("--seed", type=int, default=8)
    ap.add_argument("--min", type=int, default=12)
    ap.add_argument("--gap", type=int, default=4)
    ap.add_argument("--maxfreq", type=int, default=30)
    ap.add_argument("--chains", type=int, default=3, help="disjoint chains reported per pair")
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--spans", type=int, default=60, help="C spans for the top N candidates (-g compiles)")
    ap.add_argument("--no-footprint", action="store_true")
    ap.add_argument("--trust", type=float, default=0.85,
                    help="imm_eq and reg_bij floor for a TRUSTED pair (ranked first; low values = generic shapes)")
    ap.add_argument("--show", nargs=2, metavar=("PINNED", "SOURCE"),
                    help="print the chained alignment of one pair (fine-token mismatches marked) and exit")
    ap.add_argument("--cache", default=None, help="footprint cache dir (default <out dir>/tmp/fragclone_cache)")
    a = ap.parse_args()

    import kitlib
    lane = kitlib.bootstrap()          # refuses the repository root; every compile and the cache stay in the lane
    t0 = time.time()
    for r in rows():
        ROWS[r["id"]] = r
    units = load_units()
    tokenise(units)
    if a.show:
        return show(units, a)
    if not Path(a.out).is_absolute():
        a.out = str(Path(lane) / a.out)
        a.json = a.json and str(Path(lane) / a.json)
    pinned = [i for i, u in enumerate(units) if u["pins"]]
    if a.only:
        want = set(a.only)
        pinned = [i for i in pinned if units[i]["row"] in want or units[i]["unit"] in want]
    free = [i for i, u in enumerate(units) if not u["pins"]]
    print("units %d (pinned %d, pin-free %d), words %d  [%.1fs]" % (
        len(units), len(pinned), len(free), sum(len(u["words"]) for u in units), time.time() - t0), file=sys.stderr)
    idx = build_index(units, free, a.seed)
    freq = unit_freq(idx)
    print("index %d grams  [%.1fs]" % (len(idx), time.time() - t0), file=sys.stderr)

    cands = []
    for pi in pinned:
        pu = units[pi]
        t = pu["tok"]
        seeds = collections.defaultdict(list)
        for i in range(len(t) - a.seed + 1):
            h = hash(tuple(t[i:i + a.seed]))
            if freq.get(h, 0) > a.maxfreq:
                continue
            for ui, j in idx.get(h, ()):
                if units[ui]["row"] == pu["row"] or units[ui]["loc"] == pu["loc"]:
                    continue
                seeds[ui].append((i, j))
        for ui, sd in seeds.items():
            su = units[ui]
            runs = maximal_runs(t, su["tok"], sd)
            runs = runs + bridge_runs(t, su["tok"], runs, a.gap)
            for score, ch in chains(runs, a.gap, a.chains):
                if score < a.min:
                    continue
                ie, rb = quality(pu, su, ch)
                cands.append(dict(pinned=pu["unit"], pins=pu["pins"], source=su["unit"],
                                  same_func=pu["func"] == su["func"],
                                  cfg_same=ROWS[pu["row"]]["cfg"] == ROWS[su["row"]]["cfg"],
                                  matched=score, longest=max(L for _, _, L in ch), runs=len(ch),
                                  plo=ch[0][0], phi=ch[-1][0] + ch[-1][2], slo=ch[0][1], shi=ch[-1][1] + ch[-1][2],
                                  imm_eq=round(ie, 3), reg_bij=round(rb, 3), pi=pi, si=ui))
    print("candidates %d  [%.1fs]" % (len(cands), time.time() - t0), file=sys.stderr)

    fps = {}
    if not a.no_footprint:
        cachedir = Path(a.cache) if a.cache else Path(lane) / "tmp" / "fragclone_cache"
        cachedir.mkdir(parents=True, exist_ok=True)
        need = sorted({c["pi"] for c in cands})
        jobs = [(units[i]["unit"], ROWS[units[i]["row"]], units[i]["func"], units[i]["cls"], str(cachedir))
                for i in need]
        with ProcessPoolExecutor(a.workers) as ex:
            for uid, fp in ex.map(footprint_job, jobs):
                fps[uid] = fp
        print("footprints %d units  [%.1fs]" % (len(fps), time.time() - t0), file=sys.stderr)

    for c in cands:
        fp = fps.get(c["pinned"], {})
        cov, names, full = 0, [], 0
        for p in fp.get("pins", []):
            w = [x for x in p.get("words", []) if c["plo"] <= x < c["phi"]]
            if w:
                cov += len(w)
                full += len(w) == len(p["words"])
                names.append("%s(%s)@%d:%d/%d" % (p["macro"], p["arg"], p["line"], len(w), len(p["words"])))
        c["cov"], c["over"], c["full"] = cov, names, full
        c["trusted"] = c["imm_eq"] >= a.trust and c["reg_bij"] >= a.trust
    # overlap first; then pins whose whole footprint lies in the chain, then matched length weighted by
    # fidelity (a fragment of the same C has imm_eq and reg_bij near 1)
    cands.sort(key=lambda c: (-(1 if c["over"] and c["trusted"] else 0), -(1 if c["over"] else 0), -c["full"],
                              -c["matched"] * (0.5 + c["imm_eq"]) * (0.5 + c["reg_bij"]) - c["cov"],
                              c["pinned"], c["source"]))

    # C spans: every candidate that overlaps a pin (or the top --spans), one -g compile per unit
    want = [c for n, c in enumerate(cands) if c["over"] or n < a.spans]
    need = sorted({c["si"] for c in want} | {c["pi"] for c in want})
    lmaps = {}
    with ProcessPoolExecutor(a.workers) as ex:
        for ui, lm in ex.map(line_map_job, [(i, ROWS[units[i]["row"]], units[i]["func"], units[i]["cls"])
                                            for i in need], chunksize=8):
            lmaps[ui] = lm
    for c in want:
        c["src_lines"] = span_of(lmaps.get(c["si"]), c["slo"], c["shi"])
        c["tgt_lines"] = span_of(lmaps.get(c["pi"]), c["plo"], c["phi"])
    print("spans  [%.1fs]" % (time.time() - t0), file=sys.stderr)

    with open(a.out, "w") as f:
        f.write("\t".join(HEADER) + "\n")
        for n, c in enumerate(cands, 1):
            f.write("\t".join(str(x) for x in (
                n, c["pinned"], c["pins"], c["source"], int(c["same_func"]), int(c["cfg_same"]), c["matched"], c["longest"], c["runs"],
                "%d-%d" % (c["plo"], c["phi"]), "%d-%d" % (c["slo"], c["shi"]), c["imm_eq"], c["reg_bij"],
                int(c["trusted"]), int(bool(c["over"])), c["full"], c["cov"], ";".join(c["over"]) or "-", c.get("src_lines", ""),
                c.get("tgt_lines", ""))) + "\n")
    best = {}
    for c in cands:
        best.setdefault(c["pinned"], c)
    byrow = Path(a.out).with_name(Path(a.out).stem + "_by_row.tsv")
    with open(byrow, "w") as f:
        f.write("pinned_row\tpins\tsources\tsources_overlapping\ttrusted_overlapping\tbest_source\tmatched\tpins_fully_covered\tpin_words_covered\timm_eq\treg_bij\tpins_overlapped\n")
        n_src = collections.Counter(c["pinned"] for c in cands)
        n_ov = collections.Counter(c["pinned"] for c in cands if c["over"])
        n_tr = collections.Counter(c["pinned"] for c in cands if c["over"] and c["trusted"])
        for pid, c in sorted(best.items(), key=lambda kv: (-(1 if kv[1]["over"] and kv[1]["trusted"] else 0), -(1 if kv[1]["over"] else 0),
                                                       -kv[1]["full"], -kv[1]["cov"])):
            f.write("\t".join(str(x) for x in (pid, c["pins"], n_src[pid], n_ov[pid], n_tr[pid], c["source"], c["matched"], c["full"], c["cov"],
                                                  c["imm_eq"], c["reg_bij"], ";".join(c["over"]) or "-")) + "\n")
    if a.json:
        with open(a.json, "w") as f:
            for c in cands:
                f.write(json.dumps({k: v for k, v in c.items() if k not in ("pi", "si")}) + "\n")
    print("wrote %s (%d rows, %d overlapping pins)  [%.1fs]" % (
        a.out, len(cands), sum(1 for c in cands if c["over"]), time.time() - t0), file=sys.stderr)


if __name__ == "__main__":
    main()
