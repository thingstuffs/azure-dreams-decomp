"""The fence study's natural shapes, and the base-page shape agy found twice, as generators.

docs/PIN_PATTERNS.md section 9: about a third of the sampled `do { } while (0)` fences stand for a
real source shape that m2c lowered into something else - the fence only pins what that shape would
have produced.  Nine rows were closed by hand that way (`t20_fencefree`); each generator below is
one of their shapes, written from those rows' pre-images:

  dropcopy   m2c's `x = y;` copy dropped and its source used instead (town/func_80878714,
             town/func_800A29F0).  Where y is written later while x is still read, each such write
             is folded into its single next read, or no candidate is made.
  armstore   `if (c) { v = A; } else { v = B; } D = v;` -> the store in both arms, as `D |= K` /
             `D &= K` when an arm's value is `D op K` (town/func_800C5228, town/func_800A7FDC).
  ret2break  `return R;` inside a loop -> `break;`, with `return R;` after the loop
             (town/func_800ABDC8).
  ptr2index  a pointer walk beside a counter -> the array indexed by the counter
             (dungeon/func_8009A874, func_8009A924).
  postinc    `p += 1;` folded into the nearest preceding use, `(p++)->f`; with the once-read temp
             folded too, `sum += (entry++)->field18` (main/func_8001AA50).
  gotoloop   m2c's goto loop - a diamond whose arms both end in the loop increment, closed by
             `if (E) return; goto top;` - as the real `do { ... } while (!E);` with the increment
             once at the end (town/func_800B6514); plus the goto-form variant (the duplicated tail
             moved after the join label) and the plain `top: ...; if (E) goto top;`.
  basesym    a pointer built as a literal page plus an offset -> the symbol at the sum,
             `(u8 *)0x80010000 + 0x601C` -> `&D_8001601C`, declared if missing (agy's group lanes:
             town/func_8077DC0C, town/func_8050E100).  Never on a SLUS row: the SLUS scorer compares
             object identity, and a relocated `lui %hi` can never equal the pinned literal.

None of them adds a barrier or a pin; some delete a pin that only existed for the shape they
restore (a copy's `register ... ASM_REG` declaration, an `ASM_KEEP` on a page base).  They are
liberal on purpose - the verdict is byte equality against retail, so a rewrite that changed
behaviour cannot survive the gate; every precondition here only saves verifies.
"""
import re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from pin_census import arm_labels, HAS_PP_RE

try:
    from .t12_stmtorder import mask, movable
except ImportError:                       # pragma: no cover - direct import
    from t12_stmtorder import mask, movable

ID = r"[A-Za-z_]\w*"
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
CTRL = {"return", "goto", "break", "continue", "case", "default", "do", "else", "if", "while",
        "for", "switch", "sizeof"}
SIZE = {"u8": 1, "s8": 1, "char": 1, "void": 1, "u16": 2, "s16": 2, "short": 2,
        "u32": 4, "s32": 4, "int": 4, "unsigned": 4, "long": 4, "M2C_UNK": 4}
LABEL_RE = re.compile(r"^[ \t]*(?P<l>%s)[ \t]*:[ \t]*;?[ \t]*$" % ID)
GOTO_LINE_RE = re.compile(r"^[ \t]*goto[ \t]+(?P<l>%s)[ \t]*;[ \t]*$" % ID)
PIN_STMT_RE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+[ \t]*\(.*\)[ \t]*;[ \t]*$")
CONTROL_RE = re.compile(r"^[ \t]*(?:goto|return|break|continue|case|default|if|while|for|do|switch|else)\b")


# ------------------------------------------------------------------------------ plumbing

def _nl(s):
    return s[:-1] if s.endswith("\n") else s


def _ind(s):
    return s[:len(s) - len(s.lstrip(" \t"))]


def _sq(s):
    return re.sub(r"\s+", "", s)


def _occ(name):
    """A variable mention: not a member (`.x`, `->x`), not a call."""
    return re.compile(r"(?<![\w.])(?<!->)%s\b(?![ \t]*\()" % re.escape(name))


class _T:
    """A text, its masked twin (comments and strings blanked, same length) and their lines."""

    def __init__(self, text):
        self.text = text
        self.mtext = mask(text)
        self.lines = text.splitlines(True)
        self.m = [_nl(x) for x in self.mtext.splitlines(True)]
        if len(self.m) != len(self.lines):          # a stray form feed or the like: stay safe
            self.m = [_nl(x) for x in mask(text).split("\n")][:len(self.lines)]
        self.spans = _spans(self.m)

    def span(self, i):
        return next(((a, b) for a, b in self.spans if a <= i <= b), None)

    def build(self, edits=None, drop=(), insert_after=None):
        """New text: `edits` {line: new line text (no newline)}, `drop` lines deleted,
        `insert_after` {line: [lines]} added after a line (after its edit)."""
        edits, insert_after, drop = edits or {}, insert_after or {}, set(drop)
        out = []
        for k, ln in enumerate(self.lines):
            nl = "\n" if ln.endswith("\n") else ""
            if k not in drop:
                out.append((edits[k] + nl) if k in edits else ln)
            for extra in insert_after.get(k, []):
                out.append(extra + "\n")
        return "".join(out)


def _spans(ml):
    """[(open line, close line)] of every top-level brace block - the function bodies."""
    out, d, start = [], 0, None
    for i, ln in enumerate(ml):
        if ln.lstrip().startswith("#"):
            continue
        for c in ln:
            if c == "{":
                if d == 0:
                    start = i
                d += 1
            elif c == "}":
                d -= 1
                if d == 0 and start is not None:
                    out.append((start, i))
                    start = None
                d = max(d, 0)
    return out


def _close(ml, i):
    """Line of the brace that closes the LAST `{` on line i."""
    j = ml[i].rfind("{")
    if j < 0:
        return None
    d = 1
    for k in range(i, len(ml)):
        for c in (ml[i][j + 1:] if k == i else ml[k]):
            if c == "{":
                d += 1
            elif c == "}":
                d -= 1
                if d == 0:
                    return k
    return None


def _params(ml, a):
    head = "\n".join(ml[max(0, a - 8):a + 1])
    head = head[:head.rfind("{")] if "{" in head else head
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
    names = set()
    for p in head[left + 1:r].split(","):
        ids = re.findall(ID, p)
        if ids and ids[-1] != "void":
            names.add(ids[-1])
    return names


def _decl(ml, a, b, name):
    """(line, type text, initialiser) of a line in a..b that declares `name` and nothing else."""
    rx = re.compile(r"^(?P<i>[ \t]*)(?P<t>(?:(?:register|const|volatile|unsigned|signed|struct|union)[ \t]+)*"
                    r"%s(?:[ \t]*\*+[ \t]*|[ \t]+)(?:\*+[ \t]*)?)%s[ \t]*(?P<arr>\[[^\]]*\][ \t]*)?"
                    r"(?:ASM_REG[ \t]*\([^)]*\)[ \t]*)?(?:=[ \t]*(?P<init>[^;]*?))?[ \t]*;[ \t]*$" % (ID, re.escape(name)))
    for k in range(a, b + 1):
        m = rx.match(ml[k])
        if m and re.match(ID, ml[k].strip()).group(0) not in CTRL:
            init = m.group("init")
            if init and "," in re.sub(r"\([^()]*\)", "", init):
                continue
            ty = m.group("t").replace("register", "").strip()
            return k, ty, init
    return None, None, None


