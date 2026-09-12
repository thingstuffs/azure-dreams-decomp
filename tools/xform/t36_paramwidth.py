"""T36: a pinned copy of a narrow parameter, with the parameter declared one width up.

APPEARS     `register u8 saved_x ASM_REG("$22"); ... saved_x = tile_x;` where `tile_x` is a `u8`/`s8`/
            `u16`/`s16` parameter of the enclosing function: m2c names the copy it sees in a callee-saved
            register and types the parameter from it. Without the pin, the parameter's
            `move $sN, $aM` (and the save of `$sN`) sit earlier in the prologue than in retail.
RESOLVES    the parameter declared wider than its copy (`u16 tile_x` feeding `u8 saved_x`). The copy
            then narrows, gcc no longer merges it into the parameter's entry move, and it is scheduled
            from its own source line, where retail has it. Found by hand (dungeon/func_800CC510,
            2026-09-12): both `ASM_REG` pins off, byte-exact. `s32` parameters did not do it, and
            dropping the copies (natural.py dropcopy) left the residue unchanged.
POPULATION  2026-09-12 atlas residue map: 237 prologue-reorder pins in 129 functions, 182 of them on
            copies of parameters. First sweep (121 eligible rows): 57 rows / 102 pins byte-exact,
            51 of them through `all+1`. Mostly one spawner shape across overlays:
            `void *f(s16 kind, s8 x, s8 y, s16 z)` with `saved_x`/`saved_y` pinned to $22/$21.

Candidates: every copied parameter widened together (u8->u16, s8->s16, u16->u32, s16->s32), then all
to s32, then each parameter alone through its menu. The pins of the copies go (a pinned narrow
parameter counts as its own copy). A same-file prototype changes with the definition. The byte
verifier decides.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments, decls_of
except ImportError:
    from t29_addrsym import mask_comments, decls_of

NARROW = {"u8": ["u16", "s16", "s32", "u32"], "s8": ["s16", "u16", "s32"],
          "u16": ["u32", "s32"], "s16": ["s32", "u32"], "M2C_UNK8": ["s16", "u16", "s32"],
          "M2C_UNK16": ["s32", "u32"]}
DEF_RE = re.compile(r"^[A-Za-z_][\w \t\*]*?\b(?P<name>\w+)\s*\((?P<params>[^;{}()]*)\)\s*\{", re.M)
KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof"}
MAX_CANDS = 24


def functions(text):
    """Each definition: (name, [(param, type, type_start, type_end)], body_start, body_end)."""
    masked, out = mask_comments(text), []
    for m in DEF_RE.finditer(masked):
        if m.group("name") in KEYWORDS:
            continue
        depth, i = 0, m.end() - 1
        while i < len(masked):
            depth += (masked[i] == "{") - (masked[i] == "}")
            if depth == 0:
                break
            i += 1
        params, pos = [], m.start("params")
        for part in m.group("params").split(","):
            pm = re.fullmatch(r"\s*(?P<type>[A-Za-z_][\w \t\*]*?)\s*\b(?P<name>[A-Za-z_]\w*)\s*", part)
            if pm:
                params.append((pm.group("name"), pm.group("type").strip(), pos + pm.start("type"),
                               pos + pm.start("type") + len(pm.group("type").strip())))
            pos += len(part) + 1
        out.append((m.group("name"), params, m.end() - 1, i))
    return out


def pairs(text):
    """(function, local, param) for every pinned local that copies a narrow parameter."""
    masked, sites, out = mask_comments(text), sites_of(text), []
    for name, params, b0, b1 in functions(text):
        narrow = {p: ty for p, ty, _, _ in params if ty in NARROW}
        if not narrow:
            continue
        pinned = set()
        for s in sites:
            if b0 < s[3] < b1:
                pinned.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
        for v in sorted(pinned):
            if v in narrow:
                out.append((name, v, v)); continue
            V = re.escape(v)
            srcs = set(re.findall(r"(?<![\w.>])%s\s*=(?!=)\s*(?:\(\s*\w+\s*\)\s*)?(\w+)\s*;" % V, masked[b0:b1]))
            for _, _, (a, b) in decls_of(text, v):
                if b0 < a < b1:
                    srcs.update(re.findall(r"=\s*(?:\(\s*\w+\s*\)\s*)?(\w+)\s*;", masked[a:b]))
            for p in sorted(srcs & set(narrow)):
                out.append((name, v, p))
    return out


def build(text, fname, widen, locals_):
    """Retype the parameters in `widen` {param: type} (definition and same-file prototypes), then
    erase every pin in the function that names one of `locals_`."""
    F = next((f for f in functions(text) if f[0] == fname), None)
    if F is None:
        return None
    edits = [(a, b, widen[p]) for p, ty, a, b in F[1] if p in widen]
    masked = mask_comments(text)
    idx = {p: i for i, (p, _, _, _) in enumerate(F[1])}
    for m in re.finditer(r"\b%s\s*\((?P<params>[^;{}()]*)\)\s*;" % re.escape(fname), masked):
        parts, pos = m.group("params").split(","), m.start("params")
        if len(parts) == len(F[1]):
            for i, part in enumerate(parts):
                p = next((q for q, j in idx.items() if j == i), None)
                old = F[1][i][1]
                tm = re.search(r"\b%s\b" % re.escape(old), part) if p in widen else None
                if tm:
                    edits.append((pos + tm.start(), pos + tm.end(), widen[p]))
                pos += len(part) + 1
    t = text
    for a, b, rep in sorted(edits, reverse=True):
        t = t[:a] + rep + t[b:]
    F = next((f for f in functions(t) if f[0] == fname), None)
    pins = [s for s in sites_of(t) if F and F[2] < s[3] < F[3]
            and any(re.search(r"\b%s\b" % re.escape(v), t[s[3]:s[4]]) for v in locals_)]
    if not pins:
        return None
    t = erase_many(t, pins, clean_notes=True)
    if unscored_text(t) != unscored_text(text):
        return None
    return t


def candidates(text):
    ps, out, seen = pairs(text), [], set()
    types = {}
    for name, params, _, _ in functions(text):
        for p, ty, _, _ in params:
            types[(name, p)] = ty

    def add(label, fname, widen, locals_):
        t = build(text, fname, widen, locals_)
        if t is not None and t not in seen:
            seen.add(t); out.append((label, t))

    for fname in sorted({f for f, _, _ in ps}):
        mine = [(v, p) for f, v, p in ps if f == fname]
        locs = {v for v, _ in mine}; prm = sorted({p for _, p in mine})
        narrow = sorted(p for (f, p), ty in types.items() if f == fname and ty in NARROW)
        pick = lambda p, k: NARROW[types[(fname, p)]][min(k, len(NARROW[types[(fname, p)]]) - 1)]
        add("paramwidth:%s:all+1" % fname, fname, {p: pick(p, 0) for p in prm}, locs)
        add("paramwidth:%s:narrow+1" % fname, fname, {p: pick(p, 0) for p in narrow}, locs)
        for k in range(1, 4):       # the k-th choice of every menu at once (u16 for s8, u32 for s16, ...)
            add("paramwidth:%s:all+%d" % (fname, k + 1), fname, {p: pick(p, k) for p in prm}, locs)
            add("paramwidth:%s:narrow+%d" % (fname, k + 1), fname, {p: pick(p, k) for p in narrow}, locs)
        add("paramwidth:%s:all=s32" % fname, fname, {p: "s32" for p in prm}, locs)
        for p in prm:
            copies = {v for v, q in mine if q == p}
            for ty in NARROW[types[(fname, p)]]:
                add("paramwidth:%s:%s=%s" % (fname, p, ty), fname, {p: ty}, copies)
    return out[:MAX_CANDS]


class T:
    name = "t36_paramwidth"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not pairs(text):
            return "no pinned copy of a narrow parameter"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        cands.sort(key=lambda c: len(sites_of(c[1])))              # most pins removed first
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
