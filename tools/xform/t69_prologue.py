"""T69: the redundant parameter copies of a function dropped TOGETHER, and the keeps on them with them.

APPEARS     an m2c entry shape - a parameter named `x_arg`/`x_in`/`x_data` copied once into a local `x`
            that is never written again - with `ASM_KEEP(x)` a few lines below:

                void func(void *action_in, void *motion_in, void *tile_in, void *actor_in)
                {
                    void *action; void *motion; void *tile; void *actor;
                    action = action_in; motion = motion_in; tile = tile_in; actor = actor_in;
                    ASM_KEEP(action); ASM_KEEP(motion); ASM_KEEP(tile); ASM_KEEP(actor);

MECHANISM   `ASM_KEEP(x)` is `__asm__ __volatile__("" : "=r"(x) : "0"(x))`: a SECOND set of `x`.
            gcc 2.x's first scheduler raises a producer to LAUNCH_PRIORITY (0x7f000001) through
            `adjust_priority` -> `birthing_insn_p` (sched.c), which fires only for a live destination
            with `reg_n_sets[dest] == 1`.  The keep's extra set defeats that test, so the copy keeps
            its LUID position; erase the keep and the copy is promoted, the backward scheduler picks
            it first and therefore emits it LAST in the block, and after reload the callee-saved
            store paired with it travels down too.  That is the whole round-31 "prologue" residue:
            measured on the class's 89 sites, erasing the pin promotes exactly the kept variable's
            producer on 46 of them (6 more lose a promotion the pin caused, 37 are a different
            mechanism - `rows/promo_scan.jsonl` in work/native_lane/r31_prologue).
RESOLVES    the copies are redundant: the parameter can carry the local's name (and, for a pointer,
            its declared type) and the local disappears.  A parameter's own entry copy is not
            promoted, so the whole prologue keeps retail's order - but only when EVERY copy of the
            function goes at once.  Dropping ONE of four left the listing 132 lines from retail on
            `dungeon/func_809F4F90`, where dropping all four reaches 0; that is why `natural.dropcopy`
            (one copy at a time) and t36's note "dropping the copies left the residue unchanged"
            missed the class.
Candidates: the whole set first, then every subset, most pins removed first.  Only `vf` accepts.
"""
import collections
import itertools
import os
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of, unscored_text, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .screen import compile_s, sdiff
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from screen import compile_s, sdiff

ID = r"[A-Za-z_]\w*"
MAX_CANDS = int(os.getenv("T69_MAX_CANDS", "48"))
VERIFY_BUDGET = int(os.getenv("T69_VERIFY", "6"))
# Only these pin spellings name exactly one variable and mean "keep this value here".
ERASABLE = ("ASM_KEEP", "ASM_KEEP_NV", "ASM_SET")
DECL = re.compile(r"^(?P<ind>[ \t]+)(?P<reg>register[ \t]+)?"
                  r"(?P<type>(?:(?:unsigned|signed|struct|union|enum|const|volatile)[ \t]+)*" + ID +
                  r"[ \t]+(?:\*[ \t]*)*)(?P<var>" + ID + r")[ \t]*(?P<asm>ASM_REG\([^\n;]*\))?"
                  r"[ \t]*(?:=[ \t]*(?P<init>" + ID + r")[ \t]*)?;[^\n]*\n", re.M)
NOTYPE = {"return", "goto", "extern", "typedef", "if", "else", "while", "for", "switch", "case",
          "do", "break", "continue", "sizeof"}
QUAL = re.compile(r"\b(const|volatile)\b")


def _note(skips, key):
    if skips is not None:
        skips[key] += 1
        detail = getattr(skips, "detail", None)
        if detail is not None:          # a Detail counter: the refusal with the local it was about
            detail.append((key, getattr(skips, "cur", None)))


class Detail(collections.Counter):
    """A skips counter that also records (refusal, local) pairs, for a refusal table with the pins
    behind each refusal (the local a record was about is what its keeps name)."""

    def __init__(self, *a, **k):
        super().__init__(*a, **k)
        self.detail = []
        self.cur = None


