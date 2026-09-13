"""T59: a kept page plus an offset, written as the symbol at that address - one use at a time.

APPEARS     a page literal held by a keep and used with an offset whose symbol the file already names
            (an extern, or the NON_MATCHING arm's spelling):
                address_base = (u8 *)0x80120000;
                ASM_KEEP(address_base);
                source_entry = (volatile SourceEntry *)(address_base + 0x6A18);   // D_80126A18 elsewhere
RESOLVES    the keeps4 lane (round 23, `town/func_8096B16C`): replacing only that use with the named symbol,
            `source_entry = (volatile SourceEntry *)D_80126A18;`, and dropping the page and its keep once
            nothing else reads them, is exact where t29_addrsym (every use, at a splitting cell) and
            t54_pagebase (the page's own definition) found nothing. A symbol is a relocatable object
            address, a different compiler value from the integer page (page_astra, round 18).
POPULATION  2026-09-13: 142 such uses in 74 rows.
RESULT      2026-09-13: reproduces the keeps4 output (identical assembly). Swept over its 66 eligible rows
            outside the round-23 lane rows: 2 applied (dungeon/func_80084084 12 -> 10 pins,
            dungeon/func_81335C70 4 -> 3). t29/t54 had already taken most rows where a symbol pays.
Candidates, all through `vf`: each use alone (page and keep dropped when the page has no other reader, else
kept), then every use of that page at once. The symbol is spelled as the file spells it (`&D_X` when the
file takes its address, `D_X` otherwise).
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many

PAGE = re.compile(r"^(?P<ind>[ \t]*)(?P<p>\w+)\s*=\s*(?:\([^)]*\)\s*)?(?P<lit>0x8[0-9A-Fa-f]{3}0000)\s*;[^\n]*\n"
                  r"[ \t]*ASM_KEEP(?:_NV)?\(\s*(?P=p)\s*\)\s*;[^\n]*\n", re.M)


def use_re(p):
    # x = (T)(p + OFF);   x = (T)p + OFF;   x = p + OFF;
    return re.compile(r"(?P<lhs>\b\w+(?:->\w+|\.\w+|\[[^\]]*\])*\s*=\s*)(?P<cast>\((?:[^()]|\([^()]*\))*\)\s*)?"
                      r"\(?\s*(?:\((?:[^()]|\([^()]*\))*\)\s*)?%s\s*\+\s*(?P<off>0x[0-9A-Fa-f]+|\d+)\s*\)?\s*;" % re.escape(p))


def spelled(text, addr):
    sym = "D_%08X" % addr
    names = {m.group(0).upper(): m.group(0) for m in re.finditer(r"\bD_[0-9A-Fa-f]{8}\b", text)}
    real = names.get(sym.upper())
    if real is None:
        return None
    return ("&" + real) if re.search(r"&\s*%s\b" % re.escape(real), text) else real


def find(text):
    """[(page_start, page_end, p, [(use_start, use_end, replacement)])] per kept page with symbol-backed uses."""
    out = []
    for m in PAGE.finditer(text):
        p, base = m.group("p"), int(m.group("lit"), 16)
        nxt = re.search(r"(?<![.>\w])\b%s\s*=(?!=)" % re.escape(p), text[m.end():])
        stop = m.end() + (nxt.start() if nxt else len(text) - m.end())
        uses = []
        for u in use_re(p).finditer(text, m.end(), stop):
            sym = spelled(text, base + int(u.group("off"), 0))
            if sym:
                uses.append((u.start(), u.end(), "%s%s%s;" % (u.group("lhs"), u.group("cast") or "", sym)))
        if uses:
            out.append((m.start(), m.end(), p, uses, stop))
    return out


def rewrite(text, page, chosen):
    ps, pe, p, uses, stop = page
    for s, e, rep in sorted(chosen, reverse=True):
        text = text[:s] + rep + text[e:]
    # drop the page and its keep when nothing in its live range reads it any more
    shift = sum(len(rep) - (e - s) for s, e, rep in chosen)
    body = text[pe:stop + shift]
    if not re.search(r"(?<![.>\w])\b%s\b" % re.escape(p), re.sub(r"/\*.*?\*/", "", body, flags=re.S)):
        text = text[:ps] + text[pe:]
    return text


class T:
    name = "t59_offsetsym"
    level = 1
    needs_verify = True
    BUDGET = 24

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        return None if find(text) else "no kept page with a symbol-backed offset use"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, tried, cur, steps = len(sites_of(text)), 0, text, []
        usig = unscored_text(text)
        pages = find(text)
        for pi in reversed(range(len(pages))):
            page = find(cur)[pi] if pi < len(find(cur)) else None
            if page is None:
                continue
            trials = [[u] for u in reversed(page[3])] + ([page[3]] if len(page[3]) > 1 else [])
            for chosen in trials:
                if tried >= cls.BUDGET:
                    break
                cand = rewrite(cur, page, chosen)
                if cand == cur or unscored_text(cand) != usig or len(sites_of(cand)) >= len(sites_of(cur)):
                    continue
                tried += 1
                if vf(cand).get("exact"):
                    cur = cand
                    steps.append("%s:%d" % (page[2], len(chosen)))
                    break
        if not steps:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in, "pages": len(pages)}
        return cur, {"step": "+".join(steps), "tried": tried, "pins_in": pins_in,
                     "pins_out": len(sites_of(cur)), "pages": len(pages)}
