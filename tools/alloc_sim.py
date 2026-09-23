#!/usr/bin/env python3
"""gcc 2.x allocno-order model: compile one text with `cc1 -dl -dg`, read the dumps, and simulate
`global.c`'s `find_reg` loop.  A library copy of the round-61 study's `dumps.py` + `sim.py`
(work/native_lane/r61_alloc_study/), so generators can use the model without importing out of work/.

WHY.  A `register x ASM_REG("$19")` pin is a MISSING allocno: erasing it adds one allocno and every
lower-priority allocno slides one register down the callee-saved sequence (study rule R1).  The sort
key is `allocno_compare` (global.c:586) - `floor_log2(n_refs)*n_refs/live_length*10000*size`,
descending, ties by allocno number = declaration order - and `find_reg` hands $s0,$s1,$s2... out
strictly in that order for call-crossing values, so for those values THE REGISTER IS THE RANK (R4).
`allocate()` reproduced the real `;; Register dispositions:` of all 14 builds of the study (7 rows x
pinned/erased) exactly, which makes it a free gate ahead of the byte scorer.

Reading costs one compile: the lreg dump's `Register N used M times across K insns; crosses C calls`
is (allocno_n_refs, allocno_live_length, allocno_calls_crossed); the greg dump's
`;; N regs to allocate:` IS `allocno_order` after the qsort and `;; P conflicts:` / `;; P preferences:`
are the state `find_reg` starts from.  `norm_asm` normalises the dumped compile's own assembly the
way `xform.screen.compile_s` does, so one dump compile yields the listing too (the study's trust
check: the two must be equal).
"""
import math, re, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import parse_cfg
from xform.t29_addrsym import mask_comments
from xform.t36_paramwidth import functions
from xform import screen

INCLUDE = ROOT / "include"
GPR = ("$zero $at $v0 $v1 $a0 $a1 $a2 $a3 $t0 $t1 $t2 $t3 $t4 $t5 $t6 $t7 "
       "$s0 $s1 $s2 $s3 $s4 $s5 $s6 $s7 $t8 $t9 $k0 $k1 $gp $sp $fp $ra").split()
# FIRST_PSEUDO_REGISTER per compiler cell (study search.py).
FIRST = {"2.6.3": 67, "2.7.2": 68, "2.7.2-cdk": 76, "2.8.0": 76, "2.8.1": 76}

STAT = re.compile(r"^Register (\d+) used (\d+) times across (-?\d+) insns(.*)$", re.M)
ALLOC = re.compile(r"^;; (\d+) regs to allocate:(.*)$", re.M)


def reg_name(n):
    n = int(n)
    if 0 <= n < 32:
        return GPR[n]
    if 32 <= n < 64:
        return "$f%d" % (n - 32)
    return "r%d" % n


def compile_dumps(row, text, timeout=120):
    """{'lreg','greg','asm'} for `text` compiled as `row` with -dl -dg, or None if it does not build."""
    cell, flags = parse_cfg(row["cfg"])
    D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="allocsim_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags,
                            "-I" + str(INCLUDE), "-w", f.name, "-o", "f.i"],
                           cwd=d, capture_output=True, text=True, timeout=timeout)
        if r.returncode:
            return None
        r = subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w",
                            "-dl", "-dg", "-o", "f.s"], cwd=d, capture_output=True, text=True, timeout=timeout)
        if r.returncode:
            return None
        got = {}
        for p in sorted(d.glob("*")):
            if p.suffix in (".lreg", ".greg"):
                got[p.suffix[1:]] = p.read_text(errors="replace")
        asm = (d / "f.s").read_text(errors="replace")
    return {"lreg": got.get("lreg", ""), "greg": got.get("greg", ""), "asm": asm}


def parse_lreg(txt):
    """pseudo -> dict(n_refs, live_length, calls_crossed, note)."""
    out = {}
    for m in STAT.finditer(txt):
        p, refs, life, rest = int(m.group(1)), int(m.group(2)), int(m.group(3)), m.group(4)
        cc = 0
        mc = re.search(r"crosses (\d+) calls?", rest)
        if mc:
            cc = int(mc.group(1))
        out[p] = {"n_refs": refs, "live_length": life, "calls_crossed": cc, "note": rest.strip()}
    return out


