# r121_sdk

Decision 54 recovery for the supplied private base. `run_sdk.py apply` is the
only admission entry point. Its lane inputs and resume records live under
`work/native_lane/r121_sdk/`; `BASE_COMMIT` names the original base and
`state/base_rows.json.gz` freezes its donor registry. Existing matched sources,
headers, compiler recipes and gates remain admission authorities.

`preflight_windows.py` runs clean production gates concurrently while the
admission runner is stopped. Its cache can hold an unchanged existing C compile
failure or fixed-extent failure; it never admits a row. `run_sdk.py publish`
recomputes body/import/object proofs, appends measured ledger events, emits the
cumulative patch, and commits the checkpoint locally.

Core discovery, generation, raw first pass and production transaction logic were
ported from the supplied twins2 scripts. The remaining historical modules are
library dependencies; their old census/packaging command lines are not supported
entry points in this lane. Only one admission runner may mutate this tree.

After another lane repairs existing source-score or nonrelocation holds, refresh
the combined base, donor snapshot and ownership scope before restarting. Keep
normal production gates and regenerate the cumulative patch against that base.
