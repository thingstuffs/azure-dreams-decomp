#!/usr/bin/env python3
"""Coherence perturbation search: the round-33 catalogue's moves applied to a NONCONFORMING row and screened for
exactness AT THE MODULE RECIPE, with the cc1 listing as the cross-recipe oracle.

    python3 tools/lanes/coherence_perturb.py [--workers 12] [--only id,id] [--pinned] [--kinds a,b] [--max-dist N]

The current text compiled at its RECORDED recipe is byte-exact, so its normalised cc1 listing (tools/xform/screen.py)
IS retail's listing.  A candidate whose listing at the MODULE recipe equals it produces the same bytes there (the
listing is what the assembler sees); the byte scorer then confirms.  So every perturbation kind of perturb_basic /
perturb_struct (a generator's move reversed, hundreds of candidates a row) costs about 15 ms a candidate here, against
the ~2 s of the scorer, and the search can afford depth 1 over every nonconforming row (round 55's census:
ledger/module_recipe_census.jsonl).  Depth 1 only; the nearest candidate per row (sdiff) is journaled for a later
depth-2 pass on the rows it brings within reach.  Output ledger/coherence_perturb.jsonl; exact candidates go to
work/native_lane/coherence_perturb/out/<container>/<name>.c (+ .base_sha) for the owner's decision (the switch to the
module recipe is not covered by pin_cells_land rule 2: the current text is not exact there).
"""
import argparse, collections, json, sys, tempfile, threading, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/xform")); sys.path.insert(0, str(ROOT / "tools/lanes"))
from common import LEDGER, rows, clean_path, sha_text, read_jsonl, parse_cfg   # noqa: E402
from pin_census import sites_of, unscored_text                                 # noqa: E402
from screen import compile_s, sdiff                                            # noqa: E402
from verify import verify                                                      # noqa: E402
import perturb_basic, perturb_struct                                           # noqa: E402

OUT = LEDGER / "coherence_perturb.jsonl"
INC = f"-I{(ROOT / 'include').resolve()}"
KINDS = list(perturb_basic.PERTURBATIONS) + list(perturb_struct.PERTURBATIONS)


def nonconforming(pinned):
    mods = {m["id"]: (m["container"], m["module"]) for m in read_jsonl(LEDGER / "modules.jsonl")}
    cen = {(x["container"], x["module"]): x for x in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
    out = {}
    for rid, key in mods.items():
        x = cen.get(key)
        if not x:
            continue
        for n in x["nonconforming"]:
            if n["id"] == rid and (pinned or n["pins"] == 0):
                out[rid] = (x["best_recipe"], key[1], n["pins"], n.get("dist_at_best"))
    return out


def with_cfg(row, cfg):
    return dict(row, cfg=cfg, cell=parse_cfg(cfg)[0], flags=" ".join(parse_cfg(cfg)[1]))


def scan_row(job):
    row, recipe, module, kinds = job
    t0 = time.time()
    text = clean_path(row).read_text(errors="replace")
    rec = {"id": row["id"], "cfg": row["cfg"], "in_sha": sha_text(text), "pins": len(sites_of(text)), "module": module,
           "module_recipe": recipe, "candidates": 0, "screen_hits": 0, "hits": [], "nearest": None, "secs": 0.0}
    try:
        target = compile_s(row, text)
        base = compile_s(with_cfg(row, recipe), text)
        if target is None or base is None:
            rec["error"] = "no listing"; return rec
        rec["d_current"] = sdiff(target, base)
        usig = unscored_text(text)
        nearest = None
        for kind, fn in kinds:
            try:
                cands = fn(text, collections.Counter())
            except Exception as e:                                     # noqa: BLE001
                rec.setdefault("kind_errors", []).append(f"{kind}: {e!r}"[:120]); continue
            for params, new in cands:
                rec["candidates"] += 1
                if unscored_text(new) != usig:
                    continue
                s = compile_s(with_cfg(row, recipe), new)
                if s is None:
                    continue
                d = sdiff(target, s)
                if d == 0:
                    rec["screen_hits"] += 1
                    with tempfile.TemporaryDirectory() as td:
                        p = Path(td) / Path(row["c_path"]).name; p.write_text(new)
                        v = verify(with_cfg(row, f"{recipe} {INC}"), p)
                    if v.get("exact"):
                        rec["hits"].append({"kind": kind, "params": params})
                        d0 = ROOT / "work/native_lane/coherence_perturb/out" / row["container"]; d0.mkdir(parents=True, exist_ok=True)
                        (ROOT / "work/native_lane/coherence_perturb/.ignore").write_text("*\n")
                        (d0 / Path(row["c_path"]).name).write_text(new)
                        (d0 / (Path(row["c_path"]).name + ".base_sha")).write_text(rec["in_sha"])
                        rec["secs"] = round(time.time() - t0, 1); return rec
                elif nearest is None or d < nearest[0]:
                    nearest = (d, kind, params.get("label") if isinstance(params, dict) else str(params)[:80])
        rec["nearest"] = nearest
    except Exception as e:                                             # noqa: BLE001
        rec["error"] = repr(e)[:200]
    rec["secs"] = round(time.time() - t0, 1)
    return rec


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=12); ap.add_argument("--only"); ap.add_argument("--pinned", action="store_true")
    ap.add_argument("--kinds"); ap.add_argument("--max-dist", type=int, default=10**6, help="skip rows whose current distance at the module recipe exceeds this")
    a = ap.parse_args()
    keep = set(a.only.split(",")) if a.only else None
    kinds = [(k, f) for k, f in KINDS if not a.kinds or k in a.kinds.split(",")]
    pop = nonconforming(a.pinned)
    done = {(r["id"], r["in_sha"], r["module_recipe"]) for r in read_jsonl(OUT)} if OUT.exists() else set()
    jobs = []
    for r in rows():
        info = pop.get(r["id"])
        if not info or (keep and r["id"] not in keep) or r["container"] in ("slus", "ovmovie") or not clean_path(r).exists():
            continue
        if info[3] is not None and info[3] > a.max_dist:
            continue
        sha = sha_text(clean_path(r).read_text(errors="replace"))
        if (r["id"], sha, info[0]) in done:
            continue
        jobs.append((r, info[0], info[1], kinds))
    jobs.sort(key=lambda j: j[0].get("size") or 0)
    print(f"{len(pop)} nonconforming rows, {len(jobs)} to search with {len(kinds)} kinds", flush=True)
    lock, n, nh, t0 = threading.Lock(), 0, 0, time.time()
    with ThreadPoolExecutor(a.workers) as ex:
        for rec in ex.map(scan_row, jobs):
            with lock, OUT.open("a") as f:
                f.write(json.dumps(rec) + "\n")
            n += 1; nh += bool(rec["hits"])
            if n % 20 == 0:
                print(f"{n}/{len(jobs)} rows with a hit {nh} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n} rows with a hit {nh} {time.time() - t0:.0f}s")


if __name__ == "__main__":
    main()
