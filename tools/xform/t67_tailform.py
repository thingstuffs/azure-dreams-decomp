"""T67: the tail-shape moves - a statement run duplicated into its predecessors, or merged out of them.

WHY
    The lane-won exemplar diffs of the last 60 commits carry a control-flow change in 76 of 403
    register texts, 64 of 220 keeps and about 62 of 177 fences, and `work/native_lane/r29_tail/
    ctrlmoves.py` classifies them: TAILMERGE 35/30/36 (a run that stood twice now stands once),
    TAILDUP 19/15/27 (the reverse), RETSPLIT 17/17/6, ARMSWAP 9/4/5, EARLYRET 6/9/4.  LOOPFORM
    (35/19/10) is already served by t41/t44/natural's `gotoloop`, and GOTO2RET (9/4/8) by t48.
    Nothing in the menu changes a TAIL's shape.

    Two exemplars, both in `work/native_lane/r29_tail/ex/`:
      * `reg/dungeon_func_800D2A74.dd967a78.diff` - four `goto advance_phase;` sites, the two-statement
        tail copied into each and both labels dropped (TAILDUP);
      * `reg/dungeon_func_81257000.17a95a06.diff` then `FENCE/dungeon_func_81257000.d7a6d7dd.diff` -
        the SAME function, one lane merging the two arms' brightness tails into a shared tail and a
        later lane duplicating them back into the arms.  Both directions are real moves; only the byte
        verdict decides which one the retail bytes were built from.

    The mechanism the pin notes name is exactly this: 138 pins in 102 rows say "basic-block layout",
    351 in 188 rows "delay-slot", 300-odd more "moves a statement across a call/branch".  GCC 2.x
    cross-jumps identical tails (`jump.c`, `cross_jump`) and fills a delay slot from the tail
    (`reorg.c`); the SOURCE shape decides which block layout and which fill the retail bytes show.

THE MOVES (each in both directions where it has one)
    dup_label   a label L with k >= 2 incoming whole-line `goto L;` whose tail T (from L to the next
                terminator, <= 8 statements, no label, no declaration, no pin) is copied over each
                `goto L;`.  The label and its tail stay when control also falls through into L,
                otherwise they go.  Also with k == 1 when the goto is the only entry: the tail is
                MOVED to its one predecessor.
    sink_tail   `if (c) { A } else { B } T` -> `if (c) { A; T } else { B; T }`, T removed from after
                the if/else.  For an `if` without an `else`, only when A ends in a terminator:
                `if (c) { A } else { T }`.  Copying T into the arm AND leaving it in place is refused -
                on the path through the arm it would run twice.
    hoist_tail  the reverse: `if (c) { A; T } else { B; T }` with token-identical T ->
                `if (c) { A } else { B } T`.
    merge_runs  two token-identical statement runs (>= 2 statements) ending in the same terminator:
                one of them becomes `goto L;`, with a fresh label L before the other.  Both
                assignments are offered (`:first` keeps the earlier run's body, `:second` the later).
    split_ret   `v = E1; goto R;` ... `v = E2; goto R;` ... `R: return v;` -> `return E1;` /
                `return E2;`, when v is a plain local with no other use and its declared type is the
                function's return type; and the reverse, two `return E;` with token-identical E merged
                under one label.

REFUSALS (written before the moves, and each one tested)
    A tail or run may not contain a declaration, a label or `case`, a preprocessor line, a brace, an
    `ASM_*` pin, or a statement this module cannot read as one whole line.  A tail that holds a pin
    makes the move ineligible on the pinned text; the erase-first search below then offers the same
    move on the text with that pin erased, which is where a pinned tail becomes reachable at all.

    * SCOPE.  Every identifier of a copied, moved or jumped-to run must resolve to the SAME
      declaration at its source line and at its destination line (`natural._Fn.resolve`).  An
      arm-local carried out of its arm would otherwise become a silent shadow or a compile error the
      screen swallows as `compile-fail`.
    * JUMP TARGET IDENTITY.  `break` and `continue` in a copied tail are compared by the innermost
      enclosing loop-or-switch (break) or loop (continue) block at the source and at the landing site,
      not by depth: a `goto` out of a `switch` into a tail holding `break` retargets it at equal depth.
    * JUMPING IN.  A new `goto` may not enter a loop body or a switch body, nor any block whose
      declarations carry an initialiser (the initialiser would be jumped over).
    * THE ANCHOR.  Not only the lines INSIDE a tail or a run but every line a move rewrites, deletes
      or inserts after - the `goto L;` a tail is copied over, the `if (...) {` a tail is sunk into or
      hoisted out of, the `v = E;` that becomes `return E;` - goes through `kind_of`, whose
      `_starts_statement` refuses the braceless body of an `if`/`while`/`for`/`else`/`do` head on the
      line above.  Such a body is CONDITIONAL: copying a tail over it, or reading it as a whole
      statement, silently changes which paths run it while the candidate still compiles, so the
      screen cannot see the error.  This refuses the dominant m2c shape `if (x)\n    goto L;`
      outright rather than growing a braced-if exception.
    * TOKEN EQUALITY on a real C tokenizer over the masked+real line pair (`_line_tokens`), never on
      squashed whitespace and never on `mask()` alone: squashing fuses `- -y` into `--y`, and the
      mask blanks string bodies, so two calls with different string arguments compare equal there.
    * THE PREPROCESSOR.  `pin_census.arm_labels` labels only `NON_MATCHING` and `#if 0`, so an
      `#ifdef __mips__ ... #else` block is `both` to it and an edit in the `#else` arm passes the
      sweep's unscored-arm invariant untouched (t66's landed defect).  This module keeps t66's own
      region map: no line it edits, drops or inserts after may be preprocessor-guarded, and
      `_pp_sig` - the text of every guarded line, in order - must be identical to the BASE the move
      ran on (not to the pinned text: `erase_many(clean_notes=True)` legitimately drops an emptied
      `#ifndef NON_MATCHING` block).
    * TYPE.  `split_ret` refuses unless v's declared type is textually the function's return type
      (`s16 v; ... return v;` in an `s32` function is a truncation the merge would drop) and refuses
      any `static`/`volatile`/`const`/`extern`/pinned declaration.
    * THE PIN MULTISET.  Every emitted line is either an untouched source line, a source line
      re-indented, or `L:` / `goto L;` / `return E;` assembled from tokens already in the text.  The
      multiset of (macro, argument, declaration text) over `sites_of` must therefore be identical to
      the base's, and the scaffolding patterns t64 refuses may not appear more often than in the base.

THE SEARCH (t64's shape: erase first, then the move)
    For each live pin site in source order - every macro kind, not only the register and keep pins,
    because the mechanism notes sit on fences and `ASM_TAILSLOT_PIN` too - erase that one site
    (`erase_many(..., clean_notes=True)`, then re-read `sites_of` on the new text: every line number
    below an erasure has moved), run the menu on the erased text, and screen each candidate with
    `xform.screen.compile_s`/`sdiff` against the CURRENT pinned listing.  The pinned text is
    byte-exact, so screen distance 0 means identical cc1 output.  `vf` is called ONLY on distance-0
    candidates that pass `pin_search_engine.improves`.  Depth 2 gives the `T67_BEAM` (8) nearest
    depth-1 texts one more move.  The moves of the pinned text itself are screened too and journaled
    as `asis` - they can never pay (no pin is gone, so `improves` refuses them), but their distance is
    the evidence for whether the move alone is codegen-neutral.

    Budgets `T67_SCREENS` (400) and `T67_VERIFY` (6) per row; the search restarts on the new text
    after a win.  `tailform_candidates(text)` exposes the same moves as a search menu (<= 48, nearest
    a live pin site first).
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
from pin_census import sites_of, unscored_text, asm_blocker
from pin_sites import erase_many
from pin_search_engine import improves
from xform.screen import compile_s, sdiff
from xform.t51_sched_order import units
from xform import natural as N
# t66 is imported, never edited: its Flow, its preprocessor-region map and its augmented function
# reader are the reviewed versions of exactly the three things this module needs.
from xform.t66_sameregmerge import Flow, _pp_regions, _pp_sig, _functions, SWITCH_RE, ELSE_RE

MENU_CAP = 48
SCREEN_BUDGET = 400
VERIFY_BUDGET = 6
BEAM = int(os.getenv("T67_BEAM", "8"))
TAIL_MAX = 8                      # statements in a tail or a run (the terminator not counted)
ASIS_CAP = 8                      # unerased moves screened per row, for evidence only
PLAN_CAP = 24                     # live pins whose erasure seeds a depth-1 menu

ID = r"[A-Za-z_]\w*"
LABEL_RE = N.LABEL_RE
CASE_RE = N.CASE_RE
LOOP_RE = N.LOOP_RE
IF_RE = N.IF_RE
GOTO_LINE_RE = N.GOTO_LINE_RE
GOTO_ANY_RE = re.compile(r"\bgoto[ \t]+(%s)[ \t]*;" % ID)
ADDR_LABEL_RE = re.compile(r"&&[ \t]*(%s)" % ID)
TERM_RE = re.compile(r"^[ \t]*(?P<kw>return|goto|break|continue)\b(?P<arg>[^;]*);[ \t]*$")
MEMBER_RE = re.compile(r"(?:->|\.)[ \t]*%s" % ID)

# the scaffolding t64 refuses, whichever move produced the candidate
FORBIDDEN = (r"\bASM_[A-Z0-9_]+", r"\b__asm__\b", r"\bdo\s*\{", r"\bwhile\s*\(\s*0\s*\)",
             r"\bfor\s*\([^;]*;\s*0\s*;", r"\bif\s*\(\s*1\s*\)", r"\(\s*\{")

KEYWORDS = set("""auto break case char const continue default do double else enum extern float for
goto if int long register return short signed sizeof static struct switch typedef union unsigned
void volatile while""".split())


def _nl(s):
    return s[:-1] if s.endswith("\n") else s


def _sq(s):
    return re.sub(r"\s+", "", s)


def _ids(masked_lines):
    """Identifiers a run mentions: member names after `.`/`->` and C keywords dropped."""
    s = MEMBER_RE.sub(" ", "\n".join(masked_lines))
    return {x for x in re.findall(ID, s) if x not in KEYWORDS}


TOK_RE = re.compile(r"""
      [A-Za-z_]\w*
    | 0[xX][0-9A-Fa-f]+(?:[uUlL]*)
    | (?:\d+\.\d*|\.\d+|\d+)(?:[eE][+-]?\d+)?(?:[uUlLfF]*)
    | >>=|<<=|\.\.\.
    | ->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\+=|-=|\*=|/=|%=|&=|\|=|\^=|\#\#
    | [^\sA-Za-z0-9_]
