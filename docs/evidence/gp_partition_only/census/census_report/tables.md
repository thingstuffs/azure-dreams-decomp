# Comparison scope

The genuine-version counts below compare genuine ASPSX output with the traced generic pipeline at each declared function or physical-unit scope. They are not unqualified direct-retail byte counts. The separate `maspsx_retail` comparator reports zero unmasked differences across all 6,767 rows, with 872 masked words across 302 overlay rows (main 133/26, town 244/83, dungeon 492/192, ovmovie 3/1; SLUS 0/0). Full SLUS image and active-window byte gates are separate stronger evidence.

## Run

| records | ok | harness/compile errors | maspsx leg exact (scorer / pinned object) | self-check (traced maspsx = pipeline object) | maspsx leg resolved against retail: 0 differing words |
|---|---|---|---|---|---|
| 6767 | 6767 | 0 | 6767 | 6767 | 6767 |

**Rows exact under one common genuine ASPSX version: 6600 / 6767** (97.5%); ownerwise genuine-exact with no common version: 0; maspsx-dependent in at least one physical unit: 167 (of which a dependent unit cannot assemble at any version: 0).

Per version (rows exact / rows assembled):

| version | 2.56 | 2.67 | 2.77 | 2.79 | 2.81 | 2.86 |
|---|---|---|---|---|---|---|
| exact | 1996 | 6595 | 6600 | 6600 | 6600 | 6594 |
| assembled | 2048 | 6767 | 6767 | 6767 | 6767 | 6767 |
| %hi/%lo syntax errors | 4699 | 0 | 0 | 0 | 0 | 0 |

## Rows exact under genuine ASPSX: container x cell x version

Cell: rows / exact under one COMMON version / ownerwise exact with no common version / exact per common version 2.56, 2.67, 2.77, 2.79, 2.81, 2.86. `mixed` means physical owners use different compiler cells.

| container | cell | rows | common any | ownerwise only | 2.56 | 2.67 | 2.77 | 2.79 | 2.81 | 2.86 |
|---|---|---|---|---|---|---|---|---|---|---|
| slus | 2.6.3 | 6 | 6 | 0 | 6 | 6 | 6 | 6 | 6 | 6 |
| slus | 2.7.2 | 380 | 375 | 0 | 375 | 375 | 375 | 375 | 375 | 372 |
| slus | 2.7.2-cdk | 456 | 453 | 0 | 51 | 453 | 453 | 453 | 453 | 451 |
| slus | 2.8.1 | 35 | 33 | 0 | 3 | 33 | 33 | 33 | 33 | 33 |
| slus | 2.91.66 | 1 | 1 | 0 | 0 | 1 | 1 | 1 | 1 | 1 |
| slus | 2.95.2 | 4 | 3 | 0 | 0 | 3 | 3 | 3 | 3 | 3 |
| slus | mixed | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **slus** | all | 884 | 871 | 0 | 435 | 871 | 871 | 871 | 871 | 866 |
| main | 2.6.3 | 95 | 95 | 0 | 95 | 95 | 95 | 95 | 95 | 95 |
| main | 2.7.2 | 76 | 76 | 0 | 76 | 76 | 76 | 76 | 76 | 76 |
| main | 2.7.2-cdk | 243 | 243 | 0 | 98 | 243 | 243 | 243 | 243 | 243 |
| main | 2.8.0 | 2 | 2 | 0 | 1 | 2 | 2 | 2 | 2 | 2 |
| main | 2.8.1 | 6 | 2 | 0 | 1 | 2 | 2 | 2 | 2 | 2 |
| main | 2.95.2 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **main** | all | 423 | 418 | 0 | 271 | 418 | 418 | 418 | 418 | 418 |
| town | 2.6.3 | 146 | 126 | 0 | 126 | 126 | 126 | 126 | 126 | 126 |
| town | 2.7.2 | 91 | 82 | 0 | 82 | 82 | 82 | 82 | 82 | 82 |
| town | 2.7.2-cdk | 2413 | 2413 | 0 | 715 | 2413 | 2413 | 2413 | 2413 | 2413 |
| town | 2.8.0 | 12 | 8 | 0 | 3 | 8 | 8 | 8 | 8 | 8 |
| town | 2.8.1 | 18 | 13 | 0 | 3 | 13 | 13 | 13 | 13 | 13 |
| town | 2.91.66 | 6 | 2 | 0 | 2 | 2 | 2 | 2 | 2 | 2 |
| town | 2.95.2 | 9 | 5 | 0 | 1 | 4 | 5 | 5 | 5 | 5 |
| **town** | all | 2695 | 2649 | 0 | 932 | 2648 | 2649 | 2649 | 2649 | 2649 |
| dungeon | 2.6.3 | 25 | 25 | 0 | 25 | 25 | 25 | 25 | 25 | 25 |
| dungeon | 2.7.2 | 49 | 44 | 0 | 44 | 44 | 44 | 44 | 44 | 44 |
| dungeon | 2.7.2-cdk | 2561 | 2561 | 0 | 272 | 2557 | 2561 | 2561 | 2561 | 2560 |
| dungeon | 2.8.0 | 25 | 2 | 0 | 1 | 2 | 2 | 2 | 2 | 2 |
| dungeon | 2.8.1 | 73 | 10 | 0 | 0 | 10 | 10 | 10 | 10 | 10 |
| dungeon | 2.91.66 | 2 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| dungeon | 2.95.2 | 8 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| **dungeon** | all | 2743 | 2642 | 0 | 342 | 2638 | 2642 | 2642 | 2642 | 2641 |
| ovmovie | 2.7.2 | 15 | 15 | 0 | 15 | 15 | 15 | 15 | 15 | 15 |
| ovmovie | 2.7.2-cdk | 3 | 3 | 0 | 1 | 3 | 3 | 3 | 3 | 3 |
| ovmovie | 2.8.1 | 4 | 2 | 0 | 0 | 2 | 2 | 2 | 2 | 2 |
| **ovmovie** | all | 22 | 20 | 0 | 16 | 20 | 20 | 20 | 20 | 20 |
| **tree** | all | 6767 | 6600 | 0 | 1996 | 6595 | 6600 | 6600 | 6600 | 6594 |