def _is_local_or_param(t, a, b, name):
    return name in _params(t.m, a) or _decl(t.m, a, b, name)[0] is not None


def _writes(mtext, name):
    n = re.escape(name)
    rx = re.compile(r"(?<![\w.])(?<!->)%s[ \t]*(?:=(?!=)|[-+*/%%&|^]=|<<=|>>=|\+\+|--)|(?:\+\+|--)[ \t]*%s\b" % (n, n))
    return len(rx.findall(mtext))


def _addr_taken(mtext, name):
    return bool(re.search(r"(?:^|[^\w)\]&])&[ \t]*%s\b" % re.escape(name), mtext, re.M))


def _term(e):
    """True when `e` needs no parentheses in any operand position."""
    e = e.strip()
    if re.fullmatch(r"%s|%s" % (ID, NUM), e):
        return True
    if re.fullmatch(r"%s(?:[ \t]*(?:->|\.)[ \t]*%s|\[[^\[\]]*\])+" % (ID, ID), e):
        return True
    if e.startswith("(") and _match_paren(e, 0) == len(e) - 1:
        return True
    return False


def _match_paren(s, i):
    d = 0
    for k in range(i, len(s)):
        if s[k] == "(":
            d += 1
        elif s[k] == ")":
            d -= 1
            if d == 0:
                return k
    return None


def _negate(c):
    """`!(c)` spelled the way a person would: one top-level comparison flipped."""
    c = c.strip()
    while c.startswith("(") and _match_paren(c, 0) == len(c) - 1:
        c = c[1:-1].strip()
    if "&&" in c or "||" in c or "?" in c:
        return "!(%s)" % c
    d, hits = 0, []
    k = 0
    while k < len(c):
        ch = c[k]
        if ch in "([":
            d += 1
        elif ch in ")]":
            d -= 1
        elif d == 0:
            two = c[k:k + 2]
            if two in ("==", "!=", "<=", ">="):
                hits.append((k, two))
                k += 2
                continue
            if ch in "<>" and c[k + 1:k + 2] != ch and c[k - 1:k] not in (ch, "-"):
                hits.append((k, ch))
        k += 1
    if len(hits) != 1:
        return "!(%s)" % c if not re.fullmatch(ID, c) else "!" + c
    k, op = hits[0]
    flip = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}[op]
    return c[:k].rstrip() + " " + flip + " " + c[k + len(op):].lstrip()


def _cond_of(line, kw="if"):
    """The text inside `kw ( ... )` on a masked line, and the index just past its `)`."""
    m = re.match(r"^[ \t]*%s[ \t]*\(" % kw, line)
    if not m:
        return None, None
    close = _match_paren(line, m.end() - 1)
    if close is None:
        return None, None
    return line[m.end():close], close + 1


def _prev_nb(ml, k):
    k -= 1
    while k >= 0 and not ml[k].strip():
        k -= 1
    return k if k >= 0 else None


def _next_nb(ml, k):
    k += 1
    while k < len(ml) and not ml[k].strip():
        k += 1
    return k if k < len(ml) else None


def _reindent(real_lines, old, new):
    out = []
    for ln in real_lines:
        s = _nl(ln)
        if not s.strip():
            out.append("")
        elif s.lstrip().startswith("#"):
            out.append(s)
        elif s.startswith(old):
            out.append(new + s[len(old):])
        else:
            out.append(new + s.lstrip())
    return out


# ------------------------------------------------------------------------------ fences

_DO_RE = re.compile(r"\bdo\s*\{")
_W0_RE = re.compile(r"\bwhile\s*\(\s*0\s*\)\s*\{")
_F0_RE = re.compile(r"\bfor\s*\(\s*;\s*0\s*;\s*\)\s*\{")
_DECL_START_RE = re.compile(r"^[ \t]*(?:(?:register|const|static|volatile|unsigned|signed|struct|union|enum)[ \t]+)*"
                            r"%s(?:[ \t]*\*+[ \t]*|[ \t]+)(?:\*+[ \t]*)?%s[ \t]*(?:\[[^\]]*\][ \t]*)?(?:=|;|,|ASM_REG)" % (ID, ID))


def fences(text):
    """[(start, end, body start, body end, line)] of every barrier census.py counts, in text order,
    except those in code no byte gate compiles (a NON_MATCHING or #if 0 arm)."""
    m = mask(text)
    labels = arm_labels(text) if HAS_PP_RE.search(text) else None
    out = []
    for rx in (_DO_RE, _W0_RE, _F0_RE):
        for mm in rx.finditer(m):
            ls = m.rfind("\n", 0, mm.start()) + 1
            if m[ls:mm.start()].lstrip().startswith("#"):
                continue
            ob = mm.end() - 1
            d, cb = 0, None
            for j in range(ob, len(m)):
                if m[j] == "{":
                    d += 1
                elif m[j] == "}":
                    d -= 1
                    if d == 0:
                        cb = j
                        break
            if cb is None:
                continue
            end = cb + 1
            if rx is _DO_RE:
                t = re.match(r"\s*while\s*\(\s*0\s*\)\s*;", m[cb + 1:cb + 48])
                if not t:
                    continue
                end = cb + 1 + t.end()
            line = m.count("\n", 0, mm.start())
            if labels and line < len(labels) and labels[line] in ("port", "dead"):
                continue
            out.append((mm.start(), end, ob + 1, cb, line + 1))
    return sorted(out)


def unwrap(text, f):
    """The text with one fence taken off.  An empty fence goes with its lines; a body that declares
    anything becomes a bare block (C89: no declaration after a statement; a bare block is honest -
    the study showed it is no barrier); any other body is dedented in place."""
    s, e, bs, be, _ = f
    m = mask(text)
    body = text[bs:be]
    ls = text.rfind("\n", 0, s) + 1
    le = text.find("\n", e)
    le = len(text) if le < 0 else le
    pre, post = text[ls:s], text[e:le]
    tail = text[le + 1:] if le < len(text) else ""
    if pre.strip() or post.strip() or any(
            _DECL_START_RE.match(ln) and re.match(ID, ln.strip()).group(0) not in CTRL
            for ln in m[bs:be].splitlines() if ln.strip()):
        return text[:s] + "{" + body + "}" + text[e:]
    if not body.strip():
        return text[:ls] + tail
    if "\n" not in body:
        return text[:ls] + pre + body.strip() + "\n" + tail
    parts = body.split("\n")
    head, mid, last = parts[0], parts[1:-1], parts[-1]
    keep = ([pre + head.strip()] if head.strip() else []) + mid + ([pre + last.strip()] if last.strip() else [])
    inner = [x for x in mid if x.strip() and not x.lstrip().startswith("#")]
    cut = max(0, min((len(x) - len(x.lstrip(" \t")) for x in inner), default=len(pre)) - len(pre))
    new = []
    for x in keep:
        if x.lstrip().startswith("#") or not x.strip():
            new.append(x.rstrip() if not x.strip() else x)
        elif x[:cut].strip() == "":
            new.append(x[cut:])
        else:
            new.append(pre + x.lstrip())
    while new and not new[0].strip():
        new.pop(0)
    while new and not new[-1].strip():
        new.pop()
    return text[:ls] + "\n".join(new) + "\n" + tail


