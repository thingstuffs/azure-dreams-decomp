#!/usr/bin/env python3
"""ASPSX-version trial (toolchain fidelity plan; measurement only).

Question: is switching the pipeline's `maspsx --aspsx-version=2.56` to 2.79 (or 2.77) byte-neutral over
every row of the tree?  docs/evidence/fidelity_asv_trial.md has the answer; this is the instrument.

maspsx never sees the version string: `config_for_aspsx_version` (tools/maspsx/maspsx.py) maps it to
eight behaviour flags, and between 2.56 and 2.8x only three change (`version_config()` below reads the
live table):

    2.56          sltu_at=T  gp_allow_offset=F  gp_allow_la=F     (the pipeline today)
    2.60 - 2.69   sltu_at=F                                        (2.60: sltu_at alone)
    2.70 - 2.79   sltu_at=F  gp_allow_offset=T                     (2.77 == 2.79 by construction)
    >= 2.80       sltu_at=F  gp_allow_offset=T  gp_allow_la=T      (2.81)

so the maspsx leg is run at 2.56 (baseline) and 2.60 / 2.77 / 2.79 / 2.81, and a change is attributed by
the first version at which the object moves (2.60 -> sltu_at; 2.79 but not 2.60 -> gp_allow_offset;
2.81 but not 2.79 -> gp_allow_la).

Per row, from ONE gcc -S (tools/fidelity/aspsx_diff.py prepare_slus / prepare_overlay: the project
pipeline's own compile and verdict):
  * the maspsx leg (traced, tools/fidelity/maspsx_trace.py) at every version, ONLY the pipeline's global
    `--aspsx-version=2.56` swapped - a row's own `--aspsx-version=` dial stays last on the argv and wins,
    exactly as in tools/build/cc.sh, tools/verify.py and match.build_text;
  * an object byte-identical to the 2.56 object is `same` (sufficient for byte-neutral);
  * a changed object is judged exactly as the maspsx leg is judged now: slus by verify_slus's rule
    (pinned TU object sha, else name-masked disassembly identical to ledger/cache/slus_dis), plus a
    direct resolution against the retail SLUS; overlays by the per-row scorer itself
    (match.build_text at that --aspsx-version, the scorer's own argv, then linked_words_equal);
  * rows carrying a version dial are also run with the dial DROPPED at 2.56 and at 2.79 (what the dial
    does, and whether a global switch retires it);
  * a static predictor on maspsx's input (negative-immediate `sltu`; `SYM+OFF` memory operands of a
    small `.comm` symbol; bare `la` of a small-data symbol) - every changed row must be predicted.

    python3 tools/fidelity/asv_trial.py [--workers 8] [--only ID,ID|@file] [--container town] [--limit N]
    python3 tools/fidelity/asv_trial.py --one town/func_80614B88
Journal: work/fidelity/asv/asv_trial.jsonl (hash-keyed; unchanged rows are never recomputed).
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(HERE))
import aspsx_diff as AD  # noqa: E402
from objread import read_elf  # noqa: E402

JOURNAL = ROOT / "work/fidelity/asv/asv_trial.jsonl"
BASE = "2.56"
TRIAL = ["2.60", "2.77", "2.79", "2.81"]
DIAL_AT = ["2.56", "2.79"]
TOOL_VERSION = "1"
NICE = AD.NICE
# own scratch root, shared with no other tool: tools/fidelity/aspsx_diff.py (and jobs built on it) remove
# work/fidelity/tmp/rows when their runs end, which deleted this trial's per-row directories mid-run (the
# first run lost 10 rows + 10 partial records); only this directory is ever removed by this tool
AD.TMP = ROOT / "work/fidelity/asv/tmp"
FLAGS = ("div_uses_tge", "nop_at_expansion", "nop_mflo_mfhi", "sltu_at", "expand_li",
         "gp_allow_offset", "gp_allow_la", "addiu_at")


def _sha(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


# ------------------------------------------------------------------------------ version table
def version_config(ver: str) -> dict:
    """The live maspsx behaviour flags for an --aspsx-version (read from tools/maspsx/maspsx.py)."""
    import importlib.util
    spec = importlib.util.spec_from_file_location("maspsx_cli_asv", ROOT / "tools/maspsx/maspsx.py")
    sys.path.insert(0, str(ROOT / "tools/maspsx"))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    c = mod.config_for_aspsx_version(ver)
    return {f: getattr(c, f) for f in FLAGS}


def config_delta(a: str, b: str) -> dict:
    ca, cb = version_config(a), version_config(b)
    return {f: [ca[f], cb[f]] for f in FLAGS if ca[f] != cb[f]}


def attribute_change(changed: dict) -> str:
    """{version: bool object-changed} -> the version-gated behaviour that moved the object.

    The trial versions are nested configs (2.60 adds sltu_at=F, 2.7x adds gp_allow_offset,
    2.8x adds gp_allow_la), so the first version at which the object moves names the flag; a
    change that appears and then disappears again is `non-monotone` (should not happen)."""
    order = [("2.60", "sltu_at"), ("2.79", "gp_allow_offset"), ("2.81", "gp_allow_la")]
    causes = []
    prev = False
    for v, flag in order:
        c = bool(changed.get(v))
        if c and not prev:
            causes.append(flag)
        elif prev and not c:
            causes.append("non-monotone@" + v)
        prev = c
    return "+".join(causes) if causes else "none"


def verdict_class(base_exact: bool, same: bool, exact) -> str:
    """same / changed-exact / stops-matching / starts-matching / changed-nonexact."""
    if same:
        return "same"
    if base_exact:
        return "changed-exact" if exact else "stops-matching"
    return "starts-matching" if exact else "changed-nonexact"


# ------------------------------------------------------------------------------- predictor
MEMOPS = r"(?:lb|lbu|lh|lhu|lw|lwl|lwr|sb|sh|sw|swl|swr|lwc2|swc2|la)"


def predict(s_text: str, sdata_limit: int = 8) -> dict:
    """Static counts on maspsx's input of the three constructs whose expansion the trial versions change."""
    comm, small = {}, set()
    for m in re.finditer(r"^\s*\.(?:comm|lcomm)\s+([\w.$]+)\s*,\s*(\d+)", s_text, re.M):
        comm[m.group(1)] = int(m.group(2))
    for m in re.finditer(r"^\s*\.extern\s+([\w.$]+)\s*,\s*(\d+)", s_text, re.M):
        if 0 < int(m.group(2)) <= sdata_limit:
            small.add(m.group(1))
    small |= {k for k, v in comm.items() if 0 < v <= sdata_limit}
    sltu_neg = len(re.findall(r"^\s*sltu\s+\$\w+\s*,\s*\$\w+\s*,\s*-(?:0x[0-9a-fA-F]+|\d+)\s*$", s_text, re.M))
    comm_off = 0
    for m in re.finditer(rf"^\s*{MEMOPS}\s+\$\w+\s*,\s*([\w.$]+)\+(-?\w+)", s_text, re.M):
        if m.group(1) in comm and 0 < comm[m.group(1)] <= sdata_limit:
            comm_off += 1
    la_small = sum(1 for m in re.finditer(r"^\s*la\s+\$\w+\s*,\s*([\w.$]+)(?:\+\S+)?\s*$", s_text, re.M)
                   if m.group(1) in small)
    return {"sltu_neg": sltu_neg, "comm_off": comm_off, "la_small": la_small}


