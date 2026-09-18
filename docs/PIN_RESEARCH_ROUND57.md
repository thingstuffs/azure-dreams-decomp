# Pin research round 57: the scheduler's tie rule, and statement order as the lever

Round 57 (2026-09-18, from 88ef2356 = 5,947 pins / 1,262 rows) follows [the charter](PIN_CAMPAIGN_CHARTER.md). It answers the question round 56 left open, "what decides where sched2 places a register move", by reading the compiler instead of probing it blind, and turns the answer into two generators.

## The mechanism (gcc 2.7.2 `sched.c`, shared by 2.6.3 to 2.95.2's old scheduler)

- `schedule_block` fills each basic block **from the end**; an insn's priority is the longest dependence path back to the block start (`priority()`), and `rank_for_schedule` breaks equal priorities by `INSN_LUID`, the **original stream order**. Among ties, the source order wins.
- Every insn after a call that touches a call-clobbered register carries an anti or output dependence on the call, and `ADJUST_COST` (mips.h) zeroes those, so all of them tie at the call's priority. The instructions between two calls are therefore laid out in the order the C statements were written, except where a real data chain lifts one.
- `sched_analyze_1`: a pseudo whose `reg_n_calls_crossed` is nonzero gets **no** dependence on the call, so the first scheduling pass hoists a loop increment written *after* a call above it; a hard-register set after a call never crosses it (the `call_used_regs[i]` loop-index slip makes that unconditional).

Consequence: the decompiler recovers statement order from the scheduled bytes, which is the original order only where the scheduler moved nothing. The pinned rows of the near band's `MOVED` classes (`-move +move` 190 sites, 143 of them argument-register loads; `-li +li` 90, 62 argument loads; `-addiu +addiu` 73, 28) are permutations of independent statements around a call, and the pin was holding the decompiler's order.

Probe (scratchpad `variants.py`: C variants screened by the cc1 listing against the pinned listing): on `dungeon/func_818B1334` the variant with both loop updates written after the call is listing-exact at 2.8.1-G0, 2.7.2-cdk-G0 and 2.7.2-cdk; moving one update alone is not; every copy spelling of the first argument (register, volatile, cast, loop-top, before-loop, comma with the discarded call) fails. Byte-exact with the scorer on all three sibling rows (`func_818B1334`, `func_818B11B4`, `func_818B1484`).

## Generators

- `tools/xform/t71_updateaftercall.py`: `v += k` / `v++` / `v = (T *)v + k` on a local or parameter (declared in the function, never address-taken, not volatile), written just before a call statement that never names `v`, moved after the call (all such updates, then each alone), with the pins in the window erased jointly, singly, then the function's pins jointly. Unit test `tools/tests/test_t71_updateaftercall.py`. Over the 82 eligible pinned rows: **6 rows, 7 pins** (the three probe rows to zero; `func_800B6D74` 17 to 16, `func_8132B8AC` 14 to 12, `func_81330C74` 9 to 8).
- `tools/xform/t72_stmtperm.py`: the run of simple statements around a pin (up to eight, shrunk from the far non-call end until at most 1,000 orders remain), every dependence-preserving order (identifier read/write sets; a statement over non-address-taken locals may cross a call; loads and stores stay ordered with calls; stores to different fields of one base may swap) compiled to the cc1 listing and compared with the pinned text's listing, listing-exact orders byte-verified. Unit test `tools/tests/test_t72_stmtperm.py`. Both generators are in the landing cascade (`land_lanes.sh`, `coherence_sweep.py`).

## Housekeeping

- The forced cascade over the 312 pinned rows whose recipe changed in rounds 56b/56d (their sweep journals keyed on `(id, in_sha)` had silently skipped them), T2, one gate; then the lone and joint scans at the new recipes; then the module census over the small modules that had none (349 modules / 600 rows / 1,503 pins were uncensused, 227 of them singletons).
- The coherence tools skip rows already at their module recipe (the census files predate the coherence landings).