def _mask(t):
    """Offset-preserving mask of every comment AND literal: `/* */`, `//`, "..." and '...'.

    `t29.mask_comments` masks `/* */` only, so a rename could land inside a `//` comment or a string
    literal (round-31 review, rev_synth cases 4 and 8).  Quotes and the comment delimiters stay so the
    surrounding text still parses; everything between them becomes blanks, newlines kept.
    """
    out, i, n = list(t), 0, len(t)
    while i < n:
        c = t[i]
        if c == "/" and t[i + 1:i + 2] == "*":
            j = t.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i + 2, max(i + 2, j - 2)):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c == "/" and t[i + 1:i + 2] == "/":
            j = t.find("\n", i)
            j = n if j < 0 else j
            for k in range(i + 2, j):
                out[k] = " "
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and t[j] != c and t[j] != "\n":
                j += 2 if t[j] == "\\" else 1
            for k in range(i + 1, min(j, n)):
                if out[k] != "\n":
                    out[k] = " "
            i = min(j + 1, n) if j < n and t[j] == c else j
        else:
            i += 1
    return "".join(out)


def _directive_mask(masked):
    """1 at every character of a preprocessor DIRECTIVE line (`\\`-continuations included).

    `_pp_depth` only knows conditional nesting: it puts the `#if` line itself at the OUTER depth and
    cannot see `#define`/`#undef`/`#include` at all.  Nothing may be rewritten on any of these lines
    (round-31 review, src/dungeon/func_810332A4.c `#define effect held_effect`).
    """
    flag, cont = bytearray(len(masked) + 1), False
    for m in re.finditer(r"[^\n]*\n|[^\n]+$", masked):
        line = m.group(0)
        d = cont or line.lstrip().startswith("#")
        if d:
            for k in range(m.start(), m.end()):
                flag[k] = 1
        cont = d and line.rstrip("\n").endswith("\\")
    return flag


def _directive_names(masked):
    """Every identifier that appears on a directive line, minus the directive keyword itself."""
    out = set()
    for m in re.finditer(r"^[ \t]*#[ \t]*(\w*)([^\n]*(?:\\\n[^\n]*)*)", masked, re.M):
        out |= set(re.findall(ID, m.group(2)))
    return out


def _pasting_macros(masked):
    """Function-like macros whose body stringizes or pastes: `MAC(x)` turns the NAME into text."""
    out = set()
    for m in re.finditer(r"^[ \t]*#[ \t]*define[ \t]+(%s)\(([^\n]*(?:\\\n[^\n]*)*)" % ID, masked, re.M):
        if "#" in m.group(2):
            out.add(m.group(1))
    return out


def _occurrences(masked, name, lo, hi):
    """Spans of `name` used as an identifier in [lo, hi) - never a `.`/`->` member of that name."""
    for m in re.compile(r"(?<![\w.])%s\b" % re.escape(name)).finditer(masked, lo, hi):
        back = masked[max(lo, m.start() - 8):m.start()].rstrip()
        if back.endswith("->") or back.endswith("."):
            continue
        yield m.start(), m.end()


PREV_VALUE = {"(", ",", "=", "?", ":", "!", "&&", "||", "==", "!=", "<", ">", "<=", ">=", "return"}
NEXT_VALUE = {",", ")", ";", "?", ":", "&&", "||", "==", "!=", "<", ">", "<=", ">="}
_PREV = re.compile(r"(->|\+\+|--|&&|\|\||<<|>>|[<>=!]=|return\b|[^\s])\s*$")
_NEXT = re.compile(r"\s*(->|\+\+|--|&&|\|\||<<|>>|[<>=!]=|[^\s])")
UPPER = re.compile(r"[A-Z_][A-Z0-9_]*\Z")


def _value_use(masked, a, b, lo, hi):
    """True when the occurrence [a, b) is a bare VALUE - its type cannot change what is computed.

    A pointer's value is the same at any pointer type, so an argument, an assignment source, a
    comparison or a return is safe; `[`, `->`, `.`, `+`, `-`, `*` and `sizeof` are not.
    """
    prv = _PREV.search(masked[max(lo, a - 80):a])
    nxt = _NEXT.match(masked[b:hi])
    return bool(prv) and bool(nxt) and prv.group(1) in PREV_VALUE and nxt.group(1) in NEXT_VALUE


def _enclosing_callee(masked, pos, lo):
    """The identifier of the call whose argument list holds `pos` (None if `pos` is not in one)."""
    d, i = 0, pos - 1
    while i >= lo:
        c = masked[i]
        if c == ")":
            d += 1
        elif c == "(":
            if d == 0:
                m = re.search(r"(\w+)\s*\Z", masked[lo:i])
                return m.group(1) if m else None
            d -= 1
        elif c in ";{}":
            return None
        i -= 1
    return None


