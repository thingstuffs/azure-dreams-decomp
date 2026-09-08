"""T6: annotate every surviving ASM_* pin as an UNRESOLVED C shape with the measured effect of removing it.

The note is not a justification: every pin stands for a source shape nobody has found (measured
against the shipped toolchain, docs/FIDELITY.md); the note records what breaks when it is erased.

Uses the T2 journal (greedy erasure verdicts) and the pin census (single-site verdicts) to
write, after each pin statement or register pin, a comment naming the breakage class observed
when that pin was removed.  Comments only: codegen-neutral, still verified by the sweep.
"""
import json, re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
NOTE = {
    "reorder-only": "reorders the instructions (same instructions, different order)",
    "reg-rename": "changes the register colouring",
    "hold-set": "changes the callee-saved set / frame layout",
    "const-remat": "rematerialises a constant retail keeps in a register",
    "li-expansion": "changes the immediate-load split",
    "addressing": "changes the address form (%hi/%lo vs base+offset)",
    "code-motion": "moves a statement across a call/branch",
    "length-drift": "changes the instruction count (a copy retail keeps is dropped or added)",
    "block-order": "changes the basic-block layout",
    "polarity": "flips a branch polarity",
    "slot-rotation": "changes a delay-slot fill",
    "delay-slot": "changes a delay-slot's contents",
    "dead-code-retention": "drops a computation retail keeps",
    "linked-target": "moves a jump/call target",
    "broad": "changes the whole function shape",
    "div-guard": "changes the assembler div/rem guard expansion",
}
PREFIX = "UNRESOLVED C shape (pin): removing it"
SUFFIX = "; the source shape that makes it unnecessary has not been found"
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
            return f"{m.group(0)}   /* {PREFIX} {NOTE.get(c, c)}{SUFFIX} */"
        out = STMT.sub(stmt, text)
        def reg(m):
            nonlocal n
            if "/*" in m.group(0): return m.group(0)
            r = re.search(r'ASM_REG\("\$?([a-z0-9]+)"\)', m.group(1)).group(1)
            c = cls_for("ASM_REG", r)
            if not c: return m.group(0)
            n += 1
            return f"{m.group(0)}   /* {PREFIX} {NOTE.get(c, c)}{SUFFIX} */"
        out = REG.sub(reg, out)
        return out if n else None