# ------------------------------------------------------------------------------- judges
def slus_judge(obj: bytes, row, td) -> dict:
    """verify_slus's rule on an object: pinned TU object sha, else name-masked disassembly equal to the
    cached retail listing; plus a direct resolution of every function against the retail SLUS."""
    import verify
    p = Path(td) / "judge.o"
    p.write_bytes(obj)
    ref = (verify.read_baseline_slus() or {}).get(row["id"])
    out = {"pinned": bool(ref and _sha(obj) == ref["obj_sha"])}
    exact = out["pinned"]
    if not exact:
        dis = ROOT / "ledger/cache/slus_dis" / (row["id"].split("/")[1] + ".txt")
        if dis.exists():
            got = verify.disasm(p); tgt = dis.read_text().splitlines()
            mask = lambda ls: [re.sub(r"(R_MIPS_\w+)\s+\S+", r"\1 <>", re.sub(r"<[^>]*>", "<>", re.sub(r"^\s*[0-9a-f]+:\s*", "", l))) for l in ls]
            out["text_identical"] = len(got) == len(tgt) and mask(got) == mask(tgt)
            exact = out["text_identical"]
    v = AD.View(read_elf(obj))
    scope = sorted(v.funcs)
    rc = AD.retail_compare(v, scope, "slus")
    out["retail"] = [rc["diff"], rc["masked"], rc["checked"], len(scope)]
    if not exact and rc["diff"] == 0 and rc["masked"] == 0 and rc["checked"] == len(scope):
        # the pinned-object reference disagrees but every word resolves to the retail SLUS
        # (aspsx_diff's `retail-resolved` proof; slus/w_8005A1D0 is the one such row)
        out["retail_resolved"] = exact = True
    out["exact"] = bool(exact)
    return out