def _depths(masked):
    """Brace depth at the start of each character position (cheap prefix scan)."""
    out, d = [], 0
    for ch in masked:
        out.append(d)
        if ch == "{":
            d += 1
        elif ch == "}":
            d -= 1
    out.append(d)
    return out


def _pp_depth(masked):
    """`#if` nesting depth at every character position: the map t66 keeps for itself.

    `arm_labels`/`unscored_text` only label NON_MATCHING conditions, so nothing else backstops an
    edit inside an `#ifdef __mips__` or `#if 0` arm.  The directive line of an `#if` counts as
    outside it; `#else`/`#elif` stay inside; `#endif` counts as outside.
    """
    out, d = [], 0
    for line in masked.splitlines(True):
        s = line.lstrip()
        w = (s[1:].lstrip().split(None, 1) or [""])[0] if s.startswith("#") else ""
        if w in ("if", "ifdef", "ifndef"):
            out += [d] * len(line)
            d += 1
            continue
        if w == "endif":
            d = max(0, d - 1)
        out += [d] * len(line)
    out.append(d)
    return out


def _block_span(masked, dep, pos):
    """(open brace, close brace) of the innermost block containing `pos`."""
    d = dep[pos]
    a = pos
    while a > 0 and dep[a] >= d:
        a -= 1
    b = pos
    while b < len(masked) and dep[b] >= d:
        b += 1
    return a, b


def _writes(masked, v):
    return (len(re.findall(r"(?<![\w.>])%s\s*(?:=(?!=)|\+\+|--|[-+*/%%&|^]=|<<=|>>=)" % re.escape(v), masked))
            + len(re.findall(r"(?:\+\+|--)\s*(?<![\w.>])%s\b" % re.escape(v), masked)))


def _surviving_uses(masked, b0, b1, p, dspan, cspan):
    """Every occurrence of the parameter that the merge KEEPS (the decl and the copy go)."""
    out = []
    for a, b in _occurrences(masked, p, b0, b1):
        if dspan[0] <= a < dspan[1] or (cspan and cspan[0] <= a < cspan[1]):
            continue
        out.append((a, b))
    return out


def _retype_safe(masked, b0, b1, p, pty, lty, surv, macros, skips):
    """A retype re-interprets every SURVIVING use of the parameter at the new type: check each one.

    Round-31 review, defect 2: `_compatible` compared type strings only, so `void *a_in` used as
    `a_in + 4` or `a_in[3]` silently changed an offset, and the scalar opening changed a width or a
    signedness under a surviving use.  A scalar retype is safe only with no surviving use at all; a
    pointer retype is safe for a use whose VALUE is what is read (`_value_use`).
    """
    if not surv:
        return True
    if "*" not in pty or "*" not in lty:
        _note(skips, "retype-scalar-surviving-use")
        return False
    for a, b in surv:
        if not _value_use(masked, a, b, b0, b1):
            _note(skips, "retype-pointer-use-not-value")
            return False
        callee = _enclosing_callee(masked, a, b0)
        if callee and (callee in macros or UPPER.match(callee)):
            _note(skips, "retype-use-in-macro-call")   # `MAC(p)` may be `(p)[3]`
            return False
    return True


def _bare(ty):
    """The declared type without its storage class: `register` is carried, never compared."""
    return re.sub(r"^register\b[ \t]*", "", ty).strip()


def _compatible(pty, lty, skips):
    """The parameter may take the local's declared type only when no value changes."""
    pty = _bare(pty)
    if pty == lty:
        return True
    if set(QUAL.findall(pty)) != set(QUAL.findall(lty)):
        _note(skips, "qualifier-differs")
        return False
    if ("*" in pty) != ("*" in lty):
        # a scalar for a pointer (or the reverse) is a different KIND of type, not this class's
        # width lever: `T69_RETYPE_SCALAR` must never reach it.
        _note(skips, "pointer-vs-scalar")
        return False
    if "*" not in pty or "*" not in lty:
        # A scalar retype narrows or widens the parameter: t36/t40's lever, opened here only on
        # request (T69_RETYPE_SCALAR=1) because it changes the function's declared signature.
        if os.getenv("T69_RETYPE_SCALAR", "0") == "1":
            _note(skips, "opened-retype-scalar")
            return True
        _note(skips, "retype-scalar")
        return False
    if pty.count("*") != lty.count("*"):
        _note(skips, "pointer-depth-differs")
        return False
    return True


