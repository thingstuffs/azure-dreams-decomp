"""T83: an existing store of a just-computed value moved to immediately after its producer.

APPEARS     inside one block, a local is computed and stored to memory much later, with a fence (or a keep /
            register pin) between the two and repeated loads of the same fields in between:
                color_product = effect->unk_00 * effect->unk_32.unk_32;
                red = color_product / effect->unk_34;
                ASM_MEM_BARRIER();
                color_product = effect->unk_01 * effect->unk_32.unk_32;
                green = color_product / effect->unk_34;
                ASM_MEM_BARRIER();
                ...
                effect->unk_04.bytes.unk_04 = red;
                effect->unk_04.bytes.unk_05 = green;
RESOLVES    dungeon/func_80D1170C byte-exact (lane r59_sol_mid5, 2026-09-20): the red byte store moved to
            right after the red quotient and the green byte store right after the green quotient - BOTH
            moved together - and both ASM_MEM_BARRIER fences erased.  Mechanism: gcc 2.x cse caches the
            field loads of `effect` across the run; a real store to `effect` invalidates that table
            (`invalidate_memory` / `invalidate` on the write), so the shared scale and divisor loads come
            back as reloads instead of being folded, which is what retail has.  The stores themselves are
            free to sink: sched.c proves the two byte members disjoint (different constant offsets off one
            base, `true_dependence` false) and returns them to retail's late positions.  The fences were
            standing in for the missing store-side invalidation and go with it.
CANDIDATES  per function, every (producer, store) pair in a pinned window - `v = <expr>;` and a later
            `LHS = v;` / `LHS = (cast)v;` with v not rewritten in between - all pairs moved jointly first,
            then each singly; the store placed immediately after its producer, then one and two statements
            further down; for each move the window pins erased jointly, then singly, then the function's
            pins jointly.  A pinned window reaches from the producer (or MAX_SPAN lines above the store,
            whichever is higher up) to two lines past the store, so a pair whose producer sits above the
            pin counts when its store is in the window (round 61: 125 of the 131 r60 rows missed, 40 of
            them at listing distance 1 or 2).
            Round 61 also moves RUNS: a maximal run of adjacent stores (only blank and pin lines between
            them), each member with a producer above the run, travels as ONE unit to just after the LAST
            of those producers (and one and two statements further down), every contiguous sub-run of two
            or more members likewise.  Retail keeps such a run contiguous, so moving one member to its own
            producer splits it - the near misses of r60 are one slot off for exactly that reason; a member
            may never be lifted above its own producer (it would store a stale value), which is why the
            destination is the LAST producer of the group.  Groups are ranked runs, then the joint move of
            every pair, then the singles, then the remaining contiguous subsets, so a row with many pairs
            reaches its singles inside the listing budget.
            Candidates are ranked by cc1 listing distance to the pinned text (screen.py) and only the
            nearest go to `vf` (at most MAX_VERIFY per row).  A move across a call, across a statement that
            names v, or across a bare write to a name of the store's LHS is refused, as is one that leaves
            its block (label, brace or control statement in between).
"""
import os
import difflib, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from . import natural as N
    from . import screen
except ImportError:
    import natural as N
    import screen

MAX_PAIRS = 6            # pairs considered per row (nearest a pin first)
MAX_OFFSET = 2           # statements the store may travel past its producer
MAX_SPAN = 24            # lines between producer and store
MAX_LISTINGS = 140       # cc1 screens per row
MAX_VERIFY = 6           # byte-scorer runs per row
MAX_ROUNDS = 3
MAX_RUNS = 6             # run groups (the whole run and its sub-runs) per row
MAX_GROUPS = 14          # move groups screened per round

ID = r"[A-Za-z_]\w*"
KEYWORDS = {"if", "for", "while", "do", "return", "goto", "switch", "case", "default", "break", "continue",
            "else", "sizeof"}
STORE_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<lhs>[^=;{}]*?)[ \t]*=(?!=)[ \t]*"
                      r"(?:\([ \t]*[A-Za-z_][\w \t\*]*\)[ \t]*)?(?P<v>%s)[ \t]*;[ \t]*$" % ID)
