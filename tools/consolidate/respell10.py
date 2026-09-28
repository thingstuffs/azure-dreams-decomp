"""respell10.py: mechanical respell onto the phase-10 GameWork layout (gameWork+0x1DC..0x1FB is `map`, a MapGrid;
   0x1FC is randSeed).  gameWork.F / P->F (P declared GameWork *) / ((GameWork *)x)->F for the old flat fields ->
   the member path; `&gameWork.unk_1DC` directly under a pointer cast -> `&gameWork.map` (the sub-object address).
   Offsets and sizes are unchanged (unk_1DC..unk_1E8 were int, now void * - same lw/sw).
   pre8333C(text): a TU's own `extern V D_8008333C;` (a struct view of the same bytes) -> dropped, uses spelled
   `((V *)&gameWork.map)->m` for fold10 to map onto MapGrid fields."""
import re
M = {"unk_1DC": "map.cells", "unk_1E0": "map.unk_04", "unk_1E4": "map.unk_08", "unk_1E8": "map.unk_0C", "unk_1EC": "map.unk_10",
     "unk_1F0": "map.shiftX", "unk_1F2": "map.shiftY", "unk_1F4": "map.maskX", "unk_1F6": "map.maskY", "unk_1F8": "map.spanX",
     "unk_1FA": "map.spanY", "unk_1FC": "randSeed"}
F = "|".join(sorted(M, key=len, reverse=True))
def respell(text):
    n = [0]
    def cast(m): n[0] += 1; return m.group(1) + "&gameWork.map"
    t = re.sub(r"(\(\s*(?:const\s+)?(?:struct\s+)?(?:unsigned\s+|signed\s+)?\w+\s*\*+\s*\)\s*\(?\s*\(?\s*)&\s*gameWork\s*\.\s*unk_1DC\b(?!\s*[\[.])", cast, text)
    def dot(m): n[0] += 1; return "gameWork.%s" % M[m.group(1)]
    t = re.sub(r"\bgameWork\s*\.\s*(%s)\b" % F, dot, t)
    vs = set(re.findall(r"\bGameWork\s*\*\s*(?:const\s+)?([A-Za-z_]\w*)", t))
    if vs:
        def arr(m): n[0] += 1; return "%s->%s" % (m.group(1), M[m.group(2)])
        t = re.sub(r"\b(%s)\s*->\s*(%s)\b" % ("|".join(sorted(vs)), F), arr, t)
    def castacc(m): n[0] += 1; return "%s->%s" % (m.group(1), M[m.group(2)])
    t = re.sub(r"(\(\s*\(\s*GameWork\s*\*\s*\)\s*\w+\s*\))\s*->\s*(%s)\b" % F, castacc, t)
    # 0x008: `void * unk_008` -> `int buttons` (the s32 casts every bit test carried go; other casts stay)
    B = r"(gameWork\s*\.\s*|\(\s*\(\s*GameWork\s*\*\s*\)\s*\w+\s*\)\s*->\s*%s)" % ("".join("|\\b%s\\s*->\\s*" % v for v in sorted(vs)))
    def bcast(m): n[0] += 1; return re.sub(r"\s*(\.|->)\s*$", r"\1", m.group(1)) + "buttons"
    t = re.sub(r"\(\s*\(\s*(?:s32|int|signed int|long)\s*\)\s*%s\s*unk_008\s*\)" % B, bcast, t)
    t = re.sub(r"\(\s*(?:s32|int|signed int|long)\s*\)\s*%s\s*unk_008\b" % B, bcast, t)
    t = re.sub(r"%s\s*unk_008\b" % B, bcast, t)
    return t, n[0]
def pre8333C(text):
    m = re.search(r"^[ \t]*extern\s+(?:struct\s+)?(\w+)\s+D_8008333C\s*;[^\n]*\n", text, re.M)
    if not m or m.group(1) in ("s8", "u8", "s16", "u16", "s32", "u32", "int", "short", "char"): return text, 0
    V = m.group(1)
    t = text[:m.start()] + text[m.end():]
    k = len(re.findall(r"\bD_8008333C\b", t))
    t = re.sub(r"&\s*D_8008333C\b(?!\s*\.)", "((%s *)&gameWork.map)" % V, t)
    t = re.sub(r"\bD_8008333C\s*\.\s*", "((%s *)&gameWork.map)->" % V, t)
    if re.search(r"\bD_8008333C\b", t): return text, 0
    if '#include "shared/game_work.h"' not in t:
        t = t.replace('#include "common.h"\n', '#include "common.h"\n#include "shared/game_work.h"\n', 1)
    return t, k
def t3flag(text):
    """D_8006CCF8 -> dirSpriteFlag (shared/dir_step.h; names.tsv alias spells it back before the assembler): the row's
    one local `extern ... D_8006CCF8[...];` goes."""
    m = list(re.finditer(r"^[ \t]*extern\s+(?:unsigned char|u8|s8|char)\s+D_8006CCF8\s*\[[^\]]*\]\s*;[^\n]*\n", text, re.M))
    if len(m) != 1 or len(re.findall(r"\bextern[^;]*\bD_8006CCF8\b", text)) != 1: return text, 0
    t = text[:m[0].start()] + text[m[0].end():]
    k = len(re.findall(r"\bD_8006CCF8\b", t))
    t = re.sub(r"\bD_8006CCF8\b", "dirSpriteFlag", t)
    if '#include "shared/dir_step.h"' not in t:
        t = t.replace('#include "common.h"\n', '#include "common.h"\n#include "shared/dir_step.h"\n', 1)
        if '#include "shared/dir_step.h"' not in t: return text, 0
    return t, k
