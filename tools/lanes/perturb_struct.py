"""Round 33's forward catalogue, implementer B: the declaration- and control-level perturbations.

WHY.  The catalogue takes the ~5,400 registered rows that are byte-exact with NO pin site and applies
ONE m2c-style perturbation at a time - the INVERSE of a generator's move - so the residue fingerprints
it collects speak the generators' language (docs/HANDOVER.md, "Round 33 plan").  Every diff in the
catalogue has retail on the `-` side (a pin-free row's own text IS retail) and the m2c-like text on the
`+` side, exactly the direction in which the lone-erasure census reads a pin site.

THE FIVE KINDS HERE (the sibling module carries the statement-level ones):

  hoist         `varset.inline_def` reversed: a side-effect-free sub-expression of a simple statement
                or a return moved into a temporary declared `__typeof__(EXPR) hoisted_N;`.
  retype_void   `varset.retype_ptr` reversed: `S *p` declared `void *p`, every use that needs the type
                respelled `((S *)p)->f` / `((S *)p)[i]` / `*((S *)p)` / `((S *)p) + n`.
  split         `varset.split_def_candidates` IS the move (a merge reversed); wrapped as instances.
  merge         `varset.merge_local_candidates` + `merge_param_candidates` (a split reversed), wrapped.
  goto_to_loop  t41 / t41b reversed: a backward-goto loop written as `do { } while` / `while ( ) { }`.

THE CONTRACT (fixed; the driver and the sibling module never import this one):

    PERTURBATIONS = [(kind, fn), ...]
    fn(text, detail=None) -> [(params, new_text), ...]

`params` is JSON-serialisable and always carries `site` (the 1-based line of the edited statement or
declaration) and `label` (one human-readable line) beside the kind's own parameters.  `detail` is a
`collections.Counter`; a `Detail` records `(refusal, what)` pairs as well, so the population ceiling of
each kind reads text-only, the way `t69_prologue.Detail` reads a refusal table.  Enumeration is
deterministic and ordered by site; nothing here touches a preprocessor line, and no move adds an
`ASM_*` macro, `__asm__`, `volatile`, a fake dependency, a one-trip block, a `#pragma` or an attribute.

WHAT THE MOVES REFUSE, and why the refusals are half the deliverable.  A perturbation that changes what
the text MEANS poisons a fingerprint, so the traps are refused textually and counted:

  * a braceless control arm.  `if (c)\n    x = 1;` would take `hoisted_1 = ...;` INTO the arm and leave
    the statement out of it - and `varset` calls a braceless head `unknown`, so the statement under it
    looks like any other (`hoist:braceless-arm`);
  * a continuation line of a multi-line statement, where inserting a line splits the statement
    (`hoist:continuation-line`);
  * a statement carrying `&&`, `||` or `?`: the sub-expression may be a short-circuit or conditional
    operand, evaluated conditionally (`hoist:stmt-has-shortcircuit`);
  * a declaration: hoisting out of an initialiser puts a statement before a declaration, which C89
    refuses (`hoist:stmt-is-a-declaration`);
  * a PREFIX of a chain whose next step is not `->` (`sprite->unk_0C.at00.v = 0x80;`): the prefix's
    value is a struct, a union or an array, so the temporary is a COPY - a store into it never
    reaches the row's object and a read of it is a block copy into a new stack slot
    (`hoist:aggregate-prefix` / `hoist:indexed-prefix`), and the same from the other side when a
    FULL chain's last member, indexed element or cast type is an aggregate in the row's own
    declarations (`hoist:aggregate-member` / `-element` / `-cast`; the compile oracle in
    `work/native_lane/r33_catalog/scratch/aggregate_oracle.py` measures what the text still misses:
    1 instance in 15,359, a member whose struct is declared in `include/`);
  * a sub-expression that READS MEMORY in a statement holding a call it is not inside
    (`x = f() + p->a;`): the hoist moves the load across the call, which is the very thing the
    forward move refuses as `inline:call-between` (`hoist:call-in-statement`) - an INDIRECT call
    (`D_800294B8[i](x)`), which `varset.CALL_RE` cannot see, counts as a call;
  * `sizeof(...)`: a compile-time constant turned into a runtime value makes gcc's inline block copy
    a real `jal memcpy` - a different mechanism under this kind's name (`hoist:sizeof-in-expr`);
  * ANY text that carries a live pin: `pin_census.sites_of(text)` non-empty refuses every kind
    (`<kind>:text-is-pinned`), and no candidate may add, drop or reword a pin line
    (`<kind>:edits-a-pin`) - a local used inside `ASM_KEEP(...)` is renamed by varset's rename
    otherwise, which rewrites the ARGUMENT OF A PIN;
  * an expression naming a variable declared in a NESTED block: `__typeof__` sits in the function's
    declaration block, where that name does not exist (`hoist:names-a-block-local`);
  * `p++` on a retyped pointer: `((S *)p)++` is not an lvalue, and the assignment spelling
    (`p = (S *)p + 1;`) is a SECOND move confounded into the fingerprint (`pointer-incdec`);
  * `p - q` between two pointers, whose difference scales by the pointee (`pointer-difference`);
  * a loop body with `break`/`continue` (they would bind to the loop the rewrite creates), a body that
    declares variables, a top test with an `else` arm (the arm would land outside the loop), and a
    region holding a label, a `case` or a directive line;
  * a `volatile` sub-expression: `__typeof__` keeps the qualifier, so the temporary would be a
    volatile local - scaffolding, whoever wrote the word (`hoist:volatile-in-expr`).

A bit-field member is NOT refused textually: `__typeof__` of a bit-field is a gcc error, so the
instance is enumerated and the COMPILE refuses it - one `nobuild` record, which is what the
measurement wants to see.

Placement note: the temporary is declared as the LAST declaration of the function's declaration block,
not the first.  `__typeof__(EXPR)` at the top of the block cannot name a local that the same block
declares below it; declaration ORDER is itself a lever (t53's decl swap), so `params["decl_pos"]`
records the spelling used and the first-position variant is a widening, not a silent choice.
"""
import collections
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
if str(ROOT / "tools/xform") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools/xform"))

from pin_census import sites_of as _pin_sites                  # noqa: E402
from xform import varset as V                                  # noqa: E402
from xform.t12_stmtorder import depths, is_decl                # noqa: E402
from xform.t36_paramwidth import functions as _fn_defs         # noqa: E402
from xform.t69_prologue import _mask                           # noqa: E402

ID = r"[A-Za-z_]\w*"
MAX_PER_FN = 6                 # instances per function per kind
MAX_PER_STMT = 2               # hoist instances taken from one statement
NOT_A_TYPE = {"void", "char", "u8", "s8", "unsigned char", "signed char", "M2C_UNK8"}
KEYWORDS = V.C_KEYWORDS | {"NULL", "typeof", "__typeof__"}


class Detail(collections.Counter):
    """A skips counter that also keeps `(refusal, what)` pairs (t69_prologue.Detail's shape)."""

    def __init__(self, *a, **k):
        super().__init__(*a, **k)
        self.detail = []


