# Open items

A tracked list of known problems and decisions that are not finished. Fix an item properly when a safe moment arises
(no active landing on the rows or files involved, gates available), then move it to "Closed" with the commit.
Newest first within each section. Evidence links point at the record that measured the item.

## Open

| # | item | why it matters | next step | evidence |
|---|---|---|---|---|
| 3 | generated Rec_D_800E3D7C.h still used (and Rec_D_800814A8.h by func_810AFA04, func_81324774 - pin-lane rows skipped as busy) by dungeon/func_8133AD74 (reads through a volatile view in the generated header) | EntityRec supersedes it | resolve that row's volatile view, then retire the header | phase-6 REPORT |
| 8 | 0x800814A0 declared two ways by the original (22 rows compiled against a scalar int keep `extern int D_800814A0`) | two spellings of one address | revisit if a second readable name is wanted | TYPE_CONSOLIDATION.md phase 2 |
| 10 | 147 rows keep a `(u8 *)&gameWork` view pointer | readability | only where the local pointer is not retail's base register (128 miss when folded) | TYPE_CONSOLIDATION.md phase 4 |
| 11 | goto readability debt (1,599 rows) and remaining address-named local views | readability | byte-exact control-flow work in family packs; views via type consolidation | evidence/r78_wave1_report.md |
| 14 | tools/gate/match.py and tools/fidelity/probe_gp_module.py do not read config/slus_006.14.c_syms.txt | only the SLUS image gate + verify's module/partition gates prove a SLUS candidate naming a C-only symbol | teach both to read it | phase-6 REPORT |
| 15 | evidence records keyed on the old pinned SLUS recipe sha read stale once (slus_module_evidence, certify_slus_module, prove_slus_ownership, pin_search) | expected after a recipe move | refresh on next use | phase-6 REPORT |
| 23 | town/func_8047047C (r96_sonnet_pr3/held): candidate gives func_80017E98 a 2-arg prototype while its definition takes 3 | a false prototype hides an arity site | keep held; land only the own-parameter typing half if exact alone; record the call as an arity site (r95_pt burn-down) | work/native_lane/r96_sonnet_pr3/held/WHY.txt |
| 24 | slus/w_8004CAA0 file-scope register globals ($sp/$3/$8/$5) | `$sp` is real machine state (scratchpad stack switch at 0x1F8003FC); the other three are uncounted pins (keeping only `$sp` bound: total 16, length drift) | provenance call (hand-asm library helper?) or count + route; now visible in STATUS hidden line as `reg-global` | r97 decisions 21 |
| 25 | main/func_8000F774 fake dependency (2 sites) | the last fake dependency in the tree | Opus mechanism lane: block-0 local-alloc order height-qty > row_count > width-qty without the fakes (`lreg_explain.py --block 0`) | work/native_lane/r96_opus_fd/REPORT.md |
| 26 | pad words D_801379A8/D_801379B0 declared six ways (s32, volatile s32, PadState) | readability / one type per symbol | type phase 14: PadState { held; unk_04; pressed } (main/func_8001B7F8) as the shared type, volatiles kept where exactness needs them | r97 decisions 18 |

## Closed (round 97 pickup, 2026-10-06)

| item | fix | commit |
|---|---|---|
| 6: dungeon/func_800957B8 5 -> 1 held | pin-free since the r95 landings | 7663cc362 |
| 7: early constant call argument | answered: r96_opus_ca MECHANISM.md is a sourced negative in this cdk cc1; remaining rows in ledger/hard_basket.jsonl (CALL-ARG) | r96 decisions 7 |
| 12: dungeon/func_81875B38 site-for-pin trade | 4 -> 0 at the module recipe (r81_opus_fc6) | 892dc9de7 |
| 22: slus/w_8005F134 switch needs jtbl ownership | SLUS switch rows own their jump tables (rodata migration) | d9f94903e |

## Closed (round 78)

| item | fix | commit |
|---|---|---|
| t2_pins looped forever on pins inside a macro expansion (unchanged candidate verified exact); t16/t16b/t18 wasted budget the same way | skip unchanged candidates | 6c78cac0 |
| F0 clone family (11 rows x 6 pins): Astra's discarded-clamp reconstruction | DECIDED (coordinator, owner delegated 09-28): rejected under charter rule 3 (dead assignments between statements = fake dependency; the 09-23 dead-init ruling covers declaration initializers only). Reopen only with a real consumer for the three colour reads; no more F0 spelling lanes. Item 7 keeps the call_one mechanism question | r79 decision record |
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
