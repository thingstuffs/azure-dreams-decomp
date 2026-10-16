"""spell.py ROW 'OLD' 'NEW' [...]: literal replacements (OLD->NEW pairs) on the src text of ROW, drop a local
   `extern u8 D_8006DE24[...];`, add `#include "shared/def_table.h"`; check() against the lane inc/."""
import json, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, REPO
from check import check
import sys as _layout_sys
_layout_root = next(p for p in Path(__file__).resolve().parents if (p / "tools/source_layout.py").is_file())
_layout_sys.path.insert(0, str(_layout_root / "tools"))
from source_layout import row_path as layout_row_path
R = row_index()
def apply(rid, pairs, decl=r"^extern (u8|s8|unsigned char|char) D_8006DE24\[\w*\];\n", inc='#include "shared/def_table.h"\n'):
    t = (layout_row_path(rid, REPO)).read_text()
    for o, n in pairs:
        assert o in t, (rid, o); t = t.replace(o, n)
    if decl: t = re.sub(decl, "", t, flags=re.M)
    if inc and inc not in t:
        i = t.index('#include "common.h"\n') + len('#include "common.h"\n'); t = t[:i] + inc + t[i:]
    return t
if __name__ == "__main__":
    rid = sys.argv[1]; a = sys.argv[2:]
    t = apply(rid, list(zip(a[::2], a[1::2])))
    rec = check(R[rid], t)
    print(rec.get("listing"), rec.get("score"), rec.get("diff", [])[:6])
