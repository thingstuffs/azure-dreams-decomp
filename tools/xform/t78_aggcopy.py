"""T78: a scalarized whole-object copy written back as one aggregate assignment.

APPEARS     a run of word loads into locals followed by stores of those locals into a second object at the
            same offsets (loads and stores may come in groups), with ASM_REG pins on some of the temps and/or
            ASM_KEEP pins in the run:
                copy_word_a = source->words[0];
                copy_word_b = source->words[1];
                copy_word_c = source->words[2];          /* register s32 ... ASM_REG("$5") */
                copy_word_d = source->words[3];          /* register s32 ... ASM_REG("$6") */
                ((S *)output)->unk_00.at00.v = copy_word_a;
                ((S *)output)->unk_04.at00.v = copy_word_b;
                ((S *)output)->unk_08.at00.v = copy_word_c;
                ((S *)output)->unk_0C = copy_word_d;
                copy_word_a = source->words[4];
                copy_word_b = source->words[5];
                ((S *)output)->unk_10 = copy_word_a;
                ((S *)output)->unk_14 = copy_word_b;
            The element loads are also spelled `*(s32 *)((u8 *)src + 0xC)`, `(*(s64_local *)((u8 *)((void *)p) + 0))`
            (an 8-byte part), `arg1->word[i]` and `S32_AT(base, off)`.
RESOLVES    dungeon/func_81087524 and dungeon/func_818C2FAC (lane r59_sol_large7) and dungeon/func_818B7E14
            (lane r58_order2).  Mechanism: m2c scalarizes a struct assignment into one load and one store per
            word, and the pins then hold the order and the colours that gcc's own aggregate-copy lowering
            produces for free.  gcc 2.7.2 expands a small `*d = *s;` through `emit_block_move` /
            `move_by_pieces`, which emits the words in fixed groups (four words, then two) with the temporaries
            it invents itself - plain pseudos with no hard-register constraint and no scheduling freedom
            between the groups - so the ASM_REG colours and the ASM_KEEPs in the recovered run become
            unnecessary.  Written as separate statements the loads are ordinary pseudos, sched.c is free to
            interleave them and the register allocator to colour them differently, which is what the pins were
            pinning.  t38b_unstage_run removes a staging run; this one replaces one by the aggregate move.
CANDIDATES  per maximal run (loads and stores of the same temps against two different base expressions, each
            temp loaded once then stored once, equal counts, contiguous element offsets when the text proves
            them - `word[i]`, `unk_XX`, `+ 0xXX` - and otherwise a one-to-one pairing the byte gate decides):
            the whole run replaced by `*DST = *SRC;` when both bases are declared pointers to one named struct
            of exactly the run's size, by `*(T *)other = *named;` when only one side is, and otherwise by
            `*(CopyN *)DST = *(CopyN *)SRC;` with `typedef struct { s32 word[N/4]; } CopyN;` inserted after the
            includes when the file has no such typedef; a non-zero first offset is spelled `(u8 *)base + off`.
            The copy is tried where the first load was and where the last store was.  The temps' declarations
            (and the ASM_REG pins on them) are dropped when the run is their only use; a temp whose value is
            read after the run keeps its declaration and its last load is re-emitted beside the copy.  Then
            the run's window
            pins are erased jointly, then singly, then the function's pins jointly; every candidate is ranked
            by its cc1 listing distance to the pinned text's listing and only listing-exact ones reach `vf`.

APPEARS     (round 62, the unaligned form) the same whole-object copy already written as an aggregate
            assignment, but sourced from a hand-held page constant instead of the object's own symbol:
                copy_page = (u8 *)0x80020000;
                ASM_KEEP(copy_page);
                copy_source = (Copy32 *)(copy_page + 0x4028);
                ASM_KEEP(copy_source);            /* holds the %hi/%lo vs base+offset address form */
                direction_offsets.first  = copy_source->first;
                direction_offsets.second = copy_source->second;
                direction_offsets.third  = copy_source->third;
                ASM_KEEP(copy_page);              /* holds the colour of the block move's temporaries */
            also spelled `memcpy(dst, copy_source, 12); memcpy(dst + 12, copy_source + 12, 12); ...`,
            `*(Blob12 *)&points = *(Blob12 *)copy_source;` and, for one chunk, `dst = *copy_source;`.
RESOLVES    dungeon/func_819C04E8 (9 pins -> 5) and dungeon/func_819A1654.  Mechanism: retail materialises
            the object's address once as `lui %hi` + `addiu %lo` into a register and then runs gcc 2.7.2's
            mips.c `expand_block_move`, which for a symbol source loads three words then stores them, three
            then three then two for a 32-byte object (a source address already in a register groups four and
            four instead: measured, `*page_ptr` vs `&D_80024028` on func_819C04E8 - one of the move registers
            appears to go to the materialised %hi/%lo base).  The recovered C fakes that base register
            with a page constant, and the ASM_KEEPs hold the constant, the `addiu` and the base's liveness
            across the move.  Naming the object - `*(Copy32 *)&D_80024028` - makes cc1 emit the same
            lui/addiu base by itself (the cdk cell always splits addresses), so the keeps are unnecessary.
            The block move's grouping only depends on whether the alignment is below a word: a packed
            struct, `struct { u16 h[N/2]; }` and `struct { u8 b[N]; }` compile identically (lwl/lwr pairs),
            while an alignment-4 struct switches to `lw`/`sw` - so the inserted type is `u8 b[N]`.
APPEARS     (round 64, the joint form) SEVERAL page runs in one function - the seven spawn branches of
            dungeon/func_819A1654 each staging the same 12-byte object inside a one-line
            `do { page = (u8 *)0x80020000; ASM_KEEP(page); src = page + (0x618C); ASM_KEEP(src);
            *(Blob12 *)task->data = *(Blob12 *)src; ASM_KEEP(page); } while (0);`, the four memcpy runs of
            dungeon/func_8187C45C sharing ONE materialised page base - and the transfer that changes its
            source base halfway:
                page = (u8 *)0x80020000; src = page; src += 0x6198;
                *(Blob12 *)task->data = *(Blob12 *)src;
                page += 0x6198;                       /* retail loads the second half off ANOTHER base */
                *(Blob12 *)(task->data + 12) = *(Blob12 *)(page + 12);
RESOLVES    the r62_astra_big lane (dungeon/func_819A1654, 51 -> 24 pins): naming each object - `points =
            D_80024054[0];`, `*(Blob12 *)task->data = D_8002618C[0];` - and, for the last transfer, naming it
            while KEEPING its two chunks and re-pointing the held page register at the symbol
            (`copy_page = (u8 *)&D_80026198[0];` where the `page += 0x6198` stood) reproduces retail exactly;
            merging that transfer into one 24-byte aggregate costs 13 listing lines, because gcc's
            `expand_block_move` then runs one base register through all six words.  A run rewritten ALONE
            leaves a page base the other runs still hold, so the runs are screened one per signature and
            then applied TOGETHER, and only the joint text reaches `vf`.
CANDIDATES  per page run: the derived pointer and the copy statements replaced by one aggregate assignment
            from `D_<page+offset>` (the file's own unaligned struct type of that size, else an inserted
            `typedef struct { u8 b[N]; } AggUN;`; `extern u8 D_X[];` inserted when the symbol is new), with
            the run's pins on the page/source variables dropped and their dead declarations removed, then
            the window's remaining pins erased jointly and singly - listing-screened and gated as above.
"""
import difflib, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t72_stmtperm import decl_names
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t72_stmtperm import decl_names
    import screen

