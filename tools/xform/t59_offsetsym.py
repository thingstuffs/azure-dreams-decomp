"""T59: a kept page plus an offset, written as the symbol at that address - one use at a time.

APPEARS     a page literal held by a keep and used with an offset whose symbol the file already names
            (an extern, or the NON_MATCHING arm's spelling):
                address_base = (u8 *)0x80120000;
                ASM_KEEP(address_base);
                source_entry = (volatile SourceEntry *)(address_base + 0x6A18);   // D_80126A18 elsewhere
RESOLVES    the keeps4 lane (round 23, `town/func_8096B16C`): replacing only that use with the named symbol,
            `source_entry = (volatile SourceEntry *)D_80126A18;`, and dropping the page and its keep once
            nothing else reads them, is exact where t29_addrsym (every use, at a splitting cell) and
            t54_pagebase (the page's own definition) found nothing. A symbol is a relocatable object
            address, a different compiler value from the integer page (page_astra, round 18).
POPULATION  2026-09-13: 142 such uses in 74 rows.
RESULT      2026-09-13: reproduces the keeps4 output (identical assembly). Swept over its 66 eligible rows
            outside the round-23 lane rows: 2 applied (dungeon/func_80084084 12 -> 10 pins,
            dungeon/func_81335C70 4 -> 3). t29/t54 had already taken most rows where a symbol pays.
Candidates, all through `vf`: each use alone (page and keep dropped when the page has no other reader, else
kept), then every use of that page at once. The symbol is spelled as its own `extern` declaration demands
(an array decays to `D_X`, a scalar or a struct takes `&D_X`).

MECHANISM (round 30, `work/native_lane/r30_addr/REPORT.md`).  The lone-erasure census put 231 of the
tree's near residues in the ADDRESS MATERIALISATION class (`lui+addiu -> lui+ori`, `addiu -> ori`).  A
`-da` probe of 20 of them, stratified over all six cells, named ONE deciding pass in 20 of 20: cse's
`fold_rtx`.  Expansion emits `(plus (reg) (const_int OFF))` in both texts; with the keep gone cse knows
the register holds the page constant and folds the whole address to one `(const_int 0x801740F8)`, which
the MIPS constant splitter then materialises as `lui` + `ori`.  Retail's `addiu` is what a RELOCATABLE
operand produces: `(const (plus (symbol_ref) (const_int OFF)))` is not an integer cse can fold, so the
back end emits `%hi` / `%lo`.  The repair is exactly "name the symbol", and the only question per site is
whether the tree declares one at the address - 175 of the 231 sites, all but 3 of those with an `extern`
declaration in the row itself.

ROUND-30 OPENINGS (each an env switch, default "1", refusals journaled in `info["skips"]`).  The census
measured what t59 refused on those 231 sites: 88 "page matched but no symbol-backed use", 23 "page
definition not immediately followed by its keep", the rest with no page-literal definition at all.  The
openings are spellings, not new moves:

  T59_SIGNED_OFFSET  a use may subtract: `x = (T *)(p - 0x3328);` as well as `p + K`.  t59 shipped with
                     `+` only, which sent 42 minus-offset sites to the "no symbol-backed use" class.
  T59_SELF_BUMP      the use may BE the page's own advance - `p += K;`, `p -= K;` or `p = (T)p + K;`
                     (54 sites, the largest single shape).  It becomes `p = SYM;` and the page definition
                     and its keep go.  Guarded by `straight_line` (below): the page value must flow only
                     into that advance (nothing else between the definition and it mentions p, the keep
                     aside), and the text between must be a run of COMPLETE STATEMENTS in the definition's
                     own block - so a complete `if (...) { ... }` between is fine, and a braceless body, a
                     loop body, a switch arm or any jump target is refused.  The advance then runs exactly
                     when the definition did, exactly once.
  T59_KEEP_GAP       the keep may be up to eight lines after the page definition, over any lines that do
                     not mention the page - other pins, pin notes, unrelated statements, blank lines and
                     PREPROCESSOR DIRECTIVES - as long as those lines are complete statements in the
                     definition's own block (`straight_line` again: the definition must DOMINATE its keep,
                     or the use this module rewrites to an unconditional symbol could be reached on a path
                     the definition never ran on).  The common shape is an arm split whose port arm already
                     names the answer:
                         #ifdef NON_MATCHING
                             copy_page = D_80024038 - 0x4038;
                         #else
                             copy_page = (u8 *)0x80020000;
                         #endif
                         ASM_KEEP(copy_page);
                     The definition line and the keep line are erased separately, and a definition that
                     sits INSIDE a preprocessor arm is never erased at all (only its keep goes, leaving a
                     store nothing reads): removing the match arm's line would leave its port-arm mate
                     without a twin, which is an arm collapse, not a respelling.  A definition inside a
                     one-trip `do { ... } while (0);` is kept in place for a different reason (below).
  T59_ANY_LITERAL    the page literal's low half need not be zero (`0x8006CD30`).

WHICH ARMS MAY BE EDITED.  Never a port arm, a `#if 0` arm, or any arm whose condition is not a
NON_MATCHING test - those lines are blanked before anything is matched.  A MATCH arm (`#ifndef
NON_MATCHING`, or the `#else` of `#ifdef NON_MATCHING`) is the code the byte gate compiles and scores, so
a keep, a use or an advance inside one is rewritten like any other line - whole functions are wrapped
that way - and `apply_verified` asserts `unscored_text` is unchanged, which is what proves the port side
untouched.  The one exception is the page DEFINITION, above.

Also fixed in round 30 (defects, not openings):
  * `p + K` steps K ELEMENTS, and the step is set by the innermost cast, not by the declaration.  t59
    computed `base + K` bytes for every page, so a `s16 *` / `void **` / `s32 *` page got the wrong
    address (16 sites), while `(PointTable *)((u8 *)table_value + 0x4074)` on a `void **` page must be
    scaled by the `(u8 *)`, not by the declaration (6 more).  `scale_for_use` now reads the innermost
    cast that applies to p and falls back to p's declaration; where neither is decidable the use is
    refused and journaled.
  * a `p += K;` between the keep and a use left the use computing the pre-bump address.  The use window
    now ends at any write to p; the window in which the page must be DEAD before its definition can be
    dropped still ends only at a full redefinition, so a surviving `p += K;` keeps the definition.
  * nothing is matched inside a `#ifdef NON_MATCHING` / `#if 0` arm, inside a conditional whose condition
    is NOT a NON_MATCHING test (`#ifdef __mips__`: `pin_census.arm_labels` calls those lines "both", the
    defect that bit t66 in round 28), or inside a comment.
  * the symbol must carry an `extern` declaration the matching build can see: a name that exists only in
    a port arm is not declared for the build the byte gate scores, and a name the tree does not declare
    at all would be a new symbol, i.e. a config change.

DOMINANCE (round-30 review fixes; the three defects an adversarial reviewer demonstrated).  Writing a use
as the symbol is only valid when the page DEFINITION ran, exactly once, on every path that reaches the
use, and erasing a statement is only valid when that statement is a complete statement of its own block.
The first version of the round-30 openings proved neither:

  1. `straight_line` counted braces and grepped for `goto`/`case`/`default`/a label, so BRACELESS control
     flow passed it: `if (c)\n    p += 0x10;` and `while (c)\n    p += 0x10;` were accepted as "the
     advance runs exactly when the definition did", and the definition was then erased as dead.  It now
     also requires every `if`/`else`/`for`/`while`/`switch`/`do` in the segment to have a BRACED body
     (`else if` and the `while (0);` tail of a `do { }` aside), refuses `break`/`continue`/`return`, and
     requires the segment to end on a statement boundary (`;` or `}`) - which is what catches a macro that
     expands to a control header, e.g. `FOR_EACH(x)\n    p += K;`.
  2. the `p = (T)p + K;` advance was replaced by REWRITING ITS WHOLE LINE, so anything else on the line
     was silently deleted (`if (c) p = p + K;` lost its guard, `p = p + K; h();` lost `h();`).  Both the
     self-assignment and the `p += K;` bump now replace exactly the matched text, `p ... ;`, and never a
     character outside it.
  3. the T59_KEEP_GAP loop applied NO structural test to the gap, so a definition inside a conditional
     block could be paired with a keep outside it; the definition was erased from inside the block and the
     use rewritten to an unconditional symbol.  The gap must now pass `straight_line` too, and the
     definition and the keep must each begin a statement (`stmt_start`: not the braceless body of a
     control statement).  A gap that only closes a `do { ... } while (0);` around the definition is the one
     accepted exception - that block runs exactly once, so the definition does dominate - and there the
     definition is kept in place (`def_locked`) rather than erased, which also stops the module leaving an
     empty `do { } while (0);` behind.
Preprocessor directive lines are blanked before all three structural tests (`blank_directives`), so an arm
split's `#else` is not read as a C `else` and `#endif` does not hide the `;` that ends the previous
statement; `masked` blanks `//` comments as well as `/* */` (`t29.mask_comments` knows only the block
form), or a use inside a comment would be matched and rewritten IN the comment.

Two of the new refusals are DEFENCE IN DEPTH and are expected to stay at zero: `advance-is-a-braceless-
body` and `keep-is-a-braceless-body` both sit behind a `straight_line` of the same text, which refuses the
braceless spelling first.  They are kept because they state the invariant at the point it matters - the
statement this module ERASES or REPLACES must be a statement of its own block - and cost one comparison.
Neither `_bodies_braced` nor `one_trip_gap` masks string literals, so a `")"` inside a condition makes
their scans lose their place; both then fail CLOSED (the segment is refused), never open.

KNOWN LIMIT (not a round-30 regression, unchanged behaviour, stated so the next reader sees it): every
dominance test here is TEXTUAL and forward.  A `goto` from before the definition to a label after the keep
is not modelled, and neither is a loop that reads `p` textually above a definition at the bottom of its
body.  `vf` is the only acceptance.
"""
import os
import re
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text, arm_labels, PP_RE, NM_TRUE_RE, NM_FALSE_RE
from xform.t29_addrsym import mask_comments, decls_of, sym_decl, ELEMSIZE, INTTY

NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
CAST = r"\((?:[^()]|\([^()]*\))*\)"
KEEP = r"ASM_KEEP(?:_NV|_OLD|_DEP_NV)?"
MAX_GAP_LINES = 8
SWITCHES = ("T59_SIGNED_OFFSET", "T59_SELF_BUMP", "T59_KEEP_GAP", "T59_ANY_LITERAL")


def opened(name):
    """An opening is on unless its env switch is set to something falsey."""
    return os.environ.get(name, "1") not in ("", "0", "no", "off")


def openings():
    return {k: opened(k) for k in SWITCHES}


def _note(skips, key):
    if skips is not None:
        skips[key] = skips.get(key, 0) + 1


# ---------------------------------------------------------------- preprocessor geometry
def pp_depth(text):
    """Per line: (nesting depth of #if conditionals, True when some enclosing condition is not a
    NON_MATCHING test).  A directive line carries the depth of the block it opens or closes."""
    out, stack = [], []
    for ln in text.splitlines():
        m = PP_RE.match(ln)
        if m:
            d, cond = m.group(1), m.group(2).strip()
            if d in ("ifdef", "ifndef", "if"):
                known = (cond == "NON_MATCHING" if d in ("ifdef", "ifndef") else
                         bool(NM_TRUE_RE.match(cond) or NM_FALSE_RE.match(cond) or cond == "0"))
                stack.append(known)
            elif d == "endif" and stack:
                stack.pop()
            out.append((len(stack), not all(stack)))
            continue
        out.append((len(stack), not all(stack)))
    return out