# ------------------------------------------------------------------------------ 1. dropcopy

COPY_RE = re.compile(r"^(?P<i>[ \t]*)(?P<x>%s)[ \t]*=[ \t]*(?P<y>%s)[ \t]*;[ \t]*$" % (ID, ID))
YWRITE_RE = r"^(?P<i>[ \t]*)%s[ \t]*(?P<op><<|>>|[-+*/%%&|^])?=(?!=)[ \t]*(?P<e>[^;]+?)[ \t]*;[ \t]*$"
WHOLE_RHS_RE = r"^[ \t]*[^;=]+?(?:<<|>>|[-+*/%%&|^])?=(?!=)[ \t]*%s[ \t]*;[ \t]*$"


def dropcopy_candidates(text):
    t = _T(text)
    out = []
    for i, line in enumerate(t.m):
        cm = COPY_RE.match(line)
        decl_copy = False
        if cm:
            x, y = cm.group("x"), cm.group("y")
        else:
            dm = re.match(r"^[ \t]*(?:register[ \t]+)?%s[ \t*]+(?P<x>%s)[ \t]*=[ \t]*(?P<y>%s)[ \t]*;[ \t]*$" % (ID, ID, ID), line)
            if not dm or re.match(ID, line.strip()).group(0) in CTRL:
                continue
            x, y, decl_copy = dm.group("x"), dm.group("y"), True
        sp = t.span(i)
        if not sp or x == y or x in CTRL or y in CTRL:
            continue
        a, b = sp
        body = "\n".join(t.m[a:b + 1])
        di = i if decl_copy else _decl(t.m, a, b, x)[0]
        if di is None or di > i:
            continue
        if _writes(body, x) != 1 or _addr_taken(body, x) or _addr_taken(body, y):
            continue
        if not _is_local_or_param(t, a, b, y):
            continue
        ry, rx_ = _occ(y), _occ(x)
        drop, folds, pending, state = {i, di}, {}, None, "clean"
        bad = False
        for k in range(i + 1, b + 1):
            ln = t.m[k]
            occ = list(ry.finditer(ln))
            if not occ:
                if pending is not None and (re.search(r"[{}]", ln) or LABEL_RE.match(ln) or CONTROL_RE.match(ln)):
                    bad = True
                    break
                continue
            wm = re.match(YWRITE_RE % re.escape(y), ln)
            if wm:
                if state != "clean" or pending is not None:
                    bad = True
                    break
                if re.search(r"\b(?:do|while|for)\b|^[ \t]*%s[ \t]*:" % ID, "\n".join(t.m[i:k]), re.M):
                    bad = True           # a write inside a loop the copy sits outside of
                    break
                e = wm.group("e")
                e_real = _nl(t.lines[k])[wm.start("e"):wm.end("e")]
                e_real = rx_.sub(y, e_real) if rx_.search(e) else e_real
                pending = (k, "%s %s %s" % (y, wm.group("op"), e_real if _term(e_real) else "(%s)" % e_real)
                           if wm.group("op") else e_real)
                drop.add(k)
                continue
            if _writes(ln, y):
                bad = True
                break
            if pending is not None:
                if len(occ) != 1:
                    bad = True
                    break
                expr = pending[1]
                whole = re.match(WHOLE_RHS_RE % re.escape(y), ln)
                folds[k] = (occ[0].start(), occ[0].end(), expr if whole or _term(expr) else "(%s)" % expr)
                pending, state = None, "folded"
            elif state == "folded":
                bad = True
                break
        if bad or pending is not None:
            continue
        edits = {}
        for k in range(a, b + 1):
            if k in drop:
                continue
            ln_m, ln_r = t.m[k], _nl(t.lines[k])
            reps = [(o.start(), o.end(), y) for o in rx_.finditer(ln_m)]
            if k in folds:
                reps.append(folds[k])
            if not reps:
                continue
            for s0, e0, r in sorted(reps, reverse=True):
                ln_r = ln_r[:s0] + r + ln_r[e0:]
            edits[k] = ln_r
        pins = {k for k in range(a, b + 1) if k not in drop and PIN_STMT_RE.match(t.m[k])
                and re.search(r"\(\s*%s\s*\)" % re.escape(x), t.m[k])}
        out.append(("dropcopy:%s->%s" % (x, y), t.build(edits, drop | pins)))
        if pins:
            out.append(("dropcopy:%s->%s+pins" % (x, y), t.build(edits, drop)))
    return out


# ------------------------------------------------------------------------------ 2. armstore

IF_RE = re.compile(r"^(?P<i>[ \t]*)if[ \t]*\(.*\)[ \t]*\{[ \t]*$")
ELSE_RE = re.compile(r"^[ \t]*\}[ \t]*else[ \t]*\{[ \t]*$")
VASSIGN_RE = re.compile(r"^(?P<i>[ \t]*)(?P<v>%s)[ \t]*=(?!=)[ \t]*(?P<e>[^;]+?)[ \t]*;[ \t]*$" % ID)
STOREV_RE = re.compile(r"^(?P<i>[ \t]*)(?P<d>[^;]+?)[ \t]*=(?!=)[ \t]*(?P<v>%s)[ \t]*;[ \t]*$" % ID)


def _last_stmt(t, lo, hi):
    """Last line in lo..hi-1 that is neither blank nor a pin statement."""
    for k in range(hi - 1, lo - 1, -1):
        if t.m[k].strip() and not PIN_STMT_RE.match(t.m[k]):
            return k
    return None


def _compound(dest, e):
    """`D op K` -> `D op= K` when K is a single term, else None."""
    dn, en = _sq(dest), _sq(e)
    if not en.startswith(dn):
        return None
    k, seen = 0, 0
    while seen < len(dn):
        if not e[k].isspace():
            seen += 1
        k += 1
    rest = e[k:].strip()
    m = re.match(r"^(<<|>>|[|&^+\-*/%])(?![=|&+\-])[ \t]*(?P<k>.+)$", rest)
    if not m or not (_term(m.group("k")) or re.fullmatch(r"~[ \t]*(?:%s|%s|\(.*\))" % (ID, NUM), m.group("k").strip())):
        return None
    return "%s %s= %s" % (dest.strip(), m.group(1), m.group("k").strip())


