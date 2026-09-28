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
