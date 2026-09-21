"""T98: the declared PARAMETER width of a function changed, and the entry-copy pins erased jointly.

APPEARS     the allocation-call twin family of the second KIT wave - a small spawner whose prologue
            copies its arguments into callee-saved registers and whose pins sit on those copies and
            on the two allocation arguments:

                void *BODY_NAME(s16 arg0, s8 _arg1, s8 arg2, s16 _arg3) {
                    register s8  arg1 ASM_REG("$21");
                    register s16 arg3 ASM_REG("$17");
                    register void *work ASM_REG("$16");
                    ...
                    alloc_id = 0x112;  ASM_KEEP_NV(alloc_id);
                    arg1 = _arg1;      alloc_base = &D_80083498;   arg3 = _arg3;
                    ASM_KEEP_NV(alloc_base);
                    part = func_8003FD64(alloc_id, alloc_base);
                    ASM_KEEP(arg3);  ...  ASM_KEEP(arg1);

            dungeon/func_80CBD000 (8 pins), func_80FB7000 (4), func_80FC3000 (4), func_80E07054 (3
            of 4) and func_8009612C (5) of the round-72 move table: in each row ONE formal is
            declared at another width in EVERY declaration of the function and the whole pin group
            of the entry sequence is erased together.  `s8 arg2 -> s16 arg2` on the twins,
            `s32 target_x, s32 target_y -> s16` on func_8009612C.

RESOLVES    gcc 2.x function.c `assign_parms` with PROMOTE_PROTOTYPES: a formal declared narrower
            than the mode it is passed in does NOT get a REG_EQUIV memory it can be reloaded from -
            it gets a real pseudo with a conversion copy at function entry, which is a
            call-crossing pseudo global.c allocates callee-saved.  That is the prologue retail has,
            so the copies stop needing `ASM_REG`/`ASM_KEEP` to hold their place; declaring the
            formal WIDER moves the conversion the other way and frees the same group on the rows
            whose copies are the narrow ones.  The lanes' rule: "test the stored-byte third
            parameter as a halfword interface and jointly remove that four-pin call group; update
            every declaration in the translation unit" (work/native_lane/r71_kit_astra8/REPORT.md).

            Why t36_paramwidth misses these rows (measured on the base texts): t36 is eligible on
            func_80CBD000/func_80FB7000/func_80FC3000 but (a) its `NARROW` map only WIDENS, so an
            `s32` formal has no menu at all and func_80E07054 / func_8009612C refuse outright,
            (b) its parameter menu is the formals that HAVE a pinned copy, and the formal the twins
            need (`pos_y`, `arg2`) has none, (c) `build()` erases only the pins that NAME a copy, so
            the `ASM_REG` declarations and the `ASM_USE*` group survive every candidate, and (d) it
            has no listing screen, so a bigger menu would cost byte-scorer runs.

CANDIDATES  every scalar integer formal of a pinned function, at every other integer width (both
            directions), x three pin plans - the whole function's pins jointly, the pins that name
            the formal or a local copying it plus the function's `ASM_REG` declarations, and those
            declarations alone - plus two group candidates (every scalar formal at s16, then s32).
            Every textual declaration of the function with the same arity is retyped with the
            definition (`void *BODY_NAME(...)` appears twice in the twins, and func_8015E8A4 has a
            bare `extern void *func_8015E8A4(s32, s8, s8, s16);` type list as well).  Ranked by the
            cc1 listing distance to the PINNED text (xform/screen.py); `vf` sees the listing-exact
            candidates and at most two nearest others.  The callee-side prototype change
            func_80E07054 also needs (`func_800A48F0(void *, s32, s32)` -> `s16` third) is NOT on
            this menu: that is t76_arity's side of the call.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

INT_TYPES = ("s8", "u8", "s16", "u16", "s32", "u32")
ALIAS = {"M2C_UNK8": "s8", "M2C_UNK16": "s16", "M2C_UNK32": "s32", "char": "s8",
         "unsigned char": "u8", "short": "s16", "unsigned short": "u16", "int": "s32",
         "unsigned int": "u32", "long": "s32", "unsigned long": "u32"}
MAX_LISTINGS = 190
MAX_VERIFY = 5
MAX_CANDS = 96
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "defined"}


def _scalar(ty):
    """The integer width name of a scalar type, or None for pointers / aggregates."""
    ty = ty.strip()
    if "*" in ty:
        return None
    ty = re.sub(r"\b(const|volatile|register)\b", " ", ty).strip()
    ty = re.sub(r"\s+", " ", ty)
    if ty in INT_TYPES:
        return ty
    return ALIAS.get(ty)


def _parts(masked, open_paren):
    """[(a, b)] spans of the top-level comma-separated parts of a parameter list, or None."""
    depth, i, start, out = 0, open_paren, open_paren + 1, []
    while i < len(masked):
        c = masked[i]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
            if depth == 0:
                out.append((start, i))
                return out
        elif c == "," and depth == 1:
            out.append((start, i)); start = i + 1
        elif c in ";{}":
            return None
        i += 1
    return None


def declarations(text, fname, nparams):
    """[[(a, b)]] - the parameter-part spans of every textual declaration of `fname` with `nparams`."""
    masked, out = mask_comments(text), []
    for m in re.finditer(r"(?<![\w.>])%s[ \t\n]*\(" % re.escape(fname), masked):
        ps = _parts(masked, m.end() - 1)
        if ps and len(ps) == nparams:
            out.append(ps)
    return out


def retype(text, fname, params, want):
    """`want` = {parameter index: new type} applied to every declaration of `fname` (None if none applies)."""
    edits = []
    for ps in declarations(text, fname, len(params)):
        for i, ty in want.items():
            a, b = ps[i]
            old = params[i][1].strip()
            base = re.sub(r"\b(const|volatile|register)\b", "", old).strip()
            m = re.search(r"\b%s\b" % re.escape(base.split()[-1]), text[a:b])
            if not m:
                continue
            edits.append((a + m.start(), a + m.end(), ty))
    if not edits:
        return None
    t = text
    for a, b, rep in sorted(set(edits), reverse=True):
        t = t[:a] + rep + t[b:]
    return t


def copies_of(text, param, b0, b1):
    """Locals of the body whose declaration or a plain assignment copies `param`."""
    masked = mask_comments(text)[b0:b1]
    P = re.escape(param)
    out = set()
    for m in re.finditer(r"(?<![\w.>])([A-Za-z_]\w*)[ \t]*=[ \t]*\(?\s*(?:\(\s*\w[\w \t\*]*\)\s*)?%s\s*\)?[ \t]*;" % P, masked):
        if m.group(1) not in KEYWORDS:
            out.add(m.group(1))
    return out


def pinned_params(text):
    """[(fname, params, body, [formal indices a pin reaches])] for every pinned function with scalar formals."""
    sites, out = sites_of(text), []
    for name, params, b0, b1 in functions(text):
        if name in KEYWORDS or not params:
            continue
        mine = [s for s in sites if b0 < s[3] < b1]
        if not mine:
            continue
        idx = [i for i, p in enumerate(params) if _scalar(p[1])]
        if not idx:
            continue
        named = set()
        for s in mine:
            named.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
        reach = []
        for i in idx:
            p = params[i][0]
            if p in named or (copies_of(text, p, b0, b1) & named):
                reach.append(i)
        out.append((name, params, (b0, b1), reach))
    return out


def _plans(text, fname, params, body, touched):
    """[(tag, [sites])] - the pin groups this generator erases with a retype."""
    b0, b1 = body
    mine = [s for s in sites_of(text) if b0 < s[3] < b1]
    if not mine:
        return []
    regs = [s for s in mine if s[0] == "reg"]
    names = set()
    for i in touched:
        p = params[i][0]
        names.add(p)
        names |= copies_of(text, p, b0, b1)
    named = [s for s in mine
             if any(re.search(r"\b%s\b" % re.escape(n), text[s[3]:s[4]]) for n in names)]
    both = named + [s for s in regs if s not in named]
    plans = [("all", mine)]
    pre = _precall(text, b0, b1)
    if pre:
        entry = [s for s in mine if s[3] < pre]
        if entry and len(entry) < len(mine):
            plans.append(("precall", entry))
    args = _callargs(text, b0, b1)
    if args:
        grp = [s for s in mine
               if any(re.search(r"\b%s\b" % re.escape(n), text[s[3]:s[4]]) for n in args)]
        if grp and len(grp) < len(mine) and all(grp != g for _t, g in plans):
            plans.append(("callargs", grp))
    if both and len(both) < len(mine) and all(both != g for _t, g in plans):
        plans.append(("named+reg", both))
    if regs and len(regs) < len(mine) and all(regs != g for _t, g in plans):
        plans.append(("reg", regs))
    return plans


CALL_RE = re.compile(r"(?<![\w.>])(?P<name>[A-Za-z_]\w*)[ \t\n]*\([^;{}]*\)[ \t]*;")


def _callargs(text, b0, b1):
    """The identifiers in the argument list of the body's first ordinary call statement."""
    masked = mask_comments(text)
    for m in CALL_RE.finditer(masked, b0, b1):
        n = m.group("name")
        if n in KEYWORDS or n.startswith("ASM_"):
            continue
        inner = masked[masked.index("(", m.start()) + 1:m.end() - 2]
        return {w for w in re.findall(r"[A-Za-z_]\w*", inner) if w not in KEYWORDS}
    return set()


