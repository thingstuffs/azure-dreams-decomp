#!/usr/bin/env python3
"""Derive each row's cleanliness level from the current clean tree -> ledger/levels.jsonl.

L0 verified exact at the pin.  L1 no boilerplate, dead pins erased (t2 journalled), no blocking
fidelity site.  L2 also no M2C_FIELD.  L3 a Layer-2 pass journalled (locals/comments).  L4 in a
module with a shared header.  L5 pin-free or every pin documented.
"""
import re, collections
from pathlib import Path
from common import ROOT, UP, LEDGER, rows, read_jsonl, write_jsonl
from census import PIN_RE, M2C_LOCAL_RE, audit_index

def main():
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
        text = (cp if cp.exists() else UP / r["c_path"]).read_text(errors="replace")
        keys = [f"{r['container']}/{f}" for f in (r.get("defs") or [r["func"]])]
        blocking = any(k2 in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS") for k in keys for k2 in audit.get(k, {}))
        pins = len(PIN_RE.findall(text))
        boiler = "This header contains macros emitted by m2c" in text or "typedef float f32;" in text
        level = 0
        if not boiler and (pins == 0 or r["id"] in sweeps.get("t2_pins", {})) and not blocking:
            level = 1
            if not re.search(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#"))):
                level = 2
                if (ROOT / "refine" / r["container"] / Path(r["c_path"]).name).exists():
                    level = 3
                    if r["id"] in sweeps.get("l4_modules", {}):
                        level = 4
                        if pins == 0 or r["id"] in sweeps.get("l5_pins_documented", {}):
                            level = 5
        out.append({"id": r["id"], "level": level, "pins_left": pins, "m2c_field": len(re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#")))), "blocking": blocking}); tally[level] += r["size"]
    write_jsonl(LEDGER / "levels.jsonl", out)
    tot = sum(r["size"] for r in rows())
    for l in sorted(tally): print(f"L{l}: {tally[l]:,} B ({100*tally[l]/tot:.1f}%)")

if __name__ == "__main__":
    main()
