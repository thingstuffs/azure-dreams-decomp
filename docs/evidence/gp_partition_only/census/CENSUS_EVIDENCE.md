# Partition-only candidate: whole-tree fidelity census

This is private evidence for the 57-target transition payload. Production files were not edited by these probes. The before/after production snapshot covers all 869 active objects and the relevant tool, source, and configuration inputs; `census_setup.py verify` passed.

## Measured result

The frozen whole-registry run measured all 6,767 identities: 6,765 succeeded and two failed the owner-aggregator include-order contract (`slus/w_8003D92C`, `slus/w_80049F68`). That original journal remains at `census_full/journal.jsonl`. The final payload moves each body to its canonical member and makes the aggregator include it once. A separate, pinned two-row run against those four corrected C sources passed both rows, with fresh source keys and full six-version measurements. `census_reconcile.py` replaced exactly those two records, retaining the originals and their old/new keys in `census_reconciled/receipt.json`.

The reconciled report has 6,767/6,767 successful scorer/generic comparisons and traced-object self-checks. Its separate `maspsx_retail` comparator reports zero **unmasked** differences, with **872 masked words across 302 overlay rows**: main 133/26, town 244/83, dungeon 492/192, and ovmovie 3/1 (words/rows). SLUS has zero masked words. The masked overlay words are not direct byte proofs; full SLUS image and active-window byte gates are separate stronger checks. Genuine ASPSX equals the traced generic pipeline under at least one common version for 6,600 rows; 167 retain genuine-vs-pipeline differences. These version counts do not assert direct retail byte identity. Exact/assembled genuine-versus-pipeline counts by version are 2.56 **1,996/2,048**, 2.67 **6,595/6,767**, 2.77 **6,600/6,767**, 2.79 **6,600/6,767**, 2.81 **6,600/6,767**, and 2.86 **6,594/6,767**. The complete six-version table and every dependent row are in scoped `census_report/tables.md`; `tables_raw.md` preserves the unchanged reporter output.

SLUS contributes 884 logical rows, 860 physical objects, and 33 modules, including two partition-only owners. Twenty logical rows have plural records: 29 physical-unit measurements over ten distinct sources. Both new owners are complete, zero-mask retail and genuine exact: `accessors_814c8` has two functions/six words; `table_counters_b1b_b1c` has one function/11 words. Thirteen SLUS logical rows remain genuine-dependent, including the code remainder (149 functions/1,218 words) and code2 remainder (21/213); their selected owners are separately exact. The ready29 private stage also established the full retail image, 70 data records, and 29 fresh owner functions/1,949 words at genuine 2.79.

The named external-GP detector lists zero rows. The sole `extern-abs` ablation belongs to the code remainder. `code_metadata_probe/receipt.json` proves that removing extern directives and disabling `_expand_store_to_symbol_in_delay` produce identical listings and objects, with zero GPREL relocations in all three arms. Its residual is metadata-gated scheduling, not external-GP addressing. `_sink_call_separated_la` fired on zero rows/units and was required by none; `_split_funcaddr_la` fired on one row and is required by `dungeon/func_818D4E68`.

The 57-target payload compatibility audit is `census_transition_compatibility.json`. Thirty-eight targets match frozen fixture bytes. Four source-hygiene edits are bridged by identical raw CDK assembly; D92C then has a second canonical-include step, and both canonical owner assemblies differ only in `.file` metadata. The two member fragments are pinned as moved bodies. The complete 884-record split ledger is JSON-semantically identical despite serialization differences. The final configure delta only adds the 15 historical whole-row recipe assignments. Seven remaining differences are tests, and three are new documentation/tests. The source/tool bridge does not claim the frozen initial C bytes equal the final payload.

## Pinned receipts

| Artifact | SHA-256 |
| --- | --- |
| `census_fixture/census_setup_receipt.json` | `102a84ba40d96bbf66cd27cd61ba97456e367728de8edb7a87b7cf2db595b8f3` |
| `census_full/receipt.json` | `982edfb5293c7989e4acfc3e7ab124dbd7acc54810d12a538dd03df878f8dfac` |
| `census_final_fixture/final_source_fixture_receipt.json` | `0e7b6acb9ecd25d511d9f0444451d16f9f825f791fe191deeff6a271049dca48` |
| `census_final_two/receipt.json` | `1fdf47afa06f19f84be4a1ea68d6b476fee63a6ab250839f6c644e0debcdc612` |
| `census_reconciled/receipt.json` | `b13ec7a4b2b8f99d6d3cd8cfad991bae5b2651d72c8bb9cc6100d9421e54bbd9` |
| `census_transition_compatibility.json` | `7762945b7178b34e4838cb1e8d2002de4fa20909d7635822a779d19a7b9287cc` |
| `code_metadata_probe/receipt.json` | `201be8d71350e4c7336bcf8bafc9ff212ad23c258b6e02517841c652727fff54` |
| `census_report/summary.json` | `239cd089390ca6f06e9c6ce163e216326476fabfa21fd047f19a890ddfc1a1f6` |
| `transition/transition.patch` | `1edc3b64c5d0a359ecfa1774420f2a5585756c57bd467ab053c7c1d522554400` |
| `transition/inventory.json` | `e84ef4b1abd4c8c9f68930c991ef412e3ce5df553f7aff46fe6f5acb43d9aa0f` |

The projected registry SHA-256 is `dad8bb076a6c6c2479aa488f24419394976040a42797a4783a1912426ce608bb`. It retains all 6,767 identities and pre-existing metadata, including 428 `cfg_corrected` annotations and the `town/func_80614B88` assembler-flag override. Only 15 SLUS recipe fields were projected from a fresh private registry. The complete private SLUS partition plan and Ninja recipe are pinned in `census_fixture/`.

## Reproduction sequence

These commands describe a fresh copy of this lane; the scripts refuse to overwrite existing evidence directories. `census_runner.py` invokes the unchanged private `A.process_row` with short, per-worker ASPSX scratch and no result substitutions. The first full command exits 1 because of the two preserved source-contract errors.

```sh
python3 work/native_lane/gp_partition_only_tools/census_setup.py prepare
python3 work/native_lane/gp_partition_only_tools/census_runner.py --fixture work/native_lane/gp_partition_only_tools/census_fixture --output work/native_lane/gp_partition_only_tools/census_full --workers 4
python3 work/native_lane/gp_partition_only_tools/census_setup.py verify
python3 work/native_lane/gp_partition_only_tools/census_compatibility.py
python3 work/native_lane/gp_partition_only_tools/census_final_source.py
python3 work/native_lane/gp_partition_only_tools/census_runner.py --fixture work/native_lane/gp_partition_only_tools/census_final_fixture --output work/native_lane/gp_partition_only_tools/census_final_two --only slus/w_8003D92C,slus/w_80049F68 --workers 1
python3 work/native_lane/gp_partition_only_tools/census_reconcile.py
python3 work/native_lane/gp_partition_only_tools/census_report.py
```

`census_original_report/` retains the unstitched differential tables. `census_code_repro/scratch/` archives the extra unchanged-code compiler stream and traced object, with 55 file hashes in `scratch_pins.json`; the decisive three-arm attribution is the separate `code_metadata_probe/`.
