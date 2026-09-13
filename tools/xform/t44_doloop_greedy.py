"""T44: a backward-goto loop written as a do-while (the mirror of t41), then t41c's greedy erasure.

APPEARS     m2c's `label: ... if (C) goto label;` (or a trailing unconditional `goto label;`) in one
            block, with pins in the function. 2026-09-13: 165 such loops hold 756 pins in 113 rows.
RESOLVES    the mirror of t41. gcc 2.x's loop.c optimizes only loops with loop notes. Where the
            original WAS a structured loop, retail carries loop.c's effects (hoisting, strength
            reduction) that m2c's goto loop lacks, and pins emulate them. The do-while spelling brings
            the notes back.
Rewrite: `label:` becomes `do {` (the label is kept in front if anything else still jumps to it),
and the final `if (C) goto label;` becomes `} while (C);` (`while (1)` for an unconditional goto).
Every jump keeps its meaning. A label left at the very end of the body gets an empty statement.
RESULT      first sweep (2026-09-13, 1,466 rows; 179 loops in 119 rows): 15 rows, 26 pins, no errors.
            The loop-note lever works in both directions: t41 drops notes, t44 restores them.
Bases: the do-while alone, and with the loop's pins erased; from an exact base, t41c.greedy erases
the function's pins one at a time. Budget T44_BUDGET scorer runs per row (default 60).
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

BUDGET = int(os.environ.get("T44_BUDGET", "60"))
LABEL = re.compile(r"^([ \t]*)([A-Za-z_]\w*):(?!:)[ \t]*", re.M)


def loops(text):
    """(label_start, label_end, name, keep_label, body_end, stmt_end, cond) per backward-goto loop."""
    m, out = mask_comments(text), []
    for lab in LABEL.finditer(m):
        name = lab.group(2)
        if name in ("default", "case") or name.startswith("loop_"):
            continue
        refs = [g.start() for g in re.finditer(r"\bgoto\s+%s\s*;" % re.escape(name), m)]
        depth, i, last = 0, lab.end(), None
        while i < len(m):                                         # the last same-block backward goto
            ch = m[i]
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth < 0:
                    break
            elif depth == 0 and m.startswith("if", i) and not re.match(r"\w", m[i - 1:i] or " ") and re.match(r"if\s*\(", m[i:]):
                p = m.index("(", i)
                pe = _close(m, p, "(", ")")
                g = re.match(r"\s*(\{\s*)?goto\s+%s\s*;(\s*\})?" % re.escape(name), m[pe:]) if pe else None
                if g and bool(g.group(1)) == bool(g.group(2)):
                    last = (i, pe + g.end(), text[p + 1:pe - 1].strip())
            elif depth == 0 and re.match(r"goto\s+%s\s*;" % re.escape(name), m[i:]) and not re.match(r"\w", m[i - 1:i] or " "):
                g = re.match(r"goto\s+%s\s*;" % re.escape(name), m[i:])
                last = (i, i + g.end(), "1")
            i += 1
        if not last:
            continue
        others = [r for r in refs if not (last[0] <= r < last[1])]
        out.append((lab.start(), lab.end(), name, bool(others), last[0], last[1], last[2]))
    return out


def rewrite(text, lp):
    ls, le, name, keep, be, se, cond = lp
    ind = re.match(r"[ \t]*", text[ls:le]).group(0)
    body = text[le:be]
    if re.search(r"\b[A-Za-z_]\w*:[ \t]*\n?[ \t]*$", mask_comments(body)):
        body = body.rstrip() + " ;\n" + ind                       # a label must be followed by a statement
    head = ind + (name + ": " if keep else "") + "do {"
    return text[:ls] + head + body + "} while (" + cond + ");" + text[se:]


def bases(text):
    sites, out = sites_of(text), []
    for lp in loops(text):
        t1 = rewrite(text, lp)
        if len(sites_of(t1)) != len(sites) or unscored_text(t1) != unscored_text(text):
            continue
        F = next((f for f in functions(t1) if f[2] < lp[0] < f[3]), None)
        if F is None or not any(F[2] < s[3] < F[3] for s in sites_of(t1)):
            continue
        ss = sites_of(t1)
        inside = [s for s in ss if lp[0] < s[3] < lp[4] + (len(t1) - len(text))]
        bs = [t1] + ([erase_many(t1, inside, clean_notes=True)] if inside else [])
        out.append((lp[2], lp[0], (F[2], F[3]), bs))
    return out


class T:
    name = "t44_doloop_greedy"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not bases(text):
            return "no backward-goto loop in a function with pins"
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
                    best = ("doloop:%s" % name, t)
                break
        if best:
            return best[1], {"label": best[0], "pins": "%d->%d" % (n0, len(sites_of(best[1])))}
        return None, {"refused": ["no exact do-while base with fewer pins (%d runs)" % runs]}