def armstore_candidates(text):
    t = _T(text)
    out = []
    for i, line in enumerate(t.m):
        if not IF_RE.match(line):
            continue
        c1 = _close(t.m, i)
        if c1 is None:
            continue
        arms, n = [], None
        if ELSE_RE.match(t.m[c1]):
            c2 = _close(t.m, c1)
            if c2 is None:
                continue
            arms = [(i + 1, c1), (c1 + 1, c2)]
            n = _next_nb(t.m, c2)
        else:
            arms = [(i + 1, c1)]
            n = _next_nb(t.m, c1)
        if n is None:
            continue
        sm = STOREV_RE.match(t.m[n])
        if not sm or "=" in sm.group("d") or sm.group("d").rstrip()[-1:] in "!<>+-*/%&|^":
            continue
        v, dest_m = sm.group("v"), sm.group("d")
        dest = _nl(t.lines[n])[sm.start("d"):sm.end("d")].strip()
        if _occ(v).search(dest_m):
            continue
        sets = []
        for lo, hi in arms:
            k = _last_stmt(t, lo, hi)
            vm = VASSIGN_RE.match(t.m[k]) if k is not None else None
            if not vm or vm.group("v") != v:
                break
            e = _nl(t.lines[k])[vm.start("e"):vm.end("e")]
            if _occ(v).search(vm.group("e")):
                break
            sets.append((k, vm.group("i"), e))
        else:
            pre = None
            if len(arms) == 1:                    # `v = E0; if (c) { v = E1; } D = v;`
                p = _prev_nb(t.m, i)
                pm = VASSIGN_RE.match(t.m[p]) if p is not None else None
                if not pm or pm.group("v") != v or _occ(v).search(pm.group("e")):
                    continue
                pre = (p, _nl(t.lines[p])[pm.start("e"):pm.end("e")])
            for compound in (True, False):         # `D |= K` reads better than `D = D | K`: first
                edits, changed = {}, False
                for k, ind, e in sets:
                    c = _compound(dest, e) if compound else None
                    changed |= c is not None
                    edits[k] = ind + (c if c else "%s = %s" % (dest, e)) + ";"
                if compound and not changed:
                    continue
                drop, ins = {n}, {}
                if pre:
                    c = _compound(dest, pre[1]) if compound else None
                    ind = _ind(t.lines[i])
                    ins = {c1: [ind + "} else {", ind + "    " + (c if c else "%s = %s" % (dest, pre[1])) + ";"]}
                    edits[c1] = None
                    drop.add(pre[0])
                cand = _build_else(t, edits, drop, ins, c1 if pre else None)
                cand = _drop_dead_decl(cand, v, i)
                out.append(("armstore:%s%s%s" % (v, "|=" if compound else "", "+else" if pre else ""), cand))
    return out


def _build_else(t, edits, drop, ins, close_line):
    """t.build, where `close_line`'s `}` is re-emitted after the inserted else arm."""
    if close_line is None:
        return t.build(edits, drop)
    edits = dict(edits)
    edits.pop(close_line, None)
    extra = ins[close_line] + [_nl(t.lines[close_line])]
    return t.build(edits, set(drop) | {close_line}, {close_line: extra})


def _drop_dead_decl(text, v, near):
    """Delete v's own declaration line when nothing else in its function mentions v."""
    t = _T(text)
    sp = t.span(min(near, len(t.m) - 1))
    if not sp:
        return text
    a, b = sp
    k = _decl(t.m, a, b, v)[0]
    if k is None:
        return text
    if any(_occ(v).search(t.m[j]) for j in range(a, b + 1) if j != k):
        return text
    return t.build(drop={k})


# ------------------------------------------------------------------------------ 3. ret2break

LOOP_RE = re.compile(r"^(?P<i>[ \t]*)(?:for[ \t]*\((?P<fh>.*)\)|while[ \t]*\((?P<wc>.*)\)|(?P<do>do))[ \t]*\{[ \t]*$")
SWITCH_RE = re.compile(r"^[ \t]*switch[ \t]*\(.*\)[ \t]*\{[ \t]*$")
DOTAIL_RE = re.compile(r"^[ \t]*\}[ \t]*while[ \t]*\((?P<c>.*)\)[ \t]*;[ \t]*$")
RET_RE = re.compile(r"\breturn\b(?P<r>[^;]*);")


def _own_lines(t, i, c):
    """Lines of the loop body i..c that belong to it and not to a nested loop or switch."""
    own, k = [], i + 1
    while k < c:
        if LOOP_RE.match(t.m[k]) or SWITCH_RE.match(t.m[k]):
            e = _close(t.m, k)
            k = (e if e is not None else c) + 1
            continue
        own.append(k)
        k += 1
    return own


def ret2break_candidates(text):
    t = _T(text)
    out = []
    for i, line in enumerate(t.m):
        lm = LOOP_RE.match(line)
        if not lm:
            continue
        c = _close(t.m, i)
        if c is None:
            continue
        sp = t.span(i)
        if not sp:
            continue
        infinite = bool((lm.group("fh") is not None and _sq(lm.group("fh")) == ";;")
                        or (lm.group("wc") is not None and lm.group("wc").strip() == "1")
                        or (lm.group("do") and DOTAIL_RE.match(t.m[c]) and DOTAIL_RE.match(t.m[c]).group("c").strip() == "1"))
        own = _own_lines(t, i, c)
        if any(re.search(r"\bbreak\b", t.m[k]) for k in own):
            breaks = True
        else:
            breaks = False
        groups = {}
        for k in own:
            for m in RET_RE.finditer(t.m[k]):
                groups.setdefault(_sq(m.group("r")), []).append((k, m))
        n = _next_nb(t.m, c)
        for r, hits in groups.items():
            r_real = _nl(t.lines[hits[0][0]])[hits[0][1].start("r"):hits[0][1].end("r")].strip()
            ret = "return %s;" % r_real if r_real else "return;"
            ins = {}
            if n is not None and _sq(t.m[n]) == _sq(ret):
                pass
            elif infinite and not breaks:
                closes_fn = n is not None and n == sp[1] and t.m[n].strip() == "}"
                if r_real or not closes_fn:
                    ins = {c: [_ind(t.lines[i]) + ret]}
            else:
                continue
            edits = {}
            for k, m in hits:
                ln = edits.get(k, _nl(t.lines[k]))
                edits[k] = ln[:m.start()] + "break;" + ln[m.end():]
            out.append(("ret2break:%s" % (r_real or "void"), t.build(edits, (), ins)))
    return out


# ------------------------------------------------------------------------------ 4. ptr2index

PTRDECL_RE = re.compile(r"^(?P<i>[ \t]*)(?:(?:const|register)[ \t]+)*%s[ \t]*\*[ \t]*(?P<p>%s)[ \t]*=[ \t]*"
                        r"(?:\([^()]*\)[ \t]*)?(?P<a>&?%s(?:\[0\])?)[ \t]*;[ \t]*$" % (ID, ID, ID))
