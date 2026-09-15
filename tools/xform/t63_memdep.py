"""T63: access-spelling flips that move gcc 2.x's MEM_IN_STRUCT_P dependence exemption.

MECHANISM (measured, tools/fixtures/memdep/run.sh; read tools/fixtures/memdep/memdep.c).
gcc 2.7.2 sched.c lines 815-880 (`true_dependence`, `anti_dependence`, `output_dependence`;
byte-identical in 2.8.1 sched.c ~849) treat two memory references that `memrefs_conflict_p` cannot
separate as INDEPENDENT when one is a struct-member access through a VARYING address
(`MEM_IN_STRUCT_P` set, mode not QImode) and the other is a NON-struct access at a FIXED address (a
bare global scalar through a SYMBOL_REF, or a stack slot through the frame/stack pointer;
`rtx_addr_varies_p`, rtlanal.c 163).  cse.c `invalidate` (~7571) and loop.c (~2682) consult the same
flag, so it also decides which loads CSE keeps across a store and what loop.c treats as invariant.

`MEM_IN_STRUCT_P` is set by expand_expr for COMPONENT_REF (`p->f`, `s.f`), for ARRAY_REF (`a[i]`,
`G[0]`) and for INDIRECT_REF of an aggregate type.  A plain scalar VAR_DECL (`extern s32 G; ... G`)
and a cast dereference (`*(s32 *)((u8 *)p + 8)`, `M2C_FIELD`) are NOT in-struct.  So the SPELLING of
one access - member vs cast, scalar global vs one-element array vs struct member - changes
instruction order, surviving loads and hoisting at IDENTICAL address arithmetic.  Fixture result in
every stock cell but 2.91.66 (haifa): shapes A (`p->a = v; return G;`), F (a short member) and G
(`G = v; return p->a;`) emit the LOAD FIRST - the exemption fired and the scheduler hoisted the load
over the store - while B (the same store as a cast), C (`G` as `H[0]`), D (`G` as `GS.x`), E (a u8
member: QImode is never exempt) and H keep store-then-load.  Under `-G0`, G loses the exemption in
2.8.x/2.95.2 as well, so the struct-STORE direction (A/F) is the one that bites on those cells.

THE FLIPS (each keeps the address arithmetic identical; the screen and `vf` decide, nothing else is
asserted):
  member->cast    `p->f`, `(*p).f`, `((S *)p)->f`, `p->f.g`, `s.f`   ->  `(*(T *)((u8 *)p + OFF))`
  cast->member    `*(T *)((u8 *)p + OFF)`, `M2C_FIELD(p, T *, OFF)`  ->  `((S *)p)->m`
  global<->array  `extern T G;` with uses `G`  <->  `extern T G[1];` with uses `G[0]`
  elem<->cast     `G[k]` (k constant)  <->  `(*(T *)((u8 *)G + k*sizeof(T)))`
  cast<->index    `*(T *)((u8 *)p + OFF)`  <->  `((T *)p)[OFF/sizeof(T)]`, OFF a non-zero multiple

The last pair is an ADDITION to the four flips the brief listed, measured with the same fixture
(work/native_lane/t63_dev/scratch/probe2.c, every cell): `((int *)p)[3] = v; return G;` emits the
LOAD FIRST - an ARRAY_REF sets MEM_IN_STRUCT_P exactly as a COMPONENT_REF does - while the byte-cast
spelling of the same address keeps store-then-load.  Index 0 is NOT equivalent (`p[0]` folds to
`*p`, an INDIRECT_REF of a scalar: store-first), so the flip is only made for a non-zero index.  It
matters because the two struct flips partition the corpus: a row written with raw casts usually has
no struct typedef to name, so flip 2 skips it as `no-struct-at-offset`, and this spelling reaches
those rows without inventing a type.
Byte-typed (u8/s8) accesses are never exempt in sched but may still matter in cse, so they are tried
last.  T and OFF come from the struct declarations VISIBLE to the row (its own typedefs and the
headers it includes); an access that cannot be resolved is skipped with a recorded reason - no struct
type is ever invented.

CV-QUALIFIERS ARE PART OF THE TYPE and every flip carries them (`Type.quals`; a qualified BASE
declaration, `volatile S *p`, is skipped outright as `qualified-base`).  Dropping a `volatile` is not
a spelling change, and nothing downstream would catch it: cc1's listing is often byte-identical
across the qualifier, so the screen passes at distance 0, and `vf` only checks retail bytes.  An
earlier revision stripped `const`/`volatile` while resolving a member; on the 200 evaluated rows that
silently rewrote 50 volatile accesses as plain ones, and it made dungeon/func_80AD7000 look like a
d0=4 -> d=1 near-miss for THIS mechanism when the whole movement was the lost qualifier (with the
qualifier kept, the cast spelling reproduces the member listing byte for byte: the MEM_IN_STRUCT_P
flag changed nothing on that row).

`pin_sites.erase_many` DELETES lines, so inside the search every per-plan quantity - the window's
centre (`map_line`), the struct table and its `decl_end` offsets, the arm labels - is recomputed on
the ERASED text, never carried over from the pinned one.

Candidates per row: for each live ASM_* site, the accesses within 8 lines, (a) each flipped alone and
(b) every access of the same base flipped together, each tried with the nearest pin erased and, when
2-3 pins sit in the window, with all of them erased.  Every candidate is screened with
`xform.screen.compile_s`/`sdiff` against the CURRENT text's listing (the pinned text is byte-exact,
so distance 0 means identical cc1 output); `vf` is called only on distance-0 candidates that pass
`pin_search_engine.improves`.  Budgets `T63_SCREENS` (600) and `T63_VERIFY` (6) per row; the search
restarts on the new text after a win.

`memdep_candidates(text)` exposes the same flips as a search menu (<= 48, the single-access flips
nearest a live pin first).

No scaffolding is ever emitted: this generator only respells existing accesses and erases pins.
"""
import collections
import difflib
import os
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from common import sha_text
from pin_census import sites_of, unscored_text, asm_blocker, arm_labels, HAS_PP_RE
from pin_sites import erase_many
from pin_search_engine import improves, mechanism
from xform.screen import compile_s, sdiff

