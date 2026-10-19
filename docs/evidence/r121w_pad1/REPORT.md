# r121w_pad1: linker-owned overlay words

Launch snapshot: `29b3b1f432004b94f5d9a310b890b3da98d3959e` (`SCRATCH_HEAD`). The supplied private root had no Git metadata. A private Git baseline preserves its launch contents; `delivery.patch` is the repository-relative diff against that baseline. No work or ref changes were made outside this private root.

## Per-item status

| Kind | Converted | Held | Bytes |
|---|---:|---:|---:|
| Alignment padding | 57 | 0 | 228 |
| Overlay data pointer | 56 | 0 | 224 |
| Entry point word | 27 | 0 | 108 |
| Total | 140 | 0 | 560 |

`results.tsv` records each TU and its replacement. All 140 were own-file homes; no relink or non-home hand copy was converted. The 140 deleted sources have no current registry, split, layout, source-index, physical-build-graph or rodata-owner reference. `ledger/link_data_retired.jsonl` preserves append-only events, original source hashes, frozen baseline hashes and replacement identities. Historical evidence ledgers remain historical.

Each replacement is a complete four-byte v1 `data` or `padding` slice image in `config/link/dungeon/word_<foff>.json`, with offset, length, SHA-256, extractor and canonical symbol binding. These records do not assert an enclosing overlay boundary. No retail payload, fill pattern, compiler binary, new C, pins or masking is added. Public maps reproduce the same intervals and bindings.

## Symbol binding and build behavior

The window extractor verifies each exact word against its committed SHA-256 and publishes a private slice. The gate inserts that slice only into its raw gap; partial windows, duplicate ownership and source/split overlaps fail closed. `link_data.symbols.txt` supplies canonical address definitions to every row mini-link and the final link for undefined C references. Existing alias lowering still uses `config/names.tsv`. The final raw assembly of every scoped window was inspected: all 140 promised words remain present after module projection.

Emitting link-list files participate in window input hashes even when a word has no C row. Census replay consumes the same validated records; its snapshot binds the loader and all 140 records. Accepted matched-read and strict-prefix source hashes are unchanged. The only physical census delta is 228 bytes from proven data to padding; all code and unknown totals are unchanged.

## Proof

- Row database: PASS. Relink lint: zero problems; allowlist unchanged.
- Targeted link-list, extraction, map and source-layout tests: 93 PASS, including a real MIPS link with a retained data symbol. Census tests: 13 PASS.
- Disc extraction: 140 verified words / 560 bytes. Metadata preflight: all 80 active touched windows / 140 unique words.
- Whole-container public byte maps: PASS for all five roots, 50,952,192 bytes.
- Fresh census `regenerate.py --root . --disc 'bin/Azure Dreams.bin' --output work/native_lane/r121w_pad1/census_final --check`: PASS, **diff empty**, 1783 files. Map-set SHA-256: `10d258990ab2b7f35da42bbd9e97826441f77b1d9308405c96326195294c543e`.
- **One** fresh scoped `gate_all.py --all --workers 4` invocation with 80 explicit `--only-window` arguments: **80/80 MATCH**, exit 0. Its closing input audit passed. Scope and per-window input hashes are in `touched_windows.txt` and `gate_journal.jsonl`. No cached window proof was substituted.

Tool changes affect global tool identities. This lane's byte proof covers its 80 touched production windows; normal integration consolidation covers the remaining windows and renews affected module certificates. No new module-level certificate claim is made here.

## Deliveries

`delivery.patch`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, this report and compact supporting proofs. `proof_summary.json` is the bounded proof index. Raw private module bundles and regenerated retail files are excluded; `receipt_manifest.json` records receipt sizes and SHA-256 hashes. No receipt over 2 MB is copied into the patch.

## Holds by reason

None. `holds.tsv` contains its header only.

## HOW TO CONTINUE

Apply `delivery.patch` at the launch snapshot (or the corresponding rebased integration tree). Recreate the private build view with `bash tools/build/mk_ovl_root.sh`. Re-run row database, relink lint and census regeneration checks during integration; include the normal consolidation gate for other windows affected by the tool identity changes. The lane's one-gate marker prevents an accidental second lane invocation. Address new integration conflicts at their actual input paths; do not restore the retired C words or commit extracted blobs.
