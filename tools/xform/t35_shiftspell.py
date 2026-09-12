"""T35: a power-of-two scale spelled the other way (`y * 8` <-> `y << 3`), with the pin it stood for erased.

APPEARS     a statement scaling an integer by a power of two, `x = y * 8;` or `x = y << 3;` (also inside
            a larger expression), whose assigned variable or operand carries a pin.
RESOLVES    gcc 2.x expands `y * 2^k` through expand_mult / synth_mult and `y << k` through
            expand_shift; the two leave different pseudos and copies before allocation, so the
            spelling alone decides a lifetime or allocation choice a pin (or a fake dead store) was
            emulating. fakedep2 lane, 2026-09-12: dungeon/func_81812008 `start_entry = entry_index << 3`
            (ASM_KEEP(start_entry) off), town/func_800AB548 `double_phase = offset_phase << 1`
            (ASM_REG("$16") off) - both byte-exact where the dead-store fake had been.
POPULATION  2026-09-12 pinned functions: 285 with `y * 2^k` (647 sites), 504 with `y << k` (1,600).

Each candidate flips ONE site and erases the pins of the statement's assigned variable, of the
operand, or of both. A multiply becomes a parenthesised shift unless it is a whole right-hand side;
a shift becomes a multiply only when it is a whole operand (so precedence never changes). Only
integer scaling by 2..2^15 is touched; division is left to t17.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

POW = {2 ** k: k for k in range(1, 16)}
OPND = r"[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*|\s*\[[^\[\]]*\])*"
MUL_RE = re.compile(r"(?P<y>%s)\s*\*\s*(?P<c>0x[0-9A-Fa-f]+|\d+)\b(?!\s*[\[(])" % OPND)
SHL_RE = re.compile(r"(?P<y>%s)\s*<<\s*(?P<k>\d+)\b" % OPND)
MAX_CANDS = 24


def statement_at(masked, pos):
    """(start, end, assigned variable or None) of the statement holding `pos`."""
    a = max(masked.rfind(";", 0, pos), masked.rfind("{", 0, pos), masked.rfind("}", 0, pos)) + 1
    b = masked.find(";", pos)
    s = masked[a:b]
    m = re.match(r"\s*(?:\(\s*)?([A-Za-z_]\w*)\s*\)?\s*(?:[-+*/|&^]|<<|>>)?=(?!=)", s)
    return a, b, (m.group(1) if m else None)


def flips(text):
    """[(site_start, site_end, replacement, statement_span, assigned, operand)]"""
    masked = mask_comments(text)
    pins = [(s[3], s[4]) for s in sites_of(text)]
    out = []
    for m in MUL_RE.finditer(masked):
        c = int(m.group("c"), 0)
        if c not in POW or any(a <= m.start() < b for a, b in pins):
            continue
        before = masked[:m.start()].rstrip()
        if before.endswith(("*", "/", "%", ")")) and not before.endswith("(") and before[-1:] in "*/%":
            continue                                  # `a * y * 8`: leave chains alone
        a, b, x = statement_at(masked, m.start())
        whole = re.fullmatch(r"\s*=\s*", masked[masked.rfind("=", a, m.start()):m.start()] if "=" in masked[a:m.start()] else "") \
            and masked[m.end():b].strip() == ""
        rep = "%s << %d" % (m.group("y"), POW[c])
        enclosed = before.endswith("(") and masked[m.end():].lstrip().startswith(")")
        out.append((m.start(), m.end(), rep if whole or enclosed else "(" + rep + ")", (a, b), x, m.group("y")))
    for m in SHL_RE.finditer(masked):
        k = int(m.group("k"))
        if not 1 <= k <= 15 or any(a <= m.start() < b for a, b in pins):
            continue
        lead = masked[:m.start()].rstrip()[-1:]
        tail = masked[m.end():].lstrip()[:1]
        if lead not in ("(", "=", ",") or tail not in (")", ";", ","):
            continue                                  # only a whole operand: `x = y << 3;`, `f(y << 3)`
        a, b, x = statement_at(masked, m.start())
        out.append((m.start(), m.end(), "%s * %d" % (m.group("y"), 2 ** k), (a, b), x, m.group("y")))
    return out


def candidates(text):
    out = []
    sites = sites_of(text)
    for s0, s1, rep, span, x, y in flips(text):
        base = text[:s0] + rep + text[s1:]
        shift = len(rep) - (s1 - s0)
        ynames = set(re.findall(r"[A-Za-z_]\w*", y))
        groups = []
        for names in ([x] if x else [], sorted(ynames), ([x] if x else []) + sorted(ynames)):
            if names and names not in groups:
                groups.append(names)
        bsites = sites_of(base)
        for names in groups:
            sel = [s for s in bsites if any(re.search(r"\b%s\b" % re.escape(n), base[s[3]:s[4]]) for n in names)]
            if not sel:
                continue
            cand = erase_many(base, sel, clean_notes=True)
            if unscored_text(cand) != unscored_text(text):
                continue
            out.append(("shift:%s->%s|%s" % (text[s0:s1].strip(), rep, "+".join(names)), cand))
            if len(out) >= MAX_CANDS:
                return out
    return out


class T:
    name = "t35_shiftspell"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not flips(text):
            return "no power-of-two scaling"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no flip whose statement touches a pinned variable"]}
        cands.sort(key=lambda c: len(sites_of(c[1])))              # most pins removed first
        tried = 0
        for label, t in cands:
            tried += 1
            if vf(t).get("exact"):
                return t, {"label": label, "tried": tried}
        return None, {"refused": ["no candidate exact (%d tried)" % tried]}
