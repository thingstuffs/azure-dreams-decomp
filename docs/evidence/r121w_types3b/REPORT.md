# r121w_types3b — REPORT

Base B16b: `5ffedc394eeaddb2fa86b72186ee2c0d4aa40970`. All work stayed in the lane/private root. No Git metadata is present; `manifest.json` and `scratch/before/` bind originals and final files. Thirty-three types2 reference hashes predate B16b source changes; the actual B16b bodies and current link-list homes were re-inspected.

## Per-item status

| Lane | Status | Changed C | Definitions centralized |
|---|---|---:|---:|
| V2_051 | COMPLETE | 8 | 10 |
| V2_085 | PARTIAL_BASELINE_GATE_METADATA | 36 | 48 |
| V2_086 | PARTIAL_BASELINE_GATE_METADATA | 36 | 43 |
| V2_087 | PARTIAL_BASELINE_GATE_METADATA | 35 | 40 |

All 138 claimed paths are reconciled in `file_results.tsv`. The type work is delivered for every lane. Two T05 files already use MovingPosition; remaining unchanged files support the atomic module. No relink/hand-copy markers were found. Existing headers, module declarations, recipes, configuration and ledgers remain unchanged.

## Deliveries

`delivery.patch` changes 115 claimed C files and adds only `include/shared/types3b_types.h`: 141 local aggregate definitions centralized, including 123 address-named definitions. It contains no lane files, binaries, retail data, tool changes or production certificates. Required results, holds, touched windows and gate log are present. `folds.tsv`, `selection_evidence.tsv`, `types_introduced.tsv`, `manifest.json` and the delivery manifest make the exact selections and hashes reviewable.

Address-named references across edited C fall from **2327 to 1824**, including declarations, and **1557 to 1300** outside definitions. Plain pointer casts fall from **2176 to 2106**; the aggregate-style subset falls from **1612 to 1541**. Function-pointer casts are excluded. Twenty-two accepted pointer/parameter-view promotions remove 69 aggregate casts. The collection counter becomes a typed `u16 *`, with its integer byte-address calculation retained.

The 27 introduced types are IntVector3, SignedPair16, SignedHeightView, SignedPositionView, UnsignedPositionXZView, SpriteFlagsView, SpriteTableView, ActorUnsignedFlagsView, ObjectPayloadView, ObjectStatusPrefix16, TownSearchWorkView, TownScoreCounterView, TownEventEntryValueView, TownPanelSelectionView, TownFormatKindView, TownResourceGroupView, TownIndexedValueEntry, TownNestedPayloadView, TownNestedRecordValueView, TownGridOutputView, TownDestinationYView, EffectPhaseTimer16, MinigameProgressPair16, TownEventArgumentPair16, FlagTestTargetPair16, TownSceneModeState and TownRewardValues. Each has a concept comment and exact view layout. The unused T31 declaration's removal does not type a global or establish activity counts as coordinates.

Existing MovingTile, SpriteLinkPrefixView, ActorStatusBytesView, ProjectileObject, TrailMotion, TrailHeightView and DelayMotionZ are reused. MovingPosition was already shared. Counter/prefix, reward/coordinate, state/timer/pair, event/motion, resource/height and destination-Y/delay-Z roles are separated. TownSearchWorkView preserves both live pointer and signed-half union paths. Negative prefixes retain their two-byte and 0x14 strides. No allocation extent, field sign/width/qualifier, pointer representation, array stride or by-value copy size changes.

## Validation

**107 ordinary home rows are exact**, and the complete **28-member dungeon_ovl_fa7000 TU matches all 16,008 bytes** against retail and genuine ASPSX 2.79, with zero masks and retail substitutions. Source hashes are retained in final row/module proofs. The retail 2.7.2-cdk compiler at `-O2 -G0` accepts **790 layout assertions** for sizes, alignments, offsets and widths; the parser separately compares typed leaves and union uses.

The corrected final scoped gate, workers 4 with 394 explicit active configs, produced **392 MATCH verdicts and then failed on two metadata exceptions**. A separate stock `plan_shas` final audit confirms all 392 recorded input digests remain current; this is an input audit, not another window gate. **The aggregate gate is not PASS.** `town_scene.overlay.yaml` and `town_scene_79.overlay.yaml` remain unproved. No aggregate PASS index was fabricated.

The atomic module's 20 required windows are all among the successful, current windows and are disjoint from both failures. Its scratch certificate passes the unchanged canonical `certificate_reason` validator. Each reused snapshot is checked against the current-input audit, its actual transaction and full artifact inventory; the validator independently replays module artifacts and compares window/module bytes with retail. The binary-free text certificate is valid in this private root; integrating elsewhere requires recreating its bound proof artifacts.

Executable numeric-literal sequences and counts of existing asm/volatile/NON_MATCHING/pragma/goto/register/pin constructs are unchanged. No new pins, assembly, volatile, pragmas, gotos or masks are introduced. The patch replays with zero fuzz and zero offsets and reproduces all 116 final file hashes. All 4257 guarded existing header/configuration/ledger inputs retain their hashes.

One initial scoped run was aborted after 60 MATCH windows for a use-site audit that split overly broad concept selections. Those receipts are quarantined under `scratch/aborted_gate/` and are not used. The corrected run failed as described above; neither attempt is an aggregate PASS.

## Holds by reason

- **Baseline gate metadata, two windows:** `row_eligibility` indexes `pins_left` on existing `{id, level: -1}` records. Forty such sentinel records exist, all outside this slice's source claims; their ledger modification time predates the lane. Missing fields must not be defaulted to zero or treated as a passing review. The gate tool and ledger are outside allowed write paths, so neither is changed. `metadata_blocker.json` and `GATE_HOLD.md` provide exact evidence and an unapplied conservative repair proposal.
- **Optional cast promotions, five variables:** town/func_808127A4, town/func_80816510, town/func_8081FF68, dungeon/func_80F87270 and dungeon/func_80F8ADE0 changed generated bytes under additional promotions. Those promotions were reverted; their shared-type extractions remain exact and delivered. See `promotion_holds.tsv`.
- **Integration lifecycle:** private binary artifacts are deliberately excluded. Canonical certificate publication and serialized folding of the new header belong to the integration/header owner.

## HOW TO CONTINUE

1. Hash-check the B16b originals using `manifest.json`, then apply `delivery.patch` with zero fuzz. Use B16b hashes rather than older reference hashes. Keep other lane source claims disjoint.
2. Have the tool/ledger owner resolve negative-level sentinel handling as described in `GATE_HOLD.md`. Regenerate truthful screening data or preserve unknown neighbour eligibility; do not invent zero pins. Rerun the two held configs and complete the full scoped current-input audit before claiming aggregate success. Renew every additional proof whose input digest changes under the repair.
3. Recreate native proof artifacts in the integration root and validate the atomic certificate at integrated source hashes. Renew neighbouring certificates whose window digests change while preserving existing review holds. No production certificate is edited by this patch.
4. The serialized header owner can fold the 27 concept definitions and maps into concept headers after reviewing the separated roles. Retain live union paths, signedness, pointer types, prefix strides and exact extents; verify the full reverse consumer closure after header changes.
5. Keep the five rejected optional promotions on the current exact C. Start a fresh lane for revisions; current scripts/before-images are inspection aids, not a turnkey rebase tool. Do not rerun a full gate in this delivered lane merely to encounter the same unowned metadata failure.
