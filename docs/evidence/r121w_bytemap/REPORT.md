# r121w_bytemap — whole-image link lists

Base: staged B10 private tree, SCRATCH_HEAD `ebf0bb89f11b43101506c3fdbfb1ac90bed4716a`.
All work stays under this private root. No source functions, names, registered extents, or retail payload files enter the patch.

The schema, generator/checker, extractor, and three-image prototype are implemented. The prototype proves exact physical coverage of **2,611,200 bytes**. It is a conservative coverage profile, not a reproduction of census2's classifications: the supplied `refs/` contains two reports, but no span export, census implementation, or final per-container classification files. This evidence dependency is retained as a hold.

## Per-item status

| brief item | status | result |
|---|---|---|
| 1 schema + gate behavior | delivered | `azure-clean.linklist.v1` adds data, padding, asset, leftover, unresolved, code-region and image-reference intervals. Code-entry objects remain unchanged. The production loader rejects gaps, overlaps, bad references and inconsistent census totals; metadata never enters compilation/rebinding indices. Unconverted sparse v0 lists remain supported explicitly. |
| 2 generator + checker | implemented; real census replay held | Any number of images can be generated from the documented disjoint JSONL census export plus coverage-region witnesses. Both input and output must tile, preserve code, and reproduce all seven declared class totals. Independent checking compares every label boundary. Exact census2 ingestion/replay awaits the absent interval export and its alignment with B10. |
| 3 user-disc extraction | delivered and exercised | ISO9660 container slices from raw MODE2/2352, raw MODE1/2352, or ISO/2048; streamed output under ignored `work/assets`; each SHA-256 verified before publication. Two real dungeon jump tables, 48 + 28 = 76 bytes, extracted successfully. |
| 4 prototype + size + tests | delivered; gate receipt below | Dungeon bank `0x1001000..0x1007000`, town module `0x3fe000..0x400000`, and all MAIN.BIN `0..2578432`; main references its complete load-image child without moving code. Four link files total 277,074 bytes. All 53 pre-existing sample code entries are unchanged. |

## Schema and implementation

`docs/LINK_LISTS.md` specifies every field and the census export interface. `tools/gate/linklist.py` accepts mixed v0/v1 trees. Only entries with the original TU shape populate its code indices. Additional intervals have `kind`, `foff`, `size`, and nonempty `evidence`; data carries a concrete evidenced type or literal `typing pending`, assets carry format/size/SHA-256/extractor, and leftovers require a positive reason. Unknown bytes remain `unresolved`. Library/strong code and proven code with no placement entry use `code_region`, never a fabricated TU.

A file-only parent can have `vma: null` and reference a complete v1 load image at its exact physical extent. References must remain in-container and acyclic. MAIN's load-address families and every existing home/placement relationship remain intact. The checker derives each parent's census recursively and excludes referenced children from the root denominator. Selected overlapping roots are refused; the stronger `--complete-containers` mode requires all five complete physical containers.

`tools/byte_map.py` validates the census export, clips it around preserved TU entries and child references, checks asset boundaries, validates declared totals, and optionally verifies asset bytes against extracted user containers. A dry run is the default; `--write` emits the validated maps. Unknown, padding and leftover are distinct states. The generator never upgrades an audit region or estimated-code heuristic into an admitted census classification.

Coverage-region categories are overlapping witnesses. Their per-image interval unions and the input hashes are recorded in `prototype_receipt.json`; these witness totals are not added to the census denominator. The maps bind labels-export and coverage-ledger SHA-256 values. Label replay with `check --labels` verifies the export identity and compares every boundary, so equal aggregate totals cannot hide a moved label.

`tools/extract_assets.py` and `tools/gate/disc_slice.py` read directory extents from the user's disc, then stream only declared slices. No disc-sector map or retail content is checked in. Missing files, unsupported multi-extent/interleaved records, truncated reads, out-of-file requests, unknown extractor IDs and incorrect hashes fail closed. Output paths must resolve under this root's ignored `work/assets`, including through symlinks. A failed hash leaves no published blob or temporary file. Duplicate container references do not duplicate extraction.

