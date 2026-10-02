# func_800AFA68: entry memory pin and matrix allocation (2026-10-02)

The handover's next first-touch row, `dungeon/func_800AFA68`, goes from **10 to 9 pins**
at its existing `2.7.2-cdk-G0` recipe. This is a pin trade, not a pure-C reconstruction.
The body is named `func_800B51C8` and occupies 3,336 retail bytes (834 words).

## Landed change

Remove `ASM_REG("$22")` from `rotation_matrix`. Keep the existing entry
`ASM_KEEP_MEM_NV` at the same statement and with the same `gameWork` memory operand,
but tie it to `view_matrix` instead of `transform_flags`.

The memory operand retains the early `lui v0,%hi(gameWork)`. Its tied register operand
also affects allocation. Without the rotation pin, retaining the flags operand swaps
the rotation and flags registers (`s6`/`s7`): listing distance 32, byte total 16.
Using the rotation matrix itself as the keep operand instead swaps it with the entry
index (`s5`/`s6`). Using the view matrix preserves the complete retail allocation and
instruction order: listing distance 0, byte total 0, 9 pins.

The `.flow` dumps identify these pseudos by their initializer constants, avoiding
the lane tool's imperfect variable-name mapping on hard-register declarations:

| Variable | Pseudo | References with flags keep | References with view keep |
|---|---:|---:|---:|
| rotation_matrix | 85 | 15 | 15 |
| view_matrix | 87 | 27 | 29 |
| transform_flags | 89 | 15 | 13 |

The landed `.greg` assigns 85 to s6, 87 to s4, 88 (depth cue) to fp, and 89 to s7.

This removes one explicit register constraint while retaining one existing memory
constraint with a different carrier. No volatile, dependency expression, one-trip
block, compiler option, or assembler change was added. The pin ledger records the
changed carrier so it cannot be counted as two independent removals.

## Verification

- Original 10-pin control: exact, total 0 at `2.7.2-cdk-G0`.
- 9-pin candidate: exact, total 0; independently reverified by `apply_candidates.py`.
- Both `NON_MATCHING` builds compile and generate identical assembly.
- Fresh single/pair erasure census: no further exact erasure. `t2_pins`: noop.
- Full 393,216-byte `dungeon_engine` window: MATCH; 2,174 other windows current.
- SLUS SHA-1 gate: MATCH (860 TUs, unchanged pinned recipe).

`lineage_fingerprint.py` was run before experimentation and after the first stalled
family. This row has no `$gp` references and insufficient family-specific emission
evidence; it does **not** independently distinguish stock from cdk. The existing
module attribution was retained throughout; no alternate compiler recipe was tried.

## Remaining work and measured negatives

34 source variants were measured, plus the baseline and two bounded erasure censuses.
The lane is `work/native_lane/r87_sol_800AFA68`; its `REPORT_TABLE.md`, candidates,
pass dumps under ignored `scratch/`, and `landing.log` preserve the measurements.

- `cand/near.c`: erase the old rotation and flags-memory pins together, 8 pins,
  total 2 (0 substitutions, 2 indels). Only the entry HIGH moves past the scratch
  base initialization. The first scheduler boosts the single-set HIGH consumers;
  merely moving the source load or assigning through an unused parameter does not
  fix the order. Reusing the render-state, pitch, or game-base variables introduced
  allocation or scheduling differences. This remains a C-shape/scheduler question,
  not a compiler-version verdict.
- `cand/scratch_typed.c`: erase the scratch REG/KEEP pair and express the scratch
  accesses through typed union members. The listing residue falls from 38 to 16;
  byte total is 16 (0 substitutions, 16 indels), with 8 pins. The world UV arithmetic
  ordering now matches. The remaining regions are entry setup and outgoing stack
  argument ordering at the world/shadow projection calls. This candidate is based
  on the original 10-pin text and is **not** ready to land on the new baseline.
- Reusing the fourth corner pointer for a shadow-coordinate read retains an extra
  pointer-relative load and changes the delay slot: total 8, not exact.
- Depth-cache readbacks around the matrix store: total 16. Narrow depth-copy probes
  also miss and are diagnostic only; they are not semantic replacement proposals.
- Duplicating the shadow rotation/matrix setup into the height-clamp arms, changing
  the outer loop form, or relocating the matrix initialization did not recover the
  required allocation without other changes.

Next work on this row should start from the landed 9-pin text. For a pure-C entry
fix, explain the missing unboosted HIGH consumer without making the game-work base
non-rematerializable. For the scratch pair, compare typed-member memory dependencies
and the call argument evaluation order; do not restart constant-base or compiler
sweeps. The remaining nine pins are unresolved.