""", re.X)


def _regions(real, masked):
    """[(kind, text)] over ONE line: 'code', 'str' (a string or character literal), 'cmt'.

    `masked` (from `natural.mask`, which is string- and comment-aware over the WHOLE text, so a
    multi-line comment is blanked on every one of its lines) says which columns are code: a column
    the mask blanked while the real line has something other than a space there opens a literal or a
    comment, and the real text decides which.  A `//` or a `/*` INSIDE a string literal is therefore
    part of the literal, and a quote inside a comment is part of the comment.
    """
    out, i, n = [], 0, min(len(real), len(masked))
    code = []
    while i < n:
        if not (masked[i] == " " and real[i] != " "):
            code.append(masked[i])
            i += 1
            continue
        if code:
            out.append(("code", "".join(code)))
            del code[:]
        c = real[i]
        if c in "\"'":
            j = i + 1
            while j < n and real[j] != c:
                j += 2 if real[j] == "\\" else 1      # mask's own escape rule
            j = min(j + 1, n)
            out.append(("str", real[i:j]))
            i = j
        elif real.startswith("/*", i):
            j = real.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(("cmt", real[i:j]))
            i = j
        elif real.startswith("//", i):
            out.append(("cmt", real[i:n]))
            i = n
        else:
            # the continuation body of a multi-line comment opened on an earlier line
            j = i
            while j < n and masked[j] == " " and real[j] != " ":
                j += 1
            out.append(("cmt", real[i:j]))
            i = j
    if code:
        out.append(("code", "".join(code)))
    return out


def _line_tokens(real, masked):
    """The C token list of ONE line.

    Written after a reviewer showed the previous key (`re.sub(r"\\s+", "", line)`) was not a
    tokenizer: it fused adjacent operators, so `y = - -y;` and `y = --y;` had the SAME key and
    `hoist_tail` deleted one of the two as a duplicate of the other.  It also ran a comment regex
    over the real line with no string awareness, so a `//` inside a string literal truncated the key
    and `func("http://a")` compared equal to `func("http://b")`.

    Code runs are tokenized with maximal munch, so `--` is one token and `- -` is two.  A string or
    character literal is emitted as its RAW text, quotes and inner spacing included - two calls with
    different string arguments are different programs.  Comments are dropped: a pin note or a hand
    comment may not decide whether two runs are the same statements.
    """
    out = []
    for kind, seg in _regions(real, masked):
        if kind == "code":
            out.extend(m.group(0) for m in TOK_RE.finditer(seg))
        elif kind == "str":
            out.append(seg)
    return tuple(out)


def _key(ctx, lines):
    """Token-equality key of a run: the C token list of each of its lines.

    Whitespace and comments do not decide it (an indentation-only or comment-only difference still
    merges), but no two token-different lines may share a key.
    """
    return tuple(_line_tokens(ctx.real[k], ctx.ml[k]) for k in lines)


def _commented(ctx, lines):
    """Does any of these lines carry a comment?

    Every whole-line edit below is built from a match on the MASKED line and writes a fresh line in
    its place, so a trailing comment on the original - an m2c note, or a `/* MATCH pin: ... */`
    describing a pin that is still there - would be dropped silently.  A line whose text is copied
    over verbatim (a tail moved to a goto site, a suffix hoisted out of an arm) keeps its comment and
    is not checked here.

    Decided on `_regions`, not on a bare comment regex: `func("http://a");` carries no comment, and
    reading its `//` as one refused a legitimate `merge_runs` (the same string-blindness that made
    `_key` fuse two different calls).
    """
    return any(kind == "cmt" for k in lines for kind, _ in _regions(ctx.real[k], ctx.ml[k]))


def _fresh_label(text, base="shared_tail"):
    name, n = base, 1
    while re.search(r"\b%s\b" % re.escape(name), text):
        n += 1
        name = "%s_%d" % (base, n)
    return name


# ------------------------------------------------------------------ one text's structure

class Ctx:
    """The parsed view of one text: functions, their flow graphs, the preprocessor regions and pins."""

    def __init__(self, text):
        self.text = text
        self.t = N._T(text)
        self.ml = self.t.m
        self.real = [_nl(x) for x in self.t.lines]
        _, recs = units(text)
        self.recs = {r["line"]: r for r in recs}
        self.pp = _pp_regions(text)
        self.fns = _functions(self.t)
        self.pins = sites_of(text)
        self.pinlines = sorted({s[5] - 1 for s in self.pins})
        self.ppsig = _pp_sig(text, self.pp)
        self.usig = unscored_text(text)
        self.pinkey = _pin_key(text)
        self.flows = {}

    def flow(self, F):
        key = (F.a, F.b)
        if key not in self.flows:
            try:
                self.flows[key] = Flow(F, list(self.recs.values()), self.pp)
            except Exception:
                self.flows[key] = None
        return self.flows[key]

    def near_pin(self, line):
        """Distance in lines from the nearest live pin site (a big number when the row has none)."""
        if not self.pinlines:
            return 10 ** 6
        return min(abs(line - p) for p in self.pinlines)


def _pin_key(text):
    return collections.Counter((s[1], s[2], (s[6] or "").strip()) for s in sites_of(text))


# ------------------------------------------------------------------ statement classification

def _starts_statement(ctx, k):
    """Is line k the FIRST line of its statement?

    The line above it (blank and preprocessor lines skipped) has to have closed whatever it opened:
    a `;`, a brace, or a label's `:`.  Anything else - `... +`, `f(a,`, a braceless `if (c)` - means
    line k continues it, and a `return`/`break` classification or a move of line k alone would cut a
    statement in half.
    """
    j = k - 1
    while j >= 0 and (not ctx.ml[j].strip() or ctx.ml[j].lstrip().startswith("#")):
        j -= 1
    if j < 0:
        return True
    return ctx.ml[j].rstrip().endswith((";", "{", "}", ":"))


def kind_of(ctx, k):
    """What line k is, for the purposes of a tail: 'stmt', 'term:<kw>', or a refusal name."""
    if k in ctx.pp:
        return "pp"
    s = ctx.ml[k]
    st = s.strip()
    if not st:
        return "blank"
    if st.startswith("#"):
        return "pp"
    if "ASM_" in s:
        return "pin"
    if LABEL_RE.match(s):
        return "label"
    if CASE_RE.match(s):
        return "case"
    if "{" in s or "}" in s:
        return "brace"
    if not _starts_statement(ctx, k):
        # the CONTINUATION of a multi-line statement, which can be balanced and `;`-terminated on
        # its own (`((x->unk_66.s * f(a)) >> 10);` under `p->unk_12 = p->unk_5E +`).  Moving one
        # leaves both halves broken; measured on `dungeon/func_8188E648`, where a hoisted
        # continuation line was the whole of that row's 28 screen compile failures.  It also covers
        # the body of a braceless `if (c)` / `while (c)` written on the next line: that statement is
        # CONDITIONAL, so reading a `return`/`break` there as a tail terminator would be wrong.
        return "continuation"
    m = TERM_RE.match(s)
    if m:
        return "term:" + m.group("kw")
    if not st.endswith(";") or st.count("(") != st.count(")") or st.count("[") != st.count("]"):
        return "partial"                   # a multi-line statement or a braceless control head
    r = ctx.recs.get(k)
    if r is None:
        return "partial"
    if r["decl"] or N._DECL_START_RE.match(s):
        return "decl"
    if N.CONTROL_RE.match(s):
        return "control"
    return "stmt"


def run_from(ctx, k, stop_line, limit=TAIL_MAX, need_term=True, skips=None, tag=""):
    """The run of statements starting at line k: ([lines], terminator kind) or (None, reason).

    It ends at the first terminator (included, not counted against `limit`).  Blank lines inside a
    run are kept as part of it so the text rebuilds byte for byte; they do not count as statements.
    """
    lines, n = [], 0
    j = k
    while j < stop_line:
        kd = kind_of(ctx, j)
        if kd == "blank":
            if lines:
                lines.append(j)
            j += 1
            continue
        if kd == "stmt":
            if n >= limit:
                return None, "run-too-long"
            lines.append(j)
            n += 1
            j += 1
            continue
        if kd.startswith("term:"):
            lines.append(j)
            return lines, kd
        return None, "run-stops-at-" + kd
    return None, "run-runs-off-the-block"


def open_run(ctx, k, stop_line, limit=TAIL_MAX):
    """The statements from k up to (not including) the next terminator, label or anything else.

    Returns ([lines], terminated) where `terminated` says the run ends in a terminator.
    """
    lines, n, j = [], 0, k
    while j < stop_line:
        kd = kind_of(ctx, j)
        if kd == "blank":
            lines.append(j)
            j += 1
            continue
        if kd == "stmt":
            if n >= limit:
                break
            lines.append(j)
            n += 1
            j += 1
            continue
        if kd.startswith("term:"):
            lines.append(j)
            while lines and kind_of(ctx, lines[0]) == "blank":
                lines.pop(0)
            return lines, True
        break
    while lines and kind_of(ctx, lines[-1]) == "blank":
        lines.pop()
    while lines and kind_of(ctx, lines[0]) == "blank":
        lines.pop(0)
    return lines, False


# ------------------------------------------------------------------ the guards

def _brk_pred(h):
    return bool(LOOP_RE.match(h)) or bool(SWITCH_RE.match(h))


def _cont_pred(h):
    return bool(LOOP_RE.match(h))


def scope_ok(F, ids, src, dst):
    """Every name of a run means the same declaration at its source line and at its landing line."""
    for n in ids:
        if F.resolve(n, src) is not F.resolve(n, dst):
            return False
    return True


def jump_targets_ok(ctx, F, lines, src, dst):
    """`break`/`continue` inside a copied run keep the SAME target block, not merely the depth."""
    flow = ctx.flow(F)
    if flow is None:
        return False
    body = "\n".join(ctx.ml[k] for k in lines)
    if re.search(r"\bbreak\b", body):
        if flow._enclosing(src, _brk_pred) != flow._enclosing(dst, _brk_pred):
            return False
    if re.search(r"\bcontinue\b", body):
        if flow._enclosing(src, _cont_pred) != flow._enclosing(dst, _cont_pred):
            return False
    return True


def entered_blocks(F, frm, to):
    """The blocks a `goto` from line `frm` to line `to` would ENTER, innermost last (None: unrelated)."""
    chain, b = [], F.inner.get(to)
    while b is not None and not (b[0] < frm < b[1]):
        chain.append(b)
        b = F.parent(b)
    if b is None:
        return None                       # `to` is not reachable by descending from `frm`'s block
    return list(reversed(chain))


def jump_into_ok(F, frm, to):
    """A new goto may not enter a loop body, a switch body, or a block with an initialised decl."""
    chain = entered_blocks(F, frm, to)
    if chain is None:
        return False
    for blk in chain:
        h = F.ml[blk[0]]
        if LOOP_RE.match(h) or SWITCH_RE.match(h):
            return False
        for d in (F.decls.get(blk) or []):
            if d.get("init") is not None:
                return False
    return True


def falls_into(ctx, line):
    """Does control fall through into line `line` from the statement above it?

    Decided from SOURCE ORDER, not from `Flow.succ`: a computed `goto *` is a predecessor of every
    label there and an unclassifiable statement reaches everything, so in a jump-table function every
    label would look fallthrough-entered and no tail would ever be droppable.  Conservative: anything
    that is not a bare terminator above the label counts as falling in.
    """
    j = line - 1
    while j >= 0 and kind_of(ctx, j) == "blank":
        j -= 1
    if j < 0:
        return True
    kd = kind_of(ctx, j)
    if kd.startswith("term:"):
        return False
    if kd == "brace" and ctx.ml[j].strip() == "}":
        return True                       # a block closed above: its last arm may fall out
    return True


def ends_block(F, term_line):
    """Is `term_line` the last statement of its block (only blank lines follow it)?"""
    blk = F.inner.get(term_line)
    if blk is None:
        return False
    return all(not F.ml[j].strip() for j in range(term_line + 1, blk[1]))


# ------------------------------------------------------------------ building a candidate

def emit(ctx, base_ok, edits=None, drop=(), ins=None, touched=(), skips=None, why=""):
    """Build a candidate and run every structural invariant on it (None when one refuses)."""
    edits, ins, drop = dict(edits or {}), {k: list(v) for k, v in (ins or {}).items()}, set(drop)
    skips = collections.Counter() if skips is None else skips
    for k in set(edits) | drop | set(ins) | set(touched):
        if k in ctx.pp or (k + 1) in ctx.pp:
            skips["pp-guarded-anchor"] += 1
            return None
    cand = ctx.t.build(edits, drop, ins)
    if cand == ctx.text:
        skips["no-change"] += 1
        return None
    if _pp_sig(cand) != ctx.ppsig:
        skips["pp-guarded-edit"] += 1
        return None
    if unscored_text(cand) != ctx.usig:
        skips["unscored-arm-edit"] += 1
        return None
    if _pin_key(cand) != ctx.pinkey:
        skips["pin-multiset-changed"] += 1
        return None
    for pat in FORBIDDEN:
        if len(re.findall(pat, cand)) > len(re.findall(pat, ctx.text)):
            skips["scaffolding"] += 1
            return None
    return cand


# ------------------------------------------------------------------ dup_label / TAILDUP

def dup_label_moves(ctx, skips):
    """A label's tail copied over each `goto L;` (and the label dropped when nothing falls in)."""
    out = []
    addr_labels = set(ADDR_LABEL_RE.findall(ctx.text))
    for F in ctx.fns:
        flow = ctx.flow(F)
        if flow is None:
            skips["parse-error"] += 1
            continue
        for k in range(F.a + 1, F.b):
            m = LABEL_RE.match(ctx.ml[k])
            # `kind_of` and not LABEL_RE alone: a label written as the braceless body of an `if`
            # head on the line above is not a statement boundary this module may reason about.
            if not m or k in ctx.pp or kind_of(ctx, k) != "label":
                continue
            L = m.group("l")
            if L in addr_labels:
                skips["dup_label:label-in-jump-table"] += 1
                continue
            blk = F.inner.get(k)
            stop = blk[1] if blk else F.b
            tail, term = run_from(ctx, k + 1, stop, TAIL_MAX, True, skips, "dup_label")
            if tail is None:
                skips["dup_label:" + term] += 1
                continue
            if term == "term:goto" and L in GOTO_ANY_RE.findall(ctx.ml[tail[-1]]):
                skips["dup_label:self-loop-tail"] += 1      # `L: ... goto L;` is a loop, not a tail
                continue
            refs = [j for j in range(F.a + 1, F.b)
                    if GOTO_ANY_RE.search(ctx.ml[j]) and L in GOTO_ANY_RE.findall(ctx.ml[j])]
            whole, braceless = [], 0
            for j in refs:
                gm = GOTO_LINE_RE.match(ctx.ml[j])
                if not gm or gm.group("l") != L or j in ctx.pp:
                    continue
                if kind_of(ctx, j) != "term:goto":
                    # the ANCHOR test: `if (x)\n    goto L;` matches GOTO_LINE_RE but the goto is the
                    # CONDITIONAL body of the head above it.  Copying the tail over it would make
                    # only the tail's first statement conditional (and, when the label is dropped,
                    # strand the rest of the function) - and it compiles, so the screen is blind to
                    # it.  Refused outright; this is the dominant m2c shape and the reach it costs
                    # is reported as a deliberate over-refusal.
                    braceless += 1
                    continue
                whole.append(j)
            if braceless:
                skips["dup_label:goto-is-a-braceless-body"] += braceless
            if not whole:
                skips["dup_label:no-whole-line-goto"] += 1
                continue
            ids = _ids([ctx.ml[j] for j in tail])
            good = []
            for j in whole:
                if not scope_ok(F, ids, tail[0], j):
                    skips["dup_label:scope"] += 1
                    continue
                if not jump_targets_ok(ctx, F, tail, tail[0], j):
                    skips["dup_label:jump-target"] += 1
                    continue
                good.append(j)
            if not good:
                continue
            fall = falls_into(ctx, k)
            groups = []
            if len(good) > 1:
                groups.append(("all", good))
            near = sorted(good, key=lambda j: (ctx.near_pin(j), j))[:4]
            for j in near:
                groups.append(("one@%d" % (j + 1), [j]))
            for tag, chosen in groups:
                drop_label = (not fall) and set(chosen) == set(refs)
                if _commented(ctx, chosen) or (drop_label and _commented(ctx, [k])):
                    skips["dup_label:comment-on-a-replaced-line"] += 1
                    continue
                edits, ins, drop = {}, {}, set()
                for j in chosen:
                    body = N._reindent([ctx.real[x] for x in tail], N._ind(ctx.real[tail[0]]),
                                       N._ind(ctx.real[j]))
                    edits[j] = body[0]
                    if len(body) > 1:
                        ins[j] = body[1:]
                if drop_label:
                    drop |= {k} | set(tail)
                cand = emit(ctx, True, edits, drop, ins, touched=[k] + tail, skips=skips)
                if cand is not None:
                    out.append(("dup_label:%s:%s%s" % (L, tag, ":moved" if drop_label else ""),
                                min(ctx.near_pin(j) for j in chosen), cand))
    return out


