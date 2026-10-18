# r121w_goto4b

Base B13: `ddc07bc5949684593cdc45a67e378a1f18324318`. This supplied snapshot has no Git metadata; `preimage_manifest.json` binds the patch preimages. No commits or ref moves were made.

Removed **12 gotos**. Queue census: **126 → 114**, across 68 files. Status: **6 exact goto-free, 4 exact partial, 58 held**. The documented legacy copy `80B79054` is unchanged and skipped. Home-only counts: **125 → 113 gotos**, and **67 → 61 files still containing goto**. No new coverage or rows are claimed.

All 10 installed homes (23,340 validation bytes; no new coverage) independently recompile exactly at their unchanged recipes. One final scoped production gate, four workers: **32/32 windows MATCH**, including the current-input audit. The closure includes 87 affected rows, with native siblings and all existing shared-source placements.

No headers, rowbase records, recipes, registry rows, link lists, raw first passes, compiler or assembler tools were changed. Existing semantic field operations and legacy mechanisms remain in their original source regions; no pins, asm, volatile, pragmas, fake loops or comparison masks were introduced.

## Per-item status

| File | Gotos before → after | Status |
|---|---:|---|

| `func_80AF1A80` | 11 → 11 | held |

| `func_800D3B60` | 8 → 8 | held |

| `func_800A8714` | 6 → 5 | partial |

| `func_81330C74` | 5 → 4 | partial |

| `func_81820800` | 4 → 4 | held |

| `func_800C5028` | 4 → 4 | held |

| `func_80084340` | 4 → 4 | held |

| `func_8133336C` | 3 → 3 | held |

| `func_810318E4` | 3 → 0 | exact |

| `func_80F03000` | 3 → 3 | held |

| `func_80EF1000` | 3 → 3 | held |

| `func_80EDF000` | 3 → 3 | held |

| `func_800C0848` | 3 → 3 | held |

| `func_819835AC` | 2 → 1 | partial |

| `func_813374E8` | 2 → 1 | partial |

| `func_810ADDF4` | 2 → 2 | held |

| `func_80E64FF0` | 2 → 2 | held |

| `func_80CC2494` | 2 → 2 | held |

| `func_8028AE2C` | 2 → 2 | held |

| `func_800C88C8` | 2 → 2 | held |

| `func_800C34BC` | 2 → 2 | held |

| `func_800C2E1C` | 2 → 2 | held |

| `func_8009C284` | 2 → 2 | held |

| `func_8009B70C` | 2 → 2 | held |

| `func_819B3414` | 1 → 1 | held |

| `func_81994D8C` | 1 → 1 | held |

| `func_81905FD0` | 1 → 1 | held |

| `func_818D4E68` | 1 → 1 | held |

| `func_818B7F38` | 1 → 1 | held |

| `func_818694D4` | 1 → 1 | held |

| `func_81856800` | 1 → 1 | held |

| `func_8182C800` | 1 → 1 | held |

| `func_81811C20` | 1 → 1 | held |

| `func_8180E7F4` | 1 → 1 | held |

| `func_8180D0DC` | 1 → 1 | held |

| `func_8133C2A4` | 1 → 1 | held |

| `func_81331C88` | 1 → 0 | exact |

| `func_812B87A4` | 1 → 1 | held |

| `func_810332A4` | 1 → 1 | held |

| `func_8102C664` | 1 → 1 | held |

| `func_8101A664` | 1 → 1 | held |

| `func_81008664` | 1 → 1 | held |

| `func_80FB402C` | 1 → 1 | held |

| `func_80E91000` | 1 → 1 | held |

| `func_80DBC9D8` | 1 → 1 | held |

| `func_80CE9F34` | 1 → 1 | held |

| `func_80B97094` | 1 → 1 | held |

| `func_80B85054` | 1 → 1 | held |

| `func_80B79054` | 1 → 1 | held |

| `func_80ABF07C` | 1 → 1 | held |

| `func_80A473B8` | 1 → 0 | exact |

| `func_807B0B3C` | 1 → 1 | held |

| `func_8028A328` | 1 → 1 | held |

| `func_80285E80` | 1 → 1 | held |

| `func_800D65FC` | 1 → 1 | held |

| `func_800D0820` | 1 → 1 | held |

| `func_800BE8D0` | 1 → 1 | held |

| `func_800B8758` | 1 → 1 | held |

| `func_800B2D84` | 1 → 1 | held |

| `func_800ACC98` | 1 → 1 | held |

| `func_800A3D40` | 1 → 1 | held |

| `func_800A2F7C` | 1 → 1 | held |

| `func_8009F36C` | 1 → 0 | exact |

| `func_8009CCC4` | 1 → 0 | exact |

| `func_8009A3D4` | 1 → 1 | held |

| `func_80095A04` | 1 → 1 | held |

| `func_8008F228` | 1 → 0 | exact |

| `func_8008EB10` | 1 → 1 | held |