def entry_copies(text, fn, skips=None):
    """The redundant parameter copies of `fn`, in source order.

    A record is (param, ptype, ptype_span, local, ltype, decl_span, copy_span). Every refusal below
    is counted in `skips`; nothing here compiles anything.
    """
    name, params, b0, b1 = fn
    masked = _mask(text)
    if not params:
        _note(skips, "no-parameters")
        return []
    sig_lo = min(a for _, _, a, _ in params)
    pp = _pp_depth(masked)
    dnames = _directive_names(masked)
    pasting = _pasting_macros(masked)
    if pp[sig_lo] or pp[b0] or pp[b1] or max(pp[sig_lo:b1] or [0]):
        _note(skips, "preprocessor-region")      # never edit inside a preprocessor arm
        return []
    body = masked[b0:b1]
    dep = _depths(masked)
    pnames = {p: ty for p, ty, _, _ in params}
    pspan = {p: (a, b) for p, _, a, b in params}
    out, seen = [], set()
    for m in DECL.finditer(masked, b0, b1):
        v, ty = m.group("var"), m.group("type").strip()
        if v in pnames or v in seen or ty.split()[0] in NOTYPE:
            continue
        if hasattr(skips, "cur"):
            skips.cur = v
        if dep[m.start()] <= dep[b0]:
            continue                              # not inside this function's body
        if len([1 for d in DECL.finditer(masked, b0, b1) if d.group("var") == v]) != 1:
            _note(skips, "declared-twice")        # merging would capture another scope's variable
            continue
        if dep[m.start()] > dep[b0] + 1:
            _note(skips, "nested-scope")          # allowed, but the local's scope widens: journalled
            ba, bb = _block_span(masked, dep, m.start())
            outside = [x.start() for x in re.finditer(r"(?<![\w.])%s\b" % re.escape(v), masked[b0:b1])
                       if not (ba - b0 <= x.start() <= bb - b0)]
            if outside:
                _note(skips, "nested-scope-name-escapes")   # that occurrence named something else
                continue
        init, copy_span = m.group("init"), None
        if init:
            if init not in pnames:
                continue
            p = init
        else:
            cm = re.search(r"^[ \t]*%s[ \t]*=[ \t]*(%s)[ \t]*;[ \t]*$" % (re.escape(v), ID), body, re.M)
            if not cm or cm.group(1) not in pnames:
                continue
            p = cm.group(1)
            if dep[b0 + cm.start()] != dep[m.start()] or b0 + cm.start() < m.end():
                # T69_BLOCK_COPY=1: the copy sits in a nested block (`if (..) { v = p; .. ASM_KEEP(v)`)
                # and every occurrence of the local lies inside that block - the local is a block
                # snapshot of a parameter that is never written (checked below), so the merge is the
                # same C.  Round-32 refusal table: 27 keeps in 21 rows behind this refusal.
                opened = False
                if os.getenv("T69_BLOCK_COPY", "0") == "1" and b0 + cm.start() >= m.end() \
                        and dep[b0 + cm.start()] > dep[m.start()]:
                    ba, bb = _block_span(masked, dep, b0 + cm.start())
                    occ = [a for a, _ in _occurrences(masked, v, m.end(), b1)]
                    opened = bool(occ) and all(ba <= a < bb for a in occ)
                if not opened:
                    _note(skips, "copy-not-in-the-declaration-block")
                    continue
                _note(skips, "opened-block-copy")
            copy_span = (b0 + cm.start(), b0 + cm.end() + 1)
            first = re.search(r"(?<![\w.])%s\b" % re.escape(v), body[m.end() - b0:])
            if first and m.end() - b0 + first.start() < cm.start():
                _note(skips, "use-before-copy")
                continue
        if m.group("asm"):
            # a hard-register pin cannot move onto a parameter.  T69_DROP_REG (default 1 since round
            # 32) drops the copy AND its ASM_REG (the parameter's own pseudo takes whatever register the
            # allocator gives it): the round-32 refusal table's largest entry (384 records / 278 rows,
            # 95 keeps behind them), 11 rows / 18 pins under the byte verdict; T69_DROP_REG=0 closes it.
            if os.getenv("T69_DROP_REG", "1") != "1":
                _note(skips, "reg-pinned-local")
                continue
            _note(skips, "opened-drop-reg")
        # `register T v ASM_REG("$N") = p;` - the initialiser is a write `_writes` cannot see (the
        # pin sits between the name and the `=`); it is the one write this record expects.
        if _writes(body, v) + (1 if init and m.group("asm") else 0) != 1:
            _note(skips, "local-written-twice")
            continue
        if _writes(body, p) != 0:
            _note(skips, "param-written")
            continue
        if re.search(r"&\s*(?:%s|%s)\b" % (re.escape(v), re.escape(p)), body):
            _note(skips, "addr-taken")
            continue
        if p in dnames or v in dnames:
            # `#define effect held_effect` (src/dungeon/func_810332A4.c): the alias changes what the
            # name means for the rest of the file, and the rename would rewrite the directive.
            _note(skips, "macro-name-collision")
            continue
        surv = _surviving_uses(masked, b0, b1, p, (m.start(), m.end()), copy_span)
        if pasting and any(_enclosing_callee(masked, a, b0) in pasting for a, _ in surv):
            _note(skips, "macro-stringizes-the-name")
            continue
        if not _compatible(pnames[p], ty, skips):
            continue
        if _bare(pnames[p]) != ty and not _retype_safe(masked, b0, b1, p, _bare(pnames[p]), ty,
                                                       surv, pasting, skips):
            continue
        if m.group("reg"):
            _note(skips, "register-local-carried")    # the storage class moves with the declaration
        if any(r[0] == p for r in out):
            _note(skips, "param-copied-twice")
            continue
        seen.add(v)
        out.append((p, pnames[p], pspan[p], v, ty, (m.start(), m.end()), copy_span))
    if hasattr(skips, "cur"):
        skips.cur = None
    if not out:
        _note(skips, "no-entry-copy")
    return out


