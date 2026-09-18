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
    row, recipe, module, kinds, depth, near_max, near_k, erase_subsets, band, cap = job
    t0 = time.time()
    budget = [cap]

    def confirm(d, new):
        """True when the candidate is byte-exact at the recipe: d == 0 always goes to the scorer; 0 < d <= band too,
        while the per-row budget lasts (the listing screen has a false-negative band: byte-exact recipe pairs differ
        by two listing lines in 41% of 150 calibration rows, delay-slot spelling)."""
        if d > band or (d > 0 and budget[0] <= 0):
            return False
        if d > 0:
            budget[0] -= 1
        with tempfile.TemporaryDirectory() as td:
            pth = Path(td) / Path(row["c_path"]).name; pth.write_text(new)
            return bool(verify(with_cfg(row, f"{recipe} {INC}"), pth).get("exact"))
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
                if d <= band:
                    rec["screen_hits"] += 1
                    if confirm(d, new):
                        rec["hits"].append({"kind": kind, "params": params, "screen_d": d})
                        d0 = ROOT / "work/native_lane/coherence_perturb/out" / row["container"]; d0.mkdir(parents=True, exist_ok=True)
                        (ROOT / "work/native_lane/coherence_perturb/.ignore").write_text("*\n")
                        (d0 / Path(row["c_path"]).name).write_text(new)
                        (d0 / (Path(row["c_path"]).name + ".base_sha")).write_text(rec["in_sha"])
                        rec["secs"] = round(time.time() - t0, 1); return rec
                elif nearest is None or d < nearest[0]:
                    nearest = (d, kind, params.get("label") if isinstance(params, dict) else str(params)[:80])
        rec["nearest"] = nearest
        if erase_subsets and rec["pins"]:
            from coherence_scan import subsets as pin_subsets
            from pin_sites import erase_many
            sites = sites_of(text)
            rec["erase_subsets"] = 0
            for idx in pin_subsets(sites, 8):
                base_t = erase_many(text, [sites[i] for i in idx], clean_notes=True)
                rec["erase_subsets"] += 1
                s0 = compile_s(with_cfg(row, recipe), base_t)
                texts = [(("erase", list(idx)), base_t)]
                for kind, fn in kinds:
                    try:
                        texts += [((kind, params), new) for params, new in fn(base_t, collections.Counter())]
                    except Exception:                                  # noqa: BLE001
                        continue
                for (kind, params), new in texts:
                    rec["candidates"] += 1
                    if unscored_text(new) != unscored_text(base_t):
                        continue
                    s = compile_s(with_cfg(row, recipe), new)
                    if s is None:
                        continue
                    d = sdiff(target, s)
                    if d <= band:
                        rec["screen_hits"] += 1
                        if confirm(d, new):
                            rec["hits"].append({"erased": list(idx), "kind": kind, "params": params, "screen_d": d})
                            d0 = ROOT / "work/native_lane/coherence_perturb/out" / row["container"]; d0.mkdir(parents=True, exist_ok=True)
                            (d0 / Path(row["c_path"]).name).write_text(new)
                            (d0 / (Path(row["c_path"]).name + ".base_sha")).write_text(rec["in_sha"])
                            rec["secs"] = round(time.time() - t0, 1); return rec
                    elif rec["nearest"] is None or d < rec["nearest"][0]:
                        rec["nearest"] = (d, f"erase{list(idx)}+{kind}", params.get("label", "") if isinstance(params, dict) else str(params)[:60])
        if depth >= 2 and nearest is not None and nearest[0] <= near_max:
            # depth 2: every kind applied to each of the K nearest depth-1 texts (round-28 lesson: ranking is a valley,
            # so K is generous); still screened by listing, confirmed by the scorer
            pool = []
            for kind, fn in kinds:
                try:
                    for params, new in fn(text, collections.Counter()):
                        if unscored_text(new) != usig:
                            continue
                        s = compile_s(with_cfg(row, recipe), new)
                        if s is not None:
                            pool.append((sdiff(target, s), kind, params, new))
                except Exception:                                      # noqa: BLE001
                    continue
            pool.sort(key=lambda x: x[0])
            rec["depth2_seeds"] = 0
            for d1, k1, p1, t1 in pool[:near_k]:
                rec["depth2_seeds"] += 1
                for kind, fn in kinds:
                    try:
                        cands = fn(t1, collections.Counter())
                    except Exception:                                  # noqa: BLE001
                        continue
                    for params, new in cands:
                        rec["candidates"] += 1
                        if unscored_text(new) != usig:
                            continue
                        s = compile_s(with_cfg(row, recipe), new)
                        if s is None:
                            continue
                        d = sdiff(target, s)
                        if d <= band:
                            rec["screen_hits"] += 1
                            if confirm(d, new):
                                rec["hits"].append({"depth": 2, "first": {"kind": k1, "params": p1}, "kind": kind, "params": params, "screen_d": d})
                                d0 = ROOT / "work/native_lane/coherence_perturb/out" / row["container"]; d0.mkdir(parents=True, exist_ok=True)
                                (d0 / Path(row["c_path"]).name).write_text(new)
                                (d0 / (Path(row["c_path"]).name + ".base_sha")).write_text(rec["in_sha"])
                                rec["secs"] = round(time.time() - t0, 1); return rec
                        elif d < rec["nearest"][0]:
                            rec["nearest"] = (d, f"{k1}+{kind}", (p1.get("label", "") if isinstance(p1, dict) else "") + " | " + (params.get("label", "") if isinstance(params, dict) else ""))
    except Exception as e:                                             # noqa: BLE001
        rec["error"] = repr(e)[:200]
    rec["secs"] = round(time.time() - t0, 1)
    return rec


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=12); ap.add_argument("--only"); ap.add_argument("--pinned", action="store_true")
    ap.add_argument("--kinds"); ap.add_argument("--max-dist", type=int, default=10**6, help="skip rows whose current distance at the module recipe exceeds this")
    ap.add_argument("--depth", type=int, default=1); ap.add_argument("--near-max", type=int, default=4, help="depth 2 only on rows whose nearest depth-1 listing distance is at most this")
    ap.add_argument("--near-k", type=int, default=12, help="depth 2: seeds per row")
    ap.add_argument("--tag", default="", help="ledger suffix (a depth-2 run keeps its own journal)")
    ap.add_argument("--erase-subsets", action="store_true", help="pinned rows: each pin subset erased, then every kind at depth 1 on the erased text")
    ap.add_argument("--rescore-band", type=int, default=0, help="also send candidates with 0 < listing distance <= N to the byte scorer")
    ap.add_argument("--rescore-cap", type=int, default=40, help="per-row cap on such scorer calls")
    a = ap.parse_args()
    keep = set(a.only.split(",")) if a.only else None
    kinds = [(k, f) for k, f in KINDS if not a.kinds or k in a.kinds.split(",")]
    pop = nonconforming(a.pinned)
    global OUT
    if a.tag:
        OUT = LEDGER / f"coherence_perturb_{a.tag}.jsonl"
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
        jobs.append((r, info[0], info[1], kinds, a.depth, a.near_max, a.near_k, a.erase_subsets, a.rescore_band, a.rescore_cap))
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
