#!/usr/bin/env python3
"""Call-arity helpers behind levels.py's L5 `fidelity_site` predicate (round 95, owner decision 9;
census: work/native_lane/r95_pt/CENSUS.md section 4).

The baseline audit (config/decomp_audit_baseline.json) records PASSTHRU / INDIRECT_PASSTHRU /
JT_KEEP_ORDER sites from the RETAIL bytes; a correct arity-complete C still carries them, so
they cannot be what keeps a row off L5.  What can: a call in the current C that is arity-short
against the callee's definition (PASSTHRU), an empty-argument call through an untyped `()` slot
(INDIRECT_PASSTHRU), a computed `goto *` that is still in the text (JT_KEEP_ORDER).  A site whose
keyed function the row's text does not even define is a phantom (SLUS rows share/merge `defs`).

Everything here reads comment-stripped C text; nothing is compiled.  The definition index over
src/{main,town,dungeon,slus} is built lazily on the first PASSTHRU site that survives the phantom
filter and cached (tests inject their own with `DefIndex.from_texts`).
"""
import re, collections
from pathlib import Path
from common import ROOT, rows

_KW = {"if", "while", "for", "switch", "return", "sizeof"}
_TYPE_WORDS = {"void", "s32", "u32", "s16", "u16", "u8", "s8", "f32", "int", "char", "short", "long",
               "unsigned", "signed", "struct", "const", "volatile", "typedef", "else", "do", "case"}


def strip_comments(t):
    """Comments blanked, newlines kept."""
    return re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), t, flags=re.S))


def balanced(t, i):
    """t[i] == '(' -> (inner text, index of the matching ')') or None."""
    d = 0
    for j in range(i, len(t)):
        c = t[j]
        if c == "(":
            d += 1
        elif c == ")":
            d -= 1
            if d == 0:
                return t[i + 1:j], j
    return None


def count_args(s):
    s = s.strip()
    if not s:
        return 0
    d = 0; n = 1
    for c in s:
        if c in "([{": d += 1
        elif c in ")]}": d -= 1
        elif c == "," and d == 0: n += 1
    return n


def count_params(s):
    """Declared parameter count of a prototype/definition header; None for K&R `()`."""
    s = s.strip()
    if s == "":
        return None
    if s == "void":
        return 0
    parts = []; cur = ""; d = 0
    for c in s:
        if c in "([": d += 1
        elif c in ")]": d -= 1
        if c == "," and d == 0:
            parts.append(cur); cur = ""
        else:
            cur += c
    parts.append(cur)
    return len([p for p in parts if p.strip() != "..."])


# ---- name resolution (a callee/keyed function is spelled func_X, a true name, or a prefixed hex) ----
_NAMES = None
def _name_tables():
    """(canon: true_name -> func_ name, rev: func_ name -> {true names}, hexnames: HEX -> {names}, name2hex)."""
    global _NAMES
    if _NAMES is None:
        canon = {}; rev = collections.defaultdict(set); hexnames = collections.defaultdict(set)
        for r in rows():
            if r.get("true_name"):
                canon[r["true_name"]] = r["func"]; rev[r["func"]].add(r["true_name"])
        for p, rx in (("config/slus_006.14.symbols.txt", r"\s*(\w+)\s*=\s*0x([0-9a-fA-F]{8})\s*;"),):
            f = ROOT / p
            if f.exists():
                for ln in f.read_text(errors="replace").splitlines():
                    m = re.match(rx, ln)
                    if m: hexnames[m.group(2).upper()].add(m.group(1))
        f = ROOT / "config/names.tsv"
        if f.exists():
            for ln in f.read_text(errors="replace").splitlines():
                p = ln.split("\t")
                if len(p) >= 3 and p[0].startswith("0x"): hexnames[p[0][2:].upper()].add(p[2])
        name2hex = {n: hx for hx, ns in hexnames.items() for n in ns}
        _NAMES = (canon, rev, hexnames, name2hex)
    return _NAMES