PTRSET_RE = re.compile(r"^(?P<i>[ \t]*)(?P<p>%s)[ \t]*=[ \t]*(?:\([^()]*\)[ \t]*)?(?P<a>&?%s(?:\[0\])?)[ \t]*;[ \t]*$" % (ID, ID))
INC_RE = re.compile(r"^[ \t]*(?:(?P<p>%s)[ \t]*(?:\+\+|\+=[ \t]*1)|\+\+[ \t]*(?P<q>%s))[ \t]*;[ \t]*$" % (ID, ID))


def _zero_before(t, a, loop, v):
    for k in range(loop - 1, a - 1, -1):
        if _occ(v).search(t.m[k]):
            return bool(re.match(r"^[ \t]*(?:[A-Za-z_][\w \t\*]*[ \t])?%s[ \t]*=[ \t]*0[ \t]*;[ \t]*$" % re.escape(v), t.m[k]))
    return False


def ptr2index_candidates(text):
    t = _T(text)
    out = []
    for L, line in enumerate(t.m):
        lm = LOOP_RE.match(line)
        if not lm:
            continue
        C = _close(t.m, L)
        sp = t.span(L)
        if C is None or not sp:
            continue
        a, b = sp
        body_m = "\n".join(t.m[L + 1:C])
        incs = {}
        for k in range(L + 1, C):
            m = INC_RE.match(t.m[k])
            if m:
                incs.setdefault(m.group("p") or m.group("q"), []).append(k)
        counters = {v: ks[0] for v, ks in incs.items()
                    if len(ks) == 1 and _writes(body_m, v) == 1 and _zero_before(t, a, L, v)}
        fh = lm.group("fh")
        if fh:
            parts = fh.split(";")
            if len(parts) == 3:
                im = re.fullmatch(r"[ \t]*(%s)[ \t]*=[ \t]*0[ \t]*" % ID, parts[0])
                sm = re.fullmatch(r"[ \t]*(?:(%s)[ \t]*(?:\+\+|\+=[ \t]*1)|\+\+[ \t]*(%s))[ \t]*" % (ID, ID), parts[2])
                if im and sm and im.group(1) == (sm.group(1) or sm.group(2)) and _writes(body_m, im.group(1)) == 0:
                    counters[im.group(1)] = C          # the header's step runs after the whole body
        ptrs = []
        for p, ks in incs.items():
            if p in counters or len(ks) != 1 or _writes(body_m, p) != 1:
                continue
            pi = next((k for k in range(L - 1, a - 1, -1) if _occ(p).search(t.m[k])), None)
            if pi is None:
                continue
            dm, sm = PTRDECL_RE.match(t.m[pi]), PTRSET_RE.match(t.m[pi])
            m = dm or sm
            if not m or m.group("p") != p:
                continue
            base = m.group("a")
            if base.startswith("&"):
                if not base.endswith("[0]"):
                    continue
                base = base[1:-3]
            if any(_occ(p).search(t.m[k]) for k in range(C, b + 1)):
                continue                      # read after the loop: the pointer's value is used
            decl = None
            if not dm:
                decl = _decl(t.m, a, b, p)[0]
                if decl is None or decl > pi:
                    continue
            ptrs.append((p, ks[0], pi, base, decl))
        for cnt, li in counters.items():
            for chosen in ([ptrs] if len(ptrs) > 1 else []) + [[q] for q in ptrs]:
                cand = _ptr2index(t, L, C, cnt, li, chosen)
                if cand:
                    out.append(("ptr2index:%s[%s]" % ("+".join(q[0] for q in chosen), cnt), cand))
    return out


def _ptr2index(t, L, C, cnt, li, chosen):
    edits, drop = {}, set()
    for p, lp, pi, base, decl in chosen:
        drop |= {lp, pi} | ({decl} if decl is not None else set())
        rx = _occ(p)
        for u in range(L + 1, C + 1):
            if u == lp:
                continue
            ln_m = t.m[u]
            hits = list(rx.finditer(ln_m))
            if not hits:
                continue
            ln = edits.get(u, _nl(t.lines[u]))
            off = (1 if u > lp else 0) - (1 if u > li else 0)
            idx = cnt if off == 0 else "%s %s 1" % (cnt, "+" if off > 0 else "-")
            for h in reversed(hits):
                s0, e0 = h.start(), h.end()
                before = ln_m[:s0].rstrip()
                after = ln_m[e0:]
                if re.match(r"[ \t]*(?:\+\+|--|[-+*/%&|^]?=(?!=))", after):
                    return None
                if before.endswith("*") and (len(before) == 1 or before[:-1].rstrip()[-1:] in "(,=+-*/%&|^!~<>?:;{["):
                    star = len(before) - 1
                    ln = ln[:star] + "%s[%s]" % (base, idx) + ln[e0:]
                    continue
                am = re.match(r"[ \t]*\[(?P<k>[^\[\]]+)\]", after)
                if am:
                    ln = ln[:s0] + "%s[%s + %s]" % (base, idx, am.group("k").strip()) + ln[e0 + am.end():]
                    continue
                if re.match(r"[ \t]*->", after):
                    arrow = e0 + after.index("->")
                    ln = ln[:s0] + "%s[%s]." % (base, idx) + ln[arrow + 2:].lstrip()
                    continue
                ln = ln[:s0] + "&%s[%s]" % (base, idx) + ln[e0:]
            edits[u] = ln
    return t.build(edits, drop)


# ------------------------------------------------------------------------------ 5. postinc

INCSTMT_RE = re.compile(r"^(?P<i>[ \t]*)(?:(?P<p>%s)[ \t]*(?:\+\+|\+=[ \t]*1)|\+\+[ \t]*(?P<q>%s)|(?P<r>%s)[ \t]*=[ \t]*(?P=r)[ \t]*\+[ \t]*1)[ \t]*;[ \t]*$" % (ID, ID, ID))


def _postinc_at(ln_real, ln_m, s0, e0):
    """The line with the mention at s0..e0 rewritten as a post-increment, or None."""
    name = ln_real[s0:e0]
    before, after = ln_m[:s0].rstrip(), ln_m[e0:]
    if re.match(r"[ \t]*(?:\+\+|--|[-+*/%&|^]?=(?!=))", after) or before.endswith(("++", "--")):
        return None
    if re.match(r"[ \t]*->", after) or re.match(r"[ \t]*\[", after) or re.match(r"[ \t]*\.", after):
        return ln_real[:s0] + "(%s++)" % name + ln_real[e0:]
    return ln_real[:s0] + "%s++" % name + ln_real[e0:]


