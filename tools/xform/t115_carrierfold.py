"""T115: a kept CARRIER local folded away - the stored value, the re-read field or the source itself used where
the carrier was.

APPEARS     a local that only carries a value from where it is made to where it is used, with a keep or a
            register pin on it, in one of three shapes the late round-73 lanes solved (claude-opus-5-5):

            STORE    `t = C; F = t;` / `t |= K; F = t;` (t last loaded from or stored to F)
                     dungeon/func_81892C5C (r73_opus_p5): "APPEARS: `t = C; field = t; KEEP(t); t |= K;
                     field = t`. RESOLVES: `field = C; field |= K`."  Same family: town/func_800BF718
                     (r73_opus_p3): "`t = v; ASM_KEEP(t); ...; t += K; field = t;`, where `v` was loaded from
                     that same `field` -> `field += K;`".
            REREAD   `x = s->f; ... d = x; KEEP(d); r = a % d;` -> the field read again at the use
                     dungeon/func_800C30E4 (r73_opus_s11): "`if (s->field != 0) r = a % s->field;` - re-read the
                     field in the `%`"; dungeon/func_81886800 (r73_opus_p5): "read the field again in each
                     consumer (`G += F; w = F + (F >> k)`)" - cse turns the re-read into a register copy that
                     combine keeps, which is retail's move.
            USEFIRST `KEEP(x); h = x; USE(h);` -> `USE(x); h = x;`
                     dungeon/func_800C0848 (r73_opus_s12): "APPEARS as a keep between `x = load; y = x; f(y)`.
                     RESOLVES as `f(x); y = x;`"; dungeon/func_818B7264 (r73_opus_p5): "`KEEP(x); home = x;
                     field = home;` ... store from x first, then copy to the home."

RESOLVES    the carrier's pseudo is either gone (STORE, REREAD) or set once from a value already consumed
            (USEFIRST), so combine/cse see the store or the use against the original pseudo; the keep was
            standing in for that order.

WHY THE OWNERS MISS IT  t107_incstore folds only increments (`v++; LV = v;`), t94/t100 only scalarised
            read-modify-write blocks; t82/t105 move whole statements and never substitute a carrier.

CANDIDATES  per local v named by a pin (a keep argument or a register-pinned declaration), over the one-line
            statements of its function: every single rule instance on v, v's rules applied to a fixpoint,
            and every pinned v's rules to a fixpoint jointly.  Rules: SUBST - `v = E;` (E free of calls, `=`,
            `++`/`--` and v) substituted into v's reads up to its next assignment (a compound assignment there
            becomes `v = (E) op X;`), the definition dropped; STORE - `v = E; [..] LV = v;` -> `LV = E;` and
            `v op= X; [..] LV = v;` -> `LV op= X;` when v last came from or went to LV, else `LV = v op X;`,
            when v is not read again before its next plain assignment; USEFIRST - `h = x; S` with S reading h
            and assigning neither -> `S[h:=x]; h = x;`.  Pins on the touched locals erased (then every pin of
            the function).  Ranked by cc1 listing distance to the pinned text; listing-exact candidates and
            the two nearest go to `vf`.
            T115_CALLCOPY=1 (default ON, round 76): `KEEP(v); x = f(.. v ..); v = w;` -> the call's result routed
            through v (`v = (Tv)f(.. v ..); x = (Tx)v;`) - callcopy_candidates(), dungeon/func_809DB054.
"""
import difflib
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text, arm_labels
from pin_sites import erase_many
try:
    from .t36_paramwidth import functions
    from .t29_addrsym import decls_of
    from . import screen
except ImportError:
    from t36_paramwidth import functions
    from t29_addrsym import decls_of
    import screen

MAX_VARS = 8
MAX_STEPS = 24
CLUSTER = 6           # lines between rule instances of one statement run
MAX_LISTINGS = 40
MAX_VERIFY = 4
ID = r"[A-Za-z_]\w*"
MENTION = r"(?<![.>\w])%s\b"
STMT = re.compile(r"^(?P<ind>[ \t]*)(?P<lhs>(?:->|[^;{}=!<>])*?(?:\w|\]|\)))[ \t]*"
                  r"(?P<op>[-+*/%&|^]|<<|>>)?=(?!=)[ \t]*(?P<rhs>[^;{}]*);[ \t]*(?P<cmt>/\*.*\*/)?[ \t]*$")
