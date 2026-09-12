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
import bisect, re, sys
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
    # (d) top: BODY; if (C) { X; goto top; }  ->  do { BODY; if (!C) { break; } X; } while (1);
    out.extend((lab, cand) for lab, cand, _ in _loop_d(t, labels, gotos))
    return out


def _loop_d(t, labels, gotos):
    """m2c's loop whose back edge sits at the end of an if-block, as the real loop it was.

    A native lane on the scratchpad class (dungeon/func_800942BC, 2026-09-12): gcc's loop pass calls
    m2c's goto loop "phony" and does nothing with it, so the loop-invariant substitution loop.c
    performs in a real loop with a call (a single-use invariant temporary folded into its one use,
    before combine) never happens - and combine then turns `addu base,K` into `ori` on a constant
    base, which is what the pin was hiding.  Written as the real `do { ... } while (1);` the row
    matched with no pin.  Yields (label, text, (first line, last line) of the new loop)."""
    ml, out = t.m, []
    for top, t0 in labels.items():
        g = gotos.get(top, [])
        if not g or max(g) <= t0:
            continue
        gl = max(g)
        if not GOTO_LINE_RE.match(ml[gl]):
            continue
        close = _next_nb(ml, gl)
        if close is None or ml[close].strip() != "}":
            continue
        d, opener = 0, None
        for k in range(close, t0, -1):
            d += ml[k].count("}") - ml[k].count("{")
            if d == 0:
                opener = k
                break
        if opener is None or opener <= t0:
            continue
        cond, end = _cond_of(ml[opener])
        if cond is None or ml[opener][end:].strip() != "{":
            continue
        nxt = _next_nb(ml, close)
        if nxt is not None and re.match(r"^[ \t]*else\b", ml[nxt]):
            continue
        others = [k for k in g if k != gl]
        if any(not (t0 < k < opener) for k in others):
            continue                          # a jump to the top from outside the body
        region = range(t0 + 1, gl)
        if any(LABEL_RE.match(ml[k]) for k in region):
            continue                          # another entry into the loop
        if any(re.search(r"\b(?:break|continue)\b", ml[k]) for k in region):
            continue                          # would re-bind to the new loop
        if others and any(re.match(r"^[ \t]*(?:do|while|for)\b", ml[k]) for k in range(t0 + 1, opener)):
            continue                          # a `continue` inside a nested loop would bind there
        dd = 0
        for k in range(t0 + 1, opener):
            dd += ml[k].count("{") - ml[k].count("}")
            if dd < 0:
                break
        if dd != 0:
            continue
        first = _next_nb(ml, t0)
        ind = _ind(t.lines[first]) if first is not None and first < opener else _ind(t.lines[opener])
        in1, in2 = ind + "    ", ind + "        "
        body = [re.sub(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(top), "continue;", x)
                for x in _reindent(t.lines[t0 + 1:opener], ind, in1)]
        xin = _ind(t.lines[opener + 1]) if opener + 1 < gl else in1
        x = _reindent(t.lines[opener + 1:gl], xin, in1)
        C = _real_cond(t, opener, cond)
        new = [ind + "do {"] + body + [in1 + "if (%s) {" % _negate(C), in2 + "break;", in1 + "}"] + x + [ind + "} while (1);"]
        out.append(("gotoloop:loop:%s" % top, _replace_block(t, t0, close, new), (t0, t0 + len(new) - 1)))
    return out


def realloop_candidates(text):
    """`gotoloop` (d) together with the pins inside the new loop erased - all of them, then each alone.

    The real loop is what makes those pins unnecessary (loop.c's invariant handling and the
    loop-depth weighting of every reference inside it), so a pin pass needs the pair, not the
    restructure on its own (which removes no pin)."""
    try:
        from pin_sites import erase_many
        from pin_census import sites_of
    except ImportError:                   # pragma: no cover
        return []
    t = _T(text)
    labels, gotos = _labels_gotos(t.m)
    out = []
    for label, cand, (lo, hi) in _loop_d(t, labels, gotos):
        # a pin inside the new loop, or one that names a variable the loop uses: 800942BC's pin is
        # `ASM_KEEP(scratch);` just ABOVE the label - it hides the loop's constant base
        cm = mask(cand).splitlines()
        used = set(re.findall(ID, "\n".join(cm[lo:hi + 1])))
        inside = []
        for s in sites_of(cand):
            if lo + 1 <= s[5] <= hi + 1:
                inside.append(s)
            elif s[0] == "stmt" and set(re.findall(ID, s[2])) & used:
                inside.append(s)
            elif s[0] == "reg":
                m = re.search(r"(%s)\s*$" % ID, cand[s[3]:s[4]].split("ASM_REG")[0])
                if m and m.group(1) in used:
                    inside.append(s)
        if not inside:
            continue
        out.append((label.replace("gotoloop:loop", "realloop") + "+all", erase_many(cand, inside, clean_notes=True)))
        if len(inside) > 1:
            for s in inside[:6]:
                out.append((label.replace("gotoloop:loop", "realloop") + "+" + s[1], erase_many(cand, [s], clean_notes=True)))
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

# the pointer cast is optional: an integer local takes the page uncast (town/func_8080C324, agy
# batch 6: `offset_addr = 0x80530000; ... offset_addr += 0x6D6;` -> `(s32)&D_805306D6`) or through an
# integer cast (dungeon/func_8132A730, agy pack 2: `resource_addr = (s32)0x80170000; ... += 0x1D90;`
# -> `(s32)D_80171D90`); both are byte arithmetic on an integer local
PAGE_RE = re.compile(r"^(?P<i>[ \t]*)(?P<decl>(?:(?:const|volatile|register|unsigned|signed)[ \t]+)*%s(?:[ \t]*\*+[ \t]*|[ \t]+))?(?P<v>%s)[ \t]*=[ \t]*"
                     r"(?:\((?P<t>[^()]*\*)[ \t]*\)[ \t]*|\((?P<ic>(?:signed[ \t]+|unsigned[ \t]+)?(?:s32|u32|int|long|unsigned|unsigned[ \t]+long|M2C_UNK))[ \t]*\)[ \t]*)?"
                     r"0x(?P<a>8[0-9A-Fa-f]{7})[ \t]*;[ \t]*$" % (ID, ID))
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


