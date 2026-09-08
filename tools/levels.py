#!/usr/bin/env python3
"""Derive each row's cleanliness level from the current clean tree -> ledger/levels.jsonl.

L0 verified exact at the pin.  L1 no boilerplate, dead pins erased (t2 journalled), no blocking
fidelity site and no pseudo-call to a label inside the row (whether or not the baseline audit
listed it).  L2 also no M2C_FIELD.  L3 a Layer-2 pass journalled (locals/comments).  L4 in a
module with a shared header.  L5 STRICT: no ASM_* pin or marker, no noreturn tail-call spelling,
no fidelity site of ANY audit class, no computed-goto table, no inline asm, no NON_MATCHING guard.
A row that cannot reach L5 stays at L4 with its residue documented; `l5_residue` names what is left.
"""
import re, collections
from pathlib import Path
from common import ROOT, LEDGER, rows, read_jsonl, write_jsonl, raw_path
from census import PIN_RE, M2C_LOCAL_RE, audit_index, live_audit

def intra_tail_calls(r, text):
    """Pseudo-calls to a label inside the row's own extent, whether or not the baseline audit listed
    them: a noreturn-declared or asm-aliased func_ target whose address lies in [true base, +size)
    and which the text still calls (declarations excluded)."""
    m = re.match(r"func_([0-9A-F]{8})$", r.get("true_name") or r["func"] or "")
    if not m or r["kind"] != "overlay": return 0
    base = int(m.group(1), 16); end = base + r["size"]
    targets = set(re.findall(r"\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*__attribute__\s*\(\s*\(\s*noreturn", text))
    targets |= set(re.findall(r"(?:asm|__asm__)\s*\(\s*\"(func_[0-9A-F]{8})\"\s*\)", text))
    n = 0
    for tgt in targets:
        v = int(tgt[5:], 16)
        if base <= v < end and re.search(r"^[ \t]*(?:return[ \t]+)?" + re.escape(tgt) + r"\s*\(", text, re.M):
            n += 1
    return n

def main():
    promoted = {j["id"] for j in read_jsonl(LEDGER / "promotions.jsonl") if j.get("outcome") == "landed"} if (LEDGER / "promotions.jsonl").exists() else set()
    try:
        from evidence import EV as _EV
        _ev = {e["id"]: [k for k in ("assert_sites", "identifiers", "adrando", "data", "vm", "knowledge", "name") if e.get(k)] for e in read_jsonl(_EV / "rows.jsonl")} if (_EV / "rows.jsonl").exists() else {}
    except Exception:
        _ev = {}
    base = {b["id"]: b for b in read_jsonl(LEDGER / "baseline.jsonl")}
    sweeps = {}
    for p in (LEDGER / "sweeps").glob("*.jsonl"):
        sweeps[p.stem] = {j["id"]: j for j in read_jsonl(p) if j.get("outcome") in ("applied", "noop")}
    audit = audit_index()
    out = []; tally = collections.Counter()
    for r in rows():
        b = base.get(r["id"], {})
        l0 = r["stock"] and (b.get("exact") is True or (r["kind"] == "slus" and b.get("status") == "ok"))
        if not l0:
            out.append({"id": r["id"], "level": -1}); tally[-1] += r["size"]; continue
        cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
        text = (cp if cp.exists() else raw_path(r)).read_text(errors="replace")
        raw_text = raw_path(r).read_text(errors="replace") if raw_path(r).exists() else ""
        keys = [f"{r['container']}/{f}" for f in (r.get("defs") or [r["func"]])]
        live = live_audit(r, text)                                                       # live: a removed site no longer blocks
        blocking = any(k2 in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS") for k2 in live) or intra_tail_calls(r, text) > 0
        any_site = bool(live)
        pins = len(PIN_RE.findall(text))
        tail_idiom = len(re.findall(r"__attribute__\s*\(\s*\(\s*noreturn\s*\)\s*\)", text)) + len(re.findall(r"\b(?:asm|__asm__)\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)", text))
        computed_goto = len(re.findall(r"\bgoto\s*\*", text)); inline_asm = len(re.findall(r"__asm__|\basm\s*\(", re.sub(r"\bASM_[A-Z0-9_]+\(", "", text)))
        boiler = "This header contains macros emitted by m2c" in text or "typedef float f32;" in text
        level = 0
        if not boiler and (pins == 0 or r["id"] in sweeps.get("t2_pins", {})) and not blocking:
            level = 1
            if not re.search(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#"))):
                level = 2
                if r["id"] in promoted and text != raw_text:   # a landed Layer-2 body is the src text (ledger/promotions.jsonl)
                    level = 3
                    if r["id"] in sweeps.get("l4_modules", {}):
                        level = 4
                        # L5 is strict: no scaffolding of any kind and no fidelity site of any audit class.
                        # A row that cannot get there stays at L4 with each residue documented (T6 notes).
                        if pins == 0 and tail_idiom == 0 and not any_site and computed_goto == 0 and inline_asm == 0 and "NON_MATCHING" not in text:
                            level = 5
        recs = sorted(set(re.findall(r'#include "records/(Rec_[A-Za-z0-9_]+)\.h"', text)))
        out.append({"id": r["id"], "level": level, "evidence": _ev.get(r["id"], []), "pins_left": pins, "m2c_field": len(re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#")))), "blocking": blocking, "records": recs,
                    "l5_residue": [k for k, v in (("pins", pins), ("tail_call", tail_idiom), ("fidelity_site", int(any_site)), ("computed_goto", computed_goto), ("inline_asm", inline_asm), ("non_matching", int("NON_MATCHING" in text))) if v]}); tally[level] += r["size"]
        if recs: tally["records"] += r["size"]; tally["records_rows"] += 1
    write_jsonl(LEDGER / "levels.jsonl", out)
    tot = sum(r["size"] for r in rows())
    for l in sorted(k for k in tally if isinstance(k, int)): print(f"L{l}: {tally[l]:,} B ({100*tally[l]/tot:.1f}%)")
    print(f"on shared record headers (T7): {tally['records_rows']} rows, {tally['records']:,} B ({100*tally['records']/tot:.1f}%)")

if __name__ == "__main__":
    main()