KEYWORD = re.compile(r"^\s*(?:if|else|for|while|do|switch|case|default|return|goto|break|continue)\b")
CALL = re.compile(r"(?<![\w)\]])(?!(?:sizeof|abs)\b)[A-Za-z_]\w*\s*\(")
PIN_LINE = re.compile(r"^[ \t]*ASM_[A-Z_0-9]+\s*\(")
DECL = re.compile(r"^[ \t]*(?:(?:register|unsigned|signed|const|volatile|struct|union|enum)[ \t]+)*[A-Za-z_]\w*[ \t\*]+"
                  r"(?P<v>[A-Za-z_]\w*)[ \t]*(?:ASM_REG\([^()]*\))?[ \t]*(?:=[^;]*)?;")


def stmt(line):
    """(ind, lhs, op, rhs) of a one-line assignment statement, else None."""
    if KEYWORD.match(line) or PIN_LINE.match(line) or DECL.match(line):
        return None
    m = STMT.match(line)
    if not m:
        return None
    return m.group("ind"), m.group("lhs").strip(), m.group("op") or "", m.group("rhs").strip()


def pure(e, v=None):
    return not (CALL.search(e) or re.search(r"(?<![=!<>])=(?!=)|\+\+|--", e) or
                (v and re.search(MENTION % re.escape(v), e)))


def mentions(line, v):
    return re.search(MENTION % re.escape(v), line) is not None


def assigns(line, v):
    return re.search(r"(?<![.>\w])%s\s*(?:=(?!=)|[-+*/%%&|^]=|<<=|>>=|\+\+|--)|(?:\+\+|--)\s*%s\b"
                     % (re.escape(v), re.escape(v)), line) is not None


def paren(e):
    return e if re.fullmatch(r"[\w.>\-\[\]]+|\([^()]*\)\s*[\w.>\-\[\]]+", e) and "->" not in e.replace("->", "", 0) \
        or re.fullmatch(r"[A-Za-z_][\w]*(?:(?:->|\.)\w+|\[[^\[\]]*\])*", e) else "(%s)" % e


def subst(line, v, e):
    return re.sub(MENTION % re.escape(v), lambda m: paren(e), line)


class Body:
    """The lines of one function body; `live` lines are those a rule may touch (scored, not preprocessor)."""

    def __init__(self, lines, lo, hi, labels):
        self.lines, self.lo, self.hi, self.labels = lines, lo, hi, labels

    def ok(self, i):
        lab = self.labels[i] if i < len(self.labels) else None
        return self.lo <= i < self.hi and lab not in ("port", "dead") and not self.lines[i].lstrip().startswith("#")

    def depth_ok(self, i, j):
        """Lines i..j sit in one block (no net `}` below line i's depth)."""
        d = 0
        for k in range(i + 1, j + 1):
            code = re.sub(r"/\*.*?\*/|//.*$", "", self.lines[k])
            d += code.count("{") - code.count("}")
            if d < 0:
                return False
        return True

    def next_stmt(self, i):
        k = i + 1
        while k < self.hi and (not self.lines[k].strip() or PIN_LINE.match(self.lines[k])
                               or self.lines[k].strip().startswith(("/*", "//"))):
            k += 1
        return k if k < self.hi else None

    def reads_until_def(self, i, v):
        """Lines after i that read v before v's next assignment, and that assignment's line (or None)."""
        reads = []
        for k in range(i + 1, self.hi):
            ln = self.lines[k]
            if PIN_LINE.match(ln) or not mentions(ln, v):
                continue
            st = stmt(ln)
            if st and st[1] == v:
                if st[2] or mentions(st[3], v):
                    reads.append(k)
                return reads, k
            if assigns(ln, v):
                return reads + [k], k
            reads.append(k)
        return reads, None


def _castof(e, v):
    """'' when e is v, the cast text when e is `(T)v`, else None."""
    if e == v:
        return ""
    m = re.fullmatch(r"(\(\s*[A-Za-z_][\w \t]*\**\s*\))\s*%s" % re.escape(v), e)
    return m.group(1) if m else None