def _note(detail, key, what=None):
    """Count one refusal; a `Detail` also remembers what it was about.  A plain Counter works."""
    if detail is None:
        return
    detail[key] += 1
    rec = getattr(detail, "detail", None)
    if rec is not None:
        rec.append((key, what))


def _counter(detail):
    return detail if detail is not None else collections.Counter()


def _nl(s):
    return s[:-1] if s.endswith("\n") else s


def _indent(s):
    return re.match(r"[ \t]*", s).group(0)


def _first_diff_line(a, b):
    """1-based line where two texts first differ (the generic `site` of a wrapped move)."""
    la, lb = a.split("\n"), b.split("\n")
    for i, (x, y) in enumerate(zip(la, lb)):
        if x != y:
            return i + 1
    return min(len(la), len(lb)) + 1


def _fresh(text, base):
    for k in range(1, 64):
        name = "%s_%d" % (base, k)
        if not re.search(r"\b%s\b" % re.escape(name), text):
            return name
    return None


def _order(out):
    """Deterministic instance order: by site, then by label."""
    out.sort(key=lambda z: (z[0]["site"], z[0]["label"]))
    return out


PIN_TEXT = re.compile(r"\bASM_\w+[ \t]*\(|\b__asm__\b")


def _pin_in_a_body(text):
    """A pin-shaped token INSIDE a function body, on a line that is not a directive.

    Both qualifications are measured, not decorative: 114 population rows carry a file-scope
    `__asm__(".set D_80080000, 0x80080000");` (a symbol address, not a pin) or an
    `extern volatile u32 D_[]  __asm__("D_...");` alias, and 3 more carry the tree's own
    `#define ASM_TAILSLOT_PIN(value) ((void)0)` no-op header line.  Refusing those 122 rows would
    have cost the catalogue 2% of its population for nothing.
    """
    m = _mask(text)
    depth = 0
    for line in m.split("\n"):
        s = line.strip()
        hit = PIN_TEXT.search(line)
        if hit and depth > 0 and not s.startswith("#"):
            return True
        depth += line.count("{") - line.count("}")
    return False


def _pinned(text, kind, detail):
    """A pinned text is never perturbed - by the module, not only by the driver's population rule.

    `usable_locals` refuses a pinned DECLARATION (`asm-reg-decl`), but a local merely USED inside an
    `ASM_KEEP(...)` is not refused: `Fn._build` calls such a line kind `"pin"`, which is neither
    `unknown` nor off-cfg, so a rename walks straight through it and `ASM_KEEP(a)` becomes
    `ASM_KEEP(b)` - the argument of a pin rewritten, which is a different program at the pin.  The
    catalogue population is pin-free by construction, so no such instance ever entered it; the gate
    below makes the rule the MODULE's, for any caller (round 33 review, defect 2).
    """
    try:
        if _pin_sites(text) or _pin_in_a_body(text):
            # `sites_of` is the tree's definition of a LIVE pin (`REG_RE` wants the `register`
            # keyword, and a pin in a port/dead arm compiles to nothing); `_pin_in_a_body` is wider
            # on purpose, so an `ASM_` macro this module does not recognise - the reviewer's
            # `s32 x ASM_REG("a2");`, an unregistered spelling, a pin in a dead arm - refuses the
            # text as well.  Masked, so an `ASM_` inside a COMMENT is not a pin (39 population rows
            # carry `/* UNRESOLVED C shape (pin): ... */`).
            _note(detail, "%s:text-is-pinned" % kind, None)
            return True
    except Exception as e:                                # a parse failure is not a licence to perturb
        _note(detail, "%s:pin-scan-error:%s" % (kind, type(e).__name__), None)
        return True
    return False


def _pin_lines(text):
    """The pin statements of a text, as stripped line texts (the invariant a candidate must keep)."""
    return sorted(l.strip() for l in text.splitlines() if PIN_TEXT.search(l))


def _keeps_pins(pins, cand, kind, detail, what=None):
    """Second line of defence behind `_pinned`: no candidate may add, drop or reword a pin."""
    if _pin_lines(cand) == pins:
        return True
    _note(detail, "%s:edits-a-pin" % kind, what)
    return False


def _match_bracket(s, i, op, cl):
    """Index of the bracket matching s[i] == op, or None."""
    d = 0
    while i < len(s):
        d += (s[i] == op) - (s[i] == cl)
        if d == 0:
            return i
        i += 1
    return None


# =============================================================================== hoist

CONTROL_HEAD = re.compile(r"^(?:\}?\s*else\b|if\b|for\b|while\b|switch\b|do\b)")
FNPTR_DECL = re.compile(r"^[ \t]*(?:%s[ \t]+)+\([ \t]*\*[ \t]*%s[ \t]*\)[ \t]*\(" % (ID, ID))


FIRST_TOKEN = re.compile(r"[ \t]*(?:(?:register|static|const|volatile|struct|union|enum|unsigned"
                         r"|signed|long|short)[ \t]+)*(%s)" % ID)


def _declaration_line(s, tds=()):
    """Any declaration spelling: `varset.DECL_RE`, a leading type word, a function pointer.

    Two traps, both measured: `void (*next_callback)(void) = state->unk6C;` matches none of
    `DECL_RE`'s declarator shapes (the chain scanner hoisted `*next_callback` out of its own
    declarator), and `DECL_RE` splits ONE identifier into a type and a declarator - `effect =
    func_7003CF18(0x12);` reads as the type `effe` declaring `ct`, and `D_800CF828[0] = 1;` as
    `D_800C` declaring the array `F828`.  So the base must be the line's first whole token AND a
    type name (`varset._is_typename`, the test `Fn._declarations` makes and `DECL_RE` does not).
    """
    m = V.DECL_RE.match(s)
    if m:
        first = FIRST_TOKEN.match(s)
        if (first and first.group(1) == m.group("base") and m.group("base") not in V.STMT_KEYWORDS
                and m.group("var") not in KEYWORDS and V._is_typename(m.group("base"), tds)):
            return True
    return is_decl(s) or bool(FNPTR_DECL.match(s))


def _prev_body_line(ml, k, lo):
    j = k - 1
    while j >= lo and not ml[j].strip():
        j -= 1
    return j if j >= lo else None


def _braceless_head(ml, k, lo):
    """True when the previous non-blank body line is a control head WITHOUT its `{`.

    `varset._classify` calls such a head `unknown`, so the statement under it is an ordinary `stmt`
    node; a line inserted before it would become the arm and take the statement out of it.
    """
    j = _prev_body_line(ml, k, lo)
    if j is None:
        return False
    s = ml[j].strip()
    return bool(CONTROL_HEAD.match(s)) and not s.endswith("{")


def _complete_statement(ml, k, lo):
    """True when line k is a whole statement: nothing is inserted into a multi-line one."""
    s = ml[k]
    if s.count("(") != s.count(")") or s.count("[") != s.count("]"):
        return False
    j = _prev_body_line(ml, k, lo)
    if j is None:
        return True                                    # the first body line
    return ml[j].rstrip().endswith((";", "{", "}", ":"))


