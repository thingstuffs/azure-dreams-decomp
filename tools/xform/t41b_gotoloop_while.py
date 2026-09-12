"""T41b: a top-tested loop (while/for) written as the rotated backward goto, with its pins erased.

APPEARS     `while (COND) { ... }` or `for (INIT; COND; STEP) { ... }` with pins in the body.
RESOLVES    t41's mechanism for top-tested loops. gcc 2.x runs loop.c only on loops marked with loop
            notes, and rotates a marked while/for into a guarded bottom-tested loop. The goto spelling
            `INIT; if (COND) { top: { BODY } STEP; if (COND) goto top; }` gives the rotated layout
            without the notes, so nothing is hoisted out of it. The number of COND evaluations is the
            same, so the meaning is unchanged.
RESULT      first sweep (2026-09-12): only 27 while/for loops hold pins (11 while, 16 for, 65 pins),
            because m2c writes most loops as do-while; t41 covers those. 1 row exact.
Candidates: as t41 (every body pin erased, then single pins nearest the head). Skipped: loops whose
body has break/continue, an unbraced body, `for (;;)`, and the `while` of a do-while.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

MAX_CANDS = 30
SINGLES = 8


def _close(m, i, op, cl):
    """Index just past the bracket matching m[i] == op."""
    depth = 0
    while i < len(m):
        depth += (m[i] == op) - (m[i] == cl)
        i += 1
        if depth == 0:
            return i
    return None


def loops(text):
    """(start, body_open, body_close, kind, init, cond, step) for braced while/for loops."""
    m, out = mask_comments(text), []
    for k in re.finditer(r"\b(while|for)\s*\(", m):
        if k.group(1) == "while" and re.search(r"\}\s*$", m[:k.start()]):
            continue                                              # the while of a do-while
        p = k.end() - 1
        pe = _close(m, p, "(", ")")
        if pe is None:
            continue
        b = re.match(r"\s*\{", m[pe:])
        if not b:
            continue
        o = pe + b.end() - 1
        c = _close(m, o, "{", "}")
        if c is None or re.search(r"\b(break|continue)\b", m[o:c]):
            continue
        head = text[p + 1:pe - 1]
        if k.group(1) == "for":
            parts, depth, cur = [], 0, ""
            for ch in head:
                depth += (ch == "(") - (ch == ")")
                if ch == ";" and depth == 0:
                    parts.append(cur); cur = ""
                else:
                    cur += ch
            parts.append(cur)
            if len(parts) != 3 or not parts[1].strip():
                continue
            init, cond, step = (x.strip() for x in parts)
        else:
            init, cond, step = "", head.strip(), ""
        out.append((k.start(), o, c - 1, k.group(1), init, cond, step))
    return out


def rewrite(text, lp, label):
    s, o, c, kind, init, cond, step = lp
    pre = (init + "; " if init else "") + "if (" + cond + ") { " + label + ": {"
    post = "} " + (step + "; " if step else "") + "if (" + cond + ") goto " + label + "; }"
    return text[:s] + pre + text[o + 1:c] + post + text[c + 1:]


def candidates(text):
    out, seen, sites = [], set(), sites_of(text)
    for k, lp in enumerate(loops(text)):
        inside = [i for i, s in enumerate(sites) if lp[1] < s[3] < lp[2]]
        if not inside:
            continue
        label = "loop_%d" % k
        while re.search(r"\b%s\b" % label, text):
            label += "_"
        t1 = rewrite(text, lp, label)
        ss = sites_of(t1)
        if len(ss) != len(sites):
            continue
        order = sorted(inside, key=lambda i: sites[i][3] - lp[1])
        for chosen, tag in [(inside, "all")] + [([i], "one%d" % i) for i in order[:SINGLES]]:
            t = erase_many(t1, [ss[i] for i in chosen], clean_notes=True)
            if t not in seen and unscored_text(t) == unscored_text(text):
                seen.add(t); out.append(("gotowhile:%d:%s:%s" % (k, lp[3], tag), t))
        if len(out) >= MAX_CANDS:
            break
    return out[:MAX_CANDS]


class T:
    name = "t41b_gotoloop_while"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        sites = sites_of(text)
        if not sites:
            return "no pin sites"
        if not any(any(lp[1] < s[3] < lp[2] for s in sites) for lp in loops(text)):
            return "no while/for loop with pins inside"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
