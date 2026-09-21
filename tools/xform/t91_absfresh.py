"""T91: the conditional negate written as `abs()` into a FRESH local, so the load is set once.

APPEARS     a value loaded into a local and then negated in place - `v = <expr>; if (v < 0) { v = -v; }`
            (also the braceless form, m2c's `0 - v`, the ternary `v = (v < 0) ? -v : v` and the
            copy+negate `t = v; if (t < 0) t = -t;`, and m2c's goto spelling `if (v >= 0) goto L;
            v = 0 - v; L:`) - with a pin next to it: an ASM_SCHED_BARRIER or
            ASM_MEM_BARRIER above the load, an ASM_KEEP on the object the load reads through, or a
            `register s32 v ASM_REG("$2")` on the loaded local itself.  Ten rows of the item-target
            family (dungeon/func_80A1F0C4, 80BECDA4, 80EB6FC8, 80F3575C, 80F89240, 80FDD1A0,
            81007034, 8105B1D4, 810AF0B4, 81252D6C; work/native_lane/r65_item_study/NOTE.md) are the
            exemplars: there the pin holds a plain `sw` ahead of the two coordinate loads that follow
            it, and erasing it alone sinks the store into the first `bgez` delay slot (18 lines).

RESOLVES    gcc 2.x sched.c `schedule_insn` calls `adjust_priority` (sched.c:2513) on every
            predecessor the just-scheduled insn releases, and with `reload_completed == 0` and no
            REG_DEAD notes left the `case 0:` arm promotes the insn to `max_priority`
            (LAUNCH_PRIORITY, 0x7f000001) when `birthing_insn_p` (sched.c:2469) holds - which needs
            the SET's destination pseudo to have `reg_n_sets == 1`, i.e. to be assigned exactly once
            in the whole function.  Spelled `v = load; if (v < 0) v = -v;` the pseudo is set twice,
            the load is never promoted, it ties on priority 2 with a neighbouring store, and
            `schedule_select`'s `potential_hazard` rule (sched.c:2616/1318) gives the tie to the
            SImode store - which is what the pin was holding.  Written `fresh = abs(<expr>);` into a
            NEW single-assignment local the load is a birthing insn, it leaves the store's priority
            group, and retail's order comes back with no dependence and no extra instruction.
            `abs()` itself is t16_absidiom's mechanism - expand_abs -> the MIPS `abssi2` insn
            (mips.md), ONE rtl insn emitting retail's `bgez/subu` pair, with the `move` dropped when
            the allocator coalesces the operands.  t16 rewrites IN PLACE (`v = abs(v);`), which
            leaves `reg_n_sets == 2` and measured 48 on func_8105B1D4: it recorded `noop` on all ten
            rows.  The destination being fresh is the whole point of this generator.

CANDIDATES  per function: every negate idiom whose value comes from ONE preceding assignment
            `v = <expr>;` in the same block with nothing naming v in between (or from a run that
            m2c split - `v = A; v -= B;` - which folds back into one parenthesised expression; that
            fold is what closes dungeon/func_800A0510 and func_800D0A10) - all of them jointly
            first (some rows only fall jointly), then each singly; the producer statement becomes
            `abs_v = abs(<expr>);`, every later read of v up to v's next assignment is renamed, v's
            declaration is kept (dropping it is a further variant) and `extern int abs(int);` is
            added when the file has no abs declaration.  The fresh local is declared with v's type
            widened to s32 when v is narrower (the original width is a second variant).  Pins: the
            window's pins (positional, plus any pin naming v wherever it sits - four of the ten
            exemplars pin the declaration itself) erased jointly, then singly, then the function's
            pins jointly; candidates are ordered by fewest remaining pins and scored with `vf`
            (MAX_VERIFY per row), `screen.compile_s` used only to drop candidates that do not build
            and, inside one pin-count bucket, as a tie-break.  The screen needs the 2026-09-21
            assembler-local-label fix to be meaningful here at all: before it, `abssi2`'s `1f`/`1:`
            labels made a byte-exact rewrite compare 26-74 lines from the pinned listing.

REFUSE      an in-place `v = abs(v);` (that is t16, and it leaves reg_n_sets == 2); a v with no
            single producing assignment; a pointer-typed v.  A v that is assigned again elsewhere in
            the function is still tried - the fresh local covers this site only, and the rename stops
            at v's next assignment - but it is where the exemplar family's three misses are
            (func_81007034, func_80BECDA4, func_810AF0B4): there the one pin was holding a second
            decision, and the residue is a register recolour in an unrelated block.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t12_stmtorder import mask
    from .t16_absidiom import idioms as if_idioms, names_var, with_abs_decl
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t12_stmtorder import mask
    from t16_absidiom import idioms as if_idioms, names_var, with_abs_decl
    from t36_paramwidth import functions
    import screen

MAX_SITES = 6           # idiom sites considered in one function
MAX_LISTINGS = 20       # screen compiles per row (a build filter, not a gate)
MAX_VERIFY = 8          # scorer runs per row
WINDOW = 3              # lines above the first producer that count as the site's window
NARROW = {"s8", "u8", "s16", "u16", "char", "short", "unsigned char", "signed char",
          "unsigned short", "signed short"}
WIDE = "s32"
# `v = (v < 0) ? -v : v;` - the ternary spelling of the same idiom (t16 does not match it)
TERNARY = re.compile(r"(?P<d>[A-Za-z_]\w*)\s*=\s*\(?\s*(?P<t>[A-Za-z_]\w*)\s*<\s*0\s*\)?\s*\?\s*"
                     r"\(?\s*(?:0\s*-|-)\s*(?P<n>[A-Za-z_]\w*)\s*\)?\s*:\s*\(?\s*(?P<p>[A-Za-z_]\w*)\s*\)?\s*;")
# m2c's goto spelling of the same negate (dungeon/func_80EB6FC8): the label goes with the idiom
GOTO_NEG = re.compile(r"\bif\s*\(\s*(?P<t>[A-Za-z_]\w*)\s*>=\s*0\s*\)\s*"
                      r"(?:\{\s*goto\s+(?P<l1>[A-Za-z_]\w*)\s*;\s*\}|goto\s+(?P<l2>[A-Za-z_]\w*)\s*;)\s*"
                      r"(?P<d>[A-Za-z_]\w*)\s*=\s*(?:0\s*-\s*|-\s*)\(?\s*(?P<x>[A-Za-z_]\w*)\s*\)?\s*;\s*"
                      r"(?P<lab>[A-Za-z_]\w*)[ \t]*:")
BLOCKY = re.compile(r"[#]|\bcase\b|\bdefault\b|\breturn\b")
LABEL_DEF = re.compile(r"^[ \t]*([A-Za-z_]\w*)[ \t]*:[ \t]*$", re.M)
# `v -= B;` and `v = v - B;` - one statement of a producing run m2c split (see `_producer`)
COMPOUND = re.compile(r"^\s*(?P<v>[A-Za-z_]\w*)\s*(?:(?P<op1>[-+*/|&^]|<<|>>)=|"
                      r"=\s*(?P=v)\s*(?P<op2>[-+*/|&^]|<<|>>))\s*(?P<e>[^;]*);$", re.S)
ASSIGN_TO = r"(?<![.>\w])\b%s\b[ \t]*(?:=(?!=)|\+\+|--|[-+*/|&^%%]=|<<=|>>=)"
MENTION = r"(?<![.>\w])\b%s\b"


def negates(text, masked=None):
    """[(start, end, d, t, label)] for every conditional-negate idiom: t16's shapes, the ternary and
    m2c's `if (v >= 0) goto L; v = 0 - v; L:` (whose label belongs to the idiom)."""
    masked = mask(text) if masked is None else masked
    out = [(it["start"], it["end"], it["d"], it["t"], None) for it in if_idioms(text)]
    for m in TERNARY.finditer(masked):
        if m.group("t") == m.group("n") == m.group("p"):
            out.append((m.start(), m.end(), m.group("d"), m.group("t"), None))
    for m in GOTO_NEG.finditer(masked):
        lab, d, t = m.group("l1") or m.group("l2"), m.group("d"), m.group("t")
        if lab == m.group("lab") and m.group("x") in (d, t) and t in (d, m.group("x")):
            out.append((m.start(), m.end(), d, t, lab))
    return sorted(set(out))


