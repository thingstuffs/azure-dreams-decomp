#!/usr/bin/env python3
"""Coherence sweep: the cascade generators run on a NONCONFORMING row with the module recipe as the oracle.

    python3 tools/lanes/coherence_sweep.py [--workers 12] [--only id,id] [--pinned] [--transforms t36_paramwidth,...]

Round 55's module census names, per strong/proven module, the one stock recipe its pin-free rows prove.  A row not
exact there (recorded at another cell or with a flag) is compensating: its C shape, its recipe, or both.  The ordinary
sweep (tools/sweep.py) scores every candidate at the row's RECORDED recipe, so it can never find the shape that is exact
at the module's.  This sweep runs each generator with the row's cfg overridden to the module recipe, scores the
candidate there, and journals the outcome in ledger/coherence_sweep.jsonl (id, transform, in_sha, module recipe,
exact, total).  It writes NOTHING to src/: an exact candidate is a recipe switch whose current text is not exact at the
new recipe, so pin_cells_land rule 2 does not hold and the owner decides (`build <dir>` stages them with cells.jsonl).
Default population: the census's nonconforming PIN-FREE rows (the flag-debt and cell-fitted rows); --pinned adds the
nonconforming pinned rows (a generator that makes the pinned text exact at the module recipe is coherence without pin
loss; T2 at the new recipe then follows).
"""
import argparse, json, sys, tempfile, threading, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
from common import LEDGER, rows, clean_path, sha_text, read_jsonl, parse_cfg   # noqa: E402
from pin_census import sites_of, unscored_text                                 # noqa: E402
from verify import verify                                                      # noqa: E402
import xform                                                                   # noqa: E402

OUT = LEDGER / "coherence_sweep.jsonl"
INCLUDE = ROOT / "include"
CASCADE = ("t36_paramwidth t37_localwidth t37b_localwidth_keep t38_unstage t39_signbit t41_gotoloop t41b_gotoloop_while "
           "t41c_gotoloop_greedy t42_sinkcopy t44_doloop_greedy t48_gotoreturn t49_looptest t16_absidiom t16b_fieldabs "
           "t51_sched_order t53_reg_state t53k_keep t54_pagebase t57_keepafterstore t57b_keepafternext t59_offsetsym "
           "t63_memdep t66_sameregmerge t69_prologue t71_updateaftercall t72_stmtperm t2_pins").split()


BY = {r["id"]: r for r in rows()}


def nonconforming(pinned):
    mods = {m["id"]: (m["container"], m["module"]) for m in read_jsonl(LEDGER / "modules.jsonl")}
    cen = {(x["container"], x["module"]): x for x in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
    out = {}
    for rid, key in mods.items():
        x = cen.get(key)
        if not x:
            continue
        for n in x["nonconforming"]:
            if n["id"] == rid and (pinned or n["pins"] == 0) and BY.get(rid, {}).get("cfg") != x["best_recipe"]:   # skip rows already at the module recipe (the census file predates a landing)
                out[rid] = (x["best_recipe"], key[1], n["pins"], n.get("dist_at_best"))
    return out


def with_cfg(row, cfg):
    return dict(row, cfg=cfg, cell=parse_cfg(cfg)[0], flags=" ".join(parse_cfg(cfg)[1]))


def one(job):
    T, row, cen, recipe, module = job
    t0 = time.time()
    text = clean_path(row).read_text(errors="replace")
    rec = {"id": row["id"], "transform": T.name, "in_sha": sha_text(text), "cfg": row["cfg"], "module": module,
           "module_recipe": recipe, "pins": len(sites_of(text))}
    r2 = with_cfg(row, recipe)
    why = T.eligible(text, r2, cen)
    if why:
        return dict(rec, outcome="refused", reason=str(why)[:160], secs=round(time.time() - t0, 1))
    usig = unscored_text(text)
    try:
        if getattr(T, "needs_verify", False):
            def vf(cand, cfg=None):
                if unscored_text(cand) != usig:
                    return {"exact": False, "status": "unscored-arm-edit", "total": None}
                with tempfile.TemporaryDirectory() as td:
                    p = Path(td) / Path(row["c_path"]).name; p.write_text(cand)
                    return verify(with_cfg(row, cfg) if cfg else r2, p, include_root=INCLUDE)
            new, info = T.apply_verified(text, r2, cen, vf)
        else:
            new, info = T.apply(text, r2, cen), {}
    except Exception as e:                                             # noqa: BLE001
        return dict(rec, outcome="refused", reason=f"apply error: {e!r}"[:160], secs=round(time.time() - t0, 1))
    if new is None or new == text:
        return dict(rec, outcome="noop", secs=round(time.time() - t0, 1))
    if info.get("cfg") and info["cfg"] != recipe:
        return dict(rec, outcome="refused", reason="plugin chose another cfg", secs=round(time.time() - t0, 1))
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / Path(row["c_path"]).name; p.write_text(new)
        v = verify(r2, p, include_root=INCLUDE)
    rec.update({"exact": bool(v.get("exact")), "total": v.get("total"), "status": v.get("status"),
                "out_sha": sha_text(new), "secs": round(time.time() - t0, 1)})
    if v.get("exact"):
        d = ROOT / "work/native_lane/coherence_sweep/out" / row["container"]; d.mkdir(parents=True, exist_ok=True)
        (d / Path(row["c_path"]).name).write_text(new)
        (d / (Path(row["c_path"]).name + ".base_sha")).write_text(rec["in_sha"])
        (ROOT / "work/native_lane/coherence_sweep/.ignore").write_text("*\n")
    return dict(rec, outcome="exact" if v.get("exact") else "mismatch")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=12); ap.add_argument("--only"); ap.add_argument("--pinned", action="store_true")
    ap.add_argument("--transforms", default=",".join(CASCADE))
    a = ap.parse_args()
    keep = set(a.only.split(",")) if a.only else None
    pop = nonconforming(a.pinned)
    cen = {c["id"]: c for c in read_jsonl(LEDGER / "census.jsonl")}
    done = {(r["id"], r["transform"], r["in_sha"], r["module_recipe"]) for r in read_jsonl(OUT)} if OUT.exists() else set()
    Ts = [xform.load(n) for n in a.transforms.split(",")]
    jobs = []
    for r in rows():
        info = pop.get(r["id"])
        if not info or (keep and r["id"] not in keep) or r["container"] in ("slus", "ovmovie") or not clean_path(r).exists():
            continue
        sha = sha_text(clean_path(r).read_text(errors="replace"))
        for T in Ts:
            if (r["id"], T.name, sha, info[0]) not in done:
                jobs.append((T, r, cen.get(r["id"], {}), info[0], info[1]))
    print(f"{len(pop)} nonconforming rows, {len(jobs)} (row, transform) jobs", flush=True)
    lock, n, ex_n, t0 = threading.Lock(), 0, 0, time.time()
    with ThreadPoolExecutor(a.workers) as ex:
        for rec in ex.map(one, jobs):
            with lock, OUT.open("a") as f:
                f.write(json.dumps(rec) + "\n")
            n += 1; ex_n += rec.get("outcome") == "exact"
            if n % 200 == 0:
                print(f"{n}/{len(jobs)} exact {ex_n} {time.time() - t0:.0f}s", flush=True)
    print(f"done {n} exact {ex_n} {time.time() - t0:.0f}s")


if __name__ == "__main__":
    main()
