#!/usr/bin/env python3
"""Lane evaluator: run one generator (the tNN contract) over a frozen row list and keep the evidence.

    python3 -B tools/lane_eval.py --lane work/native_lane/<lane> --module <path/to/tNN_name.py> \
        --rows <ids file or one id> --tag <name> [--jobs 6] [--resume]

Harvested from the sched_astra lane's run_t51.py (2026-09-13) and made generator-agnostic. Per row it
snapshots the CURRENT src text, verifies the pinned baseline, calls T.eligible and T.apply_verified with a
cached vf, then verifies any returned text again outside the cache and checks that it has fewer pins and
unchanged unscored arms. Exact outputs go to <lane>/out/<container>/<file>.c with a .base_sha beside them
(tools/apply_candidates.py lands those); per-row records, base sources and scores go to
<lane>/evidence/<tag>/, a running summary to <lane>/evidence/<tag>/summary.json.

Scores come only from tools/verify.py against the existing build_ovl view (never constructed here). The
process runs inside <lane>, so stray -da dumps land there, and temporary files go under <lane>/tmp. It
never writes src/, ledgers, gates or git. At most 8 jobs (the box is shared).
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import datetime
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import sys
import tempfile
import time
import traceback

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, sha_text, parse_cfg, is_stock_cfg
from pin_census import sites_of, unscored_text
import verify as verifier


def stamp():
    return datetime.datetime.now(datetime.timezone.utc).isoformat()


def load(module):
    path = Path(module).resolve()
    sys.path.insert(0, str(path.parent))            # lane helpers imported by bare name
    spec = importlib.util.spec_from_file_location(path.stem, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod.T, path


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lane", required=True, help="lane directory: evidence/, out/ and tmp/ go here")
    ap.add_argument("--module", required=True, help="generator file defining class T")
    ap.add_argument("--rows", required=True, help="one row ID, or a newline-separated list file")
    ap.add_argument("--tag", required=True)
    ap.add_argument("--jobs", type=int, default=6, choices=range(1, 9))
    ap.add_argument("--resume", action="store_true", help="reuse finished rows of an interrupted run")
    args = ap.parse_args()
    lane = Path(args.lane).resolve()
    ids = Path(args.rows).read_text().split() if Path(args.rows).is_file() else [args.rows]
    T, mpath = load(args.module)
    os.chdir(lane)
    os.environ["PYTHONDONTWRITEBYTECODE"] = "1"
    tmp = lane / "tmp"
    tmp.mkdir(exist_ok=True)
    os.environ["TMPDIR"] = str(tmp)
    tempfile.tempdir = str(tmp)
    view = ROOT / "build_ovl"                        # never build the scorer view from a lane
    if not (view / "tools/aligned_score.py").is_file():
        ap.error("the scorer view build_ovl is missing; a gate builds it, a lane may not")
    verifier._ROOTS[False] = view
    by = {r["id"]: r for r in rows()}
    folder = lane / "evidence" / args.tag
    folder.mkdir(parents=True, exist_ok=True)
    (folder / ".ignore").write_text("*.jsonl\n*.c\n")
    frozen = {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in mpath.parent.glob("*.py")}
    (folder / "manifest.json").write_text(json.dumps(
        {"tag": args.tag, "started": stamp(), "module": str(mpath), "generator": T.name, "ids": ids,
         "tool_sha256": frozen, "jobs": args.jobs}, indent=2) + "\n")

    def one(rid):
        out = folder / (rid.replace("/", "_") + ".json")
        if args.resume and out.exists():
            return json.loads(out.read_text())
        t0 = time.time()
        rec = {"id": rid, "started": stamp()}
        try:
            row = by[rid]
            text = clean_path(row).read_text()
            source_sha = sha_text(text)
            pins = sites_of(text)
            rec.update(base_sha=source_sha, cfg=row["cfg"], pins_in=len(pins),
                       fences_in=sum(s[1] == "ASM_SCHED_BARRIER" for s in pins))
            (folder / (rid.replace("/", "_") + ".base.c")).write_text(text)
            scores, cache = [], {}
            signature = unscored_text(text)

            def at(cfg):                    # the row at another STOCK cell/flags, as sweep.py's vf takes it
                return row if not cfg else dict(row, cfg=cfg, cell=parse_cfg(cfg)[0], flags=" ".join(parse_cfg(cfg)[1]))

            def vf(cand, cfg=None):
                if unscored_text(cand) != signature:
                    return {"exact": False, "status": "unscored-arm-edit"}
                if cfg and not is_stock_cfg(cfg):
                    return {"exact": False, "status": "non-stock cfg"}
                h = (sha_text(cand), cfg)
                if h not in cache:
                    with tempfile.TemporaryDirectory(prefix="vf_") as td:
                        p = Path(td) / Path(row["c_path"]).name
                        p.write_text(cand)
                        cache[h] = verifier.verify(at(cfg), p, include_root=ROOT / "include")
                    scores.append({"sha": h[0], "cfg": cfg, **cache[h]})
                return cache[h]

            rec["baseline"] = baseline = vf(text)
            why = T.eligible(text, row, {})
            if not baseline.get("exact"):
                rec.update(outcome="baseline-not-exact", exact=False)
            elif why:
                rec.update(outcome="ineligible", reason=why, exact=False)
            else:
                new, info = T.apply_verified(text, row, {}, vf)
                rec["info"] = info
                if new is None:
                    rec.update(outcome="miss", exact=False)
                else:
                    cfg = (info or {}).get("cfg")       # a cell switch lands only under pin_cells_land.py rules 1-2
                    if cfg and cfg != row["cfg"]:
                        rec["cfg"] = cfg
                        rec["cell_rules"] = {"pinned_exact_at_new": bool(vf(text, cfg).get("exact")),
                                             "candidate_exact_at_old": bool(vf(new).get("exact"))}
                    with tempfile.TemporaryDirectory(prefix="final_") as td:   # outside the vf cache
                        p = Path(td) / Path(row["c_path"]).name
                        p.write_text(new)
                        rec["final"] = final = verifier.verify(at(cfg), p, include_root=ROOT / "include")
                    np = sites_of(new)
                    if not final.get("exact") or len(np) >= len(pins) or unscored_text(new) != signature:
                        raise RuntimeError("candidate failed the final exact / fewer-pin / arm guard")
                    if cfg and cfg != row["cfg"] and (not rec["cell_rules"]["pinned_exact_at_new"] or rec["cell_rules"]["candidate_exact_at_old"]):
                        raise RuntimeError("cell switch fails pin_cells_land.py rules 1-2")
                    output = lane / "out" / row["container"] / Path(row["c_path"]).name
                    output.parent.mkdir(parents=True, exist_ok=True)
                    output.write_text(new)
                    Path(str(output) + ".base_sha").write_text(source_sha + "\n")
                    rec.update(outcome="hit", exact=True, output=str(output.relative_to(lane)),
                               candidate_sha=sha_text(new), pins_removed=len(pins) - len(np),
                               fences_removed=rec["fences_in"] - sum(s[1] == "ASM_SCHED_BARRIER" for s in np))
            rec["scores"] = scores
            rec["source_changed_during_run"] = sha_text(clean_path(row).read_text()) != source_sha
        except Exception as e:
            rec.update(outcome="error", exact=False, error=repr(e), traceback=traceback.format_exc())
        rec["seconds"] = round(time.time() - t0, 3)
        out.write_text(json.dumps(rec, indent=2) + "\n")
        return rec

    done = []
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        for f in as_completed([pool.submit(one, rid) for rid in ids]):
            rec = f.result()
            done.append(rec)
            print(json.dumps({"done": len(done), "total": len(ids), "id": rec["id"], "outcome": rec["outcome"],
                              "pins_removed": rec.get("pins_removed", 0), "seconds": rec["seconds"],
                              "error": rec.get("error")}), flush=True)
            (folder / "summary.json").write_text(json.dumps(
                {"tag": args.tag, "generator": T.name, "updated": stamp(), "requested": len(ids),
                 "completed": len(done), "hits": sum(x["outcome"] == "hit" for x in done),
                 "pins_removed": sum(x.get("pins_removed", 0) for x in done),
                 "fences_removed": sum(x.get("fences_removed", 0) for x in done),
                 "outcomes": {k: sum(x["outcome"] == k for x in done) for k in sorted({x["outcome"] for x in done})},
                 "source_drift": [x["id"] for x in done if x.get("source_changed_during_run")],
                 "tool_sha256": frozen}, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
