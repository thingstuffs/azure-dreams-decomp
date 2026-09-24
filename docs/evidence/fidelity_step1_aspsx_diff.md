# Toolchain fidelity STEP 1: genuine-ASPSX differential over the whole tree

Measurement only (docs/TOOLCHAIN_FIDELITY_PLAN.md step 1; brief `work/fidelity/STEP1_BRIEF.md`). Nothing under
src/, include/, ledger/, config/, tools/maspsx or tools/build was touched; no gate, landing or sweep was run (git: one read-only `git status`, a slip against the brief; nothing staged or committed).

- Tool: `tools/fidelity/aspsx_diff.py` (+ `objread.py` ELF/LNK readers, `maspsx_trace.py` pass tracer/ablator,
  `aspsx_report.py` tables); test `tools/tests/test_aspsx_diff.py` (12 tests, comparator + LNK expression decoding).
- Journal: `work/fidelity/aspsx_diff.jsonl` (6,767 records, one per row, hash-keyed; a re-run recomputes only rows
  whose text, recipe or tool inputs changed - checked: `--container ovmovie` re-run = 0 to compute).
- Lists: `work/fidelity/maspsx_dependent.tsv` (610 rows), `work/fidelity/pass_dependents.tsv` (behaviour -> row),
  `work/fidelity/gp_extern_rows.tsv` (59 rows, decision 3); hypothesis probe `tools/fidelity/probe_reorder_epilogue.py`
  -> `work/fidelity/reorder_epilogue_probe.txt` (511 rows, decision 1).
- Re-run: `python3 tools/fidelity/aspsx_diff.py --workers 14` (13 min on this box for the full tree, 8,940 CPU-s),
  `python3 tools/fidelity/aspsx_diff.py --controls` (validation, exit 1 on a failure),
  `python3 tools/fidelity/aspsx_report.py` (the tables below, and the list files).

## Headline

| | rows |
|---|---|
| rows measured (every row in ledger/rows.jsonl) | **6,767** |
| maspsx leg retail-exact (scorer verdict / pinned SLUS object) and self-check passed | 6,767 |
| **exact under some GENUINE ASPSX version** | **6,157 (91.0%)** |
| **maspsx-dependent** (exact through maspsx, under NO genuine version) | **610** (836 pins in them; 439 pin-free) |
| of those, attributed by ablation | 610: 595 to one behaviour or row dial, 15 to a combination, 0 unexplained |

The fidelity debt is concentrated, not diffuse:

