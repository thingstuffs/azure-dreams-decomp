"""T21: m2c's cross-jump goto undone - every arm makes its own call again.

APPEARS     gcc's post-reload jump pass (toplev.c: jump_optimize(insns, 1, 1, 0), cross-jumping on)
            merges two identical instruction tails - the programmer's two copies of
            `sprite->anim = TABLE; func_80047784(sprite, TABLE[dir], 0);` - into one, and m2c renders
            the merge as `goto L;` into the sibling arm, with the arms' values carried across the
            label in shared function-scope variables.  Those shared variables are what cost the
            match: a pointer set in two arms is a global quantity, not a block-local one, so local-alloc
            cannot give it retail's register - and the decompiler pinned it (`register u8 *anim_table
            ASM_REG("$5")`).  The same merge shows as `P = X; break;` in switch cases and as `P = X;` at
            the end of if/else arms, followed by the one shared store + call after the join.
RESOLVES    work/native_lane/func_8098D5A8/REPORT.md, "Generator": T1 + T2, statement level.
            sink    each predecessor of the join (a `goto L`, an if/else arm, a switch `break`) gets its
                    own copy of the tail after L (to the next label, or on to the exit), with the exit
                    that keeps its continuation (`return;`, `goto M;`, or nothing when the structured
                    continuations agree); L goes once nothing jumps there (an `&&L` keeps it).
            fsub    in the rewritten arms, every temporary whose `v = E;` reaches exactly one use is
                    forward-substituted into that use (expression form - one variable per value is
                    not equivalent, REPORT v8), `v = X; v = f(v);` folds to `f(X)`, `*&X[i]` to `X[i]`.
            t1      the pinned pointer's link-time-constant (or plain-copy) definitions are substituted
                    into every use each one reaches; all-or-nothing: the defs, the declaration and its
                    pin go only when no mention of P is left.
            erase   when t1 cannot take P, the pin alone is erased from the rewritten text.
            idx     `*(u8 *)(i + (u32)SYM)` spelled `SYM[i]` where SYM is a u8 array (tried first: the
                    simplest spelling that matches wins).
            host    (work/native_lane/family17/REPORT.md, "Generator") when sink+erase comes within
                    T21_HOST_MAX words: the misplaced register is the compiler temporary feeding the
                    erased variable, which inherits a dying hard register's suggestion in combine_regs.
                    The value moves into a variable local-alloc refuses - word-sized, dead at the site,
                    already assigned elsewhere, never a fresh block-local - in host order: (1) the
                    erased variable itself, `V = (K & -4) << 16; if (V == 0)` -> `V = K & -4; if ((V <<
                    16) == 0)`; (2) a local assigned earlier in the block (a single-assignment
                    block-local feeding V renamed to it, a test `if (!(V & 8))` or `V &= 8; ... if (!V)`
                    written `H = V & 8; if (H == 0)`, an operand of V's assignment hoisted); (3) any
                    other such local; (4) V retyped s32 with `&=`.  Every copy the sink made is
                    rewritten alike; every small-residue erase candidate is a starting point.
            Candidates are generated cheapest-first per pin and each is scored; a candidate is accepted
            only if byte-exact with FEWER live pins and no more fences (`sites_of`, `_dowhile0`).
POPULATION  2026-09-11 census (native lane): 2,104 pointer ASM_REG pins, 128 set from a symbol >= 2
            times, 83 in files with a goto into a label whose next statement is a call (a file-level
            flag: most of those gotos are unrelated to the pin).  Eligible here: a live ASM_REG pin that
            a predecessor arm of a join defines and the join's tail reads (itself, or a value the arm
            derived from it), or that is set from a link-time constant two or more times, and none of
            whose mentions sits in a NON_MATCHING / #if 0 arm - 311 of the 1,704 pinned stock rows.
RESULT      2026-09-12.  Acceptance: from the 7 pre-images of aaa1157a the plugin reaches the landed
            text byte for byte, 2 scorer runs each (t1 alone leaves 16 words - the lane's v4).  Dry run
            over the 311 eligible rows (794 scorer runs, 158 s at 10 workers): 102 rows exact, 107 pins
            off, no fence, macro, asm or volatile added.  By shape: sink + erase (P not a constant; the
            freed value forward-substituted or kept) 40, t1 alone 21, sink + t1 24, sink of a whole
            structured tail 8, arms exchanged (research 4.1: find_cross_jump compares only against the
            block before the label) 8, sink to the exit 1.  The census's 61 goto->call rows: 28 exact,
            26 census pins.  Misses: 23 rows at 1-2 words - 17 of them one function in 17 overlays,
            where the erased variable stays live in another use - and 22 rows with no scorable
            candidate (P an ASM_KEEP argument, a non-constant definition, a use no definition reaches,
            a copy that would duplicate a volatile or a fence).  work/native_lane/crossjump/.
            host (2026-09-12, after the 102 landed in dff8c780): the 17-row family closes 17/17 from
            its current src - the 796-byte function by the split (10), the BC function by the test
            host `height_offset` (6, byte-identical to the family17 lane's hand candidates), and
            func_81085508 by an operand host (1).  Re-run over every other eligible row (208, 635 scorer
            runs): 17 exact, all of them the family.  12 other rows leave sink+erase within 4 words;
            only 3 offer a host site (8008AFEC split 3 -> 3, 800B39E4 test 1 -> 14, 800C9858 test
            2 -> 2) and none closed - the other 9 have no split/test/rename/operand shape or no
            word-sized dead host.
"""
import os, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text                      # noqa: E402
from pin_census import sites_of, arm_labels      # noqa: E402
from pin_sites import erase_many                 # noqa: E402
from census import _dowhile0                     # noqa: E402

try:
    from .t12_stmtorder import mask
    from . import natural as N
except ImportError:                              # pragma: no cover - direct import
    from t12_stmtorder import mask
    import natural as N

BUDGET = int(os.environ.get("T21_BUDGET", "16"))          # scorer runs per row
PIN_BUDGET = int(os.environ.get("T21_PIN_BUDGET", "10"))  # scorer runs per pin
MARK = "/*@t21@*/"

ID = r"[A-Za-z_]\w*"
ID_RE = re.compile(ID)
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)[uUlL]*"
KW = {"if", "else", "switch", "while", "for", "do", "goto", "return", "break", "continue", "case",
      "default", "sizeof"}
DECL_RE = re.compile(
    r"^(?:(?:register|const|static|volatile|unsigned|signed|struct|union|enum|extern)\s+)*%s"
    r"(?:\s+(?:const|volatile))?(?:\s*\*+\s*(?:(?:const|volatile)\s+)?|\s+)(?:\*+\s*)?%s\s*"
    r"(?:\[[^\]]*\]\s*)*(?:=|;|,|ASM_REG)" % (ID, ID), re.S)
EXITS = ("return", "goto", "break", "continue", "cgoto")
END = ("END",)


# ------------------------------------------------------------------------------ parser

class ParseError(Exception):
    pass


class Node:
    __slots__ = ("kind", "s", "e", "kids", "name", "then", "els", "body", "hdr", "parent", "idx")

    def __init__(self, kind, s, e=None):
        self.kind, self.s, self.e = kind, s, e
        self.kids, self.name, self.then, self.els, self.body, self.hdr = [], None, None, None, None, None
        self.parent, self.idx = None, None

    def children(self):
        if self.kind == "block":
            return self.kids
        return [c for c in (self.then, self.els, self.body) if c is not None]

    def walk(self):
        yield self
        for c in self.children():
            yield from c.walk()

    def __repr__(self):                          # pragma: no cover - debugging aid
        return "<%s %d-%s %s>" % (self.kind, self.s, self.e, self.name or "")


class Parser:
    """A statement parser for m2c-style C over the masked text (comments/strings blanked)."""

    def __init__(self, m):
        self.m, self.n = m, len(m)

    def ws(self, i):
        m, n = self.m, self.n
        while i < n and m[i] in " \t\r\n\f\v":
            i += 1
        return i

    def _line_head(self, i):
        return not self.m[self.m.rfind("\n", 0, i) + 1:i].strip()

    def _paren(self, i):
        if i >= self.n or self.m[i] != "(":
            raise ParseError("expected (")
        d = 0
        for k in range(i, self.n):
            c = self.m[k]
            if c in "([{":
                d += 1
            elif c in ")]}":
                d -= 1
                if d == 0:
                    return k
        raise ParseError("unbalanced (")

    def _semi(self, i):
        d = 0
        for k in range(i, self.n):
            c = self.m[k]
            if c in "([{":
                d += 1
            elif c in ")]}":
                d -= 1
                if d < 0:
                    raise ParseError("unbalanced before ;")
            elif c == ";" and d == 0:
                return k + 1
            elif c == "#" and self._line_head(k):
                raise ParseError("directive inside a statement")
        raise ParseError("no ;")

    def _colon(self, i):
        d = 0
        for k in range(i, self.n):
            c = self.m[k]
            if c in "([":
                d += 1
            elif c in ")]":
                d -= 1
            elif c == ":" and d == 0:
                return k + 1
            elif c in ";{}":
                break
        raise ParseError("case without :")

    def _sub(self, parent, i, slot):
        st, e = self.stmt(i)
        st.parent = parent
        setattr(parent, slot, st)
        return e

    def block(self, i):
        node = Node("block", i)
        j = i + 1
        while True:
            j = self.ws(j)
            if j >= self.n:
                raise ParseError("eof in block")
            if self.m[j] == "}":
                node.e = j + 1
                return node, node.e
            st, j = self.stmt(j)
            st.parent, st.idx = node, len(node.kids)
            node.kids.append(st)

    def stmt(self, i):
        m = self.m
        i = self.ws(i)
        if i >= self.n:
            raise ParseError("eof")
        c = m[i]
        if c == "#" and self._line_head(i):
            e = i
            while True:
                le = m.find("\n", e)
                le = self.n if le < 0 else le
                if m[e:le].rstrip().endswith("\\"):
                    e = le + 1
                    continue
                return Node("pp", i, le), le
        if c == "{":
            return self.block(i)
        if c == ";":
            return Node("empty", i, i + 1), i + 1
        mm = ID_RE.match(m, i)
        w = mm.group(0) if mm else None
        if w == "if":
            j = self.ws(mm.end())
            k = self._paren(j)
            node = Node("if", i)
            node.hdr = (j + 1, k)
            e = self._sub(node, k + 1, "then")
            j2 = self.ws(e)
            m2 = ID_RE.match(m, j2)
            if m2 and m2.group(0) == "else":
                e = self._sub(node, m2.end(), "els")
            node.e = e
            return node, e
        if w in ("while", "switch", "for"):
            j = self.ws(mm.end())
            k = self._paren(j)
            node = Node(w, i)
            node.hdr = (j + 1, k)
            node.e = self._sub(node, k + 1, "body")
            return node, node.e
        if w == "do":
            node = Node("do", i)
            e = self._sub(node, mm.end(), "body")
            j = self.ws(e)
            m2 = ID_RE.match(m, j)
            if not m2 or m2.group(0) != "while":
                raise ParseError("do without while")
            j = self.ws(m2.end())
            k = self._paren(j)
            node.hdr = (j + 1, k)
            j = self.ws(k + 1)
            if m[j:j + 1] != ";":
                raise ParseError("do-while without ;")
            node.e = j + 1
            return node, node.e
        if w == "goto":
            j = self.ws(mm.end())
            if m[j:j + 1] == "*":
                e = self._semi(j)
                return Node("cgoto", i, e), e
            m2 = ID_RE.match(m, j)
            if not m2:
                raise ParseError("goto")
            e = self.ws(m2.end())
            if m[e:e + 1] != ";":
                raise ParseError("goto without ;")
            node = Node("goto", i, e + 1)
            node.name = m2.group(0)
            return node, e + 1
        if w in ("return", "break", "continue"):
            e = self._semi(mm.end())
            return Node(w, i, e), e
        if w in ("case", "default"):
            e = self._colon(mm.end())
            return Node("case", i, e), e
        if w and w not in KW:
            j = self.ws(mm.end())
            if m[j:j + 1] == ":" and m[j + 1:j + 2] != ":":
                node = Node("label", i, j + 1)
                node.name = w
                return node, j + 1
        e = self._semi(i)
        node = Node("simple", i, e)
        if DECL_RE.match(m[i:e]) and (w not in KW):
            node.kind = "decl"
        return node, e


