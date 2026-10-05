"""T144: m2c's hand-spelled signed division / remainder by a power of two written back as `/` and `%` (readability; pins untouched).

APPEARS     the t17 shape `d = x; if (x < 0) { d = x + 4095; } y = d >> 12;` and the t19 shape
            `if (x < 0) ad = x + 4095; r = x - ((ad >> 12) << 12);` (and the `+=` variants), detected by those
            generators' own matchers (t17_divpow2.idioms / t19_modpow2.idioms, 2^n > 2).
RESOLVES    expand_divmod emits that exact code for `x / 2^n` and `x % 2^n`, so where m2c's copy held no register
            or order the rewrite is byte-neutral.  Spellings per site, in order: the t17/t19 rewrite as is (copy
            left, `(d / 4096)`); then, when d is a plain copy of x that nothing else reads, `x / 4096` with the
            copy and the bias variable's declaration removed.  Nothing volatile / asm / one-trip is ever added.
SEARCH      every site jointly (first spelling), then each site alone (last first), each spelling in turn,
            greedily keeping what stays exact, within T144_MAX verifies.
ACCEPTANCE  pins never change; the idiom count (bias ifs) strictly falls; byte-exact.  Works on pinned and
            pin-free rows alike (the t17/t19 generators only take pinned rows).
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
try:
    from . import t17_divpow2 as D, t19_modpow2 as M
    from .t12_stmtorder import mask
except ImportError:
    import t17_divpow2 as D, t19_modpow2 as M
    from t12_stmtorder import mask

MAX_VERIFY = int(os.environ.get("T144_MAX", "24"))
ID = r"[A-Za-z_]\w*"


def _scored_ok(text, pos):
    """Not inside a macro line or a preprocessor-dead arm: leave those alone."""
    ls = text.rfind("\n", 0, pos) + 1
    return not text[ls:pos].lstrip().startswith("#")


def sites(text):
    """[(kind, item)] ordered by position; a bias `if` claimed by the remainder matcher is not also a division."""
    mods = M.idioms(text)
    taken = {(it["start"], it["end"]) for it in mods}
    out = [("mod", it) for it in mods if _scored_ok(text, it["start"])]
    out += [("div", it) for it in D.idioms(text) if (it["start"], it["end"]) not in taken and _scored_ok(text, it["start"])]
    return sorted(out, key=lambda s: s[1]["start"])


def count(text):
    return len(sites(text))


def _func_span(masked, pos):
    """(start, end) of the top-level `{...}` containing pos."""
    depth, start = 0, None
    for i, ch in enumerate(masked):
        if ch == "{":
            if depth == 0:
                start = i
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0 and start is not None and start <= pos <= i:
                return start, i + 1
    return 0, len(masked)


def _drop_var(text, var):
    """Remove `var`'s declaration (alone, or one name of a comma list); None if the shape is not simple."""
    m = re.search(r"^([ \t]*(?:register\s+)?[\w\s\*]+?[ \t]+\**)%s[ \t]*;[ \t]*\n" % re.escape(var), text, re.M)
    if m and re.match(r"^\s*(?:register\s+)?(?:[su](?:8|16|32|64)|int|short|char|long|unsigned\s+\w+)\b", m.group(0)):
        return text[:m.start()] + text[m.end():]
    for m in re.finditer(r"^([ \t]*(?:register\s+)?(?:[su](?:8|16|32|64)|int|short|char|long)[ \t]+)([^;\n(]*);", text, re.M):
        names = [n.strip() for n in m.group(2).split(",")]
        if var in names and len(names) > 1:
            names.remove(var)
            return text[:m.start()] + m.group(1) + ", ".join(names) + ";" + text[m.end():]
    return None


