"""T40: a prologue-reorder pin, with the parameter its residue names retyped.

APPEARS     a pin whose single-erasure residue is a prologue reorder: `move $sX, $aM` plus the save of
            `$sX` move. 2026-09-12 refreshed atlas: 205 such pins in 131 functions, after t36.
RESOLVES    t36 found that a parameter's declared width decides where its entry copy is scheduled
            (`u16 tile_x` feeding `u8 saved_x`: both pins off). Here the residue itself names the
            parameter ($aM = parameter M), whether or not a pinned local copies it.
RESULT      first sweep (2026-09-12, 276 targets / 174 rows): 8 rows. Five are `s8 arg1` -> `s16` in the
            spawner shape (t36's joint widening had missed them), two `s16` -> `s32`, one
            `s32` -> `s16`.
Candidates: parameter M's type through TYPES, with that one pin erased; then every narrow
parameter one width up with the pin erased. A same-file prototype changes with the definition
(t36.build). Targets come from the residue map: JSONL {id, site, param} at $T40_TARGETS.
"""
import json, os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from . import t36_paramwidth as P
except ImportError:
    import t36_paramwidth as P

TYPES = ["s32", "u32", "s16", "u16", "s8", "u8"]
ALIAS = {"M2C_UNK": "s32", "M2C_UNK8": "s8", "M2C_UNK16": "s16", "M2C_UNK32": "s32", "int": "s32"}
TARGETS = os.environ.get("T40_TARGETS", "")
_T = None


def targets():
    global _T
    if _T is None:
        _T = {}
        if TARGETS and os.path.exists(TARGETS):
            for l in open(TARGETS):
                r = json.loads(l)
                _T.setdefault(r["id"], []).append((r["site"], r["param"]))
    return _T


def candidates(text, rid):
    sites, out, seen = sites_of(text), [], set()
    for site, m in targets().get(rid, []):
        if site >= len(sites):
            continue
        pos = sites[site][3]
        F = next((f for f in P.functions(text) if f[2] < pos < f[3]), None)
        if F is None or m >= len(F[1]):
            continue
        pname, pty = F[1][m][0], F[1][m][1]
        if "*" in pty or ALIAS.get(pty, pty) not in TYPES:
            continue
        menus = [(pname + "=" + ty, {pname: ty}) for ty in TYPES if ty != ALIAS.get(pty, pty)]
        narrow = {p: P.NARROW[ty][0] for p, ty, _, _ in F[1] if ty in P.NARROW}
        if narrow:
            menus.append(("narrow+1", narrow))
        for label, widen in menus:
            t = P.build(text, F[0], widen, set())
            if t is None:
                continue
            ss = sites_of(t)
            if len(ss) != len(sites):
                continue
            t = erase_many(t, [ss[site]], clean_notes=True)
            if t not in seen and unscored_text(t) == unscored_text(text):
                seen.add(t); out.append(("prologue:%d:%s" % (site, label), t))
    return out


class T:
    name = "t40_prologue_param"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if row["id"] not in targets():
            return "no prologue-reorder target"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text, row["id"])
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
