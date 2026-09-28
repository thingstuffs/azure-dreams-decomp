"""t1.py VARIANT: task 1 (OPEN_ITEMS #17) - the three s16 scales at 0x80084808/0A/0C as one shared array.
   Writes t1/<variant>/inc/shared/sound_volume.h + t1/<variant>/<row>.c and check()s each row."""
import json, os, re, sys
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent
V = sys.argv[1] if __name__ == "__main__" else ""   # decl suffix: "" (unsized) | "3" | "4" | "8"
D = LANE / "t1" / ("v" + (V or "u"))
if __name__ == "__main__": (D / "inc/shared").mkdir(parents=True, exist_ok=True); os.environ["TYPES_INC"] = str(D / "inc")
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, REPO
from check import check
if __name__ == "__main__": (D / "inc/shared/sound_volume.h").write_text(open(LANE / "t1/sound_volume.h.in").read().replace("@N@", V))
R = row_index()
ROWS = "w_80053DF0 w_80053E20 w_80053E90 w_80054D64 w_800552C8 w_8005560C w_800559B4".split()
def edit(t):
    t = re.sub(r"^extern s16 D_8008480[8AC](\[8\])?;\n", "", t, flags=re.M)
    t = re.sub(r"/\* S_80084808: single s16 field.*?\} S_80084808;\n\n", "", t, flags=re.S)
    t = re.sub(r"\bD_8008480A\[0\]|\bD_8008480A\b(?!\[)", "volumeScale[1]", t)
    t = re.sub(r"\bD_8008480C\[0\]", "volumeScale[2]", t)
    t = re.sub(r"\bD_80084808\[(\d)\]", r"volumeScale[\1]", t)
    first = t.index('#include "common.h"\n') + len('#include "common.h"\n')
    return t[:first] + '#include "shared/sound_volume.h"\n' + t[first:]
if __name__ == "__main__":
    for f in ROWS:
        rid = "slus/" + f
        t = edit((REPO / "src" / (rid + ".c")).read_text())
        assert not re.search(r"D_8008480[8AC]", t), rid
        (D / (f + ".c")).write_text(t)
        rec = check(R[rid], t)
        print(V or "unsized", f, rec.get("listing"), rec.get("abs_listing"), rec.get("extern_sizes"), rec.get("score"), rec.get("diff", "")[:4] if rec.get("listing") != "identical" else "")
