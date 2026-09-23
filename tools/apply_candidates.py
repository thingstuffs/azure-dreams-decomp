#!/usr/bin/env python3
"""Land candidate files produced outside the sweep machinery (agent lanes, experiments) the same
way a sweep would: verify each through tools/verify.py, copy the exact ones into src/, journal
every verdict in ledger/sweeps/<transform>.jsonl (in_sha/out_sha/outcome, resumable).

    python3 tools/apply_candidates.py <dir> --transform t9_labelcall [--workers 4] [--dry-run]

<dir> holds <container>/<basename>.c candidates.  A candidate identical to the current src text
is 'noop'; one that is not exact is 'mismatch' (nothing written); an exact one replaces src/ and
is 'applied'.  Touched windows still need the window gate afterwards (tools/build/gate_all.py).
"""
import argparse, json, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, append_jsonl, sha_text, clean_path
from verify import verify
from pin_census import landing_refusal

INCLUDE = ROOT / "include"

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dir"); ap.add_argument("--transform", required=True); ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--cells", help="JSONL of {id, to}: land those rows at stock cell `to` under "
                    "tools/pin_cells_land.py's rules (candidate exact at `to` and not at the recorded "
                    "cell, the current text exact at `to` too); written through common.set_row_cfg")
    a = ap.parse_args()
    import tempfile, threading
    from common import set_row_cfgs
    cells = {}
    if a.cells:
        for line in Path(a.cells).read_text().splitlines():
            if line.strip():
                j = json.loads(line); cells[j["id"]] = j["to"]
    cell_lock = threading.Lock()          # set_row_cfg rewrites shared ledger tables and the build roots
    by = {}
    for r in rows():
        by[(r["container"], Path(r["c_path"]).name)] = r
    cands = sorted(Path(a.dir).glob("*/*.c"))
    journal = LEDGER / "sweeps" / f"{a.transform}.jsonl"
    def one(p):
        r = by.get((p.parent.name, p.name))
        if not r: return {"candidate": str(p.relative_to(ROOT)), "outcome": "unknown-row"}
        cur = clean_path(r).read_text(errors="replace"); new = p.read_text(errors="replace")
        rec = {"id": r["id"], "transform": a.transform, "in_sha": sha_text(cur), "size": r["size"], "source": str(Path(a.dir).relative_to(ROOT)) if Path(a.dir).is_relative_to(ROOT)
               else Path(a.dir).name}   # a lane outside the tree records its NAME, never its
                                        # absolute path: this journal is committed and the
                                        # scrub hook rejects absolute home paths outside
                                        # raw/ and src/ (this comment must not contain one either)
        if new == cur: return dict(rec, outcome="noop")
        # a candidate cut from an older text would silently revert whatever landed since: the
        # verdict below proves only that the candidate is exact, not what it replaces
        side = p.with_name(p.name + ".base_sha")
        if side.exists() and side.read_text().strip() != sha_text(cur):
            return dict(rec, outcome="refused", reason="stale candidate: its row changed after it was cut (.base_sha)")
        cell = cells.get(r["id"])
        if cell and verify(r, p.resolve(), include_root=INCLUDE).get("exact"):
            cell = None                   # exact at the recorded cell already: no switch is needed
        rv = dict(r, cfg=cell) if cell else r
        v = verify(rv, p.resolve(), include_root=INCLUDE)   # the scorer runs in the gate root: absolute paths only
        rec.update({"exact": v.get("exact"), "status": v.get("status"), "class": v.get("class"), "total": v.get("total"), "secs": v.get("secs")})
        if v.get("exact"):
            # <name>.c.port_ref names a commit whose text of the row stands in for the current port
            # build when that no longer compiles (pin_census.landing_refusal, port codegen identity)
            ref = p.with_name(p.name + ".port_ref"); port_ref = None
            if ref.exists():
                rev = ref.read_text().strip(); rel = str(clean_path(r).relative_to(ROOT))
                port_ref = subprocess.run(["git", "show", f"{rev}:{rel}"], cwd=ROOT, capture_output=True, text=True).stdout or None
                rec["port_ref"] = rev
            bad = landing_refusal(new, cur, str(clean_path(r).relative_to(ROOT)), row=r, port_ref=port_ref)
            if bad:
                return dict(rec, outcome="refused", reason=bad.replace(str(ROOT), "<repo>"))
            if cell:
                # tools/pin_cells_land.py rule 2: the shipped bytes must not depend on the change,
                # so the row's current (more pinned) text must be exact at the new cell too
                with tempfile.TemporaryDirectory() as td:
                    q = Path(td) / p.name; q.write_text(cur)
                    if not verify(rv, q.resolve(), include_root=INCLUDE).get("exact"):
                        return dict(rec, outcome="refused", reason=f"current text not exact at {cell}")
                rec.update(cell_from=r["cfg"], cell_to=cell)
            done = dict(rec, outcome="applied", out_sha=sha_text(new), lines_delta=new.count("\n") - cur.count("\n"))
            try:                          # owner ruling 2026-09-23: a dead zero initializer is a tracked trade
                import dead_init
                di = dead_init.record(r["id"], cur, new, rec["source"], time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()))
                if di:
                    done["_dead_init"] = di
            except Exception as e:        # never let the bookkeeping block a landing
                print("dead_init record failed:", r["id"], repr(e)[:120], file=sys.stderr)
            if not a.dry_run:
                if cell:
                    # held until every verify has finished: the switch re-exports the build roots the
                    # scorer reads, so all of them land together through set_row_cfgs below
                    done["_cell"] = (r, new, cell, f"fewer-pin text is exact at {cell} and not at {r['cfg']}; "
                                                   f"the pinned text is exact at both ({a.transform})")
                else:
                    clean_path(r).write_text(new)
            return done
        return dict(rec, outcome="mismatch" if v.get("status") == "ok" else "build-failed", err=(v.get("err") or "")[:200].replace(str(ROOT), "<repo>"))
    tally = {}; t0 = time.time(); held = []
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(one, cands):
            rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
            di = rec.pop("_dead_init", None)
            if di and not a.dry_run:
                from common import read_jsonl
                tp = LEDGER / "recipe_trades.jsonl"
                if not any(t.get("kind") == "dead_init" and t.get("id") == di["id"] and t.get("init") == di["init"]
                           for t in (read_jsonl(tp) if tp.exists() else [])):   # recorded by hand already
                    append_jsonl(tp, di)
            if "_cell" in rec: held.append(rec)
            elif not a.dry_run: append_jsonl(journal, rec)
            tally[rec["outcome"]] = tally.get(rec["outcome"], 0) + 1
            print(f"{rec.get('id', rec.get('candidate')):32} {rec['outcome']:12} {rec.get('class') or ''} {rec.get('total') if rec.get('total') is not None else ''}")
    if held:
        set_row_cfgs([(h["_cell"][0]["id"], h["_cell"][2], h["_cell"][3]) for h in held])
        for h in held:
            r, new, _, _ = h.pop("_cell")
            clean_path(r).write_text(new); append_jsonl(journal, h)
        print(f"{len(held)} cell switches landed together")
    print(f"done {len(cands)} in {time.time()-t0:.0f}s: {tally}" + (" (dry run: nothing written)" if a.dry_run else ""))

if __name__ == "__main__":
    main()
