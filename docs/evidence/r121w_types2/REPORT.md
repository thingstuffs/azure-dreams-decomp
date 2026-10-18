# r121w_types2 — REPORT

Base B13 private snapshot: `ddc07bc5949684593cdc45a67e378a1f18324318`. The root has no Git metadata; `manifest.json` binds each original and final file. All work stayed in the lane and private root.

## Per-item status

| Item | Status | Evidence |
|---|---|---|
| Refreshed 175-lane partition | Delivered: 88 disjoint lanes, 1999 write files | partition_v2.tsv; actual module include bodies and link-list homes |
| Twelve types1 holds | Cleared atomically | dungeon_resource03_slot0: all 28 members, dependent placements, renewed certificate |
| T04 SpriteAnimationTableView | Partial population: eligible homes migrated; 6 marked copy files excluded | 27 definitions centralized; all 253 historical entries reconciled |
| T05 MovingPosition | Partial population: eligible homes migrated; 117 marked copy files excluded | 217 definitions centralized; all 554 historical entries reconciled, including already shared module uses |
| Additional assigned module cleanup | Delivered | T01 1, T02 1, T03 1 definitions centralized |

## Types and source changes

The patch removes **247 aggregate definitions**, including **239 address-named definitions**, from 210 C/header files. T04 adds one exact view to the existing `include/shared/sprite_frame_state.h`; T05 and the module's T01/T02/T03 reuse existing shared definitions. No allocation extent, member width/sign, qualifier, array stride or pointer representation changes.

T04 remains size 0x30/alignment 4: signed byte +04, unsigned halfword +14, unsigned bytes +24/+25, and **unsigned char pointer** +2C. The existing SpriteFrameState allocation declaration is unchanged. MovingPosition remains size 0xC/alignment 2 with unsigned halves at +02/+06/+0A. ActorStatusBytesView preserves the queued-path byte indexing and 0x7D extent. The link-prefix view retains its 0x14 negative-index stride.

There are **50 variable/parameter promotions**. Aggregate view casts fall from **5196 to 4985** (211 removed). Selected concept casts fall from 774 to 563. `cast_counts.tsv` records both counts for every changed C/header file. Total counts include other aggregate casts that remain in each file. Remaining casts represent mixed-view bases, byte offsets, prefixes and payload conversions; there is no cast that changes a field's type to make a layout fit. Typed local declarations already present are migrated directly. Module prototypes and entry pointer declarations are synchronized with typed parameters.

The production typefold engine is unchanged. A narrow named extraction adapter excludes unrelated aggregate/prototype scopes from its shadow screen and resolves other typed member bases, so ActorSprite's `flags` cannot rename ActionState/EntityRec fields. It also handles the explicit named T05 selections. Every selection still requires equal extent/alignment and identical typed leaves at matching offsets. `folds.json` records the maps. Call-root selections are explicit views; they do not merge sprite and actor allocations.

One legacy typedef alias maps the old R03 sprite-view spelling directly to SpriteAnimationTableView for two still-registered relink copies. Their C files remain untouched and have no partition write claims. Production module members use the shared concept directly. The alias preserves no duplicate struct definition and requires no cast.

## Validation

- **598 ordinary home rows exact**, and **27 complete native TUs exact** against retail and genuine ASPSX. Together these cover 1154 home rows and 2447 placements. There are also 116 supplemental original-copy checks. All 123 restored copy files were reverified. `row_results.json`, `verify.log`, `placement_scope.tsv` and `row_proofs.tsv` bind the evidence.
- **One completed final gate_all invocation**, workers 4, with 852 explicit active production windows: **all MATCH**. Two early runs were stopped for the complete copy audit and production-range selection checks; all their partial receipts are discarded. Scope uses the production YAML parser, including decimal offsets. Fresh final snapshots are reused for **117 renewed native certificates**. One superseded seed window is still required by the canonical certificate contract and is excluded by gate_all's active-window filter; the normal certifier separately proves that 1 legacy window. It is named in certificate_only_windows.txt. No other missing-receipt fallback is allowed.
- **23 compiler layout assertions pass** at 2.7.2-cdk -O2 -G0. The unchanged production pointer widths and all selected offsets are checked. Layout source and generated assembly remain private scratch; their hashes are in layout_receipt.json.
- The reverse include scan checks 10,654 active C inputs and all reachable quoted headers. Current source_layout and the production link-list loader agree on home/source/offset/size. Flat hand copies replaced by native_candidates bodies are excluded. No relink copies are recreated.
- All changed C retains its numeric literal sequence outside aggregate declarations and its counts of assembly/volatile/NON_MATCHING/goto constructs. No pins, assembly, volatile, pragmas, gotos, masks, recipe changes, or retail substitutions are introduced. Recipes, names and source-layout ledgers are unchanged.
- delivery.patch applies to private B13 originals with **zero fuzz**, and every result matches the final file hash.

