#!/usr/bin/env python3
"""Coherence scan: a nonconforming pinned row's pin subsets erased and scored AT ITS MODULE'S RECIPE.

    python3 tools/lanes/coherence_scan.py scan [--workers 12] [--pair-pins 8] [--only id,id]
    python3 tools/lanes/coherence_scan.py build <dir>

Round 55's module census (ledger/module_recipe_census.jsonl) names, per strong/proven module, the one stock
recipe most of its pin-free rows are exact at.  A pinned row recorded at another recipe whose PINNED text is
not exact at the module recipe is "nonconforming": its pins may be compensating for the wrong recipe.  The
lone and joint scans never score such a row there (their pools are the recipes the pinned text is exact
at).  This scan erases the whole pin set, the same-macro and same-variable groups, and (on rows with at
most --pair-pins pins) the pairs and singles, and scores each candidate with the byte scorer at the module
recipe.  An exact candidate is a pin-free-or-fewer text exact at the recipe the module's own pin-free rows
prove: two provenance facts at once.  Landing such a switch is NOT covered by pin_cells_land rule 2 (the
pinned text is not exact at the new recipe), so `build` writes candidates plus cells.jsonl for the owner's
decision and the report says so.  Output ledger/pins_coherence.jsonl, keyed on (id, in_sha, cfg).
"""
import argparse, collections, itertools, json, sys, tempfile, threading, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
from common import LEDGER, rows, clean_path, sha_text, read_jsonl        # noqa: E402
from pin_census import sites_of                                          # noqa: E402
from pin_sites import erase_many                                         # noqa: E402
from verify import verify                                                # noqa: E402
from joint_scan import var_of                                            # noqa: E402

OUT = LEDGER / "pins_coherence.jsonl"
INC = f"-I{(ROOT / 'include').resolve()}"


