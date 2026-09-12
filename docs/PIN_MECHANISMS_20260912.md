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

## Zero-copy mechanism: first CSE now isolated

While the atlas runs on frozen source, a bounded read-only compiler investigation
resolved the pass ownership of `dungeon/func_80283F70`'s remaining one-word copy
mismatch. The 42-word retail site map and existing lineage fingerprint were reread.
At the existing `2.7.2-G0 -fno-strength-reduce` recipe, both source versions were
compiled with all RTL dumps. Ordinary compilation produces identical non-comment
assembly to the dump-enabled compile; the only extra text is `-da` in a comment.

The initial RTL already explains why these are different CSE inputs. With the pin,
insn 19 sets hard register `a2` in HI mode to zero; insn 22 reads that same hard
register in QI mode into the record ID. Without the pin, insn 22 reads a QI
`subreg` of HI pseudo 75. The first CSE dump changes that pseudo subregister read
to `const_int 0`, but preserves the pinned QI register read. Subsequent passes keep
this distinction. Final assembly differs only at `move $5,$6` versus `move $5,$0`.
This is observed constant folding before allocation, not a free-register selection
problem at that site.

A locally retained FSF 2.7.2 `cse.c` corroborates the narrowing-subregister folding
path: `fold_rtx` asks `equiv_constant` for the inner register and extracts its low
part. Its directory was misleadingly named as CDK, so the actual `version.c` was
checked and both source files were preserved with hashes. Matching version strings
do not prove that every local binary patch is reproduced; the pass dumps are the
direct evidence. The unrelated 2.6.3/CDK trees are not cited as the tested binary.

A bounded scan of the 6,567 historical records matching current source found **14
sites in 14 functions** where generated code copies zero and retail copies another
register into the same destination. Five have a one-word total residue. This is a
candidate family, not proof of zero equivalence or one shared cause. It includes
same-mode keep removals and cross-mode register-pin removals; a detector must preserve
that distinction. The historical recipe limitation still applies.

**Tracked route: rtl_probe/I2.** After the atlas completes, refresh this family and
select independent representatives of those two source situations. Establish their
first diverging pass and retail zero-value provenance before proposing a lifetime or
mode rule. No natural C replacement is validated yet; do not add volatile accesses,
fake dependencies, fences, or a blanket assembler zero-copy rewrite to force a match.
No production source or atlas recipe changed in this investigation.

Machine-readable pass excerpts, exact hashes, source corroboration, lead list and
queued action: [cse_zero_copy_20260912.json](evidence/cse_zero_copy_20260912.json).
Full dumps: `work/pin_search/mechanism_80283F70/rtl_current/`.

## Address literals are split symbol addresses, and the CDK cell splits them

The atlas's residue map put 975 pins in 336 functions on variables defined from an
address literal. Their residue is generated `lui;ori` against retail `lui;addiu`, or
retail's `lui` into a scratch register followed by `addiu` into the destination. In one
function it is a lone `lui` sitting in a branch delay slot. That is gcc splitting a
*symbol* address into HIGH/LO_SUM. Upstream matched these rows at cells that emit the
one-instruction `la` macro, and emulated the split with an integer page plus pins
(`page = 0x80070000; ASM_KEEP(page); page -= 0x3328;`).

Five hand probes went 0/5 at the recorded cells with the symbol written back, but 2/5
at `2.7.2-cdk(-G0)`, where the pinned text is exact too. Each lever alone had failed:
`litsym` only matched `u8 *p = (u8 *)0x8XXXXXXX;` and never saw these spellings, and the
09-09 cell sweep stripped pins but left integers where symbols belong.

`tools/xform/t29_addrsym.py` rewrites every use as the symbol at its effective address,
spelled from the file's own declaration. It deletes the variable, its definitions and
its pins, then scores at the recorded cell. Failing that, it tries the CDK cell that keeps
the row's `-G0` setting. A switch lands only under `tools/pin_cells_land.py` rules 1–2:
the candidate is exact there and not at the recorded cell, and the pinned text is exact
there too. It reaches 431 pins in 199 rows. `tools/apply_candidates.py --cells` lands
switches from outside the sweep under the same rules.

First harvest: 52 winning rows / 113 pins, of which 44 rows landed. Seven of the others
edited a NON_MATCHING arm, and one needed its new extern outside an `#ifdef`; the
generator now refuses the first and places externs after the includes. 32 wins used a
CDK cell. An attribution control found only 2 of those exact at the CDK cell without the
rewrite, so the pair of levers, not the cell, is the finding. T2 at the new cells removed
41 more pins. **Net: 139 pins and one fence in 44 functions, 14 of them pin-free.** Rule 3
(module corroboration): 25 of the 29 switches checked have module siblings at the
target cell; four are alone in theirs.