MAX_RUNS = 3
MAX_LISTINGS = 400
MAX_VERIFY = 6
MIN_PAIRS = 3
MAX_FOREIGN = 2
NEAR_VERIFY = 3                      # a nearest-but-not-exact listing is worth one `vf` at this distance

SIZES = {"u8": 1, "s8": 1, "char": 1, "signed char": 1, "unsigned char": 1,
         "u16": 2, "s16": 2, "short": 2, "unsigned short": 2,
         "u32": 4, "s32": 4, "int": 4, "unsigned": 4, "unsigned int": 4, "long": 4, "unsigned long": 4,
         "f32": 4, "float": 4, "uptr": 4,
         "s64": 8, "u64": 8, "long long": 8, "unsigned long long": 8, "f64": 8, "double": 8}
CAST_RE = re.compile(r"^\(\s*(?:struct\s+|union\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*(?:\s+(?:int|long|char))*"
                     r"\s*\*+\s*\)\s*")
DEREF_RE = re.compile(r"^\*\s*\(\s*(?P<ty>(?:struct\s+|union\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*"
                      r"(?:\s+(?:int|long|char))*)\s*\*\s*\)\s*(?P<addr>.+)$", re.S)
AT_RE = re.compile(r"^(?:S32_AT|U32_AT)\s*\(\s*(?P<b>[^,]+?)\s*,\s*(?P<o>0x[0-9A-Fa-f]+|\d+)\s*\)$")
UNK_RE = re.compile(r"^unk_(?P<o>[0-9A-Fa-f]{2,4})\b")
IDX_RE = re.compile(r"^(?P<f>[A-Za-z_]\w*)\s*\[\s*(?P<i>0x[0-9A-Fa-f]+|\d+)\s*\]$")
NAME_RE = re.compile(r"^[A-Za-z_]\w*$")
ASM_LINE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
STORE_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<lhs>[^;=]+?)\s*=(?!=)\s*(?P<v>[A-Za-z_]\w*)\s*;[ \t]*$")
LOAD_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*=(?!=)\s*(?P<e>[^;]+?)\s*;[ \t]*$")
TYPEDEF8 = re.compile(r"typedef\s+(?:unsigned\s+)?long\s+long\s+(?P<n>[A-Za-z_]\w*)\s*;")
MEMBER_RE = re.compile(r"^\s*(?P<ty>(?:struct\s+|union\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*"
                       r"(?:\s+(?:int|long|char))*)\s*(?P<ptr>\**)\s*(?P<n>[A-Za-z_]\w*)"
                       r"\s*(?:\[\s*(?P<arr>0x[0-9A-Fa-f]+|\d+)\s*\])?\s*;")


# ------------------------------------------------------------------ text helpers

def paren_ok(s):
    d = 0
    for ch in s:
        d += (ch in "([") - (ch in ")]")
        if d < 0:
            return False
    return d == 0


def strip_parens(e):
    """`((x))` -> `x` (only when the outer parentheses really wrap the whole expression)."""
    e = e.strip()
    while e.startswith("(") and e.endswith(")") and paren_ok(e[1:-1]):
        e = e[1:-1].strip()
    return e


def unwrap(e):
    """Outer parentheses and leading pointer casts removed: `((void *)p)` -> `p`."""
    prev = None
    while prev != e:
        prev = e
        e = strip_parens(e)
        m = CAST_RE.match(e)
        if m:
            e = e[m.end():].strip()
    return e


def top_plus(e):
    """Position of the last `+` at parenthesis depth 0, or None."""
    d, out = 0, None
    for i, ch in enumerate(e):
        if ch in "([":
            d += 1
        elif ch in ")]":
            d -= 1
        elif ch == "+" and d == 0 and i and e[i - 1] not in "+(<>=!*/%&|^,-":
            out = i
    return out


def type_size(ty, big):
    ty = re.sub(r"\s+", " ", (ty or "").strip())
    if ty in big:
        return 8
    return SIZES.get(ty, 4)


def addr_parts(addr):
    """(base, offset) for an address expression: `((u8 *)x + 0xC)` -> ('x', 12)."""
    addr = strip_parens(addr)
    p = top_plus(addr)
    off = 0
    if p is not None:
        tail = addr[p + 1:].strip()
        if not re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", tail):
            return None, None
        off, addr = int(tail, 0), addr[:p].strip()
    base = unwrap(addr)
    return (base or None), off


def memref(expr, hint, big):
    """(base, offset|None, size) for a memory element reference, or None for anything else."""
    e = strip_parens(expr)
    if NAME_RE.match(e):
        return None
    m = DEREF_RE.match(e)
    if m and paren_ok(m.group("addr")):
        size = type_size(m.group("ty"), big)
        base, off = addr_parts(m.group("addr"))
        return (base, off, size) if base else None
    m = AT_RE.match(e)
    if m:
        return unwrap(m.group("b")), int(m.group("o"), 0), 4
    if "->" in e or "." in e or e.endswith("]"):
        i = e.find("->")
        if i < 0:
            m = IDX_RE.match(e)
            if not m:
                return None
            base = unwrap(e[:e.rindex("[")])
            return (base, int(m.group("i"), 0) * hint, hint) if base else None
        d = 0
        for k, ch in enumerate(e):
            if ch in "([":
                d += 1
            elif ch in ")]":
                d -= 1
            elif d == 0 and e[k:k + 2] == "->":
                i = k
                break
        else:
            return None
        base, rest = unwrap(e[:i]), e[i + 2:].strip()
        if not base:
            return None
        first = re.split(r"[.\[]", rest, 1)[0]
        m = UNK_RE.match(rest)
        if m:
            return base, int(m.group("o"), 16), hint
        m = IDX_RE.match(rest)
        if m:
            return base, int(m.group("i"), 0) * hint, hint
        if re.fullmatch(r"[A-Za-z_]\w*", first):
            return base, None, hint
    return None


def big_types(text):
    return {"long long", "unsigned long long", "s64", "u64"} | set(TYPEDEF8.findall(text))


def pp_lines(text):
    """Line indices inside a preprocessor conditional (candidates never touch an unscored arm)."""
    out, depth = set(), 0
    for i, ln in enumerate(text.split("\n")):
        s = ln.strip()
        if s.startswith(("#if", "#ifdef", "#ifndef")):
            depth += 1
        if depth:
            out.add(i)
        if s.startswith("#endif") and depth:
            depth -= 1
    return out


def decl_line_of(mlines, lo, hi, name):
    """(index, single) of the declaration line of `name` in [lo, hi), single = it declares only `name`."""
    pat = re.compile(r"^[ \t]*(?:register[ \t]+|const[ \t]+|volatile[ \t]+|static[ \t]+)*"
                     r"[A-Za-z_][\w \t]*[ \t\*]+%s[ \t]*(?:ASM_REG\([^()]*\))?[ \t]*(?P<tail>[,;])" % re.escape(name))
    for i in range(lo, hi):
        m = pat.match(mlines[i])
        if m:
            return i, m.group("tail") == ";" and "," not in mlines[i]
    return None, False


