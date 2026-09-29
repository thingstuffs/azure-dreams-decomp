# Round 79 wave record (restart plan, continued autonomously 2026-09-28/29)

Plan: docs/CLAUDE_CODEX_RESTART_PLAN_20260927.md. Previous round: evidence/r78_wave1_report.md.

## Start (2026-09-28 23:37Z)

- Start commit `9d2eb009` (Astra b11 + phase-10 type sample committed; 2,787 pin sites in 735 rows).
- In flight at start: type consolidation phase 10 full apply (286 rows; holds the landing lock, so lane landings queue
  behind it). Wave rows exclude its manifest (work/native_lane/r78_types_p10/cand10/MANIFEST.tsv).
- Meters: Codex weekly 21% used (last rollout read 16:16Z; nothing ran between then and launch, so it stands as the
  launch value), resets 2026-10-03 23:05Z. Gemini: no numeric meter. Claude: no meter available.
- Pool (served.py --strong-kit, current text): 674 rows / 2,531 pins not served by a strong lane at their current
  text; never served: 334 rows / 641 pins (1-2: 273/361, 3-7: 60/272, 8+: 1/8); older-text 8+: 81 rows / 1,111 pins.

| lane | model | rows (pins) | shape | cap |
|---|---|---|---|---|
| r79_astra_b1 | gpt-6-astra xhigh | 819B3414 (35), 818F2800 (32) | big-row continuation (r70_kit_astra1 prior), fresh_eyes + spill + near_miss | 750k / 90 min |
| r79_astra_b2 | gpt-6-astra xhigh | 800CDFD8 (30), 818CFB74 (30) | same | 750k / 90 min |
| r79_astra_b3 | gpt-6-astra xhigh | 807B0B3C (27), 80DB9000 (27) | same | 750k / 90 min |
| r79_opus_w1 | Agent opus | 81008664 (22), 81905FD0 (22) | big-row continuation (r70_kit_astra3 prior) | 150 tool-call checkpoint |
| r79_sonnet_s1 | Agent sonnet (owner: Sonnet 5.5 may be live) | 8009F018, w_80052A90 (7), 80092824, 807B040C, 80EB751C (6) | never-served 3-7 pack, same shape as Opus w-lanes (baseline 2.8 pins/lane) | 150 tool-call checkpoint |
| r79_agy_g1 | gemini-3.8-flash-high | 5 never-Gemini-served 2-pin dungeon rows | 1-2 known shapes | 90 min |

## Decisions taken (owner delegated)

- **F0 discarded clamps: rejected** under charter rule 3 (dead assignments between statements); open item closed as
  decided. Reopen only with a real consumer for the three colour reads.
- Sonnet probe: one lane only, model ID quoted in its report; scale only if it reports Sonnet 5.5 AND pays at or
  above the Opus fresh 3-7 baseline (2.8 pins/lane) on a second lane.

## Results (lanes ended 2026-09-29 00:16Z)

| lane | model (quoted) | rows | staged (pins) | measured tokens | minutes |
|---|---|---|---|---:|---:|
| r79_astra_b1 | gpt-6-astra xhigh | 819B3414, 818F2800 | 35->34, 32->31 | 233,353 C | 21 |
| r79_astra_b2 | gpt-6-astra xhigh | 800CDFD8, 818CFB74 | 30->29, 30->29 | 312,651 C | 30 |
| r79_astra_b3 | gpt-6-astra xhigh | 807B0B3C, 80DB9000 | 27->26, 27->24 | 319,531 C | 39 |
| r79_opus_w1 | claude-opus-5-5[1m] | 81008664, 81905FD0 | **22->10**, 22 open | 293,995 A (87 tool uses) | 30 |
| r79_agy_g1 | gemini-3.8-flash-high | 5 never-Gemini 2-pin rows | 0 | unmetered | 30 |
| r79_sonnet_s1 | claude-sonnet-5 (NOT 5.5) | 5 never-served 3-7 rows | stopped at ~2 min | - | 2 |

C = codex uncached+output, A = Agent-tool figure (final-context lower bound): different units, not ranked.
Codex weekly meter 21% -> 24% over the three Astra lanes (~866k C-tokens, 8 pins): ~2.7 pins per 1%, half of
round 78's big-row rate. These six rows were the top of the pool BECAUSE they had resisted Astra since r70 (41 ->
35 pins over several lanes); Astra's 1-3 pin partials on them are consistent with that. Opus on an r70 row of the
same class removed 12 by overturning the r70 lane's scaffolding (volatile entity param + `locals` stack struct +
`$8` carrier + `attempts -= 1/+= 1` pairs = reload of spilled pseudos, loop.c hoists and reorg's add-undo; one
keep relocated, still counted). Census: the volatile-param form is unique to that row; its general form is the
known spill-register family (61 rows still carry `$8`/`$9`/`$10`/`$12` pins).

**Improvement adopted / next test:** for rows first reduced by r70 Astra lanes and now plateaued under Astra,
route the next serve to Opus fresh-eyes (tier change, prior-scaffolding audit) rather than a further Astra
continuation; the prebuilt r79_astra_b4-b6 are this same class - on pickup, either launch them as Opus lanes
(rebuild with --tier opus) or keep one as Astra to test the claim. One observation, not a controlled result.
Gemini 0/5 on never-Gemini 2-pin rows (after 3/5 lanes paid in r78 on easier rows): pause Gemini pin lanes on this
pool until a known-shape family pack exists.

## End (2026-09-29 ~04:00Z)

Pins 2,787 / 735 -> **2,762 / 735** (-25, all removals landed through the lander with window + SLUS gates;
no newly pin-free rows; no census reclassification). Phase-10 types (286 rows) landed pin-neutral.
Landing incident: the b3 landing spun 2h+ in the cascade's t2_pins on dungeon/func_807B0B3C - three pins inside a
macro expansion (FINISH_GLOBAL_TABLE) are not erasable, the unchanged text verified exact and held the loop index.
Fixed in 6c78cac0 (t2_pins; same guard in t16/t16b/t18); the killed sweep's rows were re-swept by the fixed code.
Adopted improvement: that fix (enforced in code). Workflow: see routing note above (r70-plateaued big rows -> Opus).
