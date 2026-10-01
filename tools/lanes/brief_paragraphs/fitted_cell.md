## Rows registered at a FITTED compiler cell (round 84/85; read work/native_lane/r84_fable_build/REPORT.md "Rules")
The game is ONE `2.7.2-cdk -G0 -O2` build (+ a town -O1 debug family and stock Sony/devkit/minigame objects). EVERY row
registered at 2.8.0 / 2.8.1 / egcs 2.91.66 / 2.95.2 is a fitted crutch: its text was tuned until a late compiler
matched. TARGET = the row's module recipe (src/<container>/INDEX.md shows module; ledger/module_recipe_census.jsonl
best_recipe; almost always `2.7.2-cdk-G0`). Work every kit call with `--cfg "<target>"`, erase all pins there first,
then read the residue as a cdk residue (rounds 81-85 rules: split symbols for integer pages, parameters used directly
vs single-set copies, s16/u8 widths, re-reads after stores, index loops vs walkers, struct-field scratch accesses,
loops with calls). Stage with `lab.py stage-cell <row> cand.c --cfg "<target>" --note "..."` (`--equal-pins` for a
pin-free row: a 0 -> 0 move that retires the fitted cell is a landing). Never stage at a 2.8.x/egcs cell.
