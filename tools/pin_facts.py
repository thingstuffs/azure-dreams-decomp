#!/usr/bin/env python3
"""The facts about a row that a lane must not have to re-derive.

Four separate lanes independently concluded that a value stored before a call to a
`__attribute__((noreturn))` symbol is provably dead, and closed 0 rows on that basis.  The C they
were handed says "call"; retail has a plain `j` to a label inside the same function, so the value
is live.  The project could already tell them - `agent_task.fidelity_facts` identifies exactly that
case mechanically, and the fidelity census flags 25 of the 27 affected rows - but nothing wired it
into the pin packs or the depin prompt.

So this module is the one place that assembles what a pin lane needs before it forms a hypothesis:

  * the row's true link name, size and compiler cell - the landing word of any internal jump is
    counted from the true name, not from the file's own name;
  * every LABEL_AS_CALL / PASSTHRU_NO_ARGS site, with the inside-or-outside verdict computed from
    the addresses rather than read off the declaration;
  * whether a proven rowbase region covers the row, which decides whether a rewrite may introduce
    a new intra-function `j` at all;
  * which registers the residue actually involves, and whether they are argument registers -
    three lanes worked that out by hand to rule out the "under-declared callee" hypothesis, and
    two of them spent a lane's budget doing it.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

ARGREGS = {"a0", "a1", "a2", "a3"}
REG_RE = re.compile(r"\$(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra)\b")


def residue_registers(regions_text):
    """(registers named on each side, whether any is an argument register).

    The "retail keeps a value we delete" hypothesis has an obvious candidate cure - the callee is
    under-declared and really takes the value as a parameter - and it is worth exactly one glance:
    MIPS o32 passes integer arguments only in $a0-$a3, so a residue that never touches one cannot
    be an argument.  Saying so up front costs nothing and has already saved two lanes a budget.
    """
    got, tgt = set(), set()
    for line in (regions_text or "").splitlines():
        if "|" in line:
            l, _, r = line.partition("|")
            got |= {m.group(1) for m in REG_RE.finditer(l)}
            tgt |= {m.group(1) for m in REG_RE.finditer(r)}
    return got, tgt, bool((got | tgt) & ARGREGS)


SUBBASE_RE = re.compile(
    r"^[ \t]*(?P<n>[A-Za-z_]\w*)\s*=\s*\(?[^;=]*?\b(?P<base>[A-Za-z_]\w*)\s*\+\s*(?P<k>0x[0-9A-Fa-f]+|\d+)\s*\)?\s*;\s*$",
    re.M)


def single_use_subbase(text):
    """Names the `T *sub = base + K; sub->f = v;` shape that combine folds away.

    An addressing lane found this in 5 of its 9 rows and could not move it with any of ~15 C
    shapes: gcc sees the `addiu`'s result has exactly one reaching use, folds
    PLUS(PLUS(base,K1),K2) into PLUS(base,K1+K2) and deletes it.  The fold is dataflow-driven, so
    statement order, `register`, `do{}while(0)`, algebraically-identical second sets and
    struct-member versus raw-cast spellings are all provably inert.  Only a CALL_INSN between the
    definition and the use blocks it, and that forces the value into a callee-saved register,
    which is not what retail does.  Saying so up front stops the next lane spending its budget on
    the same fifteen shapes.
    """
    out = []
    for m in SUBBASE_RE.finditer(text):
        n = m.group("n")
        if len(re.findall(r"\b%s\b" % re.escape(n), text)) == 2:
            out.append(f"{n} = {m.group('base')} + {m.group('k')}")
    return out


def facts(row, text, regions_text=""):
    """The block a lane packet carries for one row."""
    lines = []
    try:
        from agent_task import fidelity_facts
        lines.append(fidelity_facts(row, text))
    except Exception as e:                      # never let a facts failure cost a lane its packet
        tb = row.get("true_name") or row["func"]
        lines.append(f"- row {row['id']}: defined as {tb}, {row['size']} bytes, cell {row['cfg']}"
                     f"  (fidelity facts unavailable: {e!r})")
    for sb in single_use_subbase(text)[:4]:
        lines.append(f"- SINGLE-USE SUB-BASE `{sb}`: gcc folds this offset into its one use and "
                     "deletes the addiu.  Statement order, `register`, do{}while(0), "
                     "algebraically-identical second sets and struct-vs-cast spellings are all "
                     "MEASURED INERT on this shape (~15 tried).  Do not spend budget re-walking "
                     "them; only a call between the definition and the use blocks the fold, and "
                     "that puts the value in a callee-saved register, which is not retail's shape.")
    got, tgt, has_arg = residue_registers(regions_text)
    if got or tgt:
        lines.append(f"- residue registers: yours {sorted(got) or '-'}, retail's {sorted(tgt) or '-'}")
        if not has_arg:
            lines.append("- none of them is an argument register ($a0-$a3), so an under-declared "
                         "callee taking the value as a parameter is ruled out without a probe")
    return "\n".join(lines)


if __name__ == "__main__":
    from common import rows, clean_path
    want = sys.argv[1]
    for r in rows():
        if r["id"] == want:
            print(facts(r, clean_path(r).read_text(errors="replace")))
            break
