# r121w_types3c delivery

Base B16b: `5ffedc394eeaddb2fa86b72186ee2c0d4aa40970`. All work stayed in this lane/private root. **Every existing header is unchanged**, including all 24 assigned headers. New shared definitions are confined to `include/shared/types3c_types.h`. The patch contains only 21 C files and that one new header.

## Per-item status

**9 lanes delivered, 1 partial, 14 held.** `results.tsv` has one line for each of the 24 partition lanes. All feasible source-owned target views are delivered; the 33 definitions inside frozen module headers are explicit holds.

| Lane | Status | Definitions removed | Frozen-header definitions held |
|---|---|---:|---:|
| V2_008 | DELIVERED | 1 | 0 |
| V2_013 | DELIVERED | 3 | 0 |
| V2_014 | DELIVERED | 3 | 0 |
| V2_015 | DELIVERED | 4 | 0 |
| V2_017 | PARTIAL | 4 | 1 |
| V2_021 | DELIVERED | 3 | 0 |
| V2_023 | DELIVERED | 1 | 0 |
| V2_030 | DELIVERED | 3 | 0 |
| V2_036 | HOLD | 0 | 1 |
| V2_037 | HOLD | 0 | 1 |
| V2_038 | HOLD | 0 | 4 |
| V2_039 | HOLD | 0 | 1 |
| V2_040 | HOLD | 0 | 1 |
| V2_041 | HOLD | 0 | 1 |
| V2_042 | HOLD | 0 | 1 |
| V2_043 | HOLD | 0 | 1 |
| V2_044 | HOLD | 0 | 2 |
| V2_045 | HOLD | 0 | 2 |
| V2_046 | HOLD | 0 | 7 |
| V2_049 | HOLD | 0 | 2 |
| V2_050 | HOLD | 0 | 2 |
| V2_059 | HOLD | 0 | 6 |
| V2_060 | DELIVERED | 1 | 0 |
| V2_088 | DELIVERED | 7 | 0 |

## Source changes and types

The patch removes **30 aggregate definitions**: 16 exact-view centralizations, 13 unsigned-halfword scalar reductions, and one unused view. Twenty-nine have address-derived names. Six historical T05 target-file claims already use MovingPosition at B16b; their state is retained. V2_017 is partial because its additional signed-position view lives in the frozen module header.

The new header adds five PascalCase concepts, each commented: **CatalogObjectPayloadView, CatalogRecordDefaults, EffectObjectPayloadView, SignedPositionView, SpriteFlagsView**. MovingTile, ProjectileObject and DelayMotionZ reuse their existing shared definitions. Existing MovingPosition users remain shared. Catalog payload/default-word concepts are kept separate from effect payloads and coordinate vectors. Unknown fields retain offset-based names.

Code-token references to address-derived S types fall **728 -> 610** across changed pre-existing files. Pointer casts fall **608 -> 602**. The cast matcher counts pointer casts, including scalar/byte casts, outside comments, strings and aggregate declarations. `source_audit.py` defines the exact regex and `cast_counts.tsv` gives each file. Two local-promotion operations remove six repeated casts: the allocated effect pointer and all three catalog loop-scope entry declarations. Other already typed locals/parameters are renamed directly. A position parameter covered by a frozen `void *` prototype retains that signature and its exact view accesses.

T06 is reduced to `u16` where the original view is exactly one unsigned halfword. This preserves negative-prefix `[-1]` scaling and all byte offsets. It does not unify animation controls, lifecycle flags, model indices or the CD status word as an object. The model stream keeps its byte pointer because it mixes word/halfword reads and byte increments. The unused town T19 declaration has no code-token consumer and is removed without introducing a false position identity.

Every applied aggregate view retains its extent/alignment, field offsets, widths, signs, qualifiers and pointer representation. There are no layout-hiding casts, new masks or allocation widenings. `folds.json` records the 30 applied operations; `held_views.json` records the 33 blocked definitions. `selection_evidence.tsv` labels all 63 reviewed selections as applied or held and gives their concept/use basis.

## Validation