**The CDK hypothesis (withdrawn in the fifth round, below):** a stage-1 scan of the 355
smallest pinned rows found another admissible cell for most of them. 96% of rows recorded at
`2.8.1-G0`, and 58% at `2.7.2`, are also exact at a CDK cell. All 32 addrsym switches, and all
30 earlier `pin_cells_land.py` switches, point at CDK. That looked like recorded non-CDK cells
being ambiguities the pins had resolved. Hits at 2.95.2 and 2.91.66 are recorded, not landed:
those are 1999 compilers, after the game's release.

Second round (one gate): `t29` now scales `V + K` by the element size of `s16 *`, `s32 *` and
pointer-to-pointer pages, and refuses rewrites that touch a NON_MATCHING arm. Its sweep over
every row plus a rerun of the refused ones landed 5 more functions. The first 548 scanned rows
gave 28 functions whose pin is dead at a CDK cell (journal `t30_cellpins`, landed with
`apply_candidates.py --cells`), and T2 at the new cells followed. **Net 43 pins; 11 more
functions pin-free.** 33 windows MATCH, SLUS SHA-1 MATCH. Census: 9,959 pins in 1,607 rows.

`tools/xform/cdkcell.py` wraps any transform to run at the CDK cell (bindings
`t31_cdk_t2_pins`, `t31_cdk_t26_alloc`, `t31_cdk_t20_fencefree`), under the same rules 1–2.
246 of the 548 scanned rows admit a CDK cell without being recorded there.

Third round (one gate):
- **`t29` confined mode.** A page variable reused for another value keeps that role; only the
  uses while the address is known become symbols. Constant steps (`V += K`, `V++`) fold, and
  integer-cast uses are accepted. A forced sweep landed 16 more functions.
- **`tools/xform/t33_argconst.py`.** Pinned locals that only ever hold constants are written back
  as the constants. RAM and scratchpad addresses are excluded (those belong to `t29`), and a read
  outside the assigning block is refused. 15 functions / 17 pins at the recorded cell, then 6
  more at CDK through `t31_cdk_t33_argconst`.
- **The admissible-cell scan.** Now `tools/pin_cells_scan.py`, with ledger
  `ledger/pins_cells_admissible.jsonl`. It supplied 33 functions whose pin is dead at a CDK cell.
- **T2 on all 65 changed rows.**

**Net 99 pins this round**; 59 windows MATCH, SLUS SHA-1 MATCH. Census: 9,860 pins in 1,601 rows.

The argmove luna lane (`work/native_lane/argmove/`: 10 rows where erasing one pin moves one
argument copy `move $aN,$sM` by a slot) solved 0/10. Its account: call expansion makes the copy,
CSE folds the unpinned alias into its source, and the scheduler then puts the ready copy in a
later legal slot. That is recorded as a hypothesis, not a verdict (owner rule); the rows are
escalated to sol with the measured dead ends (`work/native_lane/argmove_sol/`).

Fourth round (one gate): 28 pins; 24 windows MATCH, SLUS SHA-1 MATCH; census 9,832 pins in 1,600 rows.
- **Fake-dependency lane (luna, `work/native_lane/fakedep2/`), 2 of 12.** A power-of-two scale
  spelled the other way reproduced the lifetime a fake dead store had faked:
  `start_entry = entry_index << 3` (`ASM_KEEP` off) and `double_phase = offset_phase << 1` (`$16`
  pin off). gcc expands `y * 2^k` through `synth_mult` and `y << k` through `expand_shift`, which
  leave different pseudos before allocation. Two rows no longer matched their evidence records.
- **`tools/xform/t35_shiftspell.py`** flips one site and erases the assigned variable's or the
  operand's pins: 812 candidates in 212 functions, **3 exact**. The effect is real but narrow.
- **Argument-move sol lane: 0 real wins.** Its one "exact" candidate removed the `$4` pin but added
  an `ASM_SCHED_BARRIER`, so it was not landed. The family stays at total 2 after luna and sol; astra
  is the owner's last resort and is held back for it.
- `t29` dereference uses (`((T *)D_X)->f`) landed 1; the scan's CDK hits landed 15; T2 landed 3.

Lesson: count a lane's result only after scoring it and diffing it for added scaffolding. Two of
three lane claims this session (luna's drafts, sol's candidate) did not hold up.