def _functions(m):
    """[(header start, body Node or None)] for every function definition in the masked text."""
    out, d, i, n = [], 0, 0, len(m)
    hdr = 0
    while i < n:
        c = m[i]
        if c == "#" and not m[m.rfind("\n", 0, i) + 1:i].strip():
            le = m.find("\n", i)
            i = n if le < 0 else le
            continue
        if c == "{":
            if d == 0:
                j = i - 1
                while j >= 0 and m[j] in " \t\r\n":
                    j -= 1
                if j >= 0 and m[j] == ")":
                    try:
                        body, e = Parser(m).block(i)
                    except ParseError:
                        body, e = None, None
                    if body is not None:
                        out.append((hdr, body))
                        i, hdr = e, e
                        continue
            d += 1
        elif c == "}":
            d -= 1
            if d == 0:
                hdr = i + 1
        elif c == ";" and d == 0:
            hdr = i + 1
        i += 1
    return out


# ------------------------------------------------------------------------------ text plumbing

def _ls(t, i):
    return t.rfind("\n", 0, i) + 1


def _le(t, i):
    j = t.find("\n", i)
    return len(t) if j < 0 else j


def _indent(t, i):
    ls = _ls(t, i)
    head = t[ls:i]
    return head if not head.strip() else re.match(r"[ \t]*", t[ls:]).group(0)


def _own_line(t, m, s, e):
    """(start, end) covering the node's whole line(s) when nothing else shares them, else None."""
    ls, le = _ls(t, s), _le(t, e)
    if m[ls:s].strip() or m[e:le].strip():
        return None
    return ls, min(le + 1, len(t))


def _apply(t, edits):
    """Edits [(s, e, new)] applied last-first; overlapping edits are an error (None)."""
    edits = sorted(edits, key=lambda x: (x[0], x[1]))
    for a, b in zip(edits, edits[1:]):
        if b[0] < a[1]:
            return None
    for s, e, new in reversed(edits):
        t = t[:s] + new + t[e:]
    return t


def _occ_re(name):
    """A variable mention: not a member (`.x`, `->x`), not a call."""
    return re.compile(r"(?<![\w.])(?<!->)%s\b(?![ \t]*\()" % re.escape(name))


def _match_paren(s, i, o="(", c=")"):
    d = 0
    for k in range(i, len(s)):
        if s[k] == o:
            d += 1
        elif s[k] == c:
            d -= 1
            if d == 0:
                return k
    return None


def _strip_parens(e):
    e = e.strip()
    while e.startswith("(") and _match_paren(e, 0) == len(e) - 1:
        e = e[1:-1].strip()
    return e


def _is_term(e):
    """A primary with postfix operators only: `x`, `3`, `a->b[i]`, `((T *)p)->f`, `(e)` - never a
    cast, a call or an operator expression."""
    e = e.strip()
    if not e:
        return False
    if re.fullmatch(NUM, e):
        return True
    if e[0] == "(":
        c = _match_paren(e, 0)
        if c is None:
            return False
        k = c + 1
    else:
        mm = re.match(ID, e)
        if not mm or mm.group(0) in KW:
            return False
        k = mm.end()
    while k < len(e):
        while k < len(e) and e[k] in " \t\n":
            k += 1
        if k >= len(e):
            break
        if e.startswith("->", k) or e[k] == ".":
            k += 2 if e.startswith("->", k) else 1
            mm = re.match(r"\s*" + ID, e[k:])
            if not mm:
                return False
            k += mm.end()
        elif e[k] == "[":
            c = _match_paren(e, k, "[", "]")
            if c is None:
                return False
            k = c + 1
        else:
            return False
    return True


def _is_unary(e):
    """`&X`, `*X`, `(T *)X`, `-X`: binds tighter than any binary operator, looser than postfix."""
    e = e.strip()
    if re.match(r"^[&*!~-]\s*", e) and not e.startswith("--"):
        return _is_term(e[1:]) or _is_unary(e[1:])
    if e.startswith("("):
        k = _match_paren(e, 0)
        if k is not None and k < len(e) - 1 and re.fullmatch(r"\(\s*(?:%s\s*)+\**\s*\)" % ID, e[:k + 1]):
            rest = e[k + 1:]
            return _is_term(rest) or _is_unary(rest)
    return False


def _wrap(e, m, s, t_end):
    """E spelled for the operand position m[s:t_end] (the mention it replaces)."""
    e = e.strip()
    if _is_term(e):
        return e
    after = m[t_end:].lstrip()
    before = m[:s].rstrip()
    postfix = after[:1] in ("[", "(", ".") or after[:2] in ("->", "++", "--")
    if _is_unary(e) and not postfix:
        return e
    # a whole operand: an assignment's right side, an argument, a return value, an index, or a
    # mention already wrapped in its own parentheses
    b1 = before[-1:] if before else ""
    whole_l = (b1 in ("(", ",", "[") or before.endswith("return")
               or (b1 == "=" and before[-2:-1] not in ("=", "!", "<", ">", "+", "-", "*", "/", "%", "&", "|", "^")))
    whole_r = after[:1] in (")", ",", ";", "]")
    if whole_l and whole_r and not postfix:
        return e
    return "(" + e + ")"


# ------------------------------------------------------------------------------ function model

class Fn:
    def __init__(self, text, m, hdr, body):
        self.t, self.m, self.hdr, self.body = text, m, hdr, body
        self.nodes = list(body.walk())
        self.labels = {}
        for n in self.nodes:
            if n.kind == "label":
                self.labels.setdefault(n.name, n)
        self.gotos = [n for n in self.nodes if n.kind == "goto"]
        self.addr_labels = set(re.findall(r"&&\s*(%s)" % ID, m[body.s:body.e]))
        self.params = self._params()
        self.decls = {}                      # name -> [decl nodes]
        for n in self.nodes:
            if n.kind == "decl":
                for nm in _decl_names(m[n.s:n.e]):
                    self.decls.setdefault(nm, []).append(n)
        self.bad = any(n.kind == "pp" for n in self.nodes)
        self.arrays = set(re.findall(r"^[ \t]*(?:extern[ \t]+)?(?:const[ \t]+)?%s[\w \t*]*?\b(%s)[ \t]*\["
                                     % (ID, ID), m[:body.s], re.M))

    def _params(self):
        head = self.m[self.hdr:self.body.s]
        r = head.rfind(")")
        if r < 0:
            return set()
        d, left = 0, None
        for k in range(r, -1, -1):
            if head[k] == ")":
                d += 1
            elif head[k] == "(":
                d -= 1
                if d == 0:
                    left = k
                    break
        if left is None:
            return set()
        out = set()
        for p in head[left + 1:r].split(","):
            ids = re.findall(ID, p)
            if ids and ids[-1] != "void":
                out.add(ids[-1])
        return out

    def is_local(self, name):
        return name in self.params or name in self.decls

    def txt(self, n):
        return self.t[n.s:n.e]

    def mt(self, n):
        return self.m[n.s:n.e]


def _decl_names(md):
    """Declarator names of a masked declaration statement."""
    body = md.rstrip().rstrip(";")
    parts, d, cur = [], 0, ""
    for ch in body:
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        if ch == "," and d == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    out = []
    for p in parts:
        d, cut = 0, len(p)
        for k, ch in enumerate(p):
            if ch in "([{":
                d += 1
            elif ch in ")]}":
                d -= 1
            elif ch == "=" and d == 0:
                cut = k
                break
        p = re.sub(r"ASM_REG\s*\([^)]*\)", " ", p[:cut])
        p = re.sub(r"\[[^\]]*\]", " ", p)
        ids = [x for x in re.findall(ID, p) if x not in ("register", "const", "volatile", "static",
                                                          "unsigned", "signed", "struct", "union", "enum", "extern")]
        if ids:
            out.append(ids[-1])
    return out


def _var_scope(fn, v, pos):
    """(block, [shadowing blocks]) of the declaration of v visible at pos; None for a global."""
    best = None
    for d in fn.decls.get(v, []):
        b = d.parent
        if b is not None and b.s <= pos < b.e and (best is None or b.s >= best.s):
            best = b
    if best is None:
        if v in fn.params:
            return fn.body, [d.parent for d in fn.decls.get(v, []) if d.parent is not None]
        return None
    return best, [d.parent for d in fn.decls.get(v, []) if d.parent is not None and d.parent is not best
                  and best.s <= d.parent.s and d.parent.e <= best.e]


def _inside(n, anc):
    while n is not None:
        if n is anc:
            return True
        n = n.parent
    return False


def cont(n):
    """The position control reaches when statement n completes normally."""
    p = n.parent
    if p is None:
        return END
    if p.kind == "block":
        if n.idx + 1 < len(p.kids):
            return p.kids[n.idx + 1]
        return cont(p)
    if p.kind in ("if", "switch"):
        return cont(p)
    if p.kind in ("while", "for", "do"):
        return ("LOOP", id(p))
    return None


def resolve(fn, x):
    """Follow labels, blocks and gotos from a position to the statement that really runs next."""
    seen = set()
    while isinstance(x, Node):
        if id(x) in seen:
            return ("CYCLE",)
        seen.add(id(x))
        if x.kind in ("label", "case", "empty"):
            x = cont(x)
        elif x.kind == "goto":
            x = fn.labels.get(x.name)
            if x is None:
                return None
        elif x.kind == "block":
            x = x.kids[0] if x.kids else cont(x)
        elif x.kind == "return" and not fn.mt(x)[6:].strip(" \t\n;"):
            return END
        else:
            return x
    return x