# ------------------------------------------------------------------ sink_tail / hoist_tail

def _if_arms(ctx, F, skips, tag):
    """[(if_line, close_a, close_b or None)] for `if (...) {` blocks, with the `} else {` form."""
    out = []
    byopen = {o: c for o, c in F.blocks}
    for o, c in F.blocks:
        if not IF_RE.match(ctx.ml[o]):
            continue
        if not _starts_statement(ctx, o):
            # the ANCHOR test for both directions: this `if (...) {` is itself the braceless body of
            # a `while (a)` / `if (a)` / `else` / `do` head on the line above, so the statements
            # AFTER it are NOT in that head's body.  Sinking them into the arms would make them
            # conditional on the outer head, and hoisting an arm suffix out of them would make it
            # unconditional.  Both compile, so the screen cannot see either.
            skips[tag + ":if-head-is-a-braceless-body"] += 1
            continue
        if ELSE_RE.match(ctx.ml[c]) and c in byopen and re.match(r"^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$",
                                                                 ctx.ml[c]):
            out.append((o, c, byopen[c]))
        elif ctx.ml[c].strip() == "}":
            out.append((o, c, None))
    return out


def sink_tail_moves(ctx, skips):
    """The statements after an if/else pushed into both arms (or into a new `else`)."""
    out = []
    for F in ctx.fns:
        flow = ctx.flow(F)
        if flow is None:
            continue
        for o, ca, cb in _if_arms(ctx, F, skips, "sink_tail"):
            end = cb if cb is not None else ca
            blk = F.inner.get(o)
            stop = blk[1] if blk else F.b
            tail, _term = open_run(ctx, end + 1, stop, TAIL_MAX)
            if not tail:
                skips["sink_tail:no-tail"] += 1
                continue
            if any(kind_of(ctx, j) not in ("stmt",) and not kind_of(ctx, j).startswith("term:")
                   for j in tail):
                skips["sink_tail:tail-not-plain"] += 1
                continue
            ids = _ids([ctx.ml[j] for j in tail])
            ind = N._ind(ctx.real[o])
            arm_ind = ind + "    "
            body = N._reindent([ctx.real[x] for x in tail], N._ind(ctx.real[tail[0]]), arm_ind)
            if cb is not None:
                if _last_is_term(ctx, o, ca) or _last_is_term(ctx, ca, cb):
                    skips["sink_tail:arm-terminates"] += 1
                    continue
                if not (scope_ok(F, ids, tail[0], ca - 1) and scope_ok(F, ids, tail[0], cb - 1)):
                    skips["sink_tail:scope"] += 1
                    continue
                if not (jump_targets_ok(ctx, F, tail, tail[0], ca - 1)
                        and jump_targets_ok(ctx, F, tail, tail[0], cb - 1)):
                    skips["sink_tail:jump-target"] += 1
                    continue
                ins = {ca - 1: list(body), cb - 1: list(body)}
                cand = emit(ctx, True, {}, set(tail), ins, touched=[ca, cb] + tail, skips=skips)
                if cand is not None:
                    out.append(("sink_tail:if-else@%d" % (o + 1), ctx.near_pin(o), cand))
            else:
                if ctx.real[ca].strip() != "}":
                    # the close line carries a trailing comment (often a pin note): rewriting it as
                    # `} else {` would silently drop that comment
                    skips["sink_tail:close-line-carries-a-comment"] += 1
                    continue
                if not _last_is_term(ctx, o, ca):
                    # T copied into the arm AND left in place would run twice on the true path
                    skips["sink_tail:arm-does-not-terminate"] += 1
                    continue
                if not scope_ok(F, ids, tail[0], ca):
                    skips["sink_tail:scope"] += 1
                    continue
                if not jump_targets_ok(ctx, F, tail, tail[0], ca):
                    skips["sink_tail:jump-target"] += 1
                    continue
                edits = {ca: ind + "} else {"}
                ins = {ca: list(body) + [ind + "}"]}
                cand = emit(ctx, True, edits, set(tail), ins, touched=[ca] + tail, skips=skips)
                if cand is not None:
                    out.append(("sink_tail:else@%d" % (o + 1), ctx.near_pin(o), cand))
    return out