Fifth round (one gate): **84 pins**; 68 windows MATCH, SLUS SHA-1 MATCH; census **9,748 pins in
1,598 rows**.
- **Fake-dependency lane (luna, `work/native_lane/fakedep3/`), 1 of 12.** In `town/func_800C5ABC`,
  `x = load; ASM_KEEP_NV(x); x &= 0xfffe;` became one typed load-and-mask assignment,
  `x = (u16)(*(u16 *)p & 0xfffe);`. No other site in `src/` has that shape, so there is no generator.
- **`t35` at CDK (`t31_cdk_t35_shiftspell`): 0 of 6,767 candidates.**
- **The scan's hits at every plausible cell.** `pin_cells_scan.py build --plausible` also builds
  the hits at FSF 2.6.3, 2.7.2, 2.8.0 and 2.8.1. 55 rows landed and 54 changed cell. **None moved to
  CDK**: 43 went to 2.8.0 or 2.8.0-G0, 5 to 2.8.1, 5 to 2.6.3(-G0), and 1 to 2.7.2 (off 2.95.2-G0).
  28 of the 54 moved off a CDK cell. Rule 3: 12 have a module sibling at the target cell and **42
  are alone there**. 9 hits at 1999 compilers were recorded and not built. 17 stale hits go back
  through the scan.
- **Full strip (`pin_cells_scan.py strip`).** Every pin is erased at once and the text is scored over
  the row's admissible cells. **2 of 940 rows** with two or more pins are pin-free at some cell:
  `town/func_80097A54` at 2.8.0 and `town/func_80814D60` at 2.6.3. Both landed.
- T2 on the 56 changed rows landed 12 more.

**What the cell rounds show.**
- **`t29`'s CDK dependence stands.** It belongs to that mechanism (CDK splits symbol addresses
  into HIGH/LO_SUM; the FSF compilers emit `la`), and it survived its attribution control.
- **The single-pin scan hits say nothing about the build compiler.** Most pinned rows are exact
  at several cells, so a one-pin residue disappears at whichever cell happens to differ in those
  words.
- **"Every switch points at CDK" was a selection effect.** Rounds 2–4 built only the CDK hits.
  Once the FSF hits were admitted, the switches pointed mostly at 2.8.0, which had 15 rows before
  this round and has 58 now.
- **The switches are safe and can be undone.** They obey rules 1–2, so the shipped bytes do not
  depend on them. The `t30_cellpins` journal records each row's old cell (`cell_from`). To revert
  one, call `common.set_row_cfg` with that cell and regate.

**The cell levers are measured and used up:**
- the single-pin scan over 1,502 rows (every hit at a pre-1999 cell has landed);
- the full strip, 2 of 940;
- `t26` at CDK, 0 of 51;
- `t20` at CDK, 1 of 51;
- `t35` at CDK, 0 of 6,767.

The scan is keyed on each row's text hash and resumes itself, so it only rescans rows whose text
changes.

**Prologue parameter copies are typed one width too narrow (`tools/xform/t36_paramwidth.py`).**
The atlas residue map, clustered by signature over the 4,841 pins in rows unchanged since the atlas
ran, has its two largest clusters in the prologue:
- 67 rows: `move $s6,$a1` plus the save `sw $s6,0x28($sp)`;
- 60 rows: `move $s2,$a3` plus `sw $s2,0x18($sp)`.

The whole prologue-reorder family is 237 pins in 129 functions, 182 of them on m2c's pinned
copies of parameters (`register u8 saved_x ASM_REG("$22"); … saved_x = tile_x;`). A hand pilot
on `dungeon/func_800CC510` found the fix:
- Dropping the copies (`natural.py` dropcopy) left the residue unchanged (total 14).
- Declaring the parameters `s32` also left it unchanged.
- Declaring them `u16`, one width above the `u8` copies, was byte-exact with both pins off.

The narrowing copy is no longer merged into the parameter's entry move, so it is scheduled from
its own source line. `t36` retypes the copied parameters (every one together, then each one alone),
erases the copies' pins, and changes a same-file prototype with the definition.

First sweep: **57 of 121 eligible rows, 102 pins**, 51 through the joint one-step widening. It is
mostly one object-spawner shape across overlays, `void *f(s16 kind, s8 x, s8 y, s16 z)`. Joint
menus at the second to fourth width choices, and widening every narrow parameter, found 0 more in
the 64 refused rows. With the pins off, those rows score totals of 6–38, apart from four at 1–4:
a different mechanism.

