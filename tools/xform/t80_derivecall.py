"""T80: a derived value assigned just AFTER a call moved to just BEFORE it, so its pseudo crosses the call.

APPEARS     a PURE derived assignment to a local - `p = base + 0x20;`, `p = (u8 *)&D_80083160;`,
            `p = (T *)base;` - in the first few statements after a call statement, with a pin on p
            (an ASM_REG on its declaration, a keep naming it) or a pin in that window:
                func_8004491C(object, &D_80045340);
                render_flags = ((S_801715D0_1 *)object)->unk_0C;
                object_state = object + 0x20;            <- register ... ASM_REG("$19")
RESOLVES    the round-59 sol lanes: dungeon/func_8133A5D0 (r59_sol_large7 - `object_state = object + 0x20;`
            moved above `func_8004491C(...)`, the `$19` ASM_REG dropped) and dungeon/func_818ED25C
            (r59_sol_mid5 - `page_ptr = (u8 *)&D_80083160;` moved above `func_80067E2C(...)`, the `$18`
            ASM_REG dropped; with the split shift pair `call_param = (s32)((u32)saved_param << 16); ...
            call_param >>= 16;` merged into one statement the `ASM_KEEP_NV` goes too, 2 pins -> 0).
            Mechanism, gcc 2.7.2: a pseudo that is live across a call gets `reg_n_calls_crossed` set
            (flow.c), so global.c prefers a callee-saved hard register for it, and sched.c's first pass -
            which has no dependence tying such a pseudo to the call (sched_analyze_1) - leaves its setup
            insn where retail has it, above the argument loads.  Written after the call the pseudo never
            crosses it, is coloured from the call-clobbered set and the pin was holding the colour.
            This is the mirror of t71_updateaftercall, which moves loop updates the other way.
CANDIDATES  per call site, nearest the function end first: each admissible derived assignment moved to
            immediately before the call statement, and one statement further up (2 slots); each slot
            alone and composed with a merged shift pair (`v = E; [stmts]; v >>= k;` -> `v = E >> k;`,
            only when E's outer cast spells v's declared type); with the pins naming p erased, the window
            pins jointly, then singly, then the function's pins jointly.  Every candidate is screened with
            `screen.compile_s` against the pinned listing; listing-exact candidates reach `vf` best
            (most pins removed) first, and where a site has none the nearest candidate within NEAR
            still gets one scorer run (the screen ranks, it does not prove), at most MAX_VERIFY a row.  A move is admissible only when p is a
            local or parameter never address-taken, the expression is pure (locals, parameters, constants,
            `&symbol`, casts, pointer arithmetic - no dereference, no call, no `++`/`--`), p is not named
            between the call and the assignment nor in the call statement, and no operand is written by
            the call statement or by a statement in between.  Sole-body statements of an unbraced
            if/else/for/while are never moved and never moved onto (t71's rule).
SECOND STEP a bounded second step runs only where the first found nothing listing-exact at a site and
            its best listing distance is within NEAR2: the assignment moved DOWN past 1..MAX_DOWN of
            the statements that follow it (dungeon/func_800C9858 - `quad = (u8 *)&D_801E7C00;` written
            three statements later, the `ASM_KEEP_MEM_NV` gone, 36 -> 35 pins), then 2..MAX_UP
            statements further UP, then the pinned assignment moved JOINTLY with a second derived
            assignment of the same call site (relative order kept, so each statement crosses exactly
            what it crossed alone).  The DOWN move (`d0` is the assignment left where it is, only the
            pin group erased) runs whenever the first step found nothing listing-exact; the further-UP
            and joint moves only when the first step's best distance is within NEAR2, since the near
            band measured them out.  Measured on the round-60 near band (77 rows whose best distance
            was <= 4): the residual is a single instruction in a different slot (45 rows, the same
            multiset) or one instruction fewer than retail (10 rows, two equal constants the candidate
            shares and retail materialises twice), and the up-move itself is listing-neutral on 74 of
            them - the down move is the one of these steps that reaches a byte-exact row.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t72_stmtperm import decl_names
    from .t16_absidiom import names_var
    from .t71_updateaftercall import statement_end, CALL_START, CONTROL_TAIL, KEYWORDS
    from .t74_multiset import top_ops
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t72_stmtperm import decl_names
    from t16_absidiom import names_var
    from t71_updateaftercall import statement_end, CALL_START, CONTROL_TAIL, KEYWORDS
    from t74_multiset import top_ops
    import screen

MAX_SITES = 6
MAX_AFTER = 8            # statements after the call that are scanned for the derived assignment
MAX_MERGES = 2
MERGE_SPAN = 10          # lines a split shift pair may straddle
MAX_LISTINGS = 600
MAX_VERIFY = 6
NEAR = 2                 # listing distance still worth one scorer run when nothing is listing-exact
NEAR2 = 6                # best distance of the first step that still earns the second step
MAX_DOWN = 4             # statements the assignment may be moved DOWN past (the second step)
MAX_UP = 3               # slots above the call the assignment may be moved to (the second step)

ASSIGN = re.compile(r"^(?P<ind>[ \t]*)(?P<p>[A-Za-z_]\w*)\s*=(?!=)\s*(?P<e>[^;{}]+);[ \t]*$")
CAST = re.compile(r"\(\s*(?:(?:const|volatile|unsigned|signed|struct|union|enum)\s+)*"
                  r"(?P<t>[A-Za-z_]\w*)(?:\s+(?:int|long|char))?\s*(?P<st>\**)\s*\)")
WRITE = re.compile(r"(?<![\w.>])([A-Za-z_]\w*)\s*(?:[-+*/%&|^]|<<|>>)?=(?!=)"
                   r"|(?<![\w.>])([A-Za-z_]\w*)\s*(?:\+\+|--)|(?:\+\+|--)\s*([A-Za-z_]\w*)")
DECL_LINE = re.compile(r"^[ \t]*(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*"
                       r"[A-Za-z_]\w*(?:[ \t]+(?:int|long|char))?(?:[ \t]*\*+[ \t]*|[ \t]+\*?)[A-Za-z_]\w*[ \t]*(?:\[|=[^=]|;|,)")
LABEL = re.compile(r"^[ \t]*(?:#|[A-Za-z_]\w*[ \t]*:(?!:))")
JUMP = re.compile(r"^[ \t]*(?:return|goto|break|continue)\b")
PIN_LINE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
UNARY_AMP = re.compile(r"(?:^|[(,+\-|^*/%<>=&])\s*&\s*$")
SHIFT_DROP = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*>>=\s*(?P<k>-?\w+)\s*;[ \t]*$")


def written_names(s):
    """Every name the statement text assigns to, increments or decrements."""
    return {g for m in WRITE.finditer(s) for g in m.groups() if g}


def blank_casts(e, locals_):
    """`e` with every cast blanked out (a parenthesised local is not a cast)."""
    out = e
    for m in reversed(list(CAST.finditer(e))):
        if m.group("t") in locals_ and not m.group("st"):
            continue
        out = out[:m.start()] + " " * (m.end() - m.start()) + out[m.end():]
    return out


def pure_expr(e, locals_, taken):
    """The set of local operands of a pure derived expression, or None if it is not one."""
    b = blank_casts(e, locals_)
    if re.search(r"->|\[|\]|\.|\*|\?|,|&&|\|\||!|=|\+\+|--|/|%|~", b):
        return None
    if re.search(r"[A-Za-z_]\w*[ \t]*\(", b):
        return None
    out = set()
    for m in re.finditer(r"(?<![\w.$])([A-Za-z_]\w*)", b):
        if UNARY_AMP.search(b[:m.start()]):
            continue                                  # `&symbol`: a link-time constant (a BINARY
                                                      # `&` is a read of the symbol, and refuses)
        n = m.group(1)
        if n in taken or n not in locals_:
            return None
        out.add(n)
    return out


def prev_stmt_line(mlines, i, first):
    """Index of the single-line ordinary statement right above line i, or None."""
    k = i - 1
    while k > first and not mlines[k].strip():
        k -= 1
    if k <= first:
        return None
    ln = mlines[k]
    if ("{" in ln or "}" in ln or CONTROL_TAIL.match(ln) or LABEL.match(ln) or JUMP.match(ln)
            or PIN_LINE.match(ln) or DECL_LINE.match(ln) or not ln.rstrip().endswith(";")
            or ln.count("(") != ln.count(")")):
        return None
    return k


def next_stmt_line(mlines, i, last):
    """Index of the single-line ordinary statement right below line i, or None."""
    k = i + 1
    while k < last and not mlines[k].strip():
        k += 1
    if k >= last:
        return None
    ln = mlines[k]
    if ("{" in ln or "}" in ln or CONTROL_TAIL.match(ln) or LABEL.match(ln) or JUMP.match(ln)
            or PIN_LINE.match(ln) or DECL_LINE.match(ln) or not ln.rstrip().endswith(";")
            or ln.count("(") != ln.count(")")):
        return None
    return k


def sole_body_above(mlines, i, first):
    """Is line i the sole (unbraced) body of a control statement just above it?"""
    k = i - 1
    while k > first and not mlines[k].strip():
        k -= 1
    ln = mlines[k] if k > first else ""
    return bool(CONTROL_TAIL.match(ln)) and not ln.rstrip().endswith(("{", ";"))


def sites_in(text):
    """[{i, j, ind, first, assigns: [(line, p, expr, operands)]}] per admissible call statement."""
    masked = mask_comments(text)
    mlines, out = masked.split("\n"), []
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body) | {p for p, _, _, _ in params}
        taken = set(re.findall(r"&\s*([A-Za-z_]\w*)", body))
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first + 1, last):
            cm = CALL_START.match(mlines[i])
            if not cm or cm.group("f") in KEYWORDS or "ASM_" in mlines[i]:
                continue
            j = statement_end(mlines, i)
            if j is None or j >= last or not re.search(r"\)\s*;\s*$", mlines[j]):
                continue
            ind = cm.group("ind")
            call_text = "\n".join(mlines[i:j + 1])
            wr, assigns, k, n = written_names(call_text), [], j + 1, 0
            while k < last and n < MAX_AFTER:
                ln = mlines[k]
                if not ln.strip():
                    k += 1
                    continue
                if ("{" in ln or "}" in ln or CONTROL_TAIL.match(ln) or LABEL.match(ln) or JUMP.match(ln)
                        or not ln.startswith(ind) or ln[len(ind):len(ind) + 1] in (" ", "\t")):
                    break
                e = statement_end(mlines, k)
                if e is None or e >= last:
                    break
                am = ASSIGN.match(ln) if e == k and not PIN_LINE.match(ln) else None
                if am and am.group("ind") == ind and not DECL_LINE.match(ln):
                    p, expr = am.group("p"), am.group("e").strip()
                    ops = pure_expr(expr, locals_, taken) if p in locals_ and p not in taken else None
                    between = "\n".join(mlines[j + 1:k])
                    if (ops is not None and p not in ops and not (ops & wr)
                            and not re.search(r"(?<![\w.>])%s\b" % re.escape(p), between + "\n" + call_text)
                            and not sole_body_above(mlines, k, first)):
                        assigns.append((k, p, expr, ops))
                wr |= written_names("\n".join(mlines[k:e + 1]))
                n += 1
                k = e + 1
            if assigns and not sole_body_above(mlines, i, first):
                out.append({"i": i, "j": j, "ind": ind, "first": first, "last": last, "assigns": assigns})
    return out


def _crossable(site, a_lines, crossed):
    """May every moved assignment cross these lines (neither its name nor an operand touched)?"""
    byline = {a[0]: a for a in site["assigns"]}
    for k in a_lines:
        _, p, _, ops = byline[k]
        for c in crossed:
            if re.search(r"(?<![\w.>])%s\b" % re.escape(p), c) or (ops & written_names(c)):
                return False
    return True


def moved_lines(text, site, a_lines, slot):
    """The assignment lines (ascending) moved to `slot` ordinary statements above the call."""
    mlines = mask_comments(text).split("\n")
    dest, crossed = site["i"], []
    for _ in range(slot):
        d = prev_stmt_line(mlines, dest, site["first"])
        if d is None:
            return None
        crossed.append(mlines[d])
        dest = d
    if not _crossable(site, a_lines, crossed) or sole_body_above(mlines, dest, site["first"]):
        return None
    lines, keep = text.split("\n"), set(a_lines)
    moved = [lines[k] for k in a_lines]                 # every a_line is BELOW dest, so dest holds
    rest = [ln for i, ln in enumerate(lines) if i not in keep]
    return "\n".join(rest[:dest] + moved + rest[dest:]), dest


def moved_text(text, site, a_line, slot):
    """The assignment line moved to slot 0 (before the call) or 1 (one statement further up)."""
    return moved_lines(text, site, [a_line], slot)


def moved_down(text, site, a_line, k):
    """The assignment line moved DOWN past k of the ordinary statements that follow it."""
    mlines = mask_comments(text).split("\n")
    dest, crossed = a_line, []
    for _ in range(k):
        d = next_stmt_line(mlines, dest, site.get("last", len(mlines)))
        if d is None:
            return None
        crossed.append(mlines[d])
        dest = d
    if not _crossable(site, [a_line], crossed):
        return None
    lines = text.split("\n")
    s = lines[a_line]
    rest = lines[:a_line] + lines[a_line + 1:]
    return "\n".join(rest[:dest] + [s] + rest[dest:]), dest


def decl_type(masked_body, v):
    """('s32', '') for `s32 v;` / `register s32 v ASM_REG(..);`, or None."""
    m = re.search(r"^[ \t]*(?:(?:register|const)[ \t]+)*(?P<ty>[A-Za-z_]\w*(?:[ \t]+(?:int|long|char))?)"
                  r"[ \t]*(?P<st>\**)[ \t]*%s[ \t]*(?:ASM_REG\([^()]*\))?[ \t]*;" % re.escape(v),
                  masked_body, re.M)
    return (re.sub(r"[ \t]+", " ", m.group("ty")), m.group("st")) if m else None


def merge_pairs(text):
    """[(label, new_text)] for each `v = E; ... v >>= k;` merged into `v = E >> k;`."""
    masked = mask_comments(text)
    mlines, out = masked.split("\n"), []
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body) | {p for p, _, _, _ in params}
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first + 1, last):
            am = ASSIGN.match(mlines[i])
            if not am or am.group("p") not in locals_ or DECL_LINE.match(mlines[i]):
                continue
            v, e = am.group("p"), am.group("e").strip()
            cm = CAST.match(e)
            ty = decl_type(body, v)
            if not cm or cm.start() or not ty or ty != (re.sub(r"[ \t]+", " ", cm.group("t")), cm.group("st")):
                continue
            for j in range(i + 1, min(i + MERGE_SPAN, last)):
                ln = mlines[j]
                if not ln.strip():
                    continue
                sm = SHIFT_DROP.match(ln)
                if sm and sm.group("v") == v and sm.group("ind") == am.group("ind"):
                    body_e = e if not top_ops(e) else "(%s)" % e
                    lines = text.split("\n")
                    new = (lines[:i] + ["%s%s = %s >> %s;" % (am.group("ind"), v, body_e, sm.group("k"))]
                           + lines[i + 1:j] + lines[j + 1:])
                    out.append(("mg%d" % (i + 1), "\n".join(new)))
                    break
                if ("{" in ln or "}" in ln or CONTROL_TAIL.match(ln) or LABEL.match(ln) or JUMP.match(ln)
                        or re.search(r"(?<![\w.>])%s\b" % re.escape(v), ln)):
                    break
    return out


def erase_plans(text, p, lo, hi):
    """Pin groups to try: naming p (one name or several), the window jointly, both, singly, all."""
    ps = {p} if isinstance(p, str) else set(p)
    pins = sites_of(text)
    onp = [s for s in pins if names_var(s, ps)]
    win = [s for s in pins if lo <= s[5] <= hi]
    both = sorted(set(onp) | set(win), key=lambda s: s[3])
    plans, seen = [], set()
    for g in [onp, win, both] + [[s] for s in both] + [pins]:
        key = tuple(s[3] for s in g)
        if g and key not in seen:
            seen.add(key)
            plans.append(g)
    return plans


class T:
    name = "t80_derivecall"
    level = 1
    needs_verify = True

    @staticmethod
    def _pinned(text, p, lo, hi):
        return any(names_var(s, {p}) or lo <= s[5] <= hi for s in sites_of(text))

    @classmethod
    def eligible(cls, text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        for site in sites_in(text):
            for a_line, p, _, _ in site["assigns"]:
                if cls._pinned(text, p, site["i"], a_line + 2):
                    return None
        return "no pinned derived assignment after a call"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        best_d = None
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        sites = sites_in(text)[-MAX_SITES:]
        for want in reversed(sites):
            want_line = text.split("\n")[want["i"]]
            live = [s for s in sites_in(cur) if cur.split("\n")[s["i"]] == want_line]
            if not live:
                continue
            site = live[-1]
            hit = False
            for a_line, p, expr, _ in site["assigns"]:
                if hit or verifies >= MAX_VERIFY or listings >= MAX_LISTINGS:
                    break
                if not cls._pinned(cur, p, site["i"], a_line + 2):
                    continue
                cands, near, seen, best = [], [], set(), [None]

                def offer(label, vtext, ps, lo, hi):
                    """Screen every pin group of one rewritten text; collect the exact and the near."""
                    nonlocal listings
                    for group in erase_plans(vtext, ps, lo, hi):
                        if listings >= MAX_LISTINGS:
                            return
                        cand = erase_many(vtext, group, clean_notes=True)
                        gone = len(sites_of(cur)) - len(sites_of(cand))
                        if gone <= 0 or cand in seen:
                            continue
                        seen.add(cand)
                        listings += 1
                        d = screen.sdiff(target, screen.compile_s(row, cand))
                        if d is not None and (best[0] is None or d < best[0]):
                            best[0] = d
                        if d == 0:
                            cands.append((gone, label, cand))
                        elif d is not None and d <= NEAR:
                            near.append((d, -gone, label, cand))

                def with_merges(label, base, dest):
                    """`base` alone and composed with the nearest merged shift pairs."""
                    offer(label, base, [p], dest, site["j"] + 3)
                    for lb, mt in sorted(merge_pairs(base),
                                         key=lambda x: abs(int(x[0][2:]) - site["i"]))[:MAX_MERGES]:
                        offer("%s+%s" % (label, lb), mt, [p], dest, site["j"] + 3)

                for slot in (0, 1):                                    # the first step
                    mv = moved_text(cur, site, a_line, slot)
                    if mv is not None:
                        with_merges("s%d" % slot, mv[0], mv[1])
                # the second step, where the first step found nothing listing-exact.  The DOWN move
                # is not gated on the first step's distance: it is a different transform, and on
                # dungeon/func_800C9858 the up-move's listing is far while `d3` is byte-exact.
                if not cands:
                    for k in range(0, MAX_DOWN + 1):                   # written further DOWN instead
                        mv = (cur, a_line) if k == 0 else moved_down(cur, site, a_line, k)
                        if mv is None:
                            break
                        offer("d%d" % k, mv[0], [p], site["i"], mv[1] + 2)
                if not cands and best[0] is not None and best[0] <= NEAR2:
                    for slot in range(2, MAX_UP + 1):                  # further UP
                        mv = moved_lines(cur, site, [a_line], slot)
                        if mv is None:
                            break
                        with_merges("s%d" % slot, mv[0], mv[1])
                    for b_line, q, _, _ in site["assigns"]:            # two pointers moved jointly
                        if b_line == a_line or listings >= MAX_LISTINGS:
                            continue
                        pair = sorted([a_line, b_line])
                        for slot in (0, 1):
                            mv = moved_lines(cur, site, pair, slot)
                            if mv is None:
                                continue
                            offer("s%d/j" % slot, mv[0], [p, q], mv[1], site["j"] + 3)
                cands.sort(key=lambda c: -c[0])
                near.sort()
                # the listing screen is a ranking heuristic, not a rejection proof (screen.py): when
                # nothing is listing-exact the nearest candidate still gets one scorer run
                for gone, label, cand in cands + [(-n[1], n[2] + "~%d" % n[0], n[3]) for n in near[:1]]:
                    if verifies >= MAX_VERIFY:
                        break
                    verifies += 1
                    if vf(cand).get("exact"):
                        cur, hit = cand, True
                        steps.append("%s@%d-%d" % (label, a_line + 1, gone))
                        break
                if best[0] is not None and (best_d is None or best[0] < best_d):
                    best_d = best[0]
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur)),
                "sites": len(sites), "best_d": best_d}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
