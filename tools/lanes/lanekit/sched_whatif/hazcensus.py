#!/usr/bin/env python3
"""hazcensus.py - every decision where schedule_select's potential-hazard rule CHANGED the pick, undone one at a
time (flip idx:1 puts the rank-best insn back in front), on pack rows (erased text) and pin-free rows (their exact
text).  On a pin-free row a listing change means retail FOLLOWED the hazard rule there (REQUIRED); on a pack row a
distance drop means retail did NOT (AGAINST).  Features per decision go to tmp/hazcensus.jsonl.

    python3 tools/hazcensus.py pack
    python3 tools/hazcensus.py free <n> [--containers c1,c2]"""
from pathlib import Path as _P
_ROOT = str(_P(__file__).resolve().parents[4])
import json, sys, random
from pathlib import Path
from multiprocessing import Pool
sys.path.insert(0, str(Path(__file__).resolve().parent))
import flip
from flip import STATE, kitlib, variant_screen, log_run, env_of, _init, _dist
from whatif import PACK
from common import rows as all_rows, parse_cfg, clean_path

def kind(op):
    src, _, dst = op.partition("/")
    return "store" if dst == "mem" else "load" if src in ("mem", "sign_extend", "zero_extend") and dst == "reg" else src

def run(rowid, text, pinned, pool, out, tag):
    row = kitlib.row_of(rowid)
    STATE["on"] = False
    scr = variant_screen.Screen(row, pinned)
    d0, decs = log_run(row, text, [], scr)
    hz = [d for d in decs if d["haz"]]
    if not hz:
        return 0
    pool_ = Pool(4, initializer=_init, initargs=(rowid, pinned))
    res = pool_.map(_dist, [(text, env_of([("F", "%d:1" % d["idx"])])) for d in hz])
    pool_.close(); pool_.join()
    n = 0
    for d, r in zip(hz, res):
        a, b = d["ready"][0], d["ready"][1]
        rec = {"row": rowid, "tag": tag, "d0": d0, "undo": r, "pass": d["pass"], "block": d["block"], "clock": d["clock"],
               "n_ready": d["n"], "memsched": d.get("memsched"), "memtot": d.get("memtot"),
               "pick": kind(a["op"]), "pick_h": a["hz"], "pick_l": a["luid"], "pick_p": a["prio"],
               "best": kind(b["op"]), "best_h": b["hz"], "best_l": b["luid"], "best_p": b["prio"],
               "verdict": ("REQUIRED" if r and r > d0 else "IRRELEVANT" if r == d0 else "AGAINST") if tag == "free"
                          else ("AGAINST" if r is not None and r < d0 else "FOLLOWED" if r is not None and r > d0 else "IRRELEVANT")}
        out.write(json.dumps(rec) + "\n"); n += 1
    out.flush()
    return n

def main():
    a = sys.argv[1:]
    out = open(flip.LANE / "tmp" / ("hazcensus_%s.jsonl" % a[0]), "w")
    if a[0] == "pack":
        for rid in PACK:
            row = kitlib.row_of(rid)
            if parse_cfg(row["cfg"])[0] != "2.7.2-cdk":
                continue
            pinned = kitlib.base_text(row, flip.LANE)
            print(rid, run(rid, kitlib.erased_text(pinned), pinned, None, out, "pack"), flush=True)
    else:
        n = int(a[1]); cont = a[a.index("--containers") + 1].split(",") if "--containers" in a else None
        sys.path.insert(0, _ROOT + "/tools")
        from pin_census import sites_of
        cand = [r for r in all_rows() if parse_cfg(r["cfg"])[0] == "2.7.2-cdk" and r["id"] not in PACK
                and (not cont or r["container"] in cont)]
        random.Random(9595).shuffle(cand)
        done = 0
        for r in cand:
            if done >= n:
                break
            try:
                t = clean_path(r).read_text(errors="replace")
            except Exception:
                continue
            if sites_of(t):
                continue
            try:
                k = run(r["id"], t, t, None, out, "free")
            except Exception as e:
                print(r["id"], "ERR", str(e)[:60]); continue
            done += 1
            print(r["id"], k, flush=True)

if __name__ == "__main__":
    main()
