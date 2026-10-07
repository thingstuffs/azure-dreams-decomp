"""Lander admission on the LIVE fidelity-site count (round 98: 78 call-arity / prototype fixes had to be applied by
hand because tools/lanes/land_lanes.sh skipped them as `pins 0 -> 0 grew []`: pins equal, no counted kind fell).

A candidate is a win when the number of L5 `fidelity_site` sites (levels.live_fidelity_sites -- the very function
levels.jsonl and the STATUS shape census use) falls; it is refused as growth only when pins are equal and the count
rises (the same rule as `goto` / `m2c`: a landing that removes pins is not blocked by this counter)."""
import levels


def fidelity_counts(r, cand, cur, defidx=None):
    """(candidate count, current count) of live fidelity sites for row `r`."""
    return (len(levels.live_fidelity_sites(r, cand, defidx)), len(levels.live_fidelity_sites(r, cur, defidx)))


def admit(fell, grew, pins_equal, n_cand, n_cur):
    """Apply the rule to the lander's `fell` / `grew` lists in place; returns the (possibly extended) lists."""
    if n_cand < n_cur:
        fell.append("fidelity")
    elif n_cand > n_cur and pins_equal:
        grew.append("fidelity")
    return fell, grew