def _scale(ty):
    """Bytes one unit of `v + K` adds: the pointee for a pointer, 1 for an integer."""
    return _pointee(ty) if "*" in ty else 1


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
        if not vty or (not pm.group("t") and "*" in vty):
            continue                  # an uncast literal only ever fills an integer local
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
            # the close paren may follow the variable (`((u8 *) v) + 0x3460`, dungeon/func_800A7828 -
            # found by the permuter trial) or the offset (`(u8 *)(v + K)`)
            m1 = re.match(r"^(?P<i>[ \t]*)%s[ \t]*=[ \t]*(?:\((?P<c1>[^()]*)\)[ \t]*)?\(?[ \t]*(?:\((?P<c2>[^()]*\*)[ \t]*\)[ \t]*)?%s[ \t]*\)?[ \t]*(?P<op>[-+])[ \t]*(?P<k>-?[ \t]*%s)[ \t]*\)?[ \t]*;[ \t]*$" % (re.escape(v), re.escape(v), NUM), s)
            m2 = re.match(r"^(?P<i>[ \t]*)%s[ \t]*(?P<op>[-+])=[ \t]*(?P<k>-?[ \t]*%s)[ \t]*;[ \t]*$" % (re.escape(v), NUM), s)
            m = m1 or m2
            if m:
                scale = _pointee(m.group("c2")) if m1 and m.group("c2") else _scale(vty)
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
                    scale = _pointee(cast) if cm else _scale(vty)
                    if not scale:
                        dynamic = True
                        continue
                    name = _sym(text, page + int(km.group("k"), 0) * scale)
                    names.append(name)
                    rep = "(%s)&%s" % (cast, name)
                    ln = ln[:cm.start() if cm else s0] + rep + ln[e0 + km.end():]
                elif im and "*" in vty and not re.match(r"[ \t]*\[[^\]]*\][ \t]*(?:\+\+|--)", after):
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


# ------------------------------------------------------------------------------ 8. splitcursor

STEP_RE = r"^(?P<i>[ \t]*)%s[ \t]*=(?!=)[ \t]*(?P<e>[^;]+?)[ \t]*;[ \t]*$"


def splitcursor_candidates(text):
    """One name per step of a chain, where m2c reused one cursor: `v = E0; ... v = f(v); ...
    v = g(v);` -> `v = E0; ... v2 = f(v); ... v3 = g(v2);`, reads renamed up to the next step.

    From a research pass over ygofm-decomp's measured workflow (cc1psx 2.8.1): "a chain of pointer
    steps wants one name per step, not one cursor ... five distinct locals, each assigned once,
    gives five short-lived pseudos that ping-pong through $v0/$v1 the way retail does" (34 -> 7 on
    one row; fully inlining the chain was worse).  The reused cursor is one long-lived pseudo -
    exactly what a register pin on it stands in for - so the variable's pin comes off with it.
    Straight-line chains only (no label, loop or brace change between the steps) and nothing
    writes the variable after its last step, so the renaming cannot change behaviour.  At the pin
    census (2026-09-12): 171 pinned variables in 115 rows are stepped this way.
    """
    t = _T(text)
    out = []
    for a, b in t.spans:
        body = "\n".join(t.m[a:b + 1])
        seen = set()
        for k in range(a, b + 1):
            for cand in re.findall(r"\b(%s)\b" % ID, t.m[k]):
                if cand in seen or cand in CTRL:
                    continue
                seen.add(cand)
                di, ty, init = _decl(t.m, a, b, cand)
                if di is None or init or _addr_taken(body, cand):
                    continue
                v = cand
                rx = _occ(v)
                writes = [j for j in range(di + 1, b + 1) if re.match(STEP_RE % re.escape(v), t.m[j])]
                steps = [j for j in writes if rx.search(re.match(STEP_RE % re.escape(v), t.m[j]).group("e"))]
                if len(steps) < 2 or _writes(body, v) != len(writes):
                    continue           # a ++, a compound write or a write through a pointer: leave it
                first = writes[0]
                if first in steps or steps[-1] != writes[-1]:
                    continue           # the chain must start with a plain set and end the writes
                lo, hi = first, steps[-1]
                if any(LABEL_RE.match(t.m[j]) or re.match(r"^[ \t]*(?:do|while|for|goto|switch|case)\b", t.m[j])
                       or "{" in t.m[j] or "}" in t.m[j] for j in range(lo, hi + 1)):
                    continue           # straight-line chains only
                pins = {j for j in range(a, b + 1) if PIN_STMT_RE.match(t.m[j])
                        and re.search(r"[(,]\s*%s\s*[,)]" % re.escape(v), t.m[j])}
                base_ty = re.sub(r"\bregister\b", "", ty).strip()
                for which in ("all", "last"):
                    split = steps if which == "all" else steps[-1:]
                    names, n = {}, 1
                    for j in split:
                        n += 1
                        names[j] = "%s%d" % (v, n)
                    edits, cur = {}, v
                    for j in range(first, b + 1):
                        if j in pins:
                            continue
                        ln_m, ln = t.m[j], _nl(t.lines[j])
                        if j in names:
                            m = re.match(STEP_RE % re.escape(v), ln_m)
                            e0, e1 = m.start("e"), m.end("e")
                            rhs = ln[e0:e1]
                            reps = [(o.start(), o.end(), cur) for o in rx.finditer(ln_m[e0:e1])]
                            for s0, s1, r in sorted(reps, reverse=True):
                                rhs = rhs[:s0] + r + rhs[s1:]
                            cur = names[j]
                            edits[j] = m.group("i") + "%s = %s;" % (cur, rhs)
                            continue
                        if cur != v:
                            hits = list(rx.finditer(ln_m))
                            if hits:
                                for h in reversed(hits):
                                    ln = ln[:h.start()] + cur + ln[h.end():]
                                edits[j] = ln
                    decl_ln = _nl(t.lines[di])
                    plain = re.sub(r"[ \t]*ASM_REG[ \t]*\([^)]*\)", "", re.sub(r"\bregister[ \t]+", "", decl_ln))
                    ind = _ind(t.lines[di])
                    extra = [ind + "%s%s%s;" % (base_ty, "" if base_ty.endswith("*") else " ", nm)
                             for nm in names.values()]
                    edits[di] = plain.rstrip()
                    for keep_pins in ((False, True) if pins else (False,)):
                        drop = set() if keep_pins else set(pins)
                        e2 = dict(edits)
                        if keep_pins:
                            for j in pins:       # a keep on v follows the name live at that point
                                live = v
                                for s in split:
                                    if s < j:
                                        live = names[s]
                                if live != v:
                                    ln = _nl(t.lines[j])
                                    e2[j] = re.sub(r"\b%s\b" % re.escape(v), live, ln)
                        out.append(("splitcursor:%s/%s%s" % (v, which, "+pins" if keep_pins else ""),
                                    t.build(e2, drop, {di: extra})))
    return out


# ------------------------------------------------------------------------------ 9. host (register renames)

HOST_WIDE = __import__("os").environ.get("NATURAL_HOST_WIDE") == "1"   # every register pin, not just the lane's precondition
REGDECL_RE = re.compile(r"^(?P<i>[ \t]*)register[ \t]+(?P<t>[^;=]*?)\b(?P<v>%s)[ \t]+ASM_REG[ \t]*\([^)]*\)[ \t]*;[ \t]*$" % ID)
WORDDECL_RE = re.compile(r"^[ \t]*(?:register[ \t]+)?(?P<t>(?:(?:const|volatile|signed|unsigned)[ \t]+)*"
                         r"(?:s32|u32|int|unsigned|long|M2C_UNK)|[A-Za-z_]\w*[ \t]*\*+)[ \t]*(?P<n>%s)[ \t]*(?:=[^;]*)?;" % ID)


