#!/usr/bin/env python3
"""whatif.py - compile texts with the lane's switchable cdk cc1 (tmp/cc1_whatif, sched.c + R95_* env switches)
and measure listing distance against the PINNED text compiled by the SHIPPED cc1 (= retail order on an exact row).

    python3 tools/whatif.py rows   <switchset.json|-> [row ...]      # the 19 pack rows: erased + pinned texts
    python3 tools/whatif.py validate <n> <switchset.json|-> [--modules m1,m2] # pin-free rows: must stay distance 0

A switchset is {"label": {"R95_X": "1"|"s1"|"s2", ...}, ...}; "-" = the built-in list.
Only 2.7.2-cdk rows are measured (the switch build is the cdk tree)."""
from pathlib import Path as _P
_ROOT = str(_P(__file__).resolve().parents[4])
import json, os, sys, subprocess, random
from pathlib import Path
LANE = Path(__file__).resolve().parents[1]
sys.path.insert(0, _ROOT + "/tools/lanes/lanekit")
import kitlib
kitlib.bootstrap(str(LANE))
import screen, variant_screen
from common import rows as all_rows, parse_cfg, clean_path

CC1 = str(LANE / "tmp" / "cc1_whatif")
SHIPPED = "/toolchain/compilers/gcc-2.7.2-cdk/cc1"
STATE = {"on": False, "env": {}}
_orig_run = screen._run
def _run(args, **kw):
    if STATE["on"] and str(args[0]).endswith(SHIPPED):
        extra = STATE["env"].get("CC1ARGS", "").split()
        args = [CC1] + list(args[1:]) + extra
        env = dict(os.environ); env.update({k: v for k, v in STATE["env"].items() if k != "CC1ARGS"}); kw["env"] = env
    return _orig_run(args, **kw)
screen._run = _run

SW = ["R95_NOBOOST", "R95_BOOSTANY", "R95_LUIDREV", "R95_NOCLASS", "R95_HAZLAST", "R95_NOHAZ", "R95_MAXPRI_INSN"]
DEFAULT = {"off": {}}
for s in SW:
    for m in ("1", "s1", "s2"):
        if s in ("R95_NOBOOST", "R95_BOOSTANY", "R95_MAXPRI_INSN") and m != "s1":
            continue          # the boost only exists in sched1 (birthing_insn_p returns 0 after reload)
        DEFAULT["%s=%s" % (s[4:], m)] = {s: m}

PACK = ["dungeon/func_800C7F80", "dungeon/func_810332A4", "dungeon/func_81844F2C", "dungeon/func_81912154",
        "dungeon/func_8194D354", "dungeon/func_81976CB0", "dungeon/func_819835AC", "dungeon/func_81989558",
        "slus/w_80042560", "slus/w_80046C20", "slus/w_80048B8C", "slus/w_80054B08", "slus/w_8005914C",
        "town/func_800991C4", "town/func_800A2988", "town/func_800AE09C", "town/func_8046C188",
        "town/func_8080C650", "town/func_8096C508"]

def load_sets(arg):
    return DEFAULT if arg == "-" else json.load(open(arg))

def measure(row, texts, sets):
    """{label: {textname: distance}} - the target is texts['pinned'] under the shipped cc1."""
    STATE["on"] = False
    scr = variant_screen.Screen(row, texts["pinned"])
    out = {}
    for label, env in sets.items():
        STATE["on"], STATE["env"] = True, env
        out[label] = {k: scr.distance(t) for k, t in texts.items()}
        STATE["on"] = False
    return out

def cmd_rows(argv):
    sets = load_sets(argv[0]); ids = argv[1:] or PACK
    res = {}
    for rid in ids:
        row = kitlib.row_of(rid)
        if parse_cfg(row["cfg"])[0] != "2.7.2-cdk":
            print(rid, "skip (cell %s)" % row["cfg"]); continue
        pinned = kitlib.base_text(row, LANE)
        texts = {"pinned": pinned, "erased": kitlib.erased_text(pinned)}
        extra = LANE / "cand" / (rid.replace("/", "__") + ".c")
        if extra.exists():
            texts["cand"] = extra.read_text()
        m = measure(row, texts, sets)
        res[rid] = m
        base = m.get("off", {})
        line = " ".join("%s:%s/%s" % (k, v["erased"], v["pinned"]) for k, v in m.items())
        print(rid, line, flush=True)
    json.dump(res, open(LANE / "tmp" / ("whatif_rows_%s.json" % os.getpid()), "w"), indent=1)

def cmd_validate(argv):
    n = int(argv[0]); sets = load_sets(argv[1])
    mods = None
    if "--modules" in argv:
        mods = argv[argv.index("--modules") + 1].split(",")
    containers = None
    if "--containers" in argv:
        containers = argv[argv.index("--containers") + 1].split(",")
    sys.path.insert(0, _ROOT + "/tools")
    from pin_census import sites_of
    packmods = None
    if "--packmods" in argv:
        md = {}
        for ln in open(_ROOT + "/ledger/modules.jsonl"):
            if ln.strip():
                d = json.loads(ln); md[d["id"]] = (d.get("container"), d.get("module"))
        packmods = {md[r] for r in PACK if r in md}
        print("pack modules:", sorted(packmods, key=str))
    cand = []
    for r in all_rows():
        if packmods is not None and md.get(r["id"]) not in packmods:
            continue
        if parse_cfg(r["cfg"])[0] != "2.7.2-cdk" or r["id"] in PACK:
            continue
        if containers and r["container"] not in containers:
            continue
        if mods and not any(m in r["c_path"] for m in mods):
            continue
        cand.append(r)
    random.Random(95).shuffle(cand)
    tally = {k: [0, 0] for k in sets}
    changed = {k: [] for k in sets}
    done = 0
    for r in cand:
        if done >= n:
            break
        try:
            text = clean_path(r).read_text(errors="replace")
        except Exception:
            continue
        if sites_of(text):
            continue
        r = r if r.get("func") else dict(r, func=r["id"].split("/")[-1])
        try:
            m = measure(r, {"pinned": text}, sets)
        except Exception as e:
            print(r["id"], "ERR", str(e)[:80]); continue
        if m["off"]["pinned"] != 0:
            print(r["id"], "control not 0:", m["off"]["pinned"]); continue
        done += 1
        for k, v in m.items():
            d = v["pinned"]
            tally[k][0] += 1
            if d:
                tally[k][1] += 1; changed[k].append((r["id"], d))
        print(r["id"], " ".join("%s:%s" % (k, v["pinned"]) for k, v in m.items() if v["pinned"]), flush=True)
    print("\nVALIDATION over %d pin-free rows (rows whose listing CHANGED under the switch):" % done)
    for k, (t, c) in tally.items():
        print("  %-22s %3d / %d changed  %s" % (k, c, t, " ".join("%s(%d)" % x for x in changed[k][:8])))
    json.dump({"tally": tally, "changed": changed}, open(LANE / "tmp" / ("whatif_validate_%s.json" % os.getpid()), "w"), indent=1)

if __name__ == "__main__":
    {"rows": cmd_rows, "validate": cmd_validate}[sys.argv[1]](sys.argv[2:])
