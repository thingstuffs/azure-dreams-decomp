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

## Results

| landing | what | pins | gate |
|---|---|---|---|
| r57a (7dd2ccc9) | forced cascade + T2 over the 312 recipe-switched pinned rows | 5,947 -> 5,938 | 6 windows + SLUS MATCH |
| r57 | t71 (6 rows) + t72 (25 rows, one stale) lanes, cascade 19 applied | 5,938 -> 5,866 / 1,253 rows | 24 windows + SLUS MATCH |
| r57b | lone-scan flag trades at the new recipes (6 rows / 6 pins, all recorded) | 5,866 -> 5,859 / 1,251 rows | 6 windows + SLUS MATCH |
| r57c | 203 byte-neutral recipe switches in the newly censused small modules (55 pinned rows / 269 pins) | unchanged | 139 windows + SLUS MATCH |
| r57d | two coherence repairs (`dungeon/func_808B16A0` 2.95.2-G0 -fno-schedule-insns -> 2.6.3 by a width change; `dungeon/func_80D65810` 2.8.1 -> 2.7.2-cdk-G0 by a parameter copy) | unchanged | 2 windows + SLUS MATCH |

Round total: **88 pins** (5,947 to 5,859 in 1,251 rows), zero model tokens. t72 over its 761 eligible rows: 25 exact from 260k listings and 35 scorer calls; a deeper pass (8,000 listings, 3,000 orders) on the 79 rows that hit the cap found nothing; 85 rows have no permutable run; one row was listing-exact but byte-different. Receipt `docs/evidence/pin_research_round57_20260918.json`.

Recipes in use afterwards (overlay/main rows): 2.7.2-cdk-G0 4,751; 2.8.1-G0 219; 2.8.0-G0 165; 2.6.3-G0 162; 2.7.2-cdk 128; 2.7.2 119; 2.7.2-G0 116; 2.6.3 112; 2.8.1 35; 2.8.0 23; 2.95.2-G0 16; 2.91.66(-G0) 9; flags: -fno-schedule-insns 63, -fno-strength-reduce 59, -fno-cse-follow-jumps 48, -fno-schedule-insns2 31, -fno-expensive-optimizations 31, -fno-cse-skip-blocks 30, -O1 29, -fno-rerun-cse-after-loop 14, others 21.

## Bounded negatives

Coherence scan over the 31 newly nonconforming pinned rows of the small modules: 0. Coherence perturbation over the small modules: 1 of 199 pin-free rows, 2 of 510 pinned (erase-then-perturb), both landed as repairs above. Joint cells scan after the switches: 0 of 204. Lone cells scan 0 of 332, flags2 0 of 318. The forced cascade's generators refuse the switched rows for the same shape reasons as at their old recipes.

## Next

1. The t72 misses with a run but no listing-exact order (about 570 rows) now journal their nearest order; a near-miss table (distance 1-2 lines) names where the run boundary or the dependence guard is the limit (statements across an `if`, loads across a call).
2. The prologue copy-order class (`MOVED|3-4|-move,sw +move,sw`, 99 sites, callee-saved parameter copies) is the next class to read from the source: `assign_parms` order versus sched's tie rule.
3. Split the FSF-only contiguous runs into their own modules (round 56's finding) so their pinned rows get the right oracle.

## Housekeeping

- The forced cascade over the 312 pinned rows whose recipe changed in rounds 56b/56d (their sweep journals keyed on `(id, in_sha)` had silently skipped them), T2, one gate; then the lone and joint scans at the new recipes; then the module census over the small modules that had none (349 modules / 600 rows / 1,503 pins were uncensused, 227 of them singletons).
- The coherence tools skip rows already at their module recipe (the census files predate the coherence landings).