1. **`_maybe_unfill_return_delay` - 459 rows** (all of them at gcc 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 cells; 367 in
   dungeon). An INLINE maspsx rule (in `process_line`, not a post-pass: the brief's pass list would have missed it)
   that moves the gcc-filled `addu $sp,$sp,N` out of the `j $31` delay slot when 2+ callee-saved registers are
   restored. Its docstring says "Replicate ASPSX/retail"; no genuine ASPSX 2.56-2.86 does it (they pass gcc's
   `.set noreorder` epilogue through verbatim), and `work/tailslot_aspsx/REPORT.md` showed (one row checked) that the
   genuine psyq4.4 CC1PSX emits the same filled epilogue as our gcc-2.8.1. It fires on 469 rows and 459 depend on it;
   0 rows where it fires are genuine-exact. **Of the 601 rows at 2.8.x/2.9x cells only 84 are genuine-exact.**
   **But the shape IS genuine ASPSX's, applied to a different cc1 epilogue**: rewriting ONLY the gcc epilogue block
   `.set noreorder / j $31 / addu $sp,$sp,N / .set reorder` into reorder mode (`addu $sp,$sp,N / j $31`, i.e. a cc1
   that leaves the return delay slot to the assembler) makes genuine ASPSX 2.79 reproduce retail on **496 of the 511**
   maspsx-dependent rows on which `_maybe_unfill_return_delay` or `_unfill_via_load_delay` fires (459/468 and 37/42;
   0/1 where both fire; `tools/fidelity/probe_reorder_epilogue.py`, output `work/fidelity/reorder_epilogue_probe.txt`); the other 15
   shrink (e.g. 7 -> 4 words) and carry a second maspsx behaviour (`$gp` externs, a jal->j rewrite, a store
   rotation). ASPSX's own reorder-mode filler does not move the `addu $sp` into the return slot after the
   callee-saved restore sequence - the shape the maspsx helpers hard-code. So these ~500 rows are a **cc1 epilogue-mode** question (which 2.8-era
   cc1 emitted a reorder-mode return), not a missing assembler. `-fno-delayed-branch` is not it (it un-fills every
   slot: dungeon/func_7FFE7BE8 and main/func_8000E68C grow by 2 and 9 words).
2. **Small-extern `$gp` model - 59 slus rows** (decision 3; 50 fixed by withholding `.extern` sizes alone, 9 more at
   2.8.1 by that plus their fired passes). Overlays are compiled -G0 and have none.
3. **`_unfill_via_load_delay` - 37 rows** (2.8.x again: 32 of 37 at 2.8.1).
4. **The `--aspsx-version=2.40` / `2.34` row dials - 22 town rows** (2.6.3/2.7.2): retail needs a pre-2.56 ASPSX
   behaviour (the `li` expansion); dropping the dial makes maspsx == genuine 2.56+, and we have no genuine ASPSX
   older than 2.56.
5. The cdk-imitating passes the plan named are SMALL: `_split_funcaddr_la` 3 dependents, `_sink_call_separated_la`
   1, `_fold_selfinc_la` 12, `_fold_lo_into_accesses` 3; `_rewrite_tail_call_jal_to_j` 3, and six more passes with
   1 dependent each (table below). Every pass in that tail fires ONLY on its dependents (0 genuine-exact rows among
   the rows it fires on, except `_fold_selfinc_la` 1).
6. `_expand_smalldata_la` fires on 85 rows, is needed by NONE, and 68 of the rows it fires on are genuine-exact: it
   models real ASPSX behaviour. It is not fidelity debt.

## Method

For every row, from ONE gcc -S stream of the row's current `src/` text at its registered recipe (cell + flags):

- **maspsx leg** = the project pipeline itself. slus: `tools/verify.compile_slus` (gcc -> ccproc -> maspsx
  `--aspsx-version=2.56 --dont-force-G0 -G8 <row_asflags>` -> GNU as), include root `include/` as
  tools/reverify.py uses for src/ texts; verdict as `verify_slus` decides it (pinned TU object, name-masked text
  fallback; 1 row proven by direct retail resolution instead). overlays: the per-row scorer's own code in
  `build_ovl/` (`overlay_func_compare` steps: overlay evidence env incl. the candidate's noreturn decls,
  `inject_name_encoded_symbols`, rowbase link base and target symbol, `default_as_flags`, `match.build_text` with
  `asm_output`), verdict `linked_words_equal` - i.e. the scorer's own. The same `.s` is then re-assembled through
  `tools/fidelity/maspsx_trace.py`, which runs the unmodified `maspsx.py main()` with every post-pass named in
  `MaspsxProcessor.process_lines` wrapped (fired = changed the listing), plus two inline helpers
  (`_maybe_unfill_return_delay`, `_expand_store_to_symbol_in_delay`) and `_backfill_return_delay_store`. **Self-check:
  the traced object equals the pipeline's (slus: sha256 of the object; overlays: every word equals the scorer's
  linked slice outside relocation fields) on 6,767/6,767 rows.**
- **genuine leg** = the same gcc -S (slus: gcc's own `.s`; ccproc's only effect there is per-function `.section`
  lines, its names.tsv table does not resolve from tools/build/) through `ASPSX.EXE` 2.56 / 2.67 / 2.77 / 2.79 /
  2.81 / 2.86 under wibo, `-q`, CRLF, `.include` / `#APP` / `.size` / `.type` / `.set nobopt` dropped. Modes, best
  one kept per version: `-G0` when cc1 ran at -G0 (and the default -G8 as well when the TU defines small data);
  `-0` (no div checks) as well as the default when the TU divides; C-side numeric address equates
  (`.set D_X, 0x...`, `D_X = 0x...`) dropped (the symbol stays external, as in the original TU) and, as a second
  mode, respelled `.equ` (a constant). Symbol aliases `.set A, B` are dropped and mapped A -> B in the comparator.
