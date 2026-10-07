#!/usr/bin/env python3
"""loop.c movables per candidate: which `Loop from ... to ...` loops the pass saw and every movable verdict
(moved / not desirable) - one block per text.

    python3 loopsum.py <row> cand1.c [cand2.c ...]

Harvested from r97_opus_a3 (dungeon/func_81989558 1 -> 0): comparing this view between the pinned and the
erased text showed the erasure HOISTED ring*4 out of the inner loop (25 insns vs threshold 29) - the KEEP held a
loop invariant in place.  The fix made the value non-invariant the natural way (a helper parameter set twice in
the loop: consec_sets_invariant_p refuses it).  why.py --pass loop shows the loop count; this shows the movables."""
import sys
import kitlib


def summary(loop_dump):
    """The `Loop from` headers and the movable verdict lines of a .loop dump, in order."""
    return [ln for ln in loop_dump.splitlines()
            if ln.startswith("Loop from") or "moved" in ln or "desirable" in ln]


def main(argv):
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
            print("  ", ln[:150])


if __name__ == "__main__":
    main(sys.argv[1:])