def _line_span(text, start, end):
    """The whole-line span holding [start, end) - or None when other code shares those lines."""
    ls = text.rfind("\n", 0, start) + 1
    le = text.find("\n", end)
    le = len(text) if le < 0 else le + 1
    if text[ls:start].strip() or text[end:le].strip():
        return None
    return ls, le


def outer(gap):
    """What is left of `gap` outside its nested blocks, or None if the braces do not balance.

    The producer and the idiom must be in the SAME block, but a complete nested block between them
    is fine - and it is the exemplar shape: the second coordinate's producer sits above the first
    coordinate's `if (x < 0) { ... }`."""
    out, depth = [], 0
    for ch in gap:
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth < 0:
                return None
        elif not depth:
            out.append(ch)
    return None if depth else "".join(out)


def _enclosing(funcs, pos):
    for f in funcs:
        if f[2] <= pos < f[3]:
            return f
    return None


def _producer(text, masked, b0, b1, upto, v):
    """(start, end, expr) of the assignment the idiom's value comes from.

    Normally the last `v = <expr>;` before `upto` with nothing naming v in between.  When v IS named
    in between, the only shape accepted is a run of compound assignments to v and nothing else
    (`v = A; v -= B;` - m2c's split of one expression, 60 of the 219 pinned negate sites): the run
    folds back into one parenthesised expression, which is what the fresh destination then abs()es.
    """
    last = None
    for m in re.finditer(r"(?<![.>\w])\b%s\b[ \t]*=(?!=)([^;{}]*);" % re.escape(v), masked[b0:upto]):
        if not re.search(MENTION % re.escape(v), m.group(1)):
            last = m
    if last is None:
        return None
    s, e = b0 + last.start(), b0 + last.end()
    expr = text[b0 + last.start(1):b0 + last.end(1)].strip()
    whole, gap = masked[e:upto], outer(masked[e:upto])
    if gap is None:
        return None
    if re.search(MENTION % re.escape(v), whole):
        if gap != whole:                              # a nested block naming v: not a plain run
            return None
        base = e
        for stmt in re.finditer(r"[^;]*;", whole):
            m2 = COMPOUND.match(stmt.group(0))
            if not m2 or m2.group("v") != v:
                return None
            at = base + stmt.start()
            expr = "(%s) %s (%s)" % (expr, m2.group("op1") or m2.group("op2"),
                                     text[at + m2.start("e"):at + m2.end("e")].strip())
            e = at + stmt.end() - stmt.start()
        if masked[e:upto].strip():
            return None
        whole, gap = masked[e:upto], masked[e:upto]
    if BLOCKY.search(gap):
        return None
    here = set(LABEL_DEF.findall(gap))
    if any(t not in here for t in re.findall(r"\bgoto[ \t]+([A-Za-z_]\w*)", gap)):
        return None                                   # a jump out of the gap: the idiom is a join
    for lab in here:
        # a join in the gap is fine only if every jump to it is inside the gap (the sibling idiom's
        # own `goto`, m2c's spelling); otherwise another path reaches the idiom past the producer
        g = r"\bgoto[ \t]+%s\b" % re.escape(lab)
        if len(re.findall(g, masked[b0:b1])) != len(re.findall(g, whole)):
            return None
    if not expr or re.search(r"(?<![=!<>])=(?!=)|\?", expr) or re.search(MENTION % re.escape(v), expr):
        return None
    return s, e, expr


