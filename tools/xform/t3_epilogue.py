"""T3a: LABEL_AS_CALL epilogue sites -> `return`.  RETIRED 2026-09-08: superseded by t10_epilogue
(its in_row() knew only the rowbase address and matched 0 of 650 rows; its index() was not thread-safe).

m2c renders a `j <own epilogue>` as a call to a pseudo-function declared noreturn; the
assembler stage turns that jal into the retail `j`.  The honest C is `return;` (or `return v;`
when the audit knows what v0 held).  All epilogue sites of a row are rewritten together; the
sweep verifies the result.  Mid-row and other-row sites are left for a later transform.
Audit source: ledger/cache/audit.json (tools/census/gaps/decomp_audit.py --json).
"""
import json, re
from pathlib import Path
AUDIT = Path(__file__).resolve().parents[2] / "ledger/cache/audit.json"
_idx = None

def index():
    global _idx
    if _idx is None:
        d = json.load(open(AUDIT))
        _idx = {}
        for r in d["records"]:
            if r["cls"] == "LABEL_AS_CALL":
                _idx.setdefault((r["container"], r["row_key"]), []).append(r)
    return _idx

def in_row(row, target):
    """An epilogue jump is the row's own only if the target lies inside the row's extent; a jump
    to a resident or foreign tail must stay a call (the linked bytes differ, even though a
    per-row relocation-normalised compare cannot see it)."""
    try:
        vram = int(row["func"][5:], 16); tgt = int(target[5:], 16)
    except (TypeError, ValueError):
        return False
    return vram <= tgt < vram + row["size"]

def sites_for(row):
    idx = index()
    keys = [(row["container"], f) for f in (row.get("defs") or [row["func"]])]
    return [s for k in keys for s in idx.get(k, []) if in_row(row, s["target"])]

class T:
    name = "t3_epilogue"; level = 1
    @staticmethod
    def eligible(text, row, census):
        ep = [s for s in sites_for(row) if s["kind"] == "epilogue"]
        if not ep:
            return "no epilogue LABEL_AS_CALL site"
        return None
    @staticmethod
    def apply(text, row, census):
        ep = [s for s in sites_for(row) if s["kind"] == "epilogue"]
        cur = text; n = 0
        for s in ep:
            tgt = s["target"]
            # the defining function's return type decides `return;` vs `return v;`
            m = re.search(r"^[ \t]*([A-Za-z_][A-Za-z0-9_ \*]*?)\b\**(func_[0-9A-F]{8}|[a-z_][a-z0-9_]*)\s*\([^;{]*\)\s*\{", cur, re.M)
            rtype = (m.group(1).strip() if m else "void")
            v0 = str(s.get("v0") or "")
            if rtype == "void" or v0 in ("", "-", "?", "None"):
                repl = "return;"
            elif v0.startswith("imm:"):
                repl = f"return {v0[4:]};"
            else:
                repl = None      # v0 comes from a register/call we cannot name: only the drop rule applies
            # (a) pseudo-call immediately followed by a return: the return already says it all
            drop = re.compile(r"^[ \t]*" + re.escape(tgt) + r"\(\s*\);[ \t]*\n(?=[ \t]*return\b)", re.M)
            cur, k = drop.subn("", cur)
            n += k
            # (b) otherwise the pseudo-call becomes the return
            if repl is not None:
                call = re.compile(r"^([ \t]*)" + re.escape(tgt) + r"\(\s*\);[ \t]*\n", re.M)
                cur, k = call.subn(lambda mm: mm.group(1) + repl + "\n", cur)
                n += k
            if k and not re.search(r"\b" + re.escape(tgt) + r"\s*\(", re.sub(r"^.*__attribute__\(\(noreturn\)\).*$", "", cur, flags=re.M)):
                cur = re.sub(r"^extern\s+[^\n]*\b" + re.escape(tgt) + r"\s*\([^\n]*noreturn[^\n]*\n", "", cur, flags=re.M)
        # `return;` immediately followed by another `return;` at the same depth is redundant
        cur = re.sub(r"([ \t]*)return;\n\1return;\n", r"\1return;\n", cur)
        return cur if n else None
