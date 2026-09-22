"""T71: loop-carried updates moved after the call they precede, and the pin near the call erased.

APPEARS     `v += k;`, `v++;`, `v = (T *)v + k;` on a local, just before a call statement that never names v,
            with a keep or register pin holding retail's order around the call:
                source_arg = source;
                ASM_KEEP(source_arg);
                angle_offset = ((S *)cursor)->unk_1A;
                cursor += 2;
                entry_angle = entry_index << 0x11;
                entry_index += 1;
                func_80024610(source_arg, target, context, radius, ..., entry_angle >> 0x10);
RESOLVES    the round-57 `move` placement probe (dungeon/func_818B1334, func_818B11B4, func_818B1484, byte-exact
            at their recorded recipes).  Mechanism, from gcc 2.7.2 sched.c: the old list scheduler fills each
            block in reverse and breaks priority ties by original insn order (rank_for_schedule -> INSN_LUID);
            every insn between two calls that touches a call-clobbered register ties at the call's priority,
            so the stream order decides.  A pseudo that already crosses a call carries no dependence on the
            call (sched_analyze_1: reg_n_calls_crossed), so the first scheduling pass hoists an increment
            written AFTER the call above it - and the argument loads then land where retail has them.  The
            decompiler had written the increments before the call, and the pin was holding the order.
CANDIDATES  per call site (nearest the function end first): every movable update moved after the call, then
            each single one; for each, the pins within the window (two lines above the topmost update to the
            line after the call) erased jointly, then singly; then the whole function's pins jointly.  A move
            is admissible only when v is a local or parameter (declared in the function, never address-taken,
            not volatile), the update's operand is a constant or a name not written in between, and nothing
            between the update and the end of the call statement names v.  Sole-body statements of an unbraced
            if/else/for/while are never moved.  `vf` decides everything else.
SECOND LIST round 67's move table names four rows where the statement that crosses the call is a PLAIN
            assignment, not an update: dungeon/func_80FB5398 (`vertex_bytes = ((u8 *)vertex_base) + 24;`
            sunk below func_800DBA90, ASM_KEEP_MEM_NV), func_8191CD78 (`index = 1;` below func_800BCB04),
            func_800BFE94, and dungeon/func_80A20A28 of the round-72 table (five setup statements sunk).
            The note that round wrote is the shape this follows: widening `UPDATE` would change the site
            list of EVERY row (`sites_in(text)[-8:]`) and could displace a site that already pays, so the
            plain form is a SEPARATE list (`plain_sites_in`) over the calls that have NO classic update
            above them, with its own site and trial budget, consulted only after the classic phase has
            asked the verifier its own questions in its own order.
            A plain statement is movable only when it reads NO memory (its right-hand side, casts
            removed, holds no `*`, `->` or `[`), calls nothing, and names only locals that neither the
            statements in between nor the call itself write - a call may change memory and globals, so
            nothing that could see the change is moved across it.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions

MAX_SITES = 8
MAX_TRIALS = 40
PLAIN_SITES = 4                    # the second list's own site budget (round 67's note)
PLAIN_TRIALS = 24                  # ... and its own verifier budget, spent after the classic phase
SCAN_LINES = 24                    # how far above a call the second list looks for a plain statement
KEYWORDS = {"if", "for", "while", "do", "return", "goto", "switch", "case", "default", "break", "continue",
            "else", "sizeof"}
UPDATE = [re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*(?:\+\+|--)\s*;\s*$"),
          re.compile(r"^(?P<ind>[ \t]*)(?:\+\+|--)\s*(?P<v>[A-Za-z_]\w*)\s*;\s*$"),
          re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*[-+]=\s*(?P<k>-?\w+)\s*;\s*$"),
          re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*=\s*(?:\(\s*[A-Za-z_][\w \t\*]*\)\s*)?(?P=v)\s*[-+]\s*(?P<k>-?\w+)\s*;\s*$")]
PLAIN = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*=\s*(?P<rhs>[^;=][^;]*?)\s*;\s*$")
CAST_RE = re.compile(r"\(\s*[A-Za-z_][\w \t]*\**\s*\)")
CALL_START = re.compile(r"^(?P<ind>[ \t]*)(?:(?:[A-Za-z_][\w\.\->\[\]]*)\s*=\s*)?(?:\(\s*[A-Za-z_][\w \t\*]*\)\s*)?"
                        r"(?P<f>[A-Za-z_]\w*)\s*\(")
CONTROL_TAIL = re.compile(r"^[ \t]*(?:(?:else\s+)?if\b|else\b|for\b|while\b|do\b)")


def decl_names(masked_body):
    """Names declared in a function body (register/const allowed; volatile declarations excluded)."""
    names, vol = set(), set()
    for m in re.finditer(r"^[ \t]*(?P<q>(?:(?:register|const|volatile|static|unsigned|signed|struct|union|enum)[ \t]+)*)"
                         r"[A-Za-z_]\w*(?:[ \t]+long)?[ \t]*\**[ \t]*(?P<rest>[A-Za-z_]\w*(?:[ \t]*\[[^\]]*\])?"
                         r"(?:[ \t]*ASM_REG\([^()]*\))?(?:[ \t]*=[^;]*)?(?:[ \t]*,[ \t]*\**[ \t]*[A-Za-z_]\w*(?:[ \t]*\[[^\]]*\])?(?:[ \t]*=[^;]*)?)*)[ \t]*;",
                         masked_body, re.M):
        if re.match(r"[ \t]*(?:return|goto|else)\b", m.group(0)):
            continue
        for part in m.group("rest").split(","):
            n = re.match(r"[ \t\*]*([A-Za-z_]\w*)", part)
            if n:
                (vol if "volatile" in m.group("q") or "static" in m.group("q") else names).add(n.group(1))
    return names - vol


def statement_end(lines, i):
    """Index of the line that closes the statement starting at line i (paren balance, then ';'), or None."""
    depth = 0
    for j in range(i, min(len(lines), i + 12)):
        depth += lines[j].count("(") - lines[j].count(")")
        if depth <= 0 and lines[j].rstrip().endswith(";"):
            return j
        if depth <= 0 and j > i and not lines[j].strip():
            return None
    return None


def sites_in(text):
    """[(call_first, call_last, [(upd_line, v)], indent)] per admissible call statement."""
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
            if j is None or not re.search(r"\)\s*;\s*$", mlines[j]):
                continue
            ind = cm.group("ind")
            call_text = "\n".join(mlines[i:j + 1])
            updates, k = [], i - 1
            while k > first:
                ln = mlines[k]
                if not ln.strip():
                    k -= 1
                    continue
                um = next((u.match(ln) for u in UPDATE if u.match(ln)), None)
                if um is None:
                    if re.match(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(", ln) or (ln.rstrip().endswith(";") and ln.startswith(ind)
                                                                      and not CONTROL_TAIL.match(ln) and "{" not in ln
                                                                      and "}" not in ln and not re.match(r"^[ \t]*\w+\s*:", ln)):
                        k -= 1                                             # an ordinary statement: look above it
                        continue
                    break
                if um.group("ind") != ind:
                    break
                v = um.group("v")
                above = next((mlines[q] for q in range(k - 1, first, -1) if mlines[q].strip()), "")
                if CONTROL_TAIL.match(above) and not above.rstrip().endswith(("{", ";")):
                    break                                                  # sole body of an unbraced control
                between = "\n".join(x for x in mlines[k + 1:i] if not re.match(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(", x))
                ok = (v in locals_ and v not in taken and v not in KEYWORDS
                      and not re.search(r"\b%s\b" % re.escape(v), between)
                      and not re.search(r"\b%s\b" % re.escape(v), call_text))
                kk = um.groupdict().get("k")
                if ok and kk and not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", kk):
                    ok = kk in locals_ and kk not in taken and not re.search(
                        r"(?<![\w.>])%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)|(?:\+\+|--)\s*%s\b|\b%s\s*(?:\+\+|--)"
                        % ((re.escape(kk),) * 3), between + "\n" + call_text)
                if ok:
                    updates.append((k, v))
                k -= 1
            if updates:
                out.append((i, j, sorted(updates), ind))
    return out


def _writes(name):
    return re.compile(r"(?<![\w.>])%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)|(?:\+\+|--)\s*%s\b|\b%s\s*(?:\+\+|--)"
                      % ((re.escape(name),) * 3))


def plain_sites_in(text):
    """[(call_first, call_last, [(line, v)], indent)] for calls with NO classic update above them.

    The classic list is recomputed, never changed: a call it already owns is skipped here, so the
    sites this returns are disjoint from `sites_in`'s and the order of the classic phase's verifier
    calls is exactly what it was before this list existed.
    """
    masked = mask_comments(text)
    mlines, out = masked.split("\n"), []
    classic = {s[0] for s in sites_in(text)}
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body) | {p for p, _, _, _ in params}
        taken = set(re.findall(r"&\s*([A-Za-z_]\w*)", body))
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first + 1, last):
            if i in classic:
                continue
            cm = CALL_START.match(mlines[i])
            if not cm or cm.group("f") in KEYWORDS or "ASM_" in mlines[i]:
                continue
            j = statement_end(mlines, i)
            if j is None or not re.search(r"\)\s*;\s*$", mlines[j]):
                continue
            ind = cm.group("ind")
            call_text = "\n".join(mlines[i:j + 1])
            moves, k = [], i - 1
            while k > first and i - k <= SCAN_LINES and len(moves) < 6:
                ln = mlines[k]
                if not ln.strip() or re.match(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(", ln):
                    k -= 1
                    continue                                          # blank, or a pin: look above it
                pm = PLAIN.match(ln)
                if pm is None or pm.group("ind") != ind:
                    # the statement the round-57 list walks over: an ordinary one at this indent is
                    # not a candidate but does not end the scan (dungeon/func_8191CD78's `index = 1;`
                    # stands twelve statements above its call)
                    if ln.rstrip().endswith(";") and ln.startswith(ind) and not CONTROL_TAIL.match(ln) \
                            and "{" not in ln and "}" not in ln and not re.match(r"^[ \t]*\w+\s*:", ln):
                        k -= 1
                        continue
                    break
                v, rhs = pm.group("v"), pm.group("rhs")
                above = next((mlines[q] for q in range(k - 1, first, -1) if mlines[q].strip()), "")
                if CONTROL_TAIL.match(above) and not above.rstrip().endswith(("{", ";")):
                    break                                             # sole body of an unbraced control
                bare = CAST_RE.sub(" ", rhs)
                ops = set(re.findall(r"[A-Za-z_]\w*", bare))
                between = "\n".join(x for x in mlines[k + 1:i]
                                    if not re.match(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(", x))
                ok = (v in locals_ and v not in taken and v not in KEYWORDS
                      and not re.search(r"[A-Za-z_]\w*[ \t]*\(", rhs)          # no call on the right
                      and not re.search(r"[\*\[]|->", bare)                     # and no memory read
                      and ops <= locals_ and not (ops & taken)
                      and not re.search(r"\b%s\b" % re.escape(v), between)
                      and not re.search(r"\b%s\b" % re.escape(v), call_text)
                      and all(not _writes(o).search(between + "\n" + call_text) for o in ops))
                if ok:
                    moves.append((k, v))
                k -= 1
            if moves:
                out.append((i, j, sorted(moves), ind))
    return out


def rewrite(text, site, chosen):
    """The chosen update lines moved after the call statement (order kept)."""
    i, j, _, ind = site
    lines = text.split("\n")
    moved = [lines[k] for k, _ in chosen]
    keep = [ln for k, ln in enumerate(lines) if k not in {c[0] for c in chosen}]
    j2 = j - sum(1 for k, _ in chosen if k < j)
    return "\n".join(keep[:j2 + 1] + moved + keep[j2 + 1:])


def window_pins(text, lo, hi):
    return [s for s in sites_of(text) if lo <= s[5] <= hi]


class T:
    name = "t71_updateaftercall"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        if sites_in(text):
            return None
        # a row with no classic update is still this generator's when the SECOND list sees a plain
        # statement above a call; rows the classic list already owns are unaffected
        return None if plain_sites_in(text) else "no movable update before a call"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, tried, steps, cur = len(sites_of(text)), 0, [], text
        sites = sites_in(text)[-MAX_SITES:]
        for site in reversed(sites):
            live = [s for s in sites_in(cur) if s[0] == site[0] or (s[1] - s[0]) == (site[1] - site[0]) and
                    cur.split("\n")[s[0]] == text.split("\n")[site[0]]]
            if not live:
                continue
            site = live[-1]
            i, j, updates, _ = site
            plans = [("all", updates)] + ([("u%d" % k, [u]) for k, u in enumerate(updates)] if len(updates) > 1 else [])
            done = False
            for label, chosen in plans:
                moved = rewrite(cur, site, chosen)
                lo, hi = min(k for k, _ in chosen) - 1, j + 2                # 1-based pin lines: window around the run
                pins, fn_pins = window_pins(moved, lo, hi), sites_of(moved)
                trials, seen = [], set()
                for g in ([pins] if len(pins) > 1 else []) + [[p] for p in pins] + [fn_pins]:
                    key = tuple(s[3] for s in g)
                    if g and key not in seen:
                        seen.add(key); trials.append(g)
                for group in trials:
                    if tried >= MAX_TRIALS:
                        break
                    cand = erase_many(moved, group, clean_notes=True)
                    if len(sites_of(cand)) >= len(sites_of(cur)):
                        continue
                    tried += 1
                    if vf(cand).get("exact"):
                        cur, done = cand, True
                        steps.append("%s:%s-%d" % (label, "fn" if group is fn_pins else "win", len(group)))
                        break
                if done:
                    break
        # the SECOND list, after the classic phase and with budgets of its own
        ptried, psites = 0, plain_sites_in(cur)[-PLAIN_SITES:]
        for site in reversed(psites):
            if ptried >= PLAIN_TRIALS:
                break
            live = [s for s in plain_sites_in(cur) if s[0] == site[0]]
            if not live:
                continue
            site = live[-1]
            i, j, moves, _ = site
            plans = [("pall", moves)] + ([("p%d" % k, [u]) for k, u in enumerate(moves)]
                                         if len(moves) > 1 else [])
            done = False
            for label, chosen in plans:
                moved = rewrite(cur, site, chosen)
                lo, hi = min(k for k, _ in chosen) - 1, j + 2
                pins, fn_pins = window_pins(moved, lo, hi), sites_of(moved)
                trials, seen = [], set()
                for g in ([pins] if len(pins) > 1 else []) + [[p] for p in pins] + [fn_pins]:
                    key = tuple(x[3] for x in g)
                    if g and key not in seen:
                        seen.add(key); trials.append(g)
                for group in trials:
                    if ptried >= PLAIN_TRIALS:
                        break
                    cand = erase_many(moved, group, clean_notes=True)
                    if len(sites_of(cand)) >= len(sites_of(cur)):
                        continue
                    ptried += 1
                    if vf(cand).get("exact"):
                        cur, done = cand, True
                        steps.append("%s:%s-%d" % (label, "fn" if group is fn_pins else "win", len(group)))
                        break
                if done:
                    break
        tried += ptried
        if not steps:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in,
                          "sites": len(sites), "psites": len(psites)}
        return cur, {"step": "+".join(steps), "tried": tried, "pins_in": pins_in, "pins_out": len(sites_of(cur)),
                     "sites": len(sites), "psites": len(psites)}