def host_candidates(text):
    """A register-pinned variable renamed onto an existing word-sized variable of its function.

    A native lane on the register-rename class (2026-09-12, work/native_lane/regrename/REPORT.md; the
    largest cheap class, ~965 `ASM_REG` sites): the pinned variable is usually a short-lived copy or
    temporary that cse merges away (`make_regs_eqv` heads a class only with a register whose life
    reaches outside the cse block) or that inherits a pinned neighbour's register as a suggestion
    (local-alloc.c:1891, global.c's `set_preference`).  Hosting it in a variable the function already
    uses elsewhere - lazy reuse of a local, very 1997 - gives it a life the allocators treat
    differently; a fresh block-local never works.  The declaration goes (and with it the pin); `v` is
    renamed to the host inside its block; a rewrite that would change another pin's text is refused.
    Hosts: word-sized locals and parameters, those assigned later in `v`'s block first, then
    declaration order, at most six.  12 rows / 22 pins in the lane; the scorer decides every one.
    """
    from pin_census import sites_of
    t = _T(text)
    sites = sites_of(text)
    functions = list(_functions(t))
    pinned = set()
    for s in sites:
        if s[0] == "reg":
            m = re.search(r"(%s)\s*$" % ID, text[s[3]:s[4]].split("ASM_REG")[0])
            if m:
                pinned.add(m.group(1))
        elif re.fullmatch(r"\s*%s\s*" % ID, s[2] or ""):
            pinned.add(s[2].strip())
    out = []
    for si, s in enumerate(sites):
        if s[0] != "reg":
            continue
        i = s[5] - 1
        m = REGDECL_RE.match(t.m[i]) if 0 <= i < len(t.m) else None
        if not m:
            continue
        v = m.group("v")
        sp = t.span(i)
        if not sp:
            continue
        a, b = sp
        function = next((f for f in functions if f.a == a), None)
        if function is None: continue
        d, j = 0, b
        for k in range(i + 1, b + 1):
            d += t.m[k].count("{") - t.m[k].count("}")
            if d < 0:
                j = k
                break
        if not HOST_WIDE:
            # the lane's precondition (its reach: 22 hits on 130 such sites): v meets another pinned
            # variable - `v = PIN;` (mechanism 1) or `PIN = ... v ...` (mechanism 3).  Without it the
            # generator fires on ~1,100 rows / ~19,000 candidates and swamps every menu it joins.
            others = pinned - {v}
            meets = False
            for k in range(i + 1, j):
                am = re.match(r"^[ \t]*(%s)[ \t]*(?:[-+*/%%&|^]|<<|>>)?=(?!=)(.*)$" % ID, t.m[k])
                if not am:
                    continue
                lhs, rhs = am.group(1), am.group(2)
                if (lhs == v and set(re.findall(ID, rhs)) & others) or (lhs in others and _occ(v).search(rhs)):
                    meets = True
                    break
            if not meets:
                continue
        head = "\n".join(t.m[max(0, a - 8):a + 1])
        hosts = [n for n in _params(t.m, a)
                 if n not in pinned and n != v
                 and re.search(r"(?:s32|u32|int|unsigned|long|M2C_UNK|\*)\s*%s\b" % re.escape(n), head)]
        for k in range(a, b + 1):
            dm = WORDDECL_RE.match(t.m[k])
            if dm and dm.group("n") not in pinned and dm.group("n") != v and dm.group("n") not in hosts \
                    and "ASM_REG" not in t.m[k]:
                hosts.append(dm.group("n"))
        later = [h for h in hosts if any(re.match(r"^[ \t]*%s[ \t]*=(?!=)" % re.escape(h), t.m[k]) for k in range(i + 1, j))]
        hosts = later + [h for h in hosts if h not in later]
        want = [(x[1], x[2]) for n, x in enumerate(sites) if n != si]
        for h in hosts[:6 if HOST_WIDE else 4]:
            rx = _occ(v)
            edits = {}
            compatible = True
            for k in range(i + 1, j):
                hits = list(rx.finditer(t.m[k]))
                if hits:
                    source_decl, host_decl = function.resolve(v, k), function.resolve(h, k)
                    if not source_decl or not host_decl:
                        compatible = False; break
                    vt, ht = source_decl["ty"], host_decl["ty"]
                    if (not vt or not ht or (source_decl["quals"] | host_decl["quals"]) & NOSHARE
                            or not (vt == ht or _tclass(vt) in ("s", "u") and _tclass(vt) == _tclass(ht))):
                        compatible = False; break
                    ln = _nl(t.lines[k])
                    for hh in reversed(hits):
                        ln = ln[:hh.start()] + h + ln[hh.end():]
                    edits[k] = ln
            if not compatible: continue
            cand = t.build(edits, {i})
            if [(x[1], x[2]) for x in sites_of(cand)] != want:
                continue            # a kept pin named v: its text would change
            out.append(("host:%s->%s" % (v, h), cand))
    return out


# ------------------------------------------------------------------------------ 10. the fakedep levers
#
# work/native_lane/fakedep/REPORT.md (2026-09-12): on eight rows whose pin could only come off in
# exchange for a refused fake dependency (`x = (e) + a; x -= a;`), the fake never forced an order -
# it moved register allocation through stale reference counts and an inserted `(use x)`, and the
# natural C that reproduces it changes which value is a local-alloc quantity and which is global,
# and their order.  Three levers closed five rows and one pin of a sixth; each generator below is
# one lever.  They work on the text the sweep hands them - the pin already erased, so the site is
# not in the text - and rank their own candidates, at most ALLOC_CAP per generator (t18 re-sorts
# the whole menu by distance to the erased group; t15 takes it in order).  None deletes or edits a
# pin: a candidate whose kept pins' lines differ from the input's is refused.

_ENV = __import__("os").environ
ALLOC_WIDE = _ENV.get("NATURAL_ALLOC_WIDE") == "1"      # every candidate (and every decl pair), uncapped
ALLOC_CAP = int(_ENV.get("NATURAL_ALLOC_CAP", "12"))    # per generator per text
CASE_RE = re.compile(r"^[ \t]*(?:case\b[^:]*|default[ \t]*):")
VDECL_RE = re.compile(
    r"^(?P<i>[ \t]*)(?P<spell>(?P<q>(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*)"
    r"(?P<base>%s)(?P<ptr>(?:[ \t]*\*)*)[ \t]*(?P<n>%s))[ \t]*(?P<arr>\[[^\]]*\][ \t]*)?"
    r"(?P<asm>ASM_REG[ \t]*\([^)]*\)[ \t]*)?(?:=[ \t]*(?P<init>[^;]*?))?[ \t]*;[ \t]*$" % (ID, ID))
PDECL_RE = re.compile(r"^[ \t]*(?P<q>(?:(?:register|const|volatile|unsigned|signed|struct|union|enum)[ \t]+)*)"
                      r"(?P<base>%s)(?P<ptr>(?:[ \t]*\*)*)[ \t]*(?P<n>%s)[ \t]*$" % (ID, ID))