def postinc_candidates(text):
    t = _T(text)
    out = []
    for j, line in enumerate(t.m):
        im = INCSTMT_RE.match(line)
        if not im:
            continue
        p = im.group("p") or im.group("q") or im.group("r")
        rx = _occ(p)
        u = None
        for k in range(j - 1, max(j - 8, -1), -1):
            s = t.m[k]
            if not s.strip():
                continue
            if "{" in s or "}" in s or LABEL_RE.match(s) or s.lstrip().startswith("#") or CONTROL_RE.match(s):
                break
            if rx.search(s):
                u = k
                break
        if u is None or PIN_STMT_RE.match(t.m[u]):
            continue
        hits = list(rx.finditer(t.m[u]))
        if len(hits) != 1:
            continue
        new_u = _postinc_at(_nl(t.lines[u]), t.m[u], hits[0].start(), hits[0].end())
        if new_u is None:
            continue
        out.append(("postinc:%s" % p, t.build({u: new_u}, {j})))
        # the once-read temp the increment's load feeds, folded into its single use
        vm = VASSIGN_RE.match(t.m[u])
        sp = t.span(u)
        if not vm or not sp or vm.group("v") == p:
            continue
        tmp, (a, b) = vm.group("v"), sp
        dk = _decl(t.m, a, b, tmp)[0]
        uses = [k for k in range(a, b + 1) if k not in (u, dk) and _occ(tmp).search(t.m[k])]
        if dk is None or len(uses) != 1 or uses[0] < u or len(_occ(tmp).findall(t.m[uses[0]])) != 1:
            continue
        w = uses[0]
        if _writes(t.m[w], tmp) or any("{" in t.m[k] or "}" in t.m[k] or LABEL_RE.match(t.m[k]) for k in range(u + 1, w)):
            continue
        e_new = new_u[len(vm.group("i")) + (vm.start("e") - len(vm.group("i"))):].rstrip()
        e_new = e_new[:e_new.rfind(";")].rstrip()
        h = _occ(tmp).search(t.m[w])
        whole = re.match(WHOLE_RHS_RE % re.escape(tmp), t.m[w])
        expr = e_new if whole or _term(e_new) else "(%s)" % e_new
        used = _nl(t.lines[w])
        used = used[:h.start()] + expr + used[h.end():]
        at_def = _ind(t.lines[u]) + used.strip()
        out.append(("postinc:%s+fold:%s" % (p, tmp), t.build({u: at_def}, {j, w, dk})))
        out.append(("postinc:%s+fold:%s@use" % (p, tmp), t.build({w: used}, {j, u, dk})))
    return out


# ------------------------------------------------------------------------------ 6. gotoloop

def _labels_gotos(ml):
    labels, gotos = {}, {}
    for k, s in enumerate(ml):
        m = LABEL_RE.match(s)
        if m and m.group("l") not in ("default",):
            labels[m.group("l")] = k
        for g in re.finditer(r"\bgoto[ \t]+(%s)[ \t]*;" % ID, s):
            gotos.setdefault(g.group(1), []).append(k)
    return labels, gotos


def _plain_region(ml, lo, hi):
    """lo..hi-1 carries no label and no goto and its braces balance."""
    d = 0
    for k in range(lo, hi):
        s = ml[k]
        if LABEL_RE.match(s) or re.search(r"\bgoto\b", s):
            return False
        d += s.count("{") - s.count("}")
        if d < 0:
            return False
    return d == 0


def _if_jump(ml, k, target_kw):
    """An `if (C) <jump>;` ending on line k, one-line or braced: (first line, C, jump text)."""
    s = ml[k]
    rx = r"(?:goto[ \t]+%s|return\b[^;]*)[ \t]*;" % ID if target_kw == "any" else r"goto[ \t]+%s[ \t]*;" % ID
    cond, end = _cond_of(s)
    if cond is not None and re.fullmatch(r"[ \t]*(%s)[ \t]*" % rx, s[end:]):
        return k, cond, s[end:].strip()
    if s.strip() != "}":
        return None
    j = _prev_nb(ml, k)
    i = _prev_nb(ml, j) if j is not None else None
    if i is None or not re.fullmatch(r"[ \t]*(%s)[ \t]*" % rx, ml[j]):
        return None
    cond, end = _cond_of(ml[i])
    if cond is None or ml[i][end:].strip() != "{":
        return None
    return i, cond, ml[j].strip()


def gotoloop_candidates(text):
    t = _T(text)
    ml, out = t.m, []
    labels, gotos = _labels_gotos(ml)
    # (a) a statement both arms end with, moved after the join label
    for lab, k3 in labels.items():
        g = gotos.get(lab, [])
        if len(g) != 1 or g[0] > k3 or not GOTO_LINE_RE.match(ml[g[0]]):
            continue
        ga = g[0]
        pa, pb, pairs = _prev_nb(ml, ga), _prev_nb(ml, k3), []
        while (pa is not None and pb is not None and pa != pb and pa > ga - 6 and pb > ga
               and movable(ml[pa]) and movable(ml[pb]) and _sq(ml[pa]) == _sq(ml[pb]) and len(pairs) < 3):
            pairs.append((pa, pb))
            pa, pb = _prev_nb(ml, pa), _prev_nb(ml, pb)
        if not pairs:
            continue
        moved = [_nl(t.lines[b_]) for _, b_ in reversed(pairs)]
        drop = {x for pr in pairs for x in pr}
        out.append(("gotoloop:join:%s" % lab, t.build({}, drop, {k3: moved})))
    # (b) m2c's diamond loop -> do { head; if (!C) { A } else { B } tail } while (!E);
    for top, t0 in labels.items():
        g = gotos.get(top, [])
        if len(g) != 1 or g[0] < t0 or not GOTO_LINE_RE.match(ml[g[0]]):
            continue
        gl = g[0]
        ex_end = _prev_nb(ml, gl)
        ex = _if_jump(ml, ex_end, "any") if ex_end is not None else None
        if not ex:
            continue
        es, E, jump = ex
        k3 = _prev_nb(ml, es)
        lm3 = LABEL_RE.match(ml[k3]) if k3 is not None else None
        if lm3:
            cands = _diamond(t, labels, gotos, t0, gl, es, E, jump, k3, lm3.group("l"))
            out.extend(cands)
        # (c) top: body; if (E) goto top;  ->  do { body } while (E);
    for top, t0 in labels.items():
        g = gotos.get(top, [])
        if len(g) != 1 or g[0] <= t0:
            continue
        ij = _if_jump(ml, g[0], "goto")
        if not ij or ij[2] != "goto %s;" % top:
            continue
        i0, E, _ = ij
        if not _plain_region(ml, t0 + 1, i0):
            continue
        ind = _ind(t.lines[_next_nb(ml, t0)]) if _next_nb(ml, t0) is not None else "    "
        body = _reindent(t.lines[t0 + 1:i0], ind, ind + "    ")
        new = [ind + "do {"] + body + [ind + "} while (%s);" % _real_cond(t, i0, E)]
        out.append(("gotoloop:do:%s" % top, _replace_block(t, t0, g[0], new)))
    return out


