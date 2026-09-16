#!/usr/bin/env python3
"""The text-level m2c perturbations of the round-33 forward catalogue: a generator's move, REVERSED.

Every kind here takes a PIN-FREE, byte-exact row's text and moves it one step TOWARD the m2c form
that some generator would undo, so the catalogue's diffs read in the same direction as the census's:
`ref` is retail's listing (the exact text's), `cand` is the perturbed text's, the `-` lines are
retail and the `+` lines the m2c-like text.  A fingerprint measured here can therefore be looked up
directly among the pinned sites' (`tools/lanes/residue.py`, `erase_census.py --fp`).

    PERTURBATIONS = [(kind, fn), ...]
    fn(text, detail=None) -> [(params, new_text), ...]

`params` is JSON-serialisable and always carries `site` (the 1-based line of the edited statement or
declaration, in the ORIGINAL text's coordinates) and `label` (one human-readable line), plus the
kind's own parameters.  `detail` is a `collections.Counter` - `Detail` below also keeps the
(refusal, what) pairs - so the population ceiling of each kind can be read text-only, before a single
compile.  Enumeration is deterministic and ordered by site line.

The kinds (generator undone -> the move made here):

  param_copy     t69_prologue     a parameter `p` becomes `p_in`; `T p;` is declared at the top of
                                  the function's declaration block and `p = p_in;` becomes the first
                                  statement.  The body's uses stay `p`.
  decl_reorder   t53 decl-swap    two adjacent declarations of one block exchanged (symmetric).
  width_change   t36 / t37        an integer local or parameter declared one width up, one width
                                  down, or at the other signedness (symmetric).
  adjacent_swap  t51_sched_order  two adjacent simple statements exchanged, `t51.units()/access()/
                                  independent()` - the tests `sched_map.py` applies - allowing it.
  local_alias    natural.dropcopy `x = y;` before a run of statements that read `y`, the run's reads
                                  renamed `x` (m2c's redundant copy).
  page_local     t54 / t59        the D_8XXXXXXX symbols of one 64 KiB page reached through a local
                                  page base: `page = (u8 *)0xXXXX0000;` and
                                  `(*(__typeof__(D_XXXXYYYY) *)(page + 0xYYYY))` at each use.

Hard rules every kind obeys (the contract, and `_no_directive_change` proves the first mechanically):
no preprocessor directive line is ever touched or inserted; no `ASM_*` macro, `__asm__`, `volatile`,
fake dependency, one-trip block, `#pragma` or attribute is ever added; a text that already has a pin
site is refused outright (the catalogue perturbs only pin-free rows); and nothing changes what the
text means beyond the move itself.  A temp whose explicit type is not recoverable from the text is
spelled `__typeof__(expr)` (gcc 2.x accepts it and it is codegen-neutral); such an instance is a
measurement, never a landing.
"""
import collections
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for _p in (str(ROOT / "tools"), str(ROOT / "tools/xform")):
    if _p not in sys.path:
        sys.path.insert(0, _p)
from pin_census import sites_of                                    # noqa: E402
from xform.t12_stmtorder import is_decl as _t12_is_decl            # noqa: E402
from xform import t51_sched_order as T51                           # noqa: E402
from xform.t69_prologue import _mask as mask_text                   # noqa: E402

ID = r"[A-Za-z_]\w*"
CTRL = {"if", "else", "for", "while", "do", "switch", "case", "default", "return", "goto",
        "break", "continue", "sizeof", "typedef", "extern"}
CALL = re.compile(r"\b(?!sizeof\b)" + ID + r"\s*\(")
DEF_RE = re.compile(r"^(?P<head>[A-Za-z_][\w \t\*]*?)\b(?P<name>\w+)[ \t]*"
                    r"\((?P<params>(?:[^;{}()]|\([^()]*\))*)\)\s*\{", re.M)
KNR_RE = re.compile(r"\)[ \t]*\n(?:[ \t]*[A-Za-z_][^;\n]*;[ \t]*\n)+[ \t]*\{")
PARAM_RE = re.compile(r"^(?P<type>(?:(?:unsigned|signed|struct|union|enum|const|volatile)[ \t]+)*"
                      + ID + r"(?:[ \t]*\*)*)[ \t]*(?P<name>" + ID + r")$")
# The base type name MUST be followed by whitespace or a `*`: without that the identifier regex
# backtracks and reads `source_obj = source;` as a declaration of `j` of type `source_ob`
# (which made every assignment a "declaration" - a swap of two assignments would have changed the
# program).  `test_assignment_is_not_a_declaration` holds the line.
# And the type's leading word must not be a CONTROL keyword: `<ident> <ident>;` is also the shape of
# `goto done;` and `return obj;`, so without `_NOT_CTRL` the parser read a jump as a declaration of
# `done` of type `goto` - the round-33 reviewer's root cause (t51's own `declarations()` carries the
# same exclusion).  `test_a_jump_is_not_a_declaration` holds the line.
_NOT_CTRL = r"(?!(?:" + "|".join(sorted(CTRL)) + r")\b)"
_TYPE_TAIL = r"(?:[ \t]+(?:\*[ \t]*)*|[ \t]*(?:\*[ \t]*)+)"
DECL_ONE = re.compile(r"^(?P<ind>[ \t]*)(?P<stor>(?:(?:register|static|const|volatile)[ \t]+)*)"
                      r"(?P<type>(?:(?:unsigned|signed|struct|union|enum|const|volatile)[ \t]+)*"
                      + _NOT_CTRL + ID + _TYPE_TAIL + r")" + _NOT_CTRL + r"(?P<var>" + ID + r")"
                      r"(?P<arr>(?:\[[^\]\n]*\])*)[ \t]*(?:=[ \t]*(?P<init>[^;\n]*?)[ \t]*)?;[ \t]*$")
