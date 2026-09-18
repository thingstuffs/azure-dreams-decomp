# Pin research round 56: the charter's first round, the coherence family, two model packs

Round 56 (2026-09-18, 03:30 to 07:45 UTC) is the first round under [the campaign charter](PIN_CAMPAIGN_CHARTER.md). It moved the count from **5,960 pins / 1,265 rows to 5,958 pins / 1,264 rows** and repaid **11 per-row recipe deviations** (reported separately, per clause 4b). Model spend: one codex luna pack and one Gemini pack (lane packs, no Workflow tokens). Receipt: `docs/evidence/pin_research_round56_20260918.json`.

## Pins

| source | rows | pins |
|---|---:|---:|
| uncapped joint flag scan (1,068 pinned rows, eleven codegen flags, single and joint subsets) | 2 | 5 |
| Gemini pack `r56_unserved2` (12 never-served small rows) | 1 | 1 |
| codex luna pack `r56_unserved1` (12 never-served small rows) | 0 | 0 |
| coherence scan: a keep erased, exact at the module recipe (also drops `-fno-schedule-insns`) | 1 | 1 |
| cascade at the new recipes | | 1 |

The never-served pool (126 rows with one to eight pins, 240 pins; `tools/lanes/served.py`) behaves like the served one: the two packs resolved one row of 24. Codex's quota resets about 2026-09-19 06:00 UTC and is not spent further before then; Gemini answers within its print timeout on a 12-row pack. Model capacity is journaled in `ledger/model_capacity.jsonl`.

## Coherence repairs (clause 4b)

Three new tools score candidates at the row's **module recipe** (round 55's census, `ledger/module_recipe_census.jsonl`) instead of the recorded one:

- `tools/lanes/coherence_scan.py`: pin subsets erased, byte-scored at the module recipe (93 nonconforming pinned rows, one hit).
- `tools/lanes/coherence_sweep.py`: the cascade generators there, writing nothing (clean negative: they are pin-driven and refuse pin-free rows).
- `tools/lanes/coherence_perturb.py`: the round-33 catalogue moves screened by the cc1 listing at the module recipe, with the current text's listing at the recorded recipe as the retail target; depth 1 and 2, an erase-then-perturb mode for pinned rows, and a rescore band (byte-exact recipe pairs differ by two listing lines in 62 of 150 calibration rows, delay-slot spelling). 129 pin-free nonconforming rows, 10,711 candidates, 10 rows made byte-exact at their module recipe by one or two ordinary moves (width changes, a hoisted expression, a duplicated tail, parameter-copy compositions, three address literals on FSF-only rows); the pinned rows (7,704 erase-then-perturb candidates) gave no new pin.

| row | from | to | how | pins |
|---|---|---|---|---:|
| `main/func_80013FB4` | 2.7.2 | 2.7.2-cdk-G0 | perturb:width_change | 0 -> 0 |
| `dungeon/func_800A7E08` | 2.95.2 | 2.7.2-cdk-G0 | perturb:hoist | 0 -> 0 |
| `dungeon/func_800942BC` | 2.7.2-G0 | 2.7.2-cdk-G0 | perturb:width_change | 0 -> 0 |
| `town/func_800A00A8` | 2.8.1-G0 -fno-strength-reduce | 2.7.2-cdk-G0 | perturb:dup_tail | 0 -> 0 |
| `dungeon/func_800C6828` | 2.7.2-cdk-G0 -fno-schedule-insns | 2.7.2-cdk-G0 | scan:pin erased | 1 -> 0 |
| `dungeon/func_7FFEDADC` | 2.7.2+-fno-schedule-insns | 2.7.2-cdk-G0 | perturb depth2:param_copy>merge | 0 -> 0 |
| `dungeon/func_80095AFC` | 2.7.2 | 2.7.2-cdk-G0 | perturb depth2:param_copy>stmt_shift | 0 -> 0 |
| `dungeon/func_8009A364` | 2.7.2-G0 | 2.7.2-cdk-G0 | perturb band2:addr_literal | 0 -> 0 |
| `town/func_806D2D84` | 2.7.2-G0 | 2.7.2-cdk-G0 | perturb band2:addr_literal | 0 -> 0 |
| `town/func_806D3018` | 2.7.2 | 2.7.2-cdk-G0 | perturb band2:addr_literal | 0 -> 0 |
| `dungeon/func_800D5A04` | 2.95.2-G0 | 2.7.2-cdk-G0 | perturb band2:width_change | 0 -> 0 |