def _last_is_term(ctx, open_line, close_line):
    """Does the block (open_line, close_line) end in a terminator?"""
    for j in range(close_line - 1, open_line, -1):
        kd = kind_of(ctx, j)
        if kd == "blank":
            continue
        return kd.startswith("term:")
    return False


def _contiguous(ctx, lines, end):
    """Nothing but blank lines between the first of `lines` and `end` except `lines` themselves.

    `_arm_lines` skips preprocessor-guarded lines, so without this a hoisted suffix could step OVER
    a guarded statement (or leave one below it in the arm) and reorder the two.
    """
    keep = set(lines)
    return all(j in keep or not ctx.ml[j].strip() for j in range(lines[0], end))


def _arm_lines(ctx, o, c):
    """The statement lines directly inside a block, in order (blank lines dropped)."""
    return [j for j in range(o + 1, c) if ctx.ml[j].strip() and (ctx.ml[j].lstrip()[0] != "#")
            and (j not in ctx.pp)]


def hoist_tail_moves(ctx, skips):
    """The common tail of two arms pulled out after the if/else."""
    out = []
    for F in ctx.fns:
        flow = ctx.flow(F)
        if flow is None:
            continue
        for o, ca, cb in _if_arms(ctx, F, skips, "hoist_tail"):
            if cb is None:
                continue
            A = _arm_lines(ctx, o, ca)
            B = _arm_lines(ctx, ca, cb)
            if not A or not B:
                continue
            n = 0
            while n < min(len(A), len(B)) and n < TAIL_MAX + 1:
                a, b = A[-1 - n], B[-1 - n]
                ka, kb = kind_of(ctx, a), kind_of(ctx, b)
                if ka != kb or not (ka == "stmt" or ka.startswith("term:")):
                    break
                if F.inner.get(a) != (o, ca) or F.inner.get(b) != (ca, cb):
                    break                 # a statement inside a nested block, not at the arm's own depth
                if _key(ctx, [a]) != _key(ctx, [b]):
                    break
                n += 1
            if n == 0:
                skips["hoist_tail:no-common-tail"] += 1
                continue
            if n >= len(A) or n >= len(B):
                skips["hoist_tail:empties-an-arm"] += 1
                continue
            for take in range(n, 0, -1):
                ta, tb = A[-take:], B[-take:]
                if not (_contiguous(ctx, ta, ca) and _contiguous(ctx, tb, cb)):
                    # a preprocessor-guarded statement sits between the suffix lines or below them:
                    # hoisting the suffix out would reorder it past that statement
                    skips["hoist_tail:pp-line-inside-the-suffix"] += 1
                    continue
                # BOTH copies are checked.  The `if` arm's lines survive (re-indented at `cb`) and
                # the `else` arm's are DELETED, so the else copy's names must resolve to the same
                # declarations at `cb` as they did in the arm: an arm-local `x` shadowing a
                # parameter made the deleted copy read the local and the surviving copy read the
                # parameter, and it compiled.  Every other move already compares both sites.
                ids = _ids([ctx.ml[j] for j in ta])
                ids_b = _ids([ctx.ml[j] for j in tb])
                if not (scope_ok(F, ids, ta[0], cb) and scope_ok(F, ids_b, tb[0], cb)):
                    skips["hoist_tail:scope"] += 1
                    continue
                if not (jump_targets_ok(ctx, F, ta, ta[0], cb)
                        and jump_targets_ok(ctx, F, tb, tb[0], cb)):
                    skips["hoist_tail:jump-target"] += 1
                    continue
                if _commented(ctx, tb):
                    # only the `if` arm's copy survives (re-indented, comment and all); the `else`
                    # arm's lines are deleted outright, so a comment on one of them would be lost
                    skips["hoist_tail:comment-on-a-deleted-line"] += 1
                    continue
                ind = N._ind(ctx.real[o])
                body = N._reindent([ctx.real[x] for x in ta], N._ind(ctx.real[ta[0]]), ind)
                cand = emit(ctx, True, {}, set(ta) | set(tb), {cb: body},
                            touched=[cb] + ta + tb, skips=skips)
                if cand is not None:
                    out.append(("hoist_tail:%d@%d" % (take, o + 1), ctx.near_pin(o), cand))
    return out


