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

The third pack (`r58_order3`, eight `MOVED|3-4` prologue-copy rows and four `CHANGED|1-2`) resolved 1 row: the prologue copy-order class resists a model as it resisted the probes; **5,839 pins in 1,237 rows**. Briefed packs: 14 of 48 rows; the class matters more than the model.

The fifth pack (`r58_order5`, twelve 1-2-pin rows of `CHANGED|5-8`) resolved 5 rows: **5,834 pins in 1,232 rows**, 8 windows and SLUS MATCH. Briefed packs: 19 of 60 rows. A sixth pack (the rest of the small `CHANGED` rows) runs next; the class pool of 1-2-pin rows is the model lanes' working set while the CPU side is exhausted.

Pack 6 (`r58_order6`, the remaining small `CHANGED|3-4`/`5-8` rows) resolved 4 rows: **5,831 pins in 1,229 rows**, 4 windows and SLUS MATCH. Briefed packs: 23 of 72 rows. Pack 7 (`CHANGED|9-16`) runs next; the pack builder is the scratchpad's `build_pack.py <lane> <classes>`.

Pack 7 (`r58_order7`, `CHANGED|9-16`) resolved 1 row: **5,830 pins in 1,228 rows**. The yield falls with the residue size (small `CHANGED` classes 1 in 2 to 1 in 3, 9-16 words 1 in 12): the remaining 1-2-pin pool is mostly larger residues. Briefed packs: 24 of 84 rows.

Pack 8 (`r58_order8`, `CHANGED|9-16` and `BOTH|9-16`) resolved 3 rows: **5,827 pins in 1,225 rows**. Briefed packs: 27 of 96 rows. Packs 9 (the remaining `MOVED|1-2` rows) and 10 (the small `CHANGED` and `RECOLOURED` residues) run next.

Packs 9 and 10: the remaining `MOVED|1-2` rows (non-argument moves) 0 of 12; the small `CHANGED`/`RECOLOURED` residues 5 of 12: **5,822 pins in 1,220 rows**, 11 windows and SLUS MATCH. Briefed packs: 32 of 120 rows. Pack 11 (three-pin rows of the small classes) runs next.

Pack 11 (`r58_order11`, three-pin rows of the small `MOVED`/`CHANGED` classes) resolved 5 rows, 15 pins: **5,807 pins in 1,215 rows**. Three-pin rows of the paying classes pay as well as one-pin rows; the pool by pin count is the next dimension. Briefed packs: 37 of 132 rows.

Pack 12 (`r58_order12`, the recoloured and mixed 5-16-word residues) resolved 3 rows: **5,804 pins in 1,212 rows**. Briefed packs: 40 of 144 rows.

Pack 13 (`r58_order13`, three-to-four-pin rows of the small classes) resolved 3 rows, 9 pins: **5,795 pins in 1,209 rows**. Briefed packs: 43 of 156 rows.

## Round 58, later: the lane corpus mined, and what it paid the same day

Two Opus agents (model routing validated by each quoting its own model line): one audited the 128 lane "general rule" sections against the 68 generators ([the audit](PIN_LANE_RULES_AUDIT_20260519.md): ten unimplemented or narrowed rules ranked, six generators proposed by several lanes that paid little because their rule was too narrow, and the verdict that compositions whose first step looks worse need a pass-stream-ranked search rather than assembly distance); the other works one two-row lane with nine and eight pins of several kinds (`r58_opus1`, report pending). Acted on within hours:

