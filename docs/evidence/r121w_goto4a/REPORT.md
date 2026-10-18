# r121w_goto4a — continuation, pass 2

**29 gotos removed cumulatively: 188 → 159. Pass 2 removes five more: 164 → 159.** Eight files are goto-free, three retain exact partial reductions, and 69 are held. The patch contains 11 source homes and source/gate ledger evidence against B13 `ddc07bc5949684593cdc45a67e378a1f18324318`. The original patch remains byte-for-byte in `delivery_pass1.patch`.

All 75 pass 1 held/partial files received at least three new admissible, scored shapes. There are **237 distinct admissible pass 2 shapes** (242 measurements including five rejected generator outputs). `pass2_coverage_audit.json` verifies the minimum, current candidate hashes, and distinctness from pass 1 and one another after ignoring comments and whitespace. Five malformed, semantically invalid, or ineffective generator outputs are retained as rejected evidence and excluded from the quota, best candidates, and deliveries.

All 11 frozen installed sources remeasure exact at their existing recipes. The single final scoped overlay gate has **4/4 windows MATCH**, with four workers and a final current-input audit. The full SLUS retail SHA-1 gate also MATCHes with four build jobs; the generated recipe remains identical to the pinned recipe. Patch reconstruction passes for all 16 source/ledger targets. No new rows, coverage bytes, shared headers, compiler options, or assembler options.

## Per-item status

`results.tsv` has all 80 files, cumulative shapes, and every individual pass 2 score (including status, exactness, substitutions/indels where available, total, and evidence path). `holds.tsv` has the 72 unresolved files, including the three partial homes. The pass 2 count below excludes the five rejected generator outputs.

| Home | B13 | Pass 1 | Final | Status | New scored shapes |
|---|---:|---:|---:|---|---:|
| `src/slus/w_8003E4FC.c` | 28 | 14 | 14 | partial | 3 |
| `src/slus/w_8003E758.c` | 13 | 13 | 13 | held | 3 |
| `src/town/func_80956260.c` | 7 | 7 | 7 | held | 3 |
| `src/town/func_8081B4A4.c` | 6 | 6 | 6 | held | 3 |
| `src/main/func_8001A2B0.c` | 6 | 6 | 6 | held | 5 |
| `src/main/func_8000E298.c` | 6 | 6 | 6 | held | 3 |
| `src/main/func_8000E0F0.c` | 6 | 6 | 6 | held | 3 |
| `src/town/func_8095563C.c` | 5 | 5 | 5 | held | 3 |
| `src/slus/w_800595C0.c` | 5 | 1 | 1 | partial | 3 |
| `src/slus/w_80048734.c` | 5 | 5 | 5 | held | 3 |
| `src/slus/w_8005552C.c` | 4 | 4 | 4 | held | 3 |
| `src/slus/w_80041588.c` | 4 | 3 | 2 | partial | 10 |
| `src/main/func_8001A0F0.c` | 4 | 4 | 4 | held | 3 |
| `src/town/func_809548E4.c` | 3 | 3 | 3 | held | 3 |
| `src/town/func_808110CC.c` | 3 | 3 | 3 | held | 3 |
| `src/town/func_8046BD98.c` | 3 | 3 | 3 | held | 3 |
| `src/town/func_800BB530.c` | 3 | 3 | 3 | held | 3 |
| `src/slus/w_80059F8C.c` | 3 | 3 | 3 | held | 3 |
| `src/slus/w_80059E94.c` | 3 | 3 | 3 | held | 3 |
| `src/slus/w_80041344.c` | 3 | 3 | 3 | held | 3 |
| `src/town/func_8081C14C.c` | 2 | 2 | 2 | held | 3 |
| `src/town/func_80469200.c` | 2 | 2 | 2 | held | 3 |
| `src/town/func_800CF608.c` | 2 | 2 | 0 | exact | 3 |
| `src/town/func_800C4508.c` | 2 | 2 | 2 | held | 3 |
| `src/town/func_800BB3A0.c` | 2 | 2 | 2 | held | 3 |
| `src/town/func_800A6420.c` | 2 | 2 | 2 | held | 3 |
| `src/slus/w_800599B0.c` | 2 | 2 | 2 | held | 3 |
| `src/slus/konami_runtime_w_80038AB8.c` | 2 | 2 | 2 | held | 3 |
| `src/town/func_8096AE44.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_808B3620.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_80878A78.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_8081E9A4.c` | 1 | 0 | 0 | exact | 0 |
| `src/town/func_8081E410.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_80818F60.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_80818C8C.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_808151F8.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_808146C8.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_80811C54.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_806D85A0.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_805D3AC8.c` | 1 | 0 | 0 | exact | 0 |
| `src/town/func_80476DBC.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_8046986C.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_8032EF6C.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_8032C6E0.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800C6228.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800C3688.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800BC0D0.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800BB990.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800B93B0.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800B8244.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800B3E58.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800AF9D8.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800A265C.c` | 1 | 1 | 1 | held | 3 |
| `src/town/func_800A201C.c` | 1 | 1 | 1 | held | 6 |
| `src/town/func_8008EFF8.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8005F90C.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8005BAB0.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8005B16C.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8005B070.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_800565D8.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_80054A7C.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_80054104.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8004FC98.c` | 1 | 0 | 0 | exact | 0 |
| `src/slus/w_8004E8D8.c` | 1 | 1 | 0 | exact | 3 |
| `src/slus/w_8004B08C.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8004AFE8.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8004713C.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_80046C20.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_80044D24.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_80041E70.c` | 1 | 0 | 0 | exact | 0 |
| `src/slus/w_800407C0.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/w_8003F368.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/konami_runtime_w_8003B714.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/konami_runtime_w_80039884.c` | 1 | 1 | 0 | exact | 3 |
| `src/slus/konami_runtime_w_800387D0.c` | 1 | 1 | 1 | held | 3 |
| `src/slus/konami_runtime_w_80033D54.c` | 1 | 1 | 1 | held | 3 |
| `src/main/func_80021848.c` | 1 | 1 | 1 | held | 3 |
| `src/main/func_8001BA1C.c` | 1 | 1 | 1 | held | 3 |
| `src/main/func_8001B508.c` | 1 | 0 | 0 | exact | 0 |
| `src/main/func_8000FBE8.c` | 1 | 1 | 1 | held | 3 |

