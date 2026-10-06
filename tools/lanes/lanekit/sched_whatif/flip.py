#!/usr/bin/env python3
"""flip.py - the scheduler DECISION ORACLE for one row (r95_opus_T).

The lane's cdk cc1 (tmp/cc1_whatif, genuine sched.c + logging) numbers every scheduling decision with >= 2
ready insns (sched1 and sched2), logs ready[0..3] with priority (after / before the birthing boost), boost
flag, LUID, class wrt last_scheduled_insn, function unit, potential-hazard flag, and whether
schedule_select's hazard rule moved the pick.  R95_FLIP="idx:k,..." makes decision idx take ready[k].

    python3 tools/flip.py <row> [--text erased|pinned|FILE] [--depth 3] [--all] [--jobs 4]

For the text (default: all pins erased) it measures every single flip of a TIE decision (equal priority,
or a priority order created by the boost) against the PINNED listing from the SHIPPED cc1 (= retail),
then greedily stacks the best flips until distance 0 or --depth.  Output: tmp/flip/<row>.json + a table."""
import json, os, sys, re, tempfile
from pathlib import Path
from multiprocessing import Pool
LANE = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(LANE / "tools"))
import whatif                                   # bootstraps the kit, patches screen._run
from whatif import STATE, kitlib, variant_screen

TOK = re.compile(r"(\d+):p(-?\d+):o(-?\d+):b(\d):l(\d+):c(\d):u(-?\d+):h(\d+):(\S+)")

BIRTHS = []
def parse_log(path):
    decs = []
    del BIRTHS[:]
    for ln in open(path):
        if ln.startswith("B "):
            f = ln.split()
            BIRTHS.append({"func": f[1], "uid": int(f[2]), "reg": f[3], "live": int(f[4][4:]), "nsets": int(f[5][5:]),
                           "prio": int(f[6][4:]), "max": int(f[7][3:])})
            continue
        if not ln.startswith("D "):
            continue
        head, rest = ln.split("|", 1)
        h = head.split()
        d = {"idx": int(h[1]), "pass": h[2], "func": h[3], "block": h[4], "clock": h[5], "n": int(h[6][1:]),
             "haz": int(h[7][3:]), "ready": []}
        if len(h) > 8 and h[8].startswith("m"):
            a_, b_ = h[8][1:].split("/"); d["memsched"], d["memtot"] = int(a_), int(b_)
        for m in TOK.finditer(rest):
            d["ready"].append({"uid": int(m.group(1)), "prio": int(m.group(2)), "orig": int(m.group(3)),
                               "boost": int(m.group(4)), "luid": int(m.group(5)), "cls": int(m.group(6)),
                               "unit": int(m.group(7)), "hz": int(m.group(8)), "op": m.group(9)})
        if d["pass"] == "s2":
            for x in d["ready"]:
                x["boost"] = 0          # sched2 never boosts; the uid array still holds sched1's flag
        decs.append(d)
    return decs

def criterion(d, k=1):
    """Which rank_for_schedule / schedule_select criterion put ready[0] ahead of ready[k]."""
    a, b = d["ready"][0], d["ready"][k]
    if d["haz"]:
        return "HAZARD"
    if a["prio"] != b["prio"]:
        if a["boost"] or b["boost"]:
            # would they have tied / reversed without the boost?
            oa = a["orig"] if a["boost"] else a["prio"]; ob = b["orig"] if b["boost"] else b["prio"]
            return "BOOST" if oa <= ob else "PRIO+BOOST"
        return "PRIO"
    if a["cls"] != b["cls"]:
        return "CLASS"
    return "LUID"

_W = {}
def _init(rowid, target_text):
    row = kitlib.row_of(rowid)
    STATE["on"] = False
    _W["scr"] = variant_screen.Screen(row, target_text)

def _dist(args):
    text, env = args
    STATE["on"], STATE["env"] = True, env
    try:
        return _W["scr"].distance(text)
    finally:
        STATE["on"] = False

def env_of(moves):
    env = {}
    f = [m[1] for m in moves if m[0] == "F"]; b = [m[1] for m in moves if m[0] == "B"]
    if f: env["R95_FLIP"] = ",".join(f)
    if b: env["R95_BOOSTCTL"] = ",".join(b)
    return env

