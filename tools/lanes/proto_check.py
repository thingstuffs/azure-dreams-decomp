#!/usr/bin/env python3
"""Flag staged prototype edits whose declared return type contradicts the callee's real definition.
usage: proto_check.py <lane> [<lane> ...]   (compares out/<c>/<name>.c against base/; callee looked up by func or true_name)"""
import json, re, sys, glob, collections
from pathlib import Path
rows = [json.loads(l) for l in open("ledger/rows.jsonl")]
defs = collections.defaultdict(list)            # (container, name) -> [row id]
for r in rows:
    for n in {r["func"], r.get("true_name")} - {None}:
        defs[(r["container"], n)].append(r["id"])
DECL = re.compile(r"^\s*(?:extern\s+)?([A-Za-z_][\w\s\*]*?)\s*\b(func_[0-9A-Fa-f]{8}|w_[0-9A-Fa-f]{8})\s*\(", re.M)
def deftype(rid, name):
    t = Path("src/%s.c" % rid).read_text(errors="replace")
    m = re.search(r"^([A-Za-z_][\w\s\*]*?)\s*\b%s\s*\([^;{]*\)\s*\{" % name, t, re.M)
    return " ".join(m.group(1).split()) if m else None
bad = 0; n = 0
for lane in sys.argv[1:]:
    for f in glob.glob("work/native_lane/%s/out/*/*.c" % lane):
        c = f.split("/")[-2]; base = Path(f.replace("/out/", "/base/")).read_text(errors="replace")
        old = {m.group(2): " ".join(m.group(1).split()) for m in DECL.finditer(base)}
        for m in DECL.finditer(Path(f).read_text(errors="replace")):
            name, ty = m.group(2), " ".join(m.group(1).split())
            if old.get(name) == ty or "M2C_UNK" not in (old.get(name) or ""): continue
            n += 1
            cands = defs.get((c, name), []) + (defs.get(("slus", name), []) if c != "slus" else [])
            dts = {deftype(r, name) for r in cands} - {None}
            if dts and ty not in dts and not (ty == "s32" and dts <= {"int", "s32", "M2C_UNK"}):
                bad += 1; print("MISMATCH %s %s: declared %r, definition(s) %s" % (f.split("native_lane/")[1], name, ty, sorted(dts)))
print("checked %d changed prototypes, %d mismatches" % (n, bad))