- **comparator** (`compare_units`): both objects are cut into the same units - slus: every function of the TU;
  overlays: the row's retail extent (a composite `.text.<name>` bank + `.text` body, a bank label with the
  functions that follow it, as the scorer slices it). Each word becomes a token (word with its relocation field
  masked, canonical relocation). Canonical relocation = (type, target, addend) with TU-local targets rewritten
  function-relative, `.rodata/.rdata/.data` targets section-relative, `.bss/.sbss` targets symbol-relative (maspsx
  materialises commons), name-encoded externals (`D_/func_XXXXXXXX`) as addresses, equates and constant-only LNK
  patches as the constant. The LNK reader decodes the relocation expressions (psyq SUB is second-minus-first;
  2.56-2.81 `$gp` patches are type 30 `SUB(sectstart, sym)`; a patch offset is relative to the start of the BYTES
  record it follows - all three measured, and pinned by the unit test). Equal token streams link to equal bytes;
  the maspsx object is retail-exact, so genuine == maspsx is genuine == retail. Differences are counted by
  SequenceMatcher alignment (max of the two sides per non-equal region).
- **direct retail check** (independent of maspsx): every relocation of both objects is also resolved against retail
  - slus through `build_slus/build/slus_006.14.elf`'s symbol addresses (+ names.tsv aliases) and the baserom, overlays
  through name-encoded addresses and the rowbase link base - and compared positionally with the retail words. The
  maspsx leg resolves to 0 differing words on 6,767/6,767 rows; per genuine version the record carries
  `retail: [differing, masked]`.
