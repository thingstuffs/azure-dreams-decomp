#!/usr/bin/env python3
"""Hypothesis probe (docs/evidence/fidelity_step1_aspsx_diff.md, decision 1): is retail's 2.8-era return epilogue
the GENUINE ASPSX delay-slot filler working on a cc1 epilogue emitted in REORDER mode?

Our gcc 2.8.x (like genuine psyq4.4 CC1PSX, one row checked in work/tailslot_aspsx/REPORT.md) writes the epilogue as
`.set noreorder / j $31 / addu $sp,$sp,N / .set reorder`; ASPSX passes that through verbatim and maspsx's
`_maybe_unfill_return_delay` / `_unfill_via_load_delay` rewrite it to retail's shape. This probe rewrites ONLY that
block to reorder mode (`addu $sp,$sp,N / j $31`), leaves the rest of the cc1 output as is, assembles it with genuine
ASPSX 2.79 and compares with the (retail-exact) maspsx object - the same units and comparator as aspsx_diff.py.
A cc1 transformation, so its rows are NOT counted as genuine-exact in the journal; it measures where the fix lies.

    python3 tools/fidelity/probe_reorder_epilogue.py ROW [ROW ...]      (one line per row)
"""
import sys, re, tempfile, os
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools/fidelity")); sys.path.insert(0, str(ROOT / "tools"))
import aspsx_diff as A
from common import rows, clean_path
EPI = re.compile(r"\t\.set\tnoreorder\n\t\.set\tnomacro\n\tj\t\$31\n\t(addu\t\$sp,\$sp,\d+)\n\t\.set\tmacro\n\t\.set\treorder\n")
def run(rid, ver="2.79"):
    row={r["id"]:r for r in rows()}[rid]
    A.TMP.mkdir(parents=True, exist_ok=True); td=tempfile.mkdtemp(dir=str(A.TMP))
    ctx,err=(A.prepare_slus(row, clean_path(row), row["cfg"], row.get("row_asflags") or "", td) if row["kind"]=="slus" else A.prepare_overlay(row, clean_path(row), row["cfg"], None, td))
    mo,err=A.run_maspsx(ctx["m_in"], ctx["as_args"], Path(td)/"m.o", ctx["env"])
    mv=A.View(A.read_elf(mo)); scope=[ctx["symbol"]] if row["kind"]!="slus" else sorted(mv.funcs)
    if row["kind"]!="slus": mv.add_unit(scope[0]); mv.composite={scope[0]}; A.shape_unit(mv, scope[0], len(ctx["retail"]))
    src=ctx["g_src"]; n=len(EPI.findall(src))
    new=EPI.sub(lambda m: "\t"+m.group(1)+"\n\tj\t$31\n", src)
    res={}
    for tag,s in (("as-is",src),("reorder-epilogue",new)):
        modes,_=A.genuine_modes(s, ctx["flags"])
        best=None
        for fl,equ in modes:
            lnk,err=A.run_aspsx(A.aspsx_input(s,equ), ver, fl, td)
            if lnk is None: continue
            gv=A.View(A.read_lnk(lnk), mv, A.aliases(s)); gv.composite=mv.composite; gv.follow=mv.follow
            for f in scope: gv.add_unit(f, mv)
            c=A.compare_units(mv,gv,scope)
            if best is None or c["diff"]<best["diff"]: best=c
        res[tag]=(best["exact"], best["diff"])
    restores=len(re.findall(r"\n\tlw\t\$(1[6-9]|2[0-3]|30|31),\d+\(\$sp\)", src))
    print(rid, row["cfg"], "noreorder epilogues", n, "callee lw", restores, res, flush=True)
if __name__ == "__main__":
    os.environ["TMPDIR"] = str(A.TMP); tempfile.tempdir = str(A.TMP)
    for rid in sys.argv[1:]:
        run(rid)
