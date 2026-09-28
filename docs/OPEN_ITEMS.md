# Open items

A tracked list of known problems and decisions that are not finished. Fix an item properly when a safe moment arises
(no active landing on the rows or files involved, gates available), then move it to "Closed" with the commit.
Newest first within each section. Evidence links point at the record that measured the item.

## Open

| # | item | why it matters | next step | evidence |
|---|---|---|---|---|
| 1 | SLUS link has no definition for data symbols that only C references (D_80082E80) | 3 SLUS rows (w_8003D8B0, w_8003F80C, w_8004D614) cannot migrate to TileObject | configure.py defines C-only data symbols for the SLUS link, gated by image SHA-1 + recipe check (phase-6 agent working on it) | evidence/type_consolidation_phase5_open.md |
| 2 | game.h `struct S_80083178` overlaps GameWork (gameWork + 0x18) | two types for one object | migrate the 6 rows that type locals as `struct S_80083178 *`; func_800AFA68 misses by 9; slus/w_8004D5D0 is a genuine second declaration (keeps D_80083178); slus/code2 is a plural partition | TYPE_CONSOLIDATION.md phase 4 |
| 3 | generated records Rec_D_800E3D7C.h / Rec_D_800814A8.h still used (74 + 106 rows) | EntityRec supersedes them | retype record_ptrs.h onto EntityRec *, migrate, retire (phase-6 agent) | TYPE_CONSOLIDATION.md phase 5 |
| 4 | apply_names.py refuses data rows | data names are appended to names.tsv by hand in apply scripts | add an `apply_names.py --data` mode | pilot DESIGN |
| 5 | F0 clone family (11 rows x 6 pins): Astra reproduced retail with discarded colour clamps, self-rejected | 66 pins | OWNER DECISION: accept a visible dead-clamp reconstruction or keep rejecting | evidence/r78_wave1_report.md; work/native_lane/r78_astra_f0/diag/rejected_clamps/ |
| 6 | dungeon/func_800957B8 5 -> 1 held | exact only by reading a callee's 5th halfword from a spill slot (layout-dependent) | find the real 5-element record + source of tile_info[4] | work/native_lane/r78_opus_c16/held/README.md |
| 7 | early constant call argument (gcc 2.7 calls.c loads constant register args last; retail loads some first) | 37 sites / 34 rows; 11-row `call_one` clone cluster | the measurement r78_opus_rx1 named: narrow `u8/u16 x = 1` passed as x after a label / in a loop, read .cse/.combine | work/native_lane/r78_opus_rx1/REPORT.md |
| 8 | 0x800814A0 declared two ways by the original (22 rows compiled against a scalar int keep `extern int D_800814A0`) | two spellings of one address | revisit if a second readable name is wanted | TYPE_CONSOLIDATION.md phase 2 |
| 9 | 11 stale UNRESOLVED comments on lines with no live pin | misleading comments | delete them (byte-neutral; lands under the scaffolding-only lander rule? comments only - needs a comment-only landing path) | work/native_lane/r78_sol6_xjump/REPORT.md |
| 10 | 147 rows keep a `(u8 *)&gameWork` view pointer | readability | only where the local pointer is not retail's base register (128 miss when folded) | TYPE_CONSOLIDATION.md phase 4 |
| 11 | goto readability debt (1,599 rows) and remaining address-named local views | readability | byte-exact control-flow work in family packs; views via type consolidation | evidence/r78_wave1_report.md |
| 12 | r77_opus_m6 site-for-pin trade on dungeon/func_81875B38 (4 -> 1) | pins | stage with a trade-ledger entry and review | HANDOVER round 77 |
| 13 | lab.py Python API does not enforce the 60-variant cap | lane efficiency | enforce in the API as well as the CLI | r78_opus_sp11 report |

## Closed (round 78)

| item | fix | commit |
|---|---|---|
| verify.py compiled current SLUS texts against the frozen raw/include (182 rows could not compile via CLI) | live include/ for non-historical texts | e8874f3b |
| byte-exact candidates hidden by assembler macros (la/ulw/usw) in the listing screen | screen.normalise expands them | 90ce36e3 |
| lander refused scaffolding-only removals | land when a scaffolding kind falls with pins unchanged | a1304b6a |
| capped lanes never landed their staged candidates | cap stub last_message.txt | 6929bdc7 |
| caps not price-scaled (Luna killed at a Sol-sized cap) | config/lane_caps.json | 6929bdc7 |
| lockstep NON_MATCHING edits refused | pin_census._arm_lockstep_decls | 50238115 |
| STATUS m2c-name metric counted comments | code-only metric | 69d71028 |
| duck_brief crash on pin groups with no distance; build_class_pack `--rows` crash | fixed | 6e8a19e2, 50238115 |