def _decl(text, masked, b0, b1, v):
    """(line_start, line_end, indent, type) of v's declaration in the body, or None."""
    m = re.search(r"^([ \t]*)((?:register[ \t]+)?(?:(?:unsigned|signed|const|struct|union|enum)[ \t]+)*"
                  r"[A-Za-z_]\w*(?:[ \t]+(?:int|long|char|short))*[ \t\*]+)%s[ \t]*"
                  r"(?:ASM_REG\([^()]*\))?[ \t]*;[^\n]*$" % re.escape(v), masked[b0:b1], re.M)
    if not m:
        return None
    ls, le = b0 + m.start(), b0 + m.end() + 1
    ty = re.sub(r"\bregister\b", "", m.group(2)).strip()
    return ls, le, m.group(1), ty


def sites(text):
    """Every rewritable site: the negate idiom, its producing assignment and v's declaration."""
    masked, out = mask(text), []
    funcs = functions(text)
    for start, end, d, t, lab in negates(text, masked):
        fn = _enclosing(funcs, start)
        if fn is None:
            continue
        _, params, b0, b1 = fn
        if d in {p for p, _, _, _ in params}:
            continue
        if lab and (len(re.findall(r"\bgoto[ \t]+%s\b" % re.escape(lab), masked[b0:b1])) != 1 or
                    len(re.findall(r"^[ \t]*%s[ \t]*:" % re.escape(lab), masked[b0:b1], re.M)) != 1):
            continue                                  # the label is reached from somewhere else too
        prod = _producer(text, masked, b0, b1, start, d)
        if prod is None:
            continue
        ps, pe, expr = prod
        pspan, ispan = _line_span(text, ps, pe), _line_span(text, start, end)
        if pspan is None or ispan is None:
            continue
        dec = _decl(text, masked, b0, b1, d)
        if dec is not None and "*" in dec[3]:
            continue
        nxt = re.search(ASSIGN_TO % re.escape(d), masked[end:b1])
        stop = end + nxt.start() if nxt else b1
        reads = [(end + m.start(), end + m.end()) for m in
                 re.finditer(MENTION % re.escape(d), masked[end:stop])]
        out.append({"v": d, "tested": t, "fn": (b0, b1), "expr": expr, "prod": pspan, "idiom": ispan,
                    "decl": dec, "reads": reads, "indent": text[pspan[0]:ps],
                    "line": text.count("\n", 0, ps) + 1,
                    "other_sets": bool(nxt) or bool(re.search(ASSIGN_TO % re.escape(d), masked[b0:ps]))})
    return out[:MAX_SITES]


