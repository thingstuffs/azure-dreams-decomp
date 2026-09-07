#!/usr/bin/env python3
"""The row database: ledger/splits/ is the split table of every container (every row the gate
lays out, matched or not), ledger/rows.jsonl the registry of matched rows derived from it.

    python3 tools/row_db.py import [--mirror DIR]   # a mirror's overlays/<ovl>/overlay_first_pass_results.json
                                                    # and pinned build.ninja -> ledger/splits/ (frozen at the pin)
    python3 tools/row_db.py export <build_root>     # ledger/splits/<ovl>.jsonl -> <root>/overlays/<ovl>/
                                                    # overlay_first_pass_results.json (the gate's input format)
    python3 tools/row_db.py check                   # split tables well-formed; every registered row inside
                                                    # a window; every MATCH row's C present in raw/ and src/

Split-table records keep the fields the gate closure reads (identity, extent, verdict, config,
source) and drop free text and per-wave bookkeeping.  `import` only runs at a pin bump; after the
swap-over the tables are the source of truth and are edited in place (tools/row_db.py add-row).
"""
from __future__ import annotations
import argparse, json, os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, RAW, window_map, covering_windows, read_jsonl, write_jsonl, sha_file

SPLITS = LEDGER / "splits"
CONTAINERS = ("main", "town", "dungeon", "dungeon_engine", "ovmovie")
KEEP = ("func_vram", "true_name", "vram", "true_vram", "foff", "size", "result", "rerun", "config", "c_path",
        "asm_path", "source_kind", "gate_config", "gate_verified", "instances", "data_segment", "parked",
        "hand_asm", "bios_stub", "base_confidence", "load_base", "alias_of", "duplicate_of", "words_off")


def trim(row: dict) -> dict:
    out = {k: row[k] for k in KEEP if k in row and row[k] is not None}
    # only a matched row's C is an input; other rows may name scratch files that never existed here
    if out.get("result") != "MATCH" or not str(out.get("c_path", "")).startswith("overlays/"):
        out.pop("c_path", None)
    return out


def edges_of(ninja_text: str):
    edges, cur = [], None
    for raw in ninja_text.splitlines():
        m = re.match(r"^build (\S+): cc (\S+)", raw)
        if m:
            cur = {"out": m.group(1), "src": m.group(2), "ccver": "2.7.2", "ccflags": "", "asflags": ""}
            edges.append(cur); continue
        if cur is not None:
            m = re.match(r"^\s+(ccver|ccflags|asflags) = ?(.*)$", raw)
            if m: cur[m.group(1)] = m.group(2).strip()
            elif not raw.startswith(" ") and raw.strip(): cur = None
    return edges


def cmd_import(a):
    mirror = Path(a.mirror) if a.mirror else ROOT / "upstream"
    SPLITS.mkdir(parents=True, exist_ok=True)
    for ovl in CONTAINERS:
        src = mirror / "overlays" / ovl / "overlay_first_pass_results.json"
        rows = [trim(r) for r in json.load(open(src))]
        rows.sort(key=lambda r: (r.get("foff") if isinstance(r.get("foff"), int) else -1, r.get("func_vram", "")))
        write_jsonl(SPLITS / f"{ovl}.jsonl", rows)
        print(f"{ovl:15} {len(rows):5} rows -> ledger/splits/{ovl}.jsonl")
    pinned = mirror / "build.ninja.pinned"
    text = pinned.read_text()
    (SPLITS / "slus.build.ninja").write_text(text)
    edges = edges_of(text)
    write_jsonl(SPLITS / "slus.jsonl", edges)
    print(f"{'slus':15} {len(edges):5} cc edges -> ledger/splits/slus.jsonl (+ slus.build.ninja, sha256 {sha_file(SPLITS / 'slus.build.ninja')[:12]})")
    for n in ("func_sizes.json", "decomp_audit_baseline.json"):
        p = mirror / "config" / n
        if p.exists():
            (ROOT / "config" / n).write_text(p.read_text()); print(f"config/{n} imported")


def cmd_export(a):
    root = Path(a.root)
    for ovl in CONTAINERS:
        rows = read_jsonl(SPLITS / f"{ovl}.jsonl")
        d = root / "overlays" / ovl; d.mkdir(parents=True, exist_ok=True)
        tmp = d / ".overlay_first_pass_results.json.tmp"
        tmp.write_text(json.dumps(rows, indent=0) + "\n"); os.replace(tmp, d / "overlay_first_pass_results.json")   # atomic: a running gate never sees a torn table
        print(f"{ovl:15} {len(rows):5} rows -> {d.relative_to(root)}/overlay_first_pass_results.json")


def cmd_check(a):
    bad = 0
    wm = window_map()
    for ovl in CONTAINERS:
        rows = read_jsonl(SPLITS / f"{ovl}.jsonl")
        last = -1
        for r in sorted((r for r in rows if not r.get("rerun") and isinstance(r.get("foff"), int)), key=lambda r: r["foff"]):
            if r["foff"] < last:
                print(f"{ovl}: overlapping split row {r['func_vram']} at 0x{r['foff']:X}"); bad += 1
            last = r["foff"] + r["size"]
        fam = "dungeon" if ovl == "dungeon_engine" else ovl
        for r in rows:
            if r.get("result") != "MATCH" or r.get("rerun"): continue
            if r.get("source_kind") in ("platform_asm",): continue
            name = Path(r["c_path"]).name if r.get("c_path") else None
            if not name:
                print(f"{ovl}: MATCH row {r['func_vram']} has no c_path"); bad += 1; continue
            if not (RAW / fam / name).exists():
                print(f"{ovl}: raw/{fam}/{name} missing"); bad += 1
            if not (ROOT / "src" / fam / name).exists():
                print(f"{ovl}: src/{fam}/{name} missing"); bad += 1
            if not covering_windows(fam, r["foff"], r["size"], wm):
                print(f"{ovl}: MATCH row {r['func_vram']} (0x{r['foff']:X}+{r['size']}) is in no window"); bad += 1
    print("row database OK" if not bad else f"{bad} problems")
    sys.exit(1 if bad else 0)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("import"); p.add_argument("--mirror")
    p = sub.add_parser("export"); p.add_argument("root")
    sub.add_parser("check")
    a = ap.parse_args()
    {"import": cmd_import, "export": cmd_export, "check": cmd_check}[a.cmd](a)


if __name__ == "__main__":
    main()