DIRECTIVE = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)   # continuation lines belong to it
LINE_COMMENT = re.compile(r"//[^\n]*")


def blank_directives(text):
    """Every preprocessor directive line blanked, length-preservingly (continuation lines too).

    The structural tests below read C: an arm split's `#else` is not a C `else`, and `#endif` between a
    statement and the next one must not hide the `;` that ended it.
    """
    return DIRECTIVE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def masked(text):
    """Comments blanked, and every line the byte gate cannot read blanked.

    Blanked: lines only the port or the dead build compiles (`pin_census.arm_labels`), and lines inside
    a conditional whose condition is not a NON_MATCHING test - `#ifdef __mips__` and friends, which
    arm_labels calls "both" because it only understands NON_MATCHING.  Length-preserving, so every
    offset found here indexes the real text.

    `//` comments are blanked here as well as `/* */` (`t29.mask_comments` only knows the block form,
    and 108 files of the tree use the line form): a use matched inside a comment would be REWRITTEN in
    the comment, and a comment is also not a statement the structural tests below may read.
    """
    t = LINE_COMMENT.sub(lambda m: " " * len(m.group(0)), mask_comments(text))
    labs = arm_labels(text)
    deep = pp_depth(text)
    out = []
    for line, lab, (_d, unknown) in zip(t.splitlines(True), labs, deep):
        out.append(re.sub(r"[^\n]", " ", line) if (lab in ("port", "dead") or unknown) else line)
    return "".join(out)


