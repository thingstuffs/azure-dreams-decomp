# Production pin-search results — 2026-09-12

The detached `pins_restart_20260912` search processed 1,646 functions. It staged 147
improvements removing 266 pins; 1,498 rows had no accepted improvement and one hit a
compiler timeout. The initial search ended at 10:56 UTC. Retrying its tag correctly
scheduled only the failed row, which timed out again.

All 147 candidates were independently reverified and passed the source acceptance checks.
Their combined publication passed all 151 affected overlay windows and the full 884-TU
SLUS executable SHA-1 gate at 11:09 UTC. The other 2,021 windows retained current MATCH
proofs. Thirteen functions became pin-free. There were no added fences or detected fake
dependencies. The publication receipt explicitly defers `dungeon/func_800C4A80`; it does
not turn its search error into a completed search.

Receipt: `ledger/pin_runs/pins_restart_20260912.json`. Frozen inputs, candidate sources,
rollback copies and full logs remain under `work/pin_search/pins_restart_20260912/`.

The standing T2/T20 follow-up examined all 147 changed functions. T2 removed 14 further
pins from 12 functions; bounded T20 removed another five pins and two fences from four
functions, with one overlapping T2. T20 used at most 24 verifier calls per row, 12 per
fence and two rounds. The combined source change removes **285 pins and two fences across
147 functions**, with no added detected fake dependencies. There are **10,303 live pins
in 1,634 pinned rows**; 13 functions became pin-free in this batch.

All 17 windows affected by follow-up passed, followed by the full SLUS SHA-1 check and
an explicit check of the final image and pinned build recipe. Census, levels and status
were refreshed. Follow-up receipt: `ledger/pin_runs/pins_restart_20260912_followup.json`.
Combined tracked evidence: [pin_search_restart_20260912.json](evidence/pin_search_restart_20260912.json).

## Compiler timeout and generator fix

An instrumented replay reproduced the failure after 70 screen requests and saved the exact
variant. `fold_load_candidates` substituted a variable everywhere before removing its
declaration, producing `s32 (coords->unk_24.s);`. It also substituted into subsequent writes
to the temporary, despite its stated single-assignment precondition.

The generator now requires one declaration, one definition and one read in the immediately
following simple consumer, rejects address escape, updates, calls and conditional evaluation,
and removes the declaration before substituting the read. The formerly failing row completed
its 1,200-screen diagnostic replay in 22 seconds without a timeout or a full-verifier request.
Twenty generated variants from other functions compiled successfully under their recorded
compiler recipes. Unit regressions cover declaration removal and ten rejection cases.

The controller also handles future generated-program timeouts as explicit bounded stops:
it retains verified wins and the offending source, without caching a negative compilation
result. Reference timeouts remain retryable errors. An explicit publication deferral can
leave a named search error unresolved while independently verifying and gating the rest.
Default publication still refuses errors. The complete regression suite passes 26 tests.

Diagnostic evidence is under `timeout_diagnosis/` within the run directory. The
`default_policy_probe/` subdirectory is an exploratory run made before configuring the
production generator policy; it is not the production replay or completion evidence.

## Next mechanical batch

Keep baseline search as the default, following the earlier paired pilots. Select the 84
functions that already yielded removals but exhausted a row budget with pins remaining,
plus the repaired timeout row. Prepare from the current source after T2/T20 follow-up,
with 2,400 screens, 24 full verifications and 80 CPU seconds per row, four low-priority
processes. The group screen cap and beam settings remain unchanged. Search stages results;
publication still requires independent candidate, overlay and executable checks.

`pins_followup_20260912` was prepared from the gated source and started detached at 11:21 UTC:
85 rows, four workers, run key `28970f123931f5c5adf6fc717bbe1a3539a57bd0212d70153bb28df1d2a57203`.
The controller is processing rows and recording completions with no startup errors.

The initial run spent about 6.8 CPU hours for 266 removals. Rows that exhausted CPU yielded
about 17 pins per CPU hour, versus 38 for screen-limited rows and 70 for rows that completed
their search. These are observed groups, not randomized comparisons. They support a bounded,
selected follow-up rather than increasing the budget for the entire corpus. No per-function
model campaign is needed.
