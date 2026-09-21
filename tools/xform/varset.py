"""Variable-set moves: the declaration-level rewrites the landed lane diffs actually made.

WHY.  `work/native_lane/r28_dev/ex/reg/lane_won.txt.declmoves.json` inventories every landed diff of
the last 60 commits that lowered a register count with a body change (403 diffs).  The declaration
level dominates it: RETYPE-int 50, SPLIT 43 (an added local takes one definition of an existing
local), INLINE 31 + INLINE? 47 (a removed local whose defining expression now sits at its uses),
MERGE-local 24, MERGE-param 8.  The existing menu covers only the straight-line corner of each:
`t51.candidates` fuses a producer into the NEXT statement's sole use and splits a single-set lifetime
over a straight run of <= 10 statements; `natural.dropcopy` inlines only `x = y` copies;
`t60.reuse_candidates` merges two disjoint lifetimes that are both straight-line.  The lanes inlined
multi-definition temps whose uses sit several statements later across labels
(`ex/reg/dungeon_func_80CEB850.2c41d45a.diff`) and split one local into six at labels and across arms
(`ex/reg/town_func_800BC8AC.27e12c0f.diff`).  Both need reaching definitions on a control-flow graph,
which is what this module adds.

WHAT.  Five pure text moves, each `<move>_candidates(text, focus=None, skips=None) -> [(label, text)]`,
deterministic, at most CAP (48) candidates per move per call, the ones nearest `focus` first:

  inline_def   one definition web of a local substituted at the uses it alone reaches, the definition
               deleted, the declaration deleted when no definition remains (`:all` does every web).
  split_def    one definition web renamed to a fresh `V_2` declared right after `V` (`:all` gives
               every web after the first its own name).
  merge_local  two locals of the identical declared type whose live ranges are disjoint ON THE CFG,
               either naming direction.
  merge_param  a local merged into a same-type dead parameter, and the reverse `usecopy` direction:
               a parameter copied once into a local, the local used at every later use of the
               parameter (both values stay live, which is the allocation lever).
  retype_ptr   a `M2C_UNK *` / `void *` / `u8 *` local whose every dereference casts it to one struct
               pointer type declared as that type, the casts dropped.

THE ANALYSIS.  Statement-level CFG over the LOGICAL statements of one function body (labels, goto,
if/else, for/while/do, switch/case, return/break/continue, declarations, pin macros).  One node is a
RUN of physical lines - the lines are joined until the parentheses balance and the text ends in
`;`/`{`/`}`/a label colon - because round 65's one-node-per-physical-line model made every statement
that wrapped over two lines an `unknown`, and an `unknown` had an edge to every later node AND to
every label.  Over the 995 pinned functions of src/{dungeon,town,main} that was 8,626 unknown nodes
(3,742 continuation lines, 3,122 brace lines, 918 wrapped control heads, 448 other statements, 396
preprocessor lines), and the spray made a value that dies in the first loop look live in the second
(dungeon/func_813238E8) and welded two ranges of one do-while into a single back-edged web
(town/func_8009A370).  What still cannot be classified stays an `unknown`, but only a node that can
actually transfer control - one holding `goto`/`break`/`continue`/`return`/`case`/`default`, a
control keyword, a label or a brace, or whose parentheses do not balance - keeps the conservative
edges; a balanced `;`-terminated statement falls through to its successor and nowhere else.  The
edges are still an OVER-approximation of the real control flow: no rule here can DELETE an edge the
program has, which is what keeps reaching definitions and liveness sound.  Reaching definitions come from a
DFS from each definition that is killed by the next definition; a definition that READS the variable
(`V += e`, `V++`, `V = f(V)`) is unioned with the definitions reaching its read.  The resulting
union-find WEBS are the unit of inline and split, which makes "a use reached by two definitions" and
"a back edge that carries V" refusals fall out instead of being special cases.  Liveness is the
ordinary backward fixpoint over the same graph.

INTERFERENCE (`_interfere`) is the Chaitin test, both halves.  Overlapping live-in/live-out is the
obvious half; the half round 28's first cut missed is the DEFINITION edge - a definition of `a` at a
node where `b` is live OUT clobbers `b` even though `b` is not live IN there.  Without it
`a = 1; if (arg) goto mid; b = 2; r = b; mid: r = a;` merged `a` into `r` and the `arg == 0` path
read 2 where the original read 1; on the lane's own 180 real texts the def edge refuses 23 of the 372
pairs the live-in/live-out test alone accepted (6%).  `merge_param`'s first direction uses the same
test with the parameter's implicit entry definition; its `usecopy` direction additionally requires
that every path from the entry to a renamed parameter use runs THROUGH the copy (walking forward from
the copy instead follows back edges, and a loop then renames a use that runs before the copy).

WHAT IS NEVER TOUCHED.  Struct members however they are spaced (`p->f`, `p-> f`, `p . f`), labels and
the `goto`s that name them (`occ_spans` - the regex lookbehind alone cannot see either, and inlining
into one produced `goto ((s32)(1));`), string and comment bodies (the masked
twin is what every scan reads), any identifier on a line inside ANY preprocessor conditional, a local
whose address is taken, a local declared `volatile`/`const`, a local declared with a `register ...
ASM_REG(...)` pin, a comma declarator (`s32 a, b;` - never found, so refused as `undeclared`), a
shadowed name (two declarations in one function), a variable defined in a `for` header or a `while`
condition, and a use this module could not place on a CFG node.  No qualifier is ever added or
dropped: every rewritten declaration is rebuilt from the ORIGINAL declaration text with only the name
(inline/split/merge) or the base type (retype_ptr) replaced.

No move emits scaffolding: nothing here can introduce an `ASM_*` macro, `__asm__`, `volatile`, a fake
dependency or a one-trip block.  Only `vf` accepts a candidate; every ordering here is ranking.
"""
import collections
import itertools
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from xform.t12_stmtorder import mask, depths, movable
from xform.t36_paramwidth import functions as _function_defs

CAP = 48                      # candidates per move per call
MAX_NODES = 900               # a function larger than this is refused (quadratic reachability)
MAX_UNKNOWN = 0.25            # a body this degraded reaches everything from everything: refuse it

ID = r"[A-Za-z_]\w*"
CALL_RE = re.compile(r"\b(?!sizeof\b|return\b|if\b|while\b|for\b|switch\b)" + ID + r"\s*\(")
STMT_KEYWORDS = {"return", "goto", "break", "continue", "else", "do", "case", "default", "if",
                 "while", "for", "switch", "typedef", "extern", "sizeof"}
TYPEWORDS = {"u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64", "void", "char",
             "short", "int", "long", "float", "double", "unsigned", "signed", "register", "const",
             "volatile", "static", "struct", "union", "enum"}
C_KEYWORDS = TYPEWORDS | STMT_KEYWORDS | {"auto", "NULL"}
RETYPABLE = ("M2C_UNK *", "M2C_UNK8 *", "M2C_UNK16 *", "M2C_UNK32 *", "void *", "u8 *", "s8 *",
             "char *", "unsigned char *")
# a line that opens an AGGREGATE rather than a block: `... = {` and `struct|union|enum ... {`.  The
# run joiner reads on past it to the `};`, so a label table is one node, not one node per element.
AGG_OPEN_RE = re.compile(
    r"^(?!(?:if|else|for|while|switch|do|case|default)\b)[^;{}]*=\s*\{$"
    r"|^(?:typedef[ \t]+)?(?:(?:static|const|volatile|register)[ \t]+)*(?:struct|union|enum)\b[^;{}]*\{$")
# a trailing `:` ends a run only on a label or a case arm (`x = c ?` / `a :` must read on)
TERM_COLON_RE = re.compile(r"^(?:case\b.*|default[ \t]*|[A-Za-z_]\w*[ \t]*):$")
# a COMPLETE control head with no `{` of its own: `if (c)`, `while (c)`, `else`, `do`.  The run
# stops here rather than swallowing the arm under it, so a braceless arm stays a statement node of
# its own (`perturb_struct` refuses to insert a line in front of one) and the head keeps the
# conservative edges a branch needs.  An Allman `{` on the next line is joined back on.
CTRL_HEAD_RE = re.compile(r"^(?:\}[ \t]*)?(?:else[ \t]+if|if|for|while|switch)[ \t]*\(.*\)$"
                          r"|^(?:\}[ \t]*)?(?:else|do)$")


# --------------------------------------------------------------------------- small text helpers

