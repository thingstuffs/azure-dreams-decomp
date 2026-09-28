# Open items

A tracked list of known problems and decisions that are not finished. Fix an item properly when a safe moment arises
(no active landing on the rows or files involved, gates available), then move it to "Closed" with the commit.
Newest first within each section. Evidence links point at the record that measured the item.

## Open

| # | item | why it matters | next step | evidence |
|---|---|---|---|---|
| 3 | generated Rec_D_800E3D7C.h still used (and Rec_D_800814A8.h by func_810AFA04, func_81324774 - pin-lane rows skipped as busy) by dungeon/func_8133AD74 (reads through a volatile view in the generated header) | EntityRec supersedes it | resolve that row's volatile view, then retire the header | phase-6 REPORT |
| 5 | F0 clone family (11 rows x 6 pins): Astra reproduced retail with discarded colour clamps, self-rejected | 66 pins | OWNER DECISION: accept a visible dead-clamp reconstruction or keep rejecting | evidence/r78_wave1_report.md; work/native_lane/r78_astra_f0/diag/rejected_clamps/ |
| 6 | dungeon/func_800957B8 5 -> 1 held | exact only by reading a callee's 5th halfword from a spill slot (layout-dependent) | find the real 5-element record + source of tile_info[4] | work/native_lane/r78_opus_c16/held/README.md |
| 7 | early constant call argument (gcc 2.7 calls.c loads constant register args last; retail loads some first) | 37 sites / 34 rows; 11-row `call_one` clone cluster | the 11-row `call_one` cluster IS the F0 family (item 5) - resolve there; the other ~23 rows: the measurement r78_opus_rx1 named (narrow `u8/u16 x = 1` passed as x after a label / in a loop, read .cse/.combine) | work/native_lane/r78_opus_rx1/REPORT.md |
| 8 | 0x800814A0 declared two ways by the original (22 rows compiled against a scalar int keep `extern int D_800814A0`) | two spellings of one address | revisit if a second readable name is wanted | TYPE_CONSOLIDATION.md phase 2 |
| 10 | 147 rows keep a `(u8 *)&gameWork` view pointer | readability | only where the local pointer is not retail's base register (128 miss when folded) | TYPE_CONSOLIDATION.md phase 4 |
| 11 | goto readability debt (1,599 rows) and remaining address-named local views | readability | byte-exact control-flow work in family packs; views via type consolidation | evidence/r78_wave1_report.md |
| 12 | r77_opus_m6 site-for-pin trade on dungeon/func_81875B38 (4 -> 1) | pins | stage with a trade-ledger entry and review | HANDOVER round 77 |
| 14 | tools/gate/match.py and tools/fidelity/probe_gp_module.py do not read config/slus_006.14.c_syms.txt | only the SLUS image gate + verify's module/partition gates prove a SLUS candidate naming a C-only symbol | teach both to read it | phase-6 REPORT |
| 15 | evidence records keyed on the old pinned SLUS recipe sha read stale once (slus_module_evidence, certify_slus_module, prove_slus_ownership, pin_search) | expected after a recipe move | refresh on next use | phase-6 REPORT |

## Closed (round 78)

| item | fix | commit |
|---|---|---|
| stats group D_80084808.. declared at several sizes; 11 D_8006DE24 base-form rows; phase-9 full apply reverting | volumeScale[8] (size must exceed 8 bytes: stock-2.7.2 store-macro expansion); DefEntry field spelling; root cause found by the phase-9 agent with a scratch-build repro | phase 9 (this commit) |
| apply_names.py refused data rows; lab.py API ignored the 60-variant cap; verify.py include_root could not test a changed header | `apply_names.py --data [--rewrite]`; cap enforced in Lab.test/test_subs (`more=True` override); explicit include_root wins (overlay -isystem/-iquote ordering, SLUS -I before row flags) - 219 tests, whole-tree verify 6,767/6,767 exact with the new verify.py | this commit (r78_sol_tools, gpt-6-sol) |
| stale UNRESOLVED pin comments on lines with no pin (the census found 11; tree-wide there were 262 in 135 files) | removed (comment-only diff, checked mechanically); 135 rows verify-exact, 118 windows + SLUS MATCH | this commit |
| game.h struct S_80083178 overlapped GameWork | GameWork.view sub-structure; S_80083178 retired (3 genuine second declarations keep a local extern) | phase 8 (this commit) |
| stale numbering text after the symbol-dump fix (names.tsv 125 rows, object_node.h, func_800C4D18.c) | corrected; func_800C4D18 verify-exact, SLUS MATCH | this commit |
| script symbol dump misparsed (records are name[32] then u32 value; every name had the previous record's value) - reported by the owner's script decoder | tools/evidence.py parse fixed; call number n = entry n (no +1); proven by 836 compiled call sites (docs/evidence/script_call_sites_20260928.*); outputs regenerated with dated correction notes | this commit |
| SLUS link had no definition for data symbols only C names; phase-5 SLUS rows failed to link | configure.py C_SYMS + config/slus_006.14.c_syms.txt (recipe re-pinned, image MATCH); the two phase-5 candidates were wrong (folded the separate table D_80082EC0 into TileObject) and are not landed; TileObject corrected to 0x40 | phase 6 (this commit) |
| generated Rec_D_800814A8.h / most Rec_D_800E3D7C.h uses | record_ptrs.h retyped onto EntityRec *, 158 rows migrated | phase 6 (this commit) |
| verify.py compiled current SLUS texts against the frozen raw/include (182 rows could not compile via CLI) | live include/ for non-historical texts | e8874f3b |
| byte-exact candidates hidden by assembler macros (la/ulw/usw) in the listing screen | screen.normalise expands them | 90ce36e3 |
| lander refused scaffolding-only removals | land when a scaffolding kind falls with pins unchanged | a1304b6a |
| capped lanes never landed their staged candidates | cap stub last_message.txt | 6929bdc7 |
| caps not price-scaled (Luna killed at a Sol-sized cap) | config/lane_caps.json | 6929bdc7 |
| lockstep NON_MATCHING edits refused | pin_census._arm_lockstep_decls | 50238115 |
| STATUS m2c-name metric counted comments | code-only metric | 69d71028 |
| duck_brief crash on pin groups with no distance; build_class_pack `--rows` crash | fixed | 6e8a19e2, 50238115 |
