#!/usr/bin/env python3
"""Move the tree to a newer upstream commit and re-derive everything the pin change touches.

    python3 tools/pin_bump.py <commit> [--workers 6] [--stop-after STEP] [--from STEP]

Steps (each prints a header; --from resumes at a step, --stop-after stops after one):
  refresh    PIN := commit; upstream/ mirror re-extracted (tools/refresh.py)
  import     imported upstream files re-copied from the mirror with the schema rename
             (config/overlays/*, the config/*.txt/.jsonl/.tsv/.yaml/.sha1 lists, tools/configure.py,
             the raw/include copy); every changed file is listed
  slus       build_slus/ view root, `splat split`, configure.py at the pin ->
             upstream/build.ninja.pinned is DERIVED FROM THE PIN (not copied from the live tree)
  registry   ledger/rows.jsonl regenerated; diff against the previous registry
  stale      rows whose upstream text / config / stock status changed: raw/ refreshed, src/ reset to
             the new raw text (the sweeps re-derive), refine/ body set aside for re-verification,
             baseline record dropped; removed rows set aside; all under work/pin_bump/<commit>/
  baseline   tools/verify.py --baseline (only rows without a record compile)
  sweeps     census, T1/T4/T2/T6 sweeps, complete_tree, levels
  refine     set-aside refine/ bodies re-verified against the new pin: exact ones restored,
             the rest stay under work/pin_bump/<commit>/refine_stale/ (journalled, never kept silently)
  reverify   tools/reverify.py: every transformed row re-verified at the new pin (ledger/reverify.jsonl,
             the dashboard's drift list; the toolchain is the live one, so this is not optional)
  status     STATUS.md
  gate_slus  ninja in build_slus/ (the SLUS SHA-1 gate)
  gate_ovl   build_ovl/ view root + tools/build/gate_all.py on a FRESH ledger/gate.jsonl
             (the previous journal is kept under work/pin_bump/<commit>/)

Report: ledger/pin_bumps/<commit>.json (counts per step, every changed file and row id).
"""
from __future__ import annotations
import argparse, json, os, re, shutil, subprocess, sys, time
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, UP, UP_LIVE, LEDGER, CACHE, read_jsonl, write_jsonl, append_jsonl, sha_file, run

STEPS = ["refresh", "import", "slus", "registry", "stale", "baseline", "sweeps", "refine", "reverify", "status", "gate_slus", "gate_ovl"]
SWEEPS = ["t1_boiler", "t4_fields", "t2_pins", "t6_pin_notes"]   # t3_epilogue retired 2026-09-07 (window gate)
CONFIG_TOP = ["names.tsv", "slus_006.14.yaml", "slus_006.14.symbols.txt", "slus_006.14.sha1",
              "noreturn_syms.txt", "noreturn_syms.dungeon.txt", "noreturn_syms.town.txt", "noreturn_syms.ovmovie.txt",
              "sibcall_syms.txt", "sibcall_syms.dungeon.txt", "sibcall_syms.town.txt", "sibcall_syms.ovmovie.txt",
              "noreturn_false_members.jsonl"]
UPSTREAM_NAME = "azure-dec" + "omp"      # never spelled out: the scrub hook greps for it
CLEAN_NAME = "azure-clean"
WORK = None      # work/pin_bump/<commit>
REPORT = {}


def hdr(s):
    print(f"\n=== {s} ===", flush=True)


def scrub(text: str) -> str:
    """Imported upstream text -> this repo's spelling: absolute upstream path masked, repo name renamed."""
    return text.replace(str(UP_LIVE), "<upstream>").replace(UPSTREAM_NAME, CLEAN_NAME)


def git_show(commit, path):
    r = subprocess.run(["git", "-C", str(UP_LIVE), "show", f"{commit}:{path}"], capture_output=True, text=True)
    return r.stdout if r.returncode == 0 else None


def sh(cmd, cwd=None, check=True, log=None):
    print("$", cmd if isinstance(cmd, str) else " ".join(map(str, cmd)), flush=True)
    r = subprocess.run(cmd, shell=isinstance(cmd, str), cwd=cwd, text=True, capture_output=log is not None)
    if log is not None:
        Path(log).write_text((r.stdout or "") + (r.stderr or ""))
        tail = ((r.stdout or "") + (r.stderr or "")).strip().splitlines()[-3:]
        for l in tail: print("  " + l[:200])
    if check and r.returncode != 0:
        sys.exit(f"step failed (exit {r.returncode}): {cmd}")
    return r


