# Round 80 wave record (post-restart pickup, 2026-09-29)

Previous round: evidence/r79_wave_report.md (closed at f5c32120, 2,762 pin sites in 735 rows).
Goal (owner, 09-29): pick up from round 79 once its landings finish, try Sonnet 5.5, keep reducing pins to 0 and
continue the consolidation/cleanup so the source is byte-exact AND something to be proud to share.

## Start (2026-09-29 ~03:20Z)

- Restart condition met: the Agent `sonnet` alias now resolves to **claude-sonnet-5-5** (probe agent quoted
  "Sonnet 5.5 ... claude-sonnet-5-5"). The r79 lander finished r79_astra_b3 at 03:17Z (LAND_GAP_END fin0049).
- Prebuilt packs checked against live src (all 11 rows' base copies identical to src/ after phase 10): no rebuild.
- Routing per the r79 record's recommendation (r70-plateaued big rows -> Opus fresh-eyes; keep one Astra to test
  the claim): b4 stays Astra, b5/b6 renamed to Opus Agent lanes (same brief; lane paths rewritten).
- Phase-11 brief: the six b4-b6 rows appended to its busy list before launch.

| lane | model (quoted in codex.log) | rows | shape |
|---|---|---|---|
| r79_astra_b4 | gpt-6-astra xhigh | 802835B8 (24), 8008EE88 (22) | big-row continuation (Astra arm of the tier test) |
| r79_opus_b5 | claude-opus-5-5[1m] | 800AFA68 (20), 800C4A80 (19) | same pack, Opus fresh-eyes arm |
| r79_opus_b6 | claude-opus-5-5[1m] | 80F36D0C (19), 81978428 (19) | same pack, Opus fresh-eyes arm |
| r79_sonnet_s1 | claude-sonnet-5-5 | 8009F018, w_80052A90 (7), 80092824, 807B040C, 80EB751C (6) | Sonnet 5.5 probe, never-served 3-7 (Opus baseline 2.8 pins/lane) |
| r79_types_p11 | claude-opus-5-5[1m] | type consolidation phase 11 | EntityRec propagation, town root D_80016000, D_80082E60 |
| r79_sonnet_g1 | claude-sonnet-5-5 | 6 pin-free rows, 35 plain gotos | NEW: goto readability pilot |

## Readability lane (new this round)

Shape census (STATUS): plain gotos remain in 1,597 files; 964 pin-free rows hold 5,581 plain gotos (no computed
goto). The goto generators t41/t44/t48/t102 go the other way (goto forms that remove pins). A readability lane
turns gotos back into structured C, byte-exact. Tooling: `land_lanes.sh` lands an equal-pin candidate whose plain
goto count fell (and refuses one that adds gotos at equal pins); `kitlib.admissible` stages the same, plus
equal-pin candidates whose volatile / one-trip count fell (the lander's round-78 rule, now in the kit too).
Pilot r79_sonnet_g1 asks for a generator rule per working shape, so the 900-row tail can be swept by CPU.
