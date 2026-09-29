"""T124: a forward "skip" goto written as the if / if-else it was (readability; pins untouched).

APPEARS     m2c renders gcc's forward branches as labels and gotos:
              (1) `if (C) goto L; BODY L:`                        - a skip over BODY
              (2) `if (C) { A goto L; } B L:`                     - if/else whose then-arm jumps over the else-arm
              (3) `if (C) goto A; B1 goto J; A: B2 J:`            - the same with the else-arm first
            Round 80 (r80_sonnet_gp1): one text rewriter of these shapes turned 34 gotos of dungeon/func_819835AC
            into structured code in one pass, byte-exact.
RESOLVES    (1) `if (!C) { BODY }`   (2) `if (C) { A } else { B }`   (3) `if (!C) { B1 } else { B2 }`.
            BODY / B hold no label and no top-level case/default (nothing jumps into them) and are balanced
            blocks of the SAME nesting level as the label.  The `if` must start its own line and not follow
            `else` or an unbraced control head.  Other gotos to L are fine (L stays after the block); L is
            removed once nothing targets it.  Nested skips resolve inner-first (their labels vanish first).
            Sites in `#if` arms are never touched.  Pins are never touched.  Candidates: all sites at once,
            then per label, then per site (inner first), greedily keeping what stays exact.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, arm_labels, HAS_PP_RE
try:
    from .t122_gotowhile import mask, match_close, KEYWORDS, gotos, norm, reindent, line_indent
except ImportError:
    from t122_gotowhile import mask, match_close, KEYWORDS, gotos, norm, reindent, line_indent

MAX_VERIFY = int(os.environ.get("T124_MAX", "24"))
IF_HEAD = re.compile(r"\bif[ \t\n]*\(")
ATOM = re.compile(r"^[A-Za-z_]\w*(?:\.\w+|->\w+|\[[^\[\]]*\]|\([^()]*\))*$")
CMP = re.compile(r"(?<![-<>=!])(<=|>=|==|!=|<|>)(?![<>=])")
INVOP = {"<=": ">", ">=": "<", "==": "!=", "!=": "==", "<": ">=", ">": "<="}


# ---- condition inversion -------------------------------------------------------------------
def _wrapped(c):
    return len(c) > 1 and c[0] == "(" and match_close(c, 0) == len(c) - 1


def _strip(c):
    c = c.strip()
    while _wrapped(c): c = c[1:-1].strip()
    return c


def _depth0(c):
    """c with everything inside () and [] blanked."""
    out, d = [], 0
    for ch in c:
        if ch in "([": d += 1; out.append(" ")
        elif ch in ")]": d -= 1; out.append(" " if d else "x")
        else: out.append(" " if d else ch)
    return "".join(out)


def inv(c):
    """Logical negation of the C condition text c, as readable as it can be."""
    c = _strip(norm(c))
    if c.startswith("!"):
        rest = c[1:].lstrip()
        if _wrapped(rest): return _strip(rest)
        if ATOM.match(rest): return rest
    d0 = _depth0(c)
    if re.search(r"&&|\|\||\?|,|[-+*/%&|^]=|<<=|>>=|(?<![=!<>])=(?!=)|[|^]|\w\s*&", d0):
        return "!(%s)" % c
    cm = list(CMP.finditer(d0))
    if len(cm) == 1:
        a, b = cm[0].span()
        return c[:a] + INVOP[cm[0].group(1)] + c[b:]
    if not cm and ATOM.match(c): return "!" + c
    return "!(%s)" % c


# ---- structure ------------------------------------------------------------------------------
def _label_re(L):
    return re.compile(r"^[ \t]*%s[ \t]*:[ \t]*(?:;[ \t]*)?\n" % re.escape(L), re.M)


def _flat(seg):
    """seg is a run of whole statements: braces balanced, never negative, no label, no top-level case/default."""
    d = 0
    for i, ch in enumerate(seg):
        if ch == "{": d += 1
        elif ch == "}":
            d -= 1
            if d < 0: return False
        elif d == 0 and (seg.startswith("case", i) or seg.startswith("default", i)) \
                and (i == 0 or not (seg[i - 1].isalnum() or seg[i - 1] == "_")) and re.match(r"(case\b|default\s*:)", seg[i:]):
            return False
    if d: return False
    for lm in re.finditer(r"^[ \t]*([A-Za-z_]\w*)[ \t]*:", seg, re.M):
        if lm.group(1) not in KEYWORDS: return False
    return "#" not in seg


def _tail_goto(m, lo, hi):
    """(start, label) of a `goto X;` that is the LAST statement of m[lo:hi], at its own nesting level."""
    g = re.search(r"\bgoto[ \t]+(\w+)[ \t]*;[ \t\n]*$", m[lo:hi])
    if not g: return None
    s = lo + g.start(); pre = m[lo:s]
    if not _flat(pre) and pre.strip(): return None
    if re.search(r"(\belse|\)|:)[ \t\n]*$", pre): return None
    return s, g.group(1)


def _nrefs(m, L):
    return len(re.findall(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(L), m))


def parse_at(text, pos):
    """The skip shape whose `if` starts at text[pos]: (span_start, span_end, [replacement, ...]) or None."""
    m = mask(text)
    r = IF_HEAD.match(m, pos)
    if not r: return None
    ls = m.rfind("\n", 0, pos) + 1
    if m[ls:pos].strip(): return None
    prev = m[:ls].rstrip()
    if prev and prev[-1] not in ";{}:" or re.search(r"\belse$", prev): return None
    po = r.end() - 1; pc = match_close(m, po)
    if pc < 0: return None
    C = norm(text[po + 1:pc])
    k = pc + 1
    while k < len(m) and m[k] in " \t\n": k += 1
    A = None
    g = re.compile(r"goto[ \t]+(\w+)[ \t]*;").match(m, k)
    if g:
        L, he = g.group(1), g.end()
    elif m[k:k + 1] == "{":
        bc = match_close(m, k)
        if bc < 0: return None
        tg = _tail_goto(m, k + 1, bc)
        if not tg: return None
        gs, L = tg; he = bc + 1
        A = text[k + 1:gs]
        if not A.strip(): A = None
    else:
        return None
    rest = re.match(r"[ \t]*\n", m[he:])
    if not rest: return None
    he += rest.end()
    if re.match(r"\s*else\b", m[he:]): return None
    lm = _label_re(L).search(m, he)
    if not lm: return None
    body = text[he:lm.start()]
    if not body.strip() or not _flat(m[he:lm.start()]): return None
    ind = line_indent(text, pos); ind4 = ind + "    "
    n = _nrefs(m, L)
    def tail_end(lmm, ll):        # span end: eat the label line when only this goto reached it
        return lmm.end() if _nrefs(m, ll) == 1 else lmm.start()
    reps = []
    if A is not None:             # shape (2): if (C) { A goto L; } B L:
        e = tail_end(lm, L)
        reps.append((ls, e, "%sif (%s) {\n%s%s} else {\n%s%s}\n" % (ind, C, reindent(A, ind4), ind, reindent(body, ind4), ind)))
        return reps
    # shape (3): if (C) goto A; B1 goto J; A: B2 J:   (A reached by this goto only)
    if n == 1:
        tg = _tail_goto(m, he, lm.start())
        if tg:
            gs, J = tg
            jm = _label_re(J).search(m, lm.end())
            if jm and J != L:
                b2 = text[lm.end():jm.start()]
                if b2.strip() and _flat(m[lm.end():jm.start()]):
                    e = tail_end(jm, J)
                    reps.append((ls, e, "%sif (%s) {\n%s%s} else {\n%s%s}\n"
                                 % (ind, inv(C), reindent(text[he:gs], ind4), ind, reindent(b2, ind4), ind)))
    e = tail_end(lm, L)
    reps.append((ls, e, "%sif (%s) {\n%s%s}\n" % (ind, inv(C), reindent(body, ind4), ind)))
    return reps


def _arm_ok(text, s, e):
    if not HAS_PP_RE.search(text): return True
    labels = arm_labels(text)
    a = text.count("\n", 0, s); b = text.count("\n", 0, e)
    return all(labels[i] == "both" for i in range(a, min(b + 1, len(labels))))


def sites(text):
    """[if_start offsets] of every `if (...) goto L;` / `if (...) { ...; goto L; }` head (validity is decided when applied)."""
    m = mask(text); out = []
    for r in IF_HEAD.finditer(m):
        p = r.start()
        if parse_at(text, p) is not None or _maybe(m, p):
            out.append(p)
    return out


def _maybe(m, p):
    """Cheap: an if whose then-part is a goto, for sites that only become valid once inner ones went."""
    po = m.find("(", p); pc = match_close(m, po)
    if pc < 0: return False
    k = pc + 1
    while k < len(m) and m[k] in " \t\n": k += 1
    if m.startswith("goto", k): return True
    if m[k:k + 1] == "{":
        bc = match_close(m, k)
        return bc > 0 and _tail_goto(m, k + 1, bc) is not None
    return False


def rewrite(text, chosen, alt=None):
    """Apply the sites starting at offsets `chosen` (indices into sites(text)), last first; site i's form alt[i] (default 0).
    Each site is re-parsed on the text as it is by then, so nested sites resolve inner-first."""
    ss = sites(text); t = text
    for i in sorted(chosen, key=lambda i: -ss[i]):
        reps = parse_at(t, ss[i])
        if not reps or not _arm_ok(t, reps[0][0], reps[0][1]): continue
        s, e, rep = reps[min((alt or {}).get(i, 0), len(reps) - 1)]
        t = t[:s] + rep + t[e:]
    return t


def label_of(text, p):
    m = mask(text); po = m.find("(", p); pc = match_close(m, po)
    g = re.compile(r"[ \t\n]*(?:\{[^{}]*?)?\bgoto[ \t]+(\w+)").match(m, pc + 1)
    tg = None
    if not g:
        return None
    k = pc + 1
    while m[k] in " \t\n": k += 1
    if m[k] == "{":
        bc = match_close(m, k); tg = _tail_goto(m, k + 1, bc)
        return tg[1] if tg else None
    return g.group(1)


class T:
    name = "t124_skipgoto"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if rewrite(text, range(len(sites(text)))) != text else "no skip-goto shape"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ss = sites(text)
        if not ss or rewrite(text, range(len(ss))) == text:
            return None, {"refused": ["no skip-goto shape"]}
        n0, g0 = len(sites_of(text)), gotos(text); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or gotos(t) >= g0 or budget[0] <= 0: return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        allidx = list(range(len(ss)))
        allt = rewrite(text, allidx)
        if ok(allt):
            return allt, {"gotos": g0 - gotos(allt), "verifies": len(tried)}
        keep, alt = [], {}
        labs = {}
        for i in allidx: labs.setdefault(label_of(text, ss[i]), []).append(i)
        if len(labs) > 1:
            for L, grp in sorted(labs.items(), key=lambda x: -len(x[1])):
                if ok(rewrite(text, keep + grp, alt)): keep += grp
        for i in sorted(allidx, key=lambda i: -ss[i]):        # inner first
            if i in keep: continue
            for a in range(2):
                if ok(rewrite(text, keep + [i], {**alt, i: a})):
                    keep.append(i); alt[i] = a; break
        if keep:
            t = rewrite(text, keep, alt)
            return t, {"gotos": g0 - gotos(t), "of": g0, "verifies": len(tried)}
        return None, {"refused": ["no skip-goto rewrite exact (%d verifies)" % len(tried)]}