WORD_S = {"s32", "int", "signed", "signed int", "long", "long int", "signed long", "M2C_UNK", "M2C_UNK32"}
WORD_U = {"u32", "unsigned", "unsigned int", "unsigned long", "unsigned long int"}
SMALL = {"s16", "u16", "s8", "u8", "short", "char", "signed char", "unsigned char", "unsigned short",
         "M2C_UNK16", "M2C_UNK8"}
NOSHARE = {"static", "volatile", "const", "extern"}
TWIN_SETS = ({"x", "y", "z"}, {"lo", "hi"}, {"min", "max"}, {"src", "dst"}, {"left", "right"},
             {"top", "bottom"}, {"w", "h"}, {"width", "height"}, {"row", "col"}, {"r", "g", "b"},
             {"u", "v"}, {"start", "end"})
CALL_RE = re.compile(r"(?<![\w.])(?<!->)(?P<f>%s)[ \t]*\(" % ID)
CHAIN_RE = re.compile(r"(?P<b>\((?:[^()]|\([^()]*\))*\)|%s)[ \t]*->[ \t]*(?P<m>%s)" % (ID, ID))


def _ptype(q, base, ptr):
    return " ".join([x for x in q if x != "register"] + [base]) + "*" * ptr.count("*")


def _tclass(ty):
    return "s" if ty in WORD_S else "u" if ty in WORD_U else "p" if ty.endswith("*") else ty


def _twin_names(a, b):
    """`next_x`/`next_y`, `saved_x`/`saved_y`, `dx`/`dy`, `arg0`/`arg1`: one component apart."""
    if a == b:
        return False
    ta, tb = a.split("_"), b.split("_")
    if len(ta) == len(tb) > 1:
        diff = [(p.lower(), q.lower()) for p, q in zip(ta, tb) if p != q]
        if len(diff) == 1 and (any(diff[0][0] in s and diff[0][1] in s for s in TWIN_SETS)
                               or (diff[0][0].isdigit() and diff[0][1].isdigit())):
            return True
    if len(a) == len(b):
        d = [(p, q) for p, q in zip(a, b) if p != q]
        if len(d) == 1 and ({d[0][0].lower(), d[0][1].lower()} <= {"x", "y", "z"}
                            or (d[0][0].isdigit() and d[0][1].isdigit())):
            return True
    return False


def _decl_names(stmt):
    body = stmt.strip().rstrip(";")
    m = re.match(r"^(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)\s+)*%s" % ID, body)
    rest = body[m.end():] if m else body
    parts, d, cur = [], 0, ""
    for ch in rest:
        d += ch in "([{"
        d -= ch in ")]}"
        if ch == "," and d == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    out = []
    for p in parts:
        p = re.sub(r"ASM_REG\s*\([^)]*\)", "", p.split("=")[0])
        ids = re.findall(ID, re.sub(r"\[[^\]]*\]", "", p))
        if ids:
            out.append(ids[-1])
    return out


def _stmt_end(ml, k, c):
    """Line of the `;` that ends the statement starting on line k (None past a brace)."""
    d = 0
    for j in range(k, min(c, k + 12)):
        for ch in ml[j]:
            if ch in "([":
                d += 1
            elif ch in ")]":
                d -= 1
            elif ch == ";" and d == 0:
                return j
            elif ch in "{}":
                return None
    return None


def _is_fn(ml, a):
    head = "\n".join(ml[max(0, a - 8):a + 1])
    tail = re.split(r"[;}]", head[:head.rfind("{")])[-1].strip()     # the last declaration only
    return tail.endswith(")") and not tail.startswith(("typedef", "struct", "union", "enum"))


def _postfix(e):
    """True when `e` can stand in for a variable without parentheses: a primary followed by
    `->m` / `.m` / `[i]` chains (`((S *)p)->unk_10.n`)."""
    e = e.strip()
    if _term(e):
        return True
    if e.startswith("("):
        j = _match_paren(e, 0)
        if j is None:
            return False
        rest = e[j + 1:]
    else:
        m = re.match(ID, e)
        if not m:
            return False
        rest = e[m.end():]
    while rest.strip():
        rest = rest.lstrip()
        m = re.match(r"(?:->|\.)[ \t]*%s" % ID, rest)
        if m:
            rest = rest[m.end():]
            continue
        if rest.startswith("["):
            d = 0
            for k, ch in enumerate(rest):
                d += ch == "["
                d -= ch == "]"
                if d == 0:
                    rest = rest[k + 1:]
                    break
            else:
                return False
            continue
        return False
    return True


def _pin_sig(text):
    """Every live pin with its whole line's text: a lever may move a pin's line, never change it."""
    lines = text.splitlines()
    from pin_census import sites_of
    return [(s[0], s[1], s[2], lines[s[5] - 1].strip() if s[5] - 1 < len(lines) else "") for s in sites_of(text)]


class _Var:
    """One declaration's reads, writes and live intervals inside its scope (see `_Fn`)."""

    def __init__(self, F, d):
        self.d = d
        name, ml = d["name"], F.ml
        rx = _occ(name)
        callrx = re.compile(r"(?<![\w.])(?<!->)%s[ \t]*\(" % re.escape(name))
        c = d["block"][1]
        start = (F.a + 1) if d.get("param") else d["end"] + 1
        self.lines, self.reads, self.wlines, self.iv = [], [], [], []
        self.uncovered, self.addr, self.odd, self.cast_ok = 0, False, False, True
        writes = []                                   # (effective line, plain)
        if d.get("init") is not None:
            writes.append((d["end"], True))
            self.wlines.append(d["end"])
        for k in range(start, c):
            s = ml[k]
            hits = list(rx.finditer(s))
            called = callrx.search(s)
            if not hits and not called:
                continue
            if F.resolve(name, k) is not d:
                continue
            if called or LABEL_RE.match(s) or re.search(r"\bgoto[ \t]+%s\b" % re.escape(name), s):
                self.odd = True                       # a call through it, or a label of that name
            if not hits:
                continue
            self.lines.append(k)
            nread, wkind, first = 0, None, None
            for m in hits:
                before, after = s[:m.start()], s[m.end():]
                if re.search(r"(?:^|[^&\w)\]])&[ \t]*$", before):
                    self.addr = True
                if re.match(r"[ \t]*(?:(?:<<|>>|[-+*/%&|^])=|\+\+|--)", after) or re.search(r"(?:\+\+|--)[ \t]*$", before):
                    kind = "rw"
                elif re.match(r"[ \t]*=(?!=)", after):
                    kind = "w"
                else:
                    kind = "r"
                    bs = before.rstrip()
                    cast = re.search(r"\([^()]*\*[ \t]*\)[ \t]*$", before)
                    whole = re.match(r"[ \t]*(?:[,);]|[=!]=)", after) and (
                        bs.endswith(("(", ",")) or re.search(r"(?:(?:^|[^-+*/%&|^<>=!])=|[=!]=|\breturn)$", bs))
                    self.cast_ok = self.cast_ok and bool(cast or whole)
                first = first or kind
                nread += kind in ("r", "rw")
                if kind != "r":
                    wkind = kind
            plain = False
            if wkind and first != "r" and not s[:hits[0].start()].strip():
                p = _prev_nb(ml, k)
                ps = ml[p].rstrip() if p is not None else "{"
                plain = ps.endswith(("{", "}", ";", ":"))   # not the body of a braceless if/else/loop
            for _ in range(nread):                    # the statement's reads come before its write
                w = F.cover(writes, k)
                if w is None:
                    self.uncovered += 1
                else:
                    self.iv.append((w, k))
                self.reads.append(k)
            if wkind:
                e = (_stmt_end(ml, k, c) if plain else None)
                if e is None:
                    plain, e = False, k
                writes.append((e, plain))
                self.wlines.append(e)
        self.ok = not (self.uncovered or self.addr or self.odd)
        webs = []
        for w, r in sorted(self.iv):
            if webs and w <= webs[-1][1]:
                webs[-1][1] = max(webs[-1][1], r)
            else:
                webs.append([w, r])
        self.webs = webs
        self.glob = bool(self.uncovered) or len(webs) > 1 or any(F.crosses(w, r) for w, r in self.iv)


