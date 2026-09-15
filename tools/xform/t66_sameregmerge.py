"""T66: two ASM_REG declarations on ONE hard register merged into the surviving variable.

APPEARS
    A row carries two or more `register T v ASM_REG("$N")` declarations naming the SAME hard
    register $N in one function, with disjoint lifetimes.  m2c gives every value its own name, so
    one retail variable that was reused for two successive values comes back as two declarations -
    and each of them needs a pin, because neither value alone asks the allocator for $N.

RESOLVES
    Retail's author reused ONE variable.  Carry the later value in the earlier variable and it
    INHERITS the register through the surviving pin: the erased pseudo is not re-coloured, it stops
    existing, so there is no allocator decision left to go wrong.  That is why erasing the family
    (t62: 0 of 186 rows) and hosting the pinned variable on an unpinned local (natural's
    `host_candidates`) both miss - both of them ask the allocator for a NEW decision; this asks for
    one fewer.

    Measured by the sol pack `work/native_lane/probe4/` (2026-09-15, REPORT.md): 7 of 9 rows exact,
    10 pins.  `dungeon/func_81084D04` (the plain rename), `819602D8` (the cast form across
    `s16 *`/`s32`), `8008F228` (two merges, one of them `s32` into `u8 *`), `809F90DC` (a host
    hoisted to the enclosing loop and reused twice), `8187A9A8`, `80C96F24` and `800A3D40` (two
    arm-local declarations replaced by one in the enclosing block).  The pack's own rule, from
    `80C96F24`: "reuse a value staged directly as call argument N for a later nonoverlapping value
    that retail also keeps in argument register N".

THE FORMS (both directions of every pair are tried: the later value hosted on the earlier variable,
and the earlier hosted on the later one with its declaration moved up)
    rename   identical declared types: V's declaration and pin go, every use of V is written H.
    cast     both word-sized (a pointer and a 32-bit integer, two 32-bit integers of different
             signedness, or two pointer types): V's definitions become `H = (TH)(expr);` and its
             reads `(TV)H`.  A compound assignment or a `v++;` statement is a definition written
             short and is desugared into the same form (`H = (TH)((TV)H >> (5));`).  A narrow type
             (s8/u8/s16/u16/char/short) is REFUSED - the merged variable would change the width of
             the value, which is a different program.  There is NO cast-free spelling: merging two
             integer words of different signedness without casts changes what `>>`, `/`, `%` and a
             relational compare mean, and this generator has no value-range argument to make.
    hoist    H declared in an inner block that does not enclose V: its declaration moves to the
             nearest block enclosing both.  The initialiser rides along only when it is a literal,
             a symbol address or a cast of one AND no use of V sits between the new position and the
             old one (otherwise the hoisted initialiser would clobber the value V is carrying);
             otherwise it stays behind as an ordinary assignment.  Both spellings are emitted when
             both are legal.
    twoarm   the same, for two declarations in the two arms of one if/else or two `case` arms: one
             declaration in the enclosing block, each arm keeping its own assignment.

DISJOINTNESS is decided on a statement-level control-flow graph built from `t51.units()`: labels,
`goto` (computed `goto *` reaches every label), `if`/`else`, `while`/`for`/`do` back edges,
`switch`/`case`, `break`/`continue`, `return`.  A construct this module cannot classify makes every
LATER statement reachable from it, and a write that is not a whole plain `v = ...;` statement does
not kill - both over-approximate liveness, which can only refuse a merge, never allow a wrong one.
Backward liveness then decides interference in the usual way (both live at one point, or one live
where the other is defined), so a variable live around a loop back edge that encloses the other's
lifetime is refused automatically; that case is journaled as `loop-backedge`.

Refusals besides interference: an address-taken variable (`&v`), a variable whose name is also a
label or a called function, an inner-scope local of the same name, a declaration or a mention of
either variable inside ANY preprocessor region of the function (see PREPROCESSOR REGIONS below), a
multi-declarator or array declaration, and any candidate whose surviving pins are not exactly the
input's minus V's (`_expected_pins`).

TWO OPENINGS (2026-09-15, round 29), both behind env switches that default ON.  They reopen the two
largest refusals the round-28 packs measured - `host-name-collision` (141 ordered pairs in 15 rows)
and `in-macro-arg` (183 in 45) - both of which are SPELLING problems, not program problems.

    T66_RENAME_HOST (default 1)
        The host's name means something else in the block the merged declaration would cover (an
        inner local, a sibling declaration of the same name - m2c names every copy of one retail
        variable alike - or a global), so writing V's uses as H would capture.  The merge is retried
        with the SURVIVING variable renamed: to V's own name when that is free in the function, else
        to a fresh `<host>_m` that appears nowhere in the file.  A local's name is byte-neutral on
        this port, and the declaration keeps its type, its register binding and its initialiser.
        Mechanically the rename is a SEPARATE TEXT (`_host_renamed`: every line of `Facts.lines`
        rewritten once, so the masked-position rename is safe even where a line mentions both
        variables) which is then re-parsed and merged by the ordinary path - so every check in this
        module, the collision test included, fires again on the renamed text.  A pair whose rename
        wins is journaled `host-name-collision-reopened`; one that still fails keeps the old
        `host-name-collision` count, so the two columns add up to the round-28 number.
    T66_MACRO_ARGS (default 1)
        A mention of V inside the argument list of an uppercase macro call is renamed like any other
        use.  `ASM_KEEP(V)` becomes `ASM_KEEP(H)`: the pin COUNT is unchanged (`_expected_pins`
        asserts the whole multiset, with V's spelling rewritten) and the keep still keeps the same
        value at the same point, because the value V carried is now in H there.  An argument is a
        VALUE or it is refused; the refusals, every one of them per (macro, argument SLOT):

          `in-macro-arg-stringify`   the slot's parameter is under `#`/`##`.  `_stringify_macros`
            reads every function-like macro in `include/*.h`, `include/records/*.h`, `include/*.inc`
            AND the row's own `#define`s (the slus rows define `U8_AT`/`S16_AT` themselves) and
            finds four in include/: INCLUDE_ASM, INCLUDE_RODATA, ASM_LIVE_SIBCALL_PIN,
            ASM_SHAPE_D_SIBCALL_PIN.
          `in-macro-arg-nameparam`   the slot's parameter is a MEMBER, a TYPE or a TAG rather than a
            value (`_param_name_use`).  `#`/`##` cannot see this class and the first shipping of
            this opening had no test for it: `#define ZONE_OF(F) (D_80024020[zone_id].F)` over a
            pinned local named `flags` renamed the MEMBER READ, and `M2C_FIELD(expr, type_ptr,
            offset)` - in include/, called by 187 rows - renames a CAST TYPE.  Found by review
            2026-09-15; over include/ the class is M2C_FIELD and M2C_BITWISE, and in src/ the three
            `*_ZONE(F)` macros of town/func_8095563C.
          `in-macro-arg-unknown-macro`  a macro-shaped name (`MACROARG_RE`'s class) whose body is
            not in include/ or in the row - its parameter may be any of the above.  Round 28 refused
            every macro argument wholesale, so this is never worse than the baseline.
          `in-macro-arg-argcount`    the call passes more arguments than the definition read here
            declares, so the slot numbers do not line up.
          `in-asm-reg-binding`       a mention inside `ASM_REG(...)`: the pin being deleted or kept,
            never a value.
          `asm-operand-cast`         the CAST form into any `ASM_*` argument - `ASM_KEEP(var)` is
            `__asm__ __volatile__("" : "=r"(var) : "0"(var))`, so `(u8 *)h` there is not an lvalue.

        Every one of those tests reads a WHOLE-TEXT index of macro calls (`_MacroIdx`), not one line:
        until the same review the scan was per line, so a macro argument on a CONTINUATION line was
        invisible to all of them - a stringifier's argument was renamed with nothing journalled.
        Inside a macro argument a cast read is always parenthesised, `((TV)H)`, because the macro
        body decides what binds to it; that too was a per-line test, and it now holds across a line
        break.

PREPROCESSOR REGIONS (2026-09-15, after a review found three landed rows with invalid C in them)
    `pin_census.arm_labels` only recognises `NON_MATCHING` and `#if 0`: every line of an
    `#ifdef __mips__ ... #else ... #endif` block is labelled `both`, so `unscored_text` keeps none
    of it and an edit inside the `#else` arm passes the sweep's "unscored arms unchanged" invariant
    untouched.  That is how `dungeon/func_81856800` landed `u8 *(u8 *)modulo_magic;` in its non-mips
    arm - a cast rewrite applied to the port fallback declaration of the variable being merged.
    This module therefore keeps its OWN region map (`_pp_regions`): every `#if/#ifdef/#ifndef/
    #elif/#else/#endif` directive line and every line under one, whatever the condition says.  A
    pair is refused when either declaration or any mention of either variable is in a region
    (`pp-guarded-mention`), a hoist is refused when it would move a declaration into or out of one
    (`pp-guarded-anchor`), and `_pp_sig` - the text of every guarded line, in order - must be
    IDENTICAL in the candidate.  `Flow` also marks every guarded node unknown, because the two arms
    of a region are not the sequential statements the CFG would otherwise read them as.

Every candidate is screened with `xform.screen.compile_s`/`sdiff` against the CURRENT pinned text's
listing - both compile at the row's own cell, and the candidate already has one pin fewer, so
nothing is erased separately - and `vf` is called ONLY on distance-0 candidates that pass
`pin_search_engine.improves`.  Budgets `T66_SCREENS` (200) and `T66_VERIFY` (6) per row; after a win
the search restarts on the new text, because the family has shrunk and more pairs may fall.

`sameregmerge_candidates(text)` exposes the same rewrites as a search menu (<= 48, nearest pairs
first).  No scaffolding is ever emitted: this generator only deletes a declaration, moves a
declaration, renames a local, and respells the uses of the variable it deleted.

RESULT
    round 28 (`work/native_lane/r28_samereg/`): 238 pins from 127 rows in a two-minute sweep; the
        two evaluation packs left `in-macro-arg` 183 and `host-name-collision` 141 ordered pairs
        refused, over 45 and 15 rows.
    round 29 (`work/native_lane/r29_samereg2/REPORT.md`, the two openings above): 131 pins from 68
        of those 110 rows, where the round-28 generator offered 22 candidates in 2 rows.
        `t66v2_refused` (the 58 rows whose journals carried either refusal; 0 candidates before):
        35 of 57 eligible rows exact, 45 pins, 45 candidates offered / screened / exact.
        `t66v2_big` (all 52 rows of the never-examined 21+ pin band): 33 of 50 exact, 86 pins,
        125 screened.  Per opening, over both packs: T66_RENAME_HOST 441 ordered pairs newly
        offered, 36 exact, 36 pins; T66_MACRO_ARGS 476 newly offered, 94 exact, 94 pins (a
        candidate marked with both is counted in both).  Every cc1 distance journalled is 0 - the
        merged variable inherits the pin - so a miss is a refusal, not a near miss, and the only
        budget reached was T66_VERIFY, on the three largest rows.  All 68 outputs audited against
        their bases: guarded lines, unscored arms, stmt-pin macros and ASM_REG bindings all as
        expected, 0 defects.
    round 29, REVIEW (same REPORT, "Review fixes"): a review found two defects in T66_MACRO_ARGS -
        a macro parameter that is a MEMBER or a TYPE name was renamed (no detector existed; the
        class is not empty - `M2C_FIELD`'s `type_ptr` is in include/ and 187 rows call it), and the
        macro scan was per LINE, so an argument on a continuation line escaped every macro test.
        Both fixed above (`_param_name_use`/`_table_from`, `_MacroIdx`).  Neither cost a landed
        output: over the two packs' 110 frozen bases the fixed generator offers the SAME 654
        candidates byte for byte, one row aside (`dungeon/func_819A1654`, 4 ordered pairs now
        `in-macro-arg-unknown-macro`, 0 candidates either way), and `in-macro-arg-nameparam` is 0
        on that population.  Rerun `lane_eval --tag samereg22` over all 110 rows (45 of the 68
        round-29 outputs had been landed into src/ by then, so the totals are not comparable): 21
        hits, 60 pins, and on all 61 rows whose source had NOT moved the outcome and pin count are
        the round-29 run's, 61 of 61.  63 unit tests.
"""
import collections
import os
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from common import sha_text
from pin_census import sites_of, unscored_text, asm_blocker, PP_RE
from pin_search_engine import improves
from xform.screen import compile_s, sdiff
from xform.t51_sched_order import units
from xform.t62_regfamily import hard_register
from xform import natural as N