def occ_re(v):
    """Every mention of the local `v`: not a struct member (`.v`, `->v`), not part of a longer name."""
    return re.compile(r"(?<![\w.])(?<!->)" + re.escape(v) + r"\b")


MEMBER_PRE = re.compile(r"(?:->|\.)[ \t]*$")
GOTO_PRE = re.compile(r"(?<![\w.])goto[ \t]+$")
LABEL_POST = re.compile(r"^[ \t]*:(?!:)")


def occ_spans(s, v):
    """The spans of `s` that really NAME the local `v`.

    `occ_re`'s lookbehind cannot see a separator that carries whitespace, and it cannot see a
    label at all.  Three kinds of token spelled like the local are therefore filtered here, on
    the masked line, and nowhere else (every other caller of `occ_re` only over-approximates,
    which refuses a candidate and is safe):

      * a struct member however it is spaced - `p->v`, `p-> v`, `p . v`;
      * the target of a `goto`;
      * a label definition `v:` (never `case v:`, never the `:` of a conditional).

    Renaming or substituting into any of those produced broken text (`goto ((s32)(1));`).
    """
    out = []
    for m in occ_re(v).finditer(s):
        pre, post = s[:m.start()], s[m.end():]
        if MEMBER_PRE.search(pre) or GOTO_PRE.search(pre):
            continue
        if not pre.strip() and LABEL_POST.match(post):
            continue
        out.append(m.span())
    return out


def write_re(v):
    """A write to `v`: `v =`, `v op=`, `v++`, `++v` (never `*v = `, `v[i] = `, `p->v = `)."""
    n = re.escape(v)
    return re.compile(r"(?<![\w.])(?<!->)%s[ \t]*(?:=(?!=)|[-+*/%%&|^]=|<<=|>>=|\+\+|--)"
                      r"|(?:\+\+|--)[ \t]*(?<![\w.])%s\b" % (n, n))


def _nl(s):
    return s[:-1] if s.endswith("\n") else s


def _wrapped(e):
    """True when `e` is one balanced parenthesis pair around its whole body."""
    e = e.strip()
    if not (e.startswith("(") and e.endswith(")")):
        return False
    depth = 0
    for i, c in enumerate(e):
        depth += (c == "(") - (c == ")")
        if depth == 0:
            return i == len(e) - 1
    return False


def _term(e):
    """True when `e` needs no parentheses in any operand position."""
    e = e.strip()
    return _wrapped(e) or bool(re.fullmatch(
        r"[A-Za-z_]\w*|-?(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*"
        r"|[A-Za-z_]\w*(?:(?:->|\.)\w+|\[[^\[\]]*\])+"
        r"|&[A-Za-z_]\w*(?:(?:->|\.)\w+|\[[^\[\]]*\])*", e))


def pp_lines(text):
    """Per line: True when the line sits inside ANY preprocessor conditional (or is one, or is a
    continued `#define` body).  Identifiers on such lines are never renamed or rewritten."""
    out, depth, cont = [], 0, False
    for ln in text.split("\n"):
        s = ln.lstrip()
        directive = s.startswith("#")
        if directive and re.match(r"#\s*(if|ifdef|ifndef)\b", s):
            out.append(True)
            depth += 1
            cont = ln.rstrip().endswith("\\")
            continue
        if directive and re.match(r"#\s*(endif)\b", s):
            depth = max(0, depth - 1)
            out.append(True)
            cont = ln.rstrip().endswith("\\")
            continue
        out.append(depth > 0 or directive or cont)
        cont = ln.rstrip().endswith("\\")
    return out


def typedef_names(text):
    names = set()
    for m in re.finditer(r"\btypedef\b[^;{}]*?(" + ID + r")\s*;", mask(text)):
        names.add(m.group(1))
    for m in re.finditer(r"\}\s*(" + ID + r")\s*;", mask(text)):
        names.add(m.group(1))
    return names


def _is_typename(base, tds):
    return (base in TYPEWORDS or base in tds or base.startswith("M2C_")
            or bool(re.fullmatch(r"[usf](8|16|32|64)", base)) or base[:1].isupper())


DECL_RE = re.compile(
    r"^(?P<ind>[ \t]*)(?P<prefix>(?:(?:register|static|const|volatile|struct|union|enum|unsigned|signed|long|short)[ \t]+)*"
    r"(?P<base>" + ID + r")(?P<stars>(?:[ \t]*\*)*)[ \t]*)"
    r"(?P<var>" + ID + r")[ \t]*(?P<pin>ASM_REG\([^)\n]*\))?[ \t]*"
    r"(?P<arr>\[[^\]\n]*\])?[ \t]*(?P<init>=[^;\n]*)?;")

COMMA_DECL_RE = re.compile(r"^[ \t]*(?:(?:register|static|const|volatile|struct|union|enum|unsigned|signed|long|short)[ \t]+)*"
                           + ID + r"(?:[ \t]*\*)*[ \t]*" + ID + r"[ \t]*,")


# --------------------------------------------------------------------------- the CFG

class Node:
    """One LOGICAL statement: the physical lines `lines`, joined and masked in `joined`.

    `masked` and `line` stay the FIRST physical line, and a wrapped simple statement keeps the kind
    `stmt`, because that is what every caller outside this module reads (`perturb_struct` scans
    `fn.m[n.line]` and has its own continuation guard).  The analysis here reads `joined` and
    `lines`, so a statement wrapped over three lines is ONE node with one kind; anything that edits
    from `masked` alone must check `len(node.lines) == 1` first.
    """
    __slots__ = ("i", "line", "lines", "kind", "masked", "joined", "label", "raw", "depth", "succ",
                 "head")

    def __init__(self, i, line, kind, masked, raw, depth, lines=None, joined=None, label=None):
        self.i, self.line, self.kind = i, line, kind
        self.masked, self.raw, self.depth = masked, raw, depth
        self.lines = list(lines) if lines else [line]
        self.joined = masked.strip() if joined is None else joined
        self.label = label
        self.succ = []
        self.head = None            # for a block opener: the node index after its matching close

    def __repr__(self):
        return "<%d L%d %s %r>" % (self.i, self.line + 1, self.kind, self.joined[:40])


LABEL_PRE_RE = re.compile(r"^(" + ID + r")[ \t]*:(?!:)")
IFGOTO_RE = re.compile(r"^\}?\s*if\s*\(.*\)\s*goto\s+(" + ID + r")\s*;$", re.S)
PP_COND_RE = re.compile(r"#\s*(if|ifdef|ifndef|else|elif|endif)\b")
JUMPY_RE = re.compile(r"\b(goto|break|continue|return|case|default|if|else|for|while|switch|do)\b")
# a DECLARATION whose initialiser or body carries braces - `T t[] = { ... };`, `struct { ... } x;`.
# It transfers no control, so it falls through even though `_simple_unknown` otherwise refuses a
# brace.  The computed-goto label tables (`static void *const case_labels[] = { &&jt_c1, ... };`,
# 169 of them) are this shape: as a conservative node one of them reached every later node and
# every label of its function and made every pair of locals interfere.  The `goto *p;` that USES
# the table still holds `goto`, so it keeps the conservative edges.
AGG_STMT_RE = re.compile(r"^[^;{}]*=[ \t]*\{.*\}[ \t]*;$"
                         r"|^(?:typedef[ \t]+)?(?:(?:static|const|volatile|register)[ \t]+)*"
                         r"(?:struct|union|enum)\b.*\}[^;{}]*;$", re.S)


def _label_of(s):
    """(label, rest) - `L:`, `L: {`, `L: do {`, `L: ;` all NAME a label; `case`/`default` do not."""
    if re.match(r"^(?:case|default)\b", s):
        return None, s
    m = LABEL_PRE_RE.match(s)
    if not m:
        return None, s
    return m.group(1), s[m.end():].strip()


def _simple_unknown(s):
    """True when an unclassified statement provably transfers control only to its successor.

    A balanced, `;`-terminated statement with no label and no jump or control keyword cannot
    branch, so the conservative "edge to every later node and every label" is pure noise on it; an
    aggregate declaration (`AGG_STMT_RE`) counts as one although it carries braces.  Everything
    else - a wrapped control head, a braceless `if (c) x = 1;`, an unbalanced fragment, a
    preprocessor conditional - keeps the conservative edges.
    """
    if not s.endswith(";"):
        return False
    if JUMPY_RE.search(s) or LABEL_PRE_RE.match(s):
        return False
    if s.count("(") != s.count(")") or s.count("[") != s.count("]"):
        return False
    if "{" in s or "}" in s:
        return s.count("{") == s.count("}") and bool(AGG_STMT_RE.match(s))
    return True


