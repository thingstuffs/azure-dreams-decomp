# azure-dreams-decomp status

Generated 2026-10-02T06:00:04Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 423 | 62,760 | 423 | 62,760 | 423 | 62,760 | 0 |
| town | 2695 | 457,832 | 2695 | 457,832 | 2695 | 457,832 | 0 |
| dungeon | 2743 | 1,560,636 | 2743 | 1,560,636 | 2743 | 1,560,636 | 0 |
| ovmovie | 22 | 2,852 | 22 | 2,852 | 22 | 2,852 | 0 |
| ALL | 6745 | 2,555,016 | 6745 | 2,555,016 | 6745 | 2,555,016 | 0 |

ovmovie is parked by the owner (listed, excluded from ALL). Ordinary SLUS rows use pinned-TU object verification; grouped module candidates use the full SLUS image gate, including sibling functions and owned data. Historical raw baselines stay per row. Overlay rows use retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are none at the pin.

Baseline NOT exact: 0 rows

## SLUS modules

| module | logical rows | placement evidence | shared headers |
|---|---:|---|---|
| runtime_directory | 3 | unproved: module sources, headers or manifest changed | include/common.h, include/slus/runtime_directory.h |
| entry_words | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| render_words | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/records/Rec_func_80034F58_arg0.h |
| owned_80035484 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80038A10 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80044698 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_800448BC | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_8004713C | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80047338 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| owned_80047468 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| state_defaults | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| slot_transition | 4 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/slot_transition.h |
| slot_transition_secondary | 4 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/slot_transition.h |
| konami_runtime_gp_count | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| gp_shared_slots | 2 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| gp_split_storage | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| gp_shared_81510 | 2 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_81510.h |
| gp_shared_8099c | 2 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_8099c.h |
| cache_afe | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h |
| list_cursor_e0 | 1 | unproved: module sources, headers or manifest changed | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/list_cursor_e0.h |
| saved_value_b98 | 2 | not certified | include/common.h, include/slus/saved_value_b98.h |
| sort_rank_81540 | 1 | not certified | include/common.h, include/slus/sort_rank_81540.h |
| command_slots_81554 | 4 | not certified | include/common.h, include/slus/command_slots_81554.h |
| address_slot | 1 | not certified | include/common.h |
| command_words | 1 | not certified | include/common.h |
| gp_shared_8152c | 3 | not certified | include/common.h |
| gp_d92c_owned | 1 | not certified | include/common.h |
| gp_order_bytes_owner | 1 | not certified | include/common.h |
| gp_af3_pair | 2 | not certified | include/common.h |
| message_mode_81550 | 3 | not certified | include/common.h, include/slus/message_mode_81550.h |
| cd_command_state | 7 | not certified | include/common.h, include/slus/cd_state.h, include/slus/cd_cohort_types.h |
| accessors_814c8 | 0 | not applicable (partition owner) | include/common.h |
| table_counters_b1b_b1c | 0 | not applicable (partition owner) | include/common.h |
| jtbl_80054F9C | 1 | not certified | include/common.h |
| jtbl_80057A94 | 1 | not certified | include/common.h |
| jtbl_80052CE0 | 1 | not certified | include/common.h |
| jtbl_800517CC | 1 | not certified | include/common.h |
| jtbl_8004CECC | 1 | not certified | include/common.h |
| jtbl_80042BDC | 1 | not certified | include/common.h |
| jtbl_8005F134 | 1 | not certified | include/common.h |
| jtbl_8005EDA0 | 1 | not certified | include/common.h |

Not certified means no placement certificate has been issued; ownership and retail-byte proofs are separate. Partition owners do not grant whole-row placement.

