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

**The 42-pin row, astra (last escalation): best TOTAL 2 at 4 pins.** Astra rewrote the arc loop as
a backward goto, `arc_segment: … if (…) goto arc_segment;`, and 38 pin sites became unnecessary.
The mechanism: gcc 2.x runs `loop.c` (invariant hoisting, strength reduction) only on loops the
front end marked with `NOTE_INSN_LOOP_BEG/END` (`for`, `while`, `do`). In the marked loop the
constant `0xfb` was hoisted out, and the 36 `ASM_USE_NV(angle)` statements had compensated for
that hoisted constant's allocation. Unmarked, the constant stays local: 5 references over 10
instructions (`dumps/candidate/candidate.c.lreg`).

The one residue left is the pointer add `vertex_data = prim + 0x1A`, 3 words early; sol's best
candidate had the same residue. In the base, the setup's `do { … } while (0)` emits a loop note
that makes the add depend on a radius load, and the goto form has no such note. Restoring the
base's fence around both setup statements gave TOTAL 101, and around the add alone TOTAL 14. The
row is parked with this evidence: luna, sol and astra have all been spent. That is a measured dead
end, not a verdict. `tools/xform/t41_gotoloop.py` tests the goto-loop mechanism tree-wide.

`t41` first sweep: 236 do-while loops hold 744 pins in 171 rows (64 more loops skipped for
`break`/`continue`). **15 rows went exact**, 9 with every body pin erased and 6 with one. The form
is `loop_N: { … } if (C) goto loop_N;`, which keeps the meaning, since the backward jump re-enters
the block. `t41b_gotoloop_while` extends it to `while`/`for` loops, written as the guarded
bottom-tested goto that gcc's rotation of a marked loop produces:
`INIT; if (C) { top: { BODY } STEP; if (C) goto top; }`. Its population is small: 27 loops holding
65 pins, because m2c writes most loops as `do`-while. It landed 1 row. The lint confirmed the guard
and the bottom test carry the same condition.

**Argconst lane (luna, `work/native_lane/argconst/`): 2 of 10.** Both are the same mechanism. A
parameter copy assigned at the function top moves into the branch that uses it, after the
allocation call's success check, and its keep goes:
- `town/func_800BEE14`: `saved_angle = angle`; its `ASM_REG` stays.
- `dungeon/func_8028C354`: `saved_render_param = render_param`.

The shorter live range reproduces retail's order of the argument constants.

The 8 unresolved rows stay at TOTAL 2. Constant propagation folds every literal-only argument, so a
constant survives as its own producer only through a genuine non-constant use. The lane measured
literals, macros, types, register hints, reuse and reordering on them. `tools/xform/t42_sinkcopy.py`
generalizes the sink.

It moves a pinned parameter copy to the start of the innermost block that holds every use, and
refuses when the parameter or the copy is written anywhere else. Its unit test reproduced the lane's
`dungeon/func_8028C354` edit. `town/func_800BEE14` did not reproduce: the lane had chosen a different
branch there, and its own candidate lands. 125 of 1,468 pinned rows have a sinkable copy.
First sweep: **9 rows**, each with the copy assigned exactly once. The first run was killed when the
machine ran briefly low on memory, with other sessions on the box. It had applied nothing and
written nothing, and it was resumed at 4 workers.

**`tools/xform/t43_rewrite_greedy.py` (statement-shape rewrites as greedy bases): 1 of 1,467 rows.**
The menu was an if/else arm swap, `&&` against nested ifs, `?:` against if/else, and swapping a
comparison's operands. It is a clean negative. gcc canonicalizes these shapes to nearly the same
RTL, so the base stays exact but no pin becomes dead. The one hit is an arm swap in
`town/func_800B4EAC` that freed a fence and a keep. Loop notes worked (`t41c`, 38 rows) because they
switch an optimizer pass on or off. The next levers to try are other switches of that kind, not
spellings.

**Scope idea, dropped before a generator: hold-set residues are not frame layout.** Of 349 current
hold-set pins, 336 pin a plain scalar or pointer, 11 an address-taken local, and none an array or a
struct held by value. The residues are dominated by `sw`/`lw`/`move`, which are prologue and
epilogue saves. These pins decide which callee-saved registers the function uses, so this is the
register allocator, not stack-slot sharing between scopes. Declaration scope could only change
stack-allocated locals, and there are almost none.

**Pilot, dropped: the `register` keyword.** Erasing `ASM_REG("$N")` but keeping the `register`
keyword went 0 of 30; gcc 2.x ignores the keyword for allocation at -O2. The next lever is the
mirror of `t41`. m2c's own labels form 165 backward-goto loops holding 756 pins in 113 rows. Where
the original was a structured loop, `loop.c` ran on it and m2c's goto spelling lost that.
`tools/xform/t44_doloop_greedy.py` writes those loops as do-whiles and runs `t41c`'s greedy walk.
First sweep over 1,466 rows (179 loops in 119 rows): **15 rows, 26 pins**, with no errors. The
lint is clean. A braced final goto `if (C) { goto L; }` becomes `} while (C);`, and an
unconditional one becomes `while (1)`. The label is kept only if another goto uses it. So the
loop-note lever works in both directions: `t41` drops notes the original never had, and `t44`
restores notes that m2c's goto spelling lost. The third spelling, gcc's non-rotated while
(`goto T; L: BODY T: if (C) goto L;`), holds pins in only 1 loop (2 pins), so it gets no generator.