def _func_key(name):
    """func_HEX key of a definition name, or None (suffix hex, then names.tsv/symbols, then true_name)."""
    canon, _, _, name2hex = _name_tables()
    m = re.search(r"(?:^|_)([0-9A-F]{8})$", name)
    if m: return "func_" + m.group(1)
    if name in name2hex: return "func_" + name2hex[name]
    if name in canon:
        m = re.search(r"(?:^|_)([0-9A-F]{8})$", canon[name])
        if m: return "func_" + m.group(1)
    return None


def _spellings(code, func):
    """Every name the row text may use for `func` (func_HEX): itself, `asm("func_HEX")` aliases,
    true names, prefixed-hex spellings and the symbol tables' names for that address."""
    canon, rev, hexnames, _ = _name_tables()
    hx = func[5:]
    alias = set()
    for m in re.finditer(r"\b([A-Za-z_]\w*)\s*\([^)]*\)\s*(?:__attribute__\(\([^)]*\)\)\s*)?(?:__asm__|asm)\s*\(\s*\"%s\"\s*\)" % func, code):
        alias.add(m.group(1))
    return sorted({func} | alias | rev.get(func, set()) | set(re.findall(r"\b\w*?_?%s\b" % hx, code)) | hexnames.get(hx, set()))


def key_defined(code, key):
    """True if the row text DEFINES (header followed by `{`) the keyed function under any spelling."""
    for n in _spellings(code, key):
        if re.search(r"(?m)^[ \t]*[A-Za-z_][\w \t\*]*?\b%s[ \t]*\([^;{}]*\)[ \t\r\n]*\{" % re.escape(n), code):
            return True
    return False


# ---- PASSTHRU ----
def calls_of(code, names):
    """Argument counts of every call (declarations and `#` lines excluded) of any of `names`."""
    out = []
    for n in names:
        for m in re.finditer(r"(?<![\w])%s[ \t]*\(" % re.escape(n), code):
            ls = code.rfind("\n", 0, m.start()) + 1
            pre = code[ls:m.start()]
            if pre.lstrip().startswith("#"):
                continue
            b = balanced(code, m.end() - 1)
            if not b:
                continue
            tail = code[b[1] + 1:b[1] + 80].lstrip(); pre = pre.strip()
            is_decl = (bool(re.match(r"^(?:extern\s+|static\s+)?(?!return\b|goto\b|else\b|case\b)[A-Za-z_][\w \t\*]*$", pre))
                       and not re.search(r"[=(,!&|+\-/<>?:]\s*$", pre)
                       and tail.startswith(("{", ";", "__attribute__", "asm", "__asm__")))
            if is_decl and not (pre.endswith("else") or pre.startswith("return")):
                continue
            out.append(count_args(b[0]))
    return out


class DefIndex:
    """{func_HEX: [(container, file stem, declared params or None)]} over the tree's definitions."""
    def __init__(self):
        self.d = collections.defaultdict(list)

    def add_text(self, container, stem, text):
        t = strip_comments(text)
        for m in re.finditer(r"(?m)^[ \t]*(?:static[ \t]+)?[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)[ \t]*\(", t):
            key = _func_key(m.group(1))
            if not key: continue
            b = balanced(t, m.end() - 1)
            if b and t[b[1] + 1:b[1] + 60].lstrip().startswith("{"):
                self.d[key].append((container, stem, count_params(b[0])))

    @classmethod
    def from_texts(cls, items):
        """items: iterable of (container, stem, text) -- for tests."""
        x = cls()
        for c, s, t in items: x.add_text(c, s, t)
        return x

    @classmethod
    def from_tree(cls):
        x = cls()
        for cdir in ("main", "town", "dungeon", "slus"):
            for f in sorted((ROOT / "src" / cdir).glob("*.c")):
                x.add_text(cdir, f.stem, f.read_text(errors="replace"))
        return x

    def callee_params(self, target, container, row_id):
        """Declared parameter counts of the callee's definition(s): SLUS first (overlay nominal
        addresses collide across banks), else same container; the row's own definition is not
        evidence about its callee."""
        defs = [(c, p) for c, s, p in self.d.get(target, ()) if f"{c}/{s}" != row_id]
        chosen = [(c, p) for c, p in defs if c == "slus"] or [(c, p) for c, p in defs if c == container]
        return [p for c, p in chosen if p is not None]