INCLUDE = ROOT / "include"
WINDOW = 8                      # lines each side of a pin site
MENU_CAP = 48

# ------------------------------------------------------------------ types and layout

SCALARS = {
    "char": (1, 1), "signed char": (1, 1), "unsigned char": (1, 1),
    "u8": (1, 1), "s8": (1, 1), "M2C_UNK8": (1, 1), "_Bool": (1, 1),
    "short": (2, 2), "unsigned short": (2, 2), "signed short": (2, 2),
    "u16": (2, 2), "s16": (2, 2), "M2C_UNK16": (2, 2),
    "int": (4, 4), "unsigned": (4, 4), "unsigned int": (4, 4), "signed": (4, 4), "signed int": (4, 4),
    "long": (4, 4), "unsigned long": (4, 4), "signed long": (4, 4),
    "u32": (4, 4), "s32": (4, 4), "M2C_UNK": (4, 4), "M2C_UNK32": (4, 4),
    "f32": (4, 4), "float": (4, 4),
    "f64": (8, 8), "double": (8, 8),
    "s64": (8, 8), "u64": (8, 8), "M2C_UNK64": (8, 8), "long long": (8, 8),
    "unsigned long long": (8, 8), "signed long long": (8, 8),
}
PTR = (4, 4)
BYTE_TYPES = {"u8", "s8", "char", "signed char", "unsigned char", "M2C_UNK8"}

ID = r"[A-Za-z_]\w*"
NUMRE = re.compile(r"^-?(?:0[xX][0-9A-Fa-f]+|\d+)$")


def _num(s):
    s = s.strip()
    if s.startswith("(") and s.endswith(")"):
        s = s[1:-1].strip()
    if not NUMRE.match(s):
        return None
    return int(s, 16) if "x" in s.lower() else int(s, 10)


def _fmt_off(v):
    return str(v) if -10 < v < 10 else ("-0x%X" % -v if v < 0 else "0x%X" % v)


QUALS = ("const", "volatile")


def _split_quals(spelling):
    """`volatile u8` -> ('u8', ('volatile',)).  Qualifiers are canonically ordered so that
    `const volatile T` and `volatile const T` compare equal in `flips_of`'s spelling match."""
    words = spelling.split()
    quals = tuple(q for q in QUALS if q in words)
    return " ".join(w for w in words if w not in QUALS), quals


class Type:
    """A C type as (unqualified base spelling, pointer depth, cv-qualifiers).

    The qualifiers are part of the type and MUST survive a flip: dropping a `volatile` (or adding
    one) is not a spelling change - cc1's listing can be byte-identical while the C means something
    else, and `vf` only checks retail bytes, so nothing downstream would catch it.  `const` matters
    to this mechanism too: expand_expr sets RTX_UNCHANGING_P on a const MEM and sched.c's
    `true_dependence` returns 0 for those outright."""

    __slots__ = ("base", "ptr", "agg", "quals")

    def __init__(self, base, ptr=0, agg=None, quals=()):
        self.base, self.ptr, self.agg = base, ptr, agg
        self.quals = tuple(q for q in QUALS if q in quals)

    @property
    def qual_prefix(self):
        return "".join(q + " " for q in self.quals)

    @property
    def spelling(self):
        return self.qual_prefix + self.base + (" " + "*" * self.ptr if self.ptr else "")

    def cast_spelling(self):
        """How the type is written inside `*(T *)`: one more star, no space before it."""
        return self.qual_prefix + self.base + " " + "*" * (self.ptr + 1)

    def qualified(self, extra):
        """This type with the enclosing aggregate's qualifiers folded in."""
        return self if not extra else Type(self.base, self.ptr, self.agg, self.quals + tuple(extra))

    def __repr__(self):
        return "Type(%r)" % self.spelling


def _tagname(base):
    """`struct S` / `union S` name the struct `S`; every other spelling names itself."""
    return base.split(None, 1)[1] if base.startswith(("struct ", "union ")) else base


def _sizeof(ty, structs):
    if ty.ptr:
        return PTR
    if ty.agg is not None:
        return (ty.agg["size"], ty.agg["align"])
    if ty.base in SCALARS:
        return SCALARS[ty.base]
    s = structs.get(_tagname(ty.base))
    if s and s.get("ok"):
        return (s["size"], s["align"])
    return None


def _strip_comments(text):
    out, i, n = list(text), 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and text[i + 1:i + 2] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
        elif c == "/" and text[i + 1:i + 2] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            j = min(j + 1, n)
        else:
            i += 1
            continue
        for k in range(i, j):
            if out[k] != "\n":
                out[k] = " "
        i = j
    return "".join(out)


def _matching(s, i):
    """Index just past the `}` matching the `{` at s[i]."""
    depth = 0
    while i < len(s):
        if s[i] == "{":
            depth += 1
        elif s[i] == "}":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return -1


def _split_members(body):
    """Top-level `;`-separated member declarations of a struct/union body."""
    out, depth, start = [], 0, 0
    for i, c in enumerate(body):
        if c in "{([":
            depth += 1
        elif c in "})]":
            depth -= 1
        elif c == ";" and depth == 0:
            piece = body[start:i].strip()
            if piece:
                out.append(piece)
            start = i + 1
    tail = body[start:].strip()
    if tail:
        out.append(tail)
    return out


_AGG_HEAD = re.compile(r"^((?:volatile\s+|const\s+)*)(struct|union)\b")


