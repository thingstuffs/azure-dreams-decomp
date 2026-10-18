# r121w_proto2a FINAL delivery

Baseline: **B15 `518d98295ae37fd2897fb507cffa8d50da7eff4c`**. This private root has no Git metadata. Every queued baseline file was checked against its immutable `original/src/` SHA-256 before the continuation. The tree exactly matched the applied pass 1 patch, including the three module corrections. `delivery_pass1.patch` preserves pass 1 unchanged.

**The continuation proof is complete.** The requested fresh gate used `--workers 4 --all` over all **220** entries in `continuation_windows.txt`: **220 MATCH, zero errors, exit 0**, in 1950.85 seconds. All queued source hashes and the patch stayed unchanged throughout. No source correction or rollback was needed during this continuation. A canonical scope audit found **eight additional dependent windows** missing from both handoff lists. A separate fresh four-worker scope-closure gate rebuilt those eight plus **two stale pass 1 windows** omitted from the continuation list, for **10 windows total: 10 MATCH, zero errors, exit 0**. No source-repair gate was needed.

Every one of the **688 touched active windows** has a current, input-bound MATCH: 230 freshly rebuilt windows (220 requested continuation windows plus 10 scope corrections/rechecks) and 458 unaffected pass 1 MATCH receipts whose complete production input hashes were recomputed against the final tree. Those 458 are retained historical proofs, not a claim that this continuation rebuilt all 688 windows. The four pass 1 ERROR receipts are superseded by fresh MATCH receipts. No stale proof or pending window gate remains.

## Per-item status

[results.tsv](results.tsv) contains exactly one row for each of the 304 queued sources.

| Status | Files |
| --- | ---: |
| PARTIAL | 90 |
| COMPLETE | 138 |
| HOLD | 16 |
| SKIP_NON_HOME_COPY | 60 |

**228 queued C sources change.** Shared headers and out-of-queue C sources: no changes. All 57 relink/hand copies and three unregistered candidates keep their B15 bytes. Tokens: **890 → 387**, removing **503 (56.52%)**; home-source tokens: **720 → 217**. 145 queued files have no `M2C_` token. A file may remain PARTIAL after its window gate passes because a symbol/type hold remains.

The 55 prior `MODULE_SCOPE_PENDING` occurrences and the corrected `MODULE_TYPEDEF_CONTEXT` verification hold are discharged. The necessary module include remains a semantic cleanup hold, with its window gate now verified.

## Deliveries

- [delivery.patch](delivery.patch): FINAL self-contained source patch versus B15. Its bytes match the preserved [delivery_pass1.patch](delivery_pass1.patch); this continuation completes the proof. Only the 228 queued C paths occur in the patch; no lane-directory files, headers, binaries, or retail data.
- [results.tsv](results.tsv), [holds.tsv](holds.tsv), [summary.json](summary.json): per-item status, remaining symbol holds, counts, and final source hashes.
- [touched_windows.txt](touched_windows.txt), [affected_rows.json](affected_rows.json): complete 688-window production scope, including sibling-member dependencies. [continuation_windows.txt](continuation_windows.txt) preserves the exact 220-window requested invocation scope. [additional_scope_windows.txt](additional_scope_windows.txt) lists the eight missing dependencies and two stale-receipt rechecks; [gate_scope_closure_run.json](gate_scope_closure_run.json) records their fresh gate.
- [gate.log](gate.log), [gate_journal.jsonl](gate_journal.jsonl), [gate_run.json](gate_run.json): indexed gate history and final current coverage. The compact final journal contains only current MATCH records. [gate_continuation.log](gate_continuation.log), [gate_continuation_journal.jsonl](gate_continuation_journal.jsonl), and [gate_continuation_run.json](gate_continuation_run.json) preserve the fresh invocation independently.
- [window_proofs.json](window_proofs.json), [window_proofs_summary.json](window_proofs_summary.json), [carry_window_proofs.json](carry_window_proofs.json), and [carry_audit.log](carry_audit.log): canonical input hashes, receipt origin, and verification of the 458 retained proofs.
- [final_row_checks.json](final_row_checks.json), [module_final_checks.json](module_final_checks.json), [staged_sources.tsv](staged_sources.tsv), [audit.json](audit.json), and [patch_check.log](patch_check.log): source-hash-bound row/module receipts, final hashes, body/scope audit, and B15 patch dry run.
- [declaration_evidence.tsv](declaration_evidence.tsv), [declaration_evidence.json](declaration_evidence.json), and [signature_mismatches.json](signature_mismatches.json): declaration provenance and rejected stronger interfaces.
- [MANIFEST.sha256](MANIFEST.sha256): final portable delivery/evidence hashes. All indexed files are below 2 MB and contain no absolute home-directory paths.