def _classify(s):
    """Kind of one masked, stripped LOGICAL statement (a run of physical lines, space-joined)."""
    if not s:
        return "blank"
    if s.startswith("#"):
        # a conditional selects between two texts, so it keeps the conservative edges; `#define`,
        # `#undef`, `#include`, `#pragma` are not control flow at all (func_813238E8's three
        # `#define entity entity` lines sprayed an edge onto every later node and every label)
        return "unknown" if PP_COND_RE.match(s) else "ppsimple"
    if re.match(r"^case\b", s) or re.match(r"^default\s*:", s):
        return "case"              # BEFORE the label test: `default` is also spelled like an ID,
                                   # and as a `label` the switch never edged to its arm at all
    if re.fullmatch(ID + r"\s*:", s):
        return "label"
    if s == "{":
        return "blockopen"
    if IFGOTO_RE.match(s):
        return "ifgoto"
    if re.match(r"^goto\b", s) and s.endswith(";"):
        return "goto"
    if re.match(r"^return\b", s) and s.endswith(";"):
        return "return"
    if re.fullmatch(r"break\s*;", s):
        return "break"
    if re.fullmatch(r"continue\s*;", s):
        return "continue"
    if re.match(r"^\}\s*while\s*\(.*\)\s*;\s*$", s):
        return "dowhile"
    if re.match(r"^do\b", s) and s.endswith("{"):
        return "do"
    if re.match(r"^(if|else\s+if)\b", s) and s.endswith("{"):
        return "if"
    if re.match(r"^\}\s*else\s+if\b", s) and s.endswith("{"):
        return "elseif"
    if re.match(r"^\}\s*else\b", s) and s.endswith("{"):
        return "elseopen"
    if re.fullmatch(r"else\s*\{", s):
        return "elseopen"
    if re.match(r"^(for|while)\b", s) and s.endswith("{"):
        return "loop"
    if re.match(r"^switch\b", s) and s.endswith("{"):
        return "switch"
    if re.fullmatch(r"\}", s):
        return "close"
    if re.match(r"^(if|for|while|switch|else|do)\b", s):
        return "unknown"           # a braceless control head: still a branch, still conservative
    if "{" in s or "}" in s:
        return "unknown"
    if s.endswith(";") and movable(s):
        return "stmt"
    return "unknown"


def _classify_run(s):
    """(kind, label) of one logical statement, with a leading `L:` taken off first."""
    lab, rest = _label_of(s)
    if lab is None:
        return _classify(s), None
    return (_classify(rest) if rest else "label"), lab


