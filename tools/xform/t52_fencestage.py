"""T52: values staged through temporaries across a fence, written as each store's own expression.

APPEARS     a straight-line run around a live ASM_SCHED_BARRIER in which plain locals are computed
            (`t = p->f | 0xC;`, `t = x << 18;`), updated (`t |= 0x100;`, `t += u;`) and stored
            (`p->f = t;`), with the fence between the computations and the stores.
RESOLVES    the sched_astra lane (round 16): an empty volatile asm is a FULL dependency cut, so no
            statement order replaces a fence; only a changed dependency graph can.  Writing each store
            with its own expression - a direct read-modify-write of the field, `p->f = p->f | 0xC;`
            ... `p->f = p->f | 0x100;` - makes the second store's read depend on the first store,
            which is the order the fence was holding.  Three fence lanes found it independently:
            fences4 `dungeon/func_818BDB44`, fences13 `func_818BDD8C` (the same shape spelled `|=`),
            fences15 `func_80C16F00` (shift/add temporaries rebuilt into each store's expression).
Rewrite: each temporary's value and each field's stored value are carried symbolically through the
run, in terms of memory at the start of the run; every store is written with its own expression,
re-expressed through the stores before it; the temporaries' statements go, and so do the run's
fences, the run's pins naming a temporary, and the declarations (with their pins) of temporaries
nothing else uses.  Aborts on calls, control flow, `++`/`--`, a temporary read after the run, or a
field read that can no longer be expressed.  Both `LV = LV op K` and `LV op= K` are tried; from an
exact base t41c.greedy erases the function's other pins.  Budget T52_BUDGET scorer runs per row.
Windows: the maximal straight-line run also holds unrelated locals read after it (`part = obj->unk_0C;`),
so every window containing the fence (T52_SIDE statements each side) is tried, tightest first.
SELF-TEST   (2026-09-13) on the three lanes' base texts: reproduces fences4's and fences15's outputs
            exactly (both byte-exact), and on fences13's row goes one pin further than the lane (7 to 5,
            the unused register-pinned temporary's declaration dropped too).  50 fenced rows eligible.
RESULT      first sweep (2026-09-13, all 50 eligible rows): 1 row (`town/func_809548E4`, 19 to 18 pins).
            Most rows' runs rewrite and compile but are not exact: the three lane rows shared a
            mechanism the rest of the fenced population mostly does not.  A single-shape generator
            again pays about 1-2%; kept for cascades over changed rows.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t51_sched_order import units, declarations
    from .t36_paramwidth import functions
    from .t41c_gotoloop_greedy import greedy
    from .t12_stmtorder import mask
except ImportError:
    from t51_sched_order import units, declarations
    from t36_paramwidth import functions
    from t41c_gotoloop_greedy import greedy
    from t12_stmtorder import mask

BUDGET = int(os.environ.get("T52_BUDGET", "40"))
FENCE = "ASM_SCHED_BARRIER"
ID = r"[A-Za-z_]\w*"
SIMPLE_OPERAND = re.compile(r"-?(?:0x[0-9A-Fa-f]+|\d+)[uUlL]*|[A-Za-z_]\w*")
STMT = re.compile(r"^\s*(?P<lhs>[^;=]+?)\s*(?P<op>\||&|\^|\+|-|<<|>>)?=(?!=)\s*(?P<rhs>[^;]+?)\s*;\s*$")
PIN = re.compile(r"^\s*ASM_[A-Z0-9_]+\([^;]*\)\s*;\s*$")
CALLISH = re.compile(r"\b(?!sizeof\b)(?![A-Z][A-Z0-9_]*\s*\()[A-Za-z_]\w*\s*\(")   # F32(...) etc. are macros
PH = "\x01%d\x01"


def _close(s, i):
    depth = 0
    for j in range(i, len(s)):
        depth += (s[j] == "(") - (s[j] == ")")
        if depth == 0:
            return j + 1
    return None


def strip_parens(e):
    e = e.strip()
    while e.startswith("(") and _close(e, 0) == len(e):
        e = e[1:-1].strip()
    return e


def paren(e):
    e = e.strip()
    if SIMPLE_OPERAND.fullmatch(e) or (e.startswith("(") and _close(e, 0) == len(e)):
        return e
    return "(" + e + ")"


def _lv_re(lv):
    return re.compile(r"(?<![\w.>])" + re.escape(lv) + r"(?![\w\[])")


def subst(expr, temps, cur):
    """expr (read NOW) in terms of memory at the start of the run."""
    for L in sorted(cur, key=len, reverse=True):          # fields stored earlier in the run
        expr = _lv_re(L).sub(lambda _: cur[L], expr)
    return re.sub(r"(?<![\w.>])\b[A-Za-z_]\w*\b(?!\s*\()", lambda m: temps.get(m.group(0), m.group(0)), expr)


def as_current(v, cur):
    """v (start-of-run terms) in terms of memory NOW, or None if it reads a field since overwritten.
    Only the stored values of fields v actually reads are folded back (a stored constant like 0x80 is
    not a read of its field)."""
    keys = sorted((L for L in cur if _lv_re(L).search(v)), key=lambda L: -len(cur[L]))
    for n, L in enumerate(keys):
        v = v.replace(cur[L], PH % n)
    if any(_lv_re(L).search(v) for L in keys):
        return None
    for n, L in enumerate(keys):
        v = v.replace(PH % n, L)
    return strip_parens(v)


LAST_WHY = ""


def _no(why):
    global LAST_WHY
    LAST_WHY = why
    return None


def runs(text):
    """(fence record index, lo, hi) of the straight-line run around each live fence."""
    lines, recs = units(text)
    out = []
    for k, r in enumerate(recs):
        if FENCE not in r["masked"] or r["arm"] in ("port", "dead") or not PIN.match(r["masked"]):
            continue

        def ok(z):
            if z["depth"] != r["depth"] or z["arm"] != r["arm"] or z["decl"]:
                return False
            s = z["masked"]
            return bool(PIN.match(s) or (z["simple"] and STMT.match(s) and not CALLISH.search(s)
                                         and not re.search(r"\+\+|--", s)))
        lo = k
        while lo > 0 and ok(recs[lo - 1]):
            lo -= 1
        hi = k
        while hi + 1 < len(recs) and ok(recs[hi + 1]):
            hi += 1
        out.append((k, lo, hi))
    return lines, recs, out


def rewrite(text, lines, recs, lo, hi, style, decl=None):
    decl = declarations(text) if decl is None else decl
    temps, cur, stored, assigned = {}, {}, [], set()
    for z in recs[lo:hi + 1]:
        s = z["masked"]
        if PIN.match(s):
            continue
        m = STMT.match(s)
        lhs, op, rhs = m["lhs"].strip(), m["op"], m["rhs"].strip()
        val = subst(rhs, temps, cur)
        if re.fullmatch(ID, lhs) and lhs in decl:                     # a temporary
            base = temps.get(lhs, lhs)
            temps[lhs] = paren("%s %s %s" % (base, op, paren(val)) if op else val)
            assigned.add(lhs)
            continue
        lv = re.sub(r"\s+", " ", lhs)
        if op:
            val = "%s %s %s" % (cur.get(lv, lv), op, paren(val))
        stored.append((z["line"], lv, paren(val), bool(re.search(r"\b(?:%s)\b" % "|".join(map(re.escape, temps)) , rhs)) if temps else False))
        cur[lv] = paren(val)
    if not assigned or not any(t for *_, t in stored):
        return _no("no temporary flows into a store")
    # write each store in terms of memory at its own point
    new_lines = list(lines)
    cur2 = {}
    for line, lv, v, uses_temp in stored:
        e = as_current(v, cur2)
        if e is None:
            return _no("store at line %d reads a field overwritten earlier in the run" % (line + 1))
        cur2[lv] = v
        if not uses_temp:
            continue                                                 # an ordinary store stays as written
        ind = re.match(r"[ \t]*", lines[line]).group(0)
        tail = lines[line][lines[line].rfind(";") + 1:].rstrip("\n")
        mm = re.fullmatch(re.escape(lv) + r"\s*(\||&|\^|\+|-|<<|>>)\s*(.+)", e)
        if style == "opassign" and mm and (SIMPLE_OPERAND.fullmatch(mm.group(2).strip()) or
                                            (mm.group(2).strip().startswith("(") and _close(mm.group(2).strip(), 0) == len(mm.group(2).strip()))):
            new_lines[line] = "%s%s %s= %s;%s\n" % (ind, lv, mm.group(1), strip_parens(mm.group(2)), tail)
        else:
            new_lines[line] = "%s%s = %s;%s\n" % (ind, lv, e, tail)
    # the temporaries' statements go; nothing after the run may read them
    F = next((f for f in functions(text) if f[2] <= sum(len(x) for x in lines[:recs[lo]["line"]]) < f[3]), None)
    if F is None:
        return _no("run not inside a function body")
    end_off = sum(len(x) for x in lines[:recs[hi]["line"] + 1])
    rest = mask(text[end_off:F[3]])
    for t in assigned:
        m = re.search(r"(?<![\w.>])\b%s\b" % re.escape(t), rest)
        if m and not re.match(r"\s*=(?!=)", rest[m.end():]):
            return _no("temporary %s is read after the run" % t)
    for z in recs[lo:hi + 1]:
        s = z["masked"]
        m = STMT.match(s) if not PIN.match(s) else None
        if m and m["lhs"].strip() in assigned:
            new_lines[z["line"]] = ""
    return "".join(new_lines), assigned, (recs[lo]["line"], recs[hi]["line"])


def finish(text, new, assigned, span):
    """Erase the run's fences and the run's pins naming a temporary; drop unused temporaries' declarations."""
    lines = new.splitlines(True)
    lo_off = sum(len(x) for x in lines[:span[0]])
    hi_off = sum(len(x) for x in lines[:span[1] + 1])
    names = lambda s: set(re.findall(ID, s[2] + " " + (s[6] or "")))
    ss = sites_of(new)
    kill = [s for s in ss if lo_off <= s[3] < hi_off and (s[1] == FENCE or names(s) & assigned)]
    new = erase_many(new, kill, clean_notes=True) if kill else new
    for t in sorted(assigned):
        d = declarations(new).get(t)
        if not d:
            continue
        body = new[:d["start"]] + new[d["end"]:]
        if re.search(r"(?<![\w.>])\b%s\b" % re.escape(t), mask(body)):
            continue                                                 # still used elsewhere
        line = new[d["start"]:d["end"]]
        if "=" in line.split("ASM_REG")[0].split(t, 1)[1]:
            continue                                                 # an initializer stays
        ls = new.rfind("\n", 0, d["start"]) + 1
        le = new.find("\n", d["end"]); le = len(new) if le < 0 else le + 1
        pins_on = [s for s in sites_of(new) if ls <= s[3] < le]
        if pins_on:
            new = erase_many(new, pins_on, clean_notes=True)
            d = declarations(new).get(t)
            if not d:
                continue
            ls = new.rfind("\n", 0, d["start"]) + 1
            le = new.find("\n", d["end"]); le = len(new) if le < 0 else le + 1
        new = new[:ls] + new[le:]
    return new