def _real_cond(t, k, cond_m):
    """The real text of a condition found on masked line k."""
    s = t.m[k]
    at = s.find(cond_m)
    return _nl(t.lines[k])[at:at + len(cond_m)].strip() if at >= 0 else cond_m.strip()


def _replace_block(t, lo, hi, new_lines):
    lines = [_nl(x) for x in t.lines]
    tail_nl = t.text.endswith("\n")
    out = lines[:lo] + new_lines + lines[hi + 1:]
    return "\n".join(out) + ("\n" if tail_nl else "")


def _diamond(t, labels, gotos, t0, gl, es, E, jump, k3, L3):
    ml = t.m
    g3 = gotos.get(L3, [])
    if len(g3) != 1 or not (t0 < g3[0] < k3) or not GOTO_LINE_RE.match(ml[g3[0]]):
        return []
    ga = g3[0]
    k2 = _next_nb(ml, ga)
    lm2 = LABEL_RE.match(ml[k2]) if k2 is not None else None
    if not lm2:
        return []
    L2 = lm2.group("l")
    g2 = gotos.get(L2, [])
    if len(g2) != 1 or not (t0 < g2[0] < ga):
        return []
    ig = g2[0]
    if GOTO_LINE_RE.match(ml[ig]):
        j = _next_nb(ml, ig)
        ij = _if_jump(ml, j, "goto") if j is not None else None
        if not ij:
            return []
        is_, C, _ = ij
        ie = j
    else:
        ij = _if_jump(ml, ig, "goto")
        if not ij:
            return []
        is_, C, _ = ij
        ie = ig
    if not (_plain_region(ml, t0 + 1, is_) and _plain_region(ml, ie + 1, ga) and _plain_region(ml, k2 + 1, k3)):
        return []
    A = [k for k in range(ie + 1, ga) if ml[k].strip()]
    B = [k for k in range(k2 + 1, k3) if ml[k].strip()]
    tail = []
    while (A and B and len(tail) < 3 and movable(ml[A[-1]]) and movable(ml[B[-1]])
           and _sq(ml[A[-1]]) == _sq(ml[B[-1]])):
        tail.insert(0, B[-1])
        A, B = A[:-1], B[:-1]
    first = _next_nb(ml, t0)
    ind = _ind(t.lines[first]) if first is not None else "    "
    in1, in2 = ind + "    ", ind + "        "
    Cr, Er = _real_cond(t, is_, C), _real_cond(t, es, E)
    head = _reindent(t.lines[t0 + 1:is_], ind, in1)
    a_ = _reindent([t.lines[k] for k in A], ind, in2)
    b_ = _reindent([t.lines[k] for k in B], ind, in2)
    tl = _reindent([t.lines[k] for k in tail], ind, in1)
    after = []
    if jump.startswith("return"):
        r = jump[len("return"):].rstrip(";").strip()
        n = _next_nb(ml, gl)
        sp = t.span(gl)
        if r or not (n is not None and sp and n == sp[1]):
            after = [ind + jump]
    else:
        lx = re.match(r"goto[ \t]+(%s)" % ID, jump).group(1)
        n = _next_nb(ml, gl)
        if n is None or not LABEL_RE.match(ml[n]) or LABEL_RE.match(ml[n]).group("l") != lx:
            return []
    out = []
    for flip in (False, True):
        if not a_ and not b_:
            arms = []
        elif not flip:
            arms = ([in1 + "if (%s) {" % _negate(Cr)] + (a_ or [])
                    + ([in1 + "} else {"] + b_ if b_ else []) + [in1 + "}"]) if a_ else \
                   [in1 + "if (%s) {" % Cr] + b_ + [in1 + "}"]
        else:
            if not (a_ and b_):
                continue
            arms = [in1 + "if (%s) {" % Cr] + b_ + [in1 + "} else {"] + a_ + [in1 + "}"]
        new = [ind + "do {"] + head + arms + tl + [ind + "} while (%s);" % _negate(Er)] + after
        out.append(("gotoloop:%s%s" % (top_name(ml, t0), "+swap" if flip else ""), _replace_block(t, t0, gl, new)))
    return out


def top_name(ml, t0):
    return LABEL_RE.match(ml[t0]).group("l")


# ------------------------------------------------------------------------------ 7. basesym

PAGE_RE = re.compile(r"^(?P<i>[ \t]*)(?P<decl>(?:(?:const|volatile|register)[ \t]+)*%s[ \t]*\*+[ \t]*)?(?P<v>%s)[ \t]*=[ \t]*"
                     r"\((?P<t>[^()]*\*)[ \t]*\)[ \t]*0x(?P<a>8[0-9A-Fa-f]{7})[ \t]*;[ \t]*$" % (ID, ID))
LIT_RE = re.compile(r"\((?P<t>[^()]*\*)[ \t]*\)[ \t]*0x(?P<a>8[0-9A-Fa-f]{7})(?:[ \t]*\+[ \t]*(?P<k>%s)(?![ \t]*[*/%%\w(\[]))?" % NUM)
_HEADER_SYMS = None


def _header_syms():
    global _HEADER_SYMS
    if _HEADER_SYMS is None:
        found = set()
        for p in (ROOT / "include").rglob("*.h"):
            found |= set(re.findall(r"\b(?:D|func)_[0-9A-F]{8}\b", p.read_text(errors="replace")))
        _HEADER_SYMS = found
    return _HEADER_SYMS


def _pointee(ty):
    """Byte size of what a pointer type points at, or None."""
    ty = ty.replace("const", "").replace("volatile", "").replace("register", "").strip()
    if ty.count("*") > 1:
        return 4
    base = ty.rstrip("* \t").split()
    return SIZE.get(base[-1]) if base else None


def _sym(text, addr):
    """The name for an absolute address: the file's own `func_X` if it names one, else `D_X`."""
    f = "func_%08X" % addr
    return f if re.search(r"\b%s\b" % f, text) else "D_%08X" % addr


def _declare(text, name, before):
    """`extern u8 name;` added unless `before` - the text the edit started from - or a header
    already declares it.  (Asking the edited text always finds the new use: the first sweep lost
    every candidate that needed a fresh symbol to "undeclared" that way.)"""
    if re.search(r"\b%s\b" % name, before) or name in _header_syms() or name.startswith("func_"):
        return text
    lines = text.splitlines(True)
    last = max((i for i, l in enumerate(lines) if l.startswith("extern ")), default=None)
    if last is None:
        last = max((i for i, l in enumerate(lines) if l.startswith("#include")), default=-1)
    lines.insert(last + 1, "extern u8 %s;\n" % name)
    return "".join(lines)