class Fn:
    """One function definition: its declarations, its parameters and a statement-level CFG."""

    def __init__(self, text, name, params, b0, b1):
        self.text, self.name = text, name
        self.lines = text.splitlines(True)
        self.m = [_nl(x) for x in mask(text).splitlines(True)]
        if len(self.m) < len(self.lines):
            self.m += [""] * (len(self.lines) - len(self.m))
        self.d = depths(self.m)
        self.pp = pp_lines(text)
        if len(self.pp) < len(self.lines):
            self.pp += [True] * (len(self.lines) - len(self.pp))
        self.b0, self.b1 = b0, b1
        self.lo = text.count("\n", 0, b0) + 1               # first body line index
        self.hi = text.count("\n", 0, b1)                   # the closing `}` line index
        self.params = [(p, ty) for p, ty, _, _ in params]
        self.ok = True
        self.reason = None
        self.nodes = []
        self.by_line = {}
        self._build()

    # ---- construction

    MAX_RUN = 40                    # an unbalanced fragment this long is given up on, conservatively

    def _runs(self):
        """[[line, ...]] - the body's physical lines grouped into LOGICAL statements.

        A line continues into the next while its parentheses/brackets are unbalanced or it ends in
        something that is not a statement terminator (`;`, `{`, `}`, a label/case colon).  An
        aggregate opener (`... = {`, `struct {`) runs on until its braces balance and it ends in
        `;`, so an initialiser table is one node instead of one node per element.  A preprocessor
        line is always a run of its own.
        """
        out, cur, pdepth, binit, bdepth = [], [], 0, False, 0

        def flush():
            nonlocal cur, pdepth, binit, bdepth
            if cur:
                out.append(cur)
            cur, pdepth, binit, bdepth = [], 0, False, 0

        for k in range(self.lo, self.hi):
            s = self.m[k].strip()
            if not s:
                continue
            if s.startswith("#"):
                flush()
                out.append([k])
                continue
            cur.append(k)
            pdepth += s.count("(") + s.count("[") - s.count(")") - s.count("]")
            if binit:
                bdepth += s.count("{") - s.count("}")
                if (bdepth <= 0 and pdepth <= 0 and s.endswith(";")) or len(cur) >= self.MAX_RUN:
                    flush()
                continue
            if pdepth > 0:
                if len(cur) >= self.MAX_RUN:
                    flush()
                continue
            pdepth = 0
            joined = " ".join(self.m[x].strip() for x in cur)
            if s.endswith("{") and AGG_OPEN_RE.match(joined):
                binit, bdepth = True, joined.count("{") - joined.count("}")
                continue
            if CTRL_HEAD_RE.match(joined):
                nxt = next((x for x in range(k + 1, self.hi) if self.m[x].strip()), None)
                if nxt is not None and self.m[nxt].strip() == "{":
                    continue                    # Allman: the `{` under the head belongs to it
                flush()
                continue
            if s.endswith((";", "{", "}")) or TERM_COLON_RE.match(s) or len(cur) >= self.MAX_RUN:
                flush()
        flush()
        return out

    def _build(self):
        tds = typedef_names(self.text)
        for lines in self._runs():
            joined = " ".join(self.m[k].strip() for k in lines).strip()
            kind, label = _classify_run(joined)
            if kind == "blank":
                continue
            if any(self.pp[k] for k in lines) and not joined.startswith("#"):
                kind, label = "unknown", None
            if kind == "stmt" and joined.startswith("ASM_"):
                kind = "pin"
            n = Node(len(self.nodes), lines[0], kind, self.m[lines[0]], self.lines[lines[0]],
                     self.d[lines[0]], lines, joined, label)
            for k in lines:
                self.by_line[k] = n.i
            self.nodes.append(n)
        if not self.nodes or len(self.nodes) > MAX_NODES:
            self.ok, self.reason = False, "function-too-large"
            return
        unknown = sum(n.kind == "unknown" for n in self.nodes)
        if unknown > MAX_UNKNOWN * len(self.nodes):
            self.ok, self.reason = False, "body-too-degraded"
            return
        self.decls = self._declarations(tds)
        self._edges()

    def _declarations(self, tds):
        out = collections.defaultdict(list)
        for n in self.nodes:
            if len(n.lines) != 1:
                continue            # a wrapped declaration's DECL_RE offsets do not index one line
            m = DECL_RE.match(n.masked)
            if not m or not _is_typename(m.group("base"), tds):
                continue
            if m.group("base") in STMT_KEYWORDS or m.group("var") in C_KEYWORDS:
                continue
            raw = self.lines[n.line]
            out[m.group("var")].append(dict(
                node=n.i, line=n.line, ind=m.group("ind"), prefix=m.group("prefix"),
                base=m.group("base"), stars=m.group("stars").replace(" ", "").replace("\t", ""),
                var=m.group("var"), pin=bool(m.group("pin")), arr=bool(m.group("arr")),
                init=bool(m.group("init")), depth=n.depth,
                decl_text=raw[m.start("ind"):m.end("prefix")],
                register="register" in m.group("prefix"),
                qualified=bool(re.search(r"\b(volatile|const)\b", m.group("prefix")))))
        return out

    def _match_close(self, i):
        """Node index of the statement that closes the block opened by node i (None if unmatched).

        The closer is the first later node whose text takes the brace depth back to the opener's
        level at any point INSIDE it - which is what makes `} else {` the closer of the `if` above
        it.  Round 65 asked for `after <= base and depth > base`, and `} else {` has depth base+1
        and net zero braces, so it matched neither clause: `close[if]` landed on the final `}` of
        the whole chain, the `if`'s false edge jumped past the else arm and 281 else arms of the
        pinned rows had NO predecessor at all.  An opener that itself begins with `}` (`} else {`,
        `} else if (...) {`) closes one level below its own depth.
        """
        n = self.nodes[i]
        base = n.depth - 1 if n.joined.startswith("}") else n.depth
        for j in range(i + 1, len(self.nodes)):
            z = self.nodes[j]
            d = z.depth
            for c in z.joined:
                if c == "{":
                    d += 1
                elif c == "}":
                    d -= 1
                    if d <= base:
                        return j
        return None

    def _edges(self):
        nodes = self.nodes
        labels = {}
        for n in nodes:
            if n.label is not None:
                labels.setdefault(n.label, n.i)
        self.labels = labels
        # block openers -> matching close
        close = {}
        for n in nodes:
            if n.kind in ("if", "elseif", "elseopen", "loop", "do", "switch", "blockopen"):
                close[n.i] = self._match_close(n.i)
        self.close = close
        # fall-through target: skip an else chain when leaving a then-branch
        def after_chain(j):
            """Node after the whole if/else chain whose boundary node is j."""
            seen = 0
            while j is not None and j < len(nodes) and nodes[j].kind in ("elseopen", "elseif") and seen < 32:
                seen += 1
                j = close.get(j)
                if j is None:
                    return None
                j = j + 1 if nodes[j].kind == "close" else j
            return j

        def else_target(c):
            """The false edge of an `if` whose block closes at node c: the else arm when there is
            one, however it is spelled.  `} else {` IS node c; an Allman `}` on its own line with
            `else {` under it is node c+1, and round 65 sent the false edge to `ft[c]` - past the
            whole else arm, which then had no predecessor at all (22 rows)."""
            if c is None:
                return None
            if nodes[c].kind in ("elseopen", "elseif"):
                return c
            if nodes[c].kind == "close" and c + 1 < len(nodes) \
                    and nodes[c + 1].kind in ("elseopen", "elseif"):
                return c + 1
            return ft.get(c)

        ft = {}
        for n in nodes:
            j = n.i + 1
            if j < len(nodes) and nodes[j].kind in ("elseopen", "elseif"):
                ft[n.i] = after_chain(j)
            elif j < len(nodes) and nodes[j].kind == "close" and j + 1 < len(nodes) \
                    and nodes[j + 1].kind in ("elseopen", "elseif"):
                ft[n.i] = n.i + 1
            else:
                ft[n.i] = j if j < len(nodes) else None
        self.ft = ft
        # enclosing breakable / loop stacks
        stack = []          # (opener index, kind)
        enclosing = {}
        for n in nodes:
            while stack and nodes[stack[-1]].depth >= n.depth and n.kind in ("close", "dowhile"):
                break
            enclosing[n.i] = list(stack)
            if n.kind in ("loop", "switch", "do"):
                stack.append(n.i)
            elif n.kind in ("close", "dowhile") and stack:
                c = close.get(stack[-1])
                if c == n.i:
                    stack.pop()
        self.enclosing = enclosing

        def add(i, j):
            if j is not None and 0 <= j < len(nodes) and j not in nodes[i].succ:
                nodes[i].succ.append(j)

        def spray(i):
            """The conservative edges: every later node and every label of the function."""
            for j in range(i + 1, len(nodes)):
                add(i, j)
            for j in labels.values():
                add(i, j)

        for n in nodes:
            k = n.kind
            if k == "return":
                continue
            if k == "goto":
                tgt = re.match(r"^goto\s+(" + ID + r")\s*;", n.joined)
                if tgt and tgt.group(1) in labels:
                    add(n.i, labels[tgt.group(1)])
                else:
                    n.kind = "unknown"
                    k = "unknown"
            if k == "ifgoto":
                tgt = IFGOTO_RE.match(n.joined)
                if tgt and tgt.group(1) in labels:
                    add(n.i, labels[tgt.group(1)])      # a `} if (c) goto L;` loop tail: the back
                    add(n.i, ft.get(n.i))               # edge AND the fall-through, both seen
                    continue
                n.kind = k = "unknown"
            if k == "unknown":
                if _simple_unknown(n.joined):
                    add(n.i, ft.get(n.i))
                else:
                    spray(n.i)
                continue
            if k == "break":
                enc = [x for x in enclosing[n.i] if nodes[x].kind in ("loop", "switch", "do")]
                c = close.get(enc[-1]) if enc else None
                if c is not None:
                    add(n.i, ft.get(c))
                else:
                    spray(n.i)          # an unmatched block: a break with no successor at all is
                continue                # an UNDER-approximation, the one thing that is not allowed
            if k == "continue":
                enc = [x for x in enclosing[n.i] if nodes[x].kind in ("loop", "do")]
                if enc:
                    add(n.i, enc[-1])
                else:
                    spray(n.i)
                continue
            if k in ("if", "elseif"):
                add(n.i, n.i + 1)
                c = close.get(n.i)
                if c is None:
                    spray(n.i)
                else:
                    add(n.i, else_target(c))
                continue
            if k == "loop":
                add(n.i, n.i + 1)
                c = close.get(n.i)
                if c is None:
                    spray(n.i)
                else:
                    add(n.i, ft.get(c))
                continue
            if k == "do":
                add(n.i, n.i + 1)
                continue
            if k == "dowhile":
                opener = next((x for x in reversed(enclosing[n.i] + [n.i])
                               if x < n.i and nodes[x].kind == "do"), None)
                if opener is None:
                    opener = next((x.i for x in nodes[:n.i][::-1] if x.kind == "do"), None)
                add(n.i, opener)
                add(n.i, ft.get(n.i))
                continue
            if k == "switch":
                c = close.get(n.i)
                end = c if c is not None else len(nodes)
                has_default = False
                for j in range(n.i + 1, end):
                    if nodes[j].kind == "case":
                        add(n.i, j)
                        if nodes[j].joined.startswith("default"):
                            has_default = True
                if not has_default:
                    add(n.i, ft.get(c) if c is not None else None)
                if c is None:
                    spray(n.i)
                continue
            if k == "close":
                opener = None
                for x in reversed(enclosing[n.i]):
                    if close.get(x) == n.i:
                        opener = x
                        break
                if opener is not None and nodes[opener].kind == "loop":
                    add(n.i, opener)
                    continue
                add(n.i, ft.get(n.i))
                continue
            add(n.i, ft.get(n.i))

    # ---- per-variable facts

    def occurrences(self, v):
        """[(node index, physical line, [spans])] plus a count of occurrences off the CFG.

        One node may appear several times: a logical statement wrapped over three lines names the
        variable on each of them, and every rewrite here edits PHYSICAL lines.
        """
        placed, stray = [], 0
        for k in range(self.lo, self.hi):
            spans = occ_spans(self.m[k], v)
            if not spans:
                continue
            i = self.by_line.get(k)
            if i is None:
                stray += 1
                continue
            placed.append((i, k, spans))
        return placed, stray

    def kinds(self, v):
        """node -> ('plain'|'rmw'|'use'), for every node mentioning v (its declaration excluded)."""
        w = write_re(v)
        rx = occ_re(v)
        assign = re.compile(r"^\s*(?<![\w.])" + re.escape(v) + r"\s*=(?!=)\s*(?P<rhs>.*?);\s*$")
        out = {}
        ds = self.decls.get(v, [])
        # a declaration WITH an initialiser is also v's first definition; a bare one is neither
        decl_nodes = {x["node"] for x in ds if not x["init"]}
        init_nodes = {x["node"] for x in ds if x["init"]}
        placed, _ = self.occurrences(v)
        for i in sorted({x[0] for x in placed}):
            if i in decl_nodes:
                continue
            if i in init_nodes:
                init = decl_init(self, v, i)
                out[i] = "rmw" if init is None or rx.search(init) else "plain"
                continue
            s = self.nodes[i].joined
            if not w.search(s):
                out[i] = "use"
                continue
            m = assign.match(s)
            if m and not rx.search(m.group("rhs")):
                out[i] = "plain"
            else:
                out[i] = "rmw"
        return out


def functions(text, skips=None):
    """Every function definition of `text` as an Fn; a refused body is counted, never guessed at."""
    out = []
    for name, params, b0, b1 in _function_defs(text):
        try:
            f = Fn(text, name, params, b0, b1)
        except Exception as e:
            if skips is not None:
                skips["fn-parse-error:" + type(e).__name__] += 1
            continue
        if f.ok:
            out.append(f)
        elif skips is not None:
            skips["fn-refused:" + f.reason] += 1
    return out


# --------------------------------------------------------------------------- reaching definitions