def log_run(row, text, flips, scr):
    fd, path = tempfile.mkstemp(prefix="r95log_", dir=str(LANE / "tmp")); os.close(fd); os.unlink(path)
    env = dict(env_of(flips), R95_LOG=path)
    STATE["on"], STATE["env"] = True, env
    d = scr.distance(text)
    STATE["on"] = False
    decs = parse_log(path) if os.path.exists(path) else []
    if os.path.exists(path):
        os.unlink(path)
    return d, decs

def candidates(decs, all_=False):
    out = []
    for d in decs:
        for k in range(1, min(d["n"], len(d["ready"]))):
            c = criterion(d, k)
            if all_ or c in ("LUID", "CLASS", "HAZARD", "BOOST", "PRIO+BOOST") and (c != "PRIO+BOOST" or k == 1):
                out.append((d["idx"], k, c))
            if c == "PRIO" and not all_:
                break                       # ready is sorted: later entries are strictly worse
    return out

def main():
    a = sys.argv[1:]
    rowid = a[0]
    opt = lambda n, dflt: a[a.index(n) + 1] if n in a else dflt
    which = opt("--text", "erased"); depth = int(opt("--depth", "3")); jobs = int(opt("--jobs", "4"))
    row = kitlib.row_of(rowid)
    pinned = kitlib.base_text(row, LANE)
    text = {"erased": kitlib.erased_text(pinned), "pinned": pinned}.get(which) or Path(which).read_text()
    STATE["on"] = False
    scr = variant_screen.Screen(row, pinned)
    flips, hist = [], []
    d0, decs = log_run(row, text, flips, scr)
    print("# %s text=%s: %d decisions (s1 %d / s2 %d), distance %s" % (rowid, which, len(decs),
          sum(x["pass"] == "s1" for x in decs), sum(x["pass"] == "s2" for x in decs), d0), flush=True)
    cur = d0
    with Pool(jobs, initializer=_init, initargs=(rowid, pinned)) as pool:
        for step in range(depth):
            if cur == 0:
                break
            cands = [("F", "%d:%d" % (i, k), c, i) for i, k, c in candidates(decs, "--all" in a)]
            seen = set()
            for b in BIRTHS:
                if not b["live"] or (b["func"], b["uid"]) in seen:
                    continue
                seen.add((b["func"], b["uid"]))
                if b["nsets"] == 1:
                    cands.append(("B", "%s:-%d" % (b["func"], b["uid"]), "UNBOOST nsets1 prio%d" % b["prio"], -1))
                else:
                    cands.append(("B", "%s:+%d" % (b["func"], b["uid"]), "FORCEBOOST nsets%d prio%d" % (b["nsets"], b["prio"]), -1))
            byidx = {d["idx"]: d for d in decs}
            res = pool.map(_dist, [(text, env_of(flips + [(t, v)])) for t, v, c, i in cands])
            scored = sorted(((r if r is not None else 10**6), t, v, c, i) for r, (t, v, c, i) in zip(res, cands))
            print("## step %d: %d tie candidates; best: %s" % (step + 1, len(cands),
                  ", ".join("%s%s %s->%s" % (t, v, c, r) for r, t, v, c, i in scored[:8])), flush=True)
            if not scored or scored[0][0] >= cur:
                hist.append({"step": step + 1, "n": len(cands), "best": scored[:8], "improved": False})
                break
            r, t, v, c, i = scored[0]
            d = byidx.get(i)
            hist.append({"step": step + 1, "n": len(cands), "flip": t + v, "crit": c, "dist": r,
                         "decision": d, "best": scored[:8]})
            if d:
                print("   take %s (%s) %s %s %s %s -> %d" % (v, c, d["pass"], d["block"], d["clock"],
                      " ".join("%(uid)d:p%(prio)d/o%(orig)d%(b)s:l%(luid)d:c%(cls)d:%(op)s:h%(hz)d" % dict(x, b="B" if x["boost"] else "") for x in d["ready"]), r), flush=True)
            else:
                print("   take %s (%s) -> %d" % (v, c, r), flush=True)
            flips.append((t, v)); cur = r
            _, decs = log_run(row, text, flips, scr)
    out = LANE / "tmp" / "flip"; out.mkdir(exist_ok=True)
    json.dump({"row": rowid, "text": which, "d0": d0, "final": cur, "flips": flips, "hist": hist},
              open(out / (rowid.replace("/", "__") + "." + Path(which).name + ".json"), "w"), indent=1)
    print("# RESULT %s: %s -> %s with %d flip(s) %s" % (rowid, d0, cur, len(flips), flips))

if __name__ == "__main__":
    main()
