"""T15: the lane recipes as a search.

Four lanes over the near band closed 21 of 50 rows, and three of the shapes that did it are
mechanical.  This plugin tries them, in cost order, against the row's fully stripped text.

  maskfold   a local declared wider than the load that fills it, with an explicit `& 0xFF` /
             `& 0xFFFF`, is a length defect: the mask folds away because `lbu`/`lhu` already
             zero-extend, so gcc emits one word fewer than retail.  Declaring the local at the
             load's width and dropping the mask makes gcc re-mask before the use.  (Two sibling
             rows fell to this unchanged in the length-drift lane.)
  narrow     a value-preserving *mode* change on one side of a copy.  gcc-2.7/2.8's cse collapses
             a plain `b = a;` into one pseudo whenever both stay live, and then the allocator has
             no choice left - that collapse is what most `reg-rename` pins stand in for.  A
             narrowing assignment is not a REG-REG set in RTL, so cse never merges the two.
  mask2cast  `E & 0xFFFF` at a use site becomes `(u16) E` - the same mode-change handle as
             `narrow`, applied at the use rather than the declaration (harvested from an Astra
             depin lane, which is why `maskfold`'s declaration-only rewrite had missed it).
  dup_if     the statement after an `if (...) { }` written into both arms instead (same source).
  fence      `do { stmt; } while (0)` is a zero-byte scheduling barrier: it pins a statement's
             definition point without emitting anything.  A bare block does NOT do this - only the
             loop note does - so it is scaffolding in C clothing and `census.py` counts it.  It is
             tried LAST, after the shapes that are real source, and the journal says when it fired.

**Why a mechanical search over types and fences is safe:** the verdict is byte equality against
retail.  A narrowing that changed the function's behaviour could not compile to retail's bytes, so
a semantic change cannot survive the gate.  The search may therefore be liberal; only the budget
limits it.
"""
import json, os, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of, erase, asm_blocker

try:
    from .t12_stmtorder import strip_pins, mask, depths, movable, is_decl, NOTE_RE
    from . import natural
except ImportError:                       # pragma: no cover - direct import
    from t12_stmtorder import strip_pins, mask, depths, movable, is_decl, NOTE_RE
    import natural

BAND = int(os.environ.get("T15_BAND", "12"))       # strip damage a row must be within
BUDGET = int(os.environ.get("T15_BUDGET", "45"))   # verify runs per row (T15_BUDGET to raise)
ROUNDS = int(os.environ.get("T15_ROUNDS", "3"))    # greedy hill-climb rounds
WIDE = os.environ.get("T15_WIDE") == "1"          # include the generators with no measured win yet
NOFENCE = os.environ.get("T15_NOFENCE") == "1"    # drop the fence family: a search that may not add barrier debt
PARTIAL = os.environ.get("T15_PARTIAL", "1") == "1"   # accept a partial removal (10 pins -> 1) as a result
NARROW = {"s32": ["s16", "s8"], "u32": ["u16", "u8"], "int": ["s16", "s8"],
          "unsigned": ["u16", "u8"], "s16": ["s8"], "u16": ["u8"]}
# `register` is a hint with no ABI meaning, so retyping through it is safe - but until 2026-09-10
# this pattern had no storage-class slot at all, and every declaration carrying one was invisible
# to `decls()` and therefore to maskfold, narrow and retype.  dungeon/func_8132C638 hid three of
# its four locals that way: the sweep spent 400 candidates on it and could not win, while the
# shape that took it byte-exact was `maskfold` on `register u32 count;` + `return count & 0xFFFF;`
# - a candidate this generator would have produced on its own.  128 pinned rows carry such a
# declaration, 26 of them alongside an explicit mask.  `static` and `volatile` are deliberately NOT
# admitted: those change storage duration and access semantics, not just width.
DECL_RE = re.compile(r"^(?P<i>[ \t]+)(?:register[ \t]+)?(?P<ty>u8|s8|u16|s16|u32|s32|int|unsigned)[ \t]+(?P<n>[A-Za-z_]\w*)[ \t]*;[ \t]*$")
MASK_RE = re.compile(r"\b(?P<n>[A-Za-z_]\w*)[ \t]*&[ \t]*0x(?P<m>[Ff]{2}|[Ff]{4})\b")

_STRIP = None


def strip_census():
    """The strip probe, keyed by row.

    Built into a LOCAL and rebound in one assignment.  `sweep.py` runs rows through a
    ThreadPoolExecutor, and the previous form set the global to `{}` before filling it: every
    worker that arrived during the ~1,900-line read saw a non-None, half-filled dict, missed its
    row and refused it as "no strip probe for this row".  It cost 15 of the 21 rows in one sweep
    and has been quietly refusing rows in every threaded run.  Rebinding once makes the dict
    either absent or complete, never partial.
    """
    global _STRIP
    if _STRIP is None:
        built = {}
        p = ROOT / "ledger/pins_strip.jsonl"
        if p.exists():
            for line in p.read_text().splitlines():
                if line.strip():
                    r = json.loads(line)
                    built[r["id"]] = r
        _STRIP = built
    return _STRIP


def decls(text):
    """[(line index, indent, type, name)] for the plain scalar locals of the function."""
    out = []
    for i, ln in enumerate(text.splitlines()):
        m = DECL_RE.match(ln)
        if m:
            out.append((i, m.group("i"), m.group("ty"), m.group("n")))
    return out


def retype(text, idx, ty, name, newty):
    lines = text.splitlines(True)
    ln = lines[idx]
    nl = "\n" if ln.endswith("\n") else ""
    lines[idx] = re.sub(r"\b%s\b" % ty, newty, ln[:len(ln) - len(nl)], count=1) + nl
    return "".join(lines)