STORAGE = ("static", "register", "const", "volatile", "extern", "unsigned", "signed",
           "struct", "union", "enum", "typedef")
DECL_HEAD = re.compile(r"^[ \t]*(?:(?:" + "|".join(STORAGE) + r")[ \t]+)*"
                       + _NOT_CTRL + ID + _TYPE_TAIL + _NOT_CTRL + ID)
PAGE_SYM = re.compile(r"(?<![\w.])D_(?P<hex>8[0-9A-Fa-f]{7})\b")
SIDE_EFFECT = re.compile(r"\+\+|--|(?<![=!<>+\-*/%&|^])=(?!=)")
MAX_ALIAS_PER_FN = 4

# One canonical spelling per integer width, and every spelling that reaches it.
WIDTHS = {"u8": (0, 8), "s8": (1, 8), "u16": (0, 16), "s16": (1, 16), "u32": (0, 32), "s32": (1, 32)}
SPELLINGS = {"u8": "u8", "s8": "s8", "u16": "u16", "s16": "s16", "u32": "u32", "s32": "s32",
             "unsigned char": "u8", "signed char": "s8", "char": "s8",
             "short": "s16", "short int": "s16", "signed short": "s16", "signed short int": "s16",
             "unsigned short": "u16", "unsigned short int": "u16",
             "int": "s32", "signed": "s32", "signed int": "s32",
             "unsigned": "u32", "unsigned int": "u32",
             "M2C_UNK8": "u8", "M2C_UNK16": "u16", "M2C_UNK32": "u32"}
WIDE64 = ("long long", "u64", "s64", "double", "f64")
CANON = {(0, 8): "u8", (1, 8): "s8", (0, 16): "u16", (1, 16): "s16", (0, 32): "u32", (1, 32): "s32"}
# Many rows are self-contained: they carry their own `typedef`s and define only the widths they use
# (`dungeon/func_800933D8` has u8/s16/s32/u32 and no `s8`).  Writing `s8` there is a syntax error, so
# a width the text does not know is spelled in plain C, which always compiles.
C_SPELLING = {"u8": "unsigned char", "s8": "signed char", "u16": "unsigned short",
              "s16": "short", "u32": "unsigned int", "s32": "int"}
INCLUDE_RE = re.compile(r"^[ \t]*#[ \t]*include\b", re.M)


def _type_spellings(text):
    """The spelling each canonical width must be written with in THIS text."""
    if INCLUDE_RE.search(text):
        return {k: k for k in CANON.values()}          # a project header brings all six
    out = {}
    for name in C_SPELLING:
        known = re.search(r"^[ \t]*typedef\b[^;\n]*\b%s[ \t]*;" % name, text, re.M)
        out[name] = name if known else C_SPELLING[name]
    return out


class Detail(collections.Counter):
    """A refusal counter that also keeps (refusal, what) pairs - t69_prologue.Detail's contract."""

    def __init__(self, *a, **k):
        super().__init__(*a, **k)
        self.detail = []


def _note(detail, key, what=None):
    if detail is None:
        return
    detail[key] += 1
    d = getattr(detail, "detail", None)
    if d is not None:
        d.append((key, what))


# --------------------------------------------------------------------------- text scaffolding

class Ctx:
    """The line view every kind works on: masked lines, brace depth, directive flags, functions."""

    def __init__(self, text):
        self.text = text
        self.lines = text.splitlines(True)
        self.m = mask_text(text).splitlines(True)
        while len(self.m) < len(self.lines):
            self.m.append("")
        self.depth = []
        d = 0
        for ln in self.m:
            self.depth.append(d)
            d += ln.count("{") - ln.count("}")
        self.direct = []
        cont = False
        for ln in self.m:
            isd = cont or ln.lstrip().startswith("#")
            self.direct.append(isd)
            cont = isd and ln.rstrip("\n").endswith("\\")
        # How deep in `#if` / `#else` arms each line sits: a function inside one is compiled only in
        # some configuration, so perturbing it measures nothing (the `#else` arm of a NON_MATCHING
        # row is not compiled at all, and every instance in it would read as a spurious INVISIBLE).
        self.ppdepth = []
        d = 0
        for ln in self.m:
            m = re.match(r"[ \t]*#[ \t]*(if|ifdef|ifndef|else|elif|endif)\b", ln)
            if m and m.group(1) == "endif":
                d = max(0, d - 1)
            self.ppdepth.append(d)
            if m and m.group(1) in ("if", "ifdef", "ifndef"):
                d += 1
        self.fns = _functions(self)

    def code(self, i):
        """The masked line `i`, stripped of its newline."""
        return self.m[i].rstrip("\n") if 0 <= i < len(self.m) else ""

    def prev_code(self, i):
        """The previous line that carries code (blank, comment-only and directive lines skipped)."""
        j = i - 1
        while j >= 0 and (not self.m[j].strip() or self.direct[j]):
            j -= 1
        return self.code(j).strip() if j >= 0 else ""

    def dangling(self, i):
        """True when line `i` is the brace-less body of the control line above it."""
        p = self.prev_code(i)
        if p in ("else", "do") or p.endswith("else") or re.fullmatch(r"\}?\s*else", p):
            return True
        return bool(re.match(r"^(?:if|for|while|switch)\s*\(", p) and p.endswith(")"))

    def stmt_start(self, i):
        """True when line `i` begins a statement (not the continuation of a multi-line one)."""
        p = self.prev_code(i)
        return p == "" or p[-1:] in ";{}:" or self.dangling(i)

    def simple(self, i):
        """A one-line statement that may be moved: t12's `movable`, and a real statement start."""
        s = self.code(i).strip()
        if not s or self.direct[i] or "{" in s or "}" in s or not s.endswith(";"):
            return False
        if re.match(r"^" + ID + r"\s*:", s) and not s.startswith("case"):
            return False
        head = re.match(r"^(" + ID + r")", s)
        if head and head.group(1) in CTRL:
            return False
        return self.stmt_start(i)

    def is_decl(self, i):
        s = self.code(i).strip()
        if not s.endswith(";") or self.direct[i]:
            return False
        return bool(DECL_ONE.match(self.code(i))) or _t12_is_decl(self.code(i))