- **attribution** (every non-exact version): the maspsx leg is re-run with each fired pass/helper disabled, all fired
  disabled, `.extern` sizes withheld (`--strip-externs`: genuine ASPSX's extern model), each row as-flag dropped,
  maspsx configured as the genuine version (`--aspsx-version=2.67/2.77/2.79`), and the combinations; each variant is
  compared with every genuine mode of that version. A variant that makes maspsx == genuine names the behaviour.
  Singles are reported before combinations.

## Validation (before the full run; `aspsx_diff.py --controls` re-runs all 60, all PASS)

- **casesi, positive (historical).** The live maspsx no longer has the 5-word jump-table rewrite (cddcc615 applied the
  work/maspsx_jtbl patch), so the in-tree casesi rows cannot show it. The control uses the objects that report kept
  from the PRE-patch maspsx on the real-switch text: `sw_base.o` (default) vs genuine 2.56/2.67/2.79 -> **different**
  at every version (333 vs 332 words, 16 aligned differences = the rewrite + the shifted local jumps);
  `sw_preserve.o` (`--preserve-casesi-at`) -> **identical** at every version; the LIVE maspsx on `sw.c` at the row's
  recipe -> identical to genuine at all six versions (the patch is byte-faithful).
- **d92c_genuine** (`work/native_lane/r77_fable_splitaddr/cands/d92c_genuine.c` at `2.7.2-cdk`, slus/w_8003D92C):
  genuine 2.67 / 2.77 (and 2.79 / 2.81 / 2.86) with `-0` resolve to **0 differing words, 0 masked, against the retail
  SLUS**; 2.56 rejects the `%hi/%lo` input (syntax errors), as the verdict doc says. The maspsx leg on that text is
  NOT retail (27 aligned differences) and withholding the `.extern` sizes alone makes it equal genuine - the decision-3
  mechanism, reproduced.
- **in-tree positive controls** (the sceptic's rows): slus/w_8004AB7C - `_sink_call_separated_la` fires, disabling it
  alone makes maspsx == genuine; slus/w_80041AB0 and w_80043CD0 - the same for `_split_funcaddr_la`.
- **plain pin-free rows**, two per (container, cell), 52 rows: 2.6.3 / 2.7.2 / cdk / most 2.8.x-2.9x rows exact under
  genuine ASPSX; the rest are explained by a single ablation (`_maybe_unfill_return_delay`, `extern-abs`,
  `_unfill_via_load_delay`, `_fold_selfinc_la`), none unexplained. slus/code (221 functions in one TU) is compared
  function by function and differs only by the `$gp` extern model.
- Harness bugs found and fixed by these checks before the tree run, in order: LNK patch offsets are per-BYTES-record
  (a 3.4 KB function arrives in chunks); ASPSX cannot open an input whose DOS path is longer than ~100 characters;
  src/ slus texts need `include/`, not `raw/include`; `.set NAME, 0xADDR` equates must stay externals for ASPSX
  (as `.equ` constants ASPSX swaps the `addu $at` operands of `lw $2,D_X($3)` - but 6 rows need the constant reading,
  hence both modes); `.set A, B` aliases; `.set nobopt`; name-encoded externals at the same address; composite / bank
  extents (77 dungeon bank rows first came out as harness errors and 38 more as short stubs).

## Tables (generated by tools/fidelity/aspsx_report.py)

## Rows exact under genuine ASPSX: container x cell x version

Cell: rows / exact under ANY version / exact per version 2.56, 2.67, 2.77, 2.79, 2.81, 2.86.

| container | cell | rows | any | 2.56 | 2.67 | 2.77 | 2.79 | 2.81 | 2.86 |
|---|---|---|---|---|---|---|---|---|---|
| slus | 2.6.3 | 7 | 6 | 6 | 6 | 6 | 6 | 6 | 6 |
| slus | 2.7.2 | 392 | 368 | 368 | 368 | 368 | 368 | 368 | 368 |
| slus | 2.7.2-cdk | 361 | 327 | 44 | 327 | 327 | 327 | 327 | 327 |
| slus | 2.8.1 | 119 | 31 | 3 | 31 | 31 | 31 | 31 | 31 |
| slus | 2.91.66 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 |
| slus | 2.95.2 | 4 | 3 | 0 | 3 | 3 | 3 | 3 | 3 |
| **slus** | all | 884 | 736 | 421 | 736 | 736 | 736 | 736 | 736 |
| main | 2.6.3 | 95 | 95 | 95 | 95 | 95 | 95 | 95 | 95 |
| main | 2.7.2 | 78 | 78 | 77 | 78 | 78 | 78 | 78 | 78 |
| main | 2.7.2-cdk | 237 | 237 | 98 | 237 | 237 | 237 | 237 | 237 |
| main | 2.8.0 | 3 | 2 | 1 | 2 | 2 | 2 | 2 | 2 |
| main | 2.8.1 | 9 | 2 | 1 | 2 | 2 | 2 | 2 | 2 |
| main | 2.95.2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **main** | all | 423 | 414 | 272 | 414 | 414 | 414 | 414 | 414 |
| town | 2.6.3 | 146 | 126 | 126 | 126 | 126 | 126 | 126 | 126 |
| town | 2.7.2 | 94 | 85 | 85 | 85 | 85 | 85 | 85 | 85 |
| town | 2.7.2-cdk | 2388 | 2388 | 709 | 2388 | 2388 | 2388 | 2388 | 2388 |
| town | 2.8.0 | 13 | 8 | 3 | 8 | 8 | 8 | 8 | 8 |
| town | 2.8.1 | 39 | 13 | 3 | 13 | 13 | 13 | 13 | 13 |
| town | 2.91.66 | 6 | 2 | 2 | 2 | 2 | 2 | 2 | 2 |
| town | 2.95.2 | 9 | 5 | 1 | 4 | 5 | 5 | 5 | 5 |
| **town** | all | 2695 | 2627 | 929 | 2626 | 2627 | 2627 | 2627 | 2627 |
| dungeon | 2.6.3 | 33 | 33 | 33 | 33 | 33 | 33 | 33 | 33 |
| dungeon | 2.7.2 | 55 | 50 | 50 | 50 | 50 | 50 | 50 | 50 |
| dungeon | 2.7.2-cdk | 2263 | 2263 | 259 | 2262 | 2263 | 2263 | 2263 | 2262 |
| dungeon | 2.8.0 | 175 | 5 | 1 | 5 | 5 | 5 | 5 | 5 |
| dungeon | 2.8.1 | 207 | 10 | 0 | 10 | 10 | 10 | 10 | 10 |
| dungeon | 2.91.66 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| dungeon | 2.95.2 | 8 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **dungeon** | all | 2743 | 2361 | 343 | 2360 | 2361 | 2361 | 2361 | 2360 |
| ovmovie | 2.7.2 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 |
| ovmovie | 2.7.2-cdk | 2 | 2 | 1 | 2 | 2 | 2 | 2 | 2 |
| ovmovie | 2.8.1 | 5 | 2 | 0 | 2 | 2 | 2 | 2 | 2 |
| **ovmovie** | all | 22 | 19 | 16 | 19 | 19 | 19 | 19 | 19 |
| **tree** | all | 6767 | 6157 | 1981 | 6155 | 6157 | 6157 | 6157 | 6156 |

## Version sets (which genuine versions reproduce a row)

| exact under | rows |
|---|---|
| 2.67, 2.77, 2.79, 2.81, 2.86 | 4173 |
| all six | 1981 |
| none | 610 |
| 2.77, 2.79, 2.81, 2.86 | 2 |
| 2.67, 2.77, 2.79, 2.81 | 1 |

One global version per container (rows exact under that version / rows exact under ANY version):

| container | genuine-exact rows | 2.56 | 2.67 | 2.77 | 2.79 | 2.81 | 2.86 | only 2.56 |
|---|---|---|---|---|---|---|---|---|
| slus | 736 | 421 | 736 | 736 | 736 | 736 | 736 | 0 |
| main | 414 | 272 | 414 | 414 | 414 | 414 | 414 | 0 |
| town | 2627 | 929 | 2626 | 2627 | 2627 | 2627 | 2627 | 0 |
| dungeon | 2361 | 343 | 2360 | 2361 | 2361 | 2361 | 2360 | 0 |
| ovmovie | 19 | 16 | 19 | 19 | 19 | 19 | 19 | 0 |
| tree | 6157 | 1981 | 6155 | 6157 | 6157 | 6157 | 6156 | 0 |

Genuine-exact rows that 2.56 also reproduces, by cell: 2.6.3 260/260, 2.7.2 595/596, 2.7.2-cdk 1111/5217, 2.8.0 5/15, 2.8.1 7/58, 2.91.66 2/3, 2.95.2 1/8

## The -0 switch (unchecked div) and -G

| rows with div/rem | rows | exact only with -0 | exact only without -0 | either | not genuine-exact |
|---|---|---|---|---|---|
| --expand-div rows | 10 | 0 | 10 | 0 | 0 |
| other div rows | 504 | 439 | 0 | 0 | 65 |

-G: 5,177 genuine-exact rows were compiled by cc1 at -G0 and are exact with ASPSX `-G0` (no row needed the ASPSX default -G8 instead).

C-side numeric address equates (`.set D_X, 0x...`, `D_X = 0x...`): genuine-exact rows that are exact ONLY when the equates are assembled as constants (`.equ`), not as externals: 6. (Modes are tried externals first, so a row whose recorded mode says `equ` failed as externals.)

## maspsx-dependent rows by the maspsx behaviour that made the difference

Attributed at each row's closest genuine version: the maspsx leg is re-run with one behaviour removed; the behaviour whose removal makes maspsx == genuine ASPSX is the cause. `unexplained` = no single or combined ablation reaches genuine.

| cause | rows | pin-free | pins in these rows | containers | cells |
|---|---|---|---|---|---|
| _maybe_unfill_return_delay | 459 | 320 | 663 | dungeon 367, slus 56, town 25, main 9, ovmovie 2 | 2.8.1 274, 2.8.0 168, 2.95.2 12, 2.91.66 5 |
| small-extern $gp model (.extern sizes) | 50 | 40 | 34 | slus 50 | 2.7.2-cdk 31, 2.7.2 16, 2.8.1 2, 2.6.3 1 |
| _unfill_via_load_delay | 37 | 33 | 7 | slus 21, town 13, dungeon 3 | 2.8.1 32, 2.8.0 3, 2.91.66 1, 2.95.2 1 |
| row dial --aspsx-version=2.40 | 21 | 16 | 6 | town 21 | 2.6.3 16, 2.7.2 5 |
| _fold_selfinc_la | 12 | 8 | 39 | dungeon 7, town 3, slus 2 | 2.7.2 8, 2.8.0 2, 2.8.1 1, 2.6.3 1 |
| combined: extern-abs+no:all-fired | 9 | 8 | 3 | slus 9 | 2.8.1 9 |
| several passes jointly: _rotate_marked_store_into_jal_delay+_maybe_unfill_return_delay | 4 | 0 | 34 | dungeon 4 | 2.8.0 2, 2.8.1 2 |
| _split_funcaddr_la | 3 | 2 | 37 | slus 2, dungeon 1 | 2.7.2 3 |
| _fold_lo_into_accesses | 3 | 3 | 0 | slus 3 | 2.7.2-cdk 2, 2.95.2 1 |
| _rewrite_tail_call_jal_to_j | 3 | 2 | 2 | town 3 | 2.6.3 3 |
| several passes jointly: _unfill_via_load_delay+_rewrite_arg_sibcall_jal_to_j | 1 | 1 | 0 | ovmovie 1 | 2.8.1 1 |
| _rotate_marked_store_into_jal_delay | 1 | 0 | 9 | slus 1 | 2.7.2-cdk 1 |
| _prefer_lui_over_sll_branch_delay | 1 | 1 | 0 | slus 1 | 2.7.2 1 |
| _sink_call_separated_la | 1 | 1 | 0 | slus 1 | 2.7.2 1 |
| _unfill_jal_sp_delay | 1 | 1 | 0 | slus 1 | 2.7.2 1 |
| _hoist_zero_arg_before_global_clears | 1 | 1 | 0 | slus 1 | 2.7.2 1 |
| several passes jointly: _unfill_via_load_delay+_rewrite_tail_call_jal_to_j | 1 | 1 | 0 | town 1 | 2.8.0 1 |
| _prefer_marked_target_arg_setup | 1 | 0 | 2 | town 1 | 2.7.2 1 |
| row dial --aspsx-version=2.34 | 1 | 1 | 0 | town 1 | 2.7.2 1 |

## maspsx post-passes and helpers: where they fire, and who depends on them

fired = the pass changed maspsx's listing for the row; dependents = rows whose ONLY route to genuine ASPSX is removing this behaviour (its single ablation makes maspsx == genuine); neutral = fired on a row that some genuine version still reproduces (the pass imitates genuine ASPSX there, or its change is undone downstream).

| pass / helper | fired on rows | dependents | fired but genuine-exact |
|---|---|---|---|
| `_maybe_unfill_return_delay` | 469 | 459 | 0 |
| `_unfill_via_load_delay` | 43 | 37 | 0 |
| `_fold_selfinc_la` | 13 | 12 | 1 |
| `_fold_lo_into_accesses` | 4 | 3 | 0 |
| `_rewrite_tail_call_jal_to_j` | 4 | 3 | 0 |
| `_split_funcaddr_la` | 3 | 3 | 0 |
| `_rotate_marked_store_into_jal_delay` | 5 | 1 | 0 |
| `_sink_call_separated_la` | 1 | 1 | 0 |
| `_prefer_marked_target_arg_setup` | 1 | 1 | 0 |
| `_prefer_lui_over_sll_branch_delay` | 1 | 1 | 0 |
| `_unfill_jal_sp_delay` | 1 | 1 | 0 |
| `_hoist_zero_arg_before_global_clears` | 1 | 1 | 0 |
| `_expand_smalldata_la` | 85 | 0 | 68 |
| `_expand_store_to_symbol_in_delay` | 1 | 0 | 0 |
| `_hoist_delay_luis` | 1 | 0 | 0 |
| `_rewrite_arg_sibcall_jal_to_j` | 1 | 0 | 0 |

## Small-extern `$gp` model (decision 3)

Rows whose maspsx object (= retail) addresses a symbol the TU does NOT define through `$gp`: **59** (69 distinct symbols, 111 row-symbol pairs). Genuine ASPSX 2.56-2.86 never does this (every `.extern` absolute, `-G` included); so each of these rows is maspsx-dependent unless its TU defines the symbol. Rows where withholding the `.extern` sizes alone makes maspsx == genuine: 50.

| container | cell | rows | extern-abs alone reaches genuine |
|---|---|---|---|
| slus | 2.6.3 | 1 | 1 |
| slus | 2.7.2 | 16 | 16 |
| slus | 2.7.2-cdk | 31 | 31 |
| slus | 2.8.1 | 11 | 2 |

Most-shared symbols: D_80081554 (5), D_800814D0 (5), D_80081550 (4), D_80081558 (4), D_80080AD4 (4), D_800814E8 (4), D_80081500 (4), D_80080B98 (3), D_800814E0 (3), D_80080A6C (3), D_8008152C (3), D_80081540 (2)

## Difference classes (maspsx vs the closest genuine version, maspsx-dependent rows)

| class | rows |
|---|---|
| delay-slot | 462 |
| other | 117 |
| gp-extern | 59 |
| reloc | 23 |
| jal-j | 4 |
| rtype | 1 |

## Pins

|  | rows | pin-free rows | pins |
|---|---|---|---|
| genuine-exact | 6157 | 5532 | 2375 |
| maspsx-dependent | 610 | 439 | 836 |

## The ASPSX version each TU needs (decision 2)

- **2.56 cannot assemble 4,690 of 6,767 rows** (every `%hi/%lo` operand is a syntax error): all cdk (-mgas) and
  2.8.x+ output. Where it can assemble (2.6.3 / 2.7.2 macro output) it agrees with 2.67-2.86: of the 856
  genuine-exact 2.6.3/2.7.2 rows it reproduces 855. So the pipeline's global `--aspsx-version=2.56` names a version that cannot have built most of the binary;
  the cdk and 2.8.x-2.9x TUs (5,217 + 84 genuine-exact rows) imply >= 2.67, the PsyQ 4.1 pairing.
- **One global version works for every container: 2.77 (or 2.79 / 2.81) reproduces all 6,157 genuine-exact rows.**
  2.67 misses 2 (dungeon/func_819835AC cdk: 5 words; town/func_800B6A28 2.95.2: 7 words) and 2.86 misses 1
  (dungeon/func_804FE77C cdk: 118 words). No row needs 2.56 specifically, no container needs two versions. The data
  therefore does not support a per-TU assembler version in the recipe; it supports one assembler, ASPSX 2.77-2.81.
- What IS per-TU is the assembler FLAG `-0`: 439 dividing rows are exact only with `-0` (unchecked div), and the 10
  `--expand-div` rows are exact only without it (checked div) - exactly the split maspsx's per-TU `--expand-div` dial
  encodes. 65 dividing rows are maspsx-dependent for other reasons.
- The 22 `--aspsx-version=2.40/2.34` dial rows are the exception: they need an ASPSX older than any we hold.

## Decisions for the owner / orchestrator

1. **`_maybe_unfill_return_delay` (459) + `_unfill_via_load_delay` (37) are the fidelity question** - 81% of all
   debt - and the probe says where the fix lies: in the COMPILER cell, not in maspsx. With the cc1 epilogue in
   reorder mode, genuine ASPSX alone reproduces 496 of the 511 rows; both helpers are faithful models of ASPSX's
   filler applied to cc1 output that pre-filled the slot. Decision needed: find/confirm the 2.8-era cc1 behaviour that
   emits a reorder-mode return (check the genuine psyq 4.4/4.5/4.6 CC1PSX epilogues on more than the one row the
   tailslot report checked, and gcc 2.8.x `mips.c` epilogue/`final` for a switch) and, if found, move the 2.8.x cells
   to it; the two helpers then retire with zero dependents. Until then they stay.
2. **Decision 1 (cdk-imitating passes):** the dependents are few and listed (`pass_dependents.tsv`):
   `_fold_selfinc_la` 12, `_split_funcaddr_la` 3, `_fold_lo_into_accesses` 3, `_rewrite_tail_call_jal_to_j` 3,
   `_sink_call_separated_la` 1, `_rotate_marked_store_into_jal_delay` 1 (+4 jointly with the unfill rule),
   `_prefer_lui_over_sll_branch_delay` 1, `_unfill_jal_sp_delay` 1, `_hoist_zero_arg_before_global_clears` 1,
   `_prefer_marked_target_arg_setup` 1; `_unfill_via_load_delay` 37 (2.8.x). These are the step-4 re-recipe work list;
   each pass can be retired when its list is empty (none of them fires on a genuine-exact row).
3. **Decision 2 (ASPSX version):** measured answer: one version, 2.77 (2.79/2.81 equivalent), not per-TU; `-0` vs
   checked div is the per-TU switch. Changing the pipeline's `--aspsx-version=2.56` changes maspsx's own model
   (`sltu_at`, `gp_allow_offset`, `gp_allow_la`): measured on the non-exact rows, maspsx configured as 2.67 / 2.77 /
   2.79 leaves the object byte-identical on 610-612 of ~613 and alone makes no row equal genuine; the exact rows were
   not ablated, so the switch must still be gated tree-wide before it is made.
4. **Decision 3 (`$gp` model):** 59 slus rows (list: `gp_extern_rows.tsv`, 69 symbols) are retail-exact only because
   maspsx `$gp`-relativises externs by `.extern` size. Under genuine ASPSX each of them needs the symbol DEFINED in
   the TU (if the original was built with genuine ASPSX, those symbols were TU-local small data) - a source change per row, not a maspsx flag, which
   is what step 4 would have to land after the maspsx fix.
5. **Surprising, and a caveat on "genuine-exact":** 6 rows are genuine-exact only if a C-side address equate is a
   constant rather than an external (the page-constant class of the r77 verdict, seen from the assembler side). And
   the `.set D_X, 0x...` equates themselves are project artefacts: the genuine leg reads them as externals, which is
   the faithful model for every other row.