def _base_spans(s):
    """Primary expressions a postfix chain can hang off: a name, or a parenthesised group."""
    out = []
    for m in re.finditer(ID, s):
        a = m.start()
        if a and (s[a - 1].isalnum() or s[a - 1] == "_"):
            continue
        pre = s[:a].rstrip()
        if pre.endswith(("->", ".", "&")) or m.group(0) in KEYWORDS:
            continue
        if re.match(r"\s*\(", s[m.end():]):
            continue                                   # a call name, not a value
        out.append((a, m.end()))
    for i, c in enumerate(s):
        if c != "(":
            continue
        pre = s[:i].rstrip()
        if pre and (pre[-1].isalnum() or pre[-1] == "_"):
            continue                                   # a call's argument list
        j = _match_bracket(s, i, "(", ")")
        if j is not None and not V.CAST_RE.fullmatch(s[i:j + 1]):
            out.append((i, j + 1))
    return sorted(set(out))


def _chain_spans(s):
    """[(a, b, cls, chain_end)] for every postfix chain and its prefixes.

    `chain_end` is where the MAXIMAL chain off the same base ends.  A prefix of a chain that is
    written to (`sprite->unk_0C.at00.v = 0x80;`) may not be hoisted: `hoisted_1 = sprite->unk_0C.at00;`
    followed by `hoisted_1.v = 0x80;` stores into the COPY and the real store disappears (measured:
    28 of the first 100 rows' hoist instances lost an `sb`/`sh`/`sw` that way before this was added).
    """
    out = []
    for a, e in _base_spans(s):
        i, ends = e, []
        while True:
            rest = s[i:]
            mm = re.match(r"\s*(->|\.)\s*(%s)" % ID, rest)
            if mm and not re.match(r"\s*\(", s[i + mm.end():]):
                i += mm.end()
                ends.append((i, "member"))
                continue
            mm = re.match(r"\s*\[", rest)
            if mm:
                j = _match_bracket(s, i + mm.end() - 1, "[", "]")
                if j is None:
                    break
                i = j + 1
                ends.append((i, "array"))
                continue
            break
        for b, cls in ends:
            out.append((a, b, cls, ends[-1][0]))
    return out


def _paren_spans(s):
    """[(a, b)] of every parenthesised group that is neither a call's argument list nor a cast."""
    out = []
    for i, c in enumerate(s):
        if c != "(":
            continue
        pre = s[:i].rstrip()
        if pre and (pre[-1].isalnum() or pre[-1] == "_"):
            continue
        if re.search(r"\bsizeof$", pre):
            continue
        j = _match_bracket(s, i, "(", ")")
        if j is None or V.CAST_RE.fullmatch(s[i:j + 1]):
            continue
        out.append((i, j + 1))
    return out


def _call_arg_spans(s):
    """[(a, b)] of every top-level argument of every call in the line."""
    out = []
    for m in V.CALL_RE.finditer(s):
        i = m.end() - 1
        j = _match_bracket(s, i, "(", ")")
        if j is None:
            continue
        a, d = i + 1, 0
        for k in range(i + 1, j + 1):
            c = s[k]
            if c in "([":
                d += 1
            elif c in ")]":
                if k == j and d == 0:
                    out.append((a, k))
                    break
                d -= 1
            elif c == "," and d == 0:
                out.append((a, k))
                a = k + 1
    trimmed = []
    for a, b in out:
        if not s[a:b].strip():
            continue
        while a < b and s[a] in " \t":
            a += 1
        while b > a and s[b - 1] in " \t":
            b -= 1
        trimmed.append((a, b))
    return trimmed


def _call_spans(s):
    """[(a, b)] of every call in the line, from the callee through its closing `)`.

    `varset.CALL_RE` is a NAME followed by `(`, so it cannot see an INDIRECT call - `fp(n)` through
    a pointer expression (`((Callback *)p)[1](owner)`) or a table (`D_800294B8[i](x)`).  Those are
    added here by their argument list: a `(` whose previous non-space character is `)` or `]` and
    whose preceding group is not a CAST.  The span is the argument list only, so an expression
    inside the CALLEE is treated as crossing the call (it is evaluated before the arguments, and
    hoisting it moves it above any argument that calls something) - the conservative reading.
    """
    out = []
    for m in V.CALL_RE.finditer(s):
        i = m.end() - 1
        j = _match_bracket(s, i, "(", ")")
        if j is not None:
            out.append((m.start(), j + 1))
    for i, c in enumerate(s):
        if c != "(" or not s[:i].rstrip():
            continue
        pre = s[:i].rstrip()
        if pre[-1] not in ")]":
            continue
        k = _match_bracket(s[::-1], len(s) - len(pre), ")" if pre[-1] == ")" else "]",
                           "(" if pre[-1] == ")" else "[")
        if k is not None:
            a = len(s) - k - 1
            if pre[-1] == ")" and V.CAST_RE.fullmatch(s[a:len(pre)]):
                continue                                # `(s32)(x + 1)` is a cast, not a call
        j = _match_bracket(s, i, "(", ")")
        if j is not None:
            out.append((i, j + 1))
    return sorted(set(out))


MEMBER_DECL = re.compile(
    r"(?:^|[;{}])[ \t]*(?P<kw>(?:(?:const|volatile|unsigned|signed|struct|union|enum)[ \t]+)*)"
    r"(?P<base>%s)(?P<stars>(?:[ \t]*\*)*)[ \t]*(?P<var>%s)[ \t]*(?P<arr>\[[^;{}]*\])?[ \t]*(?=[;,])"
    % (ID, ID), re.M)


SCALAR_BASE = re.compile(r"(?:[usf](?:8|16|32|64)|int|char|short|long|float|double|void|signed"
                         r"|unsigned|M2C_UNK\w*)")


def _scalar_base(base):
    """True when the type word names a scalar, so an object of it is not a struct / union."""
    return bool(SCALAR_BASE.fullmatch(base))


def _aggregate_members(text):
    """(value-aggregate, element-aggregate) member names declared by this file's struct bodies.

    `hoisted_1 = src->words;` is not "a member load in a temporary" when `words` is a struct or an
    array: `__typeof__` is right, so the temporary is a whole new stack slot and the residue is a
    `lwl/lwr/swl/swr` BLOCK COPY (round 33 review, defect 3: 496 instances with a `.` after the
    hoisted span, plus full chains like `dst->words = src->words;`).  The member's own declaration
    decides, read from the row's own typedef:

      value-aggregate    `S inner;` / `u8 pad[4];` / `} u;`      - the member IS an aggregate;
      element-aggregate  `S list[4];` / `S *list;`               - `list[i]` is an aggregate.

    A name declared as a plain scalar ANYWHERE in the file is removed from both sets: one member
    name may belong to several structs and the base's type is not readable here, so the ambiguous
    ones are left to the compile rather than refused wholesale.
    """
    m_text = _mask(text)
    aggv, agge, scalar = set(), set(), set()
    for mm in re.finditer(r"\b(?:struct|union)\b[^;{}()]*\{", m_text):
        i = mm.end() - 1
        j = _match_bracket(m_text, i, "{", "}")
        if j is None:
            continue
        body = m_text[i + 1:j]
        for name in re.findall(r"\}[ \t]*(%s)[ \t]*;" % ID, body):
            aggv.add(name)                                # an anonymous struct / union member
        for dm in MEMBER_DECL.finditer(body):
            base, var = dm.group("base"), dm.group("var")
            if base in V.STMT_KEYWORDS or var in KEYWORDS:
                continue
            stars = dm.group("stars").count("*")
            arr, kw = bool(dm.group("arr")), dm.group("kw")
            # a NON-scalar base, not only a typedef this file closes with `} S;`: `Color colors[2];`
            # is declared in a header, and `colors[i]` is the struct copy that survived the first
            # pass (town/func_80816948@55, the one `lwl/lwr/swl/swr` gain left in the population)
            agg_base = not _scalar_base(base) or "struct" in kw or "union" in kw
            if stars == 0 and (arr or agg_base):
                aggv.add(var)
                if arr and agg_base:
                    agge.add(var)                         # `S list[4];`: `list[i]` is a struct too
            elif stars == 1 and agg_base:
                agge.add(var)                             # `S *list;`: `list[i]` is a struct
            else:
                scalar.add(var)
    return aggv - scalar, agge - scalar


