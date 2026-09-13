"""T50: m2c's counted do-while written back as the `for` (or `while`) it came from, then t41c's greedy erasure.

APPEARS     `v = C; ... do { body; v++; } while (v < K);` - a do-while whose last statement steps the
            variable its test reads.  m2c renders gcc's rotated loop this way: a `for` whose entry
            test gcc folds (a constant start below a constant bound) compiles to the same bottom-tested
            loop, so m2c cannot tell it from a do-while.  2026-09-13: 172 such loops in about 127
            pinned rows (70 with a constant start and bound).
RESOLVES    the two spellings differ in their loop notes and labels: a `for` has a continue point
            before its step, which is a block boundary for the scheduler and a separate place for
            loop.c.  Pins (often a fence in the body) emulate that boundary.  Lane fences12,
            dungeon/func_80DBBFC8: `for (; effect_count < 1; effect_count++)` in place of the do-while
            closed the row with its fence gone.  The loop-form lever family (t41/t41c/t44) is the
            most productive generator family (83 rows before this).
Spellings per loop: `for (; C; step)`, `for (v = C0; C; step)` with the start folded in, and
`while (C) { body }`.  A loop whose entry test gcc cannot fold compiles to different bytes, so a
wrong spelling never verifies.  A body holding `continue` is left alone (it would run the step).
Bases: each spelling alone and with the loop's pins erased; from an exact base, t41c.greedy erases
the function's pins one at a time.  Budget T50_BUDGET scorer runs per row (default 60).
RESULT      first sweep (2026-09-13, 120 rows, 459 s): 0 rows.  In 34 of the first 47 refusals a
            spelling was exact WITH every pin in place and freed nothing: for a constant-trip loop
            gcc 2.x folds the entry test and emits the same code, so the spelling is neutral.  The
            lane row was the exception.  Kept as a record and for re-sweeps of changed rows.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t41b_gotoloop_while import _close
    from .t41c_gotoloop_greedy import greedy
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t41b_gotoloop_while import _close
    from t41c_gotoloop_greedy import greedy

BUDGET = int(os.environ.get("T50_BUDGET", "60"))
COND = re.compile(r"^\s*\(?\s*([A-Za-z_]\w*)\s*\)?\s*(<=|>=|!=|<|>)\s*(.+?)\s*$", re.S)
TAILPINS = re.compile(r"(?:\s*ASM_[A-Z0-9_]+\([^;]*\)\s*;)*\s*$")
NUM = r"-?(?:0x[0-9A-Fa-f]+|\d+)[uUlL]*"


def _step_re(v):
    v = re.escape(v)
    return re.compile(r"(?P<s>(?:\+\+|--)\s*%s|%s\s*(?:\+\+|--)|%s\s*[+-]=\s*[^;=]+|%s\s*=\s*%s\s*[+-]\s*[^;=]+)\s*;$"
                      % (v, v, v, v, v))


def _line_span(text, a, b):
    """Widen [a, b) to whole lines when nothing else shares them."""
    l0 = text.rfind("\n", 0, a) + 1
    l1 = text.find("\n", b)
    l1 = len(text) if l1 < 0 else l1 + 1
    if not text[l0:a].strip() and not text[b:l1].strip():
        return l0, l1
    return a, b


def loops(text):
    """dict per counted do-while: do_start, body (open, close), step span, cond, var, init span."""
    m, out = mask_comments(text), []
    for d in re.finditer(r"\bdo\s*\{", m):
        o = d.end() - 1
        e = _close(m, o, "{", "}")                       # index just past the body's `}`
        if e is None:
            continue
        w = re.match(r"\s*while\s*\(", m[e:])
        if not w:
            continue
        p = e + w.end() - 1
        pe = _close(m, p, "(", ")")
        if pe is None or not re.match(r"\s*;", m[pe:]):
            continue
        we = pe + re.match(r"\s*;", m[pe:]).end()
        cond = text[p + 1:pe - 1]
        cm = COND.match(m[p + 1:pe - 1])
        if not cm or "&&" in cond or "||" in cond:
            continue
        v = cm.group(1)
        body_m = m[o + 1:e - 1]
        if re.search(r"\bcontinue\b", body_m):
            continue
        core = body_m[:TAILPINS.search(body_m).start()]
        sm = _step_re(v).search(core)
        if not sm:
            continue
        before = core[:sm.start()].rstrip()
        if before and before[-1] not in ";{}":
            continue                                          # not a statement of its own
        s0, s1 = o + 1 + sm.start(), o + 1 + sm.end()
        # the start value: the last `v = C;` before the loop, with nothing reading or writing v between
        init = None
        pre = m[:d.start()]
        for im in re.finditer(r"(?<![\w.>])%s\s*=(?!=)\s*(%s)\s*;" % (re.escape(v), NUM), pre):
            init = im
        if init and (re.search(r"\b%s\b" % re.escape(v), m[init.end():d.start()])
                     or m[init.end():d.start()].count("{") != m[init.end():d.start()].count("}")
                     or re.search(r"^\s*[A-Za-z_]\w*:(?!:)", m[init.end():d.start()], re.M)):
            init = None
        out.append({"do": d.start(), "open": o, "close": e - 1, "end": we, "cond": cond.strip(),
                    "var": v, "step": (s0, s1), "step_text": text[s0:s1].rstrip().rstrip(";").strip(),
                    "init": (init.start(), init.end(), init.group(1)) if init else None})
    return out


def spellings(text, lp):
    """[(label, text)] for one loop."""
    s0, s1 = _line_span(text, *lp["step"])
    body_nostep = text[lp["open"] + 1:s0] + text[s1:lp["close"]]
    body = text[lp["open"] + 1:lp["close"]]
    tail = text[lp["end"]:]
    head = text[:lp["do"]]
    out = [("for", head + "for (; %s; %s) {" % (lp["cond"], lp["step_text"]) + body_nostep + "}" + tail),
           ("while", head + "while (%s) {" % lp["cond"] + body + "}" + tail)]
    if lp["init"]:
        i0, i1, c = lp["init"]
        i0, i1 = _line_span(text, i0, i1)
        out.append(("forinit", text[:i0] + text[i1:lp["do"]]
                    + "for (%s = %s; %s; %s) {" % (lp["var"], c, lp["cond"], lp["step_text"]) + body_nostep + "}" + tail))
    return out


def bases(text):
    sites, out = sites_of(text), []
    for lp in loops(text):
        for label, t1 in spellings(text, lp):
            if len(sites_of(t1)) != len(sites) or unscored_text(t1) != unscored_text(text):
                continue
            F = next((f for f in functions(t1) if f[2] < lp["do"] < f[3]), None)
            if F is None or not any(F[2] < s[3] < F[3] for s in sites_of(t1)):
                continue
            ss = sites_of(t1)
            shift = len(t1) - len(text)
            inside = [s for s in ss if lp["do"] - 80 < s[3] < lp["end"] + shift]
            bs = [t1] + ([erase_many(t1, inside, clean_notes=True)] if inside else [])
            out.append(("%s:%s" % (label, lp["var"]), lp["do"], (F[2], F[3]), bs))
    return out


class T:
    name = "t50_dofor"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not bases(text):
            return "no counted do-while in a function with pins"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0, runs, best = len(sites_of(text)), 0, None
        for name, pos, span, bs in bases(text):
            for b in bs:
                if runs >= BUDGET:
                    break
                runs += 1
                if not vf(b).get("exact"):
                    continue
                t, used = greedy(b, pos, span, vf, BUDGET - runs)
                runs += used
                if len(sites_of(t)) < n0 and (best is None or len(sites_of(t)) < len(sites_of(best[1]))):
                    best = ("dofor:%s" % name, t)
                break
        if best:
            return best[1], {"label": best[0], "pins": "%d->%d" % (n0, len(sites_of(best[1])))}
        return None, {"refused": ["no exact for/while base with fewer pins (%d runs)" % runs]}
