"""T74: a chained assignment split so its destination is set more than once (the multi-set destination).

APPEARS     `v = a + b + c;` (or `|`, `&`, `^`, `-` chains, or `(expr) << k`) near a pin; the pin holds the place of the
            chain's last instruction or the register the chain lands in.
RESOLVES    six lanes independently (alloc48, alloc22, alloc54, alloc63, alloc69, lac6; docs/PIN_LANE_RULES_AUDIT_20260919.md
            gap 1): written as `v = a + b; v += c;` the destination pseudo is set twice, `birthing_insn_p` (sched.c)
            no longer boosts its producer in the first scheduling pass and the register allocator no longer prefers a
            fresh colour for a single-set pseudo (`reg_n_sets == 1`), so the instructions stay where retail has them.
            t69_prologue uses the same fact on parameter copies only; t35_shiftspell flips one operator.
CANDIDATES  per chained assignment (nearest a pin first): the top-level operators of the lowest precedence present
            split left-to-right at each position (`v = a + b; v += c` / `v = a; v += b; v += c`), the shift form
            `v = e; v <<= k`, each screened by the cc1 listing against the pinned text with the window pins erased
            (jointly, singly) and the function's pins jointly; listing-exact texts go to `vf`.  The destination must be
            a plain local not named inside the chain, and the chain must contain no call, no assignment and no `?:`.
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
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t72_stmtperm import decl_names
    import screen

MAX_SITES = 10
MAX_LISTINGS = 400
MAX_VERIFY = 6
PREC = {"|": 1, "^": 2, "&": 3, "<<": 4, ">>": 4, "+": 5, "-": 5}
ASSIGN = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*=(?!=)\s*(?P<e>[^;{}]+);[ \t]*(?P<tail>.*)$")


def top_ops(e):
    """[(pos, op)] of the binary operators at parenthesis depth 0, unary minus and pointer arrows excluded."""
    out, depth, i, prev = [], 0, 0, ""
    while i < len(e):
        ch = e[i]
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif depth == 0:
            two = e[i:i + 2]
            if two in ("<<", ">>") and e[i:i + 3] not in ("<<=", ">>="):
                out.append((i, two)); i += 2; prev = two; continue
            if ch in "+-|&^" and e[i + 1:i + 2] not in ("=", ch if ch in "+-|&" else "") and prev.strip() and prev[-1] not in "(+-*/%&|^<>=!,":
                if not (ch == "-" and e[i + 1:i + 2] == ">"):                 # `->` is not a minus
                    out.append((i, ch))
            elif ch in "+-" and e[i + 1:i + 2] == ch:
                i += 2; prev = ch; continue
        prev = e[:i + 1].rstrip()[-1:] if e[:i + 1].strip() else ""
        i += 1
    return out


def chains(text):
    """[(line_index, v, first, [(op, operand)...], indent, tail)] for every splittable chained assignment."""
    masked = mask_comments(text)
    lines, out = text.split("\n"), []
    mlines = masked.split("\n")
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body) | {p for p, _, _, _ in params}
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first + 1, last):
            m = ASSIGN.match(mlines[i])
            if not m or m.group("v") not in locals_:
                continue
            e = m.group("e").strip()
            if re.search(r"\w\s*\(|\?|=(?!=)|\+\+|--", re.sub(r"\(\s*[A-Za-z_][\w \t\*]*\)", "", e)) or re.search(r"\b%s\b" % re.escape(m.group("v")), e):
                continue
            ops = top_ops(e)
            if not ops:
                continue
            low = min(PREC[o] for _, o in ops)
            cut = [(p, o) for p, o in ops if PREC[o] == low]
            if not cut or (low == 4 and len(cut) != 1):
                continue
            parts, pos = [], 0
            for p, o in cut:
                parts.append(e[pos:p].strip()); pos = p + len(o)
            parts.append(e[pos:].strip())
            if any(not x for x in parts):
                continue
            out.append((i, m.group("v"), parts[0], list(zip([o for _, o in cut], parts[1:])), m.group("ind"), lines[i][len(m.group("ind")) + len(mlines[i].rstrip()) - len(m.group("ind")):] if False else ""))
    return out


def splits(chain):
    """Texts of the statement split after k operators, k = 1 .. n-1 (and fully), as lists of lines."""
    i, v, first, rest, ind, _ = chain
    outs = []
    for k in range(1, len(rest) + 1):
        head = first + "".join(" %s %s" % (o, x) for o, x in rest[:len(rest) - k])
        lines = [ind + "%s = %s;" % (v, head)] + [ind + "%s %s= %s;" % (v, o, x) for o, x in rest[len(rest) - k:]]
        outs.append(("split%d" % k, lines))
    return outs


class T:
    name = "t74_multiset"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if chains(text) else "no chained assignment to a local"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        import difflib
        pin_lines = [s[5] - 1 for s in sites_of(text)]
        cands = sorted(chains(text), key=lambda c: min(abs(c[0] - p) for p in pin_lines))[:MAX_SITES]
        for chain in cands:
            live = [c for c in chains(cur) if c[1] == chain[1] and c[2] == chain[2] and c[3] == chain[3]]
            if not live:
                continue
            chain = live[0]
            i = chain[0]
            found = False
            for label, new_lines in splits(chain):
                ls = cur.split("\n")
                moved = "\n".join(ls[:i] + new_lines + ls[i + 1:])
                pins = sites_of(moved)
                near = sorted(pins, key=lambda s: abs(s[5] - 1 - i))[:6]
                plans = ([near] if len(near) > 1 else []) + [[p] for p in near] + ([pins] if len(pins) > len(near) else [])
                for group in plans:
                    if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                        break
                    cand = erase_many(moved, group, clean_notes=True)
                    if len(sites_of(cand)) >= len(sites_of(cur)):
                        continue
                    lst = screen.compile_s(row, cand); listings += 1
                    if lst is None:
                        continue
                    d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))
                    if d:
                        continue
                    verifies += 1
                    if vf(cand).get("exact"):
                        cur, found = cand, True
                        steps.append("%s@%d-erase%d" % (label, i + 1, len(group)))
                        break
                if found:
                    break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur)), "chains": len(cands)}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
