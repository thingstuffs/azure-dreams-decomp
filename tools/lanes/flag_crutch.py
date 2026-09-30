#!/usr/bin/env python3
# Moved from work/native_lane/r81_sonnet_flagcrutch (round 81). Usage: python3 tools/lanes/flag_crutch.py OUT.jsonl [--procs 4] [--neighbours 5] [--only ROWS]; summary OUT.jsonl. No --help: any first argument is the output file.
"""Per-row flag-crutch census.

    python3 flag_crutch.py OUT.jsonl [--procs 4] [--neighbours 5] [--only ROWS.txt|id,id] [--limit N]
    python3 flag_crutch.py summary OUT.jsonl

For every pinned row whose registered cfg differs from its module census recipe (cell or flag set):
 (a) PROOF: score up to N PIN-FREE rows of the same module (current src text, exact at their own cfg) under the
     pinned row's REGISTERED cfg.  A neighbour that is not exact proves the cfg is not the module's build.
     Neighbours registered at exactly the test cfg are trivially exact and are not tested (counted apart).
 (b) the row's erased-text and pinned-text totals at the census recipe (row_census.py method).
slus-module / partitioned rows: registered cfg only -> skipped.  Resumable.  Writes nothing outside OUT's dir.
"""
from __future__ import annotations
import json, sys, time, collections
from multiprocessing import Pool
from pathlib import Path

LANES = Path(__file__).resolve().parent
sys.path.insert(0, str(LANES)); sys.path.insert(0, str(LANES / "lanekit"))
import kitlib                                                    # noqa: E402
import row_census as RC                                          # noqa: E402

OPTS = {"n": 5}
_C = {}


def norm(cfg):
    from common import parse_cfg
    cell, flags = parse_cfg(cfg)
    return cell, tuple(sorted(flags))


def module_rows():
    """(container, module) -> [row ids] from ledger/modules.jsonl"""
    if "mods" not in _C:
        m = collections.defaultdict(list)
        for l in RC.MODULES.read_text().splitlines():
            if l.strip():
                d = json.loads(l)
                m[(d["container"], d["module"])].append(d["id"])
        _C["mods"] = m
        _C["mod_of"] = {i: k for k, v in m.items() for i in v}
    return _C["mods"]


def pin_free_neighbours(rid, cfg):
    from common import clean_path
    mods = module_rows()
    key = _C["mod_of"].get(rid)
    if not key:
        return None, [], 0
    cands, same_cfg = [], 0
    for nid in sorted(mods[key]):
        if nid == rid:
            continue
        try:
            nr = kitlib.row_of(nid)
        except SystemExit:
            continue
        if not RC.per_row_trial_ok(nr):
            continue
        p = clean_path(nr)
        if not p.is_file():
            continue
        t = p.read_text(errors="replace")
        if kitlib.sites(t):
            continue
        if norm(nr["cfg"]) == norm(cfg):
            same_cfg += 1
            continue
        cands.append((nid, nr, t))
    n = OPTS["n"]
    if n and len(cands) > n:                       # evenly spread, deterministic
        cands = [cands[int(i * len(cands) / n)] for i in range(n)]
    return key, cands, same_cfg


def one(rid):
    t0 = time.time()
    out = {"id": rid}
    try:
        row = kitlib.row_of(rid)
        from common import clean_path
        text = clean_path(row).read_text(errors="replace")
        out.update(pins=len(kitlib.sites(text)), cfg=row["cfg"])
        m = RC.census_map().get(rid)
        if not m:
            out["skip"] = "no module census recipe"; return out
        out["module"], out["census_cfg"] = m
        if norm(m[1]) == norm(row["cfg"]):
            out["skip"] = "cfg == census recipe"; return out
        if not RC.per_row_trial_ok(row):
            out["skip"] = "slus/partitioned: registered cfg only"; return out
        key, nb, same = pin_free_neighbours(rid, row["cfg"])
        out["pin_free_same_cfg_untested"] = same
        tests = []
        for nid, nr, nt in nb:
            v = kitlib.score_at(nr, nt, row["cfg"])
            tests.append({"id": nid, "own_cfg": nr["cfg"], "exact": bool(v.get("exact")), "total": v.get("total"),
                          "status": v.get("status")})
        out["neighbours"] = tests
        out["tested"] = len(tests)
        out["broken"] = sum(1 for t in tests if not t["exact"])
        out["verdict"] = ("proven" if out["broken"] else "consistent" if tests else "no-neighbours")
        erased = kitlib.erased_text(text)
        e = kitlib.score_at(row, erased, m[1])
        p = kitlib.score_at(row, text, m[1])
        out["erased_at_census"] = {k: e.get(k) for k in ("exact", "total", "status")}
        if e.get("err"): out["erased_at_census"]["err"] = str(e["err"])[:160]
        out["pinned_at_census"] = {k: p.get(k) for k in ("exact", "total", "status")}
    except BaseException as ex:
        out["err"] = repr(ex)[:300]
    out["secs"] = round(time.time() - t0, 1)
    return out


def _init(opts, lane):
    OPTS.update(opts)
    kitlib.bootstrap(lane)


def summary(path):
    recs = [json.loads(l) for l in open(path) if l.strip()]
    c = collections.Counter(); pins = collections.Counter()
    for r in recs:
        k = r.get("verdict") or ("err" if "err" in r else "skip: " + r.get("skip", "?"))
        c[k] += 1; pins[k] += r.get("pins", 0)
    for k in c:
        print("%-45s rows %4d pins %4d" % (k, c[k], pins[k]))


def main():
    a = sys.argv[1:]
    if a and a[0] == "summary":
        return summary(a[1])
    if not a:
        raise SystemExit(__doc__)
    out = Path(a.pop(0)).resolve(); procs = 4; only = None; limit = None
    while a:
        k = a.pop(0)
        if k == "--procs": procs = min(4, int(a.pop(0)))
        elif k == "--neighbours": OPTS["n"] = int(a.pop(0))
        elif k == "--limit": limit = int(a.pop(0))
        elif k == "--only":
            v = a.pop(0)
            only = v.split(",") if not Path(v).is_file() else [x.split()[0] for x in Path(v).read_text().splitlines() if x.strip()]
        else: raise SystemExit("unknown option " + k)
    lane = out.parent
    kitlib.bootstrap(lane)
    ids = only if only is not None else RC.pinned_ids()
    done = set()
    if out.exists():
        for l in out.open():
            try: done.add(json.loads(l)["id"])
            except Exception: pass
    ids = [i for i in ids if i not in done]
    if limit: ids = ids[:limit]
    t0 = time.time(); n = 0
    with Pool(procs, initializer=_init, initargs=(dict(OPTS), str(lane))) as p, out.open("a") as f:
        for rec in p.imap_unordered(one, ids, chunksize=1):
            f.write(json.dumps(rec) + "\n"); f.flush(); n += 1
            if n % 20 == 0: print(n, "rows", round(time.time() - t0), "s", flush=True)
    print("done", n, "rows", round(time.time() - t0), "s")


if __name__ == "__main__":
    main()
