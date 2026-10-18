# LL6 cumulative B13 delivery, continuation 2

Base: `ddc07bc5949684593cdc45a67e378a1f18324318`. Both public-repo review defects are fixed.
`delivery.patch` is cumulative against actual B13 Git objects and supersedes pass 2.
`delivery_pass2.patch` remains unchanged (SHA-256
`8b80d3c3780b121b9a925a248ee930211a8c4328d0e159e49b71a3a367db1d06`). No lane file, retail payload, binary,
C/source change, raw move or production `config/link/` change enters the patch.

## Per-item status

| item | status | evidence/result |
|---|---|---|
| reproducible public evidence | **CLOSED** | committed census, helper, tests and small config inputs; rule IDs replace ignored paths; actual B13 clone + patch + user disc regenerates every map with empty diff |
| compact size | **CLOSED** | entire committed link tree 7,877,303 bytes; 1,318 TSV parts for 1,317 images; maximum file 1,501,960 bytes |
| pass-2 classifications | **PRESERVED** | uncached census spans exactly equal pass 2; every label boundary in all 1,317 views independently checked |
| TU/build decisions | **PRESERVED** | 10,359 original TU objects and all placement indices, geometry and bindings identical; 95/95 prior MATCH fingerprints current |
| whole-image rollout | **DELIVERED** | all five physical roots, 443 exported load/link views, 37 leftover slices; exact tiling of 50,952,192 physical bytes |
| census unknowns | **BOUNDED HOLDS** | 14,626 bytes in 625 disjoint intervals; 61 affected overlapping views |
| scene drafts | **MAPPED; TU HELD** | 25 descriptor records and A/B/C prefixes retained; full 24-twin extents and compiled shared placements remain unproved |
| debug NPC | **BOUNDS CLOSED; TU HELD** | 0x868000 is a complete 2,048-byte descriptor load; exact slice twin at 0x84E000; twin allocation and compiled TU still needed |
| test shop | **BOUNDS CLOSED; FAMILY HELD** | complete 2,048-byte load at 0x80B800; only two exact occurrences in all TOWN; four-copy/shared-TU claim remains unproved |
| devkit | **DELIVERED** | 3,587 symbol records: 678 + 2,909 arrays separated by 168 opaque bytes; no symbol names/values ship |
| stale images | **BOUNDED DELIVERY** | five existing stale/prior intervals, 2,288 bytes; further unreachability not inferred |

## Public evidence and regeneration proof

`tools/census/` now contains the census implementation, masked-prefix helper,
regeneration command and tests. `config/census/` contains the B13 input hashes,
SLUS layout, conditional bank map, 69 valid bounded-read records, three strict
replay prefixes and rule registry. The 541 stale proposals remain excluded;
none was re-signed. Instruction identities are hashes, rather than copied retail
words. All shipped inputs are metadata, addresses, types, extents and hashes.

Metadata evidence uses committed IDs such as `census:zero_fill>=16`,
`census:format:vab`, `census:noncode:decode` and label-specific neighbour rules.
The public catalogue contains zero `work/` evidence strings. Original TU notes
that mention ignored paths are losslessly recovered through their committed
`config/link/<image>.json` entries, without serializing those ignored paths into
the new maps. No build entry is edited. Header/load references also use committed
rule IDs. `docs/LINK_LISTS.md` documents the representation, readers and command.

The actual proof cloned B13 from Git, applied the cumulative patch with
`git apply --check` and `git apply --index`, and checked every delivered SHA-256.
The checkout had no `work/`, `baserom/`, lane, extracted containers or detector
cache. Its only retail input was the explicit user-owned disc. It ran:

```sh
python3 tools/census/regenerate.py --disc /path/to/Azure_Dreams.bin \
  --output /tmp/azure-census --check
```

The command extracts temporary containers from ISO9660 directory records, validates
B13 identities, runs all detectors/precision gates and bounded proofs afresh, and
regenerates all TSV/JSON byte maps. The generated file set and every byte equal
Git: **1,325 files, diff exit 0, stdout/stderr empty**.
The four generated summary/manifest files also equal this lane's final outputs.
Both independent uncached census runs reproduce all five raw span files and the
pass-2 labels. Temporary retail is removed; nothing is copied from an ignored lane
into the proof checkout. The checkout still has no work directory or untracked
files after reproduction. See `regeneration_proof.log`, `reproduction_receipt.json`
and `census_preservation_receipt.json`.

## Size before/after

Decimal UTF-8 bytes, including headers. `size_table.tsv` gives the same measurements.

| item | pass 2 bytes | pass 3 bytes | reduction | parts |
|---|---:|---:|---:|---:|
| town/town_bin | 10,698,972 | 2,297,483 | 78.53% | 2 |
| dungeon/dungeon_bin | 8,699,304 | 1,319,876 | 84.83% | 1 |
| town/leftover_symbol_dump | 2,686,236 | 599,921 | 77.67% | 1 |
| all logical image maps | 34,999,495 | 7,843,050 | 77.59% | 1318 |
| entire committed link tree | 35,200,446 | 7,877,303 | 77.62% | 1332 |
| cumulative delivery.patch | 36,598,197 | 8,818,693 | 75.9% |  |

The TSV has one interval per line with fixed short columns `o n k r h x`, a small
JSON header and shared attribute profiles. Adjacent equivalent metadata rules
are coalesced and merged assets rehashed. TU and image-reference boundaries remain.
TOWN's physical image is split into two deterministic parts; all other images fit
one file. The largest committed map is 1,501,960 bytes, below the 2 MB limit.
The patch is 8,818,693 bytes across 1,353 public paths.

