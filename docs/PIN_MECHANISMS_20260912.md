# Pin and fence mechanisms — 2026-09-12 follow-up

## Loop counter increment in the condition

`main/func_8001D54C` (true address `8040454C`, stock GCC 2.6.3, 36 retail bytes)
clears ten values reached through a pointer table. Retail is a frameless leaf:
`a0` walks the table, `v1` counts iterations, and `v0` holds each loaded pointer.
The pointer load precedes the counter increment, which fills its load delay;
the table cursor advances in the back-edge delay slot. All nine retail instructions
were read from the row's exact container extent before the source probes.

The starting C had `index++;` followed by a fenced `cursor += 4;`, ending with
`while (index < 10)`. Simply removing the fence moved the increment ahead of the
load and introduced a load-delay nop. An equivalent `for` spelling did the same.
Moving the increment into the test, `while (++index < 10)`, produced all nine
retail instructions without the fence. Independent per-row verification reports
zero substitutions and zero insertions/deletions at the existing stock recipe.

The reusable candidate rule crosses only independent updates of ordinary,
unescaped, nonvolatile locals. It requires an unconditional increment at the
tail of a `do` body, a simple comparison, and no `continue` or other early exits
that could change how often the increment executes. It adds neither pins nor
fences. Acceptance still requires the full byte verifier and final window gate.

Measurement scope matters: a mechanical scan produced 47 distinct variants across
16 fenced functions. Only the original example matched; the 15 other functions
did not. This is a useful narrow rule, not evidence for broad coverage. Keep it
in the dedicated fence pass rather than expanding the general pin-search menu.
Full sources, retail listing and results: `work/pin_search/mechanism_8001D54C/`.
The fence removal has now landed through the combined main/overlay window gates and
full SLUS gate. Tracked family evidence:
[loop_test_increment_20260912.json](evidence/loop_test_increment_20260912.json).

## Zero-equivalent copy at a loop entry: still open

`dungeon/func_80283F70` (true address `80016F70`, 168 bytes) initializes two runs
of records and one final record. The complete retail listing is frameless, uses
`a0` as the record cursor, `v1` as the ID-field cursor, `a1` as the ID, `a2` as
the counter and `a3` as the type constant. The loops have identical layouts.

Erasing only the counter's `$6` register pin at the existing stock recipe
(`2.7.2-G0 -fno-strength-reduce`) leaves one substitution and no length change:
generated `move a1,zero` versus retail `move a1,a2` after `a2` was set to zero.
Sharing the two loop counters under one name leaves exactly the same residue;
widening the first counter also changes the sign-extension/loop-test shape and
is worse (regional aligned distance seven). No source from these probes landed.

The lineage scanner was run on the exact frozen bytes using the instrument's
own environment. It reports insufficient store-emission evidence, one two-register
address construction and one zero-equivalent copy; this is not a unique compiler
attribution. No config sweep or toolchain change was made. The current recipe is
retained because the pinned source is independently exact at that recipe.

Queued compiler-pass investigation: compare CSE/RTL equivalence selection at the
initial zero assignment with and without the hard-register declaration. Determine
whether a natural live-range structure preserves the copy before building another
generator. Do not resume declaration-order or width grinding without that evidence.
Site map, lineage output, candidate sources and aligned regions are saved under
`work/pin_search/mechanism_80283F70/`.

## Exact template transfer: limited measured opportunity

A bounded Luna audit of pinned dungeon rows found 32 repeated `true_name` groups
covering 95 rows / 628 pins. Conservative token normalization found only five
exact pairs (10 rows / 70 pins). No verified transferable edit was established.
Near templates have changed constants and control flow, so they remain research
leads rather than automatic patch targets. This does not justify building a broad
fuzzy-transfer tool yet. Evidence: `work/pin_search/template_audit_20260912/`.

The historical census's roughly two dozen dominant mechanism classes remain a
reasonable organizing hypothesis. Repeated mechanisms should drive guarded
generators; repeated-looking functions alone do not establish interchangeable fixes.

## Second harvest and the next experiment

The 85-row baseline follow-up completed without errors: nine candidates removing
17 pins, 76 noops, 131,407 compiler invocations, 37 full-verifier calls, and 3,641
CPU seconds. It used doubled row budgets on 84 previously productive, budget-limited
rows plus the repaired timeout case. The latter no longer timed out.

