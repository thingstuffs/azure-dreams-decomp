"""preamble8.py: drop DEAD copies of old common.h content (game.h + globals.h, flattened by m2c into self-contained
   rows) - struct S_80083178 / S_80083178State / S_80083178Vector, MonsterInitialStats / Trap / StatGrowth and the
   globals.h externs (D_800814C8, D_80081550/54/58, D_80071298, D_80071250, D_800712B4, D_80084130, D_80084808,
   D_80083CE8) - where the name is not used anywhere else in the text.  Only rows without `#include "common.h"`.
   Input text = draft8/ (if any) else src; writes draft8/.  Declarations only: cc1 listing identical by construction
   (checked by listing8)."""
import re, sys, subprocess
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
NAMES = ["S_80083178", "S_80083178State", "S_80083178Vector", "MonsterInitialStats", "Trap", "StatGrowth",
         "D_800814C8", "D_80081550", "D_80081554", "D_80081558", "D_80071298", "D_80071250", "D_800712B4",
         "D_80084130", "D_80084808", "D_80083CE8"]
def blocks(t, name):
    pats = [r"^struct %s\s*\{.*?^\};[ \t]*\n" % name, r"^typedef struct\s*\{[^{}]*\}\s*%s;[ \t]*\n" % name,
            r"^extern [^\n;]*\b%s\s*(?:\[[^\]\n]*\])?\s*;[ \t]*\n" % name]
    return [m for p in pats for m in re.finditer(p, t, flags=re.M | re.S)]
def strip(t):
    changed = True; removed = []
    while changed:
        changed = False
        for n in NAMES:
            bs = blocks(t, n)
            if not bs: continue
            rest = t
            for m in sorted(bs, key=lambda m: -m.start()): rest = rest[:m.start()] + rest[m.end():]
            code = re.sub(r"/\*.*?\*/|//[^\n]*", "", rest, flags=re.S)
            if re.search(r"\b%s\b" % n, code): continue
            t = rest; removed.append(n); changed = True
    return t, removed
if __name__ == "__main__":
    fs = set()
    for s in NAMES[6:15]:
        fs |= set(subprocess.run(["grep", "-rlw", s, "src", "--include=*.c"], cwd=REPO, capture_output=True, text=True).stdout.split())
    out = []
    for f in sorted(fs):
        rid = f[4:-2]; src = REPO / f
        if '#include "common.h"' in src.read_text(errors="replace"): continue
        d = LANE / "draft8" / (rid + ".c"); t0 = d.read_text() if d.is_file() else src.read_text(errors="replace")
        t, rem = strip(t0)
        if rem:
            d.parent.mkdir(parents=True, exist_ok=True); d.write_text(t); out.append(rid)
            print(rid, len(rem), ",".join(rem))
    open(LANE / "results/preamble8_rows.txt", "w").write("\n".join(out) + "\n")
    print(len(out), "rows")
