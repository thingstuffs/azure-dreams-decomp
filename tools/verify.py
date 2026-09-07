#!/usr/bin/env python3
"""Verify one candidate C file for one row, or build the whole baseline.

overlay rows : upstream tools/aligned_score.py against the retail slice (exact / aligned
               distance / residue class), through the live toolchain, compiled in a temp dir.
slus rows    : compile the TU through the same three-step pipeline cc.sh uses (gcc -S ->
               ccproc -> maspsx+as) with the MIRROR include root and compare the object hash
               with the pinned TU's object (bit-reproducible).  Upstream SLUS is byte-exact by
               its SHA-1 gate, so the pinned object is the reference.

    python3 tools/verify.py town/func_800A0284 cand.c [--regions]
    python3 tools/verify.py --baseline [--workers 6] [--container town] [--limit 50]
"""
import argparse, json, os, re, subprocess, sys, tempfile, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from common import ROOT, UP, UP_LIVE, LEDGER, CACHE, NICE, rows, read_jsonl, append_jsonl, sha_file

MASPSX = UP_LIVE / "toolchain/maspsx/maspsx.py"
VENV_PY = UP_LIVE / ".venv/bin/python"

def _env():
    env = dict(os.environ)
    env.pop("AZURE_MASPSX", None); env.pop("AZURE_MASPSX_COMPANION", None)
    return env