def _functions(ctx):
    """Every definition of the text: name, parameters (parsed or refused) and its body's line span."""
    masked = "".join(ctx.m)
    starts, pos = [], 0
    for ln in ctx.m:
        starts.append(pos)
        pos += len(ln)

    def line_of(off):
        lo, hi = 0, len(starts) - 1
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if starts[mid] <= off:
                lo = mid
            else:
                hi = mid - 1
        return lo

    out = []
    for m in DEF_RE.finditer(masked):
        if m.group("name") in CTRL:
            continue
        i, d = m.end() - 1, 0
        while i < len(masked):
            d += (masked[i] == "{") - (masked[i] == "}")
            if d == 0:
                break
            i += 1
        b0, b1 = line_of(m.end() - 1), line_of(min(i, len(masked) - 1))
        if b1 <= b0:
            continue
        params, bad, base = [], [], m.start("params")
        for part, off in _split_params(m.group("params")):
            raw = part.strip()
            if not raw or raw == "void":
                continue
            a = base + off + (len(part) - len(part.lstrip()))
            if raw == "...":
                bad.append(("varargs", raw))
            elif "[" in raw:
                bad.append(("array-parameter", raw))
            elif re.search(r"\(\s*\*", raw):
                bad.append(("function-pointer-parameter", raw))
            elif re.fullmatch(ID, raw):
                bad.append(("k-and-r-signature", raw))
            else:
                pm = PARAM_RE.match(raw)
                if not pm:
                    bad.append(("parameter-not-parsed", raw))
                    continue
                ty = pm.group("type").strip()
                ns = a + pm.start("name")
                params.append(dict(name=pm.group("name"), type=ty, start=ns,
                                   end=ns + len(pm.group("name")),
                                   tstart=a + pm.start("type"), tend=a + len(ty),
                                   line=line_of(ns), tline=line_of(a + pm.start("type"))))
        pp = any(ctx.direct[k] for k in range(b0, b1 + 1))
        out.append(dict(name=m.group("name"), params=params, bad=bad, b0=b0, b1=b1,
                        sig_line=line_of(m.start()), pp=pp, cond=ctx.ppdepth[b0] > 0,
                        start=m.start(), end=i))
    return out


def _skip_fn(fn, detail):
    """The two function-level refusals every kind shares: a directive inside the body, and a body
    that sits inside a `#if` arm (compiled only in some configuration - `town/func_8051EDA4`'s
    `#else` arm is never compiled, so every instance in it would read as a spurious INVISIBLE)."""
    if fn["pp"]:
        _note(detail, "preprocessor-in-body", fn["name"])
        return True
    if fn["cond"]:
        _note(detail, "conditionally-compiled-function", fn["name"])
        return True
    return False


def _split_params(s):
    """Top-level comma split of a parameter list, each part with its offset in `s`."""
    out, depth, last = [], 0, 0
    for i, c in enumerate(s):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "," and depth == 0:
            out.append((s[last:i], last))
            last = i + 1
    out.append((s[last:], last))
    return out


def _fn_body_names(ctx, fn):
    return set(re.findall(ID, "".join(ctx.m[fn["b0"]:fn["b1"] + 1])))


def _writes(masked, v):
    V = re.escape(v)
    return (len(re.findall(r"(?<![\w.>])%s\s*(?:=(?!=)|\+\+|--|[-+*/%%&|^]=|<<=|>>=)" % V, masked))
            + len(re.findall(r"(?:\+\+|--)\s*(?<![\w.>])%s\b" % V, masked)))


def _reads(masked, v):
    return len(list(_occ(masked, v)))


def _occ(masked, name):
    """Spans of `name` used as an identifier - never a `.`/`->` member of that name."""
    for m in re.finditer(r"(?<![\w.])%s\b" % re.escape(name), masked):
        back = masked[max(0, m.start() - 8):m.start()].rstrip()
        if back.endswith(("->", ".")):
            continue
        yield m.start(), m.end()


def _rename_in_line(line, masked_line, old, new):
    """`old` renamed `new` on one physical line, using the masked line to place the occurrences."""
    out, last = [], 0
    for a, b in _occ(masked_line, old):
        out.append(line[last:a])
        out.append(new)
        last = b
    out.append(line[last:])
    return "".join(out)


def _directive_lines(text):
    out, cont = [], False
    for ln in text.splitlines():
        isd = cont or ln.lstrip().startswith("#")
        if isd:
            out.append(ln)
        cont = isd and ln.rstrip().endswith("\\")
    return out


def _no_directive_change(text, new_text):
    """The contract's directive rule, checked mechanically on every emitted instance."""
    return _directive_lines(text) == _directive_lines(new_text)


def _emit(out, detail, kind, params, text, new_text):
    """One instance, after the guards every kind shares."""
    if new_text == text:
        _note(detail, "no-op-edit", params.get("label"))
        return
    if not _no_directive_change(text, new_text):
        _note(detail, "would-touch-directive", params.get("label"))
        return
    if sites_of(new_text):
        _note(detail, "would-create-pin-site", params.get("label"))
        return
    params = dict(params)
    params["kind"] = kind
    out.append((params, new_text))


