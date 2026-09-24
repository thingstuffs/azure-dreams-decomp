# Active goal (2026-09-24, owner-approved work order)

See [GOAL_TOOLCHAIN_AND_MODULES.md](GOAL_TOOLCHAIN_AND_MODULES.md): SLUS `$gp`
repair, obsolete maspsx pass retirement, one verified module pilot, and explicit
accounting for the three unregistered MAIN routines. The primary agent handles
hard analysis and orchestration; the owner authorizes Sol and Luna delegates for
bounded grunt work. Claude's reset in about three days is a handoff checkpoint.

First execution checkpoint: [SLUS small-data measurements](evidence/fidelity_gp_repair_progress.md).
The isolated generic assembler correction passes 70/70 pinned-version probes and
changes exactly 59/884 SLUS TUs; all 69 affected globals currently have raw-asset
storage and absolute linker names, not C definitions. Five prepared candidates
are genuine-exact and diagnostic-link exact. A three-function owned-data module
now replaces the raw four bytes for D_80080A6C with a real C definition and links
SLUS byte-exact under the corrected assembler (`tools/fidelity/probe_gp_module.py`).
Production module/row/data integration and the other ownership repairs remain
before a global switch. A separate CD-control module source pilot is exact.
The [MAIN coverage audit](evidence/main_kernel_coverage_audit.md)
independently hashes/disassembles all three gaps without claiming C completion.

# Handover (2026-09-24, H28 recovery)

Picked up the interrupted 67-row H28 wave from `r77_opus_h1..h16` after the
compiler investigation. **11 functions moved to CDK, 74 pins removed, 9 newly
pin-free and 2 partial improvements.** Ten candidates recovered from h1-h8;
town/func_800B7CEC newly solved with a packed prefix copy and loop-counter
initialization before the entry test. All affected windows MATCH, SLUS MATCH,
row database OK, all eleven exact under genuine ASPSX with no compatibility
passes firing. `maspsx_dependence` 237 -> 226.

Start at `docs/evidence/r77_h28_recovery.md` and its receipt/queued-screen TSV.
The 40 queued h9-h16 rows were calibrated and screened at CDK (erasure alone:
0/40 exact); only the town prefix row received a completed reconstruction.
Do not label these packs completed. The original cohort still has 58 pinned
rows: two partially improved at CDK, 56 at their original proxy recipes.
Continue the interrupted h1-h8 candidates/dumps and the 39 unsolved queued rows.
The old h1 report predates its exact `C98cdk_p27` result and is superseded here.

# Handover (2026-09-24 00:30Z, round 77 in flight) - fresh-eyes check, then an Opus wave

**PAUSE PIN LANES -> `docs/TOOLCHAIN_FIDELITY_PLAN.md` (owner, 2026-09-24).** When the running r77 lanes finish and land, work that plan (steps 1-5) before any new pin lanes.


**Fresh-eyes check of the round-76 plan (what changed it).**
1. **slus was never offered to a strong lane.** `build_class_pack.py:78` and `ab_plan.py` skip `slus` like the parked
   `ovmovie`, with no recorded reason (round 60). slus rows land through the normal gate (`build_slus.sh` in every
   lander; 72 commits under `src/slus`) and the kit scores them. 89 rows / 306 pins had no kit-era astra/Opus serve.
   Wave 1 includes 4 slus rows (via `--rows`, which bypasses the skip); the auto-selection skip is left in place
   until wave 1 shows the kit works on slus rows.
2. **Pins per Opus lane rise with row size** (r73-r76): about 3-5 on 1-pin rows, about 6 on 2-3-pin rows, 9-16 on the
   5-6-pin partial pool. The 8+ band is 106 rows / 1,408 pins (40% of the rest); astra's cluster pack there took 5
   pins at weight 35 (`r76_astra_b8c_1`, 47 -> 42). So wave 1 leads with the 3-7 band and clone representatives.
   The 1-2 band (430 rows / 510 pins) comes after.