def _dead_after(fn, start, v, limit=4000):
    """True when no path from position `start` reads v before overwriting it.  Conservative: a
    loop head, a computed goto, a `continue` or a directive counts as a read."""
    rx = _occ_re(v)
    work, seen, steps = [start], set(), 0
    while work:
        x = work.pop()
        steps += 1
        if steps > limit or x is None:
            return False
        if x == END:
            continue
        if isinstance(x, tuple):
            return False
        if id(x) in seen:
            continue
        seen.add(id(x))
        k = x.kind
        if k in ("label", "case", "empty"):
            work.append(cont(x))
        elif k == "goto":
            if x.name not in fn.labels:
                return False
            work.append(fn.labels[x.name])
        elif k == "break":
            o = _break_owner(x)
            if o is None:
                return False
            work.append(cont(o))
        elif k in ("cgoto", "continue", "pp"):
            return False
        elif k == "return":
            if rx.search(fn.mt(x)):
                return False
        elif k in ("simple", "decl"):
            mt = fn.mt(x)
            if rx.search(mt):
                d = VDEF_RE.match(mt)
                if k == "simple" and d and d.group(1) == v and d.group(2) == "=" and not [
                        y for y in rx.finditer(mt) if y.start() != d.start(1)]:
                    continue                    # overwritten before any read on this path
                return False
            work.append(cont(x))
        elif k == "block":
            work.append(x.kids[0] if x.kids else cont(x))
        elif k == "if":
            if rx.search(fn.m[x.hdr[0]:x.hdr[1]]):
                return False
            work.append(x.then)
            work.append(x.els if x.els is not None else cont(x))
        elif k in ("switch", "while", "for", "do"):
            if rx.search(fn.mt(x)):
                return False
            work.append(cont(x))
        else:
            return False
    return True


def _is_exit(n):
    return n is not None and n.kind in EXITS


def _last_stmt(n):
    """The last statement a branch runs (through nested blocks)."""
    while n is not None and n.kind == "block":
        n = n.kids[-1] if n.kids else None
    return n


def _has(n, kinds):
    return any(x.kind in kinds for x in n.walk())


# ------------------------------------------------------------------------------ pins

class Pin:
    def __init__(self, fn, site, decl, name):
        self.fn, self.site, self.decl, self.name = fn, site, decl, name
        self.reg = site[2]
        self.scope = decl.parent                      # the declaring block
        self.shadow = [b.parent for b in fn.decls.get(name, []) if b is not decl and b.parent is not None
                       and _inside(b.parent, self.scope) and b.parent is not self.scope]

    def key(self):
        return (self.name, self.reg)

    def in_scope(self, pos):
        if not (self.scope.s <= pos < self.scope.e):
            return False
        return not any(b.s <= pos < b.e for b in self.shadow)

    def mentions(self, lo=None, hi=None):
        fn = self.fn
        lo = self.scope.s if lo is None else max(lo, self.scope.s)
        hi = self.scope.e if hi is None else min(hi, self.scope.e)
        rx = _occ_re(self.name)
        return [(mm.start(), mm.end()) for mm in rx.finditer(fn.m, lo, hi)
                if self.in_scope(mm.start()) and not (self.decl.s <= mm.start() < self.decl.e)]

    def mentioned_in(self, nodes):
        return any(self.mentions(n.s, n.e) for n in nodes)


def pins_of(text):
    """[Pin] for every live ASM_REG pin that declares a single variable inside a parsed function."""
    m = mask(text)
    fns = [Fn(text, m, h, b) for h, b in _functions(m)]
    out = []
    for s in sites_of(text):
        if s[0] != "reg":
            continue
        for fn in fns:
            if not (fn.body.s <= s[3] < fn.body.e):
                continue
            decl = next((n for n in fn.nodes if n.kind == "decl" and n.s <= s[3] < n.e), None)
            if decl is None:
                break
            names = _decl_names(m[decl.s:decl.e])
            if len(names) != 1:
                break
            out.append(Pin(fn, s, decl, names[0]))
            break
    return out


# ------------------------------------------------------------------------------ joins

class Join:
    """A point where several predecessors meet before a shared tail."""

    def __init__(self, kind, anchor, preds, tail, end_kind, end, labels=()):
        self.kind, self.anchor, self.preds = kind, anchor, preds
        self.tail, self.end_kind, self.end, self.labels = tail, end_kind, end, list(labels)


def _tail(fn, blk, k, long):
    """Statements of blk from index k: (stmts, end kind, end node) or None.
       end kind: 'exit' (last stmt included is return/goto/break/continue), 'label' (bounded by the
       label/case `end`), 'block' (runs to the end of blk)."""
    stmts = []
    while k < len(blk.kids):
        s = blk.kids[k]
        if s.kind in ("label", "case"):
            if long and stmts:
                k += 1
                continue
            return stmts, "label", s
        if s.kind in ("pp", "decl"):
            return None
        if re.search(r"\bASM_[A-Z0-9_]+\s*\(", fn.m[s.s:s.e]):
            return None                          # a copy would duplicate another pin
        if s.kind not in ("simple", "empty") and s.kind not in EXITS:
            if _has(s, ("label", "case", "pp")):
                return None
        stmts.append(s)
        if s.kind in EXITS:
            return stmts, "exit", s
        k += 1
    return stmts, "block", blk


def _run_before(blk, k):
    """The straight-line statements just before index k of blk."""
    out = []
    j = k - 1
    while j >= 0 and blk.kids[j].kind in ("simple", "empty"):
        out.insert(0, blk.kids[j])
        j -= 1
    return out


def label_joins(fn, long=False):
    out = []
    seen = set()
    for n in fn.nodes:
        if n.kind != "label" or id(n) in seen or n.parent is None or n.parent.kind != "block":
            continue
        blk = n.parent
        k = n.idx
        stack = []
        while k < len(blk.kids) and blk.kids[k].kind == "label":
            stack.append(blk.kids[k])
            seen.add(id(blk.kids[k]))
            k += 1
        names = {x.name for x in stack}
        gotos = [g for g in fn.gotos if g.name in names]
        if not gotos:
            continue
        tl = _tail(fn, blk, k, long)
        if not tl or not [s for s in tl[0] if s.kind != "empty"]:
            continue
        stmts, ek, end = tl
        first = stack[0].idx
        ft = None
        if first > 0 and blk.kids[first - 1].kind not in EXITS and blk.kids[first - 1].kind not in ("label", "case"):
            ft = blk.kids[first - 1]
        if first > 0 and blk.kids[first - 1].kind in ("label", "case"):
            ft = blk.kids[first - 1]            # a case label falling in: a predecessor we cannot sink into
        out.append(Join("label", stack[-1], {"gotos": gotos, "ft": ft, "blk": blk}, stmts, ek, end, stack))
    return out


def structured_joins(fn, long=False):
    """if/else chains and switches whose arms fall into a shared tail."""
    out = []
    for n in fn.nodes:
        if n.kind not in ("if", "switch") or n.parent is None or n.parent.kind != "block":
            continue
        blk = n.parent
        tl = _tail(fn, blk, n.idx + 1, long)
        if not tl or not [s for s in tl[0] if s.kind != "empty"]:
            continue
        stmts, ek, end = tl
        if n.kind == "if":
            arms, x, has_else = [], n, False
            while True:
                arms.append(x.then)
                if x.els is None:
                    break
                if x.els.kind == "if":
                    x = x.els
                    continue
                arms.append(x.els)
                has_else = True
                break
            live = [a for a in arms if not _is_exit(_last_stmt(a))]
            if not has_else or len(live) < 2:
                continue
            out.append(Join("if", n, {"arms": live}, stmts, ek, end))
        else:
            body = n.body
            if body.kind != "block":
                continue
            brks = [b for b in body.walk() if b.kind == "break" and _break_owner(b) is n]
            ft_end = body.kids and not _is_exit(body.kids[-1]) and body.kids[-1].kind != "case"
            if len(brks) + bool(ft_end) < 2:
                continue
            out.append(Join("switch", n, {"breaks": brks, "ft_end": bool(ft_end)}, stmts, ek, end))
    return out


def _break_owner(b):
    x = b.parent
    while x is not None and x.kind not in ("switch", "while", "for", "do"):
        x = x.parent
    return x


def _pred_arms(fn, j):
    """The straight-line code each predecessor runs just before the join."""
    arms = []
    if j.kind == "label":
        for g in j.preds["gotos"]:
            if g.parent.kind == "block":
                arms.append(_run_before(g.parent, g.idx))
        ft = j.preds["ft"]
        if ft is not None and ft.kind == "simple":
            arms.append(_run_before(ft.parent, ft.idx + 1))
    elif j.kind == "if":
        for a in j.preds["arms"]:
            arms.append(_run_before(a, len(a.kids)) if a.kind == "block" else [a])
    else:
        for b in j.preds["breaks"]:
            if b.parent.kind == "block":
                arms.append(_run_before(b.parent, b.idx))
        if j.preds["ft_end"]:
            body = j.anchor.body
            arms.append(_run_before(body, len(body.kids)))
    return arms


def _arm_defs(pin, arm):
    """(P defined in the arm?, variables the arm sets from an expression that mentions P)."""
    fn, rxp = pin.fn, _occ_re(pin.name)
    defs_p, out = False, set()
    for n in arm:
        if n.kind != "simple":
            continue
        mm = VDEF_RE.match(fn.mt(n))
        if not mm:
            continue
        v, rhs = mm.group(1), fn.mt(n)[mm.end():]
        if v == pin.name and pin.in_scope(n.s):
            defs_p = True
        elif rxp.search(rhs) or any(_occ_re(d).search(rhs) for d in out):
            out.add(v)
    return defs_p, out


def relevant(pin, j):
    """The join merges values of P: a predecessor arm defines P, and the tail uses P or a value the
    arm derived from it (the lane's shape: `anim_entry = &anim_table[dir]; goto L;`)."""
    if not pin.in_scope(j.anchor.s):
        return False
    fn = pin.fn
    defs, carried = False, set()
    for a in _pred_arms(fn, j):
        d, c = _arm_defs(pin, a)
        defs |= d
        carried |= c
    if not defs:
        return False
    for s in j.tail:
        mt = fn.mt(s)
        lead = s.s + len(mt) - len(mt.lstrip())
        for a, b in pin.mentions(s.s, s.e):
            if s.kind == "simple" and a == lead and re.match(r"\s*=(?!=)", fn.m[b:s.e]):
                continue                        # `P = ...;` in the tail is a def, not a use
            return True
        if any(_occ_re(v).search(mt) for v in carried):
            return True
    return False


# ------------------------------------------------------------------------------ sink

def _render(t, nodes, ind):
    out = []
    for s in nodes:
        if s.kind == "empty":
            continue
        seg = t[s.s:s.e]
        head = t[_ls(t, s.s):s.s]
        base = head if not head.strip() else " " * len(head)
        lines = seg.split("\n")
        out.append(ind + lines[0])
        for ln in lines[1:]:
            if not ln.strip():
                out.append("")
            elif ln.startswith(base):
                out.append(ind + ln[len(base):])
            else:
                out.append(ind + "    " + ln.lstrip())
    return out


def _exit_for(fn, pred_cont, j):
    """The statement a copy needs after the tail so control leaves the way the tail did."""
    if j.end_kind == "exit":
        return ""
    if j.end_kind == "label":
        end = j.end
        nxt = cont(end)
        while isinstance(nxt, Node) and nxt.kind == "label":
            nxt = cont(nxt)
        if isinstance(nxt, Node) and nxt.kind == "return":
            return " ".join(fn.txt(nxt).split())
        if resolve(fn, pred_cont) == resolve(fn, end):
            return ""
        if end.kind == "label":
            return "goto %s;" % end.name
        return None
    target = resolve(fn, cont(j.end))
    if resolve(fn, pred_cont) == target:
        return ""
    if target == END:
        return "return;"
    if isinstance(target, Node):
        # the statement after the tail's block, reached through a label we can name?
        c = cont(j.end)
        while isinstance(c, Node) and c.kind == "block":
            c = c.kids[0] if c.kids else None
        if isinstance(c, Node) and c.kind == "label":
            return "goto %s;" % c.name
    return ""                                   # inconclusive: let the scorer decide


