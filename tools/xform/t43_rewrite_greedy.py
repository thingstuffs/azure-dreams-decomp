"""T43: semantics-preserving statement rewrites as bases, then t41c's greedy pin erasure.

APPEARS     a pinned row with an if/else, an `&&` condition, an if nested alone in an if, a `?:`
            assignment, or an if comparing two plain operands.
RESOLVES    t41c showed that a structural rewrite which keeps the row exact with every pin in place
            can make other pins unnecessary (38 rows from goto loops). The statement shape of the
            original (arm order, condition nesting, ?: vs if/else, comparison operand order) sets RTL
            order, pseudos and block layout, which is what many block-order and code-motion pins
            compensate for. Menu, one site per base:
              armswap   if (C) {A} else {B}        ->  if (!C) {B} else {A}
              andnest   if (A && B) {X}            ->  if (A) { if (B) {X} }     (and back)
              ternary   x = c ? a : b;             ->  if (c) { x = a; } else { x = b; }  (and back)
              cmpswap   if (L < R)                 ->  if (R > L)   (plain operands only)
RESULT      first sweep (2026-09-13, 1,467 rows, 84 min, no errors): 1 row (an armswap freeing a
            fence and a keep). Negative: gcc canonicalizes these shapes to nearly the same RTL, so the
            base stays exact but frees nothing. Loop notes (t41c: 38 rows) are different in kind,
            because they switch an optimizer pass on or off.
Budget: T43_BUDGET scorer runs per row (default 60), at most T43_BASES bases per row (default 16).
A result must have fewer pins than the row. Rewrites inside NON_MATCHING arms are refused.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t41b_gotoloop_while import _close
    from .t41c_gotoloop_greedy import greedy
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t41b_gotoloop_while import _close
    from t41c_gotoloop_greedy import greedy

BUDGET = int(os.environ.get("T43_BUDGET", "60"))
BASES = int(os.environ.get("T43_BASES", "16"))
FLIP = {"==": "!=", "!=": "==", "<": ">=", ">=": "<", ">": "<=", "<=": ">"}
MIRROR = {"==": "==", "!=": "!=", "<": ">", ">": "<", "<=": ">=", ">=": "<="}
CMP = re.compile(r"^\s*(?P<l>[^=!<>&|?:]+?)\s*(?P<op>==|!=|<=|>=|<|>)\s*(?P<r>[^=!<>&|?:]+?)\s*$")
PLAIN = re.compile(r"^(?:\(\s*[A-Za-z_][\w\s\*]*\)\s*)?(?:[A-Za-z_][\w]*(?:(?:->|\.)\w+|\[[^\[\]]*\])*|-?(?:0x[0-9A-Fa-f]+|\d+)[UuLl]*)$")


def _top(s, tok):
    """Index of the first top-level occurrence of tok in s (outside parentheses), or -1."""
    depth = 0
    for i in range(len(s)):
        depth += (s[i] == "(") - (s[i] == ")")
        if depth == 0 and s.startswith(tok, i):
            return i
    return -1


def negate(c):
    m = CMP.match(c)
    if m and _top(c, "&&") < 0 and _top(c, "||") < 0:
        return "%s %s %s" % (m.group("l").strip(), FLIP[m.group("op")], m.group("r").strip())
    s = c.strip()
    if s.startswith("!(") and _close(s, 1, "(", ")") == len(s):
        return s[2:-1]
    return "!(%s)" % s


def ifs(text):
    """(if_start, cond_open, cond_close_excl, body_open, body_close, else_open, else_close) for braced ifs."""
    m, out = mask_comments(text), []
    for k in re.finditer(r"\bif\s*\(", m):
        p = k.end() - 1
        pe = _close(m, p, "(", ")")
        if pe is None:
            continue
        b = re.match(r"\s*\{", m[pe:])
        if not b:
            continue
        o = pe + b.end() - 1
        c = _close(m, o, "{", "}")
        if c is None:
            continue
        e = re.match(r"\s*else\s*\{", m[c:])
        eo = ec = None
        if e:
            eo = c + e.end() - 1
            ec = _close(m, eo, "{", "}")
        elif re.match(r"\s*else\b", m[c:]):
            continue                                              # else-if chains are left alone
        out.append((k.start(), p, pe, o, c - 1, eo, None if ec is None else ec - 1))
    return out


def rewrites(text):
    """(label, position, new text) for every menu rewrite that applies once."""
    out, m = [], mask_comments(text)
    for s, p, pe, o, c, eo, ec in ifs(text):
        cond = text[p + 1:pe - 1]
        if eo is not None and ec is not None:                     # armswap
            A, B = text[o + 1:c], text[eo + 1:ec]
            new = text[:s] + "if (" + negate(cond) + ") {" + B + "} else {" + A + "}" + text[ec + 1:]
            out.append(("armswap", s, new))
        if eo is None:
            i = _top(cond, "&&")
            if i >= 0 and _top(cond, "||") < 0:                   # andnest
                a, b = cond[:i].strip(), cond[i + 2:].strip()
                new = text[:s] + "if (" + a + ") { if (" + b + ") {" + text[o + 1:c] + "} }" + text[c + 1:]
                out.append(("andnest", s, new))
            inner = re.fullmatch(r"\s*if\s*\((.*)\)\s*\{(.*)\}\s*", m[o + 1:c], re.S)
            if inner and _close(m[o + 1:c].strip(), 3, "(", ")") is not None:
                t_in = text[o + 1:c].strip()
                ip = t_in.index("(")
                ipe = _close(t_in, ip, "(", ")")
                ib = re.match(r"\s*\{", t_in[ipe:])
                if ib and _close(t_in, ipe + ib.end() - 1, "{", "}") == len(t_in):
                    icond = t_in[ip + 1:ipe - 1]
                    ibody = t_in[ipe + ib.end():-1]
                    if _top(icond, "||") < 0 and _top(cond, "||") < 0:          # nested -> andnest back
                        new = text[:s] + "if (" + cond.strip() + " && " + icond.strip() + ") {" + ibody + "}" + text[c + 1:]
                        out.append(("andunnest", s, new))
            cm = CMP.match(cond)
            if cm and _top(cond, "&&") < 0 and _top(cond, "||") < 0 \
                    and PLAIN.match(cm.group("l").strip()) and PLAIN.match(cm.group("r").strip()):   # cmpswap
                new = text[:p + 1] + "%s %s %s" % (cm.group("r").strip(), MIRROR[cm.group("op")], cm.group("l").strip()) + text[pe - 1:]
                out.append(("cmpswap", s, new))
        if eo is not None and ec is not None:                     # if/else of one assignment each -> ternary
            a1 = re.fullmatch(r"\s*([^;=]+?)\s*=(?!=)\s*([^;]+);\s*", text[o + 1:c])
            a2 = re.fullmatch(r"\s*([^;=]+?)\s*=(?!=)\s*([^;]+);\s*", text[eo + 1:ec])
            if a1 and a2 and a1.group(1).strip() == a2.group(1).strip() and not re.search(r"[-+*/%&|^<>!]$", a1.group(1).strip()):
                ind = re.match(r"[ \t]*", text[text.rfind("\n", 0, s) + 1:]).group(0)
                new = text[:s] + "%s = %s ? %s : %s;" % (a1.group(1).strip(), cond.strip(), a1.group(2).strip(), a2.group(2).strip()) + text[ec + 1:]
                out.append(("unternary", s, new))
    for t in re.finditer(r"^([ \t]*)([^;{}=\n]+?)\s*=(?!=)\s*([^;{}\n]+?)\s*\?\s*([^;{}:\n]+?)\s*:\s*([^;{}\n]+?)\s*;", m, re.M):
        lhs = text[t.start(2):t.end(2)].strip()
        if re.search(r"[-+*/%&|^<>!]$", lhs) or "?" in text[t.start(3):t.end(5)].replace(text[t.start(3):t.end(3)], "", 1):
            continue
        c_, a_, b_ = (text[t.start(g):t.end(g)].strip() for g in (3, 4, 5))
        new = text[:t.start(2)] + "if (%s) { %s = %s; } else { %s = %s; }" % (c_, lhs, a_, lhs, b_) + text[t.end():]
        out.append(("ternary", t.start(), new))
    return out


def bases(text):
    sites, n = sites_of(text), len(sites_of(text))
    out = []
    for label, pos, new in rewrites(text):
        if len(sites_of(new)) != n or unscored_text(new) != unscored_text(text):
            continue
        F = next((f for f in functions(new) if f[2] < pos < f[3]), None)
        if F is None or not any(F[2] < s[3] < F[3] for s in sites_of(new)):
            continue
        out.append((label, pos, (F[2], F[3]), new))
    out.sort(key=lambda b: b[1])
    return out[:BASES]


class T:
    name = "t43_rewrite_greedy"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not bases(text):
            return "no applicable statement rewrite"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0, runs, best = len(sites_of(text)), 0, None
        for label, pos, span, b in bases(text):
            if runs >= BUDGET:
                break
            runs += 1
            if not vf(b).get("exact"):
                continue
            t, used = greedy(b, pos, span, vf, BUDGET - runs)
            runs += used
            if len(sites_of(t)) < n0 and (best is None or len(sites_of(t)) < len(sites_of(best[1]))):
                best = ("rewrite:%s@%d" % (label, pos), t)
        if best:
            return best[1], {"label": best[0], "pins": "%d->%d" % (n0, len(sites_of(best[1])))}
        return None, {"refused": ["no exact rewrite base with fewer pins (%d runs)" % runs]}