FILE_DECL = re.compile(
    r"^[ \t]*(?:(?:extern|static|const|volatile|register|struct|union|enum|unsigned|signed)[ \t]+)*"
    r"(?P<base>%s)(?P<stars>(?:[ \t]*\*)*)[ \t]*(?P<var>%s)[ \t]*(?P<arr>\[[^;]*\])?[ \t]*[;,=]"
    % (ID, ID))
DEREF_CAST = re.compile(r"^\*[ \t]*\([ \t]*(?:(?:struct|union|enum|const|volatile)[ \t]+)*"
                        r"(?P<base>%s)[ \t]*\*[ \t]*\)" % ID)


def _file_scope_aggregates(text):
    """File-scope names whose INDEXED element is an aggregate: `extern RECT D_80025034[2];`.

    The compile oracle (`scratch/aggregate_oracle.py`) found these after the member table was in
    place: a global array of a header-declared struct is not a member of anything, so the struct
    bodies say nothing about it, but the row's own `extern` line does.
    """
    out, depth = set(), 0
    for line in _mask(text).split("\n"):
        if depth == 0 and not line.lstrip().startswith("#"):
            m = FILE_DECL.match(line)
            if m and m.group("base") not in V.STMT_KEYWORDS and m.group("var") not in KEYWORDS \
                    and not _scalar_base(m.group("base")) \
                    and (m.group("arr") or m.group("stars").count("*") == 1):
                out.add(m.group("var"))
        depth += line.count("{") - line.count("}")
    return out


def _hoisted_aggregate(e, aggv, agge, local_agge):
    """The refusal key when the hoisted expression's VALUE is a struct / union / array, else None."""
    m = DEREF_CAST.match(e.strip())
    if m and not _scalar_base(m.group("base")):
        return "hoist:aggregate-cast"      # `*(UA32 *)&D_80080B50` - m2c's unaligned-word idiom
    ms = re.findall(r"(?:->|\.)[ \t]*(%s)" % ID, e)
    if e.rstrip().endswith("]"):                          # the last postfix step is an index
        if ms:
            return "hoist:aggregate-element" if ms[-1] in agge else None
        b = re.match(r"[ \t]*(%s)" % ID, e)
        return "hoist:aggregate-element" if b and b.group(1) in local_agge else None
    if ms and ms[-1] in aggv:
        return "hoist:aggregate-member"
    return None


def _has_top_operator(e):
    """A binary arithmetic / bitwise operator at the top level of `e`."""
    d = 0
    for i, c in enumerate(e):
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
        elif d == 0 and c in "+-*/%&|^<>" and i:
            prev = e[:i].rstrip()
            if prev and (prev[-1].isalnum() or prev[-1] in "_)]"):
                return True
    return False


def _top_comma(e):
    d = 0
    for c in e:
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
        elif c == "," and d == 0:
            return True
    return False


def _expr_ok(e, detail, what):
    """The expression itself must be side-effect free and self-contained."""
    if not e.strip():
        return False
    if V.CALL_RE.search(e):
        _note(detail, "hoist:call-inside", what)
        return False
    if re.search(r"\+\+|--", e):
        _note(detail, "hoist:incdec-inside", what)
        return False
    if re.search(r"(?<![<>!=+\-*/%&|^])=(?!=)", e):
        _note(detail, "hoist:assignment-inside", what)
        return False
    if "?" in e or "&&" in e or "||" in e:
        _note(detail, "hoist:shortcircuit-inside", what)
        return False
    if not re.search(r"[A-Za-z_0-9]", e):
        _note(detail, "hoist:not-an-expression", what)      # `**`: a cast fragment, not a value
        return False
    if re.fullmatch(r"(?:(?:struct|union|enum|const|volatile|unsigned|signed|long|short)\s+)*"
                    r"%s(?:\s*\*)*" % ID, e) and not re.fullmatch(ID, e):
        # `F(object, void **, 8)` - a macro argument that is a TYPE, not an expression
        _note(detail, "hoist:argument-is-a-type", what)
        return False
    if _top_comma(e):
        _note(detail, "hoist:comma-in-expr", what)          # a macro's argument list, not one value
        return False
    if re.search(r"\bsizeof\b", e):
        # `varset.CALL_RE` deliberately excludes `sizeof`, so `memcpy(d, s, sizeof(x))` survived the
        # call screen and `hoisted_1 = sizeof(entries);` turned a COMPILE-TIME constant into a
        # runtime value - gcc's inline block copy then became a real `jal memcpy` (round 33 review,
        # defect 4: 26 instances, town/func_800B5140 at d = 42).
        _note(detail, "hoist:sizeof-in-expr", what)
        return False
    if re.search(r"\bvolatile\b", e):
        # `__typeof__` KEEPS the qualifier, so `__typeof__(*(volatile s32 *)&c) t;` declares a
        # volatile local - scaffolding the contract forbids, even though the word was already in
        # the row.  (Measured before this: 34 such instances, 23 nobuild and 11 invisible.)
        _note(detail, "hoist:volatile-in-expr", what)
        return False
    return True


def _is_lvalue_target(s, a, b, detail, what):
    """The occurrence is written to (`x->f = e`, `x->f += e`, `&x->f`, `x[i]++`)."""
    pre, post = s[:a].rstrip(), s[b:].lstrip()
    if pre.endswith("&") and not pre.endswith("&&"):
        _note(detail, "hoist:address-taken", what)
        return True
    if pre.endswith(("++", "--")) or post.startswith(("++", "--")):
        _note(detail, "hoist:incdec-use", what)
        return True
    if re.match(r"(?:[-+*/%&|^]|<<|>>)?=(?!=)", post):
        _note(detail, "hoist:assignment-target", what)
        return True
    return False


def _one_line(s):
    """A whole one-line declaration: balanced and closed."""
    return (s.rstrip().endswith(";") and s.count("(") == s.count(")")
            and s.count("[") == s.count("]") and s.count("{") == s.count("}"))