SLOT = re.compile(r"\s*(?P<type>[A-Za-z_][\w \t\*]*?)\s*\b(?P<name>[A-Za-z_]\w*)\s*")


def _prototype_edits(text, masked, fname, params, rety, ren):
    """Retype (and rename) the same-file prototypes of `fname` with the definition (t36.build's rule).

    Each affected prototype parameter slot is rewritten whole, so a named slot keeps a name and an
    unnamed one stays unnamed.  A prototype with a different arity is not this function's."""
    edits, dep, pp = [], _depths(masked), _pp_depth(masked)
    for m in re.finditer(r"\b%s\s*\((?P<params>[^;{}()]*)\)\s*;" % re.escape(fname), masked):
        if dep[m.start()] != 0:
            continue                              # a recursive call inside a body, not a prototype
        if pp[m.start()]:
            if rety and len(m.group("params").split(",")) == len(params):
                return None                       # a prototype we may not edit would now conflict
            continue
        parts, pos = m.group("params").split(","), m.start("params")
        if len(parts) == len(params):
            for i, part in enumerate(parts):
                p = params[i][0]
                if p in rety:
                    nm = SLOT.fullmatch(part)
                    rep = rety[p] + ((" " + ren.get(p, nm.group("name"))) if nm else "")
                    if nm and "*" in rety[p]:
                        rep = rety[p] + ren.get(p, nm.group("name"))
                    edits.append((pos, pos + len(part), rep))
                pos += len(part) + 1
    return edits


