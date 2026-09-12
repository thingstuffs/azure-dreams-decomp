#!/usr/bin/env python3
"""Durable pin-search controller: prepare, run/start, status, gate-pilot, publish.

Workers only write immutable candidates and atomic result files. A controller-wide lock owns
publication. Interrupted rows resume from frozen inputs and the persistent compilation cache;
budget exhaustion is explicit and a larger budget is a new run, not a false completed match.
"""
import argparse
import collections
import concurrent.futures
import contextlib
import fcntl
import hashlib
import json
import os
import random
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, sha_text, sha_file, PARKED_CONTAINERS, parse_cfg

BASE = ROOT / "work/pin_search"
POLICY_ENV = {"T15_WIDE": "1", "T15_NOFENCE": "1", "T15_FAKE": "0", "PIN_CC_TIMEOUT": "30"}

def utc(): return time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())

def process_identity(pid):
    try:
        p=Path('/proc')/str(pid)
        if b'pin_search.py' not in (p/'cmdline').read_bytes(): return None
        return (p/'stat').read_text().rsplit(') ',1)[1].split()[19]
    except (OSError,IndexError): return None

def initialize_worker(parent_pid):
    # Linux workers must not retain the controller lock forever after a killed parent.
    # Candidate/checkpoint files are already durable; an interrupted row is replayable.
    import ctypes
    libc=ctypes.CDLL(None,use_errno=True)
    if libc.prctl(1,signal.SIGTERM,0,0,0)!=0: raise OSError(ctypes.get_errno(),"PR_SET_PDEATHSIG")
    if os.getppid()!=parent_pid: os.kill(os.getpid(),signal.SIGTERM)

def atomic_json(path, data):
    path = Path(path); path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(mode="w", dir=path.parent, delete=False) as f:
        json.dump(data, f, indent=2); f.write("\n"); f.flush(); os.fsync(f.fileno()); tmp = f.name
    os.replace(tmp, path)

def atomic_text(path, text):
    path = Path(path); path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(mode="w", dir=path.parent, delete=False) as f:
        f.write(text); f.flush(); os.fsync(f.fileno()); tmp = f.name
    os.replace(tmp, path)

def digest(value): return sha_text(json.dumps(value, sort_keys=True, separators=(",", ":")))

def safe_tag(tag):
    if not re.fullmatch(r"[a-zA-Z0-9_-]+", tag): raise ValueError("tag must contain only letters, digits, _ or -")
    return BASE / tag