def overlay_judge(cap, ver, as_flags, ctx) -> dict:
    """The per-row scorer at --aspsx-version=`ver`: match.build_text with the scorer's own argv, then
    linked_words_equal against the retail slice."""
    ofc, _ = AD._ofc()
    a, k = cap
    a = list(a); a[3] = ver; a[5] = as_flags
    k = dict(k); k["asm_output"] = None
    got, err = ofc.M.build_text(*a, **k)
    out = {"exact": bool(got is not None and ofc.linked_words_equal(got, ctx["retail"]))}
    if got is None:
        out["err"] = (err or "no output")[:200]
    else:
        out["linked_same"] = got == ctx["linked"]
        rw = [struct.unpack_from("<I", ctx["retail"], 4 * i)[0] for i in range(len(ctx["retail"]) // 4)]
        gw = [struct.unpack_from("<I", got, 4 * i)[0] for i in range(len(got) // 4)]
        out["words_diff"] = sum(1 for i in range(max(len(rw), len(gw)))
                                if (rw[i] if i < len(rw) else None) != (gw[i] if i < len(gw) else None))
    return out


def swap_version(as_args, ver):
    """The pipeline argv with the GLOBAL version (element 0) swapped; a row dial later on the argv stays."""
    assert as_args[0] == "--aspsx-version=" + BASE, as_args[0]
    return ["--aspsx-version=" + ver] + list(as_args[1:])


def drop_dial(as_args, ver):
    return ["--aspsx-version=" + ver] + [x for x in as_args[1:] if not x.startswith("--aspsx-version=")]


# ------------------------------------------------------------------------------- one row
def process_row(row, keep=False):
    from common import clean_path
    t0 = time.time()
    AD.TMP.mkdir(parents=True, exist_ok=True)
    os.environ["TMPDIR"] = str(AD.TMP); tempfile.tempdir = str(AD.TMP)
    td = tempfile.mkdtemp(prefix="asv_" + row["id"].replace("/", "__") + "_", dir=AD.TMP)
    rec = {"row": row["id"], "container": row["container"], "kind": row["kind"], "cfg": row["cfg"]}
    try:
        cfile = clean_path(row)
        cap = None
        if row["kind"] == "slus":
            ctx, err = AD.prepare_slus(row, cfile, row["cfg"], row.get("row_asflags") or "", td)
        else:
            ofc, _ = AD._ofc()
            orig = ofc.M.build_text
            calls = []

            def spy(*a, **k):
                calls.append((a, k))
                return orig(*a, **k)
            ofc.M.build_text = spy
            try:
                ctx, err = AD.prepare_overlay(row, cfile, row["cfg"], None, td)
            finally:
                ofc.M.build_text = orig
            if calls:
                cap = calls[0]
        if ctx is None:
            rec.update(status="error", err=("compile: " + str(err))[:300]); return rec
        rec["cell"] = ctx["cell"]
        row_flags = ctx["as_args"][7:]
        rec["asflags"] = " ".join(row_flags)
        dial = [x.split("=", 1)[1] for x in row_flags if x.startswith("--aspsx-version=")]
        if dial:
            rec["dial"] = dial[-1]
        rec["base_exact"] = bool(ctx["maspsx_exact"]); rec["proof"] = ctx["proof"]
        if ctx["kind"] == "slus" and not rec["base_exact"]:
            j = slus_judge(ctx["pipeline_obj"], row, td)
            if j.get("retail_resolved"):
                rec["base_exact"] = True; rec["proof"] = "retail-resolved"
        rec["pred"] = predict(ctx["m_in"])
        env = ctx["env"]
        objs, fired = {}, {}
        for ver in [BASE] + TRIAL:
            trp = Path(td) / f"tr{ver}.json"
            o, e = AD.run_maspsx(ctx["m_in"], swap_version(ctx["as_args"], ver), Path(td) / f"m{ver}.o", env, trace=trp)
            if o is None:
                rec.setdefault("run_err", {})[ver] = e
                continue
            objs[ver] = o
            fired[ver] = json.loads(trp.read_text())["fired"]
        if BASE not in objs:
            rec.update(status="error", err="maspsx at 2.56: " + str(rec.get("run_err", {}).get(BASE))[:300]); return rec
        # self-check: the traced 2.56 object is the pipeline's
        if ctx["kind"] == "slus":
            rec["selfcheck"] = _sha(objs[BASE]) == _sha(ctx["pipeline_obj"])
        else:
            mv = AD.View(read_elf(objs[BASE]))
            sym = ctx["symbol"]
            mv.add_unit(sym); mv.composite = {sym}
            AD.shape_unit(mv, sym, len(ctx["retail"]))
            got = ctx["linked"]
            if got is None or sym not in mv.funcs:
                rec["selfcheck"] = None
            else:
                toks = mv.tokens(sym)
                gw = [struct.unpack_from("<I", got, 4 * i)[0] for i in range(len(got) // 4)]
                rec["selfcheck"] = len(gw) == len(toks) and all(
                    (g & ~AD.FIELD.get(t[1], 0) & 0xFFFFFFFF) == t[0] if t[1] else g == t[0] for g, t in zip(gw, toks))
        rec["sha"] = {v: _sha(o)[:12] for v, o in objs.items()}
        rec["fired_base"] = fired[BASE]
        base_sha = _sha(objs[BASE])
        res = {}
        for ver in TRIAL:
            if ver not in objs:
                res[ver] = {"err": rec["run_err"][ver][:200]}; continue
            same = _sha(objs[ver]) == base_sha
            r = {"same": same}
            if fired[ver] != fired[BASE]:
                r["fired"] = fired[ver]
            if not same:
                if ctx["kind"] == "slus":
                    r.update(slus_judge(objs[ver], row, td))
                elif cap is not None:
                    r.update(overlay_judge(cap, ver, cap[0][5], ctx))
                else:
                    r["exact"] = None; r["err"] = "no scorer call captured"
            r["class"] = verdict_class(rec["base_exact"], same, r.get("exact"))
            res[ver] = r
        rec["v"] = res
        rec["cause"] = attribute_change({v: not res[v].get("same", True) for v in TRIAL if "err" not in res[v]})
        # a row version dial: what it does (dropped at 2.56), and whether a global switch retires it
        if dial:
            dv = {}
            for ver in DIAL_AT:
                args = drop_dial(ctx["as_args"], ver)
                o, e = AD.run_maspsx(ctx["m_in"], args, Path(td) / f"d{ver}.o", env)
                if o is None:
                    dv[ver] = {"err": e[:200]}; continue
                r = {"same": _sha(o) == base_sha}
                if not r["same"]:
                    if ctx["kind"] == "slus":
                        r.update(slus_judge(o, row, td))
                    elif cap is not None:
                        r.update(overlay_judge(cap, ver, " ".join(args[7:]), ctx))
                r["class"] = verdict_class(rec["base_exact"], r["same"], r.get("exact"))
                dv[ver] = r
            dv["config_delta_vs_dial"] = {v: config_delta(dial[-1], v) for v in DIAL_AT}
            rec["dial_drop"] = dv
        rec["status"] = "ok"
        return rec
    except Exception as exc:
        import traceback
        rec.update(status="error", err=("harness: " + "".join(traceback.format_exception_only(type(exc), exc)).strip())[:300])
        return rec
    finally:
        rec["secs"] = round(time.time() - t0, 1)
        if not keep:
            shutil.rmtree(td, ignore_errors=True)


# ------------------------------------------------------------------------------- driver
def tool_fp() -> str:
    h = hashlib.sha256((TOOL_VERSION + AD.tool_fingerprint()).encode())
    h.update(_sha((HERE / "asv_trial.py").read_bytes()).encode())
    return h.hexdigest()[:20]


def load_journal(path):
    recs = {}
    if path.exists():
        for l in path.read_text().splitlines():
            try:
                r = json.loads(l)
            except json.JSONDecodeError:
                continue
            recs[r["row"]] = r
    return recs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--only"); ap.add_argument("--container"); ap.add_argument("--limit", type=int)
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--one"); ap.add_argument("--keep", action="store_true")
    ap.add_argument("--journal", default=str(JOURNAL))
    ap.add_argument("--worker", help=argparse.SUPPRESS)
    a = ap.parse_args()
    journal_path = Path(a.journal)
    from common import rows, clean_path
    by = {r["id"]: r for r in rows()}
    if a.worker or a.one:
        rec = process_row(by[a.worker or a.one], keep=a.keep)
        print(json.dumps(rec, separators=(",", ":")) if a.worker else json.dumps(rec, indent=1))
        return
    rs = list(by.values())
    if a.only:
        ids = [x.strip() for x in (Path(a.only[1:]).read_text().split() if a.only.startswith("@") else a.only.split(","))]
        rs = [by[i] for i in ids if i in by]
    if a.container:
        rs = [r for r in rs if r["container"] == a.container]
    if a.limit:
        rs = rs[:a.limit]
    fp = tool_fp()
    journal = load_journal(journal_path)
    todo = []
    for r in rs:
        cp = clean_path(r)
        text = cp.read_text(errors="replace") if cp.exists() else ""
        key = AD.row_key(r, text, fp, r["cfg"], r.get("row_asflags") or "")
        old = journal.get(r["id"])
        if not a.force and old and old.get("key") == key and old.get("status") == "ok":
            continue
        todo.append((r, key))
    workers = min(a.workers, 8)
    print(f"asv_trial: {len(rs)} rows selected, {len(todo)} to compute, fingerprint {fp}, {workers} workers", flush=True)
    journal_path.parent.mkdir(parents=True, exist_ok=True)

    def one(item):
        r, key = item
        p = subprocess.run(NICE + [sys.executable, str(Path(__file__)), "--worker", r["id"]],
                           capture_output=True, text=True, timeout=3600, cwd=str(ROOT))
        try:
            rec = json.loads(p.stdout.strip().splitlines()[-1])
        except Exception:
            rec = {"row": r["id"], "container": r["container"], "kind": r["kind"], "status": "error",
                   "err": "worker: " + (p.stderr or p.stdout)[-300:]}
        rec["key"] = key; rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
        return rec

    t0 = time.time(); n = 0
    with ThreadPoolExecutor(max_workers=workers) as ex, open(journal_path, "a") as fh:
        for rec in ex.map(one, todo):
            fh.write(json.dumps(rec, separators=(",", ":")) + "\n"); fh.flush()
            journal[rec["row"]] = rec; n += 1
            if n % 500 == 0:
                el = time.time() - t0
                print(f"  {n}/{len(todo)} {el:.0f}s eta {el / n * (len(todo) - n):.0f}s", flush=True)
    keep_ids = set(by)
    with open(journal_path, "w") as fh:
        for rid in sorted(journal):
            if rid in keep_ids:
                fh.write(json.dumps(journal[rid], separators=(",", ":")) + "\n")
    shutil.rmtree(AD.TMP, ignore_errors=True)
    print(f"asv_trial: done {n} rows in {time.time() - t0:.0f}s -> {journal_path}", flush=True)


if __name__ == "__main__":
    main()
