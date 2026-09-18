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

The prologue copy-order class (`MOVED|3-4|-move,sw +move,sw`, 99 sites) was probed the same way on `dungeon/func_80A23000`: the MIPS prologue is RTL in 2.7.2 (`prologue` expander unconditional), so the save/copy pairs are scheduled by the same tie rule, and retail keeps the parameter copies at their statement position in statement order while the erased text keeps the compiler's entry copies in parameter order. No C spelling found moves them: wider or narrower locals add extensions, dead writes to the parameters, copies after the call and dropping the copies all screen at the plain erasure's distance. The class stays with the register allocator (t69's "which copies are parameters"), a bounded negative.

## Next

1. ~~The t72 near-miss table~~ measured (lane `r58_t72near`, 570 rows, 0 exact): 27 rows at listing distance 1 are orders where an instruction vanished (a copy or constant load folded away), 182 at distance 2 are one instruction moved, the erasure's own distance; the metric does not separate them from the plain erasure, so within-run permutation is exhausted on the current text. What remains of the class needs a run that crosses control flow, or the original statement order from a model reading the mechanism.
2. The prologue copy-order class (`MOVED|3-4|-move,sw +move,sw`, 99 sites, callee-saved parameter copies) is the next class to read from the source: `assign_parms` order versus sched's tie rule.
3. Split the FSF-only contiguous runs into their own modules (round 56's finding) so their pinned rows get the right oracle.

## Housekeeping

- The forced cascade over the 312 pinned rows whose recipe changed in rounds 56b/56d (their sweep journals keyed on `(id, in_sha)` had silently skipped them), T2, one gate; then the lone and joint scans at the new recipes; then the module census over the small modules that had none (349 modules / 600 rows / 1,503 pins were uncensused, 227 of them singletons).
- The coherence tools skip rows already at their module recipe (the census files predate the coherence landings).

## Round 58 (same day): the mechanism as a model brief

The re-census of the 30 modules changed by round 57 (365 modules, no new switch) and the t71/t72 coherence sweep at the module recipes (0 of 1,016 jobs) closed the CPU side. A Gemini pack (`work/native_lane/r58_order`, 12 rows with one or two pins from the argument-load classes, brief = the scheduler's tie rule plus the t71 worked examples) resolved **3 rows, 5 pins** before its 90-minute print timeout: `dungeon/func_800CC978` (an int-typed expression before a narrowing, `(s8)(x + 0)`; `- 0` and `>> 0` are exact too, every type-cast spelling is not: the original had real arithmetic there), `dungeon/func_818F9B98` (a copy written in both `if` arms moved after the `if`, the fence dropped), `dungeon/func_80094A20` (a result variable and a flag update restructured). Landed with 3 windows and SLUS MATCH: **5,854 pins in 1,248 rows**. The second pack (`r58_order2`, the other twelve pool rows) runs next; codex stays held until its reset.

The FSF-only module-split lever measured without the split: the 10 pinned rows inside FSF-only contiguous runs of cdk modules (15 pins), scored with their neighbours' FSF recipe as the oracle (coherence_scan's subsets, 94 row-recipe jobs): 0 hits. Splitting those runs into their own modules is a provenance repair only; no pins behind it.

The second pack (`r58_order2`) resolved **4 of 12 rows, 8 pins**: `dungeon/func_81839358` (an if-chain written as a `switch`), `dungeon/func_818B6F90` (constants stored directly, no staging locals), `dungeon/func_818B7E14` (a word-by-word copy written as one aggregate copy), `town/func_800C5ABC` (the parameter typed as the struct pointer, the field stored in each arm instead of staged). Landed with 3 windows and SLUS MATCH: **5,846 pins in 1,244 rows**. Over the two packs the mechanism-briefed rate is 7 of 24 rows, against 1 of 12 for the unbriefed pack of round 56. The eight residues carry per-row mechanism notes in the lanes' `last_message.txt`. A third pack (`r58_order3`) takes the nearest remaining classes (`MOVED|3-4`, `CHANGED|1-2`).

Detector audit of the seven Gemini wins (round 14's lesson: a lane row is a detector auditor): `t38_unstage` had refused `dungeon/func_818B6F90` because the stagings interleave, a keep sits between, one value is stored twice and two other stores sit in another order. `tools/xform/t38b_unstage_run.py` (in the cascade; test `tools/tests/test_t38b_unstage_run.py`) inlines every staging of a run into all its stores, erases the run's pins and searches the order of the run's statements with the listing screen; it reproduces the row (two pins to one, T2 takes the declaration pin). The if-chain-as-switch shape (`t73_ifswitch.py`, kept out of the cascade): 126 pinned rows carry a pure decompiled test tree, the switch rewrite builds on most, but on four probe rows its listing is no nearer retail than the plain erasure, so the tree's order is not the whole story (the case bodies' order or a jump table); a bounded negative for now.

t38b over its 239 eligible pinned rows: 0 exact (the shape lives on the one Gemini row); it stays in the cascade for rows that reach it after other moves.

The fourth pack (`r58_order4`, twelve 1-2-pin rows of the `CHANGED|3-4` class) resolved 6 rows / 6 pins (7 reported, one not landable): **5,840 pins in 1,238 rows**, 8 windows and SLUS MATCH. Mechanism-briefed Gemini packs so far: 13 of 36 rows.
