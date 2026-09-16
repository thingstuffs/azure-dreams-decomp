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
from xform.t12_stmtorder import depths, is_decl, movable       # noqa: E402
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


# A temporary declared `__typeof__(EXPR) name;` - what hoist / cond_temp themselves write.  Without
# this the declaration-block scanner read a first hoist's temporary as a STATEMENT, so a second
# hoist / cond_temp on that text declared its temporary above a statement (hoist>hoist 26% NOBUILD,
# cond_temp>cond_temp 35% in the round-33 two-move catalogue).
TYPEOF_DECL = re.compile(r"^[ \t]*__typeof__[ \t]*\(.*\)[ \t]*(?:\*[ \t]*)*[A-Za-z_]\w*"
                         r"(?:\[[^\]\n]*\])*[ \t]*(?:=[^;\n]*)?;[ \t]*$")


def _declaration_line(s, tds=()):
    """Any declaration spelling: `varset.DECL_RE`, a leading type word, a function pointer, or a
    `__typeof__(EXPR) name;` temporary (`TYPEOF_DECL`).

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
    return is_decl(s) or bool(FNPTR_DECL.match(s)) or bool(TYPEOF_DECL.match(s))


MASKED_COMMENT = re.compile(r"^[ \t]*(?:/\*[ \t*]*\*/|//[ \t]*)+[ \t]*$")


def _prev_body_line(ml, k, lo):
    """The previous line that carries CODE: a blank line and a comment-only line are both skipped.

    `_mask` blanks a comment's TEXT but keeps its `/*` and `*/`, so a line holding only
    `/* UNRESOLVED C shape (pin): ... */` used to read as the previous statement - it does not end
    in `;`, `{`, `}` or `:`, so `_complete_statement` called the line under it a continuation and
    refused it.  Measured on dungeon/func_8008FF58, whose duplicated arm tail sits under exactly
    such a note (the oracle lost that row's exact hit to it), and on the population: 39 population
    rows carry a note line directly above a statement.
    """
    j = k - 1
    while j >= lo and (not ml[j].strip() or MASKED_COMMENT.match(ml[j])):
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


ASSIGN_OP = re.compile(r"(?<![<>!=+\-*/%&|^])=(?!=)")


def _rest_side_effect_free(rest, detail, what, kind):
    """The expression AROUND the hoisted span must have no side effect of its own.

    Round-33 review, defect 2.  PLACEMENT settles a store BETWEEN the insertion point and the
    statement - the assignment goes immediately before it - and settles NOTHING about a store
    INSIDE the same expression: `if ((p->a = n) > q->a)` hoisting `q->a` puts its load BEFORE the
    store to `p->a`, and `x = p->a++ + q->b;` hoisting `q->b` puts its load before the increment.
    `_expr_ok` is applied to the hoisted span only, so it never saw either.

    The remainder is a FRAGMENT, not an expression (`if (( = n) > ` with the span cut out), so it
    is NOT put through `_expr_ok`, whose well-formedness rules - not-an-expression, a bare type, a
    top-level comma - would refuse almost every fragment.  Only the two side-effect forms are
    looked for.  A call is deliberately NOT one of them: the contract's rule is a memory read moved
    across a call and `hoist`/`cond_temp` already carry it by name (`call-in-condition`,
    `hoist:call-between`), which permits a pure-local operand to move where a blanket call guard
    would not.
    """
    if re.search(r"\+\+|--", rest):
        _note(detail, kind + ":side-effect-elsewhere-in-the-expression", what)
        return False
    if ASSIGN_OP.search(rest):
        _note(detail, kind + ":side-effect-elsewhere-in-the-expression", what)
        return False
    return True


def _stmt_rest(s, a, b):
    """The statement with the span cut out AND its own top-level `=` blanked.

    `x = p->a + q->b;` is an assignment, so the bare remainder would always read as a side effect;
    but the store to `x` happens AFTER the whole right-hand side is evaluated and the temporary is
    assigned before the statement, so that one operator is never crossed.  Every OTHER `=` is
    (`x = (p->a = n) + q->b;`), and so is an `++` anywhere - in the left-hand side included
    (`t[i++] = p->a;`).
    """
    rest = s[:a] + s[b:]
    m = ASSIGN_OP.search(rest)
    if m and rest.count("(", 0, m.start()) == rest.count(")", 0, m.start()):
        rest = rest[:m.start()] + " " + rest[m.end():]
    return rest


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


DECLARED_NAME = re.compile(
    r"^[ \t]*(?:(?:register|static|const|volatile|struct|union|enum|unsigned|signed|long|short)"
    r"[ \t]+)*%s(?:[ \t]+|[ \t]*\*+[ \t]*)(?P<var>%s)[ \t]*(?:\[|=|;|,)" % (ID, ID))


def _later_locals(fn, ins, tds=()):
    """Names DECLARED below the insertion point `ins` - `__typeof__` there cannot see them.

    `_decl_block_end` returns `fn.lo - 1` whenever the body's FIRST line is not a one-line
    declaration - a `static void *const state_labels[] = {` jump-table keep, or any multi-line
    initialiser - and the temporary is then declared ABOVE every local of the function.  45 of the
    whole-population run's 45 `cond_temp` nobuild instances (town/func_800C1FCC@68 and friends).
    `_block_locals` does not catch them: the declarations are at the block's own depth, just later.

    The scan is TEXTUAL rather than `fn.decls`-based on purpose: `varset.Fn` does not record a
    `static const s32 tbl[] = {` at all (it is an array and its line is not simple), so a
    `fn.decls`-only test left `__typeof__(tbl[0])` declared above `tbl` itself.
    """
    out = set()
    for v, ds in fn.decls.items():
        if all(d["line"] > ins for d in ds):
            out.add(v)
    for j in range(max(ins + 1, fn.lo), fn.hi):
        if _declaration_line(fn.m[j], tds):
            m = DECLARED_NAME.match(fn.m[j])
            if m and m.group("var") not in KEYWORDS:
                out.add(m.group("var"))
    return out


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
    block = block | _later_locals(fn, ins, tds)  # the same shape as cond_temp's, same guard
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
            if not _rest_side_effect_free(_stmt_rest(s, a, b), detail, what, "hoist"):
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


SCALAR_SIZE = {"u8": 1, "s8": 1, "char": 1, "M2C_UNK8": 1,
               "u16": 2, "s16": 2, "short": 2, "M2C_UNK16": 2,
               "u32": 4, "s32": 4, "int": 4, "long": 4, "f32": 4, "float": 4, "M2C_UNK32": 4,
               "u64": 8, "s64": 8, "f64": 8, "double": 8}
STRUCT_BODY = re.compile(r"\btypedef[ \t]+struct(?:[ \t]+(?P<tag>%s))?[ \t]*\{" % ID)
UNK_MEMBER = re.compile(r"^unk_(?P<off>[0-9A-Fa-f]+)$")


def _struct_offsets(text):
    """{struct name: {member: (offset, type spelling)}} for the row's OWN m2c typedefs.

    m2c writes a row's structures as a run of `u8 pad_XX[0xN];` fillers and `TYPE unk_XX;` members
    where XX IS the member's hex offset, so the layout is readable from the text without any header.
    The offsets are nevertheless WALKED (natural MIPS alignment: 1 / 2 / 4 / 4 for a pointer / 8),
    and a member named `unk_XX` whose walked offset is not 0xXX makes the WHOLE struct unreadable -
    the walk is the cross-check on the name, not the other way round.  So is any member this code
    cannot size: a nested struct or union, a typedef'd field, a bit-field, a flexible array.
    """
    m_text = _mask(text)
    out = {}
    for mm in STRUCT_BODY.finditer(m_text):
        i = mm.end() - 1
        j = _match_bracket(m_text, i, "{", "}")
        if j is None:
            continue
        names = [mm.group("tag")] if mm.group("tag") else []
        tail = re.match(r"[ \t]*(%s)[ \t]*;" % ID, m_text[j + 1:])
        if tail:
            names.append(tail.group(1))
        body = m_text[i + 1:j]
        if "{" in body or "}" in body or ":" in body:
            continue                                   # a nested struct / union or a bit-field
        off, members, ok = 0, {}, True
        for part in body.split(";"):
            if not part.strip():
                continue
            dm = re.fullmatch(r"[ \t\n]*(?P<kw>(?:(?:const|volatile|unsigned|signed)[ \t]+)*)"
                              r"(?P<base>%s)(?P<stars>(?:[ \t]*\*)*)[ \t]*(?P<var>%s)"
                              r"(?P<arr>\[[^\]]*\])?[ \t\n]*" % (ID, ID), part)
            if dm is None:
                ok = False
                break
            stars, base, var = dm.group("stars").count("*"), dm.group("base"), dm.group("var")
            if stars:
                size = align = 4
                ty = base + " " + "*" * stars
            elif base in SCALAR_SIZE:
                size = align = SCALAR_SIZE[base]
                ty = (dm.group("kw") + base).strip()
            else:
                ok = False                             # a typedef'd member: the size is not here
                break
            n = 1
            if dm.group("arr"):
                try:
                    n = int(dm.group("arr")[1:-1].strip(), 0)
                except ValueError:
                    ok = False
                    break
            off += (-off) % align
            um = UNK_MEMBER.match(var)
            if um and int(um.group("off"), 16) != off:
                ok = False                             # the walk and the name disagree
                break
            if n == 1 and not dm.group("arr"):
                members[var] = (off, ty)
            off += size * n
        if ok:
            for nm in names:
                out[nm] = members
    return out


def _offset_uses(fn, v, struct, decl_line, decl_var_span, detail, what, has_u8=True):
    """Line edits that spell every `v->m` as `*(T *)((u8 *)v + 0xNN)` (None = refused)."""
    if not has_u8:
        # The spelling needs the byte type the row does not have.  `dungeon/func_81940F34` never
        # writes `u8` and does not reach the tree's typedefs, so `(u8 *)state` is
        # "`u8' undeclared" - 4 of the 8 remaining nobuild instances of the whole-population run.
        # Substituting `char *` would be a different move under this kind's name.
        _note(detail, "retype_void:offset:row-has-no-u8-type", what)
        return None
    ptrs = _pointer_names(fn)
    edits, typed = {}, 0
    for k in range(fn.lo, fn.hi):
        spans = V.occ_spans(fn.m[k], v)
        if not spans:
            continue
        if fn.pp[k]:
            _note(detail, "retype_void:offset:use-in-preprocessor-arm", what)
            return None
        real = _nl(fn.lines[k])
        for a, b in reversed(spans):
            if k == decl_line and a == decl_var_span[0]:
                continue
            cls = _use_class(fn.m[k], a, b, ptrs)
            if cls in ("addr", "incdec", "diff"):
                _note(detail, {"addr": "retype_void:offset:address-taken",
                               "incdec": "retype_void:offset:pointer-incdec",
                               "diff": "retype_void:offset:pointer-difference"}[cls], what)
                return None
            if cls == "bare":
                continue                                # `void *` converts silently under -w
            mm = re.match(r"[ \t]*->[ \t]*(%s)" % ID, fn.m[k][b:])
            if mm is None:
                # `v[i]` or `*v`: the offset of THAT use is not written in the text, so the
                # spelling cannot be built (the index is a runtime value, the deref has no member).
                _note(detail, "retype_void:offset:use-is-not-a-member", what)
                return None
            member = mm.group(1)
            if member not in struct:
                _note(detail, "retype_void:offset:member-not-in-the-typedef", "%s.%s" % (what, member))
                return None
            end = b + mm.end()
            nxt = fn.m[k][end:].lstrip()
            if nxt[:2] in ("++", "--"):
                # POSTFIX `++` binds tighter than the unary `*`, so `*(s32 *)((u8 *)p + 0x4)++`
                # parses as `*(s32 *)(((u8 *)p + 0x4)++)` - the pointer is incremented and the
                # object is not.  45 of the 49 nobuild instances of the whole-population run.
                _note(detail, "retype_void:offset:member-incdec", "%s.%s" % (what, member))
                return None
            if nxt[:2] == "->" or nxt[:1] in (".", "[", "("):
                # `v->a->b`, `v->a[i]`: the load would have to be parenthesised and the SECOND step
                # respelled too - two moves, and the offset of the second is in another typedef.
                _note(detail, "retype_void:offset:member-use-is-a-chain", "%s.%s" % (what, member))
                return None
            if fn.m[k][:a].rstrip().endswith("&"):
                _note(detail, "retype_void:offset:address-of-member", "%s.%s" % (what, member))
                return None
            off, ty = struct[member]
            # `M2C_UNK *unk_10;` must cast to `M2C_UNK **`, not to `M2C_UNK * *`
            cast = "%s%s*" % (ty, "" if ty.endswith("*") else " ")
            real = real[:a] + "*(%s)((u8 *)%s + 0x%X)" % (cast, v, off) + real[end:]
            typed += 1
        if real != _nl(fn.lines[k]):
            edits[k] = real
    if not typed:
        _note(detail, "retype_void:offset:no-member-use", what)
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
    structs = _struct_offsets(text)
    # `u8` is m2c's byte type and almost every row has it, but a row that neither declares it nor
    # reaches the tree's typedefs cannot carry the `(u8 *)` of an offset load.
    has_u8 = bool(re.search(r"(?<![\w.])u8(?![\w])", _mask(text)))
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
            offs = structs.get(words[-1])
            if offs:
                got2 = _offset_uses(fn, v, offs, d0["line"], (dm.start("var"), dm.end("var")),
                                    detail, what, has_u8)
                if got2 is not None:
                    e2, n2 = got2
                    cur2 = e2.get(d0["line"], _nl(fn.lines[d0["line"]]))
                    keep2 = ("static " if re.search(r"\bstatic\b", d0["decl_text"]) else "") \
                        + ("register " if d0["register"] else "")
                    e2[d0["line"]] = (cur2[:dm.start("prefix")] + keep2 + "void *"
                                      + cur2[dm.start("var"):])
                    c2 = V._apply(text, e2)
                    if c2 != text and c2 not in seen \
                            and _keeps_pins(pins, c2, "retype_void", detail, what):
                        seen.add(c2)
                        out.append(({"site": d0["line"] + 1,
                                     "label": "retype_void:offset:local:%s:%s*>void*" % (v, T),
                                     "which": "local", "var": v, "from": T + " *", "to": "void *",
                                     "spelling": "offset_load", "casts": n2, "fn": name}, c2))
                        made += 1
            elif words[-1] in structs:
                pass
            else:
                _note(detail, "retype_void:offset:typedef-not-readable", what)
            if made >= MAX_PER_FN:
                break
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
            offs = structs.get(words[-1])
            if offs:
                got2 = _offset_uses(fn, p, offs, -1, (-1, -1), detail, what, has_u8)
                if got2 is not None:
                    e2, n2 = got2
                    b2 = V._apply(text, e2)
                    c2 = b2[:pa] + "void *" + b2[pb:]
                    if c2 != text and c2 not in seen \
                            and _keeps_pins(pins, c2, "retype_void", detail, what):
                        seen.add(c2)
                        out.append(({"site": text.count("\n", 0, pa) + 1,
                                     "label": "retype_void:offset:param:%s:%s*>void*" % (p, T),
                                     "which": "param", "var": p, "from": T + " *", "to": "void *",
                                     "spelling": "offset_load", "casts": n2, "fn": name}, c2))
                        made += 1
            elif words[-1] not in structs:
                _note(detail, "retype_void:offset:typedef-not-readable", what)
            if made >= MAX_PER_FN:
                break
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


def _decl_with_init(masked_line):
    """(var, initialiser text) when the line is a one-line declaration WITH an initialiser."""
    m = V.DECL_RE.match(masked_line)
    if not m or not m.group("init"):
        return None
    if m.group("base") in V.STMT_KEYWORDS or m.group("var") in KEYWORDS:
        return None
    return m.group("var"), m.group("init").lstrip("=").strip()


def _line_delta(text, cand):
    """(lines only in `text`, lines only in `cand`), as stripped texts with their multiplicity."""
    a = collections.Counter(l.strip() for l in text.split("\n"))
    b = collections.Counter(l.strip() for l in cand.split("\n"))
    return list((a - b).elements()), list((b - a).elements())


def _block_openers(ml):
    """For every line, the line number of the `{` that opens its innermost enclosing block."""
    out, stack = [], []
    for j, s in enumerate(ml):
        out.append(stack[-1] if stack else -1)
        for ch in s:
            if ch == "{":
                stack.append(j)
            elif ch == "}" and stack:
                stack.pop()
    return out


def _decl_lines(ml, opener, name, tds):
    """{enclosing block opener} for every line that declares `name`."""
    out = set()
    for j, s in enumerate(ml):
        if not _declaration_line(s, tds):
            continue
        m = DECLARED_NAME.match(s)
        if m and m.group("var") == name:
            out.add(opener[j])
    return out


def _merge_same_block(text, label, tds, detail):
    """Guest and host must be declared in the SAME block, not merely at the same depth.

    `varset.merge_local_candidates` refuses a pair whose declarations differ in DEPTH
    (`merge:different-block`), and depth is not block identity: two sibling `if` arms both declare
    at depth 2, and renaming the guest's uses to the host's name then puts a name where it does not
    exist.  cc1 says so - "`enabled' undeclared (first use this function)" on town/func_800A4A8C.

    THIS IS NOT A DEFECT OF `allow_init`: 7 of the 12 merge instances that failed to compile in the
    whole-population run are produced by HEAD's merge at its own default, so the shape predates the
    keyword.  What `allow_init` does is make more locals usable and so expose the shape on 5 more
    pairs, which is why the guard belongs to the caller that turned the keyword on.  The fix in
    varset itself - comparing the enclosing block rather than the depth - is a SECOND varset change
    and out of this task's scope; it is recommended in the report instead.
    """
    if not label.startswith("merge_local:"):
        return True                                       # a parameter is in scope for the body
    pair = label.rsplit(":", 1)[-1]
    if ">" not in pair:
        return True
    guest, host = (x.strip() for x in pair.split(">", 1))
    ml = _mask(text).split("\n")
    opener = _block_openers(ml)
    g, h = _decl_lines(ml, opener, guest, tds), _decl_lines(ml, opener, host, tds)
    if g and h and not (g & h):
        _note(detail, "merge:different-block-same-depth", label)
        return False
    return True


def _merge_init_ok(text, cand, label, detail):
    """No definition may be lost, and no `T x = x;` may be created, by an ALLOW_INIT merge.

    Both failures are properties of `allow_init=True` alone and both are read off the candidate
    itself, so the check cannot drift from what varset actually did:

      * `merge_local:g>h` where `g` is declared `T g = X;` and X is not `h`.  The merge renames g's
        occurrences to h AND DROPS g's declaration line, so the definition `g = X` disappears and
        every renamed use reads whatever `h` last held - a different program (`merge:init-lost`).
        When X IS `h` the deletion is exactly right: `T g = h;` becomes `h = h;`, the self-copy the
        merge already drops, and this is the typed-alias shape the class wants.
      * the other naming direction of the same pair, `merge_local:h>g`, renames the READ of `h`
        inside `T g = h;` and leaves `T g = g;` - a declaration initialised from itself
        (`merge:self-initialised-declaration`).
    """
    removed, added = _line_delta(text, cand)
    pair = label.rsplit(":", 1)[-1]
    if ">" not in pair:
        return True
    guest, host = (x.strip() for x in pair.split(">", 1))
    for line in removed:
        got = _decl_with_init(_mask(line))
        # ONLY the guest's own declaration is a candidate for the loss: every other removed line is
        # a line the rename REWROTE, and its replacement is in `added` with the same initialiser.
        # (Measured: without the `got[0] == guest` test the check also refused 12 honest candidates
        # on dungeon/func_81887480 and dungeon/func_8188D004, whose `void *L5 = source;` is renamed,
        # not dropped - the two rows check V7 reported merge reaching at -51% and -45%.)
        if got and got[0] == guest and got[1] != host:
            _note(detail, "merge:init-lost", "%s [%s]" % (label, line[:48]))
            return False
    for line in added:
        got = _decl_with_init(_mask(line))
        if got and got[0] == got[1]:
            _note(detail, "merge:self-initialised-declaration", "%s [%s]" % (label, line[:48]))
            return False
    return True


def merge(text, detail=None):
    """`varset.merge_local_candidates` / `merge_param_candidates`: a split lifetime merged back.

    Called with `allow_init=True` (round 33: 886 `initialised-decl` refusals in the 1,000-row
    single-move run, 4,958 population-wide, and the oracle's TYPED_ALIAS_INIT_DECL class - 20 rows
    whose m2c target opens the block with `S *alias = obj;` and whose landed text has neither).  The
    two shapes that deletion can break are refused by `_merge_init_ok` from the candidate text.
    """
    if _pinned(text, "merge", detail):
        return []
    out, pins = [], _pin_lines(text)
    tds = V.typedef_names(text)
    for which, f in (("local", V.merge_local_candidates), ("param", V.merge_param_candidates)):
        try:
            cands = f(text, None, _counter(detail), allow_init=True)
        except Exception as e:
            _note(detail, "merge:error:%s:%s" % (which, type(e).__name__))
            continue
        for label, cand in cands:
            if cand == text or not _keeps_pins(pins, cand, "merge", detail, label):
                continue
            if not _merge_same_block(text, label, tds, detail):
                continue
            if not _merge_init_ok(text, cand, label, detail):
                continue
            out.append(({"site": _first_diff_line(text, cand), "label": "merge:" + label,
                         "which": which, "varset_label": label, "allow_init": True}, cand))
    return _order(out)


# =============================================================================== goto_to_loop

LABEL_LINE = re.compile(r"^(?P<i>[ \t]*)(?P<l>%s)[ \t]*:[ \t]*(?P<br>\{)?[ \t]*$" % ID)
GOTO_LINE = re.compile(r"^[ \t]*goto[ \t]+(?P<l>%s)[ \t]*;[ \t]*$" % ID)
IFGOTO_LINE = re.compile(r"^[ \t]*if[ \t]*\((?P<c>.+)\)[ \t]*goto[ \t]+(?P<l>%s)[ \t]*;[ \t]*$" % ID)
IFOPEN_LINE = re.compile(r"^[ \t]*if[ \t]*\((?P<c>.+)\)[ \t]*\{[ \t]*$")
# `} if (COND) goto L;` - t41's own landed spelling, the closing brace and the test on ONE line.
# The line must END at the `;`, so `} if (c) goto L; x = 1;` is not read as a bare terminator.
CLOSE_IFGOTO_LINE = re.compile(
    r"^[ \t]*\}[ \t]*if[ \t]*\((?P<c>.+)\)[ \t]*goto[ \t]+(?P<l>%s)[ \t]*;[ \t]*$" % ID)
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


def _region_ok(ml, pp, lo, hi, detail, what, tds=(), braced=False):
    """The body between the label and the terminator may become a loop body.

    `braced` is the label's OWN brace (`loop_0: {`).  When it is there the region is ALREADY a
    block, so wrapping it in `do { ... } while (C);` re-uses that block and changes no
    declaration's scope - the `body-declares` guard is then measuring nothing and is skipped
    (round 33 oracle, check V5: dungeon/func_8008F15C `u32 slot_base;` and town/func_800BC0D0
    `u8 second_byte = source_record[7];` were refused by it although both labels are written
    `loop_N: {`).  Without the brace the body is a run of statements in the ENCLOSING block and the
    rewrite really would move a declaration into a new scope, so the guard stands there.
    """
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
        if braced:
            continue                       # the region is already a block: no scope to change
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
        same = CLOSE_IFGOTO_LINE.match(ml[c])
        if same is not None and same.group("l") == L:
            # t41's OWN LANDED SPELLING: `} if (COND) goto loop_0;` - the closing brace of the
            # label's block and the backward test on ONE line.  The scan below only ever looked at
            # the FIRST NON-BLANK LINE AFTER `c`, so every t41 / t41c landing read
            # `goto_to_loop:no-terminator` on the very text t41 wrote (round 33 oracle, §3 item 3:
            # 14 of 14 rows, and on 11 of them the loop spelling is the WHOLE residue, d = 5).
            # The region ends AT `c`: `_loop_text` drops line `end` and writes `} while (C);` in
            # its place, which is exactly the brace this line already carries plus the test.
            return "do_while", same.group("c").strip(), k + 1, c - 1, c, _indent(ml[c])
        if not CLOSE_LINE.match(ml[c]):
            # The closing line carries something the rewrite would DELETE: `_loop_text` replaces
            # every line from `k` to `end` with the loop, and `end` is the terminator BELOW `c`, so
            # a statement sharing line `c` disappears silently.  Reached only once the
            # same-line terminator above is not this label's - `} if (i < n) goto skip;` with the
            # real backward goto on the next line - and found by the test that builds exactly that.
            _note(detail, "goto_to_loop:label-block-close-has-a-statement", what)
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
        if not _region_ok(ml, pp, body_lo, body_hi, detail, what, tds, braced=bool(m.group("br"))):
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


# =============================================================================== cond_temp

IF_ANY_LINE = re.compile(r"^(?P<i>[ \t]*)(?P<pre>\}[ \t]*else[ \t]+)?if[ \t]*\(")
LOOP_HEAD_LINE = re.compile(r"^[ \t]*(?:while|for)[ \t]*\(")
FULL_CAST = re.compile(r"^\([ \t]*(?P<t>(?:(?:struct|union|enum|unsigned|signed|const)[ \t]+)*"
                       r"%s(?:[ \t]*\*)*)[ \t]*\)" % ID)


def _cond_span(s):
    """[a, b) of the condition of an `if` line, or None."""
    m = re.match(r"^[ \t]*(?:\}[ \t]*else[ \t]+)?if[ \t]*", s)
    if not m or m.end() >= len(s) or s[m.end()] != "(":
        return None
    j = _match_bracket(s, m.end(), "(", ")")
    return None if j is None else (m.end() + 1, j)


CAST_TAIL_OPS = set("+-*/%&|^<>=!?,~")


def _cast_covers(rest):
    """True when what FOLLOWS a leading cast is one postfix expression - no top-level operator.

    `->` is the one two-character sequence whose characters are operators on their own, so it is
    stepped over; everything inside a bracket is at depth > 0 and does not count.
    """
    i, d = 0, 0
    while i < len(rest):
        c = rest[i]
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
        elif d == 0:
            if rest[i:i + 2] == "->":
                i += 2
                continue
            if c in CAST_TAIL_OPS:
                return False
        i += 1
    return True


def _temp_type(real_e, fn, tds):
    """The temporary's declared type: a full cast's own type where the text spells one.

    `__typeof__(EXPR)` is always CORRECT and the contract allows it, but it is not what m2c writes -
    m2c declares `s32 temp;` - and reach.py's skeleton compares declaration TOKENS, so a
    `__typeof__` temporary can never equal an m2c target under the primary metric (it can only ever
    agree in the type-blind column).  Where the row itself spells the type - the expression is a
    cast, which is m2c's own idiom for a widened load (`((s32)(D_800FE508[1]))`) - that spelling is
    used instead, and `params["type_spelling"]` records which of the two the instance carries.
    """
    e = real_e.strip()
    while V._wrapped(e):
        e = e[1:-1].strip()
    m = FULL_CAST.match(e)
    if m and _cast_covers(e[m.end():]):
        # the cast must COVER the whole expression.  `(s16)a + b` has type `int` by the usual
        # arithmetic conversions, so `s16 t = (s16)a + b;` TRUNCATES, and `(s16)a == 6` is an `int`
        # too - a different declaration than m2c would ever write, under a spelling that was only
        # ever meant to be prettier.  Anything with a top-level operator after the cast falls back
        # to `__typeof__`, which is right by construction.
        words = _type_words(m.group("t"))
        if words and V._is_typename(words[-1], tds) and words[-1] not in ("void",):
            stars = m.group("t").count("*")
            return " ".join(words) + (" " + "*" * stars if stars else ""), "cast"
    return "__typeof__(%s)" % real_e, "typeof"


def _cond_temp_fn(text, fn, detail, tds=()):
    out = []
    ins = _decl_block_end(fn, tds)
    block = _block_locals(fn) | _later_locals(fn, ins, tds)
    ind = _indent(fn.lines[ins]) if ins >= fn.lo else "    "
    for n in fn.nodes:
        if len(out) >= MAX_PER_FN:
            _note(detail, "cond_temp:function-capped", fn.name)
            break
        k = n.line
        s, real = fn.m[k], _nl(fn.lines[k])
        if LOOP_HEAD_LINE.match(s):
            # a `while`/`for` condition is RE-EVALUATED on every trip, so a temporary assigned once
            # before the loop is a different program (and one assigned inside it is a different
            # move: `for (;;) { t = C; if (!t) break; ... }`).  Only an `if` is a single evaluation.
            _note(detail, "cond_temp:loop-condition-re-evaluated", "%s@%d" % (fn.name, k + 1))
            continue
        m = IF_ANY_LINE.match(s)
        if not m:
            continue
        what = "%s@%d" % (fn.name, k + 1)
        if fn.pp[k]:
            _note(detail, "cond_temp:preprocessor-line", what)
            continue
        if m.group("pre"):
            # `} else if (C) {`: the assignment would have to go BEFORE the `if` and there is no
            # statement position there - it is inside the enclosing `else`.
            _note(detail, "cond_temp:else-if", what)
            continue
        if k <= ins:
            _note(detail, "cond_temp:inside-the-declaration-block", what)
            continue
        span = _cond_span(s)
        if span is None or not _complete_statement(fn.m, k, fn.lo):
            _note(detail, "cond_temp:multi-line-condition", what)
            continue
        if _braceless_head(fn.m, k, fn.lo):
            # the `if` is itself the arm of a braceless head: a line inserted before it becomes the
            # arm and takes the `if` out of it (hoist's own `braceless-arm`).
            _note(detail, "cond_temp:braceless-arm", what)
            continue
        ca, cb = span
        cond = s[ca:cb]
        if "&&" in cond or "||" in cond or "?" in cond:
            # only the LEFTMOST operand of a short-circuit is evaluated unconditionally; every other
            # one may never run, so a temporary assigned before the `if` computes what the row did
            # not.  Refused wholesale here, the way `hoist` refuses a short-circuit statement.
            _note(detail, "cond_temp:shortcircuit-in-condition", what)
            continue
        calls = _call_spans(s)
        cands = [(ca, cb, "whole")]
        for a, b, cls, chain_end in _hoist_spans(s, detail, fn.name):
            if ca <= a and b <= cb and (a, b) != (ca, cb) and chain_end == b:
                cands.append((a, b, cls))
        taken = 0
        for a, b, cls in cands:
            if taken >= MAX_PER_STMT or len(out) >= MAX_PER_FN:
                break
            e, real_e = s[a:b].strip(), real[a:b].strip()
            while V._wrapped(e) and V._wrapped(real_e):
                e, real_e = e[1:-1].strip(), real_e[1:-1].strip()
            w2 = "%s:%s" % (e[:32], what)
            if not _expr_ok(e, detail, w2):
                continue
            if re.fullmatch(r"%s|-?\d+|0[xX][0-9A-Fa-f]+" % ID, e):
                continue                                  # a bare name is not a computation
            if _is_lvalue_target(s, a, b, detail, w2):
                continue
            if (a, b) != (ca, cb) and not _rest_side_effect_free(s[ca:a] + s[b:cb], detail, w2,
                                                                "cond_temp"):
                # the condition MINUS this operand.  The whole-condition candidate is covered by
                # `_expr_ok` above; a partial one is not, and `if ((p->a = n) > q->a)` lifted the
                # load of `q->a` above the store to `p->a` (round-33 review, defect 2).
                continue
            if V._reads_memory(e) and any(not (x <= a and b <= y) for x, y in calls):
                # the same rule `hoist` carries from `varset._inline_one`'s `inline:call-between`:
                # `if (f() != p->a)` would put the load of `p->a` BEFORE the call it followed.
                _note(detail, "cond_temp:call-in-condition", w2)
                continue
            if {x for x in re.findall(ID, e) if x not in KEYWORDS} & block:
                _note(detail, "cond_temp:names-a-block-local", w2)
                continue
            tmp = _fresh(text, "cond")
            if tmp is None:
                _note(detail, "cond_temp:no-fresh-name", w2)
                continue
            ty, spelling = _temp_type(real_e, fn, tds)
            inserts = collections.defaultdict(list)
            # m2c writes `s8 *p;`, not `s8 * p;`, and the skeleton compares declaration TOKENS
            inserts[ins].append("%s%s%s%s;" % (ind, ty, "" if ty.endswith("*") else " ", tmp))
            inserts[k - 1].append("%s%s = %s;" % (_indent(real), tmp, real_e))
            cand = V._apply(text, {k: real[:a] + tmp + real[b:]}, (), dict(inserts))
            if cand == text:
                continue
            out.append(({"site": k + 1, "label": "cond_temp:%s:%s@%d" % (cls, e[:40], k + 1),
                         "expr_class": cls, "expr": real_e, "temp": tmp, "fn": fn.name,
                         "type_spelling": spelling, "decl_line": ins + 1}, cand))
            taken += 1
    return out


def cond_temp(text, detail=None):
    """An `if` condition (or one side-effect-free operand of it) computed into a temporary first.

    m2c's own shape - `L3 = D_800FE508[1]; if (L3 < L1)` where the row reads
    `if (((s32)(D_800FE508[1])) < L1)` - and the round-33 oracle's CONDITION_TEMPORARY class, 10
    rows.  `hoist` cannot reach it: it only ever works on a `stmt` or a `return` node, never on a
    condition (report_oracle §3 item 9).  The assignment goes IMMEDIATELY before the `if`, so
    nothing can be moved across a store or a call BETWEEN the two - and that is ALL placement
    settles.  A store INSIDE the condition is a separate question and needs a CHECK, which a
    partial operand now gets (`_rest_side_effect_free`): the round-33 review found
    `if ((p->a = n) > q->a)` lifting the load of `q->a` above the store to `p->a`.
    """
    if _pinned(text, "cond_temp", detail):
        return []
    out, seen = [], set()
    tds = V.typedef_names(text)
    pins = _pin_lines(text)
    for fn in V.functions(text, _counter(detail)):
        for params, cand in _cond_temp_fn(text, fn, detail, tds):
            if cand in seen or not _keeps_pins(pins, cand, "cond_temp", detail, params["label"]):
                continue
            seen.add(cand)
            out.append((params, cand))
    return _order(out)


# =============================================================================== tail_merge

ELSE_OPEN_LINE = re.compile(r"^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$")
CLOSE_LINE = re.compile(r"^[ \t]*\}[ \t]*$")
JUMP_STMT = re.compile(r"^(?:return\b|goto\b|break\b|continue\b)")


def _arm_close(ml, dep, i):
    """Line of the `}` that closes the block opened on line `i`, `} else {` included.

    `_close_of` cannot be used here: its net brace count for `} else {` is 0, so it WALKS PAST the
    line that ends the if arm and returns the end of the else arm instead (the trap the
    `goto_to_loop` top-test scan documents).  A closing line of the block opened at depth `dep[i]`
    is the first later line whose own depth is `dep[i] + 1` and which STARTS with `}` - a nested
    block's closing line sits a level deeper, so it is never taken.
    """
    for j in range(i + 1, len(ml)):
        if dep[j] < dep[i] + 1:
            return None
        if dep[j] == dep[i] + 1 and ml[j].lstrip().startswith("}"):
            return j
    return None


def _else_close(ml, dep, c1):
    """Line of the `}` that closes the else arm opened by `} else {` on line `c1`."""
    for j in range(c1 + 1, len(ml)):
        if dep[j] < dep[c1]:
            return None
        if dep[j] == dep[c1] and ml[j].lstrip().startswith("}"):
            return j
    return None


def _arm_body(ml, lo, hi):
    """The non-blank line numbers of an arm, in order."""
    return [j for j in range(lo, hi + 1) if ml[j].strip()]


def _tail_stmt_ok(ml, dep, j, want_depth, lo, detail, what):
    """One line may be hoisted out of both arms: a simple one-line statement at the arm's own depth."""
    if dep[j] != want_depth:
        _note(detail, "tail_merge:tail-not-at-the-arms-depth", what)
        return False
    if not movable(ml[j]) or is_decl(ml[j]):
        _note(detail, "tail_merge:tail-not-a-simple-statement", what)
        return False
    if not _complete_statement(ml, j, lo):
        # `movable` only asks that the line END in `;`, so the LAST LINE of a multi-line call -
        # `                              sprite->unk_04);` in dungeon/func_800A4710 - passes it and
        # a fragment of a statement was hoisted out of both arms.  (Found by the whole-population
        # compile: 5 of tail_merge's 22 nobuild instances.)
        _note(detail, "tail_merge:tail-is-a-continuation-line", what)
        return False
    return True


def _arm_declared(ml, lo, hi, tds):
    """Names DECLARED inside an arm: a tail that reads one cannot leave the arm's scope."""
    out = set()
    for j in range(lo, hi + 1):
        m = DECL_LINE.match(ml[j])
        if m and m.group(1) not in V.STMT_KEYWORDS and V._is_typename(m.group(1), tds):
            mv = re.match(r"^[ \t]*(?:(?:register|const|static|volatile|unsigned|signed|struct"
                          r"|union|enum)[ \t]+)*%s(?:[ \t]+|[ \t]*\*+[ \t]*)(%s)" % (ID, ID), ml[j])
            if mv:
                out.add(mv.group(1))
    return out


def _common_tail(lines, ml, dep, a_lines, b_lines, want_depth, lo, detail, what):
    """The longest run of trailing lines the two arms spell identically (after their indentation).

    Token-identical after each arm's own indentation, compared on the REAL text (so a comment or a
    different spelling of the same operation is never merged), and every line must be a simple
    one-line statement sitting at the arm's own depth - a nested block's last line is not "the arm's
    tail", and pulling it out of its block would change its scope.
    """
    n = 0
    while n < len(a_lines) and n < len(b_lines):
        ja, jb = a_lines[-1 - n], b_lines[-1 - n]
        if _nl(lines[ja]).strip() != _nl(lines[jb]).strip():
            break
        if not _tail_stmt_ok(ml, dep, ja, want_depth, lo, detail, what) \
                or not _tail_stmt_ok(ml, dep, jb, want_depth, lo, detail, what):
            break
        n += 1
    return n


def _tail_merge_if(lines, ml, dep, pp, i, detail, fn_name, lo=0, tds=()):
    """Every hoistable common tail of ONE `if (..) { } else { }`, longest first."""
    out = []
    what = "%s@%d" % (fn_name, i + 1)
    c1 = _arm_close(ml, dep, i)
    if c1 is None:
        return out
    if not ELSE_OPEN_LINE.match(ml[c1]):
        # `} else if (..) {` has no arm to hoist out of (the tail would have to be repeated in
        # every leg of the chain), and a bare `}` means the `if` has no else at all - the tail then
        # already runs once, unconditionally, and there is nothing to merge.
        _note(detail, "tail_merge:else-if" if re.match(r"^[ \t]*\}[ \t]*else\b", ml[c1])
              else "tail_merge:no-else", what)
        return out
    c2 = _else_close(ml, dep, c1)
    if c2 is None or not CLOSE_LINE.match(ml[c2]):
        _note(detail, "tail_merge:else-arm-not-a-plain-block", what)
        return out
    if any(pp[j] for j in range(i, c2 + 1)):
        _note(detail, "tail_merge:preprocessor-in-the-if", what)
        return out
    want = dep[i] + 1
    a_lines = _arm_body(ml, i + 1, c1 - 1)
    b_lines = _arm_body(ml, c1 + 1, c2 - 1)
    if not a_lines or not b_lines:
        _note(detail, "tail_merge:empty-arm", what)
        return out
    n = _common_tail(lines, ml, dep, a_lines, b_lines, want, lo, detail, what)
    if not n:
        _note(detail, "tail_merge:no-common-tail", what)
        return out
    # A local DECLARED inside an arm dies with the arm: `if (c) { S *state; ...; p->f = state; }
    # else { ...; p->f = state; }` hoisted out puts the store where `state` does not exist
    # (town/func_800B361C, one of the whole-population compile's nobuild instances).
    declared = _arm_declared(ml, i + 1, c1 - 1, tds) | _arm_declared(ml, c1 + 1, c2 - 1, tds)
    ind = _indent(ml[i])
    for take in range(n, 0, -1):
        a_tail, b_tail = a_lines[-take:], b_lines[-take:]
        if declared and any(declared & set(re.findall(ID, ml[j])) for j in a_tail):
            _note(detail, "tail_merge:tail-reads-an-arm-local", what)
            continue
        a_keep, b_keep = a_lines[:-take], b_lines[:-take]
        if not a_keep:
            # hoisting everything out of the IF arm leaves `if (c) { }`; writing the shape the other
            # way round means NEGATING the condition, which is a second move.
            _note(detail, "tail_merge:if-arm-empties", what)
            continue
        for keep in (a_keep, b_keep):
            if keep and JUMP_STMT.match(ml[keep[-1]].strip()):
                # `if (c) { ...; return; stmt } else { stmt }`: the tail is DEAD in that arm, so
                # hoisting it out makes it run where it did not - a different program.
                _note(detail, "tail_merge:jump-before-the-tail", what)
                break
        else:
            drop = set(a_tail) | set(b_tail)
            body = [_nl(lines[j]).strip() for j in a_tail]
            new = lines[:i + 1]
            new += [lines[j] for j in range(i + 1, c1) if j not in drop]
            if b_keep:
                new += [lines[c1]]
                new += [lines[j] for j in range(c1 + 1, c2) if j not in drop]
                new += [lines[c2]]
            else:
                # the ELSE arm is now empty: `} else { }` is scaffolding, so the else goes with it
                # and the `if` closes on the line that carried it.  (This is the shape
                # `t15_shapes.dup_after_if` starts from, so its inverse must reach it exactly.)
                new += [ind + "}\n"]
            new += [ind + s + "\n" for s in body]
            new += lines[c2 + 1:]
            out.append(({"site": i + 1, "fn": fn_name, "n_tail": take,
                         "dropped_else": not b_keep, "tail": body[0][:48],
                         "label": "tail_merge:%d:%s@%d" % (take, body[0][:32], i + 1)},
                        "".join(new)))
    return out


def tail_merge(text, detail=None):
    """The common tail of both arms of an `if`/`else` hoisted out to follow the if once.

    The inverse of `t15_shapes.dup_after_if`, which t61_naturalkeep lands: six of the eight
    duplicated-tail rows of the round-33 oracle are t61 landings (report_oracle §3 item 4).

    ON MEANING.  The tail runs after EITHER arm in both texts, so a variable the two arms assign
    differently is read by the tail with the same value it had before: the arm still runs first and
    still writes its own value, and only ONE arm ever runs.  Nothing is reordered across the store.
    The real traps are elsewhere and each is refused above: a jump before the tail (the tail is dead
    in that arm), an `else if` (the tail would belong to every leg), no else at all (the tail
    already runs once), a tail line that is not a simple statement or does not sit at the arm's own
    depth (pulling it out of a nested block changes its scope), and a preprocessor line anywhere in
    the `if` (the two arms need not exist in the same compilation).
    """
    if _pinned(text, "tail_merge", detail):
        return []
    pins = _pin_lines(text)
    lines = text.splitlines(True)
    ml = [_nl(x) for x in _mask(text).splitlines(True)]
    ml += [""] * (len(lines) - len(ml))
    dep = depths(ml)
    tds = V.typedef_names(text)
    pp = V.pp_lines(text)
    pp += [True] * (len(lines) - len(pp))
    out, seen = [], set()
    for name, params, b0, b1 in _fn_defs(text):
        lo, hi = text.count("\n", 0, b0) + 1, min(text.count("\n", 0, b1), len(ml) - 1)
        made = 0
        for i in range(lo, hi + 1):
            if made >= MAX_PER_FN:
                _note(detail, "tail_merge:function-capped", name)
                break
            if not IFOPEN_LINE.match(ml[i]) or pp[i]:
                continue
            for p, cand in _tail_merge_if(lines, ml, dep, pp, i, detail, name, lo, tds):
                if cand == text or cand in seen \
                        or not _keeps_pins(pins, cand, "tail_merge", detail, p["label"]):
                    continue
                seen.add(cand)
                out.append((p, cand))
                made += 1
                if made >= MAX_PER_FN:
                    break
    return _order(out)


# =============================================================================== dup_tail

def dup_tail(text, detail=None):
    """`t15_shapes.dup_after_if` itself: the statement after an `if` written into BOTH arms.

    The TARGET direction of the same class - on two of the oracle's rows it is the m2c text that
    duplicates the tail and the landed text that holds it once (report_oracle §3 item 4).

    The generator's own four refusals are SILENT (`dup_after_if_candidates` simply `continue`s), so
    they are re-run here and counted; TWO are ADDED, and neither is a widening:
      * `brace-does-not-close-an-if` - the generator matches ANY line that is only `}`, so a
        `while`/`for`/`switch`/function closing brace produced `} else {`, text that does not
        compile.  The catalogue wants a refusal there, not a `nobuild` under this kind's name.
      * `jump-before-the-tail` - the refusal `tail_merge` carries in the other direction, which
        this kind did not carry until the round-33 review named it (defect 1).  An arm that has
        already returned / jumped makes the copy UNREACHABLE: 1,117 of the kind's 2,276 population
        instances were this shape and every one of them was invisible.
    """
    if _pinned(text, "dup_tail", detail):
        return []
    from xform import t15_shapes as T15
    pins = _pin_lines(text)
    lines = text.splitlines(True)
    ml = [_nl(x) for x in _mask(text).splitlines(True)]
    ml += [""] * (len(lines) - len(ml))
    dep = depths(ml)
    out, seen = [], set()
    try:
        cands = T15.dup_after_if_candidates(text)
    except Exception as e:
        _note(detail, "dup_tail:error:" + type(e).__name__)
        return []
    for label, cand in cands:
        i = int(label.rsplit(":", 1)[1]) - 1          # `dup_after_if:<1-based line of the brace>`
        what = "%s@%d" % (_nl(lines[i + 1]).strip()[:32], i + 2)
        head = _if_head_of(ml, dep, i)
        if head is None:
            _note(detail, "dup_tail:brace-does-not-close-an-if", what)
            continue
        j = _prev_body_line(ml, i, head + 1)
        if j is not None and dep[j] == dep[i] and JUMP_STMT.match(ml[j].strip()):
            # `if (c) { ...; return 0; }` followed by `stmt;`: the copy written into the IF arm
            # sits BEHIND the jump and can never run.  The C means the same (which is why all
            # 1,117 such instances compiled) and not one of them changes an instruction - every
            # one measured INVISIBLE, against 57% visible for the rest of the kind.  This is the
            # refusal `tail_merge` carries in the other direction under the same name, and the
            # round-33 review's defect 1 was that the inverse did not carry it.  Only a jump at
            # the ARM's OWN depth is dead: `if (c) { if (d) { return; } }` still falls through.
            _note(detail, "dup_tail:jump-before-the-tail", what)
            continue
        if cand == text or cand in seen or not _keeps_pins(pins, cand, "dup_tail", detail, what):
            continue
        seen.add(cand)
        out.append(({"site": i + 2, "label": "dup_tail:" + what, "brace_line": i + 1,
                     "if_line": head + 1, "stmt": _nl(lines[i + 1]).strip()[:48]}, cand))
    _dup_tail_refusals(lines, ml, dep, detail)
    return _order(out)


def _if_head_of(ml, dep, c):
    """The `if (..) {` line whose block the bare `}` on line `c` closes, or None.

    The block ending at depth `d = dep[c]` was opened EITHER by a head at depth `d - 1` that nets a
    brace (`if (..) {`, `while (..) {`, a function, a bare `{`) OR by a `} else {` line, which sits
    at depth `d` and nets ZERO.  Missing the second case was the whole population's biggest nobuild
    class: the `}` that closes an ELSE arm reported the `if` above it as its head, and the
    generator then wrote `} else { ... } else { ... }` - 278 instances that do not compile
    (main/func_80012030@29, main/func_8000E7D4@25).
    """
    d = dep[c]
    for j in range(c - 1, -1, -1):
        if dep[j] == d and ml[j].lstrip().startswith("}"):
            return None                     # a `} else {`: this brace closes the ELSE arm
        if dep[j] == d - 1:
            return j if IFOPEN_LINE.match(ml[j]) else None
        if dep[j] < d - 1:
            return None
    return None


def _dup_tail_refusals(lines, ml, dep, detail):
    """The generator's four silent `continue`s, re-run and counted (its refusal table)."""
    if detail is None:
        return
    for i in range(len(ml) - 1):
        if not CLOSE_LINE.match(ml[i]):
            continue
        nxt = ml[i + 1]
        what = "@%d" % (i + 2)
        if nxt.strip().startswith("else"):
            _note(detail, "dup_tail:next-line-is-else", what)
        elif is_decl(nxt):
            _note(detail, "dup_tail:next-line-is-a-declaration", what)
        elif not movable(nxt):
            _note(detail, "dup_tail:next-line-not-a-simple-statement", what)
        elif nxt[:len(_indent(ml[i])) + 1] != _indent(ml[i]) + nxt.strip()[0]:
            _note(detail, "dup_tail:statement-not-at-the-braces-indent", what)


# =============================================================================== the menu

PERTURBATIONS = [
    ("hoist", hoist),
    ("retype_void", retype_void),
    ("split", split),
    ("merge", merge),
    ("goto_to_loop", goto_to_loop),
    ("tail_merge", tail_merge),
    ("dup_tail", dup_tail),
    ("cond_temp", cond_temp),
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
