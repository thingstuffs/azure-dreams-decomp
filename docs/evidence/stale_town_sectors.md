# Stale Town code in DUNGEON.BIN

The comparisons below describe the original fragment leads. The exact runs
have physical ownership records in `ledger/coverage_regions.jsonl` and
`link/leftovers/stale_images/intervals.json`. The full comparisons and
individual diagnostic splits are in [retail byte ownership](retail_byte_ownership.json).

| DUNGEON offset | Size | Equal words in TOWN at the same offset |
|---|---:|---:|
| `0x16ae8` | 32 | 8 of 8 |
| `0x1e0f4` | 148 | 35 of 37 |
| `0x20e20` | 404 | 101 of 101 |
| `0x4dae0` | 60 | 15 of 15 |

The exact match starts at `0x1e0fc`, after the two differing words at
`0x1e0f4` and `0x1e0f8`. The first 35 matching words reach the return and
delay slot of Town's `func_8009B828` at `0x1e184`. The matching run continues
through the sector boundary at `0x1e800`. At `0x20e20`, the first 101 words
are the tail of `func_8009E504`. The run continues through `0x21000`.
