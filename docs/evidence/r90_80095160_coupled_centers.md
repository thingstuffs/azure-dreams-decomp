# func_80095160: the two centers must be allocated together

2026-10-02, round 90. Continued the landed three-pin source at
`2.7.2-cdk-G0`. **No further exact pin removal found.** Production remains
three pins; the repository remains 401 pins / 161 rows. This pass corrects
an incomplete allocation target in the r89 diagnosis.

Lane: `work/native_lane/r90_sol_80095160`. The baseline is byte-exact,
736 bytes / 184 words. `REPORT_TABLE.md` records 22 scored variants,
including the inherited narrow-coordinate control; none is exact. Source
changes stayed in the lane. No recipe, compiler, or assembler was changed.

## The missing constraint

The fresh center-Y calculation still gives 12 substitutions and no indels:

```c
coord_work_2 = coord_or_height + 0x20;
center_y = offset_work + 0x20;
```

The `$20` pin is removed in `cand/center_fresh.c`. Its remaining discrepancy
looks like a rotation of three saved registers. However, adjusting only
center-Y's priority is insufficient: **the X center must get s0 first**.

| Actual role | Pseudo | References / live length | Priority | Current | Retail |
|---|---:|---:|---:|---|---|
| X center (`coord_work_2`) | 92 | 2 / 18 | 1111 | s0 | s0 |
| Y center (`center_y`) | 104 | 2 / 18 | 1111 | s6 | s4 |
| Direction | 90 | 4 / 49 | 1632 | s4 | s5 |
| Body height | 102 | 4 / 67 | 1194 | s5 | s6 |
| Direction table offset | 117 | 5 / 55 | 1818 | s3 | s3 |

The union in the source confuses the tools' declaration-name mapper. The
table uses identities verified from RTL, not those printed variable names.

`prefs.py --oracle` reproduced **24/24** preferences, dispositions, and
cc1 `find_reg` results. `replay_center.py` then tested allocation order with
all conflicts and preferences held fixed:

1. Move only p104 immediately ahead of direction p90: p104 takes **s0**,
   displacing the X center into s1. The step pointers rotate and the body
   pointer goes from spilled to fp. Direction/height remain wrong.
2. Move **p92, then p104** immediately ahead of p90: only the three intended
   dispositions change—direction s4 -> s5, height s5 -> s6, Y center
   s6 -> s4. Every other allocation stays as in the baseline replay.

Logs: `scratch/center_prefs.txt`, `scratch/center_replay.txt`, and
`scratch/center_need.txt`. This is an allocation counterfactual, **not an
exact compiled C solution**. It explains why the earlier inverse reported
two movers. Its simplified model reproduces 22/24 allocnos; the explicit
preference replay, including the two spilled allocnos, reproduces 24/24.

For the unchanged graph, raising **both** centers to 3 references / 18 live
instructions would give priority 1666, between direction and table offset;
the pseudo-order tie puts X first. Equally, both could have 2 / 12. These
are useful constraints for a real source rewrite, not permission to add
dummy reads or artificial lifetime padding.

## Source hypotheses tested

- **Share map-pointer and center-Y storage.** Their lifetimes do not
  overlap. The union form creates a fresh add temporary, p135; CSE forwards
  the later use to p135 and deletes the union-member copy. The roles do not
  remain shared: total 12, unchanged. A scalar address carrier really does
  merge the roles (5 / 45, priority 2222), but changes the early map register,
  body reload, scratch allocation, and scheduling: total 49.
- **Prepare the signed height delta before defining center-Y**, or put the
  center definition in the first call argument's comma expression. Both
  compile back to the same 2 / 18 center lifetime and total 12. Statement
  placement did not survive sched1 as a useful lifetime change.
- **Change the competitors.** A narrow direction gives total 14; a separate
  signed floor-height carrier gives total 31. The latter reduces that
  carrier to 3 / 61, but changes conversion instructions and allocation.
- **Share X center with the existing Y-coordinate work variable**, after
  the initial bounds role has finished. This represents the s0 reuse in
  retail directly. The merged role becomes 7 / 66, priority 2121, and stays
  s0. Center-Y remains 2 / 18 in s6; scheduling also changes: total 14.
  Candidate: `cand/centers_x_reuses_y.c`.

The actual C to investigate next is the pair of center definitions and
their table-offset consumers after `func_8009A540`. A valid source solution
must preserve X's allocation before Y, then place Y before direction and
body height, while preserving the table-offset register and instruction
order. Re-run the exact replay after any candidate changes this graph.
No source spelling accomplishing that was found here.

## Other two pins

The `$5` lead remains total **3** (1 substitution, 2 indels): the first X
shift is late and the later call has an extra `andi a1,a1,0xffff`.
Narrowing the shift input, shifting a narrow variable in place, or narrowing
the initial X argument leaves that score unchanged. A wide placement X
removes the mask but restores the wrong late ordering: total 4. Using the
callee's narrow parameter types adds conversions: total 16.

Replacing the initial Y `<<= 6` with `*= 64` fixes the first X-shift order,
but produces a fresh Y-shift value that coalesces into s4 and an `ori`
instead of retail's `addiu`: total 5. A fresh Y-pixel local behaves the
same. This is a changed dependency graph, not a free scheduling fix.
Direct Y arguments, X hosting the later collision direction, and X
assignments in the two real height-fallback arms also miss.

Fresh traces on the **current three-pin source** confirm the earlier
classification: first X shift is a sched2 tie; later shifts remain blocked
by unequal sched1 birthing boosts. See `scratch/tile_checks.txt` and
`scratch/tile_sched4.txt`. Source-order-only trials on the latter are still
unjustified.

Moving the barrier-free failure return to the function tail gives total
15, the same delay-slot/layout family as r89. Relocating that label does
not preserve the required failure thread through optimization.

## Validation and next route

The three-pin control compiled and scored exact. The lineage fingerprint
was rerun before work and after stalled families; it remains inconclusive
for this row. No flag sweep was performed. Since no source was landed,
the previous full-window and SLUS validation remains the production result;
those expensive gates were not rerun for documentation changes.

Continue as a C rebuild with the **coupled-center** constraint above, using
the saved exact allocation replay before further source experiments. The
open compiler decisions are `global.c` allocation order, sched1's live-range
recount, and CSE's removal of the shared-storage copy. This is not evidence
of a compiler/version wall. The tile and barrier routes remain documented
in r89; none of this pass's near-misses is ready to land.
