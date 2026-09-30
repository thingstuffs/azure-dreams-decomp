#!/usr/bin/env python3
"""Module-wide cellscore: "is CFG this module's build?"

    cd work/native_lane/<lane>
    python3 <tools/lanes>/modcell.py <module-or-row> --cfg CFG [--cfg CFG2 ...] [--all | --sample N]
                                     [--procs 4] [--out OUT.jsonl] [--skip-same] [--quiet]

<module-or-row>: a row id / func name (dungeon/func_813231FC or func_813231FC) -> that row's module; a module
name from ledger/modules.jsonl (beldo.c, or beldo) -> that module; `container/beldo.c` disambiguates a name
that exists in several containers.
Scores every PIN-FREE row of the module (current src text, kitlib.sites() empty; slus/partitioned rows are
skipped: their recipe is the module's) at each --cfg with the byte scorer (kitlib.score_at, as flag_crutch.py
does for its neighbour proof).  Default --all; --sample N takes N rows evenly spread.  Rows whose registered
cfg IS the test cfg are scored too (a control: they must be exact) unless --skip-same.
Prints per cfg  `exact/total`  and each breaking row with its byte total (and own cfg).  A cfg that breaks any
pin-free row is not the module's build (flag_crutch's proof); 0 breaking = consistent with the whole module.
--out appends {"module","cfg","id","own_cfg","same_cfg","exact","total","status"} per (cfg,row); resumable.
Nothing under src/, ledger/, config/ is written; compiles run in <cwd>/tmp (lane kit bootstrap).
"""
from __future__ import annotations
import json, sys, time, collections
from multiprocessing import Pool
from pathlib import Path

HERE = Path(__file__).resolve().parent
LANES = next((p / "tools/lanes" for p in [HERE, *HERE.parents] if (p / "tools/lanes/flag_crutch.py").is_file()), None)
if LANES is None:
    raise SystemExit("modcell: cannot find tools/lanes above " + str(HERE))
sys.path.insert(0, str(LANES)); sys.path.insert(0, str(LANES / "lanekit"))
import kitlib                                                    # noqa: E402
import row_census as RC                                          # noqa: E402
import flag_crutch as FC                                         # noqa: E402


def resolve(arg):
    mods = FC.module_rows()
    mod_of = FC._C["mod_of"]
    if "/" in arg and arg.split("/")[0] in {k[0] for k in mods}:
        c, _, m = arg.partition("/")
        for k in mods:
            if k[0] == c and k[1] in (m, m + ".c"):
                return k
    cands = [k for k in mods if k[1] in (arg, arg + ".c")]
    if len(cands) == 1:
        return cands[0]
    if len(cands) > 1:
        raise SystemExit("modcell: module %r exists in several containers %s; use container/module" % (arg, [k[0] for k in cands]))
    try:
        rid = kitlib.row_of(arg)["id"]
    except SystemExit:
        raise SystemExit("modcell: %r is neither a module name nor a row id" % arg)
    if rid in mod_of:
        return mod_of[rid]
    raise SystemExit("modcell: row %s has no module in ledger/modules.jsonl" % rid)


def pin_free_rows(key):
    """[(id, row, text)] of the module's scoreable pin-free rows; also (skipped-with-pins, skipped-slus) counts."""
    from common import clean_path
    out, pinned, slus = [], 0, 0
    for rid in sorted(FC.module_rows()[key]):
        try:
            r = kitlib.row_of(rid)
        except SystemExit:
            continue
        if not RC.per_row_trial_ok(r):
            slus += 1; continue
        p = clean_path(r)
        if not p.is_file():
            continue
        t = p.read_text(errors="replace")
        if kitlib.sites(t):
            pinned += 1; continue
        out.append((rid, r, t))
    return out, pinned, slus


_W = {}

def _init(lane, work):
    kitlib.bootstrap(lane)
    _W["work"] = work