def basesym_candidates(text):
    t = _T(text)
    out = []
    for i, line in enumerate(t.m):
        pm = PAGE_RE.match(line)
        if not pm:
            continue
        sp = t.span(i)
        if not sp:
            continue
        a, b = sp
        v, page = pm.group("v"), int(pm.group("a"), 16)
        vk, vty, _ = _decl(t.m, a, b, v) if not pm.group("decl") else (i, pm.group("decl").strip(), None)
        vty = vty or pm.group("t")
        rv = _occ(v)
        body = "\n".join(t.m[a:b + 1])
        # (a) v = page; [pins on v]; v = (T *)v + K;  ->  v = &D_<page + K>;
        #     (also `v -= K`, `v -= -K` - main/func_80013B18 spells +0x7E68 that way)
        j, pins = None, set()
        for k in range(i + 1, b + 1):
            if not rv.search(t.m[k]):
                continue
            if PIN_STMT_RE.match(t.m[k]) and re.search(r"[(,]\s*%s\s*[,)]" % re.escape(v), t.m[k]):
                pins.add(k)
                continue
            j = k
            break
        if j is not None:
            s = t.m[j]
            m1 = re.match(r"^(?P<i>[ \t]*)%s[ \t]*=[ \t]*(?:\((?P<c1>[^()]*)\)[ \t]*)?\(?[ \t]*(?:\((?P<c2>[^()]*\*)[ \t]*\)[ \t]*)?%s[ \t]*(?P<op>[-+])[ \t]*(?P<k>-?[ \t]*%s)[ \t]*\)?[ \t]*;[ \t]*$" % (re.escape(v), re.escape(v), NUM), s)
            m2 = re.match(r"^(?P<i>[ \t]*)%s[ \t]*(?P<op>[-+])=[ \t]*(?P<k>-?[ \t]*%s)[ \t]*;[ \t]*$" % (re.escape(v), NUM), s)
            m = m1 or m2
            if m:
                scale = _pointee(m.group("c2")) if m1 and m.group("c2") else _pointee(vty)
                kval = int(re.sub(r"\s+", "", m.group("k")), 0) * (1 if m.group("op") == "+" else -1)
                if scale and 0x80000000 <= page + kval * scale < 0x81000000:
                    name = _sym(text, page + kval * scale)
                    cast = (m1.group("c1") if m1 and m1.group("c1") else vty).strip()
                    rhs = ("&%s" % name) if _sq(cast) in ("void*",) else "(%s)&%s" % (cast, name)
                    edits = {j: m.group("i") + "%s = %s;" % (v, rhs)}
                    drop = set(pins)
                    if pm.group("decl"):
                        edits[i] = pm.group("i") + pm.group("decl").rstrip() + ("" if pm.group("decl").rstrip().endswith("*") else " ") + v + ";"
                    else:
                        drop.add(i)
                    out.append(("basesym:%s=%s" % (v, name), _declare(t.build(edits, drop), name, text)))
        # (b) a base assigned once: every `(T *)v + K`, `v + K`, `v[K]` -> the symbol at the sum
        if _writes(body, v) != 1 or _addr_taken(body, v):
            continue
        edits, pins, dynamic, names = {}, set(), False, []
        for k in range(i + 1, b + 1):
            s = t.m[k]
            hits = list(rv.finditer(s))
            if not hits:
                continue
            if PIN_STMT_RE.match(s) and re.search(r"[(,]\s*%s\s*[,)]" % re.escape(v), s):
                pins.add(k)
                continue
            ln = _nl(t.lines[k])
            for h in reversed(hits):
                s0, e0 = h.start(), h.end()
                before, after = s[:s0], s[e0:]
                cm = re.search(r"\((?P<c>[^()]*\*)[ \t]*\)[ \t]*$", before)
                km = re.match(r"[ \t]*\+[ \t]*(?P<k>%s)(?![ \t]*[*/%%\w(\[])" % NUM, after)
                im = re.match(r"[ \t]*\[[ \t]*(?P<k>%s)[ \t]*\]" % NUM, after)
                lead = (before[:cm.start()] if cm else before).rstrip()
                if km and (not lead or lead[-1] in "(=,{;"):
                    cast = cm.group("c").strip() if cm else vty
                    scale = _pointee(cast)
                    if not scale:
                        dynamic = True
                        continue
                    name = _sym(text, page + int(km.group("k"), 0) * scale)
                    names.append(name)
                    rep = "(%s)&%s" % (cast, name)
                    ln = ln[:cm.start() if cm else s0] + rep + ln[e0 + km.end():]
                elif im and not re.match(r"[ \t]*\[[^\]]*\][ \t]*(?:\+\+|--)", after):
                    scale = _pointee(vty)
                    if not scale:
                        dynamic = True
                        continue
                    name = _sym(text, page + int(im.group("k"), 0) * scale)
                    names.append(name)
                    elem = vty.rstrip().rstrip("*").strip() or "u8"
                    rep = "*(%s *)&%s" % (elem, name) if not (elem in ("u8",) and name.startswith("D_")) else name
                    ln = ln[:s0] + rep + ln[e0 + im.end():]
                else:
                    dynamic = True
            edits[k] = ln
        if not names:
            continue
        for full in ((False, True) if not dynamic else (False,)):
            drop = set(pins)
            e2 = dict(edits)
            if full:
                drop.add(i)
                if vk is not None and vk != i:
                    drop.add(vk)
            cand = t.build(e2, drop if full else set())
            for nm in sorted(set(names)):
                cand = _declare(cand, nm, text)
            out.append(("basesym:%s%s" % (v, "" if full else "+keep"), cand))
    # (c) inline literals: `(T *)0x8XXXYYYY` (low half set) or `(T *)0x8XXX0000 + K`
    groups = {}
    for k, s in enumerate(t.m):
        if PAGE_RE.match(s):
            continue
        for m in LIT_RE.finditer(s):
            addr = int(m.group("a"), 16)
            if not m.group("k") and addr & 0xFFFF == 0:
                continue
            scale = _pointee(m.group("t")) if m.group("k") else 1
            if not scale:
                continue
            name = _sym(text, addr + (int(m.group("k"), 0) * scale if m.group("k") else 0))
            groups.setdefault(name, []).append((k, m.start(), m.end(), "(%s)&%s" % (m.group("t").strip(), name)))
    for name, hits in groups.items():
        edits = {}
        for k, s0, e0, rep in sorted(hits, key=lambda h: (h[0], -h[1])):
            ln = edits.get(k, _nl(t.lines[k]))
            edits[k] = ln[:s0] + rep + ln[e0:]
        out.append(("basesym:lit=%s" % name, _declare(t.build(edits), name, text)))
    return out


# ------------------------------------------------------------------------------ the menu

GENERATORS = (dropcopy_candidates, armstore_candidates, ret2break_candidates, ptr2index_candidates,
              postinc_candidates, gotoloop_candidates)


def candidates(text, basesym=True):
    """Every natural-shape candidate for a text, deduplicated, the input itself excluded."""
    out, seen = [], {text}
    for gen in GENERATORS + ((basesym_candidates,) if basesym else ()):
        try:
            got = gen(text)
        except Exception:                  # a generator bug must cost its own candidates only
            continue
        for label, cand in got:
            if cand not in seen:
                seen.add(cand)
                out.append((label, cand))
    return out