MENU_CAP = 48
SCREEN_BUDGET = 200
VERIFY_BUDGET = 6

ID = r"[A-Za-z_]\w*"
LABEL_RE = N.LABEL_RE
CASE_RE = N.CASE_RE
LOOP_RE = N.LOOP_RE
GOTO_RE = re.compile(r"\bgoto[ \t]+(%s)[ \t]*;" % ID)
CGOTO_RE = re.compile(r"\bgoto[ \t]*\*")
CTRL_HEAD_RE = re.compile(r"^[ \t]*(?:\}[ \t]*)?(?:else[ \t]+)?(?P<kw>if|while|for|switch|do|else)\b")
SWITCH_RE = re.compile(r"^[ \t]*(?:\}[ \t]*)?(?:else[ \t]+)?switch[ \t]*\(")
ELSE_RE = re.compile(r"^[ \t]*\}[ \t]*else\b")
CALLNAME_RE = re.compile(r"(?<![\w.])(?<!->)(%s)[ \t]*\(" % ID)
MACROARG_RE = re.compile(r"(?<![\w.])(?<!->)([A-Z][A-Z0-9_]{2,})[ \t]*\(")
# an initialiser that may be evaluated earlier than it was written: a literal, the address of
# something, or a file-scope symbol (`D_8008333C`, `MACRO_NAME`) with an optional constant index.
CONSTINIT_RE = re.compile(
    r"^(?:\([^()]*\))*(?:&[A-Za-z_]\w*(?:\[(?:0[xX][0-9A-Fa-f]+|\d+)\])?"
    r"|-?(?:0[xX][0-9A-Fa-f]+|\d+)"
    r"|(?:D_[0-9A-Fa-f]+|[A-Z][A-Z0-9_]*)(?:\[(?:0[xX][0-9A-Fa-f]+|\d+)\])?)$")
CALL_RE = re.compile(r"(?<![\w.])(?<!->)(?!(?:if|while|for|switch|return|sizeof)\b)%s[ \t]*\(" % ID)

# word-sized type classes (natural._tclass): 's' 32-bit signed, 'u' 32-bit unsigned, 'p' pointer
WORD = ("s", "u", "p")
NARROW = N.SMALL

# A mention here is the pin's own register binding, never a value: `ASM_REG("$2")`.  The binding is
# a string literal, so `natural.mask` blanks it and `_occ` cannot match inside it anyway - this is
# the belt to that brace, and it is what keeps `ASM_REG("$s0")` byte-identical in a function whose
# local is called `s0`.
NEVER_IN_MACRO = frozenset(("ASM_REG",))
# The four function-like macros in include/ that apply `#`/`##` to a parameter (verified 2026-09-15
# by listing all 74).  Kept as a constant so the module behaves the same when include/ is unreadable.
KNOWN_STRINGIFY = frozenset(("INCLUDE_ASM", "INCLUDE_RODATA", "ASM_LIVE_SIBCALL_PIN",
                             "ASM_SHAPE_D_SIBCALL_PIN"))
DEFINE_RE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+(\w+)\(([^)]*)\)(.*)$")
STR_RE = re.compile(r"\"(?:[^\"\\]|\\.)*\"|'(?:[^'\\]|\\.)*'")
ANYCALL_RE = re.compile(r"(?<![\w.])(?<!->)(\w+)[ \t]*\(")
# `MACROARG_RE`'s class, tested on a NAME and WIDENED to one and two characters: several rows define
# `U8(x)`/`S8(x)` themselves, and a two-letter macro from a header this module does not read would
# otherwise not be a macro call at all - no slot, no refusal, a silent rename.
MACRO_NAME_RE = re.compile(r"^[A-Z][A-Z0-9_]*$")
COMMENT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
# A word before a parameter that makes it a NAME: a tag, a type in `sizeof`, a label.
NAME_PREV_WORDS = frozenset(("struct", "union", "enum", "sizeof", "goto", "case"))
# the words a VALUE may follow directly; any other identifier before a parameter makes it a declarator
VALUE_PREV_WORDS = frozenset(("return", "else", "do"))
_HEADER_DEFS = None
_HEADER_STRINGIFY = None
_HEADER_TABLE = None
_TABLE_CACHE = {}


def _env_on(name, default="1"):
    """An opening's switch, read per call so a test may patch it."""
    return os.getenv(name, default).strip().lower() not in ("0", "", "no", "off", "false")


def _hash_params(params, body):
    """The parameters a macro body applies `#` or `##` to.

    String literals are masked first: `__asm__("#maspsx_pagebase_pin %0" : "+r"(var))` carries a
    literal `#` inside a string, which is NOT the stringify operator, and a crude `'#' in body`
    test calls six value-passing ASM_* pins stringifiers."""
    b = STR_RE.sub(lambda m: " " * len(m.group(0)), body)
    if "##" in b:
        return list(params)
    return [p for p in params if re.search(r"#[ \t]*%s\b" % re.escape(p), b)]


def _defs_in(text):
    """(name, [params], body) for every function-like `#define`, continuations joined."""
    for ln in text.replace("\\\n", " ").splitlines():
        m = DEFINE_RE.match(ln)
        if m:
            yield m.group(1), [p.strip() for p in m.group(2).split(",") if p.strip()], m.group(3)


def _close_stringify(defs, seed):
    """`seed` grown to a fixpoint: a macro that passes one of its OWN parameters into an argument of
    a macro already in the set stringifies it too - `#define OUTER(x) INNER(x)` over
    `#define INNER(x) #x` expands x and then stringifies it, and `_hash_params` reads only the direct
    body.  (Measured over include/ on 2026-09-15: the closure adds nothing to the four direct ones.)
    """
    out = set(seed)
    changed = True
    while changed:
        changed = False
        for name, params, body in defs:
            if name in out or not params:
                continue
            b = STR_RE.sub(lambda m: " " * len(m.group(0)), body)
            for mm in ANYCALL_RE.finditer(b):
                if mm.group(1) not in out:
                    continue
                span = _paren_span(b, mm.end() - 1)
                if span and any(re.search(r"\b%s\b" % re.escape(p), b[span[0]:span[1]])
                                for p in params):
                    out.add(name)
                    changed = True
                    break
    return out


def _header_defs():
    global _HEADER_DEFS
    if _HEADER_DEFS is None:
        defs = []
        try:
            inc = ROOT / "include"
            for p in (sorted(inc.glob("*.h")) + sorted((inc / "records").glob("*.h"))
                      + sorted(inc.glob("*.inc"))):
                defs += list(_defs_in(p.read_text(errors="replace")))
        except Exception:                      # an unreadable include/ costs candidates, never safety
            pass
        _HEADER_DEFS = tuple(defs)
    return _HEADER_DEFS


