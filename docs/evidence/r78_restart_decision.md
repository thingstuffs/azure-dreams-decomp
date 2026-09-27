# Round 78 restart decision record (2026-09-27, Claude Opus 5.5 coordinator)

Follows [the restart plan](../CLAUDE_CODEX_RESTART_PLAN_20260927.md). The owner is unavailable; routine
scheduling decisions below are taken without asking, per the plan.

## Verified state at pickup (23:15Z)

- Start commit `a0b30a59`; the pending lane-kit/doc diff was reviewed (brief, TOOLS.md, agent prompt link the
  new `tools/learnings/pin_removal_possibilities.md`; 45 lanekit tests pass) and committed as `3f145e94`
  together with the plan (one private path scrubbed for the pre-commit hook).
- Live census recomputed from `src/` with `pin_census.sites_of`: **3,098 sites / 765 rows** = STATUS.
- `served.py --strong-kit`: 610 rows / 2,351 pins not strong-served at current text (440 never, 170 older
  text). The other 155 rows / 747 pins were served by a kit-era strong lane at their current text (the tier
  guard's exclusion), not a hidden population.
- Workers found: `land_finished2.sh` pid 536862 (15-min cycle, lands `r7[0-9]_*`, idle "nothing to land"
  since 09-24); an interactive `codex` (pid 1229483, the owner's, idle since 12:07Z) left alone; a
  scratchpad `autocommit.sh` (src/STATUS/ledger only). `gemini_feed.sh` is no longer running.
- Meters: Codex weekly window **0% used**, resets 2026-10-03 23:05Z (rollout `rate_limits`; plan pro, no
  credits). Gemini (agy) probe OK, no numeric meter. Claude: no meter available - **unmeasured**.
- `r77_cdk362` / `r77_cdkmod` / `r77_step4` "fresh" candidates are already-landed byte-neutral recipe moves
  (text unchanged, so `.base_sha` still matches): nothing to recover there.

## Staged-work recovery (plan priority 1): landed, 5 pins

`r78_recover` (land_lanes.sh, isolated, 2 windows + SLUS MATCH, GATE_RC=0): **3,098 -> 3,093 / 764**.

| row | pins | origin | why it had not landed |
|---|---|---|---|
| dungeon/func_818694D4 | 3 -> 1 | r77_opus_c5 | refused at its 09-24 landing, then marked seen; passes every check now |
| dungeon/func_8008A31C | 5 -> 3 | r77_opus_m7 | lockstep edit of a port arm; the lander had no rule for it (below) |
| dungeon/func_800B89C0 | 1 -> 0 | r76_gemf_w_11 | left a now-dead `#ifdef NON_MATCHING zero_result = 0;` block; retired by hand |

Deferred: `r77_opus_m6` site-for-pin trades on `dungeon/func_81875B38` (4 -> 1) - a trade needs the trade
ledger and review; not in this wave.

## Enforcement audit and fixes

- **Lockstep port-arm edits** (owner ruling 09-22; the lane prompt already allowed them) were refused by
  `pin_census.landing_refusal`. New `_arm_lockstep_decls`: a port-arm edit lands when it is mirrored in the
  matching arm, or is a plain declaration of a variable removed everywhere; `#if 0` text unchanged; the port
  front end still runs. Tests: `tools/tests/test_landing_lockstep.py` (9). History: 54 NON_MATCHING refusals
  over 19 rows in the lane journals.
- `build_class_pack.py` crashed on a `--rows` pack with an empty class argument (exemplars never written):
  fixed. The exemplar index was 6 days stale; `refresh_exemplars.py` rebuilt it (434 -> 454 records).
- `build_ovl/tools` had drifted from `tools/gate`; `mk_ovl_root.sh` rerun before launch.
- Caps: Codex/agy lanes launch with explicit `LANE_TOKEN_CAP` / `LANE_WALL_CAP` (below). **Claude Agent
  lanes have no hard cap**: the prompt carries a 150-tool-call checkpoint (stated as such, not as a cap) and
  the coordinator records `record_usage.py` at completion; `subagent_tokens` is a final-context lower bound.
- Agent prompt (`tools/lanes/agent_lane_prompt.md`): states the lockstep/retirement rule precisely, that a
  partial byte-exact reduction is a landing, and the checkpoint budget.

## Wave 1 (rows: `r78_wave1_rows.json`)

Two priorities: (1) fresh rows in the best-paying family (never-served 3-7 band; r77 Opus 71/106 exact);
(2) resume H28 on its queued, never-launched rows. Four lanes, 20 rows, ~72 pins:

| lane | model / effort | rows | band | cap |
|---|---|---|---|---|
| r78_opus_w1, r78_opus_w2 | claude-opus-5-5, Agent tool | 5 + 5, seed 78, stratified 6 dungeon / 2 town / 2 slus; none ever served by any lane | 3-7 | 150-call checkpoint (not a cap) |
| r78_sol6_h10 | gpt-6-sol, xhigh | H28 queued h10 + one h11 row (the tier guard refused 80BAF094) | 3-4 | 250,000 tokens / 45 min |
| r78_agy_g1 | gemini-3.8-flash-high | 5 never-strong-served 1-2 rows, tier-guard clean | 1-2 | 90 min wall |

Claude concurrency: coordinator + advisor + 2 lanes = 4 of 5. Codex 1 of 3 (Astra held). Gemini 1 of 1.
Landing: `land_finished2.sh` picks up `r78_*` lanes when `last_message.txt` appears (serialized land lock).
Review after the wave: expand only the paying family; stop a family with no landing and no reusable finding
after four comparable lanes.