**`tools/xform/t37_localwidth.py`, the dual of `t36`: 21 of 1,456 rows (about 1.4%).** It declares a
pinned integer local at another width and erases its pins. The hits are mostly counts, flags and
directions going from `s32` to `s16`/`u16`, and coordinates and ticks going from `u16` to `s32`.
None of the retyped locals holds an address. That first sweep's declaration regex stopped at the
`ASM_REG(` parenthesis, so it skipped every register-bound local. `ASM_REG` accounts for about half
of all pins. With the regex fixed, 3,298 pinned integer locals are eligible (717 with two or more
pins). A `--force` rerun of `t37` landed **60 more rows**, and `t37b` (one pin at a time, from the
template lane) landed **37 rows**. Census after both: **9,505 pins**, before the landing's lane
wins, `t39` and T2. Lesson: unit-test a new generator's eligibility on a row of each pin kind, not
only on its motivating row.

**Template lane (luna, `work/native_lane/template1/`): the width lever with partial erasure.** Both
template rows gave one pin each:
- `dungeon/func_800D0360`: `register u32 color_b ASM_REG("$7")` becomes `register u8 color_b
  ASM_REG("$7")`, and its `ASM_KEEP(color_b)` goes. Nine siblings share the template and have 7
  pins each.
- `dungeon/func_80AC5000`: the same edit on `blue`. Two siblings share the template.

The lane delivered 4 exact candidates: both template rows, plus the transfer to siblings
`func_80BC1084` and `func_80BD3084`. Its account is that the byte type keeps the volatile load
into `$a3` without the keep. The 42-pin row `dungeon/func_809A38E4` did not yield. Every
reduction in its 36-use block moved the register allocation or the setup order; the lane measured
removing the uses, retyping, rewriting the conditions and dropping the register bindings.
The register binding stays; only the keep becomes unnecessary once the local has its real width.
`t37` could not find this, because it erases every pin of the local it retypes.
`tools/xform/t37b_localwidth_keep.py` retypes a local that has two or more pins and erases one pin
at a time.

**The 42-pin row, sol (escalation after luna): no exact candidate.** Its best is TOTAL 2 at 41 pins
(`work/native_lane/angle_sol/candidate.c`). One `angle` use is removed, and the first two `0xfb`
stores become a chained assignment. `best.lreg` shows the `0xfb` pseudo back at 10 references over
10 instructions and in `$v0`; the remaining residue is one pointer add scheduled 3 words early.
Sol measured the loop, aggregate, pointer, declaration, type, angle-derived and assignment-order
directions. Astra is the last escalation for this row, queued after the next gate.

**Argmove, astra (last escalation): 1 of 3** (`work/native_lane/argmove_astra/REPORT.md`).

`dungeon/func_8188E3A0` is exact at its current cell, 2.7.2-cdk-G0, with its `$4` pin off and
nothing added. The change: `addr_or_coord = (s32)D_800255E8; effect->unk_10 = (void *)addr_or_coord;`
became `effect->unk_10 = D_800255E8;`.

The RTL account:
- The pin never added a dependency to the argument move, and it did not change the move's sched2
  priority.
- Staging the symbol's low half through the `v0`-pinned local makes it a hard-register producer.
  An ordinary pseudo gets a different ready-list rank (`0x7f000001`) in the *first* scheduler,
  and backward selection then puts the address pair after the move. The fix is decided before
  allocation.
- Sol's fenced version of the same edit had been at the old cell (2.8.1-G0). The cell switch in an
  earlier round is what let the plain edit work.

The other two rows stay at total 2. In each, an argument-copy tie is decided by source order in
the first scheduler, and in one of them a dependency is created only after allocation. Eight and
six natural rewrites were measured on them, respectively. Astra's rule is scoped to "a symbol
address staged through a pinned hard-register local with no other reader".

**Fake-dependency lane 4 (luna, `work/native_lane/fakedep4/`): 1 of 12.**
`dungeon/func_800A57A0` goes pin-free. `if (object_flags >= 0) { sign_bit = 0x80000000; ->unk_14 =
object_flags | sign_bit; }` with `object_flags` pinned to `$2` became `if (!(object_flags &
0x80000000)) { object_flags |= 0x80000000; ->unk_14 = object_flags; }`. About 5 of the 12 evidence
records no longer matched the row's current text; later rounds had changed those rows. The fake
lanes have gone 2/12, 1/12 and 1/12, and each mechanism was narrow. Stop them unless
`ledger/pin_evidence.jsonl` is refreshed against the current tree first.

**`tools/xform/t39_signbit.py`** (from fakedep4): `if (X >= 0) { … F = X | 0x80000000; }` becomes
`if (!(X & 0x80000000)) { X |= 0x80000000; F = X; }`. 8 of the 13 rows with the shape went exact.