def line_of(text, pos):
    return text.count("\n", 0, pos) + 1


def in_conditional(text, pos):
    """True when `pos` sits inside any #if/#ifdef/#ifndef block (so its line may not be erased)."""
    d = pp_depth(text)
    i = line_of(text, pos) - 1
    return i < len(d) and d[i][0] > 0


# the original module-level pattern, kept for callers and as the closed-switch spelling
PAGE = re.compile(r"^(?P<ind>[ \t]*)(?P<p>\w+)\s*=\s*(?:\([^)]*\)\s*)?(?P<lit>0x8[0-9A-Fa-f]{3}0000)\s*;[^\n]*\n"
                  r"[ \t]*ASM_KEEP(?:_NV)?\(\s*(?P=p)\s*\)\s*;[^\n]*\n", re.M)

GAP_LINE = re.compile(r"[^\n]*\n")
KEEP_LINE = re.compile(r"[ \t]*%s\(\s*(?P<p>\w+)\s*\)\s*;[^\n]*\n" % KEEP)
# what may not sit between two statements this module pairs: a jump, or anything jumped TO.
# `case X:` and `default:` are jump targets like any label: with one between, the second statement can be
# entered without the first having run.  `break`/`continue`/`return` are the same hole the other way -
# the second statement can be LEFT OUT - and refusing them outright costs nothing measurable.
JUMPY = re.compile(r"\b(?:goto|case|default|break|continue|return)\b"
                   r"|^[ \t]*[A-Za-z_]\w*[ \t]*:(?!:)", re.M)
CTRL = re.compile(r"(?<![\w$])(if|else|for|while|switch|do)(?![\w$])")


def _skip_ws(seg, j):
    while j < len(seg) and seg[j].isspace():
        j += 1
    return j


def _bodies_braced(seg):
    """True when every control statement in `seg` has a BRACED body.

    A braceless body swallows exactly the next statement, so `if (c)\\n    p += K;` is a CONDITIONAL
    advance and `while (c)\\n    p += K;` an iterated one - neither runs "exactly when the definition
    did".  Brace counting cannot see either: both are brace-balanced.
    """
    for m in CTRL.finditer(seg):
        kw, j = m.group(1), m.end()
        if kw in ("if", "for", "while", "switch"):
            j = _skip_ws(seg, j)
            if j >= len(seg) or seg[j] != "(":
                return False
            depth = 0
            while j < len(seg):
                if seg[j] == "(":
                    depth += 1
                elif seg[j] == ")":
                    depth -= 1
                    if depth == 0:
                        j += 1
                        break
                j += 1
            else:
                return False
        j = _skip_ws(seg, j)
        if j >= len(seg):
            return False
        if seg[j] == "{":
            continue
        if kw == "while" and seg[j] == ";":
            continue                                  # the `while (0);` tail of a `do { ... }`
        if kw == "else" and re.match(r"if(?![\w$])", seg[j:]):
            continue                                  # `else if (...)` - the `if` is checked in its turn
        return False
    return True


def straight_line(seg):
    """True when `seg` is a run of COMPLETE STATEMENTS in one block, with no way in and no way out.

    Then a statement after `seg` runs in the same block, exactly as often, as one before it: a complete
    `if (...) { ... }` between a page definition and its advance is fine; a braceless body, a loop body, a
    switch arm, a label, a jump or an unterminated control header is not.  `seg` must have its
    preprocessor directives blanked (`blank_directives`) - a `#else` is not a C `else`.
    """
    depth = 0
    for c in seg:
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth < 0:
                return False
    if depth != 0 or JUMPY.search(seg) or not _bodies_braced(seg):
        return False
    tail = seg.rstrip()
    # ... and `seg` must END on a statement boundary, which is what catches a control header this module
    # cannot parse - a macro that expands to one, `FOR_EACH(x)\n    p += K;`
    return not tail or tail[-1] in ";}"


