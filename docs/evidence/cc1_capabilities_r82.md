model: claude-sonnet-5-5

# r82_sonnet_kit REPORT

Two tools, both in this lane dir; both locate the repo by walking up from the tool file (no absolute home paths), so they
work unchanged once moved to tools/lanes/. modcell.py must run with cwd = a lane dir (lane kit rule); cc1caps.py runs anywhere.

## modcell.py - is CFG this module's build?
    cd work/native_lane/<lane>
    python3 <tools/lanes>/modcell.py <module-or-row> --cfg CFG [--cfg CFG2 ...] [--all|--sample N] [--procs 4] [--out OUT.jsonl] [--skip-same] [--quiet]
* target: row id / func name (-> its module), module name (beldo.c or beldo), or container/module.c (ambiguous names are refused).
* scores every pin-free, non-slus row of the module (current src text) with kitlib.score_at at each cfg; reuses flag_crutch's
  module_rows/norm and row_census.per_row_trial_ok. Rows registered at exactly the test cfg are scored too as a control
  (--skip-same drops them). Prints per cfg exact/total, each BREAK row with total + own cfg, and a verdict. --out is resumable jsonl.
* Validation, beldo.c (dungeon/func_813231FC's module; 36 rows, 29 pin-free scoreable, 7 pinned skipped; 58 scores in 14 s at 4 procs):
  - 2.8.0-G0 -fno-expensive-optimizations: exact 17/29, 12 breaking. flag_crutch counts neighbours excluding the target row:
    func_813231FC itself (now pin-free at 2.7.2-cdk-G0) is one of the 12, so 11 of the other 28 = flag_crutch's 11/28 reproduced.
    Breaking totals: 813231FC 19, 813233C8 8, 81323430 13, 81323500 13, 813236DC 36, 81323F78 24 (own 2.8.1-G0), 8132518C 14,
    81325380 9, 81325730 1, 81326C34 13, 81326D28 37, 81327710 24.
  - 2.7.2-cdk-G0: exact 29/29 (28 rows registered there + 81323F78 which is registered 2.8.1-G0 and is also exact at cdk). CONSISTENT.
  - Row cfgs have moved since flag_crutch: func_813231FC is now registered 2.7.2-cdk-G0 (r81_fable_eqv staged it).

## cc1caps.py - per-cell cc1 capability table
    python3 cc1caps.py                          # markdown tables + writes caps.json (next to the tool; --json PATH to move)
    python3 cc1caps.py --has FUNC [FUNC ...]    # cells having FUNC (lists lacking cells; substring hints if no exact symbol)
    python3 cc1caps.py --diff CELL_A CELL_B     # non-numbered symbols only in one cell (e.g. 2.7.2 vs 2.7.2-cdk)
* Method: `nm` on each toolchain/compilers/gcc-*/cc1 (unstripped, ~6.4k-8k text symbols); exact-symbol match incl. data flags.
  Cells present: 2.6.3, 2.7.2, 2.7.2-cdk, 2.8.0, 2.8.1, 2.91.66, 2.95.2.
* Validation: reload_cse_simplify_operands is ABSENT in 2.7.2-cdk (and 2.6.3, 2.7.2) and PRESENT in 2.8.0/2.8.1/2.91.66/2.95.2. Confirmed.
* Limits: symbol presence is necessary, not sufficient. force_to_mode exists in EVERY cell; whether it special-cases ASM_OPERANDS
  is intra-function and invisible to nm/strings (needs disassembly or a source diff). `regmove` and `movstrsi` are not gcc 2.x function
  names (real: regmove_optimize / gen_movstrsi*, expand_block_move, block_move_loop/call), and `rerun_cse_after_loop` is a flag
  variable (flag_rerun_cse_after_loop, present in all cells) - hence the extra rows.
* Findings worth a lane's attention: 2.7.2-cdk has reload_cse_regs + reload_cse_simplify_set (stock 2.7.2 has neither) and ALSO
  regmove_optimize + flag_regmove (like 2.91.66/2.95.2, but no regmove_profitable_p); optimize_reg_copy_3 only in 2.91.66/2.95.2;
  2.7.2-cdk has EH/branch-prob/emit_group_load additions (see --diff 2.7.2 2.7.2-cdk).

## Focus functions (round 81)

| function | 2.6.3 | 2.7.2 | 2.7.2-cdk | 2.8.0 | 2.8.1 | 2.91.66 | 2.95.2 |
|---|---|---|---|---|---|---|---|
| reload_cse_regs | - | - | Y | Y | Y | Y | Y |
| reload_cse_simplify_operands | - | - | - | Y | Y | Y | Y |
| reload_cse_simplify_set | - | - | Y | Y | Y | Y | Y |
| optimize_reg_copy_1 | Y | Y | Y | Y | Y | Y | Y |
| optimize_reg_copy_2 | Y | Y | Y | Y | Y | Y | Y |
| optimize_reg_copy_3 | - | - | - | - | - | Y | Y |
| regmove | - | - | - | - | - | - | - |
| regmove_optimize | - | - | Y | - | - | Y | Y |
| regmove_profitable_p | - | - | - | - | - | Y | Y |
| combine_regs | Y | Y | Y | Y | Y | Y | Y |
| output_block_move | Y | Y | Y | Y | Y | Y | Y |
| movstrsi | - | - | - | - | - | - | - |
| gen_movstrsi | Y | Y | Y | Y | Y | Y | Y |
| gen_movstrsi_internal | Y | Y | Y | Y | Y | Y | Y |
| expand_block_move | Y | Y | Y | Y | Y | Y | Y |
| block_move_loop | Y | Y | Y | Y | Y | Y | Y |
| block_move_call | Y | Y | Y | Y | Y | Y | Y |
| force_to_mode | Y | Y | Y | Y | Y | Y | Y |
| birthing_insn_p | Y | Y | Y | Y | Y | Y | Y |
| strength_reduce | Y | Y | Y | Y | Y | Y | Y |
| cse_around_loop | Y | Y | Y | Y | Y | Y | Y |
| rerun_cse_after_loop | - | - | - | - | - | - | - |
| flag_rerun_cse_after_loop | Y | Y | Y | Y | Y | Y | Y |
| flag_regmove | - | - | Y | - | - | Y | Y |
| flag_expensive_optimizations | Y | Y | Y | Y | Y | Y | Y |
| flag_schedule_insns_after_reload | Y | Y | Y | Y | Y | Y | Y |

## Other pass entry points

| function | 2.6.3 | 2.7.2 | 2.7.2-cdk | 2.8.0 | 2.8.1 | 2.91.66 | 2.95.2 |
|---|---|---|---|---|---|---|---|
| cse_main | Y | Y | Y | Y | Y | Y | Y |
| cse_end_of_basic_block | Y | Y | Y | Y | Y | Y | Y |
| cse_basic_block | Y | Y | Y | Y | Y | Y | Y |
| fold_rtx | Y | Y | Y | Y | Y | Y | Y |
| make_regs_eqv | Y | Y | Y | Y | Y | Y | Y |
| invalidate_memory | Y | Y | Y | Y | Y | Y | Y |
| loop_optimize | Y | Y | Y | Y | Y | Y | Y |
| scan_loop | Y | Y | Y | Y | Y | Y | Y |
| move_movables | Y | Y | Y | Y | Y | Y | Y |
| check_dbra_loop | Y | Y | Y | Y | Y | Y | Y |
| combine_givs | Y | Y | Y | Y | Y | Y | Y |
| find_splittable_givs | Y | Y | Y | Y | Y | Y | Y |
| recombine_givs | - | - | - | - | - | - | Y |
| maybe_eliminate_biv | Y | Y | Y | Y | Y | Y | Y |
| record_giv | Y | Y | Y | Y | Y | Y | Y |
| analyze_insn_to_split_address | - | - | - | - | - | - | - |
| combine_instructions | Y | Y | Y | Y | Y | Y | Y |
| try_combine | Y | Y | Y | Y | Y | Y | Y |
| simplify_rtx | Y | Y | Y | Y | Y | Y | Y |
| make_compound_operation | Y | Y | Y | Y | Y | Y | Y |
| nonzero_bits | Y | Y | Y | Y | Y | Y | Y |
| num_sign_bit_copies | Y | Y | Y | Y | Y | Y | Y |
| schedule_insns | Y | Y | Y | Y | Y | Y | Y |
| schedule_block | Y | Y | Y | Y | Y | Y | Y |
| schedule_select | Y | Y | Y | Y | Y | Y | Y |
| rank_for_schedule | Y | Y | Y | Y | Y | Y | Y |
| sched_analyze | Y | Y | Y | Y | Y | Y | Y |
| priority | Y | Y | Y | Y | Y | Y | Y |
| regclass | Y | Y | Y | Y | Y | Y | Y |
| reg_scan | Y | Y | Y | Y | Y | Y | Y |
| local_alloc | Y | Y | Y | Y | Y | Y | Y |
| global_alloc | Y | Y | Y | Y | Y | Y | Y |
| allocno_compare | Y | Y | Y | Y | Y | Y | Y |
| reload | Y | Y | Y | Y | Y | Y | Y |
| reload_as_needed | Y | Y | Y | Y | Y | Y | Y |
| find_reloads | Y | Y | Y | Y | Y | Y | Y |
| life_analysis | Y | Y | Y | Y | Y | Y | Y |
| stupid_life_analysis | Y | Y | Y | Y | Y | Y | Y |
| flow_analysis | Y | Y | Y | Y | Y | - | - |
| jump_optimize | Y | Y | Y | Y | Y | Y | Y |
| thread_jumps | Y | Y | Y | Y | Y | Y | Y |
| find_cross_jump | Y | Y | Y | Y | Y | Y | Y |
| do_cross_jump | Y | Y | Y | Y | Y | Y | Y |
| mark_jump_label | Y | Y | Y | Y | Y | Y | Y |
| delete_unreachable_code | - | - | - | - | - | - | - |
| reorg_redirect_jump | Y | Y | Y | Y | Y | Y | Y |
| dbr_schedule | Y | Y | Y | Y | Y | Y | Y |
| mips_fill_delay_slot | Y | Y | Y | Y | Y | Y | Y |
| mips_expand_prologue | Y | Y | Y | Y | Y | Y | Y |
| mips_expand_epilogue | Y | Y | Y | Y | Y | Y | Y |
| mips_output_double | Y | Y | Y | Y | Y | Y | Y |
| mips_move_1word | Y | Y | Y | Y | Y | Y | Y |
| mips_address_cost | Y | Y | Y | Y | Y | Y | Y |
| mips_secondary_reload_class | - | Y | Y | Y | Y | Y | Y |
| shorten_branches | Y | Y | Y | Y | Y | Y | Y |
| final | Y | Y | Y | Y | Y | Y | Y |
| final_scan_insn | Y | Y | Y | Y | Y | Y | Y |
| split_insns | Y | Y | Y | Y | Y | Y | Y |
| delete_for_peephole | Y | Y | Y | Y | Y | Y | Y |
| compute_use_by_pseudos | - | - | - | - | - | - | Y |
| expand_inline_function | Y | Y | Y | Y | Y | Y | Y |
| integrate_decl_tree | Y | Y | Y | Y | Y | Y | Y |
| reload_cse_delete_death_notes | - | - | - | Y | Y | Y | - |
| reload_cse_noop_set_p | - | - | Y | Y | Y | Y | Y |
| reload_cse_no_longer_dead | - | - | - | Y | Y | Y | - |

## Front-end difference not visible in the symbol table (r82_fable_resid, measured with `why.py --vs-cfg`)
The cdk cc1 (cygnus-2.7.2-970404) marks EVERY sibling field of a struct that has a `volatile` member as volatile
(`mem/s/v:HI`); FSF 2.7.2 and 2.8.1 mark only the volatile member (`mem/s:HI` for siblings) - their front-end sources
are textually identical here, so this is a Cygnus change. A `volatile` struct member on a cdk-census row poisons the
whole struct's accesses (dungeon/func_80F90E88: 48 -> 17 by dropping it).