def _one(job):
    cfg, rid = job
    t0 = time.time()
    r, t = _W["work"][rid]
    rec = {"cfg": cfg, "id": rid, "own_cfg": r["cfg"], "same_cfg": FC.norm(r["cfg"]) == FC.norm(cfg)}
    try:
        v = kitlib.score_at(r, t, cfg)
        rec.update(exact=bool(v.get("exact")), total=v.get("total"), status=v.get("status"))
        if v.get("err"):
            rec["err"] = str(v["err"])[:160]
    except BaseException as ex:                      # noqa: BLE001
        rec.update(exact=False, total=None, status="exception", err=repr(ex)[:200])
    rec["secs"] = round(time.time() - t0, 1)
    return rec


def main():
    a = sys.argv[1:]
    if not a or a[0] in ("-h", "--help"):
        raise SystemExit(__doc__)
    target = a.pop(0); cfgs = []; procs = 4; sample = None; out = None; skip_same = False; quiet = False
    while a:
        k = a.pop(0)
        if k == "--cfg": cfgs.append(a.pop(0))
        elif k == "--all": sample = None
        elif k == "--sample": sample = int(a.pop(0))
        elif k == "--procs": procs = min(4, int(a.pop(0)))
        elif k == "--out": out = Path(a.pop(0)).resolve()
        elif k == "--skip-same": skip_same = True
        elif k == "--quiet": quiet = True
        else: raise SystemExit("unknown option " + k)
    if not cfgs:
        raise SystemExit("modcell: at least one --cfg is required")
    lane = kitlib.bootstrap()
    key = resolve(target)
    rows, npinned, nslus = pin_free_rows(key)
    if sample and len(rows) > sample:
        rows = [rows[int(i * len(rows) / sample)] for i in range(sample)]
    modname = "%s/%s" % key
    print("module %s: %d rows in ledger, %d pin-free scoreable%s; skipped %d pinned, %d slus/partitioned"
          % (modname, len(FC.module_rows()[key]), len(rows), " (sampled)" if sample else "", npinned, nslus), flush=True)
    work = {rid: (r, t) for rid, r, t in rows}
    done = {}
    if out and out.exists():
        for l in out.open():
            try:
                d = json.loads(l)
                if d.get("module") == modname: done[(d["cfg"], d["id"])] = d
            except Exception: pass
    jobs = []
    for c in cfgs:
        for rid, r, _ in rows:
            if skip_same and FC.norm(r["cfg"]) == FC.norm(c): continue
            if (c, rid) not in done: jobs.append((c, rid))
    t0 = time.time(); res = dict(done)
    with Pool(procs, initializer=_init, initargs=(str(lane), work)) as p:
        f = out.open("a") if out else None
        for n, rec in enumerate(p.imap_unordered(_one, jobs, chunksize=1), 1):
            res[(rec["cfg"], rec["id"])] = rec
            if f:
                f.write(json.dumps(dict(rec, module=modname)) + "\n"); f.flush()
            if not quiet and n % 10 == 0: print("  ..", n, "/", len(jobs), round(time.time() - t0), "s", flush=True)
        if f: f.close()
    print()
    for c in cfgs:
        rs = [res[(c, rid)] for rid, _, _ in rows if (c, rid) in res]
        ex = sum(1 for r in rs if r["exact"]); bad = [r for r in rs if not r["exact"]]
        same = sum(1 for r in rs if r["same_cfg"])
        print("== %s : exact %d/%d  (breaking %d; %d rows registered at exactly this cfg)" % (c, ex, len(rs), len(bad), same))
        for r in sorted(bad, key=lambda r: r["id"]):
            print("   BREAK %-34s total %-6s status %-9s own %s%s" % (r["id"], r["total"], r["status"], r["own_cfg"],
                  "  [SAME-CFG CONTROL FAILED]" if r["same_cfg"] else ""))
        print("   verdict: " + ("CONSISTENT (every pin-free row exact)" if rs and not bad else "NOT this module's build" if bad else "no rows"))
    print("\n%d scores in %ds" % (len(jobs), time.time() - t0))


if __name__ == "__main__":
    main()