`REPORT_pass1.md`, `gate_pass1.log`, `gate_journal_pass1.jsonl`, `gate_run_pass1.json`, `gate_snapshot.patch`, and `post_gate_correction.json` preserve historical pass 1 evidence. The post-gate correction receipt describes the old frozen snapshot; `scoped_gate_binding_pending` is now false and points to the fresh proof. `integration_followup.patch` is historical and already included in both delivery patches; do not apply it after the FINAL patch. Supporting scripts and immutable originals remain in the lane. The large function index stays isolated under ignored `scratch/`; its census and hash remain in `function_index_summary.json`.

## Changes and limits

Function declarations receive their identified C definition's return type and parameter list, subject to the explicit caller-ABI and module-context holds below. Home resolution follows registry `source_row` and the source-layout resolver; numerical row IDs are not treated as load addresses. Banked address lookups use registered placement addresses within the caller's load window. A repeated semantic function name is resolved to the caller's bank before taking its signature. Tagged pointer types gain exact forward declarations; required anonymous records retain the defining layout. No shared header is edited.

Fifty former data declarations identify code addresses. One keeps its existing `D_800A5FC0` linker spelling with an exact function type, because the certified module requires that imported alias. These receive their home function signatures, with stable function/address spellings preserving the original relocation address. Caller field and pointer views retain their existing storage representation. Other data refinements use explicit resident declarations already present in dungeon concept/module headers, including `ActiveEntry D_800E3648[32]`. Every accepted replacement records its evidence. An unrelated bank's same-address object or an owner-unresolved padding definition is insufficient storage evidence.

Local unknown aliases become their exact signed widths from the compatibility definitions. Explicit pointer/callback extern objects retain their pointer levels and existing signed-word view where a semantic pointee/target remains unknown. Unused FIELD/BREAK/SYNC/HIGH_WORD/UNALIGNED macro definitions and unused extern function declarations are removed. The long-long alias becomes `s64`. The compatibility include is removed from edited files with no remaining file-local `M2C_` token, except for one include needed by an out-of-queue module sibling. The final delivery deliberately retains that include and holds the dependency explicitly. Otherwise, its existing `NULL = 0` expansion is used when needed.

`src/dungeon/func_819BF2E8.c` depended on its production module for a callback declaration. It now declares the callback locally as `void shrink_effect_and_spawn_particles(void *, void *)`, from the same-bank definition in `src/dungeon/func_819BEFC0.c`. The final row is byte exact in isolation. Its unedited B15 check reports `ok`, exact=True; see `checks_baseline.jsonl`.

No cast is added to force a match. No pin, asm, volatile qualifier, NON_MATCHING branch, pragma, goto, or mask is introduced. The normalized-body audit permits only the existing signed-width aliases, the existing NULL expansion, and established symbol renames; all bodies pass that audit.

## Signature mismatches: original-prototype evidence

Four caller sites involve three symbols. The exact identified definition signature fails to compile at each caller; the retained interfaces pass the hash-bound final row checks and the current window proof.

| Caller | Symbol | Identified definition | Retained caller contract |
| --- | --- | --- | --- |
| `src/dungeon/func_8008F228.c` | `func_800424E0` | `void func_800424E0(void *entity, int value)` | `extern void func_800424E0(void *, s32, void *);` |
| `src/dungeon/func_80B9769C.c` | `func_80171B58` | `void advance_stored_path_motion(void *action, s32 action_id, void *entity, void *move_state)` | `extern void func_80171B58(void *);` |
| `src/dungeon/func_8008DCFC.c` | `load_monster_resource_data` | `s32 load_monster_resource_data(s32 resource_id, u8 *resource_entry, s32 wait_for_read)` | `extern void *(*load_monster_resource_data(s32 resource_id, s32 resource_slot, s32 wait_for_read))(s32, s8, s8, s16);` |
| `src/dungeon/func_8008F228.c` | `load_monster_resource_data` | `s32 load_monster_resource_data(s32 resource_id, u8 *resource_entry, s32 wait_for_read)` | `extern void *(*load_monster_resource_data(s32 resource_id, s32 resource_slot, s32 wait_for_read))(s32, s16, s16, s16);` |

`func_800424E0` receives three arguments at this caller while its definition takes two. The placed `func_80171B58` receives one object pointer while its home takes four parameters. Both `load_monster_resource_data` callers supply an integer resource slot and invoke its return value; the definition accepts a byte pointer and returns `s32`. Their existing narrow callback argument widths are preserved. No coercing cast is added.

The generated-TU conflict for `func_8003DB94` is recorded separately as `MODULE_PROTOTYPE_CONTEXT`: the exact home void/short signature conflicts with the out-of-queue sibling's unrecovered signed-word declaration. This is current composition evidence and is excluded from the four original-prototype conflict sites.

## Holds by reason

Counts are symbol/reason occurrences and can overlap within a file. There are no gate holds and no continuation rollback holds.