def _decl_block_end(fn, tds=()):
    """The body line AFTER which a new declaration may be inserted (the declaration block's end).

    The CONTIGUOUS run of declarations at the top of the body, not the last line `fn.decls` names:
    `varset.DECL_RE` splits `D_800CF828[0] = 1;` into the base `D_800C` and the declarator `F828`
    (`_is_typename` accepts any capitalised word), so a statement at the END of a body could be read
    as a top-level declaration and push the insertion point past real code - 1,821 statements were
    refused as "inside the declaration block" that way (dungeon/func_7FFEDD50 and friends).
    """
    top = min(n.depth for n in fn.nodes)
    last = fn.lo - 1
    for n in fn.nodes:
        if n.depth != top or not _declaration_line(n.masked, tds):
            break
        if not _one_line(n.masked):
            break        # `static void *const labels[] = {` runs on: inserting after it lands
        last = n.line    # inside the initialiser
    return last


def _block_locals(fn):
    """Names declared in a NESTED block: `__typeof__` in the declaration block cannot see them."""
    top = min(n.depth for n in fn.nodes)
    return {v for v, ds in fn.decls.items() if any(d["depth"] > top for d in ds)}


def _hoist_spans(s, detail, fn_name):
    """Every sub-expression of one statement worth hoisting, richest class first, span-deduplicated."""
    spans, seen = [], set()
    for a, b, cls, end in _chain_spans(s):
        if (a, b) not in seen:
            seen.add((a, b))
            spans.append((a, b, cls, end))
    for a, b in _call_arg_spans(s):
        e = s[a:b]
        if (a, b) in seen or re.fullmatch(r"\s*(?:%s|-?\d+|0[xX][0-9A-Fa-f]+)\s*" % ID, e):
            continue
        seen.add((a, b))
        spans.append((a, b, "arg", b))
    for a, b in _paren_spans(s):
        if (a, b) not in seen and _has_top_operator(s[a + 1:b - 1]):
            seen.add((a, b))
            spans.append((a, b, "arith", b))
    m = re.match(r"^\s*(?:return\b|[^=;]*?(?<![<>!=+\-*/%&|^])=(?!=))\s*", s)
    if m and s.rstrip().endswith(";"):
        a, b = m.end(), s.rstrip().rfind(";")
        if b > a and (a, b) not in seen and _has_top_operator(s[a:b]):
            seen.add((a, b))
            spans.append((a, b, "arith", b))
    spans.sort(key=lambda z: (z[0], -z[1]))
    return spans


def _hoist_fn(text, fn, detail, tds=(), aggv=frozenset(), agge=frozenset(), file_agge=frozenset()):
    out = []
    block = _block_locals(fn)
    local_agge = {v for v, ds in fn.decls.items()
                  if any((d["arr"] or d["stars"] == "*") and not _scalar_base(d["base"])
                         for d in ds)}
    local_agge |= {p for p, ty in fn.params            # a parameter is the same question
                   if ty.count("*") == 1 and _type_words(ty)
                   and not _scalar_base(_type_words(ty)[-1])}
    local_agge |= file_agge                           # and a file-scope array of structs
    ins = _decl_block_end(fn, tds)
    ind = _indent(fn.lines[ins]) if ins >= fn.lo else \
        (_indent(next((fn.lines[j] for j in range(fn.lo, fn.hi) if fn.lines[j].strip()), "    ")))
    for n in fn.nodes:
        if len(out) >= MAX_PER_FN:
            _note(detail, "hoist:function-capped", fn.name)
            break
        if n.kind not in ("stmt", "return"):
            continue
        k = n.line
        if fn.pp[k]:
            _note(detail, "hoist:preprocessor-line", fn.name)
            continue
        s, real = fn.m[k], _nl(fn.lines[k])
        if _declaration_line(s, tds):
            _note(detail, "hoist:stmt-is-a-declaration", fn.name)
            continue
        if k <= ins:
            _note(detail, "hoist:inside-the-declaration-block", fn.name)
            continue
        if s.strip().startswith("ASM_"):
            continue
        if "&&" in s or "||" in s or "?" in s:
            _note(detail, "hoist:stmt-has-shortcircuit", fn.name)
            continue
        if _braceless_head(fn.m, k, fn.lo):
            _note(detail, "hoist:braceless-arm", fn.name)
            continue
        if not _complete_statement(fn.m, k, fn.lo):
            _note(detail, "hoist:continuation-line", fn.name)
            continue
        taken = 0
        calls = _call_spans(s)
        for a, b, cls, chain_end in _hoist_spans(s, detail, fn.name):
            if taken >= MAX_PER_STMT or len(out) >= MAX_PER_FN:
                break
            e, real_e = s[a:b].strip(), real[a:b].strip()
            if cls == "arith" and V._wrapped(e):
                # `V._wrapped`, not `startswith("(")`: `(a << 8) | (b & 0xFF)` starts and ends with a
                # parenthesis without being one pair, and stripping it left an unbalanced fragment.
                e, real_e = e[1:-1].strip(), real_e[1:-1].strip()
            what = "%s@%d" % (e[:32], k + 1)
            if not _expr_ok(e, detail, what):
                continue
            if re.fullmatch(r"%s|-?\d+|0[xX][0-9A-Fa-f]+" % ID, e):
                continue                               # a bare name or literal is not a computation
            if _is_lvalue_target(s, a, b, detail, what):
                continue
            if chain_end != b:
                # A PREFIX of a longer chain may be hoisted only when the next step is `->`: the
                # value is then the same POINTER, and the rest of the chain works off the copy
                # exactly as it worked off the original - a write through it included
                # (`a->b->c = 1;`).  A `.` or `[` step means the prefix's value is a struct, a union
                # or an array, so the temporary is a COPY: a write lands in the copy and the real
                # store disappears (`sprite->unk_0C.at00.v = 0x80;`), and a read makes a block copy
                # into a new stack slot where retail had one load (`axis_pos =
                # motion->unk_00.at02_s16.v;`, d = 104).  This subsumes the earlier write-side-only
                # guard (`hoist:prefix-of-an-lvalue`), which the round 33 review broke on the read
                # side: 496 `.`-prefixes and 68 `[`-prefixes, 38 of the latter nobuild.
                nxt = s[b:].lstrip()
                if not nxt.startswith("->"):
                    _note(detail, "hoist:aggregate-prefix" if nxt[:1] == "."
                          else "hoist:indexed-prefix", what)
                    continue
            agg = _hoisted_aggregate(e, aggv, agge, local_agge)
            if agg:
                # the same class from the other side: a FULL chain whose last member is declared a
                # struct / union / array in this file's own typedef (`dst->words = src->words;`)
                _note(detail, agg, what)
                continue
            if V._reads_memory(e) and any(not (ca <= a and b <= cb) for ca, cb in calls):
                # `x = f() + p->a;` -> `hoisted_1 = p->a; x = f() + hoisted_1;` moves a memory READ
                # across a call: the load leaves its place after the `jal` and must live across the
                # call in a callee-saved register (dungeon/func_800B6480@39, d = 118), and for any
                # callee that writes the location it is a different program.  This is the rule the
                # forward move states for itself - `varset._inline_one` bails `inline:call-between`
                # whenever `_reads_memory(rhs)` - carried across the reversal.  A call that ENCLOSES
                # the expression is not crossed (`g(p->a)` stays), a sibling call is.
                _note(detail, "hoist:call-in-statement", what)
                continue
            if {x for x in re.findall(ID, e) if x not in KEYWORDS} & block:
                _note(detail, "hoist:names-a-block-local", what)
                continue
            tmp = _fresh(text, "hoisted")
            if tmp is None:
                _note(detail, "hoist:no-fresh-name", what)
                continue
            inserts = collections.defaultdict(list)
            inserts[ins].append(ind + "__typeof__(%s) %s;" % (real_e, tmp))
            inserts[k - 1].append(_indent(real) + "%s = %s;" % (tmp, real_e))
            cand = V._apply(text, {k: real[:a] + tmp + real[b:]}, (), dict(inserts))
            if cand == text:
                continue
            out.append(({"site": k + 1, "label": "hoist:%s:%s@%d" % (cls, e[:40], k + 1),
                         "expr_class": cls, "expr": real_e, "temp": tmp, "fn": fn.name,
                         "decl_line": ins + 1, "decl_pos": "after_last_decl"}, cand))
            taken += 1
    return out


