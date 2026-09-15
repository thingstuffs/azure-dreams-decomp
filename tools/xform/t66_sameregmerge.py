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
label or a called function, an inner-scope local of the same name, a mention of the name that is
itself a DECLARATION of it (a member of an aggregate written out in the function, a stepped-over
table, another declaration at its own line: `mention-in-declaration`, `shadowed-inner-local`), a
declaration or a mention of either variable inside ANY preprocessor region of the function (see
PREPROCESSOR REGIONS below), a multi-declarator or array declaration, and any candidate whose
surviving pins are not exactly the input's minus V's (`_expected_pins`).

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

SIX MORE OPENINGS (2026-09-15, round 30), read off the refusal table of every row of the tree that
still carries a same-register family (138 rows / 2,148 pins, `pairs_of` + `candidates_for` with one
skips Counter - `work/native_lane/r30_samereg3/scratch/census.py`).  Each has its own env switch and
its own journal: the refusal it opens keeps its old key when the switch is OFF, and a
`<class>-reopened` count says how often it fired when it is on.

    T66_DECL_RUN (default 1)          decl-unparsed, 792 ordered pairs in 41 rows - the LARGEST
        refusal, and a scan stopper rather than a parser gap.  `_augment`'s looser walk broke at the
        first line that is neither a multi-line `= {` table nor a MULTIDECL_RE declaration, and every
        declaration below that line was then invisible: the pin's declaration was dropped from the
        family and its pairs charged.  Three shapes stopped it, counted over the hidden declarations:
        the ONE-LINE computed-goto label table `static void *const state_labels[] = { &&jt_c0, ... };`
        and its `__attribute__((used))` spelling (96 in 11 rows - ARRAY_OPEN_RE only knew the
        multi-line form); an anonymous aggregate definition, `struct {` / `volatile struct {` /
        `volatile struct` alone, its members, then `} name;` (80 in 19 rows); and a declarator
        MULTIDECL_RE cannot spell - `s16 vertices[10][6][3];`, `void *volatile perspective_out;`,
        `struct { u16 a, b, c; } camera_angles;` (10 in 6 rows).  All three are now STEPPED OVER
        exactly as the multi-line table was: their declared NAMES are registered so scope resolution
        still sees them, they are never parsed into mergeable declarations, and the walk continues.
        An aggregate is stepped by brace depth to the line that closes it, and a definition whose
        depth returns to 0 on a line that does not end in `;` still breaks the walk.  (The residue is
        three `{ register s32 implicit_hi ASM_REG("hi"); ... }` one-line BLOCKS in one row: m2c's
        HI/LO idiom, which has no declaration run to walk at all.)
    T66_ASM_OPERAND (default 1)       asm-operand-cast, 44 pairs in 14 rows.  See `_cast_edits`.
    T66_INIT_PLACE (default 1)        init-before-declarations, 92 pairs in 10 rows.  See `_demote`
        and `_init_place_refusal`.
    T66_SHADOW (default 1)            shadowed-inner-local, 32 pairs in 5 rows.  See `_shadow_inners`
        and `_shadow_retry`.
    T66_COMPOUND (default 1)          compound-assign-cast, 17 pairs in 9 rows.  See `_cast_edits`.
    T66_TRY_INTERFERENCE (default 0)  interference, 224 pairs in 43 rows.  A pair whose lifetimes
        clash at the C level is offered ANYWAY, with the ordinary rename/cast forms, and the screen
        and `vf` decide.  The argument: both variables are bound to ONE hard register in a row that
        is byte-exact today, so the compiled program never holds both values at once.  A clash in the
        C text is therefore either this module's liveness over-approximating (a kill it does not
        recognise, a dead arm, a back edge carrying a dead value, an unknown statement that reaches
        every later node) or an m2c artefact - m2c names one temporary per use (`event_x_1` ..
        `event_x_8`, all on `$2` in `dungeon/func_812A524C`) and a later temporary's "read" takes the
        earlier one's value through the shared register - in which case the merged text is the more
        honest C.  Acceptance is `vf`'s byte verdict, as for every other form; nothing else in the
        module is relaxed, and `loop-backedge` keeps its own refusal.  Each pair is journaled
        `interference-nested` (one live range inside the other) or `interference-overlap`, and a
        clashing pair sorts AFTER every clean one so the screen budget is spent on the clean pairs
        first.  Measured over the 138 family rows: 452 nested, 8 overlap.