def decl_init(fn, v, node):
    """The initialiser expression of `v`'s declaration at `node` (real text), or None."""
    m = DECL_RE.match(fn.nodes[node].masked)
    if not m or not m.group("init"):
        return None
    real = _nl(fn.lines[fn.nodes[node].line])
    return real[m.start("init"):m.end("init")].lstrip("=").strip()


def reaching(fn, v, kinds):
    """(reached, backedge, defs) - reached[use] = {def nodes}, backedge[use] = crossed a back edge."""
    defs = sorted(i for i, k in kinds.items() if k in ("plain", "rmw"))
    reached = collections.defaultdict(set)
    backedge = collections.defaultdict(bool)
    for d in defs:
        seen = set()
        work = [(s, s <= d) for s in fn.nodes[d].succ]
        while work:
            n, back = work.pop()
            if (n, back) in seen:
                continue
            seen.add((n, back))
            k = kinds.get(n)
            if k in ("use", "rmw"):
                reached[n].add(d)
                if back:
                    backedge[n] = True
            if k in ("plain", "rmw"):
                continue                       # the definition kills v
            for s in fn.nodes[n].succ:
                work.append((s, back or s <= n))
    return reached, backedge, defs


def webs(fn, v, kinds):
    """Union-find webs over {definition, use} nodes; [(def nodes, use nodes, crossed back edge)]."""
    reached, backedge, defs = reaching(fn, v, kinds)
    parent = {i: i for i in kinds}

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        ra, rb = find(a), find(b)
        if ra != rb:
            parent[max(ra, rb)] = min(ra, rb)

    for use, ds in reached.items():
        for d in ds:
            union(use, d)
    groups = collections.defaultdict(list)
    for i in kinds:
        groups[find(i)].append(i)
    out = []
    for root in sorted(groups):
        members = sorted(groups[root])
        ds = [i for i in members if kinds[i] in ("plain", "rmw")]
        us = [i for i in members if kinds[i] in ("use", "rmw")]
        out.append((ds, us, any(backedge.get(u) for u in us)))
    out.sort(key=lambda w: (w[0] or w[1])[0])
    return out


def liveness(fn, v, kinds):
    """(live_in, live_out) per node for the local v."""
    n = len(fn.nodes)
    use = [kinds.get(i) in ("use", "rmw") for i in range(n)]
    kill = [kinds.get(i) == "plain" for i in range(n)]
    lin, lout = [False] * n, [False] * n
    for _ in range(n + 2):
        changed = False
        for i in range(n - 1, -1, -1):
            o = any(lin[s] for s in fn.nodes[i].succ)
            x = use[i] or (o and not kill[i])
            if o != lout[i] or x != lin[i]:
                lout[i], lin[i] = o, x
                changed = True
        if not changed:
            break
    return lin, lout


# --------------------------------------------------------------------------- eligibility

def usable_locals(fn, skips, allow_register_pin=False, allow_init=False):
    """{name: decl} for the locals every move may touch, with the refusals counted in `skips`."""
    out = {}
    params = {p for p, _ in fn.params}
    body = "\n".join(fn.m[fn.lo:fn.hi])
    for v, ds in sorted(fn.decls.items()):
        if len(ds) != 1:
            skips["shadowed"] += 1
            continue
        d = ds[0]
        if d["pin"] and not allow_register_pin:
            skips["asm-reg-decl"] += 1
            continue
        if d["qualified"]:
            skips["qualified-decl"] += 1
            continue
        if d["arr"]:
            skips["array-local"] += 1
            continue
        if d["init"] and not allow_init:
            skips["initialised-decl"] += 1
            continue
        if v in params:
            skips["param-shadow"] += 1
            continue
        if re.search(r"(?:^|[^\w)\]&])&[ \t]*" + re.escape(v) + r"\b", body, re.M):
            skips["address-taken"] += 1
            continue
        placed, stray = fn.occurrences(v)
        if stray:
            skips["use-off-cfg"] += 1
            continue
        if any(fn.pp[ln] for _, ln, _ in placed):
            skips["in-pp-arm"] += 1
            continue
        if any(COMMA_DECL_RE.match(fn.m[ln]) for _, ln, _ in placed):
            skips["multi-declarator"] += 1
            continue
        if any(fn.nodes[i].kind in ("loop", "dowhile", "switch", "if", "elseif")
               and write_re(v).search(fn.nodes[i].joined) for i, _, _ in placed):
            skips["loop-header-def"] += 1
            continue
        if any(fn.nodes[i].kind == "unknown" for i, _, _ in placed):
            skips["use-on-unknown-node"] += 1
            continue
        out[v] = d
    return out


def usable_params(fn, skips):
    """{name: type} for the PARAMETERS a split may rename.

    A parameter carries an implicit definition at the entry node, so the uses that definition
    reaches form a web with no definition NODE of its own - the parameter's first web, which is
    never renamed.  Every later web is an ordinary range and splits like a local's.  A parameter is
    never a merge guest (there is no declaration line to delete) and never carries a qualifier this
    module could drop, so what it needs is the rest of `usable_locals`' screen: not address-taken,
    every mention on a CFG node it could classify, none in a preprocessor arm, none written in a
    loop header, and no local of the same name shadowing it.
    """
    out = {}
    declared = set(fn.decls)
    body = "\n".join(fn.m[fn.lo:fn.hi])
    for p, ty in fn.params:
        if not ty or not re.fullmatch(ID, p) or p in C_KEYWORDS:
            continue
        if p in declared:
            skips["param-shadow"] += 1
            continue
        if re.search(r"(?:^|[^\w)\]&])&[ \t]*" + re.escape(p) + r"\b", body, re.M):
            skips["param:address-taken"] += 1
            continue
        placed, stray = fn.occurrences(p)
        if stray:
            skips["param:use-off-cfg"] += 1
            continue
        if any(fn.pp[ln] for _, ln, _ in placed):
            skips["param:in-pp-arm"] += 1
            continue
        if any(COMMA_DECL_RE.match(fn.m[ln]) for _, ln, _ in placed):
            skips["param:multi-declarator"] += 1
            continue
        if any(fn.nodes[i].kind in ("loop", "dowhile", "switch", "if", "elseif")
               and write_re(p).search(fn.nodes[i].joined) for i, _, _ in placed):
            skips["param:loop-header-def"] += 1
            continue
        if any(fn.nodes[i].kind == "unknown" for i, _, _ in placed):
            skips["param:use-on-unknown-node"] += 1
            continue
        out[p] = ty
    return out


def _multi_occurrence(fn, v, kinds):
    """A node that both plainly defines v and mentions it again is not line-renameable."""
    rx = occ_re(v)
    for i, k in kinds.items():
        if k == "plain" and len(rx.findall(fn.nodes[i].joined)) > 1:
            return True
    return False


SELF_COPY = re.compile(r"^\s*(?P<v>[A-Za-z_]\w*)\s*=\s*(?P=v)\s*;\s*$")


def _drop_self_copies(fn, edits, skips, what):
    """A merge collapses `host = guest;` into `x = x;`.  Delete that statement instead of leaving a
    degenerate assignment in the candidate; refuse when the line is not a plain statement node
    (a braceless arm, a loop header) where deleting it would change the control flow."""
    drops = set()
    for ln in list(edits):
        if not SELF_COPY.match(edits[ln]):
            continue
        i = fn.by_line.get(ln)
        if i is None or fn.nodes[i].kind != "stmt":
            skips["%s:self-copy-not-a-plain-statement" % what] += 1
            return None
        del edits[ln]
        drops.add(ln)
    return drops


# --------------------------------------------------------------------------- text edits

def _apply(text, edits, drops=(), inserts=None):
    """edits {line: new line without newline}, drops {line}, inserts {line: [lines]} after a line."""
    lines = text.splitlines(True)
    drops, inserts = set(drops), dict(inserts or {})
    out = []
    for k, ln in enumerate(lines):
        nl = "\n" if ln.endswith("\n") else "\n"
        if k not in drops:
            out.append((edits[k] + nl) if k in edits else ln)
        for extra in inserts.get(k, []):
            out.append(extra + "\n")
    return "".join(out)


def _rename_line(fn, line, old, new, current=None):
    """The real line with every mention of `old` replaced (mask-guided, so comments never change)."""
    real = _nl(current if current is not None else fn.lines[line])
    masked = fn.m[line]
    for a, b in reversed(occ_spans(masked, old)):
        real = real[:a] + new + real[b:]
    return real


def _rename_node(fn, node, old, new, edits):
    """Rename `old` on EVERY physical line of one CFG node (a node may be a wrapped statement)."""
    for ln in fn.nodes[node].lines:
        if occ_spans(fn.m[ln], old):
            edits[ln] = _rename_line(fn, ln, old, new, edits.get(ln))
    return edits