def hoist(text, detail=None):
    """A side-effect-free sub-expression moved into `__typeof__(EXPR) hoisted_N;` (inline reversed)."""
    if _pinned(text, "hoist", detail):
        return []
    out, seen = [], set()
    tds = V.typedef_names(text)
    aggv, agge = _aggregate_members(text)
    file_agge = _file_scope_aggregates(text)
    pins = _pin_lines(text)
    for fn in V.functions(text, _counter(detail)):
        for params, cand in _hoist_fn(text, fn, detail, tds, aggv, agge, file_agge):
            if cand in seen or not _keeps_pins(pins, cand, "hoist", detail, params["label"]):
                continue
            seen.add(cand)
            out.append((params, cand))
    return _order(out)


# =============================================================================== retype_void

def _pointer_names(fn):
    """Locals and parameters of `fn` whose declared type carries a `*`."""
    out = {v for v, ds in fn.decls.items() if any(d["stars"] for d in ds)}
    return out | {p for p, ty in fn.params if "*" in ty}


def _use_class(s, a, b, ptrs):
    """How the occurrence [a, b) of the pointer is used - what the rewrite must do with it."""
    pre, post = s[:a].rstrip(), s[b:]
    tail = post.lstrip()
    if pre.endswith("&") and not pre.endswith("&&"):
        return "addr"
    if pre.endswith(("++", "--")) or tail.startswith(("++", "--", "+=", "-=")):
        return "incdec"
    if tail.startswith("->") or tail.startswith("["):
        return "typed"
    if pre.endswith("*"):
        q = pre[:-1].rstrip()
        if not q or q[-1] in "(,=+-*/%&|^!~<>?:;[{" or re.search(r"\b(return|sizeof)$", q):
            return "typed"                              # a unary dereference
        return "bare"                                   # a multiplication: the value only
    m = re.match(r"\s*([+-])(?![=+-])", post)
    if m:
        other = re.match(r"\s*[+-]\s*(%s)\b" % ID, post)
        if m.group(1) == "-" and other and other.group(1) in ptrs:
            return "diff"
        return "arith"
    m = re.search(r"([+-])\s*$", pre)
    if m and not pre.endswith(("++", "--")):
        before = pre[:m.start(1)].rstrip()
        if before and (before[-1].isalnum() or before[-1] in "_)]"):
            other = re.search(r"(%s)\s*[+-]\s*$" % ID, pre)
            if m.group(1) == "-" and other and other.group(1) in ptrs:
                return "diff"
            return "arith"
    return "bare"


def _retype_uses(fn, v, T, decl_line, decl_var_span, detail, what):
    """Line edits that put `((T *)v)` at every use of `v` that needs the type (None = refused)."""
    ptrs = _pointer_names(fn)
    cast = "((%s *)%s)" % (T, v)
    edits, typed = {}, 0
    for k in range(fn.lo, fn.hi):
        spans = V.occ_spans(fn.m[k], v)
        if not spans:
            continue
        if fn.pp[k]:
            _note(detail, "retype_void:use-in-preprocessor-arm", what)
            return None
        real = _nl(fn.lines[k])
        for a, b in reversed(spans):
            if k == decl_line and a == decl_var_span[0]:
                continue                                # the declarator itself
            cls = _use_class(fn.m[k], a, b, ptrs)
            if cls in ("addr", "incdec", "diff"):
                _note(detail, {"addr": "retype_void:address-taken",
                               "incdec": "retype_void:pointer-incdec",
                               "diff": "retype_void:pointer-difference"}[cls], what)
                return None
            if cls == "bare":
                continue                                # `void *` converts silently under -w
            real = real[:a] + cast + real[b:]
            typed += 1
        if real != _nl(fn.lines[k]):
            edits[k] = real
    if not typed:
        _note(detail, "retype_void:no-use-needing-the-type", what)
        return None
    return edits, typed


def _type_words(decl_text):
    return [w for w in decl_text.replace("*", " ").split() if w not in ("register", "static")]


def _typable(words, stars, tds, detail, what):
    if stars != 1 or not words:
        _note(detail, "retype_void:not-a-single-pointer", what)
        return False
    if " ".join(words) in NOT_A_TYPE or words[-1] in NOT_A_TYPE:
        _note(detail, "retype_void:already-untyped", what)
        return False
    if any(w in ("const", "volatile") for w in words):
        _note(detail, "retype_void:qualified-type", what)
        return False
    if not V._is_typename(words[-1], tds):
        _note(detail, "retype_void:not-a-type-name", what)
        return False
    return True


def _has_prototype(masked, dep, name):
    for m in re.finditer(r"\b%s\s*\([^;{}()]*\)\s*;" % re.escape(name), masked):
        if dep[m.start()] == 0:
            return True
    return False