class _Fn:
    """One function body read from the text alone: brace blocks, declarations, and each local's
    reads, writes and live intervals.  A read is COVERED when a plain `v = ...;` / `v op= ...;`
    statement precedes it in the same or an enclosing block with no label, `case` or loop head in
    between (a label is a way in, a loop head a back edge); a local whose every read is covered is
    LOCALLY DEFINED and live only on its intervals (covering write, read]."""

    def __init__(self, t, a, b):
        self.t, self.a, self.b, self.ml = t, a, b, t.m
        ml = t.m
        self.blocks, stack = [], []
        for k in range(a, b + 1):
            if ml[k].lstrip().startswith("#"):
                continue
            for ch in ml[k]:
                if ch == "{":
                    stack.append(k)
                elif ch == "}" and stack:
                    self.blocks.append((stack.pop(), k))
        self.body = max(self.blocks, key=lambda oc: oc[1] - oc[0])
        self.inner = {}
        for o, c in sorted(self.blocks, key=lambda oc: oc[0] - oc[1]):     # largest first, nested win
            for k in range(o + 1, c):
                self.inner[k] = (o, c)
        self.loops = [(o, c) for o, c in self.blocks if LOOP_RE.match(ml[o])]
        self.labels = [k for k in range(a + 1, b) if LABEL_RE.match(ml[k]) or CASE_RE.match(ml[k])]
        self.decls = {blk: self._block_decls(blk) for blk in self.blocks}
        self.params = self._params()
        self.byname = {}
        for d in [x for ds in self.decls.values() for x in ds] + self.params:
            self.byname.setdefault(d["name"], []).append(d)
        self._vars = {}
        self.pinned = set()                          # (name, decl line) of every pinned variable
        from pin_census import sites_of
        for s in sites_of(t.text):
            k = s[5] - 1
            if not (a < k < b):
                continue
            for n in (re.findall(ID, s[2] or "") if s[0] == "stmt" else []):
                d = self.resolve(n, k)
                if d is not None:
                    self.pinned.add((d["name"], d["line"]))
        for ds in self.decls.values():
            for d in ds:
                if d["pinned"]:
                    self.pinned.add((d["name"], d["line"]))

    def _block_decls(self, blk):
        o, c = blk
        ml, out, k = self.ml, [], o + 1
        while k < c:
            s = ml[k]
            if not s.strip() or s.lstrip().startswith("#"):
                k += 1
                continue
            first = re.match(ID, s.strip())
            if not first or first.group(0) in CTRL or not _DECL_START_RE.match(s):
                break
            end = k
            while end < c and not ml[end].rstrip().endswith(";"):
                end += 1
            m = VDECL_RE.match(s) if end == k else None
            if m and m.group("base") not in CTRL:
                q = m.group("q").split()
                out.append(dict(line=k, end=end, name=m.group("n"), block=blk, single=True,
                                ty=_ptype(q, m.group("base"), m.group("ptr")), quals=set(q),
                                init=m.group("init"), arr=bool(m.group("arr")), pinned=bool(m.group("asm")),
                                spell=m.group("spell").strip(), ind=m.group("i")))
            else:
                for n in _decl_names(" ".join(ml[k:end + 1])):
                    out.append(dict(line=k, end=end, name=n, block=blk, single=False, ty=None, quals=set(),
                                    init=None, arr=False, pinned="ASM_REG" in s, spell=None, ind=_ind(s)))
            k = end + 1
        return out

    def _params(self):
        ml, a = self.ml, self.a
        head = "\n".join(ml[max(0, a - 8):a + 1])
        head = head[:head.rfind("{")]
        r = head.rfind(")")
        d, left = 0, None
        for k in range(r, -1, -1):
            d += head[k] == ")"
            d -= head[k] == "("
            if d == 0:
                left = k
                break
        out = []
        for p in (head[left + 1:r].split(",") if left is not None else []):
            m = PDECL_RE.match(p.replace("\n", " "))
            if m:
                q = m.group("q").split()
                out.append(dict(line=a, end=a, name=m.group("n"), block=self.body, single=True, param=True,
                                ty=_ptype(q, m.group("base"), m.group("ptr")), quals=set(q), init=None,
                                arr=False, pinned=False, spell=None, ind=""))
        return out

    def resolve(self, name, k):
        """The declaration a mention of `name` on line k refers to (None: a global)."""
        best = None
        for d in self.byname.get(name, ()):
            if d.get("param"):
                best = best or d
                continue
            o, c = d["block"]
            if o < k < c and d["line"] < k and (best is None or best.get("param") or o > best["block"][0]):
                best = d
        return best

    def var(self, d):
        key = (d["name"], d["line"], bool(d.get("param")))
        if key not in self._vars:
            self._vars[key] = _Var(self, d)
        return self._vars[key]

    def parent(self, blk):
        return self.inner.get(blk[0], None) if blk != self.body else None

    def encl(self, lo, hi):
        """Innermost block that strictly contains lines lo..hi."""
        blk = self.inner.get(lo, self.body)
        while blk is not None and not (blk[0] < hi < blk[1]):
            blk = self.parent(blk)
        return blk or self.body

    def barrier(self, w, k):
        i = bisect.bisect_right(self.labels, w)
        if i < len(self.labels) and self.labels[i] < k:
            return True
        return any(w < o <= k <= c for o, c in self.loops)

    def cover(self, writes, k):
        for w, plain in reversed(writes):
            if w >= k or not plain:
                continue
            blk = self.inner.get(w, self.body)
            if not (blk[0] < k < blk[1]):
                continue                              # a write in an arm that does not dominate k
            return None if self.barrier(w, k) else w
        return None

    def crosses(self, w, r):
        """A basic-block boundary between line w and line r (a jump, a label, a brace)."""
        if self.inner.get(w) != self.inner.get(r):
            return True
        return any(CONTROL_RE.match(self.ml[j]) or LABEL_RE.match(self.ml[j]) or "{" in self.ml[j]
                   or "}" in self.ml[j] for j in range(w + 1, r))

    def usable(self, d, init_ok=False):
        """A plain scalar local no pin names: something a lever may rename, move or split."""
        return (d["single"] and d["ty"] and not d["arr"] and not (d["quals"] & NOSHARE)
                and (init_ok or d["init"] is None) and (d["name"], d["line"]) not in self.pinned
                and not d["pinned"] and (_tclass(d["ty"]) in ("s", "u", "p") or d["ty"] in SMALL))