def _param_decl(ind, ty, name):
    """A declaration for a split parameter's second range, built from the parameter's own type."""
    core = re.sub(r"\s+", " ", ty).strip()
    return "%s%s%s%s;" % (ind, core, "" if core.endswith("*") else " ", name)


def decl_block_end(fn):
    """(line, indent) after the CONTIGUOUS run of single-line top-level declarations - where a new
    local may be declared.  Not the LAST line `fn.decls` names: `DECL_RE` reads `D_800CF828[0] = 1;`
    as a declaration (`_is_typename` accepts any capitalised word), so that line can sit past real
    code, and an insertion after it lands in the middle of the body."""
    top = min((n.depth for n in fn.nodes), default=0)
    decl_nodes = {x["node"] for ds in fn.decls.values() for x in ds}
    last, ind = fn.lo - 1, "    "
    for n in fn.nodes:
        if n.depth != top or n.i not in decl_nodes or len(n.lines) != 1:
            break
        last = n.line
        ind = re.match(r"[ \t]*", fn.lines[n.line]).group(0) or "    "
    return last, ind


def _decl_line(d, name):
    """A fresh declaration built from the original declaration text: qualifiers cannot drift."""
    core = d["decl_text"].strip()
    return d["ind"] + core + ("" if d["stars"] else " ") + name + ";"


def _fresh(text, base):
    for k in itertools.count(2):
        name = "%s_%d" % (base, k)
        if not re.search(r"\b" + re.escape(name) + r"\b", text):
            return name
        if k > 40:
            return None


def _cap(scored, focus):
    """Deduplicate, put the focus first, keep at most CAP."""
    scored.sort(key=lambda z: z[0])
    out, seen = [], set()
    for _, label, cand in scored:
        if cand in seen:
            continue
        seen.add(cand)
        out.append((label, cand))
        if len(out) >= CAP:
            break
    return out


def _focus_key(focus, names):
    return 0 if focus and focus in names else 1


# --------------------------------------------------------------------------- inline_def

def _rhs_of(fn, node, v):
    """The defining expression at `node`: `v = E;` or the initialiser of `v`'s own declaration."""
    if len(fn.nodes[node].lines) != 1:
        return None              # a wrapped definition: its spans do not index one physical line
    if any(x["node"] == node and x["init"] for x in fn.decls.get(v, [])):
        return decl_init(fn, v, node)
    m = re.match(r"^\s*(?<![\w.])" + re.escape(v) + r"\s*=(?!=)\s*(?P<rhs>.*?);\s*$", fn.nodes[node].masked)
    if not m:
        return None
    real = _nl(fn.lines[fn.nodes[node].line])
    return real[m.start("rhs"):m.end("rhs")].strip()


def _operands(expr):
    return {x for x in re.findall(ID, expr) if x not in C_KEYWORDS}


CAST_RE = re.compile(r"\(\s*(?:(?:struct|union|enum|const|volatile|unsigned|signed)\s+)*"
                     + ID + r"(?:\s*\*)*\s*\)")


def _reads_memory(expr):
    """A dereference, member or index in `expr` - the `*` of a CAST is not one."""
    return bool(re.search(r"->|\[|(?<![\w)])\*|(?<=\w)\.\w", CAST_RE.sub(" ", expr)))


def _substitution(use_masked, span, ty, rhs):
    """The text that replaces one occurrence of V: t51's cast rule, plus cast subsumption."""
    before = use_masked[:span[0]]
    tyn = re.sub(r"\s+", "", ty)
    inner = None
    m = re.match(r"^\(\s*(?P<t>[^()]*)\)\s*(?P<rest>.*)$", rhs, re.S)
    if m and re.sub(r"\s+", "", m.group("t")) == tyn:
        inner = m.group("rest").strip()
    outer_cast = bool(re.search(r"\(\s*(?:(?:struct|union|const|volatile|unsigned|signed)\s+)*"
                                + ID + r"\s*\*\s*\)\s*$", before))
    if inner is not None and outer_cast and tyn.endswith("*"):
        return inner if _term(inner) else "(" + inner + ")"
    if inner is not None:
        return rhs if _term(rhs) else "(" + rhs + ")"
    if outer_cast and tyn.endswith("*"):
        return "((" + ty + ")(" + rhs + "))"
    return "((" + ty + ")(" + rhs + "))"


def _inline_one(fn, v, d, kinds, ds, us, skips):
    """Text edits for inlining the definitions `ds` of one web at the uses `us` (or None)."""
    rhss = {}
    for node in ds:
        if kinds[node] != "plain":
            skips["inline:rmw-def"] += 1
            return None
        rhs = _rhs_of(fn, node, v)
        if rhs is None:
            skips["inline:not-a-plain-assignment"] += 1
            return None
        if CALL_RE.search(rhs) or re.search(r"\+\+|--", rhs) or "volatile" in rhs \
                or occ_re(v).search(rhs) or "?" in rhs:
            skips["inline:unsafe-rhs"] += 1
            return None
        if len(fn.m[fn.nodes[node].line].strip().rstrip(";")) == 0:
            return None
        rhss[node] = rhs
    if len({rhss[n] for n in ds}) != 1:
        skips["inline:multi-def-web"] += 1
        return None
    rhs = rhss[ds[0]]
    uses = [u for u in us if u not in ds]
    if not uses:
        skips["inline:no-use"] += 1
        return None
    for u in uses:
        if fn.nodes[u].joined.startswith("ASM_"):
            skips["inline:use-in-pin"] += 1
            return None
        if fn.nodes[u].kind in ("unknown", "decl"):
            skips["inline:use-on-unknown-node"] += 1
            return None
        if len(fn.nodes[u].lines) != 1:
            skips["inline:use-on-a-wrapped-statement"] += 1
            return None         # the substitution indexes `masked`, which is one physical line
    # region: the nodes on a path from a definition to a use, killed at the next definition
    forward = set()
    for d0 in ds:
        work = list(fn.nodes[d0].succ)
        while work:
            n = work.pop()
            if n in forward:
                continue
            forward.add(n)
            if kinds.get(n) in ("plain", "rmw"):
                continue                       # the definition kills v
            work.extend(fn.nodes[n].succ)
    pred = collections.defaultdict(list)
    for n in forward:
        for s in fn.nodes[n].succ:
            if s in forward:
                pred[s].append(n)
    region, work = set(uses), list(uses)
    while work:                                # only what actually lies between a def and a use
        n = work.pop()
        for p in pred.get(n, ()):
            if p not in region:
                region.add(p)
                work.append(p)
    ops = _operands(rhs)
    mem = _reads_memory(rhs)
    for n in sorted(region - set(ds)):
        node = fn.nodes[n]
        if n in uses:
            m = re.match(r"^\s*(?P<lhs>[^=;]*?)=(?!=)", node.joined)
            if m and m.group("lhs").strip() in ops and occ_re(v).search(node.joined[m.end():]):
                continue
        for o in ops:
            if write_re(o).search(node.joined):
                skips["inline:operand-clobbered"] += 1
                return None
        if mem and n not in uses:
            if CALL_RE.search(node.joined):
                skips["inline:call-between"] += 1
                return None
            am = re.match(r"^\s*(?P<lhs>[^=;]*?)=(?!=)", node.joined)
            if am and not re.fullmatch(ID, am.group("lhs").strip()):
                skips["inline:store-between"] += 1
                return None
    ty = (d["decl_text"].strip().replace("register ", "").strip())
    edits, drops = {}, set()
    for u in uses:
        node = fn.nodes[u]
        real = _nl(fn.lines[node.line])
        for a, b in reversed(occ_spans(node.masked, v)):
            sub = _substitution(node.masked, (a, b), ty, rhs)
            real = real[:a] + sub + real[b:]
        edits[node.line] = real
    for node in ds:
        drops.add(fn.nodes[node].line)
    return edits, drops


