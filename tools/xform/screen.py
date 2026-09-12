"""A free pre-screen for sweep candidates: cc1's assembly, compared with the pinned text's.

The pinned text is byte-exact, so a candidate whose normalised cc1 `.s` differs from the pinned
text's cannot be exact either (every stage after cc1 - maspsx, as, the link - is deterministic in its
input), and needs no scorer run.  Equal assembly is not proof: the candidate is still scored.  From
the fakedep generator lane (work/native_lane/fakedep/gen/hz.py), which screened 712 candidates for 12
scorer runs.

    s0 = compile_s(row, pinned_text); s1 = compile_s(row, candidate); sdiff(s0, s1) == 0 -> score it

Normalisation: only the lines between `.ent` and `.end` (every function in the file), comments and
`#APP`/`#NO_APP` dropped (an empty volatile asm pin leaves nothing else), `.loc/.frame/.mask/.fmask/
.set` dropped, whitespace collapsed, `$L` labels renumbered in order of appearance.  Address
constants are reduced to the halves the assembler emits, so two spellings of one address compare
equal: `li $r,0xNNNN0000` is `lui $r,0xNNNN`; `%hi(D_XXXXXXXX+K)` / `%lo(...)` are the carry-adjusted
halves of that address (the symbol's name IS its address); `addu $r,$s,IMM` is `addiu`.  Measured
2026-09-12 on 177 pairs of byte-exact texts (two landing commits): before, 8 compared unequal - 7 of
them `basesym`/host rewrites that respell an address - and after, only one (a moved `sw $31`).

Assembler-side pins are invisible here: erasing `ASM_SCHED_BARRIER`, `ASM_JALDELAY_PIN`,
`ASM_TAILSLOT_PIN` and the like can leave cc1's listing identical while maspsx's output changes (29
such sites in t26), which costs one scorer run and nothing else.
"""
import difflib, re, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import parse_cfg

INCLUDE = ROOT / "include"


def compile_s(row, text):
    """Normalised cc1 assembly lines for `text` compiled as `row` (None if it does not build)."""
    cell, flags = parse_cfg(row["cfg"])
    D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="screen_") as td:
        d = Path(td)
        f = d / (Path(row["c_path"]).name)
        f.write_text(text)
        r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(INCLUDE), "-w",
                            f.name, "-o", "f.i"], cwd=d, capture_output=True, text=True)
        if r.returncode:
            return None
        r = subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-o", "f.s"], cwd=d,
                           capture_output=True, text=True)
        if r.returncode:
            return None
        src = (d / "f.s").read_text(errors="replace").splitlines()
    out, lab, inside = [], {}, False
    for ln in src:
        s = ln.split("#")[0].strip()
        if s.startswith(".ent"):
            inside = True
            out.append(".ent")
            continue
        if s.startswith(".end"):
            inside = False
            continue
        if not inside or not s or s.startswith((".loc", ".frame", ".mask", ".fmask", ".set")):
            continue
        s = re.sub(r"\s+", " ", s)
        s = re.sub(r"\$L\d+", lambda m: lab.setdefault(m.group(0), "L%d" % len(lab)), s)
        out.append(_addr(s))
    return out


_HILO = re.compile(r"%(hi|lo)\(D_([0-9A-Fa-f]{8})\s*([+-]\s*(?:0x[0-9A-Fa-f]+|\d+))?\)")
_LI = re.compile(r"^li (\$\w+),(-?(?:0x[0-9A-Fa-f]+|\d+))$")
_ADDU_IMM = re.compile(r"^addu (\$\w+),(\$\w+),(-?(?:0x[0-9A-Fa-f]+|\d+))$")


def _halves(v):
    v &= 0xFFFFFFFF
    lo = v & 0xFFFF
    lo = lo - 0x10000 if lo & 0x8000 else lo
    return ((v - lo) >> 16) & 0xFFFF, lo


def _addr(s):
    """One spelling per address constant (see the module docstring)."""
    def hilo(m):
        v = int(m.group(2), 16) + (int(m.group(3).replace(" ", ""), 0) if m.group(3) else 0)
        hi, lo = _halves(v)
        return str(hi) if m.group(1) == "hi" else str(lo)
    s = _HILO.sub(hilo, s)
    m = _LI.match(s)
    if m:
        v = int(m.group(2), 0) & 0xFFFFFFFF
        if v & 0xFFFF == 0:
            return "lui %s,%d" % (m.group(1), v >> 16)
    m = _ADDU_IMM.match(s)
    if m:
        return "addiu %s,%s,%d" % (m.group(1), m.group(2), int(m.group(3), 0))
    return s


def sdiff(a, b):
    """Changed lines between two normalised listings (None if either failed to build)."""
    if a is None or b is None:
        return None
    return sum(1 for x in difflib.unified_diff(a, b, lineterm="", n=0)
               if x[:1] in "+-" and not x.startswith(("+++", "---")))