def rule_instances(b, v):
    """[(kind, fn)] - each fn(lines) applies one rule instance on v in place and returns True, or False."""
    out = []
    for i in range(b.lo, b.hi):
        if not b.ok(i):
            continue
        st = stmt(b.lines[i])
        if not st:
            continue
        ind, lhs, op, rhs = st
        if lhs != v:
            # USEFIRST keyed on the pinned SOURCE: `h = v; S(h)` (dungeon/func_800C0848, func_818B7264)
            if rhs == v and not op and re.fullmatch(ID, lhs):
                k = b.next_stmt(i)
                if k is not None and b.ok(k) and _usefirst_ok(b, i, k, lhs, rhs):
                    out.append(("usefirst@%d" % (i + 1), i))
            continue
        if not op and pure(rhs, v):
            out.append(("subst@%d" % (i + 1), i))
        k = b.next_stmt(i)
        if k is not None and b.ok(k):
            s2 = stmt(b.lines[k])
            if s2 and not s2[2] and _castof(s2[3], v) is not None and s2[1] != v and b.depth_ok(i, k):
                out.append(("store@%d" % (i + 1), i))
            if not op and re.fullmatch(ID, rhs) and _usefirst_ok(b, i, k, v, rhs):
                out.append(("usefirst@%d" % (i + 1), i))
    # fixpoint order: stores bottom-up (a read-modify-write store must see the store before it), then
    # use-first, then substitution
    rank = {"store": 0, "usefirst": 1, "subst": 2}
    out.sort(key=lambda x: (rank[x[0].split("@")[0]], -x[1] if x[0].startswith("store") else x[1]))
    return out


def _usefirst_ok(b, i, k, h, x):
    ln = b.lines[k]
    if not b.depth_ok(i, k) or KEYWORD.match(ln) or not mentions(ln, h):
        return False
    s2 = stmt(ln)
    if s2 is None:
        return not assigns(ln, h) and not assigns(ln, x) and ";" in ln and "{" not in ln and "}" not in ln
    return s2[1] not in (h, x) and not mentions(s2[1], h) and mentions(s2[3], h) and not s2[2]


def apply(b, v, kind, i):
    """Apply one rule at line i (the definition of v); True when the lines changed."""
    L = b.lines
    st = stmt(L[i])
    if not st:
        return False
    ind, lhs, op, rhs = st
    if kind.startswith("usefirst"):
        k = b.next_stmt(i)
        L[k] = subst(L[k], lhs, rhs)
        moved = L[i]
        L[i] = None
        L[k] = L[k] + "\n" + moved
        return True
    if lhs != v:
        return False
    if kind.startswith("subst"):
        reads, dj = b.reads_until_def(i, v)
        if not reads:
            return False
        for k in reads:
            if not b.ok(k):
                return False
            s2 = stmt(L[k])
            if s2 and s2[1] == v and s2[2]:           # `v op= X` -> `v = (E) op X`
                L[k] = "%s%s = %s %s %s;" % (s2[0], v, paren(rhs), s2[2], paren(s2[3]))
            elif s2 and s2[1] == v:
                L[k] = "%s%s = %s;" % (s2[0], v, subst(s2[3], v, rhs))
            else:
                L[k] = subst(L[k], v, rhs)
        L[i] = None
        return True
    if kind.startswith("store"):
        k = b.next_stmt(i)
        s2 = stmt(L[k])
        later, dj = b.reads_until_def(k, v)
        if later:
            return False
        lv, cast = s2[1], _castof(s2[3], v)
        if not op:
            L[k] = "%s%s = %s%s;" % (s2[0], lv, cast, paren(rhs) if cast else rhs)
        else:
            came = None
            for p in range(i - 1, b.lo - 1, -1):
                if L[p] is None or not mentions(L[p], v) or PIN_LINE.match(L[p]):
                    continue
                sp = stmt(L[p])
                if sp and sp[1] == v and not sp[2] and sp[3] == lv:
                    came = True
                elif sp and sp[1] == lv and sp[3] == v and not sp[2]:
                    came = True
                break
            L[k] = ("%s%s %s= %s;" % (s2[0], lv, op, rhs)) if came else \
                   ("%s%s = %s %s %s;" % (s2[0], lv, v, op, paren(rhs)))
        L[i] = None
        return True
    return False


def compact(lines):
    return [l for l in lines if l is not None]