def sink_edits(fn, j):
    """Edits that give every predecessor of join j its own copy of the tail; None if impossible."""
    t, m = fn.t, fn.m
    edits = []
    tail = [s for s in j.tail if s.kind != "empty"]
    if j.kind == "label":
        blk = j.preds["blk"]
        keep_labels = [x for x in j.labels if x.name in fn.addr_labels]
        sunk = 0
        for g in j.preds["gotos"]:
            if g.parent is blk and g.idx + 1 == j.labels[0].idx:
                sp = _own_line(t, m, g.s, g.e) or (g.s, g.e)
                edits.append((sp[0], sp[1], ""))       # a jump to the next statement
                continue
            ex = _exit_for(fn, cont(g), j)
            if ex is None:
                return None
            if g.parent.kind == "if":                  # `if (c) goto L;`
                ind = _indent(t, g.parent.s)
                body = _render(t, tail, ind + "    ") + ([ind + "    " + ex] if ex else [])
                edits.append((g.s, g.e, "{\n" + ind + "    " + MARK + "\n" + "\n".join(body) + "\n" + ind + "}"))
            else:
                ind = _indent(t, g.s)
                sp = _own_line(t, m, g.s, g.e)
                if sp is None:
                    return None
                body = _render(t, tail, ind) + ([ind + ex] if ex else [])
                edits.append((sp[0], sp[1], ind + MARK + "\n" + "\n".join(body) + "\n"))
            sunk += 1
        ft = j.preds["ft"]
        ft_ok = ft is not None and ft.kind not in ("case", "label")
        for lab in j.labels:
            if lab in keep_labels:
                continue
            sp = _own_line(t, m, lab.s, lab.e)
            if sp is None:
                return None
            edits.append((sp[0], sp[1], (_indent(t, tail[0].s) + MARK + "\n") if ft_ok else ""))
        if not ft_ok and not keep_labels and not (ft is not None and ft.kind == "case"):
            # the original tail is now unreachable: it goes (up to the next label)
            for s in j.tail:
                if s.kind in ("label", "case"):
                    break
                sp = _own_line(t, m, s.s, s.e)
                if sp is None:
                    return None
                edits.append((sp[0], sp[1], ""))
        return edits if (sunk or edits) else None
    # structured joins: the copy goes at the end of every arm, the tail after the join goes
    moved = [s for s in j.tail]
    if j.end_kind == "label":
        pass                                          # the arms fall into the label: nothing to add
    for s in moved:
        sp = _own_line(t, m, s.s, s.e)
        if sp is None:
            return None
        edits.append((sp[0], sp[1], ""))
    if j.kind == "if":
        for a in j.preds["arms"]:
            if a.kind == "block":
                close = a.e - 1
                ind = _indent(t, a.kids[0].s) if a.kids else _indent(t, a.s) + "    "
                ls = _ls(t, close)
                if m[ls:close].strip():
                    return None
                edits.append((ls, ls, ind + MARK + "\n" + "\n".join(_render(t, tail, ind)) + "\n"))
            else:
                ind = _indent(t, a.s)
                edits.append((a.s, a.e, "{\n" + ind + "    " + MARK + "\n" + "\n".join(
                    _render(t, [a], ind + "    ") + _render(t, tail, ind + "    ")) + "\n" + ind + "}"))
        return edits
    for b in j.preds["breaks"]:
        if b.parent.kind != "block":
            return None
        ind = _indent(t, b.s)
        sp = _own_line(t, m, b.s, b.e)
        if sp is None:
            return None
        keep_break = not _is_exit(tail[-1])
        edits.append((sp[0], sp[0], ind + MARK + "\n" + "\n".join(_render(t, tail, ind)) + "\n"))
        if not keep_break:
            edits.append((sp[0], sp[1], ""))
    if j.preds["ft_end"]:
        body = j.anchor.body
        last = body.kids[-1]
        ind = _indent(t, last.s)
        le = _le(t, last.e)
        edits.append((le + 1, le + 1, ind + MARK + "\n" + "\n".join(_render(t, tail, ind)) + "\n"))
    return edits


# ------------------------------------------------------------------------------ t1: the pinned constant

def _const_expr(fn, e):
    """E is a link-time constant: casts, `&`, a global symbol, an optional constant index/offset."""
    x = _strip_parens(e)
    while True:
        mm = re.match(r"^\(\s*(?:%s\s*)+\**\s*\)\s*" % ID, x)
        if not mm:
            break
        x = _strip_parens(x[mm.end():])
    x = x.lstrip("&").strip()
    x = _strip_parens(x)
    mm = re.fullmatch(r"(%s)(?:\s*\[\s*%s\s*\])?(?:\s*[-+]\s*%s)?" % (ID, NUM, NUM), x)
    if not mm:
        mm = re.fullmatch(r"\(\s*\(\s*u8\s*\*\s*\)\s*&?\s*(%s)\s*[-+]\s*%s\s*\)" % (ID, NUM), x)
    return bool(mm) and not fn.is_local(mm.group(1)) and mm.group(1) not in KW


def _plain_local(fn, e):
    x = _strip_parens(e)
    while True:
        mm = re.match(r"^\(\s*(?:%s\s*)+\**\s*\)\s*" % ID, x)
        if not mm:
            break
        x = _strip_parens(x[mm.end():])
    return re.fullmatch(ID, x) is not None and fn.is_local(x)


def _def_rhs(fn, pin, n):
    """E of `P = E;` (or the pin's own initialiser), else None."""
    mt = fn.mt(n)
    mm = re.match(r"^\s*%s\s*=(?!=)\s*" % re.escape(pin.name), mt)
    if mm and n.kind == "simple":
        return mm.end(), n.e - 1 - n.s              # offsets of E in the node text
    return None


KEEP_RE = r"^\s*ASM_KEEP[A-Z0-9_]*\s*\(\s*%s\s*\)\s*;"


def t1_edits(fn, pin, why=None, drop_keeps=False):
    """Substitute every definition of P into the uses it reaches; None unless every mention goes
    (`why`, a list, collects the refusal).  drop_keeps: an `ASM_KEEP*(P);` - a pin that only keeps
    P alive - goes with P (two pins off, and still only if the scorer says exact)."""
    def no(reason):
        if why is not None:
            why.append(reason)
        return None
    t, m = fn.t, fn.m
    scope = pin.scope
    keeps = [n for n in scope.walk() if n.kind == "simple" and pin.in_scope(n.s)
             and re.match(KEEP_RE % re.escape(pin.name), fn.mt(n))] if drop_keeps else []
    if drop_keeps and not keeps:
        return no("no ASM_KEEP of P to drop")
    kspans = [(k.s, k.e) for k in keeps]

    def in_keep(a):
        return any(k0 <= a < k1 for k0, k1 in kspans)
    defs = []
    for n in scope.walk():
        if n.kind == "simple" and pin.in_scope(n.s) and _def_rhs(fn, pin, n):
            defs.append(n)
    init = None
    mm = re.search(r"ASM_REG\s*\([^)]*\)\s*=\s*", fn.mt(pin.decl))
    if mm:
        init = (pin.decl, pin.decl.s + mm.end(), pin.decl.e - 1)
    if not defs and not init:
        return no("no definition of P")
    for s0, e0 in pin.mentions():
        if not in_keep(s0) and re.search(r"\bASM_[A-Z0-9_]+\s*\([^;]*$", m[_ls(m, s0):s0]):
            return no("P is an argument of another pin (ASM_KEEP...)")
    edits, covered = [], set()
    items = [(d, d.s + _def_rhs(fn, pin, d)[0], d.s + _def_rhs(fn, pin, d)[1]) for d in defs]
    if init:
        items.append(init)
    def_starts = {d.s for d in defs}
    for d, es, ee in items:
        e_txt = t[es:ee].strip()
        e_m = m[es:ee]
        if not (_const_expr(fn, e_m) or _plain_local(fn, e_m)):
            return no("a definition is neither a link-time constant nor a plain copy")
        copied = None if _const_expr(fn, e_m) else _strip_parens(re.sub(r"^\(\s*(?:%s\s*)+\**\s*\)" % ID, "", _strip_parens(e_m)))
        blk = d.parent
        if blk is None or blk.kind != "block":
            return no("a definition is not a statement of a block")
        region = []
        for s in blk.kids[d.idx + 1:]:
            if s.kind in ("label", "case", "pp"):
                break
            if s.s in def_starts:
                break
            if any(x.kind in ("label", "case", "pp") for x in s.walk()):
                break
            if any(x.s in def_starts for x in s.walk() if x is not s):
                break
            region.append(s)
        for s in region:
            if copied and re.search(r"(?<![\w.])(?<!->)%s\s*(?:=(?!=)|[-+*/%%&|^]=|<<=|>>=|\+\+|--)|(?:\+\+|--)\s*%s\b"
                                    % (re.escape(copied), re.escape(copied)), fn.mt(s)):
                return no("the copied name is written where P is used")
            for a, b in pin.mentions(s.s, s.e):
                if in_keep(a):
                    continue
                edits.append((a, b, _wrap(e_txt, m, a, b)))
                covered.add(a)
        if d is not pin.decl:
            sp = _own_line(t, m, d.s, d.e)
            if sp is None:
                return no("a definition shares its line with other code")
            edits.append((sp[0], sp[1], ""))
    rest = [a for a, b in pin.mentions() if a not in covered and not in_keep(a)
            and not any(d.s <= a < d.e and a == d.s + len(fn.mt(d)) - len(fn.mt(d).lstrip()) for d in defs)]
    if rest:
        return no("a use no definition reaches (a join, a loop or a nested definition)")
    sp = _own_line(t, m, pin.decl.s, pin.decl.e)
    if sp is None:
        return no("the declaration shares its line")
    edits.append((sp[0], sp[1], ""))
    for k in keeps:
        sp = _own_line(t, m, k.s, k.e)
        if sp is None:
            return no("an ASM_KEEP of P shares its line")
        edits.append((sp[0], sp[1], ""))
    return edits


# ------------------------------------------------------------------------------ fsub

VDEF_RE = re.compile(r"^\s*(%s)\s*(=(?!=)|<<=|>>=|[-+*/%%&|^]=)\s*" % ID)
CALL_RE = re.compile(r"(?<![\w.])(?<!->)(%s)\s*\(" % ID)


def _stores(ms):
    """True when a masked statement writes memory (not only a plain variable) or calls."""
    s = ms.strip()
    if CALL_RE.search(s) and any(x.group(1) not in KW and x.group(1) != "sizeof" for x in CALL_RE.finditer(s)):
        return True
    mm = re.match(r"^(.*?)(?<![=!<>])(=|<<=|>>=|[-+*/%&|^]=)(?!=)", s)
    if mm and not re.fullmatch(r"\s*%s\s*" % ID, mm.group(1)):
        return True
    if re.search(r"\+\+|--", s) and not re.fullmatch(r"\s*(?:%s\s*(?:\+\+|--)|(?:\+\+|--)\s*%s)\s*;" % (ID, ID), s):
        return True
    return False


