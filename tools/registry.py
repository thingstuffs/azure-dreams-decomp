#!/usr/bin/env python3
"""Enumerate every matched row -> ledger/rows.jsonl (the registry), from the row database.

Overlay rows come from ledger/splits/<ovl>.jsonl (result == MATCH with a C path); SLUS rows are
the cc edges of the pinned recipe (ledger/splits/slus.jsonl, one TU each; the functions a TU
defines are listed).  dungeon_engine is a second proof over dungeon rows and is a count only.

A row's window of record is `gate_config`.  The gate compiles every MATCH row whose extent lies
inside a window's file range, so a row the split table left without one is assigned the covering
window (`gate_config_derived: true`; the window the neighbouring rows name when several cover it).
When build_ovl/ exists the gate's row tables are re-exported so the two never disagree.
"""
import json, re, collections, subprocess, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, RAW, OVERLAYS, is_stock_cfg, is_keyed_asflags, parse_cfg, write_jsonl, read_jsonl, sha_file, window_map, covering_windows

DEF_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8})\s*\(", re.M)
SPLITS = LEDGER / "splits"


def assign_window(container, rows_named):
    """rows_named: {window name: count of rows naming it} for this container, used to break ties."""
    def pick(r):
        cands = covering_windows(container, r["foff"], r["size"])
        if not cands:
            return None
        # prefer the window most rows in the container already name, then the tightest range
        cands.sort(key=lambda w: (-rows_named.get(w[0], 0), w[2] - w[1]))
        return "config/overlays/" + cands[0][0]
    return pick


def overlay_rows():
    out = []
    for ovl in OVERLAYS:
        db = read_jsonl(SPLITS / f"{ovl}.jsonl")
        asflags = {}
        p = ROOT / "config/overlays" / f"{ovl}.as_flags.jsonl"
        if p.exists():
            for l in p.read_text().splitlines():
                if l.strip():
                    j = json.loads(l); asflags[j["func"]] = j.get("as_flags", "")
        named = collections.Counter(Path(r["gate_config"]).name for r in db if r.get("gate_config"))
        pick = assign_window(ovl, named)
        for r in db:
            if r.get("result") != "MATCH" or not r.get("c_path"):
                continue
            cfg = r.get("config") or ""
            cell, flags = parse_cfg(cfg) if cfg else ("", [])
            src = RAW / ovl / Path(r["c_path"]).name
            gate = r.get("gate_config"); derived = False
            if not gate:
                gate = pick(r); derived = gate is not None
            rec = {
                "id": f"{ovl}/{r['func_vram']}", "container": ovl, "func": r["func_vram"],
                "true_name": r.get("true_name"), "cfg": cfg, "cell": cell, "flags": " ".join(flags),
                "size": int(r["size"]), "foff": int(r["foff"]), "c_path": r["c_path"],
                "exists": src.exists(), "src_sha": sha_file(src) if src.exists() else None,
                "gate_config": gate, "instances": int(r.get("instances") or 1),
                "row_asflags": asflags.get(r["func_vram"]),
                "stock": is_stock_cfg(cfg) and not is_keyed_asflags(asflags.get(r["func_vram"])) and cfg != "platform-asm",
                "kind": "overlay",
            }
            if derived:
                rec["gate_config_derived"] = True
            out.append(rec)
    return out


def slus_rows():
    edges = read_jsonl(SPLITS / "slus.jsonl")
    sizes = json.load(open(ROOT / "config/func_sizes.json"))
    out = []
    for e in edges:
        src = RAW / "slus" / Path(e["src"]).name
        text = src.read_text(errors="replace") if src.exists() else ""
        defs = sorted(set(DEF_RE.findall(text)))
        cfg = (e["ccver"] + (" " + e["ccflags"] if e["ccflags"] else "")).strip()
        out.append({
            "id": f"slus/{Path(e['src']).stem}", "container": "slus", "func": defs[0] if len(defs) == 1 else None,
            "true_name": None, "cfg": cfg, "cell": e["ccver"], "flags": e["ccflags"],
            "size": sum(sizes.get(d, 0) for d in defs), "foff": None, "c_path": e["src"],
            "exists": src.exists(), "src_sha": sha_file(src) if src.exists() else None,
            "gate_config": "build.ninja", "instances": 1, "row_asflags": e["asflags"] or None,
            "stock": is_stock_cfg(cfg) and not is_keyed_asflags(e["asflags"]),
            "kind": "slus", "defs": defs, "ndefs": len(defs),
        })
    return out


def main():
    rows = overlay_rows() + slus_rows()
    write_jsonl(LEDGER / "rows.jsonl", rows)
    eng = [r for r in read_jsonl(SPLITS / "dungeon_engine.jsonl") if r.get("result") == "MATCH"]
    c = collections.Counter(); b = collections.Counter(); st = collections.Counter(); sb = collections.Counter()
    for r in rows:
        c[r["container"]] += 1; b[r["container"]] += r["size"]
        if r["stock"]: st[r["container"]] += 1; sb[r["container"]] += r["size"]
    print(f"{'container':10} {'rows':>6} {'bytes':>9} {'stock':>6} {'stock_B':>9}")
    for k in ("slus", "main", "town", "dungeon", "ovmovie"):
        print(f"{k:10} {c[k]:6d} {b[k]:9d} {st[k]:6d} {sb[k]:9d}")
    print(f"{'total':10} {sum(c.values()):6d} {sum(b.values()):9d} {sum(st.values()):6d} {sum(sb.values()):9d}")
    nowin = [r for r in rows if r["kind"] == "overlay" and not r["gate_config"]]
    derived = sum(1 for r in rows if r.get("gate_config_derived"))
    print(f"dungeon_engine mirror rows (not registered): {len(eng)}; windows derived for {derived} rows; rows in no window: {len(nowin)}")
    for r in nowin: print("  NO WINDOW:", r["id"], r["size"], r["foff"])
    for root in (ROOT / "build_ovl", ROOT / "build_ovl_raw"):
        if (root / "overlays").exists():
            subprocess.run([sys.executable, str(ROOT / "tools/row_db.py"), "export", str(root)], check=True, stdout=subprocess.DEVNULL)
            print(f"row tables re-exported to {root.name}/")


if __name__ == "__main__":
    main()
