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
    # What earlier searches learned about this row's pins (tools/pin_evidence.py): a byte-exact
    # removal the project declined because the price was a fake dependency.  It names the value a
    # pin orders, so the next pass does not re-derive it - and does not re-land the fake.
    try:
        from pin_evidence import for_row
        ev = for_row(row["id"], text)
    except Exception:
        ev = []
    for r in ev[:6]:
        where = r.get("where") or (f"site {r['site']} `{r['macro']}({r['arg']})` (line {r['line']})"
                                   if r.get("macro") else "this row")
        if not r.get("current", True):
            where += " on an earlier text - match it by the names, the numbering may have moved"
        verdict = r["verdict"]
        if r.get("reproduced") is False:
            verdict += " - BUT it did NOT reproduce when re-checked on this text, so treat it as a weak hint"
        elif r.get("reproduced") is None:
            verdict += " (found as part of a multi-step search; not re-checked on its own)"
        lines.append(f"- PIN EVIDENCE ({r['found_by']}): {where}: {r['hint']}.  {verdict}.  "
                     "Read it as a map of WHICH value the pin orders, not as an answer: look for the "
                     "natural C that creates that dependency (a real second use of the value, the "
                     "same statement written in both arms, one variable reused for two jobs).  The "
                     "fake construct itself is scaffolding and is counted as debt.")
    if len(ev) > 6:
        lines.append(f"- ({len(ev) - 6} more evidence records: python3 tools/pin_evidence.py {row['id']})")
    if row.get("true_name"):
        lines.append("- SCORING: this row has a recorded true name, so the per-row scorer links it "
                     "exactly where the window gate does - they agree, and every word of the "
                     "residue is real.  verify.py's caveat about a corrected internal jump being "
                     "unscoreable applies ONLY to rows with NO true name, which link at a synthetic "
                     "address; do not reach for it here.  (A lane recorded five rows as provably "
                     "unfixable on that basis; all five had a true name and `gate_candidate` "
                     "answers `not needed: scorer and gate agree`.)")
    else:
        lines.append("- SCORING: this row has NO recorded true name, so the scorer links it at its "
                     "true base while the gate links it at a synthetic address.  A rewrite that "
                     "respells an internal jump can be scorer-exact and wrong in the window, or "
                     "right in the window and unscoreable - the WINDOW is the authority, so prove "
                     "such a candidate with tools/verify.py --gate.")
    # STOP-RULE.  A length-drift lane hit this in 4 of 12 rows: when the residue is a single word
    # that is `jal` on one side and `j` on the other, next to a call to a noreturn-declared symbol,
    # the difference is maspsx's automatic tail-jump conversion (LEAD 18/22) - and that conversion
    # is strictly ZERO-ARGUMENT gated.  Giving the call a real argument, which is usually what the
    # address bytes need, permanently disqualifies it.  The conversion and its companion delay-slot
    # sink are assembler-side and pin-gated; no C reshaping reproduces them.
    jalj = False
    for line in (regions_text or "").splitlines():
        if "|" in line:
            l, _, r = line.partition("|")
            lw, rw = l.strip().split(), r.strip().split()
            if lw and rw and {lw[0], rw[0]} == {"jal", "j"}:
                jalj = True
    if jalj and re.search(r"__attribute__\s*\(\s*\(\s*noreturn", text):
        lines.append("- STOP: the residue is a `jal` against retail's `j` beside a noreturn call. "
                     "That is maspsx's automatic tail-jump conversion, which fires ONLY for a "
                     "zero-argument call - and giving the call the argument its address bytes need "
                     "permanently disqualifies it - UNLESS the callee is on the arg-carrying "
                     "sibcall set (LEAD 22, config/sibcall_syms.txt), whose whole purpose is to "
                     "convert an arg-carrying tail call.  Check both lists before believing this: "
                     "if the callee is on neither, it is assembler-side and pin-gated and no C "
                     "shape reproduces it, and the row should be recorded rather than worked.  "
                     "Note the sibcall set is derived from MAIN.BIN only, so a dungeon callee "
                     "may be missing from it for want of evidence rather than by nature.")
    got, tgt, has_arg = residue_registers(regions_text)
    if got or tgt:
        lines.append(f"- residue registers: yours {sorted(got) or '-'}, retail's {sorted(tgt) or '-'}")
        if not has_arg:
            lines.append("- none of them is an argument register ($a0-$a3), so an under-declared "
                         "callee taking the value as a parameter is ruled out without a probe")
        # A `broad` lane measured this as a selector, 2/2 one way and 0/5 the other.
        if tgt > got:
            lines.append("- RETAIL'S SET IS A STRICT SUPERSET of yours: retail keeps one more value "
                         "live.  FOLD THE LOAD - inline the loaded value directly into every "
                         "consuming expression instead of storing it to a named intermediate.  That "
                         "recovered the missing register on both rows a lane tried it on.")
        elif got == tgt and got:
            lines.append("- THE TWO SETS ARE EQUAL: same registers, different roles - a "
                         "hard-register tie.  One lane moved not a single word on five such rows, "
                         "so this RANKS A ROW LAST; it is not a verdict.  Two independent lanes "
                         "broke it on dungeon/func_8132C638 (2026-09-10) by changing the MODE "
                         "rather than the variable map: the accumulator was declared `u16` instead "
                         "of `u32` with an explicit `& 0xFFFF`, so the mask combine had folded away "
                         "came back as the widening u16->s32 at the RETURN, which combine cannot "
                         "delete.  Try the mode change on the value the residue names before you "
                         "spend the rest of the budget elsewhere.")
    return "\n".join(lines)


if __name__ == "__main__":
    from common import rows, clean_path
    want = sys.argv[1]
    for r in rows():
        if r["id"] == want:
            print(facts(r, clean_path(r).read_text(errors="replace")))
            break