_DEFIDX = None
def default_def_index():
    global _DEFIDX
    if _DEFIDX is None:
        _DEFIDX = DefIndex.from_tree()
    return _DEFIDX


def passthru_arity_short(code, target, container, row_id, defidx=None):
    """True if some call of `target` in `code` passes fewer arguments than the callee's DEFINITION
    declares (census class B).  No definition in the tree, a `(void)` definition, or several
    same-container definitions that disagree where the calls fit the smaller one -> False."""
    calls = calls_of(code, _spellings(code, target))
    if not calls:
        return False
    gd = (defidx or default_def_index()).callee_params(target, container, row_id)
    if not gd:
        return False
    pdef = max(gd)
    if pdef == 0:
        return False
    amin = min(calls)
    if amin >= pdef:
        return False
    if len(set(gd)) > 1 and amin >= min(gd):
        return False
    return True


# ---- INDIRECT_PASSTHRU ----
_VOID_SLOT = [re.compile(r"\(\s*\*+[^)]*\)\s*\(\s*void\s*\)"), re.compile(r"\(\s*\*+\s*\)\s*\(\s*void\s*\)"),
              re.compile(r"\(\*\*\)\s*\(\s*void\s*\)"),
              re.compile(r"typedef\s+\w[\w\s\*]*\(\s*\*\s*\w+\s*\)\s*\(\s*void\s*\)")]
_CAST = re.compile(r"\(\s*(?:const\s+|unsigned\s+|signed\s+|struct\s+)*[A-Za-z_][\w\s]*\**\s*\)")


def indirect_call_arities(t):
    """Argument counts of the indirect calls in comment-stripped `t`: `x->f(..)`/`x.f(..)`, `(*p)(..)`,
    `p(..)` through a name that is not a declared function, `a[i](..)`."""
    out = []
    for m in re.finditer(r"(?:->|\.)\s*([A-Za-z_]\w*)\s*\(", t):
        b = balanced(t, m.end() - 1)
        if b: out.append(count_args(b[0]))
    for m in re.finditer(r"\)\s*\(", t):
        d = 0; k = m.start()
        while k >= 0:
            if t[k] == ")": d += 1
            elif t[k] == "(":
                d -= 1
                if d == 0: break
            k -= 1
        if k < 0: continue
        pre = re.search(r"(\w+)\s*$", t[:k])
        if pre and pre.group(1) in _KW: continue
        if pre and pre.group(1) not in ("FIELD", "M2C_FIELD", "return", "else"): continue   # `T (*name)(..)` is a declaration
        if _CAST.fullmatch(t[k:m.start() + 1]): continue
        b = balanced(t, m.end() - 1)
        if b: out.append(count_args(b[0]))
    fnames = set(re.findall(r"(?m)^[ \t]*(?:extern[ \t]+|static[ \t]+)*[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)[ \t]*\([^;{}]*\)[ \t\r\n]*(?:;|\{)", t))
    for m in re.finditer(r"([A-Za-z_]\w*)\s*\(", t):
        nm = m.group(1)
        if nm in _KW or nm in fnames or nm.startswith(("func_", "w_", "D_", "M2C", "ASM_", "FIELD")) or nm.isupper() or nm in _TYPE_WORDS:
            continue
        pre = t[:m.start()].rstrip()
        if re.search(r"[\w\*]$", pre) and not re.search(r"\b(return|else|case|do)$", pre): continue   # `Type name(` declaration
        b = balanced(t, m.end() - 1)
        if b: out.append(count_args(b[0]))
    for m in re.finditer(r"\]\s*\(", t):
        b = balanced(t, m.end() - 1)
        if b: out.append(count_args(b[0]))
    return out


def indirect_empty_slot_call(code):
    """Census B_empty: every indirect call in the row passes no argument AND no slot is declared
    `(void)`-typed (that spelling may be deliberate).  Mixed rows are left alone."""
    n = indirect_call_arities(code)
    if not n or any(x for x in n):
        return False
    return not any(p.search(code) for p in _VOID_SLOT)
