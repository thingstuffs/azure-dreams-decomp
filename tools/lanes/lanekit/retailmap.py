"""retailmap.py - the retail side of a score: the scorer's listing parsed, aligned and classified, and the
map insn uid -> generated word index -> retail word index.  Plumbing for `why.py --trace --retail`,
`diff.py --scorer --classify` and `checks.py`; pure functions, no compile, no scorer call.

* `scorer_rows(text)`    -> [(idx, generated, retail)] from `verify.py --diff` text (`diff.parse_scorer`).
* `align(rows)`          -> {gen: ret} word map: LCS on branch-masked text, then identical instructions
                            outside the LCS paired nearest-first (a MOVED instruction keeps its text).
* `classify(rows)`       -> the differing regions, each item ORDER (same instruction, moved), COLOUR
                            (allocatable registers renamed only), OPCODE (different instruction or
                            constant) or COUNT (an insertion or deletion).
* `asm_words(asm)` / `uid_map(asm, generated)` -> {uid: [gen word...]}: the `-dap` assembly (gcc's
                            `# <uid> <pattern>` annotation on the first line of every insn) expanded to
                            predicted machine words (li/la/symbolic loads are two, `#nop` is one) and
                            LCS-aligned on mnemonic to the scorer's generated column.  This is a MODEL
                            of the assembler, not the assembler: `coverage` says how many words it
                            placed, and an unplaced uid prints `?`, never a guess.
"""
from __future__ import annotations

import difflib
import re

SCORER_LINE = re.compile(r"^\s*[!X~ ]?\s*\[\s*(\d+)\] (.*?)\s*\|\s*(.*?)(?:\s+raw .*)?$")
BRANCH_RE = re.compile(r"^(b\w*|j)\s")
ALLOC_REG = re.compile(r"\b(v[01]|a[0-3]|t[0-9]|s[0-8]|fp)\b")


def scorer_rows(text):
    """[(index, generated, retail)] from the byte scorer's `--diff` text; [] on a MATCH / no listing."""
    out = []
    for line in (text or "").splitlines():
        m = SCORER_LINE.match(line.rstrip())
        if m:
            out.append((int(m.group(1)), m.group(2).strip(), m.group(3).strip()))
    return out


def mask(line):
    """Branch/jump absolute targets are layout, not code: `bnez v0,0x8001f0` -> `bnez v0,TGT`."""
    return re.sub(r"0x[0-9a-f]+$", "TGT", line) if BRANCH_RE.match(line) else line


def colour_key(line):
    """`line` with every ALLOCATABLE register (v, a, t, s, fp) renamed `R`: equal keys = colour only."""
    return ALLOC_REG.sub("R", mask(line))


def _sides(rows):
    gen = [(i, g) for i, g, _ in rows if g]
    ret = [(i, t) for i, _, t in rows if t]
    return gen, ret


def align(rows):
    """({gen: ret}, [(tag, gen idxs, ret idxs)] non-equal LCS regions, moved {gen: ret})."""
    gen, ret = _sides(rows)
    a, b = [mask(t) for _, t in gen], [mask(t) for _, t in ret]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    m, regions = {}, []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            for k in range(i2 - i1):
                m[gen[i1 + k][0]] = ret[j1 + k][0]
        else:
            regions.append((tag, [gen[k][0] for k in range(i1, i2)], [ret[k][0] for k in range(j1, j2)]))
    # a moved instruction: identical text on both sides outside the LCS, nearest first
    ug = [(gen[k][0], a[k]) for k in range(len(gen)) if gen[k][0] not in m]
    matched_r = set(m.values())
    ur = [(ret[k][0], b[k]) for k in range(len(ret)) if ret[k][0] not in matched_r]
    cands = sorted((abs(gi - ri), gi, ri) for gi, gt in ug for ri, rt in ur if gt == rt)
    moved, used_g, used_r = {}, set(), set()
    for _, gi, ri in cands:
        if gi in used_g or ri in used_r:
            continue
        moved[gi] = ri
        used_g.add(gi)
        used_r.add(ri)
    m.update(moved)
    return m, regions, moved


def drift_at(m, moved, gen_idx):
    """retail - generated at the nearest LCS-equal word at or before `gen_idx` (0 when none): where an
    unmoved instruction at `gen_idx` would sit in retail, so an indel earlier in the function does not
    flip an earlier/later verdict."""
    best = None
    for g, r in m.items():
        if g in moved or g > gen_idx:
            continue
        if best is None or g > best[0]:
            best = (g, r)
    return 0 if best is None else best[1] - best[0]