`tools/lanes/land_coherence.sh` lands them: it verifies each candidate at the target recipe, switches the row's recipe, applies, restores the recipe if a row does not land, gates once, and records every row in `ledger/recipe_trades.jsonl`.

## Compiler facts established this round

- **2.7.2-cdk always splits symbol addresses.** Eleven probe functions (loads, stores, address taken, arrays, struct fields, loops): cdk emits `lui` into a real register with `%hi`/`%lo` in every case; FSF 2.7.2 emits the assembler macro form (expanded through `$at`) in every case; cdk rejects `-mno-split-addresses` and `-mno-gas`. A row whose retail bytes carry the `$at` expansion was not built by cdk whatever its C. The 53 pin-free nonconforming rows exact only at FSF 2.6.3/2.7.2 inside cdk-G0 modules form contiguous address runs (five in c_server between `func_80019A10` and `func_8001B2C8`, four in town/main.c): merged translation units in the module grouping, not shapes to reshape.
- **The listing screen's false-negative band is two lines** across recipes; the `-g` caveat of round 55 is a special case of it.
- **SLUS is excluded from the module census**: its rows are verified by object identity with the pinned TU, so they cannot be scored at another recipe, and each SLUS TU already has one recipe by construction. Corrected census: 65 overlay/main modules, 2,131 rows, 222 nonconforming (129 pin-free, 93 pinned with 395 pins) before this round's repairs.

## Bounded negatives

The uncapped flag scan's 90-row rescan with the lifted cap: 0. Erase-then-perturb at the module recipe: 0 new. Codex pack: 0 of 12 with per-row mechanism notes in `work/native_lane/r56_unserved1/last_message.txt` (delay-slot placement, constant-load scheduling, direction-table symbol forms, parameter widths). Rows within two listing lines of their module recipe after every move: 0 (listed in `ledger/coherence_perturb_band2.jsonl` as `nearest`).

## Next

1. The byte-neutral recipe reduction: 1,415 rows (1,304 pin-free, 111 pinned with 313 pins) whose current text is exact at their module recipe but recorded elsewhere (522 at 2.8.1-G0, 437 at 2.7.2, 186 at 2.7.2-cdk); rules 1-2 hold trivially; `tools/lanes/land_recipe_switch.sh`, one gate, every switch a `recipe-reduction` trade. Runs as round 56b right after this commit.
2. A mechanism probe, in the style of the cdk address probe, for the largest near-band residue class (`MOVED|1-2|-move +move`, 192 sites): what decides where sched2 places a register move. Tiny TUs first; a Workflow brief only if the probes stay opaque.
3. After the codex reset: a sol pack on the rows whose nearest coherence candidate is within two lines.

## Round 56b: the byte-neutral recipe reduction

`tools/lanes/land_recipe_switch.sh` re-recorded 1,414 rows (1,304 pin-free, 110 pinned with 313 pins) at their module census recipe; each was verified byte-exact there first, one row was skipped as no longer exact, nothing in `src/` changed. 297 windows MATCH, SLUS MATCH, row database and case ledger OK; 5,958 pins in 1,264 rows. Overlay and main rows by compiler cell afterwards: 2.7.2-cdk 3,454, 2.8.1 1,306, 2.7.2 634, 2.6.3 368, 2.8.0 57, 2.95.2 25, 2.91.66 17; flags remaining: -fno-schedule-insns 65, -fno-strength-reduce 59, -fno-cse-follow-jumps 52, -fno-schedule-insns2 33, -fno-expensive-optimizations 31, -O1 29, -fno-cse-skip-blocks 28, -fno-rerun-cse-after-loop 17. Every switch is a `recipe-reduction` entry in `ledger/recipe_trades.jsonl`. The census covered only the 65 strong/proven modules with ten or more rows; the weak-confidence modules (4,233 rows, 4,669 pins) are censused next, which also tests their grouping.
