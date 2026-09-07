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

def superseded(yamls):
    """Synthetic-base seed windows (TF-1B gate_carver: `<stem>.overlay.yaml`, vram = foff + a sweep
    constant) whose range is re-gated by a `<stem>_truebase_<vram>.overlay.yaml` twin at the proven
    base. The seed's own target is a data row; the matched rows inside it are registered under the
    truebase twin and match there, while the seed encodes j/%hi/%lo at the wrong base. Skipped and
    dropped from the journal; the twin is the window of record."""
    names = {y.name for y in yamls}
    # a seed that some registered row still names as its window of record (not a derived assignment) is kept
    owned = set()
    for l in (ROOT / "ledger/rows.jsonl").read_text().splitlines():
        if l.strip():
            r = json.loads(l)
            if r.get("gate_config") and not r.get("gate_config_derived"): owned.add(Path(r["gate_config"]).name)
    out = set()
    for y in yamls:
        stem = y.name.replace(".overlay.yaml", "")
        if "_truebase_" in stem or y.name in owned: continue
        if any(n.startswith(stem + "_truebase_") for n in names): out.add(y.name)
    return out

def container_of(name):
    name = name.replace(".overlay", "")
    return name.split("_")[0] if not name.startswith("dungeon_engine") else "dungeon_engine"

_WROWS = None
def window_rows():
    """{window yaml name: registered rows the gate compiles for it} — every row whose extent lies
    inside the window's file range, which is what the gate does (a row's own gate_config only says
    which window landed it)."""
    global _WROWS
    if _WROWS is None:
        from common import window_map
        _WROWS = {}
        rows = [json.loads(l) for l in (ROOT / "ledger/rows.jsonl").read_text().splitlines() if l.strip()]
        for cont, wins in window_map().items():
            crows = sorted((r for r in rows if r["container"] == cont), key=lambda r: r["foff"])
            for name, fs, fe, _ in wins:
                _WROWS[name] = [r for r in crows if fs <= r["foff"] and r["foff"] + r["size"] <= fe]
    return _WROWS

def inputs_sha(yaml_path):
    """sha over the window YAML, the row table and every src/<container>/*.c inside the window."""
    h = hashlib.sha256(yaml_path.read_bytes())
    cont = container_of(yaml_path.stem); fam = "dungeon" if cont == "dungeon_engine" else cont
    t = ROOT / "ledger/splits" / f"{cont}.jsonl"
    if t.exists(): h.update(t.read_bytes())
    for r in window_rows().get(yaml_path.name, []):
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
    detail = detail.replace(str(ROOT), "<repo>").replace(str(Path.home()), "<home>")
    m = re.search(r"\((\d+) bytes\)", detail)
    return {"window": yaml_path.stem.replace(".overlay", ""), "container": container_of(yaml_path.stem), "result": res, "bytes": int(m.group(1)) if m else None,
            "detail": detail, "secs": round(time.time() - t0, 1), "inputs_sha": inputs_sha(yaml_path), "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--container"); ap.add_argument("--workers", type=int, default=6); ap.add_argument("--limit", type=int); ap.add_argument("--retry", action="store_true")
    a = ap.parse_args()
    yamls = sorted((B / "config/overlays").glob("*.overlay.yaml"))
    sup = superseded(yamls)
    yamls = [y for y in yamls if y.name not in sup]
    if a.container: yamls = [y for y in yamls if container_of(y.stem) == a.container]
    prior = {j["window"]: j for j in read_jsonl(JOURNAL)}
    dead = [w for w in prior if w + ".overlay.yaml" in sup]
    if dead:
        from common import write_jsonl
        write_jsonl(JOURNAL, [j for j in read_jsonl(JOURNAL) if j["window"] + ".overlay.yaml" not in sup])
        prior = {j["window"]: j for j in read_jsonl(JOURNAL)}
        print(f"{len(sup)} superseded synthetic-base seed windows skipped ({len(dead)} stale journal records dropped); their _truebase_ twins are gated")
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
    # a parallel run can leave transient failures (shared extract reads); retry those serially
    last = {j["window"]: j for j in read_jsonl(JOURNAL)}
    retry = [y for y in todo if (lambda w: w and w["result"] != "MATCH" and "No such file" not in w["detail"])(last.get(y.stem.replace(".overlay", "")))]
    for y in retry:
        rec = run_window(y); rec["retry"] = True; append_jsonl(JOURNAL, rec); tally[rec["result"] + " (retry)"] = tally.get(rec["result"] + " (retry)", 0) + 1
    print(f"done {n} (+{len(retry)} serial retries) in {time.time()-t0:.0f}s: {tally}")

if __name__ == "__main__":
    main()