def retype_void(text, detail=None):
    """`S *p` declared `void *p`, with `((S *)p)` at every use that needs the type."""
    if _pinned(text, "retype_void", detail):
        return []
    out, seen = [], set()
    pins = _pin_lines(text)
    masked = _mask(text)
    dep, d = [], 0
    for ch in masked:
        dep.append(d)
        d += (ch == "{") - (ch == "}")
    dep.append(d)
    tds = V.typedef_names(text)
    for name, params, b0, b1 in _fn_defs(text):
        try:
            fn = V.Fn(text, name, params, b0, b1)
        except Exception as e:
            _note(detail, "retype_void:fn-parse-error:" + type(e).__name__, name)
            continue
        if not fn.ok:
            _note(detail, "retype_void:fn-refused:" + str(fn.reason), name)
            continue
        made = 0
        for v, d0 in sorted(V.usable_locals(fn, _counter(detail), allow_init=True).items(),
                            key=lambda z: z[1]["line"]):
            if made >= MAX_PER_FN:
                _note(detail, "retype_void:function-capped", name)
                break
            if not d0["stars"]:
                continue
            what = "%s:%s" % (name, v)
            words = _type_words(d0["decl_text"])
            if not _typable(words, len(d0["stars"]), tds, detail, what):
                continue
            T = " ".join(words)
            dm = V.DECL_RE.match(fn.m[d0["line"]])
            got = _retype_uses(fn, v, T, d0["line"], (dm.start("var"), dm.end("var")), detail, what)
            if got is None:
                continue
            edits, typed = got
            cur = edits.get(d0["line"], _nl(fn.lines[d0["line"]]))
            # the storage class is REBUILT, so every word of it has to be carried: `_type_words`
            # strips `static` as well as `register`, and only `register` was restored, so
            # `static S *p;` came back as `void *p;` - automatic storage where the row had static
            # (round 33 review, defect 5; population 0, a defect with an empty population).
            keep = ("static " if re.search(r"\bstatic\b", d0["decl_text"]) else "") \
                + ("register " if d0["register"] else "")
            edits[d0["line"]] = (cur[:dm.start("prefix")] + keep + "void *" + cur[dm.start("var"):])
            cand = V._apply(text, edits)
            if cand == text or cand in seen \
                    or not _keeps_pins(pins, cand, "retype_void", detail, what):
                continue
            seen.add(cand)
            out.append(({"site": d0["line"] + 1, "label": "retype_void:local:%s:%s*>void*" % (v, T),
                         "which": "local", "var": v, "from": T + " *", "to": "void *",
                         "casts": typed, "fn": name}, cand))
            made += 1
        for p, pty, pa, pb in params:
            if made >= MAX_PER_FN:
                break
            if p in fn.decls:
                continue                                # a local of the same name shadows it
            what = "%s:%s" % (name, p)
            words = _type_words(pty)
            if not _typable(words, pty.count("*"), tds, detail, what):
                continue
            if _has_prototype(masked, dep, name):
                _note(detail, "retype_void:param-has-prototype", what)
                continue
            if re.search(r"(?:^|[^\w)\]&])&[ \t]*%s\b" % re.escape(p), masked[b0:b1], re.M):
                _note(detail, "retype_void:address-taken", what)
                continue
            T = " ".join(words)
            got = _retype_uses(fn, p, T, -1, (-1, -1), detail, what)
            if got is None:
                continue
            edits, typed = got
            body = V._apply(text, edits)
            cand = body[:pa] + "void *" + body[pb:]     # the signature edit sits above every body edit
            if cand == text or cand in seen \
                    or not _keeps_pins(pins, cand, "retype_void", detail, what):
                continue
            seen.add(cand)
            out.append(({"site": text.count("\n", 0, pa) + 1,
                         "label": "retype_void:param:%s:%s*>void*" % (p, T),
                         "which": "param", "var": p, "from": T + " *", "to": "void *",
                         "casts": typed, "fn": name}, cand))
            made += 1
    return _order(out)


# =============================================================================== split / merge

def split(text, detail=None):
    """`varset.split_def_candidates` IS this move (one merged lifetime split into two names)."""
    if _pinned(text, "split", detail):
        return []
    out, pins = [], _pin_lines(text)
    try:
        cands = V.split_def_candidates(text, None, _counter(detail))
    except Exception as e:
        _note(detail, "split:error:" + type(e).__name__)
        return []
    for label, cand in cands:
        if cand == text or not _keeps_pins(pins, cand, "split", detail, label):
            continue
        out.append(({"site": _first_diff_line(text, cand), "label": "split:" + label,
                     "move": "split_def", "varset_label": label}, cand))
    return _order(out)


def merge(text, detail=None):
    """`varset.merge_local_candidates` / `merge_param_candidates`: a split lifetime merged back."""
    if _pinned(text, "merge", detail):
        return []
    out, pins = [], _pin_lines(text)
    for which, f in (("local", V.merge_local_candidates), ("param", V.merge_param_candidates)):
        try:
            cands = f(text, None, _counter(detail))
        except Exception as e:
            _note(detail, "merge:error:%s:%s" % (which, type(e).__name__))
            continue
        for label, cand in cands:
            if cand == text or not _keeps_pins(pins, cand, "merge", detail, label):
                continue
            out.append(({"site": _first_diff_line(text, cand), "label": "merge:" + label,
                         "which": which, "varset_label": label}, cand))
    return _order(out)


# =============================================================================== goto_to_loop

LABEL_LINE = re.compile(r"^(?P<i>[ \t]*)(?P<l>%s)[ \t]*:[ \t]*(?P<br>\{)?[ \t]*$" % ID)
GOTO_LINE = re.compile(r"^[ \t]*goto[ \t]+(?P<l>%s)[ \t]*;[ \t]*$" % ID)
IFGOTO_LINE = re.compile(r"^[ \t]*if[ \t]*\((?P<c>.+)\)[ \t]*goto[ \t]+(?P<l>%s)[ \t]*;[ \t]*$" % ID)
IFOPEN_LINE = re.compile(r"^[ \t]*if[ \t]*\((?P<c>.+)\)[ \t]*\{[ \t]*$")
ELSE_LINE = re.compile(r"^[ \t]*\}[ \t]*else\b")
ANY_GOTO = re.compile(r"(?<![\w.])goto[ \t]+(%s)\b" % ID)
CASE_LINE = re.compile(r"^[ \t]*(?:case\b|default[ \t]*:)")
# `(ID)(?:[ \t]*\*+)?[ \t]+ID` demanded whitespace between the stars and the name, so `S *q;` and
# `s32 *dst;` matched NEITHER branch and a loop body declaring a pointer was not refused (round 33
# review, defect 6: town/func_80811C54 `matrix_outer@298` declares `u8 *reel_strip;`).  The base is
# checked against `_is_typename` as well, so an expression statement (`count * scale;`) is not read
# as a declaration.
DECL_LINE = re.compile(r"^[ \t]*(?:(?:register|const|static|volatile|unsigned|signed|struct|union|enum)[ \t]+)*"
                       r"(%s)(?:[ \t]+|[ \t]*\*+[ \t]*)%s[ \t]*[;=\[,]" % (ID, ID))


def _close_of(ml, dep, k):
    """Line of the `}` that closes the block opened on line k (None when unbalanced)."""
    want = dep[k] + ml[k].count("{") - ml[k].count("}")
    for j in range(k + 1, len(ml)):
        if dep[j] + ml[j].count("{") - ml[j].count("}") < want <= dep[j]:
            return j
    return None


def _region_ok(ml, pp, lo, hi, detail, what, tds=()):
    """The body between the label and the terminator may become a loop body."""
    if not any(ml[j].strip() for j in range(lo, hi + 1)):
        _note(detail, "goto_to_loop:empty-body", what)
        return False
    for j in range(lo, hi + 1):
        s = ml[j].strip()
        if pp[j] or s.startswith("#"):
            _note(detail, "goto_to_loop:directive-in-region", what)
            return False
        if re.search(r"\b(break|continue)\b", s):
            _note(detail, "goto_to_loop:body-has-break-or-continue", what)
            return False
        if CASE_LINE.match(ml[j]):
            _note(detail, "goto_to_loop:region-has-case", what)
            return False
        if LABEL_LINE.match(ml[j]):
            _note(detail, "goto_to_loop:region-has-label", what)
            return False
        m = DECL_LINE.match(ml[j])
        if m and m.group(1) not in V.STMT_KEYWORDS and V._is_typename(m.group(1), tds):
            _note(detail, "goto_to_loop:body-declares", what)
            return False
    return True