def _assigned(ms):
    """Plain identifiers a masked statement assigns."""
    out = set()
    mm = VDEF_RE.match(ms)
    if mm:
        out.add(mm.group(1))
    for x in re.finditer(r"(?:\+\+|--)\s*(%s)\b|(?<![\w.])(?<!->)(%s)\s*(?:\+\+|--)" % (ID, ID), ms):
        out.add(x.group(1) or x.group(2))
    return out


def _addr_const(fn, e):
    """`&X`, or an array symbol (its name is its address): a value no store can change."""
    x = _strip_parens(e)
    while True:
        mm = re.match(r"^\(\s*(?:%s\s*)+\**\s*\)\s*" % ID, x)
        if not mm:
            break
        x = _strip_parens(x[mm.end():])
    if re.fullmatch(r"&\s*%s" % ID, x):
        return True
    return re.fullmatch(ID, x) is not None and x in fn.arrays


def _reads_memory(fn, e):
    if _addr_const(fn, e):
        return False
    if re.search(r"->|\.|\[|(?<![\w)\]])\*", e):
        return True
    return any(not fn.is_local(x) and x not in KW for x in re.findall(ID, e)
               if not re.fullmatch(r"(?:u|s)(?:8|16|32)|int|char|short|long|unsigned|signed|void|M2C_UNK|uptr|const|volatile", x))


def fsub_run(fn, run, pinned, outside_ok):
    """[[orig index, real, masked]] of a straight-line run with single-use temporaries
    forward-substituted; a definition that went is missing from the list."""
    st = [[k, fn.t[n.s:n.e], fn.m[n.s:n.e]] for k, n in enumerate(run)]
    body = fn.m[fn.body.s:fn.body.e]
    changed = True
    while changed:
        changed = False
        for i in range(len(st)):
            _, r_i, m_i = st[i]
            mm = VDEF_RE.match(m_i)
            if not mm or mm.group(2) != "=":
                continue
            v = mm.group(1)
            if v in pinned or not fn.is_local(v):
                continue
            if re.search(r"(?:^|[^\w)\]&])&\s*%s\b" % re.escape(v), body):
                continue                          # address taken: it lives in memory
            if any(re.search(r"\[|volatile", fn.mt(x)) for x in fn.decls.get(v, [])):
                continue
            e_r = r_i[mm.end():].rstrip().rstrip(";").strip()
            e_m = m_i[mm.end():].rstrip().rstrip(";").strip()
            rx = _occ_re(v)
            if rx.search(e_m) or any(x.group(1) not in KW for x in CALL_RE.finditer(e_m)):
                continue
            j = next((k for k in range(i + 1, len(st)) if rx.search(st[k][2])), None)
            if j is None or ASM_STMT_RE.match(st[j][2]):
                continue                          # never into another pin's argument
            m_j = st[j][2]
            dj = VDEF_RE.match(m_j)
            redef = dj is not None and dj.group(1) == v
            uses = [x for x in rx.finditer(m_j) if not (redef and x.start() == dj.start(1))]
            if not uses:
                continue
            multi_ok = re.fullmatch(r"%s|%s" % (ID, NUM), _strip_parens(e_m)) is not None
            if len(uses) != 1 and not multi_ok:
                continue

            def pure_def(k):
                dk = VDEF_RE.match(st[k][2])
                return bool(dk and dk.group(1) == v and dk.group(2) == "=" and not [
                    x for x in rx.finditer(st[k][2]) if x.start() != dk.start(1)])
            targets = [j]
            if multi_ok and not redef:          # a plain name or number goes into every use it reaches
                for k in range(j + 1, len(st)):
                    if not rx.search(st[k][2]):
                        continue
                    if pure_def(k):
                        break
                    if ASM_STMT_RE.match(st[k][2]):
                        targets = None
                        break
                    targets.append(k)
                    dk = VDEF_RE.match(st[k][2])
                    if dk and dk.group(1) == v:
                        break
            if targets is None:
                continue
            last = targets[-1]
            dl = VDEF_RE.match(st[last][2])
            if not (dl and dl.group(1) == v):
                k = next((k for k in range(last + 1, len(st)) if rx.search(st[k][2])), None)
                if k is not None:
                    if not pure_def(k):
                        continue
                elif not outside_ok(v):
                    continue
            ids = set(re.findall(ID, e_m))
            mem = _reads_memory(fn, e_m)
            if any(_assigned(st[k][2]) & ids or (mem and (_stores(st[k][2]) or ASM_STMT_RE.match(st[k][2])))
                   for k in range(i + 1, last)):
                continue
            if redef and dj.group(2) != "=":      # `v = X; v op= Y;` -> `v = X op Y;`
                r_j = st[j][1]
                op = dj.group(2)[:-1]
                rhs_r = r_j[dj.end():].rstrip().rstrip(";").strip()
                rhs_m = m_j[dj.end():].rstrip().rstrip(";").strip()
                st[j] = [st[j][0], "%s%s = %s %s %s;" % (r_j[:dj.start(1)], v, _paren_bin(e_r), op, _paren_bin(rhs_r)),
                         "%s%s = %s %s %s;" % (m_j[:dj.start(1)], v, _paren_bin(e_m), op, _paren_bin(rhs_m))]
            else:
                for jt in targets:
                    st[jt] = [st[jt][0]] + _subst(st[jt][1], st[jt][2], v, e_r, e_m)
            del st[i]
            changed = True
            break
    return st


ASM_STMT_RE = re.compile(r"^\s*ASM_[A-Z0-9_]+\s*\(")


def _subst(r, m, v, e_r, e_m):
    """Every use of v in one statement replaced by E (a definition's own left side kept);
    `*&X...` folds to `X...`."""
    rx = _occ_re(v)
    d = VDEF_RE.match(m)
    er, em = e_r.strip(), e_m.strip()
    for x in reversed([x for x in rx.finditer(m) if not (d and d.group(1) == v and x.start() == d.start(1))]):
        a, b = x.start(), x.end()
        if m[:a].rstrip().endswith("*") and em.startswith("&") and _deref_ok(m, a) and _is_term(em[1:]):
            cut = len(m[:a].rstrip()) - 1
            r = r[:cut] + er[1:].lstrip() + r[b:]
            m = m[:cut] + em[1:].lstrip() + m[b:]
            continue
        w = _wrap(em, m, a, b)
        r = r[:a] + (er if w == em else "(" + er + ")") + r[b:]
        m = m[:a] + w + m[b:]
    return [r, m]


def _paren_bin(e):
    e = e.strip()
    return e if _is_term(e) or _is_unary(e) else "(" + e + ")"


def _deref_ok(m, a):
    """The `*` just before position a is a unary dereference."""
    pre = m[:a].rstrip()
    pre = pre[:-1].rstrip()
    return not pre or pre[-1] in "(,=[+-*/%&|^!~<>?:" or pre.endswith("return")


def _runs(fn):
    out = []
    for b in fn.nodes:
        if b.kind != "block":
            continue
        cur = []
        for k in b.kids:
            if k.kind == "simple":
                cur.append(k)
            elif k.kind == "empty":
                continue
            else:
                if cur:
                    out.append(cur)
                cur = []
        if cur:
            out.append(cur)
    return out


def fsub_text(text, pinned_names):
    """Forward-substitution in every straight-line run that carries a MARK; statements are edited
    in place, so comments and marks between them stay."""
    marks = [mm.start() for mm in re.finditer(re.escape(MARK), text)]
    if not marks:
        return text
    m = mask(text)
    edits = []
    for h, body in _functions(m):
        fn = Fn(text, m, h, body)
        mruns = []
        for r in _runs(fn):
            prev = r[0].parent.kids[r[0].idx - 1] if r[0].idx > 0 else None
            lo = prev.e if prev is not None else r[0].parent.s + 1
            if any(lo <= p < r[-1].e for p in marks):
                mruns.append(r)
        if not mruns:
            continue
        spans = [(r[0].s, r[-1].e) for r in mruns]

        def outside_ok(v, pos, fn=fn, spans=spans):
            """No mention of v (in the scope of the declaration visible at pos) outside the runs."""
            sc = _var_scope(fn, v, pos)
            if sc is None:
                return False
            blk, sh = sc
            for mm in _occ_re(v).finditer(fn.m, blk.s, blk.e):
                p = mm.start()
                if any(b.s <= p < b.e for b in sh) or any(a <= p < b for a, b in spans):
                    continue
                if any(d.s <= p < d.e for d in fn.decls.get(v, [])):
                    continue
                return False
            return True

        for r in mruns:
            nxt = r[-1].parent.kids[r[-1].idx + 1] if r[-1].idx + 1 < len(r[-1].parent.kids) else None
            ends_ret = nxt is not None and nxt.kind == "return"

            def ok(v, base=outside_ok, ends_ret=ends_ret, pos=r[0].s, after=cont(r[-1])):
                return ends_ret or base(v, pos) or _dead_after(fn, after, v)
            kept = {x[0]: x for x in fsub_run(fn, r, pinned_names, ok)}
            for k, n in enumerate(r):
                if k not in kept:
                    sp = _own_line(text, m, n.s, n.e) or (n.s, n.e)
                    edits.append((sp[0], sp[1], ""))
                elif kept[k][1] != text[n.s:n.e]:
                    edits.append((n.s, n.e, kept[k][1]))
    return (_apply(text, edits) or text) if edits else text


# ------------------------------------------------------------------------------ cleanup

def _index_form(text):
    """`*(u8 *)(A + (u32)SYM)` -> `SYM[A]` for SYM an extern u8 array (marked runs only)."""
    arrays = set(re.findall(r"^\s*extern\s+u8\s+(%s)\s*\[" % ID, text, re.M))
    out = text
    for mm in list(re.finditer(r"\*\s*\(\s*u8\s*\*\s*\)\s*\(", out))[::-1]:
        o = mm.end() - 1
        c = _match_paren(out, o)
        if c is None:
            continue
        inner = out[o + 1:c]
        k = _top_plus(inner)
        if k is None:
            continue
        a, b = inner[:k].strip(), inner[k + 1:].strip()
        cb = re.fullmatch(r"\(\s*(?:u32|uptr|unsigned long|s32|int)\s*\)\s*(?:\(\s*%s\s*\*\s*\)\s*)?(%s)" % (ID, ID), b)
        if not cb or cb.group(1) not in arrays:
            continue
        ca = re.match(r"^\(\s*(?:u32|uptr|unsigned long)\s*\)\s*", a)
        if ca and _is_term(a[ca.end():]):
            a = a[ca.end():]
        a = _strip_parens(a)
        out = out[:mm.start()] + "%s[%s]" % (cb.group(1), a) + out[c + 1:]
    return out


def _top_plus(s):
    d = 0
    last = None
    for k, ch in enumerate(s):
        if ch in "([":
            d += 1
        elif ch in ")]":
            d -= 1
        elif ch == "+" and d == 0 and s[k - 1:k] != "+" and s[k + 1:k + 2] != "+":
            last = k
    return last