def _forward(base, before, it):
    """Second spelling: `(d / K)` -> `(x / K)` with the copy `d = x;` and d's declaration gone, when d is
    a pure copy of x, read nowhere else, and x is not written in between.  None when it does not apply."""
    d = it["d"] if it.get("d") else None
    if not d:
        return None
    mb, ma = mask(before), mask(base)
    # the copy source of d at the bias if
    m = None
    for mm in re.finditer(r"(?<![.>\w])\b%s\s*=\s*(\(\s*s32\s*\)\s*)?(%s)\s*;" % (re.escape(d), ID), mb[:it["start"]]):
        m = mm
    if m is None:
        return None
    x = m.group(2)
    if x == d:
        return None
    # find the copy in the rewritten text (same prefix: everything before the bias if is unchanged)
    cs, ce = m.start(), m.end()
    f0, f1 = _func_span(ma, cs)
    body = ma[f0:f1]
    uses = [u for u in re.finditer(r"(?<![.>\w])\b%s\b" % re.escape(d), body)]
    # every remaining use must be the copy itself, the declaration, or a `(d / K)` / `(d % K)` operand
    rest = []
    for u in uses:
        a = f0 + u.start()
        if cs <= a < ce:
            continue
        tail = ma[f0 + u.end():f0 + u.end() + 12]
        if re.match(r"\s*[/%]\s*\d+", tail):
            rest.append(a)
        else:
            return None
    if not rest or any(a < ce for a in rest):
        return None
    last = max(rest)
    span = ma[ce:last]
    if re.search(r"(?<![.>\w])\b%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)|&\s*%s\b|\b%s\s*(?:\+\+|--)|\b%s\b\s*[-+]{2}" % ((re.escape(x),) * 4), span):
        return None
    if re.search(r"\b\w+\s*\(", span):     # a call between could change a global x
        return None
    t = base
    for a in sorted(rest, reverse=True):
        t = t[:a] + x + t[a + len(d):]
    # drop the copy statement (the copy lies before the bias, so offsets are unchanged)
    ls = t.rfind("\n", 0, cs) + 1
    le = t.find("\n", ce)
    if t[ls:cs].strip() == "" and le >= 0 and t[ce:le].strip() == "":
        t = t[:ls] + t[le + 1:]
    else:
        t = t[:cs] + t[ce:]
    t2 = _drop_var(t, d)
    return t2


def spellings(text, kind, it):
    """[(label, candidate)] for one site."""
    out = []
    one = D.spell_one(text, it) if kind == "div" else M.spell_one(text, it)
    if not one:
        return out
    first = one[0][1]
    first = _parens(text, first)
    out.append((one[0][0], first))
    try:
        fw = _forward(first, text, it)
    except Exception:
        fw = None
    if fw:
        out.append(("fwd", fw))
    out += [(l, _parens(text, c)) for l, c in one[1:]]
    return out


def _parens(old, new):
    """`((x / 8))` -> `(x / 8)` where the doubled parentheses are new."""
    pat = re.compile(r"\(\((%s\s*[/%%]\s*\d+)\)\)" % ID)
    return pat.sub(lambda m: m.group(0) if m.group(0) in old else "(" + m.group(1) + ")", new)


def rewrite_all(text, fwd=False):
    """Every site, last first, re-found after each edit (an edit below never moves an earlier site)."""
    cur = text
    n = len(sites(cur))
    for idx in reversed(range(n)):
        ss = sites(cur)
        if idx >= len(ss):
            continue
        sp = spellings(cur, *ss[idx])
        if sp:
            cur = sp[1][1] if fwd and len(sp) > 1 and sp[1][0] == "fwd" else sp[0][1]
    return cur


class T:
    name = "t144_divmod"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites(text) else "no signed power-of-two divide/remainder idiom"

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0, p0 = count(text), len(sites_of(text))
        if not n0:
            return None, {"refused": ["no idiom"]}
        budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or budget[0] <= 0:
                return False
            if len(sites_of(t)) != p0 or count(t) >= n0:
                return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        if n0 > 1:
            for fwd in (True, False):
                allt = rewrite_all(text, fwd)
                if ok(allt):
                    return allt, {"sites": n0, "kept": n0, "joint": True, "fwd": fwd, "verifies": len(tried)}
        cur, kept, c0 = text, 0, n0
        for idx in reversed(range(n0)):
            ss = sites(cur)
            if idx >= len(ss) or budget[0] <= 0:
                continue
            for label, cand in spellings(cur, *ss[idx]):
                if len(sites_of(cand)) == p0 and count(cand) == len(ss) - 1 and ok_one(cand, cur, vf, budget, tried):
                    cur, kept = cand, kept + 1
                    break
        if kept:
            return cur, {"sites": n0, "kept": kept, "verifies": len(tried)}
        return None, {"refused": ["no site exact (%d verifies)" % len(tried)], "sites": n0}


def ok_one(cand, cur, vf, budget, tried):
    if cand == cur or budget[0] <= 0:
        return False
    budget[0] -= 1; tried.append(1)
    return bool(vf(cand).get("exact"))