## Pass 2 deliveries and mechanism

`town/func_800CF608`: **2 → 0**. Copy the small timer/phase advance into the three real switch arms and use `sequence->unk_6A.u++` after each timer reset. The earlier duplicated-tail spelling read the old phase into a shared temporary; the direct field increment preserves the retail scheduling and register roles. The real decrement/early-return behavior and case 3 cycle count remain intact.

`slus/konami_runtime_w_80039884`: **1 → 0**. Return the actual predicate directly: a nonzero state flag or clear global button bits. The original semantic `0x60` test is retained. No added normalization mask or cast. The complete standalone object matches.

`slus/w_8004E8D8`: **1 → 0**. Retain the nonempty-string guard and whitespace constants, rotate the character repetition to a real `while`, and break when a content byte sets the existing result. Both the byte/constant register roles and the full object match.

`slus/w_80041588`: **4 → 3 → 2**. Preserve the pass 1 real switch break. Give case 1 its own serialized `source_offset` and duplicate the small upload/DrawSync tail into that real arm. This initially left two substitutions in **case 5**, rather than in case 1: the second source-word load used `v0` instead of `a0`. Reading the second relative offset into `src_addr`, completing the pointer in the existing `tile_src`, and then assigning the upload address preserves retail’s `a0` carrier and operand order. The full jump-table-owning physical object, including data and relocations, now matches. The `masked_tile` and `convert_flags` joins remain. The frozen formatted source rechecks exact.

## Preserved pass 1 deliveries

The cumulative patch retains the 14-goto CD-dispatch reduction (`w_8003E4FC`), four event-switch breaks (`w_800595C0`), stable-base indexed slot loops (`w_8004FC98`, `w_80041E70`), the indexed town-record loop (`func_805D3AC8`), the real inner grid loop (`func_8081E9A4`), and the main word scan (`func_8001B508`). No pass 1 per-file goto reduction regressed. Seven of its eight installed source hashes remain unchanged; the upload source receives the additional exact reduction above. The source and ledger patch is regenerated from the saved B13 preimages.

## Holds by reason

| Best retained reason | Unresolved files |
|---|---:|
| addressing | 5 |
| block-order | 2 |
| broad | 3 |
| build-fail | 1 |
| code-motion | 1 |
| computed transfer; address temporary assembles but tail-call/return layout differs | 1 |
| const-remat | 4 |
| delay-slot | 1 |
| exact partial; remaining object-diff | 3 |
| hold-set | 8 |
| length-drift | 4 |
| li-expansion | 5 |
| object-diff | 25 |
| polarity | 5 |
| reg-rename | 2 |
| slot-rotation | 2 |

These are file counts, not coverage. Combined: 28 complete-object misses (including the three partials), 42 instruction/register/layout misses, one jump-table/build hold, and one computed-transfer hold. All misses remain outside the patch. No compiler-version limitation is asserted.

The menu transfer (`main/func_80021848`) has new evidence: `p2_menu_address` assembles at the existing recipe, unlike the direct symbolic call forms, but remains **2 substitutions / 7 indels**. Its address temporary does not preserve the retail transfer/return layout. The old blanket “natural indirect call fails assembly” reason is superseded.

Other retained improvements include the CD worker’s copied failure tails (532 differing disassembly lines), direct event-switch index (29), allocator copied returns (37), serialized offset in the smaller upload worker (23), record scan terminal return (5 substitutions / 4 indels), positive pitch guard inversion (10), image-block for-step spelling (38), and linear decoder arm inversion (53). See the individual best candidates and scores in `holds.tsv`; these are real misses.

## Measurement and gate scope

