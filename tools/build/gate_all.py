#!/usr/bin/env python3
"""Run every overlay window gate from build_ovl/ and journal the verdicts.

    python3 tools/build/gate_all.py [--container dungeon] [--workers 6] [--limit N] [--retry]

One line per window in ledger/gate.jsonl: window, container, result (MATCH / NO MATCH / ERROR),
bytes, first mismatch text, seconds, and the sha256 of the window's C inputs so a later run can
skip windows whose inputs did not change (--retry re-runs non-MATCH windows regardless).
Run tools/build/mk_slus_root.sh + `splat split` and tools/build/mk_ovl_root.sh first.

GATE_BUILD_ROOT names the view root to gate in (default build_ovl, exactly as before).  An
isolated landing (LAND_ISOLATED=1, docs/LANE_KIT.md) gates in build_ovl_gate, built by
`EXP=gate SRCROOT=<repo>/src bash tools/build/mk_ovl_root.sh`, so that mk_ovl_root.sh never
replaces the build_ovl the model lanes score in.  Either root reads the SAME src/ (the
overlays/<ov>/first_pass_matched symlink) and the same window YAMLs, and inputs_sha is read from
src/ directly, so the verdict does not depend on which root ran it.  GATE_JOURNAL likewise names
the journal (default ledger/gate.jsonl): a throw-away journal gates every window without touching
the record of the tree.
"""
import argparse, contextlib, hashlib, json, os, re, subprocess, sys, time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
B = ROOT / os.environ.get("GATE_BUILD_ROOT", "build_ovl")
JOURNAL = Path(os.environ.get("GATE_JOURNAL", ROOT / "ledger/gate.jsonl"))
if not JOURNAL.is_absolute(): JOURNAL = ROOT / JOURNAL
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
        # built into a LOCAL and published in one assignment: run_window computes inputs_sha in
        # worker threads, and a half-filled table handed to a peer hashes no src bytes for its
        # window - the verdict is then journalled under a sha the tree never had, and the final
        # gate_current() check fails the whole run (seen on 4 windows of a 2,175-window gate)
        wrows = {}
        rows = [json.loads(l) for l in (ROOT / "ledger/rows.jsonl").read_text().splitlines() if l.strip()]
        for cont, wins in window_map().items():
            crows = sorted((r for r in rows if r["container"] == cont), key=lambda r: r["foff"])
            for name, fs, fe, _ in wins:
                wrows[name] = [r for r in crows if fs <= r["foff"] and r["foff"] + r["size"] <= fe]
        _WROWS = wrows
    return _WROWS

def census_files(cont):
    """The container family's maspsx tail-call evidence files: config/noreturn_syms[.<family>].txt
    and config/sibcall_syms[.<family>].txt, in that fixed order, filtered to the ones that exist.
    Same family mapping split_records uses ('dungeon_engine' folds into 'dungeon') and the same
    file selection tools/gate/overlay_evidence.py:evidence_env makes for maspsx's $MASPSX_NORETURN_FILE
    / $MASPSX_SIBCALL_FILE ('main' reads the un-suffixed files -- maspsx's own built-in defaults --
    every other family reads its '.<family>.txt' override). A family with no override file is
    omitted rather than erroring: maspsx loads a missing file as an empty, inert evidence set, so
    that is the correct (and already-safe) hash contribution. config/noreturn_false_members.jsonl
    is deliberately NOT included -- it only feeds gen_noreturn_syms.py's generator, not the
    evidence maspsx reads at gate time."""
    fam = "dungeon" if cont == "dungeon_engine" else cont
    names = ("noreturn_syms.txt", "sibcall_syms.txt") if fam == "main" \
        else (f"noreturn_syms.{fam}.txt", f"sibcall_syms.{fam}.txt")
    return [p for p in (ROOT / "config" / n for n in names) if p.exists()]

def inputs_sha(yaml_path):
    """sha over the window YAML, the row table, every src/<container>/*.c inside the window, and
    the container family's noreturn + sibcall census files (census_files).  Those census files are
    read by maspsx's LEAD 18/22 tail-call passes and flip jal<->j family-wide, so a census edit has
    to invalidate every window's cached sha even though it touches no YAML, split record or src/
    file -- before this fix a census edit left every window reporting up to date and gate_all.py
    silently gated nothing (measured 2026-09-22: `--container dungeon` gated 0 windows; `--retry`
    gated 1,458).  Changing this function invalidates every window's cached inputs_sha at once; the
    next standing full gate pays that cost once, which is intended."""
    h = hashlib.sha256(yaml_path.read_bytes())
    cont = container_of(yaml_path.stem)
    # the window's own split records (config, extent, verdict) rather than the whole table, so a
    # corrected compiler cell re-gates the windows that hold that row and no other
    for rec in split_records(cont, yaml_path.name):
        h.update(json.dumps(rec, sort_keys=True).encode())
    for r in window_rows().get(yaml_path.name, []):
        p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
        if p.exists(): h.update(p.read_bytes())
    for p in census_files(cont):
        h.update(p.read_bytes())
    return h.hexdigest()