## Deliveries

Required: delivery.patch, partition_v2.tsv, results.tsv, holds.tsv, touched_windows.txt, gate.log and REPORT.md. DELIVERY_MANIFEST.tsv enumerates the exported text artifacts and their hashes. The patch contains C/headers and renewed certificate JSON only. No binaries or retail data are delivered. Every exported receipt is below 2 MB.

Native proof binaries remain in the private build view. Certificates are valid in that view; integrating the text patch elsewhere requires recreating its proof artifacts at the bound source hashes. The binary-free package is not a transferable native proof bundle. The orchestrator can reproduce these artifacts with the supplied source/window/certificate lists before publishing certificates there.

## Holds by reason

The twelve prior module-owner holds are CLEARED in results.tsv. **123 marked copy files are excluded under RELINK_COPY_NON_HOME_LL4_DELETES** (6 T04, 117 T05). The registry still treats these as own-file rows, but their source markers identify relink copies. Both marker forms are checked, including readable donor aliases and transitive donor chains. Their edits were restored to B13 and reverified; partition_v2 routes their old claims to the ultimate donors. LL4 must delete/rebind the copies. **Alias retirement also awaits LL4:** func_80FBD340 and func_80FCF340 remain registered relink copies and still need one R03 type-name shim. holds.tsv records those two consumers separately. Initial prototype/include failures were fixed by synchronizing actual module declarations. This is not a complete migration of all forty ranked concepts, nor of the remaining T01/T02/T03 census outside the assigned module.

**8 neighbouring modules were already uncertified with pending membership/type/ownership reviews in B13.** Their sources and review state are untouched. Their windows are byte-proven by the gate, but this lane does not invent owner reviews or issue first certificates for them. certificate_holds.tsv names those baseline holds; all 117 eligible existing certificates are renewed.

## HOW TO CONTINUE

1. Hash-check manifest.json against B13, apply delivery.patch with zero fuzz, and recreate/validate native proof artifacts in the integration root. Keep certificate JSON and its binary proof lifecycle together; no binary data is embedded in this delivery.
2. Dispatch 3–4 lanes from partition_v2.tsv after checking current_sha256 and live ownership. Each file appears once. Native modules include their actual wrapper/C bodies and private headers atomically. Read dependencies and gate windows may overlap. Concept headers remain frozen under one serialized owner. SLUS changes also require the image SHA-1 gate. partition_history.tsv maps every one of the 3,704 old claims to its current home/lane; it never authorizes editing an old placement copy.
3. Continue remaining T01/T02/T03 views using the refreshed partition; this lane extracts only the listed module views. For the next ranked concept T06, resolve the existing 32-bit UnsignedHalfView name collision first: the proposed scalar is 16-bit and needs a meaning-specific name and call-root review. T07 and T08 then follow the explicit target lists in refs/delivery.tar.gz.
4. Have LL4 retire the two registered relink copies listed in compatibility_aliases.tsv, then remove the shim and renew the module certificate. For further cast cleanup, use cast_counts.tsv and the typed parameter/field roots. Preserve byte arithmetic and negative-prefix strides. Complete TU and placement proofs remain required when changing an exported module type.
5. Reproduce the retained source result with the hash-guarded patch. `lane.py` and `finish.py` preserve the phase implementation and use this lane's receipts and before images; they are not a turnkey census regenerator. For a new implementation lane, extract scripts, vendor/, target_files/ and file_claims.tsv from refs/delivery.tar.gz into reference/, then revalidate its selections and ownership against the new root before staging. Carry the explicit skipped_copies.tsv exclusions forward. Regenerate scope, row/TU checks and certificate prerequisites before its one final scoped gate. The existing scratch contains immutable before images and the one-gate marker: do not rerun the final gate in this delivered lane. `verify_repair` is for new failures or declaration repairs only.
