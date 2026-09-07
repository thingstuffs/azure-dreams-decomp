"""T6: annotate every surviving ASM_* pin with its measured reason.

Uses the T2 journal (greedy erasure verdicts) and the pin census (single-site verdicts) to
write, after each pin statement or register pin, a comment naming the breakage class observed
when that pin was removed.  Comments only: codegen-neutral, still verified by the sweep.
"""
import json, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
NOTE = {
    "reorder-only": "retail schedule: same instructions, different order without it",
    "reg-rename": "retail register colouring depends on it",
    "hold-set": "retail callee-saved set / frame layout depends on it",
    "const-remat": "keeps a constant in a register as retail does",
    "li-expansion": "retail immediate-load split depends on it",
    "addressing": "retail address form (%hi/%lo vs base+offset) depends on it",
    "code-motion": "keeps a statement from moving across a call/branch",
    "length-drift": "retail keeps a copy the compiler would otherwise drop/add",
    "block-order": "retail basic-block layout depends on it",
    "polarity": "retail branch polarity depends on it",
    "slot-rotation": "retail delay-slot fill depends on it",
    "delay-slot": "retail delay-slot contents depend on it",
    "dead-code-retention": "retail keeps a computation the compiler would drop",
    "linked-target": "jump/call target placement depends on it",
    "broad": "load-bearing for the whole function shape",
    "div-guard": "assembler div/rem guard expansion",
}
_idx = None
def index():
    global _idx
    if _idx is None:
        _idx = {}
        p = ROOT / "ledger/sweeps/t2_pins.jsonl"
        if p.exists():
            for l in p.read_text().splitlines():
                j = json.loads(l)
                if j.get("outcome") in ("applied", "noop"):
                    _idx[j["id"]] = [(k[0], k[1], k[2]) for k in (j.get("kept") or [])]
    return _idx

STMT = re.compile(r"^([ \t]*)(ASM_(?!REG\b)[A-Z0-9_]+)\(([^;\n]*)\);[ \t]*$", re.M)
REG = re.compile(r"^([ \t]*register\b[^;\n]*?\bASM_REG\(\"[^\"]*\"\)[^;\n]*;)[ \t]*$", re.M)

class T:
    name = "t6_pin_notes"; level = 5
    @staticmethod
    def eligible(text, row, census):
        if not re.search(r"\bASM_[A-Z0-9_]+\(", text):
            return "no pins"
        if row["id"] not in index():
            return "no T2 verdict yet"
        return None
    @staticmethod
    def apply(text, row, census):
        kept = index()[row["id"]]
        def cls_for(macro, arg):
            for m, a, c in kept:
                if m == macro and (arg or "")[:40].startswith(a[:20]):
                    return c
            return None
        n = 0
        def stmt(m):
            nonlocal n
            if "/*" in m.group(0): return m.group(0)
            c = cls_for(m.group(2), m.group(3).strip())
            if not c: return m.group(0)
            n += 1
            return f"{m.group(0)}   /* MATCH pin: {NOTE.get(c, c)} */"
        out = STMT.sub(stmt, text)
        def reg(m):
            nonlocal n
            if "/*" in m.group(0): return m.group(0)
            r = re.search(r'ASM_REG\("\$?([a-z0-9]+)"\)', m.group(1)).group(1)
            c = cls_for("ASM_REG", r)
            if not c: return m.group(0)
            n += 1
            return f"{m.group(0)}   /* MATCH pin: {NOTE.get(c, c)} */"
        out = REG.sub(reg, out)
        return out if n else None