## Physical coverage and preserved semantics

Only physical-root rows in `coverage.tsv` may be summed. Other views overlap.
All seven labels remain disjoint and conserved; strongly-code is separate from
compiled C, and the decision-57 terminal non-code class is not an unknown/hold.
All 568 former classification-export holds remain closed.

| container | bytes | proven code | library | strongly code | proven data | terminal non-code | padding/leftover | unknown |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| dungeon | 27,813,888 | 6,834,512 | 0 | 62,168 | 1,129,209 | 18,193,583 | 1,586,602 | 7,814 |
| main | 2,578,432 | 66,776 | 492 | 5,832 | 153,083 | 2,254,271 | 96,943 | 1,035 |
| ovmovie | 3,145,728 | 5,516 | 828 | 52 | 15,617 | 2,926,291 | 195,705 | 1,719 |
| slus | 524,288 | 180,900 | 43,872 | 204 | 44,484 | 245,401 | 9,211 | 216 |
| town | 16,889,856 | 816,676 | 132 | 19,149 | 1,971,984 | 7,594,483 | 6,483,590 | 3,842 |
| **total** | **50,952,192** | 7,904,380 | 45,324 | 87,405 | 3,314,377 | 31,214,029 | 8,372,051 | 14,626 |

The unioned leftover footprint remains 329,529 bytes,
with 17,936 code-evidence bytes excluded from game-code totals.
Development code retains its census identity. Data types or allocation bounds
are not inferred from opaque hashed slices. The symbol-array separator remains
opaque. Slice equality does not prove shared compiled TUs or runtime non-loading.
All accepted pass-2 descriptor, structure and stale-interval evidence is retained.

## Deliveries and validation

- `delivery.patch`: cumulative, text-only B13 patch; no files under `work/`, no
  binaries/retail payloads, no C/raw or production-link changes.
- `delivery_pass2.patch`: unchanged historical delivery.
- `REPORT.md`, `coverage.tsv`, `holds.tsv`, `unknown_spans.tsv`: current status and
  exact queue, including committed rule IDs for all remaining unknown intervals.
- `size_table.tsv`, `size_receipt.json`: exact byte reductions and per-file cap proof.
- `regeneration_proof.log`, `reproduction_receipt.json`: actual fresh-checkout,
  uncached public regeneration and empty-diff proof.
- `verification.json`: every view boundary equal to pass 2, raw census equality,
  original TU/indices/geometry unchanged, disc identities, 15,597
  distinct asset slice hashes and all 37 leftover slices checked independently.
- `tests_pass3.log`, `test_receipt.json`: 97 tests PASS, covering split/corrupt
  storage, profile overrides, exact tiling, original TU reconstruction, compact
  asset extraction, source/instruction drift, precision and non-propagating recovery.
- `gate.log`, `gate_receipt.json`, `touched_windows.txt`: retained four-worker
  95/95 MATCH gate. `gate_continuation_receipt.json` rehashes all 95 inputs current.
  No compilation pipeline input changed, so no repeat compilation was needed.
- `delivery_manifest.json`: actual B13 reconstruction plus every public path/hash;
  the other receipt/manifest files retain input identities and bounded census totals.

## Holds by reason

- census_unknown: 61
- four_copy_family_unproved: 1
- shipped_module_loading_open: 1
- static_deadness_only: 1
- twin_extent_and_shared_tu_evidence_missing: 2
- unreachability_evidence_missing: 1

Unknown-view counts overlap. Physical unknowns total 14,626 bytes, not the sum of
view holds. Terminal typing-pending non-code is deliberately absent from holds.
Remaining holds require evidence beyond this metadata correction; none is a
public-reproducibility or size hold.

## HOW TO CONTINUE

1. Apply **only cumulative `delivery.patch`** to B13. Do not apply pass 2 first.
   Lane reports/receipts are separate deliveries; public reproduction needs none.
2. Run the single documented `tools/census/regenerate.py` command above with the
   user disc and an empty output directory. `--check` must report `diff empty`.
3. Validate catalogue storage and the five physical roots:

   ```sh
   python3 tools/byte_map.py check --catalogue link \
     --physical-roots link/physical_roots.json --complete-containers
   PYTHONPATH=tools/tests python3 -m unittest tools.tests.test_byte_map \
     tools.tests.test_byte_map_format tools.tests.test_byte_map_rollout \
     tools.tests.test_linklist tools.tests.test_source_layout -q
   python3 -m unittest discover -s tools/census/tests -q
   ```

4. Work the 625 exact physical intervals in `unknown_spans.tsv` only with bounded
   matched readers or complete code/entry proofs. Preserve terminal non-code and
   strongly-code distinctions. Do not refresh stale hashes without new evidence.
5. For scene/NPC/shop unification, recover complete twin allocations, actual home
   TUs and compiled placement matches. LL4 owns existing non-home copies. A
   four-copy shop claim needs two additional complete placements. Additional
   stale-image claims need loader/selector reachability; runtime confirmation
   needs the cited CD-read observations. No directory/source moves are authorized.
6. Keep `config/link/` as build authority. Gate only future changed compilation
   inputs, with four workers and the exact affected windows. Preserve the existing
   gate receipts. Re-run public regeneration/validation after any metadata change.