3. **Clone families:** 25 live families / 302 pins. Family 0 (10 members, 95 pins) had a rep no strong lane had served.
   Family 1 (11 x 6 = 66 pins) was served only by astra (r75_astra_p4). Family 18's rep is already pin-free and its
   sibling `80EA3000` failed mechanical transfer. All three are in wave 1. **After the clone lanes land:
   `python3 tools/lanes/clone_transfer.py --lanes r77_opus_c1,r77_opus_c2,r77_opus_c3`** (or the families mode).
4. The r76o overlap candidates were already landed as partial wins; the only pending item was the trade (below).
5. `brief_paragraphs/new_findings.md` was dated 09-21. It now carries round 76's set-exactly-once family, the
   dead-init ruling and the sched2-off signature.

**Split-address "toolchain gap" DISPROVED (Fable sceptic, owner request, 2026-09-24).** The retail split pairs come
from the `2.7.2-cdk` cell (address splitting), not the assembler; ~50 rows / ~125 page-constant pin sites at
non-splitting cells are cell-imitation scaffolding. Four owner decisions follow (maspsx la-splitting passes, slus ASPSX
version, small-extern `$gp` model, recipe route): `docs/evidence/r77_splitaddr_verdict.md`. The ADDR_ALIAS comment in
`src/slus/w_8003D92C.c` is wrong.