SIDE = int(os.environ.get("T52_SIDE", "8"))      # window reach on each side of the fence, in statements
PER_FENCE = 12


def bases(text):
    """Windows around each fence, tightest first: the maximal straight-line run also holds unrelated
    locals (`part = obj->unk_0C;`) that are read after it, so the rewrite is tried on every window
    [a, b] containing the fence, and each distinct result is kept once."""
    n0, out, seen = len(sites_of(text)), [], set()
    lines, recs, rs = runs(text)
    decl = declarations(text)
    for k, lo, hi in rs:
        found = []
        wins = sorted(((a, b) for a in range(max(lo, k - SIDE), k) for b in range(k + 1, min(hi, k + SIDE) + 1)),
                      key=lambda w: (w[1] - w[0], w[0]))
        for a, b in wins:
            for style in ("assign", "opassign"):
                r = rewrite(text, lines, recs, a, b, style, decl)
                if r is None:
                    continue
                new = finish(text, *r)
                if new in seen or len(sites_of(new)) >= n0 or unscored_text(new) != unscored_text(text):
                    continue
                seen.add(new)
                found.append(("%s@%d[%d-%d]" % (style, recs[k]["line"] + 1, recs[a]["line"] + 1, recs[b]["line"] + 1), new))
            if len(found) >= PER_FENCE:
                break
        pos = sum(len(x) for x in lines[:recs[k]["line"]])
        for label, new in found:
            F = next((f for f in functions(new) if f[2] <= min(pos, len(new) - 1) < f[3]), None)
            if F:
                out.append((label, pos, (F[2], F[3]), new))
    return out


class T:
    name = "t52_fencestage"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not any(s[1] == FENCE for s in sites_of(text)):
            return "no live scheduling fence"
        if not bases(text):
            return "no staged store run around a fence"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0, runs_, best = len(sites_of(text)), 0, None
        for label, pos, span, b in bases(text):
            if runs_ >= BUDGET:
                break
            runs_ += 1
            if not vf(b).get("exact"):
                continue
            t, used = greedy(b, pos, span, vf, BUDGET - runs_)
            runs_ += used
            if len(sites_of(t)) < n0 and (best is None or len(sites_of(t)) < len(sites_of(best[1]))):
                best = ("fencestage:%s" % label, t)
        if best:
            return best[1], {"label": best[0], "pins": "%d->%d" % (n0, len(sites_of(best[1])))}
        return None, {"refused": ["no exact staged-store rewrite (%d runs)" % runs_]}
