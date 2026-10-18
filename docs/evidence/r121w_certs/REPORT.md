# r121w_certs: certification diagnosis and preparation

Base: `ebf0bb89f11b43101506c3fdbfb1ac90bed4716a`. Work and build outputs stay in this private root. `refs/` is empty. No Git commits or ref moves were made.

55 of 74 targets pass the unchanged canonical scratch certificate producer and its current certificate reader: 52 first SLUS certificates, two SLUS renewals, and one first overlay certificate. The other 19 are precisely held: 17 overlay placement reviews and two missing SLUS module-specific headers. No installed/production certificate or level record is delivered or promoted.

There are two distinct readiness counts. **One overlay is fully reviewed and computationally ready for issuance**: `dungeon_ovl_16b08_local`. **54 SLUS modules pass all computational certification checks**, but their existing evidence prose still says Reviewer: pending. Their scratch reviewer is explicitly diagnostic; these successes do not complete the pending source review. The SLUS certifier checks a nonempty reviewer/document but does not parse that prose. The remaining final-review work is recorded rather than hidden by its permissive check.

## What was actually measured

- Enumerated 212 overlay modules and 56 whole-row SLUS modules: 268 placement candidates. The existing certificate roster contains 194 overlays and two SLUS records, leaving 18 + 54 missing. Three partition-only owners (`accessors_814c8`, `table_counters_b1b_b1c`, `sound_tu_code`) are outside the 268 and cannot grant whole-row placement.
- Ran the canonical certification path for every one of the 74 targets before repairs. All 18 overlays stopped at review incomplete. Of the SLUS targets, 54 stopped at the unbuilt private SLUS view; the two header-only owners failed earlier at their missing module-specific header. The unbuilt private view is an environment blocker, not a claim about the production build.
- Built the private SLUS tree with `-j 4`: retail SHA-1 `e6bfbb95ff6676899e077481221d73ddd4d3bf52`, 842 physical C TUs, generated recipe identical to `ledger/splits/slus.build.ninja`. Repeated the real producer for all 56 SLUS targets; 54 pass and the same two header refusals remain.
- All 18 whole-overlay-TU probes pass retail and direct genuine ASPSX 2.79, with zero masks and zero raw substitutions. These complete-TU results do not substitute for reviewed placement or complete window certification.
- All 96 target-GCC declaration-size assertions pass at the final evidence values. Initial probe driver invocation accidentally reached host `as`; it was corrected to `-S`. The subsequent failures identified stale alias expressions and three real scalar-size discrepancies; their original logs are retained.
- The single final scoped gate passed all 51 touched active windows with `--workers 4` and explicit `--only-window`/`--require-window` arguments. No full overlay gate was run. The journal and fresh transaction receipts are lane-owned.
- The reviewed local overlay certificate reuses that gate's fresh native-module proof and window receipt. Its installed-path scratch file is immediately moved to lane storage; existing ledger certificate records are preserved. A final independent reader check passes all 55 scratch certificates, and 662 C/header hash checks remain unchanged. `tools/row_db.py check` passes after the final input changes, including link-list checks.

The old `runtime_directory` record fails with “module sources, headers or manifest changed”. The old `list_cursor_e0` record fails with “certificate physical contributors or destination changed”. Both have fresh passing scratch replacements; their old ledger files are deliberately preserved.

## Mechanical preparation delivered

`delivery.patch` changes evidence/config only. It reconciles 15 over-wide imported views: eight scalar views and four incomplete/address-only views in the local initializer cohort, plus three four-byte scalar-prefix views of the existing resident object-flag owner. A one-byte incomplete view asserts no complete allocation extent. The resident owner's original declaration remains fingerprinted; the per-TU scalar prefix does not redefine the enclosing owner.

Eleven import evidence files now identify current declaration expressions (`g_game_work` / `object_flag_block` where applicable) and bind real target-compiler size measurements. The three scalar declarations that had been recorded as 16 bytes measure four bytes. No import span is enlarged. No C, header, function name, storage allocation, compiler/assembler recipe or tool changes are delivered.

The local 16-member / 1,196-byte initializer cohort has a bounded placement review, reconciled membership/import/placement review records and a fingerprinted review note. Its existing opaque interfaces and repeated record shapes remain explicit source-quality debt; this is no L4/L5 claim. The other 17 overlay reviews stay pending. Their full TU byte equality is evidence for the next reviewer, not an automatic review signature.

## Per-item status

The machine-readable table is [certs.tsv](certs.tsv): module, before state, first blocker, fix, scratch result, hold reason, exact next step and attempt-log paths. “PASS” below always means scratch proof at this root.