`results.tsv` records every queued file, all attempted shapes, closest measured candidates, and hold reasons. `holds.tsv` contains the unresolved subset.

## Deliveries

`delivery.patch` contains source and ledger deltas only. The lane directory, toolchain, objects and retail data are excluded. Also delivered: `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, `REPORT.md`, `preimage_manifest.json`, `source_receipts.json`, `gate_summary.json`, `audit_summary.json`, and `audit.log`. Internal compiler diagnostics, candidates, and complete gate artifacts are retained under this lane; large receipts are represented by hashes and compact summaries.

## Measured mechanisms

`810318E4`: explicit special-target, existing-target and created-target arms repeat only the three coordinate-copy statements. This removes all three gotos while preserving the complete 1,612-byte home and switch table. Its six existing placements also use the cleaned home; they add zero coverage.

`819835AC`: the owner-retirement arm is tested directly and falls through to the continuing-owner path. Its earlier fade-tail goto remains; duplicating that retirement tail still fails the switch-table target check.

`80A473B8`: the ground-reset arm is repeated with its own bob-offset, ground-height and floor-correction locals. Retaining the original signed halfword types closes the allocation differences. All bytes match with no goto.

`81330C74`, `813374E8`, and `81331C88`: index the stable object/part base by the existing color index, then use a genuine do/while loop. This closes one color-loop back edge in each home. `8009F36C`, `8009CCC4`, and `8008F228` similarly index status slots, spell slots, and dispatch fields from their stable bases. Unused moving cursors and redundant loop blocks were removed and scored independently.

`800A8714`: repeat the short room/default-result tail only in the earlier kind/flag arm; the remaining five gotos and their emission order are retained.

The first pass measured ordinary real-loop spellings at the supplied recipes; the second tested shared tails, real switch arms, early returns and explicit if/else. Revisit passes tested indexed stable bases, loop induction scopes, and repaired generated candidates that had duplicate local labels. Compiler and jump-table failures are retained as failures; none is installed.

The lane recorded 67 exact home baselines and 238 candidate measurements, including measured failures and final readability tidying. Ordinary candidates use the aligned row scorer; the four rows with a non-authoritative isolated baseline also use their reviewed complete TU. The production gate independently validates every changed native cohort.

The item-compaction rebuild has a full sixteen-word site map in `evidence/item_compact_site_map.md`. The fingerprint scan has no family-specific evidence for this leaf; the supplied recipe and exact preimage remain the authority. The ordinary loop rebases its cursor by 0x29C; stable-page and typed-slot hypotheses remain measured holds. No compiler-version limitation is claimed.

`800C2E1C`: the closest fully structured success-arm candidate has two substitutions / zero indels, both branch destinations landing before the final sign test instead of directly inside the error arm. Explicit error returns and signed-result lifetime variants were also measured. No near miss is delivered.

The two existing certificates for `dungeon_engine_experience` and `dungeon_resource06_slot0` are renewed from this same gate's fifteen native-window receipts. No certification window is rebuilt; no new module adoption is claimed.

## Holds by reason

- 11: structured C changes branch condition.

- 8: structured C changes branch/block layout.

- 6: switch-table mismatch.

- 5: structured C changes address calculation.

- 5: structured C changes constant rematerialization.

- 4: exact partial; remaining control edges unclosed.

- 4: structured C changes generated extent.

- 4: structured C changes register allocation.

- 3: complete module payload/byte mismatch.

- 3: structured C changes instruction placement.

- 2: candidate compiler/extent check failed.

- 2: structured C changes instructions and allocation.

- 2: structured C changes register live ranges.

- 1: frozen legacy relink copy; goto3 report.

- 1: structured C changes constant materialization.

- 1: structured C changes delay-slot scheduling.


Counts above are item records, not uncovered bytes. Exact partial files remain eligible for further cleanup and are not represented as fully goto-free.

## HOW TO CONTINUE

1. Apply `delivery.patch` only to the B13 preimages bound in `preimage_manifest.json`. Reconstruct every final SHA-256. Do not count existing shared placements again.

2. Start with the held candidates named in `results.tsv`. Prefer the smallest aligned residuals; inspect the aligned regions and actual jump-table checks before further edits. Generated duplicate-label errors are invalid candidates, not compiler walls.

3. Continue the item-table routine from its site map and measured stable-base candidates using `az-c-rebuild`; preserve the final independent page rematerialization and surviving index. Continue the status-pair routine from the two-branch-destination miss.

4. Preserve the exact installed reductions when revisiting partial homes. Skip the legacy relink copy. Keep every new source edit inside this fixed queue unless a necessary shared header extension is explicitly recorded.

5. After new exact work, recompute source/module/placement closure, validate the exported view, run one scoped gate with `--workers 4 --only-window ...`, and renew any existing native certificates using that same gate’s receipts. Internal proof payloads are not shipped; regenerate them on integration when needed.