## Version sets (which genuine versions reproduce a row)

| exact under | rows |
|---|---|
| 2.67, 2.77, 2.79, 2.81, 2.86 | 4596 |
| all six | 1993 |
| none | 167 |
| 2.77, 2.79, 2.81, 2.86 | 5 |
| 2.67, 2.77, 2.79, 2.81 | 3 |
| 2.56, 2.67, 2.77, 2.79, 2.81 | 3 |

One global version per container (rows exact under that version / rows exact under ANY version):

| container | genuine-exact rows | 2.56 | 2.67 | 2.77 | 2.79 | 2.81 | 2.86 | only 2.56 |
|---|---|---|---|---|---|---|---|---|
| slus | 871 | 435 | 871 | 871 | 871 | 871 | 866 | 0 |
| main | 418 | 271 | 418 | 418 | 418 | 418 | 418 | 0 |
| town | 2649 | 932 | 2648 | 2649 | 2649 | 2649 | 2649 | 0 |
| dungeon | 2642 | 342 | 2638 | 2642 | 2642 | 2642 | 2641 | 0 |
| ovmovie | 20 | 16 | 20 | 20 | 20 | 20 | 20 | 0 |
| tree | 6600 | 1996 | 6595 | 6600 | 6600 | 6600 | 6594 | 0 |

Genuine-exact rows that 2.56 also reproduces, by cell: 2.6.3 252/252, 2.7.2 592/592, 2.7.2-cdk 1137/5673, 2.8.0 5/12, 2.8.1 7/60, 2.91.66 2/3, 2.95.2 1/8

## The -0 switch (unchecked div) and -G

Plural rows omitted from single-stream mode and flag statistics: 20. Their effective modes and recipes are in physical_units.tsv.

| rows with div/rem | rows | exact only with -0 | exact only without -0 | either | not genuine-exact |
|---|---|---|---|---|---|
| --expand-div rows | 10 | 0 | 10 | 0 | 0 |
| other div rows | 502 | 486 | 0 | 0 | 16 |

-G: 5,470 genuine-exact rows were compiled by cc1 at -G0 and are exact with ASPSX `-G0`; 0 needed the ASPSX default -G8 instead.

C-side numeric address equates (`.set D_X, 0x...`, `D_X = 0x...`): genuine-exact rows that are exact ONLY when the equates are assembled as constants (`.equ`), not as externals: 5. (Modes are tried externals first, so a row whose recorded mode says `equ` failed as externals.)

## maspsx-dependent rows by the maspsx behaviour that made the difference

For a legacy single-stream row, a listed ablation is a measured row fix. For a partitioned row, the cause is owner-specific and any ablation is listed only in physical_units.tsv; no owner fix is promoted to a whole-row fix. `unexplained` means no tested ablation reaches genuine for that measured unit.