def parse_greg(txt):
    """(allocno_order as a pseudo list, dispositions pseudo->hard register)."""
    order = []
    m = ALLOC.search(txt)
    if m:
        for tok in m.group(2).split():
            tok = tok.split("+")[0].strip("()")
            if tok.lstrip("-").isdigit():
                order.append(int(tok))
    disp = {}
    m2 = re.search(r"Register dispositions:\n(.*?)\n\n", txt, re.S)
    if m2:
        for mm in re.finditer(r"(\d+) in (-?\d+)", m2.group(1)):
            disp[int(mm.group(1))] = int(mm.group(2))
    return order, disp


def priority(n_refs, live_length, size=1):
    """global.c allocno_compare, verbatim (int truncation of the double)."""
    if live_length == 0:
        live_length = -1
    fl = 0 if n_refs <= 0 else int(math.floor(math.log2(n_refs)))
    return int((float(fl * n_refs) / live_length) * 10000 * size)


def norm_asm(asm):
    """screen.compile_s's normalisation applied to assembly already in hand."""
    out, lab, inside = [], {}, False
    for ln in asm.splitlines():
        t = ln.split("#")[0].strip()
        if t.startswith(".ent"):
            inside = True
            out.append(".ent")
            continue
        if t.startswith(".end"):
            inside = False
            continue
        if not inside or not t or t.startswith((".loc", ".frame", ".mask", ".fmask", ".set")):
            continue
        t = re.sub(r"\s+", " ", t)
        t = re.sub(r"\$L\d+", lambda m: lab.setdefault(m.group(0), "L%d" % len(lab)), t)
        out.append(screen._addr(t))
    return out


# ------------------------------------------------------------------ global.c find_reg simulation

FIXED = ([1, 1] + [0] * 24 + [1, 1, 1, 1, 0, 1] + [0] * 32 + [0, 0, 0, 1] + [1] * 16)
CALL_USED = ([1] * 16 + [0] * 8 + [1] * 6 + [0, 1] + [1] * 20 + [0] * 12 + [1] * 4 + [1] * 16)
GPR_CLASS = set(range(32))                                            # GR_REGS
CALLEE = [r for r in range(32) if not CALL_USED[r] and not FIXED[r]]  # $s0-$s7, $fp


def parse_conflicts(greg, first_pseudo):
    """pseudo -> (conflicting pseudos, conflicting hard regs), and pseudo -> hard preferences."""
    conf, pref = {}, {}
    for m in re.finditer(r"^;; (\d+) conflicts:(.*)$", greg, re.M):
        p = int(m.group(1))
        ps, hs = set(), set()
        for t in m.group(2).split():
            v = int(t)
            (hs if v < first_pseudo else ps).add(v)
        conf[p] = (ps, hs)
    for m in re.finditer(r"^;; (\d+) preferences:(.*)$", greg, re.M):
        pref[int(m.group(1))] = set(int(t) for t in m.group(2).split())
    return conf, pref


def allocate(order, stats, conf, pref, first_pseudo):
    """global.c's find_reg loop over `order` (pseudo list in allocno order) -> {pseudo: hardreg|-1}."""
    hconf = {p: set(conf.get(p, (set(), set()))[1]) for p in order}
    pconf = {p: set(conf.get(p, (set(), set()))[0]) for p in order}
    used_so_far = set(r for r in range(32) if CALL_USED[r])
    for p in order:
        used_so_far |= set(r for r in hconf[p] if r in CALLEE)
    someone = {}
    for i, p in enumerate(order):
        s = set()
        for q in order[i + 1:]:
            if q in pconf[p] or p in pconf.get(q, set()):
                s |= pref.get(q, set())
        someone[p] = s - pref.get(p, set())
    out = {}
    for p in order:
        cc = stats.get(p, {}).get("calls_crossed", 0)
        base = set(r for r in range(first_pseudo) if (CALL_USED[r] if cc else FIXED[r]))
        base |= set(r for r in range(first_pseudo) if r not in GPR_CLASS)
        base |= hconf[p]
        best = -1
        for pss in (0, 1):
            used = set(base)
            if pss == 0:
                used |= set(r for r in range(first_pseudo) if r not in used_so_far)
                used |= someone[p]
            for r in range(first_pseudo):
                if r not in used:
                    best = r
                    break
            if best >= 0:
                break
        if best >= 0:
            pr = pref.get(p, set()) - set(base)
            if pr:
                cand = sorted(x for x in pr if x < 32)
                if cand:
                    best = cand[0]
            out[p] = best
            used_so_far.add(best)
            for q in order:
                if q != p and (q in pconf[p] or p in pconf.get(q, set())):
                    hconf[q].add(best)
        else:
            out[p] = -1
    return out


