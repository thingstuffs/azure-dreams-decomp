# Round 78 wave record (2026-09-27 23:15Z - 2026-09-28 ~01:40Z)

Decision record: [r78_restart_decision.md](r78_restart_decision.md). Rows per lane: `r78_wave1_rows.json`.
Start commit `a0b30a59` (dirty kit/doc diff reviewed and committed as `3f145e94`); end commit: see git log (`r78:`).

## Objective and lanes

Three families: (1) fresh never-served 3-7 rows (Opus w1/w2), (2) H28 continuation (Sol h10, then Opus
fresh-eyes c3/c5/c6/c7/c8 on interrupted H28 lanes), (3) cheap tiers (Gemini g1/g2 on 1-2 rows, Luna 6 on
reduced rows). Owner question added mid-wave (2026-09-27): do caps cut lanes off close to a solution, and does
a fresh look at where a lane got to help? -> cut-off experiment (`tools/lanes/cutoff_report.py`).

Models: claude-opus-5-5 (Agent tool, effort = agent default), gpt-6-sol / gpt-6-luna / gpt-6-astra (codex,
reasoning xhigh), gemini-3.8-flash-high (agy). No substitutions. Sonnet not used (plan).

## Pins

3,098 / 765 at pickup -> **3,054 / 756 landed so far**; staged and queued for the lander: c4 (1), c5 (8),
c7 (10) = 19 more (-> ~3,035). All landings through the serialized land lock with every affected window and the
SLUS SHA-1 image MATCH (GATE_RC=0 each time). No census/reclassification change; all figures are removals.

| lane | model | rows | exact/partial staged | pins | tokens (meter) | min |
|---|---|---:|---|---:|---:|---:|
| r78_recover | (staged work) | 3 | 3 | 9 -> 4 | 0 | - |
| r78_opus_w1 | opus | 5 | 2 + 1 SLUS by hand | 9 -> 0 | 252,841 A | 23 |
| r78_opus_w2 | opus | 5 | 2 (1 coherence cell trade) | 7 -> 0 | 262,044 A | 25 |
| r78_opus_c2 | opus | 3 | 1 partial | 5 -> 3 | 291,488 A | 28 |
| r78_opus_c3 | opus | 2 | 2 partial | 42 -> 33 | 301,471 A | 28 |
| r78_opus_c4 | opus | 4 | 1 | 1 -> 0 | 252,923 A | 26 |
| r78_opus_c5 | opus | 2 | 1 partial | 16 -> 8 | 303,974 A | 27 |
| r78_opus_c7 | opus | 2 | 1 partial | 13 -> 3 | 269,283 A | 23 |
| r78_opus_c1 | opus | 1 (F0) | 0 (mechanism) | - | 325,966 A | 33 |
| r78_opus_c6 | opus | 2 | 0 (mechanism) | - | 298,150 A | 33 |
| r78_opus_c8 | opus | 2 | 2 partial | 19 -> 6 | 338,035 A | 38 |
| r78_opus_reg8 | opus | 5 | 1 + 1 partial | 9 -> 2 | 258,450 A | 22 |
| r78_sol6_h10 | sol 6 | 5 | 2 partial | 7 -> 4 | 414,446 C (250,713 + extension) | 14 + ext |
| r78_sol6_fresh1 | sol 6 | 3 | 0 | - | 255,552 C | 23 |
| r78_luna6_red1 | luna 6 | 5 | 0 (cap misset) | - | 151,896 C | 12 |
| r78_luna6_red2 | luna 6 | 5 | 0 | - | 314,752 C | 45 |
| r78_astra_f0 | astra 6 | 1 (F0) | 0 (7 exact texts self-rejected) | - | 409,625 C | 47 |
| r78_agy_g1 / g2 | gemini | 10 | 3 | 5 -> 1 | unmetered | 12 each |

Meters. **A** = Agent-tool `subagent_tokens` (approximately final context; a LOWER bound on consumption).
**C** = codex rollout `input - cached_input + output` (lane_cap.py), read from the rollout because capped lanes
never print codex's exit total. A and C are different units; do not rank across them. Gemini unmetered.
Coordinator (this session) and advisor usage: unmeasured per lane. **Owner-read account meters, 2026-09-28 ~03:45Z: Claude 9% used, Codex 3% used** (whole session to that point, coordinator + all lanes): ~121 pins landed + ~15 queued -> ~14 pins per 1% Claude; Codex ~4 pins for 3%. Quota: codex weekly 0% -> 2% (resets 2026-10-03
23:05Z, no concurrent use seen); Gemini probe OK throughout; Claude: no meter.