def stmt_start(s_text, pos):
    """True when the statement at `pos` begins a statement of its own block.

    False when it is the braceless body of a control statement (`if (c)\\n    p = page;`, `else`, `do`):
    erasing such a statement hands the controller the NEXT statement as its body.  `s_text` must have its
    comments and preprocessor directives blanked.
    """
    head = s_text[:pos].rstrip()
    return not head or head[-1] in ";{}:"


ONE_TRIP = re.compile(r"\A\s*\}[ \t]*while[ \t]*\(\s*0\s*\)[ \t]*;\s*\Z")


def one_trip_gap(s_text, dstart, gap):
    """True when `gap` does nothing but close a `do { ... } while (0);` the definition sits inside.

    That block runs exactly once, so the definition still dominates its keep and the uses after it - the
    one block boundary this module may cross.  The definition itself is kept in place (`def_locked`).
    """
    if not ONE_TRIP.match(gap):
        return False
    depth, i = 0, dstart - 1
    while i >= 0:
        if s_text[i] == "}":
            depth += 1
        elif s_text[i] == "{":
            if depth == 0:
                break
            depth -= 1
        i -= 1
    else:
        return False
    return re.search(r"(?<![\w$])do\s*\Z", s_text[:i]) is not None


def page_re():
    lit = r"0x8[0-9A-Fa-f]{7}" if opened("T59_ANY_LITERAL") else r"0x8[0-9A-Fa-f]{3}0000"
    return re.compile(r"^(?P<ind>[ \t]*)(?P<p>\w+)\s*=\s*(?:%s\s*)?(?P<lit>%s)\s*;[^\n]*\n" % (CAST, lit), re.M)


def use_re(p):
    """x = (T)(p +/- OFF);   x = (T)p +/- OFF;   x = p +/- OFF;   (p itself may be the lhs)."""
    ops = "[-+]" if opened("T59_SIGNED_OFFSET") else r"\+"
    return re.compile(r"(?P<lhs>\b\w+(?:->\w+|\.\w+|\[[^\]]*\])*\s*=\s*)(?P<ocast>%s\s*)?"
                      r"(?P<lp>\(\s*)?(?P<icast>%s\s*)?%s\s*(?P<op>%s)\s*(?P<off>%s)\s*(?P<rp>\)\s*)?;"
                      % (CAST, CAST, re.escape(p), ops, NUM))


def bump_re(p):
    """p += OFF;   p -= OFF;   at the head of its line.

    The match ENDS at the `;`: it used to run to the end of the line, so replacing it deleted a trailing
    statement or comment (`p += K; h();` lost `h();`).
    """
    return re.compile(r"^(?P<ind>[ \t]*)\(?%s\)?\s*(?P<op>[-+])=\s*(?P<off>%s)\s*;" % (re.escape(p), NUM), re.M)


def any_write_re(p):
    return re.compile(r"(?<![.>\w])\b%s\s*(?:\+\+|--|[-+*/|&^]?=(?!=))" % re.escape(p))


def full_assign_re(p):
    return re.compile(r"(?<![.>\w])\b%s\s*=(?!=)" % re.escape(p))


# ---------------------------------------------------------------- types and scaling
def _decls(m_text, p):
    return {(ty, ptr) for ty, ptr, _ in decls_of(m_text, p)}


def _scale(ty, ptr):
    if ptr == 0:
        return 1 if ty in INTTY else None
    if ptr == 1:
        return ELEMSIZE.get(ty)
    if ptr >= 2:
        return 4
    return None


def cast_scale(cast):
    """The element size a cast makes `p + 1` step, or None when the cast is not decidable."""
    m = re.fullmatch(r"\(\s*(?:const\s+|volatile\s+)*(?P<ty>(?:unsigned\s+|signed\s+)*[A-Za-z_]\w*"
                     r"(?:\s+long)?)\s*(?P<p>\**)\s*\)\s*", cast)
    if not m:
        return None
    return _scale(re.sub(r"\s+", " ", m.group("ty").strip()), len(m.group("p")))


def decl_scale(m_text, p, skips=None):
    """How many bytes `p + 1` steps, from p's own declaration; 1 (journaled) when it has none."""
    decls = _decls(m_text, p)
    if len(decls) != 1:
        _note(skips, "page-has-no-single-declaration-scale-1-assumed")
        return 1
    return _scale(*next(iter(decls)))


