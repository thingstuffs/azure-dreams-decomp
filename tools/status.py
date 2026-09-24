#!/usr/bin/env python3
"""Generate STATUS.md from the ledger (rows, baseline, census, levels)."""
import collections, json, time
from common import LEDGER, ROOT, rows, read_jsonl, PARKED_CONTAINERS
from pin_census import sites_of, hidden_asm
from census import _fakedep

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
    out.append(f"\novmovie is parked by the owner (listed, excluded from ALL). Ordinary SLUS rows use pinned-TU object verification; grouped module candidates use the full SLUS image gate, including sibling functions and owned data. Historical raw baselines stay per row. Overlay rows use retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are none at the pin.\n\nBaseline NOT exact: {len(bad)} rows" + (": " + ", ".join(r["id"] for r in bad[:20]) if bad else "") + "\n")
    from slus_module_evidence import module_status
    module_records = module_status()
    if module_records:
        out.append("## SLUS modules\n\n| module | logical rows | placement evidence | shared headers |\n|---|---:|---|---|")
        for entry in module_records:
            module = entry["module"]
            proof = "current: retail + genuine ASPSX 2.79" if entry["valid"] else "unproved: " + entry["reason"]
            out.append(f"| {module['name']} | {len(module['members'])} | {proof} | " + ", ".join(module["headers"]) + " |")
        out.append("\nModule placement preserves logical row IDs. The existing L4/L5 pin, tail-jump and fidelity requirements still apply; changed shared inputs invalidate placement evidence.\n")
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
                "pin_total": len(sites_of(t)), "pins_by": collections.Counter(s[1][4:] for s in sites_of(t)), "hidden": hidden_asm(t),
                "gotos": len(_re.findall(r"\bgoto\s+[A-Za-z_]", t)),
                "computed_goto": len(_re.findall(r"\bgoto\s*\*", t)), "inline_asm": len(_re.findall(r"__asm__|\basm\s*\(", t)),
                "m2c_locals": len(set(_re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+|phi_[a-z0-9_]+)\b", t))),
                "n_local_structs": len(set(_re.findall(r"\b((?:S_|Struct|Func)[0-9A-F]{7,8}[A-Za-z0-9_]*)\b", t))),
                "audit": cen.get(r["id"], {}).get("audit", {}),   # live: sites still spelled in the current text
                "tail_idiom": len(_re.findall(r"__attribute__\s*\(\s*\(\s*noreturn\s*\)\s*\)", t)) + len(_re.findall(r"\basm\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)|__asm__\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)", t)),
                "dowhile0": len(_re.findall(r"\bdo\s*\{[^{}]*\}\s*while\s*\(\s*0\s*\)", t, _re.S)),
                "fakedep": _fakedep(t),
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
            ("fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C)", lambda c: c.get("fakedep", 0) > 0),
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
    # `cen` is the census of the frozen text at the pin; the live count is the current tree's.
    # This line used to print only the former under the bare label "Pin sites" (25,788 against
    # 12,041 live on 2026-09-11), which read as the size of the remaining debt.
    # parked containers are listed, not counted (the ALL row above excludes them too)
    live ={i: c for i, c in curc.items() if c and i.split("/")[0] not in PARKED_CONTAINERS}
    pins = collections.Counter()
    for i, c in cen.items():
        if i.split("/")[0] not in PARKED_CONTAINERS:
            pins.update(c.get("pins", {}))
    now = collections.Counter()
    for c in live.values():
        now.update(c["pins_by"])
    out.append(f"\nPin sites now: {sum(now.values()):,} in {sum(1 for c in live.values() if c['pin_total']):,} rows; "
               + ", ".join(f"{k} {v:,}" for k, v in now.most_common(8))
               + f".  At the pin: {sum(pins.values()):,}; " + ", ".join(f"{k} {v:,}" for k, v in pins.most_common(8)) + ".\n")
    hid = collections.Counter()
    for c in live.values(): hid.update(c["hidden"])
    out.append(f"Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements {hid['raw-pin']:,}, "
               f"calls of local asm wrappers {hid['wrapper-call']:,}, hand-written asm in function bodies {hid['asm-code']:,} "
               f"(C that is missing); symbol aliases {hid['symbol-alias']:,} (a second typed name for one symbol: a missing type); "
               f"file-scope asm directives {hid['file-asm']:,}.\n")
    nfl = collections.Counter(min(2, len([x for x in r["cfg"].replace("+", " ").split()[1:] if x.startswith(("-f", "-O", "-m"))]))
                          for r in rs if r["id"].split("/")[0] not in PARKED_CONTAINERS)
    out.append(f"Per-row optimization flags (weak evidence about the real build; each switch is undone from the "
               f"`t30_cellpins` journal's `cell_from`): {nfl[1]:,} rows carry one flag, {nfl[2]:,} carry two or more.\n")

    trades = list(read_jsonl(LEDGER / "recipe_trades.jsonl")) if (LEDGER / "recipe_trades.jsonl").exists() else []
    site_for_pin = sum(1 for t in trades if t.get("kind") == "site_for_pin")
    out.append(f"Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped "
               f'`{{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,'
               f'"residue_without_pin":str,"at":iso,"note":str}}` -- one pin, or two when one is not enough '
               f'(owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not '
               f'a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): '
               f"{site_for_pin:,}.\n")
    dead_init = sum(1 for t in trades if t.get("kind") == "dead_init")
    out.append(f"Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped "
               f'`{{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}}` -- a '
               f"never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling "
               f"2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by "
               f"tools/apply_candidates.py at landing): {dead_init:,}.\n")

    from census import declared_void_callees, void_exact_targets, live_sites, audit_sites
    import census as _census_mod

    def _void_tiers():
        """Tier per symbol in config/void_callees.txt.  The file carries no per-line tier marker
        (checked): tier is read instead from its `# ---- tier A ...` / `# ---- tier B ...`
        section-header comments, the convention docs/L0_BLOCKED_PLAN_20260922.md section 6
        introduced it under."""
        tiers = {}; tier = None
        p = ROOT / "config" / "void_callees.txt"
        if p.exists():
            for line in p.read_text(errors="replace").splitlines():
                s = line.strip()
                if s.startswith("#"):
                    low = s.lower()
                    if "tier a" in low: tier = "A"
                    elif "tier b" in low: tier = "B"
                    continue
                tok = line.split("#", 1)[0].split()
                if tok and _re.fullmatch(r"func_[0-9A-F]{8}", tok[0]):
                    tiers[tok[0]] = tier or "A"
        return tiers

    tiers = _void_tiers()
    tier_a = sum(1 for t in tiers.values() if t == "A")
    tier_b = sum(1 for t in tiers.values() if t == "B")
    tier_drift = set(tiers) ^ declared_void_callees()   # cross-check against the reused census function
    tierB_syms = {s for s, t in tiers.items() if t == "B"}
    tb_rows = []
    if tierB_syms:
        full_void = void_exact_targets()          # census.declared_void_callees() unioned in, both tiers
        reduced_void = full_void - tierB_syms
        for r in rs:
            if r["container"] in PARKED_CONTAINERS: continue
            keys = [f"{r['container']}/{f}" for f in (r.get("defs") or [r["func"]])]
            pt_sites = []
            for k in keys:
                pt_sites += [s for s in audit_sites().get(k, []) if s.startswith("PASSTHRU_NO_ARGS|")]
            if not pt_sites: continue
            cpv = ROOT / "src" / r["container"] / _P(r["c_path"]).name
            pv = cpv if cpv.exists() else ROOT / "raw" / r["container"] / _P(r["c_path"]).name
            if not pv.exists(): continue
            textv = pv.read_text(errors="replace")
            _census_mod._VOID_EXACT_TARGETS = full_void
            live_with = live_sites(textv, pt_sites)
            _census_mod._VOID_EXACT_TARGETS = reduced_void
            live_without = live_sites(textv, pt_sites)
            if not live_with and live_without:    # exempt with tier B, blocked again without it
                tb_rows.append(r)
        _census_mod._VOID_EXACT_TARGETS = full_void   # restore: every other call in this run sees both tiers
    tb_bytes = sum(r["size"] for r in tb_rows)
    out.append(f"Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no "
               f"per-line marker exists): tier A {tier_a}, tier B {tier_b} symbols" +
               (f"; WARNING {len(tier_drift)} symbol(s) differ from `census.declared_void_callees()` -- header "
                f"parse drifted from the file" if tier_drift else " (matches `census.declared_void_callees()`)") +
               f". Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B "
               f"were dropped, tier-A/in-tree exemptions do not cover them): {len(tb_rows)} rows, {tb_bytes:,} B.\n")

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
        resid_n = collections.Counter(); resid_b = collections.Counter()
        for x in read_jsonl(lv):
            if x["id"].split("/")[0] in PARKED_CONTAINERS: continue   # as "Pin sites now": the pins count must equal its row count
            for k in x.get("l4_residue", []):
                resid_n[k] += 1; resid_b[k] += by[x["id"]]["size"]
        out.append(f"\nL4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): "
                   f"pins {resid_n['pins']:,} rows ({resid_b['pins']:,} B), "
                   f"tail_jump {resid_n['tail_jump']:,} rows ({resid_b['tail_jump']:,} B), "
                   f"not_in_module {resid_n['not_in_module']:,} rows ({resid_b['not_in_module']:,} B).")
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
