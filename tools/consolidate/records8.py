"""records8.py - room.py (phase 7's array-of-records rewrite) generalised to D_80082660 (ObjectIndexSlot[]) and
   D_8006DE24 (DefEntry[]).  rewrite(obj, text) -> (text, notes) | (None, reason).  Pointer-typed view members map onto
   a pointer field without a cast (void * converts); every other rule is room.py's (semantics-preserving)."""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import room
OBJ = {
 "2660": dict(SYM="D_80082660", HDR='#include "shared/object_index_slots.h"', RSIZE=8,
              FIELDS=[(0, "unk_00", 1, True, "signed char"), (1, "unk_01", 1, True, "signed char"),
                      (2, "unk_02", 1, False, "unsigned char"), (4, "object", 4, None, "void *")]),
 "de24": dict(SYM="D_8006DE24", HDR='#include "shared/def_table.h"', RSIZE=0x14,
              FIELDS=[(0, "unk_00", 4, True, "int"), (4, "unk_04", 4, True, "int"), (8, "unk_08", 4, True, "int"),
                      (0xC, "unk_0C", 4, True, "int"), (0x10, "unk_10", 1, False, "unsigned char"),
                      (0x11, "unk_11", 1, False, "unsigned char"), (0x12, "kind", 1, False, "unsigned char"),
                      (0x13, "unk_13", 1, False, "unsigned char")]),
}
def member_expr(views, V, m, idx):
    mem = views[V][0].get(m)
    if mem is None: return None
    off, sz, sg, cty, cnt, sub = mem
    if cnt or sub: return None
    f = room.BY.get(off)
    if f is None: return None
    base = "%s[%s].%s" % (room.SYM, idx, f[1])
    if "*" in cty or f[3] is None:
        if "*" in cty and f[3] is None and sz == 4: return base            # pointer view on the pointer field
        if f[2] == sz: return "(*(%s *)&%s)" % (cty, base)
        return None
    if f[2] == sz and f[3] == sg: return base
    return "(*(%s *)&%s)" % (cty, base)
room.member_expr = member_expr
def rewrite(key, text):
    o = OBJ[key]
    room.SYM, room.HDR, room.RSIZE, room.FIELDS = o["SYM"], o["HDR"], o["RSIZE"], o["FIELDS"]
    room.BY = {f[0]: f for f in o["FIELDS"]}
    return room.rewrite(text)

# ---- D_80082660 byte-view idioms (m2c declared it `u8` / `u8[]` and wrote `*((i * 8) + &D) = 0`, `D[i * 8] = 0`)
E = r"(?:[^()\[\];]|\((?:[^()]|\([^()]*\))*\))+?"
def pre(key, text):
    """&D on a scalar byte declaration -> ((T *)D): the same pointer value and type once D is an array of records"""
    o = OBJ[key]; sym = o["SYM"]
    m = re.search(r"^[ \t]*extern\s+(u8|s8|unsigned char|signed char|char)\s+%s\s*;" % sym, text, re.M)
    if not m: return text
    text = text[:m.start()] + re.sub(r"%s\s*;" % sym, "%s[];" % sym, text[m.start():m.end()]) + text[m.end():]   # scalar -> unsized array: D decays to the old &D
    return re.sub(r"\(\s*&\s*%s\s*\)|&\s*%s\b" % (sym, sym), "((%s *)%s)" % (m.group(1), sym), text)
def natural(key, text):
    """byte stores through ((u8 *)D)[i * 8] / *((i * 8) + ((u8 *)D)) / ((u8 *)D)[k] -> the record field"""
    o = OBJ[key]; sym = o["SYM"]; by = {f[0]: f for f in o["FIELDS"]}; rs = o["RSIZE"]; n = [0]
    cast = r"\(\((?:u8|s8|unsigned char|signed char|char) \*\)%s\)" % sym
    def f0(m):
        n[0] += 1; return "%s[%s].%s%s" % (sym, m.group(1).strip(), by[0][1], m.group(2))
    t = re.sub(r"\*\s*\(\s*\(\s*(%s)\s*\*\s*%d\s*\)\s*\+\s*%s\s*\)(\s*=[^=])" % (E, rs, cast), f0, text)
    t = re.sub(r"%s\s*\[\s*(%s)\s*\*\s*%d\s*\](\s*=[^=])" % (cast, E, rs), f0, t)
    def fk(m):
        k = int(m.group(1), 0); f = by.get(k % rs)
        if not f or f[2] != 1: return m.group(0)
        n[0] += 1; return "%s[%d].%s%s" % (sym, k // rs, f[1], m.group(2))
    t = re.sub(r"%s\s*\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\](\s*=[^=])" % cast, fk, t)
    return t, n[0]
def rewrite2(key, text, nat=True):
    r, why = rewrite(key, pre(key, text))
    if r is None or not nat: return r, why
    t, k = natural(key, r)
    return t, why + ("; natural %d" % k if k else "")