- **Lane harvest audit:** of 795 stale and 406 already-pin-free lane candidates, 9 on still-pinned rows were current, smaller and byte-exact but never landed; 3 landed directly, 5 had been refused for editing the port arm (models flatten the `#ifdef NON_MATCHING` register scaffolding) and `tools/lanes/arm_restore.py` re-inserts those arms: 2 more landed, 3 fail the port build after the restore and stay. **5,789 pins in 1,206 rows.**
- **t74_multiset** (audit gap 1, six lanes: `v = a + b + c` written `v = a + b; v += c` so the destination is multi-set and `birthing_insn_p` stops boosting it): 36 rows / 42 pins in staging from 998 eligible rows, landing as r58t74; in the cascade.
- **t75_returnkept** (gap 6): one eligible row, kept out of the cascade.
- Gap 10 (symbol versus constant, the `-addiu,lui +lui,ori` class, 98 + 62 sites): t29, t54 and t59 all ran on those rows and refused or found nothing, so the gap is inside their candidate menus, not their detectors; the next Opus task.
- t72's dependence guard tightened after an Opus review (compound shifts, embedded increments, globals as memory, indirect calls, cast bases).
- `tools/xform/variant_screen.py`: the probe that found the sched mechanism, promoted; every lane brief now points at it.

**The variety-row Opus lane (`r58_opus1`, 215k tokens):** `dungeon/func_800C78A4` 9 pins to 5 by one joint move: four `ASM_SET` fake arguments and the call `func_800A6508(a, b, c, d)` were the decompiler's reading of live argument registers; the callee is K&R and retail passes nothing (`func_800A6508();`, prototype `()`), audit gap 3. Everything else on the two rows was classified rather than removed, and two classes recur: a **closed constant both stored and passed to the next call** (retail shares one register with the store in the delay slot; gcc rematerialises a second `lui/ori`; fourteen spellings failed, so it is a named open mechanism, not a menu gap), and a **copy or address half that exists only because a pinned hard register blocks coalescing** (the one lever that moved it: staging a value in a local versus writing it inline changes the insn count at scheduling time). Its rule for a several-pins-at-once generator: classify each pin's lone-erasure diff into {arity, symbol, closed constant, coalescing} and drop the arity and symbol groups whole. `t76_arity` implements the arity group (29 rows carry the shape, 83 pins).

**The symbol-versus-constant Opus lane (`r58_opus3`, 200k tokens, six rows of the 160-site class):** one row removed (`dungeon/func_800C96AC`: the page symbol named AND the definition placed where the erased page definition was; t29 had refused because the variable also appears in the port arm). The class splits by retail's register pair: **two registers** (`lui $4 / addiu $17,$4,lo`) is gcc's HIGH/LO_SUM, emitted only by a splitting cell (2.7.2-cdk, 2.8.x), its HIGH register fixed by the statement's LUID; **one register** (`lui $4 / addiu $4,$4`) is an atomic `la` at FSF 2.6.3/2.7.2, which wins only when retail's two words are adjacent and not in a delay slot (maspsx cannot split `la` into a slot). Three of the six rows are one word or a fixed residue from exact at the cdk cell where the pinned text itself is not exact: the cell fails, not the C, so rules 1-2 refuse what clause 4b would accept. Menu extensions for t29/t54/t59: accept parameters and port-arm variables (scored arm only), add a position axis, gate cell switches on the candidate rather than the pinned text (the coherence landing), and pre-screen by rejecting listings that show `la`. Report `work/native_lane/r58_opus3/REPORT.md`.

`t77_symplace` (the exact-address symbol in place, plus the derived-definition form from the Opus lane) over the 103 still-pinned rows of the symbol-versus-constant classes at their recorded cells: 2 rows / 3 pins, as the lane's analysis predicted (most of the class is bound by the cell, not the C; the coherence-style landing at the module recipe is the route for those). A lesson from the same hour: editing `land_lanes.sh` while a landing ran it corrupted that run after its cascade (bash reads scripts incrementally); the next landing's gate covered the affected windows. Never edit a running script.

## Round 59 plan: class-grouped codex packs with solved exemplars

The owner's direction after this wave: groups of 10-20 rows sharing a residue class, briefed with the diffs that made rows of that class byte-exact this week (121 solved rows indexed with their classes), to luna for the small classes and sol for the mid, large and far residues; capacity probed before each launch, every lane landed through the locked pipeline and its port-arm-repaired twin. Five packs are built and queued behind the residues pack: `r59_luna_changed_small`, `r59_luna_moved`, `r59_sol_mid`, `r59_sol_large`, `r59_sol_far`.
