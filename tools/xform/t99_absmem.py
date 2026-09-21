"""T99: a fixed-address global read as an ABSOLUTE memory operand instead of through its symbol.

APPEARS     a scheduling or memory barrier standing immediately in front of a read of a global whose
            symbol name IS its address - three rows of the second KIT wave:

                ASM_SCHED_BARRIER();                  ->   if ((*(u16 *)0x80013714) & 8) {
                if (D_80013714 & 8) {

            dungeon/func_81332EC0 (`ASM_MEM_BARRIER`, 1 pin), dungeon/func_80088FA0
            (`ASM_SCHED_BARRIER`, 1 pin, the array spelling `D_80013714[0]`) and dungeon/func_8008557C
            (2 pins, two separate reads of the same symbol - each respelled with ITS barrier, the
            row's other reads left alone).

RESOLVES    the lanes' rule (work/native_lane/r71_kit_astra12/REPORT.md, func_80088FA0): "a
            listing-invisible scheduling barrier sits immediately before a known global load and its
            erasure changes a branch delay slot.  RESOLVES: use the matching-width absolute memory
            operand so address expansion occurs after delay-slot selection, then verify the assembled
            bytes."  Mechanism: as a `SYMBOL_REF` the address is a HIGH/LO_SUM pair that gcc 2.x
            expands early, so cse and the delay-slot filler see two insns and may split them across
            the branch; written as an integer constant address the load is one operand whose address
            arithmetic is expanded after delay-slot selection, which is the single `lw` retail has.
            This is the INVERSE of t29_addrsym / t86_symaddr / t77_symplace, which all turn an
            address into a symbol; nothing in tools/xform spelled a symbol back as an address.

CANDIDATES  per pin site with a symbol read in the next statements: that ONE read respelled
            `(*(TY *)0xADDR)` (or `((TY *)0xADDR)[i]` for an indexed read) at the width the file
            declares for the symbol, with the pin erased alone and with the other pins of the read's
            statement; then the variant that respells every read of the symbol in the statement.
            Only `extern <integer type> D_XXXXXXXX;` / `...[N];` declarations are used - the symbol's
            name is its address, so no symbol table is consulted.  Ranked by the cc1 listing distance
            to the pinned text; `vf` sees the listing-exact candidates and the two nearest.
"""
import difflib, re, sys
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

SIZE = {"u8": 1, "s8": 1, "char": 1, "u16": 2, "s16": 2, "short": 2,
        "u32": 4, "s32": 4, "int": 4, "long": 4, "M2C_UNK8": 1, "M2C_UNK16": 2, "M2C_UNK32": 4}
DECL = re.compile(r"^[ \t]*extern[ \t]+(?P<ty>[A-Za-z_]\w*)[ \t]+(?P<v>D_[0-9A-Fa-f]{8})[ \t]*"
                  r"(?P<arr>\[[^\]]*\])?[ \t]*;", re.M)
SYMBOL = re.compile(r"(?<![\w.>])(?P<v>D_(?P<addr>[0-9A-Fa-f]{8}))\b(?P<idx>[ \t]*\[[^\[\]]*\])?")
LOOK_LINES = 3                  # how far past the pin a read may sit
MAX_SITES = 8
MAX_LISTINGS = 60
MAX_VERIFY = 4


def symbols(text):
    """{name: type} for every `extern <integer type> D_XXXXXXXX;` (or `[N];`) the file declares."""
    out = {}
    for m in DECL.finditer(mask_comments(text)):
        if m.group("ty") in SIZE:
            out[m.group("v")] = m.group("ty")
    return out


def _spell(ty, addr, idx):
    """The absolute-memory spelling of a read, indexed or not."""
    if idx is None:
        return "(*(%s *)0x%08X)" % (ty, addr)
    inner = idx.strip()[1:-1].strip()
    if re.fullmatch(r"0|0x0+", inner):
        return "(*(%s *)0x%08X)" % (ty, addr)
    return "((%s *)0x%08X)[%s]" % (ty, addr, inner)


def sites(text):
    """[{pin, sym, ty, spans}] - a pin with a read of a declared fixed-address global just below it."""
    syms = symbols(text)
    if not syms:
        return []
    masked = mask_comments(text)
    lines = masked.split("\n")
    starts, at = [], 0
    for l in lines:
        starts.append(at); at += len(l) + 1
    out = []
    for s in sites_of(text):
        if s[0] != "stmt":
            continue
        ln = s[5] - 1                               # the pin's own line, 0-based
        lo = starts[ln] if ln < len(starts) else s[4]
        hi = starts[min(ln + 1 + LOOK_LINES, len(starts) - 1)] if ln + 1 < len(starts) else len(masked)
        best = None
        for m in SYMBOL.finditer(masked, s[4], hi):
            if m.group("v") not in syms:
                continue
            if masked[m.end():m.end() + 2].strip().startswith("="):
                continue                            # a WRITE through the symbol: not this move
            best = m
            break
        if best is None:
            continue
        out.append({"pin": s, "sym": best.group("v"), "ty": syms[best.group("v")],
                    "addr": int(best.group("addr"), 16), "span": (best.start(), best.end()),
                    "idx": best.group("idx"), "line": ln})
        if len(out) >= MAX_SITES:
            break
    return out


def _stmt_span(masked, at):
    """(a, b) of the statement holding offset `at` - between the previous `;{}:` and the next `;{`."""
    a = max(masked.rfind(c, 0, at) for c in ";{}:")
    b = min([x for x in (masked.find(";", at), masked.find("{", at)) if x >= 0] or [len(masked)])
    return a + 1, b


def candidates(text):
    """[(label, new_text)] - the read respelled, alone and with its statement's other reads."""
    out, seen, sig = [], {text}, unscored_text(text)
    masked, pins = mask_comments(text), sites_of(text)
    n0 = len(pins)
    for st in sites(text):
        spell = _spell(st["ty"], st["addr"], st["idx"])
        a, b = st["span"]
        forms = [("one", [(a, b, spell)])]
        sa, sb = _stmt_span(masked, a)
        many = [(m.start(), m.end(), _spell(st["ty"], int(m.group("addr"), 16), m.group("idx")))
                for m in SYMBOL.finditer(masked, sa, sb) if m.group("v") == st["sym"]]
        if len(many) > 1:
            forms.append(("stmt", many))
        group_one = [st["pin"]]
        group_win = [p for p in pins if sa <= p[3] < sb or p is st["pin"]]
        for ftag, edits in forms:
            base = text
            for x, y, rep in sorted(edits, reverse=True):
                base = base[:x] + rep + base[y:]
            for ptag, group in (("pin", group_one), ("win", group_win)):
                if not group:
                    continue
                cand = erase_many(base, group, clean_notes=True)
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("%s@%d:%s:%s" % (st["sym"], st["line"] + 1, ftag, ptag), cand))
    return out


class T:
    name = "t99_absmem"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        if not symbols(text):
            return "no fixed-address global declared at an integer width"
        if not sites(text):
            return "no pin standing in front of a fixed-address global read"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "sites": len(sites(text))}
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
            lst = screen.compile_s(row, cand)
            listings += 1
            if lst is None:
                continue
            d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                    if y[:1] in "+-" and not y.startswith(("---", "+++")))
            ranked.append((d, len(sites_of(cand)), label, cand))
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
