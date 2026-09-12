"""T41: a bottom-tested loop written as a backward goto, with the pins inside it erased.

APPEARS     `do { ... } while (COND);` (COND not a constant 0) with pins in its body.
RESOLVES    gcc 2.x runs loop.c (invariant hoisting, strength reduction) only on loops the front end
            marked with NOTE_INSN_LOOP_BEG/END (for, while, do). A backward goto loop has the same
            blocks and no loop notes, so nothing is hoisted out of it. Astra lane,
            dungeon/func_809A38E4 (2026-09-12): the arc loop as `arc_segment: ... if (cond) goto
            arc_segment;` made 38 of 42 pins unnecessary (TOTAL 2, from an unrelated one-word
            ordering). The pins had compensated for the constant 0xfb hoisted out of the marked loop.
RESULT      first sweep (2026-09-12): 236 do-while loops with pins inside (171 rows, 744 pins), 64 more
            skipped for break/continue; 15 rows exact, 9 with every body pin erased and 6 with one.
Candidates: per loop, the goto form with every pin in its body erased, then with each single body
pin erased (nearest to the loop head first). Loops whose body has break/continue are skipped, since
the rewrite would change their meaning. The byte verifier decides.
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


def loops(text):
    """(do_start, open_brace, close_brace, while_end, COND) for each do-while with a real condition."""
    m, out = mask_comments(text), []
    for d in re.finditer(r"\bdo\s*\{", m):
        o = d.end() - 1; depth, i = 0, o
        while i < len(m):
            depth += (m[i] == "{") - (m[i] == "}")
            if depth == 0:
                break
            i += 1
        w = re.match(r"\s*while\s*\(", m[i + 1:])
        if not w:
            continue
        a = i + 1 + w.end(); depth, j = 1, a
        while j < len(m) and depth:
            depth += (m[j] == "(") - (m[j] == ")")
            j += 1
        semi = re.match(r"\s*;", m[j:])
        cond = text[a:j - 1]
        if not semi or re.fullmatch(r"\s*0\s*", cond) or re.search(r"\b(break|continue)\b", m[o:i]):
            continue
        out.append((d.start(), o, i, j + semi.end(), cond.strip()))
    return out


def rewrite(text, lp, label):
    ds, o, c, we, cond = lp
    return text[:ds] + label + ": {" + text[o + 1:c] + "} if (" + cond + ") goto " + label + ";" + text[we:]


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
                seen.add(t); out.append(("gotoloop:%d:%s" % (k, tag), t))
        if len(out) >= MAX_CANDS:
            break
    return out[:MAX_CANDS]


class T:
    name = "t41_gotoloop"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        sites = sites_of(text)
        if not any(any(lp[1] < s[3] < lp[2] for s in sites) for lp in loops(text)):
            return "no do-while loop with pins inside"
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