NOT opened, and why (the same table, read at the candidate stage):
    type-mismatch-narrow (88 pairs / 32 rows)  the width rule.  Merging an s8/u8/s16/u16 with a word
        changes the width of the value, which is a different program.
    pp-guarded-mention (33 / 9)                policy: this module never edits a preprocessor arm.
    host-name-collision (138 / 6)              NOT a name problem.  Every one of those pairs also
        carries `init-before-declarations` or `asm-operand-cast`: T66_RENAME_HOST's rename SUCCEEDS
        and `candidates_for` then refuses the renamed pair downstream, at which point the old
        `collide` count is charged anyway.  The 9 `host-rename-pair-lost` are the `vname` attempt
        making two declarations of one name (a shadow in the re-read), which falls through to the
        fresh `<host>_m`.  It is a journaling artefact over another refusal, so it needs no opening
        of its own and it falls when they open: 138 -> 56 over the same population.

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
    round 30 (`work/native_lane/r30_samereg3/REPORT.md`, the six openings above).  The refusal table
        over every row of the tree that still carries a same-register family (138 rows / 2,148 pins)
        moved from 262 ordered pairs offered / 40 candidates / ONE row with a candidate to 706 / 629
        / 42 rows at the defaults, and to 1,168 / 1,053 / 79 rows with T66_TRY_INTERFERENCE=1.
        `decl-unparsed` 792 -> 100 (`decl-unparsed-reopened` 692: the two columns add up), `asm-operand-cast` 44 -> 0, `init-before-declarations` 92 -> 48,
        `compound-assign-cast` 17 -> 0 (3 multi-line writes keep `write-multiline-cast`),
        `host-name-collision` 138 -> 56 with no opening of its own.  Three lane_eval packs:
        `t66v3_decl` (the 41 `decl-unparsed` rows) 25 of 41 exact, 53 pins; `t66v3_forms` (the 29
        rows of the five candidate-stage refusals) 21 of 29, 33 pins; `t66v3_interf` (the 43
        `interference` rows, T66_TRY_INTERFERENCE=1) 37 of 43, 81 pins - 75 DISTINCT rows and 146
        pins, six rows being in two or three of the packs.  Per opening, by replaying
        each row's menu with that one switch off (a candidate marked by two is counted in both):
        T66_DECL_RUN 456 candidates newly offered, 46 exact; T66_ASM_OPERAND 150 / 40;
        T66_COMPOUND 69 / 18; T66_INIT_PLACE 82 / 6; T66_SHADOW 2 / 1; T66_TRY_INTERFERENCE
        196 / 69.  No budget was reached, no candidate failed to compile, and every candidate that
        reached `vf` was exact (167 screened-to-0 candidates, 167 verifies, 167 hits).
        REGRESSION: with all six openings off the module offers the SAME candidates byte for byte as
        the round-29 module over the 110 frozen bases of the round-29 packs (110 of 110 identical,
        labels and skip tables included), and `lane_eval --tag t66v3_regress` over 20 of those rows
        reproduces the round-29 outcome, candidate count, pair count, skip table and steps, 20 of 20.
        103 unit tests.
    round 30, REVIEW (same REPORT, "Review fixes"): a review demonstrated three defects, all three
        of them mechanisms that PREDATE round 30 (the round-29 module emits the same candidates) and
        all three unexposed on today's tree - round 30 is what would have put a population in front
        of the first one.  (1) A mention of the pin's name that is itself a DECLARATION was renamed:
        a member line `s32 second;` inside `struct { ... } box;` is a `_occ` mention, and
        `F.resolve` cannot return a declaration it never registered (it also requires
        `d["line"] < k`, so an inner local at its OWN line resolved to the pin), so the rename
        rewrote a struct member or an unrelated declaration, byte-neutrally, with nothing journalled.
        Fixed in `Facts` against `F.declspans` (`_agg_spans`, found whether the declaration walk
        reached the aggregate or not) and against `F.byname`; the declaration-line capture is
        journalled as the shadow it is and T66_SHADOW's retry now reopens it.  (2) T66_INIT_PLACE
        tested the CROSSED initialisers for a mention of the pair and for a call, but not for a side
        effect of their own: `s32 tail = arg0[idx++];` crossed by `first = arg0[idx];` reads
        `arg0[idx + 1]` in the candidate.  Fixed (`crossed-init-has-side-effects`), and the gate now
        reads `_crossed_init`, so a crossed initialiser the parse DROPPED (`init=None` for a
        multi-declarator or a declarator spread over lines) is read off the source instead of
        passing unexamined.  (3) T66_ASM_OPERAND spelled the surviving name BARE for any mention
        inside an `ASM_*` argument, but its argument ("the operand is the register") holds only
        where the mention IS the argument: `ASM_KEEP_DEP_NV(total, scaled + 1)` became
        `(total, page + 1)`, `s32 + 1` read as `u8 * + 1`.  Fixed with a whole-argument test
        (`_MacroIdx.whole_arg`, which spans continuation lines); a sub-expression refuses the cast
        form (`asm-operand-cast-subexpr`) and leaves the rename form alone.  Cost, measured: the
        census over the 138 family rows is IDENTICAL to round 30's, per row and per skip key, at the
        defaults (706 pairs / 629 candidates) and with T66_TRY_INTERFERENCE=1 (1,168 / 1,053), the
        three new keys reading 0 in both; the four packs rerun as `samereg32b_*` reproduce
        `t66v3_*` row for row (133 of 133: outcome, pins, candidate sha, menu size, pair count,
        steps and skip table), 25/53, 21/33, 37/81 and the 20-row regression; and with every opening
        off the module still offers the round-29 module's candidates byte for byte over its 110
        frozen bases (110 of 110).  117 unit tests.
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
        self.text = "\n".join(ml)
        self.calls = _calls_in(self.text, known)

    def at(self, line, col):
        if line >= len(self.off):
            return []
        p = self.off[line] + col
        return [(c[0], _slot_of(c, p)) for c in self.calls if c[1] < p < c[2]]

    def whole_arg(self, line, col, end, pred):
        """Does the text [col, end) on `line` fill the WHOLE argument of every enclosing call
        `pred` names?  `ASM_KEEP(v)` yes, `ASM_KEEP_DEP_NV(total, v + 1)` no (see
        `_asm_arg_mentions`)."""
        if line >= len(self.off):
            return False
        p0, p1 = self.off[line] + col, self.off[line] + end
        for c in self.calls:
            if not (c[1] < p0 < c[2]) or not pred(c[0]):
                continue
            sp = next(((a, b) for a, b in c[3] if a <= p0 < b), None)
            if sp is None or self.text[sp[0]:sp[1]].strip() != self.text[p0:p1]:
                return False
        return True


def _calls_at(s, pos, known=()):
    """`_MacroIdx.at` for a single string - the one-line form, kept for direct callers."""
    return [(c[0], _slot_of(c, pos)) for c in _calls_in(s, known) if c[1] < pos < c[2]]


def _is_asm_macro(name):
    return name.startswith("ASM_")


def _whole_arg_at(s, col, end, known, pred):
    """`_MacroIdx.whole_arg` for a single string - the one-line form."""
    for c in _calls_in(s, known):
        if not (c[1] < col < c[2]) or not pred(c[0]):
            continue
        sp = next(((a, b) for a, b in c[3] if a <= col < b), None)
        if sp is None or s[sp[0]:sp[1]].strip() != s[col:end]:
            return False
    return True


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
        self.asm_partial = set()           # (line, column) inside an ASM_* argument, but not ALL of it
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
            if any(lo <= k <= hi for lo, hi in getattr(F, "declspans", ())):
                # The line is part of a DECLARATION, not a statement: a member of an aggregate
                # written out here, a stepped-over table, a declarator this module does not parse.
                # `F.resolve` cannot see a declaration it never registered and would hand this
                # mention to the pin's own declaration, so the rename would rewrite a struct
                # MEMBER (round 30 review, defect 1).
                self.ok, self.reason = False, "mention-in-declaration"
                continue
            if any(x is not d and x["line"] <= k <= x["end"]
                   for x in F.byname.get(self.name, ())):
                # the mention is another declaration OF THE SAME NAME, at its own line: `resolve`
                # requires `d["line"] < k` and so returns the outer pin even for an inner local it
                # did register.  Named like the resolve-based refusal below, because it is the same
                # capture and T66_SHADOW's retry reopens it the same way.
                self.ok, self.reason = False, "shadowed-inner-local"
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
                    names = [n for n, _ in encl]
                    self.macro_mentions.setdefault(k, []).append((m.start(), names))
                    if any(_is_asm_macro(n) for n in names) and not (
                            midx.whole_arg(k, m.start(), m.end(), _is_asm_macro)
                            if midx is not None else
                            _whole_arg_at(s, m.start(), m.end(), refuse, _is_asm_macro)):
                        # the mention is a SUB-EXPRESSION of the ASM_* argument, not the argument:
                        # T66_ASM_OPERAND's bare spelling would drop the cast from part of an
                        # expression (round 30 review, defect 3).
                        self.asm_partial.add((k, m.start()))
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


