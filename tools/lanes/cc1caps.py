#!/usr/bin/env python3
"""Per-cell cc1 capability table (which gcc pass functions exist in each compiler cell's cc1).

    python3 cc1caps.py                     # markdown table (cell x function) + writes caps.json next to this file
    python3 cc1caps.py --has FUNC [FUNC..] # cells that have FUNC (substring match if no exact symbol)
    python3 cc1caps.py --diff CELL_A CELL_B# pass-ish symbols only in one of the two cells
    python3 cc1caps.py --json OUT.json     # caps.json location (default: <tool dir>/caps.json)

Method: `nm cc1` (the cc1 binaries are unstripped host ELF; static functions show as 't'), exact symbol match.
Cells = directories under toolchain/compilers/ (gcc-2.7.2-cdk -> cell name "2.7.2-cdk").
NOT visible from symbols: intra-function behaviour, e.g. force_to_mode's ASM_OPERANDS handling (exists in every
cell as a function; whether it special-cases ASM_OPERANDS is only visible in disassembly/source diff), or patches
inside an existing function.  Presence of a function is necessary, not sufficient.
"""
import json, re, subprocess, sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = next((p for p in [HERE, *HERE.parents] if (p / "toolchain/compilers").is_dir()), None)
if ROOT is None:
    raise SystemExit("cc1caps: cannot find toolchain/compilers above " + str(HERE))
COMP = ROOT / "toolchain/compilers"

FOCUS = [  # round-81 decisive functions
    "reload_cse_regs", "reload_cse_simplify_operands", "reload_cse_simplify_set",
    "optimize_reg_copy_1", "optimize_reg_copy_2", "optimize_reg_copy_3",
    "regmove", "regmove_optimize", "regmove_profitable_p", "combine_regs", "output_block_move", "movstrsi", "gen_movstrsi", "gen_movstrsi_internal",
    "expand_block_move", "block_move_loop", "block_move_call",
    "force_to_mode", "birthing_insn_p", "strength_reduce", "cse_around_loop", "rerun_cse_after_loop",
    "flag_rerun_cse_after_loop", "flag_regmove", "flag_expensive_optimizations", "flag_schedule_insns_after_reload",
]  # rerun_cse_after_loop is a FLAG in gcc 2.x (flag_rerun_cse_after_loop), not a function; data symbols are matched too
EXTRA = [  # other identifiable pass entry points
    "cse_main", "cse_end_of_basic_block", "cse_basic_block", "fold_rtx", "make_regs_eqv", "invalidate_memory",
    "loop_optimize", "scan_loop", "move_movables", "check_dbra_loop", "combine_givs", "find_splittable_givs",
    "recombine_givs", "maybe_eliminate_biv", "record_giv", "analyze_insn_to_split_address",
    "combine_instructions", "try_combine", "simplify_rtx", "make_compound_operation", "nonzero_bits", "num_sign_bit_copies",
    "schedule_insns", "schedule_block", "schedule_select", "rank_for_schedule", "sched_analyze", "priority",
    "regclass", "reg_scan", "local_alloc", "global_alloc", "allocno_compare", "reload", "reload_as_needed",
    "find_reloads", "life_analysis", "stupid_life_analysis", "flow_analysis", "jump_optimize", "thread_jumps",
    "find_cross_jump", "do_cross_jump", "mark_jump_label", "delete_unreachable_code",
    "reorg_redirect_jump", "dbr_schedule", "mips_fill_delay_slot", "mips_expand_prologue", "mips_expand_epilogue",
    "mips_output_double", "mips_move_1word", "mips_address_cost", "mips_secondary_reload_class",
    "shorten_branches", "final", "final_scan_insn", "split_insns", "delete_for_peephole",
    "compute_use_by_pseudos", "optimize_reg_copy_1", "expand_inline_function", "integrate_decl_tree",
    "reload_cse_delete_death_notes", "reload_cse_noop_set_p", "reload_cse_no_longer_dead",
    "combine_temp_slots", "init_alias_analysis", "true_dependence", "anti_dependence", "output_dependence",
    "rest_of_compilation", "purge_addressof", "find_basic_blocks", "find_basic_block",
    "expand_mult", "expand_divmod", "expand_shift", "emit_store_flag", "expand_end_case", "expand_return",
    "instantiate_virtual_regs", "assign_parms", "assign_stack_local", "optimize_bit_field",
]

def cells():
    return sorted((d.name[4:] for d in COMP.iterdir() if d.name.startswith("gcc-") and (d / "cc1").is_file()),
                  key=lambda s: [int(x) if x.isdigit() else x for x in s.replace("-", ".").split(".")])

def symbols(cell):
    out = subprocess.run(["nm", str(COMP / ("gcc-" + cell) / "cc1")], capture_output=True, text=True, check=True).stdout
    return {l.split()[-1] for l in out.splitlines() if len(l.split()) == 3 and l.split()[1] in "TtWwDdBbRrVv"}

def build():
    cs = cells(); syms = {c: symbols(c) for c in cs}
    funcs = list(dict.fromkeys(FOCUS + EXTRA))
    return cs, syms, funcs

def table(cs, syms, funcs, title):
    lines = ["| function | " + " | ".join(cs) + " |", "|---|" + "---|" * len(cs)]
    for f in funcs:
        lines.append("| %s | %s |" % (f, " | ".join("Y" if f in syms[c] else "-" for c in cs)))
    return "\n".join(lines)

def main():
    a = sys.argv[1:]
    cs, syms, funcs = build()
    if a and a[0] == "--has":
        for f in a[1:]:
            hit = [c for c in cs if f in syms[c]]
            if not hit:
                sub = {c: sorted(s for s in syms[c] if f in s) for c in cs}
                sub = {c: v for c, v in sub.items() if v}
                print("%s: no exact symbol in any cell%s" % (f, "; substring matches: " + json.dumps(sub) if sub else ""))
            else:
                print("%s: %s   (lacks: %s)" % (f, " ".join(hit), " ".join(c for c in cs if c not in hit) or "-"))
        return
    if a and a[0] == "--diff":
        x, y = a[1], a[2]
        for lab, s in ((x + " only", syms[x] - syms[y]), (y + " only", syms[y] - syms[x])):
            print("## %s (%d)" % (lab, len(s)))
            print(" ".join(sorted(t for t in s if not (t.startswith((".", "gen_", "__", "_IO", "_nl", "output_", "yy")) or re.search(r"\.\d+$", t)))))
        return
    jpath = Path(a[a.index("--json") + 1]) if "--json" in a else HERE / "caps.json"
    caps = {"cells": cs, "focus": FOCUS, "extra": EXTRA,
            "caps": {c: {f: (f in syms[c]) for f in funcs} for c in cs},
            "symbol_counts": {c: len(syms[c]) for c in cs}}
    jpath.write_text(json.dumps(caps, indent=1) + "\n")
    print("## Focus functions (round 81)\n"); print(table(cs, syms, FOCUS, ""))
    print("\n## Other pass entry points\n"); print(table(cs, syms, [f for f in EXTRA if f not in FOCUS], ""))
    print("\ntext symbols per cell: " + ", ".join("%s=%d" % (c, len(syms[c])) for c in cs))
    print("wrote", jpath)

if __name__ == "__main__":
    main()