# ------------------------------------------------------------------ merge_runs / split_ret

def _runs_of(ctx, F, min_stmts=2):
    """[(lines, terminator kind)] - every run of 2..TAIL_MAX statements ending in a terminator."""
    out = []
    for j in range(F.a + 1, F.b):
        kd = kind_of(ctx, j)
        if not kd.startswith("term:"):
            continue
        run = [j]
        n = 0
        k = j - 1
        while k > F.a and n < TAIL_MAX - 1:
            kk = kind_of(ctx, k)
            if kk == "blank":
                k -= 1
                continue
            if kk != "stmt":
                break
            run.insert(0, k)
            n += 1
            k -= 1
            if n + 1 >= min_stmts:
                out.append((list(run), kd))
    return out


def merge_runs_moves(ctx, skips):
    """Two token-identical runs: one becomes `goto L;`, a fresh label L marks the other."""
    out = []
    for F in ctx.fns:
        flow = ctx.flow(F)
        if flow is None:
            continue
        groups = collections.defaultdict(list)
        for run, term in _runs_of(ctx, F, min_stmts=2):
            if any(j in ctx.pp for j in run):
                continue
            groups[(_key(ctx, run), term)].append(run)
        for (key, term), runs in groups.items():
            if len(runs) < 2:
                continue
            runs.sort(key=lambda r: r[0])
            for i in range(len(runs)):
                for j in range(i + 1, len(runs)):
                    a, b = runs[i], runs[j]
                    if set(a) & set(b):
                        continue
                    for tag, keep, gone in (("first", a, b), ("second", b, a)):
                        cand = _merge_pair(ctx, F, keep, gone, term, tag, skips)
                        if cand is not None:
                            out.append(("merge_runs:%s:%d+%d" % (tag, keep[0] + 1, gone[0] + 1),
                                        min(ctx.near_pin(keep[0]), ctx.near_pin(gone[0])), cand))
    return out