def _header_stringify():
    global _HEADER_STRINGIFY
    if _HEADER_STRINGIFY is None:
        defs = _header_defs()
        seed = set(KNOWN_STRINGIFY) | set(NEVER_IN_MACRO)
        seed |= {n for n, p, b in defs if _hash_params(p, b)}
        _HEADER_STRINGIFY = frozenset(_close_stringify(defs, seed))
    return _HEADER_STRINGIFY


def _stringify_macros(text):
    """Every macro whose argument may not be renamed: the headers' stringifiers, the row's own
    (`#define U8_AT(p, o) ...` sits at the top of several slus rows), anything that passes a
    parameter into one of those, and the ASM_REG binding.  Case is NOT part of the test - a
    lowercase `#define name_of(x) #x` in a row is refused like an uppercase one (`_macros_at` looks
    past `MACROARG_RE` for exactly these names)."""
    own = list(_defs_in(text))
    if not own:
        return _header_stringify()
    defs = list(_header_defs()) + own
    seed = set(_header_stringify()) | {n for n, p, b in own if _hash_params(p, b)}
    return frozenset(_close_stringify(defs, seed))


def _mask_body(body):
    """A macro body with its string literals and comments blanked (same length)."""
    b = STR_RE.sub(lambda m: " " * len(m.group(0)), body)
    return COMMENT_RE.sub(lambda m: " " * len(m.group(0)), b)


def _param_name_use(p, b):
    """Why parameter `p` of a macro whose masked body is `b` is a NAME rather than a value, or None.

    The class the round-29 review named: `#define ZONE_OF(F) (D_80024020[zone_id].F)` pastes its
    argument after a `.`, so renaming a variable inside that argument reads a DIFFERENT MEMBER -
    a different offset, a different program, and `#`/`##` (the only detector this module had) cannot
    see it.  `#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))` is
    the same defect through a TYPE name, and it is in `include/` today (187 rows call it).

    A parameter is a name when ANY occurrence in the body sits in a name position: after `.`/`->`
    (a member), after `struct`/`union`/`enum`/`sizeof`/`goto`/`case` (a tag, a type, a label), under
    `#`/`##` (a token), directly after another identifier or directly before one (`t n;` is a
    declaration, never a value - only `return`/`else`/`do` may precede a value that way), or spelled
    `p *)` / `(p)` before a value (a cast type).  Everything else is a value position; a false
    positive here costs a candidate, a false negative changes the program, so the test is one-sided
    on purpose.
    """
    for m in re.finditer(r"\b%s\b" % re.escape(p), b):
        before, after = b[:m.start()].rstrip(), b[m.end():]
        if before.endswith(".") or before.endswith("->"):
            return "member"
        if before.endswith("#") or before.endswith("##") or after.lstrip().startswith("##"):
            return "stringify"
        w = re.search(r"(\w+)$", before)
        if w and w.group(1) in NAME_PREV_WORDS:
            return "tag-or-sizeof"
        if w and w.group(1) not in VALUE_PREV_WORDS:
            # `ident p` in C is a declaration (`#define DECL(t, n) t n;`) or a cast, never a value,
            # unless the word before is one of the few keywords a value may follow.
            return "declarator"
        if re.match(r"[ \t]*\*+[ \t]*\)", after):
            return "cast-type"                       # `(type *)`
        if re.match(r"[ \t]*[A-Za-z_]", after):
            return "declaration"                     # `type name`
        if before.endswith("(") and re.match(r"[ \t]*\)", after):
            rest = after[after.index(")") + 1:]
            if re.match(r"[ \t]*[A-Za-z_(]", rest):
                # `(type)(value)` (`M2C_FIELD`'s `type_ptr`) or `(type)x`.  `*` and `&` are NOT in
                # that set: `((x) * 2)` and `((x) & 0xFF)` are arithmetic, and a value macro of that
                # shape is common, so the deref/address spelling of a cast (`(t) *p`) is left to the
                # `p *)` test above rather than costing every mask macro in the tree.
                return "cast-type"
    return None


def _arg_spans(s, span):
    """[(start, end)] of each top-level argument of the call whose parens are `span`."""
    a, b = span
    out, d, start = [], 0, a + 1
    for i in range(a + 1, b):
        ch = s[i]
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        elif ch == "," and d == 0:
            out.append((start, i))
            start = i + 1
    out.append((start, b))
    return out


def _calls_in(s, known=()):
    """[(name, open, close, [arg spans])] for every call in `s` whose name is macro-shaped
    (uppercase, `MACROARG_RE`'s class) or is a known macro whatever its case - a row may define
    `#define name_of(x) #x` in lower case."""
    out = []
    for mm in ANYCALL_RE.finditer(s):
        name = mm.group(1)
        if not (MACRO_NAME_RE.match(name) or name in known):
            continue
        span = _paren_span(s, mm.end() - 1)
        if span is None:
            continue
        out.append((name, span[0], span[1], _arg_spans(s, span)))
    return out


def _slot_of(call, pos):
    """The argument index `pos` falls in, or None when the call's arity is unreadable."""
    for i, (a, b) in enumerate(call[3]):
        if a <= pos < b:
            return i
    return None


def _table_from(defs):
    """{macro: {"params", "unsafe": {index: why}, "variadic"}} for a list of `(name, params, body)`.

    A later definition of the same name UNIONS its unsafe set with the earlier one (the row's own
    `#define` and a header's may differ and the preprocessor state is not read here), and the
    unsafe sets are then closed: a parameter a body passes into another macro's unsafe slot, or
    into an argument of a macro-shaped name this module cannot see the body of, is unsafe too.
    """
    info = {}
    for name, params, body in defs:
        b = _mask_body(body)
        rec = info.get(name)
        unsafe = dict(rec["unsafe"]) if rec else {}
        for i, p in enumerate(params):
            if p == "..." or not re.match(r"^\w+$", p):
                continue
            why = _param_name_use(p, b)
            if why:
                unsafe[i] = why
        if rec and rec["params"] != params:
            # two definitions with different parameter lists: the slot numbers do not line up, so
            # every slot of both is refused rather than guessed.
            unsafe = {i: "ambiguous-define" for i in range(max(len(params), len(rec["params"])))}
            params = rec["params"]
        info[name] = dict(params=params, unsafe=unsafe,
                          variadic=bool(params) and params[-1] == "...", body=b)
    changed = True
    while changed:
        changed = False
        for name, rec in info.items():
            b = rec["body"]
            for call in _calls_in(b, info):
                callee = info.get(call[0])
                for si, (a, e) in enumerate(call[3]):
                    if callee is not None:
                        slot = si if si < len(callee["params"]) or not callee["variadic"] \
                            else len(callee["params"]) - 1
                        if slot not in callee["unsafe"]:
                            continue
                        why = "via-%s" % call[0]
                    else:
                        why = "via-unknown-%s" % call[0]   # a macro-shaped name with no body here
                    for i, p in enumerate(rec["params"]):
                        if i in rec["unsafe"] or p == "..." or not re.match(r"^\w+$", p):
                            continue
                        if re.search(r"\b%s\b" % re.escape(p), b[a:e]):
                            rec["unsafe"][i] = why
                            changed = True
    return info


def _header_table():
    global _HEADER_TABLE
    if _HEADER_TABLE is None:
        _HEADER_TABLE = _table_from(list(_header_defs()))
    return _HEADER_TABLE


def _macro_table(text):
    """Every function-like macro this module can see, with the parameter slots that are NAMES.

    The headers plus the row's own `#define`s - the slus rows define `U8_AT`/`S16_AT` themselves.
    A macro-shaped call whose name is NOT in this table is refused at the call site
    (`in-macro-arg-unknown-macro`): round 28 refused every macro argument wholesale, so refusing
    the ones whose body is out of reach is never worse than the baseline.
    """
    own = list(_defs_in(text))
    if not own:
        return _header_table()
    key = tuple(sorted((n, tuple(p), b) for n, p, b in own))
    if key not in _TABLE_CACHE:
        if len(_TABLE_CACHE) > 64:
            _TABLE_CACHE.clear()
        _TABLE_CACHE[key] = _table_from(list(_header_defs()) + own)
    return _TABLE_CACHE[key]


class _MacroIdx:
    """Every macro call in one masked text, found WHOLE-TEXT.

    Until the round-29 review this scan was per LINE (`_macros_at`), so an argument that sat on a
    continuation line was invisible to the whole macro-argument machinery: a stringifier's argument
    was renamed with nothing journalled, and a cast read there was emitted unparenthesised.  The
    index joins the masked lines once and answers `(line, column) -> [(macro, slot)]`.
    """

    def __init__(self, ml, known=()):
        self.off, pos = [], 0
        for ln in ml:
            self.off.append(pos)
            pos += len(ln) + 1
        self.calls = _calls_in("\n".join(ml), known)

    def at(self, line, col):
        if line >= len(self.off):
            return []
        p = self.off[line] + col
        return [(c[0], _slot_of(c, p)) for c in self.calls if c[1] < p < c[2]]


def _calls_at(s, pos, known=()):
    """`_MacroIdx.at` for a single string - the one-line form, kept for direct callers."""
    return [(c[0], _slot_of(c, pos)) for c in _calls_in(s, known) if c[1] < pos < c[2]]