| Reason | Occurrences |
| --- | ---: |
| DATA_NO_DEFINITION | 187 |
| CALLBACK_TARGET_TYPES_UNKNOWN | 1 |
| POINTEE_TYPE_UNKNOWN | 1 |
| NON_HOME_COPY | 57 |
| SHARED_TYPE_NAME | 1 |
| NON_HOME_NATIVE_CANDIDATE | 3 |
| NO_C_CALLEE_DEFINITION | 20 |
| CROSS_CONTAINER_IDENTITY | 3 |
| SIGNATURE_MISMATCH | 4 |
| MODULE_PROTOTYPE_CONTEXT | 1 |
| MODULE_IMPORTED_CODE_ALIAS | 1 |
| MODULE_INCLUDE_DEPENDENCY | 1 |

Remaining home tokens are 187 unresolved data declarations, 26 local compatibility typedef occurrences needed by those declarations, and four existing shared-header type-name occurrences. Missing callee signatures record body-supported argument categories and the prior signed-word return view; they do not claim a recovered SDK ABI. Three `initialize_object_entries` bindings remain unproved across containers. The necessary compatibility include, imported `D_800A5FC0` spelling, and unreconciled sibling prototype remain explicit cleanup holds even though the delivered tree passes its windows.

## Validation

Both fresh invocations started from empty journals and bypassed cached verdicts with `--all`. The first ran exactly the requested continuation scope. The second ran only those 10 dependency and stale-receipt follow-up windows. Both completed their canonical final input-hash audits. [final_scope_audit.json](final_scope_audit.json) records why the previous scope missed seven windows with decimal YAML offsets and `dungeon_deep_t8b_2a3000` (module prefix-data overlap). The lane's `compute_scope.py` now reads parsed YAML and the canonical complete-module extents; no production tool was changed. The separate 460-window audit recomputed canonical `inputs_sha` values without compiling more windows. It verified 458 current MATCH receipts and found two stale fingerprints (`dungeon_deep_t8b_0bd880` and `dungeon_deep_t8b_0d6948`); those were discarded and freshly rebuilt in the scope-closure invocation. The initial failed audit is retained in `carry_window_proofs_summary_initial.json`. Its source hashes match the gate's before/after snapshots and the delivered sources. [window_proofs_summary.json](window_proofs_summary.json) binds every final affected window to these receipts.

The complete scope contains **1666 registered row dependencies**, including **529 linked placements**, across **688 active windows**. Superseded synthetic seed windows are excluded by production policy. The earlier direct scope was 757 rows/464 windows; final scope includes all affected module siblings. All **228 edited sources** retain exact source-hash-bound checks: 8 use the complete-module verifier where isolated scoring lacks production context, and 220 use isolated complete-row comparison. All 47 affected complete TUs have retail and genuine ASPSX MATCH receipts with zero masked bytes.

The row database/link-list check remains `row database OK`. Regenerated source/body audit and patch dry run pass. [final_validation.json](final_validation.json) checks the final queue, patch paths, source hashes, receipt coverage, and discharged gate holds. Every baseline file matches its recorded B15 hash, every final row receipt matches the delivered source hash, excluded copies are unchanged, and the patch is exactly reproducible from the 304 preserved originals and final tree. No compiler recipe, manifest, import inventory, shared header, or gate tool was changed.

## HOW TO CONTINUE

1. From B15, dry-run and apply only `delivery.patch`: `patch -p1 --dry-run --batch -i <lane>/delivery.patch`, then `patch -p1 --batch -i <lane>/delivery.patch`. The patch includes all three corrections. Carry this report, the final manifest, results/holds, and window evidence with the delivery. The continuation gate obligation is complete.
2. Select a semantic hold in `holds.tsv`. For unresolved data, establish its same-load-image owner, defining type, and allocation extent. Another bank's same address, an adjacent symbol, or a partial body access is insufficient. Remove compatibility aliases/includes only after the final dependency is resolved.
3. Recover the 20 missing C/SDK interfaces and three cross-container identities. Keep the verified caller contracts at the four signature-conflict sites until stronger original declaration/binding evidence is available.
4. Type the out-of-queue `func_800C06FC.c` sibling before restoring this caller's exact `func_8003DB94` interface. Preserve the imported `D_800A5FC0` spelling until an authorized owner batch reconciles its inventory. Move the compatibility include to its actual out-of-queue consumer in an owner batch. Leave the 60 non-home/candidate files to LL4; rename the two embedded `M2C_` shared types only with their owning header and all users in scope.
5. For new source edits, use `check_rows.py` with an explicit source list, recompute the complete home/placement/module window closure, and run one fresh four-worker gate over the changed window inputs. If a window fails, fix an in-scope cause or revert this lane's edits to files affecting that window and record a reasoned hold; re-gate only windows changed again. The historical rewrite scripts and `run_gate.py` must not be rerun over this final delivery.
