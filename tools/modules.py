#!/usr/bin/env python3
"""Module map (L4c): validate a proposed partition of one container's rows into source files and
record it in ledger/modules.jsonl.

    python3 tools/modules.py check <proposal.json>            # validate only, print the verdicts
    python3 tools/modules.py accept <proposal.json>           # validate, then write the container's records

A proposal ({"container", "modules": [{"name", "load_base", "foff_start", "foff_end", "rows",
"rationale", "confidence"}]}) is accepted only when: every registered row of the container appears in
exactly one module; modules are contiguous runs in file-offset order with no interleaving; a module
never spans two load bases (sub-overlays are different files); a row whose evidence carries an
assertion site `file.c:line` sits in a module named `file.c`; names are lowercase_snake_case `.c`.
Records: {"id", "container", "module", "module_index", "confidence"} one per row, replacing the
container's previous records.  The map is the manifest the declaration and header work (T12) and the
`l4_modules` journal build on; nothing here moves a file.
"""
import argparse, json, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, write_jsonl

NAME_RE = re.compile(r"^[a-z][a-z0-9_]*\.c$")

def load_bases(container):
    out = {}
    p = LEDGER / "splits" / f"{container}.jsonl"
    if p.exists():
        for j in read_jsonl(p):
            out[j["func_vram"]] = j.get("load_base")
    return out

def assertion_files():
    """row id -> set of source files proven by assertion sites."""
    out = {}
    p = LEDGER / "evidence" / "rows.jsonl"
    if p.exists():
        for e in read_jsonl(p):
            files = {s.get("source_file") for s in e.get("assert_sites", []) if s.get("source_file")}
            if files: out[e["id"]] = files
    return out

def check(proposal):
    cont = proposal["container"]
    reg = {r["id"]: r for r in rows() if r["container"] == cont}
    lb = load_bases(cont); af = assertion_files()
    errors = []; seen = {}
    mods = proposal.get("modules", [])
    last_end = -1
    for i, m in enumerate(mods):
        name = m.get("name", "")
        if not NAME_RE.match(name): errors.append(f"module {i}: name {name!r} is not lowercase_snake_case .c")
        ids = m.get("rows", [])
        if not ids: errors.append(f"module {i} {name}: no rows"); continue
        offs = []
        bases = set()
        for rid in ids:
            r = reg.get(rid)
            if r is None: errors.append(f"module {name}: {rid} is not a registered {cont} row"); continue
            if rid in seen: errors.append(f"{rid} appears in {seen[rid]} and {name}")
            seen[rid] = name
            offs.append(r["foff"] if r["foff"] is not None else 0)
            bases.add(lb.get(r["func"]))
            for f in af.get(rid, ()):
                if f != name: errors.append(f"{rid} carries assertion file {f} but sits in {name}")
        if offs != sorted(offs): errors.append(f"module {name}: rows not in file-offset order")
        if len(bases) > 1: errors.append(f"module {name}: spans load bases {sorted(str(b) for b in bases)}")
        if offs and offs[0] < last_end: errors.append(f"module {name}: overlaps or interleaves with the previous module")
        if offs: last_end = max(offs)
    missing = sorted(set(reg) - set(seen))
    if missing: errors.append(f"{len(missing)} rows not in any module (first: {missing[:5]})")
    # contiguity: no foreign row between a module's first and last row
    order = sorted(reg.values(), key=lambda r: (r["foff"] if r["foff"] is not None else 0, r["id"]))
    pos = {r["id"]: k for k, r in enumerate(order)}
    for m in mods:
        ks = sorted(pos[i] for i in m.get("rows", []) if i in pos)
        if ks and ks[-1] - ks[0] + 1 != len(ks):
            inside = [order[k]["id"] for k in range(ks[0], ks[-1] + 1) if seen.get(order[k]["id"]) != m["name"]]
            errors.append(f"module {m['name']}: not contiguous ({len(inside)} foreign rows inside, e.g. {inside[:3]})")
    return errors

def accept(proposal):
    cont = proposal["container"]
    p = LEDGER / "modules.jsonl"
    keep = [j for j in read_jsonl(p) if j.get("container") != cont] if p.exists() else []
    recs = []
    for i, m in enumerate(proposal["modules"]):
        for rid in m["rows"]:
            recs.append({"id": rid, "container": cont, "module": m["name"], "module_index": i, "confidence": m.get("confidence", "weak")})
    write_jsonl(p, keep + recs)
    return len(recs), len(proposal["modules"])

def main():
    ap = argparse.ArgumentParser(); ap.add_argument("cmd", choices=["check", "accept"]); ap.add_argument("proposal")
    a = ap.parse_args()
    prop = json.loads(Path(a.proposal).read_text())
    errs = check(prop)
    for e in errs[:40]: print("ERROR", e)
    print(f"{prop['container']}: {len(prop.get('modules', []))} modules, {sum(len(m.get('rows', [])) for m in prop.get('modules', []))} rows, {len(errs)} errors")
    if a.cmd == "accept":
        if errs: sys.exit(1)
        n, k = accept(prop); print(f"accepted: {n} rows in {k} modules -> ledger/modules.jsonl")

if __name__ == "__main__":
    main()