def _macros_at(s, pos, refuse=()):
    """Every macro (or macro-shaped) call whose argument list encloses `pos`, in one string.

    `MACROARG_RE`'s uppercase shape is the CLASS the round-28 refusal named, and it is what decides
    whether a mention is "in a macro argument" at all.  A name in `refuse` is looked for whatever its
    case, because a row may define `#define name_of(x) #x` in lower case and a rename inside that
    argument would change what the program says."""
    return [n for n, _ in _calls_at(s, pos, refuse)]


def _tclass(ty):
    return N._tclass(ty) if ty else None


def _cast(ty):
    """A C cast spelling for one of natural's type strings (`s16*` -> `(s16 *)`)."""
    base = ty.rstrip("*")
    stars = len(ty) - len(base)
    return "(" + base + (" " + "*" * stars if stars else "") + ")"


# ------------------------------------------------------------------ the statement-level CFG

class Flow:
    """Statement nodes of one function and their successors (see the module docstring).

    Nodes are `t51.units()` records inside the function body, preprocessor lines dropped.  Edges
    over-approximate: an unclassifiable statement reaches every later node.
    """

    def __init__(self, F, recs, pp=None, macro_ok=None, macro_refuse=(), mtable=None, midx=None):
        self.F = F
        ml = F.ml
        self.ml = ml
        # the T66_MACRO_ARGS opening, and the macros it may never rewrite (see the module docstring)
        self.macro_ok = _env_on("T66_MACRO_ARGS") if macro_ok is None else macro_ok
        self.macro_refuse = frozenset(macro_refuse) | NEVER_IN_MACRO
        # every function-like macro this module can see, and the whole-text index of macro calls
        # (built once per file: a macro argument may sit on a continuation line)
        self.mtable = _macro_table(F.t.text) if mtable is None else mtable
        self.midx = _MacroIdx(ml, self.mtable) if midx is None else midx
        self.rcache = {}                   # host-rename texts, shared by every pair of this function
        # Lines whose presence the preprocessor decides.  They stay NODES (a mention in one still
        # has to be seen) but every one of them is `unknown`: the arms of a region are alternatives,
        # not the sequence the successor rules would otherwise read them as, so reading them in
        # sequence would UNDER-approximate liveness (a `return` in one arm would look unconditional).
        self.pp = set(pp or ())
        self.nodes = [r["line"] for r in recs
                      if F.a < r["line"] < F.b and not ml[r["line"]].lstrip().startswith("#")]
        self.index = {k: i for i, k in enumerate(self.nodes)}
        self.opens = collections.defaultdict(list)
        self.closes = collections.defaultdict(list)
        for o, c in F.blocks:
            self.opens[o].append((o, c))
            self.closes[c].append((o, c))
        self.labels = {}
        self.cases = []
        for k in self.nodes:
            m = LABEL_RE.match(ml[k])
            if m:
                self.labels[m.group("l")] = k
            elif CASE_RE.match(ml[k]):
                self.cases.append(k)
        self.unknown = set()
        self.succ = {k: self._succ(k) for k in self.nodes}

    # -- helpers

    def after(self, line):
        """The first node strictly after `line` (None at the end of the function)."""
        for k in self.nodes:
            if k > line:
                return k
        return None

    def _enclosing(self, k, pred):
        blk = self.F.inner.get(k)
        while blk is not None:
            if pred(self.ml[blk[0]]):
                return blk
            blk = self.F.parent(blk)
        return None

    def _succ(self, k):
        ml, s = self.ml, self.ml[k]
        out, unknown = set(), k in self.pp
        stripped = s.strip()
        chunks = [c.strip() for c in s.split(";") if c.strip()]
        last = chunks[-1] if chunks else ""
        kw = last.split(None, 1)[0] if last else ""
        opens_block = bool(self.opens.get(k)) and stripped.endswith("{")
        jump = kw in ("goto", "return", "break", "continue") and not stripped.endswith("{")

        if CGOTO_RE.search(s):                      # `goto *table[i]` reaches every label
            out |= set(self.labels.values())
        for name in GOTO_RE.findall(s):
            if name in self.labels:
                out.add(self.labels[name])
            else:
                unknown = True
        if re.search(r"\bbreak[ \t]*;", s):
            blk = self._enclosing(k, lambda h: bool(LOOP_RE.match(h)) or bool(SWITCH_RE.match(h)))
            if blk is None:
                unknown = True
            else:
                nxt = self.after(blk[1])
                if nxt is not None:
                    out.add(nxt)
        if re.search(r"\bcontinue[ \t]*;", s):
            blk = self._enclosing(k, lambda h: bool(LOOP_RE.match(h)))
            if blk is None:
                unknown = True
            else:
                out.add(blk[0])
        # a control head whose body is neither on this line nor in a block opened here
        head = CTRL_HEAD_RE.match(s)
        if head and not opens_block and not stripped.endswith((";", "}")):
            unknown = True
        if not jump:
            nxt = self.after(k)
            if nxt is not None:
                out.add(nxt)
        for o, c in self.opens.get(k, []):
            if o == c:
                continue
            conditional = bool(CTRL_HEAD_RE.match(ml[o]) and not re.match(r"^[ \t]*(?:\}[ \t]*)?do\b", ml[o]))
            if conditional or ELSE_RE.match(ml[o]):
                nxt = self.after(c)
                if nxt is not None:
                    out.add(nxt)
            if SWITCH_RE.match(ml[o]):
                out |= {x for x in self.cases if self.F.inner.get(x) == (o, c)}
        for o, c in self.closes.get(k, []):
            if o != c and LOOP_RE.match(ml[o]):
                out.add(o)                           # the back edge
        if unknown:
            self.unknown.add(k)
            out |= {x for x in self.nodes if x > k}
        return {x for x in out if x in self.index}


def _macro_arg_refusal(encl, refuse, table, macro_ok):
    """Why a mention inside these macro arguments may not be renamed, or None.

    `encl` is `[(macro, slot)]`, innermost order irrelevant: EVERY enclosing call has to accept the
    rename.  The order of the tests is the order the columns of the round-28 before/after table
    were counted in - the ASM_REG binding and the stringifiers were already their own refusals
    before the opening, so they stay named whether the opening is on or off, and everything else
    reads `in-macro-arg` when it is off.
    """
    names = [n for n, _ in encl]
    bad = [x for x in names if x in refuse]
    if bad:
        return "in-asm-reg-binding" if "ASM_REG" in bad else "in-macro-arg-stringify"
    if not macro_ok:
        return "in-macro-arg"
    for name, slot in encl:
        rec = table.get(name)
        if rec is None:
            # a macro-shaped name whose body this module cannot see (a header it does not read, a
            # call through an uppercase function pointer): its parameter may be a member or a type.
            return "in-macro-arg-unknown-macro"
        if slot is None:
            return "in-macro-arg-unknown-macro"
        if rec["variadic"] and slot >= len(rec["params"]) - 1:
            slot = len(rec["params"]) - 1
        elif slot >= len(rec["params"]):
            return "in-macro-arg-argcount"       # the call does not match the definition read here
        if slot in rec["unsafe"]:
            return "in-macro-arg-nameparam"
    return None


# ------------------------------------------------------------------ one variable's facts

class Facts:
    """Where one declaration's variable is mentioned, written and live."""

    def __init__(self, flow, d):
        self.d = d
        self.name = d["name"]
        self.ok = True
        self.reason = None
        F, ml = flow.F, flow.ml
        rx = N._occ(self.name)
        o, c = d["block"]
        self.mentions = {}                 # line -> [match objects on the masked line]
        self.macro_mentions = {}           # line -> [(column, [enclosing macro names])]
        self.kills = set()
        self.addr = False
        macro_ok = getattr(flow, "macro_ok", False)
        refuse = getattr(flow, "macro_refuse", NEVER_IN_MACRO)
        table = getattr(flow, "mtable", None) or {}
        midx = getattr(flow, "midx", None)
        for k in flow.nodes:
            if not (o < k < c):
                continue
            s = ml[k]
            hits = list(rx.finditer(s))
            lm = LABEL_RE.match(s)
            if (lm and lm.group("l") == self.name) \
                    or re.search(r"\bgoto[ \t]+%s\b" % re.escape(self.name), s) \
                    or any(m.group(1) == self.name for m in CALLNAME_RE.finditer(s)):
                self.ok, self.reason = False, "label-or-call-named"
            if not hits:
                continue
            if k in flow.pp:
                # a mention the preprocessor decides: the port fallback declaration beside a pin
                # (`#ifdef __mips__ register T v ASM_REG("$N"); #else T v; #endif`) is the common
                # one, and rewriting it is how invalid C reached three landed rows.
                self.ok, self.reason = False, "pp-guarded-mention"
                continue
            if k == d["line"]:
                if d["init"] is not None:
                    self.kills.add(k)
                continue
            if F.resolve(self.name, k) is not d:
                self.ok, self.reason = False, "shadowed-inner-local"
                continue
            for m in hits:
                before = s[:m.start()]
                if re.search(r"(?:^|[^&\w)\]])&[ \t]*$", before):
                    self.addr = True
                encl = midx.at(k, m.start()) if midx is not None \
                    else _calls_at(s, m.start(), refuse)
                if not encl:
                    continue
                why = _macro_arg_refusal(encl, refuse, table, macro_ok)
                if why:
                    self.ok, self.reason = False, why
                else:
                    self.macro_mentions.setdefault(k, []).append(
                        (m.start(), [n for n, _ in encl]))
            self.mentions[k] = hits
            if self._is_kill(flow, k, hits):
                self.kills.add(k)
        if d["line"] in flow.pp or d["end"] in flow.pp:
            self.ok, self.reason = False, "pp-guarded-mention"
        if self.addr:
            self.ok, self.reason = False, "address-taken"
        self.lines = sorted(set(self.mentions) | {d["line"]})
        self.uses = sorted(k for k in self.mentions if k not in self.kills)

    def _is_kill(self, flow, k, hits):
        """A whole plain `v = ...;` statement that does not read v, and is not the body of a
        braceless if/loop (then it may not execute, so it may not kill)."""
        s = flow.ml[k]
        m = re.match(r"^[ \t]*%s[ \t]*=(?!=)(?P<rhs>[^;]*);[ \t]*$" % re.escape(self.name), s)
        if not m or N._occ(self.name).search(m.group("rhs")):
            return False
        p = N._prev_nb(flow.ml, k)
        prev = flow.ml[p].rstrip() if p is not None else "{"
        return prev.endswith(("{", "}", ";", ":"))


