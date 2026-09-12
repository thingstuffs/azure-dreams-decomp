"""T41c: the goto-loop rewrite as a base, then a greedy walk over every pin in the function.

APPEARS     a do-while loop (t41's population) in a row with pins, inside or around the loop.
RESOLVES    hoisting out of a marked loop changes registers AROUND the loop too, so the pins a goto
            loop makes unnecessary need not sit in its body (the astra lane's 42-pin row freed pins
            outside it). t41 tries body erasures jointly with the rewrite; t41c starts from an exact
            base, either the goto form alone or the goto form with every body pin erased, and then
            erases each remaining pin of the function in turn (body first, then nearest outside),
            keeping every erasure that stays exact.
Budget: T41C_BUDGET scorer runs per row (default 60). A result must have fewer pins than the row.
RESULT      first sweep (2026-09-12, after t41): 38 rows exact, about 50 pin lines removed, mostly one
            pin per row. The largest of the goto-loop generators: many pins the rewrite frees sit
            outside the loop body.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t41_gotoloop import loops, rewrite
    from .t36_paramwidth import functions
except ImportError:
    from t41_gotoloop import loops, rewrite
    from t36_paramwidth import functions

BUDGET = int(os.environ.get("T41C_BUDGET", "60"))


def bases(text):
    """(loop index, label, head position, function span, [base texts]) per do-while loop."""
    sites, out = sites_of(text), []
    for k, lp in enumerate(loops(text)):
        F = next((f for f in functions(text) if f[2] < lp[1] < f[3]), None)
        if F is None or not any(F[2] < s[3] < F[3] for s in sites):
            continue
        label = "loop_%d" % k
        while re.search(r"\b%s\b" % label, text):
            label += "_"
        t1 = rewrite(text, lp, label)
        if len(sites_of(t1)) != len(sites) or unscored_text(t1) != unscored_text(text):
            continue
        inside = [i for i, s in enumerate(sites) if lp[1] < s[3] < lp[2]]
        bs = [t1]
        if inside:
            ss = sites_of(t1)
            bs.append(erase_many(t1, [ss[i] for i in inside], clean_notes=True))
        out.append((k, label, lp[1], (F[2], F[3]), bs))
    return out


def greedy(base, head, span, vf, budget):
    """Erase pins of the function one at a time from an exact base; returns (text, runs used)."""
    cur, runs = base, 0
    while runs < budget:
        ss = sites_of(cur)
        fn = [s for s in ss if span[0] < s[3] < span[1] + (len(cur) - len(base))]
        fn.sort(key=lambda s: abs(s[3] - head))
        progress = False
        for s in fn:
            if runs >= budget:
                break
            t = erase_many(cur, [s], clean_notes=True)
            if unscored_text(t) != unscored_text(base):
                continue
            runs += 1
            if vf(t).get("exact"):
                cur, progress = t, True
                break
        if not progress:
            break
    return cur, runs


class T:
    name = "t41c_gotoloop_greedy"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not bases(text):
            return "no do-while loop in a function with pins"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0, runs, best = len(sites_of(text)), 0, None
        for k, label, head, span, bs in bases(text):
            for b in bs:
                if runs >= BUDGET:
                    break
                runs += 1
                if not vf(b).get("exact"):
                    continue
                t, used = greedy(b, head, span, vf, BUDGET - runs)
                runs += used
                if len(sites_of(t)) < n0 and (best is None or len(sites_of(t)) < len(sites_of(best[1]))):
                    best = ("gotogreedy:%d" % k, t)
                break
        if best:
            return best[1], {"label": best[0], "pins": "%d->%d" % (n0, len(sites_of(best[1])))}
        return None, {"refused": ["no exact goto base with fewer pins (%d runs)" % runs]}