Overlay candidate scores use the unchanged retail scorer and local-table checks. Substitutions/indels are its aligned metrics. SLUS candidate exactness requires SHA-256 identity of every complete physical ELF object against paired B13 objects compiled in this lane at the same recipes and headers, including local data and relocations. Its nonexact `total` counts differing disassembly lines and is not comparable with overlay totals; a final image gate separately establishes linked retail identity. `measurements.tsv` is the cumulative individual-score index.

Touched overlay windows: `main_boot`, `town_deep_t8b_79cdc8`, `town_scene`, `town_scene_55`. These cover the four changed overlay homes. The new sequence home adds `town_scene` to the pass 1 closure. No changed overlay home has a link-list or native-module sibling placement dependency. SLUS physical/module and connected code/code2 closure is recorded in `module_scope.json`; standalone changed units are also compiled and the complete image is gated. Ownership, names, recipes, partition definitions, and raw baselines stay at B13.

The exact source facts refresh `ledger/reverify.jsonl` and `ledger/goto_lanes.jsonl`; fresh window facts refresh `ledger/gate.jsonl`, and the fresh image fact appends to `ledger/gate_slus.jsonl`. `ledger/evidence/r121w_goto4a.json` binds final source hashes, scope, scores, gate facts, pass 1 patch hash, and the continuation quota audit. The connected `list_cursor_e0` certificate was already stale at B13; it is not renewed or used as proof.

The gate preparation was suspended before the SLUS/overlay validation stages to include the final exact upload result. Its sources and physical-unit measurements were refreshed before continuing. Only one scoped overlay gate invocation is made in pass 2. All final input hashes are checked again afterward.

## Deliveries

Required: `delivery.patch` (cumulative source + ledger versus B13), `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, and this `REPORT.md`. Original records are preserved in `delivery_pass1.patch`, `results_pass1.tsv`, and `REPORT_pass1.md`. Supporting portable files: `measurements.tsv`, `pass2_coverage_audit.json`, `pass2_shapes.json`, `pass2_rejected.json`, `final_sources.json`, `scope.json`, `module_scope.json`, `source_audit.json`, `preimage_manifest.json`, `patch_validation.json`, and `delivery_manifest.json`.

No lane directory, object, executable, retail slice, or binary proof payload enters the patch. Internal compiler/gate products stay in ignored private directories; large receipt inventories are represented by compact counts/sizes and manifest SHA-256. Delivered files contain no absolute host paths and are below 2 MB. No Git commits or ref moves.

## HOW TO CONTINUE

1. Apply `delivery.patch` only to its manifest-bound B13 preimages; do not stack it onto `delivery_pass1.patch`. Reconstruct and check every final hash in `preimage_manifest.json`. Keep all 11 exact installed homes and zero new-coverage accounting.
2. Continue the upload worker from the **installed two-goto version**, or `candidates/p2_upload_source_pointer_stage/src/slus/w_80041588.c`. Its case 1 private offset and case 5 address/pointer stages must stay together. The previous one-word commuted-add candidate is now solved. Remaining work is the semantic flag conversion and masked-upload joins; the old goto-free `tile_tails` candidate remains a 105-line object miss and needs rebasing on the new exact partial.
3. CD dispatch: `p2_cd_last_return` reduces 14 to 13 gotos at a six-line complete-object miss; retain it as a probe. The full supported-case switch and if-chain also miss. Preserve all pass 1 call tails/ignored-event returns and avoid invented cases. The CD queue worker’s `p2_queue_failed_tails` improves the recorded complete-object miss to 532 lines but retains unrelated control joins.
4. The compact event decoder retains its default/range join. `p2_event_direct_index` is fully goto-free at 29 differing disassembly lines; keep the four installed breaks and reproduce the original table/range layout before accepting it. The smaller upload worker has a separate 23-line candidate at `p2_upload_serial_offset`; the large-worker solution is not automatically additive there.
5. For small overlay holds, keep the selection processor’s pass 1 two-substitution constant-rematerialization probe and `func_8032EF6C`’s new `p2_record_return_exit` (5 substitutions / 4 indels). The renderer’s persistent game-state and cell-table roles still swap `s3`/`s2` at eight substitutions; earlier cell-table loading, final global rematerialization, and independent rectangle-store order did not close it. The menu address-temporary probe now builds, so inspect its real transfer layout rather than treating assembly failure as universal.
6. For every other hold, start from its `best_candidate` in `holds.tsv`, inspect the individual pass 2 scores/notes in `results.tsv` and `pass2_shapes.json`, and choose a new control/lifetime shape beyond the at-least-three already audited. Failed local-table candidates remain failures; do not force table targets, ABI behavior, masks, casts, or flags. No wall/park verdict has been established.
7. After future source changes, remeasure the exact homes in their complete physical/link-list closure, refresh the exported view, and run one final scoped gate with `--workers 4` and `--only-window` for each touched window. Any SLUS source change also needs complete physical-unit identity and the retail image gate. Keep binaries and retail data out of the delivery.
