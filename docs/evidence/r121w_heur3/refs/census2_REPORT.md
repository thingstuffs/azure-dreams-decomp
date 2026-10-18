# r121_census2 — CONTINUE1 cumulative delivery

Base: bf7d314669cac0c5f956d276a9604c7458624810 (B6). All work stays in this lane and its private root. The external toolchain and environment links are used read-only. This patch supersedes pass 1 and remains cumulative. Non-code is never decompiled.

All **50,952,192 bytes** carry exactly one evidenced label. Unresolved bytes: **51,991 → 14,386** in this continuation; the owner goal of zero remains incomplete. Unsupported pieces retain explicit holds.

## Per-item status

| item | status | result |
|---|---|---|
| A / 0 neighbour policy | delivered | A single simultaneous neighbour pass resolves 37,429 B / 4,596 slivers. Only pieces shorter than 16 B with non-code on both sides and no overlapping aligned jr ra qualify. Same labels retain their class; differing labels become typing pending. Precision is recomputed each run; each output class is gated separately at >=0.999. |
| A / 3 code-adjacent pieces | audited; bounded holds | 65 short pieces / 456 B audited; 176 B code-proven, 46 pieces / 280 B remain. Strict complete-body replays and an independently validated complete masked-body detector resolve supported prefixes; the unreferenced jr-ra/nop candidate stays held. The detailed audit distinguishes load-before-prologue prefixes, data edges and an epilogue. No existing row extent grows. |
| B / 1 no-base retry | complete | 551 original no-base spans / 13,414 B retried against rowbases, 201 admitted loader extents, revalidated bank grids, twin stride, bracketing and authenticated module headers. 40 placed; 511 retain no-base holds. Placement itself adds no code or data-type claim. |
| C / 2 placed handoffs | delivered with holds | 14 C rows / 800 B delivered (5 earlier handoffs covered); 45 placed code handoffs remain, with individual donor/entry reasons. 17 earlier placement/entry holds remain. New C requires genuine m2c raw, ELF relocation replay and strict production-window MATCH. |
| original 2 split audit | delivered | 380 effective-view corrections, including pass 1's 175 splits + 195 exclusions, all append-only. Admitted code over erroneous audit data views is zero. Data remnants retain audit status. |
| original 3 extents | complete context checks | 257 neighbouring C bodies examined: 255 exact in isolation, 2 exact through registered complete TUs with retail + genuine ASPSX 2.79 MATCH. Dungeon's 884-byte member contains a 4-byte owned head and 880-byte function; OVMOVIE's full TU emits its registered 304 bytes. No extent expanded. |
| original 4 / 6 data and SLUS | partial typing delivered | Checked bounded matched-C reads, TOWN resource-table fields and SLUS glyph/flag windows retained. Untyped non-code remains terminal typing pending. |
| original 5 entropy / CD map | partial placement delivered | 201/745 loader extents admitted. 1,359 duplicate sector groups / 4,286 occurrences retained as evidence; no duplicate is called leftover. |

## Label table before / after

The first column is the unchanged B6 reference-policy snapshot. Pass 1 already includes owner decision 57. The final column includes this continuation's validated neighbour pass, code-prefix evidence and strict C deliveries.

| label | before B6 policy | pass 1 | after CONTINUE1 |
|---|---:|---:|---:|
| 1 proven_code | 7,884,096 | 7,884,096 | 7,884,872 |
| 2 library_code | 45,216 | 45,324 | 45,324 |
| 3 strongly_code | 92,078 | 107,497 | 106,897 |
| 4 proven_data | 3,313,612 | 3,317,931 | 3,318,453 |
| 4 noncode_typing_pending | 0 | 31,174,668 | 31,211,087 |
| 5 padding_leftover | 8,371,531 | 8,370,685 | 8,371,173 |
| 6 unknown | 31,245,659 | 51,991 | 14,386 |

Total denominator: 50,952,192 B. Of the 800 newly registered C bytes, 24 were already label-1 instances, so label 1 grows by 776 B. Partial instances remain label 1. T4/T5 remain visible label-3 shape-only evidence (15,419 B); all code tiers use exact-count precision gates. Per-container tables and detector counts: census_after.md / census_after.json.

## Neighbour validation

Validation uses reproducible independent random 4/8/12-byte holes inside each original C row and typed-data interval, every C/non-code class boundary, whole short C rows, padding and terminal non-code interiors. Neighbour witnesses are the immediate surviving bytes. New slivers never become witnesses for another admission. Any aligned jr ra overlapping a hole blocks it. The sample classes are reported separately; no simulated C bytes are silently counted as data.

| simulated class | holes | tested bytes | admitted bytes | proven-C bytes mislabelled |
|---|---:|---:|---:|---:|
| C_data_border | 19,257 | 183,400 | 0 | 0 |
| noncode_class_border | 1,011,633 | 9,634,600 | 9,611,168 | 0 |
| padding_interior | 41,379 | 330,608 | 330,608 | 0 |
| pending_noncode_interior | 78,269 | 614,964 | 614,964 | 0 |
| proven_C_interior | 95,328 | 759,408 | 0 | 0 |
| typed_data_interior | 38,431 | 298,356 | 298,236 | 0 |
| whole_short_C | 402 | 3,852 | 0 | 0 |

Proven-C bytes mislabelled: 0. Per-output precision: 4 noncode_typing_pending 1.000000000, 4 proven_data 1.000000000, 5 padding_leftover 1.000000000. Code-only prefixes that overlap existing return rows have separate strict full-body replay evidence in delivery/replayed_prefixes.jsonl. No row extent grows. The per-container confusion counts and exact seed are in delivery/neighbour_validation.json. The rule is an evidence classification, not an inferred allocation or format type.

