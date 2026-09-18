# Pin research round 55: the stale rescans, joint erasure, and the recipe-coherence question

Round 55 (2026-09-18) is CPU-only: no model tokens were spent. Its first landing removed **23 pins: 5,989 / 1,266 rows** (from 6,012 / 1,269), all at unchanged recipes, holding every recipe switch for the owner; after the owner's decision (addendum) the switches landed too: **46 pins for the round, 5,966 / 1,265 rows**. The receipt is `docs/evidence/pin_research_round55_20260918.json`.

## Why this round is CPU-only

Rounds 35-54 removed 91 pins in one day with codex, Gemini and opus lanes at roughly five pins a round; rounds 28-34 removed 1,005 in four rounds by sweeping a discovered move over the tree. With codex gone, the cheapest lever is any measured move that was never re-run on the current text. The four lone-erasure rescans (`tools/pin_cells_scan.py` cells / flags / flags2 / stack) last ran on 2026-09-13; since then 654 of the 1,271 pinned rows, carrying 4,262 pins, had changed text and were never rescanned. The 37 rows edited in rounds 35-54 had never been through the generator cascade either.

## What ran

| job | rows | result | wall |
|---|---:|---|---:|
| lone rescan, cells | 564 | 7 hits, 2 rows landable at 2.8.0 (7 pins) | 14 min |
| lone rescan, flags | 640 | 13 hits in 9 rows | 30 min |
| lone rescan, flags2 | 466 | 3 hits in 2 rows | 9 min |
| lone rescan, stack | 93 | 1 hit | 7 min |
| joint erasure, cells mode (new) | 847 | 66,062 subsets, 10 rows with hits, 9 with a pair or triple that only falls together | 23 min |
| joint erasure, rows over 30 pins | 13 | 0 | 3 s |
| generator cascade over rounds 35-54 rows | 37 | 1 application (t69_prologue, 2 pins); the landing cascade added t54_pagebase, 1 pin | 4 min |
| zero_init on the remaining `$0` sites | 15 | 7 admitted, 0 exact, 3 two lines away | 1 min |
| flag discovery pilot, 15 never-screened flags | 90 | 0 hits; ten flags inert on 89 of 90 rows, `-g` admissible on 88, three break nearly every row | 16 min |
| module recipe census pilot, main/c_server.c | 260 | one stock recipe covers 206 rows; 54 nonconforming rows carry 24 pins | 5 min |

`tools/lanes/joint_scan.py` (tests in `tools/tests/test_joint_scan.py`) erases subsets of a row's pins together: every subset on rows with at most ten pins, else the whole set, the same-macro and same-variable groups and the pairs. Each subset is screened by the cc1 listing (`tools/xform/screen.py`, about 15 ms) at the recorded recipe and at every recipe the lone scan found admissible; only an identical listing goes to the byte scorer. The prefilter reproduced the lone scan's own single-site hits on all ten rows where both had one. Its one measured gap is `-g`, where 22 listing matches on two rows had no byte confirmation; `-g` is not a lever. Round 31's lesson (pins that hold one mechanism fall only together) is what this scan measures: `tools/pin_sites.py --subsets` had done it at the recorded recipe on the 2026-09-12 tree, and T2 walks singles.

## What landed

Eight rows from the joint scan at their recorded recipes (20 pins: `dungeon/func_80E61AA8` and `func_81083284` from three pins to zero, `func_80B97298` from three to one, the other five rows by two or three each) and the cascade's `dungeon/func_819A764C` (the redundant parameter copy `self` and its keep dropped together by t69_prologue; the parameter itself carries the `$18` role). The cascade over the nine changed rows applied t54_pagebase once more (one pin); T2 found nothing further. All 11 covering windows MATCH (153 s, 8 workers), the 884-TU SLUS SHA-1 gate MATCHES, STATUS reports 5,989 pin sites in 1,266 rows. The non-mips preprocessor arms of all nine changed rows are identical before and after. The research case ledger is refreshed for the changed case row and validates.

## What is held: every recipe switch

The owner asked whether the two-flag cap is our own rule, whether a legitimate flag might have been used, and whether a flag that breaks close neighbours says the flag is wrong or the neighbours' C is wrong. The cap is the owner's own rule (2026-09-13). The provenance test is at the translation-unit level, and this round ran it: for each recipe switch the scan proposed, every row of the same module (ledger/modules.jsonl) was scored at the recorded recipe and at the proposed one.

| row | switch | neighbours exact before | after | broken | fixed |
|---|---|---:|---:|---:|---:|
| dungeon/func_80E657E4 | 2.7.2-cdk-G0 to 2.8.0 | 11 | 4 | 8 | 1 |
| town/func_800B1464 | 2.8.1 to 2.8.1 -O1 | 42 | 11 | 32 | 1 |
| dungeon/func_819C04E8 | + -fno-expensive-optimizations | 4 | 1 | 3 | 0 |
| main/func_80012848 | + -fno-expensive-optimizations (c_server) | 168 | 151 | 17 | 0 |
| dungeon/func_800D53F0 | + -fno-expensive-optimizations | 5 | 3 | 2 | 0 |
| dungeon/func_800969CC | 2.7.2 to 2.8.0 | 3 | 3 | 2 | 2 |
| main/func_80014684 | + -fno-expensive-optimizations | 121 | 118 | 3 | 0 |
| town/func_8032E720 | + -fno-strength-reduce (third flag) | 8 | 9 | 0 | 1 |
| town/func_8087514C | + -O1 on the scheduling pair | 3 | 3 | 0 | 0 |

