"""T26: the allocation levers on every pin, each candidate screened free before it is scored.

A native lane on the fake-dependency evidence (2026-09-12, work/native_lane/fakedep/REPORT.md) found
that a pin whose only byte-exact removal was a fake dependency is holding a register-ALLOCATION
decision, and that natural C reproduces it by moving a value between local-alloc and global-alloc
(HOST, often of a variable other than the pinned one), keeping a temporary local (UNHOST), or
reordering two declarations (DECL ORDER).  `natural.ALLOC_LEVERS` generates them (gen/RESULT.md:
all six of the lane's closes reproduced; a 20-row dry run found 6 more pins on 5 rows).

Per live pin, in source order: erase it; try the erased text itself (a dead pin) and every
ALLOC_LEVERS candidate on it.  Each candidate is compiled by cc1 alone and its assembly compared with
the row's current (byte-exact) text's (tools/xform/screen.py); only an identical listing is scored.
The first exact one is kept and the walk continues on it (the next pin now sits at the same index).

Budgets per row: T26_BUDGET scorer runs (default 60), T26_SCREEN cc1 compiles (default 800).
"""
import os, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import sha_text
from pin_census import sites_of
from pin_sites import erase_many
import natural as N
from screen import compile_s, sdiff

BUDGET = int(os.environ.get("T26_BUDGET", "60"))
SCREEN = int(os.environ.get("T26_SCREEN", "800"))


class T:
    name = "t26_alloc"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        return None if sites_of(text) else "no pin sites"

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        ref = compile_s(row, text)
        p_in = len(sites_of(text))
        if ref is None:
            return None, {"pins_in": p_in, "pins_out": p_in, "err": "the current text does not build under the screen"}
        cur, steps, i = text, [], 0
        tried = screened = 0
        sites_tried = []
        while tried < BUDGET and screened < SCREEN:
            live = sites_of(cur)
            if i >= len(live):
                break
            s = live[i]
            base = erase_many(cur, [s], clean_notes=True)
            won, seen, near = None, set(), None
            cands = [("erase", base)]
            for g in N.ALLOC_LEVERS:
                try:
                    cands += g(base)
                except Exception:                     # a generator bug must not cost the row
                    pass
            for lab, c in cands:
                h = sha_text(c)
                if h in seen or len(sites_of(c)) >= len(live):
                    continue
                seen.add(h)
                if screened >= SCREEN or tried >= BUDGET:
                    break
                screened += 1
                d = sdiff(ref, compile_s(row, c))
                if d is None:
                    continue
                if near is None or d < near:
                    near = d
                if d:
                    continue
                tried += 1
                if verify_fn(c).get("exact"):
                    won = (lab, c)
                    break
            sites_tried.append({"site": i, "pin": s[1], "cands": len(seen), "best_sdiff": near,
                                "won": won[0] if won else None})
            if won:
                cur = won[1]
                steps.append("%s:%s" % (s[1], won[0]))
            else:
                i += 1
        info = {"tried": tried, "screened": screened, "pins_in": p_in, "pins_out": len(sites_of(cur)),
                "sites": sites_tried[:24]}
        if not steps:
            return None, info
        return cur, dict(info, step=" ".join(steps))
