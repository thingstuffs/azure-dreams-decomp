#!/usr/bin/env python3
"""Enumerate every matched row at the pin -> ledger/rows.jsonl.

Overlay rows come from upstream's overlay_first_pass_results.json (result == MATCH with a C
path).  SLUS rows are the cc edges of the pinned build.ninja (one TU each; the functions a TU
defines are listed).  dungeon_engine is recorded as a mirror count only.
"""
import json, re, collections
from pathlib import Path
from common import UP, LEDGER, OVERLAYS, is_stock_cfg, parse_cfg, write_jsonl, sha_file

DEF_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8})\s*\(", re.M)

def overlay_rows():
    out = []
    for ovl in OVERLAYS:
        db = json.load(open(UP / "overlays" / ovl / "overlay_first_pass_results.json"))
        asflags = {}
        p = UP / "config/overlays" / f"{ovl}.as_flags.jsonl"
        if p.exists():
            for l in p.read_text().splitlines():
                if l.strip():
                    j = json.loads(l); asflags[j["func"]] = j.get("as_flags", "")
        for r in db:
            if r.get("result") != "MATCH" or not r.get("c_path"):
                continue
            cfg = r.get("config") or ""
            cell, flags = parse_cfg(cfg) if cfg else ("", [])
            src = UP / r["c_path"]
            out.append({
                "id": f"{ovl}/{r['func_vram']}", "container": ovl, "func": r["func_vram"],
                "true_name": r.get("true_name"), "cfg": cfg, "cell": cell, "flags": " ".join(flags),
                "size": int(r["size"]), "foff": int(r["foff"]), "c_path": r["c_path"],
                "exists": src.exists(), "src_sha": sha_file(src) if src.exists() else None,
                "gate_config": r.get("gate_config"), "instances": int(r.get("instances") or 1),
                "row_asflags": asflags.get(r["func_vram"]),
                "stock": is_stock_cfg(cfg) and r["func_vram"] not in asflags and cfg != "platform-asm",
                "kind": "overlay",
            })
    return out

def slus_rows():
    edges, cur = [], None
    for raw in (UP / "build.ninja.pinned").read_text().splitlines():
        m = re.match(r"^build (\S+): cc (\S+)", raw)
        if m:
            cur = {"out": m.group(1), "src": m.group(2), "ccver": "2.7.2", "ccflags": "", "asflags": ""}
            edges.append(cur); continue
        if cur is not None:
            m = re.match(r"^\s+(ccver|ccflags|asflags) = ?(.*)$", raw)
            if m: cur[m.group(1)] = m.group(2)
            elif not raw.startswith(" ") and raw.strip(): cur = None
    sizes = json.load(open(UP / "config/func_sizes.json"))
    out = []
    for e in edges:
        src = UP / e["src"]
        text = src.read_text(errors="replace") if src.exists() else ""
        defs = sorted(set(DEF_RE.findall(text)))
        cfg = (e["ccver"] + (" " + e["ccflags"] if e["ccflags"] else "")).strip()
        out.append({
            "id": f"slus/{Path(e['src']).stem}", "container": "slus", "func": defs[0] if len(defs) == 1 else None,
            "true_name": None, "cfg": cfg, "cell": e["ccver"], "flags": e["ccflags"],
            "size": sum(sizes.get(d, 0) for d in defs), "foff": None, "c_path": e["src"],
            "exists": src.exists(), "src_sha": sha_file(src) if src.exists() else None,
            "gate_config": "build.ninja", "instances": 1, "row_asflags": e["asflags"] or None,
            "stock": e["ccver"] in {"2.6.3","2.7.2","2.7.2-cdk","2.8.0","2.8.1","2.91.66","2.95.2"} and not e["asflags"],
            "kind": "slus", "defs": defs, "ndefs": len(defs),
        })
    return out

def main():
    rows = overlay_rows() + slus_rows()
    write_jsonl(LEDGER / "rows.jsonl", rows)
    eng = [r for r in json.load(open(UP / "overlays/dungeon_engine/overlay_first_pass_results.json")) if r.get("result") == "MATCH"]
    c = collections.Counter(); b = collections.Counter(); st = collections.Counter(); sb = collections.Counter()
    for r in rows:
        c[r["container"]] += 1; b[r["container"]] += r["size"]
        if r["stock"]: st[r["container"]] += 1; sb[r["container"]] += r["size"]
    print(f"{'container':10} {'rows':>6} {'bytes':>9} {'stock':>6} {'stock_B':>9}")
    for k in ("slus", "main", "town", "dungeon", "ovmovie"):
        print(f"{k:10} {c[k]:6d} {b[k]:9d} {st[k]:6d} {sb[k]:9d}")
    print(f"{'total':10} {sum(c.values()):6d} {sum(b.values()):9d} {sum(st.values()):6d} {sum(sb.values()):9d}")
    print(f"dungeon_engine mirror rows (not registered): {len(eng)}")

if __name__ == "__main__":
    main()
