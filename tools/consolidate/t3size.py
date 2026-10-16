"""t3size.py SYM: declared-size A/B for a small SLUS table: every row with a local `extern T SYM[...]` gets that line
   replaced by `extern u8 SYM[]` / `[8]` / `[16]`; check() each (verify.py byte score).  -> results/t3size_SYM.jsonl"""
import json, re, sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import row_index, REPO
from check import check
import sys as _layout_sys
_layout_root = next(p for p in Path(__file__).resolve().parents if (p / "tools/source_layout.py").is_file())
_layout_sys.path.insert(0, str(_layout_root / "tools"))
from source_layout import row_path as layout_row_path, source_items as layout_source_items
LANE = Path(__file__).resolve().parent.parent; R = row_index(); SYM = sys.argv[1]
VAR = {"unsized": "[]", "8": "[8]", "16": "[16]"}
def one(rid):
    t = (layout_row_path(rid, REPO)).read_text(errors="replace")
    m = list(re.finditer(r"^[ \t]*extern\s+[^;]*\b%s\b[^;]*;[^\n]*\n" % SYM, t, re.M))
    out = {"id": rid, "cfg": R[rid]["cfg"], "decls": [x.group(0).strip()[:60] for x in m]}
    if len(m) != 1: out["skip"] = "decls %d" % len(m); return out
    for k, v in VAR.items():
        n = t[:m[0].start()] + "extern u8 %s%s;\n" % (SYM, v) + t[m[0].end():]
        c = check(R[rid], n); out[k] = bool((c.get("score") or {}).get("exact"))
    return out
if __name__ == "__main__":
    ids = [rid for rid, p in layout_source_items(REPO) if re.search(r"\b%s\b" % SYM, p.read_text(errors="replace"))]
    ids = [i for i in ids if i in R]
    import collections; C = collections.Counter()
    with ProcessPoolExecutor(14) as ex, open(LANE / "results" / ("t3size_%s.jsonl" % SYM), "w") as fh:
        for o in ex.map(one, ids):
            fh.write(json.dumps(o) + "\n")
            C["skip" if o.get("skip") else "%s u:%d 8:%d 16:%d" % (o["cfg"].split("-")[-1] if "-G" in o["cfg"] else o["cfg"], o["unsized"], o["8"], o["16"])] += 1
    for k, v in sorted(C.items()): print(v, k)