Opus: ~2.83M A-tokens over 10 lanes for 43 pins landed or staged (~66k A-tokens per pin, zero-yield lanes
included). Codex: ~1.55M C-tokens for 3 pins (Sol) - Sol/Luna were served the hardest leftovers (plateaued or
reduced rows), so this is not a model ranking.

## Cut-off experiment (owner question)

History (r60-r77 lab logs, 1,202 row-serves): lanes that stopped near (unstaged state at listing distance <= 4
with fewer pins) were rarely still improving: finished 56 of 417, quota-cut 4 of 45, interrupted 1 of 4. Caps
themselves had almost never fired before this round.

This round:
- **Extend arm** (resume the same codex session, +150k): r78_sol6_h10, 5 rows, 3 at distance 2 when cut ->
  **0 pins**. The resumed session re-sends its whole context: ~60 trials for 150k vs 176 for the first 250k.
- **Fresh-eyes arm** (new context + prior evidence packet, `continuation_notes.py`, `fresh_eyes` brief):
  Opus c1-c8: 6 of 17 rows reduced, **30 pins beyond the prior floor**; Sol fresh1 (same rows as the failed
  extension) 0/3; Luna red2 0/5; Astra F0 0/1.
- Honest reading: fresh eyes paid **with Opus**, not with Sol/Luna, so arm and model are confounded; and the
  F0 lanes show a third pattern (accumulated evidence -> a measured mechanism, not yet a landing). Sample sizes
  are one to eight lanes per cell: unmeasured as a controlled result. Keep alternating arms on future cut lanes.
- Every Opus fresh-eyes gain came from overturning a named prior assumption (reports quote which one).

## Reusable findings

1. **Spill-register / rematerialisation pins** (c3, c5, c6, c7 independently): `ASM_REG("$8"/"$10"/"$12")` +
   keeps imitate reload - spilled pseudos rebuilt in the first free spill register, or a REG_EQUIV symbol
   address rematerialised. Fix: real params/tables/symbols, plain locals that spill, drop all bindings together.
   Brief paragraph `spill_register.md`; family test lane r78_opus_reg8 (5 never-served `$8` rows) running.
   Population: 67 `$8` pins in 58 rows (+ `$10`/`$12`).
2. **Volatile store blocks the delay-slot filler** (c4, slus/w_80053CFC): reorg's backward search stops at a
   volatile store; store through the plain pointer already passed -> `li $a0` fills the jal slot.
3. **F0 clone family (11 rows, 66 pins)**: mechanism measured (c1): the three consumer-less colour reads,
   placed by sched1; Astra reproduced retail with discarded two-sided clamps (7 byte-exact texts) and rejected
   them itself as artificial dead computation. Kept at `work/native_lane/r78_astra_f0/diag/rejected_clamps/`.
4. "Page bases" that are symbol addresses (c7), literal scratchpad args are cse, not copies (c3).

## Later in the round (2026-09-28 03:30Z - 04:40Z)

- **Astra on the spill family** (r78_astra_sp12/sp13, 3 rows each, 367k + 504k C-tokens): 15 pins
  (dungeon/func_8185CFD4 13 -> 3; four rows -1/-2). Codex weekly meter 3% -> 6% over Astra x2 + the Sol census:
  ~5 pins per 1% of a quota otherwise idle. Decision: Astra becomes a production tier (2 concurrent lanes, 750k /
  90 min caps) on rows Opus reduced or left near (different tier = not a repeat); r78_astra_n1/n2 launched.
- **Cross-jump census** (r78_sol6_xjump, 184k C-tokens): of 43 live "basic-block layout" pins only **3** are
  jump2 cross-jump blockers (dungeon/func_80BA9094:59, dungeon/func_8133AD74:626,643); 10 sched, 8 cse, 6 dbr,
  5 combine, 5 rtl, ... A clean negative: no toolchain question to open. Four pins erase to listing distance 0
  but are NOT byte-exact (verify totals 5-20): their effect is below the cc1 listing; not free removals.
  11 UNRESOLVED comments sit on lines with no live pin (stale; listed in the census REPORT.md).
- **Near-miss conversion** (r78_opus_c13): dungeon/func_800A1AD4 17 -> 7 by giving the NEIGHBOUR of a
  combine-merged argument insn launch priority (single-set local, birthing_insn_p); brief paragraph
  `near_miss.md`; c14/c15 apply it to the next highest-stake near misses (cutoff_report ranking).
- Fresh never-served 3-7 lanes decayed: w1 9, w2 7, w3 5, w4 3, w5 2, w6 4 pins.

## Process review at the owner's 05:50Z check-in (Claude 13% / Codex 10% used)