def _functions(t):
    for a, b in t.spans:
        if _is_fn(t.m, a):
            try:
                yield _Fn(t, a, b)
            except Exception:             # an unreadable function costs its own candidates only
                continue


def _interferes(v, h):
    """Would v and h, as one variable, ever hold two live values at once?"""
    for w1, r1 in v.iv:
        for w2, r2 in h.iv:
            if w1 < r2 and w2 < r1:
                return True
        if any(w1 < k < r1 for k in h.wlines):
            return True
    for w2, r2 in h.iv:
        if any(w2 < k < r2 for k in v.wlines):
            return True
    return False


def _rename(t, lines, old, new, edits=None):
    edits = dict(edits or {})
    rx = _occ(old)
    for k in sorted(set(lines)):
        ln = edits.get(k, _nl(t.lines[k]))
        for m in reversed(list(rx.finditer(t.m[k]))):
            ln = ln[:m.start()] + new + ln[m.end():]
        edits[k] = ln
    return edits


def _capped(scored):
    scored.sort(key=lambda x: x[0])
    out, seen = [], set()
    for _, label, cand in scored:
        if cand not in seen:
            seen.add(cand)
            out.append((label, cand))
    return out if ALLOC_WIDE else out[:ALLOC_CAP]


def hostwide_candidates(text):
    """HOST, widened: a local V renamed onto an existing variable H, V's declaration deleted.

    REPORT.md "HOST": the variable to host is often not the pinned one but whichever nearby local
    lost or gained the register retail gives the winner (a local qty in base; in the fake it leaves
    the qty list or changes `phys=`).  Merging it into H changes which value is a local-alloc
    quantity and which is global.  Hosts, most likely first:
      twin  the twin of a sibling block computing the same quantity (`y_sum` -> the sibling's
            `coord_value`, same right-hand side), promoted to function scope - dungeon/func_80AC9228,
            both pins off;
      same  a same-block variable first assigned after V's last use (the merge makes it set and die
            twice, so local-alloc refuses it) - dungeon/func_80DBD3EC `position_x` -> `position_z`,
            dungeon/func_809A1A8C `step_y` -> `signed_frame` (one of two pins);
      func  a function-scope variable whose uses all lie in other blocks - dungeon/func_800B30D0
            `target_node` -> `source_pos`.
    Ranked: a renamed sibling twin; a same-block host with a twin name (`position_x` ->
    `position_z`); a same-name sibling twin (the two blocks' `position_x` as one function-scope
    variable - also exact on 80DBD3EC); any other same-block host, nearest first; a function-scope
    host, nearest first.  On the four HOST rows the lane's edit ranks 2-5.  Guards:
    V and H both locally defined (see `_Fn`) and never live at once; same signedness for words, the
    same type for anything narrower, a `void *` V onto a typed pointer only when every read of V is
    cast or passed whole; neither pinned; every renamed mention resolves to H; no pin line changes.
    Unlike `host_candidates` (the pinned variable itself, its pin deleted) nothing here touches a pin.
    """
    try:
        return _hostwide(text)
    except Exception:
        return []


def _hostwide(text):
    t = _T(text)
    want = _pin_sig(text)
    scored = []
    for F in _functions(t):
        locs = [d for ds in F.decls.values() for d in ds if F.usable(d, init_ok=True)]
        params = [d for d in F.params if F.usable(d)]
        top = F.decls.get(F.body, [])
        for V in locs:
            if V["init"] is not None:
                continue
            v = F.var(V)
            if not v.ok or not v.reads or len(v.webs) != 1:
                continue
            vlo, vhi = min(v.lines), max(v.lines)
            region = F.encl(vlo, vhi)
            for H in locs + params:
                if H is V or H["name"] == V["name"] and H["block"] == V["block"]:
                    continue
                tv, th = V["ty"], H["ty"]
                if not (tv == th or (_tclass(tv) in ("s", "u") and _tclass(tv) == _tclass(th))
                        or (tv == "void*" and th.endswith("*") and v.cast_ok)):
                    continue
                h = F.var(H)
                if not h.ok or not h.lines:
                    continue
                if H["block"] == V["block"] and not H.get("param"):
                    if min(h.lines + [H["end"] + 1 if H["init"] is not None else 10 ** 9]) <= vhi:
                        continue
                    kind, gap = "same", min(h.lines) - vhi
                elif H["block"] == F.body or H.get("param"):
                    if any(region[0] < k < region[1] for k in h.lines):
                        continue
                    kind, gap = "func", min(abs(k - vlo) for k in h.lines)
                else:
                    continue
                if _interferes(v, h) or any(F.resolve(H["name"], k) is not H for k in v.lines):
                    continue
                cand = t.build(_rename(t, v.lines, V["name"], H["name"]), {V["line"]})
                if _pin_sig(cand) != want:
                    continue
                # tiers: 0 a renamed sibling twin, 1 a same-block host with a twin name, 2 a
                # same-name sibling twin, 3 any other same-block host, 4 a function-scope host
                tier = 1 if kind == "same" and _twin_names(V["name"], H["name"]) else 3 if kind == "same" else 4
                scored.append(((tier, gap, V["line"]),
                               "hostwide:%s@%d->%s/%s" % (V["name"], vlo + 1, H["name"], kind), cand))
        # the sibling block's twin, promoted to function scope
        for V in locs:
            v = F.var(V)
            if V["init"] is not None or not v.ok or not v.reads or len(v.webs) != 1:
                continue
            wm = re.match(r"^[ \t]*%s[ \t]*=(?!=)[ \t]*(?P<e>[^;]+?)[ \t]*;[ \t]*$" % re.escape(V["name"]),
                          F.ml[min(v.wlines)]) if v.wlines else None
            if not wm or re.fullmatch(r"[ \t]*(?:%s|%s)[ \t]*" % (ID, NUM), wm.group("e")):
                continue
            rhs = _sq(wm.group("e"))
            vb = V["block"]
            for H in locs:
                hb = H["block"]
                if H is V or H["init"] is not None or H["ty"] != V["ty"] or hb == vb or hb == F.body:
                    continue
                if (hb[0] <= vb[0] and vb[1] <= hb[1]) or (vb[0] <= hb[0] and hb[1] <= vb[1]):
                    continue                          # nested: not siblings
                h = F.var(H)
                if not h.ok or not any(
                        (m := re.match(r"^[ \t]*%s[ \t]*=(?!=)[ \t]*(?P<e>[^;]+?)[ \t]*;[ \t]*$" % re.escape(H["name"]),
                                       F.ml[k])) and _sq(m.group("e")) == rhs for k in h.wlines):
                    continue
                n = H["name"]
                if any(d["name"] == n for d in top + F.params):
                    continue
                # every mention of n in the function must be V's, H's or another block's own local,
                # and no block between the body and V's / H's block may declare n
                bad = False
                for k in range(F.a + 1, F.b):
                    if _occ(n).search(F.ml[k]) and not any(dd["line"] <= k <= dd["end"] for dd in F.byname.get(n, ())):
                        d = F.resolve(n, k)
                        if d is None or (d is not H and d is not V and d["block"] != vb and d["block"] != hb
                                         and ((d["block"][0] < vb[0] and vb[1] < d["block"][1])
                                              or (d["block"][0] < hb[0] and hb[1] < d["block"][1]))):
                            bad = True
                            break
                for blk in (vb, hb):
                    p = F.parent(blk)
                    while p is not None and p != F.body:
                        if any(d["name"] == n for d in F.decls.get(p, [])):
                            bad = True
                        p = F.parent(p)
                if bad or (n != V["name"] and any(_occ(n).search(F.ml[k]) for k in range(vb[0] + 1, vb[1]))):
                    continue
                if _interferes(v, h):
                    continue
                edits = _rename(t, v.lines, V["name"], n) if n != V["name"] else {}
                at = max((d["end"] for d in top), default=F.a)
                ind = top[-1]["ind"] if top else _ind(F.ml[_next_nb(F.ml, F.a)] if _next_nb(F.ml, F.a) else "    ")
                cand = t.build(edits, {V["line"], H["line"]}, {at: [ind + H["spell"] + ";"]})
                if _pin_sig(cand) != want:
                    continue
                scored.append(((2 if n == V["name"] else 0, 0, V["line"]),
                               "hostwide:%s@%d->%s/twin" % (V["name"], min(v.lines) + 1, n), cand))
    return _capped(scored)