def _merge_pair(ctx, F, keep, gone, term, tag, skips):
    """`gone` becomes `goto L;`; a fresh label L is inserted before `keep`."""
    if not ends_block(F, keep[-1]):
        skips["merge_runs:not-last-in-block"] += 1
        return None
    if term in ("term:break", "term:continue"):
        pred = _brk_pred if term == "term:break" else _cont_pred
        flow = ctx.flow(F)
        if flow is None or flow._enclosing(keep[-1], pred) != flow._enclosing(gone[-1], pred):
            skips["merge_runs:jump-target"] += 1
            return None
    ids = _ids([ctx.ml[x] for x in keep])
    if not scope_ok(F, ids, keep[0], gone[0]):
        skips["merge_runs:scope"] += 1
        return None
    if not jump_into_ok(F, gone[0], keep[0]):
        skips["merge_runs:jump-into"] += 1
        return None
    if _commented(ctx, gone):
        skips["merge_runs:comment-on-a-replaced-line"] += 1
        return None
    L = _fresh_label(ctx.text)
    ind = N._ind(ctx.real[keep[0]])
    edits = {gone[0]: N._ind(ctx.real[gone[0]]) + "goto %s;" % L}
    drop = set(gone[1:])
    ins = {keep[0] - 1: [ind + L + ":"]}
    return emit(ctx, True, edits, drop, ins, touched=[keep[0], keep[0] - 1] + list(gone), skips=skips)


RETV_RE = re.compile(r"^[ \t]*return[ \t]+(?P<v>%s)[ \t]*;[ \t]*$" % ID)
ASSIGN_RE = re.compile(r"^[ \t]*(?P<v>%s)[ \t]*=(?!=)(?P<e>[^;]*);[ \t]*$" % ID)


def _return_type(F):
    """The function's declared return type, normalised the way `natural._ptype` spells one."""
    ml = F.ml
    head = "\n".join(ml[max(0, F.a - 8):F.a + 1])
    if "{" not in head:
        return None
    head = head[:head.rfind("{")]
    r = head.rfind(")")
    if r < 0:
        return None
    d, left = 0, None
    for k in range(r, -1, -1):
        d += head[k] == ")"
        d -= head[k] == "("
        if d == 0:
            left = k
            break
    if left is None:
        return None
    pre = re.split(r"[;}]", head[:left])[-1]
    m = re.search(r"(?P<ptr>[ \t*]*)(?P<name>%s)[ \t]*$" % ID, pre)
    if not m:
        return None
    ty = pre[:m.start()] + m.group("ptr")
    ty = re.sub(r"\b(?:static|extern|inline|__inline__)\b", " ", ty)
    ty = re.sub(r"__attribute__[ \t]*\(\(.*?\)\)", " ", ty, flags=re.S)
    return _sq(ty)


def split_ret_moves(ctx, skips):
    """`v = E; goto R;` ... `R: return v;` written as `return E;`, and the reverse."""
    out = []
    for F in ctx.fns:
        out.extend(_split_ret_forward(ctx, F, skips))
        out.extend(_ret_merge(ctx, F, skips))
    return out


