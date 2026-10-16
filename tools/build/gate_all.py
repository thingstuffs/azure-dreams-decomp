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
import argparse, contextlib, hashlib, io, json, math, os, re, signal, subprocess, sys, time, traceback
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor, as_completed
from bisect import bisect_left, bisect_right
from contextvars import ContextVar
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
B = ROOT / os.environ.get("GATE_BUILD_ROOT", "build_ovl")
JOURNAL = Path(os.environ.get("GATE_JOURNAL", ROOT / "ledger/gate.jsonl"))
if not JOURNAL.is_absolute(): JOURNAL = ROOT / JOURNAL
sys.path.insert(0, str(ROOT / "tools"))
from common import read_jsonl, append_jsonl
from source_layout import row_path as layout_row_path

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
    that is the correct (and already-safe) hash contribution. Banked noreturn is additionally bound by scoped_inputs below; these tracked files
    remain audit inputs. Family false members participate in the scoped contribution."""
    fam = "dungeon" if cont == "dungeon_engine" else cont
    names = ("noreturn_syms.txt", "sibcall_syms.txt") if fam == "main" \
        else (f"noreturn_syms.{fam}.txt", f"sibcall_syms.{fam}.txt")
    return [p for p in (ROOT / "config" / n for n in names) if p.exists()]

def legacy_inputs_sha(yaml_path):
    """sha over the window YAML, the row table, every src/<container>/*.c inside the window, and
    the container family's noreturn + sibcall census files (census_files), plus
    every banked C segment's per-region frozen evidence and family false members.  Those census files are
    read by maspsx's LEAD 18/22 tail-call passes and flip jal<->j family-wide, so a census edit has
    to invalidate every window's cached sha even though it touches no YAML, split record or src/
    file -- before this fix a census edit left every window reporting up to date and gate_all.py
    silently gated nothing (measured 2026-09-22: `--container dungeon` gated 0 windows; `--retry`
    gated 1,458).  Changing this function invalidates every window's cached inputs_sha at once; the
    next standing full gate pays that cost once, which is intended."""
    h = hashlib.sha256(b"gate_all.inputs.v3.scoped-rowbase\0")
    h.update(yaml_path.read_bytes())
    cont = container_of(yaml_path.stem)
    # the window's own split records (config, extent, verdict) rather than the whole table, so a
    # corrected compiler cell re-gates the windows that hold that row and no other
    for rec in split_records(cont, yaml_path.name):
        h.update(json.dumps(rec, sort_keys=True).encode())
    for r in window_rows().get(yaml_path.name, []):
        p = layout_row_path(r, ROOT)
        if p.exists(): h.update(p.read_bytes())
    # Production C selectors, shared by noreturn and rowbase dependencies.
    records = [*window_rows().get(yaml_path.name, []),
               *(r for r in split_records(cont, yaml_path.name)
                 if r.get("result") == "MATCH" and not r.get("rerun"))]
    if cont == "dungeon_engine":
        records.extend(r for r in split_records("dungeon", yaml_path.name)
                       if r.get("result") == "MATCH" and not r.get("rerun"))
    offsets = [r["foff"] for r in records if isinstance(r.get("foff"), int)
               and r.get("source_kind", "c") == "c"]
    fam = "dungeon" if cont == "dungeon_engine" else cont
    # scoped_inputs binds region identities and noreturn names, not the delta
    # or confidence the LINKER reads. Bind complete selected rowbase records.
    rowbase = ROOT / 'config/overlays' / (fam + '.rowbase.jsonl')
    if rowbase.exists():
        from gate.gate_read_cache import read_records
        selected = [r for r in read_records(rowbase)
                    if any(int(str(r['foff_start']), 0) <= off < int(str(r['foff_end']), 0)
                           for off in offsets)]
        h.update(json.dumps(selected, sort_keys=True, separators=(',', ':')).encode())
    if cont in {"town", "dungeon", "dungeon_engine"}:
        from gate.gen_noreturn_syms import scoped_inputs
        h.update(json.dumps(scoped_inputs(fam, offsets, root=ROOT),
                            sort_keys=True, separators=(",", ":")).encode())
    for p in census_files(cont):
        h.update(p.read_bytes())
    # the family's rodata-owner records (round 85, overlay_local_gate.rodata_owner) decide how an owner row is
    # linked, so an edit to them must re-gate the family's windows like a census edit does
    owners = ROOT / "config/overlays" / f"{'dungeon' if cont == 'dungeon_engine' else cont}.rodata_owners.jsonl"
    if owners.exists():
        h.update(owners.read_bytes())
    # the absolute-address symbol file (round 95 equate migration) resolves names the window's rows reference
    # (overlay_local_gate ABS_SYMS_FILE), so an edit to it re-gates every window, as a census edit does
    abs_syms = ROOT / "config/overlays/abs_syms.txt"
    if abs_syms.exists():
        h.update(abs_syms.read_bytes())
    # Even a one-member window depends on every sibling and the physical recipe.
    from gate.overlay_module_gate import fingerprint
    for module in window_modules().get(yaml_path.name, []):
        cache = _MODULE_SHA_SNAPSHOT.get()
        key = (ROOT, module["key"])
        digest = cache.get(key) if cache is not None else None
        if digest is None:
            digest = fingerprint(module, ROOT)["sha256"]
            if cache is not None: cache[key] = digest
        h.update(digest.encode())
    return h.hexdigest()

def inputs_sha(yaml_path):
    # v4: complete dependency projection for ordinary windows as well as TUs.
    # No historical v3 journal digest can be promoted without a new proof.
    from lanes.proof_receipts import window_inputs, hashed
    return hashed(window_inputs(ROOT, 'config/overlays/'+yaml_path.name))

_MODULE_SHA_SNAPSHOT = ContextVar("gate_module_sha_snapshot", default=None)

@contextlib.contextmanager
def inputs_snapshot():
    """Bound repeated evidence reads to one incremental SHA sweep.

    Worker run_window hashes are deliberately outside this context. Discard
    the snapshot before compiling and use a new one for the final audit.
    """
    from gate.gen_noreturn_syms import scoped_input_snapshot
    token = _MODULE_SHA_SNAPSHOT.set({})
    try:
        from lanes.proof_receipts import input_snapshot
        with scoped_input_snapshot(), input_snapshot():
            yield
    finally:
        _MODULE_SHA_SNAPSHOT.reset(token)

_WMODULES = None
def window_modules():
    """Snapshot module placement once, like window_rows and split_records.

    Do not reload/validate the whole roster and reread all window YAMLs for
    every SHA. Fingerprints themselves are recomputed for each affected window
    so mutable source/evidence inputs remain current during worker gates.
    Publish only a complete local table, as with window_rows.
    """
    global _WMODULES
    if _WMODULES is None:
        from gate.overlay_module_gate import load_modules, affected_windows
        modules = {}
        for module in load_modules(ROOT):
            for name in affected_windows(module, ROOT):
                modules.setdefault(Path(name).name, []).append(module)
        _WMODULES = modules
    return _WMODULES

_SPLITS = {}
_SPLIT_INDEX = {}
def split_records(cont, yaml_name):
    """Split-table records whose extent lies inside the window's file range."""
    if cont not in _SPLITS:
        _SPLITS[cont] = read_jsonl(ROOT / "ledger/splits" / f"{cont}.jsonl")
    from common import window_map
    fam = "dungeon" if cont == "dungeon_engine" else cont
    rng = next(((fs, fe) for n, fs, fe, _ in window_map().get(fam, []) if n == yaml_name), None)
    if rng is None: return []
    fs, fe = rng
    records = _SPLITS[cont]
    cached = _SPLIT_INDEX.get(cont)
    if cached is None or cached[0] is not records:
        index = sorted((r["foff"], i) for i, r in enumerate(records)
                       if isinstance(r.get("foff"), int))
        cached = (records, [off for off, _ in index], [i for _, i in index])
        _SPLIT_INDEX[cont] = cached
    _, offsets, indexes = cached
    # Preserve ledger order (and thus existing SHAs), while visiting only rows
    # whose start can lie inside this window instead of every family row.
    candidates = indexes[bisect_left(offsets, fs):bisect_right(offsets, fe)]
    return [records[i] for i in sorted(candidates)
            if records[i]["foff"] + (records[i].get("size") or 0) <= fe]

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

def schedule_windows(windows, prior):
    """Longest recorded run first; unknown/invalid costs lead, ties are stable."""
    def cost(path):
        value = prior.get(path.stem.replace(".overlay", ""), {}).get("secs")
        if not isinstance(value, (int, float)) or not math.isfinite(value) or value < 0:
            return float("inf")
        return value
    return sorted(windows, key=cost, reverse=True)

_GATE_WORKER = None

def init_worker(receipts=None,transaction=None,portable_output=None):
    # Same scheduling priority as the old `nice -n10 python3` subprocess.
    os.nice(10)
    os.chdir(B)
    sys.path.insert(0, str(B / "tools"))
    global _GATE_WORKER
    global _RECEIPTS,_TRANSACTION
    global _PORTABLE_OUTPUT
    _RECEIPTS=receipts;_TRANSACTION=transaction;_PORTABLE_OUTPUT=portable_output
    import overlay_local_gate
    _GATE_WORKER = overlay_local_gate


def worker_output(yaml_path):
    """Run the unchanged checks in a persistent interpreter, with a per-job deadline."""
    out, err = io.StringIO(), io.StringIO()
    # These historical memos were designed for a single gate invocation.
    _GATE_WORKER._RENAMED = None
    _GATE_WORKER._RODATA_OWNERS.clear()
    import overlay_as_flags
    overlay_as_flags._MAIN_TABLE = None
    if _GATE_WORKER._MATCH_MOD is not None:
        _GATE_WORKER._MATCH_MOD.DEFAULT_FUNC_AS_FLAGS = _GATE_WORKER._MATCH_MOD._default_func_as_flags()
    def timeout(signum, frame):
        raise TimeoutError("timeout")
    previous = signal.signal(signal.SIGALRM, timeout)
    signal.alarm(3600)
    try:
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            try:
                _GATE_WORKER.main(["--config", str(yaml_path.relative_to(B)), "--clean"])
            except SystemExit as e:
                if e.code: print(e.code, file=sys.stderr)
            except TimeoutError:
                raise
            except Exception:
                traceback.print_exc()
    finally:
        signal.alarm(0)
        signal.signal(signal.SIGALRM, previous)
        # Object identities and large per-window indexes must not accumulate.
        _GATE_WORKER._NM_CACHE.clear()
    return (out.getvalue() + err.getvalue()).strip().splitlines()


_RECEIPTS = None
_TRANSACTION = None
_PORTABLE_OUTPUT = None

def run_window(yaml_path, in_process=False):
    t0 = time.time()
    with window_lock(yaml_path.name):
        publish = _RECEIPTS is not None and bool(window_modules().get(yaml_path.name))
        from lanes import proof_receipts as P
        target=yaml_path.relative_to(B).as_posix()
        P.validate_view(ROOT,B,target)
        with P.input_snapshot():proof_before=P.window_inputs(ROOT,target)
        before = P.hashed(proof_before)
        try:
            if in_process:
                out = worker_output(yaml_path)
            else:
                r = subprocess.run(["nice", "-n10", "python3", "tools/overlay_local_gate.py", "--config", str(yaml_path.relative_to(B)), "--clean"],
                                   cwd=B, capture_output=True, text=True, timeout=3600)
                out = (r.stdout + r.stderr).strip().splitlines()
            last = next((l for l in reversed(out) if l.startswith(("MATCH", "NO MATCH"))), None)
            if last is None:
                res, detail = "ERROR", (out[-1] if out else "")[:200]
            else:
                res, detail = ("MATCH" if last.startswith("MATCH") else "NO MATCH"), last[:200]
        except (subprocess.TimeoutExpired, TimeoutError):
            res, detail = "ERROR", "timeout"
        P.validate_view(ROOT,B,target)
        sha = inputs_sha(yaml_path)   # under the lock: the sha describes the text that was gated
        if before is not None and sha != before:
            res, detail = 'ERROR', 'inputs changed during fresh window gate'
        rec = {"window": yaml_path.stem.replace(".overlay", ""), "container": container_of(yaml_path.stem), "result": res,
               "inputs_sha": sha}
        if _PORTABLE_OUTPUT is not None and res == 'MATCH':
            P.export_window(ROOT,B,target,Path(_PORTABLE_OUTPUT)/yaml_path.stem.replace('.overlay',''),proof_before,out)
        if publish and res == 'MATCH':
            from fidelity.certify_overlay_module import snapshot_gate_window
            snapshot_gate_window(B,yaml_path.relative_to(B).as_posix(),_RECEIPTS,_TRANSACTION,rec,out)
    detail = detail.replace(str(ROOT), "<repo>").replace(str(Path.home()), "<home>")
    m = re.search(r"\((\d+) bytes\)", detail)
    return {"window": yaml_path.stem.replace(".overlay", ""), "container": container_of(yaml_path.stem), "result": res, "bytes": int(m.group(1)) if m else None,
            "detail": detail, "secs": round(time.time() - t0, 1), "inputs_sha": sha, "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--only-window',action='append',default=[],help='explicit production configs for a scoped lane proof run; never passed by the production lander')
    ap.add_argument('--portable-output',type=Path,help='export input-bound lane proof artifacts for every freshly built window')
    ap.add_argument('--carried-proofs',type=Path,help='reviewed index mapping production configs to portable lane evidence directories')
    ap.add_argument('--require-window', action='append', default=[], help='production config that must be freshly gated even when its input hash is current')
    ap.add_argument("--container"); ap.add_argument("--workers", type=int, default=default_workers()); ap.add_argument("--limit", type=int); ap.add_argument("--retry", action="store_true"); ap.add_argument("--all", action="store_true", help="gate every window regardless of its cached inputs_sha (after a pipeline/tool change, which inputs_sha does not cover)")
    ap.add_argument("--worker-mode", choices=("process", "subprocess"), default="process",
                    help="persistent gate interpreters (default) or the legacy per-window subprocess")
    ap.add_argument('--receipts', type=Path, help='new directory for this invocation only; cached windows are never published')
    ap.add_argument('--transaction', help='caller-owned fresh transaction token, required with --receipts')
    a = ap.parse_args()
    if a.workers<1:ap.error('workers must be positive')
    if bool(a.receipts)!=bool(a.transaction):ap.error('--receipts and --transaction are required together')
    global _RECEIPTS,_TRANSACTION,_PORTABLE_OUTPUT
    _PORTABLE_OUTPUT=a.portable_output.resolve() if a.portable_output else None
    if _PORTABLE_OUTPUT is not None:_PORTABLE_OUTPUT.mkdir(parents=True,exist_ok=False)
    _RECEIPTS=a.receipts.resolve() if a.receipts else None;_TRANSACTION=a.transaction
    if _RECEIPTS is not None:_RECEIPTS.mkdir(parents=True,exist_ok=False)
    tool_sha=hashlib.sha256((ROOT/'tools/build/gate_all.py').read_bytes()).hexdigest() if _RECEIPTS is not None else None
    yamls = sorted((B / "config/overlays").glob("*.overlay.yaml"))
    sup = superseded(yamls)
    yamls = [y for y in yamls if y.name not in sup]
    if a.container: yamls = [y for y in yamls if container_of(y.stem) == a.container]
    if a.only_window:
        requested=set(a.only_window);available={y.relative_to(B).as_posix() for y in yamls}
        if requested-available:ap.error('requested windows outside active production scope: '+', '.join(sorted(requested-available)))
        yamls=[y for y in yamls if y.relative_to(B).as_posix() in requested]
    required = set(a.require_window)
    active = {y.relative_to(B).as_posix() for y in yamls}
    if required - active:
        ap.error('required windows outside active production scope: ' + ', '.join(sorted(required - active)))
    if required and a.limit:
        ap.error('--limit cannot truncate required window proofs')
    prior = {j["window"]: j for j in read_jsonl(JOURNAL)}
    dead = [w for w in prior if w + ".overlay.yaml" in sup]
    if dead:
        from common import write_jsonl
        write_jsonl(JOURNAL, [j for j in read_jsonl(JOURNAL) if j["window"] + ".overlay.yaml" not in sup])
        prior = {j["window"]: j for j in read_jsonl(JOURNAL)}
        print(f"{len(sup)} superseded synthetic-base seed windows skipped ({len(dead)} stale journal records dropped); their _truebase_ twins are gated")
    carried={}
    if a.carried_proofs:
        carried=json.loads(a.carried_proofs.read_text())
        if not isinstance(carried,dict) or set(carried)-active:ap.error('carried windows outside active production scope')
    reused={}
    todo = []
    with inputs_snapshot():
        for y in yamls:
            w = y.stem.replace(".overlay", ""); p = prior.get(w)
            target=y.relative_to(B).as_posix()
            if a.all or a.retry:
                todo.append(y);continue
            if target in carried and not a.all and not a.retry:
                from lanes import proof_receipts as P
                try:
                    current=inputs_sha(y)
                    rec=dict(window=w,container=container_of(y.stem),result='MATCH',inputs_sha=current,
                             detail='input-bound lane proof',secs=0,at=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()))
                    if _RECEIPTS is not None:P.import_window(ROOT,B,target,carried[target],_RECEIPTS,_TRANSACTION,rec)
                    else:P.verify(ROOT,carried[target],expected_kind='overlay-window',expected_target=target)
                    append_jsonl(JOURNAL,rec);prior[w]=rec;reused[target]=carried[target]
                    continue
                except (OSError,ValueError,KeyError,TypeError,subprocess.SubprocessError) as e:
                    print('portable proof miss '+target+': '+str(e),flush=True)
                    todo.append(y);continue
            if p and p["result"] == "MATCH" and p.get("inputs_sha") == inputs_sha(y) and not a.retry and not a.all and y.relative_to(B).as_posix() not in required: continue
            if p and p["result"] != "MATCH" and not a.retry and not a.all and p.get("inputs_sha") == inputs_sha(y): continue
            todo.append(y)
    if a.limit: todo = todo[:a.limit]
    print(f'{len(reused)} windows use current input-bound lane proofs',flush=True)
    todo = schedule_windows(todo, prior)
    print(f"{len(todo)} windows to gate ({len(yamls) - len(todo)} up to date), {a.workers} workers", flush=True)
    t0 = time.time(); n = 0; tally = {}
    in_process = a.worker_mode == "process"
    pool = ProcessPoolExecutor if in_process else ThreadPoolExecutor
    options = {"initializer": init_worker,"initargs":(_RECEIPTS,_TRANSACTION,_PORTABLE_OUTPUT)} if in_process else {}
    with pool(max_workers=a.workers, **options) as ex:
        for future in as_completed([ex.submit(run_window, y, in_process) for y in todo]):
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
    with inputs_snapshot():
        bad = [y.name for y in scope if not gate_current(last.get(y.stem.replace(".overlay", "")), inputs_sha(y))]
    from lanes import proof_receipts as P
    with P.input_snapshot():
        for target,directory in reused.items():P.verify(ROOT,directory,expected_kind='overlay-window',expected_target=target)
    if bad:
        print(f"FAILED: {len(bad)} windows lack a current MATCH: {bad[:8]}", file=sys.stderr)
        raise SystemExit(1)
    if _RECEIPTS is not None:
        from fidelity.certify_overlay_module import sha
        if sha(ROOT/'tools/build/gate_all.py')!=tool_sha:raise ValueError('gate tool changed during fresh receipt publication')
        fresh={}
        proved={y.relative_to(B).as_posix() for y in todo}|set(reused)
        for directory in _RECEIPTS.iterdir():
            p=directory/'receipt.json'
            if p.is_file():
                config=json.loads(p.read_text())['config']
                if config not in proved:raise ValueError('receipt was not gated in this invocation')
                fresh[config]=sha(p)
        index={'schema':1,'result':'PASS','transaction':_TRANSACTION,'authority':str(ROOT.resolve()),'view':str(B.resolve()),
               'gate_tool_sha256':tool_sha,'windows':fresh}
        p=_RECEIPTS/'index.json';tmp=p.with_suffix('.tmp');tmp.write_text(json.dumps(index,sort_keys=True)+'\n');tmp.replace(p)
        print(f'fresh certification receipts: {len(fresh)} windows',flush=True)

def gate_current(record, expected_sha):
    return bool(record and record.get("result") == "MATCH" and record.get("inputs_sha") == expected_sha)

def default_workers():
    available=len(os.sched_getaffinity(0)) if hasattr(os,'sched_getaffinity') else (os.cpu_count() or 1)
    return max(1,min(16,available-available//3))

if __name__ == "__main__":
    main()