def pinned_locals(text, b0, b1):
    names = []
    for p in sites_of(text):
        if not (b0 <= p[3] < b1):
            continue
        seg = text[text.rfind("\n", 0, p[3]) + 1:text.find("\n", p[3])]
        if p[1] == "ASM_REG":
            m = DECL.match(seg)
            if m:
                names.append(m.group("v"))
        elif p[0] == "stmt":
            names += re.findall(ID, p[2] or "")
    out = []
    for n in names:
        if n not in out and not n.startswith(("ASM_", "D_", "func_")):
            out.append(n)
    return out[:MAX_VARS]


def run(text, fn, plan):
    """Apply `plan` - [(v, kind)] single instances, or [(v, None)] fixpoints - to function fn."""
    lines = text.split("\n")
    labels = arm_labels(text)
    starts, at = [], 0
    for l in lines:
        starts.append(at); at += len(l) + 1
    lo = next(i for i, s in enumerate(starts) if s > fn[2]) if any(s > fn[2] for s in starts) else len(lines)
    hi = max(i for i, s in enumerate(starts) if s <= fn[3])
    touched = set()
    for v, kind in plan:
        steps = 0
        while steps < MAX_STEPS:
            b = Body(lines, lo, hi, labels)
            insts = rule_instances(b, v)
            if kind and kind.startswith("range:"):
                a, z = map(int, kind.split(":")[1:])
                insts = [x for x in insts if a <= x[1] <= z]
            elif kind:
                insts = [x for x in insts if x[0] == kind]
            done = False
            for k, i in insts:
                if apply(b, v, k, i):
                    touched.add(v); done = True
                    break
            if not done:
                break
            # re-split (a usefirst move joins two lines) and re-index; arm labels follow the moved lines
            new = []
            newlab = []
            for l, lab in zip(lines, labels + [None] * (len(lines) - len(labels))):
                if l is None:
                    continue
                for part in l.split("\n"):
                    new.append(part); newlab.append(lab)
            hi -= len(lines) - len(new)
            lines, labels = new, newlab
            steps += 1
            if kind and not kind.startswith("range:"):
                break
    return "\n".join(lines), touched


def erase_named(text, names, allpins=False, stmts_only=False):
    """Pins naming `names` erased (stmts_only: keeps/barriers only, register declarations stay), or all pins."""
    grp = []
    for p in sites_of(text):
        if stmts_only and p[0] != "stmt":
            continue
        seg = text[text.rfind("\n", 0, p[3]) + 1:text.find("\n", p[4] - 1 if p[4] > p[3] else p[3])]
        if allpins or any(mentions(seg, n) for n in names):
            grp.append(p)
    return erase_many(text, grp, clean_notes=True) if grp else text


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    labels = arm_labels(text)
    for fn in functions(text):
        vs = pinned_locals(text, fn[2], fn[3])
        if not vs:
            continue
        plans = []
        for v in vs:
            lines = text.split("\n")
            lo = text.count("\n", 0, fn[2]) + 1
            hi = text.count("\n", 0, fn[3])
            insts = rule_instances(Body(lines, lo, hi, labels), v)
            for kind, _i in insts:
                plans.append(("%s:%s" % (v, kind), [(v, kind)]))
            # clusters: a fixpoint over the instances within CLUSTER lines of each other (one statement run)
            at = sorted({i for _k, i in insts})
            groups, cur = [], []
            for i in at:
                if cur and i - cur[-1] > CLUSTER:
                    groups.append(cur); cur = []
                cur.append(i)
            if cur:
                groups.append(cur)
            if len(groups) > 1:
                for g in groups:
                    if len(g) > 1:
                        plans.append(("%s:fix@%d-%d" % (v, g[0] + 1, g[-1] + 1), [(v, "range:%d:%d" % (g[0], g[-1]))]))
            plans.append(("%s:fix" % v, [(v, None)]))
        if len(vs) > 1:
            plans.append(("all:fix", [(v, None) for v in vs]))
        for label, plan in plans:
            try:
                t2, touched = run(text, fn, plan)
            except (StopIteration, ValueError, IndexError):
                continue
            if not touched or t2 == text:
                continue
            for ptag, allp, stmts in (("named", False, False), ("stmt", False, True), ("all", True, False)):
                cand = erase_named(t2, touched, allp, stmts)
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("%s:%s" % (label, ptag), cand))
    if os.getenv("T115_CALLCOPY", "1") == "1":
        for label, t2, v in callcopy_candidates(text):
            for ptag, allp in (("named", False), ("all", True)):
                cand = erase_named(t2, {v}, allp) if allp else t2
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("%s:%s" % (label, ptag), cand))
    return out


