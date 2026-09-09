#!/usr/bin/env python3
"""Declaration census (L4b groundwork): how every function and data symbol is declared across the
per-row files of a container, against how it is defined.

    python3 tools/decl_census.py [--container town] [--out work/decl_census]

Per container it writes <out>/<container>.json:
  functions: {sym: {"definition": {"row", "ret", "params"} | null, "prototypes": {"<ret>|<params>": [rows...]}}}
  data:      {sym: {"types": {"<type>": [rows...]}, "records": [Rec_* headers whose class is the symbol]}}
and prints the conflict counts.  A symbol is CONFLICTING when its prototypes (or extern types)
disagree across files; the definition's own signature is the canonical prototype the T12 header
takes, and a data symbol's canonical type is the T7 record where one exists, else the single agreed
type, else a union of the views (the T7 mechanism) or a per-row cast.  Comments are stripped; names
are spelled through config/names.tsv so a renamed function's callers count under its func_ symbol.
"""
import argparse, json, re, collections
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, rows

DECL = re.compile(r"^\s*extern\s+([^;()]*?)\b(D_[0-9A-F]{8}|[A-Za-z_][A-Za-z0-9_]*)\s*(\[[^\]]*\])?\s*;", re.M)
PROTO = re.compile(r"^\s*(?:extern\s+)?([A-Za-z_][\w\s\*]*?)\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^;{]*)\)\s*(?:__attribute__\s*\(\([^)]*\)\)\s*)?;", re.M)
DEF = re.compile(r"^\s*([A-Za-z_][\w\s\*]*?)\b([A-Za-z_][A-Za-z0-9_]*)\s*\(([^;{)]*)\)\s*(?:__attribute__\s*\(\([^)]*\)\)\s*)?\{", re.M)
KW = {"if", "while", "for", "switch", "return", "sizeof", "do", "else", "typedef", "struct", "union"}

def strip(t):
    return re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))

def names_table():
    out = {}
    p = ROOT / "config" / "names.tsv"
    if p.exists():
        for raw in p.read_text().splitlines():
            cols = raw.split("#", 1)[0].rstrip("\n").split("\t")
            if len(cols) >= 3 and cols[1].strip() and cols[2].strip(): out[cols[2].strip()] = cols[1].strip()
    return out

def norm(s):
    return " ".join(s.replace("extern", "").split())

def main():
    ap = argparse.ArgumentParser(); ap.add_argument("--container"); ap.add_argument("--out", default="work/decl_census")
    a = ap.parse_args()
    canon = names_table()
    rec_class = {}
    rj = ROOT / "ledger" / "records.json"
    if rj.exists():
        for name, rec in json.load(open(rj)).items():
            cls = rec.get("class", "")
            if cls.startswith("global:"): rec_class.setdefault(cls[7:], []).append(name)
    out_dir = ROOT / a.out; out_dir.mkdir(parents=True, exist_ok=True)
    conts = [a.container] if a.container else ["slus", "main", "town", "dungeon"]
    for cont in conts:
        funcs = collections.defaultdict(lambda: {"definition": None, "prototypes": collections.defaultdict(list)})
        data = collections.defaultdict(lambda: {"types": collections.defaultdict(list), "records": []})
        for r in rows():
            if r["container"] != cont: continue
            p = ROOT / "src" / cont / Path(r["c_path"]).name
            if not p.exists(): continue
            t = strip(p.read_text(errors="replace"))
            for m in DEF.finditer(t):
                name = canon.get(m.group(2), m.group(2))
                if name in KW: continue
                funcs[name]["definition"] = {"row": r["id"], "ret": norm(m.group(1)), "params": norm(m.group(3))}
            for m in PROTO.finditer(t):
                name = canon.get(m.group(2), m.group(2))
                if name in KW or name.startswith("ASM_") or name.startswith("M2C_"): continue
                funcs[name]["prototypes"][norm(m.group(1)) + "|" + norm(m.group(3))].append(r["id"])
            for m in DECL.finditer(t):
                name = m.group(2)
                if "(" in m.group(1) or name in KW: continue
                ty = norm(m.group(1)) + ("[]" if m.group(3) is not None else "")
                data[name]["types"][ty].append(r["id"])
        for sym in data:
            data[sym]["records"] = rec_class.get(sym, [])
        fc = sum(1 for f in funcs.values() if len(f["prototypes"]) > 1)
        fd = sum(1 for f in funcs.values() if f["definition"] and f["prototypes"] and any(k != f["definition"]["ret"] + "|" + f["definition"]["params"] for k in f["prototypes"]))
        dc = sum(1 for d in data.values() if len(d["types"]) > 1)
        dr = sum(1 for d in data.values() if d["records"])
        json.dump({"container": cont, "functions": funcs, "data": data}, open(out_dir / f"{cont}.json", "w"), indent=0, default=dict)
        print(f"{cont}: functions {len(funcs)} (prototypes disagree across files {fc}; disagree with the definition {fd}); data symbols {len(data)} (types disagree {dc}; on a T7 record {dr})")

if __name__ == "__main__":
    main()