def _split_ret_forward(ctx, F, skips):
    out = []
    rty = _return_type(F)
    for k in range(F.a + 1, F.b):
        m = LABEL_RE.match(ctx.ml[k])
        if not m or k in ctx.pp or kind_of(ctx, k) != "label":
            continue
        R = m.group("l")
        j = k + 1
        while j < F.b and kind_of(ctx, j) == "blank":
            j += 1
        rm = RETV_RE.match(ctx.ml[j]) if j < F.b else None
        if not rm or j in ctx.pp or kind_of(ctx, j) != "term:return":
            continue
        v = rm.group("v")
        d = F.resolve(v, j)
        if d is None or not d.get("single") or d.get("param") or d.get("arr"):
            skips["split_ret:not-a-plain-local"] += 1
            continue
        if d["pinned"] or (d["quals"] & N.NOSHARE) or (d["name"], d["line"]) in F.pinned:
            skips["split_ret:qualified-or-pinned"] += 1
            continue
        if d["init"] is not None:
            # dropping the declaration would drop its initialiser, which may have a side effect
            skips["split_ret:declaration-has-an-initialiser"] += 1
            continue
        if rty is None or d["ty"] is None or _sq(d["ty"]) != rty:
            # `s16 v; ... return v;` in an `s32` function is a truncation `return E;` would drop
            skips["split_ret:type-differs-from-return-type"] += 1
            continue
        if falls_into(ctx, k):
            skips["split_ret:fallthrough-into-label"] += 1
            continue
        refs = [x for x in range(F.a + 1, F.b)
                if GOTO_ANY_RE.search(ctx.ml[x]) and R in GOTO_ANY_RE.findall(ctx.ml[x])]
        if ADDR_LABEL_RE.search(ctx.text) and R in ADDR_LABEL_RE.findall(ctx.text):
            skips["split_ret:label-in-jump-table"] += 1
            continue
        pairs = []
        ok = True
        for x in refs:
            gm = GOTO_LINE_RE.match(ctx.ml[x])
            if not gm or gm.group("l") != R or x in ctx.pp:
                ok = False
                break
            if kind_of(ctx, x) != "term:goto":
                # the ANCHOR test: `goto R;` is the braceless body of a head on the line above
                ok = False
                break
            p = x - 1
            while p > F.a and kind_of(ctx, p) == "blank":
                p -= 1
            if kind_of(ctx, p) != "stmt":
                # the ANCHOR test on the line this move REWRITES.  `if (c)\n    v = 1;\ngoto R;`
                # reads as the pair `v = E; goto R;` to ASSIGN_RE, but the assignment is
                # conditional and the goto is not: rewriting it as `return 1;` and dropping the
                # goto strands the `!c` path (and, in the `:dropped` form, deletes `R: return v;`
                # with it).  It compiles, so the screen cannot see it.
                ok = False
                break
            am = ASSIGN_RE.match(ctx.ml[p])
            if not am or am.group("v") != v or N._occ(v).search(am.group("e")) or p in ctx.pp:
                ok = False
                break
            pairs.append((p, x))
        if not ok or not pairs:
            skips["split_ret:goto-not-preceded-by-the-assignment"] += 1
            continue
        mentions = [x for x in range(F.a + 1, F.b) if N._occ(v).search(ctx.ml[x])]
        expect = {d["line"], j} | {p for p, _ in pairs}
        if set(mentions) - expect:
            skips["split_ret:variable-used-elsewhere"] += 1
            continue
        groups = [("all", pairs)] if len(pairs) > 1 else []
        groups += [("one@%d" % (p + 1), [(p, x)])
                   for p, x in sorted(pairs, key=lambda pr: ctx.near_pin(pr[0]))[:4]]
        for tag, chosen in groups:
            full = len(chosen) == len(pairs)
            lost = [y for pr in chosen for y in pr] + ([k, j, d["line"]] if full else [])
            if _commented(ctx, lost):
                skips["split_ret:comment-on-a-replaced-line"] += 1
                continue
            edits, drop = {}, set()
            for p, x in chosen:
                e = ctx.real[p]
                am = ASSIGN_RE.match(ctx.ml[p])
                rhs = e[am.start("e"):am.end("e")].strip()
                edits[p] = N._ind(e) + "return %s;" % rhs
                drop.add(x)
            if full:
                drop |= {k, j, d["line"]}
            cand = emit(ctx, True, edits, drop, {},
                        touched=[k, j, d["line"]] + [x for pr in chosen for x in pr], skips=skips)
            if cand is not None:
                out.append(("split_ret:%s:%s%s" % (R, tag, ":dropped" if full else ""),
                            min(ctx.near_pin(p) for p, _ in chosen), cand))
    return out


def _ret_merge(ctx, F, skips):
    """The reverse: two token-identical `return E;` merged under one label."""
    out = []
    groups = collections.defaultdict(list)
    for j in range(F.a + 1, F.b):
        if kind_of(ctx, j) != "term:return" or j in ctx.pp:
            continue
        m = TERM_RE.match(ctx.ml[j])
        if not m or not m.group("arg").strip():
            continue                      # a bare `return;` carries no value: nothing to merge
        groups[_key(ctx, [j])].append(j)
    for key, js in groups.items():
        if len(js) < 2:
            continue
        for i in range(len(js)):
            for k in range(i + 1, len(js)):
                a, b = js[i], js[k]
                for tag, keep, gone in (("first", a, b), ("second", b, a)):
                    if not ends_block(F, keep):
                        skips["split_ret:merge-not-last-in-block"] += 1
                        continue
                    ids = _ids([ctx.ml[keep]])
                    if not scope_ok(F, ids, keep, gone):
                        skips["split_ret:merge-scope"] += 1
                        continue
                    if not jump_into_ok(F, gone, keep):
                        skips["split_ret:merge-jump-into"] += 1
                        continue
                    if _commented(ctx, [gone]):
                        skips["split_ret:merge-comment-on-a-replaced-line"] += 1
                        continue
                    L = _fresh_label(ctx.text, "return_tail")
                    edits = {gone: N._ind(ctx.real[gone]) + "goto %s;" % L}
                    ins = {keep - 1: [N._ind(ctx.real[keep]) + L + ":"]}
                    cand = emit(ctx, True, edits, set(), ins,
                                touched=[keep, keep - 1, gone], skips=skips)
                    if cand is not None:
                        out.append(("split_ret:merge:%s:%d+%d" % (tag, keep + 1, gone + 1),
                                    min(ctx.near_pin(keep), ctx.near_pin(gone)), cand))
    return out


MOVES = (dup_label_moves, sink_tail_moves, hoist_tail_moves, merge_runs_moves, split_ret_moves)


# ------------------------------------------------------------------ the menu

def tailform_moves(text, skips=None, cap=MENU_CAP):
    """[(kind, label, text)] - every tail move of one text, nearest a live pin site first."""
    skips = collections.Counter() if skips is None else skips
    out = []
    try:
        ctx = Ctx(text)
    except Exception as e:
        skips["error:Ctx:" + type(e).__name__] += 1
        return out
    scored = []
    for move in MOVES:
        kind = move.__name__.removesuffix("_moves")
        try:
            got = move(ctx, skips)
        except Exception as e:
            skips["error:%s:%s" % (kind, type(e).__name__)] += 1
            continue
        for label, dist, cand in got:
            scored.append((dist, kind, label, cand))
    scored.sort(key=lambda z: (z[0], z[2]))
    seen = set()
    for dist, kind, label, cand in scored:
        h = sha_text(cand)
        if h in seen:
            continue
        seen.add(h)
        out.append((kind, label, cand))
        if len(out) >= cap:
            break
    return out


def tailform_candidates(text, cap=MENU_CAP):
    """[(label, text)] for the engine menu (<= cap, nearest a live pin site first)."""
    return [(label, cand) for _kind, label, cand in tailform_moves(text, None, cap)]


# ------------------------------------------------------------------ the generator