def maskfold_candidates(text):
    """Narrow a local to its mask width and delete the mask (`x & 0xFF` with `u8 x`)."""
    out = []
    masked = mask(text)
    for idx, ind, ty, name in decls(text):
        width = None
        for m in MASK_RE.finditer(masked):
            if m.group("n") != name:
                continue
            width = "u8" if len(m.group("m")) == 2 else "u16"
            break
        if width is None or ty == width:
            continue
        t = retype(text, idx, ty, name, width)
        t = MASK_RE.sub(lambda m: m.group("n") if m.group("n") == name else m.group(0), t)
        if t != text:
            out.append(("maskfold:%s->%s" % (name, width), t))
    return out


def narrow_candidates(text):
    out = []
    for idx, ind, ty, name in decls(text):
        for newty in NARROW.get(ty, []):
            out.append(("narrow:%s %s->%s" % (name, ty, newty), retype(text, idx, ty, name, newty)))
    return out


def fence_candidates(text):
    """Wrap one simple statement in `do { ... } while (0);` - a zero-byte scheduling barrier."""
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    dep = depths(masked)
    for i, ln in enumerate(lines):
        if not movable(masked[i]) or is_decl(masked[i]):
            continue
        # Measured precondition: a fence only does anything when the statement's own
        # value-producing insn survives to final code (a real store, a real computation).  On a
        # plain register-to-register copy, cse/combine delete the insn outright and the fence is a
        # no-op or a regression - four rows of one lane showed exactly that.
        cp = re.fullmatch(r"(?P<d>[A-Za-z_]\w*)\s*=\s*(?P<s>[A-Za-z_]\w*)\s*;", masked[i].strip())
        if cp and cp.group("s") in {n for _, _, _, n in decls(text)}:
            continue        # a LOCAL-to-local copy only; `x = D_800D0C40;` is a load and does fence
        nl = "\n" if ln.endswith("\n") else ""
        body = ln[:len(ln) - len(nl)]
        ind = re.match(r"[ \t]*", body).group(0)
        new = f"{ind}do {{\n{ind}    {body.strip()}\n{ind}}} while (0);{nl}"
        out.append(("fence:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 1:])))
    for i, ln in enumerate(lines):
        s = masked[i].strip()
        if not s.startswith("return") or not s.endswith(";"):
            continue
        nl = "\n" if ln.endswith("\n") else ""
        body = ln[:len(ln) - len(nl)]
        ind = re.match(r"[ \t]*", body).group(0)
        new = f"{ind}do {{\n{ind}    {body.strip()}\n{ind}}} while (0);{nl}"
        out.append(("fence-return:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 1:])))
    return out


USE_MASK_RE = re.compile(r"(?P<e>\b[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+)*)\s*&\s*0x(?P<m>[Ff]{2}|[Ff]{4})\b")


def mask2cast_candidates(text):
    """`E & 0xFFFF` at a USE site becomes `(u16) E`.

    Harvested from an Astra depin lane: the mask and the cast compute the same value, but a cast is
    a mode change in RTL where the AND is an ordinary binary op, so cse cannot fold the two pseudos
    together - the same handle as `narrow`, applied at the use instead of the declaration.  t15's
    `maskfold` only ever retyped the *declaration*, which is why it missed these.
    """
    out = []
    masked = mask(text)
    for m in USE_MASK_RE.finditer(masked):
        ty = "u8" if len(m.group("m")) == 2 else "u16"
        expr = text[m.start("e"):m.end("e")]
        cand = text[:m.start()] + f"({ty}) {expr}" + text[m.end():]
        out.append(("mask2cast:%s->%s" % (expr[:20], ty), cand))
    return out


IF_RE = re.compile(r"^(?P<i>[ \t]*)\}[ \t]*$")


def dup_after_if_candidates(text):
    """The statement after an `if (...) { ... }` written into BOTH arms instead.

    Also harvested from an Astra depin lane.  gcc's cross-jumping merges the duplicates back, but
    the duplication changes which block owns the store - and a value written in both arms is what
    fills a branch delay slot.  Only the simple shape is generated: a closing brace at some indent,
    no `else`, followed by one movable simple statement at the same indent.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i, ln in enumerate(masked):
        m = IF_RE.match(ln.rstrip("\n"))
        if not m or i + 1 >= len(lines):
            continue
        if masked[i + 1].strip().startswith("else"):
            continue
        if not movable(masked[i + 1]) or is_decl(masked[i + 1]):
            continue
        ind = m.group("i")
        if masked[i + 1][:len(ind) + 1] != ind + masked[i + 1].strip()[0]:
            continue                       # the statement must sit at the brace's own indent
        stmt = lines[i + 1].strip()
        new = (f"{ind}    {stmt}\n{ind}}} else {{\n{ind}    {stmt}\n{ind}}}\n")
        out.append(("dup_after_if:%d" % (i + 1),
                    "".join(lines[:i] + [new] + lines[i + 2:])))
    return out


SELF_RE = re.compile(r"^(?P<i>[ \t]*)(?P<x>[A-Za-z_]\w*)\s*=\s*(?P<a>[^;=][^;]*?)\s*;\s*$")
SELF2_RE = re.compile(r"^[ \t]*(?P<x>[A-Za-z_]\w*)\s*=\s*(?P=x)\s*(?P<op>[-+*/|&^]|<<|>>)\s*(?P<b>[^;]+?)\s*;\s*$")
COMMUTE_RE = re.compile(r"(?P<l>\b[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+)*|\b0x[0-9A-Fa-f]+\b|\b\d+\b)\s*(?P<op>[+*|&^])\s*(?P<r>\b[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+)*|\b0x[0-9A-Fa-f]+\b|\b\d+\b)")


def collapse_selfassign_candidates(text):
    """`x = A; x = x op B;` becomes `x = A op B;`.

    Harvested from a code-motion lane, where it turned a six-word reorder residue into an exact
    match.  It removes an intermediate RTL definition point rather than moving one, which is a
    different lever from every other entry in this menu.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i in range(len(lines) - 1):
        a = SELF_RE.match(masked[i].rstrip("\n"))
        b = SELF2_RE.match(masked[i + 1].rstrip("\n"))
        if not a or not b or a.group("x") != b.group("x"):
            continue
        rhs_a = lines[i].split("=", 1)[1].rsplit(";", 1)[0].strip()
        rhs_b = lines[i + 1].split("=", 1)[1].rsplit(";", 1)[0].strip()
        # `x = x op B` -> the ` op B` tail
        tail = rhs_b[len(a.group("x")):].strip()
        if not tail:
            continue
        new = f"{a.group('i')}{a.group('x')} = {rhs_a} {tail};\n"
        out.append(("collapse:%s" % a.group("x"), "".join(lines[:i] + [new] + lines[i + 2:])))
    return out


def commute_candidates(text):
    """Swap the operands of one commutative binary op.

    Also from the code-motion lane: `a + b` where retail compiled `b + a` costs real words, because
    the operand order in the source decides the rs/rt encoding independently of everything else.
    """
    out = []
    masked = mask(text)
    for m in COMMUTE_RE.finditer(masked):
        l, op, r = text[m.start("l"):m.end("l")], m.group("op"), text[m.start("r"):m.end("r")]
        if l == r:
            continue
        cand = text[:m.start()] + f"{r} {op} {l}" + text[m.end():]
        out.append(("commute:%s%s%s" % (l[:12], op, r[:12]), cand))
    return out


def empty_fence_candidates(text):
    """An EMPTY `do { } while (0);` inserted at a statement boundary.

    Distinct from `fence`, which wraps an existing statement: this inserts a barrier of its own,
    emitting nothing but a loop note.  Harvested from a length-drift lane, where placing one as the
    function's first statement kept gcc's frame-save ahead of the first global load and restored a
    load-delay `nop` retail has - taking that row from four words off to one in a single move.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    dep = depths(masked)
    for i, ln in enumerate(lines):
        if not movable(masked[i]) or is_decl(masked[i]):
            continue
        ind = re.match(r"[ \t]*", ln).group(0)
        new = f"{ind}do {{\n{ind}}} while (0);\n"
        out.append(("efence:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i:])))
    return out


FOLD_A = re.compile(r"^(?P<i>[ \t]*)(?P<t>[A-Za-z_]\w*)\s*=\s*(?P<e>[^;=][^;]*?)\s*;\s*$")
FOLD_B = re.compile(r"^[ \t]*(?P<d>[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+|\s*\[[^\]]+\])*)\s*=\s*(?P<t>[A-Za-z_]\w*)\s*;\s*$")


def fold_temp_candidates(text):
    """`tmp = expr; dest = tmp;` becomes `dest = expr;`, deleting the temp's declaration.

    Harvested from a `broad` lane: routing a value through a temp gives gcc an extra definition
    point, and writing the expression straight into its destination lets the allocator target the
    register the destination needs (a call argument, or one side of a commutative operand pair).
    Only fired when the temp is assigned once and read once, on the very next line.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i in range(len(lines) - 1):
        a = FOLD_A.match(masked[i].rstrip("\n"))
        b = FOLD_B.match(masked[i + 1].rstrip("\n"))
        if not a or not b or a.group("t") != b.group("t"):
            continue
        t = a.group("t")
        if len(re.findall(r"\b%s\b" % re.escape(t), mask(text))) != 3:
            continue                       # the declaration, the write and this one read
        rhs = lines[i].split("=", 1)[1].rsplit(";", 1)[0].strip()
        dest = lines[i + 1].split("=", 1)[0].strip()
        new = f"{a.group('i')}{dest} = {rhs};\n"
        cand = "".join(lines[:i] + [new] + lines[i + 2:])
        cand = re.sub(r"^[ \t]*[A-Za-z_][\w \t\*]*?\b%s\s*;[ \t]*\n" % re.escape(t), "", cand, count=1, flags=re.M)
        out.append(("foldtemp:%s" % t, cand))
    return out


def fence_pair_candidates(text):
    """Two CONSECUTIVE statements wrapped together in `do { ... } while (0);`.

    Harvested from a block-order lane: wrapping a `p = base + off; p->f = v;` pair tightly pulls
    the pair out of a neighbouring statement's load-delay slot and into retail's adjacency.  This
    pins a two-instruction *adjacency*, which the single-statement `fence` cannot express - that
    one pins a definition point and leaves the pair free to be split around it.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    dep = depths(masked)
    for i in range(len(lines) - 1):
        if not movable(masked[i]) or not movable(masked[i + 1]):
            continue
        if is_decl(masked[i]) or is_decl(masked[i + 1]) or dep[i] != dep[i + 1]:
            continue
        ind = re.match(r"[ \t]*", lines[i]).group(0)
        new = (f"{ind}do {{\n{ind}    {lines[i].strip()}\n{ind}    {lines[i+1].strip()}\n"
               f"{ind}}} while (0);\n")
        out.append(("fence2:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 2:])))
    return out


GOTO_ARM_RE = re.compile(r"^(?P<i>[ \t]*)if\s*\([^;{}]*\)\s*\{\s*$")


def hoist_from_goto_arm_candidates(text):
    """`if (c) { stmt; goto A; }` becomes `stmt; if (c) goto A;`.

    From a polarity lane.  For an `if (c) goto A; goto B;` pair, gcc's branch SENSE is decided by
    whether the true arm's body is a bare single `goto` or carries an extra statement: with an
    extra statement it lowers to jumpifnot-skip form and a later pass collapses the negated branch
    onto B, and no spelling of the condition - inversion, arm swap, operand order - changes that
    (ten variants, byte-identical).  Hoisting the statement out so both arms are bare gotos is what
    restores the natural sense.  Condition-inversion is NOT the lever for this class.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i, ln in enumerate(masked):
        m = GOTO_ARM_RE.match(ln.rstrip("\n"))
        if not m or i + 3 > len(lines):
            continue
        body, jump, close = masked[i + 1], masked[i + 2], masked[i + 3] if i + 3 < len(masked) else ""
        if not movable(body) or is_decl(body):
            continue
        if not jump.strip().startswith("goto ") or close.strip() != "}":
            continue
        ind = m.group("i")
        cond = lines[i].strip()[:-1].rstrip()          # drop the trailing '{'
        new = (f"{ind}{lines[i + 1].strip()}\n{ind}{cond} {lines[i + 2].strip()}\n")
        out.append(("hoistgoto:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 4:])))
    return out


INPLACE_RE = re.compile(
    r"^(?P<i>[ \t]*)(?:u8|s8|u16|s16|u32|s32|int|unsigned)\s+(?P<n>[A-Za-z_]\w*)\s*=\s*"
    r"(?P<src>[A-Za-z_]\w*)\s*(?P<op>[-+*/|&^]|<<|>>)\s*(?P<k>[^;]+?)\s*;\s*$")


def inplace_update_candidates(text):
    """`s32 index = state << 2;` becomes `state <<= 2;`, with the single use renamed.

    From an addressing lane, which called it the one mechanically generalisable positive result in
    its batch: when a value computed from an existing live variable by one operator is used exactly
    once, declaring a fresh local costs a register-allocation degree of freedom that keeps `reorg`
    from hoisting the computation into a branch's otherwise-empty delay slot.  Written as an
    in-place update of the source, the slot fills.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    whole = mask(text)
    for i, ln in enumerate(masked):
        m = INPLACE_RE.match(ln.rstrip("\n"))
        if not m:
            continue
        name, src = m.group("n"), m.group("src")
        if name == src:
            continue
        if len(re.findall(r"\b%s\b" % re.escape(name), whole)) != 2:
            continue                       # this definition and exactly one use
        if len(re.findall(r"\b%s\b" % re.escape(src), whole)) < 2:
            continue
        real = lines[i]
        k = real.split(m.group("op"), 1)[1].rsplit(";", 1)[0].strip()
        new = f"{m.group('i')}{src} {m.group('op')}= {k};\n"
        rest = "".join(lines[:i] + [new] + lines[i + 1:])
        rest = re.sub(r"\b%s\b" % re.escape(name), src, rest)
        # drop the now-unused declaration of the old local, if it had a separate one
        rest = re.sub(r"^[ \t]*(?:u8|s8|u16|s16|u32|s32|int|unsigned)[ \t]+%s[ \t]*;[ \t]*\n"
                      % re.escape(name), "", rest, count=1, flags=re.M)
        out.append(("inplace:%s->%s" % (name, src), rest))
    return out


def deadstore_candidates(text):
    """A trailing dead store after a local's LAST use: `x = 0;` before the return.

    From a broad lane, which closed a row with it.  A dead write *after* the last real use (not a
    dead init before the first) stops the register allocator recycling that local's hardware
    register as scratch for an unrelated computation sitting in between, which is what forced the
    row's third range check onto the same register as its first two - and that in turn unlocked the
    matching delay-slot fill.  Distinct from every other entry here: it adds a statement rather
    than moving, folding or retyping one.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    whole = mask(text)
    for idx, ind, ty, name in decls(text):
        uses = [i for i, m in enumerate(masked)
                if i != idx and re.search(r"\b%s\b" % re.escape(name), m)]
        if len(uses) < 2:
            continue
        last = uses[-1]
        # place the dead store after the last use, at the first statement boundary at that depth
        dep = depths(masked)
        for j in range(last + 1, min(last + 6, len(lines))):
            if dep[j] != dep[last] or not movable(masked[j]):
                continue
            new = f"{ind}{name} = 0;\n"
            out.append(("deadstore:%s@%d" % (name, j + 1),
                        "".join(lines[:j] + [new] + lines[j:])))
            break
    return out


DEC_RE = re.compile(r"^(?P<i>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*(?P<op>[-+])=\s*1\s*;\s*$")
WHILE_RE = re.compile(r"^[ \t]*\}\s*while\s*\((?P<c>.+)\)\s*;\s*$")
IFGOTO_RE = re.compile(r"^[ \t]*if\s*\((?P<c>.+)\)\s*goto\s+(?P<l>\w+)\s*;\s*$")


def loop_counter_merge_candidates(text):
    """A loop's trailing `x -= 1;` merged into its own condition: `} while (--x >= 0);`.

    From a reorder-only lane.  When the operand the scheduler swapped out is the loop's own
    trailing increment or decrement, merging it into the back-edge test changes the RTL shape
    enough to fix or improve the ordering - where ordinary statement reordering is completely
    inert.  It closed one site on each of two twin rows (damage 4 -> 2 apiece) and improved a
    third.  Distinct from every other generator here: it changes the loop's own control
    expression rather than a statement's position or a value's type.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i in range(len(lines) - 1):
        d = DEC_RE.match(masked[i].rstrip("\n"))
        if not d:
            continue
        v, op = d.group("v"), d.group("op")
        nxt = masked[i + 1].rstrip("\n")
        pre = "--" if op == "-" else "++"
        w = WHILE_RE.match(nxt)
        g = IFGOTO_RE.match(nxt)
        if w:
            cond = lines[i + 1].split("while", 1)[1].strip().rstrip(";").strip()[1:-1].strip()
        elif g:
            cond = lines[i + 1].split("if", 1)[1].split("goto", 1)[0].strip().strip("()").strip()
        else:
            continue
        if not re.search(r"\b%s\b" % re.escape(v), cond):
            continue
        newcond = re.sub(r"\b%s\b" % re.escape(v), pre + v, cond, count=1)
        tail = (lines[i + 1].replace(cond, newcond, 1))
        out.append(("loopmerge:%s" % v, "".join(lines[:i] + [tail] + lines[i + 2:])))
    return out


LOAD_DECL_RE = re.compile(r"^[ \t]*(?P<v>[A-Za-z_]\w*)\s*=\s*(?P<rhs>[^;]*(?:->|\[|\*)[^;]*)\s*;\s*$")
ASSIGN_RE = re.compile(r"^(?P<i>[ \t]*)(?P<x>[A-Za-z_]\w*)\s*=\s*(?P<e>[^;=][^;]*?)\s*;\s*$")


def depinject_candidates(text, max_cands=24):
    """A real RAW dependency, injected then folded away: `t = e + a; t -= a;`.

    From a reorder-only lane, which closed a row with it.  Splitting the round trip across two
    statements creates a dependency the scheduler must respect, and combine folds the add/sub away
    for free - so it forces an ordering at zero bytes.  **The anchor must be something gcc cannot
    constant-propagate**: the lane measured that a literal, `$zero`, or anything cse traces to a
    literal has its dependency removed before the scheduler ever runs, and the edit then moves
    nothing at all.  So anchors here are only locals assigned from a memory load (`->`, `[]`, `*`).
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    scal = {n for _, _, _, n in decls(text)}
    anchors = []
    for i, m in enumerate(masked):
        a = LOAD_DECL_RE.match(m.rstrip("\n"))
        if a and a.group("v") in scal:
            anchors.append((i, a.group("v")))
    if not anchors:
        return out
    for j, ln in enumerate(masked):
        t = ASSIGN_RE.match(ln.rstrip("\n"))
        if not t or not movable(ln) or is_decl(ln):
            continue
        x = t.group("x")
        if x not in scal:
            continue
        # A reorder-only lane measured the precondition for FAILURE: when the pinned value is a
        # bare register copy or a small immediate destined for an argument register, combine folds
        # the injected round-trip back to the original `move`/`li` BEFORE the post-reload scheduler
        # runs, so the injection cannot change the order and only costs a stack slot (+8 bytes of
        # frame, observed three times).  Nothing survives for the UID tie-break to see.
        rhs = t.group("e").strip()
        if re.fullmatch(r"[A-Za-z_]\w*", rhs) or re.fullmatch(r"0x[0-9A-Fa-f]{1,3}|\d{1,4}", rhs):
            continue
        for ai, av in anchors:
            if ai >= j or av == x:
                continue
            real = lines[j]
            expr = real.split("=", 1)[1].rsplit(";", 1)[0].strip()
            ind = t.group("i")
            new = f"{ind}{x} = ({expr}) + {av};\n{ind}{x} -= {av};\n"
            out.append(("depinject:%s^%s" % (x, av),
                        "".join(lines[:j] + [new] + lines[j + 1:])))
            if len(out) >= max_cands:
                return out
    return out


LOADLOCAL_RE = re.compile(r"^(?P<i>[ \t]*)(?P<n>[A-Za-z_]\w*)\s*=\s*(?P<e>[^;=]*(?:->|\[|\*)[^;=]*)\s*;\s*$")


def fold_load_candidates(text):
    """A local assigned once from a memory load, inlined into every consumer.

    From a `broad` lane, 2 for 2, WITH a precondition that says when to reach for it: compare the
    residue's register sets.  When retail's set is a strict SUPERSET of ours - retail keeps one
    more value live - folding the load directly into each consuming expression, instead of storing
    it to a named intermediate, recovers the missing register.  When the two sets are EQUAL it is a
    hard-register tie and no C reshaping moved a single word in five attempts, so do not spend
    probes.  `pin_facts` now prints that verdict per row.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    whole = mask(text)
    scal = {n for _, _, _, n in decls(text)}
    for i, ln in enumerate(masked):
        m = LOADLOCAL_RE.match(ln.rstrip("\n"))
        if not m or m.group("n") not in scal:
            continue
        name = m.group("n")
        uses = len(re.findall(r"\b%s\b" % re.escape(name), whole))
        if uses < 3:                      # declaration + this assignment + at least one use
            continue
        expr = lines[i].split("=", 1)[1].rsplit(";", 1)[0].strip()
        rest = "".join(lines[:i] + lines[i + 1:])
        rest = re.sub(r"\b%s\b" % re.escape(name), "(" + expr + ")", rest)
        rest = re.sub(r"^[ \t]*(?:u8|s8|u16|s16|u32|s32|int|unsigned|void)[\w \t\*]*?\b%s\b[ \t]*;[ \t]*\n"
                      % re.escape(name), "", rest, count=1, flags=re.M)
        out.append(("foldload:%s" % name, rest))
    return out


STORE_RE = re.compile(r"^[ \t]*[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+|\s*\[[^\]]*\])+\s*=\s*[^;=][^;]*;\s*$")
DIRECT_CALL_RE = re.compile(r"^[ \t]*(?:[A-Za-z_]\w*\s*=\s*)?(?P<f>[A-Za-z_]\w*)\s*\([^;]*\)\s*;\s*$")


PTRTY = r"(?:u8|s8|void|char|M2C_UNK)"
LITDECL_RE = re.compile(r"^(?P<i>[ \t]+)%s[ \t]*\*[ \t]*(?P<n>[A-Za-z_]\w*)[ \t]*=[ \t]*"
                        r"\(%s[ \t]*\*\)[ \t]*0x(?P<a>8[0-9A-Fa-f]{7})[ \t]*;[ \t]*$"
                        % (PTRTY, PTRTY), re.M)
LITASSIGN_RE = re.compile(r"^(?P<i>[ \t]+)(?P<n>[A-Za-z_]\w*)[ \t]*=[ \t]*"
                          r"\(%s[ \t]*\*\)[ \t]*0x(?P<a>8[0-9A-Fa-f]{7})[ \t]*;[ \t]*$" % PTRTY, re.M)


def _add_extern(text, decl):
    """Put an extern next to the others, or after the includes if there are none."""
    if decl.strip() in text:
        return text
    lines = text.splitlines(True)
    last = max((i for i, l in enumerate(lines) if l.startswith("extern ")), default=None)
    if last is None:
        last = max((i for i, l in enumerate(lines) if l.startswith("#include")), default=-1)
    lines.insert(last + 1, decl)
    return "".join(lines)


def litsym_candidates(text):
    """A local holding a literal page address, where retail references a SYMBOL.

    `li-expansion` in the brief: `lui;ori` yours against `lui;addiu` retail's means the C
    materialises an integer where retail names a symbol, and the extra live value is what the pin
    was holding down.  Two rows fell to exactly this on 2026-09-10 (town/func_8059E540,
    dungeon/func_800AF9C8, landed d876ca54), one needing the array-decay spelling with the extern
    already present and one needing `&D_X` with the extern added - so both spellings are emitted
    and the budget decides.
    """
    out = []
    for rx in (LITDECL_RE, LITASSIGN_RE):
        for m in rx.finditer(text):
            name, addr = m.group("n"), m.group("a").upper()
            sym = "D_8" + addr[1:]
            uses = len(re.findall(r"\b%s\b" % re.escape(name), text))
            if uses < 2:                      # the assignment itself plus at least one read
                continue
            for repl, decl in ((sym, "extern u8 %s[];\n" % sym), ("&" + sym, "extern u8 %s;\n" % sym)):
                t = text[:m.start()] + text[m.end() + 1:]          # drop the assignment line
                # a separate `u8 *name;` declaration is now dead
                t = re.sub(r"^[ \t]*%s[ \t]*\*[ \t]*%s[ \t]*;[ \t]*\n" % (PTRTY, re.escape(name)),
                           "", t, flags=re.M)
                t = re.sub(r"\b%s\b" % re.escape(name), repl.replace("\\", "\\\\"), t)
                t = _add_extern(t, decl)
                if t != text:
                    out.append(("litsym:%s->%s" % (name, repl), t))
    return out


CALLSTMT_RE = re.compile(r"^(?P<i>[ \t]+)(?P<f>func_[0-9A-Fa-f]{8}|[A-Za-z_]\w*)\((?P<a>.*)\);[ \t]*$")


def _args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "," and depth == 0:
            out.append(cur); cur = ""; continue
        if ch in "([": depth += 1
        elif ch in ")]": depth -= 1
        cur += ch
    out.append(cur)
    return out


def livetie_candidates(text, max_cands=24):
    """Tie a value that is DEAD ACROSS A CALL into one of the call's arguments, at zero bytes.

    The `ASM_USE` class, mechanised.  Retail keeps a copy of a value the unpinned build drops,
    because after the call the value is never read - it is overwritten - so gcc has no reason to
    keep it live and the copy disappears.  `arg + v - v` makes the argument expression depend on
    `v`, which keeps it live, while combine cancels the round trip so no instruction is emitted.

    Harvested from town/func_800A56D0 (landed d876ca54), where `ASM_USE(depth_or_page)` sat
    immediately before `func_8006658C(ptr, packet)` and the answer was
    `func_8006658C(ptr, packet + depth_or_page - depth_or_page)`.

    The precondition is the one the win had and is checked here: the next mention of `v` after
    the call is a WRITE (or there is none), so the value really is dead across it.  Tying a value
    that is read later changes nothing, because it was already live.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    scal = {n for _, _, _, n in decls(text)}
    if not scal:
        return out
    for j, ln in enumerate(masked):
        m = CALLSTMT_RE.match(ln.rstrip("\n"))
        if not m or not m.group("a").strip():
            continue
        args = _args(m.group("a"))
        for v in sorted(scal):
            # v must be assigned somewhere before the call
            if not any(re.match(r"^[ \t]*%s[ \t]*=" % re.escape(v), masked[k]) for k in range(j)):
                continue
            # and dead across it: the next mention after the call is a write
            nxt = None
            for k in range(j + 1, len(masked)):
                if re.search(r"\b%s\b" % re.escape(v), masked[k]):
                    nxt = masked[k]; break
            if nxt is not None and not re.match(r"^[ \t]*%s[ \t]*(=[^=]|\+\+|--)" % re.escape(v), nxt):
                continue
            if re.search(r"\b%s\b" % re.escape(v), m.group("a")):
                continue                      # already in the argument list: nothing to tie
            for ai, a in enumerate(args):
                if not a.strip():
                    continue
                new_args = list(args)
                new_args[ai] = "%s + %s - %s" % (a.strip(), v, v)
                new = "%s%s(%s);\n" % (m.group("i"), m.group("f"), ", ".join(x.strip() for x in new_args))
                out.append(("livetie:%s^%s#%d" % (v, m.group("f"), ai),
                            "".join(lines[:j] + [new] + lines[j + 1:])))
                if len(out) >= max_cands:
                    return out
    return out


DOWHILE_END_RE = re.compile(r"^(?P<i>[ \t]+)(?P<v>[A-Za-z_]\w*)[ \t]*(?:\+\+|\+=[ \t]*1)[ \t]*;[ \t]*$")
DOWHILE_LABEL_RE = re.compile(r"^[ \t]*(?P<l>[A-Za-z_]\w*)[ \t]*:[ \t]*$")
DOWHILE_DECL_RE = r"^(?P<d>[ \t]*(?:register[ \t]+)?(?:u8|s8|u16|s16|u32|s32|int|unsigned)[ \t]+)%s[ \t]*=[ \t]*(?P<s>[^;=,]+);[ \t]*$"
DOWHILE_TEST_RE = re.compile(r"^[ \t]*\}[ \t]*while[ \t]*\([ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*"
                             r"(?P<op><=?)[ \t]*(?P<k>[^)]+?)[ \t]*\)[ \t]*;[ \t]*$")


def dowhile2for_candidates(text):
    """m2c's counted `do/while` written back as the `for` it came from.

    APPEARS when m2c lowers a counted loop: `v = 0;` then `do { ... v++; } while (v < K);`.
    That spelling puts the increment at the bottom of the body as an ordinary statement.

    RESOLVES because a `for` header makes the increment the loop's own update expression, which
    gcc's `reorg` may then steal into a branch delay slot - which is exactly the word the pinned
    build was missing.  Both source rows were `length-drift` and one carried the
    `ASM_SCHED_BARRIER` the shape removes outright.

    POPULATION at the time it was written: 41 pinned rows match the appearance condition, 9 of
    them in band, 7 of those not already closed by the lane - so it is a class, not a one-off.
    That count is the bar a harvested shape has to clear before it is worth a generator: `litsym`
    and `livetie` were each built from a single win and closed nothing.

    Two independent wins, dungeon/func_80A4B134 and dungeon/func_80B9A94C (2026-09-11).

    Two m2c spellings it used to miss (t20, dungeon/func_8009A924, closed by `ptr2index` and then
    this): the counter started in its declaration (`s32 direction = 0;` - the declaration keeps
    the variable, the header takes the start), and a label sitting right before the increment
    (`next: direction++;`) - the label is where m2c's `goto next` continued the loop, so in the
    `for` those gotos are `continue`, and the label goes.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for j, ln in enumerate(masked):
        mt = DOWHILE_TEST_RE.match(ln.rstrip("\n"))
        if not mt:
            continue
        v, k, op = mt.group("v"), mt.group("k").strip(), mt.group("op")
        mi = DOWHILE_END_RE.match(masked[j - 1].rstrip("\n")) if j else None
        if not mi or mi.group("v") != v:
            continue
        # walk back to the matching `do {`
        depth, top = 0, None
        for x in range(j, -1, -1):
            depth += masked[x].count("}") - masked[x].count("{")
            if depth == 0 and re.match(r"^[ \t]*do[ \t]*\{[ \t]*$", masked[x].rstrip("\n")):
                top = x
                break
        if top is None:
            continue
        init = None                      # nearest preceding `v = <start>;` (or `s32 v = <start>;`)
        for x in range(top - 1, -1, -1):
            m0 = re.match(r"^[ \t]*%s[ \t]*=[ \t]*(?P<s>[^;=]+);[ \t]*$" % re.escape(v),
                          masked[x].rstrip("\n"))
            if m0:
                init = (x, m0.group("s").strip(), None)
                break
            m1 = re.match(DOWHILE_DECL_RE % re.escape(v), masked[x].rstrip("\n"))
            if m1:
                init = (x, m1.group("s").strip(), lines[x][:m1.end("d")] + v + ";\n")
                break
            if re.search(r"\b%s\b" % re.escape(v), masked[x]):
                break                    # touched by something else first: not a plain counter
        if init is None:
            continue
        ix, start, keep_decl = init
        ind = re.match(r"^([ \t]*)", lines[top]).group(1)
        head = "%sfor (%s = %s; %s %s %s; %s++) {\n" % (ind, v, start, v, op, k, v)
        body = lines[top + 1:j - 1]                      # drop the trailing `v++;`
        lab = DOWHILE_LABEL_RE.match(masked[j - 2].rstrip("\n")) if j >= 2 and j - 2 > top else None
        if lab:
            name = lab.group("l")
            refs = [x for x, m in enumerate(masked) if re.search(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(name), m)]
            nested = any(re.match(r"^[ \t]*(?:do\b|while\b|for\b|switch\b)", masked[x]) for x in range(top + 1, j - 2))
            if refs and all(top < x < j - 2 for x in refs) and not nested:
                body = [re.sub(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(name), "continue;", b)
                        for b in lines[top + 1:j - 2]]
            else:
                body = body + ["%s    ;\n" % ind]            # a label needs a statement after it
        pre = lines[:ix] + ([keep_decl] if keep_decl else []) + lines[ix + 1:top]
        new = pre + [head] + body + ["%s}\n" % ind] + lines[j + 1:]
        out.append(("dowhile2for:%s<%s" % (v, k), "".join(new)))
    return out


def fence_store_before_call_candidates(text):
    """Fence a memory store that sits immediately before a DIRECT call.

    From a code-motion lane, with the precondition that makes it usable: wrapping the store in
    `do { ... } while (0);` re-pins it ahead of the call's argument-setup moves, which took one row
    from 7 words to 3.  It works when the call is a direct `jal` to a named symbol, and **backfires
    on an indirect call through a loaded function pointer** (4 -> 7 on the row that tried it),
    because the barrier then also pins the pointer load, and retail schedules that load after the
    argument moves while the unbarriered build puts it before.  So a call whose callee is a
    dereferenced pointer or a struct member is skipped here.
    """
    out = []
    lines = text.splitlines(True)
    masked = mask(text).splitlines(True)
    for i in range(len(lines) - 1):
        if not STORE_RE.match(masked[i].rstrip("\n")):
            continue
        nxt = masked[i + 1].rstrip("\n")
        m = DIRECT_CALL_RE.match(nxt)
        if not m:
            continue
        if "->" in nxt.split("(")[0] or "." in nxt.split("(")[0] or "*" in nxt.split("(")[0]:
            continue                       # an indirect call: measured to regress
        ind = re.match(r"[ \t]*", lines[i]).group(0)
        new = f"{ind}do {{\n{ind}    {lines[i].strip()}\n{ind}}} while (0);\n"
        out.append(("fencestore:%d" % (i + 1), "".join(lines[:i] + [new] + lines[i + 1:])))
    return out


class T:
    name = "t15_shapes"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no live pin site"
        # A NON_MATCHING arm is no longer a refusal: `sites_of` ignores pins in code no byte gate
        # compiles, and `sweep.py` refuses any candidate that edits that code (`unscored_text`).
        why = asm_blocker(text)
        if why:
            return why
        rec = strip_census().get(row["id"])
        if rec is None:
            return "no strip probe for this row"
        if rec.get("in_sha") != sha_text(text):
            return "strip probe is stale for this text"
        t = rec.get("total")
        if t is None or t > BAND:
            return f"strip damage {t} above band {BAND}"
        return None

    @staticmethod
    def _menu(cur, slus=False):
        """Real source first, barriers last.  The fence study's natural shapes (`natural.py`) lead:
        a third of the fences the first passes landed stood for one of them, and census.py counts
        a fence like a pin, so a shape that frees a pin without one must be tried before any fence
        (`basesym` never on a SLUS row - that scorer compares object identity)."""
        real = (natural.candidates(cur, basesym=not slus, host=False) + loop_counter_merge_candidates(cur)
                + dup_after_if_candidates(cur) + dowhile2for_candidates(cur) + narrow_candidates(cur)
                + natural.host_candidates(cur))    # many per row: after the proven shapes, never ahead of them
        if WIDE:
            real += (fold_load_candidates(cur) + depinject_candidates(cur) + deadstore_candidates(cur)
                     + inplace_update_candidates(cur) + hoist_from_goto_arm_candidates(cur)
                     + fold_temp_candidates(cur) + collapse_selfassign_candidates(cur)
                     + maskfold_candidates(cur) + mask2cast_candidates(cur)
                     + litsym_candidates(cur) + livetie_candidates(cur) + commute_candidates(cur))
        if NOFENCE:
            return real
        fences = (fence_store_before_call_candidates(cur) + fence_candidates(cur) + fence_pair_candidates(cur)
                  + (empty_fence_candidates(cur) if WIDE else []))
        return real + fences

    @staticmethod
    def _strip_keeping(text, keep):
        """Erase every pin site except the one at index `keep` (None = erase all)."""
        cur = text
        n = len(sites_of(text))
        for i in sorted(range(n), reverse=True):
            if i == keep:
                continue
            cur = erase(cur, sites_of(cur)[i])
        out = []
        for ln in cur.splitlines(True):
            nl = "\n" if ln.endswith("\n") else ""
            body = NOTE_RE.sub("", ln[:len(ln) - len(nl)])
            if not body.strip() and ("MATCH pin:" in ln or "UNRESOLVED C shape (pin)" in ln):
                continue
            out.append(body.rstrip() + nl if body != ln[:len(ln) - len(nl)] else ln)
        return "".join(out)

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        """Greedy hill-climb over the shape menu.

        The single-shot sweep left 39 rows whose residue a *single* candidate improved without
        closing - the mechanism was right and the row needed more than one edit.  So each round
        keeps the best improving candidate and searches again from there, up to ROUNDS rounds or
        the budget.  A round that improves nothing stops the climb: the menu has nothing left to
        say about that row, and its `best_label` names what came closest for the lane that follows.
        """
        base = strip_pins(text)
        pins_in = len(sites_of(text))
        tried = 0
        v = verify_fn(base)
        tried += 1
        if v.get("exact"):
            return base, {"step": "strip", "tried": tried, "pins_in": pins_in, "pins_out": 0}
        strip_total = v.get("total")
        cur, cur_total, steps = base, strip_total, []
        best_label = "strip"
        seen = {sha_text(base)}
        for rnd in range(ROUNDS):
            # Measured menu.  EIGHT of the ten generators were harvested from a lane that closed a
            # row by hand with that exact shape, and seven of those eight then scored ZERO as
            # single-shot sweeps.  The pattern is consistent enough to plan around: a lane closes a
            # row with a *combination* of edits and reports the one it thinks did the work, but the
            # shape rarely carries on its own.  Only the fence and narrow families transfer.  Corpus-wide wins after 1,019 row-attempts: fence 63, narrow 11,
            # fence-return 3, dup_after_if 2 - and ZERO for foldtemp, collapse, maskfold, mask2cast,
            # commute and efence, each of which was harvested from a lane win on some other row.
            # `commute` alone quadrupled the sweep's wall time for nothing, so the default menu is
            # the four that have paid; T15_WIDE=1 runs the whole set when a new class is opened.
            cands = T._menu(cur, row.get("kind") == "slus")
            round_best = None
            for label, cand in cands:
                if tried >= BUDGET:
                    break
                h = sha_text(cand)
                if h in seen:
                    continue
                seen.add(h)
                v = verify_fn(cand)
                tried += 1
                if v.get("exact"):
                    steps.append(label)
                    return cand, {"step": "+".join(steps), "tried": tried, "rounds": rnd + 1,
                                  "pins_in": pins_in, "pins_out": 0,
                                  "fence": any(x.startswith("fence") for x in steps)}
                t = v.get("total")
                if t is not None and t < (cur_total if cur_total is not None else 1e9):
                    if round_best is None or t < round_best[0]:
                        round_best = (t, label, cand)
            if round_best is None or tried >= BUDGET:
                break
            cur_total, best_label, cur = round_best[0], round_best[1], round_best[2]
            steps.append(round_best[1])
        # PARTIAL REMOVAL.  Landing 10 pins -> 9 is a real result: the row is measurably less
        # scaffolded and the next pass has one fewer site to explain.  Until now this plugin only
        # ever accepted a FULLY pin-free candidate, so every partial success was computed and then
        # thrown away.  If the full strip could not be made exact, try leaving each single pin in
        # place and run the whole menu against that base; the first exact result removes pins_in-1
        # sites, and the row comes back to the next sweep smaller.
        if PARTIAL and pins_in > 1:
            for keep in range(pins_in):
                if tried >= BUDGET:
                    break
                pbase = T._strip_keeping(text, keep)
                v = verify_fn(pbase)
                tried += 1
                if v.get("exact"):
                    return pbase, {"step": "partial-strip", "tried": tried, "pins_in": pins_in,
                                   "pins_out": 1, "kept": keep}
                for label, cand in T._menu(pbase, row.get("kind") == "slus"):
                    if tried >= BUDGET:
                        break
                    h = sha_text(cand)
                    if h in seen:
                        continue
                    seen.add(h)
                    v = verify_fn(cand)
                    tried += 1
                    if v.get("exact"):
                        return cand, {"step": "partial+" + label, "tried": tried,
                                      "pins_in": pins_in, "pins_out": 1, "kept": keep}
        return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in,
                      "best_total": cur_total, "best_label": best_label, "strip_total": strip_total,
                      "climb": "+".join(steps) or None,
                      "moved": (strip_total - cur_total) if (cur_total is not None and strip_total is not None) else None,
                      "stopped": "budget" if tried >= BUDGET else "no-improvement"}
