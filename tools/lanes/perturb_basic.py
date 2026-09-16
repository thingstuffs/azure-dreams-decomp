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
  stmt_shift     t51_sched_order  the same move at a DISTANCE: one simple statement moved k = 2..6
                                  positions up or down, independent of every statement it crosses.
  local_alias    natural.dropcopy `x = y;` before a run of statements that read `y`, the run's reads
                                  renamed `x` (m2c's redundant copy), in five openings and two
                                  declaration spellings - see the function's own docstring.
  page_local     t54 / t59        the D_8XXXXXXX symbols of one 64 KiB page reached through a local
                                  page base: `page = (u8 *)0xXXXX0000;` and
                                  `(*(__typeof__(D_XXXXYYYY) *)(page + 0xYYYY))` at each use;
                                  a second instance per page uses the SIGNED base above the page
                                  and negative offsets (`page - 0x34C`), m2c's own spelling.
  addr_literal   t29_addrsym      a `D_8XXXXXXX` reference written as its integer address,
                                  `(*(__typeof__(D_X) *)0xADDR)`, one symbol or one whole page.

Every instance carries an `opening` parameter naming which widening produced it, so a kind's reach
can be read per opening instead of per kind.

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
# A temporary declared `__typeof__(EXPR) name;` (what `hoist` / `cond_temp` / the typed alias write):
# the run-33 two-move catalogue lost every hoist>param_copy / hoist>page_local / hoist>local_alias
# composition (99% NOBUILD) because the declaration-run scanners below read that line as a
# STATEMENT and inserted their own statement above it - a declaration after a statement, C89.
TYPEOF_DECL = re.compile(r"^[ \t]*__typeof__[ \t]*\(.*\)[ \t]*(?:\*[ \t]*)*" + ID
                         + r"(?:\[[^\]\n]*\])*[ \t]*(?:=[^;\n]*)?;[ \t]*$")
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
        return (bool(DECL_ONE.match(self.code(i))) or _t12_is_decl(self.code(i))
                or bool(TYPEOF_DECL.match(self.code(i))))


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


def _writes_object(masked, v):
    """`_writes`, plus a write to a MEMBER of `v` - `v.f = ...`, `v.a.b++`, `v.arr[2] = ...`.

    THE DEFECT THIS CLOSES (round-33 review, MAJOR 5).  `_writes` only sees `v` followed by an
    assignment operator, so a struct member write was not a write of `v` and did not cut the alias's
    run; `_value_reads` then counted that same occurrence as a READ, pulled the line into the span
    and RENAMED THE WRITE - `callback_sets_alias.first = ...` stores into the copy, and the copy
    `alias = callback_sets;` above it reads an aggregate nothing had written yet.  Both halves go
    away once the member write cuts the run: the occurrence that admitted the span WAS the write.

    `->` is deliberately NOT included.  `v->f = x` writes the POINTEE, not the pointer, and an alias
    that copies the pointer addresses the same object - that rename is the kind's own move.
    `_writes` itself is left alone: param_copy and the untouched kinds share it.
    """
    V = re.escape(v)
    return _writes(masked, v) + len(re.findall(
        r"(?<![\w.>])%s(?:\s*\.\s*%s(?:\s*\[[^\]\n]*\])?)+\s*"
        r"(?:=(?!=)|\+\+|--|[-+*/%%&|^]=|<<=|>>=)" % (V, ID), masked))


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
    if TYPEOF_DECL.match(ctx.code(i)):
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


# --------------------------------------------------------------------------- stmt_shift

MAX_SHIFT = 6
MIN_SHIFT = 2
MAX_SHIFT_PER_FN = 8
TYPE_WORDS = set(SPELLINGS) | set(C_SPELLING) | {"unsigned", "signed", "char", "short", "int",
                                                 "long", "void", "const", "volatile", "register"}


def _pure_local_stmt(masked, locs, addr_taken):
    """True when the statement reads and writes NOTHING but locals whose address is never taken.

    `L6 = 0;`, `L4 = L6;`, `L7 = (s32)L6;` - a plain identifier assigned from locals, literals and
    casts, with no call, no dereference, no index, no member and no global.  Such a statement is
    INVISIBLE to a function call and to any store through a pointer: the objects it touches have no
    address in the program, so nothing else can name them.  That is what lets it cross a call - the
    one refusal that stands between the catalogue and three of the six t51 rows the round-33 oracle
    tagged SWAP_REFUSED_CONTROL_OR_DECL.
    """
    m = T51.ASSIGN.match(masked)
    if not m:
        return False
    lhs, rhs = m["lhs"].strip(), m["rhs"]
    if not re.fullmatch(ID, lhs) or lhs not in locs or lhs in addr_taken:
        return False
    if CALL.search(rhs) or MEM_OP.search(rhs) or "&" in rhs:
        return False
    for name in re.findall(ID, rhs):
        if name in TYPE_WORDS:
            continue
        if name not in locs or name in addr_taken:
            return False
    return True


def stmt_shift(text, detail=None):
    """adjacent_swap's move at a DISTANCE: one simple statement moved k = 2..6 positions.

    t51_sched_order's own lever is `move`, not `exchange with the neighbour`, and the round-33 text
    oracle found three t51 landings (dungeon/func_800BCB8C, dungeon/func_81325730,
    town/func_80469200) whose target differs from the landed text by a statement that travelled
    across MORE THAN ONE statement - a move `adjacent_swap` cannot express at any depth, because
    every intermediate text it would pass through is a different program's text only by accident.

    The statement moves UP or DOWN within its own block, crossing k statements.  It must be
    independent of EVERY statement it crosses, pairwise, under the same two tests adjacent_swap
    uses - `t51.independent()` (the tests `sched_map.py` applies) and `_mem_independent()` (the
    alias test t51 leaves to the gate) - and it may cross nothing but simple statements at the same
    depth and in the same arm: a control line, a declaration, a label or a call refuses the shift,
    on the moved statement's side as well as on any crossed one.  `params` carries `k` and `dir`.

    ONE OPENING on top of that, and the six rows are what asked for it: when the MOVED statement
    reads and writes nothing but locals whose address is never taken (`_pure_local_stmt`), it may
    cross a CALL - a call cannot name an object that has no address.  Those instances are tagged
    `pure_local_k_dir` and they are the only ones allowed at k == 1, because adjacent_swap refuses
    any pair with a call in it and the two populations therefore still do not meet.
    """
    if not _guard(text, detail, "stmt_shift"):
        return []
    ctx = Ctx(text)
    lines51, recs = T51.units(text)
    by = {r["line"]: r for r in recs}
    out = []
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        locs = {p["name"] for p in fn["params"]}
        for i in range(fn["b0"] + 1, fn["b1"]):
            if not ctx.direct[i] and ctx.is_decl(i):
                locs.update(_decl_vars(ctx.code(i)))
        fbody = "".join(ctx.m[fn["b0"]:fn["b1"] + 1])
        addr_taken = {v for v in locs
                      if re.search(r"&\s*(?<![\w.])%s\b" % re.escape(v), fbody)}

        def movable(i):
            """A line that may be moved or crossed, with the reason it may not."""
            r = by.get(i)
            if r is None:
                return "not-a-unit"
            if not r["simple"]:
                return "control-or-not-simple"
            # t51's `is_decl` only knows a fixed list of type words, so `S_Ctx *ctx;` and
            # `Fields *fields;` read to it as ORDINARY STATEMENTS - the first whole-population run
            # of this kind moved 180 such declarations and every one of them was a NOBUILD (a
            # declaration after a statement is not C89).  This module's own parser knows them.
            if r["decl"] or ctx.is_decl(i) or _declarative(ctx, i):
                return "declaration"
            if not ctx.simple(i):
                return "multi-line-statement-or-label"
            if ctx.dangling(i):
                return "brace-less-control-body"
            if CALL.search(r["masked"]):
                return "call"
            return None

        emitted = 0
        for i in range(fn["b0"] + 1, fn["b1"]):
            why = movable(i)
            if why:
                _note(detail, why, ctx.code(i).strip()[:40])
                continue
            ri = by[i]
            pure = _pure_local_stmt(ri["masked"], locs, addr_taken)
            for direction in ("up", "down"):
                crossed = []
                crossed_a_call = False
                step = -1 if direction == "up" else 1
                j = i
                for _ in range(MAX_SHIFT):
                    j += step
                    if not (fn["b0"] < j < fn["b1"]):
                        break
                    if not ctx.code(j).strip():
                        continue                      # a blank line is not a position
                    why = movable(j)
                    if why == "call" and pure:
                        why = None                    # see `_pure_local_stmt`
                        crossed_a_call = True
                    if why:
                        _note(detail, "crosses-" + why, ctx.code(j).strip()[:40])
                        break
                    rj = by[j]
                    if rj["depth"] != ri["depth"]:
                        _note(detail, "crosses-depth-differs", ctx.code(j).strip()[:40])
                        break
                    if rj["arm"] != ri["arm"]:
                        _note(detail, "crosses-arm-differs", ctx.code(j).strip()[:40])
                        break
                    if not T51.independent(ri["masked"], rj["masked"]):
                        _note(detail, "crosses-dep-data", ctx.code(j).strip()[:40])
                        break
                    if not _mem_independent(ri["masked"], rj["masked"], locs):
                        _note(detail, "crosses-dep-mem-alias", ctx.code(j).strip()[:40])
                        break
                    crossed.append(j)
                    k = len(crossed)
                    # k == 1 is adjacent_swap's own move and is not repeated here - EXCEPT when a
                    # call was crossed, which adjacent_swap refuses outright, so the two kinds'
                    # populations still do not overlap on a single site.
                    if k < MIN_SHIFT and not crossed_a_call:
                        continue
                    if emitted >= MAX_SHIFT_PER_FN:
                        _note(detail, "over-eight-shifts", fn["name"])
                        break
                    moved = ctx.lines[i]
                    if not moved.endswith("\n"):
                        _note(detail, "statement-spans-lines", ctx.code(i).strip()[:40])
                        break
                    body = list(ctx.lines)
                    body.pop(i)
                    # after the pop a line ABOVE `i` keeps its index and a line BELOW shifts up by
                    # one, so `j` is the insertion index in both directions: before line `j` when
                    # moving up, after it (it now sits at j-1) when moving down.
                    body.insert(j, moved)
                    tag = ("pure_local_%d_%s" if crossed_a_call else "shift_%d_%s") % (k, direction)
                    _emit(out, detail, "stmt_shift",
                          dict(site=i + 1, k=k, dir=direction, opening=tag,
                               pure_local=bool(crossed_a_call),
                               fn=fn["name"], stmt=ctx.code(i).strip()[:60],
                               across=[ctx.code(x).strip()[:40] for x in crossed],
                               label="stmt_shift %s: %s moved %s across %d statements"
                                     % (fn["name"], ctx.code(i).strip()[:30], direction, k)),
                          text, "".join(body))
                    emitted += 1
    out.sort(key=lambda z: (z[0]["site"], z[0]["dir"], z[0]["k"]))
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


def _straight_blocks(ctx, fn, minlen=2):
    """The maximal straight runs of simple statements at one depth: a run has no control line, no
    label, no declaration and no brace in it, so a copy inserted at its head reaches every line.

    `minlen` is 2 for the base kind (m2c's copy spans at least two statements) and 1 for the
    ALIAS_READ_ONCE opening, whose whole run is a single statement.
    """
    blocks, cur = [], []
    for i in range(fn["b0"] + 1, fn["b1"]):
        s = ctx.code(i).strip()
        if not s:
            continue
        broke = (ctx.direct[i] or not ctx.simple(i) or ctx.is_decl(i) or ctx.dangling(i)
                 or (cur and ctx.depth[i] != ctx.depth[cur[0]]))
        if broke:
            if len(cur) >= minlen:
                blocks.append(cur)
            cur = []
            if not (ctx.direct[i] or not ctx.simple(i) or ctx.is_decl(i) or ctx.dangling(i)):
                cur = [i]
            continue
        cur.append(i)
    if len(cur) >= minlen:
        blocks.append(cur)
    return blocks


LABEL_RE = re.compile(r"^[ \t]*(?!case\b|default\b)" + ID + r"[ \t]*:(?!:)")
CASE_LABEL_RE = re.compile(r"^[ \t]*(?:case\b|default[ \t]*:)")
MEMBER_AFTER = re.compile(r"^[ \t]*->")


def _case_label_between(ctx, blk0, a, at):
    """True when a `case` / `default` label of the SLOT'S OWN block sits above line `a`.

    THE DEFECT THIS CLOSES (round-33 review, BLOCKING 1).  `_decl_slot` walks back to the innermost
    `{`, and for a `switch (x) {` that brace is the SWITCH BODY's: the slot is then the line above
    the first `case`, where control NEVER passes - every entry to a switch body is a jump to one of
    its labels.  A declaration there is legal C89 and harmless when it has no initialiser, but an
    INITIALISED one never runs, so the alias is read and written uninitialised.  `LABEL_RE` cannot
    see this: it is written `(?!case\\b|default\\b)` on purpose, for the goto labels it does check.

    The scan starts at the block's own brace line (not at `at`), because `switch (x) { case 0:` puts
    the first label on the brace line itself.  `ctx.depth[i] <= ctx.depth[at]` keeps a NESTED
    switch's labels out: a nested switch body is one brace deeper than the slot, so its labels never
    stand for a slot the program cannot reach.  The one over-refusal the `i == blk0` clause can make
    is a whole nested switch written on the block's own brace line, which is conservative and rare.
    """
    for i in range(blk0, a):
        if ctx.direct[i] or ctx.depth[i] > ctx.depth[at]:
            continue
        s = ctx.code(i)
        if CASE_LABEL_RE.match(s):
            return True
        if i == blk0 and re.search(r"\{[ \t]*(?:case\b|default[ \t]*:)", s):
            return True
    return False


def _value_reads(masked, v):
    """Occurrences of `v` read for its VALUE - an `&v` is not one.

    The base kind never needed the distinction, because a variable whose address is taken anywhere
    in the function was refused outright.  The `address_taken` opening keeps such a variable, so
    `&v` must not pull the alias's span over the line that takes the address (renaming it there
    would produce `&v_alias`, a different object).
    """
    n = 0
    for s, _e in _occ(masked, v):
        if masked[:s].rstrip().endswith("&"):
            continue
        n += 1
    return n


def _decl_slot(ctx, fn, a, wide=True):
    """Where an alias declaration may be inserted above line `a`: (line, reason_it_was_widened).

    The base walk consumes the block's leading run of ONE-LINE, single-declarator declarations and
    stops at the first line that is not one.  If that line is still DECLARATIVE, inserting a
    declaration after it is illegal C89 (a declaration may not follow a statement) and inserting it
    before changes nothing - but the reason it stopped is usually not "a statement": on the round-33
    landed rows it is a MULTI-DECLARATOR line (`s32 a, b;`) or a MULTI-LINE aggregate declaration
    (`static void *const table[] = {`), both of which a declaration may perfectly well follow.
    `wide` consumes those two shapes as well and reports which one it needed; anything else still
    refuses, and the refusal now names the line's shape instead of one flat counter.
    """
    blk0 = _block_open_line(ctx, fn, a)
    at = blk0 + 1
    widened = None
    while at < a:
        s = ctx.code(at).strip()
        if ctx.direct[at]:
            return None, "directive-in-declaration-block"
        if not s:
            at += 1
            continue
        if ctx.is_decl(at) and "{" not in s and "}" not in s:
            at += 1
            continue
        if not _declarative(ctx, at):
            break                                   # a real statement: the slot is here
        # a declaration the one-line parser will not consume - name its shape
        if s.endswith(";") and "{" not in s and "}" not in s and "," in s:
            if not wide:
                return None, "declaration-block-not-simple:multi-declarator"
            widened = widened or "multi_declarator"
            at += 1
            continue
        # a multi-line declaration: run to the line that closes it, braces balanced
        j, bal = at, 0
        while j < a:
            bal += ctx.code(j).count("{") - ctx.code(j).count("}")
            if bal == 0 and ctx.code(j).rstrip().endswith(";"):
                break
            j += 1
        else:
            return None, "declaration-block-not-simple:unterminated"
        if bal != 0:
            return None, "declaration-block-not-simple:unbalanced"
        if not wide:
            return None, "declaration-block-not-simple:multi-line"
        widened = widened or "multi_line_declaration"
        at = j + 1
    if at > a:
        return None, "declaration-slot-below-run"
    if at < len(ctx.lines) and ctx.direct[at]:
        return None, "declaration-slot-below-run"
    return at, widened


# A BARE value use of a pointer: the whole of it is handed somewhere, with no operator applied.
# The test is deliberately a whitelist.  A blacklist let `*(record + 1)` through as "bare" - the
# operator there is the `+` AFTER the name, not a `*` before it - and `void *record_alias = record;`
# then made `*(record_alias + 1)` arithmetic on `void *`, which is what 10 of the first
# whole-population run's local_alias NOBUILDs were.
BARE_AFTER = re.compile(r"^[ \t]*(?:[,;)]|==|!=)")
BARE_BEFORE = re.compile(r"(?:^|[=(,])[ \t]*$")


def _uses_in_span(ctx, span, v):
    """Every occurrence of `v` on the span's masked lines, tagged `member` / `bare` / `other`.

    `member` is `v->f`, which the untyped alias can spell by casting back; `bare` is a use that
    hands the pointer on whole (`p = v;`, `g(v)`, `v == 0`) and needs no cast at all; `other` is
    everything else - arithmetic, an index, a dereference, a `.` member, `&v`, a cast - and one
    `other` refuses the untyped spelling for the whole run.
    """
    out = []
    for i in span:
        line = ctx.code(i)
        for s, e in _occ(line, v):
            before = line[:s]
            after = line[e:]
            if MEMBER_AFTER.match(after):
                out.append((i, s, e, "member"))
            elif BARE_AFTER.match(after) and BARE_BEFORE.search(before):
                out.append((i, s, e, "bare"))
            else:
                out.append((i, s, e, "other"))
    return out


def local_alias(text, detail=None):
    """natural.dropcopy reversed: m2c's redundant `x = y;` in front of a run that reads `y`.

    A local or parameter `y` read inside one straight run of consecutive simple statements gets a
    fresh local of its declared type: the copy is inserted before the run's first read and every
    read of `y` from there to its last read in the run is renamed.  The alias therefore spans
    whatever sits between them - calls included - which is where an m2c copy is not a plain
    coalescable move.

    FIVE OPENINGS, each named in the instance's `opening` parameter and each measurable on its own
    (the round-33 text oracle found the base kind enumerating NOTHING on 6 of the 24 t20_fencefree
    rows t20 landed, and named the refusal behind each):

      base            two or more reads in a write-free run of two or more statements.
      read_once       ALIAS_READ_ONCE: the copy is read ONCE and the run is one statement.  m2c
                      writes a copy it then reads a single time (`s32 L3; L3 = pair_count; ...`)
                      and the two-read rule refused every such site (`no-run-with-two-reads`).
      written_in_run  ALIAS_WRITTEN_IN_RUN: the source is WRITTEN inside the run.  The alias is a
                      SNAPSHOT OF THE VALUE BEFORE THAT WRITE: only the reads up to the writing
                      statement are renamed, the writing statement itself and everything after it
                      keep reading `y`, so both texts compute the same values.  The writing
                      statement's own right-hand side is left alone (it is evaluated after the
                      snapshot's last renamed read, and renaming it would need the write's order).
      block_reopened  ALIAS_BLOCK_REFUSED: the declaration slot needed `_decl_slot(wide=True)` -
                      a multi-declarator or multi-line declaration walked over (see there).
      address_taken   ALIAS_BLOCK_REFUSED's other half: `&y` occurs in the function but NOT inside
                      the alias's span, and the span has no call and no store through memory, so
                      nothing can write `y` through that pointer while the copy is live.

    Plus TWO SPELLINGS of the declaration, emitted beside the statement form on the same run:

      typed_init      TYPED_ALIAS_INIT_DECL: `T alias = y;` as an INITIALISED declaration at the
                      top of the block instead of `T alias;` + `alias = y;`.  Legal only when `y`
                      is not written and no label sits between the declaration slot and the run
                      (the initialiser runs at block entry, the statement ran at the run's head).
      typed_init_void `void *alias = y;` - m2c's UNTYPED alias - for a pointer `y`, with every use
                      that needs the type spelled back as `((T)alias)->f`.  Emitted only where
                      every use in the span is a bare value or a `->` member access.

    One instance per (run, variable, opening); the MAX_ALIAS_PER_FN longest spans of each opening
    are kept, emitted in site order.
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
        blocks = _straight_blocks(ctx, fn, minlen=1)
        if not blocks:
            _note(detail, "no-straight-run", fn["name"])
            continue
        runs = []
        for v in sorted(set(cands)):
            # AN AGGREGATE IS NEVER COPIED (round-33 review, MAJOR 5, and the residue left after the
            # member-write fix).  A source that is not a pointer and is used anywhere with a `.` is
            # a struct or a union, and three things go wrong at once: a member WRITE renamed into
            # the copy stores nowhere (`_writes_object` cuts the run, but only where it can see the
            # write); an ARRAY member DECAYS to the address of the array INSIDE the copy, so
            # `packed_cursor = shuffle.indices;` hands out a pointer into a different object
            # (slus/w_8004AA78, the one instance the fix's own scan still found); and gcc emits the
            # copy as a real struct move, which is catalogue mass no census residue answers.  m2c's
            # redundant copy is a REGISTER copy - param_copy refuses a struct-by-value parameter for
            # the same reason.  Cost, measured: 29 instances of 37,821 over the whole population.
            if not str(_declared_type(ctx, fn, v) or "").rstrip().endswith("*") and \
                    re.search(r"(?<![\w.])%s[ \t]*\." % re.escape(v), body):
                _note(detail, "aggregate-source:used-with-a-member", "%s:%s" % (fn["name"], v))
                continue
            taken = bool(re.search(r"&\s*(?<![\w.])%s\b" % re.escape(v), body))
            for blk in blocks:
                # a write of `v` ends the alias's run: the copy would then hold a stale value, so
                # each write-free segment of the run is considered on its own, and a segment that
                # a write CUT SHORT is the `written_in_run` opening.
                seg, segs = [], []
                for i in blk:
                    if _writes_object(ctx.code(i), v):
                        segs.append((seg, True))
                        seg = []
                        continue
                    seg.append(i)
                segs.append((seg, False))
                for s, cut in segs:
                    if not s:
                        continue
                    reads = [i for i in s if _value_reads(ctx.code(i), v)]
                    if not reads:
                        continue
                    span = [i for i in s if reads[0] <= i <= reads[-1]]
                    if cut:
                        opening = "written_in_run"
                    elif len(reads) < 2 or len(s) < 2:
                        opening = "read_once"
                    else:
                        opening = "base"
                    if taken:
                        if any(re.search(r"&\s*(?<![\w.])%s\b" % re.escape(v), ctx.code(i))
                               for i in span):
                            _note(detail, "address-taken-inside-the-span", "%s:%s" % (fn["name"], v))
                            continue
                        if any(CALL.search(ctx.code(i)) or MEM_OP.search(ctx.code(i).split("=")[0])
                               for i in span):
                            _note(detail, "address-taken:call-or-store-in-the-span",
                                  "%s:%s" % (fn["name"], v))
                            continue
                        opening = "address_taken"
                    runs.append((len(span), span, v, opening))
        if not runs:
            _note(detail, "no-run-with-a-read", fn["name"])
            continue
        chosen = []
        for opening in ("base", "read_once", "written_in_run", "address_taken"):
            group = sorted([r for r in runs if r[3] == opening], key=lambda r: (-r[0], r[1][0], r[2]))
            chosen += group[:MAX_ALIAS_PER_FN]
            for extra in group[MAX_ALIAS_PER_FN:]:
                _note(detail, "over-four-runs:" + opening, "%s:%s" % (fn["name"], extra[2]))
        chosen.sort(key=lambda r: (r[1][0], r[2], r[3]))
        for n, span, v, opening in chosen:
            a = span[0]
            ty = _declared_type(ctx, fn, v)
            spelled = ty if ty else "__typeof__(%s)" % v
            name = v + "_alias"
            k = 2
            while name in allnames:
                name = "%s_alias%d" % (v, k)
                k += 1
            at, widened = _decl_slot(ctx, fn, a)
            if at is None:
                _note(detail, widened, "%s:%s" % (fn["name"], v))
                continue
            if widened:
                opening = "block_reopened"
            ind = re.match(r"[ \t]*", ctx.lines[a]).group(0)
            dind = re.match(r"[ \t]*", ctx.lines[at] if ctx.lines[at].strip() else ctx.lines[a]).group(0)
            sep = "" if spelled.endswith("*") else " "
            renamed = list(ctx.lines)
            for k2 in span:
                renamed[k2] = _rename_in_line(renamed[k2], ctx.m[k2], v, name)
            lines = list(renamed)
            lines.insert(a, "%s%s = %s;\n" % (ind, name, v))
            lines.insert(at, "%s%s%s%s;\n" % (dind, spelled, sep, name))
            base_params = dict(site=a + 1, label="local_alias %s: %s = %s over %d statements (%s)"
                               % (fn["name"], name, v, n, opening),
                               fn=fn["name"], var=v, alias=name, run=n, type=spelled,
                               opening=opening, typed="explicit" if ty else "typeof")
            _emit(out, detail, "local_alias", base_params, text, "".join(lines))

            # --- the INITIALISED declaration spellings (TYPED_ALIAS_INIT_DECL)
            why = None
            if any(_writes_object(ctx.code(i), v) for i in range(at, a)):
                why = "typed-init:source-written-above-the-run"
            elif any(LABEL_RE.match(ctx.code(i)) for i in range(at, a)):
                why = "typed-init:label-between-the-declaration-and-the-run"
            elif _case_label_between(ctx, _block_open_line(ctx, fn, a), a, at):
                # the slot is inside a SWITCH BODY, above its first label: control never passes
                # through it and the initialiser never runs (the statement form is unaffected).
                why = "typed-init:case-label-between-the-declaration-and-the-run"
            elif re.search(r"&\s*(?<![\w.])%s\b" % re.escape(v), body) and \
                    any(CALL.search(ctx.code(i)) or MEM_OP.search(ctx.code(i).split("=")[0])
                        for i in range(at, a)):
                # `&v` exists somewhere in the function, so a call or a store through a pointer
                # BETWEEN the declaration slot and the run can write `v`.  The statement form takes
                # its snapshot at the run's head and is unaffected; an initialiser at block entry
                # would snapshot the value before that write.  The span itself is already guarded
                # by the `address_taken` opening; this is the interval above it.
                why = "typed-init:address-taken-with-a-call-or-store-above-the-run"
            if why:
                _note(detail, why, "%s:%s" % (fn["name"], v))
                continue
            init = list(renamed)
            init.insert(at, "%s%s%s%s = %s;\n" % (dind, spelled, sep, name, v))
            p = dict(base_params, site=at + 1, opening="typed_init",
                     label="local_alias %s: %s%s%s = %s (initialised declaration, %d statements)"
                           % (fn["name"], spelled, sep, name, v, n))
            _emit(out, detail, "local_alias", p, text, "".join(init))
            if not spelled.endswith("*"):
                _note(detail, "typed-init-void:source-is-not-a-pointer", "%s:%s" % (fn["name"], v))
                continue
            uses = _uses_in_span(ctx, span, v)
            if any(u[3] == "other" for u in uses):
                _note(detail, "typed-init-void:use-needs-more-than-a-member-cast",
                      "%s:%s" % (fn["name"], v))
                continue
            vlines = list(ctx.lines)
            for i, s0, e0, what in sorted(uses, key=lambda u: (-u[0], -u[1])):
                repl = ("((%s)%s)" % (spelled, name)) if what == "member" else name
                vlines[i] = vlines[i][:s0] + repl + vlines[i][e0:]
            vlines.insert(at, "%svoid *%s = %s;\n" % (dind, name, v))
            p = dict(base_params, site=at + 1, opening="typed_init_void", type="void *",
                     label="local_alias %s: void *%s = %s (untyped alias, %d casts back)"
                           % (fn["name"], name, v, sum(1 for u in uses if u[3] == "member")))
            _emit(out, detail, "local_alias", p, text, "".join(vlines))
    out.sort(key=lambda z: (z[0]["site"], z[0]["opening"], z[0]["label"]))
    return out


# --------------------------------------------------------------------------- the address family

MAX_ADDR_PER_FN = 6


def _sym_kinds(ctx):
    """Every `D_8XXXXXXX` of the text, tagged `function` / `array` / `scalar`.

    The tag decides how a reference may be respelled, and it must separate the two shapes the old
    `symbol-used-as-array-or-function` counter lumped together (1,412 of page_local's 2,798
    refusals on the 1,000-row run): an ARRAY reference is spellable through the page base, a
    FUNCTION reference is not - its type carries a signature no cast of ours reconstructs, and a
    call through an integer-derived pointer is not the move any generator makes.
    """
    whole = "".join(ctx.m)
    kinds = {}
    for m in PAGE_SYM.finditer(whole):
        kinds.setdefault(m.group(0), "scalar")
    for m in re.finditer(r"(?<![\w.])(D_8[0-9A-Fa-f]{7})\b[ \t]*\(", whole):
        kinds[m.group(1)] = "function"
    for m in re.finditer(r"^[ \t]*(?:extern[ \t]+)?[A-Za-z_][\w \t]*[\s*](D_8[0-9A-Fa-f]{7})[ \t]*"
                         r"\([^)]*\)[ \t]*;", whole, re.M):
        kinds[m.group(1)] = "function"
    for m in re.finditer(r"(?<![\w.])(D_8[0-9A-Fa-f]{7})\b[ \t]*\[", whole):
        if kinds.get(m.group(1)) != "function":
            kinds[m.group(1)] = "array"
    # ...and from the DECLARATION, not only from a use: `extern u8 D_X[];` used only bare would
    # otherwise read as a scalar, and `&D_X` on it takes the pointer-to-incomplete-array spelling
    # gcc 2.x refuses (the 7 addr_literal NOBUILDs left after the first fix).
    for m in re.finditer(r"^[ \t]*(?:extern[ \t]+)?[A-Za-z_][\w \t]*[\s*](D_8[0-9A-Fa-f]{7})[ \t]*"
                         r"\[[^\]\n]*\]", whole, re.M):
        if kinds.get(m.group(1)) != "function":
            kinds[m.group(1)] = "array"
    return kinds


def _sym_kind_of(kinds, sym):
    return kinds.get(sym, "scalar")


def _declaration_line(ctx, i):
    """True when line `i` declares a name - INCLUDING the `extern`/`typedef` shapes `_declarative`
    deliberately refuses (both words are in CTRL, which that parser checks before STORAGE, because
    `extern` also begins nothing a statement may be inserted in front of).  `_declarative` itself is
    left alone: `_decl_slot` and `_first_statement_line` both read it, and there an in-body `extern`
    stopping the walk is the conservative answer."""
    s = ctx.code(i).strip()
    if not s or ctx.direct[i]:
        return False
    if re.match(r"^(?:extern|typedef|static|register)\b", s):
        return True
    return bool(ctx.is_decl(i) or _declarative(ctx, i))


def _first_init_eq(s):
    """The offset of a declaration's first initialiser `=`, or None: everything before it is the
    DECLARATOR, which is a definition of the name and never a use of it."""
    depth = 0
    for k, c in enumerate(s):
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "=" and depth == 0 and s[k + 1:k + 2] != "=" and s[k - 1:k] not in "=!<>+-*/%&|^":
            return k
    return None


def _sym_uses(ctx, fn, kinds, detail, why_fn):
    """Every symbol reference in the body: [(line, start, end, sym, 'value'|'addr')], by page.

    A reference in the DECLARATOR of an in-body declaration is not a use and is skipped (round-33
    review, MAJOR 4): a row that writes `extern s32 D_8008DAB4;` inside the body had that
    declaration rewritten to `extern s32 (*(__typeof__(D_8008DAB4) *)0x8008DAB4);`, with the
    `__typeof__` naming the very declarator being declared.  cc1 refuses it, so the 21 such records
    of the first run were NOBUILDs rather than poisoned fingerprints - but the brief names the case
    blocking, and a wasted compile is still a wasted compile.  A reference in an INITIALISER
    (`S *input = &D_80083160;`) is an ordinary use and is kept.
    """
    uses = collections.defaultdict(list)
    for i in range(fn["b0"] + 1, fn["b1"]):
        if ctx.direct[i]:
            continue
        decl_eq = None
        if _declaration_line(ctx, i):
            decl_eq = _first_init_eq(ctx.code(i))
            if decl_eq is None:
                decl_eq = len(ctx.code(i))          # no initialiser: the whole line is declarator
        for m in PAGE_SYM.finditer(ctx.code(i)):
            sym = m.group(0)
            if decl_eq is not None and m.start() < decl_eq:
                _note(detail, "symbol-in-its-own-declaration", sym)
                continue
            if kinds.get(sym) == "function":
                _note(detail, why_fn, sym)
                continue
            head = ctx.code(i)[:m.start()].rstrip()
            tail = ctx.code(i)[m.end():].lstrip()
            page = m.group("hex")[:4].upper()
            # `&D_X` is an address use - but `&D_X[0]` and `&D_X.f` are NOT: there the `&` binds to
            # the subscript or the member, and the symbol itself is an ordinary value use.  Reading
            # them as address uses spelled `((__typeof__(&D_X))ADDR)[0]` - a pointer to an
            # INCOMPLETE ARRAY, indexed - is what 67 of addr_literal's and most of page_local's
            # NOBUILDs were on the first whole-population run; on the page_local side the bare
            # `(page + 0xYYYY)[0]` it produced would have been a silent TYPE change (u8 elements).
            # An ARRAY symbol never takes the address spelling at all: `__typeof__(&D_X)` is
            # `T (*)[]` and gcc 2.x refuses to index or dereference it (probed on
            # main/func_80021A84: the value spelling builds, the `&` spelling does not).
            addr = (head.endswith("&") and _sym_kind_of(kinds, sym) != "array"
                    and tail[:1] not in ("[", ".") and not tail.startswith("->"))
            if addr:
                uses[page].append((i, len(head) - 1, m.end(), sym, "addr"))
            else:
                uses[page].append((i, m.start(), m.end(), sym, "value"))
    return uses


def _first_statement_line(ctx, fn):
    """The line the page base's assignment is inserted at: the first line of the body that is not a
    declaration, a blank line or a comment.

    `_decl_run_end` is not used here, and the reason is measured.  It gives up outright when the
    leading block holds a declaration its one-line parser cannot consume (a multi-line aggregate:
    30 of page_local's refusals on the 1,000-row run, and the binding refusal on
    dungeon/func_819A0DB8).  Worse, it STOPS AT A COMMENT LINE and returns the line before it, so on
    main/func_800121A4 the assignment was inserted above a `u8 *global_page = (u8 *)0x80010000;`
    that follows a four-line comment - `parse error before '*'`, a declaration after a statement,
    and a NOBUILD.  This walk skips comment-only lines and runs a multi-line declaration to its
    terminator.  `_decl_run_end` itself is deliberately left alone: param_copy shares it and its
    measured population is round 33's t69_prologue evidence (report_impl_C.txt says what it costs
    there).
    """
    at = fn["b0"] + 1
    while at < fn["b1"]:
        s = ctx.code(at).strip()
        raw = ctx.lines[at].strip()
        comment = raw.startswith(("/*", "*", "*/", "//"))
        if ctx.direct[at]:
            return None
        if not s:
            if raw and not comment:
                return None            # masked to nothing and not a comment: do not guess
            at += 1
            continue
        if comment and set(s) <= set("/*"):
            # `mask_text` blanks a comment's TEXT but keeps its punctuation, so the opening line of
            # a block comment masks to `/*` - non-empty, not a declaration, and the walk stopped
            # there.  On main/func_800121A4 that put `page = (u8 *)0x80080000;` above the
            # `u8 *global_page = (u8 *)0x80010000;` that follows the comment: a declaration after a
            # statement, and a NOBUILD.  Measured over the whole population, page_local's nobuilds
            # go 26 -> 24 (main/func_800121A4 is one of the two); the rest are other shapes.  The
            # two conditions together are safe - a continuation line like `*p = 0;` also starts
            # with a `*`, but its masked text is not punctuation alone.
            at += 1
            continue
        if ctx.is_decl(at) and "{" not in s and "}" not in s:
            at += 1
            continue
        if not _declarative(ctx, at):
            return at
        j, bal = at, 0
        while j < fn["b1"]:
            bal += ctx.code(j).count("{") - ctx.code(j).count("}")
            if bal == 0 and ctx.code(j).rstrip().endswith(";"):
                break
            j += 1
        else:
            return None
        if bal != 0:
            return None
        at = j + 1
    return None


def _fresh_page_name(ctx, fn, scope):
    """`page`, or `page2`.. when the function or the file already spells it (the per-FUNCTION check
    the round-33 oracle asked for: the old test scanned the WHOLE FILE, so one unrelated function's
    local `page` refused every function of the row)."""
    names = _fn_body_names(ctx, fn) | {p["name"] for p in fn["params"]} | scope
    for k in range(1, 6):
        cand = "page" if k == 1 else "page%d" % k
        if cand not in names:
            return cand
    return None


def _file_scope_names(ctx):
    inside = [False] * len(ctx.lines)
    for fn in ctx.fns:
        for i in range(fn["b0"], min(fn["b1"] + 1, len(inside))):
            inside[i] = True
    return set(re.findall(ID, "".join(m for i, m in enumerate(ctx.m) if not inside[i])))


def addr_literal(text, detail=None):
    """t29_addrsym reversed: a `D_8XXXXXXX` reference written as its integer address.

    t29 deletes a pinned local holding an address literal and writes every use as the SYMBOL at
    that address; m2c wrote the address.  Under this tree's D_ADDRESS link convention the symbol's
    address IS the hex in its name, so the reversal needs nothing but the name:

        a value use   `D_X`  ->  `(*(__typeof__(D_X) *)0xADDR)`
        an address    `&D_X` ->  `((__typeof__(&D_X))0xADDR)`

    An ARRAY symbol takes the value spelling too, and it is exactly right there: `__typeof__(D_X)`
    is the array type, so `*(__typeof__(D_X) *)ADDR` is an lvalue of array type which decays to
    `ADDR` in an operand position and indexes as `(...)[i]` - no `&D_X[0]` needed and no pointer
    type invented.  A FUNCTION symbol is refused (`symbol-is-a-function`).

    Two instance shapes, as the round-33 brief asks: one per SYMBOL (all of its uses in the
    function at once - what t29's `every variable alone` candidate undoes) and one per PAGE (every
    symbol whose address shares the upper half, all at once - t29's `all together` candidate).
    """
    if not _guard(text, detail, "addr_literal"):
        return []
    ctx = Ctx(text)
    kinds = _sym_kinds(ctx)
    out = []
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        uses = _sym_uses(ctx, fn, kinds, detail, "symbol-is-a-function")
        if not uses:
            _note(detail, "no-page-symbols", fn["name"])
            continue
        by_sym = collections.defaultdict(list)
        for page, us in uses.items():
            for u in us:
                by_sym[u[3]].append(u)

        def rewrite(group, params):
            lines = list(ctx.lines)
            for i, a, b, sym, what in sorted(group, key=lambda u: (-u[0], -u[1])):
                addr = int(sym[2:], 16)
                if what == "addr":
                    repl = "((__typeof__(&%s))0x%08X)" % (sym, addr)
                else:
                    repl = "(*(__typeof__(%s) *)0x%08X)" % (sym, addr)
                lines[i] = lines[i][:a] + repl + lines[i][b:]
            _emit(out, detail, "addr_literal", params, text, "".join(lines))

        for sym in sorted(by_sym)[:MAX_ADDR_PER_FN]:
            g = by_sym[sym]
            rewrite(g, dict(site=min(u[0] for u in g) + 1, fn=fn["name"], symbol=sym,
                            scope="symbol", opening="symbol", uses=len(g),
                            kind_of_symbol=kinds.get(sym, "scalar"),
                            label="addr_literal %s: %s -> 0x%s (%d uses)"
                                  % (fn["name"], sym, sym[2:], len(g))))
        for extra in sorted(by_sym)[MAX_ADDR_PER_FN:]:
            _note(detail, "over-six-symbols", "%s:%s" % (fn["name"], extra))
        for page in sorted(uses):
            g = uses[page]
            if len({u[3] for u in g}) < 2:
                _note(detail, "single-symbol-page", "%s:%s" % (fn["name"], page))
                continue
            rewrite(g, dict(site=min(u[0] for u in g) + 1, fn=fn["name"], page="0x%s0000" % page,
                            scope="page", opening="page", uses=len(g),
                            symbols=sorted({u[3] for u in g})[:8],
                            label="addr_literal %s: every symbol of page 0x%s0000 (%d symbols, "
                                  "%d uses)" % (fn["name"], page, len({u[3] for u in g}), len(g))))
    out.sort(key=lambda z: (z[0]["site"], z[0]["opening"], z[0]["label"]))
    return out


# --------------------------------------------------------------------------- page_local

def page_local(text, detail=None):
    """t54_pagebase / t59_offsetsym reversed: one 64 KiB page's symbols reached through a local base.

    Every use of `D_XXXXYYYY` whose upper half is the page becomes
    `(*(__typeof__(D_XXXXYYYY) *)(page + 0xYYYY))`, with `u8 *page;` declared and
    `page = (u8 *)0xXXXX0000;` as the first statement.  Two instances per page of a function:

      the UNSIGNED base   `u8 *page; page = (u8 *)0xXXXX0000;` and `page + 0xYYYY` at each use.
      the SIGNED base     `u32 page; page = 0xZZZZ0000;` with ZZZZ the NEXT 64 KiB boundary and
                          every offset NEGATIVE (`page - 0x34C`, `0x80100000 - 0x1AE0`).  This is
                          the shape the m2c texts of the landed t54 rows actually carry, and it is
                          retail's own arithmetic: `addiu` takes a SIGNED 16-bit immediate, so a
                          symbol whose low half is >= 0x8000 is reached from the boundary above it.

    THE TWO REFUSALS THE ROUND-33 RUN MEASURED AS BINDING ARE OPENED HERE.
    `symbol-used-as-array-or-function` was 1,412 of 2,798 refusals; an ARRAY symbol is now spelled
    `(*(__typeof__(D_X) *)(page + 0xYYYY))[i]` (the deref has array type and indexes directly) and
    only a FUNCTION symbol still refuses.  `address-of-symbol` was 468; `&D_X` is now
    `((__typeof__(&D_X))(page + 0xYYYY))`, the same typed spelling the signed mode always used.

    THE BARE `(page + 0xYYYY)` FOR AN ADDRESS USE IS GONE (round-33 review, BLOCKING 3).  It has
    type `u8 *`, so `&D_X + 4` became a four-BYTE step instead of a four-ELEMENT one - a different
    address, silently, on 59 compiled records that all carried an address-materialisation residue.
    The `&`-taken symbols here are scalars (an ARRAY symbol never takes the address spelling), so
    `__typeof__(&D_X)` is a plain `T *` and the cast is codegen-neutral.

    Every use ABOVE the line the base assignment lands on is dropped, not rewritten (round-33
    review, BLOCKING 2): the assignment goes after the block's leading declaration run, and a
    declaration whose initialiser was rewritten there read `page` before `page` was set.
    """
    if not _guard(text, detail, "page_local"):
        return []
    ctx = Ctx(text)
    kinds = _sym_kinds(ctx)
    scope = _file_scope_names(ctx)
    out = []
    for fn in ctx.fns:
        if _skip_fn(fn, detail):
            continue
        page_name = _fresh_page_name(ctx, fn, scope)
        if page_name is None:
            _note(detail, "page-name-in-use", fn["name"])
            continue
        at = _first_statement_line(ctx, fn)
        if at is None:
            _note(detail, "declaration-block-not-simple", fn["name"])
            continue
        uses = _sym_uses(ctx, fn, kinds, detail, "symbol-used-as-a-function")
        # A use ABOVE `at` would read `page` before the assignment that sets it: `page` is an
        # ordinary uninitialised local there, so the text compiles and the address is garbage.
        # Those uses are dropped (the instance rewrites the rest), never rewritten.
        for page in list(uses):
            keep, above = [], []
            for u in uses[page]:
                (keep if u[0] >= at else above).append(u)
            for u in above:
                _note(detail, "use-above-the-page-assignment", "%s:%s" % (fn["name"], u[3]))
            if keep:
                uses[page] = keep
            else:
                del uses[page]
        if not uses:
            _note(detail, "no-page-symbols", fn["name"])
            continue
        ind = _indent(ctx, fn)
        for page in sorted(uses):
            us = uses[page]
            if len(us) < 2:
                _note(detail, "single-use-page", "%s:%s" % (fn["name"], page))
                continue
            hi = int(page, 16)
            modes = ["unsigned"]
            # The SIGNED base is the boundary ABOVE the page and every offset is negative, and the
            # reason is `addiu`'s SIGNED 16-bit immediate: retail reaches a symbol whose low half is
            # >= 0x8000 from the next boundary down, which is why the m2c texts of the landed t54
            # rows read `u32 page = 0x800E0000; ... (page - 0x27BC)`.  Emitting that form for a
            # page whose symbols all sit in its LOWER half would write `page - 0xC284`, an offset
            # no compiler produces - catalogue mass with no census counterpart.  So the second
            # instance is offered only when every offset from the boundary above fits the
            # immediate.
            if all(((hi + 1) << 16) - int(u[3][2:], 16) <= 0x8000 for u in us):
                modes.append("signed")
            for mode in modes:
                base = (hi << 16) if mode == "unsigned" else ((hi + 1) << 16)
                lines = list(ctx.lines)
                for i, a, b, sym, what in sorted(us, key=lambda u: (-u[0], -u[1])):
                    addr = int(sym[2:], 16)
                    if mode == "unsigned":
                        expr = "%s + 0x%04X" % (page_name, addr - base)
                    else:
                        expr = "%s - 0x%X" % (page_name, base - addr)
                    if what == "addr":
                        # NEVER the bare `(page + 0xYYYY)`: it is a `u8 *` and pointer arithmetic on
                        # it steps in bytes (round-33 review, BLOCKING 3).
                        repl = "((__typeof__(&%s))(%s))" % (sym, expr)
                    else:
                        repl = "(*(__typeof__(%s) *)(%s))" % (sym, expr)
                    lines[i] = lines[i][:a] + repl + lines[i][b:]
                if mode == "unsigned":
                    lines.insert(at, "%s%s = (u8 *)0x%08X;\n" % (ind, page_name, base))
                    lines.insert(fn["b0"] + 1, "%su8 *%s;\n" % (ind, page_name))
                else:
                    lines.insert(at, "%s%s = 0x%08X;\n" % (ind, page_name, base))
                    lines.insert(fn["b0"] + 1, "%su32 %s;\n" % (ind, page_name))
                _emit(out, detail, "page_local",
                      dict(site=at + 1,
                           label="page_local %s: %s base 0x%08X, %d uses (%s)"
                                 % (fn["name"], mode, base, len(us), page_name),
                           fn=fn["name"], page="0x%08X" % base, base_mode=mode,
                           opening=mode, uses=len(us), name=page_name,
                           n_addr_of=sum(1 for u in us if u[4] == "addr"),
                           n_array=sum(1 for u in us if kinds.get(u[3]) == "array"),
                           symbols=sorted({u[3] for u in us})[:8]),
                      text, "".join(lines))
    out.sort(key=lambda z: (z[0]["site"], z[0]["opening"], z[0]["label"]))
    return out


PERTURBATIONS = [
    ("param_copy", param_copy),
    ("decl_reorder", decl_reorder),
    ("width_change", width_change),
    ("adjacent_swap", adjacent_swap),
    ("stmt_shift", stmt_shift),
    ("local_alias", local_alias),
    ("page_local", page_local),
    ("addr_literal", addr_literal),
]
