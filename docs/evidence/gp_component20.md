# `gp_01`: current inventory of the historical 20-row component

The frozen `gp_remaining38` snapshot labels this component `gp_01` and contains 20 rows. The current `ledger/maspsx_dependence.jsonl` has 199 records and 32 GP-affected rows; all 20 historical members remain present (19 direct small-extern causes and `slus/code2` with the combined cause). The other 12 current GP rows are outside this component. This report keeps the historical cohort and current32 denominator distinct.

The 20 rows still form a shared-symbol component in the frozen map. They span split positions 1–680, with 660 nonmembers inside that interval. The component has 22 symbols, 12 of which connect multiple rows. Full row and symbol evidence is in [inventory.json](gp_component20/inventory.json).

## Current recipes and source footprint

| Row | Current recipe | Source bytes | Lines | Lexical body lower bound | Ledger `defs` entries |
|---|---|---:|---:|---:|---:|
| `slus/code` | `2.7.2` | 32,093 | 1,486 | 156 | 221 |
| `slus/code2` | `2.8.1` | 9,565 | 364 | 24 | 32 |
| `slus/w_8003E34C` | `2.7.2-cdk` | 663 | 33 | 1 | 1 |
| `slus/w_8003E4FC` | `2.7.2-cdk` | 3,291 | 157 | 1 | 2 |
| `slus/w_8003E758` | `2.7.2-cdk -G32 -fno-expensive-optimizations` | 17,780 | 501 | 1 | 5 |
| `slus/w_8003F2A4` | `2.6.3 -fno-schedule-insns` | 1,306 | 44 | 1 | 1 |
| `slus/w_8003F368` | `2.7.2` | 2,825 | 116 | 1 | 5 |
| `slus/w_8003F5AC` | `2.7.2-cdk` | 332 | 18 | 1 | 1 |
| `slus/w_8003F624` | `2.7.2` | 796 | 26 | 1 | 3 |
| `slus/w_80041134` | `2.8.1` | 615 | 24 | 1 | 1 |
| `slus/w_8004B08C` | `2.7.2-cdk` | 1,873 | 59 | 1 | 7 |
| `slus/w_8004DCA8` | `2.8.1` | 1,507 | 28 | 1 | 1 |
| `slus/w_8004DCEC` | `2.7.2-cdk -fno-schedule-insns -fno-delayed-branch` | 364 | 15 | 1 | 1 |
| `slus/w_8004DD2C` | `2.7.2-cdk` | 999 | 38 | 1 | 3 |
| `slus/w_8004DDE4` | `2.7.2-cdk -fno-schedule-insns` | 1,451 | 51 | 1 | 3 |
| `slus/w_8004DE88` | `2.7.2-cdk` | 1,655 | 47 | 1 | 1 |
| `slus/w_8004DF8C` | `2.7.2-cdk` | 1,713 | 59 | 1 | 1 |
| `slus/w_8004E130` | `2.7.2-cdk` | 551 | 24 | 1 | 3 |
| `slus/w_80050DA8` | `2.7.2-cdk` | 969 | 33 | 1 | 3 |
| `slus/w_80050E20` | `2.7.2-cdk` | 1,206 | 50 | 1 | 3 |

Combined source footprint: 81,554 bytes and 3,173 lines. The lexical scanner finds 198 recognizable top-level function bodies across these files, a lower-bound metric only. `ledger/rows.jsonl` lists 221 `defs` entries for `slus/code` and 32 for `slus/code2`; those registry symbols can include aliases/include-derived entries and overlap neighboring row mappings, so they are not source-body counts. No definitive function total is claimed.

Current recipes are spread over seven exact variants: 10 rows use `2.7.2-cdk` with no flags; 3 use plain `2.7.2`; 3 use `2.8.1`; the other 4 each use a distinct flags/compiler variant. All 20 current split recipes match the historical snapshot fields, and every `asflags` is empty.

## Grouping constraints and recovered source evidence

- `slus/code` is the main shared-symbol bridge: it connects `D_80080B98`, `D_800814E0`, `D_80081540`, and `D_80081550/54/58`. Its registry row has 221 `defs` symbols and its source is the largest file here. Shared-symbol connectivity does not establish a retail TU boundary.
- The `w_8003E34C` / `w_8003E4FC` / `w_8003E758` / `w_8003F5AC` cluster shares `D_80080AD0/AD4/ADC`; `D_800814D0` further links `code2`, `w_8003F2A4`, and `w_8003F368`. These rows cross `2.7.2-cdk`, `2.6.3`, plain `2.7.2`, and `2.8.1` recipes.
- The `D_80081550/54/58` cluster (`code`, `w_8004DCA8`, and `w_8004DCEC` through `w_8004E130`) includes adjacent local rows, but `code` remains a separate large source. `w_80050DA8` and `w_80050E20` share `D_80080B98` with `code`, at split positions 679–680.
- `ledger/evidence/rows.jsonl` indexes recovered evidence for 10 of these 20 IDs. None of the indexed rows has assertion sites/copies or developer identifiers. `slus/code` has 26 prior knowledge notes and six script-call names; nine other indexed rows have prior knowledge notes, and three of those carry applied names. The remaining ten IDs have no evidence-index row (the generator omits rows with no evidence fields). Per-ID details are in `inventory.json`.
- `docs/EVIDENCE.md` describes a recovered source map from assertion file/line facts for TOWN/MAIN code. It supplies no assertion-based source placement for this SLUS component. `config/slus_modules.json` currently assigns none of these rows or symbols to a module. These absences leave placement open; they neither preclude evidence-backed present ownership nor establish a historical retail TU boundary.
- Path ambiguity: `ledger/splits/slus.jsonl` records logical `src/<basename>.c` paths, while the GP row inventory and current files use `src/slus/<basename>.c`. The inventory joins them by row ID and basename; the split path alone is not source-map proof.

## Evidence and limits

Current GP membership comes from `ledger/maspsx_dependence.jsonl`; current recipes and split positions come from `ledger/splits/slus.jsonl`; registry definitions come from `ledger/rows.jsonl`. Historical graph edges and GP source-use/declaration sites come from `work/native_lane/gp_remaining38/cohorts.json` and `docs/evidence/fidelity_gp_symbols.tsv`. Recovered naming/source evidence was limited to these IDs in `ledger/evidence/rows.jsonl`, interpreted through `docs/EVIDENCE.md` and `tools/evidence.py`. Actual source sizes, lines, and lexical lower-bound body counts were measured only in the 20 named files. No build or compile was run, and no whole-tree source scan was performed. Asset-backed symbols remain untyped by this inventory.

Next primary analysis: establish per-access retail addressing and actual object extents for one local cluster before any grouping trial. Keep `code`/`code2` bridges and their different recipes explicit; shared names alone do not justify one combined TU.

## Subsequent function-level work

The production denominator is now 29 GP rows; all 20 historical members remain.
The [combined private rehearsal](gp_ready14.md) prepares the other nine. A
[focused CD-state audit](gp_component20_local/REPORT.md) maps all 860 retail
words in the four local functions and records AD0/AD4/ADC access widths and
initial bytes, without asserting one shared recipe or historical TU.

The [E0 partition prototype](gp_e0_partition.md) is more concrete: extracting
one function from each collector into the adjacent 41134 list unit gives real
C storage, all 44 genuine-exact words, and a full retail-exact stock image. It
is not registry-compatible yet: the current whole-row membership gate correctly
refuses that redistribution. The next architecture task is explicit function
provenance and complete collector-remainder verification, using E0 as a bounded
pilot. No production rows or dependency records are moved by this experiment.
