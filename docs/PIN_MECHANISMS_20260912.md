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

## Round 18 (2026-09-13): phase censuses, two astra lanes (t53_reg_state, t54_pagebase), the lane kit and `sweep.py --processes`

Gated (the cascade's gate: 55 windows MATCH and SLUS SHA-1 MATCH): **8,521 pins in 1,493 rows**, 107 pins removed this round (9 in part 1 at be10db9f, 98 after it), 12 rows newly pin-free. Fences are unchanged: 488 live `ASM_SCHED_BARRIER`, 81 `ASM_MEM_BARRIER`. By each row's first change after part 1: `t53_reg_state` 47 rows, 55 pins (the lane's 7, the sweep's 40, and the cascade's follow-ups on them); `t54_pagebase` 27 rows, 43 pins (the lane's outputs and its sweep).

- **pin_search on the rows no search had seen at their current text** (`pins_unseen_20260913`): the
  181 pinned rows whose current sha256 matched no baseline result (10 never searched), 960 pins.
  **6 rows, 9 pins**, 0 fences, for 2,992 CPU-seconds (127 complete, 29 screen budget, 23 CPU budget).
  Published through its own gate (MATCH). The erasures mode on the 115 of them with 2 to 8 pins:
  **0** for 154 CPU-seconds. The rows the rewrites changed in rounds 14 to 17 hold nothing a plain
  search finds.
- **A random-sample phase census** (`work/native_lane/reg_astra/evidence/phase_census.py`, records
  and tables beside it). One pin erased at a time, one site per row, seed 20260913: 320 `ASM_REG`,
  150 `ASM_KEEP*`, 80 fences, 60 others. Both builds were compiled with `-da`, and every pass (rtl
  through dbr) was compared three ways: the operations (registers anonymised, copies and asm
  dropped) as a multiset, the same operations in order, and the stream with registers renamed
  (wiring). The register pins fall into four classes at combine:

  | class | sites | what differs |
  |---|---:|---|
  | ops | 94 (29%) | different operations at combine (the first operation difference anywhere: rtl 39, cse 24, combine 19, loop 12) |
  | wiring | 133 (42%) | same operations in the same order, different data flow (copies, lifetimes) |
  | late | 82 (26%) | identical at combine; the pin acts in allocation or later (35 of them differ earlier and reconverge) |
  | order | 11 (3%) | same operations, another order |

  This corrects the sched_astra reading ("204 of 255 register sites differ before sched1, which
  producer survives"): that measure included wiring. Only about a third of register pins change
  which instructions exist. `ASM_KEEP` erasures change operations mostly at cse (35 of 150) and loop
  (13): a keep pin hides a value from CSE. Fence erasures change the order mostly at sched (34 of 80).
- **t51 groups hook and t51b_pairs (new).** `t51_sched_order.T.groups(pins)` now names the erasure
  groups that seed the search (single sites, then the joint fence set), and `apply_verified` is a
  classmethod. On three rows with a stub scorer the old and new t51 journal identically. t51b
  overrides the groups with pairs (all pairs up to 8 pins, nearby pairs above), because joint
  erasures paid where single ones did not and t51 erased one pin per base.
  Result: **0 of 787** rows with 2 to 8 pins (reg_astra's held-out rows skipped), for 90,439 compiles
  and 8,817 verifies. Joint erasures that need no rewrite are pin_search's; a pair base under t51's
  one-site menu does not pay.
- **Page bases, the next blocker candidate.** Three of the first four `ASM_KEEP` sites whose erasure
  changes operations at cse are one shape: a constant page (`base = (u8 *)0x800D0000;
  ASM_KEEP(base); *(s16 *)(base + 0x1054)`) that CSE folds with its offset into one constant address
  once the pin goes; retail loads the page once into a named register. Pins on variables assigned an
  address literal: **739 in 274 rows** (365 KEEP, 202 REG, 139 KEEP_NV), 117 of the rows already at
  2.7.2-cdk. t29_addrsym has seen all 274: 169 current records, all refused, 121 with "no candidate
  exact at the recorded cell or at a CDK cell that admits the pinned text", about 25 detector gaps
  (port arms, no declaration, non-operand uses). The round-9 luirename luna lane (0/10) put the misses
  on the page pseudo's allocation (rematerialised into the allocator's preferred register, a
  short-lived base's live-range split lost). t53 could not settle the family, because it only erases
  `ASM_REG` sites and 537 of the 739 pins are keeps. So a second lane, page_astra, was briefed on this
  corpus, below.
- **page_astra lane (astra, 28 min) and t54_pagebase (new).** A focused census of the page-variable
  pins themselves (one per row, 273 sites) made the family one mechanism. 137 of the 189 KEEP page
  pins first differ at cse. The lane's findings:
  - A keep is an unknown register definition: its tied input keeps the value but its output hides
    the constant. Without it, `fold_rtx` folds page plus offset into one constant address. FSF
    2.7.2's `find_best_addr` accepts the fold before comparing address costs; 2.8.1 compares them.
  - At CDK and 2.8.x, combine proves a page and a positive disjoint offset share no bits and turns
    the PLUS into an IOR. MIPS rejects that as an address, so a signed load stays `lhu; sll; sra`.
  - The repair keeps the local and rewrites only its definition as the page symbol (`DungeonPage
    *level_page = (DungeonPage *)D_80080000;`), erasing one keep or the group. t29 deleted the whole
    variable and substituted every use, which changes allocation; it also refused typed views and
    complex operands, and tried only bare CDK cells.
  - Bounded unreachable cases: pure respelling of a closed constant (no zero-cost opacity), an
    otherwise dead page load, and a runtime-unknown base with no runtime producer.
  - Hypotheses that failed: address cost alone, integer or pointer type, literal-based views, a
    const or register local, a static const pointer, an external pointer object, OR spelling,
    64-bit intermediates, masking an aligned symbol, and negative-offset rebasing.

  Held out: H1 (t29's "no candidate exact" rows) 1 of 40, H2 (the other page-base rows) **5 of 30**;
  development 17 of 204 rows, 25 pins. Its 24 outputs: 21 landed (then 18 re-spelled without
  redundant casts, each verified), one refused by the port-build lint (the file declares the symbol
  only under `#ifdef __mips__` with a hidden `.set`), and two need a cell switch the sweep can make.
  t54 now tidies its own wins the same way, keeping a tidied spelling only if vf still says exact.
  Sweep over the 274 page-base rows (threaded, so cell switches land; 7 minutes): **8 more rows**. Two
  took a cell switch that keeps the row's flags (`town/func_8032F3C0` to `2.7.2-cdk -O1`,
  `dungeon/func_8194CF00` to `2.7.2-cdk -G0 -fno-schedule-insns -fforce-addr`), under rules 1-2. These
  are the two lane outputs `apply_candidates.py` could not land at the recorded cell. 10 rows refused
  because no page variable is left. With the lane's outputs, t54 changed 29 rows.
- **Lane kit (owner: set astra up for its best chance, harvest everything).** `tools/fetch_gcc_src.sh`
  puts the GNU sources of every cell in `toolchain/gcc-src/<version>/` (2.6.3 exists only as bz2; two
  lanes had fetched single files from GitHub). `tools/lane_eval.py` is sched_astra's `run_t51.py`
  made generator-agnostic (any module, any lane directory). `tools/phase_census.py` is this round's
  census, with the class taken at combine (reg_astra pointed out that an any-pass class counts
  differences that reconverge: 94/133/82/11 at combine against 99/132/81/8). `docs/LANE_KIT.md` lists
  what a lane gets before launch and what to harvest after.
- **reg_astra lane (astra).** On the owner's rule (astra when other avenues struggle), one lane with
  analysis and tool freedom on register pins, briefed with the census classes, the pinned build as
  an oracle for every intermediate pass, the 40 t51 register wins as exemplars, and two held-out
  sets frozen before it started (H1: 50 census rows stratified by class; H2: 60 population rows).
  It finished in 55 minutes (327K tokens). Its tool is `t53_reg_state` (`tools/xform/t53_reg_state.py`
  with `reg_state.py`). Held out: H1 2 of 50 (both in the ops class), H2 **4 of 60 (6.7%)**, six
  register pins, plus one development row, all independently verified. The integrated copy reproduced
  all seven through `tools/lane_eval.py` before they landed (`apply_candidates.py`); two spellings were
  then tidied and verified. Findings:
  - Agreement with the pinned build's pass streams is neither necessary nor sufficient for exactness.
    On 40 verified positives and 40 negatives, the combine stream agreed for 2 positives and 13
    negatives; normalised assembly for all 40 positives and no negative. Screen on assembly; use
    stream distance only to seed searches.
  - Combinations pay where single rewrites do not. At `80C96F24`, a local width change that worsened
    assembly distance (2 to 5) but improved stream distance seeded a producer fusion. Each alone was
    non-exact, by 5 and by 2 words.
  - A new producer spelling for page bases: a known byte page plus disjoint bits, written as OR
    (`(u8 *)((u32)ram_base | 0x174)`, `800CA184`, 932 words).
  - 35 of the 82 combine-equal sites differ at an earlier pass and reconverge. local-alloc needs a
    pseudo to live in one block with exactly one death before its priority matters (local-alloc.c
    470ff), so a lifetime split moves a pseudo between the allocators rather than changing its
    priority (`810876B4`).
  - Bounded unreachable finding: six ordinary-local spellings of a two-input fixture allocate the same
    register (2, not the pinned 16) at all five stock cells.
  - The existing menus emit candidates on most census sites (t51's move on 88 of 94 ops sites), so the
    misses are selection and combination, not missing shapes. t53 adds class-aware fairness and a
    two-rewrite beam.

  **Integration lesson: the verify budget was the bottleneck.** The first sweep pass used the lane's
  defaults (384 compiles, 24 verifies) and ran at 2.3 rows a minute with a load of 5.6 on 14 workers.
  Every one of the first 13 wins (the lane's 7, the sweep's first 6) was accepted on its first verify,
  an assembly-identical candidate. The closing round that scores non-identical candidates never won,
  but spent all 24 verifies on 86% of misses, and verifies serialise on the per-window lock in
  `build_ovl`. The sweep was stopped and resumed at 3 verifies (now t53's default). Check where a
  lane's wins spend their budget before sweeping its tool.

  **Then the GIL was the bottleneck.** At 3 verifies the sweep still ran at about 3 rows a minute on
  8 threads. t53 is Python-bound: on a 119-line row it takes 17 s, of which 5 s waits on gcc and 12 s
  is pure Python parsing dumps, and `sweep.py`'s worker threads share one GIL. Three fixes, each
  checked to leave results unchanged:
  - candidates parse only the passes `metrics()` reads (the seven lane outputs came back
    byte-identical, in 127 s against 253 s);
  - precompiled patterns and a `close_paren` that jumps between `( ) "` and backslash (0 differences
    over 39 dumps and 15,600 starts);
  - `sweep.py --processes`: worker processes, with the journal still written by one process. A cell
    switch is journaled `deferred` for a threaded rerun, because the row database's lock is a thread
    lock.

  On the page-base rows (the 172 outside page_astra's held-out sets, searched first): 8 rows, 8
  pins (4.7%), all by t53's generic levers (moves, lifetime splits, widths). It only erases `ASM_REG`
  sites, so it cannot reach the family's KEEP three-quarters.

  Sweep over every row with `ASM_REG` (1,159 searched, page_astra's held-out rows skipped, 8 processes,
  about 40 minutes): **40 rows, 40 pins (3.5%)**, no fences, 3 rows pin-free. Levers: lifetime split
  16, statement move 7, width 7, fusion 6, allocation host/unhost 3, declaration order 1. Together
  with the lane's 7 rows, t53 changed 47.
- **The cascade** (t53 with `--processes`, and t54, now in it): 10 rows over the 74 changed ones (t53 4, `t37_localwidth` 3, `t49_looptest` 2, `t41c_gotoloop_greedy` 1); a second pass found nothing, and neither did T2.
- **Evaluation.**
  - What paid: two astra lanes briefed from a census, each with the gcc sources, the exemplars,
    frozen held-out sets and `tools/lane_eval.py`. Each delivered a working tool in under an hour: t53
    at 3.5% of register rows, and t54 at 16.7% of the page-base held-out rows (29 rows in all).
  - The page-base census was what made the second brief sharp: one mechanism (CSE folding the page)
    instead of a family of anecdotes.
  - The harvest discipline held: reproduce the lane's outputs before landing, and verify every tidy.
  - What did not: `t51b_pairs` (0 of 787) and erasures on the unseen rows (0 of 115).
  - Integration cost: the lane's budgets and the thread-based sweep made the first t53 sweep six times
    slower than it needed to be.
  - What to do better: before sweeping a lane tool, check where its wins spend their budget and
    profile its Python time. Run Python-bound tools with `--processes`.
  - Next census targets: the KEEP family beyond page bases (most of its erasures change operations at
    cse), and the fences (488, unchanged this round).

## Round 19 (2026-09-13): the keep and fence census, `t53k_keep`, the keep lane

Part 1 gated (the search's publication gate, 15 windows MATCH and SLUS SHA-1 MATCH, then the cascade's
gate, 5 windows MATCH and SLUS SHA-1 MATCH): **8,491 pins in 1,492 rows**, 30 pins removed in 19 rows, 1
newly pin-free (`dungeon/func_80FDD7E4`); 488 live fences, unchanged. By source: `t53k_keep` 18 rows
(16 in its sweep, 2 in the cascade), `t53_reg_state` 4 (1 held-out page row, 3 in the cascade), the search
2, the cascade's width and T2 steps 6 pins.

- **Census 19** (`tools/phase_census.py`, seed 20260914, one pin per row, page-base rows excluded):
  250 keeps and 150 fences. Read the register-renamed (`abs`) table for the deciding pass, not the
  operations (`ms`) table: `ms` drops registers, so allocation effects fall through to the last pass,
  and dbr patterns carry insn UIDs that shift whenever an insn is erased (`ms` put 121 keeps at dbr,
  `abs` 5).
  - **Keeps**, class at combine: ops 104, wiring 61, late 73 (54 first differ at sched1), order 12. The
    first pass whose wiring differs is cse for 93. Two thirds are decided at or before combine: the
    keep hides an equivalence that CSE (or combine) uses once it is gone, folding the value into its
    uses (ops) or substituting the source register for a copy (wiring). Volatility does not separate
    the classes: `ASM_KEEP` and `ASM_KEEP_NV` split alike. The kept value is spread across kinds: in
    the ops class arithmetic 33 (13 on a load), constants 18, copies 15, loads 10, compound updates 5,
    calls 4; in the wiring class copies of another local or a parameter hold 33 of 61.
  - **Fences**: ops 26 (combine), late 124: the first scheduler 71, delay-slot filling 31, cross-
    jumping (jump2) 12, the second scheduler 9, greg 1. Five classes, not one mechanism.
  - Source (2.7.2 `cse.c`): an `ASM_OPERANDS` costs 1000, so CSE never substitutes it (line 720); a
    volatile one is `do_not_record` (line 1970). After a keep, the variable is an asm output CSE knows
    nothing about.
- **The t51 journal's scheduler inversions** (free: no compiles). For fence erasures the reordered
  pairs are memory against register work (load | arith 13, load | const 10, store | move 6, store |
  const 5), with no same-base memory pairs. Before the erasure the pair is never co-ready (64); after
  it, dynamic priority (38) or an equal rank (43) orders it. A fence is a dependency cut, not a
  tie-breaker, which is why t51's statement orders (a LUID tool) removed no scheduling fence.
- **`t53k_keep` (new):** t53_reg_state's search seeded from keep erasures. t53 gains a `sites()` hook,
  and its old seed list is reproduced on all 6,767 rows. **16 of 1,003 keep rows, 16 pins (1.6%)**,
  41 minutes on 8 processes. Its journal is the largest keep census so far: 2,958 one-keep erasures,
  ops 1,434 / late 846 / wiring 518 / order 160, first wiring difference at cse for 1,217. Allocation
  and order levers do not reach a value hidden from CSE.
- **t53 on the page lane's unswept held-out rows:** 1 of 19 (`dungeon/func_8194D354`).
- **pin_search baseline on the 62 pinned rows round 18 changed** (`pins_changed_r18`): 2 pins, 1,641
  CPU-s, published through its own gate after a drift check (both rows are t53k rows; t53k left them).
- **The cascade** over the 19 changed rows: 10 records in two passes (t37 3, t53 3, t53k 2, t37b 1,
  T2 1); a third pass applied nothing.
- **The keep lane** (`work/native_lane/keep_astra/`, astra): the biggest single mechanism in the census
  is the CSE hide, about two thirds of 1,889 non-page keep pins, and the page lane cracked one kind of
  it (page constants) in under an hour. The fences' biggest class (sched1) is where the last astra tool,
  sixteen luna lanes and three generators all sit near 1%. The brief carries the census per class and
  per kind, the page lane's mechanism and unreachable classes as the worked example, the cse.c lines,
  454 landed keep-removal diffs, t53k's per-site journal, and the harness helpers pre-copied.
- **Fence lanes (luna) fences18-20:** 164 fence rows were never given to a fence lane (63 with more than
  15 pins, 37 with 7 to 15, 29 MEM_BARRIER-only, 21 in other lanes, 14 slus/ovmovie). The 36 usable
  rows of the 7-to-15 pool go to three lanes. Each row names the fence whose lone erasure is nearest
  retail and the pass that decides it (sched1 21, dbr 6, combine 5, jump2 3, sched2 1), with the
  reordered pairs when a scheduler decides; eleven are within two instructions of retail.

### Part 2: the keep lane, three fence lanes, `t16b_fieldabs`

Part 2 gated (19 windows MATCH and SLUS SHA-1 MATCH): **8,475 pins in 1,492 rows**, 16 pins removed in 15
rows: 15 fences (13 scheduling, 2 memory) and one keep. Live fences: 475 scheduling (488 at the round's
start), 80 memory. The round: 46 pins, 15 fences.

- **keep_astra (gpt-6-astra, about 35 minutes of work):** its analysis holds; its tool does not land.
  - Mechanism by value kind, from five-cell controls and paired row dumps: a keep's tied output is a fresh
    unknown definition, and erasing it restores constant, register, memory and known-bit equivalences. A
    closed constant is substituted at the first CSE (`func_80B46E18`: CONST_INT(0) into three call
    arguments); a copy pseudo is replaced by its source (`canon_reg`, the oldest equivalent register); two
    equal loads fold into one; a dead load or arithmetic loses its consumer at jump and vanishes; known
    bits make an OR result and a truncated copy interchangeable; combine merges a call result's copy.
  - Its productive construct was a one-trip `do { v = e; } while (0)` around the kept value's producer.
    The loop notes stop the first CSE (`cse_end_of_basic_block`) and make the scheduler add dependencies
    (FSF 2.7.2 `sched.c:2053-2080`). Plain braces and `if (1)` fail on the same rows (0 of 8 each), so the
    notes are causal. Held out: H1 4 of 40, H2 7 of 40, every hit a keep traded for a one-trip block.
    census.py counts a one-trip block like a pin, so none land. The brief did not list the scaffolding
    (the fence briefs do); LANE_KIT now carries the list verbatim. The 40 exact trades are refused
    evidence in `ledger/refused_trades.jsonl`, which `tools/pin_evidence.py` now reads as a third source
    (`one-trip-block` records): at those keeps a block boundary at the producer reproduces retail, so the
    original likely had a real block, loop or macro boundary there.
  - Bounded unreachable (same state, no extra runtime work): a zero-instruction unknown definition of a
    closed constant or an unchanged same-mode copy; keeping an otherwise dead nonvolatile producer; a
    runtime-unknown producer when retail has no load, call or store for it; repeated identical loads with
    no aliasing event between them. Unresolved: KEEP4/MEMDEP early-clobber, hard registers, most
    arithmetic and known-bit cases. Its advice: real joins (a true phi between different values kept a
    separate register in its control), sub-word producer types, and the census tool's label
    normalisation.
- **Fence lanes fences18-20 (luna, 36 never-laned rows with 7-15 pins): 10 of 36 exact (28%)**, the best
  fence-lane rate so far; each row named its nearest fence and its deciding pass.
  - fences18 (3): a counted `for` in place of a do-while (`dungeon/func_8028A5D8`); `abs()` for two
    staged negates with a fence above them (`dungeon/func_80E0F7C0`); an initialisation moved after the
    record setup, which also freed a keep (`town/func_8080C324`).
  - fences19 (5): one temporary reused for two halfword copies (`dungeon/func_8196096C`); four copies of one
    transfer function where the slot keep moves after the direct store and the fence goes
    (`func_80E91000`, `80E9D000`, `80EA3000`, `80EAF000`). Those four remove a fence and relocate a keep:
    a weaker kind of win, accepted because nothing is added.
  - fences20 (2): a counter update duplicated into both arms of the dispatch test
    (`dungeon/func_80084084`); direct 0x80 stores in the zero-state arm, so cross-jumping cannot merge
    the tails (`dungeon/func_8102F83C`).
  - The misses read as before: independent pairs ordered by priority or a tie (sched1), delay-slot
    ownership (dbr), tail merging (jump2).
- **`t16b_fieldabs` (new, from the fences18 win):** a field's absolute value staged through a temporary
  (`x = F; ... if (x < 0) { x = -x; } ... F = x;`, usually two fields with a fence above the loads),
  written as `F = abs(F);`, with the run's fences and the temporaries' pins erased and unused declarations
  dropped. t16 was eligible on the lane's row but offers only `x = abs(x);`, keeping the staging the fence
  ordered. It reproduces the lane's output (identical assembly) and landed the other 5 census rows, one
  fence each; its detector's 3 further rows came back noop.
- **Joint erasures on 82 rows changed since round 14 (2-8 pins):** 0. **The cascade** over the 15 changed
  rows: nothing.
- **Evaluation.**
  - Worked: fence lanes briefed with each row's deciding pass and nearest fence (10 of 36, against 8 of 52
    and 7 of 71 before); a generator from a lane win in the same hour (t16b, 5 rows); t53k (18 rows);
    reading the census by its wiring table.
  - Did not: the keep lane's tool (all trades), because its brief omitted the scaffolding list; joint
    erasures (0 of 82).
  - Better: every brief carries the scaffolding list verbatim. A refused trade is still a measurement.
    Run a guarded landing script from its own command line: `pgrep -f "[s]weep.py "` matched a wrapper
    shell that had just run a sweep.
  - Next: re-lane the earlier fence-lane misses with the round-19 packs (158 of 183 rows still fenced),
    each row quoting its previous lane's verdict.

## Round 20 (2026-09-13): fence re-lanes, `t57_keepafterstore`, the polarity flip by hand

Gated (8 windows MATCH and SLUS SHA-1 MATCH): **8,466 pins in 1,492 rows**, 9 pins removed, all
scheduling fences; 466 live scheduling fences, 80 memory. By source: t57 4, the re-lanes 3, the polarity
flip by hand 2 (one row).

- **`t57_keepafterstore` (new):** the fences19 wins' shape (a fenced `slot = base ± N; ASM_KEEP(slot);
  base[±N] = v;` with the keep moved after the store and the fence dropped). Each of the four transfer
  copies held a second fenced slot of the same shape: 4 applied, one fence each. The shape occurs nowhere
  else in the tree.
- **Fence re-lanes fences21-24 (luna, 44 rows):** rows an earlier fence lane (fences2-17) failed on, each
  quoting that lane's verdict, with the round-19 row facts. **4 of 44 exact (9%)**, against 28% on
  never-laned rows in round 19: fences21 0/12, fences22 0/12, fences23 2/12, fences24 2/8. A second look
  at a failed row pays about a third as well as a fresh row.
  - Landed: a reused variable split into two locals (`dungeon/func_8008C504`); a fenced dispatch test's
    polarity flipped so the other target falls through (`dungeon/func_8180A214`, `town/func_800C217C`).
  - Refused: `town/func_80092AB0`, exact only with a NEW branch whose two arms hold the same stores,
    placed before the existing `if (callback != NULL)`; the stores in both arms of the existing `if` miss
    by 12. A branch that exists only to shape code is scaffolding, like a fake dependency: recorded in
    `ledger/refused_trades.jsonl` (`identical-arm-branch`).
- **The polarity flip by hand:** a census found 5 fenced `if (c) { FENCE; goto A; } goto B;` sites in 4
  rows, two of them the lanes' own. `dungeon/func_80090C24`, both sites flipped (`if (!c) goto B; goto
  A;`): exact, 2 fences. `dungeon/func_800C289C`: not exact. Hand-verifying two rows was cheaper than a
  generator.
- **Shapes too rare for generators:** a fence above an update feeding both arms of the next `if` (4 sites
  in 4 rows); a fence above a constant staged into a shared store tail by `goto` (3 sites). Left to the
  lanes; the pack builder's brief now lists every round-19/20 winning shape and the two refused forms.
- **An artifact of normalised assembly:** three rows (`dungeon/func_8008D730`, `func_800C5368`,
  `func_81323F78`) have a lone fence whose erasure compiles to the same normalised assembly, yet T2's
  verify at the current text said not exact. The normalisation hides the difference.
- **Evaluation.** Worked: generators and hand passes built from lane wins (t57 4 fences, the flip 2).
  Did not: re-lanes (9%), so they stop. Next: the 63 never-laned fence rows with more than 15 pins,
  with the round-19 packs (fences25-28 first, the 48 smallest).

## Round 21 (2026-09-13): fence lanes on rows with more than 15 pins, `t57b_keepafternext`

Gated (9 windows MATCH and SLUS SHA-1 MATCH): **8,440 pins in 1,492 rows**, 26 pins removed: 20 fences
(16 scheduling, 4 memory), 4 keeps, 2 register pins; 450 live scheduling fences, 76 memory. By each row's
first change: the lanes' 7 rows 15 pins (with their cascade follow-ups), t57b's 7 rows 11.

- **Fence lanes fences25-28 (luna, the 48 smallest of the 63 never-laned fence rows with more than 15
  pins, 16-29 pins each): 7 of 48 exact (15%)**, against 28% at 7-15 pins in round 19; every output
  admissible (no identical-arm branch, no one-trip block).
  - fences25 (1): a page literal and its keep replaced by the symbol the NON_MATCHING arm already named,
    and a staged temporary inlined (`dungeon/func_8132B8AC`).
  - fences26 (1): the inner collision test inverted into an early return (`dungeon/func_80095160`).
  - fences27 (3): an existing keep moved after the statement that follows it, the fence above dropped
    (`dungeon/func_818BDEBC`, `func_818C3B90`, `func_8197C800`): t57's slot case in general form.
  - fences28 (2): a staged field update written as direct arm-local read-modify-writes
    (`dungeon/func_8186F0C4`); a pointer setup moved after its scalar producer (`dungeon/func_818B7F38`).
- **`t57b_keepafternext` (new, from the fences27 wins):** t57 generalised - a fence over `v = e;
  ASM_KEEP(v);` and one ordinary statement; the keep moves past that statement and the fence goes. t57
  gains a `find_sites` class hook that t57b overrides (no module patching under the sweep's threads). It
  reproduces all three fences27 outputs (identical assembly). Swept over its 34 eligible rows outside the
  lane rows: 7 applied, one fence each (a third fenced site in each of the four transfer copies, and
  `dungeon/func_818B1664`, `func_81978428`, `func_819835AC`); 1 more in the cascade.
- **The cascade** over the 14 changed rows: 10 records in one pass (t41c 2, t37, t38, t41b, t44, t49, t53,
  t57b, T2 1 each).
- **`t58_nmsymbol` (new, from the fences25 win, swept after this gate):** a pinned matching arm replaced
  by the NON_MATCHING arm that already names the symbol; 14 eligible rows.
- **Evaluation:** the fence-lane rate holds at 15% on rows with more than 15 pins, half the 7-15 rate and
  still the best model-time lever for fences. Keep relocation (t57, t57b and seven lane rows) is now the
  most frequent fence win: the fence sits between a kept value and the next statement, and the keep placed
  after that statement holds the same order without a barrier.

## Round 22 (2026-09-13): the largest fence rows and the memory barriers; `t58_nmsymbol` measured

Gated (10 windows MATCH and SLUS SHA-1 MATCH): **8,432 pins in 1,491 rows**, 8 pins removed (6 memory
barriers, 1 scheduling fence, 1 `ASM_USE`), `town/func_800B6514` pin-free; 449 live scheduling fences, 70
memory.

- **`t58_nmsymbol` (built in round 21, from the fences25 win): 0 of 14.** The first version deleted the
  NON_MATCHING arm, and every candidate died on sweep.py's unscored-arm check (`unscored-arm-edit`): a
  generator must never touch a NON_MATCHING arm. Kept and copied into the matching arm, still none is exact
  alone. A NON_MATCHING arm is evidence, not a lever by itself; the fences25 win also needed the fence above
  removed and a temporary inlined.
- **Fence lanes fences29-32 (luna): 7 of 41 exact (17%).**
  - The 14 largest never-laned fence rows (32-89 pins, fences29-30): 1 of 14. A statement moved past the
    loop-back test (`dungeon/func_807B0B3C`).
  - The 27 never-laned rows whose only fences are memory barriers (fences31-32; the pack builder now picks
    either fence macro and names it, and those briefs explain a memory clobber): 6 of 27 (22%).
    - Staged field values written as direct `|=` read-modify-writes (`dungeon/func_800BB400`,
      `func_80E07054`): the barrier had stopped CSE merging the reloads the original made.
    - A slot pointer built as `D_X + 0xFA` indexed by the slot (`dungeon/func_80CC2828`).
    - A pure computation hoisted above the branch that used it (`town/func_800B6514`,
      `dungeon/func_818E6F98`).
    - A staged tile store written as one indexed store, and a shared `row + 1` merged out of both arms
      (`town/func_800B9CC8`).
  - Two outputs carried a lane comment (`/* memory barrier erased for this candidate */`), stripped before
    landing (comments do not reach the bytes).
- **The cascade** over the 7 changed rows: 1 record in one pass.
- **Evaluation.** The fence-lane rate by row size, fresh rows with the round-19 packs: 7-15 pins 28%, 16-29
  pins 15%, 32-89 pins 7%; memory-barrier rows 22%. Every never-laned fence row has now been laned except
  13 slus rows and one ovmovie row. Next: the fence-lane recipe applied to keeps. The t53k journal names
  622 keep rows, unchanged since it measured them, whose nearest single keep erasure is within 3
  instructions of retail (258 with fewer than 5 pins); luna keep lanes on those, each row naming the keep,
  its class, its deciding pass and what it holds, with the refused forms listed verbatim.

## Round 23 (2026-09-13): keep lanes with the fence-lane recipe, `t59_offsetsym`

Gated (4 windows MATCH and SLUS SHA-1 MATCH): **8,425 pins in 1,489 rows**, 7 pins removed (5 keeps, 1
register pin, 1 scheduling fence), `dungeon/func_800C72B4` and `town/func_8096B16C` pin-free; 448 live
scheduling fences, 70 memory. By source: the lanes 3, t59 3, the cascade 1 (t41c).

- **Keep lanes keeps1-4 (luna, 48 rows): 2 of 48 exact (4%)**, against 15-28% for fence lanes built the
  same way. The rows were unchanged since t53k measured them and their nearest single keep erasure was
  within 3 instructions of retail (the t53k journal names 622 such rows; these are the 48 with the fewest
  pins). Each row named that keep, its class at combine, the pass whose wiring first differs, what the kept
  variable holds and the erasure's residue; the brief carried keep_astra's mechanism by value kind and the
  refused forms verbatim (`build_keep_lanes.py`, `keep_lane_brief.md`, in `tools/lanes/` since round 24).
  - keeps4 (2 of 12): the loop decrement moved after the two calls that read the value
    (`dungeon/func_800C72B4`); a kept page plus an offset written as the symbol the file already names
    (`town/func_8096B16C`, `(volatile SourceEntry *)D_80126A18`).
  - keeps1-3 (0 of 36) missed by 1-5 instructions on nearly every row, and named the same mechanisms again
    and again: CSE rematerialises or shares a constant, coalesces a pointer or channel copy into its
    source, combine folds an offset or a decrement into the address. That is the class keep_astra bounded
    in round 19: a closed constant or an unchanged same-mode copy has no zero-cost C spelling without a
    genuinely different producer. **A near miss by assembly distance is not a near miss in C when the
    difference is an equivalence CSE is entitled to use.** Keep lanes stop.
- **`t59_offsetsym` (new, from the keeps4 win):** a kept page literal used with an offset whose symbol the
  file already names (an extern or the NON_MATCHING arm's spelling), rewritten one use at a time, the page
  and its keep dropped once nothing else reads them. t29_addrsym (every use, at a splitting cell),
  t54_pagebase (the page's own definition) and t58 (the whole matching arm) all missed that row. It
  reproduces the lane's output (identical assembly). 142 such uses in 74 rows; swept over the 66 eligible
  rows outside the lane rows: 2 applied (`dungeon/func_80084084`, where m2c had named the page local
  `D_800E0000`, two uses and both page keeps gone; `dungeon/func_81335C70`, `held_base = &D_80083460;`).
  t29 and t54 had already taken most rows where a symbol pays.
- **fences33 (luna): the 13 slus fence rows no lane had: 1 of 13.** `slus/w_80040CBC`: the store after an
  `if`/`else` written in both existing arms, the fence below gone. Every fence row has now been laned except
  one ovmovie row.
- **pin_search baseline on the 35 pinned rows changed since round 19 part 1** (`pins_changed_r23`): 0 pins;
  28 of 35 stopped on a screen or CPU budget. The rows these rounds changed were changed by lanes and
  generators that had already taken what a local search finds.
- **Sizing the register pins for the same recipe:** the t53 journal names 443 REG rows, unchanged since it
  measured them, whose nearest single REG erasure is within 3 instructions (147 with fewer than 5 pins). But
  for register pins the first wiring difference is at `rtl` on 388 of them (a hard-register declaration
  changes the RTL from expansion on), and 255 are `wiring` at combine: allocation choices. The per-row facts
  that made fence lanes pay say little there, and earlier luna lanes on allocation rows went 0 of 10 twice.
- **Evaluation.** Worked: generators from lane wins (t59). Did not: keep lanes (4%), the changed-rows search
  (0). Fence lanes have run through their pool. The next lever needs a new idea rather than the recipe
  applied to another family.

## Round 24 (2026-09-13): lane tooling into the repo, the register census re-read, site shapes, wrap-up

Gated (2 windows MATCH and SLUS SHA-1 MATCH): **8,422 pins in 1,489 rows**, 3 pins removed (2 register pins, 1 keep); fences unchanged (448 scheduling, 70 memory).

- **Lane tooling moved into `tools/lanes/`** (it lived in a session scratchpad, where a new session could not
  find it): `build_fence_lanes.py` (fresh packs and `--relane`, the round-19 and round-20 builders merged; the
  brief is now the template `fence_lane_brief.md`, listing every fence-lane win from fences2-33 and the
  refused forms verbatim), `build_keep_lanes.py` (`--classes` picks by class, per the census rule) with
  `keep_lane_brief.md`, `launch_lane.sh` (luna by default, the PID in the lane directory), `land_lanes.sh`
  (the landing transaction: the lane filter, the cascade with t16b, t57, t57b and t59, tidy, T2, one gate;
  this round's landing ran through it) and `freeze_heldouts.py` (keep_astra's held-out freeze, generalised).
  LANE_KIT gains the rule round 23 taught: a near miss by assembly distance is not a near miss in C, so pick
  a lane's pool by class as well as residue.
- **Two leftover lane outputs landed.** Both had been exact since their lanes ran, and the port build
  (`-DNON_MATCHING`) refused both; the refusals are in `ledger/sweeps/lane_page_astra.jsonl` and
  `lane_regrename.jsonl`. `dungeon/func_8188C800` (page_astra): the page literal and its keep written as
  `D_80080000`, whose declaration sat inside the file's `#ifdef __mips__` block with its `.set`; the
  declaration moved out beside the other externs (as 30 other files declare it), the `.set` stays.
  `dungeon/func_80F03000` (regrename): the register pin's variable merged into `start_tile_y`, which the
  function has already finished with; the lane had also renamed the NON_MATCHING arm's own declaration,
  a redeclaration in the port build, and that line is restored. The cascade then took the row's second
  register pin: `t44_doloop_greedy` wrote its `goto state_two_check` loop as a `do`-`while` (8 to 6 pins).
- **The register census, re-read (`phase_census.py`, 300 register sites, seed 20260915).** Round 23 read
  "the first wiring difference is at `rtl` on 388 of 443 near-miss rows" as allocation choices. The wiring
  table is the wrong one for register pins. The declared hard register changes the first-appearance numbering
  that stream is renamed by, so it differs from expansion on even where nothing else does: in one `late`
  row the rtl and cse differences are register numbers alone, and combine is identical. The register-anonymised tables (operations and their order) cannot see a name:
  - **206 of 300 (69%): operations and order identical through the first scheduler.** The pin only
    chooses registers. By class at combine: wiring 120, late 86. By first difference after allocation:
    greg for every wiring site; greg 46 and sched2 36 for late.
  - **77 (26%) change operations before combine** (rtl 31, jump 3, cse 18, loop 13, combine 12): the hard register
    hides a value from CSE, the keeps' class.
  - So round 23's conclusion holds, measured the right way: two thirds of the 4,146 register pins are
    allocation choices. reg_astra (round 18) proved no class unreachable and named the lever: whether a
    value is local or global to the allocator, the allocator's suggestions, and its priorities.
    `t53_reg_state` searches that lever at 16 sites a row.
- **Site-shape census (`tools/site_shapes.py`, CPU only).** Every live pin site is keyed by its macro and
  its line with one non-blank line either side: comments and casts dropped, the pinned variable spelled V,
  identifiers I, numbers N. The t53/t53k per-site facts are joined in.
  - **8,435 sites fall into 5,664 shapes; 4,640 of them occur once, and the top 30 cover 7%.**
  - The pin line alone concentrates (the top 30 cover 80%), but that is the macro's own spelling
    (`ASM_KEEP(V);`) and carries no mechanism.
  - The shapes that recur with context: kept page constants used with an offset
    (`V = 0x800E0000; ASM_KEEP(V); p = V + N;`, about 110 sites, class ops), which is the page family
    t29, t54 and t59 have worked; keeps next to keeps; and one function repeated across overlays.
- **Transfer copies are already harmonised.** 294 groups of functions identical up to names and numbers
  (pins and register declarations dropped) cover 1,030 rows. Only one group has members with different pin
  counts: 2 rows with 1 pin each, whose pin-free copy compiles at another cell. Earlier rounds carried each
  win to the copies, so an erasure guided by a copy has nothing left to take.
- **Evaluation: the owner's 20-30 patterns.** Right at the level of mechanism:
  - register pins: allocation 69%, operation changes 26%;
  - keeps: the CSE hide, by kind of value;
  - fences: five deciding passes.

  Wrong at the level of source: at one line of context 4,640 of the 8,435 sites have a shape of their
  own, so the generators built from recurring shapes have taken what recurs. What remains needs a search per mechanism
  (t51, t53 and t53k have that form), or a lane that finds a new move for the largest class: register
  allocation choices.

## Round 25 (2026-09-14): two astra lanes in parallel (allocation choices, keeps), the tail-slot pins tested against the real toolchain

Owner's rules for the round: astra is fine when it can open a large piece; agent work runs through
workflows with an explicitly chosen model (opus/sonnet), never Fable-inheriting subagents; orchestrate,
decide on the data, and change approach when the data says so. Landing count: see the round's entry in
HANDOVER (part 1 lands the lane outputs, the t61 sweep and the cascade; part 2 the t60 sweep and the
diagnosed luna packs).

- **alloc_astra (astra, 87 min) on the register pins that only choose a register** (206 of 300 in the
  round-24 census; 2,391 allocation-only sites in the current population). Tool `t60_alloc_inputs`:
  **H1 0/40 (0/31 allocation-only), H2 2/40**; both wins are t51/t53-family combinations (a lifetime split
  plus a statement move; hostwide reuse), found in about 250 observations and one verify each where t53's
  journal had 331 observations and no win on the same source. The lane's lasting artifact is an
  **observer of the stock allocator**: `allocator_gdb.py` runs the unstripped i386 cc1 under gdb and reads
  local-alloc's quantities (births, deaths, weighted refs, size, suggestions, attempt order, result) and
  global.c's allocnos (preferences, conflicts), validating each trace by assembly equality with a normal
  compile. It covered 2,385 of 2,391 allocation-only sites (`evidence/trace_sites.jsonl`, per-row traces in
  `scratch/trace_population/`); generalised as `tools/alloc_trace.py`.
  - Mechanisms confirmed with traces: a suggestion (a copy to or from a hard register, an arithmetic tie)
    outranks numeric priority (`town/func_800A10FC`: the erased callback, priority 3,333, takes r2 by
    suggestion; the address, priority 10,000, then takes r3); local/global membership follows the lifetime
    shape (`810876B4`: four refs global to two refs local); global allocation prefers registers already in
    use over a lower free number (`818EC800`); declaration order settles a genuine GLOBAL tie in all five
    cells (a fixture: seven assembly lines swap) but never local birth order.
  - Reasons for the actual allocation, per site (overlapping; journal sites): hard-register-scan-order
    357, suggestion-selection 195, pseudo-eliminated-before-allocation 106, call-clobber-exclusion 102,
    earlier-quantity-conflict 78, target-register-already-selected 75, global-scan-order-or-class 49,
    preexisting-hard-conflict 40; 973 of 2,391 current sites carry only the coarse "global competition or
    scan order" label. By register class: saved 820, argument 681, return 674, other 216.
  - **Allocator-input agreement is not a better acceptance screen than assembly distance** (38 landed
    controls: normalized assembly AUC 1.0, allocated-operand projection 0.913, peer allocator-input
    projection 0.475). The pinned hard local has no allocatable pseudo to reproduce literally.
  - Failed: "stock lreg prints the quantity internals" (it prints assignments only; gdb is needed);
    "priority alone chooses" (no); "declarations control local order" (no); "reuse is a lever t53 lacks"
    (`natural.hostwide` has it; a 20-row pilot 0); "the fake-dependency records are a pure allocation
    class" (7 of 22 mapped). Bounded unreachable: six ordinary spellings of a leaf intermediate cannot
    select a saved register in any cell. Four unsuggested equal-priority local ties are named as direct
    targets (`town/func_8047E1C0`, `dungeon/func_8199A800`, `dungeon/func_819835AC`, `dungeon/func_800C29F0`).
  - Read as a decision: the lane found no new lever, and a mechanism-level search on this class pays
    about 5% on the population. The observer turns the class into DIAGNOSED rows (which register is held
    by which value, which copy suggested the choice), which is what a row lane can act on; round 25 part 2
    measures that per reason with four luna packs (`tools/lanes/build_alloc_lanes.py`).
- **keep2_astra (astra, 34 min) on the 1,871 keeps outside page rows**, briefed with the scaffolding list
  and the previous keep lane's 40 refused one-trip outputs as the map of where a boundary works. Tool
  `t61_naturalkeep`: **H1 1/40 (ops 1/18), H2 0/40**; but its sweep over 707 rows landed **20 rows, 20
  keeps (2.8%)**, plus its six exact outputs. The one productive family, `join-consumer`: one to three
  existing consumer statements distributed into the arms of an EXISTING branch (an implicit else
  synthesised where needed; the owner-accepted dup-after-if shape). The work stays separate through
  scheduling, then jump2 cross-jumps the common tails and emits retail's single sequence; in one row it
  also keeps a saved sub-word copy (`SET HI91`, `AND(SUBREG(HI91))`) alive through combine. Candidate and
  pinned wiring become equal at jump2 in every win. No existing generator constructs a branch history.
  - Full census of the population (1,871 keeps erased one at a time, label ids corrected): 669 identical
    through combine (first difference sched1 455, sched2 75, greg 63, jump2 22, lreg 19, none 35), 1,196
    change CSE or combine, 6 transient. Class at combine: ops 621, wiring 467, late 687, order 96.
  - Nine natural-shape menus produced zero (prefix producer into arms 147 variants, role exchange, later
    source update, mask as mode, sub-word producer type, field increment, real do/while/goto rewrites).
    The five-cell fixture (100 controls) bounds four respelling families as unreachable.
  - The reviewer (an opus workflow, LANE_KIT item 2) found the lane-path import (`from keep_shapes`
    resolved only under lane_eval's sys.path), a dropped indentation on a sole-body erasure, a doubled
    cast and `u8*` spacing; fixed in the lane copies, reproduced 6/6 byte-identically, then copied. The
    swept tool therefore differs from the lane's frozen hashes by those fixes. The sweep ran with
    `T61_VERIFY=3`: every win came on the first verify of an assembly-identical candidate.
- **Tail-slot pins: the toolchain hypothesis refuted twice, then the refutation itself refuted by a
  skeptic.** The owner asked for the parked stock-ASPSX check. An opus workflow (run + skeptic,
  `work/tailslot_aspsx/REPORT.md`) fed the pinned and the unpinned gcc output of all 126 rows to genuine
  ASPSX 2.56-2.86 (the SN binaries under the sibling decomp repository's `toolchain/psyq/`, run with wibo):
  **0 of 655 records put the dead value in the tail-j delay slot**; the genuine SN cc1 at every PsyQ level
  (`CC1_DIFFERENTIAL.md`) is byte-identical to the decompals rebuild and never fills the slot either. Those
  two results stand. Their CONCLUSION ("a toolchain gap, no C shape") was wrong, and a Fable skeptic lane
  the owner asked for (`work/tailslot_skeptic/REPORT.md`) showed why:
  - **254 of the 256 pins sit on an intra-function jump, not a call.** Solving each row's base from its own
    retail `j` targets puts the "callee" inside the row for 254 sites (123 of 126 rows have every `j`
    intra-row); at 39 sites the word before the "callee" equals the delay word, gcc's reorg.c thread fill
    (`toolchain/gcc-src/2.7.2/reorg.c` 3118-3135), which is why m2c named a function at label+4. The
    pseudo-call to a `noreturn` symbol is the decompiler's spelling of `goto`/`return`; maspsx converts it
    to `j` by name list, and the "dead" value is the live join value gcc parks in its own jump's slot.
  - **412 pins of this family already fell** (664 live sites in 365 rows at the pin commit, counted by
    `sites_of`; STATUS's 499 counts `ASM_TAILSLOT_PIN` only): 314 + 66 + 2 in the fidelity campaign of
    2026-09-09 (label-as-call replaced by honest `goto`/`return`), 24 by `t11_midrow`, 2 traded for fences,
    1 dead. 220 of those rows are exact today with retail's intra-row `j` and a filled slot and no pin.
    2,021 pin-free exact rows carry the same shape (6,450 sites). The old repo's 7 pin-removing commits
    are all "re-land as honest all-return C, zero pins; rowbase gap filled".
  - **Three of the 15 pin-only rows rewritten as honest C are byte-exact at the true base** through the
    scorer's own pipeline (`town/func_808755AC` and `town/func_808B32AC` as `return arg0;`,
    `main/func_8001A22C` as an if/else with a common `return`), zero pins; through `tools/verify.py` at the
    synthetic link base they differ by ONE word, the `j` target. The bases were not fitted: bank neighbours
    with 2-3 local `j`s solve the same delta.
  - So the family is **label-as-call residue plus a missing true base**: 90 of the 126 pinned rows have no
    `config/overlays/*.rowbase.jsonl` region, and at a synthetic base an honest `j $L` cannot be exact while
    `j <absolute symbol>` smuggles the true address in. What settles it: rowbase records for those 90 rows
    under the ledger's standard (at least two local `j`s solving one base plus an exact recompile;
    `selfbase.json` lists a solved base per row), the `_truebase_` twin windows, then `t10_epilogue` /
    `t11_midrow` and honest rewrites; the 36 rows with a region are attackable now. The maspsx marker gate
    stays (nothing generalises), and ASPSX 2.40 remains the one untested binary.
  - Side findings kept: for 2.8.x rows stock ASPSX passes gcc's `j $31 / addu $sp` epilogue through while
    maspsx un-fills it and retail agrees with maspsx; gcc 2.7.2 (genuine and rebuilt alike) silently drops a
    volatile asm on 7 of the 15 pinned rows' cdk/2.8.x-shaped C.
- **Tail-slot follow-through (parts 3 and 4):** with the owner's approval of promotion for proven rows, 23 + 81 =
  104 label-as-call rows were re-landed as honest C at their true base (475 pins: every tail-slot pin on them
  plus the keeps, register pins and fences that had held the pseudo-call shape). The recipe: honest candidate
  exact through the per-row scorer -> `rowbase.py promote` with that candidate as the discriminating recompile
  -> true name registered in `ledger/splits/` -> landed through the window gate. Three shape rules from the
  packs: normalise the thread-fill (the source label is target-4 when the word before the "callee" equals the
  delay word); a u16 store swaps the addu operands, so keep the sum in a u32 temp; a shared `move v0,<saved>`
  join is a `goto` to the existing return label, never a duplicated `return`. `t10_epilogue` found nothing on
  any of these rows because its eligibility comes from `ledger/cache/audit.json`, which has no records for them
  (re-run `decomp_audit.py` before trusting it again). Gate-side residue: jump-table rows need the true-space
  definition name in the source; the town assembler dial keys on the synthetic name; two rows' rowbase segments
  build 36 bytes short of their extent.
- **Tooling:** `tools/lanes/build_exemplars.py` (landed diffs that lowered a family's count with a body
  change, an INDEX with the generators journaled for each row), `tools/alloc_trace.py` (the observer),
  `tools/lanes/build_alloc_lanes.py` with `alloc_lane_brief.md` (diagnosed register packs by allocator
  reason). All three were written by opus workflow agents from a specification.

## Round 27 (2026-09-15): the search is menu-limited, the lane ledger and pool table, and the MEM_IN_STRUCT_P lever

Started at d7a6d7dd: **7,253 pins in 1,354 rows** (REG 3,622 = 50%, KEEP+KEEP_NV 2,592, fences 409). The owner asked for a
critical review of the approach, new mechanisms (long CPU jobs welcome if they pay), and less model spend, with tooling
built by opus workflows and reviewed here. What was measured, in the order it changed the plan:

- **The CPU search was never budget-limited by the beam; it is menu-limited.** Every earlier `pin_search` escalation
  (4x, 16x: rounds 15-17) raised the ROW budgets (screens, verifies, CPU) and left the per-group cap `group_screens` at
  240, which ends each pin group's beam at depth ~1.7 of 3 (menu mean 62 candidates, beam 4). `prepare` now takes
  `--group-screens/--depth/--beam/--band`. The pilot `deep_pilot_r27_20260915` (39 near-band rows, beam 16, 2,400
  screens per group, 62,492 compiles in 20 minutes): **0 pins; 37 of 39 rows exhausted their candidate space at ~1,100
  distinct texts, and not one group came closer than under the 240 cap.** The reachable candidate set is small and
  flat. A longer job with the current menu is pointless; only a new move kind can pay.
- **The near band, read from the last full run (`changed_r26_20260915`, 368 rows):** 43% of single-pin erasures land
  within 4 assembly lines of retail (482 of 1,129 groups), and in 76% of groups the beam never got closer than the bare
  erasure. Classifying those 463 near residues by content: **66% contain no load or store at all** (an ALU instruction
  or a copy moved, renamed or dropped), 20% mixed, 14% memory-only; by shape: pure reorder 44%, register rename 23%,
  other 33%; keeps are 57% of the band. A `KEEP` is `asm volatile("" : "=r"(v) : "0"(v))`: it forces the value into a
  register at that point, splits its pseudo, and is a full memory fence; a `KEEP_NV` only splits the pseudo. The
  residues match: `move $2,$5; sw $2` becoming `sw $5` (the keep held a copy), `rem $3 -> rem $2` (a temp changed
  register), `li $2,1` moved (the keep held an order).
- **What the lane wins actually did** (`build_exemplars.py`, 763 REG / 501 KEEP / 177 FENCE landed diffs over the last
  60 commits, split by the journal into lane-won and generator-won; a hunk classifier over the lane-won half): REG
  lanes removed a declaration in 61% of diffs and added one in 46% (a lifetime split, a merge onto an existing host, a
  rename with a new type), rewrote statements in 48%, changed control flow in 17%; a pure width change alone was 9%.
  KEEP and FENCE lanes look the same with more control flow (29%, 35%). Median diff 5-15 changed lines. A text-only
  replay of the engine's whole menu on 120 lane-won pre-fix texts (`scratchpad/reach_lane.py`, token distance to the
  landed text, renames counted against it) reached the landed text at depth 1 on **1 of 120**; 29 rows had any
  candidate reduce the distance (median reduction 0%, mean 5%), 6 had one that covered half of it (the closest
  families: dropcopy 9, basesym 4, host 3): the menu does not contain the lanes' moves, and t53's journal says the same from the other side (it ran out of candidates on 82% of its rows and
  its candidates improved the assembly distance on a third of sites without ever reaching zero).
- **The lane ledger and the pool table** (`tools/lanes/ledger.py`, `tools/lanes/pools.py`; opus-built, opus-reviewed,
  reviewed here): 184 lanes, 1,560 rows served, 716 exact, 498 landed, 510 pins by the lanes' own outputs (the cascade
  after each landing is not in that number). By tier and family: opus LAC 73% (15 rows), astra LAC 71% (7), sol LAC 40%
  (128), sol REG 31% (435), luna REG 19% (275), luna FENCE 16% (365), luna KEEP 5% (80), sol SWITCH 1% (80), agy REG 6%.
  By register stratum: alloc2 conflict 39%, alloc5 scan-order 29%, alloc1 preference 24%, alloc4 coalesced 17%, alloc3
  lifetime 15%. `--closed 0.2` names what no pack may be built on again: FAKEDEP, ARG, SWITCH, KEEP (4% over 92),
  FENCE (15% over 385), REG alloc3 and alloc4. The pool table (every pinned row by family, stratum, band, served or
  not, near band, and the rate measured on that stratum) shows REG unserved 132 rows / 697 pins, of which the paying
  strata hold about 20 rows; KEEP unserved 178 rows / 489 pins on a family whose lanes pay 4%. The fresh-row pack
  lever is measured out; the table is what says so before a pack is launched.
- **A new lever, from the compiler source, proven by fixture (`tools/fixtures/memdep/run.sh`):** gcc 2.7.2 `sched.c`
  815-880 (`true_dependence`, `anti_dependence`, `output_dependence`; byte-identical in 2.8.1) treat two memory
  references that `memrefs_conflict_p` cannot separate as INDEPENDENT when one is a struct-member access through a
  varying address (`MEM_IN_STRUCT_P`, mode not QImode) and the other a non-struct access at a fixed address (a bare
  global scalar, a stack slot). `cse.c` (`invalidate`, 7571: a struct member or a varying sum "need not invalidate
  scalar variables", QImode excepted) and `loop.c` (2682, the store table keyed on the flag) consult the same bit;
  `expr.c` sets it for `COMPONENT_REF`, `ARRAY_REF` and an aggregate `INDIRECT_REF`, never for `*(T *)((u8 *)p + k)`
  or `M2C_FIELD`. In every stock cell but 2.91.66 (haifa) the fixture's `p->a = v; return G;` emits the load FIRST
  (the exemption fired and the scheduler hoisted it), while the same store spelled as a cast, or `G` spelled `H[0]` or
  `GS.x`, keeps store-then-load. So the SPELLING of one access changes instruction order, surviving loads and hoisting
  at identical address arithmetic. Twenty-six rounds never tested it and no generator flips a spelling; pinned rows
  still carry 4,215 raw-cast accesses (577 rows / 3,835 pins). Its reach is bounded by the residue census above:
  at most the 34% of near residues that contain a memory operation, plus the fence and CSE classes. `t63_memdep`
  (opus, reviewed) is being built and evaluated on the near-band keep rows; two hand probes before it (an untargeted
  flip of the nearest raw access at 26 keep sites; residue-directed flips at 40) changed the listing at one site and
  were inconclusive because they resolved almost no struct types, which is what the generator is for.
- **`t63_memdep` measured** (opus-built; the opus reviewer found a BLOCKING defect - the member->cast flip silently
  dropped `volatile`, invisible to the screen, and the implementer's one "the mechanism bites" example was that
  dropped qualifier, not the flag - plus a stale-window defect after erasure; both fixed, 47 unit tests). Rates by
  family through `lane_eval` before the fix: fence / memory-barrier rows **10 of 168 eligible (6%)**, near-band keep
  rows 1 of 142, near-band rows 0 of 62; the residue census bounds it: in 66-76% of the misses the held instruction
  is not a memory reference, which no access spelling can move. The corrected sweep over the whole tree
  (`ledger/sweeps/t63_memdep.jsonl`, 12 minutes at 6 workers): **19 rows applied, 37 pins** in the counted containers
  (the largest: `dungeon/func_8133C2A4` 12 -> 6, `func_819835AC` 18 -> 15, `func_81008664` 66 -> 63, `town/func_80953900`
  8 -> 5); the one hit whose members were `volatile` (`dungeon/func_80083E28`) was refused as it should be. Every
  landed diff is one shape: `ASM_SCHED_BARRIER()` or `ASM_MEM_BARRIER()` beside a struct-member store through a
  pointer (`primitive->tag = ...`, `entry->kind = 2`, `st->state = 6`), respelled `(*(T *)((u8 *)p + off)) = ...` so the
  store conflicts with the neighbouring fixed-address access again - the PSX SDK's own primitive macros write the
  tag word through exactly such a cast - or a bare global respelled as a one-element array. The spelling is uglier
  than `p->f`; a later tidy may choose among the equivalent non-struct spellings. `t63_memdep` is in the cascade list.

## Round 28 (2026-09-15): the menu replayed at depth 2 with rename invariance, the move inventory, two generators by workflow

Started at 1677434c: **7,206 pins in 1,348 rows**, the machine idle. The round continues round 27's pattern (a critical
measurement before any model spend; tools by opus workflow with an adversarial opus reviewer; packs only from the pool table)
on the two levers its handover named: a variable-set generator learned from the lane diffs, and a register generator directed
by the allocator probe's `sugg` / `order-swap` classes. Measured first, all CPU:

- **Round 27's reachability replay was too strict.** It compared the engine's depth-1 candidates with the landed text token
  for token, so a split whose fresh name or declaration position differed from the lane's counted as a miss, and a two-move fix
  was out of reach by construction. `tools/lanes/reach.py` (from the scratchpad's `reach2.py`) compares SKELETONS (pins erased,
  comments gone, the function's locals alpha-renamed by first appearance, declaration runs sorted, struct bodies untouched) and
  expands the 12 nearest depth-1 texts once more. On the same 120 lane-won register diffs (seed 1): **depth-1 exact 7** (t51
  `single-set` 4, `gotoloop`, t51 `move`, t51 `fuse`), **depth-2 exact 6** (dropcopy+armstore, hostwide twice, dropcopy twice,
  basesym twice, fuse twice, fuse+width), closer 62, no closer 45 (all 120 rows). So the CURRENT menu holds
  about one lane-won fix in nine at depth 2 - but only under oracle ranking (distance to the known answer); the search's
  assembly-distance beam had run on most of these rows and found none, and the reached rows are the small diffs (9 of 13 within
  8-27 tokens; the unreached median is 48). The nearest families on the unreached: t53 width 6, dropcopy 4, single-set 4,
  hostwide 3, narrow 3; median distance reduction 9%, 31 of 107 halfway. The 100 lane-won KEEP diffs: depth-1 exact 9 (t53
  width 4, t51 move 3, fuse 1, dropcopy 1), depth-2 exact 0, closer 56, no closer 35, median reduction 11%, 24 halfway
  (nearest families single-set 5, narrow 4, commute 3, hostwide 3, dropcopy 3). Two conclusions the workflow was briefed with: the
  ranking is a lever for the reachable ninth (is the correct first step in the top 4 by screen distance, by pass-stream
  distance, or by neither?), and new moves are the lever for the rest.
- **The move inventory** (`tools/lanes/declmoves.py`, declaration-level, over the 403 lane-won register diffs): a width retype
  50, a lifetime SPLIT (an added local takes one definition of an existing one) 43, an INLINE of a removed local's defining
  expression at its uses 31 certain + 47 probable, a MERGE into another local 24 or into a parameter 8, a rename 9, control flow
  changed 76, a parameter list 13, and **113 diffs with no declaration change at all** (statement rewrites: expression forms,
  `goto done` -> `return`, order). The keep diffs (220): control flow 64, width 39, inline 19+31, split 11, none 51. The menu's
  own split/inline/merge moves are bounded (t51 `single-set`: a straight-line run of at most ten statements; t51 `fuse`: the next
  statement's sole use; natural `dropcopy`: bare copies; t60 `reuse`: straight-line disjoint lifetimes), which is the gap the
  variable-set generator is specified against: per-definition inlining across statements and labels, splits and merges decided
  on a statement-level control-flow graph, merges into parameters, pointer retypes.
- **Register lane rate by stratum and pin band**, read from the lane directories (base pins at serve time; out/ = exact):
  alloc1 4-8 pins 37% (31 of 84), alloc1 9-20 37% (20 of 54), alloc2 4-8 56% (32 of 57), alloc2 9-20 19% (5 of 26), alloc5 4-8
  28% (9 of 32), alloc1 2-3 9% (7 of 82). The lane kit's "33-42% on rows with 1-3 pins, 0-8% elsewhere" was a round-25 luna
  measurement and is wrong for sol on these strata: the 4-8 band pays best. The pool table's unserved alloc1/alloc2 rows (18,
  of which 8 are copies of one function, `dungeon/func_80BC1084` … `80C8D084`, 6 pins each, `d0 = 2`) are refused by
  `build_alloc_lanes.py` (a site without a specific observer reason) and went out as probe-briefed sol packs `probe3` (the
  eight copies + `800C84B8`, with a note to solve one and transfer) and `probe4` (nine rows, 3-20 pins).
- **The changed-rows search** (`changed_r27_20260915`, the 72 rows changed since their last search, round 26's budget,
  8 workers, ~25 min): one candidate (`dungeon/func_8028484C` 6 -> 4), 71 noop - the usual 1-2%.
- **The allocator probe's machine-targetable classes, by register:** the 175 `sugg` sites on rows with at most 8 pins name $2
  49 times, $3 34, $4 29, $6 18, $7 16, $5 12, saved registers 13 - all local quantities, i.e. the missing copy is to or from a
  return or argument register (local-alloc.c 1792-1834 sets `qty_phys_sugg` from exactly such a copy insn). The 102
  `order-swap` sites are all global allocnos with a named competitor (global.c `allocno_compare`: log2(refs)·refs/live·size).
  That reading is the brief of the second generator, `t65_regroute`.

Running as this is written: the opus workflow `tools/lanes/workflows/r28_varset.js` (two implementers in parallel, an
adversarial reviewer each, a fix stage each): item A `tools/xform/varset.py` + `t64_varset.py`, evaluated by the reachability
delta on the same 120/100 rows, a ranking audit on the reached rows, and `lane_eval` on 100 near-band register rows and 60
near-band keep rows; item B `t65_regroute.py`, evaluated on 80 `sugg` rows and 60 `order-swap` rows. Frozen row lists in
`work/native_lane/r28_dev/rows/`; the exemplar corpus and the two measurement tools are copied under that lane directory so
nothing points at a session scratchpad.

### Round 28 results: the two workflows, the packs, the sweep

- **`t66_sameregmerge`** (second workflow, 3 opus agents / 672k tokens / 89 min): two `register T v ASM_REG("$N")`
  declarations on the SAME hard register with disjoint lifetimes (decided on a statement-level control-flow graph) merged
  into the surviving variable - a plain rename when the types match, a cast form across word-sized types (`H = (TH)(expr)`,
  reads `(TV)H`, narrow types refused), the host declaration hoisted to the block enclosing both, two arm-local declarations
  made one. The later value inherits the register through the surviving pin: no allocator decision is left to go wrong,
  which is why erasing the family (t62, 0 of 186) and hosting the pinned variable on an unpinned local (natural `host`) both
  miss. `lane_eval`: 31 of 76 rows with 1-8 pins, 28 of 60 with 9-20, the reviewer's own 20 rows 15 of 20; every candidate
  it ever screened sat at cc1 distance 0 (the selectivity is entirely in the legality test). The reviewer's four defects
  (edits inside `#ifdef __mips__` arms - `pin_census.arm_labels` labels only NON_MATCHING conditions, so `unscored_text`
  is blind to every other arm and the module now keeps its own preprocessor map; an undocumented cast-free signedness
  merge that turned a logical shift arithmetic; a hoisted initialiser placed before a switch's first `case`; skip counts
  summed over restart passes) were fixed. **Tree-wide sweep: 127 rows, 238 pins in 2 minutes**; the cascade over those
  rows added 44 (t37 13 rows, t53 14, t41c 3, t63 2, t16, t36, t38, t53k, t66 itself once more). The lesson for the
  brief of every future pack: the move a sol lane repeats across five of seven wins is a generator, and the generator
  removes in two minutes what the lanes would have taken ~15 packs to serve.
- **`t64_varset`** (first workflow, item A; the whole workflow 6 opus agents / 1.51M tokens / 4.6 h): `tools/xform/varset.py`
  - `inline_def` (one definition of a multi-definition local substituted at the uses only it reaches), `split_def` (one
  definition and its exclusive uses renamed), `merge_local` / `merge_param` (disjoint on the CFG, with a def-over-live-out
  interference test the reviewer had to demand), `retype_ptr` - under an erase-first depth-2 search ranked by the screen
  and the pass-stream distance. `lane_eval`: **10 of 100 near-band register rows (21 pins), 2 of 60 near-band keeps (4)**;
  the reviewer's own 20 rows 0 of 20 (rows that collapse to ~11 distinct functions); 9 of the 10 register wins use a varset
  move (inline_def 6, merge_local 2, merge_param 2, split_def 1). Reachability delta on the replay: register 13 -> 16 of
  120 (one by `split_def`, the rest by the erase-first structure), keep 6 -> 9 - but the reviewer showed the broad replay
  credits families t64 refuses (width, narrow); restricted to t64's own menu the delta is register 11 -> 13, keep 2 -> 2.
  **The ranking audit** on the 11 rows the menu reaches at depth 2: the correct first step is in the top 4 by screen
  distance in 2, by pass-stream distance in 2, by neither in 9; it does not lower the screen distance at all in 10 of 11 and
  raises it in 5. A two-move fix's first half does not look like the pinned output, so no distance-ranked beam finds it:
  the depth-2 rows need an exhaustive (bounded-menu) expansion, not a better ranking. Still-unreached classes: CTRL (29
  register, 38 keep rows) is the largest and nothing in the menu touches it; scalar width retypes (14 / 11) are refused by
  policy.
- **`t65_regroute`** (item B): the probe-directed routing of a value through the ABI role its `sugg` register names (return
  through the variable, argument k spelled through it, a merge with the parameter) and the priority moves for `order-swap`
  sites: **0 of 65 eligible sugg rows and 0 of 60 order-swap rows, no candidate ever reached screen distance 0** (665
  screened), before and after the reviewer's five defects (a substring hoist that deleted stores, a merge that renamed
  struct members) were fixed. With probe3's finding below, the `sugg` class is bounded: the missing suggestion needs a real
  consumer of the value in that register (a four-argument call whose body does the retail work), which clean C cannot add.
- **Packs** (sol, from the pool table): `probe4` (nine unserved alloc1/alloc2 rows with 3-20 pins, probe-briefed) **7 of
  9, 10 pins**, five of them by the same-register merge that became t66; `probe3` (the eight copies of one 6-pin function
  plus one) **0 of 9**: the `$a3` byte value's suggestion needs a real fourth-argument consumer; every clean spelling leaves
  the erased pseudo a local quantity without suggestions choosing `$v1`. The swept tree matches or beats the pack's outputs
  on six of its seven rows (one row, `dungeon/func_809F90DC`, keeps one pin the pack removed by a hoist the generator's
  forms do not cover).
- **Search** `changed_r27_20260915`: one candidate (`dungeon/func_8028484C` 6 -> 4) on 72 rows, published through its gate.
- **Landed and gated** (109 windows MATCH + the search's, SLUS SHA-1 MATCH): **6,893 pins in 1,342 rows**, from 7,206 (-313:
  t66 sweep 238, cascade 44, t64 outputs 21, search 2, the rest T2/tidy). Then `t64_varset` over the 513 near-band rows
  (`--processes`: 13 minutes; the threaded run managed 5 rows a minute on the GIL): **24 rows / 38 pins (4.7% of the band)**,
  cascade 3, second gate 28 windows MATCH: **6,850 pins in 1,338 rows** (-356 for the round). The non-mips preprocessor arms
  of every landed row were compared before and after both landings (9 + 5 rows carry `__mips__`): none differ. `probe4`'s seven outputs were stale by the time
  the landing ran (the sweep had rewritten every one of its rows) and the ledger credits the rows to the generator.

## Round 31 (2026-09-16): the scheduling residue mapped to C

Measured first (CPU, before any tool was commissioned; the owner: "progress is real. Start the next phase"):
- **Packs**: the pool's remaining REG strata admit nothing worth a lane - `build_alloc_lanes.py --dry-run` on the unserved
  alloc4 rows 0 admitted, alloc3 2; `build_probe_lanes` refused the same rows in round 30 (no knob-sufficient site); the
  KEEP pool (`build_keep_lanes.py --dry-run --max-residue 2`) offers 12 rows on a family whose lanes pay 4%. No packs this
  round; do not rerun the dry-runs.
- **The census, fresh on the landed tree** (`erase_census.py --diff 4`, 23 s): 6,271 sites, near band 2,092 (d0 1-4),
  moved 980 / recoloured 425 / ops 666 / same-ops 21. The moved class by first differing pass: sched 271, dbr 186, cse 149,
  sched2 131, combine 116, loop 95, rtl 24 - `work/native_lane/r31_sched/rows/{sched,dbr,early}_sites.tsv`.
- **t51's reach on the 402 sched-moved sites** (its own `candidates()` at the site, up to 64 screened per site): a
  distance-0 candidate on 1 site (unverified), nearest at 2 on 235, at 4 on 161; the nearest is `commute` or `fuse`
  far more often than `move`. **The single statement move never fixes a sched site**: on 60 sites where t51's own
  independence test allows the move that the residue names, 0 reach distance 0 (23 stop at 2, 26 at 4, 7 offer no such
  move), and 312 of the 402 sites move three or more instructions. The body class is a region reschedule - the round-16
  and round-27 verdict a third time, now per site - and a t51 refusal table would not change it.
- **`tools/lanes/sched_map.py`** (new): both texts compiled with `-g -da`, which keeps gcc 2.x's line notes in every dump,
  so the insns whose relative order changed map to C lines; each moved insn is classified with t51's own tests. Body
  sched sites (329) by lead reason: independent 105, stmt-not-simple 99 (a control line, a bare block, a multi-line
  statement), dep-mem 44 (two memory statements - t51 never reorders those; t63's flips are the honest lever there),
  crossed-not-simple 33, dep-data 17, same-statement 12. **The one coherent class the mapping found is the PROLOGUE: 89
  sites in 65 rows (893 pins in those rows)** where the insn exchanged with the body is the function's `$sp` adjust (74) or
  a callee-saved store (15), at sched2 (53: KEEP 36, KEEP_NV 8, SCHED_BARRIER 7) or moved into a delay slot at dbr (36:
  KEEP 19, REG 5, SCHED_BARRIER 5). 87 of the 89 pins sit nine or more lines below the function's first body line: the
  pin is not at the top; it holds an ordinary statement whose instructions the second scheduler would otherwise lift
  above the stack adjust. That is round 31's workflow item (`work/native_lane/r31_prologue/rows/`).

## Round 30 (2026-09-15, evening): the lone-erasure census, t66's remaining refusals, the address class

Measured first (CPU, before any tool was commissioned):
- **The lone-erasure census** (`tools/lanes/erase_census.py`, 23 s for the whole tree at 8 processes): every one of the
  6,480 live sites erased alone and screened against the pinned listing. `d0 == 0` - the class the cc1 screen cannot see,
  the one a maspsx-level screen would serve - is **21 sites** (SCHED_BARRIER 11, KEEP 4, JALDELAY 2, UNDEF 2, MEM_BARRIER 1,
  REG 1): the handover's `screen_s` item is closed without a build. The near band by site: d0 1 = 89, 2 = 907, 3 = 284,
  4 = 881 (2,161 sites within four lines, 33%); 1,506 sites at 30 or more.
- **What one erasure changes, at d0 <= 4** (the residue lines grouped): one instruction MOVED, text unchanged, 1,002 sites
  (46%: KEEP 345, REG 217, KEEP_NV 182, SCHED_BARRIER 114 - the scheduling class t51 serves); the same instructions
  RECOLOURED 460 (21%: REG 234, KEEP 134 - the allocator class, bounded at the C level in rounds 26-28); an operation
  changed 678 (31%). The largest specific pattern in the last group is address materialisation: `lui+addiu -> lui+ori`
  112, `addiu -> ori` 73, `addiu -> move+ori` 22, `addiu -> lui+ori` 15 - 231 sites in 143 rows where retail spells an
  address as a symbol's carry-adjusted halves or adds an offset to a kept page, and the erased text folds it to an
  integer constant or an IOR. That is the pinned-integer-page family of rounds 5-7 and 18 (t29/t33/t54/t59), all swept:
  these sites are their residue, and they are the round's second workflow item (`work/native_lane/r30_addr/`).
- **t66's refusal table over every family row of the tree** (138 rows / 2,148 pins; ONE row still offers a candidate),
  pairs / rows / pins: decl-unparsed 792 / 41 / 797; interference 224 / 43 / 899; host-name-collision (candidate stage,
  after the rename opening) 138 / 6 / 170; init-before-declarations 92 / 10 / 172; type-mismatch-narrow 88 / 32 / 433 (the
  width rule, not an opening); address-taken 77 / 6 / 137; asm-operand-cast 44 / 14 / 356; pp-guarded-mention 33 / 9 / 124;
  shadowed-inner-local 32 / 5 / 148; loop-backedge 20 / 4 / 70; compound-assign-cast 17 / 9 / 220. `decl-unparsed` is not
  a parser gap but a scan stopper: `_augment`'s walk breaks at the first line it cannot read and hides every declaration
  below it - an anonymous `struct {` declaration (80 hidden declarations, 19 rows), the ONE-LINE computed-goto label table
  `static void *const state_labels[] = { &&jt_c0, ... };` (96, 11 rows; the biggest family rows: `dungeon/func_81008664`
  63 pins / 23 hidden), a multi-dimensional array or `void *volatile` (10, 6 rows). The first workflow item opens those
  and the three spelling refusals (asm-operand-cast, init-before-declarations, shadowed-inner-local), and TRIES the
  interference class under vf: both variables share one hard register in a byte-exact row, so the compiled program never
  holds both values at once - the C-level clash is the liveness over-approximating or an m2c artifact (one temporary per
  use, `event_x_1..8` on `$2`), and the byte verdict decides. `work/native_lane/r30_samereg3/rows/` holds the lists.
- **t67 has no opening**: its skips are structural (`sink_tail:no-tail` 279 rows, `arm-does-not-terminate` 194,
  `label-in-jump-table` 60, `run-stops-at-brace` 135), not spellings. **t64 has no refusal table**: it is a search; its
  misses sit one move from the pinned listing with `inline_def` nearest in 87 of 137 (d = 2 in 86), the menu verdict again.
- **Two sol packs from the pool** (`probe5`: REG alloc3 4-8, 12 rows admitted of 20; `probe6`: REG alloc4 2-3 and 4-8, 10 of
  40 - the rest "no knob-sufficient site"), launched 19:48Z.
- **The MOVED class by pass** (`tools/phase_census.work` driven over the 1,002 moved sites, scratchpad `moved_phase.py`,
  4 min at 6 processes): the first pass whose instruction ORDER differs after the erasure is `sched` 276, `dbr` 188, `cse`
  152, `sched2` 132, `combine` 122, `loop` 100, `rtl` 24, `greg` 4, `cse2` 2, `jump` 1. So 41% of the moved residues are
  the two scheduling passes (t51's class: KEEP 168, SCHED_BARRIER 64+, KEEP_NV 64), 19% are delay-branch reorg (a fill
  moved into or out of a delay slot - the "delay-slot" pin notes; KEEP 76, REG 56, SCHED_BARRIER 23), and 37% are code
  motion before allocation (cse 152 - REG 76, KEEP_NV 40 - loop 100, combine 122). Class at combine: late 434, ops 240,
  wiring 174, order 154. What is NOT yet measured for any of these: which C-level move t51 / t57 / t63 refuse on each
  site, because those generators do not journal refusals - the next opening after t66's is a refusal table for t51 on
  the 408 sched-moved sites, built the way t66's was.
- **The two sol packs**: both died at 20:11Z with "Selected model is at capacity" (205k and 331k tokens in; probe5 had one
  exact output by then) and were relaunched at 20:11Z; done 20:39Z. probe5 (REG alloc3 4-8, 12 rows): 2 exact -
  `dungeon/func_7FFEE0B8` 6 -> 5 (the value passed at its actual consuming argument position), `slus/w_80041588` 7 -> 5 (an
  artificial keep replaced by the store the row already needed). probe6 (REG alloc4 2-3 / 4-8, 10 rows): 4 exact -
  `dungeon/func_80D3C944` 4 -> 2 (a byte load split across the intervening call: t64's split_def), `slus/w_80041344` 4 -> 3
  (the value hosted in a non-overlapping local already on that register: t66's move in the other direction),
  `town/func_800C7328` 3 -> 2 (a missing argument position recovered and forwarded), `town/func_80820AF4` 3 -> 2 (the value
  hosted in a real call-argument producer). 6 of 22 rows, 8 pins, ~50 min of sol each; the alloc3/alloc4 strata pay as the
  pool table said (15-17%) and no move repeats across the wins the way probe4's did - nothing new to write up as a
  generator. Their outputs land with the round's gate.
- **The workflow (`r30_samereg3_addr.js`, 6 agents / 1.46M tokens / 142 min).** Item A, `t66_sameregmerge` openings v3:
  `T66_DECL_RUN` (the declaration walk steps over an anonymous struct, a one-line label table, a multi-dimensional array),
  `T66_ASM_OPERAND` (the bare surviving name inside an ASM_* argument), `T66_COMPOUND` (an assignment whose right side reads
  V, a write through the pointer), `T66_INIT_PLACE` (the demoted assignment after the block's last declaration unless a
  crossed initialiser mentions the pair, calls, or has a side effect), `T66_SHADOW` (the inner local renamed first), and
  `T66_TRY_INTERFERENCE` (clashing pairs offered anyway; nested 452 / overlap 8 over the 138 family rows). Evaluation: 25 of
  41 hidden-declaration rows / 53 pins, 21 of 29 form rows / 33 pins, **37 of 43 interference rows / 81 pins** (36% of the
  nested candidates, 50% of the overlap ones, every verify exact); 20 round-29 rows with every opening off byte-identical
  to the round-29 candidates, 110 of 110 frozen bases identical. The reviewer's three majors - a rename capturing a member
  of an anonymous aggregate in the same declaration run, a crossed initialiser with a side effect, an ASM_* sub-expression
  spelled bare - fixed at zero measured cost (133 of 133 row-slots identical after the fixes), 117 tests. Item B, the
  address class: 20 of 20 sites at six cells first differ at `.cse` - `fold_rtx` folds the kept page plus its offset into one
  CONST_INT; the `plus->ior` combine story of round 18 is not what these sites measure. 173 of the 231 addresses are named by
  the row's own `extern`; t54 as shipped 1 of 100, t59 as shipped 0 of 100; t59 opened four ways (a self-advance `p = p + K`
  as the symbol, a keep up to 8 lines from the definition, the `&D_X` spelling from the declaration, pointer scaling) offers
  118 sites / 79 rows and lands **3 rows / 4 pins**; 15 more rows come back reorder-only at total <= 2, so what remains of
  the class after respelling is the scheduling class. Three majors (braceless control flow accepted by `straight_line`, a
  whole-line replacement span, the keep-gap loop without a structural test) fixed, 75 tests.
- **Landed and gated** (64 windows MATCH, SLUS SHA-1 MATCH; non-mips arms identical on all 86 changed rows): **6,264 pins in
  1,303 rows**, from 6,473 (-209): the t66 openings 148 pins / 73 evaluation outputs + 32 / 11 rows in the forced tree sweep
  with `T66_TRY_INTERFERENCE=1` (two passes: 9 + 2 rows; the second pass paid on the `T66_VERIFY`-limited rows), t59 4 / 3
  (its forced sweep added nothing), the packs 8 / 6, the cascade 17 (t53_reg_state 13, t53k 2, t63 2). The day, rounds 28-30:
  7,206 -> 6,264 (-942), four opus workflows 5.23M subagent tokens (1.51M + 0.67M + 1.59M + 1.46M), four sol packs.

## Round 29 (2026-09-15): the control-flow inventory, t66's openings, the tail forms, and two clean negatives

Started at b17cbf57 (6,850 pins in 1,338 rows) on the owner's "keep going, keep evaluating what works and what doesn't".
Measured first, all CPU or text:

- **The pack-rule harvest** (every sol/luna pack's closing "generator rule" lines, 920 of them, 411 on exact rows): free
  text, dominated by lifetime / reuse / split / order / pointer words; the only recurring move outside the menu was tail
  duplication and return splitting (alloc46, 53, 67, 75). No second crisp move of t66's kind.
- **The control-flow inventory** (`tools/lanes/ctrlmoves.py` over the lane-won diffs with a control-flow change, REG 76 /
  KEEP 64 / FENCE ~62): TAILMERGE 35/30/36, TAILDUP 19/15/27, LOOPFORM 35/19/10 (t41/t44), RETSPLIT 17/17/6, GOTO2RET
  9/4/8 (t48), ARMSWAP 9/4/5, EARLYRET 6/9/4, other 35/39/30. `dungeon/func_81257000` was tail-merged by one lane and
  tail-duplicated back by a later one - both directions are real moves, and (see t67 below) mostly byte-neutral.
- **t64_varset over the rest of the tree** (`--processes`, 45 minutes): **82 rows / 123 pins, 10.7% of the 768 eligible rows
  outside the near band** against 4.7% on the near band itself - the band the search had worked hardest paid least, which
  is the same fact as round 27's "menu-limited" read from the other side. The cascade added 28 (t66 7 rows, t53k 4, t63 3).
  With `--workers` threads the sweep crawled at 5 rows a minute (reg_state parsing under the GIL); worker processes ran it
  at ~35.
- **The exhaustive depth-2 pilot is a clean negative.** `T64_BEAM=64 T64_SCREENS=20000` on eight near-miss rows whose
  nearest candidate sat one line from retail: **0 of 8**, three rows exhausting t64's whole bounded menu at depth 2 before the
  cap, the nearest candidate still at distance 1 on seven, ~5 h of CPU. Round 27's deep-beam verdict now holds at depth 2:
  the near band's last residual line needs a move the menu lacks, not a wider expansion of it. Do not re-run wider.
- **t66's two refusal classes opened** (opus workflow item, reviewed: 68 rows / 131 pins on the 110 rows the refusals had
  named, the reviewer's own 20 rows 8 of 20 / 12 pins): `host-name-collision` cleared by renaming the surviving variable
  (a local's name is byte-neutral), `in-macro-arg` cleared by renaming inside macro arguments except the pin binding
  itself and any macro that stringifies its parameter (none in include/). The reviewer's blocking defect: a macro whose
  parameter is a member or type name, not a value; and a multi-line macro argument invisible to the one-line matcher.
- **t67_tailform** (dup_label, sink_tail, hoist_tail, merge_runs, split_ret on a statement CFG): **6 of 238 eligible
  control-flow-noted rows (8 pins), 2 of 74 near-band keeps.** The mechanism finding explains the rate and re-reads the
  inventory: under `-da`, every tail move is expressed at `.rtl` and `jump.c`'s `cross_jump` canonicalises it away at
  `.jump` or `.jump2`, so 92% of `sink_tail`, 79% of `dup_label` and 61% of `split_ret` rewrites give a byte-identical cc1
  listing - the TAILDUP/TAILMERGE labels in the lane diffs are mostly co-occurrence with the real move (a fusion, a
  declaration merge), not mechanism. The moves pay only where the arms differ above the tail so the identical-tail test
  fails after the copy (`town/func_80818C8C`, 5 -> 2). On the exemplar corpus t67 reaches 1 of 120 tail-labelled diffs
  exactly and gets 47 closer. A second class is out of reach by policy: where the lone erasure is already cc1-identical
  (`d0 == 0`: 11 of 685 plans, and the ten nearest misses), the residue is assembler-side (a delay-slot fill, a fence) and no
  cc1-screened candidate can rank it - the screen is blind there and only vf could tell, at six calls a row.
- `dungeon/func_809F90DC`: the probe4 output three-way merged onto the swept text by hand, exact at 15 pins.
- **Landed and gated** (160 windows MATCH, SLUS SHA-1 MATCH): **6,473 pins in 1,304 rows**, from 6,850 (-377: t64 tree 123, the
  t66 openings through two tree sweeps - 47 rows before the fix stage finished (see the audit below) and 28 in the forced
  re-sweep with the final module; the 90 evaluation outputs were stale at landing - t67 30 rows, three cascades, the port).
- **Audit of the early t66 sweep.** The whole-tree sweep of the opened t66 was started at 16:40Z while the workflow's fix
  agent still owned the module (the fix that followed was the per-slot NAME classifier for macro parameters); it applied
  48 rows before it was stopped, every one verified byte-exact by vf. Byte equality does not prove struct honesty (a
  rename inside a NAME slot that lands on a member of the same offset and type verifies exact and misnames the field),
  so the 48 rows were audited afterwards with the final module's macro table: 31 macro calls new to those rows, all
  in VALUE slots (ASM_KEEP/_NV 14, ASM_USE2_NV 3, LOAD_GLOBAL_PAGE / FINISH_GLOBAL_TABLE 8, U8_AT/S16_AT 2, ASM_SET,
  ASM_TAILSLOT_PIN_TIED, ASM_KEEP_DEP_NV 2), none in a NAME slot, no call to a macro the table cannot see. Nothing to
  revert. The order was still wrong: a sweep of a module a fix agent is editing starts only after the workflow returns.
  The non-mips preprocessor arms of every changed row were compared before and after: none differ. Since the morning's
  7,206: **-733 in one day**, of which one mechanism family (same-register merges and their openings) is ~520.