def struct_size(text, ty, big):
    """Byte size of a named struct/typedef, or None when it cannot be read off the text."""
    ty = ty.strip()
    m = re.search(r"typedef\s+struct(?:\s+\w+)?\s*\{(?P<b>[^{}]*)\}\s*%s\s*;" % re.escape(ty), text) \
        or re.search(r"struct\s+%s\s*\{(?P<b>[^{}]*)\}" % re.escape(ty), text)
    if not m:
        return None
    total = 0
    body = mask_comments(m.group("b"))
    for part in body.split(";"):
        part = part.strip()
        if not part:
            continue
        mm = MEMBER_RE.match(part + ";")
        if not mm:
            return None
        n = 4 if mm.group("ptr") else type_size(mm.group("ty"), big)
        if not mm.group("ptr") and mm.group("ty").strip() not in SIZES and mm.group("ty").strip() not in big:
            return None
        total += n * (int(mm.group("arr"), 0) if mm.group("arr") else 1)
    return total or None


def ptr_type_of(mlines, lo, hi, params, name):
    """The declared pointee type name of `name` when it is a pointer to a named (non-builtin) type."""
    for p, ty, _, _ in params:
        if p == name:
            t = ty.strip()
            if t.endswith("*") and t.count("*") == 1:
                t = t[:-1].strip()
                return t if t not in SIZES and t not in ("void", "u8", "s8") else None
            return None
    i, _ = decl_line_of(mlines, lo, hi, name)
    if i is None:
        return None
    m = re.match(r"^[ \t]*(?:register[ \t]+|const[ \t]+|static[ \t]+)*(?P<ty>[A-Za-z_][\w \t]*?)[ \t]*\*[ \t]*%s\b"
                 % re.escape(name), mlines[i])
    if not m or "*" in mlines[i][:m.start("ty")]:
        return None
    t = re.sub(r"\s+", " ", m.group("ty").strip())
    return t if t not in SIZES and t not in ("void", "u8", "s8", "struct", "union") else None


# ------------------------------------------------------------------ run detection

def runs(text):
    """Every maximal scalarized copy run: a dict with the temps, bases, offsets and line span."""
    masked = mask_comments(text)
    mlines, out, ppl = masked.split("\n"), [], pp_lines(text)
    big = big_types(text)
    for fname, params, b0, b1 in functions(text):
        lo = masked.count("\n", 0, b0)
        hi = masked.count("\n", 0, b1)
        locals_ = decl_names(masked[b0:b1])
        pnames = {p for p, _, _, _ in params}
        sizes = {}
        for n in locals_:
            i, _ = decl_line_of(mlines, lo + 1, hi, n)
            if i is not None:
                m = re.match(r"^[ \t]*(?:register[ \t]+|const[ \t]+|static[ \t]+)*(?P<ty>[A-Za-z_][\w \t]*?)[ \t]+\**[ \t]*%s\b"
                             % re.escape(n), mlines[i])
                sizes[n] = type_size(m.group("ty"), big) if m else 4
        i = lo + 1
        while i < hi:
            items, j, foreign, seen = [], i, 0, set()
            while j < hi:
                ln = mlines[j]
                el = element(ln, locals_, pnames, sizes, big)
                if el:
                    items.append((j,) + el)
                    seen.add(el[1])
                    seen.add(el[2][0])
                    j += 1
                    continue
                if not ln.strip():
                    j += 1
                    continue
                if ASM_LINE.match(ln):
                    items.append((j, "pin", None, None))
                    j += 1
                    continue
                if items and foreign < MAX_FOREIGN and ln.rstrip().endswith(";") and "{" not in ln and "}" not in ln \
                        and not re.match(r"^[ \t]*(?:return|goto|break|continue|case|default)\b", ln) \
                        and not any(re.search(r"\b%s\b" % re.escape(n), ln) for n in seen):
                    items.append((j, "other", None, ln))
                    foreign += 1
                    j += 1
                    continue
                break
            r, rest = None, list(items)
            while len(rest) >= 2 * MIN_PAIRS:      # a stray load above the run shrinks off the left
                r = validate(list(rest), mlines, lo, hi, params, text, big, ppl)
                if r:
                    break
                rest = rest[1:]
            if r:
                r["fn"] = fname
                out.append(r)
                i = r["last"] + 1
            else:
                i += 1
    return out


def element(ln, locals_, pnames, sizes, big):
    """('store'|'load', temp, (base, off, size)) for one copy statement line, else None."""
    m = STORE_RE.match(ln)
    if m and m.group("v") in locals_ and paren_ok(m.group("lhs")):
        ref = memref(m.group("lhs"), sizes.get(m.group("v"), 4), big)
        if ref:
            return "store", m.group("v"), ref
    m = LOAD_RE.match(ln)
    if m and m.group("v") in locals_ and m.group("v") not in pnames and paren_ok(m.group("e")):
        ref = memref(m.group("e"), sizes.get(m.group("v"), 4), big)
        if ref:
            return "load", m.group("v"), ref
    return None


def validate(items, mlines, lo, hi, params, text, big, ppl):
    """The run description when the items are a whole-object copy, else None."""
    els = [it for it in items if it[1] in ("load", "store")]
    if len(els) < 2 * MIN_PAIRS:
        return None
    while items and items[-1][1] != "store":
        items.pop()
    els = [it for it in items if it[1] in ("load", "store")]
    loads = [it for it in els if it[1] == "load"]
    stores = [it for it in els if it[1] == "store"]
    if len(loads) != len(stores) or len(loads) < MIN_PAIRS:
        return None
    first, last = items[0][0], items[-1][0]
    if any(k in ppl for k in range(first, last + 1)):
        return None
    lbase = {it[3][0] for it in loads}
    sbase = {it[3][0] for it in stores}
    if len(lbase) != 1 or len(sbase) != 1:
        return None
    src, dst = lbase.pop(), sbase.pop()
    if src == dst or not src or not dst:
        return None
    pairs, pending = [], {}                 # each temp: load, then store, and a temp may be reused after that
    for it in els:
        if it[1] == "load":
            if it[2] in pending:
                return None
            pending[it[2]] = it
        else:
            ld = pending.pop(it[2], None)
            if ld is None or ld[3][2] != it[3][2]:
                return None
            pairs.append((it[2], ld[3], it[3]))
    if pending or len(pairs) < MIN_PAIRS:
        return None
    total = sum(p[1][2] for p in pairs)
    if total % 4 or total < 12:
        return None
    soff = [p[1][1] for p in pairs]
    doff = [p[2][1] for p in pairs]
    src_off = dst_off = 0
    if all(o is not None for o in soff):
        order = sorted(range(len(pairs)), key=lambda k: soff[k])
        cur = soff[order[0]]
        src_off = cur
        for k in order:
            if soff[k] != cur:
                return None
            cur += pairs[k][1][2]
        if all(o is not None for o in doff):
            dst_off = min(doff)
            if any(doff[k] - dst_off != soff[k] - src_off for k in range(len(pairs))):
                return None
    elif all(o is not None for o in doff):
        order = sorted(range(len(pairs)), key=lambda k: doff[k])
        cur = doff[order[0]]
        dst_off = cur
        for k in order:
            if doff[k] != cur:
                return None
            cur += pairs[k][1][2]
    temps = list(dict.fromkeys(p[0] for p in pairs))
    for it in items:
        if it[1] == "other" and any(re.search(r"\b%s\b" % re.escape(n), it[3]) for n in temps + [src, dst]):
            return None
    run_lines = {it[0] for it in items}
    drop, keep, relive = [], [], []
    for t in temps:
        uses = [k for k in range(lo + 1, hi) if k not in run_lines and re.search(r"\b%s\b" % re.escape(t), mlines[k])]
        dl, single = decl_line_of(mlines, lo + 1, hi, t)
        if dl is None or "=" in mlines[dl]:
            return None
        rest = [k for k in uses if k != dl]
        if not rest:
            (drop if single else keep).append((t, dl))
            continue
        keep.append((t, dl))
        nxt = next((k for k in rest if k > last), None)
        if nxt is not None and not re.match(r"^[ \t]*%s\s*=(?!=)" % re.escape(t), mlines[nxt]):
            ld = [it[0] for it in items if it[1] == "load" and it[2] == t]      # its value is live past the run
            if not ld:
                return None
            relive.append(ld[-1])
    return {"first": first, "last": last, "items": items, "pairs": pairs, "src": src, "dst": dst,
            "src_off": src_off, "dst_off": dst_off, "size": total, "temps": temps, "drop": drop, "keep": keep,
            "relive": sorted(relive), "lo": lo, "hi": hi, "params": params,
            "indent": re.match(r"[ \t]*", mlines[first]).group(0)}