## Coverage proof on samples

The staged prototype uses existing MATCH C rows first, explicit MATCH `row_kind=data` objects next, then the census method's zero-run rule outside these objects. Platform assembly retains library classification. Audit `data_segment` flags and estimated-code coverage are not accepted as independent proof. Two descriptor-only object types stay pending. Remaining bytes stay unknown. This intentionally lacks census2's instance, admitted-tier, format and neighbour passes.

| physical root | bytes | proven code | library | proven data | pending type | padding | unknown |
|---|---:|---:|---:|---:|---:|---:|---:|
| `dungeon/bank_1001000` | 24,576 | 14,216 | 0 | 160 | 8 | 0 | 10,192 |
| `main/main_bin` | 2,578,432 | 64,968 | 72 | 0 | 0 | 102,523 | 2,410,869 |
| `town/image_3fe000` | 8,192 | 3,180 | 0 | 0 | 0 | 1,472 | 3,540 |

Strongly-code is zero in this conservative profile. The three physical roots sum to 2,611,200 bytes. Their totals sum independently to the same number. MAIN's 36,864-byte `image_25c800` is a referenced child, already included in the MAIN root; it is not counted again. No leftovers are asserted in the real samples because the provided evidence does not prove them. Synthetic tests cover that schema branch.

| generated link file | entries | UTF-8 bytes |
|---|---:|---:|
| `dungeon/bank_1001000` | 36 | 8,424 |
| `main/image_25c800` | 255 | 44,488 |
| `main/main_bin` | 1333 | 212,825 |
| `town/image_3fe000` | 63 | 11,337 |

The four link files total **277,074 bytes** (about 270.6 KiB); the source census-profile JSONL is **302,515 bytes**. Files contain only offsets, lengths, labels, evidence references, binding metadata and hashes. Their total size is about 10.61% of the sampled physical byte denominator, including the child-map metadata. No binary payload, compressed retail copy, or encoded retail content appears in the delivery.

## Verification and receipts

- `linklist_receipt.json`: all **751** lists load, all **9,116** code placements retain their code-only indices, no link-list/row-database consistency problems, **53** unchanged sample code entry objects.
- `test_receipt.json`: **176 tests pass**: 26 new byte-map/extraction tests, existing link-list and source-layout tests, and overlay/module scoped-fingerprint tests. Negative cases include gaps, overlaps, trailing gaps, wrong totals, swapped labels with unchanged totals, sparse or cyclic image references, unknown-to-leftover/type promotion, stale code conflicts, bad hashes, output escapes and malformed/truncated disc reads. The first combined invocation lacked the existing module test's sibling-fixture import path; its failure hash is retained and the corrected invocation uses `PYTHONPATH=tools/tests` without a product change.
- `reproduction_receipt.json`: two fresh prototype reruns reproduce all four map files, the labels JSONL and the prototype receipt byte-for-byte.
- `extraction_receipt.json`: two real blobs, 76 bytes, verified from the staged user's disc. Blobs remain under ignored `work/assets` and are excluded from the patch.
- `touched_windows.json`: the complete eight-window intersection with the three sample roots.
- `gate_receipt.json`: **8/8 MATCH**, exit 0, four workers, 222.625 seconds including the successful final 8/8 input audit. The receipt records the loader tool SHA-256, the identical build-view tool hash, all four map hashes, and every window's input digest.
- `delivery_manifest.json`: **22 files**, 674,356-byte text patch; SHA-256 `90e8c11957c1f732df5ba182303d9dc4be3d845ac801df4a5d14a6c692dd54ad`. `git apply --check` and actual application to a private reconstruction pass, and every reconstructed file matches its delivered SHA-256.

Detailed raw logs and generated build products remain in ignored lane `scratch/` or the private build view. Compact receipts retain their sizes and SHA-256 values. No receipt larger than 2 MB or binary is delivered. Only one final scoped gate was requested, with `--workers 4` and explicit `--only-window`/`--require-window` for each of the eight touched windows; no full gate is run.

## Deliveries

