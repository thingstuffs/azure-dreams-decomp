"""T110: a parameter GROUP declared at the consumer's width, jointly with its carrier copies (folded or retyped).

APPEARS     a spawner/effect function whose scalar parameters reach the body through carrier locals held by
            pins - `register s32 variant_flag ASM_REG("$21"); variant_flag = variant; ... ASM_KEEP(variant_flag);`,
            `s16 held_duration = duration; ... ASM_KEEP(offset_y);`, `s8 saved_x = grid_x; ASM_KEEP_NV(saved_x);` -
            where the value only ever reaches a halfword field or a `(x << 16)` test.  Round-73 lanes:
              dungeon/func_8132B4C8  (claude-opus-5-5, r73_opus_s5, 2 pins)  four s32 formals -> s16, the pinned
                                     `variant_flag` copy FOLDED into `variant`;
              dungeon/func_8132E83C  (claude-opus-5-5, r73_opus_s4, 2 pins)  duration/offset_x/y/z s32 -> s16, the
                                     `held_duration`/`held_offset_x` carriers FOLDED, the two tail keeps erased;
              dungeon/func_80FF9000, func_80FE1000  (claude-opus-5-5, r73_opus_a4, 2 + 2 pins)  the s8 formals ->
                                     s32 and their s8 carriers RETYPED s16 (the other direction);
              dungeon/func_818F33BC  (astra, r74_astra_pre1), func_80E0D090 (opus s7), func_80B9D094 (opus a6):
                                     the same retype plus a second move each (expression fold / statement order).

RESOLVES    opus (func_8132E83C): "APPEARS: `ASM_KEEP(<stack parameter>)` at the end of a function, where the
            erasure moves the parameter's `lw` from the prologue to its use and shrinks the frame. RESOLVES: declare
            that stack parameter (and its siblings the row already narrows through `sN held = param` locals) with
            the narrow type of the field it is added to (`s16`/`u16`). Fold the redundant held locals."
            opus (func_8132B4C8): "declare that parameter, and the sibling scalar parameters, as s16/u16 (the t84
            narrow-parameter family), and use the parameter directly."  opus (func_80FF9000): "declare the
            parameters s32 and the copies s16 (t84 narrow-param family, other direction)."
            Mechanism (t84/t98): gcc 2.x assign_parms gives a formal declared narrower than its passing mode a real
            pseudo with an entry conversion instead of a REG_EQUIV stack slot; the carrier locals are what m2c
            invented for that pseudo, so with the width right they are either redundant (fold) or a plain
            narrowing copy (retype).

WHY THE OWNERS MISS IT (measured 2026-09-23, work/native_lane/r73_h2_t98_paramcell_check and siblings)
            t98_paramcell retypes FORMALS only - the copy stays, `all=s16:all` is listing distance 2 on
            func_8132B4C8 and 20 on func_8132E83C (its group also narrows `scale`/`velocity_z`), 62 on
            func_80FF9000 (the copies must go s16 as well); t84 refuses "no pinned s32 copy of an s32 parameter"
            (the copies are s8/s16 or unpinned), t36 refuses or misses (it only widens the formal).

CANDIDATES  per pinned function: formal groups (the formals a pin reaches directly or through a copy; those
            plus every formal with a copy; the contiguous run spanning them; every scalar formal) x widths
            (s16, u16, s32) x carrier plans (fold: the copy's declaration and `c = P;` dropped and c renamed to
            P; retype16: the copies declared s16; retypeP: the copies at the formal's new width; keep) x pin
            plans (every pin of the function; the pins naming the group plus the register bindings).  Every
            textual declaration of the function (and of a `#define BODY_NAME x` target) with the same arity
            is retyped with it.  Ranked by cc1 listing distance to the pinned text; the listing-exact and the
            two nearest go to `vf`.  A signature change: `info["signature_change"]` names the function.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments, decls_of
    from .t36_paramwidth import functions
    from .t98_paramcell import _scalar, retype, copies_of
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments, decls_of
    from t36_paramwidth import functions
    from t98_paramcell import _scalar, retype, copies_of
    import screen

MAX_LISTINGS = 120
MAX_VERIFY = 4
MAX_CANDS = 160
WIDTHS = ("s16", "u16", "s32")


def _span(text, fname):
    return next(((p, x, y) for n, p, x, y in functions(text) if n == fname), None)


def _retype_all(text, fname, params, want):
    """t98.retype on fname and on every `#define fname X` target (BODY_NAME twins)."""
    t = retype(text, fname, params, want) or text
    for m in re.finditer(r"^[ \t]*#[ \t]*define[ \t]+%s[ \t]+([A-Za-z_]\w*)" % re.escape(fname), t, re.M):
        t = retype(t, m.group(1), params, want) or t
    return None if t == text else t


def _copies(text, param, b0, b1):
    """t98.copies_of, also through a `register T c ASM_REG("$n") = param;` declaration."""
    body = re.sub(r"[ \t]*ASM_REG\([^)]*\)", "", text[b0:b1])
    return copies_of(body, param, 0, len(body))


def carriers(text, param, b0, b1):
    """Locals of the body that copy `param` and are assigned nowhere else (one declaration in the body)."""
    masked = mask_comments(text)[b0:b1]
    out = []
    for c in sorted(_copies(text, param, b0, b1)):
        ds = [d for d in decls_of(text, c) if b0 < d[2][0] < b1]
        if len(ds) != 1 or ds[0][1]:
            continue
        sets = re.findall(r"(?<![\w.>])%s[ \t]*(?:[-+*/&|^]|<<|>>)?=(?!=)" % re.escape(c), masked)
        decl_init = "=" in re.sub(r"ASM_REG\([^)]*\)", "", text[ds[0][2][0]:ds[0][2][1]])
        if len(sets) - (1 if decl_init else 0) > 1 or re.search(r"&[ \t]*%s\b" % re.escape(c), masked) \
                or re.search(r"\b%s[ \t]*(?:\+\+|--)|(?:\+\+|--)[ \t]*%s\b" % (re.escape(c), re.escape(c)), masked):
            continue
        out.append(c)
    return out


def fold(text, fname, param, c):
    """Drop carrier c (declaration and its `c = param;`) and read `param` in its place."""
    sp = _span(text, fname)
    if sp is None:
        return None
    _p, b0, b1 = sp
    body = text[b0:b1]
    ds = decls_of(body, c)
    if len(ds) != 1:
        return None
    a, b = ds[0][2]
    body = body[:a] + body[b:]
    body, n = re.subn(r"^[ \t]*%s[ \t]*=[ \t]*(?:\(\s*\w[\w \t\*]*\)\s*)?%s[ \t]*;[^\n]*\n"
                      % (re.escape(c), re.escape(param)), "", body, flags=re.M)
    body = re.sub(r"(?<![\w.>])%s\b" % re.escape(c), param, body)
    return text[:b0] + body + text[b1:]


def retype_local(text, fname, c, ty):
    sp = _span(text, fname)
    if sp is None:
        return None
    _p, b0, b1 = sp
    body = text[b0:b1]
    ds = decls_of(body, c)
    if len(ds) != 1:
        return None
    a, b = ds[0][2]
    line = body[a:b]
    new = re.sub(r"^([ \t]*)(?:register[ \t]+)?%s\b" % re.escape(ds[0][0]), r"\g<1>" + ty, line, count=1)
    new = re.sub(r"[ \t]*ASM_REG\([^)]*\)", "", new)
    return text[:b0] + body[:a] + new + body[b:] + text[b1:]


def groups(text, params, b0, b1, mine):
    idx = [i for i, p in enumerate(params) if _scalar(p[1])]
    named = set()
    for s in mine:
        seg = text[s[3]:s[4]]
        if s[0] == "reg":
            le = text.find("\n", s[4])
            seg = text[text.rfind("\n", 0, s[3]) + 1:le]
        named.update(re.findall(r"\b([A-Za-z_]\w*)\b", seg))
    reach = [i for i in idx if params[i][0] in named or set(_copies(text, params[i][0], b0, b1)) & named]
    withc = sorted(set(reach) | {i for i in idx if _copies(text, params[i][0], b0, b1)})
    # the siblings the row already narrows through a carrier (`s16 held = param;` of an s32 formal)
    rank = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4}
    narrowed = []
    for i in idx:
        for c in carriers(text, params[i][0], b0, b1):
            ds = [d for d in decls_of(text, c) if b0 < d[2][0] < b1]
            cw = _scalar(ds[0][0]) if ds else None
            if cw and rank.get(cw, 4) < rank.get(_scalar(params[i][1]), 4):
                narrowed.append(i)
                break
    out = []
    for tag, g in (("reach", reach), ("narrowed", sorted(set(reach) | set(narrowed))), ("copied", withc),
                   ("run", [i for i in idx if withc and withc[0] <= i <= withc[-1]]), ("all", idx)):
        if g and all(g != o for _t, o in out):
            out.append((tag, g))
    return out


def candidates(text):
    out, seen, sig = [], {text}, unscored_text(text)
    n0 = len(sites_of(text))
    for fname, params, b0, b1 in functions(text):
        mine = [s for s in sites_of(text) if b0 < s[3] < b1]
        if not mine or not params:
            continue
        for gtag, g in groups(text, params, b0, b1, mine):
            for w in WIDTHS:
                want = {i: w for i in g if _scalar(params[i][1]) != w}
                if not want:
                    continue
                cmap = {i: carriers(text, params[i][0], b0, b1) for i in g}
                for cplan in ("fold", "retype16", "retypeP", "keep"):
                    if cplan != "keep" and not any(cmap.values()):
                        continue
                    # pins first (offsets of the pinned text), then the carrier edits, then the formals
                    names = {params[i][0] for i in g} | {c for i in g for c in cmap[i]}
                    named = [s for s in mine if s[0] == "reg" or any(
                        re.search(r"\b%s\b" % re.escape(n), text[s[3]:s[4]]) for n in names)]
                    only = [s for s in named if s[0] != "reg" or any(
                        re.search(r"\b%s\b" % re.escape(n), text[text.rfind("\n", 0, s[3]) + 1:text.find("\n", s[4])])
                        for n in names)]
                    for ptag, grp in (("all", mine), ("named+reg", named), ("named", only)):
                        if not grp or (ptag != "all" and len(grp) == len(mine)) \
                                or (ptag == "named" and len(grp) == len(named)):
                            continue
                        cur = erase_many(text, grp, clean_notes=True)
                        ok = True
                        for i in g:
                            for c in cmap[i]:
                                if cplan == "fold":
                                    nxt = fold(cur, fname, params[i][0], c)
                                elif cplan == "retype16":
                                    nxt = retype_local(cur, fname, c, "s16")
                                elif cplan == "retypeP":
                                    nxt = retype_local(cur, fname, c, want.get(i, _scalar(params[i][1])))
                                else:
                                    nxt = cur
                                if nxt is None:
                                    ok = False; break
                                cur = nxt
                        if not ok:
                            continue
                        cur2 = _retype_all(cur, fname, params, want)
                        if cur2 is None:
                            continue
                        if cur2 in seen or unscored_text(cur2) != sig or len(sites_of(cur2)) >= n0:
                            continue
                        seen.add(cur2)
                        out.append(("%s:%s=%s:%s:%s" % (fname, gtag, w, cplan, ptag), cur2))
                        if len(out) >= MAX_CANDS:
                            return out
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t110_paramfold"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        sites = sites_of(text)
        if not sites:
            return "no pin sites"
        for fname, params, b0, b1 in functions(text):
            mine = [s for s in sites if b0 < s[3] < b1]
            if mine and params and any(g for _t, g in groups(text, params, b0, b1, mine)[:2]):
                if any(carriers(text, p, b0, b1) for p, t, _a, _b in params if _scalar(t)) \
                        or groups(text, params, b0, b1, mine)[0][0] == "reach":
                    return None
        return "no pinned function whose scalar formal a pin reaches (directly or through a carrier)"

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
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried,
                                  signature_change=label.split(":")[0])
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
