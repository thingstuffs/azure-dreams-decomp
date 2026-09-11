"""T20: a fence traded back for the C it stands for.

APPEARS     a row carrying a zero-byte barrier that census.py counts like a pin - `do { ... } while
            (0)`, `while (0) { }`, `for (;0;)`: 505 rows / 708 fences on 2026-09-11 (the 16 in
            NON_MATCHING arms no byte gate compiles are left alone here).
RESOLVES    docs/PIN_PATTERNS.md section 9: about a third of the sampled fences stand for a natural
            source shape m2c lowered into something else, and the fence only pins what that shape
            produces.  `natural.py` carries one generator per shape the study closed by hand (plus
            agy's base-page symbol); the nine rows landed by hand under this name are its test set -
            the generators rebuild all nine without a fence.
SEARCH      per fence, in text order: take it off (`unwrap`; a fence that is dead alone lands as
            that), then the natural shapes over the WHOLE function, nearest the fence first - the
            shape usually lives next to the fence, not in it (the if/else before a fenced call, the
            copy a fenced statement reads) - greedily for T20_ROUNDS rounds within T20_FENCE_BUDGET
            verifies; then with one pin near the fence erased too, as agy's group lanes did.  A last
            pass tries the shapes on the text itself, for a pin a shape deletes on its own (a copy's
            `register ... ASM_REG` declaration, an `ASM_KEEP` on a page base).
ACCEPTANCE  pins never grow and pins + fences strictly fall: census.py counts a fence like a pin, and
            nothing here may trade one for the other.  Every step label names a shape, never a
            fence (t18's `_is_fence` keys on the label).
RESULT      2026-09-11, every fenced row (503 rows, 692 scored fences): 122 rows, 151 fences + 21
            pins off, nothing added (net -172), 38 rows left with neither.  123 of the 151 fences
            were DEAD - exact with the fence simply taken off, 109 of them in rows no t15/t18 fence
            ever touched (agent-lane fences nothing had re-tested).  The shapes took the rest:
            dropcopy 21, dup_after_if 7, narrow 6, armstore 4, basesym 4, one pin erased with its
            fence.  Then the pinned rows with no fence (585 where a shape deletes a pin, + 10 fenced
            rows re-run after the `_declare` fix): 83 rows, 121 pins off - dropcopy 67, basesym 29,
            ptr2index 3.  Session: 205 rows, net -293, 45 rows free of pins and fences.  Run it after
            every lane or campaign landing, the way t2 re-tests pins: nothing else re-tests a fence.
"""
import os, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import sha_text
from pin_census import sites_of
from pin_sites import erase_many
from census import _dowhile0

try:
    from . import natural as N
    from .t15_shapes import dowhile2for_candidates, dup_after_if_candidates, narrow_candidates
except ImportError:                       # pragma: no cover - direct import
    import natural as N
    from t15_shapes import dowhile2for_candidates, dup_after_if_candidates, narrow_candidates

BUDGET = int(os.environ.get("T20_BUDGET", "80"))              # verify runs per row
FENCE_BUDGET = int(os.environ.get("T20_FENCE_BUDGET", "24"))  # menu verifies per fence
ROUNDS = int(os.environ.get("T20_ROUNDS", "2"))               # greedy rounds per fence
NEAR = int(os.environ.get("T20_NEAR", "6"))                   # a pin this many lines from the fence may fall with it
PIN_PASS = os.environ.get("T20_PIN_PASS", "1") == "1"         # the shapes on the text itself, for pins
NATURAL = ("dropcopy", "armstore", "ret2break", "ptr2index", "postinc", "gotoloop", "basesym")


def debt(text):
    """(live pins, fences) - the two things census.py counts as scaffolding."""
    return len(sites_of(text)), _dowhile0(text)


def _edit_line(a, b):
    """The 1-based line in `a` of the first character where `b` differs from it."""
    lo, hi = 0, min(len(a), len(b))
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if a[:mid] == b[:mid]:
            lo = mid
        else:
            hi = mid - 1
    return a.count("\n", 0, lo) + 1


def _tier(label):
    head = label.split(":")[0]
    return 0 if head in NATURAL else 2 if head == "narrow" else 1