def interference(flow, a, b, kind=None):
    """None when the two variables can be one, else the reason.

    `kind` is an optional one-element list the clash shape is written into for the journal:
    `nested` when one variable's live range lies inside the other's, else `overlap` (see
    T66_TRY_INTERFERENCE in the module docstring).
    """
    ain, aout = live(flow, a)
    bin_, bout = live(flow, b)
    clash = [k for k in flow.nodes
             if (ain.get(k) and bin_.get(k)) or (aout.get(k) and bout.get(k))]
    if not clash:
        return None
    if kind is not None:
        sa = [k for k in flow.nodes if ain.get(k) or aout.get(k)] + a.lines
        sb = [k for k in flow.nodes if bin_.get(k) or bout.get(k)] + b.lines
        lo_a, hi_a, lo_b, hi_b = min(sa), max(sa), min(sb), max(sb)
        kind.append("nested" if (lo_a <= lo_b and hi_b <= hi_a)
                    or (lo_b <= lo_a and hi_a <= hi_b) else "overlap")
    for o, c in flow.F.loops:
        if any(o < k < c for k in clash) and any(o < k < c for k in a.lines) \
                and any(o < k < c for k in b.lines):
            return "loop-backedge"
    return "interference"


# ------------------------------------------------------------------ candidates

class Pair:
    __slots__ = ("F", "flow", "H", "V", "hf", "vf_", "reg", "block", "dist", "twoarm",
                 "base", "sites", "interf", "shadow")


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

# ---------------------------------------------------------------- T66_DECL_RUN (round 30, opening 1)
# The three shapes the looser walk used to break on.  Each is STEPPED OVER: its declared names are
# registered so scope resolution still sees them, and none of them is ever parsed into a mergeable
# declaration (they are aggregates, tables and arrays - no pin merges into one).
#
# (a) the label table, on ONE line as well as the multi-line `= {` form ARRAY_OPEN_RE already knew,
#     and with the `__attribute__((used))` spelling between the brackets and the `=`;
ARRAY_RUN_RE = re.compile(
    r"^[ \t]*(?:(?:static|const|register|volatile|unsigned|signed|struct|union|enum)[ \t]+)*"
    r"%s(?:(?:[ \t]*\*)+[ \t]*|[ \t]+)(?:(?:const|volatile)(?:[ \t]*\*)*[ \t]+)*%s"
    r"(?:[ \t]*\[[^\]]*\])+(?:[ \t]*__attribute__[ \t]*\(\(.*\)\))?[ \t]*=[ \t]*\{" % (ID, ID))
# (b) an aggregate DEFINITION opened in the declaration run: `struct {`, `volatile struct {`,
#     `volatile struct` alone with the brace on the next line, or `struct Tag {`.  Stepped by brace
#     depth to the line that closes it; the names come from that closing line (`} camera_angles;`).
AGG_OPEN_RE = re.compile(
    r"^[ \t]*(?:(?:static|const|register|volatile|unsigned|signed)[ \t]+)*"
    r"(?:struct|union|enum)\b(?:[ \t]+%s)?[ \t]*(?:\{.*)?$" % ID)
# (c) a declarator MULTIDECL_RE cannot spell: a multi-dimensional array (`s16 v[10][6][3];`) or a
#     qualifier behind the pointer stars (`void *volatile perspective_out;`).  Otherwise identical to
#     MULTIDECL_RE, so it can never step over a statement MULTIDECL_RE would have stopped at.
RUNDECL_RE = re.compile(
    r"^[ \t]*(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*"
    r"%s(?:(?:[ \t]*\*)+[ \t]*|[ \t]+)(?:(?:const|volatile)(?:[ \t]*\*)*[ \t]+)*"
    r"\(?\*?%s\)?(?:[ \t]*\([^;]*\))?(?:[ \t]*\[[^\]]*\])*"
    r"(?:[ \t]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\))?"
    r"(?:[ \t]*,[ \t]*\**%s(?:[ \t]*\[[^\]]*\])*)*[ \t]*(?:=[^;]*)?;[ \t]*$" % (ID, ID, ID))


def _agg_close(F, k, c):
    """(line, column) of the brace that closes an aggregate definition opened at line `k`, or None.

    Brace depth from `k`; the opening brace may sit on `k` itself or on the line below it (m2c
    writes `volatile struct` and then `{`).  A definition whose depth returns to 0 on a line that
    does not end in `;` is NOT stepped over - the walk breaks there rather than guess what follows.
    The COLUMN matters: `} camera_angles = {1, 2};` closes the aggregate at the first brace, and
    slicing from the last one would take the initialiser's `}` and lose the declared name.
    """
    depth, seen = 0, False
    for j in range(k, min(c, len(F.ml))):
        s = F.ml[j]
        if not seen and j > k + 1:
            return None                      # no `{` where an aggregate definition must have one
        for i, ch in enumerate(s):
            if ch == "{":
                depth, seen = depth + 1, True
            elif ch == "}":
                depth -= 1
                if seen and depth <= 0:
                    return (j, i) if s.rstrip().endswith(";") else None
    return None