def _parse_member(decl, structs):
    """-> (Type, [(name, [array dims])]) or (None, reason).

    cv-qualifiers are CARRIED on the Type, never dropped: see Type's docstring."""
    decl = decl.strip()
    if ":" in re.sub(r"\[[^\]]*\]", "", decl):
        return None, "bitfield"
    m = _AGG_HEAD.match(decl)
    if m:
        quals = tuple(m.group(1).split())
        rest = decl[m.end():].lstrip()
        tag = ""
        tm = re.match(ID, rest)
        if tm:
            tag = tm.group(0)
            rest = rest[tm.end():].lstrip()
        if rest.startswith("{"):
            end = _matching(rest, 0)
            if end < 0:
                return None, "unresolved-struct"
            agg = _layout(rest[1:end - 1], m.group(2) == "union", structs)
            if not agg["ok"]:
                return None, agg["why"]
            ty = Type("struct " + tag if tag else "struct", 0, agg, quals)
            decls = rest[end:].strip()
        else:
            # a plain `struct TAG` reference: the keyword is part of the type's spelling
            ty = Type((m.group(2) + " " + tag) if tag else m.group(2), 0, None, quals)
            decls = rest
    else:
        # plain type words then declarators
        words, quals = [], []
        i = 0
        while True:
            wm = re.match(r"\s*(" + ID + r")", decl[i:])
            if not wm:
                break
            w = wm.group(1)
            if w in QUALS:
                quals.append(w)
                i += wm.end()
                continue
            nxt = decl[i + wm.end():].lstrip()
            if words and not (words[-1] in ("unsigned", "signed", "long", "short") and
                              w in ("char", "short", "int", "long")):
                break
            words.append(w)
            i += wm.end()
            if nxt[:1] in ("*", ";", ",", "[", "") or re.match(r"^" + ID + r"\s*(?:\[|;|,|$)", nxt):
                if not (words[-1] in ("unsigned", "signed", "long", "short")):
                    break
        if not words:
            return None, "unresolved-member"
        ty = Type(" ".join(words), 0, None, quals)
        decls = decl[i:]
    names = []
    for part in _split_top(decls, ","):
        part = part.strip()
        if not part:
            continue
        if "(" in part:
            return None, "complex-type"
        pm = re.match(r"^((?:\*\s*)*)(" + ID + r")((?:\s*\[[^\]]*\])*)\s*$", part)
        if not pm:
            return None, "unresolved-member"
        dims = []
        bad = False
        for d in re.findall(r"\[([^\]]*)\]", pm.group(3)):
            v = _num(d)
            if v is None:
                bad = True
            dims.append(v)
        if bad:
            return None, "unresolved-member"
        names.append((pm.group(2), pm.group(1).count("*"), dims))
    if not names:
        return None, "unresolved-member"
    return ty, names


def _split_top(s, sep):
    out, depth, start = [], 0, 0
    for i, c in enumerate(s):
        if c in "{([":
            depth += 1
        elif c in "})]":
            depth -= 1
        elif c == sep and depth == 0:
            out.append(s[start:i])
            start = i + 1
    out.append(s[start:])
    return out


def _layout(body, is_union, structs):
    """{'ok', 'size', 'align', 'members': [(name, off, Type, dims)], 'why'}"""
    members, off, align, size = [], 0, 1, 0
    for decl in _split_members(body):
        ty, info = _parse_member(decl, structs)
        if ty is None:
            return {"ok": False, "why": info, "size": 0, "align": 1, "members": []}
        for name, stars, dims in info:
            mty = Type(ty.base, ty.ptr + stars, ty.agg, ty.quals)
            sz = _sizeof(mty, structs)
            if sz is None:
                return {"ok": False, "why": "unresolved-struct", "size": 0, "align": 1, "members": []}
            msize, malign = sz
            for d in reversed(dims):
                msize *= d
            if is_union:
                moff = 0
            else:
                off = (off + malign - 1) // malign * malign
                moff = off
                off += msize
            align = max(align, malign)
            size = max(size, moff + msize)
            members.append((name, moff, mty, dims))
    size = (size + align - 1) // align * align
    return {"ok": True, "why": None, "size": size, "align": align, "members": members}


_TYPEDEF_RE = re.compile(r"\btypedef\s+(struct|union)\s+(" + ID + r")?\s*\{")
_PLAIN_RE = re.compile(r"(?<!typedef\s)\b(struct|union)\s+(" + ID + r")\s*\{")


def parse_structs(text):
    """{name: layout} for every `typedef struct NAME { ... } NAME;` / `struct NAME { ... };`.

    Declarations are processed in file order so a struct may use one declared above it; a struct that
    cannot be laid out keeps `ok=False` with the reason, and `decl_end` records where its typedef
    closes (a flip may not name a struct declared below the access)."""
    src = _strip_comments(text)
    structs = {}
    for m in re.finditer(r"\b(?:typedef\s+)?(struct|union)\s+(" + ID + r")?\s*\{", src):
        istypedef = src[:m.start()].rstrip().endswith("typedef") or \
            re.search(r"\btypedef\s+$", src[max(0, m.start() - 12):m.start()]) is not None
        open_brace = src.index("{", m.start())
        end = _matching(src, open_brace)
        if end < 0:
            continue
        body = src[open_brace + 1:end - 1]
        tail = src[end:end + 200]
        names = []
        tm = re.match(r"\s*(" + ID + r")\s*;", tail)
        if m.group(2):
            names.append(m.group(2))
        if tm and (istypedef or True):
            names.append(tm.group(1))
        lay = _layout(body, m.group(1) == "union", structs)
        lay["decl_end"] = end + (tm.end() if tm else 0)
        for n in dict.fromkeys(names):
            structs.setdefault(n, lay)
    return structs


