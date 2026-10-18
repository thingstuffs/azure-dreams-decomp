# r121w_proto2b final delivery

**Every final touched window is MATCH: 813/813, with zero gate holds.**
The continuation freshly gated all 209 requested windows with four workers:
**175 MATCH / 34 ERROR**, exit 1.
Four pass 1 source edits caused the failures. After measured repairs, a second fresh
gate covered exactly their **34 affected windows**, with four workers:
**34 MATCH / exit 0**.

The fingerprint audit then found **48 stale receipts** through nested required-window
dependencies, including three pass 1 receipts, and **111 further windows** missing
from the direct scope. A third fresh gate covered exactly those **159
windows**, with four workers: **159 MATCH / exit 0**.
No further source changes were made.

The final reconciliation checks **813 complete input fingerprints**:
702 computed by the read-only sweep on the frozen final tree and 111 supplied
and audited by the fresh dependency gate. All receipts match those same-tree
fingerprints, including the **490 current pass 1 MATCH receipts**.
Sources remained frozen throughout the sweep, dependency gate, and reconciliation.
The failed engine receipt is superseded.

Baseline: B15 `518d98295ae37fd2897fb507cffa8d50da7eff4c`, recorded by
`SCRATCH_HEAD`. **228 queued C files** are delivered. Compared with the
preserved `delivery_pass1.patch`, three files have narrower edits and one file is
restored completely to B15. The patch contains only queued `src/` C paths:
**no lane files, shared headers, manifests, ledgers, recipes, binaries, or retail
payloads**. No Git commit or ref move was made. `original/src/` preserves B15 bytes.

## Per-item status

All **303 queue files** have a line in [results.tsv](results.tsv), with baseline
and delivered hashes, row receipts, and declaration holds. Every `gate_scope_hold`
cell is empty.

| Status | Files | Meaning |
| --- | ---: | --- |
| COMPLETE | 139 | Declaration work complete; affected windows have current MATCH receipts |
| PARTIAL | 89 | Row-exact edits delivered; declaration evidence remains held |
| HOLD | 13 | B15 bytes retained, with the reason recorded |
| SKIP_COPY | 62 | Relink, hand-copy, or unregistered native copy retained for LL4 |
| Total | 303 | Entire fixed queue assessed |

File-local `M2C_` occurrences fall from **939 to 364**,
removing **575 (61.2%)**. Home sources fall from
**749 to 174**; excluded copies retain 190.
The remaining home occurrences are 164 unproved data declarations, eight reviewed
code-address imports, and two local typedefs. 153 home sources have zero local
occurrences. Counts include embedded generated type names and exclude header contents.

## Deliveries

- [delivery.patch](delivery.patch): final changes against B15.
  [delivery_pass1.patch](delivery_pass1.patch) preserves pass 1 unchanged.
- [results.tsv](results.tsv), [holds.tsv](holds.tsv),
  [signature_evidence.tsv](signature_evidence.tsv), and
  [final_row_checks.json](final_row_checks.json): complete accounting, declaration
  provenance, and exact row receipts for all 228 final edited hashes.
  [continuation_repairs.json](continuation_repairs.json) records all four before/after
  hashes; [gate_failure_resolution.tsv](gate_failure_resolution.tsv) maps every
  initial non-MATCH window to its correction and fresh MATCH receipt.
- [touched_windows.txt](touched_windows.txt): independently recomputed final
  **813-window** dependency scope across **132 fingerprint-dependent native modules**
  (48 have directly edited sources).
  [gate_refresh_attempted.txt](gate_refresh_attempted.txt) preserves the actual
  209-window first continuation scope; [gate_repair_windows.txt](gate_repair_windows.txt)
  records the exact 34-window repair scope. `gate_refresh_windows.txt` is retained
  as historical input; its entries are all proved now.
  [gate_dependency_refresh_windows.txt](gate_dependency_refresh_windows.txt) records
  the exact 159-window dependency gate; [fingerprint_scope_audit.json](fingerprint_scope_audit.json)
  explains the extra fingerprint dependency layer.
