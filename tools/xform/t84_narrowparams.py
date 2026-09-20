"""T84: pinned callee-saved copies of `s32` parameters dropped by declaring the parameter group narrow (s16/u16).

APPEARS     `register s32 saved_offset_y ASM_REG("$19") = offset_y;` (one or more) at the top of a function whose
            parameters are all `s32`; retail loads the stack-passed parameters into callee-saved registers in the
            prologue and holds them across the allocation call, the pin-erased build reloads them from the argument
            area at each use and the frame shrinks (the CHANGED|17-32 residue of the four sprite-spawn rows).
RESOLVES    gcc 2.7.2 function.c assign_parms: a parameter whose declared type is narrower than the mode it is passed
            in (PROMOTE_PROTOTYPES: `s16` arrives as an int) gets a REAL pseudo with a conversion copy at function
            entry instead of a REG_EQUIV memory it can be reloaded from, so the value is a call-crossing pseudo that
            global.c allocates callee-saved - the prologue `lw $19,64($sp)` retail has.  Narrowing the pinned
            parameters alone leaves the allocation order wrong (offset_x took $20); narrowing the whole group of
            sibling offsets (`s16 offset_x, s16 offset_y, s16 offset_z`) reproduces retail's order too:
            dungeon/func_8132DED0, func_8132E6F8, func_8132E018, func_8132ED0C byte-exact with no register
            scaffolding (2026-09-20, by hand after the sol pack r59_sol_large7 measured every placement variant at
            distance 26-30).  t36_paramwidth widens narrow copies; this is the other direction on `s32` copies.
CANDIDATES  the pinned parameters P; P plus the parameter just before the first of them; every parameter from that
            one to the last; every scalar `s32` parameter - each group as s16, then u16; the copies dropped (their
            uses renamed to the parameter) and the function's remaining pins erased jointly, or left in place.
            A same-file prototype changes with the definition.  Ranked by the cc1 listing distance to the pinned
            text; `vf` on listing-exact candidates only.  A signature change: `info["signature_change"]` names the
            function so the landing step can review textual callers (none for the four rows above).
"""
import re, sys, difflib
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    import screen

MAX_VERIFY = 4
COPY = re.compile(r"^[ \t]*register[ \t]+s32[ \t]+(?P<local>[A-Za-z_]\w*)[ \t]+ASM_REG\(\"\$\d+\"\)[ \t]*=[ \t]*(?P<param>[A-Za-z_]\w*)[ \t]*;[^\n]*\n", re.M)
DEF = re.compile(r"^(?P<head>(?:static[ \t]+)?[A-Za-z_][\w \t\*]*?\b(?P<name>[A-Za-z_]\w*))[ \t]*\((?P<params>[^;{}]*?)\)[ \t]*\n?[ \t]*\{", re.M)


def definitions(text):
    """[(name, params_span, [(type, name, span)])] for every function definition with a parenthesised parameter list."""
    masked = mask_comments(text)
    out = []
    for m in DEF.finditer(masked):
        if m.group("name") in ("if", "for", "while", "switch", "return"):
            continue
        ps, plist, pos = m.group("params"), [], m.start("params")
        for part in ps.split(","):
            pm = re.match(r"(\s*)(?P<type>[A-Za-z_][\w \t\*]*?)[ \t\*]+(?P<pname>[A-Za-z_]\w*)\s*$", part)
            if pm:
                tspan = (pos + pm.start("type"), pos + pm.end("type"))
                plist.append((pm.group("type").strip(), pm.group("pname"), tspan, "*" in part))
            pos += len(part) + 1
        if plist:
            out.append((m.group("name"), (m.start("params"), m.end("params")), plist))
    return out


def sites_in(text):
    """[(fname, params, copies)] where copies = [(local, param, match)] are pinned s32 copies of s32 parameters."""
    out = []
    defs = definitions(text)
    for name, span, params in defs:
        s32 = {p for t, p, _, ptr in params if t == "s32" and not ptr}
        copies = [(m.group("local"), m.group("param"), m) for m in COPY.finditer(text) if m.group("param") in s32]
        if copies:
            out.append((name, params, copies))
    return out


def retype(text, fname, group, ty):
    """The definition's (and any same-file prototype's) parameters in `group` retyped to `ty`."""
    out = text
    for name, span, params in definitions(out):
        if name != fname:
            continue
        for t, p, (a, b), ptr in sorted(params, key=lambda x: -x[2][0]):
            if p in group:
                out = out[:a] + ty + out[b:]
        break
    proto = re.compile(r"^(extern[ \t]+)?[A-Za-z_][\w \t\*]*\b%s[ \t]*\(([^;{}]*)\)[ \t]*;" % re.escape(fname), re.M)
    m = proto.search(out)
    if m:
        parts = m.group(2).split(",")
        names = [p for _, p, _, _ in next((ps for n, _, ps in definitions(text) if n == fname), [])]
        if len(parts) == len(names):
            new = []
            for part, pn in zip(parts, names):
                new.append(re.sub(r"\bs32\b", ty, part, count=1) if pn in group else part)
            out = out[:m.start(2)] + ",".join(new) + out[m.end(2):]
    return out


def drop_copies(text, copies):
    out = text
    for local, param, m in sorted(copies, key=lambda c: -c[2].start()):
        out = out[:m.start()] + out[m.end():]
    for local, param, _ in copies:
        out = re.sub(r"\b%s\b" % re.escape(local), param, out)
    return out


def candidates(text):
    """[(label, text)] narrowed variants, most specific group first."""
    outs, seen = [], set()
    for fname, params, copies in sites_in(text):
        names = [p for _, p, _, _ in params]
        scalars = [p for t, p, _, ptr in params if t == "s32" and not ptr]
        pinned = [p for _, p, _ in copies]
        k = min(names.index(p) for p in pinned)
        groups = [("pinned", pinned)]
        if k > 0 and names[k - 1] in scalars:
            groups.append(("prev+pinned", [names[k - 1]] + pinned))
            groups.append(("prev..end", [p for p in names[k - 1:] if p in scalars]))
        groups.append(("pinned..end", [p for p in names[k:] if p in scalars]))
        groups.append(("all", scalars))
        for label, group in groups:
            key = tuple(sorted(set(group)))
            if key in seen or not group:
                continue
            seen.add(key)
            for ty in ("s16", "u16"):
                t = drop_copies(retype(text, fname, set(group), ty), copies)
                outs.append(("%s:%s:%s" % (fname, label, ty), t, fname))
    return outs


class T:
    name = "t84_narrowparams"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if sites_in(text) else "no pinned s32 copy of an s32 parameter"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, listings, verifies = len(sites_of(text)), 0, 0
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        ranked = []
        for label, t, fname in candidates(text):
            for mode in ("erase-all", "copies-only"):
                cand = erase_many(t, sites_of(t), clean_notes=True) if mode == "erase-all" else t
                if len(sites_of(cand)) >= pins_in:
                    continue
                lst = screen.compile_s(row, cand); listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))
                ranked.append((d, len(sites_of(cand)), label + ":" + mode, cand, fname))
        ranked.sort(key=lambda x: (x[0], x[1]))
        best = ranked[0][0] if ranked else None
        for d, n, label, cand, fname in ranked:
            if d or verifies >= MAX_VERIFY:
                break
            verifies += 1
            if vf(cand).get("exact"):
                return cand, {"step": label, "listings": listings, "tried": verifies, "pins_in": pins_in,
                              "pins_out": len(sites_of(cand)), "signature_change": fname}
        return None, {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": pins_in, "best": best}