| Module | Before | Result |
|---|---|---|
| `dungeon_town_map` | missing | HOLD: placement review |
| `dungeon_ovl_d54c` | missing | HOLD: placement review |
| `dungeon_dungeon_setup` | missing | HOLD: placement review |
| `dungeon_ovl_16b08_local` | missing | PASS (scratch) |
| `dungeon_ovl_16b08_f6a8` | missing | HOLD: placement review |
| `dungeon_ovl_1831370` | missing | HOLD: placement review |
| `dungeon_ovl_1831cd8` | missing | HOLD: placement review |
| `dungeon_ovl_1830850` | missing | HOLD: placement review |
| `dungeon_ovl_9c32d4` | missing | HOLD: placement review |
| `dungeon_ovl_19a332c` | missing | HOLD: placement review |
| `dungeon_ovl_1930844` | missing | HOLD: placement review |
| `dungeon_ovl_18d0850` | missing | HOLD: placement review |
| `dungeon_ovl_188898c` | missing | HOLD: placement review |
| `dungeon_ovl_188298c` | missing | HOLD: placement review |
| `dungeon_ovl_18ca83c` | missing | HOLD: placement review |
| `dungeon_ovl_18b8824` | missing | HOLD: placement review |
| `dungeon_floor_spawns` | missing | HOLD: placement review |
| `dungeon_floor_generate` | missing | HOLD: placement review |
| `runtime_directory` | stale | PASS (scratch) |
| `entry_words` | missing | PASS (scratch) |
| `render_words` | missing | PASS (scratch) |
| `owned_80035484` | missing | PASS (scratch) |
| `owned_80038A10` | missing | PASS (scratch) |
| `owned_80044698` | missing | PASS (scratch) |
| `owned_800448BC` | missing | PASS (scratch) |
| `owned_8004713C` | missing | PASS (scratch) |
| `owned_80047338` | missing | PASS (scratch) |
| `owned_80047468` | missing | PASS (scratch) |
| `state_defaults` | missing | PASS (scratch) |
| `slot_transition` | missing | PASS (scratch) |
| `slot_transition_secondary` | missing | PASS (scratch) |
| `konami_runtime_gp_count` | missing | PASS (scratch) |
| `gp_shared_slots` | missing | PASS (scratch) |
| `gp_split_storage` | missing | PASS (scratch) |
| `gp_shared_81510` | missing | PASS (scratch) |
| `gp_shared_8099c` | missing | PASS (scratch) |
| `cache_afe` | missing | PASS (scratch) |
| `list_cursor_e0` | stale | PASS (scratch) |
| `saved_value_b98` | missing | PASS (scratch) |
| `sort_rank_81540` | missing | PASS (scratch) |
| `command_slots_81554` | missing | PASS (scratch) |
| `address_slot` | missing | PASS (scratch) |
| `command_words` | missing | PASS (scratch) |
| `gp_shared_8152c` | missing | PASS (scratch) |
| `gp_d92c_owned` | missing | PASS (scratch) |
| `gp_order_bytes_owner` | missing | PASS (scratch) |
| `gp_af3_pair` | missing | PASS (scratch) |
| `message_mode_81550` | missing | PASS (scratch) |
| `cd_command_state` | missing | PASS (scratch) |
| `jtbl_80054F9C` | missing | PASS (scratch) |
| `jtbl_80041344` | missing | PASS (scratch) |
| `jtbl_80057A94` | missing | PASS (scratch) |
| `jtbl_80052CE0` | missing | PASS (scratch) |
| `jtbl_800517CC` | missing | PASS (scratch) |
| `jtbl_8004CECC` | missing | PASS (scratch) |
| `jtbl_80042BDC` | missing | PASS (scratch) |
| `jtbl_8005F134` | missing | PASS (scratch) |
| `jtbl_8005EDA0` | missing | PASS (scratch) |
| `jtbl_80052144` | missing | PASS (scratch) |
| `jtbl_80057D20` | missing | PASS (scratch) |
| `jtbl_80041588` | missing | HOLD: own header |
| `jtbl_800595C0` | missing | HOLD: own header |
| `sound_pitch_conversions` | missing | PASS (scratch) |
| `sound_register_helpers` | missing | PASS (scratch) |
| `sound_range_records` | missing | PASS (scratch) |
| `sound_transfer_helpers` | missing | PASS (scratch) |
| `sound_streaming_transfer` | missing | PASS (scratch) |
| `sound_key_buffer` | missing | PASS (scratch) |
| `sound_dma_lifecycle` | missing | PASS (scratch) |
| `sound_reset_state` | missing | PASS (scratch) |
| `sound_transfer_frontends` | missing | PASS (scratch) |
| `sound_event_start` | missing | PASS (scratch) |
| `sound_register_value` | missing | PASS (scratch) |
| `sound_reverb_writer` | missing | PASS (scratch) |