def module_recipe():
    mods = {m["id"]: (m["container"], m["module"]) for m in read_jsonl(LEDGER / "modules.jsonl")}
    cen = {(x["container"], x["module"]): x for x in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
    out = {}
    for rid, key in mods.items():
        x = cen.get(key)
        if x and x.get("best_recipe"):
            out[rid] = (x["best_recipe"], key[1], {n["id"] for n in x["nonconforming"]})
    return out


def subsets(sites, pair_pins):
    n = len(sites); seen, out = set(), []

    def add(idx):
        idx = tuple(sorted(set(idx)))
        if idx and idx not in seen:
            seen.add(idx); out.append(idx)
    add(range(n))
    by_m, by_v = collections.defaultdict(list), collections.defaultdict(list)
    for i, s in enumerate(sites):
        by_m[s[1]].append(i); by_v[var_of(s)].append(i)
    for g in list(by_m.values()) + list(by_v.values()):
        add(g)
    if n <= pair_pins:
        for i in range(n):
            add((i,))
        for a, b in itertools.combinations(range(n), 2):
            add((a, b))
    return out


def score(row, cfg, text):
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(text)
        return verify(dict(row, cfg=f"{cfg} {INC}"), f)


def scan_row(job):
    row, recipe, module, pair_pins = job
    t0 = time.time()
    text = clean_path(row).read_text(errors="replace")
    sites = sites_of(text)
    rec = {"id": row["id"], "cfg": row["cfg"], "in_sha": sha_text(text), "pins": len(sites), "module": module,
           "module_recipe": recipe, "tested": 0, "best": None, "hits": [], "secs": 0.0}
    try:
        base = score(row, recipe, text)
        rec["pinned_at_recipe"] = {"exact": bool(base.get("exact")), "total": base.get("total")}
        best = None
        for idx in subsets(sites, pair_pins):
            cand = erase_many(text, [sites[i] for i in idx], clean_notes=True)
            v = score(row, recipe, cand); rec["tested"] += 1
            tot = v.get("total")
            if v.get("exact"):
                rec["hits"].append({"sites": list(idx), "macros": [sites[i][1] for i in idx]})
            elif tot is not None and (best is None or tot < best[0]):
                best = (tot, list(idx))
        rec["best"] = best
    except Exception as e:                                             # noqa: BLE001
        rec["error"] = repr(e)
    rec["secs"] = round(time.time() - t0, 1)
    return rec


def cmd_scan(a):
    done = {r["id"]: r for r in read_jsonl(OUT)} if OUT.exists() else {}
    keep = set(a.only.split(",")) if a.only else None
    mr = module_recipe()
    todo = []
    for r in rows():
        if r["container"] in ("slus", "ovmovie") or not r.get("stock") or (keep and r["id"] not in keep):
            continue
        info = mr.get(r["id"])
        if not info or r["id"] not in info[2] or r["cfg"] == info[0]:
            continue                                                   # conforming, no census, or already at the module recipe (the census file predates a landing)
        p = clean_path(r)
        if not p.exists():
            continue
        text = p.read_text(errors="replace"); sites = sites_of(text)
        if not sites or len(sites) > a.max_pins:
            continue
        prev = done.get(r["id"])
        if prev and prev["in_sha"] == sha_text(text) and prev["cfg"] == r["cfg"] and prev["module_recipe"] == info[0]:
            continue
        todo.append((r, info[0], info[1], a.pair_pins))
    todo.sort(key=lambda j: len(sites_of(clean_path(j[0]).read_text(errors="replace"))))
    print(f"{len(todo)} nonconforming pinned rows to scan", flush=True)
    lock, n, nh, t0 = threading.Lock(), 0, 0, time.time()
    with ThreadPoolExecutor(a.workers) as ex:
        for rec in ex.map(scan_row, todo):
            with lock, OUT.open("a") as f:
                f.write(json.dumps(rec) + "\n")
            n += 1; nh += bool(rec["hits"])
            if n % 10 == 0:
                print(f"{n}/{len(todo)} rows with a hit {nh} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n} rows with a hit {nh} {time.time() - t0:.0f}s")


def cmd_build(a):
    by = {r["id"]: r for r in rows()}
    d = Path(a.dir); d.mkdir(parents=True, exist_ok=True)
    cells, pins = [], 0
    for rec in read_jsonl(OUT):
        if not rec.get("hits") or rec["id"] not in by:
            continue
        row = by[rec["id"]]; text = clean_path(row).read_text(errors="replace")
        if sha_text(text) != rec["in_sha"] or row["cfg"] != rec["cfg"]:
            continue
        best = max(rec["hits"], key=lambda h: len(h["sites"]))
        sites = sites_of(text)
        c, name = rec["id"].split("/"); (d / c).mkdir(exist_ok=True)
        (d / c / (name + ".c")).write_text(erase_many(text, [sites[i] for i in best["sites"]], clean_notes=True))
        (d / c / (name + ".c.base_sha")).write_text(rec["in_sha"])
        cells.append({"id": rec["id"], "to": rec["module_recipe"], "hits": len(best["sites"]), "coherence": True,
                      "pinned_exact_at_to": rec.get("pinned_at_recipe", {}).get("exact")})
        pins += len(best["sites"])
    (d / "cells.jsonl").write_text("".join(json.dumps(x) + "\n" for x in cells))
    print(f"rows {len(cells)}, pins {pins}; NOTE: pin_cells_land rule 2 does not hold for these (pinned text not exact "
          f"at the module recipe) - owner's decision before landing")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("scan"); s.add_argument("--workers", type=int, default=12); s.add_argument("--only")
    s.add_argument("--pair-pins", type=int, default=8); s.add_argument("--max-pins", type=int, default=40)
    b = sub.add_parser("build"); b.add_argument("dir")
    a = ap.parse_args()
    {"scan": cmd_scan, "build": cmd_build}[a.cmd](a)


if __name__ == "__main__":
    main()