def _agg_spans(F):
    """[(first line, last line)] of every aggregate DEFINITION written out inside this function.

    Found independently of the declaration-run walk (round 30 review, defect 1): the walk sees an
    aggregate only where it steps over one, and the member lines of an aggregate it never reached -
    it broke above, or `T66_DECL_RUN` is off - are ordinary lines to `Facts`.  A member line
    `s32 second;` is then a `_occ` mention of the pin variable `second` whose own declaration is
    the OUTER one (`F.resolve` needs `d["line"] < k`, so it cannot return a member it never
    registered), and the rename rewrites a STRUCT MEMBER.  Byte-neutral where nothing else names
    the member, so nothing downstream catches it.

    Spans cover the opening line through the closing `} name;` (which declares a name of its own).
    The close is found by brace depth ALONE, not by `_agg_close`, which also demands that the
    closing line end in `;` before the walk may step over it: a declarator this module cannot read
    is a reason to refuse the rename, never a reason to leave the members exposed to it.
    """
    out, c = [], min(F.b, len(F.ml))
    for k in range(F.a, c):
        if not AGG_OPEN_RE.match(F.ml[k]):
            continue
        depth, seen, end = 0, False, None
        for j in range(k, c):
            if not seen and j > k + 1:
                break                        # no `{` where an aggregate definition must have one
            for ch in F.ml[j]:
                if ch == "{":
                    depth, seen = depth + 1, True
                elif ch == "}":
                    depth -= 1
            if seen and depth <= 0:
                end = j
                break
        if end is not None:
            out.append((k, end))
    return out


ATTRIBUTE_RE = re.compile(r"__attribute__[ \t]*\(\(.*?\)\)", re.S)
STATIC_RE = re.compile(r"^[ \t]*(?:(?:const|volatile|register|unsigned|signed)[ \t]+)*static\b")
INIT_EQ_RE = re.compile(r"(?<![=!<>+\-*/%&|^])=(?!=)")


def _run_names(F, blk, k, end, s, arr=False):
    """Register the names a stepped-over declaration declares, and nothing else about it.

    An `__attribute__((...))` is cut out first: `natural._decl_names` takes the LAST identifier of a
    declarator, so `void *const state_labels[] __attribute__((used)) = {...}` would register `used`
    and lose `state_labels` - the one thing this branch exists to register.

    `init` matters even though nothing mergeable is read out of these: `_init_place_refusal` walks
    the initialisers a demoted assignment would cross, and a stepped-over declaration that carried
    one and reported None would be a crossing it never tested.  A `static` initialiser does not run
    at block entry, so that one is None; every other `=` records the text after it, which is all the
    refusal reads (a mention of V or H, a call).
    """
    body = ATTRIBUTE_RE.sub(" ", s)
    m = None if STATIC_RE.match(body) else INIT_EQ_RE.search(body)
    init = body[m.end():] if m else None
    for n in N._decl_names(body):
        F.decls.setdefault(blk, []).append(dict(
            line=k, end=end, name=n, block=blk, single=False, ty=None, quals=set(), run=True,
            init=init, arr=arr, pinned="ASM_REG" in s, spell=None, ind=N._ind(F.ml[k])))


def _augment(F):
    """Declarations `natural._Fn` stopped short of.

    Its block scan breaks at the first line its declaration regex does not recognise, and one
    `M2C_UNK (*update_actor)(void *, void *);` in the middle of a 90-line declaration run hides
    every declaration under it - 75 of the pins in the two evaluation packs.  This walks the same
    run with a looser test and adds what is missing (a line it cannot parse into a type still
    registers its NAMES, so scope resolution still sees them).

    T66_DECL_RUN (round 30, opening 1) steps over three more shapes the same way - the one-line
    computed-goto label table, an aggregate definition, and a declarator MULTIDECL_RE cannot spell -
    instead of breaking on them and hiding every declaration below (792 ordered pairs, 41 rows,
    `decl-unparsed`).  With the switch off the loop body is exactly what it was.
    """
    run_on = _env_on("T66_DECL_RUN")
    F.runsteps = []                        # (shape, first line, last line) of every stepped-over run
    for blk in F.blocks:
        o, c = blk
        known = {d["line"] for d in F.decls.get(blk, [])}
        stop = max(known) + 1 if known else o + 1
        k = stop
        stepped = False                    # a T66_DECL_RUN stopper has been walked past in THIS block
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
                F.runsteps.append(("array-multiline", k, end))
                k = end + 1
                continue
            if not s.rstrip().endswith(";") or not MULTIDECL_RE.match(s):
                first = re.match(ID, s.strip())
                if not run_on or not first or first.group(0) in N.CTRL:
                    # `return x;` and `case 3:` are not declarations, whatever a declarator regex
                    # makes of them: the run ENDS there rather than stepping over a statement.
                    break
                if ARRAY_RUN_RE.match(s):
                    # (a) the label table on one line, and the `__attribute__((used))` spelling
                    end = k
                    while end < c and not F.ml[end].rstrip().endswith(";"):
                        end += 1
                    if end >= c:
                        break
                    _run_names(F, blk, k, end, " ".join(F.ml[k:end + 1]), arr=True)
                    F.runsteps.append(("array", k, end))
                    stepped = True
                    k = end + 1
                    continue
                if AGG_OPEN_RE.match(s):
                    # (b) `struct {` / `volatile struct` ... `} name;` - by brace depth
                    close = _agg_close(F, k, c)
                    if close is None:
                        break
                    end, col = close
                    _run_names(F, blk, k, end, F.ml[end][col:])
                    F.runsteps.append(("aggregate", k, end))
                    stepped = True
                    k = end + 1
                    continue
                if RUNDECL_RE.match(s):
                    # (c) `s16 v[10][6][3];`, `void *volatile perspective_out;`
                    _run_names(F, blk, k, k, s)
                    F.runsteps.append(("declarator", k, k))
                    stepped = True
                    k += 1
                    continue
                break
            m = N.VDECL_RE.match(s)
            if m and m.group("base") not in N.CTRL:
                q = m.group("q").split()
                F.decls.setdefault(blk, []).append(dict(
                    line=k, end=k, name=m.group("n"), block=blk, single=True, run_below=stepped,
                    ty=N._ptype(q, m.group("base"), m.group("ptr")), quals=set(q),
                    init=m.group("init"), arr=bool(m.group("arr")), pinned=bool(m.group("asm")),
                    spell=m.group("spell").strip(), ind=m.group("i")))
            else:
                for n in N._decl_names(s):
                    F.decls.setdefault(blk, []).append(dict(
                        line=k, end=k, name=n, block=blk, single=False, ty=None, quals=set(),
                        init=None, arr=False, pinned="ASM_REG" in s, spell=None, ind=N._ind(s),
                        run_below=stepped))
            k += 1
    # Every line whose text belongs to a declaration rather than to a statement: the runs this walk
    # stepped over, plus every aggregate definition in the function whether the walk reached it or
    # not (round 30 review, defect 1 - see `_agg_spans`).  `Facts` refuses a mention there.
    F.declspans = [(lo, hi) for _, lo, hi in F.runsteps] + _agg_spans(F)
    F.byname = {}
    for d in [x for ds in F.decls.values() for x in ds] + F.params:
        F.byname.setdefault(d["name"], []).append(d)
    F._vars = {}
    return F


