#!/usr/bin/env python3
"""loop.c movables per candidate: which `Loop from ... to ...` loops the pass saw and every movable verdict
(moved / not desirable) - one block per text.

    python3 loopsum.py <row> cand1.c [cand2.c ...]

Harvested from r97_opus_a3 (dungeon/func_81989558 1 -> 0): comparing this view between the pinned and the
erased text showed the erasure HOISTED ring*4 out of the inner loop (25 insns vs threshold 29) - the KEEP held a
loop invariant in place.  The fix made the value non-invariant the natural way (a helper parameter set twice in
the loop: consec_sets_invariant_p refuses it).  why.py --pass loop shows the loop count; this shows the movables."""
import argparse
import re
import sys
from pathlib import Path
import kitlib


def summary(loop_dump):
    """Movables and induction decisions, with reduction init locations in final RTL.

    A dump can omit the final RTL. Never invent an init position in that case.
    The compiler's `combined with` target is the base, not the first access.
    """
    kitlib.add_paths()
    from sched_trace import instructions
    rtl = instructions(loop_dump, modes=True)
    out = []
    lines = loop_dump.splitlines()
    for i, ln in enumerate(lines):
        if (ln.startswith("Loop from") or "moved" in ln or "desirable" in ln
                or re.search(r"\bbiv\b|\bBiv\b|\bgiv at\b|dest .* src reg .* benefit|^First use:", ln)):
            out.append(ln)
            if "reduced to" in ln:
                j = i + 1
                while j < len(lines) and lines[j].startswith("    "):
                    out[-1] += " " + lines[j].strip()
                    j += 1
                m = re.search(r"reduced to .*?\(reg:SI (\d+)\)", out[-1])
                if m:
                    reg = m[1]
                    sets = [r for r in rtl if re.match(r"\(set \(reg(?:/\w+)*:SI " + reg + r"\) ", r['pattern'])]
                    # Reduction registers are new pseudos; their first printed set is the init.
                    init = sets[0] if sets else None
                    pos = "init uid %d: %s" % (init['uid'], init['pattern']) if init else "init not present in dump"
                    out.append("  " + pos + "; loop.c:4130-4133 emits at loop_start (LUID-last in its block before sched1); "
                               "sched.c:2469-2472 breaks ties by LUID")
            m = re.search(r"giv at (\d+) combined with giv at (\d+)", ln)
            if m:
                out[-1] += "  [base giv %s: LAST access in compiler's giv chain]" % m[2]
    return out


def main(argv):
    if argv[:1] == ['--dump']:
        ap = argparse.ArgumentParser(description='Summarise an existing .loop dump without compiling')
        ap.add_argument('--dump', type=Path, required=True)
        for ln in summary(ap.parse_args(argv).dump.read_text()):
            print(ln)
        return
    if len(argv) < 2 or not all(a.endswith(".c") for a in argv[1:]):
        raise SystemExit(__doc__)
    kitlib.bootstrap()
    row = kitlib.row_of(argv[0])
    for f in argv[1:]:
        d = kitlib.dumps(row, open(f).read(), want={"loop"})
        if not d or d.get("error"):
            print(f, "ERROR", d and d.get("error"))
            continue
        print("==", f)
        for ln in summary(d["loop"]):
            print("  ", ln)


if __name__ == "__main__":
    main(sys.argv[1:])