def _fresh_name(text, v, taken):
    base = "abs_" + re.sub(r"^(?:target_|offset_|value_|tmp_)", "", v)
    name, k = base, 2
    while re.search(MENTION % re.escape(name), text) or name in taken:
        name, k = "%s_%d" % (base, k), k + 1
    return name


def rewrite(text, chosen, grouped=True, widen=True):
    """The rewritten text: each site's producer becomes `fresh = abs(expr);`, the negate goes."""
    taken, names = set(), []
    for s in chosen:
        names.append(_fresh_name(text, s["v"], taken))
        taken.add(names[-1])
    edits = []
    for s, n in zip(chosen, names):
        edits.append((s["prod"][0], s["prod"][1], "%s%s = abs(%s);\n" % (s["indent"], n, s["expr"])))
        edits.append((s["idiom"][0], s["idiom"][1], ""))
        for a, b in s["reads"]:
            edits.append((a, b, n))
    decls, at0 = {}, None                         # insertion point -> declaration lines
    for s, n in zip(chosen, names):
        ty = s["decl"][3] if s["decl"] else WIDE
        if widen and ty in NARROW:
            ty = WIDE
        at, ind = (s["decl"][1], s["decl"][2]) if s["decl"] else (s["fn"][0] + 1, "    ")
        if grouped:                               # all of them where the FIRST v is declared
            at0 = at0 or (at, ind)
            at, ind = at0
        decls.setdefault(at, []).append("%s%s %s;\n" % (ind, ty, n))
    for at, lines in decls.items():
        edits.append((at, at, "".join(lines)))
    cur, last = text, len(text) + 1
    for a, b, repl in sorted(edits, key=lambda e: (-e[0], -e[1])):
        if b > last:                              # two sites' spans overlap: not a rewrite to offer
            return None
        cur, last = cur[:a] + repl + cur[b:], a
    return with_abs_decl(cur)