def decl_type(m_text, p):
    """`p`'s declared type as a cast body ('u8 *'), or None when it has no single local declaration."""
    decls = _decls(m_text, p)
    if len(decls) != 1:
        return None
    ty, ptr = next(iter(decls))
    return (ty + " " + "*" * ptr) if ptr else ty


def scale_for_use(m_text, p, m, skips=None):
    """The step of `p + 1` inside one use match: the innermost cast that applies to p wins."""
    inner = m.group("icast")
    if inner is None and m.group("lp") is None:
        inner = m.group("ocast")          # `x = (u8 *)p + K;` - the cast applies to p
    if inner is not None:
        s = cast_scale(inner.strip())
        if s is None:
            _note(skips, "use-cast-cannot-be-scaled")
        return s
    return decl_scale(m_text, p, skips)


def spelled(text, addr, skips=None):
    """The symbol at `addr` as the row spells it, or None.

    The name must appear OUTSIDE any port/dead/unknown arm and outside comments, and must carry an
    `extern` declaration: a name that exists only in a `#ifdef NON_MATCHING` arm is not declared for the
    build the byte gate scores, and a name the tree does not declare is a new symbol (a config change).
    """
    m = masked(text)
    sym = "D_%08X" % (addr & 0xFFFFFFFF)
    names = {x.group(0).upper(): x.group(0) for x in re.finditer(r"\bD_[0-9A-Fa-f]{8}\b", m)}
    real = names.get(sym.upper())
    if real is None:
        _note(skips, "no-symbol-named-at-the-address")
        return None
    d = sym_decl(m, real)
    if d is None:
        _note(skips, "symbol-has-no-extern-declaration")
        return None
    # the DECLARATION decides, not how the file happens to spell the name elsewhere: an array decays to
    # a pointer, a scalar or a struct needs `&`.  t59 shipped with the "does the file write &D_X?"
    # heuristic and produced `(PackedOffsets *)D_80024004` for `extern PackedOffsets D_80024004;`,
    # which gcc rejects outright ("cannot convert to a pointer type").
    return real if d[1] else "&" + real


def cast_for(m_text, p, sym):
    """A cast to p's OWN declared type, '' when the symbol already has it, None when p has no type.

    Never widens or narrows anything: the type is the one the row declared for p.
    """
    ty = decl_type(m_text, p)
    if ty is None:
        return None
    base = sym[1:] if sym.startswith("&") else sym
    d = sym_decl(m_text, base)
    if d is not None:
        elem, arr = d
        if ty == elem + " *" and (arr and sym == base or not arr and sym.startswith("&")):
            return ""
    return "(%s)" % ty


