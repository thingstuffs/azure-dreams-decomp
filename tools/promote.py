#!/usr/bin/env python3
"""Land accepted Layer-2 bodies into src/ — the only tree the gates compile — and journal it.

    python3 tools/promote.py [--dry-run] [--workers 6] [--only id,id] [--source refine|agents:<model-effort>]

Why: the campaign used to write accepted bodies to refine/ while every proof (window gates, SLUS gate,
reverify), every sweep (T1..T10) and every level measurement read src/.  A body that is not in src/ is not
in the product.  This tool verifies each body byte-exact through tools/verify.py (with the include root,
as the sweeps do), writes src/, and then runs the row's WINDOW GATE (tools/gate/overlay_local_gate.py over
the window that holds the row): the per-row scorer links every row at its true base, while the gate links a
row with no recorded true name at its synthetic address (the legacy population), so a body whose internal
jumps changed spelling can be scorer-exact and still wrong in the window (2026-09-08: 10 dungeon windows).
A body that fails the gate is reverted and journalled `gate-mismatch`; only `landed` counts.  It writes src/; ledger/promotions.jsonl is the record the level metric reads (L3 =
landed).  Legacy `/* MATCH pin: ... */` notes are dropped first so the T6 sweep re-annotates every pin
with the current wording.  After a run, re-run the standing sweeps so the machine layers reach the
promoted text, then the gates:
    for t in t6_pin_notes t7_headers t2_pins t8_passthru t10_epilogue t9_regpins; do python3 tools/sweep.py $t; done
    python3 tools/build/gate_all.py && tools/build/build_slus.sh && python3 tools/reverify.py 6 && python3 tools/levels.py && python3 tools/status.py
"""
import argparse, os, re, subprocess, sys, tempfile, threading, time
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, NICE, rows, read_jsonl, append_jsonl, sha_text, clean_path, raw_path, covering_windows
from verify import verify, gate_root, window_lock, run_window_gate

def gate(yaml_name, locked=False):
    """The window gate over src/ for one window YAML, uncached; the caller holds the window lock
    (verify.window_lock: cross-process, shared with the lane's `verify.py --gate` and the sweeps)."""
    if locked: return run_window_gate(yaml_name)
    with window_lock(yaml_name): return run_window_gate(yaml_name)

def needs_gate(row):
    """The per-row scorer links every row at its true base; the window gate links a row WITHOUT a recorded true name at its
    synthetic address (the legacy population). Only that class can be scorer-exact and wrong in the window (all 13 mismatches
    of 2026-09-08 were such rows), so only that class pays for a window gate at landing; a whole-overlay window such as
    town_scene recompiles every row it holds and takes minutes."""
    return row["kind"] == "overlay" and not row.get("true_name")

def windows_of(row):
    """Every window whose range holds the row (the gate compiles all rows in a range, named or not)."""
    names = {Path(row["gate_config"]).name} if row.get("gate_config") and row["kind"] == "overlay" else set()
    if row.get("foff") is not None:
        for w in covering_windows(row["container"], row["foff"], row["size"]):
            names.add(Path(w[0]).name if not str(w[0]).endswith(".yaml") else Path(w[0]).name)
    return sorted(n for n in names if n.endswith(".yaml"))

INCLUDE = ROOT / "include"
JOURNAL = LEDGER / "promotions.jsonl"
OLD_NOTE = re.compile(r"[ \t]*/\*\s*MATCH pin:([^*]*)\*/")
# legacy wording (2026-09-07 lanes) -> the T6 breakage class (tools/xform/t6_pin_notes.py NOTE)
LEGACY = [("whole function shape", "broad"), ("same instructions, different order", "reorder-only"), ("register colouring", "reg-rename"),
          ("moving across", "code-motion"), ("address form", "addressing"), ("otherwise drop/add", "length-drift"),
          ("constant in a register", "const-remat"), ("frame layout", "hold-set"), ("delay-slot fill", "slot-rotation"),
          ("delay-slot contents", "delay-slot"), ("immediate-load split", "li-expansion"), ("basic-block layout", "block-order"),
          ("computation the compiler would drop", "dead-code-retention"), ("branch polarity", "polarity"),
          ("slus-", "slus-object")]
NOTE_TEXT = dict(__import__("xform.t6_pin_notes", fromlist=["NOTE"]).NOTE, **{"slus-object": "changes the compiled object of the TU"})
PREFIX, SUFFIX = __import__("xform.t6_pin_notes", fromlist=["PREFIX"]).PREFIX, __import__("xform.t6_pin_notes", fromlist=["SUFFIX"]).SUFFIX

def normalise(text):
    """Rewrite the legacy `/* MATCH pin: ... */` notes into the current debt-record wording (comment-only);
    an unrecognised legacy note is dropped so the T6 sweep re-annotates the pin from its verdict."""
    def sub(m):
        body = m.group(1).lower()
        for key, cls in LEGACY:
            if key in body:
                return f"   /* {PREFIX} {NOTE_TEXT[cls]}{SUFFIX} */"
        return ""
    return OLD_NOTE.sub(sub, text)

def body_for(row, source):
    name = Path(row["c_path"]).name
    if source == "refine":
        p = ROOT / "refine" / row["container"] / name
    else:
        p = LEDGER / "agents" / "out" / source.split(":", 1)[1] / row["container"] / name
    return p if p.exists() else None