A pin-free row exact at the recorded recipe carries no compensation, so its going non-exact under the proposed recipe is the strongest available evidence that the translation unit was not built that way. "The neighbour's C is wrong" cannot rescue a switch: that C reproduces retail bytes today. The lone rescans found 24 hit pins, but each build stages one erasure per row (10 pins over the 16 candidates; T2 at the new recipe would collect the rest). The switches are therefore held (16 candidates, listed in the receipt), not refused: the standing cell-switch rule (rules 1-2 of `tools/pin_cells_land.py`) would allow them, and about 300 pins landed in rounds 11-12 under that rule carry the same debt. That is the owner's call.

## The finding behind the question: per-row recipes were never provenance

The c_server census makes the point independently of any switch. It is a 260-row module whose rows are 224 proven and 36 strong in ledger/modules.jsonl; its rows are recorded at six compiler cells and eight flag variants. Scoring every row's current text at all fourteen stock cells shows one recipe, `2.7.2-cdk-G0`, exact on 206 rows (196 of the 237 pin-free rows). The 54 rows not exact there carry 24 of the module's 43 pins; 15 of them are exact at no stock recipe at all (their recorded recipes carry flags), and a contiguous run of rows from `func_80019948` to `func_8001ABF4` is exact only at FSF 2.6.3/2.7.2, which is either a second translation unit inside the grouping or over-fitted C; the census summary reports each module's confidence mix rather than one label. A translation unit has one recipe, so the nonconforming rows are, by construction, rows whose C or recipe is compensating: a provenance-grounded target list that the pin count alone never produced. `work/native_lane/r55_census/run_all.sh` extends the census to the 74 proven/strong modules with ten or more rows (2,420 rows, about an hour of scorer time); it is the documented next long job.

## Bounded negatives

The remaining fifteen `ASM_REG("$0")` sites refuse the round-54 zero rewrite (0 of 7 admitted candidates exact). The fifteen flags nobody had screened are either inert on gcc 2.x at -O2 for these rows (`-O3`, inlining, struct-return conventions, `-fno-defer-pop`, `-fomit-frame-pointer`, `-mno-gpopt`, `-fshort-enums`, `-fcaller-saves`) or break almost every pinned row (`-fvolatile`, `-mlong-calls`, `-fno-delayed-branch`); none frees a pin on the 90-row pilot. Thirteen rows with more than 30 pins have no joint erasure at any admissible cell. The joint scan's flag modes were stopped at 725 of 847 rows to free the scorer for the gate; their ledger resumes.

## Addendum (later on 2026-09-18): the owner's decision and the module census

The owner ruled that trading a pin for a compiler flag is a positive (the pin says where, the flag says which pass; both are leads for the real C difference), lifted the two-flag cap, and asked that nothing be lost for the later goal of reducing flags and compilers on a cleaner source. Every trade is therefore recorded first in `ledger/recipe_trades.jsonl` (site, macro, argument, line, lone-erasure distance, residue fingerprint, recipe from and to, module-neighbour numbers), and the 12 held switch rows (13 pins) were landed through the standard cell-switch path. All twelve landed (the lane refused nothing), and the cascade plus T2 at the new recipes removed ten more pins on those rows (t54_pagebase three, t53k_keep one, t37b_localwidth_keep one, T2 five): **5,989 to 5,966 pins in 1,265 rows**. All 12 covering windows MATCH (246 s), the SLUS SHA-1 gate MATCHES, the row database and the case ledger validate, and the non-mips arms of every changed row are identical. The follow-up pins are recorded in the trade ledger too.

The module recipe census ran over the strong/proven modules with ten or more rows (SLUS excluded after the fact: its rows are verified by object identity with the pinned TU, so they cannot be scored at another recipe, and each SLUS TU already has one recipe by construction; 65 overlay/main modules, 2,131 rows; `ledger/module_recipe_census.jsonl`, `work/native_lane/r55_census/`). Per container the best single stock recipe is uniform: 2.7.2-cdk-G0 for 56 of 60 overlay modules, 2.6.3 for 3 of 5 main modules. 56 of the 65 modules have one recipe exact on at least 90% of their pin-free rows, while their recorded per-row recipes run to 24 variants in one module. The 222 nonconforming rows (129 pin-free, 93 pinned carrying 395 of the modules' 1,065 pins) are the provenance-grounded target list: 62 of the pin-free ones are exact at no stock cell at all (their recorded recipes carry a flag: -fno-schedule-insns2 14, -O1 13, -fno-strength-reduce 13, -fno-schedule-insns 10), 67 are exact at another cell (cell-fitted).

## Next

1. Owner decision on recipe switches, with the neighbour table as the evidence standard for any future one.
2. The module census over the strong and proven modules, then the nonconforming rows as the reconstruction target list, oracle: exact at the module's recipe.
3. The uncapped flag scan (every pinned row, the eleven known codegen flags, joint subsets) runs after the switch landing; its hits are trades, recorded the same way.
4. Flag reduction: the 62 pin-free rows exact at no stock cell, oracle = exact at the module recipe. Round 56 already runs three coherence tools against the nonconforming rows: `coherence_scan.py` (pin subsets scored at the module recipe: one hit, a keep in `dungeon/func_800C6828` that also drops `-fno-schedule-insns`), `coherence_sweep.py` (the cascade generators there: a clean negative, they are pin-driven) and `coherence_perturb.py` (the round-33 catalogue moves screened by cc1 listing at the module recipe, 4,223 candidates in 24 s: four pin-free rows become exact at the module recipe by one move, one of them leaving the 1999 compiler 2.95.2). Those land through `tools/lanes/land_coherence.sh` under the charter's clause 4b (coherence repairs), added for this purpose and open to the owner's veto; they are reported as recipe repairs, separately from pin removals.