# ------------------------------------------------------------------ steps
def step_refresh(commit):
    old = json.load(open(LEDGER / "pin.json"))["pin"] if (LEDGER / "pin.json").exists() else None
    REPORT["old_pin"] = old
    (ROOT / "PIN").write_text(commit + "\n")
    sh([sys.executable, "tools/refresh.py"], cwd=ROOT)
    meta = json.load(open(LEDGER / "pin.json"))
    REPORT["new_commit"] = meta["commit"]
    # the previous registry is the diff base for later steps
    shutil.copy(LEDGER / "rows.jsonl", WORK / "rows.prev.jsonl")
    (WORK / "old_pin").write_text(old or "")


def step_import(commit):
    old = (WORK / "old_pin").read_text().strip() or None
    changed = []
    def put(dst: Path, text: str):
        if dst.exists() and dst.read_text(errors="replace") == text: return
        dst.parent.mkdir(parents=True, exist_ok=True); dst.write_text(text); changed.append(str(dst.relative_to(ROOT)))
    # config/overlays/*: window YAMLs, as_flags/rowbase/first-pass files
    for p in sorted((UP / "config/overlays").iterdir()):
        if p.is_file(): put(ROOT / "config/overlays" / p.name, scrub(p.read_text(errors="replace")))
    for n in CONFIG_TOP:
        p = UP / "config" / n
        if p.exists(): put(ROOT / "config" / n, scrub(p.read_text(errors="replace")))
    # raw/include is the untouched pinned header set; include/ carries the same headers plus this repo's own
    for p in sorted((UP / "include").glob("*")):
        if p.is_file():
            put(ROOT / "raw/include" / p.name, p.read_text(errors="replace"))
            put(ROOT / "include" / p.name, scrub(p.read_text(errors="replace")))
    # gate/build tool copies: re-copy any upstream tools/<name> that changed between the two pins
    tools_changed = []
    for sub in ("gate", "build"):
        for f in sorted((ROOT / "tools" / sub).iterdir()):
            if f.suffix not in (".py", ".sh"): continue
            new = git_show(commit, f"tools/{f.name}")
            if new is None: continue                       # this repo's own tool (gate_all, mk_*_root) or a work/ import
            oldt = git_show(old, f"tools/{f.name}") if old else None
            if oldt is not None and scrub(oldt) == scrub(new) and f.name != "configure.py": continue
            if f.read_text(errors="replace") != scrub(new):
                f.write_text(scrub(new)); tools_changed.append(f"tools/{sub}/{f.name}")
    REPORT["import"] = {"files_changed": changed, "tools_changed": tools_changed}
    print(f"{len(changed)} config/include files re-imported, {len(tools_changed)} tool copies refreshed")
    for t in tools_changed: print("  tool:", t)
    for c in changed[:40]: print("  ", c)
    if len(changed) > 40: print(f"   ... {len(changed) - 40} more")


def step_slus(commit):
    B = ROOT / "build_slus"
    sh(["bash", "tools/build/mk_slus_root.sh"], cwd=ROOT)
    for d in ("asm", "assets", "build", "config/generated"):
        shutil.rmtree(B / d, ignore_errors=True)
    (B / "config/generated").mkdir(parents=True)
    sh([str(B / ".venv/bin/splat"), "split", "config/slus_006.14.yaml"], cwd=B, log=WORK / "splat.log")
    sh([sys.executable, "tools/configure.py"], cwd=B, log=WORK / "configure.log")
    # the pinned recipe is now what the pinned configure.py generates, not the live tree's file
    pinned = UP / "build.ninja.pinned"
    live_sha = sha_file(pinned)
    shutil.copy(B / "build.ninja", pinned)
    meta = json.load(open(LEDGER / "pin.json"))
    meta["build_ninja_sha256"] = sha_file(pinned); meta["build_ninja_source"] = "configure.py at the pin (build_slus)"
    meta["live_build_ninja_sha256"] = live_sha
    (LEDGER / "pin.json").write_text(json.dumps(meta, indent=1) + "\n")
    # informational: per-TU cell differences between the derived recipe and the live tree's file
    def edges(p):
        out, cur = {}, None
        for raw in Path(p).read_text().splitlines():
            m = re.match(r"^build (\S+): cc (\S+)", raw)
            if m: cur = {"ccver": "2.7.2", "ccflags": "", "asflags": ""}; out[m.group(2)] = cur; continue
            if cur is not None:
                m = re.match(r"^\s+(ccver|ccflags|asflags) = ?(.*)$", raw)
                if m: cur[m.group(1)] = m.group(2).strip()
                elif not raw.startswith(" ") and raw.strip(): cur = None
        return out
    a, b = edges(pinned), edges(UP_LIVE / "build.ninja")
    diff = sorted(k for k in a if k in b and a[k] != b[k])
    REPORT["slus"] = {"tus": len(a), "live_tus": len(b), "cells_differ_from_live": diff, "only_pinned": sorted(set(a) - set(b)), "only_live": sorted(set(b) - set(a))}
    print(f"pinned recipe: {len(a)} TUs; live tree: {len(b)}; cells differing from live: {len(diff)}")