# ---------------------------------------------------------------- overlay rows
DEF_SYM = re.compile(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8})\s*\([^;{]*\)\s*\{", re.M)

def normalise_definition(row, cfile):
    """A few upstream rows define their function under a stale rowbase name (e.g. the true-space
    name before a base correction).  The scorer is keyed on the row symbol, and an identifier
    rename is byte-neutral, so score a copy whose definition carries the row symbol."""
    text = Path(cfile).read_text(errors="replace")
    defs = DEF_SYM.findall(text)
    if not defs or row["func"] in defs or (row.get("true_name") and row["true_name"] in defs):
        return cfile
    if len(set(defs)) != 1:
        return cfile
    other = defs[0]
    tmp = Path(tempfile.mkdtemp()) / Path(cfile).name
    tmp.write_text(re.sub(r"\b" + re.escape(other) + r"\b", row["func"], text))
    return tmp

def verify_overlay(row, cfile, regions=False, include_root=None):
    env = _env()
    # the include root is passed as a USER include directory (-I), exactly as the window gate's
    # cc.sh does; C_INCLUDE_PATH would make it a system header and GCC then tolerates
    # redefinitions the gate rejects
    cfg = row["cfg"] + (f" -I{Path(include_root).resolve()}" if include_root else "")
    cfile = normalise_definition(row, cfile)
    cmd = NICE + ["python3", str(UP_LIVE / "tools/aligned_score.py"), "--func", row["func"],
                  "--overlay", row["container"], "--configs", cfg]
    cmd += ["--regions", str(cfile)] if regions else ["--summary-json", str(cfile)]
    t0 = time.time()
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, timeout=900, cwd=UP_LIVE, env=env)
    except subprocess.TimeoutExpired:
        return {"status": "TIMEOUT", "exact": False, "secs": round(time.time() - t0, 2)}
    secs = round(time.time() - t0, 2)
    if regions:
        return {"status": "regions", "text": r.stdout, "secs": secs}
    rec = None
    for line in reversed(r.stdout.splitlines()):
        try: j = json.loads(line)
        except json.JSONDecodeError: continue
        if str(j.get("schema", "")).endswith("aligned-score.v1"): rec = j; break
    if rec is None:
        return {"status": "HARNESS-ERROR", "exact": False, "secs": secs, "err": (r.stderr or r.stdout)[-300:]}
    best = (rec["results"][0] or {}).get("best") or {}
    if not best:
        return {"status": "NO-BEST", "exact": False, "secs": secs, "err": json.dumps(rec["results"][0])[:300]}
    al = best.get("aligned") or {}; lw = best.get("length_words") or {}; rs = best.get("residue") or {}
    return {"status": best.get("build_status") or "ok", "exact": bool(best.get("exact")),
            "subs": al.get("substitutions"), "indels": al.get("indels"), "total": al.get("total"),
            "gen_words": lw.get("generated"), "tgt_words": lw.get("target"),
            "class": rs.get("class"), "signals": rs.get("signals"), "secs": secs,
            "err": (best.get("error") or None)}

# ---------------------------------------------------------------- slus rows
def compile_slus(row, cfile, outdir, include_root=None):
    inc = Path(include_root).resolve() if include_root else UP / "include"
    cc_dir = UP_LIVE / "toolchain/compilers" / f"gcc-{row['cell']}"
    s_path = Path(outdir) / "a.s"; o_path = Path(outdir) / "a.o"
    # compile from the source's own directory by basename: the ELF FILE symbol records the path
    # as given, and the object hash must not depend on where the candidate lives
    cfile = Path(cfile)
    gcc = [str(cc_dir / "gcc"), f"-B{cc_dir}/", "-S", "-O2"] + row["flags"].split() + ["-I", str(inc), "-w", cfile.name, "-o", str(s_path)]
    r = subprocess.run(NICE + gcc, capture_output=True, text=True, cwd=cfile.parent, env=_env())
    if r.returncode != 0:
        return None, "gcc: " + (r.stderr or r.stdout)[-300:]
    asflags = (row.get("row_asflags") or "").split()
    pipe = (f"python3 {UP_LIVE}/tools/ccproc.py < {s_path} | {VENV_PY} {MASPSX} --aspsx-version=2.56 --dont-force-G0 "
            f"--run-assembler --gnu-as-path=mipsel-linux-gnu-as -I{UP} -I{inc} -EL -march=r3000 -G8 {' '.join(asflags)} -o {o_path}")
    r = subprocess.run(pipe, shell=True, capture_output=True, text=True, cwd=UP_LIVE, env=_env())
    if r.returncode != 0 or not o_path.exists():
        return None, "as: " + (r.stderr or r.stdout)[-300:]
    return o_path, None

def disasm(obj):
    r = subprocess.run(["mipsel-linux-gnu-objdump", "-d", "-r", str(obj)], capture_output=True, text=True)
    return [l for l in r.stdout.splitlines() if re.match(r"^\s+[0-9a-f]+:\s", l)]

def verify_slus(row, cfile, include_root=None):
    t0 = time.time()
    ref = (read_baseline_slus() or {}).get(row["id"])
    with tempfile.TemporaryDirectory() as td:
        obj, err = compile_slus(row, cfile, td, include_root)
        if obj is None:
            return {"status": "failed", "exact": False, "err": err, "secs": round(time.time() - t0, 2)}
        h = sha_file(obj)
        if ref is None:
            return {"status": "ok", "exact": None, "obj_sha": h, "err": "no pinned object cached", "secs": round(time.time() - t0, 2)}
        if h == ref["obj_sha"]:
            return {"status": "ok", "exact": True, "obj_sha": h, "secs": round(time.time() - t0, 2)}
        # crude residue for slus: disassembly diff vs cached pinned disassembly
        got = disasm(obj)
        tgt = (CACHE / "slus_dis" / (row["id"].split("/")[1] + ".txt")).read_text().splitlines()
        ndiff = sum(1 for a, b in zip(got, tgt) if a.split(None, 2)[-1] != b.split(None, 2)[-1]) + abs(len(got) - len(tgt))
        return {"status": "ok", "exact": False, "obj_sha": h, "gen_words": len(got), "tgt_words": len(tgt),
                "total": ndiff, "class": "length-drift" if len(got) != len(tgt) else "slus-diff", "secs": round(time.time() - t0, 2)}

_slus_base = None
def read_baseline_slus():
    global _slus_base
    if _slus_base is None:
        p = CACHE / "slus_obj.json"
        _slus_base = json.load(open(p)) if p.exists() else {}
    return _slus_base

def baseline_slus(row):
    t0 = time.time()
    (CACHE / "slus_dis").mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as td:
        obj, err = compile_slus(row, UP / row["c_path"], td)
        if obj is None:
            return {"id": row["id"], "status": "failed", "exact": False, "err": err, "secs": round(time.time() - t0, 2)}
        h = sha_file(obj)
        (CACHE / "slus_dis" / (row["id"].split("/")[1] + ".txt")).write_text("\n".join(disasm(obj)) + "\n")
        return {"id": row["id"], "status": "ok", "exact": None, "obj_sha": h, "secs": round(time.time() - t0, 2)}

# ---------------------------------------------------------------- entry points
def verify(row, cfile, regions=False, include_root=None):
    if row["kind"] == "slus":
        return verify_slus(row, cfile, include_root)
    return verify_overlay(row, cfile, regions, include_root)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("row_id", nargs="?"); ap.add_argument("cfile", nargs="?")
    ap.add_argument("--regions", action="store_true"); ap.add_argument("--include-root")
    ap.add_argument("--baseline", action="store_true"); ap.add_argument("--workers", type=int, default=6)
    ap.add_argument("--container"); ap.add_argument("--limit", type=int); ap.add_argument("--all", action="store_true", help="include non-stock rows")
    a = ap.parse_args()
    by = {r["id"]: r for r in rows()}
    if a.baseline:
        rs = [r for r in by.values() if r["exists"] and (a.all or r["stock"]) and (not a.container or r["container"] == a.container)]
        if a.limit: rs = rs[:a.limit]
        out = LEDGER / "baseline.jsonl"
        done = {r["id"] for r in read_jsonl(out)}
        rs = [r for r in rs if r["id"] not in done]
        print(f"baseline: {len(rs)} rows to verify ({len(done)} already done)", flush=True)
        CACHE.mkdir(parents=True, exist_ok=True)
        slus_cache = read_baseline_slus()
        def one(r):
            if r["kind"] == "slus": return baseline_slus(r)
            return dict(verify_overlay(r, UP / r["c_path"]), id=r["id"])
        n = 0; t0 = time.time()
        with ThreadPoolExecutor(max_workers=a.workers) as ex:
            for rec in ex.map(one, rs):
                rec["src_sha"] = by[rec["id"]]["src_sha"]; rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
                append_jsonl(out, rec); n += 1
                if rec.get("obj_sha") and by[rec["id"]]["kind"] == "slus":
                    slus_cache[rec["id"]] = {"obj_sha": rec["obj_sha"], "src_sha": rec["src_sha"]}
                if n % 200 == 0:
                    json.dump(slus_cache, open(CACHE / "slus_obj.json", "w"))
                    el = time.time() - t0; print(f"{n}/{len(rs)} {el:.0f}s eta {el/n*(len(rs)-n):.0f}s", flush=True)
        json.dump(slus_cache, open(CACHE / "slus_obj.json", "w"), indent=0)
        print(f"done {n} in {time.time()-t0:.0f}s")
        return
    row = by[a.row_id]
    print(json.dumps(verify(row, Path(a.cfile).resolve(), a.regions, a.include_root), indent=1))

if __name__ == "__main__":
    main()
