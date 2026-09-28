"""t1v.py VARIANT...: verify.py (SLUS object identity, include_root = a full include copy whose globals.h drops
   `extern short D_80084808[8];` and whose shared/sound_volume.h declares the variant) on the task-1 texts.
   The readable name is respelled D_80084808 in the text (ccproc does the same after cc1)."""
import json, os, re, shutil, sys, tempfile
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
sys.path.insert(0, str(REPO / "tools")); os.chdir(REPO)
tempfile.tempdir = str(LANE / "tmp")
from common import rows
from verify import verify
R = {r["id"]: r for r in rows()}
for V in sys.argv[1:]:
    D = LANE / "t1" / ("v" + (V or "u"))
    inc = D / "inc_full"
    if inc.exists(): shutil.rmtree(inc)
    shutil.copytree(REPO / "include", inc)
    g = (inc / "globals.h").read_text(); assert "extern short D_80084808[8];\n" in g
    (inc / "globals.h").write_text(g.replace("extern short D_80084808[8];\n", ""))
    (inc / "shared/sound_volume.h").write_text(re.sub(r"\bvolumeScale\b", "D_80084808", (LANE / "t1/sound_volume.h.in").read_text().replace("@N@", V)))
    for f in sorted(D.glob("w_*.c")):
        rid = "slus/" + f.stem
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / f.name; p.write_text(re.sub(r"\bvolumeScale\b", "D_80084808", f.read_text()))
            v = verify(R[rid], p, include_root=inc)
        print(V or "unsized", f.stem, {k: v.get(k) for k in ("exact", "total", "status", "proof", "err")})