**Round-77 levers measured:** clone ports (lane given the solved sibling's base/out/REPORT) ~150k tokens and ~6 min a
lane at 3/3 rows vs ~400k / ~45 min for from-scratch lanes; `tools/lanes/port_candidates.py` finds them,
`clone_wholeport.py` does token-identical siblings mechanically. slus: 4 rows served, 1 pin (the split class). Kit fix:
slus rows had func=None (lab.py crashed on all 556).
Review items (landed through the gate): town/func_80953900 deletes a NON_MATCHING block whose arms both reduce to the
symbol; slus/w_8003E39C removes a $3 pin by reusing the $2-pinned variable; spelling trades in r77_opus_c4 (goto into
block, duplicated tails), m7, p1, m5 (dead init). r77_opus_m6 has an unstaged site-for-pin trade
(`trades/func_81875B38_keep_z_dest.c`, 4 -> 1).

**Landed:** `town/func_8032FD1C` pin-for-flag trade (+`-fno-schedule-insns2`; the current 2-pin text is exact at the
target, so rule 2 holds): 3,512 -> **3,510 / 857**. Ledger kind corrected to `pin-for-flag` by hand.
This is the second adjacent town row with the sched2 signature, after round 73's `func_8032E364`.

**Wave 1 (Opus, Agent tool, 7 lanes, 31 rows, `docs/evidence/r77_wave1_rows.json`):** `r77_opus_m1..m4` (3-7 band,
never strong-served, random within container strata seed 77: 12 dungeon / 4 town / 4 slus), `r77_opus_c1` (family
0 + 1 reps), `r77_opus_c2` (family 2, 18, 9, 10), `r77_opus_c3` (1-2-pin family reps 3/15/4/11/7). `land_finished2`
(pid 536862) lands `r77_*`. Record each lane's usage at completion (`record_usage.py`).
Gemini: at its weekly limit since 16:15Z; `gemini_feed.sh` (pid 1018772) re-probes hourly.
compose2 near-fullB2 finished: 211 rows, 11 wins, 5 h.

# Handover (2026-09-23, round 76) - start here

**State.** Round 76 started at 3,701 pins / 902 rows. The owner's 2026-09-23 ruling ("3706 seems like the more
accurate count") made `pin_census.sites_of` count a pin inside a local macro once per call instead of once per
definition (`docs/evidence/r76_pin_count_discrepancy.md`): 3,701 -> **3,706 / 902** (2 rows affected;
`hidden_asm` wrapper-call bucket 9 -> 0). Landings since (cascade catch-up + composition, clone transfer, cell
scan, the A/B harvest, ongoing model lanes) have taken STATUS.md's "Pin sites now" to **3,529 in 865 rows**
(check `grep "Pin sites now" STATUS.md` for the live figure - it moves under `land_finished2.sh`).

**A/B result (`python3 tools/lanes/ab_report.py --glob 'r76*' --ok-only`, last table).** Exact rate / weighted
cost-per-pin (`config/model_cost_weights.json`, luna=1 unit): claude-opus-5-5 50.0% exact, 0.703/pin, weight 10;
gpt-6-astra 56.0%, 4.507/pin, weight 35; gpt-6-sol 16.7%, 1.842/pin, weight 10; gpt-6-luna 10.0%, 1.670/pin,
weight 1; gemini-3.8-flash-high 8.6%, **0/pin (free this window)**; claude-sonnet-5 **0/30 rows** - not a
solver at this band. Routing for round 77+: **Opus is the 1-7-pin workhorse** (cheapest per pin among the
non-free arms); **astra for clone-family representatives, 8+-pin cluster packs, and rows Opus fails** (second
try); **Gemini (agy) free feed takes everything it can** (`tools/lanes/gemini_feed.sh`, pid/log in
`r76_measurement_protocol.md`, stops on `work/native_lane/STOP_GEMINI_FEED` or a probe hitting the weekly
limit); luna/sol stay weak lanes (cheap top-up only, not primary).

**Mechanism: set-exactly-once (`pin_research_round76_move_table.md`).** An `ASM_KEEP`/`ASM_REG` pin fakes a
SECOND set of a pseudo (`REG_N_SETS==1` gets sched.c's `birthing_insn_p` boost and local-alloc's REG_EQUIV
live-length doubling). 25 of the harvest's 43 removed pins are this family. Built/extended generators:
**t118_setonce** (fold an in-place update chain to one set), **t119_deadinit** (owner-approved: a dead `= 0`/
`NULL` declaration initializer is ordinary C, not a dead-store violation), **t120_unvolatile** (drop a
volatile access together with its register pin), t69/t111/t113/t115/t94 extended with UNPIN_REST/HOIST/
ADDRCARRIER/CALLCOPY/CASTUSE levers; **t121_barrierstrip** (probe: strips one-trip `do{}while(0)` + barriers,
0 standalone exact, 2 wins composed with t118/t119/t120, not added to the cascade).

**Tooling fixes this round:** `cascade_list.py` (the one EXTRA_T parser; repaired `cascade_extra.txt` sed
corruption, added t100/t103-t117); `compose2.py` (depth-2 generator composition, now with `--pinfree` for
stage-1 candidates that reach zero pins); `clone_transfer.py` v2 (code-line alignment) + `clone_families.py`
(union-find over 902 rows, 194 pairs, `ledger/clone_families.jsonl`); `served.py` tier guard; `lane_limit.py`;
`record_usage.py`; `lane_cap.py`; cluster packs (`--cluster N-M`).

**Running at hand-back:** `tools/lanes/land_finished2.sh` pid 536862 (lands every `r7[0-9]_*` lane, 15 min
cycle); the Gemini free feed (`gemini_feed.sh`, pid 1018772); `compose2.py r76_compose_near_fullB2 --near 2`
pid 2292536 (depth-2 composition over ~211 near-miss rows, est. 3h+, lands itself). Check liveness with
`ps -p <pid>` before relying on any of these.

**NEXT:**
(a) An Opus wave on the never-strong-served pool (`python3 tools/lanes/served.py --strong-kit --count`) and
the clone-family representatives (`ledger/clone_families.jsonl`, 26 families / 92 rows / 358 pins projected
324 after in-flight transfers); astra as the second try on every Opus miss.
(b) Land the pending recipe trade `town/func_8032FD1C` at `+-fno-schedule-insns2` (found by lane
`r76o_opus_b37`, `cells/town/func_8032FD1C.c`; rules 1-2 hold) through the normal trade lander.
(c) L4 module placement is untouched: all rows still `not_in_module`.

Full detail: `docs/evidence/r76_cascade_compose.md`, `r76_pin_count_discrepancy.md`, `r76_clones.md`,
`r76_cells_small.md`, `r76_measurement_protocol.md`, `pin_research_round76_move_table.md`. Everything below
the previous two dated blocks moved to `docs/handover_archive/HANDOVER_through_20260922.md`.


# Handover (2026-09-23 07:30Z) - round 73/74/75 done: 4,322 -> 3,776 pins, 1,053 -> 911 rows in one night

Read the 2026-09-22 23:55Z block and the 03:40Z / 04:35Z updates below for the design. Outcome (ab_report --ok-only over
r73_*/r74_*/r75_*): **Claude Opus 5.5 lanes** (Agent tool, same kit pack) 215 rows / 132 exact / 251 pins staged;
**gpt-6-astra** 97 / 70 / 154; **gpt-6-sol** 106 / 20 (19%; 30-33% with `brief_paragraphs/residual_to_form.md`, now in
the brief); **gpt-6-luna** 70 / 10 (14%). Routing that held: Opus and astra on 1-6-pin rows (Opus ~70% on 1-pin rows,
50-80% on 3-4-pin, 2-5 rows and 9-17 pins per pack on the partial-residue pool at 5-6 pins; astra 22/30 there);
sol6+v3 as a cheap 30% lane on 3-pin rows; luna6 not worth its tokens; nobody on the astra-failed 11+ residue (0/5) or
the 2-pin dungeon page-constant tail (~20%; cse folds the integer, symbols need a split-address cell). Four recipe
trades landed through `land_coherence.sh` (now LAND_ISOLATED-aware, ROUND/date from env): main/func_8001270C ->
plain 2.8.1; dungeon/func_81811EC0 -> 2.8.1-G0 -mno-split-addresses (byte-neutral, kind corrected by hand);
town/func_8032E364 +-fno-schedule-insns2 (byte-neutral); dungeon/func_810830BC 2.7.2 -> 2.8.1-G0 (coherence, matches
its three twins). Harvests: t103-t113 built (docs/evidence/pin_research_round73_move_table.md; harvest 3 running as
this is written - lanes r73_h3_*, landed by land_finished2). Kit: lanekit/diff.py, dump.py, `lab.py --grid`,
`lab.py cellscore`/--cfg (docs/evidence/lane_tool_harvest_20260923.md: 26/23/21/3 lanes had rebuilt them). Withheld:
`r73_opus_a2/exp/rejected_fakedep/func_8194CF00.c` (identity helper). Review items: `r73_opus_s11` deleted an emptied
`#ifdef NON_MATCHING` declaration block (func_800C30E4), `r73_opus_s20` rewrote a pin-only NON_MATCHING arm
(func_80096134), `r73_opus_p2` dropped a `.set` alias (func_81844800) - all went through the landing gate.
**Next:** partial-residue pool (100 rows at 4-6 pins unserved; `scratchpad/partial_pool.json` rule: live pins, a
candidate somewhere, never Opus-served) for Opus/astra; 64 one-pin retry rows for Opus; land the harvest-3 lanes;
commit config/ tools/ docs/ (the snapshot job commits src/ ledger/ STATUS only). Every pack's rows:
`docs/evidence/r73_ab_rows.json`; pool logs `work/native_lane/_r73_logs/`.

# Handover (2026-09-22 23:55Z) - round 73 in flight: gpt-6-sol / gpt-6-luna A/B

Codex capacity returned early (all four models answer; the 09-26 date in the old error text was wrong). The owner
asked to try the new, much cheaper `gpt-6-sol` and `gpt-6-luna` before spending astra. Three pools are running with
`--no-land` (`tools/lanes/land_finished2.sh`, pid 536862, lands every finished lane every 15 min):
`R73SOL6` (gpt-6-sol, c=4, 11 packs), `R73LUNA6` (gpt-6-luna, c=4, 14 packs), `R73ASTRA` (c=2, 2 control packs);
logs `work/native_lane/_r73_logs/pool_r73{sol6,luna6,astra}.log`, wave script `tools/lanes/r73_ab_wave.sh`, rows
`docs/evidence/r73_ab_rows.json` (3-7-pin band alternated by rank between sol6 and luna6; 8-19-pin band 2:1
sol6/astra; 1-2-pin band luna6; every row a retry of 5.6-era lanes with no candidate anywhere, never served by astra).
Read the result with `python3 tools/lanes/ab_report.py --glob 'r73_*' --ok-only`; baselines (same tool over
`r7[012]_kit*`, `--ok-only`): gpt-5.6-sol 29/95 rows exact (30.5%), gpt-6-astra 96/120 (80%).
Tooling this round (Opus 5.5): `sol6`/`luna6` keys in `launch_lane.sh` + `pool.py`, `pool.py --kit`, `ledger.py`
tiers sol6/luna6 and an ANSI fix for the `model:` header (codex 0.154+ writes it bold; every recent lane had lost its
model in the ledger), `tools/lanes/ab_report.py` + tests (74 pass). The 15 stale unrun kit packs (rows landed since)
were moved to `work/native_lane/_unrun_stale_20260922/` because `served.py` counts an unrun pack's rows as served.
`reset_watch2.sh` (would have relaunched astra + 5.6-sol on those packs) was killed.


**03:40Z update (round 73/74 in flight).** Codex A/B on matched 3-7-pin retry rows: gpt-6-sol 4/40 rows exact, gpt-6-luna
~5/55, gpt-6-astra 5/10 on the same band (and 4/7 on 8+); gpt-6-sol 0/11 on 8+. Claude Opus 5.5 run as lanes through the
Agent tool (same kit pack, `codex.log` carries `model: claude-opus-5-5[1m]`): 1-2-pin band 9/10 rows (17/20 pins), 4-pin
band 7/10 rows (21/40 pins) - the best rate per row tonight; one candidate withheld as a fake dependency
(`r73_opus_a2/exp/rejected_fakedep/func_8194CF00.c`, identity inline helper). Running: R74ASTRA (40 rows, 3-7 band),
R74SOL6V3 (gpt-6-sol + `brief_paragraphs/residual_to_form.md`, A/B vs tonight's 10%), R74ASTRAPRE (astra on sol6-failed
rows with sol6's diagnosis appended), Opus lanes r73_opus_a3-a6 / s3-s6 / h1 (h1 = astra-failed 11-12-pin rows), an Opus
harvest agent (round-73 move table + generators -> `r73_h_*` lanes, landed by land_finished2), a Sonnet check of the
`main/func_8001270C` pin-for-flag trade (plain 2.8.1; record prepared under `r73_opus_s2/exp/1270c/`). Miner's verdict on
the cheap models: `docs/evidence/lane_log_mining_gpt6_20260923.md`. Pins 4,322 -> 4,264 (03:15Z landing). Row plan for
every lane: `docs/evidence/r73_ab_rows.json`.


**04:35Z checkpoint.** Pins 4,322 -> 4,047 in 997 rows (04:08 landing batch of 18 lanes). Decision matrix: Opus 5.5 lanes 65%
of rows exact, astra 68%, luna6 15%, sol6 13% -> 30% with `brief_paragraphs/residual_to_form.md` (adopt for cheap lanes;
pool `R74SOL6V3B` running it on the partial-residue pool's 3-pin rows). Pre-diagnosis for astra: no lift, dropped. Harvest 2
built t109-t113 (43 rows / 55 pins staged in `r73_h2_*`, land automatically). Opus is now on: 1-pin rows (s16/s17), the
partial-residue pool (p1/p2: rows with an earlier partial win, pins left), a8/s14 finishing. The 2-pin dungeon tail of the
1-2 retry pool is hard (page-constant pins: cse folds the integer, symbols need a split-address cell). Full lane list:
`docs/evidence/r73_ab_rows.json`; harvest-3 notes `work/native_lane/_r73_logs/harvest2_notes.md`.


Everything before the 2026-09-23 07:30Z block: docs/handover_archive/HANDOVER_through_20260922.md