**Code-motion lane (luna, `work/native_lane/codemotion/`): 0 of 10.** It was rebuilt without the
page-family rows, which belong to the lui-rename dead end. The pins hold branch-sense, load,
argument-move and stack-reload motion. The lane's accounts again come back to register coalescing
and its side effects on scheduling and delay-slot filling. The best candidates reached TOTAL 2
(`dungeon/func_800D7198`, a loop-carried update sunk to its consumer; `dungeon/func_80921B2C`).

**Since round 6** the yield went 288 → 28 → 85 → 32 → 0, and three luna lanes went 2/10, 0/10 and
0/10 on scheduling and allocator residues. The next hypothesis is per-file compiler flags, which
the earlier cell scan never tried (it covered only the stock compilers). The tree already has rows
built with `-fno-schedule-insns`, `-fno-strength-reduce` or `-fno-cse-skip-blocks`. Astra's argmove
account showed the FIRST scheduler decides those orders, and `-fno-schedule-insns` turns it off.

**Flags in the tree today.** 343 rows carry extra flags. 143 of those are only the `-G0` spelling;
about 200 use real optimization flags (`-fno-schedule-insns` 45, `-fno-strength-reduce` 39,
`-fno-schedule-insns2` 22, `-O1` 19, and a long tail). They are scattered: most modules have 1–3
flagged rows, and flags differ within one module (`scene_runtime.c` mixes `2.6.3 -G0`, `-O1` and
`-fno-schedule-insns`). A real build gives each file one flag set, so these are per-row choices made
by earlier matching work: the same cell underdetermination the compiler scan showed. Flags are
therefore an accepted lever here, and a flag switch lands under `pin_cells_land.py` rules 1–2 like a
compiler switch. Module agreement is weak evidence for them.

The scorer honours extra flags in a cfg string. `dungeon/func_80D150D0`, recorded at `2.7.2-G0
-fno-schedule-insns`, scores exact with the flag and TOTAL 134 without it.

**Flag pilot on the lane dead ends: 1 admissible hit in 32.** The pilot covered 32 rows from the
argmove, argconst, code-motion and lui-rename packs, each still at its lane base. It erased each
row's named pin under 8 flag variants of the recorded cell (`-O1`, `-fno-schedule-insns`,
`-fno-schedule-insns2`, `-fno-strength-reduce`, `-fno-cse-skip-blocks`, `-fno-rerun-cse-after-loop`,
`-fno-expensive-optimizations`, `-fno-caller-saves`). In `town/func_8081DD70` (2.95.2-G0) the
erasure is exact at `-fno-expensive-optimizations`, and so is the pinned text. That is about 3% on
the hardest rows in the tree, at no model cost. `pin_cells_scan.py scan --flags` now runs the same
two stages over every pinned row (ledger `ledger/pins_flags_admissible.jsonl`), and `build --flags`
lands its hits under rules 1–2. The compiler never changes, and each switch can be undone from the
journal.

**Lui register-rename lane (luna, `work/native_lane/luirename/`): 0 of 10.**
- **The family.** It is the largest coherent reg-rename sub-cluster: erasing the pin changes only the
  register a symbol's high half (`lui`) is loaded into. Most of the rows are `t29`'s integer-page
  family, which `t29` had refused.
- **The lane's account.** Retail keeps the high half and the low half in separate registers
  (`lui $v0; addiu $a3,$v0,…`). The pin prevents the two pseudos coalescing, and without it they
  coalesce.
- **What it measured.** Symbol, array-decay, typed-pointer, alias, declaration-order, page-type and
  per-use rewrites. All kept the rename (TOTAL 1–3).
- **Status.** A measured dead end at luna; sol was not spent on it. The lever is unknown: something
  in the original must keep the high-half pseudo live (for example a second address sharing the
  page), and no natural form found it.

