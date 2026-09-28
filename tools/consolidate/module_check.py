"""module_check.py: prove the slot_transition module members of cand7/ by cc1-listing identity of the whole composed
   module (live include + src members) vs (lane inc/ + cand7 members), at every member cfg.  Exit 1 on any diff."""
import sys, re
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import listing, row_index, REPO
LANE_ = Path(__file__).resolve().parent.parent; S = REPO / "src/slus"; R = row_index()
MODS = {"slot_transition.c": ["w_80041AE4", "w_80041B98", "w_80041BE4", "w_80041C64"],
        "slot_transition_secondary.c": ["w_80043D04", "w_80043DB8", "w_80043E04", "w_80043E60"]}
def compose(mod, new):
    t = (S / mod).read_text()
    def inc(m):
        f = m.group(1)
        if f.startswith(("shared/", "slus/slot_transition.h")):
            p = (LANE_ / "inc" / f) if new else (REPO / "include" / f)
            return p.read_text() if p.is_file() else m.group(0)
        if f.endswith(".c"):
            c = LANE_ / "cand7/slus" / f
            return c.read_text() if (new and c.is_file()) else (S / f).read_text()
        return m.group(0)
    for _ in range(5): t = re.sub(r'^#include "([^"]+)"[^\n]*$', inc, t, flags=re.M)
    return t
strip = lambda s: [l for l in (s or "").splitlines() if not l.lstrip().startswith(".file")]
bad = 0
for mod, mem in MODS.items():
    for cfg in sorted({R["slus/" + w]["cfg"] for w in mem if "slus/" + w in R}):
        r = dict(R["slus/" + mem[1]]); r["kind"] = "overlay"; r["cfg"] = cfg
        a, b = listing(r, compose(mod, False)), listing(r, compose(mod, True))
        ok = bool(a) and bool(b) and strip(a) == strip(b); bad += not ok
        print(mod, cfg, "IDENTICAL" if ok else "DIFFERS")
sys.exit(1 if bad else 0)
