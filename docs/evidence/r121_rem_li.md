# r121 rem_li: nine li-expansion remnants closed with the old-assembler dial

9 exact ordinary C rows /452 B (town). Each piece compiled to retail-identical code except that retail has
`ori rX,$zero,K` where the stock assembler expands `li` to `addiu rX,$zero,K` (ASPSX older than 2.50,
maspsx `expand_li`). The pieces sit in the town old-assembler island already established by decision 49
(r97_decisions.md; 22 genuine-2.34 rows). Recipe: the fixed 2.6.3-G0 plus the per-row as-flag
`--aspsx-version=2.40` (config/overlays/town.as_flags.jsonl, one proof record per row, with true-name alias).
No C was changed to dodge the difference.

| Row | foff | size | retail diff (scorer) | genuine 2.34 / 2.21 vs retail |
|---|---|---|---|---|
| town/func_80875808 | 0x7F5808 | 80 | exact (0) | exact / exact |
| town/func_80875858 | 0x7F5858 | 84 | exact (0) | exact / exact |
| town/func_808758AC | 0x7F58AC | 96 | exact (0) | exact / exact |
| town/func_8087FFD0 | 0x7FFFD0 | 32 | exact (0) | exact / exact |
| town/func_8087FFF0 | 0x7FFFF0 | 32 | exact (0) | exact / exact |
| town/func_80880010 | 0x800010 | 32 | exact (0) | exact / exact |
| town/func_80880030 | 0x800030 | 32 | exact (0) | exact / exact |
| town/func_80880050 | 0x800050 | 32 | exact (0) | exact / exact |
| town/func_80880070 | 0x800070 | 32 | exact (0) | exact / exact |

Windows: config/overlays/town_r121li_7F5808_true_80701808.overlay.yaml, config/overlays/town_r121li_7FFFD0_true_80700FD0.overlay.yaml. Without the dial both windows fail at the first li word (0x24 addiu vs 0x34 ori).
Per-row dial, not per-island: 0x8087FD58-0x808816D8 also contains one addiu TU (func_80880298).
No compiler-source or SDK-provenance claim beyond the established 2.34 island; see receipt for hashes.
