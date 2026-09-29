"""T122: a backward-goto loop written as the structured loop it was (readability; pins untouched).

APPEARS     m2c renders gcc's rotated loops as labels and backward gotos:
              (a) `if (C) { L: BODY if (C) goto L; }`                 - gcc's own rotation of `while (C) BODY`
              (b) `if (C) { L: if (C2) { BODY if (C) goto L; } }`     - `while (C && C2) BODY`
              (c) `L: BODY if (C) goto L;`                            - `do BODY while (C);`
            (`if (C) goto L;` may also be `if (C) { goto L; }`.)  Round 80: 964 pin-free rows still hold
            5,581 plain gotos; town/func_8032EEA8's (b) loop is byte-exact both as `while (a && b)` and as
            `while (a) { if (!b) break; ... }` - gcc 2.x rotates the structured loop into the same blocks.
RESOLVES    the structured loop, byte-exact.  A loop whose BODY holds `break`/`continue` is skipped (the new
            loop would capture them), as is a label any other goto targets.  Loop notes can change loop.c's
            decisions, so every candidate is verified: all loops at once first, then one at a time,
            greedily keeping each loop that stays exact.  Pins are never touched: an applied row has the
            same pins and fewer gotos (land_lanes.sh / kitlib.admissible accept that since round 80).
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

MAX_VERIFY = int(os.environ.get("T122_MAX", "16"))
LABEL = re.compile(r"^[ \t]*([A-Za-z_]\w*)[ \t]*:[ \t]*(?:;[ \t]*)?\n", re.M)
KEYWORDS = {"default", "case"}


def mask(text):
    """Comments, string and char literals blanked (same length) so braces/parens inside them never count."""
    m = mask_comments(text)
    m = re.sub(r"//[^\n]*", lambda x: " " * len(x.group(0)), m)
    return re.sub(r'"(?:[^"\\\n]|\\.)*"|\'(?:[^\'\\\n]|\\.)*\'', lambda x: '"' + " " * (len(x.group(0)) - 2) + '"', m)


def match_close(m, i):
    """Index of the bracket closing the one at m[i] ('(' or '{')."""
    o = m[i]; c = {"(": ")", "{": "}"}[o]; d = 0
    for j in range(i, len(m)):
        if m[j] == o: d += 1
        elif m[j] == c:
            d -= 1
            if d == 0: return j
    return -1


def enclosing_open(m, i):
    """Index of the innermost unmatched '{' before i (the block that contains position i)."""
    d = 0
    for j in range(i - 1, -1, -1):
        if m[j] == "}": d += 1
        elif m[j] == "{":
            if d == 0: return j
            d -= 1
    return -1


def cond_goto(m, p, label):
    """At p (whitespace allowed): `if (C) goto L;` or `if (C) { goto L; }` -> (C span, end) else None."""
    r = re.compile(r"[ \t\n]*if[ \t]*\(").match(m, p)
    if not r: return None
    po = r.end() - 1; pc = match_close(m, po)
    if pc < 0: return None
    g = re.compile(r"[ \t\n]*(?:\{[ \t\n]*goto[ \t]+%s[ \t]*;[ \t\n]*\}|goto[ \t]+%s[ \t]*;)[ \t]*\n?" % (label, label)).match(m, pc + 1)
    if not g: return None
    return (po + 1, pc), g.end()


def if_head(m, p):
    """At p (whitespace allowed): `if (C) {` -> (C span, brace index, close brace index) else None."""
    r = re.compile(r"[ \t\n]*if[ \t]*\(").match(m, p)
    if not r: return None
    po = r.end() - 1; pc = match_close(m, po)
    b = re.compile(r"[ \t\n]*\{").match(m, pc + 1) if pc > 0 else None
    if not b: return None
    bo = b.end() - 1; bc = match_close(m, bo)
    if bc < 0: return None
    return (po + 1, pc), bo, bc


def norm(s):
    return re.sub(r"\s+", " ", s).strip()


def loose_flow(m_body):
    """True when BODY has a break/continue not inside a loop or switch of its own (a new loop would capture it)."""
    for k in re.finditer(r"\b(break|continue)\b", m_body):
        # inside a nested loop/switch of BODY?  find the innermost enclosing construct keyword by brace scan
        pre = m_body[:k.start()]; d = 0; inner = False
        for j in range(len(pre) - 1, -1, -1):
            if pre[j] == "}": d += 1
            elif pre[j] == "{":
                if d == 0:
                    head = pre[max(0, j - 200):j]
                    h = re.search(r"\b(for|while|do|switch|if|else)\b[^{};]*$", head)
                    if h and h.group(1) in ("for", "while", "do", "switch"):
                        inner = True; break
                    if h and h.group(1) in ("if", "else"):
                        continue
                    break
                d -= 1
        if not inner:
            return True
    return False


def reindent(body, indent):
    lines = body.strip("\n").split("\n")
    live = [l for l in lines if l.strip()]
    if not live: return ""
    cut = min(len(l) - len(l.lstrip(" \t")) for l in live)
    return "\n".join((indent + l[cut:]) if l.strip() else "" for l in lines).rstrip() + "\n"


def line_indent(text, i):
    s = text.rfind("\n", 0, i) + 1
    return re.match(r"[ \t]*", text[s:]).group(0)


def loops(text):
    """[(start, end, [replacement, ...])] for every loop shape found; replacements best-first."""
    m = mask(text); out = []
    for lm in LABEL.finditer(m):
        L = lm.group(1)
        if L in KEYWORDS: continue
        refs = [g.start() for g in re.finditer(r"\bgoto[ \t]+%s[ \t]*;" % re.escape(L), m)]
        if len(refs) != 1 or refs[0] < lm.end(): continue
        bo = enclosing_open(m, lm.start())
        if bo < 0: continue
        bc = match_close(m, bo)
        if bc < refs[0]: continue
        # (b) first statement after the label is `if (C2) {` holding the back edge as its last statement
        ih = if_head(m, lm.end())
        if ih and ih[1] < refs[0] < ih[2]:
            (c2a, c2b), ibo, ibc = ih
            gstart = last_if_line(m, ibo, refs[0])
            cg = cond_goto(m, gstart, re.escape(L)) if gstart > ibo else None
            if cg and m[cg[1]:ibc].strip() == "" and not re.match(r"\s*else\b", m[ibc + 1:]):
                (ca, cb), gend = cg
                body = text[ibo + 1:gstart]
                if not loose_flow(m[ibo + 1:gstart]):
                    C, C2 = text[ca:cb], text[c2a:c2b]
                    outer = outer_if(m, text, bo, bc, lm.start(), ibc, C)
                    if outer:
                        s, e, ind = outer
                        par = lambda x: "(%s)" % x if re.search(r"\|\||\?", x) else x
                        rb = reindent(body, ind + "    ")
                        out.append((s, e, [
                            "%swhile (%s && %s) {\n%s%s}\n" % (ind, par(C), par(C2), rb, ind),
                            "%swhile (%s) {\n%s    if (!(%s)) {\n%s        break;\n%s    }\n%s%s}\n"
                            % (ind, C, ind, C2, ind, ind, rb, ind)]))
                        continue
        # (a)/(c) the back edge at the label's own level
        d = 0; ok = True
        for ch in m[lm.end():refs[0]]:
            if ch == "{": d += 1
            elif ch == "}":
                d -= 1
                if d < 0: ok = False; break
        if not ok or d != 1 and d != 0: continue
        gstart = last_if_line(m, lm.end(), refs[0])
        cg = cond_goto(m, gstart, re.escape(L)) if gstart >= lm.end() else None
        if not cg: continue
        (ca, cb), gend = cg
        body_m = m[lm.end():gstart]
        if loose_flow(body_m) or not body_m.strip(): continue
        body = text[lm.end():gstart]; C = text[ca:cb]
        outer = outer_if(m, text, bo, bc, lm.start(), gend - 1, C)
        if outer:
            s, e, ind = outer
            out.append((s, e, ["%swhile (%s) {\n%s%s}\n" % (ind, C, reindent(body, ind + "    "), ind),
                               "%sif (%s) {\n%s    do {\n%s%s    } while (%s);\n%s}\n"
                               % (ind, C, ind, reindent(body, ind + "        "), ind, C, ind)]))
            continue
        ind = line_indent(text, gstart)
        out.append((lm.start(), gend, ["%sdo {\n%s%s} while (%s);\n" % (ind, reindent(body, ind + "    "), ind, C)]))
    return out


def last_if_line(m, lo, hi):
    """Start of the line holding the last `if (` between lo and hi (-1 when none)."""
    k = None
    for k in re.finditer(r"\bif[ \t]*\(", m[lo:hi]): pass
    return -1 if k is None else m.rfind("\n", 0, lo + k.start()) + 1


def outer_if(m, text, bo, bc, lstart, lend, C):
    """When block bo..bc is `if (C) { <label ...loop... > }` holding nothing but the loop, with the SAME
    condition C and no else: (start, end, indent) of the whole if statement; else None."""
    if m[bo + 1:lstart].strip() or m[lend + 1:bc].strip(): return None
    head = m[:bo].rstrip()
    if not head.endswith(")"): return None
    pc = len(head) - 1; d = 0
    for j in range(pc, -1, -1):
        if m[j] == ")": d += 1
        elif m[j] == "(":
            d -= 1
            if d == 0: po = j; break
    else:
        return None
    k = re.search(r"\bif[ \t]*$", m[:po])
    if not k or re.search(r"\belse[ \t\n]*$", m[:k.start()]): return None
    if norm(text[po + 1:pc]) != norm(C): return None
    if re.match(r"\s*else\b", m[bc + 1:]): return None
    s = m.rfind("\n", 0, k.start()) + 1
    e = bc + 1
    if m[e:e + 1] == "\n": e += 1
    return s, e, line_indent(text, k.start())


def rewrite(text, which, alt=None):
    """Apply loops number `which` (indices into loops(text)), last first so offsets hold; alt[i] picks a form."""
    ls = loops(text); t = text
    for i in sorted(which, key=lambda i: -ls[i][0]):
        s, e, reps = ls[i]
        t = t[:s] + reps[(alt or {}).get(i, 0)] + t[e:]
    return t


def gotos(text):
    return len(re.findall(r"\bgoto\s+\w+\s*;", mask(text)))


class T:
    name = "t122_gotowhile"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if loops(text) else "no backward-goto loop shape"

    @staticmethod
    def apply_verified(text, row, census, vf):
        ls = loops(text)
        if not ls:
            return None, {"refused": ["no backward-goto loop shape"]}
        n0, g0 = len(sites_of(text)), gotos(text); budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == text or len(sites_of(t)) != n0 or gotos(t) >= g0: return False
            if budget[0] <= 0: return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        # overlapping spans (nested shapes) cannot be applied together: keep the outermost-first non-overlapping set
        idx = []
        for i, (s, e, _) in sorted(enumerate(ls), key=lambda x: (x[1][0], -x[1][1])):
            if all(e <= ls[j][0] or s >= ls[j][1] for j in idx): idx.append(i)
        allt = rewrite(text, idx)
        if len(idx) > 1 and ok(allt):
            return allt, {"loops": len(idx), "verifies": len(tried)}
        keep, alt = [], {}
        for i in idx:
            for a in range(len(ls[i][2])):
                t = rewrite(text, keep + [i], {**alt, i: a})
                if ok(t):
                    keep.append(i); alt[i] = a; break
        if keep:
            return rewrite(text, keep, alt), {"loops": len(keep), "of": len(idx), "verifies": len(tried)}
        return None, {"refused": ["no loop rewrite exact (%d verifies)" % len(tried)]}