## Holds by reason

- **17 overlays: placement review incomplete.** Review each named membership JSON, shared header and import evidence using its TSV next step. The complete TU, natural allocation/order, direct-genuine and retail probes already pass. Compiler warnings and opaque interfaces remain visible in `scratch/type_audit/<module>/compile.log`; genuine equality is not a substitute for reconciling C interface meaning. Eleven of these received safe evidence-only corrections, without claiming the review complete.
- **2 SLUS modules: no module-specific shared header.** `jtbl_80041588` and `jtbl_800595C0` list only `include/common.h`. The certifier refuses them before image/genuine checks. Their existing data-ownership receipt does not provide placement. Adding and integrating proper interfaces is a separate source/header change, outside this evidence/config-only packet; naming an unrelated header would not fix the contract.
- **54 SLUS scratch passes: final review prose/identity remains pending.** Finish those reviews before authoritative issuance. No byte/recipe repair was necessary for their computational proof. This review hold overlaps the successful proof count and is not another failed certificate attempt.
- **Window-selection follow-up:** `dungeon_ovl_16b08_f6a8` still fails first at review. Its certifier window roster additionally contains `dungeon_deep_t8b_00f6a8.overlay.yaml`, which `gate_all.superseded()` excludes in favor of the true-base twin. This is a measured selector disagreement, not a claimed observed window failure. Reconcile selection/receipt coverage before issuing from active-window receipts; do not delete evidence or weaken a byte check to obtain a pass.
- **Integration freshness:** 21 already-recorded modules share touched windows. The scoped gate rebuilt their relevant window contexts; their certificate records were not rewritten. Validate and renew whichever fingerprints change after applying the packet. Their exact keys are in `scratch/scoped_gate_plan.json` and the compact audit receipt. No unmeasured claim that all 21 are stale is made.

There are no measured recipe-split, timeout, missing-membership or post-fix tool-error holds among these targets. No window failure was observed in the scoped run.

## Deliveries and proof locations

- [delivery.patch](delivery.patch): applicable evidence/config changes and a compact audit receipt. SHA-256 `19045b1cc2126d6c9ddc4aa2975d9fb09e27e738a07aa9712ce88090eade0040`.
- [certs.tsv](certs.tsv): all 74 target rows. SHA-256 `dcfef1f2ed0863470642ed0e0555b7319d59edb08f3834f06bc7c4f2153ae660`.
- [REPORT.md](REPORT.md): this report, holds and continuation.

The patch adds `docs/evidence/r121w_certs_audit.json`, containing per-item results, receipt/certificate hashes, declaration measurements, scoped windows and affected-neighbor keys. These are diagnosis receipts; binary proof bundles are not delivered or presented as portable authority. Scratch certificates live in `scratch/certificates/`, full local artifacts in `scratch/overlay_builds/`, `scratch/fresh_gate/` and the private overlay view. The delivery contains no binaries and no receipt over 2 MB. Helpers in this lane reproduce the audit without editing production tools.

## HOW TO CONTINUE

1. Apply `delivery.patch` to the recorded base (or rebase the evidence edits explicitly), then regenerate the canonical overlay view from the final tree. Run `tools/row_db.py check`. Changes after this scratch snapshot require fresh evidence; copied JSON alone does not issue production placement.
2. Reissue `dungeon_ovl_16b08_local` at final inputs using reviewer `codex-r121w-certs` and the normal complete-window certifier. Keep its source-quality debt visible. Validate the 21 recorded neighboring modules and renew only those whose bound inputs changed.
3. Finish the 54 SLUS reviews named by the TSV, then use `python3 tools/fidelity/certify_slus_module.py MODULE --reviewer REVIEWER --write` under the normal landing lock. Both stale records already have passing current scratch replacements. The private full-image recipe/retail and direct-genuine proofs need no source or recipe repair.
4. Give the two jump-table modules proper reviewed shared interfaces in a separate C/header transaction, preserving retail bytes and the pinned graph, then repeat their canonical certifier. Do not claim ownership-only receipts as placement certificates.
5. Finish the other 17 overlay reviews using their exact TSV paths and probe logs. Resolve the F6A8 superseded-seed selection discrepancy before receipt-based issuance. Gate only the windows touched by those final changes, with four workers; no full gate is needed for this packet.

To recheck this unchanged scratch root, run `python3 validate_final.py` in the lane. The complete scoped command is retained in `scratch/scoped_gate_command.txt`; do not rerun it merely to reproduce already-current results. Recompute `make_deliveries.py` and `write_report.py` only when results or final inputs change.