def _pp_regions(text):
    """Every 0-based line index a preprocessor conditional covers - the `#if`/`#ifdef`/`#ifndef`/
    `#elif`/`#else`/`#endif` directive lines included, whatever the condition is.

    `arm_labels` answers a DIFFERENT question (which build compiles the line) and it only knows
    `NON_MATCHING` and `#if 0`; an `#ifdef __mips__` block is `both` to it, top to bottom.  This
    module needs "is this line's presence decided by the preprocessor", so it counts depth itself.
    """
    out, depth = set(), 0
    for i, ln in enumerate(text.splitlines()):
        m = PP_RE.match(ln)
        if m:
            d = m.group(1)
            if d in ("ifdef", "ifndef", "if"):
                out.add(i)
                depth += 1
                continue
            if d == "endif":
                out.add(i)
                depth = max(0, depth - 1)
                continue
            out.add(i)                        # elif / else
            continue
        if depth:
            out.add(i)
    return out


def _pp_sig(text, regions=None):
    """The text of every preprocessor-guarded line, in order: the invariant a candidate may not
    change.  `natural._T.build` copies untouched lines byte for byte, so a hoist that only moves
    unguarded lines leaves this identical even though the line numbers move."""
    lines = text.splitlines()
    regions = _pp_regions(text) if regions is None else regions
    return tuple(lines[i] for i in sorted(regions) if i < len(lines))


def _paren_span(s, open_idx):
    d = 0
    for i in range(open_idx, len(s)):
        if s[i] == "(":
            d += 1
        elif s[i] == ")":
            d -= 1
            if d == 0:
                return (open_idx, i)
    return None


def live(flow, facts):
    """Backward liveness: {node: (live_in, live_out)} for one variable."""
    o, c = facts.d["block"]
    scope = [k for k in flow.nodes if o < k < c]
    use = {k: (k in facts.mentions and k not in facts.kills) for k in scope}
    kill = {k: k in facts.kills for k in scope}
    lin = {k: False for k in scope}
    changed = True
    while changed:
        changed = False
        for k in reversed(scope):
            lout = any(lin.get(s, False) for s in flow.succ.get(k, ()))
            v = use[k] or (lout and not kill[k])
            if v != lin[k]:
                lin[k] = v
                changed = True
    lout = {k: any(lin.get(s, False) for s in flow.succ.get(k, ())) for k in scope}
    return lin, lout


def interference(flow, a, b):
    """None when the two variables can be one, else the reason."""
    ain, aout = live(flow, a)
    bin_, bout = live(flow, b)
    clash = [k for k in flow.nodes
             if (ain.get(k) and bin_.get(k)) or (aout.get(k) and bout.get(k))]
    if not clash:
        return None
    for o, c in flow.F.loops:
        if any(o < k < c for k in clash) and any(o < k < c for k in a.lines) \
                and any(o < k < c for k in b.lines):
            return "loop-backedge"
    return "interference"


# ------------------------------------------------------------------ candidates

class Pair:
    __slots__ = ("F", "flow", "H", "V", "hf", "vf_", "reg", "block", "dist", "twoarm",
                 "base", "sites")


def _decl_of(F, line, name):
    for ds in F.decls.values():
        for d in ds:
            if d["line"] == line and d["name"] == name:
                return d
    return None


def _pin_vars(text, sites):
    """[(site, name)] for every live ASM_REG pin, with the variable it declares."""
    out = []
    for s in sites:
        if s[1] != "ASM_REG":
            continue
        decl = (s[6] or "").split()
        if not decl:
            continue
        out.append((s, decl[-1].lstrip("*")))
    return out


MULTIDECL_RE = re.compile(
    r"^[ \t]*(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*"
    r"%s(?:(?:[ \t]*\*)+[ \t]*|[ \t]+)\(?\*?%s\)?(?:[ \t]*\([^;]*\))?(?:[ \t]*\[[^\]]*\])?"
    r"(?:[ \t]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\))?"
    r"(?:[ \t]*,[ \t]*\**%s(?:[ \t]*\[[^\]]*\])?)*[ \t]*(?:=[^;]*)?;[ \t]*$" % (ID, ID, ID))


ARRAY_OPEN_RE = re.compile(
    r"^[ \t]*(?:(?:static|const|register|volatile|unsigned|signed|struct|union|enum)[ \t]+)*"
    r"%s(?:(?:[ \t]*\*)+[ \t]*|[ \t]+)(?:const[ \t]+)?%s[ \t]*\[[^\]]*\][ \t]*=[ \t]*\{[ \t]*$" % (ID, ID))


def _augment(F):
    """Declarations `natural._Fn` stopped short of.

    Its block scan breaks at the first line its declaration regex does not recognise, and one
    `M2C_UNK (*update_actor)(void *, void *);` in the middle of a 90-line declaration run hides
    every declaration under it - 75 of the pins in the two evaluation packs.  This walks the same
    run with a looser test and adds what is missing (a line it cannot parse into a type still
    registers its NAMES, so scope resolution still sees them)."""
    for blk in F.blocks:
        o, c = blk
        known = {d["line"] for d in F.decls.get(blk, [])}
        stop = max(known) + 1 if known else o + 1
        k = stop
        while k < c:
            s = F.ml[k]
            if not s.strip() or s.lstrip().startswith("#"):
                k += 1
                continue
            if ARRAY_OPEN_RE.match(s):
                # `static void *const state_labels[] = { &&case_0, ... };` - the computed-goto
                # label table m2c writes first in a jump-table function.  natural's scan stops dead
                # on it (`void *const` is not a declaration start there), taking the row's whole
                # declaration run with it; step over it, registering its name for scope resolution.
                end = k
                while end < c and not F.ml[end].rstrip().endswith(";"):
                    end += 1
                for n in N._decl_names(" ".join(F.ml[k:end + 1])):
                    F.decls.setdefault(blk, []).append(dict(
                        line=k, end=end, name=n, block=blk, single=False, ty=None, quals=set(),
                        init=None, arr=True, pinned=False, spell=None, ind=N._ind(s)))
                k = end + 1
                continue
            if not s.rstrip().endswith(";") or not MULTIDECL_RE.match(s):
                break
            m = N.VDECL_RE.match(s)
            if m and m.group("base") not in N.CTRL:
                q = m.group("q").split()
                F.decls.setdefault(blk, []).append(dict(
                    line=k, end=k, name=m.group("n"), block=blk, single=True,
                    ty=N._ptype(q, m.group("base"), m.group("ptr")), quals=set(q),
                    init=m.group("init"), arr=bool(m.group("arr")), pinned=bool(m.group("asm")),
                    spell=m.group("spell").strip(), ind=m.group("i")))
            else:
                for n in N._decl_names(s):
                    F.decls.setdefault(blk, []).append(dict(
                        line=k, end=k, name=n, block=blk, single=False, ty=None, quals=set(),
                        init=None, arr=False, pinned="ASM_REG" in s, spell=None, ind=N._ind(s)))
            k += 1
    F.byname = {}
    for d in [x for ds in F.decls.values() for x in ds] + F.params:
        F.byname.setdefault(d["name"], []).append(d)
    F._vars = {}
    return F


def _functions(t):
    return [_augment(F) for F in N._functions(t)]


def _fn_of(fns, line):
    return next((F for F in fns if F.a < line < F.b), None)


