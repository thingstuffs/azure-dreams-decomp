"""shtypes.py: field tables of the shared types parsed from the lane inc/shared headers (the `/* 0xOFF */ type name;`
   comment layout every shared header uses).  flat(T) -> [(off, size, ctype, path)] with nested structs expanded
   (GameWork.view.slot[i]...).  Also OBJ: shared object spellings -> (type, base offset)."""
import re
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent
INC = LANE / "inc" / "shared"
PRIM = {"char": 1, "signed char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2, "int": 4, "unsigned int": 4,
        "long": 4, "Fixed1616": 4, "u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4}
def _structs():
    S = {}
    for h in sorted(INC.glob("*.h")):
        t = h.read_text()
        for m in re.finditer(r"typedef (?:struct|union) (\w+) \{(.*?)\n\}\s*(\w+)\s*;", t, re.S):
            fields = []
            for fm in re.finditer(r"/\* 0x([0-9A-F]+) \*/\s*([\w ]+?)\s*(\*?)\s*(\w+)\s*(?:\[\s*(0x[0-9A-Fa-f]+|\d+)\s*\])?\s*;", m.group(2)):
                off = int(fm.group(1), 16); ty = fm.group(2).strip(); star = fm.group(3); name = fm.group(4)
                n = int(fm.group(5), 0) if fm.group(5) else None
                fields.append((off, (ty + " *") if star else ty, name, n))
            S[m.group(3)] = fields
    return S
S = _structs()
def size_of(ty):
    if ty.endswith("*"): return 4
    if ty in PRIM: return PRIM[ty]
    f = S[ty]; last = f[-1]
    return last[0] + size_of(last[1]) * (last[3] if last[3] is not None else 1)
def flat(T, base=0, prefix=""):
    out = []
    for off, ty, name, n in S[T]:
        if name.startswith("pad_"): continue
        cnt = n if n is not None else 1
        for i in range(cnt):
            p = prefix + name + ("[%d]" % i if n is not None else "")
            o = base + off + i * size_of(ty)
            if ty in S and ty != "Fixed1616": out += flat(ty, o, p + ".")
            elif ty == "Fixed1616": out += [(o, 4, "int", p + ".v"), (o, 2, "unsigned short", p + ".w.frac"), (o + 2, 2, "short", p + ".w.i"), (o, 4, "Fixed1616", p)]
            else: out.append((o, size_of(ty), ty, p))
    return out
OBJ = {"gameWork": ("GameWork", "gameWork."), "dungeonStatus": ("DungeonGlobalStatus", "dungeonStatus."),
       "D_80082E80": ("TileObject", "D_80082E80."), "D_80083780": ("EntityRec", "D_80083780."),
       "D_800814A8": ("EntityRec", "D_800814A8->"), "D_800E3D7C": ("EntityRec", "D_800E3D7C->"),
       "objectFlagBlock": ("ObjectFlagBlock", "objectFlagBlock."), "D_80083498": ("ObjectNodeHeader", "D_80083498.")}
if __name__ == "__main__":
    import sys
    for T in sys.argv[1:]:
        for r in flat(T): print("0x%03X %d %-16s %s" % r)

SIGNED_T = {"char", "signed char", "short", "int", "long", "Fixed1616"}
def leaves(T):
    """[(off, size, signed, ptr, path)] of the primitive leaves (Fixed1616 -> .v int and .w.i short)."""
    out = []
    for off, size, ty, path in flat(T):
        if ty == "Fixed1616": continue
        out.append((off, size, ty in SIGNED_T, ty.endswith("*"), path, ty))
    return out
def structs_at(T, base=0, prefix=""):
    """[(off, type, path)] of every struct-typed member node (sub-objects), incl. array elements."""
    out = []
    for off, ty, name, n in S[T]:
        if ty in S and ty != "Fixed1616":
            for i in range(n if n is not None else 1):
                p = prefix + name + ("[%d]" % i if n is not None else "")
                o = base + off + i * size_of(ty)
                out.append((o, ty, p)); out += structs_at(ty, o, p + ".")
    return out
def path_off(T, path):
    """offset and type of a member path like `view.slot[2]` / `unk_1DC` / `x.w.i` (None if unknown)."""
    if path == "": return 0, T
    for o, ty, p in structs_at(T):
        if p == path: return o, ty
    for o, sz, ty, p in flat(T):
        if p == path: return o, ty
    return None
