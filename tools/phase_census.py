#!/usr/bin/env python3
"""Phase census: for one pin erased alone, which gcc pass first differs from the pinned build, and how.

    python3 tools/phase_census.py run --out <file.jsonl> [--per-family REG=320,KEEP=150,FENCE=80,OTHER=60]
                                      [--ids FILE] [--seed 20260913] [--jobs 6] [--tmp DIR]
    python3 tools/phase_census.py summary <file.jsonl>

Round 18 (2026-09-13). One random site per sampled row and family; the pinned and the erased text are
both compiled with -da and every pass dump (rtl, jump, cse, loop, cse2, flow, combine, sched, lreg, greg,
sched2, jump2, dbr) is compared three ways, asm patterns dropped:
  ms   the operations as a multiset, registers anonymised and plain reg-reg copies dropped (identity)
  seq  the same operations in order
  abs  the stream with registers renamed by first appearance, copies included (data-flow wiring)
Class at combine (the pass itself, so a difference that reconverges by combine does not count):
ops (ms differs), order (seq differs), wiring (abs differs), late (identical at combine).
Comparisons are lossy (flags, notes and links dropped): a screen and a census, never an exactness proof.
Keep --out outside work/ subtrees that agents search (a 600-site census is ~0.8 MB).
"""
import argparse
import collections
import json
from multiprocessing import Pool
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, parse_cfg
from pin_census import sites_of
from pin_sites import erase_many
from xform.sched_trace import instructions, normalize, distance

PHASES = ["rtl", "jump", "cse", "loop", "cse2", "flow", "combine", "sched", "lreg", "greg", "sched2", "jump2", "dbr"]
ANON = re.compile(r"\(reg(?:/\w+)?:([A-Z0-9]+) \d+(?: [^)]+)?\)")
ASMP = re.compile(r"asm_operands|asm_input")
COPY = re.compile(r"^\(set \(reg:\w+\) \(reg:\w+\)\)$")
TMP = None


def family(macro):
    if macro.startswith("ASM_REG"):
        return "REG"
    if macro.startswith("ASM_KEEP"):
        return "KEEP"
    return "FENCE" if macro in ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER") else "OTHER"


def compile_dumps(row, text):
    cell, flags = parse_cfg(row["cfg"])
    cc = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="census_", dir=TMP) as td:
        d = Path(td)
        (d / Path(row["c_path"]).name).write_text(text)
        cmd = [str(cc / "gcc"), "-B" + str(cc) + "/", "-S", "-O2", *flags, "-I" + str(ROOT / "include"), "-w", "-da",
               Path(row["c_path"]).name, "-o", "f.s"]
        try:
            r = subprocess.run(cmd, cwd=d, capture_output=True, text=True, timeout=60)
        except subprocess.TimeoutExpired:
            return None
        if r.returncode or not (d / "f.s").exists():
            return None
        return {"asm": normalize((d / "f.s").read_text(errors="replace")),
                "dumps": {p.suffix[1:]: p.read_text(errors="replace") for p in d.iterdir() if p.suffix[1:] in PHASES}}


def features(src):
    ab = [x["pattern"] for x in instructions(src, True) if not ASMP.search(x["pattern"])]
    ops = [ANON.sub(r"(reg:\1)", x["pattern"]) for x in instructions(src) if not ASMP.search(x["pattern"])]
    nc = [p for p in ops if not COPY.match(p)]
    return ab, nc, len(ops) - len(nc)


