"""T128: a `void` function that returned a value - the return register is live at the exit (dbr fact).

APPEARS     a pin whose lone erasure changes ONLY a branch delay slot (sched2 identical): reorg.c:3257
            fill_slots_from_thread skips a fall-through insn that sets a register live at the branch target.  At an
            exit branch, `$2` is live there only when the function returns a value - retail's function was non-void
            (its callers ignored the result), and the pin imitated the skipped `lui $2`/`li $2` slot choice.
            r80_opus_cl_move: dungeon/func_800AC914 1 -> 0 with `void` -> `s32` and no return statement.
RESOLVES    the definition's `void` return type -> `s32`, jointly with ONE pin erased (each pin tried, last first);
            a file-local `void` prototype of the same function is rewritten too.  No return statement is added
            (gcc 2.x accepts falling off the end of a non-void function; the bytes decide).
ACCEPTANCE  exact, pins strictly fall.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
from pin_sites import erase_many

MAX_VERIFY = int(os.environ.get("T128_MAX", "12"))
DEF = re.compile(r"^(static\s+)?void(\s+)(func_[0-9A-Fa-f]{8}|\w+)(\s*\([^;{]*\)\s*\{)", re.M)


def retyped(text):
    """text with the (single) void function definition made `s32` (and its local prototypes), or None."""
    defs = list(DEF.finditer(text))
    if len(defs) != 1:
        return None
    m = defs[0]; name = m.group(3)
    t = text[:m.start()] + (m.group(1) or "") + "s32" + m.group(2) + name + m.group(4) + text[m.end():]
    t = re.sub(r"^((?:extern\s+|static\s+)?)void(\s+%s\s*\([^;{]*\)\s*;)" % re.escape(name), r"\1s32\2", t, flags=re.M)
    return t


class T:
    name = "t128_nonvoid"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin"
        return None if retyped(text) else "no single void definition"

    @staticmethod
    def apply_verified(text, row, census, vf):
        base = retyped(text)
        if base is None:
            return None, {"refused": ["no single void definition"]}
        n0 = len(sites_of(text)); tried = [0]
        for s in sorted(sites_of(base), key=lambda s: -s[3]):
            if tried[0] >= MAX_VERIFY:
                break
            cand = erase_many(base, [s], clean_notes=True)
            if len(sites_of(cand)) >= n0:
                continue
            tried[0] += 1
            if vf(cand).get("exact"):
                return cand, {"erased": s[1], "line": s[5], "verifies": tried[0]}
        return None, {"refused": ["no exact non-void + one-pin erasure (%d verifies)" % tried[0]]}
