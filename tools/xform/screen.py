"""A free pre-screen for sweep candidates: cc1's assembly, compared with the pinned text's.

The pinned text is byte-exact, so a candidate whose normalised cc1 `.s` differs from the pinned
text's cannot be exact either (every stage after cc1 - maspsx, as, the link - is deterministic in its
input), and needs no scorer run.  Equal assembly is not proof: the candidate is still scored.  From
the fakedep generator lane (work/native_lane/fakedep/gen/hz.py), which screened 712 candidates for 12
scorer runs.

    s0 = compile_s(row, pinned_text); s1 = compile_s(row, candidate); sdiff(s0, s1) == 0 -> score it

Normalisation: only the lines between `.ent` and `.end` (every function in the file), comments and
`#APP`/`#NO_APP` dropped (an empty volatile asm pin leaves nothing else), `.loc/.frame/.mask/.fmask/
.set` dropped, whitespace collapsed, `$L` labels renumbered in order of appearance.
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
        out.append(s)
    return out


def sdiff(a, b):
    """Changed lines between two normalised listings (None if either failed to build)."""
    if a is None or b is None:
        return None
    return sum(1 for x in difflib.unified_diff(a, b, lineterm="", n=0)
               if x[:1] in "+-" and not x.startswith(("+++", "---")))
