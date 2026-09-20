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
            pins jointly.  Candidates are ranked by cc1 listing distance to the pinned text (screen.py) and
            only the nearest go to `vf` (at most MAX_VERIFY per row).  A move across a call, across a
            statement that names v, or across a bare write to a name of the store's LHS is refused, as is
            one that leaves its block (label, brace or control statement in between).
"""
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
MAX_LISTINGS = 90        # cc1 screens per row
MAX_VERIFY = 6           # byte-scorer runs per row
MAX_ROUNDS = 3

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


def pairs(text):
    """[(prod_line, store_line, v, lhs)] (0-based lines) for every movable producer/store pair."""
    t = N._T(text)
    out = []
    for fn in N._functions(t):
        loc = _locals(t, fn)
        for s in range(fn.a + 1, fn.b):
            sm = STORE_RE.match(t.m[s])
            if not sm:
                continue
            lhs, v = sm.group("lhs").strip(), sm.group("v")
            if v not in loc or not lhs or not MEMLHS_RE.search(lhs) or _has_call(lhs) or "ASM_" in t.m[s]:
                continue
            lnames = [n for n in re.findall(ID, lhs) if n != v]
            prod = None
            for p in range(s - 1, max(fn.a, s - MAX_SPAN) - 1, -1):
                ln = t.m[p]
                if not ln.strip() or PIN_LINE_RE.match(ln):
                    continue
                pm = PROD_RE.match(ln)
                if pm and pm.group("v") == v:
                    prod = p
                    break
                if N._occ(v).search(ln) or "{" in ln or "}" in ln or LABEL_RE.match(ln) or CONTROL_RE.match(ln):
                    break
            if prod is None or prod + 1 == s:
                continue
            pe = PROD_RE.match(t.m[prod])
            if N._occ(v).search(pe.group("e")) or pe.group("ind") != sm.group("ind"):
                continue
            if fn.crosses(prod, s):
                continue
            bad = False
            for j in range(prod + 1, s):
                ln = t.m[j]
                if not ln.strip() or PIN_LINE_RE.match(ln):
                    continue
                if not _plain(ln) or _has_call(ln) or N._occ(v).search(ln) or any(_writes(ln, n) for n in lnames):
                    bad = True
                    break
            if not bad:
                out.append((prod, s, v, lhs))
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
    for s, a in moves:
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
        if m is not None:
            out.append(("%s@%s+%d" % ("+".join(str(c[1] + 1) for c in chosen), chosen[0][0] + 1, off), m))
    return out


class T:
    name = "t83_storeafterproducer"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        ps = pairs(text)
        if not ps:
            return "no producer/store pair"
        lines = [s[5] for s in sites_of(text)]
        if not any(any(p <= ln <= s + 2 for ln in lines) for p, s, _, _ in ps):
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
        lines = [s[5] for s in sites]
        ps = [p for p in pairs(cur) if any(p[0] <= ln <= p[1] + 2 for ln in lines)]
        ps = sorted(ps, key=lambda p: min(abs(ln - p[1]) for ln in lines))[:MAX_PAIRS]
        if not ps:
            return None, listings, verifies, None
        ps = sorted(ps)
        groups = [ps[i:i + n] for n in range(len(ps), 1, -1) for i in range(len(ps) - n + 1)] + [[p] for p in ps]
        cands, best = [], None
        for group in groups:
            for label, moved in _plans(cur, group, range(MAX_OFFSET + 1)):
                msites = sites_of(moved)
                if len(msites) != len(sites):
                    continue
                lo, hi = min(p[0] for p in group), max(p[1] for p in group) + 2
                win = [i for i, s in enumerate(sites) if lo <= s[5] <= hi]
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
        for d, _, cand, name in cands[:2]:
            if verifies >= min(MAX_VERIFY, 2):
                break
            verifies += 1
            if vf(cand).get("exact"):
                return (cand, name), listings, verifies, best
        return None, listings, verifies, best
