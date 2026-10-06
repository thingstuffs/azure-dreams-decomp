#!/usr/bin/env python3
"""census_table.py - TIE_CENSUS rows from tmp/flip/*.erased.json (flip.py output)."""
from pathlib import Path as _P
_ROOT = str(_P(__file__).resolve().parents[4])
import json, glob
for f in sorted(glob.glob(_ROOT + "/work/native_lane/r95_opus_T/tmp/flip/*.erased.json")):
    d = json.load(open(f))
    print("ROW %s  d0=%s final=%s moves=%d" % (d["row"], d["d0"], d["final"], len(d["flips"])))
    for h in d["hist"]:
        if "flip" not in h:
            b = h["best"][:1]
            print("   stall: best single move %s" % (["%s%s %s->%s" % (x[1], x[2], x[3], x[0]) for x in b]))
            continue
        dec = h.get("decision")
        alts = [x for x in h["best"] if x[0] == h["dist"]]
        alt = ", ".join("%s%s(%s)" % (x[1], x[2], x[3]) for x in alts)
        if dec:
            k = int(h["flip"].split(":")[1]); r = dec["ready"]
            fmt = lambda x: "uid%(uid)d %(op)s p%(prio)d/o%(orig)d%(bb)s l%(luid)d c%(cls)d h%(hz)d" % dict(x, bb="B" if x["boost"] else "")
            print("   %-12s %-11s %s %s %s | ours: %s | retail: %s | -> %d | alts: %s" % (h["flip"], h["crit"], dec["pass"], dec["block"], dec["clock"],
                  fmt(r[0]), fmt(r[k]) if k < len(r) else "?", h["dist"], alt))
        else:
            print("   %-12s %-30s -> %d | alts: %s" % (h["flip"], h["crit"], h["dist"], alt))
