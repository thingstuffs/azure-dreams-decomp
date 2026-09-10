#!/usr/bin/env python3
"""Generate STATUS.md from the ledger (rows, baseline, census, levels)."""
import collections, json, time
from common import LEDGER, ROOT, rows, read_jsonl, PARKED_CONTAINERS
from pin_census import sites_of

def main():
    rs = rows(); by = {r["id"]: r for r in rs}
    base = {b["id"]: b for b in read_jsonl(LEDGER / "baseline.jsonl")}
    cen = {c["id"]: c for c in read_jsonl(LEDGER / "census.jsonl")}
    pin = json.load(open(LEDGER / "pin.json"))
    out = []
    out.append(f"# azure-dreams-decomp status\n\nGenerated {time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())}. Pin `{pin['pin']}` ({pin['commit'][:12]}, raw/ frozen at {pin['extracted_at']}).\n")
    out.append("## Denominator (rows matched at the pin)\n\n| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |\n|---|---:|---:|---:|---:|---:|---:|---:|")
    T = collections.Counter()
    for c in ("slus", "main", "town", "dungeon", "ovmovie", "ALL"):
        sel = [r for r in rs if (c == "ALL" and r["container"] not in PARKED_CONTAINERS) or r["container"] == c]
        st = [r for r in sel if r["stock"]]
        ex = [r for r in st if base.get(r["id"], {}).get("exact") is True or (r["kind"] == "slus" and base.get(r["id"], {}).get("status") == "ok")]
        nb = [r for r in st if r["id"] not in base]
        out.append(f"| {c} | {len(sel)} | {sum(r['size'] for r in sel):,} | {len(st)} | {sum(r['size'] for r in st):,} | {len(ex)} | {sum(r['size'] for r in ex):,} | {len(nb)} |")
    bad = [r for r in rs if r["stock"] and r["id"] in base and base[r["id"]].get("exact") is False]
    out.append(f"\novmovie is parked by the owner (listed, excluded from ALL). SLUS rows are verified by object identity with the pinned TU (SLUS is byte-exact by its SHA-1 gate, tools/build/build_slus.sh); overlay rows by retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are none at the pin.\n\nBaseline NOT exact: {len(bad)} rows" + (": " + ", ".join(r["id"] for r in bad[:20]) if bad else "") + "\n")
    out.append("## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)\n\n| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |\n|---|---:|---:|---:|---:|---:|---:|")
    tot = sum(r["size"] for r in rs)
    import re as _re
    from pathlib import Path as _P
    PIN_RE = _re.compile(r"\bASM_([A-Z0-9_]+)\(")
    def cur_facts(r):
        cp = ROOT / "src" / r["container"] / _P(r["c_path"]).name
        p = cp if cp.exists() else ROOT / "raw" / r["container"] / _P(r["c_path"]).name
        if not p.exists(): return None
        t = p.read_text(errors="replace")
        return {"boiler": "This header contains macros emitted by m2c" in t or "typedef float f32;" in t,
                "m2c_field": len(_re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in t.splitlines() if not l.lstrip().startswith("#")))),
                # through the pin machinery, not the raw text: PIN_RE also matches a pin note in a
                # comment and a local wrapper #define, so a row the campaign had freed kept
                # being counted and this column drifted from pin_watch and the sweep
                "pin_total": len(sites_of(t)), "gotos": len(_re.findall(r"\bgoto\s+[A-Za-z_]", t)),
                "computed_goto": len(_re.findall(r"\bgoto\s*\*", t)), "inline_asm": len(_re.findall(r"__asm__|\basm\s*\(", t)),
                "m2c_locals": len(set(_re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+|phi_[a-z0-9_]+)\b", t))),
                "n_local_structs": len(set(_re.findall(r"\b((?:S_|Struct|Func)[0-9A-F]{7,8}[A-Za-z0-9_]*)\b", t))),
                "audit": cen.get(r["id"], {}).get("audit", {}),   # live: sites still spelled in the current text
                "tail_idiom": len(_re.findall(r"__attribute__\s*\(\s*\(\s*noreturn\s*\)\s*\)", t)) + len(_re.findall(r"\basm\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)|__asm__\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)", t)),
                "dowhile0": len(_re.findall(r"\bdo\s*\{[^{}]*\}\s*while\s*\(\s*0\s*\)", t, _re.S)),
                "markers": sum(1 for _s in sites_of(t) if _s[1] in (
                    "ASM_TAILSLOT_PIN", "ASM_TAILSLOT_PIN_TIED", "ASM_PAGEBASE_PIN", "ASM_JALDELAY_PIN",
                    "ASM_LIVE_SIBCALL_PIN", "ASM_SHAPE_D_SIBCALL_PIN", "ASM_BRANCH_LABEL_SPLIT"))}
    curc = {r["id"]: cur_facts(r) for r in rs}
    defs = [("m2c boilerplate block", lambda c: c["boiler"]), ("M2C_FIELD raw offsets", lambda c: c["m2c_field"] > 0), ("m2c local names", lambda c: c["m2c_locals"] > 0),
            ("ASM_ pins", lambda c: c["pin_total"] > 0), ("goto", lambda c: c["gotos"] > 0), ("computed-goto jump table", lambda c: c["computed_goto"] > 0),
            ("inline asm outside macros", lambda c: c["inline_asm"] > 0), ("fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS)", lambda c: any(k in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS") for k in c["audit"])),
            ("any fidelity site", lambda c: bool(c["audit"])),
            ("noreturn tail-call spelling (scaffolding, docs/FIDELITY.md)", lambda c: c.get("tail_idiom", 0) > 0), ("maspsx marker pins (scaffolding)", lambda c: c.get("markers", 0) > 0),
            ("do{}while(0) scheduling barrier (scaffolding, pure C)", lambda c: c.get("dowhile0", 0) > 0),
            ("local address-named struct", lambda c: c["n_local_structs"] > 0),
            ("clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names)", lambda c: not c["boiler"] and c["m2c_field"] == 0 and c["pin_total"] == 0 and c["gotos"] == 0 and c["m2c_locals"] == 0)]
    for name, f in defs:
        sel = [by[i] for i, c in cen.items() if not c.get("missing") and f(dict(c, audit=c.get("audit_pin", c.get("audit", {}))))]   # pin column: the audit as it was at the pin
        b = sum(r["size"] for r in sel)
        sel2 = [by[i] for i, c in curc.items() if c and f(c)]
        b2 = sum(r["size"] for r in sel2)
        out.append(f"| {name} | {len(sel)} | {b:,} | {100*b/tot:.1f}% | {len(sel2)} | {b2:,} | {100*b2/tot:.1f}% |")
    pins = collections.Counter(); 
    for c in cen.values():
        for k, v in c.get("pins", {}).items(): pins[k] += v
    out.append(f"\nPin sites: {sum(pins.values()):,} total; " + ", ".join(f"{k} {v:,}" for k, v in pins.most_common(8)) + ".\n")
    lv = LEDGER / "levels.jsonl"
    out.append("## Cleanliness levels (bytes at or above each level)\n")
    if lv.exists():
        L = collections.Counter()
        for x in read_jsonl(lv):
            for l in range(0, x["level"] + 1): L[l] += by[x["id"]]["size"]
        out.append("| level | bytes | % |\n|---|---:|---:|")
        for l in range(6): out.append(f"| L{l} | {L[l]:,} | {100*L[l]/tot:.1f}% |")
        recs = [x for x in read_jsonl(lv) if x.get("records")]
        rb = sum(by[x["id"]]["size"] for x in recs)
        out.append(f"\nOn shared record headers (T7, `include/records/`): {len(recs)} rows, {rb:,} bytes ({100*rb/tot:.1f}%); "
                   f"records used: {len({r for x in recs for r in x['records']})}.")
    else:
        exb = sum(r["size"] for r in rs if r["stock"] and (base.get(r["id"], {}).get("exact") is True or (r["kind"] == "slus" and base.get(r["id"], {}).get("status") == "ok")))
        out.append(f"L0 (verified byte-exact at the pin): {exb:,} bytes ({100*exb/tot:.1f}%). No transforms applied yet; every row is at L0.\n")
    try:
        from evidence import census as _ev_census
        out.append("\n## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)\n")
        out.append(_ev_census())
        out.append("\nEvery lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.")
    except Exception as e:
        out.append(f"\n(evidence census unavailable: {e})")
    (ROOT / "STATUS.md").write_text("\n".join(out) + "\n")
    print("\n".join(out))

if __name__ == "__main__":
    main()