def promote_text(row, text, source, dry_run=False):
    """Verify `text` for `row`; write src/ when exact. Returns the journal record."""
    text = normalise(text)
    cp = clean_path(row)
    before = cp.read_text(errors="replace") if cp.exists() else raw_path(row).read_text(errors="replace")
    rec = {"id": row["id"], "source": source, "body_sha": sha_text(text), "src_before_sha": sha_text(before), "size": row["size"],
           "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}
    if text == before:
        return dict(rec, outcome="noop", out_sha=sha_text(text))
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / cp.name; p.write_text(text)
        v = verify(row, p, include_root=INCLUDE)
    rec.update({"exact": v.get("exact"), "status": v.get("status"), "class": v.get("class"), "total": v.get("total"), "secs": v.get("secs"),
                "err": (v.get("err") or "").replace(str(ROOT), "<repo>").replace(str(Path.home()), "<home>")[-300:] or None})
    if not v.get("exact"):
        return dict(rec, outcome="mismatch" if v.get("status") == "ok" else "build-failed")
    if dry_run:
        return dict(rec, outcome="would-land", out_sha=sha_text(text))
    wins = windows_of(row) if needs_gate(row) else []
    if row["kind"] == "overlay" and not wins: rec["gate"] = "not needed: row linked at its true name (scorer and gate agree)"
    # hold every window the row sits in for write + gate + (revert): a concurrent landing in the same
    # window must not be visible to this row's gate, or a bad neighbour would fail this row (and vice versa)
    locks = [window_lock(w) for w in wins]
    for l in locks: l.__enter__()
    try:
        cp.parent.mkdir(parents=True, exist_ok=True); cp.write_text(text)
        for w in wins:
            res, detail = gate(w, locked=True)
            if res != "MATCH":
                cp.write_text(before)   # revert: the window is the proof of record
                return dict(rec, outcome="gate-mismatch", gate=res, window=w, detail=detail[:200])
    finally:
        for l in reversed(locks): l.__exit__(None, None, None)
    if wins: rec["gate"] = "MATCH"; rec["windows"] = wins
    return dict(rec, outcome="landed", out_sha=sha_text(text))

def latest():
    """Latest promotion record per row (a later revert or re-landing supersedes)."""
    out = {}
    if JOURNAL.exists():
        for j in read_jsonl(JOURNAL): out[j["id"]] = j
    return out

def landed_ids():
    return {i for i, j in latest().items() if j.get("outcome") == "landed"}

def repair(window_names, source, workers):
    """Windows that failed gate_all after a promotion: revert every landed row inside them to the committed
    text (journal `reverted`), then re-promote each from `source` with the gate in the loop."""
    sys.path.insert(0, str(ROOT / "tools" / "build")); import gate_all
    land = landed_ids(); todo = []
    for w in window_names:
        y = w if w.endswith(".yaml") else f"{w}.overlay.yaml"
        for r in gate_all.window_rows().get(y, []):
            if r["id"] in land and r not in todo: todo.append(r)
    print(f"repair {len(window_names)} windows: {len(todo)} landed rows to revert and re-promote", flush=True)
    for r in todo:
        cp = clean_path(r); rel = str(cp.relative_to(ROOT))
        subprocess.run(["git", "checkout", "HEAD", "--", rel], cwd=ROOT, check=True)
        append_jsonl(JOURNAL, {"id": r["id"], "outcome": "reverted", "reason": "window gate NO MATCH after promotion", "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())})
    return todo

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true"); ap.add_argument("--workers", type=int, default=6)
    ap.add_argument("--only"); ap.add_argument("--source", default="refine"); ap.add_argument("--limit", type=int)
    ap.add_argument("--repair-windows", help="comma list of window stems that failed the gate: revert + re-promote their landed rows")
    a = ap.parse_args()
    if a.repair_windows:
        todo = repair(a.repair_windows.split(","), a.source, a.workers)
        a.only = ",".join(r["id"] for r in todo) or "-"
    rs = [r for r in rows() if r["exists"] and r["stock"]]
    if a.only: keep = set(a.only.split(",")); rs = [r for r in rs if r["id"] in keep]
    jobs = []
    for r in rs:
        p = body_for(r, a.source)
        if p: jobs.append((r, p))
    if a.limit: jobs = jobs[:a.limit]
    print(f"{len(jobs)} bodies from {a.source}; {'dry run' if a.dry_run else 'landing into src/'}", flush=True)
    tally = {}
    def work(job):
        r, p = job
        try:
            return promote_text(r, p.read_text(errors="replace"), a.source, a.dry_run)
        except Exception as e:
            return {"id": r["id"], "source": a.source, "outcome": "error", "err": repr(e)[:200]}
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for i, rec in enumerate(ex.map(work, jobs), 1):
            if not a.dry_run: append_jsonl(JOURNAL, rec)
            tally[rec["outcome"]] = tally.get(rec["outcome"], 0) + 1
            if rec["outcome"] not in ("landed", "would-land", "noop"): print(rec["id"], rec["outcome"], (rec.get("err") or "")[:120], flush=True)
            if i % 250 == 0: print(f"  {i}/{len(jobs)} {tally}", flush=True)
    print(tally)

if __name__ == "__main__":
    main()