def _guard(text, detail, kind):
    """The population rule: the catalogue perturbs pin-free rows only."""
    if sites_of(text):
        _note(detail, "text-has-pins", kind)
        return False
    return True


def _declarative(ctx, i):
    """True when line `i` starts a DECLARATION of any shape - including the multi-line ones
    (`static void *const table[] = {`) a statement may never be inserted in front of."""
    s = ctx.code(i).strip()
    if not s or ctx.direct[i]:
        return False
    head = re.match(r"^(" + ID + r")", s)
    if head and head.group(1) in CTRL:
        return False
    if head and head.group(1) in STORAGE:
        return True
    return bool(DECL_HEAD.match(ctx.code(i))) and not re.match(r"^[ \t]*" + ID + r"[ \t]*\(", ctx.code(i))


def _decl_run_end(ctx, fn):
    """The line after the function's leading declaration block (where the first statement sits),
    or None when that block is not a plain run of one-line declarations."""
    i = fn["b0"] + 1
    last = i
    while i < fn["b1"]:
        s = ctx.code(i).strip()
        if ctx.direct[i]:
            return None
        if not s:
            i += 1
            continue
        if ctx.depth[i] == ctx.depth[fn["b0"]] + 1 and ctx.is_decl(i) and "{" not in s and "}" not in s:
            i += 1
            last = i
            continue
        break
    if i < fn["b1"] and _declarative(ctx, i):
        return None                     # a declaration the run parser could not consume
    return last


def _indent(ctx, fn):
    for i in range(fn["b0"] + 1, fn["b1"]):
        if ctx.code(i).strip():
            return re.match(r"[ \t]*", ctx.lines[i]).group(0) or "    "
    return "    "


# --------------------------------------------------------------------------- param_copy

def param_copy(text, detail=None):
    """t69_prologue reversed: m2c's entry copy of a parameter into a local of the body's name.

    `void f(u8 *tile)` with `tile` used in the body becomes `void f(u8 *tile_in)` plus
    `u8 *tile;` at the top of the declaration block and `tile = tile_in;` as the first statement.
    `site` is the line the copy statement is inserted at, in the original text's coordinates.
    """
    if not _guard(text, detail, "param_copy"):
        return []
    ctx = Ctx(text)
    for _ in KNR_RE.finditer("".join(ctx.m)):
        _note(detail, "k-and-r-signature", None)
    out = []
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        for why, what in fn["bad"]:
            _note(detail, why, "%s:%s" % (fn["name"], what))
        if not fn["params"]:
            _note(detail, "no-parameters", fn["name"])
            continue
        at = _decl_run_end(ctx, fn)
        if at is None:
            _note(detail, "declaration-block-not-simple", fn["name"])
            continue
        names = _fn_body_names(ctx, fn) | set(re.findall(ID, text))
        body = "".join(ctx.m[fn["b0"]:fn["b1"] + 1])
        decls = "".join(ctx.m[fn["b0"] + 1:at])
        ind = _indent(ctx, fn)
        for p in fn["params"]:
            ty = p["type"]
            if ("struct" in ty or "union" in ty) and "*" not in ty:
                _note(detail, "struct-by-value-parameter", "%s:%s" % (fn["name"], p["name"]))
                continue
            new = p["name"] + "_in"
            if new in names:
                _note(detail, "name-collides", "%s:%s" % (fn["name"], new))
                continue
            if not _reads("".join(ctx.m[fn["b0"] + 1:fn["b1"]]), p["name"]):
                _note(detail, "parameter-never-read", "%s:%s" % (fn["name"], p["name"]))
                continue
            if _reads(decls, p["name"]):
                # the copy lands after the declarations, so a declaration initialiser that reads the
                # parameter would read the local before it is set
                _note(detail, "read-in-declaration-initialiser", "%s:%s" % (fn["name"], p["name"]))
                continue
            lines = list(ctx.lines)
            sig = lines[p["line"]]
            col = p["start"] - sum(len(x) for x in ctx.m[:p["line"]])
            lines[p["line"]] = sig[:col] + new + sig[col + len(p["name"]):]
            sep = "" if ty.endswith("*") else " "
            lines.insert(at, "%s%s = %s;\n" % (ind, p["name"], new))
            lines.insert(fn["b0"] + 1, "%s%s%s%s;\n" % (ind, ty, sep, p["name"]))
            _emit(out, detail, "param_copy",
                  dict(site=at + 1, label="param_copy %s: %s -> %s (local %s%s%s)"
                       % (fn["name"], p["name"], new, ty, sep, p["name"]),
                       fn=fn["name"], param=p["name"], new_param=new, type=ty,
                       decl_line=fn["b0"] + 2),
                  text, "".join(lines))
    out.sort(key=lambda z: z[0]["site"])
    return out


# --------------------------------------------------------------------------- decl_reorder

