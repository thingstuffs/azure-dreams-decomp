# r121_sdk — decision 54

Base: `f32fd43bedd7e30509d5dd72fe9a808f87fd3cc8`. Status: **FIXED POINT**.

Delivered 232 new complete C rows / 91,568 bytes; 33 production windows MATCH. Genuine spimdisasm/m2c first passes are in raw/. Source scores are exact; every changed word is independently bound to a production ELF relocation. No admission uses pins, asm, volatile, NON_MATCHING, masks, or goto. Static placement does not assert runtime residency.

| round | unlocked rows | unlocked bytes |
|---:|---:|---:|
| 1 | 230 | 90892 |
| 2 | 0 | 0 |
| 3 | 2 | 676 |
| 4 | 0 | 0 |

Input: 23,972 attempt records, 1560 distinct container/offset targets, and 370 supplied windows. Targets already covered at the base contribute no delivery rows. Source-score and nonrelocation overlaps are held for twins2. Existing rowbase extents and deltas stay fixed; solved-to-proven changes use the normal promotion hook.

SDK survey: {'NO_USABLE_MATCHED_HEADER': 308, 'BOUND': 37, 'BOUND_CANONICAL': 11, 'HOLD_NO_TYPED_PSYQ_PROTOTYPE': 4, 'HOLD_CANONICAL_DISAGREEMENT': 11}. A matched donor's explicit declaration takes precedence, including local outliers and old-style declarations. Without one, only an unchanged resident SDK symbol with an approved canonical declaration binds. `rand` uses s32 rand(void), `rsin` uses s32 rsin(s32). The other canonical declarations require a uniquely dominant matched source/header ABI agreeing with the PsyQ archive prototype. Old-style declarations support a unique C89-compatible typed signature; ambiguous signatures retain separate vote buckets. Pointer pointees are opaque across translation units, following the inherited contract rule. Full symbol evidence is in docs/evidence/r121_sdk_contracts.json.

Canonical symbols bound: rsin, RotTransPers, RotAverage4, ratan2, AddPrim, SetSemiTrans, SetPolyFT4, SetDrawArea, rand, EnterCriticalSection, ExitCriticalSection.

Conflicting symbols without a canonical fallback (a donor's own declaration can still bind): PushMatrix: HOLD_NO_TYPED_PSYQ_PROTOTYPE; PopMatrix: HOLD_NO_TYPED_PSYQ_PROTOTYPE; RotTransPers4: HOLD_CANONICAL_DISAGREEMENT; RotMatrix: HOLD_CANONICAL_DISAGREEMENT; GetTPage: HOLD_CANONICAL_DISAGREEMENT; GetClut: HOLD_CANONICAL_DISAGREEMENT; SetTile: HOLD_CANONICAL_DISAGREEMENT; DrawSync: HOLD_CANONICAL_DISAGREEMENT; LoadImage: HOLD_CANONICAL_DISAGREEMENT; StoreImage: HOLD_CANONICAL_DISAGREEMENT; SetDrawMode: HOLD_CANONICAL_DISAGREEMENT; strcpy: HOLD_NO_TYPED_PSYQ_PROTOTYPE; bzero: HOLD_CANONICAL_DISAGREEMENT; memcpy: HOLD_NO_TYPED_PSYQ_PROTOTYPE; printf: HOLD_CANONICAL_DISAGREEMENT.

Remaining holds (deduplicated physical offsets and bank windows): {'existing matched source/extent blocks production': 1253, 'no further complete eligible function in bounded SDK hold': 49, 'overlaps twins2 source-score/nonrelocation scope': 52, 'matched_callee_contracts_unresolved': 129, 'entry_no_unique_complete_existing_rowbase': 69, 'template has goto: CONTINUE3 hold': 21}.

Production window blockers: {'existing-matched-source-compile-failure': 282, 'existing-matched-extent-length-drift': 8}. Exact existing rows, source hashes, compiler diagnostics, and overlap with twins2's frozen scope are listed in docs/evidence/r121_sdk_window_holds.json. Existing source failures remain holds in this lane.

Starting-tree production checks: {'checked': 370, 'matched': 80, 'intrinsic_existing_failures': 290, 'complete': True}. These are normal clean production gates on the unchanged source tree, run concurrently with no admission runner active. Only a recorded intrinsic compile failure in an existing matched file, or a fixed-extent length failure, can block further proposals. Such holds require the same source hash and interface/compiler guard. Other failed checks remain eligible for ordinary admission attempts. Complete records are in docs/evidence/r121_sdk_preflight.json.

Deliveries: delivery.patch, results.tsv, next.tsv, levels_seed_needed.tsv; src/raw pairs, append-only split/baseline/promotion/reverify records, registry/graph changes, production object copies and receipts under docs/evidence/r121_sdk*. The patch is cumulative against the base SHA. Raw measurements retain failures; no exact L0 baseline policy is silently imposed. Integration must seed levels under its policy.

The archived native objects change only ELF STT_FILE filename strings to repository-relative metadata. The production objects remain untouched; all code bytes, relocation records and symbol indices are preserved. Both hashes and the metadata byte ranges are recorded.

Per-item status: tooling and decision 54 binding implemented; contract and bank closure FIXED POINT; production/source/raw/object gates required per admission. Other twins2 classes are held outside this lane.

HOW TO CONTINUE: from this private root run `python3 tools/lanes/r121_sdk/run_sdk.py apply` with no second mutation runner. Check state/progress.json and evidence/run.log in the lane. Refresh prerequisite checks with `python3 tools/lanes/r121_sdk/preflight_windows.py` only while the mutation runner is stopped. Existing source-score and nonrelocation repairs belong to twins2; after their integration, refresh the base/donor snapshot and scope, then rerun all affected gates. After a code fix, retry failed transactions only when inputs or dependencies change. Re-publish with `python3 tools/lanes/r121_sdk/run_sdk.py publish`. Do not bypass base guards.