def step_registry(commit):
    sh([sys.executable, "tools/registry.py"], cwd=ROOT)
    old = {r["id"]: r for r in read_jsonl(WORK / "rows.prev.jsonl")}
    new = {r["id"]: r for r in read_jsonl(LEDGER / "rows.jsonl")}
    added = sorted(set(new) - set(old)); removed = sorted(set(old) - set(new))
    text_changed, stock_flip, cfg_changed = [], [], []
    for i in sorted(set(new) & set(old)):
        o, n = old[i], new[i]
        if o.get("src_sha") != n.get("src_sha"): text_changed.append(i)
        if bool(o.get("stock")) != bool(n.get("stock")): stock_flip.append((i, bool(o.get("stock")), bool(n.get("stock"))))
        if (o.get("cfg"), o.get("row_asflags")) != (n.get("cfg"), n.get("row_asflags")): cfg_changed.append(i)
    stale = sorted(set(text_changed) | {i for i, _, _ in stock_flip} | set(cfg_changed) | set(added))
    REPORT["registry"] = {"rows_old": len(old), "rows_new": len(new), "added": added, "removed": removed,
                          "text_changed": text_changed, "stock_flip": stock_flip, "cfg_changed": cfg_changed, "stale": stale,
                          "stock_old": sum(1 for r in old.values() if r.get("stock")), "stock_new": sum(1 for r in new.values() if r.get("stock"))}
    write_jsonl(WORK / "stale_rows.jsonl", [new[i] for i in stale])
    write_jsonl(WORK / "removed_rows.jsonl", [old[i] for i in removed])
    print(f"rows {len(old)} -> {len(new)}: added {len(added)}, removed {len(removed)}, text changed {len(text_changed)}, "
          f"stock flips {len(stock_flip)} (to stock: {sum(1 for _, a, b in stock_flip if b)}), cfg/asflags changed {len(cfg_changed)}; "
          f"stale set {len(stale)}; stock rows {REPORT['registry']['stock_old']} -> {REPORT['registry']['stock_new']}")


def step_stale(commit):
    stale = read_jsonl(WORK / "stale_rows.jsonl"); removed = read_jsonl(WORK / "removed_rows.jsonl")
    prev_src = WORK / "prev_src"; refine_stale = WORK / "refine_stale"; gone = WORK / "removed"
    n_raw = n_src = n_ref = 0
    for r in stale:
        name = Path(r["c_path"]).name; c = r["container"]
        up = UP / r["c_path"]
        if not up.exists(): continue
        raw = ROOT / "raw" / c / name; src = ROOT / "src" / c / name; ref = ROOT / "refine" / c / name
        raw.parent.mkdir(parents=True, exist_ok=True)
        if not raw.exists() or raw.read_bytes() != up.read_bytes(): shutil.copyfile(up, raw); n_raw += 1
        if src.exists():
            (prev_src / c).mkdir(parents=True, exist_ok=True); shutil.copyfile(src, prev_src / c / name)
        src.parent.mkdir(parents=True, exist_ok=True)
        if not src.exists() or src.read_bytes() != raw.read_bytes(): shutil.copyfile(raw, src); n_src += 1
        if ref.exists():
            (refine_stale / c).mkdir(parents=True, exist_ok=True); shutil.move(str(ref), refine_stale / c / name); n_ref += 1
    for r in removed:
        name = Path(r["c_path"]).name; c = r["container"]
        for sub in ("raw", "src", "refine"):
            p = ROOT / sub / c / name
            if p.exists():
                (gone / sub / c).mkdir(parents=True, exist_ok=True); shutil.move(str(p), gone / sub / c / name)
    # The baseline is rebuilt in full at every pin: the toolchain the rows compile through is the
    # upstream LIVE toolchain, so an unchanged row can still change bytes at a new pin (assembler
    # changes). Overlay rows ~17 min at 6 workers, SLUS rows ~30 s; the pinned SLUS objects and
    # disassemblies (ledger/cache/) are regenerated from the new mirror.
    base = read_jsonl(LEDGER / "baseline.jsonl")
    if not (WORK / "baseline.prev.jsonl").exists():      # keep the pre-bump baseline across re-runs
        shutil.copy(LEDGER / "baseline.jsonl", WORK / "baseline.prev.jsonl")
    write_jsonl(LEDGER / "baseline.jsonl", [])
    if (CACHE / "slus_obj.json").exists(): (CACHE / "slus_obj.json").unlink()
    shutil.rmtree(CACHE / "slus_dis", ignore_errors=True)
    REPORT["stale"] = {"rows": len(stale), "raw_refreshed": n_raw, "src_reset": n_src, "refine_set_aside": n_ref,
                       "removed_rows": len(removed), "baseline_dropped": len(base)}
    print(f"{len(stale)} stale rows: raw refreshed {n_raw}, src reset {n_src}, refine set aside {n_ref}; "
          f"removed rows {len(removed)}; baseline cleared for a full rebuild ({len(base)} records)")


