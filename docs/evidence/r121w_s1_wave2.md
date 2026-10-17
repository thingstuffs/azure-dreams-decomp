## Continuation delivery 2 (2026-10-17)

Delivered **143 new complete C placements / 82,724 bytes**, incrementally on top of `delivery_wave1.patch`. All **32 active touched windows MATCH** in the single wave-2 production gate (`--workers 4`, repeated `--only-window`); no full gate ran. The scope includes the existing placements affected by changed link-list inputs and the separately promoted home record. A read-only publication input-hash audit passes for all 32 windows. Wave-1 deliveries, sources, receipts and rows are preserved.

| Original hold class | New rows | New bytes |
|---|---:|---:|
| entry_no_unique_complete_existing_rowbase | 8 | 1,032 |
| matched_callee_contracts_unresolved | 135 | 81,692 |

Per-item status:
- Callee contracts: PARTIAL. Recovered the complete C89/K&R definition and its own compatible public prototype for `dungeonSearchOutwardForEligibleTile`; selected the encoded resident callee's actual typed definition where scalar signedness differs; proved leading DUNGEON callees with a complete callback-header correspondence and an independently j-pinned following region. TOWN packed CD-read records establish exact sector bounds for the callees beyond conservative rowbase extents. Raw descriptor words, container hash, ISO file LBA and decoder semantics are rechecked. The historical decoder source hash differs from this supplied tree; the same decoding statements are explicitly verified in the current matched source and both hashes are retained.
- Caller contracts: COMPLETE for delivered rows. Lane-local parsing filters C control keywords: the old regex mistook `else if` for another function definition and suppressed the caller interface. Actual typed argument/result lanes and matched call arity are audited. Unknown required inputs remain held.
- Rowbase entries: PARTIAL. 9 new complete-body records are normally promoted, including the existing 96-byte home TU at file `0x553b14`. All prior records, extents and deltas are preserved. Promotion scratch retains matched caller declarations; one page symbol uses the same binding already proved by the native ELF census. Production shares the unchanged home TU.
- Native placement: COMPLETE for delivered rows. Address-valued symbol-plus-addend constraints are collected from the unmodified native ELF; every site for one symbol must agree. An independently matched, symbol-separable TOWN donor replaces a numeric-page donor for six spans. No instructions or source words are patched.
- Ownership/integration: PARTIAL. Supplied holds and occupied extents checked. The earlier sdk2 census handoff/exclusion manifest is still missing. Integration must reconcile it and seed levels from `levels_seed_needed2.tsv`.
- Raw baselines: MEASURED. Eight generated first passes compile exactly, 66 compile with differences, and 69 fail compilation. Those results are retained honestly; all 143 unchanged-TU production placements have exact source scores.
- Packaging: COMPLETE. `delivery2.patch` contains only changes over the applied wave-1 tree. Text receipts include native object SHA-256 and relocation evidence; objects remain local. Large scratch receipts ship as compact summaries with hashes.

Holds by reason (128 of the 271 continuation input records retain uncovered bytes):
- `entry_no_unique_complete_existing_rowbase`: 21
- `link_list_home_definition_identity_conflict`: 1
- `link_list_symbol_addend_conflict`: 7
- `matched_callee_contracts_unresolved`: 45
- `matched_donor_standalone_compile_failure`: 1
- `sdk_canonical_declaration_disagreement`: 2
- `template_has_goto`: 5
- `typed_caller_callee_argument_contract_unresolved`: 46

Input records overlap; do not sum their remaining bytes as unique coverage. The aggregate 14,040-byte DUNGEON inputs now retain unmatched leading callees and goto-bearing donors. MAIN entries still lack an independently bounded image witness. The seven known 1,400-byte source rows still require incompatible values for the same native symbol; both prior donors remain unsuitable. The archive/global SDK disagreements remain held. The 96-byte `0x5dc11c` dependent now has a proven home base, but the source defines dashboard label `func_805D3B14`; the link-list home rule requires its true-address identity and forbids bindings on a home entry. No reader or source identity was changed.

Deliveries: `delivery2.patch`, `results2.tsv`, `holds2.tsv`, `touched_windows2.txt`, `gate2.log`, `admitted_rows2.tsv`, `levels_seed_needed2.tsv`, this addendum, and `docs/evidence/r121w_s1_wave2*` text receipts.

HOW TO CONTINUE (delivery 2):
1. Apply wave 1 once, then `delivery2.patch`. Preserve all earlier SDK and wave-1 material. Reconcile the external census handoffs against both admitted-row lists and seed only the new rows under the integration levels policy.
2. Resume from `holds2.tsv` and `results2.tsv`. Refresh registry, donor snapshot, image bounds and ownership scope on the integrated root; do not resume local mutation state blindly. The final accepted plan is local `wave2/evidence/stage/complete.json`; its digest is in the shipping receipt.
3. Largest residual DUNGEON inputs need actual matched leading callee bodies and goto-free existing donors. Source-shape repairs belong to their owner. MAIN needs independent bounded image evidence; do not reuse the conflicting historical derived boot-window base.
4. The `0x5dc11c` dependent needs a separately authorized home-definition identity repair or another matched home TU. Its missing-base subproblem is solved by the shipped CD-record proof and normal promotion. Keep the SDK canonical disagreements and native symbol conflicts held unless their evidence changes.
5. Use lane-local `scripts/wave2_*.py` as the evidence and admission recipe: full-body contracts, caller audit, exact per-row production-segment scoring, unchanged-TU link lists, raw generation/measurement, normal rowbase promotion, registry/graph checks, dependency-closed touched scope. After new admissions, run one scoped final production gate with four workers. Shared gate readers and production sources remain unchanged.