def pairs_of(text, skips=None):
    """Every ordered (host, victim) pair of same-register ASM_REG declarations whose lifetimes are
    disjoint, nearest first.  `skips` counts the refusals."""
    skips = collections.Counter() if skips is None else skips
    out = []
    try:
        t = N._T(text)
        _, recs = units(text)
    except Exception:
        skips["parse-error"] += 1
        return out
    pp = _pp_regions(text)
    macro_ok = _env_on("T66_MACRO_ARGS")
    refuse = _stringify_macros(text)
    mtable = _macro_table(text)
    midx = _MacroIdx(t.m, mtable)
    fns = _functions(t)
    sites = sites_of(text)
    byfn = collections.defaultdict(list)
    for s, name in _pin_vars(text, sites):
        F = _fn_of(fns, s[5] - 1)
        if F is None:
            skips["decl-no-function(per declaration)"] += 1
            continue
        byfn[(F.a, F.b)].append((s, name, F))
    flows = {}
    factcache = {}
    for key, group in byfn.items():
        byreg = collections.defaultdict(list)
        for s, name, F in group:
            byreg[hard_register(s[2])].append((s, name, F))
        for reg, members in byreg.items():
            if len(members) < 2:
                continue
            F = members[0][2]
            if key not in flows:
                try:
                    flows[key] = Flow(F, recs, pp, macro_ok=macro_ok, macro_refuse=refuse,
                                      mtable=mtable, midx=midx)
                except Exception:
                    skips["parse-error"] += 1
                    flows[key] = None
            flow = flows[key]
            if flow is None:
                continue
            decls = []
            for s, name, _ in members:
                d = _decl_of(F, s[5] - 1, name)
                if d is None or not d["single"] or d["arr"] or not d["ty"] \
                        or d["line"] != d["end"] or (d["quals"] & N.NOSHARE):
                    continue
                if d["line"] not in factcache:
                    factcache[d["line"]] = Facts(flow, d)
                decls.append((d, factcache[d["line"]]))
            # Every skip below is counted per ORDERED PAIR; the declarations dropped just above
            # cost pairs too, so charge them at the same scale instead of once per declaration.
            n, k_ = len(members), len(decls)
            if k_ < n:
                skips["decl-unparsed"] += n * (n - 1) - k_ * (k_ - 1)
            for i, (dh, fh) in enumerate(decls):
                for j, (dv, fv) in enumerate(decls):
                    if i == j:
                        continue
                    if not fh.ok:
                        skips[fh.reason] += 1
                        continue
                    if not fv.ok:
                        skips[fv.reason] += 1
                        continue
                    why = interference(flow, fh, fv)
                    if why:
                        skips[why] += 1
                        continue
                    p = Pair()
                    p.F, p.flow, p.H, p.V, p.hf, p.vf_, p.reg = F, flow, dh, dv, fh, fv, reg
                    p.base, p.sites = text, sites
                    p.block = F.encl(min(fh.lines + fv.lines), max(fh.lines + fv.lines))
                    p.dist = min(abs(x - y) for x in fh.lines for y in fv.lines)
                    p.twoarm = _arms(F, dh["block"], dv["block"])
                    if fh.macro_mentions or fv.macro_mentions:
                        # an ordered pair the `in-macro-arg` refusal used to cost (informational:
                        # it is offered, not skipped - the before/after table reads it beside the
                        # `in-macro-arg` count a T66_MACRO_ARGS=0 run still reports)
                        skips["in-macro-arg-reopened"] += 1
                    out.append(p)
    out.sort(key=lambda p: (p.dist, p.H["line"], p.V["line"]))
    return out


def _arms(F, b1, b2):
    """Are these two blocks the two arms of one `if`/`else`, or two `case` arms of one switch?"""
    if b1 == b2:
        return False
    a, b = sorted([b1, b2])
    if a[1] == b[0] and ELSE_RE.match(F.ml[b[0]]):
        return True                                  # `} else {` closes the first and opens the second
    parent = F.inner.get(a[0])
    if parent and parent == F.inner.get(b[0]) and SWITCH_RE.match(F.ml[parent[0]]):
        return any(CASE_RE.match(F.ml[k]) for k in range(a[1], b[0] + 1))
    return False


def _decl_line_without_init(t, d):
    """The declaration's own line with its `= init` cut out, the trailing pin note kept."""
    s = t.m[d["line"]]
    m = N.VDECL_RE.match(s)
    if not m or m.group("init") is None:
        return None
    eq = s.rfind("=", 0, m.start("init"))
    semi = s.find(";", m.end("init"))
    if eq < 0 or semi < 0:
        return None
    ln = N._nl(t.lines[d["line"]])
    return ln[:eq].rstrip() + ln[semi:]


def _const_init(init):
    """A literal, a symbol (or one constant-indexed element of one), an address, or a cast of one:
    an initialiser that may be evaluated earlier than it was written."""
    return bool(init) and bool(CONSTINIT_RE.match(N._sq(init)))


def _insert_after(F, block):
    """The line a new declaration of `block` goes after: its last declaration, else its `{`."""
    ds = F.decls.get(block) or []
    return max([d["end"] for d in ds] + [block[0]])


def _first_case(F, block):
    """The line of the first `case`/`default` label directly inside `block`, if `block` is a
    switch body.  Everything above it is the block's declaration region: legal for a bare
    declaration, UNREACHABLE for anything that executes."""
    if not SWITCH_RE.match(F.ml[block[0]]):
        return None
    for k in range(block[0] + 1, min(block[1], len(F.ml))):
        if F.inner.get(k) == block and CASE_RE.match(F.ml[k]):
            return k
    return None


def _reaches(F, block, line):
    """May code placed just after `line` in `block` ever execute?

    A switch body is entered at a `case` label, never at its `{`, so an initialiser or an
    assignment parked above the first label is jumped over and the variable is read uninitialised.
    `_insert_after` lands exactly there for a declaration-free switch body (it returns the
    `switch (...) {` line itself), and only a lucky codegen difference would have made the screen
    notice.  A BARE declaration there is fine - it emits nothing - so this gates the variants that
    carry an initialiser or an assignment, not the plain hoist.
    """
    first = _first_case(F, block)
    return first is None or line >= first


def _demote(F, d):
    """Where the assignment that replaces declaration `d` may go, as (kind, line).

    A declaration in the middle of a block's declaration run cannot simply become a statement:
    C89 puts every declaration first, so `register s32 next ASM_REG("$4");` two lines below would
    then be a syntax error (17 candidates in the mid pack before this was measured).  The
    assignment goes after the LAST declaration of that block instead - and only when none of the
    declarations it now follows has an initialiser of its own, because those initialisers run in
    declaration order and one of them may read the very value being moved.
    """
    later = [x for x in (F.decls.get(d["block"]) or []) if x["line"] > d["line"]]
    if not later:
        return ("edit", d["line"]) if _reaches(F, d["block"], d["line"]) else None
    if any(x["init"] is not None for x in later):
        return None
    at = max(x["end"] for x in later)
    return ("after", at) if _reaches(F, d["block"], at) else None


def _rename_edits(t, facts, new, edits=None):
    return N._rename(t, list(facts.mentions), facts.name, new, edits)


COMPOUND_RE = re.compile(r"^(?P<i>[ \t]*)%s[ \t]*(?P<op><<|>>|[-+*/%%&|^])=(?!=)(?P<rhs>[^;]*);(?P<tail>.*)$")
INCDEC_RE = re.compile(r"^(?P<i>[ \t]*)(?:(?P<pre>\+\+|--)%s|%s(?P<post>\+\+|--))[ \t]*;(?P<tail>.*)$")


def _cast_edits(t, facts, host, tv, th, skips):
    """V's definitions become `H = (TH)(expr);`, its reads `(TV)H`.

    A compound assignment and a `v++;`/`v--;` STATEMENT are definitions too - `v >>= 5;` is
    `v = (TV)(v >> 5);` written short - so they take the same form, desugared:
    `H = (TH)((TV)H >> (5));`.  That spelling is what makes the merge of two 32-bit words of
    different signedness sound: every operand keeps the signedness it was written with, so a
    logical shift stays logical and an unsigned compare stays unsigned.  (Until 2026-09-15 this
    module also emitted an undocumented cast-free `implicit` spelling AHEAD of this one, which
    silently changed `u32 >>= 5` into an arithmetic shift; it was removed in review.)
    """
    if any(x.startswith("ASM_") for hits in facts.macro_mentions.values()
           for _, encl in hits for x in encl):
        # `ASM_KEEP(var)` is `__asm__ __volatile__("" : "=r"(var) : "0"(var))`: the argument is an
        # OUTPUT operand, and `(u8 *)h` is not an lvalue.  The rename form of the same pair is
        # unaffected - only the cast spelling has to be refused here.
        skips["asm-operand-cast"] += 1
        return None
    edits = {}
    ch, cv = _cast(th), _cast(tv)
    name = re.escape(facts.name)
    comp_re = re.compile(COMPOUND_RE.pattern % name)
    incdec_re = re.compile(INCDEC_RE.pattern % (name, name))
    for k, hits in facts.mentions.items():
        s = t.m[k]
        ln = N._nl(t.lines[k])
        if len(hits) == 1 and k not in facts.kills:
            m = comp_re.match(s)
            if m and not N._occ(facts.name).search(m.group("rhs")):
                rhs = ln[m.start("rhs"):m.end("rhs")].strip()
                edits[k] = "%s%s = %s((%s%s) %s (%s));%s" % (
                    m.group("i"), host, ch, cv, host, m.group("op"), rhs,
                    ln[m.start("tail"):])
                continue
            m = incdec_re.match(s)
            if m:
                op = "+" if (m.group("pre") or m.group("post")) == "++" else "-"
                edits[k] = "%s%s = %s((%s%s) %s 1);%s" % (
                    m.group("i"), host, ch, cv, host, op, ln[m.start("tail"):])
                continue
        if k in facts.kills:
            m = re.match(r"^(?P<i>[ \t]*)%s[ \t]*=(?!=)(?P<rhs>[^;]*);(?P<tail>.*)$"
                         % re.escape(facts.name), s)
            if not m:
                skips["write-not-plain-cast"] += 1
                return None
            rhs = ln[m.start("rhs"):m.end("rhs")].strip()
            edits[k] = "%s%s = %s(%s);%s" % (m.group("i"), host, ch, rhs, ln[m.end("rhs") + 1:])
            continue
        for m in reversed(hits):
            after = s[m.end():]
            if re.match(r"[ \t]*(?:=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--)", after) \
                    or re.search(r"(?:\+\+|--)[ \t]*$", s[:m.start()]):
                skips["compound-assign-cast"] += 1
                return None
            # Inside a macro argument the macro body decides what the cast binds to, and this line
            # cannot be read for it: parenthesise there always.
            in_macro = any(col == m.start() for col, _ in facts.macro_mentions.get(k, ()))
            paren = in_macro or bool(re.match(r"[ \t]*(?:\[|->|\.|\()", after))
            rep = ("(%s%s)" % (cv, host)) if paren else "%s%s" % (cv, host)
            ln = ln[:m.start()] + rep + ln[m.end():]
        edits[k] = ln
    return edits