def _functions(t):
    return [_augment(F) for F in N._functions(t)]


def _fn_of(fns, line):
    return next((F for F in fns if F.a < line < F.b), None)


def _fresh(t, base, taken=()):
    """`<base>_s`, or `_s2`.. when that is taken: a name no word of the file already is, and none
    this text has already handed out (two inner locals of one file may share a base name)."""
    for suffix in ["_s"] + ["_s%d" % i for i in range(2, 10)]:
        cand = base + suffix
        if cand not in taken and not re.search(r"\b%s\b" % re.escape(cand), t.mtext):
            return cand
    return None


def _rename_many(t, plan):
    """{line: new line} for a plan of {line: [(old name, new name)]}.

    One pass per LINE over every rename it carries, positions taken from the original masked line
    and applied right to left.  `natural._rename` chains only renames of ONE name: a second call on
    a line the first already edited would splice at stale offsets, which is how two inner locals
    renamed on one line would have lost the first rewrite.
    """
    edits = {}
    for k, subs in plan.items():
        ln = N._nl(t.lines[k])
        hits = []
        for old, new in subs:
            hits += [(m.start(), m.end(), new) for m in N._occ(old).finditer(t.m[k])]
        for a, b, new in sorted(hits, reverse=True):
            ln = ln[:a] + new + ln[b:]
        edits[k] = ln
    return edits


def _shadow_inners(F, d, flow):
    """The inner declarations that capture `d`'s name inside `d`'s block, or None when one of them
    may not be renamed (T66_SHADOW, round 30, opening 4).

    Refused: a parameter or a global (there is no inner block to rename in); a declaration this
    module cannot spell as a plain scalar local - an aggregate member, a table, a multi-declarator -
    since `natural._occ` skips `.x`/`->x` and the rename would then touch the declaration alone;
    an inner local that is ITSELF an `ASM_REG` pin (the merge may not respell another pin's
    variable); a mention in a preprocessor region; and a mention in a macro argument slot the
    classifier calls a NAME (or in a stringifier, or in a macro whose body is out of reach).
    """
    o, c = d["block"]
    rx = N._occ(d["name"])
    inners, lines = {}, collections.defaultdict(set)
    for k in range(o + 1, min(c, len(F.ml))):
        if k == d["line"] or not rx.search(F.ml[k]):
            continue
        other = F.resolve(d["name"], k)
        if other is None or other is d:
            # the capture AT the inner declaration's own line: `resolve` requires `d["line"] < k`,
            # so it hands that line to the outer declaration (round 30 review, defect 1).
            other = next((x for x in F.byname.get(d["name"], ())
                          if x is not d and x["line"] <= k <= x["end"]), None)
        if other is None or other is d:
            continue
        if other.get("param") or not other["single"] or not other["ty"] or other["pinned"] \
                or other["arr"] or other["line"] != other["end"]:
            return None
        ob = other["block"]
        if not (o < ob[0] and ob[1] <= c):
            return None
        inners[other["line"]] = other
        lines[other["line"]].add(k)
    if not inners:
        return None
    for line, other in inners.items():
        ob = other["block"]
        want = {line}
        for k in range(line, min(ob[1], len(F.ml))):
            if rx.search(F.ml[k]) and (k == line or F.resolve(d["name"], k) is other):
                want.add(k)
        if any(k in flow.pp for k in want):
            return None
        for k in want:
            for m in rx.finditer(F.ml[k]):
                encl = flow.midx.at(k, m.start())
                if encl and _macro_arg_refusal(encl, flow.macro_refuse, flow.mtable,
                                               flow.macro_ok):
                    return None
        lines[line] = want
    return [(inners[line], sorted(lines[line])) for line in sorted(inners)]


def _shadow_retry(text, entries, skips):
    """One text with every capturing inner local renamed, re-read for the pairs it now offers.

    Mechanically the same move as `_rename_host`: a SEPARATE TEXT, re-parsed and merged by the
    ordinary path, so `Facts`, the liveness test, the collision test and the preprocessor guards
    all fire again on what the compiler will actually see.  A local's name is byte-neutral on this
    port; where the inner local is named by a statement pin (`ASM_KEEP(inner)`) the pin's ARGUMENT
    is respelled with it, exactly as T66_MACRO_ARGS respells the victim's - the pin count and the
    keep's position do not move, and `_expected_pins` asserts the whole multiset against THIS text.
    """
    t = N._T(text)
    plan, want, taken, touched = collections.defaultdict(list), set(), set(), 0
    for F, d, flow in entries:
        got = _shadow_inners(F, d, flow)
        if got is None:
            skips["shadow-inner-refused"] += 1
            continue
        sub = []
        for other, lines in got:
            new = _fresh(t, other["name"], taken)
            if new is None:
                sub = None
                break
            taken.add(new)
            sub.append((other, lines, new))
        if not sub:
            skips["shadow-name-taken"] += 1
            continue
        for other, lines, new in sub:
            for k in lines:
                plan[k].append((other["name"], new))
            if (other["name"], other["line"]) in F.pinned:
                touched += 1
        want.add(d["line"])
    if not plan:
        return []
    try:
        text1 = t.build(_rename_many(t, plan))
    except Exception:
        skips["shadow-build-failed"] += 1
        return []
    if _pp_sig(text1) != _pp_sig(text) or unscored_text(text1) != unscored_text(text):
        skips["shadow-build-failed"] += 1        # unreachable by construction; the assertion stands
        return []
    if touched:
        skips["shadow-renames-a-pin-argument"] += touched
    got = []
    for p in pairs_of(text1, collections.Counter(), _shadow=False):
        if p.H["line"] not in want and p.V["line"] not in want:
            continue
        p.shadow = True
        got.append(p)
    skips["shadowed-inner-local-reopened"] += len(got)
    return got