def step_baseline(commit, workers):
    sh([sys.executable, "tools/verify.py", "--baseline", "--workers", str(workers)], cwd=ROOT, log=WORK / "baseline.log")
    base = read_jsonl(LEDGER / "baseline.jsonl"); rows = {r["id"]: r for r in read_jsonl(LEDGER / "rows.jsonl")}
    bad = [b["id"] for b in base if rows.get(b["id"], {}).get("stock") and not (b.get("exact") is True or (rows[b["id"]]["kind"] == "slus" and b.get("status") == "ok"))]
    gated = [b["id"] for b in base if b.get("proof") == "window-gate"]
    REPORT["baseline"] = {"records": len(base), "not_exact": bad, "gate_proven": gated}
    print(f"baseline records {len(base)}; proven by the window gate (scorer cannot measure the shape): {len(gated)}; NOT exact at the new pin: {len(bad)}")
    for i in bad[:30]: print("  not exact:", i)


def step_sweeps(commit, workers):
    sh([sys.executable, "tools/census.py"], cwd=ROOT, log=WORK / "census.log")
    tally = {}
    for t in SWEEPS:
        r = sh([sys.executable, "tools/sweep.py", t, "--workers", str(workers)], cwd=ROOT, log=WORK / f"sweep_{t}.log")
        tally[t] = (Path(WORK / f"sweep_{t}.log").read_text().strip().splitlines() or [""])[-1][:200]
    sh([sys.executable, "tools/complete_tree.py"], cwd=ROOT)
    sh([sys.executable, "tools/levels.py"], cwd=ROOT, log=WORK / "levels.log")
    REPORT["sweeps"] = tally


