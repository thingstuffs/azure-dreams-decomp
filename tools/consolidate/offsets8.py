"""offsets8.py: prove the new GameWork layout is offset- and type-size-identical to the landed flat one:
   compile (gcc 2.7.2-cdk cc1) &((GameWork*)0)->OLD and ->NEW for every respell entry + sizeof, compare."""
import json, re, subprocess, tempfile
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
D = REPO / "toolchain/compilers/gcc-2.7.2-cdk"
M = json.load(open(LANE / "tools/respell_map8.json"))
def words(hdr, exprs):
    with tempfile.TemporaryDirectory(dir=LANE / "tmp") as td:
        t = Path(td); (t / "h.h").write_text(hdr.read_text())
        body = '#include "h.h"\nint o[] = {%s};\n' % ", ".join(exprs)
        (t / "f.c").write_text(body)
        subprocess.run([str(D / "gcc"), "-B%s/" % D, "-E", "-I", str(t), "f.c", "-o", "f.i"], cwd=t, check=True)
        subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", "-o", "f.s"], cwd=t, check=True)
        return [int(x, 0) for x in re.findall(r"\.word\s+(\S+)", (t / "f.s").read_text())]
keys = sorted(M)
old = words(REPO / "include/shared/game_work.h", ["(int)&((GameWork*)0)->%s" % k for k in keys] + ["(int)sizeof(((GameWork*)0)->%s)" % k for k in keys] + ["sizeof(GameWork)"])
new = words(LANE / "inc/shared/game_work.h", ["(int)&((GameWork*)0)->%s" % M[k] for k in keys] + ["(int)sizeof(((GameWork*)0)->%s)" % M[k] for k in keys] + ["sizeof(GameWork)", "sizeof(GameView)", "sizeof(ViewSlot)", "(int)&((GameWork*)0)->view", "(int)&((GameWork*)0)->unk_1DC"])
n = len(keys); bad = [(k, hex(old[i]), hex(new[i]), old[n+i], new[n+i]) for i, k in enumerate(keys) if old[i] != new[i] or old[n+i] != new[n+i]]
print("fields", n, "mismatch", bad, "sizeof GameWork old/new", hex(old[-1]), hex(new[2*n]), "GameView", hex(new[2*n+1]), "ViewSlot", hex(new[2*n+2]), "view@", hex(new[2*n+3]), "1DC@", hex(new[2*n+4]))