class T:
    name = "t67_tailform"
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
        m = N.mask(text)
        has_goto = bool(GOTO_ANY_RE.search(m))
        has_label = any(LABEL_RE.match(ln) for ln in m.splitlines())
        has_if = bool(re.search(r"^[ \t]*if[ \t]*\(.*\)[ \t]*\{[ \t]*$", m, re.M))
        has_ret = len(re.findall(r"^[ \t]*return[ \t]+[^;]+;[ \t]*$", m, re.M)) >= 2
        if not ((has_goto and has_label) or has_if or has_ret):
            return "no label, if-block or repeated return to reshape"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        screens = max(1, int(os.getenv("T67_SCREENS", str(SCREEN_BUDGET))))
        verifies = max(1, int(os.getenv("T67_VERIFY", str(VERIFY_BUDGET))))
        beam = max(1, int(os.getenv("T67_BEAM", str(BEAM))))
        pins_in = len(sites_of(text))
        usig = unscored_text(text)
        allskips, skips = collections.Counter(), collections.Counter()
        moves = collections.Counter()
        log = dict(pins_in=pins_in, pins_out=pins_in, screen_budget=screens, vf_budget=verifies,
                   beam=beam, plans=0, candidates_n=0, screened=0, tried=0, compile_failures=0,
                   passes=0, depth2=0, asis=[], steps=[], nearest=[], erasures=[], moves={},
                   moves_first_pass={}, skips={}, skips_all_passes={})
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
                pins = sites_of(cur)

                # ---- the moves of the pinned text itself: evidence only (no pin is gone, so
                # `improves` refuses them), and the distance says whether the move is neutral.
                if first:
                    asis = tailform_moves(cur, skips)
                    log["moves_first_pass"] = dict(sorted(collections.Counter(
                        k for k, _l, _c in asis).items()))
                    for kind, label, cand in asis[:ASIS_CAP]:
                        if log["screened"] >= screens:
                            skips["budget"] += 1
                            break
                        log["screened"] += 1
                        got = compile_s(row, cand)
                        if got is None:
                            log["compile_failures"] += 1
                            skips["compile-fail"] += 1
                            continue
                        log["asis"].append({"d": sdiff(ref, got), "label": label})

                plans = list(enumerate(pins))[:PLAN_CAP]
                log["plans"] = len(plans)
                seen_cand = set()
                for pi, (idx, site) in enumerate(plans):
                    if log["screened"] >= screens:
                        skips["budget"] += 1
                        break
                    allowance = max(8, (screens - log["screened"]) // max(1, len(plans) - pi))
                    spent0 = log["screened"]
                    base = erase_many(cur, [site], clean_notes=True)
                    if unscored_text(base) != usig:
                        skips["erasure-in-unscored-arm"] += 1
                        continue
                    if len(sites_of(base)) != len(pins) - 1:
                        skips["erasure-changed-more-than-one-pin"] += 1
                        continue
                    log["screened"] += 1
                    erased = compile_s(row, base)
                    if erased is None:
                        log["compile_failures"] += 1
                        skips["erasure-compile-fail"] += 1
                        continue
                    d0 = sdiff(ref, erased)
                    log["erasures"].append({"plan": "pin%d" % idx, "macro": site[1], "d0": d0})

                    depth1 = []
                    for kind, label, cand in tailform_moves(base, skips):
                        h = sha_text(cand)
                        if h in seen_cand:
                            continue
                        seen_cand.add(h)
                        log["candidates_n"] += 1
                        if not _sane(cur, cand, usig, len(pins)):
                            skips["scaffolding-or-arm"] += 1
                            continue
                        if log["screened"] - spent0 >= allowance * 3 // 4 or log["screened"] >= screens:
                            skips["budget"] += 1
                            break
                        log["screened"] += 1
                        got = compile_s(row, cand)
                        if got is None:
                            log["compile_failures"] += 1
                            skips["compile-fail"] += 1
                            continue
                        d = sdiff(ref, got)
                        moves[kind] += 1
                        step = "pin%d+%s" % (idx, label)
                        near.append((d, step, d0))
                        depth1.append((d, kind, label, cand))
                        if d != 0:
                            continue
                        if cls._try(cur, cand, got, vf, log, dead, skips, verifies, step):
                            cur, won = cand, True
                            break
                    if won:
                        break

                    # ---- depth 2: one more move on the nearest depth-1 texts
                    depth1.sort(key=lambda z: (z[0], z[2]))
                    for d, kind, label, seed in depth1[:beam]:
                        if log["screened"] - spent0 >= allowance or log["screened"] >= screens:
                            skips["budget"] += 1
                            break
                        for kind2, label2, cand in tailform_moves(seed, skips):
                            h = sha_text(cand)
                            if h in seen_cand:
                                continue
                            seen_cand.add(h)
                            log["candidates_n"] += 1
                            if not _sane(cur, cand, usig, len(pins)):
                                skips["scaffolding-or-arm"] += 1
                                continue
                            if log["screened"] - spent0 >= allowance or log["screened"] >= screens:
                                skips["budget"] += 1
                                break
                            log["screened"] += 1
                            log["depth2"] += 1
                            got = compile_s(row, cand)
                            if got is None:
                                log["compile_failures"] += 1
                                skips["compile-fail"] += 1
                                continue
                            dd = sdiff(ref, got)
                            moves[kind2] += 1
                            step = "pin%d+%s / %s" % (idx, label, label2)
                            near.append((dd, step, d0))
                            if dd != 0:
                                continue
                            if cls._try(cur, cand, got, vf, log, dead, skips, verifies, step):
                                cur, won = cand, True
                                break
                        if won:
                            break
                    if won:
                        break
                if first:
                    log["skips"] = dict(sorted(skips.items()))
                    first = False
                allskips += skips
                if not won:
                    break
        except Exception as e:
            log["error"] = repr(e)
            allskips += skips
        if not log["skips"] and allskips:
            log["skips"] = dict(sorted(allskips.items()))
        log["skips_all_passes"] = dict(sorted(allskips.items()))
        log["moves"] = dict(sorted(moves.items()))
        log["nearest"] = [{"d": d, "d0": z, "label": l}
                          for d, l, z in sorted(near, key=lambda x: (x[0] is None, x[0]))[:12]]
        log["erasures"] = sorted(log["erasures"], key=lambda e: (e["d0"] is None, e["d0"]))[:8]
        log["asis"] = sorted(log["asis"], key=lambda e: (e["d"] is None, e["d"]))[:8]
        log["pins_out"] = len(sites_of(cur))
        if not log["steps"]:
            return None, log
        return cur, log

    @staticmethod
    def _try(cur, cand, got, vf, log, dead, skips, verifies, step):
        if not improves(cur, cand):
            skips["no-improvement"] += 1
            return False
        listing = (sha_text("\n".join(got)), tuple(sorted(s[1] for s in sites_of(cand))))
        if listing in dead:
            skips["same-listing-as-a-failed-verify"] += 1
            return False
        if log["tried"] >= verifies:
            skips["budget"] += 1
            return False
        log["tried"] += 1
        if not vf(cand).get("exact"):
            dead.add(listing)
            return False
        log["steps"].append(step)
        return True


def _sane(original, candidate, signature, npins):
    """The sweep-level guard: fewer pins, the unscored arms untouched, no scaffolding added."""
    if unscored_text(candidate) != signature or len(sites_of(candidate)) >= npins:
        return False
    for pat in FORBIDDEN:
        if len(re.findall(pat, candidate)) > len(re.findall(pat, original)):
            return False
    return True