def read(row, text):
    """One dump compile -> {'order','disp','stats','conf','pref','listing','first'} (None if it does not build)."""
    cell, _ = parse_cfg(row["cfg"])
    fp = FIRST.get(cell)
    d = compile_dumps(row, text)
    if d is None or fp is None:
        return None
    order, disp = parse_greg(d["greg"])
    stats = parse_lreg(d["lreg"])
    conf, pref = parse_conflicts(d["greg"], fp)
    return {"order": order, "disp": disp, "stats": stats, "conf": conf, "pref": pref,
            "listing": norm_asm(d["asm"]), "first": fp, "lreg": d["lreg"], "sets": set_counts(d["lreg"], fp)}


INSN_HEAD = re.compile(r"^\((?:insn|call_insn|jump_insn) \d+ ", re.M)
SET_DEST = re.compile(r"\(set \(reg(?:/\w+)*:\w+ (\d+)\)")


def set_counts(lreg, first_pseudo):
    """pseudo -> (REG_N_SETS as the dump's insn stream shows it, carries REG_EQUIV).

    Round 76 (docs/evidence/pin_research_round76_move_table.md, the set-exactly-once family): an `ASM_KEEP(v)` is
    an asm "+r" output, a SECOND set of v.  gcc 2.x's local-alloc.c `update_equiv_regs` gives a pseudo with
    REG_N_SETS == 1 whose set carries REG_EQUAL/REG_EQUIV an equivalence and DOUBLES its REG_LIVE_LENGTH, and
    sched.c `birthing_insn_p` needs REG_N_SETS == 1 too.  The lreg dump's `used N times across K insns` is read
    AFTER the doubling, so `simulate()` already sees it; these counts say WHICH allocnos were doubled (a
    screen: a generator making v single-set can check that v became `doubled`)."""
    sets, equiv = {}, set()
    heads = [m.start() for m in INSN_HEAD.finditer(lreg)] + [len(lreg)]
    for a, b in zip(heads, heads[1:]):
        blk = lreg[a:b]
        ds = [int(x) for x in SET_DEST.findall(blk) if int(x) >= first_pseudo]
        for d in ds:
            sets[d] = sets.get(d, 0) + 1
        if "REG_EQUIV" in blk and ds:
            equiv.add(ds[0])
    return {p: (n, p in equiv) for p, n in sets.items()}


def doubled(rd):
    """{pseudo: bool} - the allocnos whose live length update_equiv_regs doubled (single set + REG_EQUIV)."""
    sc = rd.get("sets") or set_counts(rd.get("lreg", ""), rd["first"])
    return {p: sc.get(p, (0, False)) == (1, True) for p in rd["order"]}