Independent publication plus T2/T20 yielded 21 pins in total; the manual loop rewrite
added one fence removal. All 15 combined windows, five follow-up windows and the
full SLUS gate passed. Current census: 10,282 pins in 1,634 rows. Evidence and source
hashes: [pin_followup_20260912.json](evidence/pin_followup_20260912.json) and
`ledger/pin_runs/pins_followup_20260912*.json`.

This batch's search yield was about 17 pins per CPU hour, versus about 39 in the
first broad batch. Selection differs, so this is not a controlled algorithm comparison.
It argues against simply doubling every remaining row's budget. The next bounded
experiment targets fences, including functions with no ASM pins. A fresh static scan
found 534 scored fences across 411 functions before the manual fence landing; 19
functions had no T20 completion record for their current source hash.

Queued harvest-efficiency change: refine staged candidates with bounded T2/T20 before
publication, recording parent and derived hashes, then run the combined gates once.
Current follow-up is correct but rebuilding the large dungeon window after both
publication and follow-up adds unnecessary work. Preserve transactional rollback,
source-policy checks and independent final verification when making this change.

## Fence batch evaluation and joint-erasure coverage

`pins_fences_20260912` finished all 19 rows without errors or removals: 425 actual
full-verifier calls and 406 CPU seconds. Sixteen rows reached the attempt limit; three
finished their available menu. Most shape searches did not improve the unwrap residue.
`dungeon/func_8180DE3C` narrowed an intensity temporary to cut its residue from eight to
four, but did not match. `dungeon/func_800AA49C` remains a one-instruction unwrap lead.
This result does not support broadening the unchanged fence pass. No source publication
or gate rebuild was needed. Evidence: [fence_batch_20260912.json](evidence/fence_batch_20260912.json).

A current-source audit found 405 functions with 2–8 pins whose successful historical
subset records do not cover every joint erasure. They contain 2,137 pins. This count
excludes single-pin rows, stale source hashes and unsuccessful compile records; historical
records still lack current recipe fingerprints. T27's fallback group list includes
singles and nearby pairs, and its per-group shape search can consume the budget before
larger combinations. T2 cannot remove a group that only becomes dead together.

The next experiment removes pin subsets without any shape mutations, using the cheap
assembly screen and mandatory full verification of possible wins. The first 100 rows
contain 763 pins and favor more pins and smaller functions; this is not a random sample.
The dedicated mode has exhaustive enumeration through eight pins, explicit limits and
saved near misses, with the established recovery/publication path. Its value will be
judged on verified removals per CPU time, not number of tested variants. Audit:
[joint_erase_audit_20260912.json](evidence/joint_erase_audit_20260912.json).

### First joint-erasure harvest: 18 pins landed

All 100 rows completed without errors or budget stops: six candidates / 18 pins,
20,585 compiler calls, 125 full verifies and 443 CPU seconds. This is about 146 pins
per CPU hour before publication/follow-up, versus 17 in the prior extended beam batch.
The populations differ. The 117 near-screen fallback checks produced no additional
wins; lowering this allowance is worth a measured trial, but assembly equality alone
must never become the acceptance proof.

The six candidates are `town/func_800B8934`, `town/func_8032F060`,
`dungeon/func_8009A288`, `dungeon/func_81977230`, `dungeon/func_80976434`, and
`dungeon/func_80E3BD94`. A current independent three-probe check on the first row shows:
removing the entry pointer's register pin alone costs four aligned differences;
removing its distant `ASM_KEEP` alone costs 27; removing both is exact. The source
already has the right natural lifetime, while the two remaining constraints interact.
The five-pin win on `func_8009A288` removes interacting constant keep markers together.
These are removal-group mechanisms, requiring no speculative C rewrite.

All six publication windows and SLUS passed. T2/T20 initially removed one further pin
in `dungeon/func_80976434`, but source review rejected it: legacy `host_candidates`
reused a `void *target` for integer angle arithmetic. Byte equality did not establish
honest types. That extra change was restored, and fresh window/SLUS gates passed.
Three compatible integer-host alternatives failed (aligned distances 65, eight, three).
The legacy generator now resolves types at each rename site and rejects incompatible
pointer/integer, signed/unsigned, and qualified reuse. No casts were added to force it.
Final accepted total: 18 pins removed across six functions, leaving 10,264 pins in
1,634 pinned rows. Preserve the rejected-source and probe evidence in the run directory.