## Complete masked-body prefixes

The existing T1 mask can identify a complete compiled C body even when literal member offsets differ. A separate detector looks back 4/8/12 bytes before a framed ABI-valid suffix, requires a complete masked donor body of at least 48 bytes, and restricts the prefix to caller-register writes with no SP, K0/K1, branch, call or COP0 use. It changes only remaining unknown bytes and requires both its own precision gate and the ordinary T1 gate. Typed data and established labels retain precedence.

Cross-fold proven-C true positives: 4,976 B; structured-data false positives: 0 B; entropy false positives: 0 B; precision: 1.0. This admits 48 B across 6 prefixes as label 3. The four full C candidates with ordinary member-offset differences still fail actual ELF relocation replay and remain C-transfer holds. This detector does not register C or extend existing rows. Full counts and applied intervals: delivery/masked_prefix_validation.json.

## Deliveries and verification

- delivery.patch and delivery_manifest.json: cumulative changes relative to B6. Every changed ledger keeps its exact original byte prefix. No absolute home paths and no large span dumps enter the patch.
- census.py, run_census.sh, census_after.json/.md: reproducible root-dot census, per-run code/neighbor precision and checked reader hashes. spans/ is ignored and holds large detector caches, disassembly and scratch builds.
- delivery/neighbour_validation.json, neighbour_summary.json, short_code_audit.json: validation, admitted byte counts and explicit code-adjacent checks.
- masked_prefix_probe.py and delivery/masked_prefix_validation.json: independent cross-fold precision, negative counts and the exact label-3 prefix intervals; masked_prefix_fix.py records append-only audit-view cuts.
- delivery/placement_retry.json: all 551 placement attempts, candidates, unique witnesses and refusals. Six bank-grid runs are revalidated against every intersecting proven region; module headers require independent agreeing regions and no contradictory region.
- delivery/anchored_donor_audit.json: a final bounded full-body search covers remaining short gaps and placed handoffs across detector boundaries; only leads passing actual ELF replay are admitted.
- delivery/production_gate_receipt.json and negative_control.json: exact C manifests for every covering window, unchanged raw tool output hashes, zero source debt, module graph checks, and rejection of a one-word wrong-pointer control.
- Genuine raw first passes: 12 exact and 2 nonmatching raw measurements, all retained honestly in baseline records. All 14 clean C bodies are exact; the raw tool output is unchanged behind its compatibility preamble.
- handoff_code.tsv and delivery/twin_delivery.json: per-handoff donor review and strict C proof receipts when delivered; remaining work has a stated reason.
- delivery/split_fixups.json, typed_*.jsonl, cd_bank_map.json, sdk_thunks.json, entropy_duplicates.json, slus_object_relocations.json, slus_glyph_receipt.json and town_data_receipt.json retain pass 1 evidence. Nine identified BIOS thunks remain library code under decision 55.
- tools/gate/jsonl_revisions.py is shared by tools/common.py and cached gate readers. Explicit revisions are resolved before overlap and exported-roster validation; unrelated reruns and refusal checks retain their semantics. The native-module fingerprint also binds the helper.
- delivery/extent_context_retry.json: both former isolated proof holds close through current complete-TU retail + genuine ASPSX proofs. The original isolated measurements remain unchanged as historical evidence.
- verification.json: complete disjoint byte coverage, append-only ledger checks, binary input hashes, tests and patch reconstruction. The patch is applied in an ignored private check tree and every reconstructed delivered file is compared byte-for-byte.
- delivery/reproduction_receipt.json: reproduce.py requires two successful final root-dot reruns with byte-identical JSON and Markdown. Twenty-one focused tests and 108 scoped-fingerprint tests pass; all 22 covering C windows and both complete-TU extent proofs are MATCH.

## Holds

Final unresolved stops (span count / bytes): piece <16 B: 46 / 280; no base: 511 / 12,668; placed; no proven complete function start or bounded data reader: 57 / 1,438. next.tsv is the exact final byte list with placement and the next evidence needed. A supported base alone cannot turn a data sliver into code or establish a bounded reader.

Existing native-module certificates outside these fresh receipts need refresh after the shared gate reader/tool hashes change. This patch preserves their historical certificate files.

Loader maps remain conditional where runtime occurrence was not proved. Duplicates do not prove leftover status. No unrelated source or row extent is changed to remove a hold.

## HOW TO CONTINUE

1. Apply the cumulative delivery.patch at B6. Refresh the generated view with `bash tools/build/mk_ovl_root.sh`, then run `python3 tools/row_db.py export build_ovl` and `python3 tools/row_db.py check`. Refresh affected native-module certificates after the gate reader/tool identity change.
2. Run `bash work/native_lane/r121_census2/run_census.sh` from the private root. It recomputes code and neighbour validation, verifies read proposals, and writes large spans only under ignored spans/.
3. Take remaining handoff_code.tsv rows marked placed code. Require a complete referenced entry and a full matched donor whose every differing word is a real ELF relocation. Preserve a genuine m2c first pass and pass every covering production window before registering C. Individual reasons identify missing gates.
4. For next.tsv placed residuals, prove a complete entry or bounded matched-C reader. For no-base holds, require new independent placement evidence. Code-adjacent short pieces need the exact prefix/extent or return-entry proof recorded in delivery/short_code_audit.json.
5. Re-emit the cumulative patch after each delivery with `python3 work/native_lane/r121_census2/deliver.py`; use `check_patch.py` to reconstruct and compare it. To reproduce first passes, clone matt-kempster/m2c into spans/m2c at revision 708d2d2; spimdisasm uses the existing environment. Detector caches can be regenerated from the delivered scripts. Keep the private spans/baseline snapshots to re-emit this cumulative patch; a fresh checkout must restore its B6 originals first.
