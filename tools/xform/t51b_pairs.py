"""T51b: t51_sched_order seeded from PAIRS of erased pins instead of single ones.

APPEARS     a row with two or more live pins, whose single erasures t51 has already searched.
RESOLVES    joint erasures paid where single ones did not (pin_search's erasure groups, round 14; many
            fence-lane wins removed two or more pins at once), but t51 erases one pin per base, so a
            rewrite that needs two pins gone together is never tried.
Bases: every pair of live sites on rows with at most T51B_MAXPINS (default 8) pins; on larger rows the
pairs whose lines lie within T51B_SPAN (default 12) of each other, nearest first, at most 40. The four
nearest pair erasures by assembly distance seed t51's menu (statement move, lifetime split, producer
fusion, commutation, register hint) at t51's budgets (T51_COMPILERS, T51_VERIFY), then t51's greedy
cleanup. A pair is focused on its register site (t51's lifetime and hint levers need a variable).
RESULT      2026-09-13: 0 of 787 rows with 2 to 8 pins (reg_astra's held-out rows skipped), for 90,439
            compiles and 8,817 verifies. Joint erasures that need no rewrite are pin_search's (erasures
            mode); a pair base under t51's one-site menu does not pay. Kept for the record, not in the cascade.
"""
import itertools
import os

from xform.t51_sched_order import T as T51, sites_of

MAXPINS = int(os.getenv("T51B_MAXPINS", "8"))
SPAN = int(os.getenv("T51B_SPAN", "12"))


class T(T51):
    name = "t51b_pairs"

    @staticmethod
    def eligible(text, row, census):
        return T51.eligible(text, row, census) or (None if len(sites_of(text)) > 1 else "fewer than two pins")

    @classmethod
    def groups(cls, pins):
        pairs = list(itertools.combinations(range(len(pins)), 2))
        if len(pins) <= MAXPINS:
            return [list(p) for p in pairs]
        near = sorted((abs(pins[i][5] - pins[j][5]), i, j) for i, j in pairs if abs(pins[i][5] - pins[j][5]) <= SPAN)
        return [[i, j] for _, i, j in near[:40]]