def inline_def_candidates(text, focus=None, skips=None):
    """A local's definition web substituted at the uses it alone reaches; `:all` does every web."""
    skips = collections.Counter() if skips is None else skips
    scored = []
    for fn in functions(text, skips):
        locs = usable_locals(fn, skips, allow_init=True)
        for v, d in sorted(locs.items()):
            kinds = fn.kinds(v)
            if not kinds:
                continue
            if _multi_occurrence(fn, v, kinds):
                skips["inline:multi-occurrence-node"] += 1
                continue
            ws = webs(fn, v, kinds)
            if any(w[2] for w in ws):
                skips["inline:back-edge"] += 1
                continue
            per_web = []
            for wi, (ds, us, _) in enumerate(ws):
                if not ds:
                    continue
                got = _inline_one(fn, v, d, kinds, ds, us, skips)
                if got is None:
                    continue
                per_web.append((wi, ds, got))
            ndefs = sum(1 for k in kinds.values() if k in ("plain", "rmw"))
            for wi, ds, (edits, drops) in per_web:
                dead = len(drops) == ndefs
                if d["init"] and d["node"] in ds and not dead:
                    skips["inline:partial-web-on-an-initialised-declaration"] += 1
                    continue
                cand = _apply(text, edits, drops | ({d["line"]} if dead else set()))
                scored.append(((_focus_key(focus, {v}), abs(fn.nodes[ds[0]].line), v, wi),
                               "inline_def:%s@%d" % (v, fn.nodes[ds[0]].line + 1), cand))
            if len(per_web) == len(ws) and len(per_web) > 1:
                edits, drops = {}, set()
                clash = False
                for _, _, (e, dr) in per_web:
                    if set(e) & set(edits) or dr & drops:
                        clash = True
                    edits.update(e)
                    drops |= dr
                if not clash:
                    scored.append(((_focus_key(focus, {v}), -1, v, -1),
                                   "inline_def:all:%s" % v, _apply(text, edits, drops | {d["line"]})))
    return _cap(scored, focus)


# --------------------------------------------------------------------------- split_def

def split_def_candidates(text, focus=None, skips=None):
    """One definition web renamed to a fresh `V_2`; `:all` splits every admissible web.

    PER WEB, NOT PER VARIABLE.  Round 65 refused the whole variable when ANY of its webs was
    degenerate or crossed a back edge, and town/func_8081A100's `element` has a `default:` arm whose
    use no definition reaches - so its three clean loop ranges were never offered at all.  A web is
    closed under reaching definitions: every definition in it reaches only uses in it and every use
    in it is reached only by definitions in it, so renaming one web cannot change what another web
    means.  Only the web being renamed has to qualify.

    PARAMETERS split too (`usable_params`): their first web is the one the implicit entry definition
    reaches, which has no definition node and is therefore skipped like any degenerate web, and the
    new range's declaration goes at the end of the declaration block.
    """
    skips = collections.Counter() if skips is None else skips
    scored = []
    for fn in functions(text, skips):
        locs = usable_locals(fn, skips, allow_init=True)
        params = usable_params(fn, skips)
        end, ind = decl_block_end(fn)
        for v in sorted(set(locs) | set(params)):
            d = locs.get(v)
            kinds = fn.kinds(v)
            if not kinds:
                continue
            if _multi_occurrence(fn, v, kinds):
                skips["split:multi-occurrence-node"] += 1
                continue
            ws = webs(fn, v, kinds)
            if len(ws) < 2:
                skips["split:single-web"] += 1
                continue
            name = _fresh(text, v)
            if name is None:
                skips["split:no-fresh-name"] += 1
                continue

            def declare(nm):
                return (_decl_line(d, nm) if d is not None else _param_decl(ind, params[v], nm))

            at = d["line"] if d is not None else end
            ok_webs = []
            for wi, (ds, us, back) in enumerate(ws):
                if not ds:
                    skips["split:web-without-def"] += 1      # only THIS web, never the variable
                    continue
                if back:
                    skips["split:web-crosses-a-back-edge"] += 1
                    continue
                if wi == 0:
                    skips["split:first-web-keeps-the-name"] += 1
                    continue
                ok_webs.append((wi, ds, us))
            for wi, ds, us in ok_webs:
                edits = {}
                for n in sorted(set(ds) | set(us)):
                    _rename_node(fn, n, v, name, edits)
                if not edits:
                    continue
                cand = _apply(text, edits, (), {at: [declare(name)]})
                scored.append(((_focus_key(focus, {v}), fn.nodes[ds[0]].line, v, wi),
                               "split_def:%s>%s@%d" % (v, name, fn.nodes[ds[0]].line + 1), cand))
            # every admissible web gets its own name
            edits, decls, k, ok = {}, [], 2, True
            for wi, ds, us in ok_webs:
                nm = "%s_%d" % (v, k)
                k += 1
                if re.search(r"\b" + re.escape(nm) + r"\b", text):
                    ok = False
                    break
                decls.append(declare(nm))
                for n in sorted(set(ds) | set(us)):
                    _rename_node(fn, n, v, nm, edits)
            if ok and edits and len(ok_webs) > 1:
                scored.append(((_focus_key(focus, {v}), -1, v, -1), "split_def:all:%s" % v,
                               _apply(text, edits, (), {at: decls})))
    return _cap(scored, focus)


# --------------------------------------------------------------------------- merge_local

def _same_type(a, b):
    norm = lambda d: re.sub(r"\s+", " ", d["decl_text"].replace("register", "").strip()) + d["stars"]
    return norm(a) == norm(b)


def _interfere(fn, kinds_a, kinds_b, entry_a=False, entry_b=False):
    """Chaitin interference between two value sets on the CFG.

    Two variables may share one name only when no point of the program needs both values.  Live-in
    and live-out overlap is the obvious half; the half round 28's first cut missed is the
    DEFINITION edge - a definition of `a` at a node where `b` is still live OUT overwrites `b`'s
    value even though `b` is not live IN at that node (it is dead there only on the path that
    reaches the definition).  Without it

        a = 1; if (arg) goto mid; b = 2; r = b; mid: r = a;

    merged `a` into `r`, and the `arg == 0` path then read 2 where the original read 1.
    `entry_a` / `entry_b` add the implicit definition a parameter carries at the entry node.
    """
    lia, loa = liveness(fn, None, kinds_a)
    lib, lob = liveness(fn, None, kinds_b)
    for i in range(len(fn.nodes)):
        if (lia[i] and lib[i]) or (loa[i] and lob[i]):
            return True
        da = kinds_a.get(i) in ("plain", "rmw")
        db = kinds_b.get(i) in ("plain", "rmw")
        if (da and lob[i]) or (db and loa[i]):
            return True
    if fn.nodes:
        if entry_a and lib[0]:
            return True
        if entry_b and lia[0]:
            return True
    return False


def _disjoint(fn, kinds_a, kinds_b):
    return not _interfere(fn, kinds_a, kinds_b)


def merge_local_candidates(text, focus=None, skips=None, allow_init=False):
    """Two same-type locals with disjoint CFG live ranges, merged in both naming directions.

    `allow_init` (default False, the behaviour every existing caller keeps) passes straight through
    to `usable_locals`: an INITIALISED declaration - `S *alias = obj;`, m2c's own typed-alias shape -
    then becomes a merge candidate instead of counting `initialised-decl`.  It is off by default
    because the merge DELETES the guest's declaration line, initialiser and all: with it on, the
    caller owns the two shapes that deletion can break - a guest whose initialiser is not the host
    (the definition is lost) and a host whose initialiser READS the guest (the line becomes
    `T host = host;`).  `tools/lanes/perturb_struct.merge` is the caller that turns it on, and it
    refuses both from the candidate text (`merge:init-lost`, `merge:self-initialised-declaration`).
    """
    skips = collections.Counter() if skips is None else skips
    scored = []
    for fn in functions(text, skips):
        locs = usable_locals(fn, skips, allow_init=allow_init)
        kinds = {v: fn.kinds(v) for v in locs}
        for a, b in itertools.combinations(sorted(locs), 2):
            da, db = locs[a], locs[b]
            if not _same_type(da, db):
                continue
            if da["depth"] != db["depth"]:
                skips["merge:different-block"] += 1
                continue
            if not kinds[a] or not kinds[b]:
                skips["merge:unused-local"] += 1
                continue
            if not _disjoint(fn, kinds[a], kinds[b]):
                skips["merge:live-ranges-overlap"] += 1
                continue
            for host, guest in ((a, b), (b, a)):
                gd = locs[guest]
                edits = {}
                for n in sorted(kinds[guest]):
                    _rename_node(fn, n, guest, host, edits)
                extra = _drop_self_copies(fn, edits, skips, "merge")
                if extra is None:
                    continue
                cand = _apply(text, edits, {gd["line"]} | extra)
                scored.append(((_focus_key(focus, {a, b}), abs(da["line"] - db["line"]), guest, host),
                               "merge_local:%s>%s" % (guest, host), cand))
    return _cap(scored, focus)