def _loop_text(lines, k, end, ind, cond, body, form):
    head = (ind + "do {") if form == "do_while" else (ind + "while (%s) {" % cond)
    tail = (ind + "} while (%s);" % cond) if form == "do_while" else (ind + "}")
    return "".join(lines[:k] + [head + "\n"]
                   + [b if b.endswith("\n") else b + "\n" for b in body]
                   + [tail + "\n"] + lines[end + 1:])


def _terminator(ml, dep, k, hi, L, g, braced, detail, what):
    """(form, cond, body_lo, body_hi, region_end, indent) for label L's backward goto, or None.

    The indent is the one of the `if` line the shape is built round - the statement column of the
    loop - not the label's, which m2c writes at column 0."""
    if braced:
        c = _close_of(ml, dep, k)
        if c is None:
            _note(detail, "goto_to_loop:unbalanced-label-block", what)
            return None
        t = next((j for j in range(c + 1, hi + 1) if ml[j].strip()), None)
        m = IFGOTO_LINE.match(ml[t]) if t is not None else None
        if m is None or m.group("l") != L or dep[t] != dep[k]:
            _note(detail, "goto_to_loop:no-terminator", what)
            return None
        return "do_while", m.group("c").strip(), k + 1, c - 1, t, _indent(ml[t])
    nxt = next((j for j in range(k + 1, hi + 1) if ml[j].strip()), None)
    mo = IFOPEN_LINE.match(ml[nxt]) if nxt is not None else None
    if mo and dep[nxt] == dep[k]:                       # t41b's shape: a top test round the body
        c = _close_of(ml, dep, nxt)
        # `_close_of` walks past `} else {` (its net brace count is 0), so the region would take the
        # else arm with it and the rewrite would emit `while (C) { A } else { B }`.
        if c is not None and any(ELSE_LINE.match(ml[j]) and dep[j] == dep[nxt] + 1
                                 for j in range(nxt + 1, c)):
            _note(detail, "goto_to_loop:top-test-has-an-else", what)
            c = None
        last = next((j for j in range(c - 1, nxt, -1) if ml[j].strip()), None) if c else None
        mg = GOTO_LINE.match(ml[last]) if last is not None else None
        if mg and mg.group("l") == L and dep[last] == dep[nxt] + 1 and last > nxt:
            return "while", mo.group("c").strip(), nxt + 1, last - 1, c, _indent(ml[nxt])
    for j in range(k + 1, min(hi, g) + 1):              # t41's shape: the test at the label's depth
        if not ml[j].strip() or dep[j] != dep[k]:
            continue
        m = IFGOTO_LINE.match(ml[j])
        if m and m.group("l") == L:
            return "do_while", m.group("c").strip(), k + 1, j - 1, j, _indent(ml[j])
        m = IFOPEN_LINE.match(ml[j])
        if m:
            c = _close_of(ml, dep, j)
            inner = [x for x in range(j + 1, c) if ml[x].strip()] if c is not None else []
            mg = GOTO_LINE.match(ml[inner[0]]) if len(inner) == 1 else None
            if mg and mg.group("l") == L:
                return "do_while", m.group("c").strip(), k + 1, j - 1, c, _indent(ml[j])
    _note(detail, "goto_to_loop:no-terminator", what)
    return None


def _goto_fn(lines, ml, dep, pp, lo, hi, detail, tds=()):
    """Every backward-goto loop of one function body, as a `do`/`while` instance."""
    out = []
    labels, gotos = {}, collections.defaultdict(list)
    for j in range(lo, hi + 1):
        m = LABEL_LINE.match(ml[j])
        if m and m.group("l") not in KEYWORDS:
            labels.setdefault(m.group("l"), []).append(j)
    for j, s in enumerate(ml):
        for m in ANY_GOTO.finditer(s):
            gotos[m.group(1)].append(j)
    for L in sorted(labels, key=lambda x: labels[x][0]):
        if len(out) >= MAX_PER_FN:
            _note(detail, "goto_to_loop:function-capped", L)
            break
        k = labels[L][0]
        what = "%s@%d" % (L, k + 1)
        if len(labels[L]) != 1:
            _note(detail, "goto_to_loop:label-declared-twice", what)
            continue
        gs = gotos.get(L, [])
        if len(gs) != 1:
            _note(detail, "goto_to_loop:label-multi-goto" if gs else "goto_to_loop:label-unused", what)
            continue
        g = gs[0]
        if g <= k:
            _note(detail, "goto_to_loop:goto-from-outside", what)
            continue
        m = LABEL_LINE.match(ml[k])
        got = _terminator(ml, dep, k, hi, L, g, bool(m.group("br")), detail, what)
        if got is None:
            continue
        form, cond, body_lo, body_hi, end, ind = got
        if body_hi < body_lo:
            _note(detail, "goto_to_loop:empty-body", what)
            continue
        if not _region_ok(ml, pp, body_lo, body_hi, detail, what, tds):
            continue
        floor = dep[k] + (1 if (m.group("br") or form == "while") else 0)
        if any(dep[j] < floor for j in range(body_lo, body_hi + 1) if ml[j].strip()):
            _note(detail, "goto_to_loop:body-leaves-the-block", what)
            continue
        body = [_nl(lines[j]) for j in range(body_lo, body_hi + 1)]
        out.append(({"site": k + 1, "label": "goto_to_loop:%s:%s@%d" % (form, L, k + 1),
                     "form": form, "loop_label": L, "cond": cond[:60], "body_lines": len(body)},
                    _loop_text(lines, k, end, ind, cond, body, form)))
    return out


def goto_to_loop(text, detail=None):
    """A backward-goto loop written as `do { } while (C);` / `while (C) { }` (t41 / t41b reversed)."""
    if _pinned(text, "goto_to_loop", detail):
        return []
    tds = V.typedef_names(text)
    pins = _pin_lines(text)
    lines = text.splitlines(True)
    ml = [_nl(x) for x in _mask(text).splitlines(True)]
    ml += [""] * (len(lines) - len(ml))
    dep = depths(ml)
    pp = V.pp_lines(text)
    pp += [True] * (len(lines) - len(pp))
    out, seen = [], set()
    for name, params, b0, b1 in _fn_defs(text):
        lo, hi = text.count("\n", 0, b0) + 1, min(text.count("\n", 0, b1), len(ml) - 1)
        for p, cand in _goto_fn(lines, ml, dep, pp, lo, hi, detail, tds):
            if cand == text or cand in seen \
                    or not _keeps_pins(pins, cand, "goto_to_loop", detail, p["label"]):
                continue
            seen.add(cand)
            p["fn"] = name
            out.append((p, cand))
    return _order(out)


# =============================================================================== the menu

PERTURBATIONS = [
    ("hoist", hoist),
    ("retype_void", retype_void),
    ("split", split),
    ("merge", merge),
    ("goto_to_loop", goto_to_loop),
]
KINDS = [k for k, _ in PERTURBATIONS]


def perturbations(text, detail=None):
    """[(kind, params, new_text)] for every kind, in menu order (a convenience for a driver)."""
    out = []
    for kind, f in PERTURBATIONS:
        try:
            got = f(text, detail)
        except Exception as e:                    # one kind's bug costs only its own instances
            _note(detail, "error:%s:%s" % (kind, type(e).__name__))
            continue
        for params, cand in got:
            out.append((kind, params, cand))
    return out