def cleanup(text, before):
    """Dead declarations (of names the rewrite emptied), then the marks."""
    m = mask(text)
    mb = mask(before)
    edits = []
    for h, body in _functions(m):
        fn = Fn(text, m, h, body)
        for name, ds in fn.decls.items():
            rx = _occ_re(name)
            if len(rx.findall(mb)) <= len(rx.findall(m)):
                continue                         # the rewrite took no mention of it
            for d in ds:
                if len(_decl_names(fn.mt(d))) != 1 or "ASM_REG" in fn.mt(d) or d.parent is None:
                    continue
                blk = d.parent
                sh = [x.parent for x in ds if x is not d and x.parent is not None and x.parent is not blk
                      and blk.s <= x.parent.s and x.parent.e <= blk.e]
                now = [x for x in rx.finditer(m, blk.s, blk.e) if not (d.s <= x.start() < d.e)
                       and not any(b.s <= x.start() < b.e for b in sh)]
                if now:
                    continue
                init = re.search(r"=\s*(.+?)\s*;\s*$", fn.mt(d), re.S)
                if init and CALL_RE.search(init.group(1)):
                    continue
                sp = _own_line(text, m, d.s, d.e)
                if sp:
                    edits.append((sp[0], sp[1], ""))
    if edits:
        text = _apply(text, edits) or text
    text = re.sub(r"^[ \t]*" + re.escape(MARK) + r"[ \t]*\n", "", text, flags=re.M)
    return text.replace(MARK, "")


def _drop_dead_labels(text, names):
    m = mask(text)
    out = text
    for nm in names:
        if re.search(r"\bgoto\s+%s\s*;" % nm, m) or re.search(r"&&\s*%s\b" % nm, m):
            continue
        out = re.sub(r"^[ \t]*%s:[ \t]*\n" % nm, "", out, flags=re.M)
    return out


# ------------------------------------------------------------------------------ candidates

# ------------------------------------------------------------------------------ host

HOST_MAX = int(os.environ.get("T21_HOST_MAX", "4"))         # a sink+erase residue this small triggers it
HOST_BUDGET = int(os.environ.get("T21_HOST_BUDGET", "10"))  # scorer runs per pin for host candidates
WORD_T = re.compile(r"^(?:(?:const|signed|unsigned)\s+)*(?:s32|u32|int|long|unsigned|signed|M2C_UNK|uptr)"
                    r"(?:\s+(?:int|long))?$")
NUMK = re.compile(r"^(?:[-~]\s*)?(?:0x[0-9A-Fa-f]+|\d+)[uUlL]*$")
PREC = {"||": 1, "&&": 2, "|": 3, "^": 4, "&": 5, "==": 6, "!=": 6, "<": 7, ">": 7, "<=": 7, ">=": 7,
        "<<": 8, ">>": 8, "+": 9, "-": 9, "*": 10, "/": 10, "%": 10}
ARITH = ("<<", ">>", "&", "|", "^", "+", "-", "*")


def _ws_span(e, a, b):
    while a < b and e[a] in " \t\n":
        a += 1
    while b > a and e[b - 1] in " \t\n":
        b -= 1
    return a, b


def _strip_span(e, a, b):
    """(a, b) of e[a:b] without surrounding whitespace and wrapping parentheses."""
    while True:
        a, b = _ws_span(e, a, b)
        if a < b and e[a] == "(" and _match_paren(e[:b], a) == b - 1:
            a, b = a + 1, b - 1
            continue
        return a, b


CAST_T = re.compile(r"^\s*(?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*"
                    r"(?:u8|s8|u16|s16|u32|s32|int|char|short|long|void|uptr|M2C_UNK|unsigned|signed|%s(?=\s*\*))"
                    r"(?:\s+(?:int|long|char|short))*\s*\**\s*$" % ID)


def _ends_cast(e, k):
    """e[k-1] is the `)` of a cast (`(u8 *)`, `(s16)`, `(S_X *)`): what follows is an operand, so a
    `&`, `*`, `-` or `+` after it is unary."""
    if k <= 0 or e[k - 1] != ")":
        return False
    d = 0
    for j in range(k - 1, -1, -1):
        if e[j] == ")":
            d += 1
        elif e[j] == "(":
            d -= 1
            if d == 0:
                return bool(CAST_T.match(e[j + 1:k - 1]))
    return False


def _split_top(e, a, b):
    """The loosest top-level binary operator of e[a:b] (the rightmost of equals):
    (lhs span, op, rhs span, raw lhs span, raw rhs span) - raw spans keep their parentheses - or None."""
    a, b = _strip_span(e, a, b)
    best, d, k = None, 0, a
    while k < b:
        c = e[k]
        if c in "([":
            d += 1
        elif c in ")]":
            d -= 1
        elif d == 0:
            if c == "?":
                return None
            two = e[k:k + 2]
            if two in ("->", "++", "--"):
                k += 2
                continue
            op = two if two in ("||", "&&", "==", "!=", "<=", ">=", "<<", ">>") else c if c in "|^&<>+-*/%" else None
            if op:
                prev = e[a:k].rstrip()
                if prev and (prev[-1].isalnum() or prev[-1] in "_)]") and not _ends_cast(e, a + len(prev)):
                    if best is None or PREC[op] <= best[0]:
                        best = (PREC[op], k, op)
                k += len(op)
                continue
        k += 1
    if best is None:
        return None
    _, k, op = best
    return (_strip_span(e, a, k), op, _strip_span(e, k + len(op), b), _ws_span(e, a, k), _ws_span(e, k + len(op), b))


def _word_local(fn, h, pos):
    """The declaration of the local h visible at pos when it is a plain word-sized integer (never
    u16/s16/u8, a pointer, an array, volatile, pinned or address-taken), else None."""
    sc = _var_scope(fn, h, pos)
    if sc is None:
        return None
    blk, sh = sc
    if any(b.s <= pos < b.e for b in sh):
        return None
    d = next((x for x in fn.decls.get(h, []) if x.parent is blk), None)
    if d is None:
        return None
    md = fn.mt(d)
    if "ASM_REG" in md or "volatile" in md or len(_decl_names(md)) != 1:
        return None
    mm = re.match(r"^\s*(?:register\s+)?(.*?)\s*\b%s\b\s*(?:=[^;]*)?;\s*$" % re.escape(h), md, re.S)
    if not mm or not WORD_T.match(mm.group(1).strip()):
        return None
    if re.search(r"(?:^|[^\w)\]&])&\s*%s\b" % re.escape(h), fn.m[fn.body.s:fn.body.e]):
        return None
    return d


def _retype_edit(fn, v, pos):
    """The edit that retypes the (not word-sized, unpinned) declaration of v visible at pos to s32."""
    d = next((dd for dd in fn.decls.get(v, []) if dd.parent is not None and dd.parent.s <= pos < dd.parent.e), None)
    if d is None or "ASM_REG" in fn.mt(d) or _word_local(fn, v, pos) is not None or len(_decl_names(fn.mt(d))) != 1:
        return None
    mt = re.match(r"^(\s*)((?:register\s+)?)(.*?)(\s*\b%s\b)" % re.escape(v), fn.mt(d), re.S)
    if not mt or not mt.group(3).strip() or "*" in mt.group(3) or "[" in fn.mt(d):
        return None
    return (d.s + mt.start(3), d.s + mt.end(3), "s32")


def _ndefs(fn, h):
    return sum(1 for n in fn.nodes if n.kind == "simple" and h in _assigned(fn.mt(n)))


def _hosts(fn, sites, exclude):
    """[(rank, name)]: word-sized locals dead at every site and already assigned elsewhere (so global
    to local-alloc) - rank 2 when assigned earlier in the first site's block, 3 otherwise."""
    first = sites[0]
    earlier = set()
    if first.parent is not None and first.parent.kind == "block":
        for k in first.parent.kids[:first.idx]:
            if k.kind == "simple":
                earlier |= _assigned(fn.mt(k))
    out = []
    for h in fn.decls:
        if h in exclude or _ndefs(fn, h) < 1:
            continue
        if not all(_word_local(fn, h, n.s) is not None for n in sites):
            continue
        if not all(_dead_after(fn, n, h) for n in sites):
            continue
        out.append((2 if h in earlier else 3, -_ndefs(fn, h), fn.decls[h][0].s, h))
    return [(r, h) for r, _, _, h in sorted(out)]