def decl_reorder(text, detail=None):
    """t53's decl-swap, symmetric: two adjacent declaration lines of one block exchanged."""
    if not _guard(text, detail, "decl_reorder"):
        return []
    ctx = Ctx(text)
    out = []
    inside = [False] * len(ctx.lines)
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        for i in range(fn["b0"] + 1, fn["b1"]):
            inside[i] = True
    for i in range(len(ctx.lines) - 1):
        if not inside[i] or not inside[i + 1]:
            continue
        if ctx.direct[i] or ctx.direct[i + 1]:
            continue
        if not (ctx.is_decl(i) and ctx.is_decl(i + 1)):
            continue
        if ctx.depth[i] != ctx.depth[i + 1]:
            _note(detail, "depth-differs", str(i + 1))
            continue
        if ctx.dangling(i) or ctx.dangling(i + 1):
            # a brace-less `if (c)` body: the first line IS the body, so a swap moves the body out
            # of the arm.  A declaration can never legally be one, but the guard is cheap and it is
            # what stops a mis-parse from landing a swap inside an arm.
            _note(detail, "brace-less-control-body", ctx.code(i).strip()[:40])
            continue
        if "," in ctx.code(i) or "," in ctx.code(i + 1):
            _note(detail, "multi-declarator", ctx.code(i).strip()[:40])
            continue
        a, b = DECL_ONE.match(ctx.code(i)), DECL_ONE.match(ctx.code(i + 1))
        if not a or not b:
            _note(detail, "declaration-not-parsed", ctx.code(i).strip()[:40])
            continue
        bad = False
        for d in (a, b):
            if d.group("init") and (CALL.search(d.group("init")) or SIDE_EFFECT.search(d.group("init"))):
                _note(detail, "initialiser-has-side-effect", d.group("init")[:40])
                bad = True
        if bad:
            continue
        if b.group("init") and re.search(r"(?<![\w.])%s\b" % re.escape(a.group("var")), b.group("init")):
            _note(detail, "second-reads-first", "%s/%s" % (a.group("var"), b.group("var")))
            continue
        lines = list(ctx.lines)
        first, second = lines[i], lines[i + 1]
        if not first.endswith("\n"):
            _note(detail, "declaration-spans-lines", str(i + 1))
            continue
        lines[i], lines[i + 1] = second if second.endswith("\n") else second + "\n", first
        _emit(out, detail, "decl_reorder",
              dict(site=i + 1, label="decl_reorder: %s <-> %s"
                   % (a.group("var"), b.group("var")),
                   first=a.group("var"), second=b.group("var"),
                   first_type=a.group("type").strip(), second_type=b.group("type").strip()),
              text, "".join(lines))
    out.sort(key=lambda z: z[0]["site"])
    return out


# --------------------------------------------------------------------------- width_change

def _canon_type(ty):
    t = re.sub(r"\s+", " ", ty.strip())
    t = re.sub(r"^(?:const|volatile|register)\s+", "", t)
    return SPELLINGS.get(t)


