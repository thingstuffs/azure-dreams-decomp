"""T133: a backward-goto loop written as a REAL loop, jointly with erasing the register pins that stood in for its weight.

APPEARS     a row with (a) a backward goto loop (`label: ... if (c) goto label;`, or a rotated
            `if (c) { L: ... if (c) goto L; }`) and (b) pins on variables the loop references:
            `register T v ASM_REG("$r")` (callee-saved $16-$23/$30 first) and KEEP/USE-style pins.
RESOLVES    r81_opus_alloc1 (2026-09-30): global.c/flow.c weight a pseudo's references by loop depth only
            inside NOTE_INSN_LOOP_BEG/END.  m2c's goto loop has no notes, so every reference counts 1 and
            the allocation order (which variable gets which callee-saved register) comes out wrong; the
            ASM_REG pins stood in for the missing weight.  As do/while (or while) the weight is back and the
            pins are unnecessary (dungeon/func_80097F94: 6 -> 0 pins, 4 gotos gone; func_80F90E88: 2 pins).
            When the same rewrite lets loop.c MOVE code retail does not show (8009E0EC hoists an address,
            81904990 strength-reduces), the goto loop is original: those loops are refused, screened for
            free by comparing cc1's instruction count before and after the rewrite (pins kept).
CANDIDATES  loop rewrites come from t44_doloop_greedy (do-while, one label at a time) and t122_gotowhile
            (while / if+do-while forms); nothing is reimplemented.  Per loop L, with V = the pinned variables
            L references:
              all     every pin on V erased
              callee  only the callee-saved ASM_REG pins on V erased (when different from `all`)
              single  each pin on V alone, callee-saved first, LAST pin first
            plus, first, a joint candidate rewriting every t44 loop that holds a V pin, with all of them erased.
            A candidate must keep the unscored arms, have strictly fewer pins and the retail instruction count
            (cc1 listing, free); the first byte-exact one wins.
Budget: T133_MAX verifies per row (default 14), T133_LIST cc1 listings (default 40).
"""
import os, re, sys
from pathlib import Path