def unhost_candidates(text):
    """UNHOST: a local used in two blocks keeps only one of them.

    REPORT.md "UNHOST" (dungeon/func_81839358, `vel_z ASM_REG("$5")` off): `vel_y` is used in two
    blocks, so it is a global allocno and global-alloc hands it `$5` after local-alloc gave `vel_z`
    `$4` - retail is the other way round.  In state_1 the lane dropped the temporary,
    `unk_10.n = unk_10.n * 5;` like its two sibling lines: `vel_y` leaves greg's list and block 0's
    value becomes a local quantity.  (A fresh block-local there also matched.)  So, for a locally
    defined variable with two or more webs (a web: a write and the reads it covers), in each web
    but the first (every web under NATURAL_ALLOC_WIDE): inline the defining expression when the
    web is one write and one read and nothing between them can change it (no call, no pin, no write
    to a variable it reads, stores only to other members of the same base), else redeclare the
    variable at the top of the innermost block that holds that web and nothing else of it.
    """
    try:
        return _unhost(text)
    except Exception:
        return []


def _stores(s):
    """(kind, lhs) of a statement line: ('var', name), ('mem', lhs text), ('unknown', ...) or None."""
    d = 0
    for k, ch in enumerate(s):
        if ch in "([":
            d += 1
        elif ch in ")]":
            d -= 1
        elif ch == "=" and d == 0 and s[k + 1:k + 2] != "=" and s[k - 1:k] not in ("=", "!", "<", ">") \
                or ch == "=" and d == 0 and s[k - 2:k] in ("<<", ">>"):
            lhs = re.sub(r"(?:<<|>>|[-+*/%&|^])$", "", s[:k].rstrip()).strip()
            return ("var", lhs) if re.fullmatch(ID, lhs) else ("mem", lhs)
    if re.search(r"\+\+|--", s):
        m = re.search(r"(%s)[ \t]*(?:\+\+|--)|(?:\+\+|--)[ \t]*(%s)" % (ID, ID), s)
        whole = m and re.fullmatch(r"[ \t]*(?:%s[ \t]*(?:\+\+|--)|(?:\+\+|--)[ \t]*%s)[ \t]*;[ \t]*" % (ID, ID), s)
        return ("var", m.group(1) or m.group(2)) if whole else ("unknown", s)
    return None


def _disjoint(e_chains, lhs):
    """True when a store to `lhs` cannot touch any `base->member` the moved expression reads:
    the same base, a different first member."""
    m = CHAIN_RE.match(lhs.strip())
    if not m or not e_chains:
        return False
    return all(_sq(b) == _sq(m.group("b")) and mm != m.group("m") for b, mm in e_chains)


def _unhost(text):
    t = _T(text)
    want = _pin_sig(text)
    scored = []
    for F in _functions(t):
        for ds in F.decls.values():
            for V in ds:
                if not F.usable(V, init_ok=True):
                    continue
                v = F.var(V)
                if not v.ok or len(v.webs) < 2:
                    continue
                for wi, (lo, hi) in enumerate(v.webs):
                    if wi == 0 and not ALLOC_WIDE:
                        continue
                    reads = [k for w, k in v.iv if lo <= w and k <= hi]
                    wl = [k for k in v.wlines if lo <= k <= hi]
                    occ = [k for k in v.lines if lo <= k <= hi]
                    if not reads:
                        continue
                    rank = (len(v.webs) != 2, lo)
                    # (a) inline: one write, one read
                    got = _inline(t, F, V, v, lo, reads, wl, want)
                    if got:
                        scored.append(((rank, 0), "unhost:%s@%d/inline" % (V["name"], reads[0] + 1), got))
                    # (b) a block-local for this web
                    blk = F.encl(min(occ + wl), max(occ + wl))
                    if blk == V["block"] or blk == F.body or SWITCH_RE.match(F.ml[blk[0]]):
                        continue
                    if any(blk[0] < k < blk[1] and not (lo <= k <= hi) for k in v.lines + v.wlines):
                        continue
                    if any(d["name"] == V["name"] for d in F.decls.get(blk, [])):
                        continue
                    at = max((d["end"] for d in F.decls.get(blk, [])), default=blk[0])
                    nb = _next_nb(F.ml, blk[0])
                    ind = _ind(F.ml[nb]) if nb is not None and nb < blk[1] else _ind(F.ml[blk[0]]) + "    "
                    spell = re.sub(r"^register[ \t]+", "", V["spell"])
                    cand = t.build({}, (), {at: [ind + spell + ";"]})
                    if _pin_sig(cand) != want:
                        continue
                    scored.append(((rank, 1), "unhost:%s@%d/local" % (V["name"], lo + 1), cand))
    return _capped(scored)


