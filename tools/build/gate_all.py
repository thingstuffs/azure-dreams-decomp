#!/usr/bin/env python3
"""Run every overlay window gate from build_ovl/ and journal the verdicts.

    python3 tools/build/gate_all.py [--container dungeon] [--workers 6] [--limit N] [--retry]

One line per window in ledger/gate.jsonl: window, container, result (MATCH / NO MATCH / ERROR),
bytes, first mismatch text, seconds, and the sha256 of the window's C inputs so a later run can
skip windows whose inputs did not change (--retry re-runs non-MATCH windows regardless).
Run tools/build/mk_slus_root.sh + `splat split` and tools/build/mk_ovl_root.sh first.
"""
import argparse, hashlib, json, re, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
B = ROOT / "build_ovl"; JOURNAL = ROOT / "ledger/gate.jsonl"
sys.path.insert(0, str(ROOT / "tools"))
from common import read_jsonl, append_jsonl

def container_of(name):
    return name.split("_")[0] if not name.startswith("dungeon_engine") else "dungeon_engine"

def inputs_sha(yaml_path):
    """sha over the window YAML and every src/<container>/*.c the window's rows point at."""
    h = hashlib.sha256(yaml_path.read_bytes())
    cont = container_of(yaml_path.stem.replace(".overlay", ""))
    rows = [json.loads(l) for l in (ROOT / "ledger/rows.jsonl").read_text().splitlines()]
    for r in rows:
        if r.get("gate_config", "").endswith(yaml_path.name):
            p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            if p.exists(): h.update(p.read_bytes())
    return h.hexdigest()

def run_window(yaml_path):
    t0 = time.time()
    try:
        r = subprocess.run(["nice", "-n10", "python3", "tools/overlay_local_gate.py", "--config", str(yaml_path.relative_to(B)), "--clean"],
                           cwd=B, capture_output=True, text=True, timeout=3600)
        out = (r.stdout + r.stderr).strip().splitlines()
        last = next((l for l in reversed(out) if l.startswith(("MATCH", "NO MATCH"))), None)
        if last is None:
            res, detail = "ERROR", (out[-1] if out else "")[:200]
        else:
            res, detail = ("MATCH" if last.startswith("MATCH") else "NO MATCH"), last[:200]
    except subprocess.TimeoutExpired:
        res, detail = "ERROR", "timeout"
    m = re.search(r"\((\d+) bytes\)", detail)
    return {"window": yaml_path.stem.replace(".overlay", ""), "container": container_of(yaml_path.stem), "result": res, "bytes": int(m.group(1)) if m else None,
            "detail": detail, "secs": round(time.time() - t0, 1), "inputs_sha": inputs_sha(yaml_path), "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--container"); ap.add_argument("--workers", type=int, default=6); ap.add_argument("--limit", type=int); ap.add_argument("--retry", action="store_true")
    a = ap.parse_args()
    yamls = sorted((B / "config/overlays").glob("*.overlay.yaml"))
    if a.container: yamls = [y for y in yamls if container_of(y.stem) == a.container]
    prior = {j["window"]: j for j in read_jsonl(JOURNAL)}
    todo = []
    for y in yamls:
        w = y.stem.replace(".overlay", ""); p = prior.get(w)
        if p and p["result"] == "MATCH" and p.get("inputs_sha") == inputs_sha(y) and not a.retry: continue
        if p and p["result"] != "MATCH" and not a.retry and p.get("inputs_sha") == inputs_sha(y): continue
        todo.append(y)
    if a.limit: todo = todo[:a.limit]
    print(f"{len(todo)} windows to gate ({len(yamls) - len(todo)} up to date), {a.workers} workers", flush=True)
    t0 = time.time(); n = 0; tally = {}
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(run_window, todo):
            append_jsonl(JOURNAL, rec); n += 1; tally[rec["result"]] = tally.get(rec["result"], 0) + 1
            if n % 50 == 0: print(f"{n}/{len(todo)} {time.time()-t0:.0f}s {tally}", flush=True)
    print(f"done {n} in {time.time()-t0:.0f}s: {tally}")

if __name__ == "__main__":
    main()