def _precall(text, b0, b1):
    """The end offset of the body's first ordinary call statement (0 if it has none)."""
    masked = mask_comments(text)
    for m in CALL_RE.finditer(masked, b0, b1):
        n = m.group("name")
        if n in KEYWORDS or n.startswith("ASM_"):
            continue
        return m.end()
    return 0


def candidates(text):
    """[(label, new_text)] - a formal at another width x a pin plan."""
    out, seen, sig = [], {text}, unscored_text(text)
    n0 = len(sites_of(text))
    for fname, params, body, reach in pinned_params(text):
        idx = [i for i, p in enumerate(params) if _scalar(p[1])]
        order = [i for i in reach] + [i for i in idx if i not in reach]
        wants = []
        for ty in ("s16", "s32"):                       # the group candidates first: a menu cap
            group = {i: ty for i in idx if _scalar(params[i][1]) != ty}   # must never cut them
            if len(group) > 1:
                wants.append(("all=%s" % ty, group))
        for i in order:
            cur = _scalar(params[i][1])
            for ty in INT_TYPES:
                if ty != cur:
                    wants.append(("%s=%s" % (params[i][0], ty), {i: ty}))
        for tag, want in wants:
            base = retype(text, fname, params, want)
            if base is None:
                continue
            # the retype shifts every offset, so the body span is re-found in the RETYPED text
            span = next(((x, y) for n, _p, x, y in functions(base) if n == fname), None)
            if span is None:
                continue
            for ptag, group in _plans(base, fname, params, span, sorted(want)):
                if not group:
                    continue
                cand = erase_many(base, group, clean_notes=True)
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("%s:%s:%s" % (fname, tag, ptag), cand))
                if len(out) >= MAX_CANDS:
                    return out
    return out


class T:
    name = "t98_paramcell"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no live pin site"
        found = pinned_params(text)
        if not found:
            return "no pinned function with a scalar integer formal"
        if not any(r for _f, _p, _b, r in found):
            return "no pin naming a formal or a copy of one"
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