_SPLITS = {}
def split_records(cont, yaml_name):
    """Split-table records whose extent lies inside the window's file range."""
    if cont not in _SPLITS:
        _SPLITS[cont] = read_jsonl(ROOT / "ledger/splits" / f"{cont}.jsonl")
    from common import window_map
    fam = "dungeon" if cont == "dungeon_engine" else cont
    rng = next(((fs, fe) for n, fs, fe, _ in window_map().get(fam, []) if n == yaml_name), None)
    if rng is None: return []
    fs, fe = rng
    return [r for r in _SPLITS[cont] if isinstance(r.get("foff"), int) and fs <= r["foff"] and r["foff"] + (r.get("size") or 0) <= fe]

LANE_ROOT = ROOT / "build_ovl"          # the root the model lanes score in (tools/verify.py)
ISOLATED = B.resolve() != LANE_ROOT.resolve()

@contextlib.contextmanager
def window_lock(yaml_name):
    """In an ISOLATED root, take the same per-window lock tools/verify.py uses
    (build_ovl/work/<window>.lock, verify.window_lock): a lane running `verify.py --gate` swaps its
    candidate into src/ under that lock, and a window compiled in the middle of that swap would be
    gating a text the tree does not hold.  In the default root nothing is taken - unchanged."""
    if not ISOLATED:
        yield; return
    import fcntl
    p = LANE_ROOT / "work" / f"{yaml_name}.lock"
    p.parent.mkdir(parents=True, exist_ok=True)
    with open(p, "w") as fh:
        fcntl.flock(fh, fcntl.LOCK_EX)
        try:
            yield
        finally:
            fcntl.flock(fh, fcntl.LOCK_UN)

def run_window(yaml_path):
    t0 = time.time()
    with window_lock(yaml_path.name):
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
        sha = inputs_sha(yaml_path)   # under the lock: the sha describes the text that was gated
    detail = detail.replace(str(ROOT), "<repo>").replace(str(Path.home()), "<home>")
    m = re.search(r"\((\d+) bytes\)", detail)
    return {"window": yaml_path.stem.replace(".overlay", ""), "container": container_of(yaml_path.stem), "result": res, "bytes": int(m.group(1)) if m else None,
            "detail": detail, "secs": round(time.time() - t0, 1), "inputs_sha": sha, "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}

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
        for future in as_completed([ex.submit(run_window, y) for y in todo]):
            rec = future.result()
            append_jsonl(JOURNAL, rec); n += 1; tally[rec["result"]] = tally.get(rec["result"], 0) + 1
            if n % 50 == 0: print(f"{n}/{len(todo)} {time.time()-t0:.0f}s {tally}", flush=True)
    # a parallel run can leave transient failures (shared extract reads); retry those serially
    last = {j["window"]: j for j in read_jsonl(JOURNAL)}
    retry = [y for y in todo if (lambda w: w and w["result"] != "MATCH" and "No such file" not in w["detail"])(last.get(y.stem.replace(".overlay", "")))]
    for y in retry:
        rec = run_window(y); rec["retry"] = True; append_jsonl(JOURNAL, rec); tally[rec["result"] + " (retry)"] = tally.get(rec["result"] + " (retry)", 0) + 1
    print(f"done {n} (+{len(retry)} serial retries) in {time.time()-t0:.0f}s: {tally}")
    # A completed subprocess is not a successful gate. Include cached failures, too.
    last = {j["window"]: j for j in read_jsonl(JOURNAL)}
    scope = todo if a.limit else yamls
    bad = [y.name for y in scope if not gate_current(last.get(y.stem.replace(".overlay", "")), inputs_sha(y))]
    if bad:
        print(f"FAILED: {len(bad)} windows lack a current MATCH: {bad[:8]}", file=sys.stderr)
        raise SystemExit(1)

def gate_current(record, expected_sha):
    return bool(record and record.get("result") == "MATCH" and record.get("inputs_sha") == expected_sha)

if __name__ == "__main__":
    main()
