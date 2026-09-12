"""T27: a beam search over the whole shape menu for every pin group, steered by the free screen.

t18 scores every menu candidate with the scorer (~1.3 s a run), so it affords 10-60 candidates a
group and climbs greedily.  tools/xform/screen.py compiles a candidate with cc1 alone - 0.012 s on
average over a 25-row sample, 2026-09-12 - and counts the lines its assembly differs from the row's
byte-exact text's.  That count steers the search here, and only a candidate whose listing is
identical is scored.  So each group gets a beam: its erasure, then T27_DEPTH rounds, each expanding
the T27_BEAM lowest-diff texts with t15's whole menu (the natural shapes, ALLOC_LEVERS and t15's
own; run with T15_NOFENCE=1 T15_WIDE=1) - the "every combination of lever on one or more pins" job,
up to DEPTH stacked shapes on one erasure.  Menu mean 62 candidates (median 47, max 238).

Groups: the per-site census's pin groups where it is current for the text (t18's linkage), then
every pin alone, then every pair of pins within T27_PAIR lines.  A group is searched only when its
erased listing is within T27_BAND changed lines.

Accept: exact, fewer pins, no more fences (census counts a fence like a pin).  After a landing the
walk restarts on the new text.  Budgets per row: T27_BUDGET scorer runs, T27_SCREEN compiles (and
T27_GROUP_SCREEN per group).
"""
import os, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
for p in (ROOT / "tools", Path(__file__).resolve().parent):
    if str(p) not in sys.path:
        sys.path.insert(0, str(p))
from common import sha_text
from pin_census import sites_of, asm_blocker
from pin_sites import pin_groups, erase_many
import natural as N
from screen import compile_s, sdiff

try:
    from .t15_shapes import T as T15
except ImportError:                       # pragma: no cover - direct import
    from t15_shapes import T as T15

DEPTH = int(os.environ.get("T27_DEPTH", "3"))
BEAM = int(os.environ.get("T27_BEAM", "4"))
BAND = int(os.environ.get("T27_BAND", "30"))
PAIR = int(os.environ.get("T27_PAIR", "4"))
BUDGET = int(os.environ.get("T27_BUDGET", "40"))
SCREEN = int(os.environ.get("T27_SCREEN", "6000"))
GROUP_SCREEN = int(os.environ.get("T27_GROUP_SCREEN", "800"))


def debt(text):
    return len(sites_of(text)), len(N.fences(text))


def groups(text, row):
    """Census groups (cheapest first) when the census is current for this text, then singles, then
    near pairs - each once."""
    s = sites_of(text)
    n = len(s)
    out, seen = [], set()
    cen = pin_groups(row["id"], sha_text(text), n) or []
    cand = [tuple(g["sites"]) for g in sorted(cen, key=lambda g: (g["cost"] is None, g["cost"] or 0))]
    cand += [(i,) for i in range(n)]
    cand += [(i, j) for i in range(n) for j in range(i + 1, n) if abs(s[i][5] - s[j][5]) <= PAIR]
    for g in cand:
        if g not in seen and all(i < n for i in g):
            seen.add(g)
            out.append(g)
    return out


class T:
    name = "t27_beam"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        return asm_blocker(text)

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        slus = row.get("kind") == "slus"
        ref = compile_s(row, text)
        p_in, f_in = debt(text)
        if ref is None:
            return None, {"pins_in": p_in, "pins_out": p_in, "err": "the current text does not build under the screen"}
        cur, steps, log = text, [], []
        cnt = {"tried": 0, "screened": 0}

        def menu(t):
            try:
                return T15._menu(t, slus)
            except Exception:                 # a generator bug must not cost the row
                return []

        def search(grp):
            """The group's beam: (label, text) of an exact candidate, or None; and a log record."""
            live = sites_of(cur)
            pc, fc = debt(cur)
            base = erase_many(cur, [live[i] for i in grp], clean_notes=True)
            cnt["screened"] += 1
            d0 = sdiff(ref, compile_s(row, base))
            rec = {"group": list(grp), "d0": d0}
            if d0 is None or d0 > BAND:
                return None, rec

            def good(c):
                p, f = debt(c)
                return p < pc and f <= fc

            if d0 == 0 and good(base):
                cnt["tried"] += 1
                if verify_fn(base).get("exact"):
                    return ("erase", base), dict(rec, best=0)
            seen, gs, best = {sha_text(base)}, 1, d0
            frontier = [(d0, base, "erase")]
            for _ in range(DEPTH):
                children = []
                for _d, t, lab in frontier:
                    for l, c in menu(t):
                        h = sha_text(c)
                        if h in seen:
                            continue
                        seen.add(h)
                        if gs >= GROUP_SCREEN or cnt["screened"] >= SCREEN or cnt["tried"] >= BUDGET:
                            break
                        gs += 1
                        cnt["screened"] += 1
                        dc = sdiff(ref, compile_s(row, c))
                        if dc is None:
                            continue
                        lab2 = lab + "+" + l
                        if dc == 0 and good(c):
                            cnt["tried"] += 1
                            if verify_fn(c).get("exact"):
                                return (lab2, c), dict(rec, best=0, screened=gs)
                        children.append((dc, c, lab2))
                if not children:
                    break
                children.sort(key=lambda x: x[0])
                frontier = children[:BEAM]
                best = min(best, frontier[0][0])
            return None, dict(rec, best=best, screened=gs)

        restart = True
        while restart and cnt["tried"] < BUDGET and cnt["screened"] < SCREEN:
            restart = False
            for grp in groups(cur, row):
                if cnt["tried"] >= BUDGET or cnt["screened"] >= SCREEN:
                    break
                won, rec = search(grp)
                log.append(rec)
                if won:
                    cur = won[1]
                    steps.append("g%s:%s" % ("+".join(map(str, grp)), won[0]))
                    restart = True
                    break
        p_out, f_out = debt(cur)
        info = {"tried": cnt["tried"], "screened": cnt["screened"], "pins_in": p_in, "pins_out": p_out,
                "fences_in": f_in, "fences_out": f_out,
                "groups": [r for r in log if r.get("d0") is not None and r["d0"] <= BAND][:24]}
        if not steps:
            return None, info
        return cur, dict(info, step=" ".join(steps))