**Sixth round, one gate:** 202 windows MATCH, SLUS SHA-1 MATCH; **288 pins, down to 9,460 in 1,577
rows**. All of it came from generators, and three of those generators came from lane results:
- the type-width family: `t36`, `t37`, `t37b`;
- `t38` (astra) and `t39` (fakedep4);
- the four lane wins themselves;
- T2.

What worked:
- **Clustering the atlas's residue records.** It needed no model and found the largest single lever
  (`t36`).
- **Turning each lane win into a generator the same day.** Astra's 1 row became 8 via `t38`,
  fakedep4's 1 became 8 via `t39`, and template1's 4 became part of `t37b`'s 37.

What did not:
- **The 42-pin row.** Its 36 references to `angle` still resist a natural rewrite.
- **Fake-evidence lanes on a stale ledger.**

Next levers:
- Re-cluster the residue records. Only rows whose text has not changed since the atlas still have
  valid records, so a fresh atlas over the changed rows would renew the map.
- Widths of struct fields and globals: the next level of the type-width family.

**Seventh round: the residue map refreshed, and how many patterns there are.**
- **Refresh.** The atlas was re-run single-site only (`--pairs 0 --groups 1`) on the 644 rows whose
  text had changed since 09-12 (5,126 pins). It crashed on a long probe name and was finished under
  a second tag (1 row). Together with the unchanged 09-12 records, residue records now cover
  **9,045 of 9,058 stock pins (99%)**. `scratchpad cluster_live.py` merges and clusters them.
- **Tool fixes in `tools/pin_atlas.py`.** A strip probe on a row with 56+ pins overflowed
  NAME_MAX, so long probe keys are now hashed. After a crash, the controller's `completed` count
  undercounts: the worker pool drained its queue first, so 643 of 644 rows had written
  `result.json`. Any change to the tool's code forces a new tag.
- **Answer by residue: not 20–30 patterns.** There are 7,113 distinct fine signatures. With
  registers and immediates folded there are still 5,178, and the top 30 cover 15% (top 100: 23%).
- **Answer by source mechanism: fewer.** One cause, "m2c declared a type one width off" (`t36`,
  `t37`, `t37b`), covered 175 functions across many residue classes. The patterns live at the level
  of what the pin compensates for, not of what it visibly protects.
- **Largest coarse clusters:**
  - prologue reorders (`move $sX,$aM` with the save of `$sX`), 205 pins in 131 functions;
  - displaced argument moves (`move $aN`), 163 pins in 122 functions;
  - displaced argument constants (`li $aN`), 121 pins in 97 functions.
- **`tools/xform/t40_prologue_param.py`.** The prologue residue names its parameter (`$aM`), so
  `t40` retypes exactly that parameter with the pin erased. Targets come from the residue map:
  276 pins in 174 functions. First sweep: **8 rows**.
  - Five spawner rows had `s8 arg1` widened to `s16` alone; `t36`'s joint widening of both
    parameters had failed on them.
  - Two had an `s16` parameter declared `s32`, and one an `s32` declared `s16`.

  The residue named the right parameter every time. But 8 of 174 says most prologue reorders are
  not a type question.
- **Cascade.** Re-running the type generators on `t40`'s 8 changed rows landed 11 more:
  - `t36` 5, the spawner rows' `arg2` now widening too;
  - `t37` 6.

  Removing one pin changes the text enough for another generator to apply. Until now only T2 was
  re-run on changed rows, so round 6's 186 changed rows never went back through `t36`–`t39`. The
  cascade reruns `t36`, `t37`, `t37b`, `t38`, `t39` and T2 over every row changed since round 5
  until a pass applies nothing. The journals skip text a transform has already seen, and `t40`
  stays out because its target site indices go stale. `land7.sh` now ends every landing with the
  same loop.

  Over the rows changed since round 5, pass 1 applied 8: `t37` 1, T2 6, and `t38` 1, which
  removed an `ASM_SCHED_BARRIER`. Pass 2 applied nothing. With the 8-row follow-up that makes 19
  records. Most of the cascade's value is in the rows the latest generator just changed, not in
  older rounds.
- **Pilot, dropped: an unprototyped callee.** Removing the parameter list of a prototyped callee
  declaration, with an argmove pin erased, went 0 of 12 candidates on 10 rows. Few files prototype
  their callees at all.

Lanes launched after this gate:
- **astra on three argmove rows** (`work/native_lane/argmove_astra/`), the owner's last escalation
  after luna and sol. Its brief states that sol's fence-for-pin trade was refused.
- **luna on 12 more fake-evidence rows** (`work/native_lane/fakedep4/`). 21 such rows remain.