def _collides(F, H, V, bt):
    """Does the host's name mean something other than H or V anywhere in block `bt`?"""
    rxh = N._occ(H["name"])
    return any(rxh.search(F.ml[k]) and F.resolve(H["name"], k) not in (H, V)
               for k in range(bt[0] + 1, min(bt[1], len(F.ml)))
               if k not in (H["line"], V["line"]))


def _expected_pins(pair, host):
    """The pin multiset a candidate of this pair must carry.

    The pins of the text the pair was read from, with V's own `ASM_REG` dropped and V's name
    rewritten to `host` wherever a pin's text names it - which is exactly the T66_MACRO_ARGS
    assertion that `ASM_KEEP(V)` became `ASM_KEEP(H)` and the pin COUNT did not move.  V's spelling
    is rewritten only on lines `Facts` recorded as V's own mentions, where every occurrence of the
    name resolves to V; `natural._occ` (never `str.replace`) does the rewriting, so `v` inside
    `driver_value` is left alone.  A reg site's `arg` is the REGISTER, never a name - a function
    with a local called `s0` and a pin on `$s0` would otherwise rewrite its own binding.
    """
    want = collections.Counter()
    rx = N._occ(pair.V["name"])
    vlines = set(pair.vf_.mentions)
    for s in pair.sites:
        k = s[5] - 1
        macro, arg, decl = s[1], s[2], (s[6] or "").strip()
        if s[0] == "reg" and k == pair.V["line"]:
            continue                                   # the pin being deleted
        if k in vlines:
            if s[0] == "stmt":
                arg = rx.sub(host, arg)
            else:
                decl = rx.sub(host, decl)
        want[(macro, arg, decl)] += 1
    return want


def _fresh_name(pair):
    """`<host>_m`, or `_m2`.. when that is taken: a name no word of the file already is."""
    body = pair.F.t.mtext
    for suffix in ["_m"] + ["_m%d" % i for i in range(2, 10)]:
        cand = pair.H["name"] + suffix
        if not re.search(r"\b%s\b" % re.escape(cand), body):
            return cand
    return None


def _vname_free(pair):
    """May the merged variable be spelled with V's name?  Only when V's name is V's alone in this
    function: no other declaration carries it and no mention of it resolves elsewhere (a global)."""
    F, vn = pair.F, pair.V["name"]
    if vn == pair.H["name"]:
        return False
    if any(d is not pair.V for d in F.byname.get(vn, ())):
        return False
    rx = N._occ(vn)
    return not any(rx.search(F.ml[k]) and F.resolve(vn, k) is not pair.V
                   for k in range(F.a + 1, min(F.b, len(F.ml)))
                   if k not in (pair.V["line"], pair.H["line"]))


def _host_renamed(pair, new):
    """The whole text with every mention of the host - its declaration line included - renamed.

    One edit per line, built from the ORIGINAL masked positions, so a line that mentions both
    variables is safe; `Facts` guarantees every occurrence of the host's name on one of these lines
    resolves to the host, and it refuses a host with a mention in any preprocessor region, so the
    guarded lines and the unscored arms are untouched by construction (asserted by the caller).

    None when a mention of the host sits on a line `Facts` never saw (one `t51.units()` does not
    record): renaming the host is the ONE rewrite in this module whose missed mention does not have
    to fail the build, because the collision that provoked the rename is a live declaration of that
    very name - the stale mention would silently bind to it.  V's rename is safe without this: V's
    declaration is deleted, so a missed mention of V cannot compile."""
    t, F = pair.F.t, pair.F
    o, c = pair.H["block"]
    seen, rx = set(pair.hf.lines), N._occ(pair.H["name"])
    if any(rx.search(F.ml[k]) for k in range(o + 1, min(c, len(F.ml))) if k not in seen):
        return None
    return t.build(N._rename(t, pair.hf.lines, pair.H["name"], new))


def _rename_host(pair, skips):
    """T66_RENAME_HOST: retry the merge with the surviving variable renamed (docstring, opening 1).

    V's own name first (the clearest spelling - it is what retail's one variable was called at the
    second value), then a fresh `<host>_m`.  The renamed text is re-parsed from scratch and merged
    by the ordinary path, so the collision test, `Facts`, the liveness test and the preprocessor
    guards all fire again on what the compiler will actually see."""
    names = ([(pair.V["name"], "vname")] if _vname_free(pair) else [])
    fresh = _fresh_name(pair)
    if fresh:
        names.append((fresh, "hostm"))
    if not names:
        skips["host-rename-name-taken"] += 1
        return []
    base = pair.F.t.text
    cache, last = pair.flow.rcache, None
    for new, tag in names:
        key = (pair.H["line"], new)
        if key not in cache:
            try:
                text1 = _host_renamed(pair, new)
                if text1 is None:
                    cache[key] = None
                elif _pp_sig(text1) != _pp_sig(base) or unscored_text(text1) != unscored_text(base):
                    cache[key] = None            # unreachable by construction; the assertion stands
                else:
                    cache[key] = (text1, pairs_of(text1, collections.Counter()))
            except Exception:
                cache[key] = None
        if cache[key] is None:
            skips["host-rename-build-failed"] += 1
            continue
        _, ps = cache[key]
        p1 = next((q for q in ps
                   if q.H["line"] == pair.H["line"] and q.V["line"] == pair.V["line"]
                   and q.reg == pair.reg and q.H["name"] == new), None)
        if p1 is None:
            # the rename changed what `Facts`/`interference` see - the pair is no longer offered
            skips["host-rename-pair-lost"] += 1
            continue
        last = collections.Counter()
        got = candidates_for(p1, last, renamed=tag)
        if got:
            skips.update(last)
            return got
    if last:
        skips.update(last)
    return []