| cause | rows | pin-free | pins in these rows | containers | cells |
|---|---|---|---|---|---|
| _maybe_unfill_return_delay | 108 | 43 | 335 | dungeon 90, town 11, main 5, ovmovie 1, slus 1 | 2.8.1 70, 2.8.0 21, 2.95.2 12, 2.91.66 5 |
| row dial --aspsx-version=2.40 | 21 | 16 | 6 | town 21 | 2.6.3 16, 2.7.2 5 |
| _fold_selfinc_la | 12 | 8 | 39 | dungeon 7, town 3, slus 2 | 2.7.2 8, 2.8.0 2, 2.6.3 1, 2.8.1 1 |
| _unfill_via_load_delay | 7 | 4 | 6 | town 5, dungeon 1, slus 1 | 2.8.1 3, 2.8.0 2, 2.91.66 1, 2.95.2 1 |
| _rewrite_tail_call_jal_to_j | 3 | 2 | 2 | town 3 | 2.6.3 3 |
| _fold_lo_into_accesses | 3 | 3 | 0 | slus 3 | 2.7.2-cdk 2, 2.95.2 1 |
| several passes jointly: _rotate_marked_store_into_jal_delay+_maybe_unfill_return_delay | 2 | 0 | 9 | dungeon 2 | 2.8.0 1, 2.8.1 1 |
| several passes jointly: _unfill_via_load_delay+_rewrite_tail_call_jal_to_j | 1 | 1 | 0 | town 1 | 2.8.0 1 |
| _prefer_marked_target_arg_setup | 1 | 0 | 2 | town 1 | 2.7.2 1 |
| row dial --aspsx-version=2.34 | 1 | 1 | 0 | town 1 | 2.7.2 1 |
| _split_funcaddr_la | 1 | 0 | 37 | dungeon 1 | 2.7.2 1 |
| several passes jointly: _unfill_via_load_delay+_rewrite_arg_sibcall_jal_to_j | 1 | 1 | 0 | ovmovie 1 | 2.8.1 1 |
| owner-specific: _expand_store_to_symbol_in_delay | 1 | 1 | 0 | slus 1 | mixed 1 |
| owner-specific: several passes jointly: _fold_lo_into_accesses+_unfill_via_load_delay+_maybe_unfill_return_delay | 1 | 1 | 0 | slus 1 | mixed 1 |
| _rotate_marked_store_into_jal_delay | 1 | 0 | 9 | slus 1 | 2.7.2-cdk 1 |
| _prefer_lui_over_sll_branch_delay | 1 | 1 | 0 | slus 1 | 2.7.2 1 |
| _unfill_jal_sp_delay | 1 | 1 | 0 | slus 1 | 2.7.2 1 |
| _hoist_zero_arg_before_global_clears | 1 | 1 | 0 | slus 1 | 2.7.2 1 |

## maspsx post-passes and helpers: where they fire, and who depends on them

fired = the pass changed a whole physical compilation unit's listing, counted once per logical row; it may have fired outside that row's scoped functions. Whole-row dependents below exclude owner-only ablations, which are listed separately in pass_dependents_physical.tsv.

| pass / helper | fired on logical rows | whole-row dependents | owner-only rows | fired but common-version exact | fired but ownerwise exact |
|---|---|---|---|---|---|
| `_maybe_unfill_return_delay` | 112 | 108 | 0 | 1 | 0 |
| `_fold_selfinc_la` | 13 | 12 | 0 | 1 | 0 |
| `_unfill_via_load_delay` | 10 | 7 | 0 | 0 | 0 |
| `_rewrite_tail_call_jal_to_j` | 4 | 3 | 0 | 0 | 0 |
| `_fold_lo_into_accesses` | 4 | 3 | 0 | 0 | 0 |
| `_rotate_marked_store_into_jal_delay` | 3 | 1 | 0 | 0 | 0 |
| `_hoist_zero_arg_before_global_clears` | 1 | 1 | 0 | 0 | 0 |
| `_prefer_marked_target_arg_setup` | 1 | 1 | 0 | 0 | 0 |
| `_prefer_lui_over_sll_branch_delay` | 1 | 1 | 0 | 0 | 0 |
| `_unfill_jal_sp_delay` | 1 | 1 | 0 | 0 | 0 |
| `_split_funcaddr_la` | 1 | 1 | 0 | 0 | 0 |
| `_expand_store_to_symbol_in_delay` | 1 | 0 | 1 | 0 | 0 |
| `small-extern-gp` | 0 | 0 | 1 | 0 | 0 |
| `_expand_smalldata_la` | 96 | 0 | 0 | 91 | 0 |
| `_rewrite_arg_sibcall_jal_to_j` | 1 | 0 | 0 | 0 | 0 |
| `_hoist_delay_luis` | 1 | 0 | 0 | 0 | 0 |

## Small-extern `$gp` model (decision 3)

Logical rows with a scoped physical unit that addresses an external symbol through `$gp`: **0** (0 distinct symbols, 0 unique row-symbol pairs). Single-stream rows where withholding `.extern` sizes alone reaches genuine: 0; plural rows with that result for at least one owner only: 0. The latter is not a measured whole-row repair; owner symbols and causes are in physical_units.tsv.

| container | cell | rows | single-stream extern-abs fixes | owner-only extern-abs rows |
|---|---|---|---|---|

Most-shared symbols: 

## Difference classes (maspsx vs the closest genuine version, maspsx-dependent rows)

| class | rows |
|---|---|
| delay-slot | 111 |
| other | 55 |
| reloc | 6 |
| jal-j | 4 |
| rtype | 1 |

## Pins

|  | rows | pin-free rows | pins |
|---|---|---|---|
| genuine-exact | 6600 | 5917 | 2658 |
| ownerwise exact, no common version | 0 | 0 | 0 |
| maspsx-dependent | 167 | 84 | 445 |