Next steps: expand erasure-only coverage to the other current 2–8-pin rows. For larger functions, prioritize groups
sharing a variable before enumerating all distant pairs, using the verified register
plus keep example as the control. Avoid applying an exponential search to large pin
sets. Preserve results and exact source hashes to avoid repeating completed work.
Evidence: [joint_erase_batch_20260912.json](evidence/joint_erase_batch_20260912.json).

## Joint-erasure expansion and type-repair audit

`pins_joint_expand_20260912` completed 365 rows without errors or budget stops:
nine candidates removing 33 pins, including the last four pins in
`dungeon/func_800B30D0`. Search used 19,734 compiler calls, 335 full verifies and
629 CPU seconds. All 13 publication windows and SLUS passed. Bounded T2/T20 made
no further changes. The source diffs only erase register/keep/barrier scaffolding.

The 305 smaller functions supplied 14 removals in 465 CPU seconds. The 60 larger
functions supplied 19 removals in 164 CPU seconds. This is selected coverage, not a
randomized comparison, but supports trying variable-linked groups in the remaining
large functions. Across both joint-erasure batches, 435 near-screen fallback checks
produced no extra wins. The next bounded throughput experiment disables those extra
checks while retaining full verification for every possible acceptance and saving
near misses. It also tries only the full set, variable groups and macro families in
288 larger functions / 5,355 pins; it does not enumerate their quadratic pair space.

A bounded review of 156 exact saved production pairs plus 18 follow-up pairs found
one earlier incompatible legacy-host rewrite in `dungeon/func_8180E7F4`: a pointer
`slot_base` was reused in the signed integer `element_mask`. Four correctly typed
alternatives failed (aligned distances five, five, five, seven). Restoring its original
pointer declaration requires restoring one pin. This audit matches changed assignment
RHSs and declaration types; it is not a full semantic audit. Older history without
matching intermediate sources remains unknown. Artifacts and probes are retained under
`work/pin_search/host_type_audit_20260912/`; the guarded generator prevents new
incompatible type reuse. The repair is tracked separately from the 33-removal harvest.

The restoration passed independent byte verification, its affected window and SLUS.
Final net reduction this cycle is 32 pins: 33 removed and one restored for honest types.
Current census: 10,232 pins in 1,633 pinned rows. Tracked receipts include the separate
repair in `ledger/pin_runs/host_type_repair_20260912.json`; combined evidence is
[joint_expand_20260912.json](evidence/joint_expand_20260912.json).

## Family-only pass: 26 removals harvested

`pins_joint_families_20260912` completed all 288 larger functions in 79 CPU seconds:
2,249 compiler calls, ten full verifies, ten candidates and 22 pin removals. No budget
stops or errors occurred. Eight wins remove a register/keep (or undef) group on one
variable; one removes three keep markers together, and one removes a register plus
two keeps. This is roughly 1,001 staged pins per CPU hour, before publication costs.
The prior larger-row sample yielded about 417; population differences still matter.

Review found stale `Byte-exact pin` and `MATCH:` annotations left on erased-pin lines.
The eraser now removes those annotations only on selected pin lines, preserving other
comments and retained pins. A ten-winner replay, `pins_joint_families_clean_20260912`,
retained all 22 removals in 12 CPU seconds and is the publication source. Original
candidate artifacts remain immutable. All 14 publication windows and SLUS passed.
T2 removed four further pins in three functions; all four affected windows and SLUS
passed. Four obsolete follow-up pin comments were removed with token equality checked
and another fresh four-window/SLUS gate. The shared T2 eraser now cleans these notes.
Final harvest: **26 pins**, leaving **10,206 pins in 1,633 pinned rows**. Receipts are
in `ledger/pin_runs/pins_joint_families_clean_20260912*.json`.

The next learned grouping mechanism is multi-operand connectivity: a keep/use involving
several named variables connects their register declarations. The old family pass only
recognized single-identifier arguments. The new plan tries each variable's pin group
and each connected group, with duplicate groups removed. It does not change C expressions.
Of 102 statically linked functions, 15 have fresh complete small-subset searches;
a saved selection contains the other 87 functions / 1,695 pins. This small batch is
deferred while we map the current population and compare interaction predictors.
The search/eraser suite has 46 passing tests.

Cache replay exposed a separate efficiency issue: batch-wide recipe identities change
when the selected compiler/SLUS-reference set changes, invalidating some reusable row
compilations. The ten-row replay made 90 compiler calls and ten cache hits. Queue stable
row recipe identities with cross-batch regression and legacy-publication compatibility;
do not weaken current source/recipe checks merely to reuse old cache entries.
