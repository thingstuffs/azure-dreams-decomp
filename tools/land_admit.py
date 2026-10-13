"""Lander admission on the LIVE fidelity-site count (round 98: 78 call-arity / prototype fixes had to be applied by
hand because tools/lanes/land_lanes.sh skipped them as `pins 0 -> 0 grew []`: pins equal, no counted kind fell).

A candidate is a win when the number of L5 `fidelity_site` sites (levels.live_fidelity_sites -- the very function
levels.jsonl and the STATUS shape census use) falls; it is refused as growth only when pins are equal and the count
rises (the same rule as `goto` / `m2c`: a landing that removes pins is not blocked by this counter)."""
from collections import Counter
import re

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


def macro_volatile_uses(text):
    """Invocations of function-like macros whose body says `volatile` (r117 w_800463EC: the SPAD accessor).

    The `volatile` token sits once in the #define, so a candidate that moves seven of eight accessor sites to a plain
    twin removed seven volatile accesses that a token count cannot see. Each invocation counts as one volatile.
    """
    text = re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', text, flags=re.S))
    names = set(re.findall(r'^[ \t]*#[ \t]*define[ \t]+(\w+)\([^)\n]*\)[^\n]*\bvolatile\b', text, flags=re.M))
    body = re.sub(r'^[ \t]*#[ \t]*define[^\n]*', '', text, flags=re.M)
    return sum(len(re.findall(r'\b%s\s*\(' % re.escape(n), body)) for n in names)


def equal_pin_changes(row, cand, cur):
    """Equal-pin scaffolding admission used by land_lanes, without lane opt-ins.

    Keep these counters aligned with land_lanes.sh's admission block. Formatting
    and READABLE_LANES are deliberately not rebaseline admission reasons.
    """
    def code(text):
        return re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', text, flags=re.S))
    bad = re.compile(r'ASM_[A-Z0-9_]+(?=\()|ODDITY_[A-Z_]+(?=\()|while\s*\(\s*0\s*\)|__asm__|\basm\s*\(|\bvolatile\b')
    def kinds(text):
        found = Counter(m.group(0).replace(' ', '') for m in bad.finditer(
            re.sub(r'/\*.*?\*/', '', text, flags=re.S)))
        found['volatile'] += macro_volatile_uses(text)
        # r118 (owner 10-13): union sites are tracked trades (ledger/union_trades.jsonl); fewer unions is a fidelity gain
        found['union'] += len(re.findall(r'\bunion\b', re.sub(r'//[^\n]*', '', re.sub(r'/\*.*?\*/', '', text, flags=re.S))))
        return +found
    kc, ku = kinds(cand), kinds(cur)
    fell = [k for k in ku if kc[k] < ku[k]]
    grew = [k for k in kc if kc[k] > ku[k]]
    counters = {
        'goto': r'\bgoto\s+\w+\s*;|\bgoto\s*\*|[{,=]\s*&&\s*[A-Za-z_]\w*',
        'm2c': r'\bM2C_[A-Z_]+\b|\b(?:temp|var|phi)_[a-z][a-z0-9_]*\b|\barg[0-9]\b|\bsp[0-9A-F]{2,3}\b|\bNON_MATCHING\b|\bS_[0-9A-F]{8}\w*',
        'fakedep': r'\+\s*(\w+)\s*-\s*\1\b(?!\s*[\[(.]|\s*->)|-\s*(\w+)\s*\+\s*\2\b(?!\s*[\[(.]|\s*->)|\b(\w+)\s*\^\s*\3\b|&\s*(\w+)\s*&\s*\4\b|(?<![\w.>\]])\b(\w+)\s*=\s*\5\s*;|(?<![\w.>\]])\b(\w+)\s*\+=\s*(\w+)\s*;\s*\6\s*-=\s*\7\s*;',
    }
    for kind, pattern in counters.items():
        nc, nu = len(re.findall(pattern, code(cand))), len(re.findall(pattern, code(cur)))
        if nc < nu:
            fell.append(kind)
        elif nc > nu:
            grew.append(kind)
    return admit(fell, grew, True, *fidelity_counts(row, cand, cur))
