"""T96: the conditional negate in the spellings t16 does not see, rewritten IN PLACE as `abs()`.

APPEARS     m2c's other two branch spellings of gcc's MIPS `abssi2`, with a pin standing for the
            branch it built around the negate:

              (goto)      if (axis_delta >= 0) { goto store_end; }          dungeon/func_81912154,
                          axis_delta = 0 - axis_delta;                      dungeon/func_818AAE60
                store_end:  ...
              (if/else)   if (delta_x < 0) { distance = delta_x;            dungeon/func_818E6800
                              ASM_KEEP_NV(distance); distance = -distance;
                          } else { distance = delta_x; }
              (fold)      target_x -= source_coord;                         dungeon/func_818B1664
                          if (target_x < 0) { target_x = -target_x; }
                          work.distance[0] = target_x;
                       -> work.distance[0] = abs(target_x - source_coord);

RESOLVES    nine pins over the four rows of the first KIT wave (work/native_lane/r70_kit_astra2,
            astra5 x2, astra6), byte-exact at their recorded recipes.  Mechanism is t16's: gcc 2.x's
            MIPS backend has one `abssi2` insn (mips.md, `bgez %1,1f; move %0,%1; subu %0,$0,%0`),
            and `expand_abs` reaches it through the tree code, so cse never sees the copy and never
            folds it away.  Written as a branch the copy and the negate are two insns whose ORDER
            the scheduler is free to change - which is what the `ASM_SCHED_BARRIER` above each of
            dungeon/func_818AAE60's five sites was holding.

            Why the two owners missed it (measured 2026-09-21 on the four lanes' base texts):
              * `t16_absidiom.idioms()` returns 0 on dungeon/func_81912154, func_818AAE60 and
                func_818E6800 - its `IF_RE` only matches `if (t < 0) { d = -x; }` and it skips any
                `if` followed by `else`.  Its pin plan is `names_var`, so the positional barriers
                above the idiom would be out of reach even if it matched.
              * `t91_absfresh` DOES detect the goto spelling (5 and 6 `negates()` on the two rows)
                but keeps only the sites with a single producing assignment (1 of 5, 4 of 6) and
                rewrites into a FRESH local by design; these rows are exact in place.

CANDIDATES  per function, up to MAX_SITES idioms of the three spellings; each one in place, with its
            producer folded into the call, and with its producer AND its consumer folded (the
            consumer only when the negated local is dead until its next assignment); all sites of
            the function jointly first, then one at a time.  Pin plans are POSITIONAL - the nearest
            pin to each rewritten site, the nearest two, every barrier pin within WINDOW lines of a
            site, the pins naming the negated local, and (on a small row) every pin.  Candidates are
            screened against the pinned text's cc1 listing and only the listing-nearest ones reach
            the byte verifier, as t74/t94 do.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t12_stmtorder import mask
    from .t16_absidiom import idioms as if_idioms, with_abs_decl
    from .t36_paramwidth import functions
    from .t91_absfresh import GOTO_NEG, ASSIGN_TO, MENTION
    from . import screen
except ImportError:
    from t12_stmtorder import mask
    from t16_absidiom import idioms as if_idioms, with_abs_decl
    from t36_paramwidth import functions
    from t91_absfresh import GOTO_NEG, ASSIGN_TO, MENTION
    import screen

MAX_SITES = 6
MAX_CANDS = 210
MAX_LISTINGS = 230
MAX_VERIFY = 6
WINDOW = 6                      # lines around a site whose barrier pins are a plan of their own
BARRIERS = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")

NEG = r"(?:0\s*-\s*|-\s*)\(?\s*(?P<x>[A-Za-z_]\w*)\s*\)?"
IFELSE = re.compile(r"\bif\s*\(\s*(?P<t>[A-Za-z_]\w*)\s*<\s*0\s*\)\s*"
                    r"\{(?P<a>[^{}]*)\}\s*else\s*\{(?P<b>[^{}]*)\}")
PIN_STMT = re.compile(r"^ASM_[A-Z0-9_]+\([^;]*\)$")
COPY = re.compile(r"^(?P<d>[A-Za-z_]\w*)\s*=\s*(?P<s>[A-Za-z_]\w*)$")
NEGST = re.compile(r"^(?P<d>[A-Za-z_]\w*)\s*=\s*" + NEG + r"$")
# a producing statement directly above the idiom: `d = <expr>;` or `d <op>= <expr>;`
PROD = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*"
                  r"(?:(?P<op>[-+*|&^]|<<|>>)=|=)[ \t]*(?P<e>[^;=][^;]*);[ \t]*$")
CONS = re.compile(r"^(?P<ind>[ \t]*)(?P<lhs>[^=;]+?)[ \t]*=[ \t]*(?P<v>[A-Za-z_]\w*)[ \t]*;[ \t]*$")


def _stmts(body):
    return [s.strip() for s in body.split(";") if s.strip()]


def _ifelse_sites(text, masked):
    """[(start, end, d, src)] for `if (t < 0) { d = t; pins; d = -d; } else { d = t; }`."""
    out = []
    for m in IFELSE.finditer(masked):
        t = m.group("t")
        a = [s for s in _stmts(m.group("a")) if not PIN_STMT.match(s)]
        b = [s for s in _stmts(m.group("b")) if not PIN_STMT.match(s)]
        if len(b) != 1:
            continue
        cb = COPY.match(b[0])
        if not cb or cb.group("s") != t:
            continue
        d = cb.group("d")
        if len(a) == 1:                                  # `{ d = -t; }`
            n = NEGST.match(a[0])
            if not n or n.group("d") != d or n.group("x") != t:
                continue
        elif len(a) == 2:                                # `{ d = t; d = -d; }`
            ca, n = COPY.match(a[0]), NEGST.match(a[1])
            if not (ca and n and ca.group("d") == d and ca.group("s") == t
                    and n.group("d") == d and n.group("x") in (d, t)):
                continue
        else:
            continue
        out.append((m.start(), m.end(), d, t))
    return out


def _goto_sites(text, masked, funcs):
    out = []
    for m in GOTO_NEG.finditer(masked):
        lab, d, t = m.group("l1") or m.group("l2"), m.group("d"), m.group("t")
        if lab != m.group("lab") or not (d == t == m.group("x")):
            continue                                     # only the IN-PLACE negate is an abs here
        fn = _enclosing(funcs, m.start())
        if fn is None:
            continue
        b0, b1 = fn
        if (len(re.findall(r"\bgoto[ \t]+%s\b" % re.escape(lab), masked[b0:b1])) != 1
                or len(re.findall(r"^[ \t]*%s[ \t]*:" % re.escape(lab), masked[b0:b1], re.M)) != 1):
            continue                                     # the label is reached from somewhere else
        out.append((m.start(), m.end(), d, d))
    return out


def _enclosing(funcs, pos):
    for _f, _p, b0, b1 in funcs:
        if b0 <= pos < b1:
            return b0, b1
    return None


def _line_span(text, start, end):
    """The whole-line span holding [start, end), or None when other code shares those lines."""
    ls = text.rfind("\n", 0, start) + 1
    le = text.find("\n", end)
    le = len(text) if le < 0 else le + 1
    if text[ls:start].strip() or text[end:le].strip():
        return None
    return ls, le


def sites(text):
    """[{kind, span, d, src, ind, line, prod, cons}] - every rewritable conditional negate."""
    masked = mask(text)
    funcs = functions(text)
    raw = ([("goto",) + s for s in _goto_sites(text, masked, funcs)]
           + [("ifelse",) + s for s in _ifelse_sites(text, masked)]
           + [("plainif", it["start"], it["end"], it["d"], it["d"]) for it in if_idioms(text)])
    out, seen = [], set()
    lines = text.split("\n")
    for kind, a, b, d, src in sorted(raw, key=lambda r: r[1]):
        fn = _enclosing(funcs, a)
        span = _line_span(text, a, b)
        if fn is None or span is None or span in seen:
            continue
        seen.add(span)
        i = text.count("\n", 0, span[0])
        ind = re.match(r"[ \t]*", lines[i]).group(0)
        s = {"kind": kind, "span": span, "d": d, "src": src, "ind": ind, "line": i,
             "fn": fn, "prod": None, "cons": None}
        if kind != "ifelse":
            s["prod"] = _producer(text, masked, span[0], d)
            s["cons"] = _consumer(text, masked, span[1], fn[1], d)
        out.append(s)
    return out[:MAX_SITES]


def _producer(text, masked, upto, d):
    """(line span, folded expression) for the statement right above the idiom, pins skipped."""
    lines, at = masked[:upto].split("\n"), upto
    i = len(lines) - 2
    real = text.split("\n")
    while i >= 0:
        s = lines[i].strip()
        if not s:
            i -= 1; continue
        if re.fullmatch(r"ASM_[A-Z0-9_]+\([^;]*\);", s):
            i -= 1; continue
        break
    if i < 0:
        return None
    m = PROD.match(lines[i])
    if not m or m.group("v") != d:
        return None
    e = m.group("e").strip()
    if not e or re.search(r"[A-Za-z_]\w*\s*\(", e) or "?" in e:
        return None                                      # a call or a ternary: leave it alone
    if m.group("op"):
        expr = "%s %s %s" % (d, m.group("op"), e if re.fullmatch(r"[\w.\->\[\]]+", e) else "(%s)" % e)
    else:
        if re.search(MENTION % re.escape(d), e):
            return None
        expr = e
    start = sum(len(l) + 1 for l in real[:i])
    return (start, start + len(real[i]) + 1), expr


def _consumer(text, masked, at, b1, d):
    """(line span, lhs) for a `X = d;` right below the idiom whose d is dead until its next set."""
    lines = masked[at:b1].split("\n")
    j, off = 0, at
    while j < len(lines) and not lines[j].strip():
        off += len(lines[j]) + 1; j += 1
    if j >= len(lines):
        return None
    m = CONS.match(lines[j])
    if not m or m.group("v") != d or re.search(MENTION % re.escape(d), m.group("lhs")):
        return None
    end = off + len(lines[j]) + 1
    nxt = re.search(ASSIGN_TO % re.escape(d), masked[end:b1])
    stop = end + nxt.start() if nxt else b1
    if re.search(MENTION % re.escape(d), masked[end:stop]):
        return None                                      # d is read again: the store must stay
    return (off, end), m.group("lhs").strip()


def _edits(s, variant, call):
    """[(a, b, replacement)] for one site in one variant, or None."""
    d, src, ind = s["d"], s["src"], s["ind"]
    expr = src
    ed = []
    if variant in ("fold", "foldcons"):
        if not s["prod"]:
            return None
        (pa, pb), expr = s["prod"]
        ed.append((pa, pb, ""))
    if variant == "foldcons":
        if not s["cons"]:
            return None
        (ca, cb), lhs = s["cons"]
        ed.append((s["span"][0], s["span"][1], ""))
        ed.append((ca, cb, "%s%s = %s(%s);\n" % (ind, lhs, call, expr)))
    else:
        ed.append((s["span"][0], s["span"][1], "%s%s = %s(%s);\n" % (ind, d, call, expr)))
    return ed


CALLS = {"abs": "abs", "abs-nodecl": "abs", "__builtin_abs": "__builtin_abs"}


def rewrite(text, chosen, variant, call):
    ed = []
    for s in chosen:
        one = _edits(s, variant, CALLS[call])
        if one is None:
            return None
        ed += one
    ed.sort(key=lambda e: -e[0])
    for (a, _b, _r), (_c, d, _r2) in zip(ed, ed[1:]):
        if d > a:                                        # overlapping edits: not offerable
            return None
    t = text
    for a, b, rep in ed:
        t = t[:a] + rep + t[b:]
    if call == "abs":
        return with_abs_decl(t)
    return t


def _plans(new, text, chosen):
    """Positional pin groups on the rewritten text."""
    pins = sites_of(new)
    if not pins:
        return []
    shift = len(new.split("\n")) - len(text.split("\n"))
    marks = [s["line"] + (shift if False else 0) for s in chosen]
    def nearest(k):
        g = []
        for ln in marks:
            for p in sorted(pins, key=lambda p: abs(p[5] - 1 - ln))[:k]:
                if p not in g:
                    g.append(p)
        return g
    bar = [p for p in pins if p[1] in BARRIERS and any(abs(p[5] - 1 - ln) <= WINDOW for ln in marks)]
    names = {s["d"] for s in chosen} | {s["src"] for s in chosen}
    named = [p for p in pins if any(a.strip() in names for a in (p[2] or "").split(","))]
    out = [("n1", nearest(1)), ("n2", nearest(2)), ("bar", bar), ("var", named)]
    if len(pins) <= 6:
        out.append(("fn", list(pins)))
    return out


def candidates(text):
    """[(label, new_text)] - each variant/spelling of each site (and of all sites) x pin plan."""
    found = sites(text)
    if not found:
        return []
    out, seen, sig = [], {text}, unscored_text(text)
    subsets = []
    if len(found) > 2:                                   # a row where only SOME sites fall together
        subsets = [[s for s in found if s is not drop] for drop in found]
        subsets += [found[i:] for i in range(1, len(found) - 1)]
    groups = ([found] if len(found) > 1 else []) + [[s] for s in found] + subsets
    for chosen in groups:
        sub = 1 < len(chosen) < len(found)
        tag = ("some%d@%d" % (len(chosen), chosen[0]["line"] + 1) if sub else
               "all%d" % len(chosen) if len(chosen) > 1 else
               "%s@%d" % (chosen[0]["kind"], chosen[0]["line"] + 1))
        for call in (("abs", "abs-nodecl") if sub else ("abs", "abs-nodecl", "__builtin_abs")):
            for variant in (("inplace",) if sub else ("inplace", "fold", "foldcons")):
                new = rewrite(text, chosen, variant, call)
                if new is None or unscored_text(new) != sig:
                    continue
                plans = _plans(new, text, chosen)
                plans = [p for p in plans if p[0] in ("n2", "bar", "var")] if sub else [("", [])] + plans
                for name, group in plans:
                    cand = erase_many(new, group, clean_notes=True) if group else new
                    if cand in seen or unscored_text(cand) != sig:
                        continue
                    if len(sites_of(cand)) >= len(sites_of(text)):
                        continue
                    seen.add(cand)
                    out.append(("%s:%s%s:%s" % (tag, variant,
                                                {"abs": "", "abs-nodecl": "-nd"}.get(call, "-bi"),
                                                name or "keep"), cand))
                    if len(out) >= MAX_CANDS:
                        return out
    return out


class T:
    name = "t96_absplace"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        found = sites(text)
        if not found:
            return "no conditional-negate idiom"
        if all(s["kind"] == "plainif" and not s["prod"] for s in found):
            return "only t16's own in-place idiom"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "sites": len(sites(text))}
        if not candidates(text):
            return None, dict(info, refused=["no candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        cur, steps, listings, verifies, spent, nearest = text, [], 0, 0, set(), []
        while listings < MAX_LISTINGS and verifies < MAX_VERIFY:
            ranked = []
            for label, cand in candidates(cur):
                if cand in spent or listings >= MAX_LISTINGS:
                    continue
                lst = screen.compile_s(row, cand); listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                ranked.append((d, len(sites_of(cand)), label, cand))
            ranked.sort(key=lambda x: (x[0], x[1]))
            if not steps:
                nearest = [{"distance": d, "label": l} for d, _, l, _ in ranked[:6]]
            moved = False
            for d, _, label, cand in ranked:
                if verifies >= MAX_VERIFY or (d and (steps or verifies >= 2)):
                    break
                spent.add(cand); verifies += 1
                if vf(cand).get("exact"):
                    cur, moved = cand, True
                    steps.append("%s|d%d" % (label, d))
                    break
            if not moved:
                break
        info.update(listings=listings, tried=verifies)
        if not steps:
            return None, dict(info, nearest=nearest)
        return cur, dict(info, step="+".join(steps), pins_out=len(sites_of(cur)))
