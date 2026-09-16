# Pin-removal goal: 500 new removals or an evidence-based plateau

Active objective: continue small, hypothesis-driven waves; prove a source fix,
transfer it cheaply, adapt to results; stop after 500 new pins are removed or
measured removals plateau with no productive approach remaining. The initial
round-35 ten-pin demonstration is outside this goal's counter.

Baseline: commit `500808e2`, **6,138 pins in 1,292 rows**. Goal target if reached:
5,638 pins or fewer, without inventory redefinition or replacement scaffolding.
Fixed row recipes, independent exact verification, source-hash checking, and the
applicable overlay/SLUS gates remain required. A stopped budget is a bounded
negative, not a proof of impossibility.

## Round 36 (gated)

- Proper pairs inside larger pinned integer families: 234 rows, 28,499 screens,
  11 rows reaching a 400-screen cap. One verified result: `dungeon/func_81084D04`,
  two register bindings removed while `step_x` becomes `s32`. Its values are
  explicitly truncated to `u16` before use, so the signed local preserves values.
  `tile_x` stays `s32`. The matching `u32` pair alternative was not selected.
- Five same-callee transfer rows: 1,227 additional screens, no hits, two capped.
  This was a bounded family transfer; it does not establish width-space exhaustion.
- Return repairs: one Sol agent audited all seven strict pinned/non-void/bare-return
  rows and reviewed a 36-body syntactic fall-through inventory. Three verified
  one-pin repairs (`dungeon/func_80086E64`, `town/func_80097340`,
  `town/func_800C49C4`); four bare-return negatives, no additional straightforward
  fall-through case. 34 distinct candidate screens, 40 full verifiers including
  controls and independent rechecks. Return expressions make actual results live
  instead of preserving them with keeps.
- Caller return declarations corrected to the unique same-container callee return
  type: 249 rows, 3,313 screens, 8 screen-hit rows, **zero fully verified hits**
  (11 full verifiers). No prototype edits landed. Screen equality is not byte proof.
- `town/func_8080E838` aggregate-copy hypothesis: 10 source forms (whole 88-byte
  copy, paired 88/24-byte copies, and 16-byte chunk copies, as aggregates or
  builtins with pin-erasure variants), no exact result. Whole aggregate copy
  reproduced the loop structure but chose different register roles. The old arc
  loop wall `809A38E4` was read and baseline-erased once; the prior multi-agent
  investigation already covers the obvious loop/angle directions, so no new
  mutation campaign was launched there.

Four functions / **6 pins removed**, including one extra from the changed-row
`t53_reg_state` cascade (`80086E64`, the remaining binding). Current count:
**6,132 pins in 1,290 rows; 6/500 toward the goal**. Two newly pin-free rows.
All five changed overlay windows MATCH (244 seconds), SLUS SHA-1 MATCH, row
database OK. This is progress, not a plateau; the goal remains active.

Artifacts: `work/native_lane/r36_width/`, `r36_returns/`, `r36_proto/`,
`r36_struct/`. The return lane's report gives every tested negative and result.

## Next concrete hypotheses

1. The four failed return repairs changed branch/epilogue layout. Test the actual
   return-value representation, with range evidence: a function returning only
   0/1 may have had a narrow scalar return type. Compare return-width changes
   jointly with the explicit-return repair before scaling anything.
2. Transfer the width-pair mechanism to functions outside the pilot's size/local
   limits only with a concrete value relation or range argument. Avoid repeating
   the same capped candidate prefix and counting that as a new experiment.
3. If those fail, select a different semantic/structural cause. Do not declare a
   plateau while a new source-repair family is still producing verified wins.
