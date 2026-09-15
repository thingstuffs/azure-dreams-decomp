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
label or a called function, a mention inside a macro argument, an inner-scope local of the same
name, a declaration or a mention of either variable inside ANY preprocessor region of the function
(see PREPROCESSOR REGIONS below), a multi-declarator or array declaration, and any candidate whose
surviving pins are not exactly the input's minus V's.

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
declaration, and respells the uses of the variable it deleted.
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

    def __init__(self, F, recs, pp=None):
        self.F = F
        ml = F.ml
        self.ml = ml
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
        self.kills = set()
        self.addr = False
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
                for mm in MACROARG_RE.finditer(s):
                    span = _paren_span(s, mm.end() - 1)
                    if span and span[0] < m.start() < span[1]:
                        self.ok, self.reason = False, "in-macro-arg"
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
    __slots__ = ("F", "flow", "H", "V", "hf", "vf_", "reg", "block", "dist", "twoarm")


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
                    flows[key] = Flow(F, recs, pp)
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
                    p.block = F.encl(min(fh.lines + fv.lines), max(fh.lines + fv.lines))
                    p.dist = min(abs(x - y) for x in fh.lines for y in fv.lines)
                    p.twoarm = _arms(F, dh["block"], dv["block"])
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
            paren = bool(re.match(r"[ \t]*(?:\[|->|\.|\()", after))
            rep = ("(%s%s)" % (cv, host)) if paren else "%s%s" % (cv, host)
            ln = ln[:m.start()] + rep + ln[m.end():]
        edits[k] = ln
    return edits


def candidates_for(pair, skips):
    """[(form, label, text)] for one ordered pair."""
    F, t = pair.F, pair.F.t
    H, V, hf, vf_ = pair.H, pair.V, pair.hf, pair.vf_
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
    places = []
    for bt, btag in zip(targets, ("hoist", "hoistfn")):
        # The host's name must mean the host everywhere in the block it is about to cover: an inner
        # local or a global of that name there would be captured by the rename (or by the new scope).
        # A mention that already means V is one the rewrite renames - V may even carry H's own name,
        # which is m2c's spelling of one variable declared twice, the clearest case of all.
        rxh = N._occ(H["name"])
        if any(rxh.search(F.ml[k]) and F.resolve(H["name"], k) not in (H, V)
               for k in range(bt[0] + 1, min(bt[1], len(F.ml)))
               if k not in (H["line"], V["line"])):
            skips["host-name-collision"] += 1
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
        return []
    kind = "twoarm" if pair.twoarm else ("hoist" if hoist else "plain")

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
            label = "t66:%s:%s%s:%s->%s@$%s" % (kind, form, ("+" + tag if tag else ""),
                                                V["name"], H["name"], pair.reg)
            out.append(("%s/%s%s" % (kind, form, ("+" + tag) if tag else ""), label, cand))
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
        want = _pin_key(text)
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
                if len(sites_of(cand)) != pins_in - 1 or not _pins_ok(want, cand, p, text):
                    skips["pinsig-changed"] += 1
                    continue
                out.append((label, cand))
                if len(out) >= cap:
                    return out
    except Exception as e:                       # a parse fault costs candidates, never a sweep row
        skips["error:" + type(e).__name__] += 1
    return out


def _reg_arg(text, d):
    for s in sites_of(text):
        if s[1] == "ASM_REG" and s[5] - 1 == d["line"]:
            return s[2]
    return None


def _pins_ok(want, cand, pair, text):
    """The candidate's pins are the input's minus V's own, and no other pin's text changed."""
    got = _pin_key(cand)
    lost, gained = want - got, got - want
    if gained or sum(lost.values()) != 1:
        return False
    macro, arg, decl = next(iter(lost))
    return (macro == "ASM_REG" and arg == _reg_arg(text, pair.V)
            and decl.split()[-1].lstrip("*") == pair.V["name"])


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
                        if len(sites_of(cand)) != len(sites_of(cur)) - 1 \
                                or not _pins_ok(_pin_key(cur), cand, p, cur):
                            skips["pinsig-changed"] += 1
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