def pairs_of(text, skips=None, _shadow=True):
    """Every ordered (host, victim) pair of same-register ASM_REG declarations whose lifetimes are
    disjoint, nearest first.  `skips` counts the refusals.

    `_shadow` is False on the ONE level of re-entry T66_SHADOW and T66_RENAME_HOST allow: the text
    those build has already had its shadowing inner locals renamed."""
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
    try_interf = _env_on("T66_TRY_INTERFERENCE", "0")
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
    shadowed = {}
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
                if factcache[d["line"]].reason == "shadowed-inner-local":
                    shadowed[d["line"]] = (F, d, flow)
                decls.append((d, factcache[d["line"]]))
            # Every skip below is counted per ORDERED PAIR; the declarations dropped just above
            # cost pairs too, so charge them at the same scale instead of once per declaration.
            n, k_ = len(members), len(decls)
            if k_ < n:
                skips["decl-unparsed"] += n * (n - 1) - k_ * (k_ - 1)
            r = sum(1 for d, _ in decls if d.get("run_below"))
            if r:
                # T66_DECL_RUN: the declarations only this opening reaches, charged at the same
                # ordered-pair scale, so `decl-unparsed` + `decl-unparsed-reopened` is the count a
                # T66_DECL_RUN=0 run reports.
                skips["decl-unparsed-reopened"] += k_ * (k_ - 1) - (k_ - r) * (k_ - r - 1)
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
                    kind = []
                    why = interference(flow, fh, fv, kind)
                    interf = None
                    if why:
                        if why != "interference" or not try_interf:
                            skips[why] += 1
                            continue
                        # T66_TRY_INTERFERENCE: both variables are bound to ONE hard register in a
                        # row that is byte-exact today, so the compiled program never holds both
                        # values at once - the C-level clash is liveness over-approximating or an
                        # m2c artefact.  The merged text is offered and `vf` decides (docstring).
                        interf = kind[0] if kind else "overlap"
                        skips["interference-reopened"] += 1
                        skips["interference-" + interf] += 1
                    p = Pair()
                    p.F, p.flow, p.H, p.V, p.hf, p.vf_, p.reg = F, flow, dh, dv, fh, fv, reg
                    p.base, p.sites, p.interf, p.shadow = text, sites, interf, None
                    p.block = F.encl(min(fh.lines + fv.lines), max(fh.lines + fv.lines))
                    p.dist = min(abs(x - y) for x in fh.lines for y in fv.lines)
                    p.twoarm = _arms(F, dh["block"], dv["block"])
                    if fh.macro_mentions or fv.macro_mentions:
                        # an ordered pair the `in-macro-arg` refusal used to cost (informational:
                        # it is offered, not skipped - the before/after table reads it beside the
                        # `in-macro-arg` count a T66_MACRO_ARGS=0 run still reports)
                        skips["in-macro-arg-reopened"] += 1
                    out.append(p)
    if shadowed and _shadow and _env_on("T66_SHADOW"):
        seen = {(p.H["line"], p.V["line"], p.reg) for p in out}
        out += [p for p in _shadow_retry(text, list(shadowed.values()), skips)
                if (p.H["line"], p.V["line"], p.reg) not in seen]
    # a pair whose lifetimes clash goes LAST: the clean pairs have first call on the screen budget
    out.sort(key=lambda p: (bool(p.interf), p.dist, p.H["line"], p.V["line"]))
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


SIDE_EFFECT_RE = re.compile(r"(?<![=!<>+\-*/%&|^])=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--")


def _crossed_init(F, x):
    """The initialiser text of a crossed declaration, read from its SOURCE when the parse dropped it.

    `natural._block_decls` and `_augment`'s fallback branch record `init=None` for every declaration
    line `VDECL_RE` cannot spell - a multi-declarator, a declarator spread over lines, a non-static
    table - so a crossing that carries an initialiser reported none and was invisible to the whole
    refusal (round 30 review, defect 2).  A `static` initialiser does not run at block entry (it is
    not a crossing at all), so that one stays None; everything else is read off the masked lines of
    the declaration with its `ASM_REG(...)` and `__attribute__((...))` cut out, and whatever follows
    the first `=` is handed to the tests.  A multi-declarator's remainder (`1, b = 2`) carries the
    `=` of the second declarator and therefore refuses - the conservative answer, which is correct.
    """
    if x["init"] is not None:
        return x["init"]
    s = " ".join(F.ml[x["line"]:min(x["end"], len(F.ml) - 1) + 1])
    if STATIC_RE.match(F.ml[x["line"]]):
        return None
    body = ATTRIBUTE_RE.sub(" ", re.sub(r"ASM_REG[ \t]*\([^)]*\)", " ", s))
    m = INIT_EQ_RE.search(body)
    return body[m.end():] if m else None


def _init_place_refusal(F, later, guard, moved_init):
    """T66_INIT_PLACE: why the demoted assignment may NOT cross these declarations, or None.

    The demoted assignment lands after the LAST declaration of the run, so it now runs AFTER every
    initialiser those declarations carry, where it used to run before them.  That is the same
    program only when neither order can see the difference:

      - no crossed initialiser reads V or H (it would read the value the move is carrying);
      - no crossed initialiser calls anything (a call may read or write whatever the moved
        assignment reads or writes);
      - no crossed initialiser has a side effect of its own (`++`, `--`, an embedded assignment):
        the demoted assignment now runs AFTER it and would read the value it left behind
        (`s32 tail = arg0[idx++];` crossed by `first = arg0[idx];` - round 30 review, defect 2);
      - the moved initialiser does not name a crossed declaration (it would read an initialised
        value where it used to read an uninitialised one, and vice versa);
      - the moved initialiser neither calls anything nor assigns (its own side effects would then
        happen after the crossed initialisers ran).

    Every test is one-sided: a false refusal costs a candidate, a false pass changes the program.
    """
    inits = [i for i in ((x, _crossed_init(F, x)) for x in later) if i[1] is not None]
    if not inits:
        return None
    rxs = [N._occ(g) for g in guard if g]
    for _, init in inits:
        if any(rx.search(init) for rx in rxs):
            return "crossed-init-reads-the-pair"
        if CALL_RE.search(init):
            return "crossed-init-calls"
        if SIDE_EFFECT_RE.search(init):
            return "crossed-init-has-side-effects"
    names = {x["name"] for x in later}
    mv = moved_init or ""
    if any(n in names for n in re.findall(ID, mv)):
        return "moved-init-reads-a-crossed-declaration"
    if CALL_RE.search(mv) or SIDE_EFFECT_RE.search(mv):
        return "moved-init-has-side-effects"
    return None