`delivery.patch` contains the tools, schema documentation, tests, four prototype link files, ignored asset-output rules, the prototype reproducer and labels export, compact receipts and the patch reproducer. `delivery_manifest.json` lists each included path's SHA-256 and byte length. `REPORT.md` is the standalone report. The patch is generated from retained staged originals rather than any shared git state; no commits or ref moves occur.

## Holds by reason

1. **Missing classification evidence:** `refs/census_method.md` and `refs/census2_REPORT.md` provide methods and aggregate numbers, but not exact final disjoint spans. Reconstructing those classifications from prose would fabricate evidence. Exact replay of 50,952,192 bytes, 31,211,087 typing-pending bytes, and 14,386 unknown bytes is not claimed. This prototype's unknown totals are scoped conservative holds, not a regression in the separate census2 result.
2. **Snapshot alignment:** census2's report is based on B6 plus its cumulative continuation; this private root is staged B10. A fresh export must reconcile current rows and evidence. Existing TU/census conflicts are rejected rather than clipped away or relabelled silently.
3. **Physical ownership for rollout:** 747 other link-list images remain v0, including overlapping historical placement views. A full-container owner map needs explicit nonoverlapping physical roots and canonical image references. No unproved VMA, type, leftover status, or code entry is invented to force full coverage.
4. **Formats/types still pending:** descriptor-only objects and terminal non-code do not gain concrete types from coverage alone. For proven data without a concrete type, an evidenced physical slice can use an opaque asset representation while retaining its census class and verified hash. Unknown bytes require new evidence before becoming assets or data.

## HOW TO CONTINUE

1. Apply `delivery.patch` to the staged B10 tree. Keep the five original files under lane `scratch/before/` if re-emitting the cumulative patch; `deliver.py` needs those originals. The patch and all receipts exclude retail blobs. Use the user's own existing disc extraction for the prototype and gate commands.
2. Reproduce and check the sample maps from the repo root:

   ```sh
   python3 work/native_lane/r121w_bytemap/prototype.py
   python3 tools/byte_map.py check --labels work/native_lane/r121w_bytemap/prototype_labels.jsonl
   python3 tools/extract_assets.py --disc 'bin/Azure Dreams.bin'
   PYTHONPATH=tools/tests TMPDIR="$PWD/work/native_lane/r121w_bytemap/scratch" python3 -m unittest tools.tests.test_byte_map tools.tests.test_linklist tools.tests.test_source_layout tools.tests.test_overlay_scoped_fingerprint tools.tests.test_module_scoped_fingerprint -q
   ```

3. Place a current, evidenced census2 disjoint-span export inside the authorized private root. Adapt it to the documented `azure-clean.census-map.v1` JSONL headers/spans. Preserve all seven classes, evidence kinds, padding-vs-leftover distinction, actual asset boundaries, and code/data type evidence. Compute asset SHA-256 from the user's own bytes. Use opaque format only for independently proved non-code. If a code-placement span disagrees with the census snapshot, resolve that evidence mismatch first.
4. Select canonical physical load-image owners per container; do not count overlapping aliases twice. Build complete child maps and file-only container parents for MAIN, TOWN, DUNGEON, OVMOVIE and SLUS. Run the generator dry first, inspect sizes/totals, then write and require the complete-container proof:

   ```sh
   python3 tools/byte_map.py generate --labels <current-export.jsonl> --verify-retail
   python3 tools/byte_map.py generate --labels <current-export.jsonl> --verify-retail --write
   python3 tools/byte_map.py check --labels <current-export.jsonl> --complete-containers
   ```

5. Compare the resulting global and per-container totals with the same census export, retaining unresolved and typing-pending holds. Refresh the generated view with `bash tools/build/mk_ovl_root.sh`; gate only windows intersecting newly touched maps, using four workers. Gate-tool changes invalidate older certificates; retain their historical receipts and refresh the affected proofs through the normal owner workflow.
6. Once this lane changes again, run `python3 work/native_lane/r121w_bytemap/deliver.py` to reconstruct the cumulative text patch and compare every applied file with the delivery manifest. The existing scoped gate receipt applies only to the exact tool/map hashes it records.
