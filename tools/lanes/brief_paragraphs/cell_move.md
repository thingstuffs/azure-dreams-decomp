## CELL-MOVE LANE (round 80): these rows are registered at the WRONG compiler cell

Every row in this pack is a toolchain-fidelity **step-4 candidate** (docs/evidence/fidelity_step2_split_fingerprint.md,
docs/evidence/fidelity_step4_candidates.tsv): it is registered at a NON-splitting cell (2.6.3 / FSF 2.7.2), but its
RETAIL bytes carry the split-address fingerprint (a `lui` scheduled away from its `%lo` user, `%lo` into another
register, a HIGH shared by several users, a HIGH in a delay slot) that only a splitting compiler emits
(2.7.2-cdk `-mgas`, 2.8.x). Its module's census recipe is the TARGET cell given per row in `rows.md` ("target").
Most of this row's pins exist to make the WRONG compiler imitate the right one: page constants held in registers,
`ASM_KEEP` on addresses, hard-register `lui` values. Earlier lanes worked these rows at the registered cell and
plateaued - that is why.

**Work at the target cell, for everything.** Every `lab.py` / `diff.py` / `why.py` / `dump.py` call takes
`--cfg "<target>"` (lab.py: `python3 <kit>/lab.py <row> cand.c --score --cfg "<target>"`). Write the function as the
original programmer would: real symbols instead of integer pages (`extern` arrays/structs at their addresses, the
shared types in include/shared/ where they fit), plain locals, no register imitation. At the splitting cell the
compiler produces the split HIGH/LO pairs itself. Then remove the remaining pins at that cell as usual.

**Staging (lab.py does NOT stage at a foreign cfg - it prints a hand-over line instead):** when a candidate is exact at
the target (`exact: true` from `lab.py ... --score --cfg "<target>"`, re-checked with
`python3 <repo>/tools/verify.py <row> <abs path> --cfg "<target>"` if that flag exists, else trust lab.py), copy it
to `out/<container>/<name>.c`, copy `base/<container>/<name>.c.base_sha` next to it as `<name>.c.base_sha`, and append
ONE line per row to `cells.jsonl` in the lane directory:

    {"id": "<row>", "to": "<target cfg>", "coherence": "retail split-address fingerprint; module census <target>; <one line: what changed>", "pins_before": N, "pins_after": M}

Stage the best candidate per row (fewest pins; a candidate with the SAME pins is still worth staging when it is
exact at the target - the move itself is progress: the row then sits at its true cell). The legitimacy rules are
unchanged (no volatile / ASM_* / one-trip blocks / fake dependencies added). The coordinator lands staged rows with
tools/fidelity/land_recipe_move.py (recipe trade recorded in ledger/recipe_trades.jsonl, window + SLUS gates).
If NOTHING is exact at the target, report the best distance there and what differs - and whether a flag variant of
the target (e.g. `-fno-schedule-insns`, which the registered cfg may carry for a reason) closes it.
