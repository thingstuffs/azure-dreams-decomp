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
        return None if runs(text) else "no scalarized copy run"

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
        info = {"listings": listings, "tried": verifies, "runs": nruns, "best_d": best_d,
                "pins_in": pins_in, "pins_out": len(sites_of(cur))}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