def host_candidates(text, vname, ranked=False):
    """[(label, text)]: the value that inherits a dying hard register's suggestion in combine_regs
    moved into a variable local-alloc refuses (family17 REPORT, "Generator").  Host order: (1) the
    erased variable itself, its assignment split `V = inner; use(V op k)`; (2) a word-sized local
    already assigned earlier in the block; (3) any other word-sized local dead at the site and
    assigned elsewhere; (4) the erased variable retyped s32 with `&=`.  Identical copies of a site
    (the sink's) are all rewritten; never a fresh block-local."""
    m = mask(text)
    t = text
    pinned = {p.name for p in pins_of(text)}
    res = []                                     # (rank, seq, label, edits)
    for h0, body in _functions(m):
        fn = Fn(text, m, h0, body)
        if vname not in fn.decls:
            continue
        rx = _occ_re(vname)

        def ln(pos):
            return t.count("\n", 0, pos) + 1

        def key(n):
            return " ".join(fn.m[n.s:(n.hdr[1] + 1 if n.kind == "if" else n.e)].split())

        def twins(n):
            k = key(n)
            return [x for x in fn.nodes if x.kind == n.kind and x.parent is not None
                    and x.parent.kind == "block" and key(x) == k]

        def own_start(n):
            return not m[_ls(m, n.s):n.s].strip()

        vdef = [S for S in fn.nodes if S.kind == "simple" and S.parent is not None and S.parent.kind == "block"
                and (lambda d: d is not None and d.group(1) == vname and d.group(2) == "=")(VDEF_RE.match(fn.mt(S)))]
        # (1) split the erased variable's own assignment: V = A op k; use(V) -> V = A; use((V op k))
        for S in vdef:
            rs = S.s + VDEF_RE.match(fn.mt(S)).end()
            sp = _split_top(m, rs, S.e - 1)
            if not sp or sp[1] not in ARITH or not NUMK.match(m[sp[2][0]:sp[2][1]].strip()) \
                    or rx.search(m[sp[0][0]:sp[0][1]]) or t[rs:S.e - 1] != m[rs:S.e - 1]:
                continue
            blk = S.parent
            if S.idx + 1 >= len(blk.kids):
                continue
            U = blk.kids[S.idx + 1]
            dU = VDEF_RE.match(fn.mt(U)) if U.kind == "simple" else None
            if U.kind == "if":
                ua, ub = U.hdr
                live = _dead_after(fn, U.then, vname) and _dead_after(fn, U.els if U.els is not None else cont(U), vname)
            elif U.kind == "simple":
                ua, ub = U.s, U.e
                live = bool(dU and dU.group(1) == vname) or _dead_after(fn, cont(U), vname)
            else:
                continue
            uses = [x for x in rx.finditer(m, ua, ub)
                    if not (dU and dU.group(1) == vname and x.start() == U.s + dU.start(1))]
            if len(uses) != 1 or not live:
                continue
            ea, eb = _ws_span(m, rs, S.e - 1)
            k = t[sp[2][0]:sp[2][1]].strip()
            edits = [(ea, eb, t[sp[0][0]:sp[0][1]]), (uses[0].start(), uses[0].end(), "(%s %s %s)" % (vname, sp[1], k))]
            res.append((1, (0 if U.kind == "if" else 3, S.s), "split:%s@%d" % (vname, ln(S.s)), edits))
        # (2)/(3) a single-assignment block-local feeding V's assignment, renamed to a host
        for U in vdef:
            blk = U.parent
            if U.idx == 0:
                continue
            S = blk.kids[U.idx - 1]
            mm = VDEF_RE.match(fn.mt(S)) if S.kind == "simple" else None
            if not mm or mm.group(2) != "=":
                continue
            L = mm.group(1)
            if L == vname or L in pinned or len(fn.decls.get(L, [])) != 1:
                continue
            dL = fn.decls[L][0]
            if dL.parent is fn.body or len(_decl_names(fn.mt(dL))) != 1 or "=" in fn.mt(dL):
                continue
            ment = [x for x in _occ_re(L).finditer(m, fn.body.s, fn.body.e) if not (dL.s <= x.start() < dL.e)]
            inU = [x for x in ment if U.s <= x.start() < U.e]
            if len(ment) != 2 or len(inU) != 1 or not (S.s <= ment[0].start() < S.e):
                continue
            spd = _own_line(t, m, dL.s, dL.e)
            if spd is None:
                continue
            for rank, H in _hosts(fn, [S], {L, vname} | pinned):
                if _occ_re(H).search(fn.mt(U)):
                    continue
                edits = [(S.s + mm.start(1), S.s + mm.end(1), H), (inU[0].start(), inU[0].end(), H), (spd[0], spd[1], "")]
                res.append((rank, (1, S.s), "rename:%s->%s@%d" % (L, H, ln(S.s)), edits))
        # (1)-(4) a test on V (or on a kept pin): if (!(V & k)) -> H = V & k; if (H == 0)
        done = set()
        for I in fn.nodes:
            if I.kind != "if" or I.parent is None or I.parent.kind != "block" or id(I) in done:
                continue
            ca, cb = I.hdr
            if t[ca:cb] != m[ca:cb]:
                continue
            na, nb = _strip_span(m, ca, cb)
            X, fmt = None, None
            if m[na:na + 1] == "!" and m[na + 1:na + 2] != "=":
                X, fmt = _strip_span(m, na + 1, nb), "%s == 0"
            else:
                sp = _split_top(m, ca, cb)
                if sp and sp[1] in ("==", "!=") and m[sp[2][0]:sp[2][1]].strip() == "0":
                    X, fmt = sp[0], "%s " + sp[1] + " 0"
                elif sp and sp[1] in ARITH:
                    X, fmt = (na, nb), "%s != 0"
            if X is None:
                continue
            spx = _split_top(m, X[0], X[1])
            if not spx or spx[1] not in ARITH:
                continue
            opl, opr = m[spx[0][0]:spx[0][1]].strip(), m[spx[2][0]:spx[2][1]].strip()
            if vname not in (opl, opr) and opl not in pinned and opr not in pinned:
                continue
            tw = twins(I)
            for x in tw:
                done.add(id(x))
            if not all(own_start(x) for x in tw):
                continue
            xt = t[X[0]:X[1]]

            def mk(H, assign, tw=tw, fmt=fmt):
                edits = []
                for x in tw:
                    ls = _ls(t, x.s)
                    edits.append((ls, ls, t[ls:x.s] + assign + "\n"))
                    edits.append((x.hdr[0], x.hdr[1], fmt % H))
                return edits
            tag = "x%d" % len(tw) if len(tw) > 1 else ""
            vdead = all(_dead_after(fn, x.then, vname) and _dead_after(fn, x.els if x.els is not None else cont(x), vname)
                        for x in tw)
            if vname in (opl, opr) and vdead and all(_word_local(fn, vname, x.s) for x in tw):
                res.append((1, (1, I.s), "test:%s@%d%s" % (vname, ln(I.s), tag), mk(vname, "%s = %s;" % (vname, xt))))
            for rank, H in _hosts(fn, tw, {vname} | pinned):
                res.append((rank, (2, I.s), "test:%s@%d%s" % (H, ln(I.s), tag), mk(H, "%s = %s;" % (H, xt))))
            if opl == vname and spx[1] == "&" and vdead:
                re4 = _retype_edit(fn, vname, I.s)
                if re4 is not None:
                    edits = mk(vname, "%s &= %s;" % (vname, t[spx[2][0]:spx[2][1]].strip())) + [re4]
                    res.append((4, (2, I.s), "retype:%s@%d%s" % (vname, ln(I.s), tag), edits))
        # (2)-(4) an in-place update then a bare test: V &= k; if (!V) -> H = V & k; if (H == 0)
        done2 = set()
        for S in fn.nodes:
            if S.kind != "simple" or S.parent is None or S.parent.kind != "block" or id(S) in done2:
                continue
            mm = VDEF_RE.match(fn.mt(S))
            if not mm or mm.group(1) != vname or mm.group(2) == "=" or mm.group(2)[:-1] not in ARITH:
                continue
            blk = S.parent
            if t[S.s:S.e] != m[S.s:S.e]:
                continue
            j = S.idx + 1                       # unrelated simple statements may stand between
            while j < len(blk.kids) and blk.kids[j].kind == "simple" and not rx.search(fn.mt(blk.kids[j])):
                j += 1
            if j >= len(blk.kids) or blk.kids[j].kind != "if":
                continue
            U, gap = blk.kids[j], j - S.idx
            c = _strip_parens(" ".join(m[U.hdr[0]:U.hdr[1]].split()))
            fmt = None
            if c.startswith("!") and not c.startswith("!=") and _strip_parens(c[1:]) == vname:
                fmt = "%s == 0"
            elif re.fullmatch(r"%s\s*(==|!=)\s*0" % re.escape(vname), c):
                fmt = "%s " + re.search(r"==|!=", c).group(0) + " 0"
            elif c == vname:
                fmt = "%s != 0"
            if fmt is None:
                continue
            def after(x, gap=gap):
                kk = x.parent.kids
                if x.idx + gap >= len(kk) or kk[x.idx + gap].kind != "if":
                    return None
                if any(kk[q].kind != "simple" or rx.search(fn.mt(kk[q])) for q in range(x.idx + 1, x.idx + gap)):
                    return None
                return kk[x.idx + gap]
            pairs = [(x, after(x)) for x in twins(S) if after(x) is not None and key(after(x)) == key(U)]
            mids = [fn.mt(x.parent.kids[q]) for x, _ in pairs for q in range(x.idx + 1, x.idx + gap)]
            for x, _ in pairs:
                done2.add(id(x))
            if not all(_dead_after(fn, u.then, vname) and _dead_after(fn, u.els if u.els is not None else cont(u), vname)
                       for _, u in pairs):
                continue
            rhs = _paren_bin(t[S.s + mm.end():S.e - 1].strip())
            op = mm.group(2)[:-1]
            tag = "x%d" % len(pairs) if len(pairs) > 1 else ""

            def mk2(H, pairs=pairs, op=op, rhs=rhs, fmt=fmt):
                edits = []
                for x, u in pairs:
                    edits.append((x.s, x.e, "%s = %s %s %s;" % (H, vname, op, rhs)))
                    edits.append((u.hdr[0], u.hdr[1], fmt % H))
                return edits
            for rank, H in _hosts(fn, [x for x, _ in pairs], {vname} | pinned):
                if any(_occ_re(H).search(s) for s in mids):
                    continue
                res.append((rank, (2, S.s), "test:%s@%d%s" % (H, ln(S.s), tag), mk2(H)))
            re4 = _retype_edit(fn, vname, S.s)
            if re4 is not None:
                res.append((4, (2, S.s), "retype:%s@%d" % (vname, ln(S.s)), [re4]))
        # (2)/(3) an operation inside V's assignment moved into a host: V = A - (P << 8) -> H = P << 8; V = A - H
        for S in vdef:
            if not own_start(S):
                continue
            rs = S.s + VDEF_RE.match(fn.mt(S)).end()
            sp = _split_top(m, rs, S.e - 1)
            if not sp or t[rs:S.e - 1] != m[rs:S.e - 1]:
                continue
            for side, raw in ((sp[0], sp[3]), (sp[2], sp[4])):
                sub = _split_top(m, side[0], side[1])
                if not sub or sub[1] not in ARITH or rx.search(m[side[0]:side[1]]) or not re.search(ID, m[side[0]:side[1]]):
                    continue
                for rank, H in _hosts(fn, [S], {vname} | pinned):
                    if _occ_re(H).search(fn.mt(S)):
                        continue
                    ls = _ls(t, S.s)
                    edits = [(ls, ls, t[ls:S.s] + "%s = %s;\n" % (H, t[side[0]:side[1]])), (raw[0], raw[1], H)]
                    res.append((rank, (4, S.s), "operand:%s@%d" % (H, ln(S.s)), edits))
    out, seen = [], {sha_text(text)}
    for rank, seq, lab, edits in sorted(res, key=lambda r: (r[0], r[1])):
        c = _apply(text, edits)
        if c is None or sha_text(c) in seen:
            continue
        seen.add(sha_text(c))
        out.append((rank, lab, c) if ranked else (lab, c))
    return out


def _pin_now(text, key, nth):
    ps = [p for p in pins_of(text) if p.key() == key]
    return ps[nth] if nth < len(ps) else None


def _erase_pin(text, site):
    """erase_many, and the pin's own trailing note whatever it says (`/* MATCH: ... a1 ... */` describes
    a pin that is gone)."""
    out = erase_many(text, [site], clean_notes=True)
    ls = out.rfind("\n", 0, site[3]) + 1
    le = out.find("\n", site[3])
    le = len(out) if le < 0 else le
    mm = re.match(r"^(.*?;)[ \t]*/\*(?:(?!\*/).)*\*/[ \t]*$", out[ls:le])
    return out[:ls] + mm.group(1) + out[le:] if mm else out


def _minimal(pin, j):
    """A structured join with its tail cut after the last statement that reads P (or a value an arm
    derived from P): the arms rejoin right after the call, no label needed."""
    if j.kind == "label":
        return None
    fn = pin.fn
    carried = set()
    for a in _pred_arms(fn, j):
        carried |= _arm_defs(pin, a)[1]
    last = None
    for i, s in enumerate(j.tail):
        if pin.mentions(s.s, s.e) or any(_occ_re(v).search(fn.mt(s)) for v in carried):
            last = i
    if last is None or last + 1 >= len(j.tail):
        return None
    return Join(j.kind, j.anchor, j.preds, j.tail[:last + 1], "block", j.end, j.labels)


def _swap_if(text, pos):
    """The if/else at pos with its two arms exchanged and the condition negated (research 4.1:
    find_cross_jump compares only against the block physically before the label)."""
    m = mask(text)
    for h, body in _functions(m):
        if not (body.s <= pos < body.e):
            continue
        fn = Fn(text, m, h, body)
        n = next((x for x in fn.nodes if x.kind == "if" and x.s == pos), None)
        if n is None or n.els is None or n.els.kind != "block" or n.then.kind != "block":
            return None
        neg = N._negate(text[n.hdr[0]:n.hdr[1]])
        return _apply(text, [(n.hdr[0], n.hdr[1], neg), (n.then.s, n.then.e, text[n.els.s:n.els.e]),
                             (n.els.s, n.els.e, text[n.then.s:n.then.e])])
    return None