PROD_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>%s)[ \t]*=(?!=)[ \t]*(?P<e>[^;{}]+);[ \t]*$" % ID)
PIN_LINE_RE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+[ \t]*\(")
CALL_RE = re.compile(r"(?<![\w.])(?<!->)(?P<f>%s)[ \t]*\(" % ID)
MEMLHS_RE = re.compile(r"->|\.|\[|^[ \t]*\*")
STMT_END_RE = re.compile(r";[ \t]*$")
CONTROL_RE = re.compile(r"^[ \t]*(?:goto|return|break|continue|case|default|if|while|for|do|switch|else)\b")
LABEL_RE = re.compile(r"^[ \t]*(?P<l>%s)[ \t]*:[ \t]*;?[ \t]*$" % ID)


def _writes(line, name):
    """`name` written as a whole variable on this line (`name = `, `name op= `, `name++`, `--name`)."""
    n = re.escape(name)
    return bool(re.search(r"(?<![\w.])(?<!->)%s[ \t]*(?:[-+*/%%&|^]|<<|>>)?=(?!=)" % n, line)
                or re.search(r"(?<![\w.])(?<!->)%s[ \t]*(?:\+\+|--)|(?:\+\+|--)[ \t]*%s\b" % (n, n), line))


def _has_call(line):
    return any(m.group("f") not in KEYWORDS and not m.group("f").startswith("ASM_")
               for m in CALL_RE.finditer(line))


def _plain(line):
    """An ordinary one-line statement (not a pin, label, control head or brace)."""
    s = line.strip()
    return bool(s and STMT_END_RE.search(line) and "{" not in line and "}" not in line
                and not PIN_LINE_RE.match(line) and not CONTROL_RE.match(line) and not LABEL_RE.match(line))


def _skippable(line):
    """A line a run may span and a producer walk may step over: blank, or a pin statement."""
    return not line.strip() or bool(PIN_LINE_RE.match(line))


def _locals(t, fn):
    """Names declared in the function (params included) that a store may be moved around."""
    names = {d["name"] for d in fn.params}
    for k in range(fn.a, fn.b + 1):
        m = N.VDECL_RE.match(t.m[k])
        if m and m.group("base") not in KEYWORDS:
            names.add(m.group("n"))
    body = "\n".join(t.m[fn.a:fn.b + 1])
    taken = set(re.findall(r"&[ \t]*(%s)" % ID, body))
    vol = {m.group("n") for m in (N.VDECL_RE.match(t.m[k]) for k in range(fn.a, fn.b + 1))
           if m and set(m.group("q").split()) & {"volatile", "static", "extern"}}
    return names - taken - vol


def _lhs_names(lhs, v):
    return [n for n in re.findall(ID, lhs) if n != v]


def _stores(t, fn, loc):
    """[(line, v, lhs, indent)] - every `MEM = v;` store of a movable local in the function."""
    out = []
    for s in range(fn.a + 1, fn.b):
        sm = STORE_RE.match(t.m[s])
        if not sm:
            continue
        lhs, v = sm.group("lhs").strip(), sm.group("v")
        if v not in loc or not lhs or not MEMLHS_RE.search(lhs) or _has_call(lhs) or "ASM_" in t.m[s]:
            continue
        out.append((s, v, lhs, sm.group("ind")))
    return out


def window_pins(sites, prod, store):
    """Indices of the pins in a pair's window: from the producer (or MAX_SPAN lines above the store,
    whichever is higher up) to two lines past the store.  The producer may sit above the pin."""
    lo, hi = min(prod, store - MAX_SPAN), store + 2
    return [i for i, s in enumerate(sites) if lo <= s[5] - 1 <= hi]


def pairs(text, adjacent=False):
    """[(prod_line, store_line, v, lhs)] (0-based lines) for every movable producer/store pair.
    `adjacent` keeps the pairs whose store already follows its producer (a run member)."""
    t = N._T(text)
    out = []
    for fn in N._functions(t):
        loc = _locals(t, fn)
        for s, v, lhs, ind in _stores(t, fn, loc):
            lnames = _lhs_names(lhs, v)
            prod = None
            for p in range(s - 1, max(fn.a, s - MAX_SPAN) - 1, -1):
                ln = t.m[p]
                if _skippable(ln):
                    continue
                pm = PROD_RE.match(ln)
                if pm and pm.group("v") == v:
                    prod = p
                    break
                if N._occ(v).search(ln) or "{" in ln or "}" in ln or LABEL_RE.match(ln) or CONTROL_RE.match(ln):
                    break
            if prod is None or (prod + 1 == s and not adjacent):
                continue
            pe = PROD_RE.match(t.m[prod])
            if N._occ(v).search(pe.group("e")) or pe.group("ind") != ind:
                continue
            if fn.crosses(prod, s):
                continue
            if _crossable(t, prod + 1, s, [(prod, s, v, lhs)]):
                out.append((prod, s, v, lhs))
    return out


def _crossable(t, lo, hi, members):
    """Nothing in lines [lo, hi) stops the members' stores from travelling over it.  The members'
    own store lines are not obstacles: the group moves as one and keeps its order."""
    srcs = {s for _, s, _, _ in members}
    for j in range(lo, hi):
        ln = t.m[j]
        if _skippable(ln) or j in srcs:
            continue
        if not _plain(ln) or _has_call(ln):
            return False
        for _, s, v, lhs in members:
            if N._occ(v).search(ln) or any(_writes(ln, n) for n in _lhs_names(lhs, v)):
                return False
    return True


def _run_producer(t, fn, start, v, ind):
    """The nearest `v = <expr>;` above line `start` (the first line of a run), or None."""
    for p in range(start, max(fn.a, start - MAX_SPAN) - 1, -1):
        ln = t.m[p]
        if _skippable(ln):
            continue
        pm = PROD_RE.match(ln)
        if pm and pm.group("v") == v:
            if N._occ(v).search(pm.group("e")) or pm.group("ind") != ind:
                return None
            return p
        if _writes(ln, v) or "{" in ln or "}" in ln or LABEL_RE.match(ln) or CONTROL_RE.match(ln):
            return None
    return None


def runs(text):
    """[[(prod, store, v, lhs), ...]] - maximal runs of two or more adjacent stores whose producers all
    sit above the run.  Retail keeps such a run contiguous; the whole run is one move."""
    t = N._T(text)
    out = []
    for fn in N._functions(t):
        loc = _locals(t, fn)
        st = _stores(t, fn, loc)
        blocks, cur = [], []
        for x in st:
            if cur and all(_skippable(t.m[j]) for j in range(cur[-1][0] + 1, x[0])):
                cur.append(x)
            else:
                blocks.append(cur)
                cur = [x]
        blocks.append(cur)
        for blk in blocks:
            if len(blk) < 2:
                continue
            start = blk[0][0]
            group = []
            for s, v, lhs, ind in blk:
                p = _run_producer(t, fn, start - 1, v, ind)
                if p is None or fn.crosses(p, s):
                    if len(group) > 1:
                        out.append(group)
                    group = []
                    continue
                group.append((p, s, v, lhs))
            if len(group) > 1:
                out.append(group)
    return out


def run_groups(text):
    """Run moves worth screening: each run, then its contiguous sub-runs, longest first."""
    out = []
    for g in runs(text):
        for n in range(len(g), 1, -1):
            for i in range(len(g) - n + 1):
                out.append(g[i:i + n])
    return out[:MAX_RUNS]


def run_plans(text, group):
    """[(label, moved_text)] - the whole group lifted, in order, to just after its LAST producer (and one
    and two statements past it)."""
    t = N._T(text)
    lines = text.split("\n")
    start, last = group[0][1], max(p[0] for p in group)
    if last >= start:
        return []
    out = []
    for off, tgt in enumerate(targets(lines, last, start)):
        if not _crossable(t, tgt + 1, group[-1][1], group):
            break
        moved = move(text, [(s, tgt) for _, s, _, _ in group])
        if moved is None or moved == text:
            continue
        out.append(("run%s@%d+%d" % ("+".join(str(p[1] + 1) for p in group), last + 1, off), moved))
    return out


def targets(text, prod, stop):
    """Insertion lines (0-based, `after this line`) for a store: 0, 1 and 2 statements past its producer."""
    lines = text.split("\n") if isinstance(text, str) else text
    out, k = [prod], prod + 1
    while len(out) <= MAX_OFFSET and k < stop:
        ln = lines[k]
        if not ln.strip() or PIN_LINE_RE.match(ln):
            k += 1
            continue
        if not _plain(ln):
            break
        out.append(k)
        k += 1
    return out


def move(text, moves):
    """The chosen store lines lifted to just after their insertion lines (None if a move eats a move)."""
    lines, srcs = text.split("\n"), {s for s, _ in moves}
    if any(a in srcs or a >= s for s, a in moves):
        return None
    after = {}
    for s, a in sorted(moves):
        after.setdefault(a, []).append(lines[s])
    out = []
    for k, ln in enumerate(lines):
        if k in srcs:
            continue
        out.append(ln)
        out.extend(after.get(k, ()))
    return "\n".join(out)


def _plans(text, chosen, offsets):
    """[(label, moved_text)] for one set of pairs, each store pushed `offset` statements down."""
    out, lines = [], text.split("\n")
    for off in offsets:
        moves = []
        for prod, s, _, _ in chosen:
            ts = targets(lines, prod, s)
            if off >= len(ts):
                moves = None
                break
            moves.append((s, ts[off]))
        if not moves:
            continue
        m = move(text, moves)
        if m is not None and m != text:
            out.append(("%s@%s+%d" % ("+".join(str(c[1] + 1) for c in chosen), chosen[0][0] + 1, off), m))
    return out


def _groups(text, sites):
    """The move groups of one round, ranked: runs, the joint move of every pair, the singles, then the
    remaining contiguous subsets.  Only groups with a pin in their window are kept."""
    def inwin(g):
        return any(window_pins(sites, p[0], p[1]) for p in g)
    rgs = [("run", g) for g in run_groups(text) if inwin(g) and run_plans(text, g)]
    ps = [p for p in pairs(text) if window_pins(sites, p[0], p[1])]
    ps = sorted(sorted(ps, key=lambda p: min(abs(s[5] - 1 - p[1]) for s in sites))[:MAX_PAIRS])
    rest = [("pairs", ps[i:i + n]) for n in range(len(ps) - 1, 1, -1) for i in range(len(ps) - n + 1)]
    out = rgs + ([("pairs", ps)] if len(ps) > 1 else []) + [("pairs", [p]) for p in ps] + rest
    return out[:MAX_GROUPS]


class T:
    name = "t83_storeafterproducer"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        sites = sites_of(text)
        if not sites:
            return "no pins"
        ps, rs = pairs(text), runs(text)
        if not ps and not rs:
            return "no producer/store pair"
        if not _groups(text, sites):
            return "no pair in a pinned window"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        cur, steps, listings, verifies, best = text, [], 0, 0, None
        for _ in range(MAX_ROUNDS):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            step, listings, verifies, d = cls._round(row, cur, target, vf, listings, verifies)
            if d is not None and (best is None or d < best):
                best = d
            if step is None:
                break
            cur, done = step
            steps.append(done)
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur)),
                "near": best}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))

    @classmethod
    def _round(cls, row, cur, target, vf, listings, verifies):
        """One exact step on `cur` (or None), with the listing/verify counters carried through."""
        sites = sites_of(cur)
        groups = _groups(cur, sites)
        if not groups:
            return None, listings, verifies, None
        cands, best = [], None
        for kind, group in groups:
            plans = run_plans(cur, group) if kind == "run" else _plans(cur, group, range(MAX_OFFSET + 1))
            for label, moved in plans:
                msites = sites_of(moved)
                if len(msites) != len(sites):
                    continue
                win = sorted({i for p in group for i in window_pins(sites, p[0], p[1])})
                trials, seen = [], set()
                for g in ([win] if len(win) > 1 else []) + [[i] for i in win] + \
                         ([list(range(len(sites)))] if len(sites) > len(win) else []):
                    if g and tuple(g) not in seen:
                        seen.add(tuple(g))
                        trials.append(g)
                for g in trials:
                    if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                        break
                    cand = erase_many(moved, [msites[i] for i in g], clean_notes=True)
                    if len(sites_of(cand)) >= len(sites):
                        continue
                    lst = screen.compile_s(row, cand)
                    listings += 1
                    if lst is None:
                        continue
                    d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                            if y[:1] in "+-" and not y.startswith(("---", "+++")))
                    best = d if best is None else min(best, d)
                    name = "%s-erase%d" % (label, len(g))
                    if d == 0:                                   # listing-exact: the scorer decides at once
                        verifies += 1
                        if vf(cand).get("exact"):
                            return (cand, name), listings, verifies, best
                    else:
                        cands.append((d, len(cands), cand, name))
        cands.sort(key=lambda c: (c[0], c[1]))                   # nothing was listing-exact: the two nearest
        NEAR_VERIFY = int(os.environ.get('NEAR_VERIFY', '4'))            # round 61: the near band (d <= 2) gets four scorer runs
        for d, _, cand, name in [c for c in cands if c[0] <= 2][:NEAR_VERIFY]:
            if verifies >= min(MAX_VERIFY, NEAR_VERIFY):
                break
            verifies += 1
            if vf(cand).get("exact"):
                return (cand, name), listings, verifies, best
        return None, listings, verifies, best