def classify(rows):
    """[{region, gen: [idx], ret: [idx], items: [{kind, gen, ret, got, tgt}], counts}] + totals.

    Region = one non-equal LCS hunk.  A moved instruction (ORDER) is booked once, to the region that
    holds its generated side (the `ret` column says where retail has it).  What is left in a region is paired
    in order: equal after renaming allocatable registers -> COLOUR, otherwise OPCODE; the unpaired rest
    is COUNT (`+` generated only, `-` retail only)."""
    gen, ret = _sides(rows)
    gt, rt = dict(gen), dict(ret)
    m, regions, moved = align(rows)
    moved_r = set(moved.values())
    out, totals = [], {"ORDER": 0, "COLOUR": 0, "OPCODE": 0, "COUNT": 0}
    for tag, gi, ri in regions:
        items = []
        for g in gi:
            if g in moved:
                items.append({"kind": "ORDER", "gen": g, "ret": moved[g], "got": gt[g], "tgt": rt[moved[g]]})
        rest_g = [g for g in gi if g not in moved]
        rest_r = [r for r in ri if r not in moved_r]
        for g, r in zip(rest_g, rest_r):
            kind = "COLOUR" if colour_key(gt[g]) == colour_key(rt[r]) else "OPCODE"
            items.append({"kind": kind, "gen": g, "ret": r, "got": gt[g], "tgt": rt[r]})
            m.setdefault(g, r)
        for g in rest_g[len(rest_r):]:
            items.append({"kind": "COUNT", "gen": g, "ret": None, "got": gt[g], "tgt": None})
        for r in rest_r[len(rest_g):]:
            items.append({"kind": "COUNT", "gen": None, "ret": r, "got": None, "tgt": rt[r]})
        if not items:
            continue
        counts = {k: sum(1 for x in items if x["kind"] == k) for k in totals}
        for k, v in counts.items():
            totals[k] += v
        label = max(counts, key=lambda k: (counts[k], -list(totals).index(k)))
        out.append({"region": len(out) + 1, "gen": gi, "ret": ri, "items": items, "counts": counts, "label": label})
    return out, totals


# ------------------------------------------------------------------------ -dap assembly -> words

LOADSTORE = {"lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr", "sb", "sh", "sw", "swl", "swr", "lwc2", "swc2"}
IMM_FORM = {"addu": "addiu", "subu": "addiu", "and": "andi", "or": "ori", "xor": "xori",
            "slt": "slti", "sltu": "sltiu"}
CANON = {"beqz": "beq", "bnez": "bne", "b": "beq", "negu": "subu", "not": "nor", "bal": "jal"}
ANNOT = re.compile(r"#\s*(\d+)\s+([\w/.]+)\s*$")


def _int(s):
    try:
        return int(s, 0)
    except ValueError:
        return None


def _keys(mn, ops):
    """Predicted disassembly mnemonics of one assembler line (the assembler's macro expansion)."""
    last = ops[-1] if ops else ""
    if mn == "li":
        v = _int(last)
        if v is None:
            return ["lui", "ori"]
        if -32768 <= v <= 65535:
            return ["li"]
        return ["lui"] if v & 0xffff == 0 else ["lui", "ori"]
    if mn == "la":
        return ["lui", "addiu"]
    if mn in LOADSTORE:
        if re.fullmatch(r"-?\w*\(\$\w+\)", last) or "%lo(" in last or "%gp_rel(" in last:
            return [mn]
        return ["lui", mn]
    if mn in IMM_FORM and _int(last) is not None:
        return [IMM_FORM[mn]]
    if mn == "j" and last.startswith("$31"):
        return ["jr"]
    if mn in ("beq", "bne") and len(ops) == 3 and ops[1] == "$0":
        return [mn + "z"]
    return [mn]


def asm_words(asm):
    """[(uid or None, mnemonic key, asm line)] - one entry per PREDICTED machine word of the function
    body (between `.ent` and `.end`), with the `-dap` uid of the insn the line belongs to."""
    out, inside, cur = [], False, None
    for raw in asm.splitlines():
        s = raw.strip()
        if s.startswith(".ent"):
            inside = True
            continue
        if s.startswith(".end"):
            inside = False
            continue
        if not inside or not s:
            continue
        if s == "#nop":
            out.append((None, "nop", s))
            continue
        if s.startswith(("#", ".")) or s.endswith(":"):
            continue
        m = ANNOT.search(s)
        uid = int(m.group(1)) if m else None
        code = s.split("#", 1)[0].strip()
        if not code:
            continue
        parts = code.split(None, 1)
        mn, ops = parts[0], [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []
        if uid is not None:
            cur = uid
        elif mn == "nop":
            cur = None            # a delay-slot `nop` gcc printed itself belongs to no insn
        # any other line without an annotation is the 2nd.. line of a multi-line template (same insn)
        for k in _keys(mn, ops):
            out.append((cur, k, s))
    return out


def _canon(k):
    return CANON.get(k, k)


def uid_map(asm, generated):
    """({uid: [gen idx]}, {gen idx: uid}, (placed words, predicted words, generated words)).

    `generated` = [(gen idx, disassembly text)].  Mnemonic LCS between the predicted words of the `-dap`
    assembly and the scorer's generated column; `replace` hunks of equal length are placed one to one
    (a mis-predicted expansion inside an otherwise aligned run), anything else stays unplaced."""
    words = asm_words(asm)
    a = [_canon(k) for _, k, _ in words]
    b = [_canon(t.split()[0]) if t.split() else "" for _, t in generated]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    by_uid, by_gen, placed = {}, {}, 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal" or (tag == "replace" and i2 - i1 == j2 - j1):
            for k in range(i2 - i1):
                uid, g = words[i1 + k][0], generated[j1 + k][0]
                placed += 1
                if uid is None:
                    continue
                by_uid.setdefault(uid, []).append(g)
                by_gen[g] = uid
    return by_uid, by_gen, (placed, len(words), len(generated))