_HERE = Path(__file__).resolve()
sys.path.insert(0, str(_HERE.parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from . import t44_doloop_greedy as D44
    from . import t122_gotowhile as G122
    from . import screen
    from .t29_addrsym import mask_comments
except ImportError:
    sys.path.insert(0, str(_HERE.parent))
    import t44_doloop_greedy as D44
    import t122_gotowhile as G122
    import screen
    from t29_addrsym import mask_comments

MAX_VERIFY = int(os.environ.get("T133_MAX", "14"))
MAX_LISTINGS = int(os.environ.get("T133_LIST", "40"))
CALLEE_NUM = {str(n) for n in list(range(16, 24)) + [30]}
CALLEE_NAME = {"s%d" % n for n in range(9)} | {"fp"}
IDENT = re.compile(r"[A-Za-z_]\w*")


def is_callee(site):
    return site[0] == "reg" and (site[2] in CALLEE_NUM or site[2] in CALLEE_NAME)


def pinned_var(site):
    """The variable a pin names (None for a pin that names none, e.g. an expansion)."""
    if site[0] == "reg":
        ids = IDENT.findall(site[6] or "")
        return ids[-1] if ids else None
    if site[0] == "stmt" and site[2] and IDENT.fullmatch(site[2].strip()):
        return site[2].strip()
    return None


def _refs(masked_seg, var):
    return re.search(r"(?<![\w.>])%s\b" % re.escape(var), masked_seg) is not None


def _same_sites(text, t1):
    a, b = sites_of(text), sites_of(t1)
    if len(a) != len(b) or any(x[:3] != y[:3] or x[6] != y[6] for x, y in zip(a, b)):
        return None
    return b


def _swap_in(text):
    """t44 skips labels named loop_N (its own t41 output).  m2c's own labels are named that too, so hide the
    prefix with a same-length rename (offsets are preserved) while t44 looks; a no-op when `looq_` is in use."""
    if "looq_" in text:
        return text
    return re.sub(r"\bloop_", "looq_", text)


def _swap_out(text, orig):
    return text if "looq_" in orig else text.replace("looq_", "loop_")


def _d44_loops(text):
    return D44.loops(_swap_in(text))


def _d44_rewrite(text, lp):
    return _swap_out(D44.rewrite(_swap_in(text), lp), text)


DANGLING_IF = re.compile(r"\bif[ \t\n]*\((?:[^;{}()]|\([^;{}]*\))*\)[ \t\n]*\}")


def _wellformed(t1):
    """t44 mis-cuts an unbraced `if (c) goto L;` back edge (its scan re-matches the bare goto inside it and
    leaves `if (c) } while (1);`): such a rewrite is dropped here, t122 handles that shape."""
    return DANGLING_IF.search(mask_comments(t1)) is None


def _loop_rewrites(text):
    """[(tag, span_in_text, rewritten_text)] - one loop rewritten at a time, pins untouched."""
    out, seen = [], set()
    squash = lambda x: re.sub(r"\s+", "", x)          # the same loop spelled with other whitespace is one candidate
    for lp in _d44_loops(text):
        t1 = _d44_rewrite(text, lp)
        if t1 != text and _wellformed(t1) and squash(t1) not in seen:
            seen.add(squash(t1))
            out.append(("do:" + _swap_out(lp[2], text), (lp[0], lp[5]), t1))
    try:
        ls = G122.loops(text)
    except Exception:
        ls = []
    for i, (s, e, reps) in enumerate(ls):
        for a in range(len(reps)):
            t1 = G122.rewrite(text, [i], {i: a})
            if t1 != text and squash(t1) not in seen:
                seen.add(squash(t1))
                out.append(("while%d.%d" % (i, a), (s, e), t1))
    return out


def _pins_for(text, sites, span):
    """Indexes (into sites) of the pins on variables referenced inside span."""
    m = mask_comments(text)
    seg = m[span[0]:span[1]]
    out = []
    for i, s in enumerate(sites):
        v = pinned_var(s)
        if v and _refs(seg, v):
            out.append(i)
    return out


def _sets(sites, idx):
    """Erasure sets over the pin indexes `idx`, biggest first."""
    callee = [i for i in idx if is_callee(sites[i])]
    other = [i for i in idx if not is_callee(sites[i])]
    sets = [("all", list(idx))]
    if callee and callee != list(idx):
        sets.append(("callee", callee))
    for i in sorted(callee, reverse=True) + sorted(other, reverse=True):
        if len(idx) > 1 or ("one", [i]) != sets[0][1:]:
            sets.append(("one%d" % i, [i]))
    return sets


def candidates(text):
    """[(label, candidate_text, rewrite_tag)] - joint candidate first, then per loop."""
    sites = sites_of(text)
    if not sites:
        return []
    out, seen = [], {text}
    per = []
    for tag, span, t1 in _loop_rewrites(text):
        ss = _same_sites(text, t1)
        if ss is None or unscored_text(t1) != unscored_text(text):
            continue
        idx = _pins_for(text, sites, span)
        if not idx:
            continue
        per.append((tag, span, t1, ss, idx))
    # joint: every t44 loop that holds pins, applied one label at a time on the running text
    dos = [p for p in per if p[0].startswith("do:")]
    if len(dos) > 1:
        cur, names, idxs = text, [], set()
        for tag, span, t1, ss, idx in dos:
            names.append(tag[3:])
            idxs.update(idx)
        for name in names:
            lp = next((l for l in _d44_loops(cur) if _swap_out(l[2], cur) == name), None)
            if lp is None:
                cur = None
                break
            cur = _d44_rewrite(cur, lp)
        ss = _same_sites(text, cur) if cur else None
        if ss is not None and unscored_text(cur) == unscored_text(text):
            t = erase_many(cur, [ss[i] for i in sorted(idxs)], clean_notes=True)
            if t not in seen and unscored_text(t) == unscored_text(text):
                seen.add(t)
                out.append(("joint:%s:all" % "+".join(names), t, "joint"))
    for tag, span, t1, ss, idx in per:
        for kind, chosen in _sets(sites, idx):
            t = erase_many(t1, [ss[i] for i in chosen], clean_notes=True)
            if t in seen or unscored_text(t) != unscored_text(text) or len(sites_of(t)) >= len(sites):
                continue
            seen.add(t)
            out.append(("%s:%s" % (tag, kind), t, tag))
    return out


def icount(lst):
    return sum(1 for l in lst if l and not l.startswith(".") and not l.endswith(":"))


class T:
    name = "t133_looppins"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        sites = sites_of(text)
        if not sites:
            return "no pin sites"
        if not any(s[0] in ("reg", "stmt") and pinned_var(s) for s in sites):
            return "no pin on a named variable"
        if not (_d44_loops(text) or _safe_g122(text)):
            return "no backward-goto loop"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no loop rewrite with pins on its variables"]}
        n0 = len(sites_of(text))
        target = screen.compile_s(row, text)
        tn = icount(target) if target is not None else None
        bad_loops, tried, listed = set(), 0, 0
        for label, cand, tag in cands:
            if tried >= MAX_VERIFY:
                break
            if tn is not None and listed < MAX_LISTINGS:
                lst = screen.compile_s(row, cand)
                listed += 1
                if lst is None or icount(lst) != tn:
                    continue                      # not the retail instruction count: cannot be exact
            tried += 1
            if vf(cand).get("exact"):
                return cand, {"step": label, "pins_in": n0, "pins_out": len(sites_of(cand)), "verifies": tried}
        return None, {"refused": ["no exact loop rewrite + pin erasure (%d verifies of %d candidates)" % (tried, len(cands))]}


def _safe_g122(text):
    try:
        return G122.loops(text)
    except Exception:
        return []