# ---------------------------------------------------------------- sites
def find(text, skips=None):
    """Per kept page with symbol-backed uses:

        [(def_span, keep_span, p, [(kind, start, end, replacement)], use_stop, def_locked)]

    `def_span` and `keep_span` are erased separately (they need not be adjacent); `def_locked` says the
    definition may never be erased - it sits inside a preprocessor arm (erasing it would collapse the
    arm), or inside the one-trip `do { ... } while (0);` this module is allowed to pair across (erasing it
    would leave an empty block behind).  `kind` is "use" for a rewritten offset use and "bump" for the
    page's own advance.
    """
    m_text = masked(text)
    s_text = blank_directives(m_text)          # the same offsets, read as C: no `#else`, no `#endif`
    out = []
    for m in page_re().finditer(m_text):
        p, base = m.group("p"), int(m.group("lit"), 16)
        k = KEEP_LINE.match(m_text, m.end())
        if not (k and k.group("p") == p):
            k = None
            if not opened("T59_KEEP_GAP"):
                _note(skips, "keep-not-on-the-line-after-the-page-definition")
                continue
            q = m.end()
            for _ in range(MAX_GAP_LINES):
                k2 = KEEP_LINE.match(m_text, q)
                if k2 and k2.group("p") == p:
                    k = k2
                    break
                g = GAP_LINE.match(m_text, q)
                if not g or g.end() == q:
                    break
                if re.search(r"(?<![.>\w])\b%s\b" % re.escape(p), g.group(0)):
                    break                 # a reader of the page before its keep: not this shape
                q = g.end()
            if k is None:
                _note(skips, "no-keep-of-the-page-within-%d-lines" % MAX_GAP_LINES)
                continue
        keep_span = (k.start(), k.end())
        if in_conditional(text, k.start()) and pp_depth(text)[line_of(text, k.start()) - 1][1]:
            _note(skips, "keep-inside-a-non-NON_MATCHING-conditional")
            continue
        # DOMINANCE.  The definition must run, exactly once, on every path that reaches the keep - else
        # the use this module rewrites to an unconditional symbol can be reached with the page holding
        # something else.  And both the definition and the keep must be complete statements of their own
        # block, or erasing one hands a controller the next statement as its body.
        gap = s_text[m.end():k.start()]
        one_trip = False
        if not straight_line(gap):
            if one_trip_gap(s_text, m.start(), gap):
                one_trip = True               # `do { p = page; } while (0);` - exactly one trip
            else:
                _note(skips, "keep-is-not-in-the-page-definition's-block")
                continue
        if not stmt_start(s_text, m.start()):
            _note(skips, "page-definition-is-a-braceless-body")
            continue
        if not stmt_start(s_text, k.start()):
            _note(skips, "keep-is-a-braceless-body")
            continue
        w = any_write_re(p).search(m_text, k.end())
        use_stop = w.start() if w else len(m_text)
        uses = []
        for u in use_re(p).finditer(m_text, k.end(), use_stop):
            if JUMPY.search(s_text[k.end():u.start()]):
                # the same dominance question for a USE: past a label the use can be entered on a path
                # the definition never ran on, and `p + K` is then not the symbol.  (Measured tree-wide
                # over the 904 ASM_KEEP files: 0 of the 212 offered replacements sit past one.)
                _note(skips, "use-is-past-a-label-or-jump-from-the-keep")
                continue
            scale = scale_for_use(m_text, p, u, skips)
            if scale is None:
                continue
            if bool(u.group("lp")) != bool(u.group("rp")):
                _note(skips, "use-parentheses-do-not-balance")
                continue
            off = int(u.group("off"), 0) * scale
            sym = spelled(text, base + off if u.group("op") == "+" else base - off, skips)
            if sym:
                uses.append(("use", u.start(), u.end(),
                             "%s%s%s;" % (u.group("lhs"), u.group("ocast") or "", sym)))
        if opened("T59_SELF_BUMP"):
            adv = _advance(m_text, p, base, m.end(), keep_span, skips, text, s_text)
            if adv:
                uses.append(adv)
        if uses:
            out.append(((m.start(), m.end()), keep_span, p, uses, use_stop,
                        in_conditional(text, m.start()) or one_trip))
        else:
            _note(skips, "page-matched-but-no-symbol-backed-use")
    return out


def _advance(m_text, p, base, after, keep_span, skips, text, s_text):
    """The page's own advance (`p += K;` or `p = (T)p + K;`) rewritten as `p = SYM;`, or None.

    `after` is the end of the page definition and `keep_span` its keep, which is excluded from the
    "nothing else reads the page" test - the keep is the pin this candidate erases.  The replacement span
    is EXACTLY the matched advance, `p ... ;`: rewriting its whole line silently deleted anything else on
    that line (a guard before it, a statement after it), the round-30 review's second defect.
    """
    b = bump_re(p).search(m_text, keep_span[1])
    s = use_re(p).search(m_text, keep_span[1])
    if s is not None and not re.fullmatch(r"\(?%s\)?\s*=\s*" % re.escape(p), s.group("lhs")):
        s = None                                  # not a self-assignment
    if b is None and s is None:
        return None
    ind = ""
    if s is not None and (b is None or s.start() < b.start()):
        scale = scale_for_use(m_text, p, s, skips)
        if scale is None or bool(s.group("lp")) != bool(s.group("rp")):
            return None
        if "\n" in s.group(0):
            _note(skips, "self-assignment-spans-lines")
            return None
        start, end = s.start(), s.end()
        op, off = s.group("op"), int(s.group("off"), 0) * scale
    else:
        scale = decl_scale(m_text, p, skips)
        if scale is None:
            _note(skips, "page-type-cannot-be-scaled")
            return None
        start, end = b.start(), b.end()
        ind = b.group("ind")                      # the bump match starts at the line's indentation
        op, off = b.group("op"), int(b.group("off"), 0) * scale
    span = m_text[after:keep_span[0]] + m_text[keep_span[1]:start]
    if re.search(r"(?<![.>\w])\b%s\b" % re.escape(p), span):
        _note(skips, "advance-is-not-the-page-value's-only-reader")
        return None
    if not straight_line(s_text[after:keep_span[0]] + s_text[keep_span[1]:start]):
        _note(skips, "advance-is-conditional-or-in-another-block")
        return None
    if not stmt_start(s_text, start):             # `ind` is whitespace, which stmt_start strips anyway
        _note(skips, "advance-is-a-braceless-body")
        return None
    sym = spelled(text, base + off if op == "+" else base - off, skips)
    if sym is None:
        return None
    cast = cast_for(m_text, p, sym)
    if cast is None:
        _note(skips, "page-has-no-declared-type-for-the-advance-spelling")
        return None
    return ("bump", start, end, "%s%s = %s%s;" % (ind, p, cast, sym))