def candidates(text, key, nth):
    """[(label, text)] cheapest first for the nth pin with key (name, reg)."""
    pin = _pin_now(text, key, nth)
    if pin is None or _pp_in(pin):
        return []
    fn = pin.fn
    pinned_all = {p.name for p in pins_of(text)}
    others = pinned_all - {pin.name}
    out = []

    def finish(t2, ops, sunk):
        """fsub (P kept out of it) -> t1, or erase -> fsub again -> cleanup; index spelling first."""
        res = []
        variants = [(ops, t2)]
        if sunk:
            t2a = fsub_text(t2, pinned_all)
            variants = [(ops + ["fsub"], t2a)] + ([(ops, t2)] if t2a != t2 else [])
        for o, tv in variants:
            p2 = _pin_now(tv, key, nth)
            if p2 is None:
                continue
            outs = []
            e1 = t1_edits(p2.fn, p2)
            t3 = _apply(tv, e1) if e1 is not None else None
            if t3 is not None:
                outs.append((o + ["t1"], t3))
            else:
                e1k = t1_edits(p2.fn, p2, drop_keeps=True)
                t3k = _apply(tv, e1k) if e1k is not None else None
                if t3k is not None:
                    outs.append((o + ["t1+keep"], t3k))
                elif sunk:
                    outs.append((o + ["erase"], _erase_pin(tv, p2.site)))
            for o2, t3 in outs:
                spell = []
                if "fsub" in o:                 # the values t1/erase freed, substituted in turn
                    t3f = fsub_text(t3, others)
                    if t3f != t3:
                        spell.append((o2 + ["fsub2"], t3f))
                spell.append((o2, t3))
                for o3, t4 in spell:
                    c = cleanup(t4, text)
                    ci = _index_form_marked(t4, text)
                    if ci is not None:
                        ci = cleanup(ci, text)
                        if ci != c:
                            res.append((o3 + ["idx"], ci))
                    res.append((o3, c))
        return res

    def sunk_text(sel):
        edits, names = [], []
        for j in sel:
            e = sink_edits(fn, j)
            if e is None:
                return None
            edits += e
            names += [x.name for x in j.labels]
        if not edits:
            return None
        t2 = _apply(text, edits)
        return None if t2 is None else _drop_dead_labels(t2, names)

    # 1. t1 alone
    out += finish(text, [], False)
    # 2. sink the joins this pin runs through (relevance judged on the short tail)
    rel = [j for j in label_joins(fn) + structured_joins(fn) if relevant(pin, j)]
    anchors = {id(j.anchor) for j in rel}
    mins = [_minimal(pin, j) or j for j in rel]
    sets = [(mins, "")]
    if any(a is not b for a, b in zip(mins, rel)):
        sets.append((rel, "-full"))
    if len(rel) > 1:
        sets += [((j,), "") for j in mins]
    longs = [j for j in label_joins(fn, True) if id(j.anchor) in anchors]
    if longs and [len(j.tail) for j in longs] != [len(j.tail) for j in rel if j.kind == "label"]:
        sets.append((longs + [j for j in mins if j.kind != "label"], "-long"))
    swaps = [j for j in mins if j.kind == "if" and len(j.preds["arms"]) == 2]
    for sel, tag in sets:
        t2 = sunk_text(sel)
        if t2 is None:
            continue
        ops = ["sink%s(%s)" % (tag, ",".join(_jname(fn, j) for j in sel))]
        out += finish(t2, ops, True)
    if swaps:
        t2 = sunk_text(mins)
        for j in swaps:
            t2 = _swap_if(t2, j.anchor.s) if t2 is not None else None
        if t2 is not None:
            out += finish(t2, ["sink(%s)+swap" % ",".join(_jname(fn, j) for j in mins)], True)
    # de-duplicate, keep order
    seen, res = set(), []
    for o, c in out:
        h = sha_text(c)
        if h in seen or c == text:
            continue
        seen.add(h)
        res.append(("%s$%s:%s" % (key[0], key[1], "+".join(o)), c))
    return res


def _pp_in(pin):
    """P's code crosses a NON_MATCHING / #if 0 / match-only arm: its declaration or a mention sits
    on a line both builds do not compile (an edit there is one the byte gate cannot see whole).
    A directive elsewhere in the scope is harmless - t1's regions and the tails stop at it."""
    fn = pin.fn
    if not any(n.kind == "pp" and pin.scope.s <= n.s < pin.scope.e for n in fn.nodes):
        return False
    labels = arm_labels(fn.t)
    lines = [fn.t.count("\n", 0, a) for a, _ in pin.mentions()] + [fn.t.count("\n", 0, pin.decl.s)]
    return any(labels[k] != "both" for k in lines if k < len(labels))


def _index_form_marked(t3, base):
    """The index spelling applied only to statements the rewrite touched (lines absent from base)."""
    old = set(base.splitlines())
    lines = t3.split("\n")
    out, changed = [], False
    for ln in lines:
        if ln not in old and "*(u8 *)" in ln:
            new = _index_line(ln, base)
            if new != ln:
                changed = True
                out.append(new)
                continue
        out.append(ln)
    return "\n".join(out) if changed else None


def _index_line(ln, base):
    arrays = set(re.findall(r"^\s*extern\s+u8\s+(%s)\s*\[" % ID, base, re.M))
    if not arrays:
        return ln
    hdr = "".join("extern u8 %s[];\n" % a for a in sorted(arrays))
    return _index_form(hdr + ln)[len(hdr):]


def _jname(fn, j):
    if j.kind == "label":
        return j.labels[-1].name
    return "%s@%d" % (j.kind, fn.t.count("\n", 0, j.anchor.s) + 1)


def _const_defs(p):
    fn = p.fn
    n_c = 0
    for n in p.scope.walk():
        if n.kind == "simple" and p.in_scope(n.s):
            r = _def_rhs(fn, p, n)
            if r and _const_expr(fn, fn.m[n.s + r[0]:n.s + r[1]]):
                n_c += 1
    if re.search(r"ASM_REG\s*\([^)]*\)\s*=", fn.mt(p.decl)):
        mm = re.search(r"ASM_REG\s*\([^)]*\)\s*=\s*(.*?)\s*;\s*$", fn.mt(p.decl), re.S)
        if mm and _const_expr(fn, mm.group(1)):
            n_c += 1
    return n_c


def eligible_pins(text):
    """[(pin, why, priority)] for every pin this transform can work on, best first.
       priority 0: set from a link-time constant and behind a join (the lane's shape);
                1: set from a link-time constant two or more times (T1 alone);
                2: behind a join, never a constant (sink + erase only)."""
    out = []
    try:
        ps = pins_of(text)
    except (ParseError, RecursionError):
        return out
    counts, seen = {}, {}
    for p in ps:
        k = p.key()
        p.nth = counts.get(k, 0)
        counts[k] = p.nth + 1
        d = " ".join(p.fn.t[p.decl.s:p.decl.e].split())
        c = seen.get((k, d), 0)
        seen[(k, d)] = c + 1
        p.ident = (k, d, c)
    for p in ps:
        if _pp_in(p):
            continue
        fn = p.fn
        js = [j for j in label_joins(fn) + structured_joins(fn) if relevant(p, j)]
        nc = _const_defs(p)
        if js and nc:
            out.append((p, "join+const", 0))
        elif nc >= 2:
            out.append((p, "multi-const", 1))
        elif js:
            out.append((p, "join", 2))
    out.sort(key=lambda x: (x[2], x[0].decl.s))
    return out


def _added_scaffolding(cand, cur):
    """A candidate may not add an ASM_* macro, an asm body or a volatile."""
    mc, mu = mask(cand), mask(cur)
    for rx in (r"\bASM_[A-Z0-9_]+\s*\(", r"\b__asm__\b|\basm\s*\(", r"\bvolatile\b"):
        if len(re.findall(rx, mc)) > len(re.findall(rx, mu)):
            return True
    return False


class T:
    name = "t21_crossjump"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin"
        if not eligible_pins(text):
            return "no ASM_REG pin behind a join or set from a constant twice"
        return None

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        p_in, f_in = len(sites_of(text)), _dowhile0(text)
        cur, steps, tried, attempts, best = text, [], 0, [], None
        failed = set()
        while tried < BUDGET:
            todo = [(p, why, prio) for p, why, prio in eligible_pins(cur) if p.ident not in failed]
            if not todo:
                break
            p = todo[0][0]
            won, spent, best_erase = None, 0, None
            pc, fc = len(sites_of(cur)), _dowhile0(cur)
            for lab, cand in candidates(cur, p.key(), p.nth):
                if tried >= BUDGET or spent >= PIN_BUDGET:
                    break
                if not (len(sites_of(cand)) < pc and _dowhile0(cand) <= fc) or _added_scaffolding(cand, cur):
                    continue
                tried += 1
                spent += 1
                v = verify_fn(cand)
                tot = v.get("total")
                attempts.append([lab, 0 if v.get("exact") else tot])
                if v.get("exact"):
                    won = (lab, cand)
                    break
                if tot is not None and (best is None or tot < best[0]):
                    best = (tot, lab)
                if tot is not None and "sink" in lab and "erase" in lab and tot <= HOST_MAX:
                    best_erase = (best_erase or []) + [(tot, len(best_erase or []), lab, cand)]
            # host: sink+erase came within a few words - the value feeding the erased variable
            # inherited a hard register's suggestion; move it into a variable local-alloc refuses.
            # Every such base is a start (best first): fsub may already have folded the site away.
            if not won and best_erase:
                hspent, seen_h = 0, set()
                hosts = sorted((rk, bi, b[2], hl, hc) for bi, b in enumerate(sorted(best_erase))
                               for rk, hl, hc in host_candidates(b[3], p.name, ranked=True))
                for _, _, blab, hlab, hc in hosts:
                    if hspent >= HOST_BUDGET:
                        break
                    h = sha_text(hc)
                    if h in seen_h:
                        continue
                    seen_h.add(h)
                    if not (len(sites_of(hc)) < pc and _dowhile0(hc) <= fc) or _added_scaffolding(hc, cur):
                        continue
                    tried += 1
                    hspent += 1
                    lab = "%s+host(%s)" % (blab, hlab)
                    v = verify_fn(hc)
                    tot = v.get("total")
                    attempts.append([lab, 0 if v.get("exact") else tot])
                    if v.get("exact"):
                        won = (lab, hc)
                        break
                    if tot is not None and tot < best[0]:
                        best = (tot, lab)
            if won:
                cur = won[1]
                steps.append(won[0])
            else:
                failed.add(p.ident)
        info = {"tried": tried, "pins_in": p_in, "pins_out": len(sites_of(cur)), "fences_in": f_in,
                "fences_out": _dowhile0(cur), "best": None if best is None else "%s@%s" % best,
                "attempts": attempts[:24]}
        if not steps:
            return None, info
        return cur, dict(info, step=" ".join(steps))