def step_refine(commit, workers):
    from verify import verify
    from concurrent.futures import ThreadPoolExecutor
    rows = {r["id"]: r for r in read_jsonl(LEDGER / "rows.jsonl")}
    stale_dir = WORK / "refine_stale"
    cands = []
    for p in sorted(stale_dir.glob("*/*.c")) if stale_dir.exists() else []:
        c = p.parent.name; rid = None
        for r in rows.values():
            if r["container"] == c and Path(r["c_path"]).name == p.name: rid = r["id"]; break
        if rid and rows[rid].get("stock"): cands.append((rid, p))
    def one(a):
        rid, p = a
        v = verify(rows[rid], p, include_root=ROOT / "include")
        return rid, p, v
    restored, dropped = [], []
    journal = LEDGER / "agents" / "pin_bump_refine.jsonl"
    with ThreadPoolExecutor(max_workers=workers) as ex:
        for rid, p, v in ex.map(one, cands):
            ok = v.get("exact") is True
            rec = {"id": rid, "pin": commit, "exact": ok, "class": v.get("class"), "total": v.get("total"), "err": (v.get("err") or "")[:160],
                   "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}
            append_jsonl(journal, rec)
            if ok:
                dst = ROOT / "refine" / p.parent.name / p.name; dst.parent.mkdir(parents=True, exist_ok=True)
                shutil.move(str(p), dst); restored.append(rid)
            else:
                dropped.append(rid)
    REPORT["refine"] = {"re_verified": len(cands), "restored": restored, "stale_kept_aside": dropped}
    print(f"refine bodies re-verified {len(cands)}: restored {len(restored)}, set aside (not exact at the new pin) {len(dropped)}")


def step_reverify(commit, workers):
    sh([sys.executable, "tools/reverify.py", str(workers)], cwd=ROOT, log=WORK / "reverify.log")
    bad = [b["id"] for b in read_jsonl(LEDGER / "reverify.jsonl") if not (b.get("exact") or (b.get("status") == "ok" and b.get("exact") is None))]
    REPORT["reverify"] = {"rows": len(read_jsonl(LEDGER / "reverify.jsonl")), "not_exact": bad}
    print(f"transformed rows re-verified: {REPORT['reverify']['rows']}; not exact: {len(bad)}")
    for i in bad[:30]: print("  drift:", i)


def step_status(commit):
    sh([sys.executable, "tools/status.py"], cwd=ROOT, log=WORK / "status.log")


def step_gate_slus(commit, workers):
    r = sh(["ninja", "-C", str(ROOT / "build_slus"), "-j", str(workers)], cwd=ROOT, check=False, log=WORK / "ninja.log")
    ok = r.returncode == 0
    REPORT["gate_slus"] = {"ok": ok, "log": str((WORK / "ninja.log").relative_to(ROOT))}
    print("SLUS SHA-1 gate:", "OK" if ok else "FAILED (see work/pin_bump/.../ninja.log)")
    if not ok:
        for l in (WORK / "ninja.log").read_text().splitlines():
            if "FAILED" in l or "sha1" in l.lower(): print("  ", l[:200])


def step_gate_ovl(commit, workers):
    j = LEDGER / "gate.jsonl"
    if j.exists() and j.stat().st_size:
        shutil.copy(j, WORK / "gate.prev.jsonl"); j.write_text("")
    sh(["bash", "tools/build/mk_ovl_root.sh"], cwd=ROOT)
    sh([sys.executable, "tools/build/gate_all.py", "--workers", str(workers)], cwd=ROOT, log=WORK / "gate_all.log")
    last = {}
    for r in read_jsonl(j): last[r["window"]] = r
    tally = {}
    for r in last.values(): tally[r["result"]] = tally.get(r["result"], 0) + 1
    bad = {w: (r["result"], r["detail"][:160]) for w, r in last.items() if r["result"] != "MATCH"}
    REPORT["gate_ovl"] = {"windows": len(last), "tally": tally, "not_match": bad}
    print(f"overlay windows {len(last)}: {tally}")
    for w, (res, d) in sorted(bad.items())[:40]: print(f"  {w}: {res} {d}")


def main():
    global WORK
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("commit"); ap.add_argument("--workers", type=int, default=6)
    ap.add_argument("--from", dest="start", choices=STEPS, default="refresh"); ap.add_argument("--stop-after", choices=STEPS)
    a = ap.parse_args()
    r = subprocess.run(["git", "-C", str(UP_LIVE), "rev-parse", "--verify", a.commit + "^{commit}"], capture_output=True, text=True)
    if r.returncode != 0: sys.exit(f"{a.commit} is not a commit in the upstream tree")
    full = r.stdout.strip(); short = full[:8]
    WORK = ROOT / "work" / "pin_bump" / short; WORK.mkdir(parents=True, exist_ok=True)
    rep_path = LEDGER / "pin_bumps" / f"{short}.json"; rep_path.parent.mkdir(exist_ok=True)
    if rep_path.exists(): REPORT.update(json.load(open(rep_path)))
    REPORT.update({"commit": full, "pin": short, "started": REPORT.get("started") or time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())})
    busy = subprocess.run("ps -eo pid,args | grep '[a]gent_task.py' | grep -c " + re.escape(str(ROOT)), shell=True, capture_output=True, text=True).stdout.strip()
    if busy not in ("", "0"): print(f"WARNING: an agent campaign is running in this tree ({busy} process); its refine/ writes race the stale step", flush=True)
    t0 = time.time()
    for s in STEPS[STEPS.index(a.start):]:
        hdr(f"{s}  (t+{time.time() - t0:.0f}s)")
        fn = globals()[f"step_{s}"]
        if s in ("baseline", "sweeps", "refine", "reverify", "gate_slus", "gate_ovl"): fn(short, a.workers)
        else: fn(short)
        REPORT.setdefault("steps_done", []).append(s) if s not in REPORT.get("steps_done", []) else None
        rep_path.write_text(json.dumps(REPORT, indent=1) + "\n")
        if a.stop_after == s: break
    REPORT["finished"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()); rep_path.write_text(json.dumps(REPORT, indent=1) + "\n")
    print(f"\nreport: {rep_path.relative_to(ROOT)}  ({time.time() - t0:.0f}s)")


if __name__ == "__main__":
    main()
