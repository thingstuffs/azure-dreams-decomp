"""T116: libgpu's ordering-table link written with the P_TAG `addr:24` bitfield instead of pinned mask registers.

APPEARS     an OT link `DST = (DST & 0xFF000000) | (SRC & 0x00FFFFFF);` whose 24-bit mask lives in a register-
            pinned local (`register u32 addr_mask ASM_REG("$18") = 0x00FFFFFF;`), usually with a `0xFF000000`
            partner local - the erase residue swaps the mask with a pointer allocno.  18 pinned rows carry a
            pinned 0x00FFFFFF mask.  Exemplars (claude-opus-5-5): dungeon/func_818D4800 (r73_opus_s22),
            dungeon/func_81910EC0 and func_8182121C (r73_opus_s3).

RESOLVES    opus (func_818D4800): "APPEARS: a `$sN`-pinned `0x00FFFFFF` mask (usually with a `0xFF000000`
            partner) in `(*p & 0xFF000000) | (ot & 0x00FFFFFF)` OT-link code whose erasure swaps the mask with
            a pointer allocno. RESOLVES: rewrite the link as a 24-bit `addr` bitfield copy (P_TAG
            setaddr/getaddr), so the mask's pre-combine reference count rises."  opus (s3, harvest-2 H11):
            "libgpu OT link as a `P_TAG` bitfield, masks local to the link block".  The bitfield store
            expands to the same and/or/or insns, but the mask is a fresh constant per link (store_bit_field),
            so its reference count and live range - the allocno priority the pin stood in for - change.

MEASURED    (2026-09-23, r73_h3_t116_ptaglink_check) 0/3 exemplars: 818D4800 d30 (the lane's text also drops
            the duplicated `next_object` arm reads), 81910EC0 d4, 8182121C d24 (both need the masks declared
            inside the link block plus a parameter retype).  NOT SWEPT; the next version needs the
            block-local mask declaration as a candidate.

WHY THE OWNERS MISS IT  no generator knows the bitfield spelling; t66/t87 merge or split the mask local, t29/t86
            respell pages only.

CANDIDATES  for the function holding the pinned mask M (and its 0xFF000000 partner T, if any): every link
            `DST = (DST & T) | (SRC & M);` (T/M the local or the literal) rewritten `((P_TAG *)&DST)->addr =
            ((P_TAG *)&SRC)->addr;` (SRC an lvalue) or `... ->addr = (u32)(SRC);` - all links jointly, then each
            alone; the remaining reads of M and T written as the literals (LITERAL) or left on plain locals
            (PLAIN); the mask pins erased.  A file-local `P_TAG` typedef is added when the file has none.  Ranked
            by the cc1 listing distance to the pinned text; listing-exact and the two nearest go to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t36_paramwidth import functions
    import screen

MAX_LINKS = 8
MAX_LISTINGS = 30
MAX_VERIFY = 4
ADDR, TAG = "0x00FFFFFF", "0xFF000000"
TYPEDEF = "typedef struct {\n    u32 addr : 24;\n    u32 len : 8;\n} P_TAG;\n"
MENTION = r"(?<![.>\w])%s\b"


def _masks(text, b0, b1, value):
    """Locals of the function initialised or assigned to `value` (case-insensitive hex)."""
    body = text[b0:b1]
    return sorted(set(re.findall(r"\b([A-Za-z_]\w*)[ \t]*(?:ASM_REG\([^()]*\))?[ \t]*=[ \t]*%s[uU]?[ \t]*;" % value,
                                 body, re.I)))


def _balanced(s):
    d = 0
    for ch in s:
        d += (ch == "(") - (ch == ")")
        if d < 0:
            return False
    return d == 0


def _norm(s):
    return re.sub(r"\s+", "", s)


def links(text, b0, b1, ms, ts):
    """[(start, end, indent, dst, src)] link statements in [b0, b1)."""
    mm = "|".join([re.escape(m) for m in ms] + [ADDR])
    tt = "|".join([re.escape(t) for t in ts] + [TAG])
    rx = re.compile(r"^(?P<ind>[ \t]*)(?P<dst>[^;{}\n=]+?)[ \t]*=(?!=)\s*\(\s*(?P<dst2>[^;{}]+?)\s*&\s*(?:%s)\s*\)\s*\|"
                    r"\s*\(\s*(?P<src>[^;{}]+?)\s*&\s*(?:%s)\s*\)\s*;[ \t]*$" % (tt, mm), re.M | re.I)
    out = []
    for m in rx.finditer(text, b0, b1):
        dst, src = m.group("dst").strip(), m.group("src").strip()
        start = m.start()
        if _norm(dst) != _norm(m.group("dst2")):
            # `w = DST; DST = (w & T) | (SRC & M);` - the copy goes with the link (dungeon/func_818D4800)
            w = m.group("dst2").strip()
            pm = None
            if re.fullmatch(r"[A-Za-z_]\w*", w):
                for pm in re.finditer(r"^[ \t]*%s[ \t]*=[ \t]*([^;{}\n]+);[ \t]*\n(?:[ \t]*\n)*" % re.escape(w), text[b0:m.start()], re.M):
                    pass
            if not pm or b0 + pm.end() != m.start() or _norm(pm.group(1)) != _norm(dst):
                continue
            start = b0 + pm.start()
        if not _balanced(src) or not _balanced(dst):
            continue
        out.append((start, m.end(), m.group("ind"), dst, src))
    return out[:MAX_LINKS]


def _lvalue(e):
    e = e.strip()
    if re.match(r"^\(\s*(?:s32|u32|int|unsigned)\s*\)", e):
        return False
    return bool(re.fullmatch(r"\*.*|[A-Za-z_]\w*(?:\s*(?:->|\.)\s*\w+|\s*\[[^\[\]]+\])+|[A-Z_0-9]+_AT\(.*\)", e, re.S))


def spell(ind, dst, src):
    rhs = "((P_TAG *)&%s)->addr" % src if _lvalue(src) else "(u32)(%s)" % src
    return "%s((P_TAG *)&%s)->addr = %s;" % (ind, dst, rhs)


def with_typedef(text):
    if re.search(r"\bP_TAG\b[ \t]*;", text) and "typedef" in text:
        return text
    inc = list(re.finditer(r"^#include[^\n]*\n", text, re.M))
    at = inc[-1].end() if inc else 0
    return text[:at] + TYPEDEF + text[at:]


def literalise(text, b0, b1, names, value):
    """Reads of `names` inside [b0, b1) written as `value`; their plain `= value;` statements dropped."""
    body = text[b0:b1]
    for n in names:
        body = re.sub(r"^[ \t]*%s[ \t]*=[ \t]*%s[uU]?[ \t]*;[^\n]*\n" % (re.escape(n), value), "", body, flags=re.M | re.I)
        lines = []
        for l in body.split("\n"):
            if re.match(r"^[ \t]*(?:register[ \t]+)?(?:(?:unsigned|signed|const)[ \t]+)*[A-Za-z_]\w*[ \t\*]+%s\b" % re.escape(n), l):
                lines.append(l)                           # the declaration stays (plain, unused)
            else:
                lines.append(re.sub(MENTION % re.escape(n), value, l))
        body = "\n".join(lines)
    return text[:b0] + body + text[b1:]


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    for fname, _params, b0, b1 in functions(text):
        ms = _masks(text, b0, b1, ADDR)
        ts = _masks(text, b0, b1, TAG)
        pins = [p for p in sites_of(text) if b0 <= p[3] < b1 and any(
            re.search(MENTION % re.escape(v), text[text.rfind("\n", 0, p[3]) + 1:text.find("\n", p[3])]) for v in ms + ts)]
        if not pins:
            continue
        ls = links(text, b0, b1, ms, ts)
        sets = ([ls] if len(ls) > 1 else []) + [[l] for l in ls] + [[]]
        for sel in sets:
            cur = text
            for s, e, ind, dst, src in sorted(sel, key=lambda x: -x[0]):
                cur = cur[:s] + spell(ind, dst, src) + cur[e:]
            nb1 = b1 + len(cur) - len(text)
            mp = [p for p in sites_of(cur) if b0 <= p[3] < nb1 and any(
                re.search(MENTION % re.escape(v), cur[cur.rfind("\n", 0, p[3]) + 1:cur.find("\n", p[3])]) for v in ms + ts)]
            erased = erase_many(cur, mp, clean_notes=True)
            nb1e = nb1 + len(erased) - len(cur)
            forms = [("plain", erased), ("literal", literalise(literalise(erased, b0, nb1e, ms, ADDR), b0,
                                                               nb1e, ts, TAG))]
            for tag, cand in forms:
                if sel:
                    cand = with_typedef(cand)
                label = "%s:%s:%s" % (fname, "all%d" % len(sel) if len(sel) > 1 else
                                      ("link@%d" % (text.count("\n", 0, sel[0][0]) + 1) if sel else "nolink"), tag)
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append((label, cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t116_ptaglink"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not re.search(ADDR, text, re.I):
            return "no 0x00FFFFFF mask"
        if not candidates(text):
            return "no pinned 0x00FFFFFF/0xFF000000 mask local"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        menu = candidates(text)
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        ranked, listings = [], 0
        for label, cand in menu:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((_dist(target, lst), len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