Module placement preserves logical row IDs. The existing L4/L5 pin, tail-jump and fidelity requirements still apply; changed shared inputs invalidate placement evidence.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2332 | 515,092 | 20.1% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,456,820 | 57.0% | 0 | 0 | 0.0% |
| m2c local names | 5182 | 2,172,128 | 84.9% | 781 | 303,284 | 11.9% |
| ASM_ pins | 2135 | 1,464,792 | 57.3% | 175 | 236,824 | 9.3% |
| goto | 1545 | 1,318,412 | 51.5% | 666 | 721,864 | 28.2% |
| computed-goto jump table | 317 | 437,288 | 17.1% | 70 | 101,204 | 4.0% |
| inline asm outside macros | 361 | 255,656 | 10.0% | 241 | 203,624 | 8.0% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 308 | 157,064 | 6.1% |
| any fidelity site | 2654 | 1,286,064 | 50.3% | 1777 | 959,904 | 37.5% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,500 | 21.9% | 122 | 106,264 | 4.2% |
| maspsx marker pins (scaffolding) | 393 | 351,556 | 13.7% | 1 | 1,176 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,176 | 6.1% | 208 | 146,396 | 5.7% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 2 | 820 | 0.0% |
| local address-named struct | 633 | 346,988 | 13.6% | 3038 | 1,566,096 | 61.2% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 156,440 | 6.1% | 5317 | 1,523,212 | 59.6% |

Pin sites now: 500 in 174 rows; REG 287, KEEP_NV 81, KEEP 56, SCHED_BARRIER 20, USE2_NV 10, USE_NV 9, USE 8, SET 5.  At the pin: 25,755; REG 12,776, KEEP 6,852, KEEP_NV 2,500, SCHED_BARRIER 1,349, TAILSLOT_PIN 499, USE 294, USE_NV 260, KEEP_DEP_NV 184.

Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 1, calls of local asm wrappers 0, hand-written asm in function bodies 1 (C that is missing); symbol aliases 98 (a second typed name for one symbol: a missing type); file-scope asm directives 390.

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 162 rows carry one flag, 12 carry two or more.


## Likely incorrect compiler (registered recipe vs the real build)

The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects (r84_fable_build). A row listed here carries a recipe its module's pin-free rows do not use - usually pins fitted at the wrong compiler. Module recipe = ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.

| class | rows | dungeon / town / main | pinned rows | pins |
|---|---:|---|---:|---:|
| late cell (2.8.x / egcs / 2.95.2: fitted) | 32 | 25 / 5 / 2 | 14 | 59 |
| cdk cell + crutch flags, module is plain | 23 | 15 / 7 / 1 | 10 | 28 |
| stock cell inside a cdk module | 20 | 9 / 9 / 2 | 2 | 24 |
| other mismatch with the module recipe (-G, stock flavour, -O1) | 201 | 108 / 40 / 53 | 14 | 35 |
| **total** | **276** | | **40** | **146** |

Most-pinned rows off their build recipe: dungeon/func_800C4A80 16 pins (2.7.2-G0 -fno-expensive-optimizations -fno-cse-follow-jumps -> 2.7.2-cdk-G0); dungeon/func_8187A9A8 13 pins (2.8.1-G0 -> 2.7.2-cdk-G0); dungeon/func_800AFA68 10 pins (2.7.2-cdk-G0 -> 2.7.2-cdk); town/func_800ABBF8 8 pins (2.7.2-G0 -fno-expensive-optimizations -fno-schedule-insns -> 2.7.2-cdk-G0); dungeon/func_81876014 7 pins (2.7.2-cdk-G0 -fno-schedule-insns -> 2.7.2-cdk-G0); dungeon/func_8009F018 7 pins (2.7.2-cdk-G0 -fno-expensive-optimizations -> 2.7.2-cdk-G0); dungeon/func_800969CC 7 pins (2.8.0 -fno-cse-skip-blocks -> 2.7.2-cdk-G0); town/func_800BAE88 6 pins (2.91.66-G0 -fno-gcse -> 2.7.2-cdk-G0); dungeon/func_80DE48EC 5 pins (2.8.0-G0 -> 2.7.2-cdk-G0); dungeon/func_80A20A28 5 pins (2.7.2-cdk-G0 -> 2.7.2-cdk); dungeon/func_800BFE94 5 pins (2.8.0 -fno-expensive-optimizations -> 2.7.2-cdk-G0); dungeon/func_8180A990 4 pins (2.7.2-cdk-G0 -fno-cse-follow-jumps -> 2.7.2-cdk-G0).

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 15.

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,557,868 | 100.0% |
| L1 | 2,557,868 | 100.0% |
| L2 | 2,557,868 | 100.0% |
| L3 | 2,556,808 | 100.0% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 819 rows, 474,348 bytes (18.5%); records used: 102.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 174 rows (236,700 B), tail_jump 9 rows (3,452 B), not_in_module 6,745 rows (2,555,016 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
