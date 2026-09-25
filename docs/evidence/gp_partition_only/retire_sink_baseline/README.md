# Private sink-retirement baseline archive stage

This is the **pre-validation-controls-refresh** proof, staged for review. It is not the final validation-controls run or authorization to activate the assembler change. The stage contains no copied fixture/build trees, full retail image, or large object set.

The 44 files under `artifacts/` include the exact removal, supplemental, and test-migration patches; candidate CLI and package; preparation, verification, combined, and overlay scripts; receipts and logs; the combined source, frozen, and production pins; ownership and two placement certificates; the former-consumer object comparison; and the completed 2,175-window overlay journal. The census summary and frozen GP57 ownership/input-pin receipts provide the bounded lineage for the combined proof.

`index.json` records each artifact's repository-relative original path, original SHA-256, staged path, staged SHA-256, size, format, and replacement counts. UTF-8 text replaces the workspace root with `<repo>` and the reference repository root with `<reference-repo>`. The three `.o` files are copied byte-for-byte and all hash to `ec50b0f0dcc399fb1e586450aa2581dd89f810ceb5c305551474b87b4268ee0c`. Ten text artifacts needed scrubbing. No JSON/JSONL input exceeded 1 MB; `stage.py` applies deterministic gzip (`mtime=0`) when that threshold is crossed.

The combined proof wrote `combined_production_before.json` and `combined_frozen_before.json`. Its end-of-run `combined_receipt.json` records `production_unchanged: true` and `frozen_fixture_unchanged: true` after recomputing both snapshots; it did not serialize separate post-run snapshots. This archive preserves that distinction. The overlay receipt independently records identical pre/post tracked-production and candidate hashes.

`python3 work/native_lane/gp_partition_only_tools/retire_sink/archive_stage/stage.py` staged and verified all 44 source and archive hashes. The stage is intentionally one-shot and refuses to overwrite `artifacts/`; verification of an existing stage can call `verify()` from that script. The index SHA-256 is `6345dbe4c34c432520248ae7c6ab84c35b139e03ffa3f8ea275262ca781cc9dc`.