# --------------------------------------------------------------------------- merge_param

def merge_param_candidates(text, focus=None, skips=None, allow_init=False):
    """A local merged into a same-type dead parameter, and the `usecopy` reverse direction.

    `allow_init`: see `merge_local_candidates` - the same keyword, the same default, passed through
    to `usable_locals` and nothing else.  Direction (1) deletes the local's declaration, so the same
    caller-side refusals apply; the `usecopy` direction deletes nothing.
    """
    skips = collections.Counter() if skips is None else skips
    scored = []
    for fn in functions(text, skips):
        locs = usable_locals(fn, skips, allow_init=allow_init)
        if not fn.nodes:
            continue
        body = "\n".join(fn.m[fn.lo:fn.hi])
        for p, pty in fn.params:
            if not re.fullmatch(ID, p) or p in C_KEYWORDS:
                continue
            if re.search(r"(?:^|[^\w)\]&])&[ \t]*" + re.escape(p) + r"\b", body, re.M):
                skips["param:address-taken"] += 1
                continue
            pkinds = fn.kinds(p)
            pplaced, pstray = fn.occurrences(p)
            if pstray or any(fn.pp[ln] for _, ln, _ in pplaced):
                skips["param:off-cfg-or-pp"] += 1
                continue
            ptype = re.sub(r"\s+", " ", pty.strip())
            for v, d in sorted(locs.items()):
                vkinds = fn.kinds(v)
                if not vkinds:
                    continue
                dtype = re.sub(r"\s+", " ", d["decl_text"].replace("register", "").strip())
                if re.sub(r"\s*\*\s*", "*", ptype) != re.sub(r"\s*\*\s*", "*", dtype):
                    continue
                # (1) the local becomes the parameter: the parameter must be dead wherever v lives.
                # The parameter carries an implicit definition at the entry node (entry_b below).
                first_def = min((i for i, k in vkinds.items() if k in ("plain", "rmw")), default=None)
                if first_def is None:
                    skips["param:local-never-defined"] += 1
                elif _interfere(fn, vkinds, pkinds, entry_b=True):
                    skips["param:live-ranges-overlap"] += 1
                elif any(k in ("plain", "rmw") for k in pkinds.values()):
                    skips["param:parameter-reassigned"] += 1
                else:
                    edits = {}
                    for n in sorted(vkinds):
                        _rename_node(fn, n, v, p, edits)
                    extra = _drop_self_copies(fn, edits, skips, "param")
                    if extra is not None:
                        scored.append(((_focus_key(focus, {v, p}), d["line"], v, p),
                                       "merge_param:%s>%s" % (v, p),
                                       _apply(text, edits, {d["line"]} | extra)))
                # (2) usecopy: `v = p;` is v's only definition -> later uses of p become v
                defs = [i for i, k in vkinds.items() if k in ("plain", "rmw")]
                if len(defs) != 1 or vkinds[defs[0]] != "plain":
                    continue
                if _rhs_of(fn, defs[0], v) != p:
                    continue
                if any(k in ("plain", "rmw") for k in pkinds.values()):
                    skips["usecopy:parameter-reassigned"] += 1
                    continue
                copy = defs[0]
                # A use of `p` may become `v` only when EVERY path from the entry to that use runs
                # through the copy.  Walking forward from the copy instead (round 28's first cut)
                # follows back edges, so in
                #     i = 0; loop: r = p; v = p; i = i + 1; if (i < 3) goto loop;
                # the `r = p` above the copy counted as "later" and was rewritten to read `v`
                # before `v` was ever assigned.  The entry walk below cannot say that: it stops at
                # the copy node, so anything reachable around the back edge is refused.
                pre = set()
                work = [0]
                while work:
                    n = work.pop()
                    if n in pre or n == copy:
                        continue
                    pre.add(n)
                    work.extend(fn.nodes[n].succ)
                if any(i in pre for i in pkinds if i != copy):
                    skips["usecopy:parameter-used-before-copy"] += 1
                    continue
                later = [i for i in pkinds if i != copy]
                if not later:
                    skips["usecopy:no-later-parameter-use"] += 1
                    continue
                edits = {}
                for n in sorted(later):
                    _rename_node(fn, n, p, v, edits)
                scored.append(((_focus_key(focus, {v, p}), fn.nodes[copy].line, p, v),
                               "merge_param:usecopy:%s>%s" % (p, v), _apply(text, edits)))
    return _cap(scored, focus)


# --------------------------------------------------------------------------- retype_ptr

CAST_TAIL_RE = re.compile(r"\(\s*(?:struct\s+)?(?P<s>" + ID + r")\s*\*\s*\)\s*$")


def retype_ptr_candidates(text, focus=None, skips=None):
    """An untyped pointer local whose every dereference casts it to one struct pointer type."""
    skips = collections.Counter() if skips is None else skips
    scored = []
    for fn in functions(text, skips):
        locs = usable_locals(fn, skips)
        for v, d in sorted(locs.items()):
            ty = re.sub(r"\s+", " ", d["decl_text"].replace("register ", "").strip())
            ty = re.sub(r"\s*\*\s*", " *", ty).strip()
            if not d["stars"] or re.sub(r"\s+", " ", ty) not in RETYPABLE:
                skips["retype:not-an-untyped-pointer"] += 1
                continue
            placed, stray = fn.occurrences(v)
            if stray:
                continue
            targets, bad = set(), False
            hits = []
            for i, ln, spans in placed:
                if ln == d["line"]:
                    continue
                s = fn.m[ln]
                for a, b in spans:
                    before, after = s[:a], s[b:]
                    mm = CAST_TAIL_RE.search(before)
                    if mm and re.match(r"^\s*\)\s*(?:->|\.)", after) \
                            and before[:mm.start()].rstrip().endswith("("):
                        targets.add(mm.group("s"))
                        hits.append((ln, mm.start(), b, mm.group("s")))
                        continue
                    # a plain copy, argument or assignment target is fine; arithmetic is not
                    if re.search(r"[\[\+\-]\s*$", before) or after.lstrip()[:1] in ("[", "+", "-"):
                        bad = True
                        continue
                    if re.match(r"^\s*(?:=(?!=)|,|\)|;|\}|\?|:|==|!=)", after) or not after.strip():
                        continue
                    bad = True
            if bad:
                skips["retype:arithmetic-or-index"] += 1
                continue
            if len(targets) != 1 or not hits:
                skips["retype:not-one-struct-type"] += 1
                continue
            s = targets.pop()
            newty = s + " *"
            edits, broken = {}, False
            for line, a, b, _ in sorted(hits, reverse=True):
                cur = edits.get(line, _nl(fn.lines[line]))
                # `((S *)v)->f` -> `v->f`: drop the cast AND the parenthesis pair around it
                mstr = fn.m[line]
                open_paren = mstr.rfind("(", 0, a)
                close = mstr.find(")", b)
                if open_paren < 0 or close < 0 or open_paren >= a:
                    broken = True
                    break
                edits[line] = cur[:open_paren] + v + cur[close + 1:]
            if broken or not edits:
                skips["retype:unbalanced"] += 1
                continue
            dl = _nl(fn.lines[d["line"]])
            dm = DECL_RE.match(fn.m[d["line"]])
            newdecl = dl[:dm.start("prefix")] + \
                (("register " if d["register"] else "") + newty).replace("  ", " ") + \
                dl[dm.start("var"):]
            edits[d["line"]] = newdecl
            scored.append(((_focus_key(focus, {v}), d["line"], v, s),
                           "retype_ptr:%s>%s" % (v, s), _apply(text, edits)))
    return _cap(scored, focus)


# --------------------------------------------------------------------------- the menu

MOVES = (inline_def_candidates, split_def_candidates, merge_local_candidates,
         merge_param_candidates, retype_ptr_candidates)
MOVE_NAMES = tuple(f.__name__.removesuffix("_candidates") for f in MOVES)


def candidates(text, focus=None, skips=None):
    """Every varset move, round-robin across the five families so none starves the others."""
    skips = collections.Counter() if skips is None else skips
    groups = []
    for f in MOVES:
        try:
            groups.append(f(text, focus, skips))
        except Exception as e:                  # a move's bug costs only its own candidates
            skips["error:" + f.__name__ + ":" + type(e).__name__] += 1
            groups.append([])
    out, seen = [], {text}
    for batch in itertools.zip_longest(*groups):
        for item in batch:
            if item and item[1] not in seen:
                seen.add(item[1])
                out.append(item)
    return out