- [gate.log](gate.log): all continuation invocations, process exits, and final audit.
  [gate_refresh_journal.jsonl](gate_refresh_journal.jsonl) and
  [gate_refresh_run.json](gate_refresh_run.json) preserve the initial failures.
  [gate_repair_journal.jsonl](gate_repair_journal.jsonl) and
  [gate_repair_run.json](gate_repair_run.json) contain the fresh repair proofs.
  [gate_dependency_refresh_journal.jsonl](gate_dependency_refresh_journal.jsonl) and
  [gate_dependency_refresh_run.json](gate_dependency_refresh_run.json) contain
  the fresh transitive dependency proofs.
  [gate_dependency_resolution.tsv](gate_dependency_resolution.tsv) accounts for
  all 48 stale and 111 previously omitted dependency receipts.
- [gate_journal.jsonl](gate_journal.jsonl) and [gate_run.json](gate_run.json): final
  current proof index. The journal retains all 813 verified touched windows.
  [gate_currentness.json](gate_currentness.json) independently compares every
  complete input fingerprint with its successful receipt.
  [gate_fingerprint_sweep.log](gate_fingerprint_sweep.log) preserves the read-only
  sweep; [gate_fingerprint_audit.json](gate_fingerprint_audit.json) preserves the
  pre-refresh 48-stale diagnostic and actual source hashes.
- [gate_pass1.log](gate_pass1.log),
  [gate_journal_pass1.jsonl](gate_journal_pass1.jsonl),
  [gate_run_pass1.json](gate_run_pass1.json), and [REPORT_pass1.md](REPORT_pass1.md):
  preserved original failure and handoff.
- [summary.json](summary.json), [audit.json](audit.json),
  [final_validation.json](final_validation.json), [delivery_files.txt](delivery_files.txt),
  and [MANIFEST.sha256](MANIFEST.sha256): delivery checks and portable selection.

Complete-TU repair proofs and historical signature, binding, SDK, and row-check
evidence are included in the manifest. Every portable receipt is under 2 MB and
contains no absolute machine path. The large definition index is represented by
size and SHA-256 in `summary.json`. Historical rewrite/finalization scripts and
rejected `scratch/` trials are not instructions to rerun.

## Repairs and validation

| File | Cause in pass 1 edits | Final disposition |
| --- | --- | --- |
| `src/dungeon/func_8009681C.c` | New typedef duplicates a callee typedef; converting `D_8009BE2C` also removes a reviewed import | Retain the import; keep the local signed-word pointer cleanup |
| `src/dungeon/func_800A2504.c` | Converting `D_800A7CC4` removes a reviewed import | Entire file restored to B15; declaration work held |
| `src/dungeon/func_800C06FC.c` | Exact home `void` prototype conflicts with an unqueued sibling's existing signed-word declaration of `func_8003DB94` | Retain the existing caller view; keep safe field/local type cleanups |
| `src/dungeon/func_800C6438.c` | Converting `D_800CB9DC` removes a reviewed import | Retain the import; keep the exact independent prototype and field cleanup |

All four repairs were measured as candidate substitutions while the initial gate's
sources stayed frozen. Each complete TU matches retail and genuine ASPSX 2.79:

| Complete TU | Bytes | Retail | Genuine ASPSX 2.79 |
| --- | ---: | --- | --- |
| dungeon_engine_transition_effects | 7,236 | MATCH | MATCH |
| dungeon_engine_entity_effects | 9,476 | MATCH | MATCH |
| dungeon_engine_effect_dispatch | 10,612 | MATCH | MATCH |
| dungeon_engine_trap_effects | 13,148 | MATCH | MATCH |

`transition_context_failure.log`, `transition_typedef_only_trial.json`, and
`dispatch_context_failure.log` preserve the declaration failures and import-only
trial. The `*_repair_proof.json` files bind the measured candidates to delivered
hashes. The previous dungeon utility repair still matches its complete 6,140-byte
TU; its engine window now also has a current MATCH receipt.

After the first continuation gate completed, the four measured source corrections
were applied. Three retain edits; one becomes a baseline hold. New row checks in
`checks_continuation.jsonl` are exact. The repair gate rebuilt only the 34 windows
invalidated by those corrections. Sources remained frozen during each gate and
after the repair gate through final delivery.

