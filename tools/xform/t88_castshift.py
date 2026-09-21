"""T88: a power-of-two scale spelled the other way INSIDE its cast, with the pin it stood for erased.

APPEARS     a scaling by a power of two whose left operand carries one or more casts, inside a larger
            (usually pointer-typed) expression, with a pin on the scaled variable:
                ASM_KEEP(offset_value);                 /* four lines up */
                offset_value = (void *)((s32)offset_value * 2);
            also `x = (u32)((u16)count << 2);`, `f((s32)(a->b) * 8)`.
RESOLVES    dungeon/func_8187C45C (lane r62_astra_big, `offset_value = (void *)((s32)offset_value << 1);`,
            41 -> 40 pins, byte-exact): gcc 2.x expands `y * 2^k` through expand_mult / synth_mult and
            `y << k` through expand_shift, which leave different pseudos and copies before allocation, so
            the spelling alone decides a lifetime or a schedule a pin was holding - here the position of
            the neighbouring owner-sprite load (erasing the keep without the respelling costs 2 listing
            lines).  This is t35_shiftspell's mechanism on the operand shape t35 cannot express: t35's
            flip parenthesises the BARE variable and leaves the casts outside it, turning
            `(void *)((s32)offset_value * 2)` into `(void *)((s32)(offset_value << 1))` - a shift of a
            `void *`, which does not even compile, so t35 never offered this row a candidate.  Extending
            the operand leftwards over its casts also makes the site an enclosed one, so the replacement
            needs no parentheses of its own and reads as the original C would have been written.
POPULATION  2026-09-21, 1,141 pinned rows: 50 rows carry a cast-scaled power of two (24 multiply sites,
            50 shift sites).
CANDIDATES  per flipped site (multiply -> shift and, for a whole operand, shift -> multiply), the pins of
            the statement's window erased one at a time, then the pins naming the scaled variable, then
            the window jointly; every text is screened by its cc1 listing against the pinned text's and
            only listing-exact ones reach `vf` (at most six a row), as t74 does.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    import screen

POW = {2 ** k: k for k in range(1, 16)}
CAST = r"(?:\(\s*(?:const\s+|volatile\s+|unsigned\s+|signed\s+|struct\s+|union\s+)*[A-Za-z_]\w*" \
       r"(?:\s+(?:int|long|char))*\s*\**\s*\)\s*)"
OPND = r"[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*\[[^\[\]]*\])*"
MUL_RE = re.compile(r"(?P<c>%s+)(?P<y>%s)\s*\*\s*(?P<k>0x[0-9A-Fa-f]+|\d+)\b(?!\s*[\[(])" % (CAST, OPND))
SHL_RE = re.compile(r"(?P<c>%s+)(?P<y>%s)\s*<<\s*(?P<k>\d+)\b" % (CAST, OPND))
WINDOW = 6
MAX_SITES = 4
MAX_LISTINGS = 120
MAX_VERIFY = 6


def statement_at(masked, pos):
    """(start, end, assigned variable or None) of the statement holding `pos`."""
    a = max(masked.rfind(";", 0, pos), masked.rfind("{", 0, pos), masked.rfind("}", 0, pos)) + 1
    b = masked.find(";", pos)
    m = re.match(r"\s*(?:\(\s*)?([A-Za-z_]\w*)\s*\)?\s*(?:[-+*/|&^]|<<|>>)?=(?!=)", masked[a:b])
    return a, b, (m.group(1) if m else None)


def enclosed(masked, a, b):
    """True when the whole span already stands alone: `((s32)y * 2)`, `= (s32)y * 2;`, `f((s32)y * 2)`."""
    lead = masked[:a].rstrip()[-1:]
    tail = masked[b:].lstrip()[:1]
    return lead in ("(", "=", ",") and tail in (")", ";", ",")


def flips(text):
    """[(start, end, replacement, statement span, assigned variable, scaled variable)] - cast-scaled sites.

    The operand is taken WITH its casts, which is what t35_shiftspell cannot do."""
    masked, out = mask_comments(text), []
    pins = [(s[3], s[4]) for s in sites_of(text)]
    for rx, to_shift in ((MUL_RE, True), (SHL_RE, False)):
        for m in rx.finditer(masked):
            k = int(m.group("k"), 0)
            if to_shift and k not in POW:
                continue
            if not to_shift and not 1 <= k <= 15:
                continue
            if any(x <= m.start() < y for x, y in pins):
                continue
            body = "%s%s %s %d" % (m.group("c"), m.group("y"), "<<" if to_shift else "*",
                                   POW[k] if to_shift else 2 ** k)
            rep = body if enclosed(masked, m.start(), m.end()) else "(" + body + ")"
            a, b, x = statement_at(masked, m.start())
            out.append((m.start(), m.end(), rep, (a, b), x, m.group("y")))
    return out


def line_of(text, pos):
    return text.count("\n", 0, pos) + 1


def plans(cand, line, names):
    """[(label, [sites])] - the pin groups to erase: singly in the window, the named ones, the window."""
    sites = sites_of(cand)
    win = [s for s in sites if line - WINDOW <= s[5] <= line + WINDOW]
    named = [s for s in sites if any(re.search(r"\b%s\b" % re.escape(n), cand[s[3]:s[4]]) for n in names)]
    out, seen = [], set()
    for label, g in [("one%d" % k, [s]) for k, s in enumerate(win)] + \
            [("named", named), ("win", win)]:
        key = tuple(s[3] for s in g)
        if not g or key in seen:
            continue
        seen.add(key)
        out.append((label, g))
    return out


def candidates(text):
    """[(label, text)] - every flip with one pin group erased, textual only (deduplicated)."""
    out, seen = [], set()
    for s0, s1, rep, span, x, y in flips(text)[:MAX_SITES]:
        base = text[:s0] + rep + text[s1:]
        if unscored_text(base) != unscored_text(text):
            continue
        line = line_of(base, s0)
        names = [n for n in (x, y.split("->")[0].split(".")[0].split("[")[0]) if n]
        for label, group in plans(base, line, names):
            cand = erase_many(base, group, clean_notes=True)
            if len(sites_of(cand)) < len(sites_of(text)) and unscored_text(cand) == unscored_text(text) \
                    and cand not in seen:
                seen.add(cand)
                out.append(("%s->%s|%s" % (text[s0:s1].strip(), rep.strip(), label), cand))
    return out


class T:
    name = "t88_castshift"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not flips(text):
            return "no cast-scaled power of two"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no flip whose window holds a removable pin"]}
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"]}
        ranked, listings, best = [], 0, None
        for label, cand in cands:
            if listings >= MAX_LISTINGS:
                break
            listings += 1
            d = screen.sdiff(target, screen.compile_s(row, cand))
            if d is None:
                continue
            best = d if best is None else min(best, d)
            ranked.append((d, len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda r: (r[0], r[1]))
        tried = 0
        for d, out, label, cand in ranked:
            if d or tried >= MAX_VERIFY:
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, {"label": label, "listings": listings, "tried": tried, "best_d": 0,
                              "pins_in": len(sites_of(text)), "pins_out": out}
        return None, {"listings": listings, "tried": tried, "best_d": best,
                      "pins_in": len(sites_of(text)), "pins_out": len(sites_of(text))}
