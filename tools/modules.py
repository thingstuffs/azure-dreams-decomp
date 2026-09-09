#!/usr/bin/env python3
"""Module map (L4c): validate a proposed partition of one container's rows into source files and
record it in ledger/modules.jsonl.

    python3 tools/modules.py check <proposal.json> [--scope <input.json>]    # validate only, print the verdicts
    python3 tools/modules.py accept <proposal.json> [--scope <input.json>]   # validate, then write the rows' records

A proposal may cover one sub-overlay group of a container (the input file it was made from is its
scope); the records of several partial proposals combine into the container's map.

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
            if j.get("func_vram"): out[j["func_vram"]] = j.get("load_base")
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

CONTAINERS = ("slus", "main", "town", "dungeon", "ovmovie")

def container_of(proposal):
    """A proposal names its input file stem (`town_0x8007d760`, `dungeon_overlays`); the container is the prefix."""
    c = proposal["container"]
    return next((k for k in CONTAINERS if c == k or c.startswith(k + "_")), c)

def scope_ids(proposal, scope):
    """The rows a proposal must cover: the whole container, or the rows of the input file it was made from."""
    if scope:
        return {x["id"] for x in json.loads(Path(scope).read_text())}
    return None

def row_key(r):
    """File-offset order; SLUS rows (one executable, no per-row foff) order by their lowest symbol address."""
    if r.get("foff") is not None:
        return r["foff"]
    addrs = [int(m.group(1), 16) for s in [r.get("func")] + list(r.get("defs") or []) if s for m in [re.search(r"([0-9A-F]{8})$", s)] if m]
    return min(addrs) if addrs else 0

def check(proposal, scope=None):
    cont = container_of(proposal)
    reg = {r["id"]: r for r in rows() if r["container"] == cont}
    ids_in_scope = scope_ids(proposal, scope)
    if ids_in_scope is not None:
        reg = {k: v for k, v in reg.items() if k in ids_in_scope}
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
            offs.append(row_key(r))
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
    order = sorted(reg.values(), key=lambda r: (row_key(r), r["id"]))
    pos = {r["id"]: k for k, r in enumerate(order)}
    for m in mods:
        ks = sorted(pos[i] for i in m.get("rows", []) if i in pos)
        if ks and ks[-1] - ks[0] + 1 != len(ks):
            inside = [order[k]["id"] for k in range(ks[0], ks[-1] + 1) if seen.get(order[k]["id"]) != m["name"]]
            errors.append(f"module {m['name']}: not contiguous ({len(inside)} foreign rows inside, e.g. {inside[:3]})")
    return errors

def accept(proposal):
    """Records for the proposal's rows replace any earlier record of those rows (partial proposals per
    sub-overlay group combine into the container's map)."""
    cont = container_of(proposal)
    covered = {rid for m in proposal["modules"] for rid in m["rows"]}
    p = LEDGER / "modules.jsonl"
    keep = [j for j in read_jsonl(p) if j.get("id") not in covered] if p.exists() else []
    recs = []
    for i, m in enumerate(proposal["modules"]):
        for rid in m["rows"]:
            recs.append({"id": rid, "container": cont, "module": m["name"], "module_index": i, "confidence": m.get("confidence", "weak")})
    write_jsonl(p, keep + recs)
    return len(recs), len(proposal["modules"])

def main():
    ap = argparse.ArgumentParser(); ap.add_argument("cmd", choices=["check", "accept"]); ap.add_argument("proposal")
    ap.add_argument("--scope", help="the input JSON the proposal was made from (a partial proposal must cover exactly its rows)")
    a = ap.parse_args()
    prop = json.loads(Path(a.proposal).read_text())
    errs = check(prop, a.scope)
    for e in errs[:40]: print("ERROR", e)
    print(f"{prop['container']} ({container_of(prop)}): {len(prop.get('modules', []))} modules, {sum(len(m.get('rows', [])) for m in prop.get('modules', []))} rows, {len(errs)} errors")
    if a.cmd == "accept":
        if errs: sys.exit(1)
        n, k = accept(prop); print(f"accepted: {n} rows in {k} modules -> ledger/modules.jsonl")

if __name__ == "__main__":
    main()