def _demote(F, d, guard=(), moved_init=None, skips=None):
    """Where the assignment that replaces declaration `d` may go, as (kind, line).

    A declaration in the middle of a block's declaration run cannot simply become a statement:
    C89 puts every declaration first, so `register s32 next ASM_REG("$4");` two lines below would
    then be a syntax error (17 candidates in the mid pack before this was measured).  The
    assignment goes after the LAST declaration of that block instead - and, before round 30, only
    when none of the declarations it now follows has an initialiser of its own, because those
    initialisers run in declaration order and one of them may read the very value being moved
    (`init-before-declarations`, 92 ordered pairs in 10 rows).  T66_INIT_PLACE tests that instead
    of assuming it: see `_init_place_refusal`.
    """
    later = [x for x in (F.decls.get(d["block"]) or []) if x["line"] > d["line"]]
    if not later:
        return ("edit", d["line"]) if _reaches(F, d["block"], d["line"]) else None
    if any(_crossed_init(F, x) is not None for x in later):
        # `_crossed_init`, not `x["init"]`: a crossed declaration whose initialiser the parse
        # dropped used to pass this gate unexamined (round 30 review, defect 2).
        if not _env_on("T66_INIT_PLACE"):
            return None
        why = _init_place_refusal(F, later, guard, moved_init)
        if why:
            if skips is not None:
                skips["init-place-" + why] += 1
            return None
        if skips is not None:
            skips["init-before-declarations-reopened"] += 1
    at = max(x["end"] for x in later)
    return ("after", at) if _reaches(F, d["block"], at) else None


def _rename_edits(t, facts, new, edits=None):
    return N._rename(t, list(facts.mentions), facts.name, new, edits)


COMPOUND_RE = re.compile(r"^(?P<i>[ \t]*)%s[ \t]*(?P<op><<|>>|[-+*/%%&|^])=(?!=)(?P<rhs>[^;]*);(?P<tail>.*)$")
INCDEC_RE = re.compile(r"^(?P<i>[ \t]*)(?:(?P<pre>\+\+|--)%s|%s(?P<post>\+\+|--))[ \t]*;(?P<tail>.*)$")


def _asm_arg_mentions(facts):
    """({(line, col)} inside an `ASM_*` argument, {(line, col)} ALSO inside something else).

    The second set is the shape T66_ASM_OPERAND may not spell either way: `ASM_KEEP(U16_AT(p, v))`
    can take neither the cast (the asm operand would not be an lvalue) nor the bare name (the inner
    macro would lose the cast, and with it the signedness the merge is sound in).  It is refused as
    `asm-operand-cast-mixed-macro`, and it does not occur in the tree today.
    """
    asm, mixed = set(), set()
    for k, hits in facts.macro_mentions.items():
        for col, encl in hits:
            if not any(_is_asm_macro(x) for x in encl):
                continue
            asm.add((k, col))
            if not all(_is_asm_macro(x) for x in encl):
                mixed.add((k, col))
    return asm, mixed


PLAINWRITE_RE = re.compile(r"^(?P<i>[ \t]*)%s[ \t]*=(?!=)(?P<rhs>[^;]*);(?P<tail>.*)$")


def _is_deref(s, pos):
    """Is the `*` immediately left of `pos` a DEREFERENCE rather than a multiplication?

    `*v = e` writes through v and only reads it; `a * v` is arithmetic.  The difference is what
    sits left of the star: an identifier, a `)` or a `]` makes it a binary operator, anything else
    (an operator, an open bracket, the start of the line) makes it unary.  Reading only `endswith
    ("*")` calls `frame * div5_magic` a deref - measured on `dungeon/func_807B0B3C`.
    """
    i = len(s[:pos].rstrip()) - 1
    if i < 0 or s[i] != "*":
        return False
    j = len(s[:i].rstrip()) - 1
    while j >= 0 and s[j] == "*":
        j = len(s[:j].rstrip()) - 1
    return j < 0 or not (s[j].isalnum() or s[j] in "_)]")


