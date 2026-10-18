# r121w_types1 implementation pilot

Base: `879caf70374330317439c1cd8acfd6e66c471758` (B12). The three highest ranked targets are implemented in **51 source files**, removing **75 local aggregate definitions**, including **74 address-named structs**. Two shared concept headers are new; MovingTile reuses its existing definition unchanged. All 51 home rows are byte-exact, and the single final scoped gate matched **81/81 windows**, covering **113 registered rows, including 62 link-list placements**.

**Per-item status**

| Item | Status | Header under include/shared/ | Files switched | Definitions removed |
|---|---|---|---:|---:|
| T01 MovingTile | Delivered in pilot | `dungeon_moving_views.h` | 34 | 39 |
| T02 SpriteLinkPrefixView | Delivered in pilot | `object_links.h` | 15 | 17 |
| T03 ActorStatusBytesView | Delivered in pilot | `actor_status.h` | 17 | 19 |

These file counts overlap. This is a scoped implementation pilot, not a claim that the complete top-three census population has migrated. The selected disjoint planning batches are B015, B027, B033 and B034: 84 historical source claims. Revalidation yields 51 current source files, 21 former duplicate-file claims covered through those homes, and 12 former claims held at another module-owned home. Per-view results are **75 DELIVERED, 36 COVERED_BY_HOME, 12 HOLD** in results.tsv.

**Types and layout**

- MovingTile: size 0x26, alignment 1; unsigned bytes at +0x24/+0x25. The existing `include/shared/dungeon_moving_views.h` is byte-for-byte unchanged. Uses feed tile lookup, map flags, facing and grid-coordinate operations.
- SpriteLinkPrefixView: size 0x14, alignment 4; `void *` at +0. `include/shared/object_links.h` preserves every `[-1]` expression and its 0x14 scaling. It is an interior link view, not an ObjectNodeHeader allocation.
- ActorStatusBytesView: size 0x7D, alignment 1; unsigned bytes at +0x74/+0x7C. `include/shared/actor_status.h` documents the observed queued-path coordinate uses. The planned type name is retained; the fields remain unk_74/unk_7C. The actor base is still indexed by the original byte offsets.

The new headers use built-in C types and have no includes, so their adoption does not import unrelated type definitions. No new casts, masks, pins, assembly, volatile accesses, NON_MATCHING, pragmas or gotos were introduced. No allocation extents were widened and no union alternatives were resolved.

The unchanged vendored production typefold engine performed 74 address-named folds through the reference prototype. The remaining already-named `Source` in dungeon/func_800AD984 was extracted with the same layout map and typed expression engine by named_view.py. Its only member spelling changes are field_24 -> unk_24 and field_25 -> unk_25. This narrow adapter does not change the production rewriter's eligibility rules.

**Proof and validation**

- All 51 current source candidates scored exact at their registered `2.7.2-cdk-G0` recipe: zero substitutions and indels. row_results.json and verify.log retain the measurements; named_verify.log records the named extraction.
- Twelve compiler assertions pass for extent, alignment, pointer width and member offsets at `2.7.2-cdk -O2 -G0`; inputs are layout_check.c and hashes/results are in layout_receipt.json.
- Each address-named extraction preserves all other non-preprocessor C tokens. Layout maps retain signedness, field width, pointer spelling and array shape. Source-use evidence is in source_audit.json.
- scope.py validates home/TU/offset/size correspondence through the production link-list loader and follows every registered source consumer, including consumers outside the historical batches. It binds 56 link-list inputs and includes every active overlapping production window. No shared home outside the claims was edited.
- Exactly one gate_all invocation ran with `--workers 4` and 81 explicit `--only-window` arguments. It used a fresh lane-local journal; all 81 windows were built. gate.log and gate_journal.jsonl contain the final verdicts. row_proofs.tsv maps every affected row to its successful window proofs. SLUS is outside this source closure.
- delivery.patch applies to lane-local copies of the B12 originals with `patch --fuzz=0`; all 53 resulting file hashes equal the retained private files. manifest.json binds changed sources, header closure, relevant controls, link lists and window input hashes.

The registry accounts for 44,820 home code bytes and 137,132 bytes across placements. Those are coverage figures, not removed machine code. The removed local declarations total 7,527 source bytes before include overhead.

**Deliveries**

Required: delivery.patch, results.tsv, holds.tsv, touched_windows.txt, gate.log and this REPORT.md. Supporting: manifest.json, summary.json, row_results.json, row_proofs.tsv, placement_scope.tsv, scope.json, source_audit.json, patch_check.log and the lane scripts. The patch contains only 51 C files and two concept headers; no binary, retail bytes, ledger changes or compiler/configuration changes. All exported receipts are below 2 MB. Build outputs remain private scratch data and are excluded from delivery.patch and the published receipt files.

**Holds by reason**

Twelve historical T03 local-view entries in 12 former files resolve in B12 to `src/dungeon/func_809C9B9C.c`. That home belongs to the 28-member `dungeon_resource03_slot0` native module; its current definitions are in `include/modules/dungeon_resource03_slot0.h` (for example R03_8017139C_S_8017139C_3). The home and header are outside these disjoint claims. Migrating them requires the module owner, a complete-TU check, its placement closure and certificate renewal. holds.tsv names every former local and its current home. No compiler, layout, byte-equality or gate failure remains in the retained pilot.

**HOW TO CONTINUE**

1. Review manifest.json and apply delivery.patch only when every non-null before_sha256 matches and both added headers are absent. This private root has no .git metadata, so the package uses source hashes and a standard unified patch. On an integrated tree, recompute the current row/placement and reverse include closure; current source names and ownership take precedence over the older reference hashes.
2. Assign `dungeon_resource03_slot0` atomically to clear the twelve held entries. Consolidate the module-header definitions once; do not recreate the removed placement files. Verify all 28 members plus dependent placements and renew that module's certificate under one owner.
3. Continue the remaining T01/T02/T03 candidates by refreshing the 175-lane partition with B12 source_layout and link-list homes. The old flat-file partition is no longer disjoint at the TU level. Use pilot.py and scope.py as the checked example; preserve the current refusal boundaries and add explicit semantic selections rather than automatically merging equal layouts.
4. For the next ranked concepts, freeze T04 SpriteAnimationTableView in shared/sprite_frame_state.h and reuse T05 MovingPosition only after confirming their call roots. Preserve T04's unsigned-char table pointer and T05's unsigned halves. Before T06, resolve the existing `UnsignedHalfView` name: dungeon_moving_views.h already defines that name as a 32-bit view, whereas the proposed T06 is 16-bit. Pick a meaning-specific name and recheck include collisions; do not hide the discrepancy with a cast.
5. Reproduction in a fresh copy of this lane/private root: unpack refs/delivery.tar.gz into reference/, run pilot.py stage, pilot.py verify, named_view.py, pilot.py apply, scope.py, then run_gate.sh once. After its success run finalize.py and write_report.py. The current before/after and manifests are immutable receipts; use a fresh lane to rerun staging. For only applying the reviewed result, use the hash-guarded patch rather than regenerating the census.
