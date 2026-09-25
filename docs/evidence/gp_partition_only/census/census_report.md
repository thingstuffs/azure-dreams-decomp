# Guarded generic whole-tree ASPSX census

Measured **6767** private registered rows with unchanged candidate tools. Two canonical-source records were remeasured in a separate pinned fixture and explicitly stitched into the frozen whole-tree journal. Pipeline exact: **6767**; self-check: **6767**; status errors: **0**. Rows matching the traced generic pipeline under at least one common genuine version: **6600**. The retail comparator found zero unmasked differences, with **872** masked words across **302** overlay rows.

| Container | Rows | Pipeline exact | Self-check | Genuine equals pipeline | Retail masked words / rows |
| --- | ---: | ---: | ---: | ---: | ---: |
| slus | 884 | 884 | 884 | 871 | 0 / 0 |
| main | 423 | 423 | 423 | 418 | 133 / 26 |
| town | 2695 | 2695 | 2695 | 2649 | 244 / 83 |
| dungeon | 2743 | 2743 | 2743 | 2642 | 492 / 192 |
| ovmovie | 22 | 22 | 22 | 20 | 3 / 1 |

The two selected partition-only owners retain complete physical-unit measurements. The code and code2 collector records retain their full logical functions and separate remainder measurements; owner-specific genuine results do not imply genuine equality for those remainders.

The six-version tables measure genuine-versus-pipeline equality. Direct retail comparison has zero unmasked differences, but its 872 relocation-masked words are not direct byte proofs. SLUS has zero masks in this census; the full SLUS image and active-window byte gates are separate stronger checks.

SLUS scope: **884** logical rows, **860** physical objects, **33** modules including **2** partition-only owners. The **20** partitioned logical records contain **29** physical-unit measurements across **10** sources. SLUS genuine-dependent rows: **13**.

Small-extern GP: the named-symbol detector lists zero rows. The sole `extern-abs` ablation is on the `slus/code` remainder; a pinned three-arm probe shows stripping externs and disabling `_expand_store_to_symbol_in_delay` produce identical listings and objects, with zero GPREL relocations in every arm. Its remaining difference is metadata-gated scheduling, not GP addressing. `_sink_call_separated_la` fired zero times and was required zero times; `_split_funcaddr_la` fired once and was required by `dungeon/func_818D4E68`.

The original raw journal and input pins are preserved in census_full/; its two old owner records remain there. The replacement records and source hashes are in census_final_two/, and the explicit old/new keys are in census_reconciled/receipt.json. Tables and physical-unit/pass TSVs from the unchanged private aspsx_report.py are in census_report/. The prior registry's 428 cfg_corrected annotations and one town assembler-flag override remain present; only 15 SLUS recipe fields were projected from the fresh registry.