Rates since the 09% / 3% reading: ~80 pins for +4% Claude (~20 pins per 1%), ~20 pins for +7% Codex (~3 per 1%).
Yield by lane mode (lander records): Opus big-row fresh-eyes 6.1 pins/lane (51k A-tokens/pin), Opus spill family
5.1 (57k), Opus near-miss 4.2 (67k), Opus fresh 3-7 rows 2.8 (97k); Astra spill 7.5, Astra near/big 1.7; Gemini
1.2 (near free); Sol/Luna pin lanes 0.25.
**Adopted routing:** Opus default = 2-row big-row (8+) packs or family packs with exemplars; fresh 3-7 packs
demoted. Astra on family-shaped work with exemplars. Sol/Luna: no pin lanes (Sol keeps bounded census/tooling).
Gemini keeps feeding 1-2 rows.
**Readability is now the larger debt** for a shareable tree: m2c placeholder names in 2,692 rows (49.7% of
bytes), gotos 1,599 rows, address-named local structs 3,140 rows; only 21.7% of bytes are fully clean. 2,382
pin-free rows carry m2c names (1,896 <= 600 B). Bounded test: gpt-6-luna `agent_task.py --mode readability
--batch 10` on 20 pin-free rows (the Sep 8 pilot measured ~13k input / 2k uncached tokens per row), staged
without --commit for review before any scaling.
**Correction after the test:** the STATUS "m2c local names" metric counted comments (`/* arg0 in func_X */`
struct notes): 2,687 -> **789** rows in code (status.py fixed; clean-shape rows 4,271 = 32.3% of bytes, not
21.7%). Of those, only **191** rows have placeholders outside `extern` prototype parameter names (594 rows'
only placeholders are callee prototype parameter names - harmless). Luna readability on 20 real rows: 12
accepted, 2 fully renamed; the rest were prototype names it correctly left. Not scaled: local naming is nearly
done. The real readability debt is 1,599 goto rows and 3,140 address-named local struct types (+ unk_XX
fields); those need understanding and byte-exact control-flow work (Opus/Astra family packs), and struct naming
needs a header/type design decision - queued for the owner, not started. Staged Luna outputs remain in
ledger/agents/out/gpt-6-luna-xhigh-r78read*/ (not landed).

## Owner decisions queued (not taken while the owner is away)

- **F0 discarded clamps**: land the reconstruction (5 of 6 pins on 11 clones, ~55 pins) with a visible comment
  and a trade record, or keep treating unused clamp assignments as fake dependencies? Retail's lbu reads have no
  consumer, so some dead computation existed; the specific clamp is invented. Coordinator + Astra: not landed.
- dungeon/func_800957B8 5 -> 1 (r78_opus_c16, held in its lane's held/): byte-exact only because a shrunk
  `tile_info[4]` lets the callee read its 5th halfword from a spill slot - an out-of-bounds read that imitates
  the stack layout. Coordinator did not land it; landable form needs the real 5-element record.
- r77_opus_m6 site-for-pin trade on dungeon/func_81875B38 (4 -> 1): still unstaged.

## Process changes adopted (each enforced in code, not prose)

- Lockstep port-arm edits land (`pin_census._arm_lockstep_decls`, 9 tests).
- Caps default ON and price-scaled per model (`config/lane_caps.json`, `launch_lane.sh`); a capped lane gets a
  `last_message.txt` stub so the lander lands its staged partials (`lane_cap.py`).
- `build_class_pack.py` `--rows` with no class no longer crashes; exemplars refreshed at round start.
- Agent lanes write reports with a Bash heredoc (the Write tool refuses subagent report files).
- `cutoff_report.py`, `extend_lane.sh`, `continuation_notes.py`, brief paragraphs `fresh_eyes`, `f0_mechanism`,
  `spill_register`.

## Next bounded tasks

1. Land c4/c5/c7 (lander), then c8/reg8. If reg8 pays, build a spill-register generator or class pack over the
   58 `$8` rows (Luna for the known shape, Opus for the misses).
2. Continue H28 fresh-eyes on the remaining interrupted rows (h5-h8), and the reduced rows c3/c5/c7 left
   (800C9858 22, 81912154 11, 800969CC 8, 8197C800 3) - reduced source is a new state.
3. c4's delay-slot rule: count rows with a constant call argument pinned next to a volatile store before a call.
4. **jump2 cross-jump blockers** (r78_opus_c8): the last fence on dungeon/func_80284BEC and the state_2
   barrier on dungeon/func_818E6800 exist only to stop jump2 cross-jumping identical blocks retail keeps
   separate. Check the census for fences whose erasure residue is a cross-jump merge, then test whether
   the real toolchain's find_cross_jump differs (bounded experiment) before sending more C spellings.
5. Sol/Luna: route to known-shape family packs (spill-register, symbol-page) rather than plateaued leftovers.