def width_change(text, detail=None):
    """t36/t37, symmetric: an integer local or parameter declared at another width or signedness."""
    if not _guard(text, detail, "width_change"):
        return []
    ctx = Ctx(text)
    out = []
    spell = _type_spellings(text)
    protos = set()
    for m in re.finditer(r"^[A-Za-z_][\w \t\*]*?\b(" + ID + r")[ \t]*\([^;{}]*\)[ \t]*;", "".join(ctx.m), re.M):
        protos.add(m.group(1))
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        body = "".join(ctx.m[fn["b0"]:fn["b1"] + 1])
        targets = []
        if fn["params"] and fn["name"] in protos:
            _note(detail, "prototype-in-file", fn["name"])
        for p in ([] if fn["name"] in protos else fn["params"]):
            targets.append(("param", p["name"], p["type"], p["tline"],
                            p["tstart"] - sum(len(x) for x in ctx.m[:p["tline"]]), len(p["type"])))
        for i in range(fn["b0"] + 1, fn["b1"]):
            if ctx.direct[i] or not ctx.is_decl(i):
                continue
            d = DECL_ONE.match(ctx.code(i))
            if not d:
                continue
            if "," in ctx.code(i):
                _note(detail, "multi-declarator", ctx.code(i).strip()[:40])
                continue
            if d.group("arr"):
                _note(detail, "array", d.group("var"))
                continue
            targets.append(("local", d.group("var"), d.group("type").strip(), i,
                            d.start("type"), len(d.group("type").rstrip())))
        for what, var, ty, line, col, tlen in targets:
            if "*" in ty:
                _note(detail, "pointer", var)
                continue
            if any(w in ty for w in WIDE64):
                _note(detail, "64-bit-type", ty)
                continue
            if re.search(r"(?<![\w.])%s\b[^;\n]*:" % re.escape(var), ctx.code(line)):
                _note(detail, "bit-field", var)
                continue
            if re.search(r"&\s*(?<![\w.])%s\b" % re.escape(var), body):
                _note(detail, "address-taken", var)
                continue
            can = _canon_type(ty)
            if can is None:
                _note(detail, "not-an-integer-type", ty)
                continue
            sign, width = WIDTHS[can]
            moves = [("up", (sign, width * 2)), ("down", (sign, width // 2)),
                     ("sign", (1 - sign, width))]
            for name, key in moves:
                if key not in CANON:
                    _note(detail, "no-" + ("wider" if name == "up" else "narrower"), can)
                    continue
                to = spell[CANON[key]]
                if to == ty.strip() or CANON[key] == can:
                    continue
                lines = list(ctx.lines)
                src = lines[line]
                if src[col:col + tlen].strip() != ty.strip():
                    _note(detail, "type-span-mismatch", "%s:%s" % (fn["name"], var))
                    continue
                lines[line] = src[:col] + to + src[col + tlen:]
                _emit(out, detail, "width_change",
                      dict(site=line + 1,
                           label="width_change %s %s %s: %s -> %s (%s)"
                                 % (fn["name"], what, var, ty, to, name),
                           fn=fn["name"], var=var, what=what, move=name,
                           canon=CANON[key], **{"from": ty, "to": to}),
                      text, "".join(lines))
    out.sort(key=lambda z: (z[0]["site"], z[0]["move"]))
    return out


# --------------------------------------------------------------------------- adjacent_swap

# A real memory operator: `->`, an index, a `.` member of something, or a UNARY `*` - a star that
# follows the statement's start or an operator (so `p * q` is multiplication and `(S *)p` a cast).
MEM_OP = re.compile(r"->|\[|(?<=[\w)\]])\.(?!\d)"
                    r"|(?:^|[-=+*/%&|^<>!?:,;(\[{])[ \t]*\*[ \t]*(?!\**[ \t]*\))")


MEM_ANY = object()          # "an unnamed memory location": a global store, which anything may alias
# Every declarator of a declaration line, so that `s32 a, b;` and `void (*cb)(void);` count as
# locals too: `DECL_ONE` alone sees only the single-declarator scalar form, and a name missing from
# the local set makes a store to it read as a GLOBAL store (an over-refusal, not a wrong instance).
_DECLARATOR = re.compile(r"(?<![\w.])(" + ID + r")[ \t]*(?:\[[^\]\n]*\])*[ \t]*(?=[,;=)]|[ \t]*$)")


def _decl_vars(masked_line):
    """The names a declaration line declares (its declarator part, before any initialiser)."""
    head = masked_line.split("=")[0]
    return [m.group(1) for m in _DECLARATOR.finditer(head)]


def _mem_ids(masked, locals_=None):
    """(memory-written identifiers, memory-read identifiers) of one masked statement.

    `t51.access()` calls `x = <memory>;` a NON-memory statement - its `ma` flag is False whenever the
    LHS is a plain identifier - so `t51.independent()` reports a store/load pair on the SAME lvalue
    (`a[0] = 1;` / `x = a[0];`) as independent.  That is safe inside t51, whose every candidate is
    proved by the gate, but a catalogue instance is never gated: it would enter as a "two independent
    statements exchanged" record while actually changing the program (the round-33 reviewer's
    BLOCKING 3).  This adds the alias test t51 leaves to the gate, at base-identifier granularity:
    a statement's memory-touching side contributes all of its identifiers.

    `locals_` (the function's parameters and declared locals) closes the second half of the same
    modelling gap: a plain-identifier assignment to a name that is NOT a local is a store to a
    GLOBAL - memory, which an unrelated dereference on the other side may alias
    (`D_800814AC = delta;` beside `((Gfx *)0x80010000)->shade = c;`).  It contributes `MEM_ANY`,
    which every dereference collides with.  Without `locals_` that half is not tested.
    """
    m = T51.ASSIGN.match(masked)
    if not m:
        if not MEM_OP.search(masked):
            return set(), set()
        ids = set(re.findall(ID, masked)) | {MEM_ANY}
        return ids, ids
    lhs, rhs = m["lhs"].strip(), m["rhs"]
    plain = re.fullmatch(ID, lhs)
    w = set() if plain else set(re.findall(ID, lhs))
    r = set(re.findall(ID, rhs)) if MEM_OP.search(rhs) else set()
    if w and MEM_OP.search(lhs):
        r |= w                                    # an indexed store also READS its index operands
    if plain and locals_ is not None and lhs not in locals_:
        w.add(MEM_ANY)                            # a store to a global: unnamed memory
    if MEM_OP.search(masked):
        r.add(MEM_ANY)                            # a dereference: may reach any global
    return w, r


def _mem_independent(a, b, locals_=None):
    """No memory base an lvalue of one writes is touched by the other."""
    wa, ra = _mem_ids(a, locals_)
    wb, rb = _mem_ids(b, locals_)
    return not (wa & (rb | wb) or wb & (ra | wa))


def adjacent_swap(text, detail=None):
    """t51_sched_order reversed-and-forward (the move is symmetric): two adjacent independent simple
    statements exchanged.  The gate is t51's own - `units()` for the statement records, `access()` /
    `independent()` for the dependency - the same tests `tools/lanes/sched_map.py` applies."""
    if not _guard(text, detail, "adjacent_swap"):
        return []
    ctx = Ctx(text)
    lines51, recs = T51.units(text)
    by = {r["line"]: r for r in recs}
    out = []
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        locs = {p["name"] for p in fn["params"]}       # a store to anything else is a GLOBAL store
        for i in range(fn["b0"] + 1, fn["b1"]):
            if not ctx.direct[i] and ctx.is_decl(i):
                locs.update(_decl_vars(ctx.code(i)))
        for i in range(fn["b0"] + 1, fn["b1"] - 1):
            j = i + 1
            ra, rb = by.get(i), by.get(j)
            if ra is None or rb is None:
                continue
            if not (ra["simple"] and rb["simple"]):
                _note(detail, "control-or-not-simple", ctx.code(i).strip()[:40])
                continue
            if ra["decl"] or rb["decl"]:
                _note(detail, "declaration", ctx.code(i).strip()[:40])
                continue
            if not (ctx.simple(i) and ctx.simple(j)):
                _note(detail, "multi-line-statement", ctx.code(i).strip()[:40])
                continue
            if ra["depth"] != rb["depth"]:
                _note(detail, "depth-differs", ctx.code(i).strip()[:40])
                continue
            if ra["arm"] != rb["arm"]:
                _note(detail, "arm-differs", ctx.code(i).strip()[:40])
                continue
            if ctx.dangling(i) or ctx.dangling(j):
                _note(detail, "brace-less-control-body", ctx.code(i).strip()[:40])
                continue
            if CALL.search(ra["masked"]) or CALL.search(rb["masked"]):
                _note(detail, "call", ctx.code(i).strip()[:40])
                continue
            if not T51.independent(ra["masked"], rb["masked"]):
                wa, _, ma = T51.access(ra["masked"])
                wb, rb2, mb = T51.access(rb["masked"])
                _note(detail, "dep-mem" if (ma and mb) and not (wa & (rb2 | wb)) else "dep-data",
                      ctx.code(i).strip()[:40])
                continue
            if not _mem_independent(ra["masked"], rb["masked"], locs):
                _note(detail, "dep-mem-alias", ctx.code(i).strip()[:40])
                continue
            lines = list(ctx.lines)
            first, second = lines[i], lines[j]
            if not first.endswith("\n"):
                continue
            lines[i], lines[j] = (second if second.endswith("\n") else second + "\n"), first
            _emit(out, detail, "adjacent_swap",
                  dict(site=i + 1, label="adjacent_swap %s: %s <-> %s"
                       % (fn["name"], ctx.code(i).strip()[:30], ctx.code(j).strip()[:30]),
                       fn=fn["name"], first=ctx.code(i).strip()[:60], second=ctx.code(j).strip()[:60]),
                  text, "".join(lines))
    out.sort(key=lambda z: z[0]["site"])
    return out


# --------------------------------------------------------------------------- local_alias

def _declared_type(ctx, fn, v):
    for p in fn["params"]:
        if p["name"] == v:
            return p["type"]
    for i in range(fn["b0"] + 1, fn["b1"]):
        if ctx.direct[i] or not ctx.is_decl(i) or "," in ctx.code(i):
            continue
        d = DECL_ONE.match(ctx.code(i))
        if d and d.group("var") == v and not d.group("arr"):
            return d.group("type").strip()
    return None


def _block_open_line(ctx, fn, i):
    """The line carrying the `{` of the innermost block containing line `i`.

    A line-depth scan is not enough: before `} else {` the then-block is still open, so comparing
    line depths walks past the `else` and lands on the `if`'s brace - the declaration then goes into
    the WRONG arm (two rows built `S *x;` in the then-arm and used it in the else-arm).  This counts
    braces backwards instead.
    """
    bal = 0
    for j in range(i - 1, fn["b0"] - 1, -1):
        if ctx.direct[j]:
            continue
        for c in reversed(ctx.code(j)):
            if c == "}":
                bal += 1
            elif c == "{":
                if bal == 0:
                    return j
                bal -= 1
    return fn["b0"]


def _straight_blocks(ctx, fn):
    """The maximal straight runs of simple statements at one depth: a run has no control line, no
    label, no declaration and no brace in it, so a copy inserted at its head reaches every line."""
    blocks, cur = [], []
    for i in range(fn["b0"] + 1, fn["b1"]):
        s = ctx.code(i).strip()
        if not s:
            continue
        broke = (ctx.direct[i] or not ctx.simple(i) or ctx.is_decl(i) or ctx.dangling(i)
                 or (cur and ctx.depth[i] != ctx.depth[cur[0]]))
        if broke:
            if len(cur) >= 2:
                blocks.append(cur)
            cur = []
            if not (ctx.direct[i] or not ctx.simple(i) or ctx.is_decl(i) or ctx.dangling(i)):
                cur = [i]
            continue
        cur.append(i)
    if len(cur) >= 2:
        blocks.append(cur)
    return blocks


def local_alias(text, detail=None):
    """natural.dropcopy reversed: m2c's redundant `x = y;` in front of a run that reads `y`.

    A local or parameter `y` read at least twice inside one straight run of two or more consecutive
    simple statements, written nowhere in that run and never address-taken, gets a fresh local of its
    declared type: the copy is inserted before the run's first read and every read of `y` from there
    to its last read in the run is renamed.  The alias therefore spans whatever sits between them -
    calls included - which is where an m2c copy is not a plain coalescable move.  One instance per
    (run, variable); the four with the longest span are kept, emitted in site order.
    """
    if not _guard(text, detail, "local_alias"):
        return []
    ctx = Ctx(text)
    out = []
    allnames = set(re.findall(ID, text))
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        body = "".join(ctx.m[fn["b0"]:fn["b1"] + 1])
        cands = [p["name"] for p in fn["params"]]
        for i in range(fn["b0"] + 1, fn["b1"]):
            if ctx.direct[i] or not ctx.is_decl(i) or "," in ctx.code(i):
                continue
            d = DECL_ONE.match(ctx.code(i))
            if d and not d.group("arr"):
                cands.append(d.group("var"))
        blocks = _straight_blocks(ctx, fn)
        if not blocks:
            _note(detail, "no-straight-run-of-two", fn["name"])
            continue
        runs = []
        for v in sorted(set(cands)):
            if re.search(r"&\s*(?<![\w.])%s\b" % re.escape(v), body):
                _note(detail, "address-taken", "%s:%s" % (fn["name"], v))
                continue
            for blk in blocks:
                # a write of `v` ends the alias's run: the copy would then hold a stale value, so
                # each write-free segment of the run is considered on its own
                seg, segs = [], []
                for i in blk:
                    if _writes(ctx.code(i), v):
                        _note(detail, "written-in-run", "%s:%s" % (fn["name"], v))
                        segs.append(seg)
                        seg = []
                        continue
                    seg.append(i)
                segs.append(seg)
                for s in segs:
                    if len(s) < 2:
                        continue
                    reads = [i for i in s if _reads(ctx.code(i), v)]
                    if len(reads) < 2:
                        continue
                    span = [i for i in s if reads[0] <= i <= reads[-1]]
                    runs.append((len(span), span, v))
        if not runs:
            _note(detail, "no-run-with-two-reads", fn["name"])
            continue
        runs.sort(key=lambda r: (-r[0], r[1][0], r[2]))
        chosen = sorted(runs[:MAX_ALIAS_PER_FN], key=lambda r: (r[1][0], r[2]))
        for extra in runs[MAX_ALIAS_PER_FN:]:
            _note(detail, "over-four-runs", "%s:%s" % (fn["name"], extra[2]))
        for n, span, v in chosen:
            a = span[0]
            ty = _declared_type(ctx, fn, v)
            spelled = ty if ty else "__typeof__(%s)" % v
            name = v + "_alias"
            k = 2
            while name in allnames:
                name = "%s_alias%d" % (v, k)
                k += 1
            blk0 = _block_open_line(ctx, fn, a)
            at = blk0 + 1
            while at < a:
                s = ctx.code(at).strip()
                if ctx.direct[at]:
                    break
                if not s:
                    at += 1
                    continue
                if ctx.is_decl(at) and "{" not in s and "}" not in s:
                    at += 1
                    continue
                break
            if at > a or (at < len(ctx.lines) and ctx.direct[at]):
                _note(detail, "declaration-slot-below-run", "%s:%s" % (fn["name"], v))
                continue
            if at < a and _declarative(ctx, at):
                _note(detail, "declaration-block-not-simple", "%s:%s" % (fn["name"], v))
                continue
            ind = re.match(r"[ \t]*", ctx.lines[a]).group(0)
            dind = re.match(r"[ \t]*", ctx.lines[at] if ctx.lines[at].strip() else ctx.lines[a]).group(0)
            lines = list(ctx.lines)
            for k2 in span:
                lines[k2] = _rename_in_line(lines[k2], ctx.m[k2], v, name)
            lines.insert(a, "%s%s = %s;\n" % (ind, name, v))
            sep = "" if spelled.endswith("*") else " "
            lines.insert(at, "%s%s%s%s;\n" % (dind, spelled, sep, name))
            _emit(out, detail, "local_alias",
                  dict(site=a + 1, label="local_alias %s: %s = %s over %d statements"
                       % (fn["name"], name, v, n),
                       fn=fn["name"], var=v, alias=name, run=n, type=spelled,
                       typed="explicit" if ty else "typeof"),
                  text, "".join(lines))
    out.sort(key=lambda z: z[0]["site"])
    return out


# --------------------------------------------------------------------------- page_local

def page_local(text, detail=None):
    """t54_pagebase / t59_offsetsym reversed: one 64 KiB page's symbols reached through a local base.

    Every use of `D_XXXXYYYY` whose upper half is the page becomes
    `(*(__typeof__(D_XXXXYYYY) *)(page + 0xYYYY))`, with `u8 *page;` declared and
    `page = (u8 *)0xXXXX0000;` as the first statement.  One instance per page of a function.
    """
    if not _guard(text, detail, "page_local"):
        return []
    ctx = Ctx(text)
    out = []
    arrays = set()
    for m in re.finditer(r"(?<![\w.])D_(8[0-9A-Fa-f]{7})\b[ \t]*(\[|\()", "".join(ctx.m)):
        arrays.add("D_" + m.group(1))
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        names = _fn_body_names(ctx, fn) | {p["name"] for p in fn["params"]}
        if "page" in names or re.search(r"(?<![\w.])page\b", "".join(ctx.m)):
            _note(detail, "page-name-in-use", fn["name"])
            continue
        at = _decl_run_end(ctx, fn)
        if at is None:
            _note(detail, "declaration-block-not-simple", fn["name"])
            continue
        uses = collections.defaultdict(list)          # page -> [(line, start, end, symbol)]
        for i in range(fn["b0"] + 1, fn["b1"]):
            if ctx.direct[i]:
                continue
            for m in PAGE_SYM.finditer(ctx.code(i)):
                sym, hx = m.group(0), m.group("hex")
                tail = ctx.code(i)[m.end():m.end() + 2]
                head = ctx.code(i)[:m.start()].rstrip()
                if sym in arrays or tail.lstrip()[:1] in ("[", "("):
                    _note(detail, "symbol-used-as-array-or-function", sym)
                    continue
                if head.endswith("&"):
                    _note(detail, "address-of-symbol", sym)
                    continue
                uses[hx[:4].upper()].append((i, m.start(), m.end(), sym))
        if not uses:
            _note(detail, "no-page-symbols", fn["name"])
            continue
        ind = _indent(ctx, fn)
        for page in sorted(uses):
            us = uses[page]
            if len(us) < 2:
                _note(detail, "single-use-page", "%s:%s" % (fn["name"], page))
                continue
            lines = list(ctx.lines)
            for i, a, b, sym in sorted(us, key=lambda u: (-u[0], -u[1])):
                off = int(sym[2:], 16) & 0xFFFF
                repl = "(*(__typeof__(%s) *)(page + 0x%04X))" % (sym, off)
                lines[i] = lines[i][:a] + repl + lines[i][b:]
            lines.insert(at, "%spage = (u8 *)0x%s0000;\n" % (ind, page))
            lines.insert(fn["b0"] + 1, "%su8 *page;\n" % ind)
            _emit(out, detail, "page_local",
                  dict(site=at + 1, label="page_local %s: page 0x%s0000, %d uses"
                       % (fn["name"], page, len(us)),
                       fn=fn["name"], page="0x%s0000" % page, uses=len(us),
                       symbols=sorted({u[3] for u in us})[:8]),
                  text, "".join(lines))
    out.sort(key=lambda z: z[0]["site"])
    return out


PERTURBATIONS = [
    ("param_copy", param_copy),
    ("decl_reorder", decl_reorder),
    ("width_change", width_change),
    ("adjacent_swap", adjacent_swap),
    ("local_alias", local_alias),
    ("page_local", page_local),
]