@contextlib.contextmanager
def ownership():
    BASE.mkdir(parents=True, exist_ok=True); (BASE / ".ignore").write_text("*\n")
    with (BASE / "controller.lock").open("a") as f:
        try: fcntl.flock(f, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError: raise RuntimeError("another pin-search controller owns the workspace")
        yield

def fingerprints(selected):
    """Hash explicit, narrow input trees once per controller, never an unrestricted repo walk."""
    recipe_paths = {p for p in (ROOT / "include").rglob("*") if p.is_file()}
    for d in ("tools/gate", "tools/build", "tools/maspsx"):
        recipe_paths.update(p for p in (ROOT / d).rglob("*") if p.is_file() and p.suffix in (".py", ".sh", ".json"))
    recipe_paths.update((ROOT / "config").glob("*.txt"))
    recipe_paths.update((ROOT / "config").glob("*.json"))
    recipe_paths.update((ROOT / "config").glob("*.tsv"))
    recipe_paths.add(ROOT / "ledger/cache/slus_obj.json")
    for r in selected:
        if r.get("kind") == "slus": recipe_paths.add(ROOT / "ledger/cache/slus_dis" / (r["id"].split("/")[1]+".txt"))
    recipe_paths.update((ROOT / "config/overlays").glob("*.yaml"))
    recipe_paths.update(ROOT / p for p in ("tools/verify.py", "tools/common.py", "tools/xform/screen.py", "PIN"))
    for cell in {parse_cfg(r["cfg"])[0] for r in selected}:
        recipe_paths.update(p for p in (ROOT / "toolchain/compilers" / ("gcc-" + cell)).iterdir()
                            if p.is_file() and p.name in ("gcc", "cc1", "cpp", "as"))
    for exe in ("mipsel-linux-gnu-as", "mipsel-linux-gnu-ld", "mipsel-linux-gnu-objdump", "gcc", "python3"):
        p = shutil.which(exe)
        if p: recipe_paths.add(Path(p).resolve())
    recipe = {str(p.relative_to(ROOT)) if p.is_relative_to(ROOT) else str(p): sha_file(p)
              for p in sorted(recipe_paths) if p.exists()}
    # Bind the actual retail inputs, not only their names. These are individual known files.
    for p in list((ROOT / "work/disc/containers").glob("*.BIN")) + [ROOT / "work/disc/extract/SLUS_006.14"]:
        if p.exists(): recipe[str(p.relative_to(ROOT))] = sha_file(p)
    search_paths = list((ROOT / "tools/xform").glob("*.py"))
    search_paths += [ROOT / "tools" / p for p in ("pin_search.py", "pin_search_engine.py", "pin_sites.py", "pin_census.py", "census.py")]
    search_paths += [ROOT / "ledger" / p for p in ("pins_site.jsonl", "pins_subsets.jsonl")]
    search = {str(p.relative_to(ROOT)): sha_file(p) for p in search_paths if p.exists()}
    return dict(recipe=digest(recipe), search=digest(search), recipe_inputs=recipe, search_inputs=search)

def run_key(manifest):
    return digest({k: manifest[k] for k in ("rows", "fingerprints", "options", "environment", "modes")})

def configure(env):
    # Ambient search flags must not silently affect candidate generation or the resume key.
    for k in list(os.environ):
        if k.startswith(("T15_", "T20_", "T27_", "NATURAL_", "PIN_CC_", "AZURE_MASPSX")) or k in (
                "GCC_EXEC_PREFIX","COMPILER_PATH","CPATH","C_INCLUDE_PATH","LIBRARY_PATH"):
            os.environ.pop(k)
    os.environ.update(env)

def prepare(a):
    from pin_census import sites_of, asm_blocker
    from xform.natural import fences
    from pin_search_engine import DEFAULTS
    if a.pilot and a.mode not in ("baseline", "targeted"):
        raise ValueError("this mode cannot be combined with the pin comparison pilot")
    if getattr(a, "families_only", False) and a.mode != "erasures":
        raise ValueError("--families-only requires --mode erasures")
    d = safe_tag(a.tag)
    if (d / "manifest.json").exists(): raise RuntimeError("tag already prepared; use run to resume or a new tag")
    rs = [r for r in rows() if r.get("stock") and r.get("exists") and r["container"] not in PARKED_CONTAINERS]
    eligible = [(r, clean_path(r).read_text()) for r in rs if clean_path(r).exists()]
    eligible = [(r, t) for r, t in eligible if (sites_of(t) if a.mode != "fences" else fences(t)) and not asm_blocker(t)]
    if a.ids:
        keep = set(Path(a.ids).read_text().replace("\n", ",").strip(",").split(","))
        eligible = [(r, t) for r, t in eligible if r["id"] in keep]
    replay = []
    if a.pilot:
        rec = ROOT / "work/pin_recovery_20260912/inventory.json"
        if rec.exists():
            lookup = {r["id"]: r for r in rs}
            for x in json.loads(rec.read_text())[:12]:
                r = lookup[x["id"]]
                t = subprocess.check_output(["git", "show", a.replay_commit + ":" + x["path"]], cwd=ROOT, text=True)
                if sites_of(t) and not asm_blocker(t): replay.append((r, t))
    chosen = list(replay)
    used = {r["id"] for r, _ in chosen}
    # Round-robin compiler x pin-count strata, deterministic within each stratum.
    buckets = collections.defaultdict(list); rng = random.Random(a.seed)
    for r, t in eligible:
        if r["id"] not in used:
            n = len(sites_of(t)); buckets[(r["cfg"], "single" if n == 1 else "2-5" if n <= 5 else "6+")].append((r,t))
    for xs in buckets.values(): rng.shuffle(xs)
    limit = a.sample or len(eligible)
    while len(chosen) < limit and any(buckets.values()):
        for key in sorted(buckets):
            if buckets[key] and len(chosen) < limit: chosen.append(buckets[key].pop())
    d.mkdir(parents=True, exist_ok=True)
    records = []
    for r, t in chosen:
        p = d / "inputs" / (r["id"].replace("/", "_") + ".c"); atomic_text(p, t)
        records.append(dict(row=r, source_sha=sha_text(t), input=str(p.relative_to(d)),
                            current_sha=sha_file(clean_path(r)), replay=r["id"] in used))
    opts = dict(DEFAULTS, screens=a.screens, verifies=a.verifies, cpu_seconds=a.cpu_seconds,
                objective="fences" if a.mode == "fences" else "pins",
                fallback=getattr(a, "fallback", DEFAULTS["fallback"]),
                families_only=getattr(a, "families_only", False))
    manifest = dict(schema=1, created=utc(), tag=a.tag, rows=records, options=opts,
                    modes=["baseline", "targeted"] if a.pilot else [a.mode],
                    environment=POLICY_ENV, fingerprints=fingerprints([r for r, _ in chosen]))
    manifest["options"]["cache_namespace"] = a.tag if a.pilot else "production"
    manifest["run_key"] = run_key(manifest)
    atomic_json(d / "manifest.json", manifest)
    print(f"prepared {a.tag}: {len(records)} rows; modes={manifest['modes']}; key={manifest['run_key'][:12]}")

def load_manifest(d, check=True):
    m = json.loads((d / "manifest.json").read_text())
    if run_key(m) != m["run_key"]: raise RuntimeError("manifest identity changed")
    if check:
        now=fingerprints([x["row"] for x in m["rows"]])
        changed = now["recipe"]!=m["fingerprints"]["recipe"] if check=="recipe" else now!=m["fingerprints"]
        if changed: raise RuntimeError("search/toolchain/header/evidence inputs changed; prepare a new tag (cache is reusable)")
    for x in m["rows"]:
        if sha_file(d / x["input"]) != x["source_sha"]: raise RuntimeError("frozen input changed: " + x["row"]["id"])
    return m

def result_path(d, mode, rowid): return d / "results" / mode / (rowid.replace("/", "_") + ".json")

def job_key(manifest,item,mode):
    return digest(dict(row=item["row"],source_sha=item["source_sha"],mode=mode,
        fingerprints=manifest["fingerprints"],options=manifest["options"],environment=manifest["environment"]))

def cache_result(d,manifest,item,mode,result):
    if not reusable(result,manifest["run_key"]):return
    atomic_json(BASE/"completed"/(job_key(manifest,item,mode)+".json"),
                dict(directory=str(d.relative_to(BASE)),result=result))

def reuse_completed(d,manifest,item,mode):
    key=job_key(manifest,item,mode);p=BASE/"completed"/(key+".json")
    if not p.exists():return False
    saved=json.loads(p.read_text());r=saved["result"];origin=BASE/saved["directory"]
    if r.get("job_key")!=key or not reusable(r,r.get("run_key")):return False
    if r.get("candidate"):
        source=origin/r["candidate"]
        if not source.exists() or sha_file(source)!=r["candidate_sha"]:return False
        if source!=d/r["candidate"]:atomic_text(d/r["candidate"],source.read_text())
    if r.get("timeout"):
        evidence=r["timeout"];source=origin/evidence["source"]
        if not source.exists() or sha_file(source)!=evidence["source_sha"]:return False
        if source!=d/evidence["source"]:atomic_text(d/evidence["source"],source.read_text())
    for n in r.get("near",[]):
        source=origin/n["source"]
        if source.exists() and source!=d/n["source"]:atomic_text(d/n["source"],source.read_text())
    r=dict(r,reused_from=r["run_key"],run_key=manifest["run_key"],at=utc(),historical_cpu_seconds=r.get("cpu_seconds",0))
    for k in ("seconds","cpu_seconds","compiled","screened","tried","generation_seconds","verify_seconds","compile_seconds"):
        r[k]=0
    atomic_json(result_path(d,mode,item["row"]["id"]),r)
    return True

def reusable(result, key):
    # Budget exhaustion is a recorded bounded experiment, not a claim of impossibility.
    # Raising the budget requires a new manifest and schedules the row again.
    return result.get("run_key") == key and result.get("outcome") in ("candidate", "noop", "refused") and result.get("stop_reason") not in (
        "reference-build-error", "candidate-build-failures", "error", "interrupted")

def restore_publication(files, root, directory):
    # Check the complete transaction before any restoration; never erase a concurrent edit.
    for x in files:
        if sha_file(root/x["path"]) not in (x["before_sha"],x["after_sha"]):
            raise RuntimeError("publication recovery source conflict: "+x["path"])
        if sha_file(directory/x["backup"]) != x["before_sha"]:
            raise RuntimeError("publication backup changed: "+x["path"])
    for x in files: atomic_text(root/x["path"],(directory/x["backup"]).read_text())

def record_publication(state, manifest):
    proof=ROOT/"ledger/pin_runs"/(manifest["tag"]+".json")
    atomic_json(proof,dict(run_key=manifest["run_key"],finished=state["finished"],options=manifest["options"],
        recipe=manifest["fingerprints"]["recipe"],search=manifest["fingerprints"]["search"],
        files=[{k:x[k] for k in ("id","path","before_sha","after_sha")} for x in state["files"]],
        deferred=state.get("deferred",[]), overlay="MATCH",slus="MATCH"))

def publication_results(d, manifest, mode, deferred_ids):
    """Explicitly defer named retryable rows without accepting their search as complete."""
    if mode not in manifest["modes"]: raise RuntimeError("mode was not searched")
    pending=set(deferred_ids); accepted=[]; deferred=[]
    for item in manifest["rows"]:
        rowid=item["row"]["id"]; p=result_path(d,mode,rowid)
        if not p.exists(): raise RuntimeError("search incomplete: "+rowid)
        r=json.loads(p.read_text())
        if r.get("run_key")!=manifest["run_key"]: raise RuntimeError("stale result: "+rowid)
        if rowid in pending:
            if reusable(r,manifest["run_key"]): raise RuntimeError("cannot defer a completed result: "+rowid)
            deferred.append(dict(id=rowid,source_sha=item["source_sha"],outcome=r["outcome"],
                stop_reason=r.get("stop_reason"),reason=r.get("reason","").replace(str(ROOT),"<repo>")))
            pending.remove(rowid)
        elif not reusable(r,manifest["run_key"]):
            raise RuntimeError("retryable search failure remains: "+rowid)
        else: accepted.append((item,r))
    if pending: raise RuntimeError("unknown deferred rows: "+", ".join(sorted(pending)))
    return accepted,deferred

def worker(job):
    d, manifest, item, mode = job; d = Path(d)
    configure(manifest["environment"])
    from pin_search_engine import Session
    from pin_census import landing_refusal
    from verify import verify
    row = item["row"]; original = (d / item["input"]).read_text()
    out = dict(id=row["id"], mode=mode, run_key=manifest["run_key"], job_key=job_key(manifest,item,mode), source_sha=item["source_sha"], at=utc())
    session = None
    try:
        cache = BASE / "cache" / manifest["options"].get("cache_namespace","production") / mode; cache.mkdir(parents=True, exist_ok=True)
        def vf(text):
            with tempfile.TemporaryDirectory(prefix="pin_verify_") as tmp:
                p = Path(tmp) / Path(row["c_path"]).name; p.write_text(text)
                return verify(row, p, include_root=ROOT / "include")
        def checkpoint(text):
            sha=sha_text(text);p=d/"candidates"/mode/(sha+".c");atomic_text(p,text)
            atomic_json(d/"progress"/mode/(row["id"].replace("/","_")+".json"),
                dict(run_key=manifest["run_key"],candidate=str(p.relative_to(d)),candidate_sha=sha,source_sha=item["source_sha"]))
        session = Session(row, original, manifest["fingerprints"]["recipe"],
                          cache / (row["id"].replace("/", "_") + ".sqlite"), manifest["options"], vf, checkpoint)
        progress=d/"progress"/mode/(row["id"].replace("/","_")+".json")
        if progress.exists():
            saved=json.loads(progress.read_text());p=d/saved["candidate"]
            if saved.get("run_key")==manifest["run_key"] and sha_file(p)==saved["candidate_sha"]:
                # Reverify a recovered success before retaining it. Search restarts deterministically
                # from frozen input, reusing compilation cache; the prior success cannot be lost.
                session.verify(p.read_text())
        text, info = session.run(mode); out.update(info)
        out["outcome"] = "noop"
        if text != original:
            refusal = landing_refusal(text, original, str(clean_path(row).relative_to(ROOT)))
            if refusal: out.update(outcome="refused", reason=refusal)
            else:
                sha = sha_text(text); p = d / "candidates" / mode / (sha + ".c")
                atomic_text(p, text); out.update(outcome="candidate", candidate=str(p.relative_to(d)), candidate_sha=sha)
        # Compact family packets: at most three unresolved candidate texts per physical row.
        for i, near in enumerate(session.near):
            text = near.pop("text"); p = d / "near" / mode / (row["id"].replace("/", "_") + f"_{i}.c")
            atomic_text(p, text); near["source"] = str(p.relative_to(d))
        out["near"] = session.near
    except Exception as exc:
        out.update(outcome="error", stop_reason="error", reason=repr(exc)[:500])
        if session is not None:
            try: session.db.close()
            except Exception: pass
    if session is not None and session.timeout:
        timeout=dict(session.timeout);text=timeout.pop("text")
        p=d/"timeouts"/mode/(timeout["source_sha"]+".c");atomic_text(p,text)
        out["timeout"]=dict(timeout,source=str(p.relative_to(d)))
    # Workers persist completion themselves, before returning to the parent. A killed parent
    # cannot lose completed results, even when an earlier submitted row is still running.
    atomic_json(result_path(d, mode, row["id"]), out)
    cache_result(d,manifest,item,mode,out)
    return out

def run(a):
    d = safe_tag(a.tag); m = load_manifest(d)
    configure(m["environment"])
    identity=process_identity(os.getpid())
    atomic_json(d / "state.json", dict(phase="searching", pid=os.getpid(), process_identity=identity, started=utc(), run_key=m["run_key"]))
    jobs = []
    for i, x in enumerate(m["rows"]):
        for mode in m["modes"][::1 if i % 2 == 0 else -1]:
            p = result_path(d, mode, x["row"]["id"])
            if not p.exists() or not reusable(json.loads(p.read_text()), m["run_key"]):
                if not reuse_completed(d,m,x,mode):jobs.append((str(d), m, x, mode))
    print(f"{a.tag}: {len(jobs)} pending row/arm jobs, {a.workers} processes", flush=True)
    failures = 0
    with concurrent.futures.ProcessPoolExecutor(max_workers=a.workers,initializer=initialize_worker,initargs=(os.getpid(),)) as pool:
        pending = {}; iterator = iter(jobs)
        def fill():
            while len(pending) < a.workers:
                job = next(iterator, None)
                if job is None: break
                pending[pool.submit(worker, job)] = job
        fill(); done = 0
        while pending:
            ready, _ = concurrent.futures.wait(pending, timeout=10, return_when=concurrent.futures.FIRST_COMPLETED)
            for f in ready:
                pending.pop(f); r = f.result(); done += 1
                failures += r["outcome"] == "error"
                print(f"{done}/{len(jobs)} {r['mode']} {r['id']} {r['outcome']} {r['stop_reason']}", flush=True)
            fill()
            atomic_json(d / "state.json", dict(phase="searching", pid=os.getpid(), updated=utc(),
                        process_identity=identity, completed_this_run=done, pending=len(jobs)-done, failures=failures, run_key=m["run_key"]))
    atomic_json(d / "state.json", dict(phase="search-failed" if failures else "searched", finished=utc(), run_key=m["run_key"]))
    summarize(d, m)
    if failures: raise RuntimeError(f"{failures} worker errors; rerun the same tag to retry")

def summarize(d, m):
    report = dict(tag=m["tag"], run_key=m["run_key"], at=utc(), modes={})
    for mode in m["modes"]:
        records = [json.loads(p.read_text()) for p in (d / "results" / mode).glob("*.json")]
        report["modes"][mode] = dict(records=len(records), outcomes=dict(collections.Counter(r["outcome"] for r in records)),
            stops=dict(collections.Counter(r.get("stop_reason") for r in records)),
            pins_removed=sum(r.get("pins_in",0)-r.get("pins_out",0) for r in records if r["outcome"] == "candidate"),
            fences_removed=sum(r.get("fences_in",0)-r.get("fences_out",0) for r in records if r["outcome"] == "candidate"),
            totals={k:sum(r.get(k,0) for r in records) for k in ("compiled", "screened", "cache_hits", "tried", "seconds", "cpu_seconds", "generation_seconds", "fallback_tried", "fallback_wins", "compile_timeouts")})
    atomic_json(d / "summary.json", report)
    print(json.dumps(report, indent=2))
    return report

def packets(a):
    """Bounded, reusable research packets; no model calls or source mutation."""
    import difflib
    d=safe_tag(a.tag);m=load_manifest(d,check=False)
    items={x["row"]["id"]:x for x in m["rows"]};families=collections.defaultdict(list)
    for p in (d/"results"/a.mode).glob("*.json"):
        r=json.loads(p.read_text())
        if r.get("run_key")!=m["run_key"] or r.get("outcome")!="noop":continue
        for near in r.get("near",[]):families[near["kind"]].append((r,near))
    summary={}
    for kind, candidates in families.items():
        picked=[];seen=set()
        for r,n in sorted(candidates,key=lambda rn:rn[1]["distance"]):
            if r["id"] in seen:continue
            seen.add(r["id"]);picked.append((r,n))
            if len(picked)==3:break
        lines=[f"# {kind}: unresolved pin family", "", f"Run: `{m['run_key']}`; mode: `{a.mode}`.",
               "", "These are search leads, not proven shared fixes. Group indices are local to the search state;",
               "the diff below is against the frozen row input. A near assembly match is not acceptance.",
               "", "Research deliverable: explain the compiler/interface mechanism, state a safe applicability",
               "predicate, implement a reusable generator, and include negative examples. Validate on",
               "held-out family members. Preserve exact target, source and final image/window gates."]
        for r,n in picked:
            item=items[r["id"]];row=item["row"]
            source=(d/item["input"]).read_text();candidate=(d/n["source"]).read_text()
            lines += ["",f"## {r['id']}","",f"Compiler: `{row['cfg']}`; extent: `{row.get('foff')}` + `{row['size']}` bytes.",
                      f"Frozen source: `{item['input']}`; candidate: `{n['source']}`.",
                      f"Group: `{n['group']}`; screen distance: `{n['distance']}`; attempted shape: `{n['label']}`.",
                      f"Stop reason: `{r['stop_reason']}`; recorded attempts: `{r.get('tried',0)}` full verifications, `{r.get('screened',0)}` screens.",
                      "", "```diff", ''.join(difflib.unified_diff(source.splitlines(True),candidate.splitlines(True),n=2)).rstrip(),"```"]
        p=d/"packets"/(kind+".md");atomic_text(p,'\n'.join(lines)+'\n')
        summary[kind]=dict(rows=len({r['id'] for r,_ in candidates}),representatives=[r['id'] for r,_ in picked],packet=str(p.relative_to(d)))
    atomic_json(d/"packets/index.json",dict(run_key=m["run_key"],families=summary));print(json.dumps(summary,indent=2))

def gate_slus_copy(source, destination, log_path, workers):
    """Independent full-executable gate over an isolated source view and build outputs."""
    if destination.exists(): shutil.rmtree(destination)
    shutil.copytree(ROOT/"build_slus",destination,symlinks=True)
    (destination/"src").unlink();(destination/"src").symlink_to(source/"slus",target_is_directory=True)
    recipe=destination/"build.ninja"
    if sha_file(recipe)!=sha_file(ROOT/"ledger/splits/slus.build.ninja"):
        raise RuntimeError("isolated SLUS recipe differs from pinned recipe")
    with log_path.open("w") as log:
        subprocess.run(["nice","-n10","ninja","-C",str(destination),"-j",str(workers)],
                       cwd=ROOT,stdout=log,stderr=subprocess.STDOUT,check=True)
        # Explicitly recheck the final image even if ninja found an up-to-date stamp.
        subprocess.run(["sha1sum","-c","config/slus_006.14.sha1"],cwd=destination,
                       stdout=log,stderr=subprocess.STDOUT,check=True)
    return dict(result="MATCH",recipe_sha256=sha_file(recipe),log=str(log_path.relative_to(ROOT)))

def gate_pilot(a):
    from promote import windows_of
    d = safe_tag(a.tag); m = load_manifest(d,check="recipe")
    configure(m["environment"])
    # Search history may be replayed after a controller revision. Compilation inputs must
    # still match exactly; search-version equality is unnecessary to gate immutable output.
    def gate_arm(mode):
        source = d / "gate_src" / mode
        if not source.exists(): shutil.copytree(ROOT / "src", source)
        changed = []
        for x in m["rows"]:
            row = x["row"]; p = result_path(d, mode, row["id"])
            if not p.exists(): raise RuntimeError("pilot search incomplete")
            r = json.loads(p.read_text())
            target = source / row["container"] / Path(row["c_path"]).name
            target.write_text((d / (r["candidate"] if r["outcome"] == "candidate" else x["input"])).read_text())
            if r["outcome"] == "candidate": changed.append(row)
        exp = "pin_" + a.tag + "_" + mode; build = ROOT / ("build_ovl_" + exp)
        with (d / ("gates_" + mode + ".log")).open("w") as log:
            subprocess.run(["bash", "tools/build/mk_ovl_root.sh"], cwd=ROOT, env=dict(os.environ, EXP=exp, SRCROOT=str(source)),
                           stdout=log, stderr=subprocess.STDOUT, check=True)
        names = sorted({w for row in changed if row["kind"] == "overlay" for w in windows_of(row)})
        def gate(name):
            cmd=["nice","-n10","python3","tools/overlay_local_gate.py","--config","config/overlays/"+name,"--clean"]
            p=subprocess.run(cmd,cwd=build,capture_output=True,text=True,timeout=3600)
            lines=(p.stdout+p.stderr).splitlines(); verdict=next((l for l in reversed(lines) if l.startswith(("MATCH", "NO MATCH"))), "ERROR")
            return dict(window=name, exact=p.returncode==0 and verdict.startswith("MATCH"), detail=verdict, returncode=p.returncode)
        results=[]
        with concurrent.futures.ThreadPoolExecutor(max_workers=max(1,a.workers//len(m["modes"]))) as pool:
            for f in concurrent.futures.as_completed([pool.submit(gate,w) for w in names]):
                r=f.result(); results.append(r); print(mode,r,flush=True)
        receipt=dict(run_key=m["run_key"], mode=mode, overlay=results, at=utc(),
                     candidates={r["id"]:json.loads(result_path(d,mode,r["id"]).read_text())["candidate_sha"] for r in changed})
        # SLUS candidates need the independent full-image gate, not only per-TU scoring.
        if any(r["kind"]=="slus" for r in changed):
            receipt["slus"]=gate_slus_copy(source,d/("build_slus_"+mode),d/("slus_"+mode+".log"),a.workers)
        atomic_json(d / ("gated_"+mode+".json"),receipt)
        if not all(x["exact"] for x in results): raise RuntimeError("pilot window gate failed")
    with concurrent.futures.ThreadPoolExecutor(max_workers=len(m["modes"])) as pool:
        for future in concurrent.futures.as_completed([pool.submit(gate_arm,mode) for mode in m["modes"]]):
            future.result()

def publish(a):
    from pin_census import landing_refusal
    from pin_search_engine import improvement_policy
    from verify import verify
    # Historical search output can be independently verified after search-code changes.
    # The frozen manifest, result identities and actual compilation recipe must still match.
    d=safe_tag(a.tag); m=load_manifest(d,check="recipe"); mode=a.mode
    if len(m["modes"])>1: raise RuntimeError("pilot is comparison-only; prepare a production tag for current sources")
    tx=d/"publication.json"
    if tx.exists():
        state=json.loads(tx.read_text())
        if state["phase"]=="complete": record_publication(state,m);print("already published"); return
        # Recover the exact interrupted transaction, refusing to overwrite any other edit.
        restore_publication(state["files"],ROOT,d)
        state["phase"]="rolled-back";atomic_json(tx,state)
    accepted,deferred=publication_results(d,m,mode,getattr(a,"defer",[]) or [])
    files=[]
    policy = improvement_policy(m["options"])
    for x,r in accepted:
        if r["outcome"]!="candidate": continue
        row=x["row"]; source=clean_path(row); cand=d/r["candidate"]
        if sha_file(source)!=x["source_sha"] or sha_file(cand)!=r["candidate_sha"]: raise RuntimeError("stale source or candidate: "+row["id"])
        before=source.read_text(); text=cand.read_text()
        bad=landing_refusal(text,before,str(source.relative_to(ROOT)))
        if bad or not policy(before,text): raise RuntimeError("candidate policy failure: "+str(bad))
        with tempfile.TemporaryDirectory(prefix="pin_final_") as tmp:
            p=Path(tmp)/Path(row["c_path"]).name;p.write_text(text)
            v=verify(row,p,include_root=ROOT/"include")
        if not v.get("exact"): raise RuntimeError("candidate no longer exact: "+row["id"])
        backup="backups/"+row["id"].replace("/","_")+".c"; atomic_text(d/backup,before)
        files.append(dict(id=row["id"],path=str(source.relative_to(ROOT)),before_sha=sha_text(before),after_sha=sha_text(text),backup=backup,candidate=r["candidate"]))
    state=dict(phase="publishing",files=files,deferred=deferred,run_key=m["run_key"],at=utc());atomic_json(tx,state)
    try:
        for x in files:
            if sha_file(ROOT/x["path"])!=x["before_sha"]:raise RuntimeError("source changed during verification")
        for x in files: atomic_text(ROOT/x["path"],(d/x["candidate"]).read_text())
        with (d/"publication.log").open("a") as log:
            for cmd in (["bash","tools/build/mk_ovl_root.sh"],["python3","tools/build/gate_all.py","--workers",str(a.workers)],
                        ["bash","tools/build/build_slus.sh","-j",str(a.workers)]):
                subprocess.run(cmd,cwd=ROOT,stdout=log,stderr=subprocess.STDOUT,check=True)
    except BaseException:
        restore_publication(files,ROOT,d)
        state["phase"]="rolled-back";atomic_json(tx,state);raise
    state["phase"]="complete";state["finished"]=utc();atomic_json(tx,state)
    record_publication(state,m)
    print(f"published {len(files)} functions; overlay and SLUS gates MATCH; {len(deferred)} search rows deferred")

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument("action",choices=["prepare","run","start","status","packets","gate-pilot","publish"])
    ap.add_argument("--tag",required=True);ap.add_argument("--workers",type=int,default=4)
    ap.add_argument("--sample",type=int,default=0);ap.add_argument("--seed",type=int,default=20260912)
    ap.add_argument("--pilot",action="store_true");ap.add_argument("--ids");ap.add_argument("--mode",choices=["targeted","baseline","fences","erasures"],default="baseline")
    ap.add_argument("--screens",type=int,default=1200);ap.add_argument("--verifies",type=int,default=12);ap.add_argument("--cpu-seconds",type=float,default=40)
    ap.add_argument("--fallback",type=int,default=2,choices=range(0,3),help="near-screen full-verifier allowance per row")
    ap.add_argument("--families-only",action="store_true",help="erasures: full set, variable groups and macro families only")
    ap.add_argument("--replay-commit",default="c35efafb")
    ap.add_argument("--defer",action="append",default=[],metavar="ROW_ID",
                    help="publish only: explicitly leave this retryable search error unresolved (repeatable)")
    a=ap.parse_args(); d=safe_tag(a.tag)
    if a.action=="packets":packets(a);return
    if a.action=="status":
        m=load_manifest(d,check=False);summarize(d,m)
        if (d/"state.json").exists():
            s=json.loads((d/"state.json").read_text());identity=process_identity(s.get("pid",0))
            s["process_running"]=bool(identity and identity==s.get("process_identity"))
            if s.get("phase")=="searching" and not s["process_running"]:s["observed_phase"]="interrupted"
            print(json.dumps(s,indent=2))
        return
    if a.action=="start":
        load_manifest(d)
        # Fail synchronously if another controller owns the workspace.
        with ownership(): pass
        with (d/"controller.log").open("a") as log:
            p=subprocess.Popen(["nice","-n10",sys.executable,str(Path(__file__).resolve()),"run","--tag",a.tag,"--workers",str(a.workers)],
                               cwd=ROOT,stdin=subprocess.DEVNULL,stdout=log,stderr=subprocess.STDOUT,start_new_session=True)
        print(f"detached pid {p.pid}; log {d/'controller.log'}");return
    with ownership():
        if a.action=="prepare": prepare(a)
        elif a.action=="run": run(a)
        elif a.action=="gate-pilot": gate_pilot(a)
        elif a.action=="publish": publish(a)

if __name__=="__main__": main()
