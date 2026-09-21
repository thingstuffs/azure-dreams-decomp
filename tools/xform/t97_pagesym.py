"""T97: a staged page address spelled as a NEIGHBOUR symbol plus an offset, not as its own symbol.

APPEARS     the staged page run t92_pagerun already finds - `V = 0x80070000; ASM_KEEP(V);
            V -= 13008;` - and its cross-variable form, where the bias step assigns ANOTHER local:

                table_page = (u8 *)0x80150000;  ASM_KEEP(table_page);
                table = table_page + 0x1168;              ->  table = D_80151168;

RESOLVES    eight pins over four rows of the first KIT wave: dungeon/func_800AFA68 (two runs),
            dungeon/func_818BDEBC (two runs), dungeon/func_80A170DC and dungeon/func_80C1509C (the
            cross-variable form).  The lanes' exact texts do NOT name the symbol at the run's final
            address; they name a neighbour and add the difference:

                camera_state = (u8 *)&D_8006CD10 + (32);       /* 0x8006CD30 */
                table_base   = (s32)D_8006CCE8 - 0x10;         /* 0x8006CCD8, although the file
                table_base   = (s32)D_8006CCD8 + 0x10;            already names BOTH symbols */

            Mechanism (measured on dungeon/func_800AFA68, `xform.screen` listings): the bare symbol
            is one `SYMBOL_REF` constant, so cse holds the whole address in a pseudo and REUSES it
            at the function's second staging site - `lui $16,32775` once and `addiu $8,$16,-13008`
            twice.  Retail rematerialises the pair at both sites, which is what the `ASM_KEEP_NV`
            was holding.  Written `SYM + K` the address is a PLUS rtx whose `lui` is re-emitted per
            site, and the listing distance to the pinned text falls from 7 to 0.

            Why t92 misses it: t92 is eligible on both rows and finds both runs, but its seed is
            respelled by `t29_addrsym.sym_expr(text, addr, ...)`, which always names `D_%08X % addr`
            exactly - one spelling, with four PIN plans over it.  The neighbour-plus-offset spelling
            is not on its menu.  On dungeon/func_80A170DC and func_80C1509C t92 refuses "no staged
            page run" outright: `runs()` stops at the first statement that READS V without stepping
            it, and the cross-variable tail is exactly that statement.

CANDIDATES  per run (and per pair of runs): the symbols the FILE already names within 0x400 of the
            final address, then invented symbols at the address minus 4, 8, 0x10, 0x20, 0x40 and
            0x100, then the exact symbol - each with t92's pin plans (the run's own window, the wide
            window, the pins naming V).  A `u8 *` local is spelled `(u8 *)&SYM + K`, a wider pointer
            `(T *)((u8 *)&SYM + K)`, an integer local `(TY)SYM + K`, always byte-scaled.  Screened
            against the pinned text's cc1 listing; only the listing-nearest reach the byte verifier.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from . import t29_addrsym as A
    from . import t92_pagerun as t92
    from . import screen
except ImportError:
    import t29_addrsym as A
    import t92_pagerun as t92
    import screen
try:
    from .t36_paramwidth import functions
except ImportError:
    from t36_paramwidth import functions

MAX_RUNS = 6
MAX_SYMS = 9
MAX_LISTINGS = 220
MAX_VERIFY = 6
NEAR_FILE = 0x400                                  # how far a symbol the file names may sit
OFFSETS = (0x10, 0x20, 0x8, 0x4, 0x40, 0x100)
NUM = t92.NUM
mask_comments = A.mask_comments
ASSIGN_TO = r"(?<![.>\w])\b%s\b[ \t]*(?:=(?!=)|\+\+|--|[-+*/|&^%%]=|<<=|>>=)"
MENTION = r"(?<![.>\w])\b%s\b"


def _syms_in(text):
    return sorted({int(m, 16) for m in re.findall(r"\bD_([0-9A-Fa-f]{8})\b", text)})


def _expr(text, sym, k, ty, ptr, ext):
    """`sym + k` spelled for a local of type `ty` with `ptr` stars, byte-scaled."""
    if ptr:
        base = A.sym_expr(text, sym, "u8 *", ext)
        if k:
            base = "%s %s 0x%X" % (base, "+" if k > 0 else "-", abs(k))
        if ptr == 1 and ty == "u8":
            return base
        return "(%s %s)(%s)" % (ty, "*" * ptr, base) if k else "(%s %s)%s" % (ty, "*" * ptr, base)
    base = A.sym_expr(text, sym, None, ext)
    out = "(%s)%s" % (ty, base)
    if k:
        out = "%s %s 0x%X" % (out, "+" if k > 0 else "-", abs(k))
    return out


def spellings(text, addr, ty, ptr):
    """[(tag, expression, externs)] - the neighbour symbols first, the exact symbol last."""
    out, seen = [], set()
    for s in _syms_in(text):
        k = addr - s
        if k and abs(k) <= NEAR_FILE:
            out.append(("file%+d" % k, s, k))
    for k in OFFSETS:
        out.append(("new+%#x" % k, addr - k, k))
    out.append(("exact", addr, 0))
    ranked = []
    for tag, s, k in out:
        if s in seen or not (0x80000000 <= s <= 0x81FFFFFF):
            continue
        seen.add(s)
        ext = set()
        ranked.append((tag, _expr(text, s, k, ty, ptr, ext), ext))
    return ranked[:MAX_SYMS]


# ---------------------------------------------------------------- the cross-variable tail form
TAIL_RE = r"[ \t\n]*(?P<lead>(?:%s)?)\(?(?P<w>[A-Za-z_]\w*)\)?[ \t]*=[ \t]*(?P<cast>%s*)\(?[ \t]*" \
          r"(?P<inner>%s*)\(?(?P<v>[A-Za-z_]\w*)\)?[ \t]*(?P<op>[-+])[ \t]*(?P<k>%s)[ \t]*\)?[ \t]*;[ \t]*"


def tails(text):
    """[{v, w, lo, hi, addr, ty, ptr, span}] - `V = <page>; pins; W = V + K;` (W != V)."""
    masked = mask_comments(text)
    rx = re.compile(TAIL_RE % (t92.TYPE, A.CAST, A.CAST, NUM))
    out = []
    for m in t92.SEED_RE.finditer(masked):
        v = m.group("v")
        if v in t92.KEYWORDS:
            continue
        page = int(re.search(r"0x(8[0-9A-Fa-f]{7})", m.group("rhs")).group(1), 16)
        cs, _ = t92._chunks(masked, m.end(), min(len(masked), m.end() + 1200))
        at = m.end()
        for a, b, chunk in cs:
            if not chunk.strip():
                at = b; continue
            if re.fullmatch(r"[ \t\n]*ASM_[A-Z0-9_]+[ \t]*\([^;]*\)[ \t]*;[ \t]*", chunk):
                at = b; continue
            t = rx.fullmatch(chunk)
            if not t or t.group("v") != v or t.group("w") == v:
                break
            w, ds = t.group("w"), A.decls_of(masked, t.group("w"))
            tys = {(ty, p) for ty, p, _ in ds}
            if len(tys) != 1:
                break
            ty, ptr = next(iter(tys))
            inner = re.sub(r"[\s()*]", " ", t.group("inner") or "").split()
            scale = 1 if (inner and inner[0] in A.BYTEPTR) else t92._elem_bytes(ty, ptr)
            k = int(t.group("k"), 0) * scale
            addr = (page + (-k if t.group("op") == "-" else k)) & 0xFFFFFFFF
            # the seed's own local dies with the edit: it must not be READ again before it is
            # next assigned, or the rewrite would leave a use of an uninitialised value
            fn = next(((x, y) for _f, _p, x, y in functions(text) if x <= m.start() < y), None)
            if fn is None:
                break
            nxt = re.search(ASSIGN_TO % re.escape(v), masked[b:fn[1]])
            stop = b + nxt.start() if nxt else fn[1]
            if re.search(MENTION % re.escape(v), masked[b:stop]):
                break
            lo = m.start("lead") + len(m.group("lead"))
            body = b
            out.append({"v": v, "w": w, "lo": lo, "hi": body, "addr": addr, "ty": ty, "ptr": ptr,
                        "wlead": (a + (len(chunk) - len(chunk.lstrip())), a + len(t.group("lead")) +
                                  (len(chunk) - len(chunk.lstrip())))})
            break
    return out


def _tail_edits(text, t, expr):
    """The seed statement (and everything up to the tail's `=`) replaced by `W = expr;`."""
    ind = text[text.rfind("\n", 0, t["lo"]) + 1:t["lo"]]
    if ind.strip():
        return None
    lead = text[t["wlead"][0]:t["wlead"][1]]
    return [(t["lo"], t["hi"], "%s%s = %s;" % (lead if lead.strip() else "", t["w"], expr))]


def _run_edits(text, r, expr):
    ed = [(r["seed"][0], r["seed"][1], expr)]
    head = text[r["lhs"][0]:r["lhs"][1]]
    if head.lstrip().startswith("("):
        ed.append((r["lhs"][0], r["lhs"][1],
                   re.sub(r"\(\s*(%s)\s*\)" % re.escape(r["v"]), r"\1", head, count=1)))
    for a, b in r["steps"]:
        while a > 0 and text[a - 1] in " \t":
            a -= 1
        ed.append((a, b, ""))
    return ed


def _apply(text, ed, ext):
    t = text
    for a, b, rep in sorted(ed, reverse=True):
        t = t[:a] + rep + t[b:]
    return re.sub(r"[ \t]+$", "", t92._externs(t, ext), flags=re.M)


def _found(text):
    return [("run", r) for r in t92.runs(text)[:MAX_RUNS]] + [("tail", t) for t in tails(text)[:MAX_RUNS]]


def _key(kind, r):
    return (kind, r["v"], r.get("w"), r["addr"], r["ty"], r["ptr"])


def _relocate(chosen, text2):
    """The same runs/tails re-found in `text2` (the text with the pin group already erased)."""
    pool, out = _found(text2), []
    for kind, r in chosen:
        k = _key(kind, r)
        hit = next((x for x in pool if _key(*x) == k), None)
        if hit is None:
            return None
        pool.remove(hit)
        out.append(hit)
    return out


def candidates(text):
    """[(label, new_text)] - each run/tail x each symbol spelling x each pin plan.

    The pin group is erased FIRST and the runs are then re-found in the erased text: a tail's own
    edit SWALLOWS the keep between the seed and the tail, so an offset map over the pinned text
    could not be carried across it.
    """
    found = _found(text)
    if not found:
        return []
    pins = sites_of(text)
    out, seen, sig = [], {text}, unscored_text(text)
    groups = [[f] for f in found] + ([found] if len(found) > 1 else [])
    for chosen in groups:
        kinds = {k for k, _ in chosen}
        tag = ("%s@%d" % (chosen[0][0], chosen[0][1]["lo"]) if len(chosen) == 1
               else "%s%d" % ("+".join(sorted(kinds)), len(chosen)))
        def _core(r):                              # the run WITHOUT the pins swallowed past its last step
            return r["steps"][-1][1] if r.get("steps") else r["hi"]
        core = [s for s in pins if any(r["lo"] <= s[3] < _core(r) for _k, r in chosen)]
        win = [s for s in pins if any(r["lo"] <= s[3] < r["hi"] for _k, r in chosen)]
        wide = [s for s in pins if any(r["lo"] <= s[3] < r.get("wide", r["hi"]) for _k, r in chosen)]
        named = [s for s in pins
                 if any(re.search(r"\b%s\b" % re.escape(n), text[s[3]:s[4]])
                        for _k, r in chosen for n in (r["v"], r.get("w") or r["v"]))]
        for name, group in (("core", core), ("win", win), ("wide", wide), ("var", named),
                            ("core+var", core + [g for g in named if g not in core])):
            if not group:
                continue
            base = erase_many(text, group, clean_notes=True)
            here = _relocate(chosen, base)
            if here is None:
                continue
            per = [spellings(base, r["addr"], r["ty"], r["ptr"]) for _k, r in here]
            n = min(len(p) for p in per)
            for i in range(n):
                ed, ext, ok = [], set(), True
                for (kind, r), sp in zip(here, per):
                    _stag, expr, e = sp[i]
                    ext |= e
                    one = _run_edits(base, r, expr) if kind == "run" else _tail_edits(base, r, expr)
                    if one is None:
                        ok = False; break
                    ed += one
                if not ok:
                    continue
                cand = _apply(base, ed, ext)
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= len(pins):
                    continue
                seen.add(cand)
                out.append(("%s:%s:%s" % (tag, per[0][i][0], name), cand))
    return out


class T:
    name = "t97_pagesym"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        if not t92.runs(text) and not tails(text):
            return "no staged page run or cross-variable tail"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in,
                "runs": len(t92.runs(text)), "tails": len(tails(text))}
        menu = candidates(text)
        if not menu:
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