def rewrite(text, page, chosen):
    """Apply the chosen replacements, erase the keep, and drop the page definition when it is dead.

    The keep is the pin this module removes, so it always goes; the definition only goes when nothing
    reads the page value any more, and never when it sits inside a preprocessor arm (`def_locked`).
    """
    dspan, kspan, p, _uses, _use_stop, locked = page
    if not chosen:
        return text
    orig = text
    for _kind, s, e, rep in sorted(chosen, key=lambda c: c[1], reverse=True):
        text = text[:s] + rep + text[e:]
    P = r"(?<![.>\w])\b%s\b" % re.escape(p)
    bumps = [s for kind, s, _e, _r in chosen if kind == "bump"]
    if bumps:
        # the advance was the page value's only reader and now re-defines p outright: the definition is
        # dead exactly when nothing between it and the advance mentioned p (the keep aside)
        seg = orig[dspan[1]:kspan[0]] + orig[kspan[1]:min(bumps)]
        dead = not re.search(P, mask_comments(seg))
    else:
        # the page lives until it is redefined outright; a surviving `p += K;` still reads it
        nxt = full_assign_re(p).search(mask_comments(orig), kspan[1])
        stop = nxt.start() if nxt else len(orig)
        shift = sum(len(rep) - (e - s) for _k, s, e, rep in chosen if s < stop)
        head = mask_comments(orig[dspan[1]:kspan[0]])
        tail = mask_comments(text[kspan[1]:stop + shift])
        dead = not re.search(P, head) and not re.search(P, tail)
    spans = [kspan] if (locked or not dead) else [dspan, kspan]
    for a, b in sorted(spans, reverse=True):
        text = text[:a] + text[b:]
    return text


class T:
    name = "t59_offsetsym"
    level = 1
    needs_verify = True
    BUDGET = 24

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        return None if find(text) else "no kept page with a symbol-backed offset use"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, tried, cur, steps = len(sites_of(text)), 0, text, []
        skips = {}
        usig = unscored_text(text)
        pages = find(text, skips)
        for pi in reversed(range(len(pages))):
            live = find(cur)
            page = live[pi] if pi < len(live) else None
            if page is None:
                _note(skips, "page-gone-after-an-earlier-step")
                continue
            trials = [[u] for u in reversed(page[3])] + ([page[3]] if len(page[3]) > 1 else [])
            for chosen in trials:
                if tried >= cls.BUDGET:
                    _note(skips, "budget")
                    break
                cand = rewrite(cur, page, chosen)
                if cand == cur:
                    _note(skips, "no-change")
                    continue
                if unscored_text(cand) != usig:
                    _note(skips, "edits-an-unscored-arm")
                    continue
                if len(sites_of(cand)) >= len(sites_of(cur)):
                    _note(skips, "no-pin-removed")
                    continue
                tried += 1
                if vf(cand).get("exact"):
                    cur = cand
                    steps.append("%s:%s:%d" % (page[2], "+".join(sorted({k for k, _s, _e, _r in chosen})),
                                               len(chosen)))
                    break
                _note(skips, "not-exact")
        info = {"tried": tried, "pins_in": pins_in, "pages": len(pages), "skips": skips,
                "openings": openings()}
        if not steps:
            info["pins_out"] = pins_in
            return None, info
        info.update(step="+".join(steps), pins_out=len(sites_of(cur)))
        return cur, info