def merge(text, fn, chosen, skips=None):
    """Apply `chosen` to `fn`: the parameters take the locals' names (and pointer types), the locals
    and their copies go, and the single-variable keeps on those locals are erased."""
    name, params, b0, b1 = fn
    masked = _mask(text)
    sig_lo = min(a for _, _, a, _ in params)
    ren = {r[0]: r[3] for r in chosen}
    rety = {r[0]: r[4] for r in chosen if _bare(r[1]) != r[4]}
    edits = []
    dropped_reg = False
    for p, pty, ps, v, lty, dspan, cspan in chosen:
        edits.append((dspan[0], dspan[1], ""))
        if cspan:
            edits.append((cspan[0], cspan[1], ""))
        # a `register` local keeps its storage class when it becomes the parameter, and a `register`
        # parameter keeps its own (legal C; the round-31 reviewer's case 5: dropping it silently
        # changed what the source said, and the retype path used to drop it too).  A local declared
        # `register T v ASM_REG(..)` (the T69_DROP_REG opening) is the exception: that `register` is
        # the pin's syntax, not the source's, and goes with the pin.
        asm_pinned = "ASM_REG" in masked[dspan[0]:dspan[1]]
        dropped_reg = dropped_reg or asm_pinned
        reg = ((not asm_pinned and bool(re.match(r"[ \t]*register\b", masked[dspan[0]:dspan[1]])))
               or bool(re.match(r"register\b", pty)))
        newty = lty if p in rety else pty
        if reg and not re.match(r"register\b", newty):
            newty = "register " + newty
        if newty != pty:
            edits.append((ps[0], ps[1], newty))
    proto = _prototype_edits(text, masked, name, params, rety, ren)
    if proto is None:
        _note(skips, "prototype-not-retypable")
        return None
    edits += proto
    gone = [(x, y) for x, y, rep in edits if rep == ""]
    for p, v in ren.items():
        for a, b in _occurrences(masked, p, 0, len(masked)):
            if any(x <= a < y for x, y in gone):
                continue                          # the occurrence is inside a statement we delete
            if sig_lo <= a < b0 or b0 < a < b1:
                edits.append((a, b, v))
    edits = sorted(set(edits))
    for (x, y, _), (x2, y2, _) in zip(edits, edits[1:]):
        if x2 < y:
            _note(skips, "overlapping-edit")
            return None
    pp = _pp_depth(masked)
    if any(pp[x] or pp[max(x, y - 1)] for x, y, _ in edits):
        _note(skips, "preprocessor-region")       # an edit position inside a #if arm, anywhere in the file
        return None
    dm = _directive_mask(masked)
    if any(dm[x] or dm[max(x, y - 1)] for x, y, _ in edits):
        _note(skips, "preprocessor-directive-line")   # #define/#undef/#include/#if lines are read-only
        return None
    t = text
    for x, y, rep in reversed(edits):
        t = t[:x] + rep + t[y:]
    F = next((f for f in functions(t) if f[0] == name), None)
    if F is None:
        _note(skips, "function-lost")
        return None
    pins, kept = [], False
    for s in sites_of(t):
        if not (F[2] < s[3] < F[3]):
            continue
        names = re.findall(r"(?<![\w.])(%s)\b" % "|".join(re.escape(v) for v in ren.values()), t[s[3]:s[4]])
        if not names:
            continue
        if s[1] in ERASABLE and s[2] in ren.values():
            pins.append(s)
        else:
            kept = True
    if kept:
        _note(skips, "pin-shape-not-erasable")
    if not pins and not dropped_reg:
        _note(skips, "no-pin-removed")
        return None
    if pins:
        t = erase_many(t, pins, clean_notes=True)
    if unscored_text(t) != unscored_text(text):
        _note(skips, "arm-edit")
        return None
    return t


def prologue_candidates(text, skips=None):
    """[(label, candidate text)] - the whole copy set first, then its subsets, most pins removed first."""
    if skips is None:
        skips = collections.Counter()
    out, seen = [], set()
    n_in = len(sites_of(text))
    for fn in functions(text):
        ec = entry_copies(text, fn, skips)
        if not ec:
            continue
        subs = [tuple(range(len(ec)))]
        if len(ec) > 1:
            subs += [s for k in range(len(ec) - 1, 0, -1) for s in itertools.combinations(range(len(ec)), k)]
        for sel in subs:
            if len(out) >= MAX_CANDS:
                _note(skips, "menu-capped")
                break
            t = merge(text, fn, [ec[i] for i in sel], skips)
            if t is None or t in seen:
                continue
            seen.add(t)
            out.append(("prologue:%s:%s" % (fn[0], "+".join(ec[i][3] for i in sel)), t))
    out.sort(key=lambda c: len(sites_of(c[1])))
    return out[:MAX_CANDS]


class T:
    name = "t69_prologue"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not any(entry_copies(text, fn) for fn in functions(text)):
            return "no redundant parameter copy"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        skips = collections.Counter()
        cands = prologue_candidates(text, skips)
        pins_in = len(sites_of(text))
        info = {"skips": dict(skips), "candidates": len(cands), "pins_in": pins_in}
        if not cands:
            info["refused"] = ["no buildable candidate"]
            return None, info
        base = compile_s(row, text)                    # ranking only; vf is the sole authority
        ranked = []
        for label, t in cands:
            d = sdiff(base, compile_s(row, t)) if base is not None else None
            if d is None:
                skips["does-not-compile"] += 1
                continue
            ranked.append((d, -(pins_in - len(sites_of(t))), label, t))
        ranked.sort()
        info["skips"] = dict(skips)
        info["screen"] = [[d, lab] for d, _, lab, _ in ranked[:8]]
        tried = 0
        for d, negrem, label, t in ranked[:VERIFY_BUDGET]:
            tried += 1
            if vf(t).get("exact"):
                info.update(label=label, tried=tried, screen_distance=d, pins_out=len(sites_of(t)))
                return t, info
        info.update(tried=tried, refused=["no candidate exact at the recorded cell"])
        return None, info
