"""Compile a row's text to its cc1 listing (no -da).  Lane-local helper; tmp under the lane."""
import os, subprocess, sys, tempfile
from pathlib import Path
REPO = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").exists() and (p / "include/common.h").exists())
LANE = Path(__file__).resolve().parent.parent      # the lane directory that holds this tools/ copy
sys.path.insert(0, str(REPO / "tools/build")); sys.path.insert(0, str(REPO / "tools")); sys.path.insert(0, str(REPO / "tools/lanes/lanekit"))
os.environ.setdefault("TMPDIR", str(LANE / "tmp")); (LANE / "tmp").mkdir(exist_ok=True)
tempfile.tempdir = str(LANE / "tmp")
from common import rows, parse_cfg, clean_path

def row_index():
    return {r["id"]: (r if r["func"] else dict(r, func=r["id"].split("/")[-1])) for r in rows()}

def listing(row, text, include=None):
    if row.get("kind") == "slus":
        import kitlib
        try: d = kitlib.dumps(row, text, want=set())
        except Exception as e: return None
        return d.get("asm") if d and not d.get("error") else None
    cell, flags = parse_cfg(row["cfg"])
    D = REPO / "toolchain/compilers" / ("gcc-" + cell)
    inc = include or (REPO / "include")
    with tempfile.TemporaryDirectory(prefix="cc_") as td:
        d = Path(td); (d / "f.c").write_text(text)
        r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(inc), "-w", "f.c", "-o", "f.i"], cwd=d, capture_output=True, text=True)
        if r.returncode: return None
        r = subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-o", "f.s"], cwd=d, capture_output=True, text=True)
        if r.returncode: return None
        return (d / "f.s").read_text(errors="replace")