**`tools/xform/t41c_gotoloop_greedy.py`: 38 rows, about 50 pins.** It builds an exact base (the goto
form alone, or with the body's pins erased), then erases the function's remaining pins one at a
time, body first and then nearest outside. It is the largest of the three goto-loop generators:
most of the pins a goto loop frees sit outside its body, where `t41` never looked. The goto-loop
family is 54 rows so far (15 + 1 + 38). The loops become `loop_N:` gotos, which is valid 1997 C and
not scaffolding. The owner may prefer structured loops; each rewrite can be reverted from its
journal.

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

## Round 11 (2026-09-13): per-row flags, and an assembler version the C cannot express

Gated (114 windows MATCH, SLUS SHA-1 MATCH): **9,036 pins in 1,527 rows**, 279 pins and 36 functions
pin-free since round 9. By source: `t45` 38, the flag switches 150 (one pin per row), the cascade 91.

- **The flag scan (`pin_cells_scan.py scan --flags`), harvested.** 1,465 pinned rows were each
  scored at the recorded cell plus one of eight optimization flags. 212 single pins were dead at a
  flag variant, in 150 rows. `build --flags` chose one cell per row: 196 hit pins. All 150 landed
  under `pin_cells_land.py` rules 1–2 (the fewer-pin text exact at the flag cell and not at the
  recorded one, the pinned text exact at both). The cascade and T2 then took 91 pins in 69 records: T2 33, `t37` 15, `t37b` 8, `t41c` 6, `t36`, `t38` and `t44` 2 each, `t41` 1 more.
  - By flag: `-fno-cse-skip-blocks` 36 rows, `-fno-schedule-insns` 26, `-fno-strength-reduce` 26,
    `-fno-expensive-optimizations` 24, `-fno-rerun-cse-after-loop` 14, `-O1` 10,
    `-fno-schedule-insns2` 8, the rest 6.
  - By pin: `ASM_KEEP` 86, `ASM_REG` 51, `ASM_KEEP_NV` 25, `ASM_SCHED_BARRIER` 17, others 18.
  - **The switches are weak evidence, like the cell switches.** A translation-unit test failed.
    The town window 0x8032EEE4–0x803305E0 holds 15 of town's 43 hit rows (8 at `-O1`), but
    every row there was scored at four `-O1` cells, and seven unpinned rows are exact at none of
    them. Only 4 rows go pin-free at `-O1`. The hits are per-row underdetermination, as the CDK
    hits were. Each switch can be undone from the `t30_cellpins` journal (`cell_from`).
- **`t45_orzero_aspsx`: 20 rows, 38 pins, and the hidden `READ_ZERO`/`ASM_UNDEF` wrappers.**
  - The single-pin rows included `register s32 zero ASM_REG("$0")` carriers, written as `zero | 9`
    to get `ori v0,$zero,9` where gcc's `li v0,9` assembles to `addiu`. That is the `li` expansion
    of ASPSX before 2.50 (maspsx `expand_li`); no C spelling reaches it through gcc.
  - A static census of retail bytes classified every row. `ori rX,$zero,K` (0 < K < 0x8000)
    occurs only in town: 22 pinned rows and 1 clean. No row anywhere mixes it with
    `addiu rX,$zero,K`.
  - The `ori` rows form address islands: 0x80874C9C–0x808757A0, 0x80877FEC–0x80878110,
    0x80878924–0x80878A78 and 0x8087FD58–0x808816D8. Every row inside them stays exact under
    `--aspsx-version=2.40`. Eleven rows between 0x80878180 and 0x80878714, and `func_80880298`,
    break under it: those are `addiu` TUs.
  - This is build evidence, not underdetermination: object files assembled by an older ASPSX.
  - Each row carries a proof record in `config/overlays/town.as_flags.jsonl`
    (`--aspsx-version=2.40`, the per-function as-flag route), and `tools/orzero_aspsx.py` does the
    rewrite. Every candidate was exact under the dial and not without it.
  - The dungeon `$0` pins are a different mechanism: a hard zero for `move $sN,$zero` or
    `return zero`, and the dial breaks them.
- **The landing lint learned port codegen identity.** 18 of the 20 `t45` rows were first refused:
  "edits a NON_MATCHING arm". Removing a pin removes its port fallback too (`#define zero 0`,
  `s32 zero = 0;`), and `port_view` compares text. Given the row, `pin_census.landing_refusal` now
  also accepts a port-arm edit when the `-DNON_MATCHING` build, at the row's own cell and compiler,
  generates identical assembly. `#if 0` text must still be unchanged.
  - Seven rows still had the nameless `#define ({...}) (value)` arms that 548963e9 left behind,
    and their port build does not compile. For those, `<name>.c.port_ref` names a commit whose text
    stands in (548963e9^).
  - Four rows whose current port build reads an uninitialized `zero` failed the identity, as they
    should. They landed in two steps. First a scored-only candidate (`rewrite(scored_only=True)`,
    no port arm touched). Then the full rewrite of the landed text as a tidy, which passes the
    identity because the leftovers are unused.
  - The eighth corrupted arm (`dungeon/func_809F33F8`, dead, preprocessor-only) was deleted.
- **`apply_candidates --cells` verifies in parallel.** It holds the cell switches until every verify
  has finished, then lands them with `common.set_row_cfgs`: one read and write per ledger table,
  one root export. Per-row `set_row_cfg` calls re-exported the roots under running verifies, which
  is why cell switches had to land with one worker.
- **Census notes:**
  - Pins by macro: `ASM_REG` 49%, `ASM_KEEP`/`_NV` 34%, fences 553.
  - `ASM_REG` by register: v0/v1/a0–a3 2,822, s0–s7 1,319.
  - 40 local `__asm__` wrapper defines are still invisible to `sites_of`: 34 call sites in 19
    files, mostly SLUS (`PIN_KEEP`, `LEGACY_ASM_KEEP`, `SCHED_KEEP`, …).
  - The single-pin rows' notes are the generic `UNRESOLVED … changes the X` text; binning them
    gave no new mechanism.
- **Launched after this gate:**
  - `scan --flags2`: the scheduling pair for the fences, `-mno-split-addresses` (it exists from
    2.8.0 and changes 2.8.x codegen) for 2.8.x address-split pins, and five flags that change
    2.6.3/2.7.2 codegen on a probe TU. Rows already carrying a flag are skipped.
  - A fold pilot: pinned single-use temporaries folded into their one use, 581 candidates in
    185 rows; `t38_unstage` is the staged-store special case.

## Round 12 (2026-09-13): the second flag set, stacking, hidden asm exposed, two lanes

Gated (100 windows MATCH, SLUS SHA-1 MATCH): **8,954 pins in 1,542 rows**. The count now includes 86 pins that were always there but
hidden. Net of that exposure, 168 pins came out:

- the flag switches, 87 (71 from the second set and 16 from stacking, one pin per row);
- the lanes, 4;
- `t48`, 3;
- the fold, 2;
- the cascade and T2, 72.

- **The owner's two decisions.**
  - Flag stacking: yes, capped at two flags per row, under rules 1–2, each switch undoable.
  - Hidden asm: expose it where it hides pins, and track the rest in STATUS.

  Both are recorded in HANDOVER, and STATUS carries two new lines.
- **Hidden asm, counted and exposed.** `pin_census.hidden_asm` classifies every `__asm__` the
  pin census could not see:
  - 59 raw empty-template statements in function bodies;
  - 52 calls of local wrapper macros;
  - 7 hand-written asm statements in bodies: C that is missing, including an
    `__asm__(".end func_…\n.if 0")` that hides the rest of `dungeon/func_804FE77C` from the
    assembler;
  - 113 symbol aliases (`T x __asm__("sym")`, a second typed name for one symbol: a missing type);
  - 448 file-scope directives, mostly `.set` absolute symbols.

  `tools/expose_asm.py` (journal `t47_expose_asm`) rewrote 98 statements in 66 rows to the `ASM_*`
  macro each spells exactly (`"=r"(x) : "0"(x)` → `ASM_KEEP`, `: : "r"(x)` → `ASM_USE`,
  `::: "memory"` → `ASM_MEM_BARRIER`, `""` → `ASM_SCHED_BARRIER`, a copy through an asm →
  `dst = src; ASM_KEEP(dst)`). It also expanded multi-statement wrappers verbatim and deleted their
  definitions. Every file was scored and passed the port-codegen lint. Two were refused: their
  wrappers' port definitions set a value (`zero = 0`), which `ASM_UNDEF`'s port form does not.
  Left hidden: 3 raw statements, 10 wrapper calls, 7 hand-written asm.
- **The second flag set (`scan --flags2`), 1,280 rows, 7.3 CPU-h: 94 pins in 71 rows.**
  - By flag: `-fno-cse-follow-jumps` 68, `-fforce-addr` 16, the scheduling pair 6,
    `-mno-split-addresses` 4. About 19 of the 94 are fences or barriers.
  - **Measured inert:** `-fno-peephole`, `-fno-function-cse`, `-fno-thread-jumps`,
    `-fno-force-mem` and `-mmips-as` were admissible on 232 to 834 of the first 834 rows, with not
    one hit. Every admissible cell is compiled in every stage-2 erasure call, so these five cost most
    of the scan's first 5.1 CPU-h. They are now excluded (`INERT`), and the rest ran roughly three
    times faster.
  - Lesson: pilot a new flag set on about 100 rows and drop flags that never hit, before the full
    scan.
- **Stacking (`scan --stack`), 158 of the 173 rows that carry exactly one flag: 20 pins in 16 rows.**
  The 15 largest rows are left for the next round. STATUS now counts rows with one flag and with
  two or more.
- **`apply_candidates --cells` in parallel, first production run:** 71 rows in 32 s, and 61 switches
  written by one `set_row_cfgs` call.
- **Two luna lanes.**
  - **`loadkeep`** (keeps on loaded values, the largest keep class): 1 of 12. `dungeon/func_800BF6A0`
    went to typed record indexing, a 0x14-byte `Entry` array in place of manual scaled addressing.
    Other lessons from the lane:
    - some keeps hold a load whose value is dead, which gcc's CSE deletes and retail kept;
    - some hold a page constant live across a call, where gcc would rematerialize it;
    - some fix the order of two independent loads.

    None of the three is a spelling.
  - **`fences2`** (live `ASM_SCHED_BARRIER`): 3 of 12. In `town/func_800B3834` and `town/func_8009AA74`,
    gotos into a shared return tail became direct returns. In `main/func_8001FAA8`, a store through a
    temporary became a direct store.
- **`t48_gotoreturn`** (the fence lane's CFG wins as a generator): a goto into a return tail is
  written as its own return, paired with one pin erased, fences first. It landed 3 of 290 rows.
  Most rows needed more than that one change.
- **Pilots and hand studies that did not pay:**
  - `t46_foldtemp` (a pinned single-use temporary folded into its use): 2 of 181.
  - A struct assignment for the 16-byte copy loop of `town/func_800B0994`: TOTAL 17. That copy is
    not a block move.
  - The symbol form of `dungeon/func_80093898`: not exact at any cell.
- **Census notes:**
  - Keeps by what the variable holds: loads 20%, arithmetic 17%, page literals 12%, constants 9%,
    parameter copies 6%.
  - The retail split-address signature (`lui $at` versus `lui $rN`) matches each row's cell family;
    the FSF rows with split loads are literal integer addresses. There is no mismatched family to
    harvest.
  - The live fences' neighbourhoods are mixed. The largest shape is a store followed by register
    work (81).
- **The cascade:** 47 records over 146 changed rows. T2 19, `t37` 8, `t48` 6, `t37b` 5, `t41c` 5, `t36` 2,
  `t44` 2; pass 2 applied nothing.
- **Evaluation.**
  - What worked: the CPU scans (87 switched rows) and the fence lane. At 3 of 12 its rate is the best
    of any lane so far, and luna is the cheap tier.
  - What did not: generators distilled from single lane wins (`t48` 1%, the fold 1%). The fence wins
    needed the surrounding branch structure rewritten too, not one lever. The five inert flags cost
    about 4 CPU-h.
  - Next: more fence lanes (56 fence rows with at most 3 pins remain), and the stacking scan resumed
    over its 15 largest rows and the 87 rows that just took a flag.

## Round 13 (2026-09-13): four fence lanes, the pin search on changed rows, `t49_looptest`

Gated (the search's publication gate, then 21 windows MATCH and SLUS SHA-1 MATCH): **8,873 pins in 1,529 rows**, 81 pins (the search 53, the lanes 11, cells 4,
`t49` 2, stacking 1, the cascade 10) and 13 fences removed.

- **Four luna fence lanes (`work/native_lane/fences3`–`fences6`, 12 rows each, every row with at most
  three pins):** 11 of 48 exact, each with one fence gone. Four shapes won, as in round 12:
  - explicit outcome blocks: `return_one` / `return_zero` labels in place of nested returns
    (`town/func_8032C6E0`);
  - success arms that call and return directly, so cross-jumping can no longer merge the tails
    (`dungeon/func_80097AB8`);
  - a do-while decrement moved into the loop test (`dungeon/func_818B1484`, `dungeon/func_818B11B4`);
  - a store written directly.

  The rows that failed all came down to the first scheduler's order between independent chains:
  address materialization against a delay slot, and two unrelated store/load chains. Every rewrite
  the lanes tried there kept the same dependency graph.
- **`t49_looptest`, from the fences4 wins:** a do-while counter's tail update moves into the test
  (`v -= 1; } while (v >= 0);` becomes `} while (--v >= 0);`), paired with one pin erased.
  - It is safe only when the update is the body's last statement (other variables' steps may
    follow) and the body has no `continue` or label.
  - It reproduces the lane's candidate for `func_818B1484` byte for byte.
  - Swept over 168 eligible rows: 2 (1%): the lane fix rarely transfers alone.
- **The pin search (`pin_search.py` baseline, tag `pins_changed_20260913`):** 515 pinned rows that had
  changed since the atlas harvest, lane rows excluded. 53 pins in 2.5 CPU-h. Published through its
  own gate.
- **The stock-cell scan resumed** over 239 changed rows: 5 hits. The 1999 compilers are no longer
  scanned, because their hits are never built. **Stacking** finished its last 56 rows: 1 hit.
  Both levers are thin now.
- **The cascade:** 9 records over 50 changed rows (T2 5, `t36`, `t37`, `t38`, `t41c` 1 each); pass 2 applied nothing.
- **Evaluation.**
  - What worked: the fence lanes. They are the only lever still removing fences at scale, at about
    one row in four on the cheap tier. The pin search on changed rows paid 53 for CPU alone.
  - Live fences now: 516.
  - What did not: the cell and stacking scans are nearly dry (6 hits between them).
  - Next: fence lanes over rows with more pins, since every row with at most three pins is now done
    or assigned; and hold the pin search back until enough rows have changed again.

## Round 14 (2026-09-13): six more fence lanes, joint erasures on changed rows

Gated (the erasure search's publication gate, then 18 windows MATCH and SLUS SHA-1 MATCH): **8,817 pins in 1,523 rows**, 56 pins and 9 fences removed. By source: `t16` 26 (11 rows), the joint
erasures 17 (4 rows), the lanes 10 (7 rows), the cascade 3.

- **Six luna fence lanes (`work/native_lane/fences7`–`fences12`):** 71 rows with 4 to 6 pins, the
  last of the fenced rows below 7 pins. 7 of 71 exact, 10 pins. The rate falls with pin count: the
  rows with at most 3 pins went 11 of 48. The winning shapes:
  - condition polarity, so the success arm falls through (`func_800ABD9C`);
  - direct returns in place of a shared zero-return label (`func_800BB728`);
  - direct stores in both arms, so cross-jumping cannot merge them (`func_80F87270`);
  - a `for` induction edge in place of a `do` loop (`func_80DBBFC8`);
  - a page literal written as the symbol array it indexes, `D_800DDE84[type_id]`, which removed 4
    pins (`func_800B7CFC`);
  - `abs()` for a manual conditional negate, twice (`town/func_800C2BFC`, `dungeon/func_8192365C`).
    `t16_absidiom` had missed both, because m2c spells the negate `d = 0 - d`. `t16` now accepts that
    spelling, which lifts it from 108 to 128 eligible rows (measured on the current tree).
  - The briefs now make every compiler call `cd` into the lane directory first. In round 13 a lane
    left `cc1 -da` dumps at the repo root; those were moved to `fences3/root_dumps/`.
- **Joint erasures (`pin_search.py --mode erasures`, tag `erase_changed_20260913`):** 245 rows with 2
  to 8 pins that changed since `b13b4cf2`, lane rows excluded, budgets 512 / 12 / 20 CPU-s. 17 pins,
  published through its own gate, for 401 CPU-s: 4 rows, each losing several pins together. These
  are subsets that no single erasure (T2) and no shape search reached. A row whose cell, flags or
  neighbouring code changed can open new joint removals.
- **The same over larger rows came back empty.** `--families-only` (the full set, variable groups,
  macro families) over 138 changed rows with 9 to 40 pins: 0 of 138, 55 CPU-s. Joint erasure pays
  only where the exhaustive subset walk runs, at 8 pins or fewer.
- **The cascade:** 3 records over 21 changed rows (`t37`, `t44`, T2 1 each); pass 2 applied nothing.
- **`t16_absidiom` with the `0 - x` spelling:** swept over 134 eligible rows, forced. 11 rows and 26 pins,
  the best return of any lever this round, and it came from one lane observation.
- **Evaluation.**
  - Worked: the lanes as auditors of the existing generators. One lane row showed that `t16`'s
    detector missed m2c's `0 - x`; a one-line fix then took 11 rows mechanically. Joint erasures on
    small changed rows paid 17 pins for 401 CPU-s.
  - Did not: the fence lanes' rate falls with pin count, 11 of 48 at up to 3 pins and 7 of 71 at 4 to
    6. `--families-only` erasures on larger rows found nothing.
  - Next: audit the other generators' detectors against m2c's spellings. A static check per
    generator costs no model time: which pinned rows hold the idiom's operators but are refused as
    ineligible. Fence lanes on the rows with 7 or more pins only if the audit runs dry.

## Round 15 (2026-09-13): the generator audit, t50_dofor, the search at four times the budget

Gated (15 overlay windows and the SLUS build MATCH): **8,755 pins in 1,523 rows**, 62 pins and 13 fences removed.

- **Auditing the generators against the lane wins.** Every generator was run on the base text of the
  33 lane wins that have one. The detectors mostly fired: t43 or t48 was eligible on five of the
  rows whose mechanism it claims. What failed was the candidate space. For each lane win, recording
  every candidate the claimed generator offered (no compile) and measuring its distance to the lane's
  exact output showed the closest candidate was never the lane's answer.
- **t48_gotoreturn:** its return-tail reader stopped at a pin line right after the label
  (`return_zero: ASM_SCHED_BARRIER(); return 0;`), so that tail was never a sink target. It now
  skips pin lines. On the lane bases it reproduces two lane results (`dungeon/func_800BB728` 5 to 4
  pins, `town/func_800B3834` 2 to 1). 16 more rows became eligible; the re-sweep of the 18 rows whose
  candidates changed landed 1 (`dungeon/func_800A1984`). A related check showed that an unused label
  left behind does not change the output.
- **t50_dofor (new):** m2c writes a constant-trip `for` as `v = 0; do { ...; v++; } while (v < N);`.
  t50 offers `for (; C; step)`, `for (v = C0; C; step)` and `while (C)`, then t41c's greedy erasure. It
  reproduces the fences12 lane's `dungeon/func_80DBBFC8`, but the sweep over 120 rows landed 0. In 34
  of the first 47 refusals a spelling was exact with every pin in place and freed nothing: gcc 2.x
  folds the entry test and emits the same code. A spelling that changes no pass does not free pins,
  which is the round 9 lesson again.
- **The shape census.** Counted over the pinned rows: fenced exit arms 5 rows, fenced label tails 4,
  stores into both arms after a join 64, staging across a fence 36, counted do-whiles 127. The
  single-lever generators for these were not built: t50's null result and the ~1% rate of every
  earlier single-lever generator (t48, t49, fold) say the lanes are the cheaper way to find the rare
  rows.
- **pin_search at four times the budget (`budget4x_20260913`, `budget4x_b_20260913`, `budget4x_c_20260913`):** in the changed-rows run
  (`pins_changed_20260913`), 249 of 515 rows stopped on a budget (151 on screens, 93 on CPU, 5 on
  verifies). Those rows hold 3,540 of the run's 4,182 pins and still found candidates at 5 to 7%. The
  233 without a candidate were searched again at 4800 screens / 24 verifies / 160 CPU-s. The first 197
  (`budget4x_20260913`, 31 min wall at 10 workers, CPU only): 16 rows with a candidate, 21 pins, about
  the rate the same rows showed at 1x (8%). 11 of the 16 came from rows that ran out of CPU budget
  AGAIN, so the search is still budget-limited there. The other 34 (`budget4x_b_20260913`, held back
  while t50 swept them): 1 row, 1 pin (`dungeon/func_81941338`). Then the 283 rows whose most recent search, anywhere, stopped on
  a budget (`budget4x_c_20260913`, 2,734 pins; the full-corpus 1x run `pins_restart_20260912` had 716
  such rows): 16 rows, 24 pins (7 of them from rows that ran out of CPU budget again). **The three
  runs together: 46 pins in 33 of 514 rows (6.4%), CPU only, no model.** Each published through its
  own gate.
- **Fence lanes fences13 to fences17:** 52 rows with 7 to 15 pins, rows in the search excluded. The
  brief now lists every fence-lane shape so far and tells the lane to expect to combine two changes.
  **8 of 52 exact** (fences13 1, fences14 0, fences15 6, fences16 1, fences17 0 of 4), one pin each:
  - direct field read-modify-writes in place of staged flags (`dungeon/func_818BDD8C`) or staged
    shift/add chains (`dungeon/func_80C16F00`), the shape fences4 found on `func_818BDB44`;
  - the branch after a call inverted (`dungeon/func_813284E4`);
  - the positive-height adjustment arm duplicated with explicit stores, on four copies of one
    function (`dungeon/func_80BC1BA8`, `80BC7BA8`, `80BCDBA8`, `80BD9BA8`);
  - `attempt = 0` moved into the shared `loop_ready:` block (`dungeon/func_80D3CBF8`).

  Five distinct fixes in 52 rows (10%), the rate the 4-to-6-pin rows showed. The misses were
  diagnosed as instruction order: 84 of the 116 fence misses so far read that way.
  fences16 left 62 `cc1 -da` dump files at the repo root despite the brief (moved to its
  `root_strays/`); the rule is now the first line of the lane prompt.
- **Copies of a function are not a lever.** Grouping the rows by token shape (identifiers and
  numbers folded) finds only 35 groups with a pinned member (111 rows, 615 pins), and the four copies
  above are not even structurally identical. Porting a win between copies would need fuzzy
  alignment for a small population.
- **The cascade:** the first pass over the 42 changed rows applied 6 (t37 2, t44 2, T2 2); the second applied nothing. The round's 62 pins: searches 46, lanes 8, cascade 6, t48 2.
- **Evaluation.** What paid: the search at four times the budget on rows whose last search stopped on a budget (46 pins, CPU only, the cheapest lever this round); fence lanes on 7-to-15-pin rows (8 of 52, five distinct fixes, about the 4-to-6-pin rate); the cascade (6). What did not: t50_dofor (0 of 120) and the t48 detector fix (1 row). Detector gaps are real but small once a lane's shape is rare, and a spelling that changes no pass frees nothing. What to do better: the lanes diagnose an ordering mechanism in 84 of 116 misses, and every single-lever generator lands about 1%, so the next step is an oracle rather than another generator. Round 16 gives one astra lane the first scheduler's ordering, with freedom of analysis and tooling (the owner's request). The 4x search still stopped on a budget in 95 rows; 18 of its candidate rows ran out of CPU again, and a 16x run there is the next CPU-only job. It can search while astra works, but publishes only after astra stops.

## Round 16 (2026-09-13): one astra lane on the first scheduler's order, and its tool `t51_sched_order`

Gated (the 16x search's publication gate, then 70 overlay windows and the SLUS build MATCH, then a comment-only regate): **8,645 pins in 1,507 rows**, 110 pins and 3 fences removed.

The owner asked for one round spent differently: pick the biggest blocker and give one astra lane
freedom of analysis, tooling and approach. The fence lanes had diagnosed an instruction ORDER in 84
of their 116 misses, and the atlas's three largest clusters are orders, so the blocker picked was
gcc 2.x's first scheduler (`work/native_lane/sched_astra/`, `gpt-6-astra`, about an hour). It wrote
its analysis before building anything, froze two held-out sets, then built and measured a tool.

- **The mechanism, from the GNU sched.c sources (2.7.2, 2.8.0, 2.8.1) and fresh CDK dumps.**
  - gcc 2.x schedules each block BACKWARD. The ready list is ranked by dynamic priority, then
    dependence class against the last scheduled insn, then LUID, and hazard selection can override
    the rank.
  - The priority is dynamic. When its last consumer is scheduled, a single-set live producer is
    promoted to launch priority (0x7f000001), which shortens live ranges.
  - LUID is recomputed over the RTL that survives CSE and combine. It is not the C line order. CSE
    can erase an early alias and leave only the late ABI setup.
  - An empty volatile asm is a full dependency cut: every register and all of memory, with pending
    reads and writes flushed. **A fence is not a tie-breaker, and no permutation of side-effect-free
    statements can stand in for one.** Only a changed dependency graph or CFG can, which is what the
    fence lanes' wins did.
  - Prologue saves do not exist at sched1: the backend creates them later, in saved-register-mask
    order. So statement order cannot reach the prologue-reorder cluster directly (0 of 20 held out).
- **Register pins are mostly not scheduler ties.** Among 255 REG sites with paired dumps, 204
  already differ before sched1 (a producer kept or lost by the pin) and 51 keep the same abstract
  order through sched1 but allocate differently. One repair that works there is splitting another
  local's lifetime.
- **The SHA-current population.** The atlas records still match the current text for 5,700 of the
  8,765 pins. 742 of those differ from retail only in instruction order: pure reorders, including 228
  REG and 59 fences. The three order clusters hold 143, 148 and 143 pins.
- **The tool, `tools/xform/t51_sched_order.py`** (with `sched_trace.py`). It keeps the unrelated pins,
  erases one pin at a time and compiles with dumps. It tries statement moves over up to six real
  statements (blank lines and comments do not count), whole-expression commutation, fusing a producer
  into its sole consumer, splitting a lifetime into a second local, and a `register` hint. It ranks
  these by the scheduler decisions it observed, and only `vf` accepts. Budget per row: 256 compiles
  and 24 verifies. Frozen held-out result: **fence-lane rows 6 of 165 (7 pins, of them 0
  ASM_SCHED_BARRIER and 2 ASM_MEM_BARRIER); atlas order rows 4 of 60 (6 pins)**, about four times the
  single-lever generators' rate. Its ten outputs landed (13 pins). The lane named split locals
  `t51_<var>`; they landed as `<var>_2`, which does not change codegen, and the tool now does the same.
- **Bounded unreachable classes (not all-C verdicts):** constant-alias setup order (60 compiles over
  six spellings and five cells: all identical); backend-created prologue save order at a fixed frame;
  a full asm barrier through statement permutation; a late or assembler order with its input held
  fixed.
- **The t51 sweep over the other 1,297 rows** (every eligible pinned row except the 225 held out and
  astra's ten; 12 workers, 55 min, CPU only): **61 rows, 79 pins, 2 `ASM_SCHED_BARRIER`**. At 4.7% of
  rows it matches the held-out rate (4.4%), so the held-out measurement was honest. By the rewrite that
  freed the pin: statement move 28, lifetime split 27, producer fusion 5, commutation 1. The lifetime
  split, which the dumps tie to allocation rather than to the scheduler, pays as often as the order
  moves. That is the biggest single-generator result since the goto-loop family (round 8).
- **pin_search at 16x the budget** on the 18 rows that found a candidate at 4x and ran out of CPU
  again (`budget16x_20260913`, 19,200 screens / 48 verifies / 640 CPU-s): 2 rows, 7 pins
  (`dungeon/func_800AA49C` 26 to 21, `dungeon/func_81330C74` 18 to 16).
- **The cascade:** the first pass over the 73 changed rows applied 9 (t37 2, t44 2, t48 2, T2 3); the
  second applied nothing. Counted by each row's first change this round, follow-ups included: t51's rows
  87 pins (79 plus 8), astra's rows 16 (13 plus 3), the 16x search 7. 16 rows became pin-free. REG went
  from 4,285 to 4,218 and KEEP from 2,094 to 2,071.
- **Comments after the split.** t51's first version inserted the new `<var>_2` declaration before the
  original declaration's trailing comment, so a pin note moved onto an unpinned line. Twenty comment edits
  put it right: 5 notes moved back onto their still-pinned declarations, 7 stale notes of pins t51's
  cleanup had erased, and 8 older orphaned pin notes in the same files dropped. Comments do not change
  codegen; the regate matched. The tool now inserts after the whole line, and its fuse rewrite no longer
  wraps an rhs that is already the local's own cast of one operand.
- **Evaluation.** What paid: t51, the lane's tool, is the best single generator since the goto-loop family (79 pins direct, 87 with follow-ups, CPU only), and its full-sweep rate matched the frozen held-out rate. The lane itself cost one astra session and replaced a wrong model of the scheduler with the right one. The 16x search paid 7 pins on 2 of 18 rows. What did not: fences. t51 removed 3 of 494, and the lane showed why: a fence is a full dependency cut, so only a changed dependency graph (the fence lanes' CFG and data rewrites) can replace one; the prologue cluster is created after sched1 (0 of 20). What to do better: put t51 in the cascade for changed rows (about 43 s a row); widen it with the directions the lane did not test (pin pairs, multiline statements, wider CFG); for fences, generate real dependencies, such as the direct field read-modify-write the lanes found three times; and run the 4x search on the 49 budget-stopped rows the round-15 lanes held.

## Round 17 (2026-09-13): larger budgets for t51 and the search, and t52 for staged stores across a fence

Gated (the lane-row search's publication gate, then 2 windows and the SLUS build MATCH): **8,628 pins in 1,507 rows**, 17 pins and 3 fences removed.

- **t51 at four times its budget** (1,024 compiles, 96 verifies per row) on the 223 rows where the
  first sweep used up its budget without a win (3,431 pins; the other 1,013 had run out of candidates
  instead): **6 rows, 10 pins**, 39 min at 10 workers. `dungeon/func_818B0E10` lost 5 pins (15 to 10).
  At the larger budget the producer fusion led (4 of the 6) over the lifetime split (2). The rate on
  these leftovers (2.7%) is about half the first sweep's (4.7%). The 44 of astra's 225 held-out rows
  that also ran out of t51's budget: 1 row, 1 pin (`dungeon/func_80FB176C`, 3 to 2, a lifetime split),
  6 min. Together 7 of 267 budget-limited rows (2.6%), 11 pins: a larger t51 budget is past its
  diminishing return.
- **pin_search at four times the budget on the 48 fence-lane rows** held out of round 15's searches
  (`budget4x_d_20260913`): 5 rows, 5 pins (10%), published through its own gate.
- **t52_fencestage (new).** The sched_astra lane showed that a fence is a full dependency cut, and three
  fence lanes had replaced one the same way: a value staged through temporaries, written instead as each
  store's own expression, e.g. a direct read-modify-write (`p->f = p->f | 0xC; ... p->f = p->f | 0x100;`),
  so the second store's read depends on the first store. t52 carries the temporaries' values
  symbolically through the straight-line run around a fence and rewrites every store that reads one. It
  tries every window that contains the fence, because the full run also holds unrelated locals that are
  read later. On the three lanes' base texts it reproduces two lane outputs exactly and goes one pin
  further on the third. Over the rows: 50 fenced rows eligible; the first 17 went 0 of 17 (each had 1 to
  10 exact-checked rewrites, none exact); the other 33 (held until the searches published): 1,
  `town/func_809548E4` (19 to 18 pins). **1 of 50 overall (2%)**: the rewrite compiles on most rows
  but is exact on few. The three lane rows shared a mechanism the rest of the fenced population mostly
  does not, so this is the usual single-shape rate, not an unlock.
- **t51 integration fixes found while landing round 16:** a declaration's trailing comment moved onto
  the new `<var>_2` line (20 comment edits), a doubled cast in the fusion rewrite, a lane-directory
  dependency, and `u8 * x_2` spacing. A first fix for the cast was wrong (`(s32) a * 2` casts only `a`)
  and a unit test caught it.
- **The cascade** (t51 now in the list): over the 13 changed rows, nothing. By each row's first change: t51 at 4x 11, the lane-row search 5, t52 1, with one fence each.
- **Evaluation.** What paid: only the budget escalations, and they have reached their diminishing return (t51 at 4x 2.6% of rows, the search on the held lane rows 10%). t52 confirmed that a single-shape generator built from lane wins pays about 1-2%, even for a shape the lanes found three times. At 17 pins this is the smallest round in many: the CPU levers are used up on rows that have not changed. What to do better: when the levers plateau, the owner-approved mode is one astra lane on the biggest blocker. The largest block is REG (4,207 pins). The sched_astra dumps place most register pins before sched1, in which producer survives CSE and combine, so that is the next lane's question if the owner agrees to spend astra again. Fences (488) are the alternative, as a dependency-graph question.