All **228 edited source hashes** have exact final row checks. The normalized
body audit covers **230 definitions** and permits only documented aliases,
code-symbol references, direct fields, vector spelling, and NULL expansion.
No pin, asm, volatile, NON_MATCHING, pragma, goto, coercing cast, or mask mechanism
is added. All 62 copies retain B15 hashes. The row database/link-list check reports
`row database OK`. The final patch passes zero-fuzz forward and reverse dry runs.

The direct row/native scope has 693 windows. A module fingerprint also binds the
digests of its required windows; a broad window therefore propagates a source
change into sibling module fingerprints and their other windows. Including this
canonical dependency layer expands the final scope to 813, excluding four
production-superseded seeds. The entity caller's nine sibling windows remain in
that scope through this coupling even though its source is restored to B15.
The extra gate refreshes the 48 stale receipts and 111 newly identified windows.
All 813 final receipts are current; there are no failed or unproved touched windows.

## Signature work and original-prototype evidence

All M2C function declarations in home sources are removed. **47 direct prototypes**
use identified C definitions, including three resolved through true-space placement.
**82 apparent data declarations** become identified code addresses; five use
applicable engine concept declarations. Another 62 function sites retain
caller-supported views, including address-only callbacks without proved arity.
Twenty-one resident alias hints support later work. No storage extent is inferred
from neighboring labels or partial reads.

**Proven original-prototype mismatches: one.** In `src/dungeon/func_800B1364.c`,
`load_monster_resource_data` returns a callable pointer in the caller declaration;
its same-bank definition in `src/dungeon/func_8009B434.c` returns `s32`. The caller
immediately invokes it. Using the exact definition fails with `called object is
not a function`; both original and retained caller rows are exact. See
`loader_signature_mismatch.json`. The native cohort prototype conflict above is
an integration constraint and is not counted as additional original-prototype evidence.

The separate `prototype_followup.patch` supplies the loader's outer parameters
(`s32`, `u8 *`, `s32`) and has an exact 812-word row proof. **It is not applied or
window-gated in this delivery.** The current engine MATCH certifies the delivered
source hash only. Seven cross-container identities remain held; ten rejected home
spellings retain signatures through registered placement symbols, as documented
in `binding_evidence.json`.

## Holds by reason

These are declaration/follow-up holds; **SCOPED_GATE_REFRESH: 0 windows**.
Counts are symbol/reason occurrences, except `NON_HOME_COPY`, which counts files.
Every hold has evidence, its retained declaration where relevant, and a next step
in [holds.tsv](holds.tsv).

| Reason | Count | Needed evidence or action |
| --- | ---: | --- |
| DATA_TYPE_OR_EXTENT_UNPROVED | 164 | Correct-bank object definition or applicable concept type and extent |
| NO_C_OR_SDK_SIGNATURE | 55 | C definition, SDK header, or asm ABI |
| CROSS_CONTAINER_IDENTITY | 7 | Actual callee identity in the caller load image |
| NATIVE_IMPORT_CONTRACT | 8 | Coordinated cohort declarations and reviewed import inventory |
| NATIVE_DECLARATION_CONTRACT | 1 | Coordinate the unqueued sibling declaration before adopting the exact home prototype |
| SIGNATURE_MISMATCH | 1 | Reconcile callable caller and scalar-returning loader |
| FOLLOWUP_GATE | 1 | Apply and gate the separate loader parameter candidate in a later batch |
| RETAINED_DATA_ALIAS | 2 | Resolve storage before removing local typedefs |
| NON_HOME_COPY | 62 | LL4 handling |

## HOW TO CONTINUE

1. Verify `MANIFEST.sha256`, check B15, and apply `delivery.patch`. Every touched
   window has current MATCH proof; no gate repair remains in this delivery.
2. Resolve declaration holds by correct load image and defining source. Coordinate
   native import inventories and unqueued sibling declarations before changing
   those interfaces. Leave the 62 excluded copies to LL4.
3. Treat `prototype_followup.patch` as a separate candidate. If selected later,
   apply it after the final delivery, check its rows, and freshly gate its full
   affected scope. Its row proof alone is not window certification.
4. Before later edits, compute row placements, complete native TU dependencies,
   and the nested required-window fingerprint dependency layer. Audit every
   receipt in that scope, then gate only invalidated windows with four workers
   and fresh evidence. Do not rerun historical rewrite or pass 1 finalization scripts.
