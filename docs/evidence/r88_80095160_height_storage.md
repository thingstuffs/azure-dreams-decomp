# func_80095160: disjoint actor/height storage (2026-10-02)

The next handover row, `dungeon/func_80095160`, goes from **5 to 4 pins** at
its existing `2.7.2-cdk-G0` recipe. Its body is named `func_8009A8C0` and
occupies 736 retail bytes (184 words). The removed pin is `ASM_REG("$18")`
on `floor_height`.

## Landed source change

An explicit local union holds the actor pointer through the collision/monster
checks, then holds the floor sampler's signed word result. Every member is
read only after that member was assigned; the actor is never accessed after
the height member is written. Both roles occupy retail's `$s2`.

The height shift moves to the shared `check_height` block. The dead target-X
variable receives the placement call's status and supplies its zero test.
Its coordinate value is no longer needed after forming the tile argument.
These are two recorded variable-hosting spelling trades. No pin, volatile,
one-trip block, artificial dependency, compiler option, or assembler change
was introduced. Four existing pins remain, so this is a partial solve.

## Why both hosting changes matter

The previous lane's `fh3` candidate removed the height pin but left one
instruction wrong: the first sign extension read `$v0`, not `$s2`. Its
halfword variable let CSE use the full-word call-result pseudo directly.
Keeping a full-word height avoids that alias, but a separate height variable
has allocation priority 5000 (4 references / 16 live instructions), ahead of
the actor's 1973 (10 / 152, doubled by its parameter equivalence). It gets
`$s4`, leaving five register substitutions.

Hosting height in the actor's finished storage fixes the lifetime relationship
but, alone, swaps `$s1` and `$s2`. The allocation measurements are:

| Source | Target X refs / live / priority | Actor-or-height refs / live / priority | Allocation |
|---|---|---|---|
| Actor/height hosting only | 8 / 54 / 4444 | 14 / 93 / 4516 | X=s2, actor/height=s1; total 24 |
| Also host placement status in target X | 10 / 54 / 5555 | 14 / 93 / 4516 | X=s1, actor/height=s2; exact |

The extra status definition and test count before allocation; later passes
keep the call result/test in `$v0`, so no extra move survives. The final
`.greg` assigns pseudo 93 to register 17 and pseudo 86 to register 18.
The source names in `prio.py`/`alloc_need.py` are shifted by the local union
declaration: the table was obtained from the equivalent scalar-hosting
diagnostic (`cand/host_actor_status.c`, independently byte-exact), then
cross-checked against the union candidate's RTL and register dispositions.

## Validation

- Five-pin control and four-pin candidate: exact, total 0 at the unchanged recipe.
- Independent `apply_candidates.py` verification: `applied match 0`.
- Both old and new `NON_MATCHING` builds compile. Their assembly differs;
  this is a shared-C rewrite, with no conditional port/dead arms changed.
- All 15 nonempty subsets of the four surviving pins were screened; none
  is exact. `t2_pins`: noop.
- Full 393,216-byte `dungeon_engine` window: MATCH; 2,174 other windows current.
- SLUS SHA-1 gate: MATCH (860 TUs, unchanged pinned recipe).

The lineage fingerprint was run before experimentation and after a stalled
family. This row has no distinguishing store/address signatures or GP uses;
the fingerprint is inconclusive. The established module recipe was retained
throughout; no alternate recipe was tried.

## Remaining four pins and next measurements

| Pin | Lone-erasure listing distance | Next measurement |
|---|---:|---|
| `coord_or_height`, `$3` | 18 | Trace the shared result variable's allocation and the final height-test conversion together; simple separate/ternary return spellings missed. |
| `center_y`, `$20` | 75 | Recover distinct center/target live ranges before body details: erasure coalesces spatial roles and changes body-pointer spilling and the saved-register assignment. |
| `tile_coord`, `$5` | 6 | Account for both shifts: the first call's x shift combines into a late argument setup; the later x-tile pseudo gets sched1's single-set boost. In-place X fixes its scheduling but retains an extra argument move. |
| `ASM_SCHED_BARRIER()` | 38 | Compare jump/jump2 return-block merging and delay-slot fill at `move_failed`; the ordinary erasure relocates the shared height shift and failure return. |

These distances are listing-screen measurements, not byte scores or claims
that the pins are impossible to remove. The subset scan is on the exact
four-pin candidate. Earlier experiments started from the five-pin source;
any follow-up must rebase onto the landed text.

Lane: `work/native_lane/r88_sol_80095160`. `REPORT_TABLE.md` records 49
measured variants, including formatting repeats; `REPORT.md` contains the
full retail register/region map. `cand/`, `out/`, the erasure table, and pass
dumps in ignored `scratch/` preserve the candidates and measurements.