- **41 native members / 8 complete overlay TUs** match retail and genuine ASPSX 2.79, with 31056 resolved module bytes, zero masked bytes and no retail substitutions. Every member of each touched atomic owner is proved, including unchanged siblings. `module_results.json` binds the fingerprints and receipts.
- **6/6 town rows exact** at their registered recipes.
- **One completed final scoped gate**, `--workers 4 --all`, with **32 explicit active production windows: all MATCH**. Scope uses the production YAML parser and source-layout resolver. The production link-list loader agrees on source, home and extent for every selected entry. All **47/47 affected overlay placements** are covered by the window ranges. No superseded/certificate-only window is needed.
- **SLUS full-image SHA-1 MATCH**, 842 TUs, recipe identical to the pinned copy. All seven cd_command_state members and their complete physical owner match genuine ASPSX 2.79 and retail with zero masked relocations. Its scratch certificate passes the unchanged production validator. A first genuine attempt hit the DOS path limit; the short private-root `g/` scratch path passes without source/tool changes.
- **8 overlay scratch certificates VALID**, plus **1 SLUS scratch certificate VALID**. Overlay certificates consume only fresh receipts from the final gate transaction; there is no certificate fallback gate. Canonical ledger certificates are untouched. The existing overlay review identities are retained from their manifests; the SLUS scratch review does not publish a production placement review.
- **28 compiler layout assertions pass** at 2.7.2-cdk -O2 -G0: sizes, alignments, offsets and member widths for the five new types. The strict layout maps and emitted bytes preserve signs and pointer types.
- `header_guards.tsv` proves all 24 existing assigned headers equal their immutable before images. No existing shared header is edited. All 153 claim paths have before images and final guards. Unclaimed files and marked copies are untouched. The one reference-hash drift is untargeted `src/slus/w_8003E4FC.c`, already different in the private B16b export; it remains unchanged and passes full module/image checks.
- Existing asm, volatile, NON_MATCHING, pragma, goto and register constructs retain their code counts. No pins, assembly, volatile, pragmas, gotos, masks, recipes, names, storage or link-list changes are introduced.
- `delivery.patch` replays with **zero fuzz**, and every one of its 22 final file hashes equals `manifest.json`.

## Header-freeze correction

I initially treated the assigned module-header paths as writable. BRIEF's wording freezes every existing header, so those temporary edits and their dependent C changes were restored. The earlier wider gate attempt was stopped **after seven partial MATCH window records**; its one partial window receipt and all other preliminary evidence are discarded. The completed final gate covers the corrected source delivery. The earlier proposal is retained only in ignored private scratch and is not a delivery.

## Deliveries

Required: `delivery.patch`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, and this report. `DELIVERY_MANIFEST.tsv` lists the exported text artifacts and SHA-256 hashes. Supporting tables include applied/held selections, header guards, cast counts, placement scope, row/module/SLUS proof summaries, per-window hashes in `gate_results.tsv`, scratch certificate JSON, layout checks and patch replay checks. The patch contains no lane files, existing headers, canonical certificates, binaries or retail data. Every exported receipt is below 2 MB.

Scratch certificates are valid in this private proof view. Their binary proof directories remain private and are excluded from delivery. A text certificate is not a transferable native proof bundle: recreate its artifacts at the integration source hashes before publishing it there.

## Holds by reason

**EXISTING_HEADER_FROZEN — 33 definitions / 15 lanes**, including V2_017's remaining view. `holds.tsv` names each declaration, target and path. These cannot be removed or centralized while the existing module headers are frozen. The untouched T31 declaration is unused but still belongs to a frozen header. No aliases are added. If a later lane is authorized to edit module headers, it must also audit registered relink-copy consumers; the discarded wider proposal found 18 copies needing four compatibility aliases for the be1084 owner. This delivery changes neither those copies nor their header.

**BASELINE_OWNER_REVIEW_PENDING — SLUS production placement.** The evidence document still says reviewer pending. Its source migration, full image proof, all member/physical-owner proofs and scratch validator result are delivered. The orchestrator must supply production review identity and use its landing lock before publishing placement evidence.

There are no unresolved byte-match holds for the delivered source changes.

## HOW TO CONTINUE

1. Check `DELIVERY_MANIFEST.tsv` and every `manifest.json` before hash against the integration B16b inputs. Apply `delivery.patch` with zero fuzz and check each after hash. Assert all existing headers remain unchanged.
2. Recreate the native/window/SLUS proof artifacts at the delivered source hashes, using the explicit scope lists and scratch certificates. Keep certificate JSON and its binary proof lifecycle together; no canonical certificate is in the patch.
3. Have the serialized shared-type owner fold the five new concepts into the appropriate concept headers only when that header work is authorized. Preserve scalar T06 uses, catalog/effect separation and all original access widths/signs.
4. Resolve the existing-header freeze before continuing the 33 held definitions. Work each module atomically, recheck current home/copy ownership, preserve any needed LL4 compatibility, and prove all owner members and their complete window closure. Do not edit copies outside that lane's claims.
5. Resolve the SLUS production review and certify under the integration landing lock. Do not rerun `final_gate.py` or `run_finish.sh` in this delivered lane; its one completed final gate marker and receipts are immutable. Start a fresh guarded lane/root for additional work.