def drop_decls(text, chosen):
    """v's declaration line removed wherever v is no longer mentioned and the line holds no pin."""
    cur = text
    for s in sorted(chosen, key=lambda s: -(s["decl"][0] if s["decl"] else 0)):
        if not s["decl"]:
            continue
        v = s["v"]
        m = re.search(r"^[ \t]*[^\n;]*(?<![.>\w])\b%s\b[ \t]*;[^\n]*\n" % re.escape(v), cur, re.M)
        if not m or "ASM_" in m.group(0):
            continue
        rest = mask(cur[:m.start()] + cur[m.end():])
        if re.search(MENTION % re.escape(v), rest):
            continue
        cur = cur[:m.start()] + cur[m.end():]
    return cur


def pin_plans(new, chosen):
    """[[site...]] pin groups to erase: the window jointly, each window pin, then every pin."""
    pins = sites_of(new)
    if not pins:
        return []
    names = {s["v"] for s in chosen}
    lo = min(new.count("\n", 0, s["prod"][0]) + 1 for s in chosen) - WINDOW
    hi = max(new.count("\n", 0, s["idiom"][1]) + 2 for s in chosen)
    win = [p for p in pins if lo <= p[5] <= hi or names_var(p, names)]
    plans = ([win] if len(win) > 1 else []) + [[p] for p in win]
    if len(pins) > len(win):
        plans.append(pins)
    return plans


class T:
    name = "t91_absfresh"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        if not sites(text):
            return "no conditional negate with a single producing assignment"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        found = sites(text)
        pins_in = len(sites_of(text))
        info = {"sites": len(found), "pins_in": pins_in, "pins_out": pins_in}
        if not found:
            return None, dict(info, refused="no site")
        shapes = []
        if len(found) > 1:
            shapes.append(("joint", found, True, True))
            shapes.append(("joint-persite-decl", found, False, True))
        for i, s in enumerate(found):
            shapes.append(("single%d" % i, [s], False, True))
        if any(s["decl"] and s["decl"][3] in NARROW for s in found):
            shapes.append(("narrow", found, True, False))
        cands, seen = [], set()
        for label, chosen, grouped, widen in shapes:
            base = rewrite(text, chosen, grouped=grouped, widen=widen)
            if base is None:                             # two sites' spans overlap: not offerable
                continue
            for tag, new in (("", base), ("-nodecl", drop_decls(base, chosen))):
                if tag and new == base:
                    continue
                for group in pin_plans(new, chosen):
                    cand = erase_many(new, group, clean_notes=True)
                    out = len(sites_of(cand))
                    if out >= pins_in or cand in seen:
                        continue
                    seen.add(cand)
                    cands.append((out, len(cands), "%s%s-erase%d" % (label, tag, len(group)), cand))
        cands.sort(key=lambda c: (c[0], c[1]))
        target, listings, ranked = screen.compile_s(row, text), 0, []
        for out, order, label, cand in cands:
            if listings >= MAX_LISTINGS:
                ranked.append((out, MAX_LISTINGS, order, label, cand))
                continue
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue                                  # does not build: never worth a scorer run
            d = screen.sdiff(target, lst)
            ranked.append((out, 0 if d is None else d, order, label, cand))
        ranked.sort(key=lambda c: (c[0], c[1], c[2]))
        tried = 0
        for out, d, order, label, cand in ranked:
            if tried >= MAX_VERIFY:
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step=label, pins_out=out, dist=d, tried=tried,
                                  listings=listings, cands=len(cands))
        return None, dict(info, tried=tried, listings=listings, cands=len(cands),
                          best=ranked[0][1] if ranked else None)
