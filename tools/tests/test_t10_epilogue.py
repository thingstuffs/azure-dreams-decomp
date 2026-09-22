#!/usr/bin/env python3
"""t10_epilogue unit test: run the transform on the PRE-landing text of the four rows that
needed the shared-tail action by hand on 2026-09-22 and check the candidate verifies exact."""
import json, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, parse_cfg
from verify import verify
from pin_census import landing_refusal
import xform
T = xform.load("t10_epilogue")
INCLUDE = ROOT / "include"

CASES = [   # (row id, git rev holding the PRE-landing text)
    ("main/func_8001B154", "a31aee0f"),
    ("main/func_8001A444", "cee5a218"),
    ("town/func_805D313C", "b9584211"),
    ("town/func_800A1B10", "6667b57b"),
]
R = {r["id"]: r for r in rows()}
cen = {}
ok = 0
for rid, rev in CASES:
    row = R[rid]
    rel = "src/%s/%s" % (row["container"], Path(row["c_path"]).name)
    text = subprocess.run(["git", "show", "%s:%s" % (rev, rel)], cwd=ROOT,
                          capture_output=True, text=True).stdout
    assert text, rel
    def vf(cand, cfg=None):
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / Path(row["c_path"]).name
            p.write_text(cand)
            r2 = row if not cfg else dict(row, cfg=cfg, cell=parse_cfg(cfg)[0],
                                          flags=" ".join(parse_cfg(cfg)[1]))
            return verify(r2, p, include_root=INCLUDE)
    why = T.eligible(text, row, cen)
    if why:
        print("%-22s ELIGIBLE-REFUSED %s" % (rid, why)); continue
    cand, info = T.apply_verified(text, row, cen, vf)
    cur = (ROOT / rel).read_text()
    print("%-22s %s" % (rid, json.dumps({k: v for k, v in info.items() if k != "menu"})))
    print("    menu: %s" % info.get("menu"))
    if cand is None:
        print("    NO EXACT CANDIDATE")
    else:
        bad = landing_refusal(cand, text, rel, row=row)   # the gate sweep.one() applies after exact
        if bad:
            print("    EXACT but LANDING-REFUSED: %s" % bad); continue
        ok += 1
        same = cand.strip() == cur.strip()
        print("    EXACT, landing gate clean; identical to the landed text: %s" % same)
        if not same and "--diff" in sys.argv:
            import difflib
            print("".join(difflib.unified_diff(cur.splitlines(1), cand.splitlines(1),
                                               "landed", "t10", n=1)))
print("exact: %d/%d" % (ok, len(CASES)))