def _cast_edits(t, facts, host, tv, th, skips):
    """V's definitions become `H = (TH)(expr);`, its reads `(TV)H`.

    A compound assignment and a `v++;`/`v--;` STATEMENT are definitions too - `v >>= 5;` is
    `v = (TV)(v >> 5);` written short - so they take the same form, desugared:
    `H = (TH)((TV)H >> (5));`.  That spelling is what makes the merge of two 32-bit words of
    different signedness sound: every operand keeps the signedness it was written with, so a
    logical shift stays logical and an unsigned compare stays unsigned.  (Until 2026-09-15 this
    module also emitted an undocumented cast-free `implicit` spelling AHEAD of this one, which
    silently changed `u32 >>= 5` into an arithmetic shift; it was removed in review.)

    T66_ASM_OPERAND (round 30, opening 2) - inside an `ASM_*` argument the operand is the REGISTER,
    and a word is a word on this port, so the surviving name goes in BARE (`ASM_KEEP(h)`) and every
    other read is cast exactly as before.  `ASM_KEEP(var)` is `__asm__ __volatile__("" : "=r"(var)
    : "0"(var))`, so `(u8 *)h` there is not an lvalue for the output operand; that is what used to
    refuse the whole pair (`asm-operand-cast`, 44 ordered pairs in 14 rows).  The pin count cannot
    move (`_expected_pins` asserts the whole multiset with V's spelling rewritten), the argument
    count cannot move (one name replaces one name), and an `ASM_REG` binding never reaches here at
    all - `NEVER_IN_MACRO` refuses the pair in `Facts`.

    T66_COMPOUND (round 30) - the `compound-assign-cast` refusal was not about `v += e` (that has
    its own spelling above).  Over the 17 ordered pairs it charged, 23 of the 28 trigger lines are
    a PLAIN assignment whose right-hand side reads V (`v = (u8 *)v + 4;`), which `_is_kill` refuses
    to call a kill, and one is a plain assignment in a braceless `if` body (a write that may not
    execute, so it may not kill either).  Both are definitions written in the ordinary way and both
    have the ordinary spelling, `H = (TH)(<rhs with every V read written (TV)H>);`.  Five more are
    not writes at all: `*v = e` and `*v &= e` write THROUGH the pointer and READ v, and the old
    lookahead read the `=` after the name without looking at the `*` before it.  The three that
    remain are assignments spread over several lines, which this per-line edit map cannot spell:
    they keep their own refusal, `write-multiline-cast`.
    """
    asm_args, asm_mixed = _asm_arg_mentions(facts)
    asm_ok = _env_on("T66_ASM_OPERAND")
    comp_ok = _env_on("T66_COMPOUND")
    if asm_args:
        if not asm_ok:
            # the round-29 refusal: the cast spelling of the pair is gone, the rename spelling of
            # the same pair is untouched (it only respells the name the keep already carries).
            skips["asm-operand-cast"] += 1
            return None
        if asm_mixed:
            skips["asm-operand-cast-mixed-macro"] += 1
            return None
        if getattr(facts, "asm_partial", None):
            # The opening's argument is "inside an ASM_* argument the operand is the REGISTER", and
            # it holds only where the mention IS the argument.  `ASM_KEEP_DEP_NV(total, v + 1)` is
            # an expression whose operand is the whole argument: dropping the cast from one term of
            # it changes the value (`s32 + 1` read as `u8 * + 1` is +4 bytes), and the cast cannot
            # be kept either - `_expected_pins` compares the pin's argument against the victim's
            # name substituted, so `((s32)h) + 1` is not that pin any more.  Refused, and the
            # RENAME form of the same pair is untouched (round 30 review, defect 3).
            skips["asm-operand-cast-subexpr"] += 1
            return None
        skips["asm-operand-cast-reopened"] += 1
    edits = {}
    ch, cv = _cast(th), _cast(tv)
    name = re.escape(facts.name)
    comp_re = re.compile(COMPOUND_RE.pattern % name)
    incdec_re = re.compile(INCDEC_RE.pattern % (name, name))
    write_re = re.compile(PLAINWRITE_RE.pattern % name)
    comp_used = [False]                    # T66_COMPOUND actually spelled something on this pair

    def spell(k, m, s):
        """How one READ of V at `m` on line `k` is spelled with the surviving variable."""
        if (k, m.start()) in asm_args:
            return host                       # T66_ASM_OPERAND: the operand is the register
        after = s[m.end():]
        # Inside a macro argument the macro body decides what the cast binds to, and this line
        # cannot be read for it: parenthesise there always.
        paren = any(col == m.start() for col, _ in facts.macro_mentions.get(k, ())) \
            or bool(re.match(r"[ \t]*(?:\[|->|\.|\()", after))
        return ("(%s%s)" % (cv, host)) if paren else "%s%s" % (cv, host)

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
        wm = write_re.match(s)
        lhs_write = bool(wm) and bool(hits) and hits[0].start() == len(wm.group("i"))
        if k in facts.kills or (comp_ok and lhs_write):
            if not lhs_write:
                skips["write-not-plain-cast"] += 1
                return None
            # `v = <rhs>;<tail>` - a kill, or (T66_COMPOUND) a write `_is_kill` would not call one:
            # the rhs reads V (`v = (u8 *)v + 4;`) or the statement is a braceless if/loop body.
            a, b = wm.start("rhs"), wm.end("rhs")
            if any(x.start() >= b for x in hits):
                # `v = e; ASM_KEEP(v);` on one line: the tail is copied verbatim below, so a mention
                # in it would survive V's deletion.  (A kill cannot reach here - `_is_kill` demands
                # an empty tail - so this is T66_COMPOUND's refusal alone.)
                skips["write-tail-mentions-victim"] += 1
                return None
            if k not in facts.kills:
                comp_used[0] = True        # a write `_is_kill` would not have called one
            rhs = ln[a:b]
            for m in reversed([x for x in hits if a <= x.start() < b]):
                rhs = rhs[:m.start() - a] + spell(k, m, s) + rhs[m.end() - a:]
            edits[k] = "%s%s = %s(%s);%s" % (wm.group("i"), host, ch, rhs.strip(),
                                             ln[wm.start("tail"):])
            continue
        for m in reversed(hits):
            after = s[m.end():]
            deref = _is_deref(s, m.start())
            if re.match(r"[ \t]*(?:=(?!=)|[-+*/%&|^]=|<<=|>>=|\+\+|--)", after) \
                    or re.search(r"(?:\+\+|--)[ \t]*$", s[:m.start()]):
                # T66_COMPOUND: `*v = e` / `*v &= e` assign THROUGH the pointer, so the name is a
                # READ like any other; the old lookahead never looked left of it.
                if not (comp_ok and deref):
                    skips["write-multiline-cast" if comp_ok and not s.rstrip().endswith(";")
                          else "compound-assign-cast"] += 1
                    return None
                comp_used[0] = True        # `*v = e` read as the read it is
            ln = ln[:m.start()] + spell(k, m, s) + ln[m.end():]
        edits[k] = ln
    if comp_used[0]:
        # the pair the `compound-assign-cast` refusal used to cost: `compound-assign-cast` plus
        # `compound-assign-cast-reopened` is the count a T66_COMPOUND=0 run reports.
        skips["compound-assign-cast-reopened"] += 1
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
                    # `_shadow=False`: the text a rename builds has already had its shadowing inner
                    # locals renamed when T66_SHADOW built it, and one level of re-entry is the cap.
                    cache[key] = (text1, pairs_of(text1, collections.Counter(), _shadow=False))
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
        ["macroarg"] if (hf.macro_mentions or vf_.macro_mentions) else []) + (
        ["shadow"] if getattr(pair, "shadow", None) else []) + (
        ["interf-" + pair.interf] if getattr(pair, "interf", None) else [])
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
            vplace = _demote(F, V, guard=(V["name"], H["name"]),
                             moved_init=V["init"], skips=skips)
            if vplace is None:
                skips["init-before-declarations"] += 1
                continue
        hstmt = None if H["init"] is None else (H["ind"] + "%s = %s;" % (H["name"], H["init"].strip()))
        hplace = _demote(F, H, guard=(V["name"], H["name"]),
                         moved_init=H["init"], skips=skips) if hstmt else None
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