def candidates_for(pair, skips, renamed=None):
    """[(form, label, text)] for one ordered pair.

    `renamed` is the T66_RENAME_HOST tag (`vname` or `hostm`) when this pair was read from a text
    whose surviving variable has already been renamed; it both marks the labels and stops the
    recursion at one level."""
    F, t = pair.F, pair.F.t
    H, V, hf, vf_ = pair.H, pair.V, pair.hf, pair.vf_
    marks = ([renamed] if renamed else []) + (
        ["macroarg"] if (hf.macro_mentions or vf_.macro_mentions) else [])
    mark = ("+" + "+".join(marks)) if marks else ""
    th, tv = H["ty"], V["ty"]
    if th == tv:
        spells = [("rename", None)]
    elif _tclass(th) in WORD and _tclass(tv) in WORD:
        # A word is a word: pointer, s32 or u32 - merged in the CAST spelling only, which keeps the
        # signedness every operand was written with.  A cast-free merge of two integer words is a
        # different program wherever the sign matters (`u32 v >>= 5` becomes an arithmetic shift),
        # and the generator has no value-range argument to offer; that spelling was removed in
        # review on 2026-09-15.
        spells = [("cast", (tv, th))]
    elif th in NARROW or tv in NARROW:
        skips["type-mismatch-narrow"] += 1      # merging would change the value's width
        return []
    else:
        skips["type-mismatch-unsupported"] += 1
        return []

    out = []
    hoist = H["block"] != pair.block
    if hoist and not (pair.block[0] < H["line"] < pair.block[1]):
        skips["hoist-target-arm"] += 1
        return []
    # The declaration goes to the nearest block enclosing both, and - since where a declaration
    # sits is itself the lever (probe4's func_800A3D40 won at function scope) - to the function
    # body as well when that is a different block.
    targets = [pair.block] if not hoist else [pair.block] + (
        [F.body] if pair.block != F.body else [])
    places, collide = [], 0
    for bt, btag in zip(targets, ("hoist", "hoistfn")):
        # The host's name must mean the host everywhere in the block it is about to cover: an inner
        # local or a global of that name there would be captured by the rename (or by the new scope).
        # A mention that already means V is one the rewrite renames - V may even carry H's own name,
        # which is m2c's spelling of one variable declared twice, the clearest case of all.
        if _collides(F, H, V, bt):
            collide += 1
            continue
        if not hoist:
            places.append(("", bt, None, None, None, [], True))
            continue
        anchor = _insert_after(F, bt)
        if anchor in pair.flow.pp or (anchor + 1) in pair.flow.pp:
            # the moved declaration would land inside a preprocessor region, where only one build
            # would see it.  The `anchor + 1` half is deliberately blunt: with `anchor` itself
            # unguarded, `anchor + 1` can only be an OPENING directive, and `build` inserts before
            # it - so that branch refuses a candidate that would in fact land unguarded.  It is a
            # false refusal, not a safety check; `_pp_sig` is the invariant that decides.  It cost
            # nothing measurable (`pp-guarded-anchor` does not appear in either evaluation pack).
            skips["pp-guarded-anchor"] += 1
            continue
        ind = (F.decls.get(bt) or [{}])[0].get("ind") or (N._ind(F.ml[bt[0]]) + "    ")
        keep = N._nl(t.lines[H["line"]])
        stripped = _decl_line_without_init(t, H) if H["init"] is not None else keep
        if stripped is None:
            skips["decl-unparsed"] += 1
            continue
        # what a hoisted initialiser would jump over: a use of V it would clobber, a call, or an
        # assignment that could change what the initialiser reads
        lo, hi = min(anchor, H["line"]), max(anchor, H["line"])
        names = set(re.findall(ID, H["init"] or ""))
        between = [k for k in vf_.mentions if lo <= k <= hi]
        for k in range(lo, hi):
            s = F.ml[k]
            if CALL_RE.search(s):
                between.append(k)
                continue
            a = re.match(r"^(?P<lhs>[^=;]*)=(?!=)", s)
            if a and names & set(re.findall(ID, a.group("lhs"))):
                between.append(k)
        places.append((btag, bt, anchor, ind + keep.lstrip(), ind + stripped.lstrip(), between,
                       _reaches(F, bt, anchor)))
    if not places:
        # Every target block the merged declaration could cover already means something else by the
        # host's name.  T66_RENAME_HOST retries the whole merge on a text where the SURVIVING
        # variable has been renamed (see the module docstring); the collision is only charged when
        # that fails too, so `host-name-collision` + `host-name-collision-reopened` is the count a
        # T66_RENAME_HOST=0 run reports.
        if collide and renamed is None and _env_on("T66_RENAME_HOST"):
            got = _rename_host(pair, skips)
            if got:
                skips["host-name-collision-reopened"] += collide
                return got
        if collide:
            skips["host-name-collision"] += collide
        return []
    if collide:
        skips["host-name-collision"] += collide
    kind = "twoarm" if pair.twoarm else ("hoist" if hoist else "plain")
    want_pins = _expected_pins(pair, H["name"])

    for form, spell in spells:
        if spell is None:
            base_edits = _rename_edits(t, vf_, H["name"])
        else:
            base_edits = _cast_edits(t, vf_, H["name"], tv, th, skips)
            if base_edits is None:
                continue
        # V's own initialiser has to survive as an assignment where the declaration stood
        vplace = vstmt = None
        if V["init"] is not None:
            init = V["init"].strip()
            rhs = ("%s(%s)" % (_cast(th), init)) if spell else init
            vstmt = "%s%s = %s;" % (V["ind"], H["name"], rhs)
            vplace = _demote(F, V)
            if vplace is None:
                skips["init-before-declarations"] += 1
                continue
        hstmt = None if H["init"] is None else (H["ind"] + "%s = %s;" % (H["name"], H["init"].strip()))
        hplace = _demote(F, H) if hstmt else None
        variants = []
        for btag, bt, anchor, moved_keep, moved_bare, between, reach in places:
            if not btag:
                variants.append(("", dict(base_edits), {V["line"]}, {}))
            elif H["init"] is None:
                # a bare declaration emits nothing, so it is legal even above a switch's first case
                variants.append((btag, dict(base_edits), {V["line"], H["line"]},
                                 {anchor: [moved_keep]}))
            else:
                if hplace is not None:
                    e, drop_h, ins_h = dict(base_edits), set(), {}
                    if hplace[0] == "edit":
                        e[H["line"]] = hstmt
                    else:
                        drop_h, ins_h = {H["line"]}, {hplace[1]: [hstmt]}
                    ins_h.setdefault(anchor, []).insert(0, moved_bare)
                    variants.append((btag, e, {V["line"]} | drop_h, ins_h))
                if _const_init(H["init"]) and not between:
                    if not reach:
                        # the initialiser would sit above the first `case` of a switch body, where
                        # control never arrives: the merged variable would be read uninitialised
                        skips["unreachable-anchor"] += 1
                    else:
                        variants.append((btag + "_init", dict(base_edits), {V["line"], H["line"]},
                                         {anchor: [moved_keep]}))
        if not variants:
            skips["init-before-declarations"] += 1
            continue
        for tag, edits, dropped, ins in variants:
            e, ins = dict(edits), {k: list(v) for k, v in ins.items()}
            if vstmt is not None:
                if vplace[0] == "edit":
                    e[V["line"]] = vstmt
                    dropped = {x for x in dropped if x != V["line"]}
                else:
                    ins.setdefault(vplace[1], []).append(vstmt)
            cand = t.build(e, dropped, ins)
            if _pin_key(cand) != want_pins:
                # the surviving pins must be the base text's minus V's own ASM_REG, with V's
                # spelling rewritten wherever a pin names it (`ASM_KEEP(V)` -> `ASM_KEEP(H)`)
                skips["pinsig-changed"] += 1
                continue
            label = "t66:%s:%s%s:%s->%s@$%s%s" % (kind, form, ("+" + tag if tag else ""),
                                                  V["name"], H["name"], pair.reg, mark)
            out.append(("%s/%s%s%s" % (kind, form, ("+" + tag) if tag else "", mark), label, cand))
    return out


def _pin_key(text):
    return collections.Counter((s[1], s[2], (s[6] or "").strip()) for s in sites_of(text))


def sameregmerge_candidates(text, skips=None, cap=MENU_CAP):
    """[(label, text)] - the merges of one text, nearest pairs first, at most `cap`."""
    skips = collections.Counter() if skips is None else skips
    out, seen = [], set()
    try:
        usig = unscored_text(text)
        ppsig = _pp_sig(text)
        pins_in = len(sites_of(text))
        for p in pairs_of(text, skips):
            for form, label, cand in candidates_for(p, skips):
                h = sha_text(cand)
                if h in seen:
                    continue
                seen.add(h)
                if _pp_sig(cand) != ppsig:
                    skips["pp-guarded-edit"] += 1
                    continue
                if unscored_text(cand) != usig:
                    skips["unscored-arm-edit"] += 1
                    continue
                if len(sites_of(cand)) != pins_in - 1:       # `_expected_pins` decided the rest
                    skips["pinsig-changed"] += 1
                    continue
                out.append((label, cand))
                if len(out) >= cap:
                    return out
    except Exception as e:                       # a parse fault costs candidates, never a sweep row
        skips["error:" + type(e).__name__] += 1
    return out


# ------------------------------------------------------------------ the generator

class T:
    name = "t66_sameregmerge"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        sites = sites_of(text)
        if not sites:
            return "no live pins"
        if not row.get("cfg"):
            return "missing compiler recipe"
        regs = collections.Counter(hard_register(s[2]) for s in sites if s[1] == "ASM_REG")
        if not any(n >= 2 for n in regs.values()):
            return "no same-register pin family"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        screens = max(1, int(os.getenv("T66_SCREENS", str(SCREEN_BUDGET))))
        verifies = max(1, int(os.getenv("T66_VERIFY", str(VERIFY_BUDGET))))
        pins_in = len(sites_of(text))
        usig = unscored_text(text)
        ppsig = _pp_sig(text)
        # One Counter PER PASS.  A shared one re-counted every pair refused in pass 1 on every
        # later pass, so a row with three wins reported its refusals four times over (measured
        # 2026-09-15: t66_mid `interference` 174 shared vs 58 first-pass).  `skips` is the FIRST
        # pass - the one whole population, per ordered pair; `skips_all_passes` is the sum.
        allskips, skips = collections.Counter(), collections.Counter()
        forms = collections.Counter()
        log = dict(pins_in=pins_in, pins_out=pins_in, screen_budget=screens, vf_budget=verifies,
                   families=0, pairs=0, candidates_n=0, screened=0, tried=0, compile_failures=0,
                   passes=0, steps=[], nearest=[], distances=[], forms={}, skips={},
                   skips_all_passes={})
        cur, near, dead = text, [], set()
        try:
            first = True
            while True:
                won = False
                skips = collections.Counter()
                log["passes"] += 1
                ref = compile_s(row, cur)
                if ref is None:
                    log["error"] = "reference-build-error"
                    allskips += skips
                    break
                ps = pairs_of(cur, skips)
                if first:
                    fam = collections.Counter(hard_register(s[2]) for s in sites_of(cur)
                                              if s[1] == "ASM_REG")
                    log["families"] = sum(1 for n in fam.values() if n >= 2)
                    log["family_pins"] = sum(n for n in fam.values() if n >= 2)
                    log["pairs"] = len(ps)                     # first pass: the whole population
                    log["distances"] = sorted(p.dist for p in ps)[:12]
                log["pairs_max"] = max(log.get("pairs_max", 0), len(ps))
                seen = set()
                for p in ps:
                    for form, label, cand in candidates_for(p, skips):
                        h = sha_text(cand)
                        if h in seen:
                            continue
                        seen.add(h)
                        if _pp_sig(cand) != ppsig:
                            # the invariant `unscored_text` cannot state: `arm_labels` calls every
                            # line of an `#ifdef __mips__` block `both`, so an edit in its `#else`
                            # arm leaves `unscored_text` untouched.  See PREPROCESSOR REGIONS.
                            skips["pp-guarded-edit"] += 1
                            continue
                        if unscored_text(cand) != usig:
                            skips["unscored-arm-edit"] += 1
                            continue
                        if len(sites_of(cand)) != len(sites_of(cur)) - 1:
                            skips["pinsig-changed"] += 1     # `_expected_pins` decided the rest
                            continue
                        log["candidates_n"] += 1
                        forms[form] += 1
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
                        near.append((d, label, p.dist))
                        if d != 0:
                            continue
                        if not improves(cur, cand):
                            skips["no-improvement"] += 1
                            continue
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
                            log["steps"].append(label)
                            won = True
                            break
                    if won:
                        break
                if first:
                    log["skips"] = dict(sorted(skips.items()))    # the first pass, before any win
                    first = False
                allskips += skips
                if not won:
                    break
        except Exception as e:
            log["error"] = repr(e)
            allskips += skips
        if not log["skips"] and allskips:                        # an exception before the first
            log["skips"] = dict(sorted(allskips.items()))        # pass finished
        log["skips_all_passes"] = dict(sorted(allskips.items()))
        log["forms"] = dict(sorted(forms.items()))
        log["nearest"] = [{"d": d, "label": l, "pair_distance": g}
                          for d, l, g in sorted(near, key=lambda x: (x[0] is None, x[0]))[:12]]
        log["pins_out"] = len(sites_of(cur))
        if not log["steps"]:
            return None, log
        return cur, log