def _includes(text):
    """The headers a text includes.  Scanned on the raw text: _strip_comments blanks strings too."""
    return [m.group(1) for m in
            re.finditer(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"', text, re.M)]


_HDR_CACHE = {}


def _header_structs(name, seen):
    if name in seen:
        return {}
    seen.add(name)
    if name in _HDR_CACHE:
        return _HDR_CACHE[name]
    p = INCLUDE / name
    if not p.is_file():
        _HDR_CACHE[name] = {}
        return {}
    t = p.read_text(errors="replace")
    out = {}
    for inc in _includes(t):
        out.update(_header_structs(inc, seen))
    out.update(parse_structs(t))
    _HDR_CACHE[name] = out
    return out


def visible_structs(text):
    """Structs the row can name: those of the headers it includes, then its own (which win)."""
    out, seen = {}, set()
    for inc in _includes(text):
        out.update(_header_structs(inc, seen))
    for k, v in out.items():
        v = dict(v)
        v["decl_end"] = -1                # a header declaration precedes every access
        out[k] = v
    own = parse_structs(text)
    out.update(own)
    return out


def leaves(struct, structs, prefix="", base_off=0, depth=0, quals=()):
    """[(path, offset, Type)] for every scalar/pointer leaf reachable by member syntax.

    `quals` carries the cv-qualifiers of the enclosing aggregates down: in
    `volatile struct { s32 a; } x;` the leaf `x.a` is a `volatile s32`, and a flip that spelled it
    `*(s32 *)(...)` would silently drop the qualifier."""
    if depth > 6 or not struct.get("ok"):
        return []
    out = []
    for name, off, ty, dims in struct["members"]:
        path = prefix + name
        if dims:
            continue                       # a member of array type is never flipped
        if ty.ptr == 0 and ty.agg is not None:
            out.extend(leaves(ty.agg, structs, path + ".", base_off + off, depth + 1,
                              quals + ty.quals))
            continue
        if ty.ptr == 0 and ty.base not in SCALARS:
            sub = structs.get(_tagname(ty.base))
            if sub and sub.get("ok"):
                out.extend(leaves(sub, structs, path + ".", base_off + off, depth + 1,
                                  quals + ty.quals))
            continue
        out.append((path, base_off + off, ty.qualified(quals)))
    return out


# ------------------------------------------------------------------ access finding

class Access:
    __slots__ = ("kind", "start", "end", "line", "base", "off", "type", "text", "group", "priority")

    def __init__(self, kind, start, end, line, base, off, ty, text, group, priority=2):
        self.kind, self.start, self.end, self.line = kind, start, end, line
        self.base, self.off, self.type, self.text = base, off, ty, text
        self.group, self.priority = group, priority

    def __repr__(self):
        return "Access(%s,%s,%s,%s)" % (self.kind, self.base, self.off, self.text)


def _lineno(text, pos):
    return text.count("\n", 0, pos) + 1


def _arm_of(labels, line):
    return labels[line - 1] if labels and line <= len(labels) else "both"


def _in_macro(text, pos):
    ls = text.rfind("\n", 0, pos) + 1
    if text[ls:pos + 1].lstrip().startswith("#"):
        return True
    prev_end = ls - 1
    prev_start = text.rfind("\n", 0, prev_end) + 1
    return text[ls:text.find("\n", pos) if text.find("\n", pos) > 0 else len(text)].rstrip().endswith("\\") or \
        text[prev_start:prev_end].rstrip().endswith("\\")


_DECL_RE = re.compile(r"(?:^|[(,;{]|\bregister\b)\s*(?P<q>(?:const\s+|volatile\s+)*)(?:struct\s+)?(?P<ty>"
                      + ID + r")\s*(?P<stars>(?:\*\s*)+)(?P<name>" + ID + r")\s*(?=[;,)=])", re.M)
_STRUCT_LOCAL_RE = re.compile(r"(?:^|[(,;{])\s*(?P<q>(?:const\s+|volatile\s+)*)(?:struct\s+)?(?P<ty>"
                              + ID + r")\s+(?P<name>" + ID + r")\s*(?=[;,)=])", re.M)


def pointer_types(code, structs):
    """{var: struct name} for locals/parameters declared as `S *v`."""
    out = {}
    for m in _DECL_RE.finditer(code):
        if m.group("stars").count("*") == 1 and m.group("ty") in structs:
            out[m.group("name")] = m.group("ty")
    return out


def struct_locals(code, structs):
    out = {}
    for m in _STRUCT_LOCAL_RE.finditer(code):
        if m.group("ty") in structs and m.group("ty") != m.group("name"):
            out[m.group("name")] = m.group("ty")
    return out


def qualified_bases(code, structs):
    """Bases whose DECLARATION is cv-qualified (`volatile S *p`, `const S s`).

    Every member reached through such a base inherits the qualifier, and the cast spelling would
    have to carry it through the inner `(u8 *)` too; rather than reason about that, accesses on
    these bases are skipped (reason `qualified-base`).

    Only declarations whose type NAMES A VISIBLE STRUCT count.  The two declaration regexes also
    match inside a struct body, where `struct { volatile u8 v; } at00u;` would otherwise put the
    member name `v` in the set and silence every access through an unrelated pointer called `v`."""
    out = set()
    for rx in (_DECL_RE, _STRUCT_LOCAL_RE):
        for m in rx.finditer(code):
            if m.group("q").strip() and m.group("ty") in structs:
                out.add(m.group("name"))
    return out


_CASTBASE_RE = re.compile(r"\(\s*\(\s*(" + ID + r")\s*\*\s*\)\s*(" + ID + r")\s*\)\s*->\s*")
_ARROW_RE = re.compile(r"(?<![\w.>])(" + ID + r")\s*->\s*")
_DEREF_RE = re.compile(r"\(\s*\*\s*(" + ID + r")\s*\)\s*\.\s*")
_DOT_RE = re.compile(r"(?<![\w.>)\]])(" + ID + r")\s*\.\s*")
_CHAIN_RE = re.compile(r"(" + ID + r")((?:\s*\.\s*" + ID + r")*)")


def _member_accesses(text, code, structs, skips):
    """Every resolvable member access, as an Access with kind 'member'."""
    out = []
    ptypes = pointer_types(code, structs)
    slocals = struct_locals(code, structs)
    qbases = qualified_bases(code, structs)
    addressed = set(re.findall(r"&\s*(" + ID + r")\b", code))
    seen = set()

    def emit(mstart, chain_at, sname, base_expr, is_local):
        if base_expr in qbases:
            skips["qualified-base"] += 1
            return
        cm = _CHAIN_RE.match(code, chain_at)
        if not cm:
            skips["unresolved-member"] += 1
            return
        end = cm.end()
        if code[end:end + 1] in ("[", "("):
            skips["array-member" if code[end:end + 1] == "[" else "complex-type"] += 1
            return
        path = re.sub(r"\s+", "", cm.group(0))
        st = structs.get(sname)
        if not st or not st.get("ok"):
            skips["unresolved-struct"] += 1
            return
        table = {p: (o, t) for p, o, t in leaves(st, structs)}
        if path not in table:
            # a whole-aggregate access (`p->sub` where sub is a struct) is a copy, not a scalar MEM
            skips["struct-typed" if any(k.startswith(path + ".") for k in table)
                  else "unresolved-member"] += 1
            return
        off, ty = table[path]
        pre = code[max(0, mstart - 12):mstart]
        if re.search(r"&\s*$", pre) or re.search(r"\bsizeof\s*\(\s*$", pre):
            skips["address-of"] += 1
            return
        if is_local and base_expr not in addressed:
            skips["local-not-addressed"] += 1
            return
        if (mstart, end) in seen:
            return
        seen.add((mstart, end))
        group = ("base", base_expr)
        prio = 3 if ty.base in BYTE_TYPES and ty.ptr == 0 else (0 if ty.ptr == 0 and ty.base not in BYTE_TYPES else 1)
        out.append(Access("member", mstart, end, _lineno(text, mstart),
                          ("&" + base_expr) if is_local else base_expr, off, ty,
                          text[mstart:end], group, prio))

    for m in _CASTBASE_RE.finditer(code):
        emit(m.start(), m.end(), m.group(1), m.group(2), False)
    for m in _ARROW_RE.finditer(code):
        if code[max(0, m.start() - 1):m.start()] == ")":
            continue
        sname = ptypes.get(m.group(1))
        if not sname:
            skips["unresolved-struct"] += 1
            continue
        emit(m.start(), m.end(), sname, m.group(1), False)
    for m in _DEREF_RE.finditer(code):
        sname = ptypes.get(m.group(1))
        if not sname:
            skips["unresolved-struct"] += 1
            continue
        emit(m.start(), m.end(), m.group(1), m.group(1), False)
    for m in _DOT_RE.finditer(code):
        sname = slocals.get(m.group(1))
        if not sname:
            continue
        emit(m.start(), m.end(), sname, m.group(1), True)
    return out


_CAST_RE = re.compile(
    r"\*\s*\(\s*(?P<ty>" + ID + r"(?:\s+" + ID + r")*)\s*(?P<stars>(?:\*\s*)+)\)\s*"
    r"\(\s*\(\s*(?:u8|s8|char|unsigned\s+char|signed\s+char)\s*\*\s*\)\s*"
    r"(?P<base>" + ID + r")\s*\+\s*(?P<off>\(\s*-?(?:0[xX][0-9A-Fa-f]+|\d+)\s*\)|-?(?:0[xX][0-9A-Fa-f]+|\d+))\s*\)")
_M2C_RE = re.compile(
    r"M2C_FIELD\s*\(\s*(?P<base>" + ID + r")\s*,\s*(?P<ty>" + ID + r"(?:\s+" + ID + r")*)\s*"
    r"(?P<stars>(?:\*\s*)+)\s*,\s*(?P<off>\(?\s*-?(?:0[xX][0-9A-Fa-f]+|\d+)\s*\)?)\s*\)")
_INDEX_RE = re.compile(
    r"\(\s*\(\s*(?P<ty>" + ID + r"(?:\s+" + ID + r")*)\s*(?P<stars>(?:\*\s*)+)\)\s*"
    r"(?P<base>" + ID + r")\s*\)\s*\[\s*(?P<idx>-?(?:0[xX][0-9A-Fa-f]+|\d+))\s*\]")
_CAST_VAR_RE = re.compile(
    r"\*\s*\(\s*" + ID + r"(?:\s+" + ID + r")*\s*(?:\*\s*)+\)\s*"
    r"\(\s*\(\s*(?:u8|s8|char)\s*\*\s*\)\s*" + ID + r"\s*\+\s*(?![-(\d]|0[xX])")


def _cast_accesses(text, code, skips):
    out = []
    for rx, macro in ((_CAST_RE, False), (_M2C_RE, True)):
        for m in rx.finditer(code):
            off = _num(m.group("off"))
            if off is None:
                skips["variable-offset"] += 1
                continue
            stars = m.group("stars").count("*")
            tbase, tquals = _split_quals(m.group("ty"))
            if not tbase:
                skips["complex-type"] += 1
                continue
            ty = Type(tbase, stars - 1, None, tquals)
            start, end = m.start(), m.end()
            if not macro and code[max(0, start - 1):start] == "(" and code[end:end + 1] == ")":
                start, end = start - 1, end + 1       # the row idiom's outer parens
            pre = code[max(0, start - 12):start]
            if re.search(r"&\s*$", pre):
                skips["address-of"] += 1
                continue
            prio = 3 if ty.base in BYTE_TYPES and ty.ptr == 0 else (0 if ty.ptr == 0 else 1)
            out.append(Access("cast", start, end, _lineno(text, start), m.group("base"), off, ty,
                              text[start:end], ("base", m.group("base")), prio))
    for m in _CAST_VAR_RE.finditer(code):
        skips["variable-offset"] += 1
    for m in _INDEX_RE.finditer(code):
        k = _num(m.group("idx"))
        if k is None:
            skips["variable-index"] += 1
            continue
        tbase, tquals = _split_quals(m.group("ty"))
        if not tbase:
            skips["complex-type"] += 1
            continue
        ty = Type(tbase, m.group("stars").count("*") - 1, None, tquals)
        esz = _elem_size(ty)
        if esz is None:
            skips["complex-type"] += 1
            continue
        pre = code[max(0, m.start() - 12):m.start()]
        if re.search(r"&\s*$", pre):
            skips["address-of"] += 1
            continue
        prio = 3 if ty.base in BYTE_TYPES and ty.ptr == 0 else (0 if ty.ptr == 0 else 1)
        out.append(Access("index", m.start(), m.end(), _lineno(text, m.start()), m.group("base"),
                          k * esz, ty, text[m.start():m.end()], ("base", m.group("base")), prio))
    return out


def _elem_size(ty):
    if ty.ptr:
        return PTR[0]
    return SCALARS[ty.base][0] if ty.base in SCALARS else None


IDB = ID + r"\b"       # a maximal identifier: `[A-Za-z_]\w*` alone may match a prefix of a longer one
_EXTERN_SCALAR_RE = re.compile(r"^[ \t]*extern[ \t]+(?P<ty>(?:const[ \t]+|volatile[ \t]+)?" + IDB +
                               r"(?:[ \t]+" + IDB + r")*)[ \t]*(?P<stars>(?:\*[ \t]*)*)"
                               r"(?P<name>" + IDB + r")[ \t]*(?P<dim>\[[^\]]*\])?[ \t]*;", re.M)


def _header_names(text):
    """Every identifier any included header declares (a global there may not be respelled)."""
    names = set()
    seen = set()

    def walk(name):
        if name in seen:
            return
        seen.add(name)
        p = INCLUDE / name
        if not p.is_file():
            return
        t = _strip_comments(p.read_text(errors="replace"))
        for m in _EXTERN_SCALAR_RE.finditer(t):
            names.add(m.group("name"))
        for m in re.finditer(r"^[ \t]*(?:extern[ \t]+)?[A-Za-z_][\w \t\*\(\)]*?\b(" + IDB + r")[ \t]*(?:\[[^\]]*\])?[ \t]*(?:;|\()", t, re.M):
            names.add(m.group(1))
        for m in re.finditer(r"^[ \t]*#[ \t]*define[ \t]+(" + ID + r")", t, re.M):
            names.add(m.group(1))
        for inc in _includes(t):
            walk(inc)
    for inc in _includes(text):
        walk(inc)
    return names


def global_flips(text, code, structs, skips, labels):
    """[(label, new_text, group, line, priority)] for flips 3 and 4 on the row's own externs."""
    out = []
    hdr = _header_names(text)
    # A declaration's own `[N]` is a dimension, not a subscript: never rewrite inside one.
    decl_spans = [(d.start(), d.end()) for d in _EXTERN_SCALAR_RE.finditer(code)]
    in_decl = lambda pos: any(a <= pos < b for a, b in decl_spans)
    for m in _EXTERN_SCALAR_RE.finditer(code):
        name, dim, stars = m.group("name"), m.group("dim"), m.group("stars")
        tbase, tquals = _split_quals(m.group("ty"))
        if not tbase:
            skips["complex-type"] += 1
            continue
        # the qualifier is part of the type: `extern volatile u8 G[8]` must cast to `volatile u8 *`
        ty = Type(tbase, stars.count("*"), None, tquals)
        if name in hdr:
            skips["global-in-include"] += 1
            continue
        if ty.ptr == 0 and ty.base not in SCALARS:
            skips["unresolved-struct"] += 1
            continue
        uses = [u for u in re.finditer(r"(?<![\w.>])" + re.escape(name) + r"\b(?!\s*\()", code)
                if not in_decl(u.start())]
        if not uses:
            continue
        if any(_arm_of(labels, _lineno(text, u.start())) in ("port", "dead") for u in uses):
            skips["global-in-unscored-arm"] += 1
            continue
        line = _lineno(text, uses[0].start())
        esz = SCALARS.get(ty.base, PTR)[0] if ty.ptr == 0 else 4
        if dim is None:
            # flip 3 forward: scalar -> one-element array
            pieces, ok = [], True
            for u in uses:
                after = code[u.end():u.end() + 2]
                if after.lstrip()[:1] == "[":
                    ok = False
                    break
                # every use becomes `G[0]`, `&G` included: `&G` on an array is the array's address,
                # a different type, and the brief's spelling is `&G[0]`.
                pieces.append((u.start(), u.end(), name + "[0]"))
            if not ok:
                skips["unresolved-member"] += 1
                continue
            new = _apply(text, pieces + [(m.start("name"), m.end("name"), name + "[1]")])
            out.append(("g2arr:%s" % name, new, ("global", name), line, 0 if ty.ptr == 0 else 1))
        elif _num(dim[1:-1]) == 1:
            pieces, ok = [], True
            for u in uses:
                if code[u.end():u.end() + 3].replace(" ", "")[:3] == "[0]":
                    # only the subscript goes: a leading `&` still has to address the object
                    pieces.append((u.start(), code.index("]", u.end()) + 1, name))
                else:
                    ok = False
                    break
            if not ok:
                skips["unresolved-member"] += 1
                continue
            new = _apply(text, pieces + [(m.start("dim"), m.end("dim"), "")])
            out.append(("arr2g:%s" % name, new, ("global", name), line, 0))
        # flip 4: a constant-index element of a global array <-> the cast
        if dim is not None:
            for u in re.finditer(r"(?<![\w.>])" + re.escape(name) + r"\s*\[\s*(-?(?:0[xX][0-9A-Fa-f]+|\d+))\s*\]", code):
                k = _num(u.group(1))
                if k is None or in_decl(u.start()):
                    continue
                if _arm_of(labels, _lineno(text, u.start())) in ("port", "dead"):
                    skips["in-unscored-arm"] += 1
                    continue
                if re.search(r"&\s*$", code[max(0, u.start() - 4):u.start()]):
                    skips["address-of"] += 1
                    continue
                rep = "(*(%s)((u8 *)%s + %s))" % (ty.cast_spelling(), name, _fmt_off(k * esz))
                out.append(("elem2cast:%s[%d]" % (name, k), _apply(text, [(u.start(), u.end(), rep)]),
                            ("global", name), _lineno(text, u.start()),
                            3 if ty.base in BYTE_TYPES and ty.ptr == 0 else 0))
    return out


def _apply(text, pieces):
    """Replace disjoint (start, end, repl) spans, last first."""
    for s, e, r in sorted(pieces, key=lambda p: p[0], reverse=True):
        text = text[:s] + r + text[e:]
    return text


def _cast_spelling(base, off, ty):
    return "(*(%s)((u8 *)%s + %s))" % (ty.cast_spelling(), base, _fmt_off(off))


def _member_spelling(sname, base, path):
    return "((%s *)%s)->%s" % (sname, base, path)


def find_accesses(text, structs=None, skips=None):
    """Every flippable access in `text`, with the skip reasons counted along the way."""
    skips = collections.Counter() if skips is None else skips
    structs = visible_structs(text) if structs is None else structs
    code = _strip_comments(text)
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    out = []
    for a in _member_accesses(text, code, structs, skips) + _cast_accesses(text, code, skips):
        if _arm_of(labels, a.line) in ("port", "dead"):
            skips["in-unscored-arm"] += 1
            continue
        if _in_macro(text, a.start):
            skips["in-macro-def"] += 1
            continue
        out.append(a)
    out.sort(key=lambda a: a.start)
    return out


def flips_of(text, a, structs, skips):
    """[(label, replacement)] for one access - every spelling it can be flipped to."""
    if a.kind == "member":
        return [("m2c:%d:%s+%s" % (a.line, a.base, _fmt_off(a.off)),
                 _cast_spelling(a.base, a.off, a.type))]
    if a.kind == "index":
        return [("i2c:%d:%s+%s" % (a.line, a.base, _fmt_off(a.off)),
                 _cast_spelling(a.base, a.off, a.type))]
    out = []
    want = re.sub(r"\s+", "", a.type.spelling)
    hits, late = [], False
    for name, st in structs.items():
        if not st.get("ok"):
            continue
        match = [p for p, off, ty in leaves(st, structs)
                 if off == a.off and re.sub(r"\s+", "", ty.spelling) == want]
        if not match:
            continue
        if st.get("decl_end", 0) > a.start:   # the typedef closes below the access: it cannot be named
            late = True
            continue
        hits.append((name, match[0]))
    if hits:
        code = _strip_comments(text)
        preferred = pointer_types(code, structs).get(a.base)
        used = collections.Counter(m.group(1) for m in _CASTBASE_RE.finditer(code)
                                   if m.group(2) == a.base)
        hits.sort(key=lambda h: (h[0] != preferred, -used[h[0]], h[0]))
        name, path = hits[0]
        out.append(("c2m:%d:%s->%s" % (a.line, name, path), _member_spelling(name, a.base, path)))
    elif late:
        skips["typedef-after-use"] += 1
    else:
        skips["no-struct-at-offset"] += 1
    esz = _elem_size(a.type)
    if esz and a.off and a.off % esz == 0:
        out.append(("c2i:%d:%s[%d]" % (a.line, a.base, a.off // esz),
                    "((%s)%s)[%d]" % (a.type.cast_spelling(), a.base, a.off // esz)))
    elif esz is None:
        skips["complex-type"] += 1
    return out


def flip_of(text, a, structs, skips):
    """The first flip of an access, or None (kept for callers that want one spelling)."""
    fl = flips_of(text, a, structs, skips)
    return fl[0] if fl else None


# ------------------------------------------------------------------ candidate plans

def _single_flips(text, accesses, structs, skips):
    out = []
    for a in accesses:
        for label, rep in flips_of(text, a, structs, skips):
            if rep == a.text:
                continue
            out.append((label, _apply(text, [(a.start, a.end, rep)]), a))
    return out


def _group_flips(text, accesses, structs, skips):
    """Every access of one base flipped together (retail's author spelled one pointer one way)."""
    by = collections.defaultdict(list)
    for a in accesses:
        for label, rep in flips_of(text, a, structs, skips):
            by[(a.group, label.split(":")[0])].append((a, rep))
    out = []
    for (group, family), members in sorted(by.items(), key=lambda kv: (kv[0][0], kv[0][1])):
        if len(members) < 2:
            continue
        pieces = [(a.start, a.end, rep) for a, rep in members if rep != a.text]
        if len(pieces) < 2:
            continue
        out.append(("group:%s:%s:%s:n%d" % (family, group[0], group[1], len(pieces)),
                    _apply(text, pieces), members[0][0]))
    return out


def all_flips(text, structs=None, skips=None):
    """[(label, candidate_text, anchor Access or None)] - every flip this text admits."""
    skips = collections.Counter() if skips is None else skips
    structs = visible_structs(text) if structs is None else structs
    code = _strip_comments(text)
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    accesses = find_accesses(text, structs, skips)
    out = _single_flips(text, accesses, structs, skips)
    out += _group_flips(text, accesses, structs, skips)
    for label, new, group, line, prio in global_flips(text, code, structs, skips, labels):
        out.append((label, new, Access("global", 0, 0, line, group[1], 0, Type("void"), "", group, prio)))
    return out


def _rank_key(a, anchor_line):
    """Nearest a pin first; non-byte scalar flips before pointer flips before byte flips."""
    if a is None:
        return (9999, 3, 0)
    return (abs(a.line - anchor_line) if anchor_line is not None else a.line, a.priority, a.line)


def memdep_candidates(text):
    """Menu generator: <= 48 access-spelling flips, the singles nearest a live pin first."""
    try:
        structs = visible_structs(text)
    except Exception:
        return []
    skips = collections.Counter()
    try:
        accesses = find_accesses(text, structs, skips)
    except Exception:
        return []
    pins = sites_of(text)
    anchors = [s[5] for s in pins]
    anchor = None
    singles = _single_flips(text, accesses, structs, skips)
    if anchors:
        def near(a):
            return min(abs(a.line - x) for x in anchors)
        singles.sort(key=lambda t: (near(t[2]), t[2].priority, t[2].line))
    else:
        singles.sort(key=lambda t: (t[2].priority, t[2].line))
    out, seen = [], {text}
    for label, cand, a in singles:
        if cand in seen:
            continue
        seen.add(cand)
        out.append(("memdep:" + label, cand))
        if len(out) >= MENU_CAP:
            return out
    rest = _group_flips(text, accesses, structs, skips)
    code = _strip_comments(text)
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    rest += [(l, c, None) for l, c, g, ln, p in global_flips(text, code, structs, skips, labels)]
    for item in rest:
        label, cand = item[0], item[1]
        if cand in seen:
            continue
        seen.add(cand)
        out.append(("memdep:" + label, cand))
        if len(out) >= MENU_CAP:
            break
    return out


# ------------------------------------------------------------------ the generator

def map_line(old, new, line):
    """Map a 1-based line number of `old` onto `new`.

    `pin_sites.erase_many` DELETES whole lines (an erased statement's line, its pin note, an emptied
    `#ifndef NON_MATCHING` pair), so every line below an erasure shifts up.  A window centred on the
    un-erased line number would select a different set of accesses; a difflib alignment is exact
    whatever erase_many removed, and costs nothing beside a compile."""
    a, b = old.splitlines(), new.splitlines()
    if a == b:
        return line
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    i = line - 1
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if i1 <= i < i2:
            return (j1 + (i - i1) if tag == "equal" else j1) + 1
    return max(1, len(b))


def erasure_plans(text, window=WINDOW):
    """[(label, [sites], anchor_line)]: the nearest pin alone, then the window's 2-3 pins together."""
    pins = sites_of(text)
    plans = []
    for i, s in enumerate(pins):
        plans.append(("pin%d" % i, [s], s[5]))
    for i, s in enumerate(pins):
        near = [t for t in pins if abs(t[5] - s[5]) <= window]
        if 2 <= len(near) <= 3 and near[0] is s:
            plans.append(("pins%d+%d" % (i, len(near)), near, s[5]))
    return plans


class T:
    name = "t63_memdep"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pins"
        if not row.get("cfg"):
            return "missing compiler recipe"
        skips = collections.Counter()
        try:
            structs = visible_structs(text)
            accesses = find_accesses(text, structs, skips)
        except Exception as e:
            return "parse error: %r" % (e,)
        if not accesses:
            return "no resolvable memory accesses"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        screens = max(1, int(os.getenv("T63_SCREENS", "600")))
        verifies = max(1, int(os.getenv("T63_VERIFY", "6")))
        pins_in = len(sites_of(text))
        usig = unscored_text(text)
        skips = collections.Counter()
        log = dict(pins_in=pins_in, pins_out=pins_in, screen_budget=screens, vf_budget=verifies,
                   screened=0, tried=0, candidates_n=0, compile_failures=0, steps=[], nearest=[],
                   plans=0, accesses=0, bare_globals=0, moved=0, erasures=[], skips={})
        cur = text
        near, dead = [], set()
        try:
            first = True
            while True:                     # the screen budget bounds this; a win restarts the search
                won = False
                ref = compile_s(row, cur)
                if ref is None:
                    log["error"] = "reference-build-error"
                    break
                structs = visible_structs(cur)
                code = _strip_comments(cur)
                labels = arm_labels(cur) if HAS_PP_RE.search(cur) else None
                log["bare_globals"] = len(list(_EXTERN_SCALAR_RE.finditer(code)))
                if first:            # the row's skip census: one scan of the whole text, not per plan
                    first = False
                    whole = find_accesses(cur, structs, skips)
                    for a in whole:
                        flips_of(cur, a, structs, skips)
                    global_flips(cur, code, structs, skips, labels)
                    log["accesses_total"] = len(whole)
                plans = erasure_plans(cur)
                log["plans"] = len(plans)
                seen_cand = set()
                for plab, chosen, anchor in plans:
                    base = erase_many(cur, chosen, clean_notes=True)
                    if unscored_text(base) != usig:
                        skips["in-unscored-arm"] += 1
                        continue
                    if log["screened"] < screens:
                        log["screened"] += 1
                        erased = compile_s(row, base)
                        d0 = sdiff(ref, erased)
                        # The bare erasure is measured, never verified: a pin that falls on its own is
                        # pin_search's win, not this mechanism's, and would flatter the evaluation.
                        log["erasures"].append({"plan": plab, "d0": d0,
                                                "class": mechanism(ref, erased)})
                    else:
                        d0 = None
                    bskips = collections.Counter()
                    # Everything below is measured on the ERASED text: erase_many deletes lines, so
                    # `cur`'s line numbers, arm labels and struct decl_end offsets are all stale here.
                    banchor = map_line(cur, base, anchor)
                    bcode = _strip_comments(base)
                    bstructs = visible_structs(base)
                    blabels = arm_labels(base) if HAS_PP_RE.search(base) else None
                    ball = find_accesses(base, bstructs, bskips)
                    baccess = [a for a in ball if abs(a.line - banchor) <= WINDOW]
                    log["accesses"] = max(log["accesses"], len(baccess))
                    cands = _single_flips(base, baccess, bstructs, bskips)
                    # (b) every access of a base seen in the window, flipped across the whole function
                    bases = {a.group for a in baccess}
                    cands += _group_flips(base, [a for a in ball if a.group in bases],
                                          bstructs, bskips)
                    for label, new, group, line, prio in global_flips(base, bcode, bstructs,
                                                                      bskips, blabels):
                        if abs(line - banchor) <= WINDOW:
                            cands.append((label, new, Access("global", 0, 0, line, group[1], 0,
                                                             Type("void"), "", group, prio)))
                    cands.sort(key=lambda t: _rank_key(t[2], banchor))
                    for label, cand, a in cands:
                        h = sha_text(cand)
                        if h in seen_cand:
                            continue
                        seen_cand.add(h)
                        log["candidates_n"] += 1
                        if log["screened"] >= screens:
                            skips["budget"] += 1
                            continue
                        log["screened"] += 1
                        got = compile_s(row, cand)
                        if got is None:
                            log["compile_failures"] += 1
                            skips["compile-fail"] += 1
                            continue
                        d = sdiff(ref, got)
                        near.append((d, plab + "+" + label, d0))
                        if d0 is not None and d != d0:
                            log["moved"] += 1
                        if d != 0:
                            continue
                        if not improves(cur, cand) or unscored_text(cand) != usig:
                            continue
                        # An assembler-side pin leaves several spellings with ONE cc1 listing and one
                        # verdict; re-verifying them only spends the row's budget (80CC2828 spent
                        # all six that way).  The key carries the surviving pins too, because maspsx
                        # sees macros cc1 does not, so two plans are not interchangeable.
                        listing = (sha_text("\n".join(got)),
                                   tuple(sorted(s[1] for s in sites_of(cand))))
                        if listing in dead:
                            skips["same-listing-as-a-failed-verify"] += 1
                            continue
                        if log["tried"] >= verifies:
                            skips["budget"] += 1
                            continue
                        log["tried"] += 1
                        if not vf(cand).get("exact"):
                            dead.add(listing)
                        else:
                            cur = cand
                            log["steps"].append(plab + "+" + label)
                            won = True
                            break
                    if won:
                        break
                if not won:
                    break
        except Exception as e:                       # a parse fault must not fail a sweep row
            log["error"] = repr(e)
        log["skips"] = dict(sorted(skips.items()))
        log["nearest"] = [{"d": d, "d0": z, "label": l}
                          for d, l, z in sorted(near, key=lambda x: (x[0] is None, x[0]))[:12]]
        log["erasures"] = sorted(log["erasures"], key=lambda e: (e["d0"] is None, e["d0"]))[:8]
        log["pins_out"] = len(sites_of(cur))
        if not log["steps"]:
            return None, log
        return cur, log