def work(task):
    row, picks = task
    text = clean(row).read_text(errors="replace")
    base = compile_dumps(row, text)
    if base is None:
        return [{"id": row["id"], "error": "base-compile"}]
    bf = {p: features(s) for p, s in base["dumps"].items()}
    sites, out = sites_of(text), []
    for fam, si in picks:
        s = sites[si]
        rec = {"id": row["id"], "family": fam, "macro": s[1], "site": si, "npins": len(sites)}
        after = compile_dumps(row, erase_many(text, [s], clean_notes=True))
        if after is None:
            out.append(dict(rec, error="erased-compile"))
            continue
        rec["asm_distance"] = distance(base["asm"], after["asm"])
        ph = {}
        for p in PHASES:
            if p in bf and p in after["dumps"]:
                (ab, nc, cp), (ab2, nc2, cp2) = bf[p], features(after["dumps"][p])
                ph[p] = {"abs": ab == ab2, "seq": nc == nc2, "ms": collections.Counter(nc) == collections.Counter(nc2),
                         "ops": [len(nc), len(nc2)], "copies": [cp, cp2]}
        rec["phases"] = ph
        rec["class"] = classify(rec)
        out.append(rec)
    return out


def clean(row):
    return ROOT / "src" / row["container"] / Path(row["c_path"]).name


def classify(rec):
    c = rec["phases"].get("combine")
    if not c:
        return "no-combine"
    return "ops" if not c["ms"] else "order" if not c["seq"] else "wiring" if not c["abs"] else "late"


def run(args):
    global TMP
    TMP = args.tmp
    want = dict((k, int(v)) for k, v in (x.split("=") for x in args.per_family.split(",")))
    only = set(Path(args.ids).read_text().split()) if args.ids else None
    pop = collections.defaultdict(list)
    for r in rows():
        if r["container"] == "ovmovie" or (only is not None and r["id"] not in only) or not clean(r).exists():
            continue
        by = collections.defaultdict(list)
        for i, s in enumerate(sites_of(clean(r).read_text(errors="replace"))):
            by[family(s[1])].append(i)
        for f, idx in by.items():
            pop[f].append((r, idx))
    rnd, tasks = random.Random(args.seed), {}
    for f, n in want.items():
        for r, idx in rnd.sample(pop[f], min(n, len(pop[f]))):
            tasks.setdefault(r["id"], (r, []))[1].append((f, rnd.choice(idx)))
    print({f: len(v) for f, v in pop.items()}, "rows per family;", len(tasks), "rows sampled", flush=True)
    with open(args.out, "w") as fo, Pool(args.jobs) as pool:
        for n, res in enumerate(pool.imap_unordered(work, list(tasks.values())), 1):
            for rec in res:
                fo.write(json.dumps(rec) + "\n")
            if n % 50 == 0:
                print(n, "rows done", flush=True)


def summary(path):
    recs = [json.loads(line) for line in open(path)]
    ok = [r for r in recs if "phases" in r]
    print(len(recs), "records,", len(ok), "usable,", dict(collections.Counter(r["error"] for r in recs if "error" in r)))
    fams = sorted({r["family"] for r in ok})
    for key, what in (("ms", "operation multiset"), ("seq", "operation sequence"), ("abs", "wiring (renamed stream)")):
        print("\nfirst pass where the %s differs:" % what)
        print("%-7s" % "family" + "".join("%7s" % p[:6] for p in PHASES + ["none"]) + "     n")
        for f in fams:
            c = collections.Counter(next((p for p in PHASES if p in r["phases"] and not r["phases"][p][key]), "none")
                                    for r in ok if r["family"] == f)
            print("%-7s" % f + "".join("%7d" % c[p] for p in PHASES + ["none"]) + "%6d" % sum(c.values()))
    print("\nclass at combine:")
    for f in fams:
        c = collections.Counter(classify(r) for r in ok if r["family"] == f)   # recomputed: older records stored another rule
        print("  %-6s" % f, dict(c.most_common()))


if __name__ == "__main__":
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("run")
    a.add_argument("--out", required=True)
    a.add_argument("--per-family", default="REG=320,KEEP=150,FENCE=80,OTHER=60")
    a.add_argument("--ids")
    a.add_argument("--seed", type=int, default=20260913)
    a.add_argument("--jobs", type=int, default=6)
    a.add_argument("--tmp")
    b = sub.add_parser("summary")
    b.add_argument("jsonl")
    args = ap.parse_args()
    run(args) if args.cmd == "run" else summary(args.jsonl)