def priority_undoubled(rd, p):
    """The allocno priority p would have with its live length NOT doubled (a what-if for adding a second set)."""
    st = rd["stats"].get(p, {})
    life = st.get("live_length", -1)
    if doubled(rd).get(p):
        life = max(1, life // 2)
    return priority(st.get("n_refs", 0), life)


def simulate(rd):
    """sim dispositions for a reading, ordered by allocno_compare (priority desc, ties by pseudo)."""
    order = sorted(rd["order"], key=lambda p: (-priority(rd["stats"].get(p, {}).get("n_refs", 0),
                                                         rd["stats"].get(p, {}).get("live_length", -1)), p))
    return allocate(order, rd["stats"], rd["conf"], rd["pref"], rd["first"])


def user_pseudos(lreg, order):
    """Allocno pseudos the RTL marks `(reg/v:...)` - a user variable - in declaration (pseudo) order."""
    seen = set(int(m.group(1)) for m in re.finditer(r"\(reg/v(?:/\w+)*:\w+ (\d+)\)", lreg))
    return [p for p in sorted(order) if p in seen]


def flow_vector(rd):
    """The allocator-visible flow state: (n_refs, live_length, calls_crossed) per allocno, sorted.

    Two texts with the same vector and the same disposition sequence are the same allocation problem:
    study rule R6 - reordering independent statements does not move a single live_length."""
    v = []
    for p in rd["order"]:
        st = rd["stats"].get(p, {})
        v.append((st.get("n_refs"), st.get("live_length"), st.get("calls_crossed")))
    return tuple(sorted(v))


# ------------------------------------------------------- declaration order -> pseudo numbers (R3)

SCALAR_WORDS = {"s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32", "f64", "int", "char",
                "short", "long", "unsigned", "signed", "float", "double", "void", "_Bool", "bool"}
NARROW = {"s8", "u8", "s16", "u16", "char", "short"}
QUALIFIERS = {"register", "volatile", "const", "static", "auto"}
KEYWORDS = {"return", "if", "else", "while", "for", "switch", "case", "goto", "do", "break",
            "continue", "default", "sizeof", "typedef"}
DECL_LINE = re.compile(r"^[ \t]*(?P<body>[A-Za-z_][\w \t*,\[\]]*?)"
                       r"(?:[ \t]*ASM_REG\(\"[^\"]*\"\))?[ \t]*;[ \t]*$")
TOKEN = re.compile(r"[A-Za-z_]\w*|\*|\[[^\]]*\]")


def _declarators(body):
    """[(name, type_words, stars, array)] for one declaration line body (`u16 *a, b[2]`)."""
    parts = body.split(",")
    toks = [x for x in TOKEN.findall(parts[0]) if x not in QUALIFIERS]
    names = [x for x in toks if x[:1].isalpha() or x[:1] == "_"]
    if len(names) < 2:
        return []
    ty = names[:-1]
    out = [(names[-1], ty, toks.count("*"), any(x[:1] == "[" for x in toks))]
    for part in parts[1:]:
        t2 = TOKEN.findall(part)
        n2 = [x for x in t2 if x[:1].isalpha() or x[:1] == "_"]
        if len(n2) != 1:
            return []
        out.append((n2[0], ty, t2.count("*"), any(x[:1] == "[" for x in t2)))
    return out


def locals_in_order(text, b0, b1):
    """[(name, type_words, scalar)] for the function body's declarations, in source order.

    Every scalar declaration takes one pseudo in source order, `register ... ASM_REG(...)` ones
    included (their slot is reserved even though the decl is a hard register): the pinned and erased
    builds of the study rows differ by exactly the pin's own pseudo, nothing else renumbers.
    """
    masked = mask_comments(text)
    out = []
    for ln in masked[b0:b1].split("\n"):
        m = DECL_LINE.match(ln)
        if not m:
            continue
        for name, ty, stars, array in _declarators(m.group("body")):
            if not ty or ty[0] in KEYWORDS or name in KEYWORDS:
                continue
            scalar = (not array) and (stars > 0 or bool(set(ty) & SCALAR_WORDS))
            out.append((name, ty, scalar))
    return out


def decl_pseudos(text, first_pseudo):
    """{name: pseudo} for one function's parameters and scalar locals (study rule R3).

    gcc creates DECL_RTL in declaration order: the four virtual registers take first_pseudo..+3,
    then each parameter (plus one conversion pseudo when the declared type is narrower than the mode
    it arrives in - PROMOTE_PROTOTYPES), then every scalar local.  Aggregates live in memory and take
    no pseudo.  Returns None when the file is not a single function definition.
    """
    fs = functions(text)
    if len(fs) != 1:
        return None
    fname, params, b0, b1 = fs[0]
    n = first_pseudo + 4
    m = {}
    for pname, ptype, _, _ in params:
        m[pname] = n
        n += 2 if (ptype.split()[-1] in NARROW and "*" not in ptype) else 1
    base_local = n
    for name, ty, scalar in locals_in_order(text, b0, b1):
        if not scalar:
            continue
        m.setdefault(name, n)
        n += 1
    return {"map": m, "base_local": base_local, "end": n, "fname": fname}