class T:
    name = "t20_fencefree"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if N.fences(text):
            return None
        if PIN_PASS and sites_of(text):
            return None
        return "no fence and no pin"

    @staticmethod
    def _menu(text, slus):
        """The natural shapes, then t15's two other real shapes, then `narrow` - never a fence."""
        return (N.candidates(text, basesym=not slus) + dowhile2for_candidates(text)
                + dup_after_if_candidates(text) + narrow_candidates(text))

    @staticmethod
    def apply_verified(text, row, census, verify_fn):
        slus = row.get("kind") == "slus"
        p_in, f_in = debt(text)
        cur, steps, log = text, [], []
        tried = 0

        def attempt(cand):
            nonlocal tried
            tried += 1
            return verify_fn(cand)

        def gains(cand):
            p, f = debt(cand)
            pc, fc = debt(cur)
            return p <= pc and p + f < pc + fc

        def ranked(here, line, seen):
            cands = [(lab, c) for lab, c in T._menu(here, slus) if sha_text(c) not in seen]
            cands.sort(key=lambda lc: (_tier(lc[0]), abs(_edit_line(here, lc[1]) - line)))
            return cands

        def search(base, line, total):
            """A shape that makes the unwrapped text exact: (label, text) or None, and a log record."""
            here, here_total, climb, gb, seen, improving = base, total, [], 0, {sha_text(base)}, []
            for _ in range(ROUNDS):
                best = None
                for lab, c in ranked(here, line, seen):
                    if gb >= FENCE_BUDGET or tried >= BUDGET:
                        break
                    seen.add(sha_text(c))
                    gb += 1
                    w = attempt(c)
                    if w.get("exact") and gains(c):
                        return ("+".join(climb + [lab]), c), {"menu": gb, "best": 0}
                    wt = w.get("total")
                    if wt is not None and (here_total is None or wt < here_total):
                        improving.append((wt, "+".join(climb + [lab]), c))
                        if best is None or wt < best[0]:
                            best = (wt, lab, c)
                if best is None or gb >= FENCE_BUDGET or tried >= BUDGET:
                    break
                here_total, here = best[0], best[2]
                climb.append(best[1])
            # one pin near the fence falls with it: on the unwrapped text, and on the two
            # candidates that came closest
            starts = [(None, "", base)] + sorted(improving, key=lambda x: x[0])[:2]
            for _, lab0, start in starts:
                live = sites_of(start)
                ln0 = line if start is base else _edit_line(base, start)
                near = sorted((s for s in live if abs(s[5] - ln0) <= NEAR), key=lambda s: abs(s[5] - ln0))[:3]
                for s in near:
                    if gb >= 2 * FENCE_BUDGET or tried >= BUDGET:
                        break
                    c = erase_many(start, [s], clean_notes=True)
                    if sha_text(c) in seen:
                        continue
                    seen.add(sha_text(c))
                    gb += 1
                    if attempt(c).get("exact") and gains(c):
                        return (((lab0 + "+") if lab0 else "") + "erase:" + s[1], c), {"menu": gb, "best": 0}
                    if start is not base:
                        continue
                    for lab, c2 in ranked(c, line, seen)[:4]:
                        if gb >= 2 * FENCE_BUDGET or tried >= BUDGET:
                            break
                        seen.add(sha_text(c2))
                        gb += 1
                        if attempt(c2).get("exact") and gains(c2):
                            return ("erase:%s+%s" % (s[1], lab), c2), {"menu": gb, "best": 0}
            return None, {"menu": gb, "best": here_total,
                          "climb": "+".join(climb) or None}

        k = 0
        while tried < BUDGET:
            fl = N.fences(cur)
            if k >= len(fl):
                break
            f = fl[k]
            base = N.unwrap(cur, f)
            if base == cur:
                k += 1
                continue
            v = attempt(base)
            if v.get("exact") and gains(base):
                cur = base
                steps.append("unwrap@%d" % f[4])
                continue
            won, rec = search(base, f[4], v.get("total"))
            log.append(dict(rec, fence=f[4], unwrap=v.get("total")))
            if won:
                cur = won[1]
                steps.append("@%d:%s" % (f[4], won[0]))
                continue
            k += 1
        # the shapes on the text itself, where the shape deletes a pin on its own
        for _ in range(ROUNDS if PIN_PASS else 0):
            hit = None
            pc, fc = debt(cur)
            for lab, c in sorted(T._menu(cur, slus), key=lambda lc: _tier(lc[0])):
                if tried >= BUDGET:
                    break
                p, f = debt(c)
                if not (p < pc and f <= fc):
                    continue
                if attempt(c).get("exact"):
                    hit = (lab, c)
                    break
            if not hit:
                break
            cur = hit[1]
            steps.append("pin:" + hit[0])
        p_out, f_out = debt(cur)
        info = {"tried": tried, "pins_in": p_in, "pins_out": p_out, "fences_in": f_in, "fences_out": f_out,
                "fences": log[:12]}
        if not steps:
            return None, info
        return cur, dict(info, step=" ".join(steps))