KEEP1 = re.compile(r"^[ \t]*ASM_KEEP(?:_NV)?[ \t]*\([ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*\)[ \t]*;")
CALLSET = re.compile(r"^(?P<ind>[ \t]*)(?P<x>[A-Za-z_]\w*)[ \t]*=(?!=)[ \t]*(?P<rhs>(?:\([^()]*\)[ \t]*)?"
                     r"[A-Za-z_]\w*[ \t]*\(.*\))[ \t]*;[ \t]*(?:/\*.*\*/)?[ \t]*$")
RESET = re.compile(r"^[ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*=(?!=)[ \t]*(?P<rhs>[^;]*);")


def _vtype(text, fn, v):
    for p, t, _a, _b in fn[1]:
        if p == v:
            return re.sub(r"\s+", " ", re.sub(r"\bregister\b", "", t)).strip()
    ds = [d for d in decls_of(text, v) if fn[2] < d[2][0] < fn[3]]
    if len(ds) == 1:
        return (ds[0][0] + " " + "*" * ds[0][1]).strip()
    return None


def callcopy_candidates(text):
    """T115_CALLCOPY (round 76): `KEEP(v); x = f(.. v ..); v = w;` -> `v = (Tv)f(.. v ..); x = (Tx)v; v = w;`.

    dungeon/func_809DB054 (claude-opus-5-5, r76o_opus_b12; astra solved it too, r76o_astra_b12): "APPEARS:
    `ASM_KEEP(v)` right before a call that takes v, where v is a copy of another variable and is re-set to that
    variable right after the call. RESOLVES: assign the call's result to v, then copy it to the result variable,
    so the re-set is no longer redundant for cse."  Without the keep cse knows `v == w` across the call and
    deletes the re-set; routed through v, the call result is a second value of v and the re-set stays."""
    out = []
    lines = text.split("\n")
    for fn in functions(text):
        lo, hi = text.count("\n", 0, fn[2]), text.count("\n", 0, fn[3])
        for i in range(lo, min(hi, len(lines) - 2)):
            km = KEEP1.match(lines[i])
            if not km:
                continue
            v = km.group("v")
            j = i + 1
            while j < hi and not lines[j].strip():
                j += 1
            cm = CALLSET.match(lines[j])
            if not cm or cm.group("x") == v or not mentions(cm.group("rhs"), v):
                continue
            k = j + 1
            while k < hi and not lines[k].strip():
                k += 1
            rm = RESET.match(lines[k])
            if not rm or rm.group("v") != v or mentions(rm.group("rhs"), v):
                continue
            tv, tx = _vtype(text, fn, v), _vtype(text, fn, cm.group("x"))
            if not tv or not tx:
                continue
            same = re.sub(r"\s", "", tv) == re.sub(r"\s", "", tx)
            ind, x, rhs = cm.group("ind"), cm.group("x"), cm.group("rhs")
            for tag, a, b in (("cast", "(%s)" % tv, "(%s)" % tx), ("bare", "", "")):
                if tag == "bare" and not same:
                    continue
                if tag == "cast" and same:
                    continue
                nl = list(lines)
                nl[j] = "%s%s = %s%s;\n%s%s = %s%s;" % (ind, v, a, rhs, ind, x, b, v)
                nl[i] = None
                t2 = "\n".join(z for z in nl if z is not None)
                out.append(("%s@%d:callcopy:%s" % (v, i + 1, tag), t2, v))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t115_carrierfold"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not candidates(text):
            return "no pinned carrier local with a store/re-read/use-first rewrite"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        menu = candidates(text)
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        # fixpoints and joint plans first: they are the lanes' shapes; singles fill the rest of the budget
        menu.sort(key=lambda c: (":fix" not in c[0] and ":usefirst" not in c[0] and ":callcopy" not in c[0],
                                 len(sites_of(c[1]))))
        ranked, listings = [], 0
        for label, cand in menu:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((_dist(target, lst), len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