def _inline(t, F, V, v, lo, reads, wl, want):
    """The web's one write `V = E;` folded into its one read, or None."""
    if len(reads) != 1 or wl != [lo] or v.reads.count(reads[0]) != 1:
        return None
    if _tclass(V["ty"]) not in ("s", "u", "p"):
        return None                                   # a narrow V truncates: inlining would not
    r = reads[0]
    m = re.match(r"^(?P<i>[ \t]*)%s[ \t]*=(?!=)[ \t]*(?P<e>[^;]+?)[ \t]*;[ \t]*$" % re.escape(V["name"]), F.ml[lo])
    if not m or _occ(V["name"]).search(m.group("e")):
        return None
    e_m = m.group("e")
    if re.search(r"(?<![=!<>])=(?!=)|\+\+|--", e_m):
        return None
    calls = [c.group("f") for c in CALL_RE.finditer(e_m) if c.group("f") not in CTRL]
    if any(not f.isupper() for f in calls):
        return None                                   # a call in E: never moved
    e_real = t.lines[lo][m.start("e"):m.end("e")]
    mem = bool(re.search(r"->|\[|\.[ \t]*[A-Za-z_]|(?:^|[^\w)\]])\*", e_m) or calls)
    chains = [(c.group("b"), c.group("m")) for c in CHAIN_RE.finditer(e_m)]
    if mem and (calls or re.search(r"\[|(?:^|[^\w)\]])\*[ \t]*[A-Za-z_(]", re.sub(r"\([^()]*\*[ \t]*\)", "", e_m))):
        chains = []                                   # a memory read CHAIN_RE cannot name: no store may pass
    evars = {x for x in re.findall(ID, re.sub(r"(?:->|\.)[ \t]*%s" % ID, "", e_m)) if x not in CTRL}
    hit = list(_occ(V["name"]).finditer(F.ml[r]))
    if len(hit) != 1:
        return None
    between = [F.ml[j] for j in range(lo + 1, r)] + [F.ml[r][:hit[0].start()]]
    for j, s in enumerate(between):
        if "ASM_" in s or any(c.group("f") not in CTRL and not c.group("f").isupper() for c in CALL_RE.finditer(s)):
            return None
        if any(_writes(s, x) for x in evars):
            return None
        if j == len(between) - 1:
            break                                     # the read's own statement stores after it reads
        st = _stores(s) if s.strip() else None
        if st and st[0] != "var" and mem and not _disjoint(chains, st[1]):
            return None
        if st and st[0] == "unknown":
            return None
    bs, af = F.ml[r][:hit[0].start()].rstrip(), F.ml[r][hit[0].end():].lstrip()
    top_comma = re.search(r",", re.sub(r"\((?:[^()]|\([^()]*\))*\)|\[[^\]]*\]", "", e_m))
    bare = ((bs.endswith("[") and af.startswith("]"))                       # a whole subscript
            or (bs.endswith(("(", ",")) and af.startswith((")", ",")) and not top_comma)   # a whole argument
            or (re.search(r"(?:(?:^|[^-+*/%&|^<>=!])=|\breturn)$", bs) and af.startswith(";")))  # a whole rhs
    ins = e_real if (_postfix(e_m) or bare) else "(%s)" % e_real
    ln = _nl(t.lines[r])
    ln = ln[:hit[0].start()] + ins + ln[hit[0].end():]
    cand = t.build({r: ln}, {lo})
    return cand if _pin_sig(cand) == want else None


def declorder_candidates(text):
    """DECL ORDER: one local's declaration moved directly before another's.

    REPORT.md "DECL ORDER" (dungeon/func_80CEA348, `next_y ASM_REG("$19")` off): `next_x` declared
    directly before `next_y`.  Both are global allocnos with equal priority, so global-alloc's
    `allocno_compare` falls to its tie-break, the allocno number - declaration order - and the
    oracle trace of the candidate is the base's with only greg's order flipped.  Ties need twins,
    so the pairs are two plain locals of one declaration list, both live across a basic-block
    boundary, with twin names (`next_x`/`next_y`) or parallel uses (the same statement shape on
    neighbouring lines) - every pair of such globals under NATURAL_ALLOC_WIDE.  The later one moves
    directly before the earlier one (their only other relative order); it must have no initialiser
    (nothing is evaluated in a different order), and a pinned declaration never moves.
    """
    try:
        return _declorder(text)
    except Exception:
        return []


def _shape(s, name):
    s = re.sub(r"(->|\.)[ \t]*%s" % ID, r"\1M", s.strip())
    s = re.sub(r"\b%s\b" % NUM, "N", s)
    return re.sub(r"\b%s\b" % re.escape(name), "@", _sq(s))


def _parallel(F, x, vx, y, vy):
    sx = {k: _shape(F.ml[k], x["name"]) for k in set(vx.lines)}
    sy = {k: _shape(F.ml[k], y["name"]) for k in set(vy.lines)}
    pairs = sum(1 for kx, a in sx.items() for ky, b in sy.items() if kx != ky and abs(kx - ky) <= 3 and a == b)
    return pairs >= 2


def _declorder(text):
    t = _T(text)
    want = _pin_sig(text)
    scored = []
    for F in _functions(t):
        for blk, ds in F.decls.items():
            ok = [d for d in ds if F.usable(d, init_ok=True)]
            for i, x in enumerate(ok):
                for y in ok[i + 1:]:                  # y declared after x: y moves before x
                    if y["init"] is not None or y["line"] == x["line"]:
                        continue
                    vx, vy = F.var(x), F.var(y)
                    if not vx.lines or not vy.lines or not (vx.glob and vy.glob):
                        continue
                    tier = 0 if _twin_names(x["name"], y["name"]) else \
                        1 if x["ty"] == y["ty"] and _parallel(F, x, vx, y, vy) else 2
                    if tier == 2 and not ALLOC_WIDE:
                        continue
                    edits = {x["line"]: _nl(t.lines[y["line"]]) + "\n" + _nl(t.lines[x["line"]])}
                    cand = t.build(edits, {y["line"]})
                    if _pin_sig(cand) != want:
                        continue
                    scored.append(((tier, x["line"], y["line"]),
                                   "declorder:%s<%s@%d" % (y["name"], x["name"], x["line"] + 1), cand))
    return _capped(scored)


# ------------------------------------------------------------------------------ the menu

GENERATORS = (dropcopy_candidates, armstore_candidates, ret2break_candidates, ptr2index_candidates,
              postinc_candidates, gotoloop_candidates, splitcursor_candidates, realloop_candidates,
              host_candidates, hostwide_candidates, unhost_candidates, declorder_candidates)
# the register-allocation levers: many per row, so a budgeted menu appends them after its own shapes
ALLOC_LEVERS = (host_candidates, hostwide_candidates, unhost_candidates, declorder_candidates)


def candidates(text, basesym=True, host=True):
    """Every natural-shape candidate for a text, deduplicated, the input itself excluded.

    host=False leaves out `host_candidates` (~11 per row on 525 rows) and the three fakedep levers
    (`ALLOC_LEVERS`, at most ALLOC_CAP each): a budgeted menu that puts the natural shapes first
    (t15/t18) appends them itself, after its own proven shapes."""
    out, seen = [], {text}
    gens = GENERATORS if host else tuple(g for g in GENERATORS if g not in ALLOC_LEVERS)
    for gen in gens + ((basesym_candidates,) if basesym else ()):
        try:
            got = gen(text)
        except Exception:                  # a generator bug must cost its own candidates only
            continue
        for label, cand in got:
            if cand not in seen:
                seen.add(cand)
                out.append((label, cand))
    return out
