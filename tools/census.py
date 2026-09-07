#!/usr/bin/env python3
"""Static census of every row's C at the pin -> ledger/census.jsonl (one record per row)."""
import json, re, collections
from pathlib import Path
from common import ROOT, LEDGER, rows, write_jsonl, raw_path

PIN_RE = re.compile(r"\bASM_([A-Z0-9_]+)\(")
REG_RE = re.compile(r'ASM_REG\("\$?([a-z0-9]+)"\)')
M2C_LOCAL_RE = re.compile(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+|phi_[a-z0-9_]+)\b")
LOCAL_STRUCT_RE = re.compile(r"\b((?:S_|Struct|Func)[0-9A-F]{7,8}[A-Za-z0-9_]*)\b")
CALL_RE = re.compile(r"\b(func_[0-9A-F]{8})\s*\(")
DATA_RE = re.compile(r"\b(D_[0-9A-F]{8})\b")
LABEL_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*:\s*(?://.*|/\*.*)?$", re.M)
DEF_RE = re.compile(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8})\s*\(", re.M)

def audit_index():
    d = json.load(open(ROOT / "config/decomp_audit_baseline.json"))
    idx = {}
    for key, v in d.get("sites", {}).items():
        c = collections.Counter(s.split("|")[0] for s in v.get("sites", []))
        idx[key] = dict(c)
    return idx

def census_one(row, audit):
    p = raw_path(row)
    if not p.exists():
        return {"id": row["id"], "missing": True}
    text = p.read_text(errors="replace")
    body = text
    defs = set(DEF_RE.findall(text))
    pins = collections.Counter(PIN_RE.findall(text))
    regs = collections.Counter(REG_RE.findall(text))
    labels = [l for l in LABEL_RE.findall(text) if l not in ("default", "case")]
    keys = [f"{row['container']}/{f}" for f in (row.get("defs") or [row["func"]])]
    aud = collections.Counter()
    for k in keys:
        aud.update(audit.get(k, {}))
    rec = {
        "id": row["id"], "lines": text.count("\n"), "chars": len(text),
        "boiler": "This header contains macros emitted by m2c" in text or "typedef float f32;" in text,
        "m2c_field": len(re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#")))),
        "pins": dict(pins), "pin_total": sum(pins.values()), "pin_regs": dict(regs),
        "gotos": len(re.findall(r"\bgoto\s+[A-Za-z_]", text)), "computed_goto": len(re.findall(r"\bgoto\s*\*", text)),
        "labels": len(labels), "jt_keep": "jt_keep" in text or "&&" in text,
        "m2c_locals": len(set(M2C_LOCAL_RE.findall(text))),
        "local_structs": sorted(set(LOCAL_STRUCT_RE.findall(text)))[:12],
        "n_local_structs": len(set(LOCAL_STRUCT_RE.findall(text))),
        "externs": len(re.findall(r"^extern\b", text, re.M)),
        "calls": sorted(set(CALL_RE.findall(text)) - defs), "data": sorted(set(DATA_RE.findall(text))),
        "nonmatching": "NON_MATCHING" in text,
        "inline_asm": len(re.findall(r"__asm__|\basm\s*\(", text)), "include_asm": "INCLUDE_ASM(" in text,
        "noreturn": text.count("noreturn"), "register_decls": len(re.findall(r"\bregister\b", text)),
        "volatile": text.count("volatile"), "switch": len(re.findall(r"\bswitch\s*\(", text)),
        "audit": dict(aud), "ndefs": len(defs),
    }
    return rec

def main():
    audit = audit_index()
    rs = rows()
    recs = [census_one(r, audit) for r in rs]
    write_jsonl(LEDGER / "census.jsonl", recs)
    by = {r["id"]: r for r in rs}
    tot = collections.Counter(); B = collections.Counter()
    for c in recs:
        if c.get("missing"): continue
        sz = by[c["id"]]["size"]
        for k, cond in (("boiler", c["boiler"]), ("m2c_field", c["m2c_field"] > 0), ("pins", c["pin_total"] > 0),
                        ("gotos", c["gotos"] > 0), ("computed_goto", c["computed_goto"] > 0), ("m2c_locals", c["m2c_locals"] > 0),
                        ("local_structs", c["n_local_structs"] > 0), ("nonmatching", c["nonmatching"]), ("inline_asm", c["inline_asm"] > 0),
                        ("audit_blocking", any(k2 in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS") for k2 in c["audit"])),
                        ("audit_any", bool(c["audit"])), ("clean_shape", not c["boiler"] and c["m2c_field"] == 0 and c["pin_total"] == 0 and c["gotos"] == 0 and c["m2c_locals"] == 0)):
            if cond: tot[k] += 1; B[k] += sz
    print(f"{'defect':16} {'files':>6} {'bytes':>9}")
    for k in ("boiler", "m2c_field", "m2c_locals", "pins", "gotos", "computed_goto", "local_structs", "nonmatching", "inline_asm", "audit_blocking", "audit_any", "clean_shape"):
        print(f"{k:16} {tot[k]:6d} {B[k]:9d}")

if __name__ == "__main__":
    main()