# ------------------------------------------------------------------ rewriting

def typedef_name(text, size):
    """(name, needs_insert) for the CopyN struct covering `size` bytes."""
    n = size // 4
    for cand in ("Copy%d" % size, "AggCopy%d" % size):
        m = re.search(r"typedef\s+struct(?:\s+\w+)?\s*\{\s*s32\s+\w+\s*\[\s*(?P<k>\d+)\s*\]\s*;\s*\}\s*%s\s*;"
                      % cand, text)
        if m:
            if int(m.group("k")) == n:
                return cand, False
            continue
        if not re.search(r"\b%s\b" % cand, text):
            return cand, True
    return None, False


def insert_typedef(text, name, size):
    lines = text.split("\n")
    at = 0
    for i, ln in enumerate(lines[:60]):
        if ln.startswith("#include"):
            at = i + 1
    return "\n".join(lines[:at] + ["", "typedef struct { s32 word[%d]; } %s;" % (size // 4, name)] + lines[at:])


def obj_expr(base, off, ty, declared):
    """The lvalue for one side: `*src` / `*(T *)base` / `*(T *)((u8 *)base + 0x10)`."""
    if off:
        return "*(%s *)((u8 *)%s + %s)" % (ty, base, hex(off))
    if declared == ty:
        return "*%s" % base
    return "*(%s *)%s" % (ty, base)


def forms(text, run, mlines):
    """[(label, statement, extra_typedef|None)] - the aggregate assignments to try, best first."""
    lo, hi, params = run["lo"], run["hi"], run["params"]
    big = big_types(text)
    st = ptr_type_of(mlines, lo + 1, hi, params, run["src"])
    dt = ptr_type_of(mlines, lo + 1, hi, params, run["dst"])
    out, seen = [], set()

    def add(label, ty, declared_src, declared_dst, td=None):
        s = "%s = %s;" % (obj_expr(run["dst"], run["dst_off"], ty, declared_dst),
                          obj_expr(run["src"], run["src_off"], ty, declared_src))
        if s not in seen:
            seen.add(s)
            out.append((label, s, td))

    for ty in ([st] if st and st == dt else []):
        if struct_size(text, ty, big) in (None, run["size"]):
            add("named", ty, st, dt)
    for ty, side in ((st, "src"), (dt, "dst")):
        if ty and struct_size(text, ty, big) == run["size"]:
            add("named1_" + side, ty, st, dt)
    name, need = typedef_name(text, run["size"])
    if name:
        add("cast", name, st, dt, name if need else None)
    return out


def rewrite(text, run, stmt, td, place):
    """The run replaced by `stmt`, foreign statements kept, dead temp declarations dropped."""
    lines = text.split("\n")
    body = []
    for it in run["items"]:
        if it[1] == "other" or it[0] in run["relive"]:
            body.append(lines[it[0]])
        elif it[1] == "pin" and not any(re.search(r"\b%s\b" % re.escape(t), lines[it[0]]) for t in run["temps"]):
            body.append(lines[it[0]])
    call = run["indent"] + stmt
    block = ([call] + body) if place == "first" else (body + [call])
    new = lines[:run["first"]] + block + lines[run["last"] + 1:]
    for _, dl in sorted(run["drop"], key=lambda x: -x[1]):
        if dl < run["first"]:
            new.pop(dl)
    if td:
        return insert_typedef("\n".join(new), td, run["size"]), len(block)
    return "\n".join(new), len(block)


def plans(text, cand, run, copy_line):
    """[(label, [sites])] - the pin groups to erase, in the brief's order."""
    keep_lines = set()
    mlines = mask_comments(cand).split("\n")
    for t, _ in run["keep"]:
        i, _ = decl_line_of(mlines, 0, len(mlines), t)
        if i is not None:
            keep_lines.add(i + 1)
    sites = sites_of(cand)
    win = [s for s in sites if copy_line - 4 <= s[5] <= copy_line + 1 or s[5] in keep_lines]
    out, seen = [], set()
    for label, g in [("none", [])] + ([("win", win)] if len(win) > 1 else []) + \
            [("win1_%d" % k, [s]) for k, s in enumerate(win)] + ([("fn", sites)] if len(sites) > len(win) else []):
        key = tuple(s[3] for s in g)
        if key not in seen:
            seen.add(key)
            out.append((label, g))
    return out


# ------------------------------------------------------------------ page-based unaligned copies (round 62)

MAX_PAGE_RUNS = 4
MAX_JOINT_RUNS = 14                  # a function's page runs are rewritten together (round 64)
MAX_SIG_LISTINGS = 40                # listings spent screening one run signature
PAGE_SPAN = 18
PAGE_OTHER = 3
ATTRS = r"(?:__attribute__\s*\(\([^()]*\)\)\s*)*"
STRUCT_END = r"\}\s*" + ATTRS                     # `} __attribute__((packed)) Name;` and `} Name __attribute__((packed));`
MEMCPY_RE = re.compile(r"^[ \t]*memcpy\s*\(\s*(?P<d>.+)\s*,\s*(?P<s>.+)\s*,\s*(?P<n>0x[0-9A-Fa-f]+|\d+)\s*\)\s*;[ \t]*$")
PAGEC_RE = re.compile(r"^[ \t]*(?P<v>[A-Za-z_]\w*)\s*=(?!=)\s*(?P<rhs>.+?)\s*;[ \t]*$")
PLUSEQ_RE = re.compile(r"^[ \t]*(?P<v>[A-Za-z_]\w*)\s*(?P<op>\+|-)=\s*(?P<o>0x[0-9A-Fa-f]+|\d+)\s*;[ \t]*$")
LVNAME_RE = re.compile(r"^[A-Za-z_]\w*(?:\s*(?:\.|->)\s*[A-Za-z_]\w*)*$")
# `do {  page = (u8 *)0x80020000;  ASM_KEEP(page);  ...  } while (0);` on ONE line: m2c's staging block.
STAGE1_RE = re.compile(r"^(?P<ind>[ \t]*)do\s*\{(?P<body>.*)\}\s*while\s*\(\s*0\s*\)\s*;[ \t]*$")


def top_op(e):
    """(position, '+'|'-') of the last top-level additive operator, or (None, None)."""
    d, out, op = 0, None, None
    for i, ch in enumerate(e):
        if ch in "([":
            d += 1
        elif ch in ")]":
            d -= 1
        elif ch in "+-" and d == 0 and i and e[i - 1] not in "+-(<>=!*/%&|^," \
                and not (ch == "-" and e[i + 1:i + 2] == ">"):      # `task->data` is not a subtraction
            out, op = i, ch
    return out, op


def pbase_off(addr):
    """(base, offset) for `x`, `x + 0xC`, `x + (0xC)`, `(T *)((u8 *)x - 0x10)`; offset is signed."""
    addr = unwrap(addr)
    i, op = top_op(addr)
    off = 0
    if i is not None:
        tail = strip_parens(addr[i + 1:])
        if not re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", tail):
            return None, None
        off = int(tail, 0) * (-1 if op == "-" else 1)
        addr = addr[:i].strip()
    base = unwrap(addr)
    return (base or None), off


def cast_const(e):
    """The integer of `(u8 *)0x80020000` / `0x80020000`, else None."""
    e = unwrap(e)
    return int(e, 0) if re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", e) else None


def unfold(text):
    """Single-line `do { ... } while (0);` staging blocks split into bare statements at the block's indent.

    Returns (text, [(unfolded block, original line)]) - `refold` puts back every block a rewrite did not
    consume, so a partial result never reformats code it did not change.  Only blocks holding a page
    constant are touched, and never one carrying `break`/`continue`/a nested block."""
    lines, out, folds = text.split("\n"), [], []
    for ln in lines:
        m = STAGE1_RE.match(ln)
        body = m.group("body") if m else None
        if not body or "{" in body or "}" in body or not re.search(r"0x8[0-9A-Fa-f]{7}\b", body) \
                or re.search(r"\b(?:break|continue|return|goto)\b", body):
            out.append(ln)
            continue
        parts = [p.strip() for p in re.split(r"(?<=;)", body) if p.strip()]
        if not all(p.endswith(";") for p in parts) or len(parts) < 3:
            out.append(ln)
            continue
        new = [m.group("ind") + p for p in parts]
        folds.append(("\n".join(new), ln))
        out.extend(new)
    return "\n".join(out), folds


def refold(text, folds):
    """Every staging block still intact restored to its original one-line spelling."""
    for new, old in folds:
        text = text.replace(new, old)
    return text


def struct_text(text, ty):
    """(body, packed) of a named struct/typedef, or (None, False)."""
    for pat in (r"typedef\s+struct(?:\s+\w+)?\s*\{(?P<b>[^{}]*)" + STRUCT_END + r"%s\s*" + ATTRS + r";",
                r"struct\s+%s\s*\{(?P<b>[^{}]*)" + STRUCT_END):
        m = re.search(pat % re.escape(ty), text)
        if m:
            return mask_comments(m.group("b")), "packed" in m.group(0)
    return None, False


def members(text, ty, big, depth=0):
    """[(name, type, size, offset)] for a named struct, or None."""
    body, _ = struct_text(text, ty)
    if body is None or depth > 3:
        return None
    out, off = [], 0
    for part in body.split(";"):
        part = part.strip()
        if not part:
            continue
        m = MEMBER_RE.match(part + ";")
        if not m:
            return None
        n = 4 if m.group("ptr") else tsize(text, m.group("ty"), big, depth + 1)
        if n is None:
            return None
        n *= int(m.group("arr"), 0) if m.group("arr") else 1
        out.append((m.group("n"), m.group("ty").strip(), n, off))
        off += n
    return out or None


def tsize(text, ty, big, depth=0):
    """Byte size of a type name (builtin, typedef or struct), or None."""
    ty = re.sub(r"\s+", " ", (ty or "").strip())
    if ty in big:
        return 8
    if ty in SIZES:
        return SIZES[ty]
    ms = members(text, ty, big, depth)
    return sum(m[2] for m in ms) if ms else None


def talign(text, ty, big, depth=0):
    """Natural alignment of a type name (1 for a packed struct), or None."""
    ty = re.sub(r"\s+", " ", (ty or "").strip())
    if ty in big:
        return 8
    if ty in SIZES:
        return SIZES[ty]
    body, packed = struct_text(text, ty)
    if body is None or depth > 3:
        return None
    if packed:
        return 1
    ms = members(text, ty, big, depth)
    if ms is None:
        return None
    a = 1
    for _, mty, _, _ in ms:
        x = 4 if mty.endswith("*") else talign(text, mty, big, depth + 1)
        if x is None:
            return None
        a = max(a, min(x, 4))
    return a


def unaligned_types(text, big):
    """{size: name} for the file's struct types whose alignment is below a word."""
    out = {}
    for m in re.finditer(STRUCT_END + r"(?P<n>[A-Za-z_]\w*)\s*" + ATTRS + r";", text):
        n = m.group("n")
        if n in SIZES or n in out.values():
            continue
        s, a = tsize(text, n, big), talign(text, n, big)
        if s and a and a < 4 and s not in out:
            out[s] = n
    return out


def agg_forms(text, size, big):
    """[(type name, typedef text|None)] - unaligned struct types covering `size` bytes."""
    out = [(n, None) for s, n in unaligned_types(text, big).items() if s == size]
    name = "AggU%d" % size
    if not re.search(r"\b%s\b" % name, text):
        out.append((name, "typedef struct { u8 b[%d]; } %s;" % (size, name)))
    return out[:2]


def addr_expr(lv):
    """An address expression for an lvalue: `*(T *)p` -> `p`, `a.b` -> `&a.b`."""
    lv = strip_parens(lv)
    m = DEREF_RE.match(lv)
    if m and paren_ok(m.group("addr")):
        return strip_parens(m.group("addr"))
    if lv.startswith("*"):
        rest = strip_parens(lv[1:])
        return rest if NAME_RE.match(rest) else None
    if LVNAME_RE.match(lv):
        return "&" + lv
    m = IDX_RE.match(lv)
    return "&" + lv if m else None


def elem_of(ln, srcvar, text, big, ptype):
    """(size, soff, dst_addr, dst_off|None, dst_text, ty) for one copy reading through `srcvar`."""
    m = MEMCPY_RE.match(ln)
    if m and paren_ok(m.group("d")) and paren_ok(m.group("s")):
        b, o = pbase_off(m.group("s"))
        if b == srcvar and o is not None:
            return int(m.group("n"), 0), o, m.group("d").strip(), None, None, None
        return None
    m = STORE_RE.match(ln) or re.match(r"^(?P<ind>[ \t]*)(?P<lhs>.+?)\s*=(?!=)\s*(?P<v>.+?)\s*;[ \t]*$", ln)
    if not m:
        return None
    lhs, rhs = m.group("lhs").strip(), (m.group("v") if "v" in m.groupdict() else "").strip()
    if not paren_ok(lhs) or not paren_ok(rhs):
        return None
    da = addr_expr(lhs)
    if da is None:
        return None
    r = strip_parens(rhs)
    dm = DEREF_RE.match(r)
    if dm and paren_ok(dm.group("addr")):                       # *(T *)(src + off)
        b, o = pbase_off(dm.group("addr"))
        n = tsize(text, dm.group("ty"), big)
        if b == srcvar and o is not None and n and n % 4 == 0:
            return n, o, da, None, lhs, dm.group("ty")
        return None
    if r == "*" + srcvar or re.fullmatch(r"\*\s*%s" % re.escape(srcvar), r):
        n = tsize(text, ptype, big) if ptype else None
        return (n, 0, da, None, lhs, ptype) if n else None
    m2 = IDX_RE.match(r)
    if m2 and unwrap(r[:r.rindex("[")]) == srcvar and int(m2.group("i"), 0) == 0:
        n = tsize(text, ptype, big) if ptype else None
        return (n, 0, da, None, lhs, ptype) if n else None
    if ptype:                                                   # src->member / src.member
        mm = re.fullmatch(r"%s\s*->\s*([A-Za-z_]\w*)" % re.escape(srcvar), r)
        lm = re.fullmatch(r"(?P<p>.+?)\s*(?:\.|->)\s*(?P<m>[A-Za-z_]\w*)", lhs)
        if mm and lm and lm.group("m") == mm.group(1) and paren_ok(lm.group("p")):
            pa = addr_expr(lm.group("p").strip())
            for nm, _, sz, off in (members(text, ptype, big) or []):
                if nm == mm.group(1) and pa:
                    return sz, off, pa, off, lhs, None
    return None


def page_runs(text):
    """Every `page = 0x...; src = page + off; <aggregate copies through src>` run."""
    masked = mask_comments(text)
    mlines, out, ppl = masked.split("\n"), [], pp_lines(text)
    big = big_types(text)
    for fname, params, b0, b1 in functions(text):
        lo = masked.count("\n", 0, b0)
        hi = masked.count("\n", 0, b1)
        pages = []
        for k in range(lo + 1, hi):
            m = PAGEC_RE.match(mlines[k])
            if m:
                v = cast_const(m.group("rhs"))
                pages.append((k, m.group("v"),
                              v if v is not None and v >= 0x80000000 and not (v & 0xFFFF) else None))
        if not any(p[2] is not None for p in pages):
            continue
        k = lo + 1
        while k < hi:
            r = one_page_run(text, mlines, k, lo, hi, params, pages, ppl, big)
            if r:
                r["fn"] = fname
                out.append(r)
                k = r["last"] + 1
            else:
                k += 1
    return out


def one_page_run(text, mlines, start, lo, hi, params, pages, ppl, big):
    """The run beginning with the derived-pointer assignment on line `start`, or None."""
    if start in ppl:
        return None
    m = PAGEC_RE.match(mlines[start])
    if not m:
        return None
    srcvar = m.group("v")
    base, off = pbase_off(m.group("rhs"))
    val = next((v for k, n, v in reversed(pages) if n == base and k < start), None)
    if val is None or off is None:
        return None
    pagevar, addr = base, val + off
    ptype = ptr_type_of(mlines, lo + 1, hi, params, srcvar)
    ptypes = {srcvar: ptype, pagevar: ptr_type_of(mlines, lo + 1, hi, params, pagevar)}
    items, copies, foreign, j = [(start, "deriv")], [], 0, start + 1
    cursrc, curoff, pageval, rebase = srcvar, 0, val, None
    while j < hi and j - start <= PAGE_SPAN:
        if j in ppl:
            break
        ln = mlines[j]
        m2 = PLUSEQ_RE.match(ln)
        if m2 and m2.group("v") == cursrc and not copies:
            addr += int(m2.group("o"), 0) * (-1 if m2.group("op") == "-" else 1)
            items.append((j, "deriv"))
            j += 1
            continue
        if m2 and copies and rebase is None and m2.group("v") == pagevar and pagevar != cursrc:
            # the held page register is re-pointed at the SAME object halfway through the transfer:
            # retail changes the copy's source base there (dungeon/func_819A1654's last 24 bytes)
            nv = pageval + int(m2.group("o"), 0) * (-1 if m2.group("op") == "-" else 1)
            if nv != addr:
                break
            pageval, cursrc, curoff, rebase = nv, pagevar, nv - addr, j
            items.append((j, "rebase"))
            j += 1
            continue
        el = elem_of(ln, cursrc, text, big, ptypes.get(cursrc))
        if el:
            items.append((j, "copy"))
            copies.append(tuple(el[:1]) + (el[1] + curoff,) + tuple(el[2:]) + (j,))
            j += 1
            continue
        if not ln.strip():
            items.append((j, "blank"))
            j += 1
            continue
        if ASM_LINE.match(ln):
            items.append((j, "pin"))
            j += 1
            continue
        if copies:
            break
        if foreign < PAGE_OTHER and ln.rstrip().endswith(";") and "{" not in ln and "}" not in ln \
                and not re.match(r"^[ \t]*(?:return|goto|break|continue|case|default)\b", ln) \
                and not re.search(r"\b%s\b" % re.escape(srcvar), ln):
            items.append((j, "other"))
            foreign += 1
            j += 1
            continue
        break
    if not copies:
        return None
    while items[-1][1] in ("blank", "pin", "other"):
        k, kind = items[-1]
        if kind == "pin" and any(re.search(r"\b%s\b" % re.escape(n), mlines[k]) for n in (srcvar, pagevar)):
            break                                   # a trailing keep ON THE RUN'S OWN variables is the run's
        items.pop()
    if rebase is not None and rebase > items[-1][0]:
        rebase = None
    cur, dbase, dstart = 0, None, None
    for c in copies:
        n, so, da, doff = c[0], c[1], c[2], c[3]
        if so != cur:
            return None
        b, o = (da, doff) if doff is not None else pbase_off(da)
        if b is None:
            return None
        if dbase is None:
            dbase, dstart = b, o
        elif b != dbase or o - dstart != cur:
            return None
        cur += n
    if cur % 4 or cur < 8 or addr < 0x80000000:
        return None
    k = start - 1                                   # the page constant itself joins the run when it is adjacent
    pre = []
    while k > lo and (not mlines[k].strip() or ASM_LINE.match(mlines[k])) and start - k <= 4:
        pre.append((k, "pin" if ASM_LINE.match(mlines[k]) else "blank"))
        k -= 1
    m3 = PAGEC_RE.match(mlines[k]) if k > lo and k not in ppl else None
    if m3 and m3.group("v") == pagevar and cast_const(m3.group("rhs")) is not None:
        items = [(k, "deriv")] + sorted(pre) + items
    return {"first": items[0][0], "last": items[-1][0], "items": items, "copies": copies, "size": cur,
            "srcvar": srcvar, "pagevar": pagevar, "addr": addr, "dst": copies[0][2], "ptype": ptype,
            "rebase": rebase, "lo": lo, "hi": hi,
            "indent": re.match(r"[ \t]*", mlines[start]).group(0)}


SYMDECL_RE = r"extern\s+(?P<ty>(?:struct\s+|union\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*" \
             r"(?:\s+(?:int|long|char))*)\s*(?P<ptr>\**)\s*%s\s*(?P<arr>\[[^\]]*\])?\s*;"


def sym_decl(text, name):
    """(declared type, is an array) of `extern <ty> D_X[];`, or (None, False)."""
    m = re.search(SYMDECL_RE % re.escape(name), mask_comments(text))
    if not m or m.group("ptr"):
        return None, False
    return m.group("ty").strip(), m.group("arr") is not None


def paren_addr(e):
    """An address expression safe to cast: `(u8 *)p + 0x98` -> `((u8 *)p + 0x98)`."""
    e = e.strip()
    return e if NAME_RE.match(e) or re.fullmatch(r"&\s*[A-Za-z_]\w*(?:\s*(?:\.|->)\s*[A-Za-z_]\w*)*", e) \
        else "(" + e + ")"


def sym_names(text, addr):
    """[(source spelling, extern line|None)] for the object at `addr` - always a valid address."""
    name = "D_%08X" % addr
    if re.search(r"\b%s\b" % name, text):
        out = [("&" + name, None)]
        if sym_decl(text, name)[1]:                 # an array name decays: both spellings are addresses
            out.append((name, None))
        return out
    return [(name, "extern u8 %s[];" % name)]


def page_forms(text, run, big):
    """[(label, [statement lines], [extra declarations])] - the copies to try, best first."""
    out, seen = [], set()
    dst = paren_addr(run["dst"])
    name = "D_%08X" % run["addr"]
    dty, darr = sym_decl(text, name)
    if dty and tsize(text, dty, big) == run["size"]:
        # the object's OWN declared type: `points = D_80024054[0];` (the r62_astra_big spelling)
        add_form(out, seen, "typed_" + dty,
                 ["*(%s *)%s = %s;" % (dty, dst, name + "[0]" if darr else name)], [])
    for sym, ext in sym_names(text, run["addr"]):
        one = run["copies"][0]
        if len(run["copies"]) == 1 and one[5] and one[4]:
            add_form(out, seen, "same", ["%s = *(%s *)%s;" % (one[4], one[5], sym)], [ext])
        for ty, td in agg_forms(text, run["size"], big):
            add_form(out, seen, "agg_" + ty,
                     ["*(%s *)%s = *(%s *)%s;" % (ty, dst, ty, sym)], [ext, td])
    return out[:5]


def split_sub(run, sym):
    """astra's two-chunk form: {line: statements|None} keeping the run's own copy boundaries.

    The object is named, the copies that read it before the rebase take the symbol directly, the rebase
    statement re-points the held page register at the symbol and the copies after it are left alone."""
    if run["rebase"] is None:
        return None
    sub = {run["rebase"]: ["%s = (u8 *)%s;" % (run["pagevar"], sym)]}
    for n, so, da, doff, dst_text, ty, line in run["copies"]:
        if line > run["rebase"]:
            sub[line] = None                                    # reads the page var: already the symbol base
        elif dst_text and ty:
            src = sym if not so else "((u8 *)%s + 0x%X)" % (sym, so)
            sub[line] = ["%s = *(%s *)%s;" % (dst_text, ty, src)]
        else:
            return None
    return sub


def page_variants(text, run, big):
    """[(label, decls, statements, sub|None)] - every rewrite of one run, best first."""
    out = [(label, decls, stmts, None) for label, stmts, decls in page_forms(text, run, big)]
    if run["rebase"] is not None:
        for sym, ext in sym_names(text, run["addr"]):
            sub = split_sub(run, sym)
            if sub:
                out.insert(0, ("split_" + sym, [ext] if ext else [], [], sub))
    seen, uniq = {}, []                                   # labels index the joint phase's form choice
    for label, decls, stmts, sub in out[:6]:
        seen[label] = seen.get(label, 0) + 1
        uniq.append((label if seen[label] == 1 else "%s@%d" % (label, seen[label]), decls, stmts, sub))
    return uniq


def add_form(out, seen, label, stmts, decls):
    key = tuple(stmts)
    if key not in seen:
        seen.add(key)
        out.append((label, stmts, [d for d in decls if d]))


def insert_decls(text, decls):
    lines = text.split("\n")
    at = 0
    for i, ln in enumerate(lines[:80]):
        if ln.startswith("#include"):
            at = i + 1
    return "\n".join(lines[:at] + [""] + list(decls) + lines[at:])


def page_body(lines, run, stmts, keep_pins, sub=None):
    """(the run's replacement lines, index of the first new copy line inside them)."""
    names, body, done, at = (run["srcvar"], run["pagevar"]), [], False, 0
    for k, kind in run["items"]:
        if sub is not None and k in sub:
            if sub[k] is None:
                body.append(lines[k])
            else:
                if not done:
                    at, done = len(body), True
                body.extend(run["indent"] + s for s in sub[k])
        elif kind == "copy" and not done:
            at, done = len(body), True
            body.extend(run["indent"] + s for s in stmts)
        elif kind in ("copy", "deriv", "rebase"):
            continue
        elif kind == "pin":
            if keep_pins or not any(re.search(r"\b%s\b" % re.escape(n), lines[k]) for n in names):
                body.append(lines[k])
        else:
            body.append(lines[k])
    return body, at


def drop_dead(text, names):
    """Declarations of `names` with no remaining use in their function removed (with their ASM_REG pins)."""
    new = text.split("\n")
    for name in names:
        cand = "\n".join(new)
        masked = mask_comments(cand).split("\n")
        for _, _, b0, b1 in functions(cand):
            plo, phi = cand.count("\n", 0, b0), cand.count("\n", 0, b1)
            dl, single = decl_line_of(masked, plo + 1, phi, name)
            if dl is None or not single:
                continue
            if not [k for k in range(plo + 1, phi)
                    if k != dl and re.search(r"\b%s\b" % re.escape(name), masked[k])]:
                new.pop(dl)
            break
    return "\n".join(new)


def page_rewrite(text, run, stmts, decls, keep_pins, sub=None):
    """The run replaced by `stmts` (or by `sub`); dead page/source declarations dropped.

    Returns (text, 1-based line of the first new copy statement)."""
    lines = text.split("\n")
    body, at = page_body(lines, run, stmts, keep_pins, sub)
    new = lines[:run["first"]] + body + lines[run["last"] + 1:]
    line = run["first"] + at
    if decls:
        new = insert_decls("\n".join(new), decls).split("\n")
        line += len([d for d in decls if d]) + 1
    marker = new[line]
    out = drop_dead("\n".join(new), (run["srcvar"], run["pagevar"])).split("\n")
    best = min((k for k, ln in enumerate(out) if ln == marker), key=lambda k: abs(k - line), default=line)
    return "\n".join(out), best + 1


def page_apply(text, jobs):
    """Several runs of one text rewritten together: jobs = [(run, stmts, decls, keep_pins, sub)]."""
    lines, decls, names = text.split("\n"), [], set()
    for run, stmts, ds, keep, sub in sorted(jobs, key=lambda j: -j[0]["first"]):
        body, _ = page_body(lines, run, stmts, keep, sub)
        lines = lines[:run["first"]] + body + lines[run["last"] + 1:]
        decls += [d for d in ds if d]
        names.update((run["srcvar"], run["pagevar"]))
    text = "\n".join(lines)
    seen, uniq = set(), []
    for d in decls:
        if d not in seen:
            seen.add(d)
            uniq.append(d)
    if uniq:
        text = insert_decls(text, uniq)
    return drop_dead(text, sorted(names))


def page_plans(cand, copy_line):
    """[(label, [sites])] - the pin groups to erase around the new copy."""
    sites = sites_of(cand)
    win = [s for s in sites if copy_line - 2 <= s[5] <= copy_line + 4]
    out, seen = [], set()
    for label, g in [("none", [])] + ([("win", win)] if len(win) > 1 else []) + \
            [("win1_%d" % k, [s]) for k, s in enumerate(win)]:
        key = tuple(s[3] for s in g)
        if key not in seen:
            seen.add(key)
            out.append((label, g))
    return out[:6]


def run_sig(run):
    """Runs with the same signature take the same rewrite: screen one, apply to all (round 64)."""
    c = run["copies"][0]
    return (run["addr"], run["size"], len(run["copies"]), c[5], run["rebase"] is not None,
            run["srcvar"], run["pagevar"])


def page_joint(row, text, target, vf, budget, folds):
    """Every page run of the function rewritten at once.  (text, tag) or None.

    The four runs of dungeon/func_8187C45C share ONE materialised page base and the seven spawn branches
    of dungeon/func_819A1654 copy the same object, so a run rewritten alone leaves a base the others still
    hold; astra's exact texts rewrite them together.  One listing screen per run SIGNATURE picks the form,
    then all the runs carrying a chosen form are applied together and the joint text alone reaches `vf`."""
    runs = page_runs(text)[:MAX_JOINT_RUNS]
    if len(runs) < 2:
        return None
    big, pins_in = big_types(text), len(sites_of(text))
    best, spent = {}, 0
    for run in runs:
        sig = run_sig(run)
        if sig in best:
            continue
        for label, decls, stmts, sub in page_variants(text, run, big):
            for keep in (False, True):
                if budget[0] >= MAX_LISTINGS or spent >= MAX_SIG_LISTINGS:
                    break
                c = refold(page_apply(text, [(run, stmts, decls, keep, sub)]), folds)
                out = len(sites_of(c))
                if out >= pins_in:
                    continue
                lst = screen.compile_s(row, c)
                budget[0] += 1
                spent += 1
                d = screen.sdiff(target, lst)
                if d is None:
                    continue
                budget[2] = d if budget[2] is None else min(budget[2], d)
                if best.get(sig) is None or (d, out) < best[sig][:2]:
                    best[sig] = (d, out, label, keep)
    if not best:
        return None
    for only_zero in (False, True):
        jobs, tags = [], []
        for run in runs:
            b = best.get(run_sig(run))
            if not b or (only_zero and b[0]):
                continue
            v = {l: (dc, st, sb) for l, dc, st, sb in page_variants(text, run, big)}.get(b[2])
            if v is None:
                continue
            jobs.append((run, v[1], v[0], b[3], v[2]))
            tags.append("%s/%s" % (b[2], "keep" if b[3] else "drop"))
        if len(jobs) < 2 or budget[0] >= MAX_LISTINGS or budget[1] >= MAX_VERIFY:
            continue
        c = refold(page_apply(text, jobs), folds)
        out = len(sites_of(c))
        if out >= pins_in:
            continue
        lst = screen.compile_s(row, c)
        budget[0] += 1
        d = screen.sdiff(target, lst)
        if d is None:
            continue
        budget[2] = d if budget[2] is None else min(budget[2], d)
        if d:
            continue
        budget[1] += 1
        if vf(c).get("exact"):
            return c, "joint%d:%s" % (len(jobs), "+".join(sorted(set(tags))))
    return None


def page_step(row, cur, target, vf, budget, folds=()):
    """One page-run rewrite that the byte gate accepts, or None.  budget = [listings, verifies, best]."""
    big = big_types(cur)
    for run in page_runs(cur)[:MAX_PAGE_RUNS]:
        ranked, pins_in = [], len(sites_of(cur))
        for label, decls, stmts, sub in page_variants(cur, run, big):
            for keep in (True, False):
                base, copy_line = page_rewrite(cur, run, stmts, decls, keep, sub)
                for pl, group in page_plans(base, copy_line):
                    if budget[0] >= MAX_LISTINGS:
                        break
                    c = refold(erase_many(base, group, clean_notes=True) if group else base, folds)
                    out = len(sites_of(c))
                    if out >= pins_in:
                        continue
                    lst = screen.compile_s(row, c)
                    budget[0] += 1
                    d = screen.sdiff(target, lst)
                    if d is not None:
                        budget[2] = d if budget[2] is None else min(budget[2], d)
                        ranked.append((d, out, "%s/%s/%s" % (label, "keep" if keep else "drop", pl), c))
        ranked.sort(key=lambda x: (x[0], x[1]))
        for d, out, tag, c in ranked:
            if budget[1] >= MAX_VERIFY or d:
                break
            budget[1] += 1
            if vf(c).get("exact"):
                return c, tag
    return None


def page_phase(row, cur, target, vf, budget):
    """The page passes over one text: the joint rewrite first, then run-by-run.  (text, [tags])."""
    steps = []
    folded, folds = unfold(cur)
    if folds and not page_runs(folded):
        folded, folds = cur, []
    got = page_joint(row, folded, target, vf, budget, folds)
    if got:
        cur, tag = got
        steps.append("page:" + tag)
    else:
        cur = refold(folded, folds)
    while budget[0] < MAX_LISTINGS and budget[1] < MAX_VERIFY:
        folded, folds = unfold(cur)
        if folds and not page_runs(folded):
            folded, folds = cur, []
        got = page_step(row, folded, target, vf, budget, folds)
        if not got:
            break
        cur, tag = got
        steps.append("page:" + tag)
    return cur, steps

# ------------------------------------------------------------------ generator

class T:
    name = "t78_aggcopy"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        if "=" not in text:
            return "no statements"
        if runs(text) or page_runs(text):
            return None
        folded, folds = unfold(text)                    # a run staged inside a one-line do/while block
        if folds and page_runs(folded):
            return None
        return "no scalarized copy run"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in,
                          "pins_out": pins_in}
        seen_runs, best_d, nruns = set(), None, 0
        for _ in range(MAX_RUNS):
            live = [r for r in runs(cur) if (r["src"], r["dst"], len(r["pairs"])) not in seen_runs]
            if not live or listings >= MAX_LISTINGS:
                break
            run = live[0]
            seen_runs.add((run["src"], run["dst"], len(run["pairs"])))
            nruns += 1
            mlines = mask_comments(cur).split("\n")
            ranked = []
            for fi, (label, stmt, td) in enumerate(forms(cur, run, mlines)):
                for pi, place in enumerate(("first", "last")):
                    base, nblock = rewrite(cur, run, stmt, td, place)
                    if pi and nblock == 1:
                        break                                   # nothing else in the run: one placement only
                    copy_line = run["first"] + 1 - sum(1 for _, dl in run["drop"] if dl < run["first"]) \
                        + (0 if place == "first" else nblock - 1) + (2 if td else 0)
                    for pl, group in plans(cur, base, run, copy_line):
                        if listings >= MAX_LISTINGS:
                            break
                        c = erase_many(base, group, clean_notes=True) if group else base
                        out = len(sites_of(c))
                        lst = screen.compile_s(row, c)
                        listings += 1
                        d = screen.sdiff(target, lst)
                        if d is None:
                            continue
                        best_d = d if best_d is None else min(best_d, d)
                        if out < pins_in:                       # only a pin-removing text is worth `vf`
                            ranked.append((d, out, fi, pi, "%s/%s/%s" % (label, place, pl), c))
            ranked.sort(key=lambda x: (x[0], x[1], x[2], x[3]))
            hit = False
            for d, out, _, _, tag, c in ranked:
                if verifies >= MAX_VERIFY or (d and (hit or d > NEAR_VERIFY or verifies)):
                    break
                verifies += 1
                if vf(c).get("exact"):
                    cur, hit = c, True
                    steps.append(tag)
                    break
        budget = [listings, verifies, None]
        cur, page_steps = page_phase(row, cur, target, vf, budget)
        steps += page_steps
        listings, verifies, page_d = budget
        if page_d is not None:
            best_d = page_d if best_d is None else min(best_d, page_d)
        info = {"listings": listings, "tried": verifies, "runs": nruns, "best_d": best_d,
                "pins_in": pins_in, "pins_out": len(sites_of(cur))}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
