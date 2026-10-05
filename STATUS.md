# azure-dreams-decomp status

Generated 2026-10-05T13:59:45Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 423 | 62,760 | 423 | 62,760 | 423 | 62,760 | 0 |
| town | 2695 | 457,832 | 2695 | 457,832 | 2695 | 457,832 | 0 |
| dungeon | 2743 | 1,560,692 | 2743 | 1,560,692 | 2743 | 1,560,692 | 0 |
| ovmovie | 22 | 2,852 | 22 | 2,852 | 22 | 2,852 | 0 |
| ALL | 6745 | 2,555,072 | 6745 | 2,555,072 | 6745 | 2,555,072 | 0 |

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
| jtbl_80052144 | 1 | not certified | include/common.h |
| jtbl_80057D20 | 1 | not certified | include/common.h |

Not certified means no placement certificate has been issued; ownership and retail-byte proofs are separate. Partition owners do not grant whole-row placement.

Module placement preserves logical row IDs. The existing L4/L5 pin, tail-jump and fidelity requirements still apply; changed shared inputs invalidate placement evidence.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2332 | 515,120 | 20.1% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,456,876 | 57.0% | 0 | 0 | 0.0% |
| m2c local names | 5182 | 2,172,184 | 84.9% | 363 | 170,120 | 6.7% |
| ASM_ pins | 2135 | 1,464,820 | 57.3% | 103 | 148,408 | 5.8% |
| goto | 1545 | 1,318,468 | 51.5% | 316 | 362,396 | 14.2% |
| computed-goto jump table | 317 | 437,344 | 17.1% | 13 | 22,304 | 0.9% |
| inline asm outside macros | 361 | 255,656 | 10.0% | 235 | 201,848 | 7.9% |
| fidelity blocking site (LABEL_AS_CALL/PASSTHRU_NO_ARGS) | 1489 | 680,132 | 26.6% | 308 | 157,064 | 6.1% |
| any fidelity site | 2654 | 1,286,092 | 50.3% | 1777 | 959,932 | 37.5% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 751 | 560,528 | 21.9% | 124 | 108,616 | 4.2% |
| maspsx marker pins (scaffolding) | 393 | 351,556 | 13.7% | 1 | 1,176 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,176 | 6.1% | 122 | 98,852 | 3.9% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 2 | 820 | 0.0% |
| local address-named struct | 633 | 346,988 | 13.6% | 2977 | 1,557,180 | 60.9% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 156,440 | 6.1% | 6031 | 1,979,072 | 77.4% |

Pin sites now: 192 in 103 rows; REG 113, KEEP 26, KEEP_NV 24, SCHED_BARRIER 10, USE 4, USE2_NV 3, USE_NV 3, MEM_BARRIER 2.  At the pin: 25,755; REG 12,776, KEEP 6,852, KEEP_NV 2,500, SCHED_BARRIER 1,349, TAILSLOT_PIN 499, USE 294, USE_NV 260, KEEP_DEP_NV 184.

Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 1, calls of local asm wrappers 0, hand-written asm in function bodies 0 (C that is missing); symbol aliases 106 (a second typed name for one symbol: a missing type); file-scope asm directives 359.

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 107 rows carry one flag, 6 carry two or more.


## Likely incorrect compiler (registered recipe vs the real build)

The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects (r84_fable_build). A row listed here carries a recipe its module's pin-free rows do not use - usually pins fitted at the wrong compiler. Module recipe = ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.

| class | rows | dungeon / town / main | pinned rows | pins |
|---|---:|---|---:|---:|
| late cell (2.8.x / egcs / 2.95.2: fitted) | 4 | 3 / 0 / 1 | 4 | 10 |
| cdk cell + crutch flags, module is plain | 4 | 4 / 0 / 0 | 2 | 8 |
| stock cell inside a cdk module | 0 | 0 / 0 / 0 | 0 | 0 |
| other mismatch with the module recipe (-G, stock flavour, -O1) | 5 | 0 / 4 / 1 | 2 | 2 |
| **total** | **13** | | **8** | **20** |

SLUS rows off their region's build (game image = 2.7.2-cdk, sound TU = stock 2.7.2; module members included): 14 rows, 1 pinned / 1 pins.

Most-pinned rows off their build recipe: dungeon/func_81876014 7 pins (2.7.2-cdk-G0 -fno-schedule-insns -> 2.7.2-cdk-G0); dungeon/func_80DE48EC 5 pins (2.8.0-G0 -> 2.7.2-cdk-G0); dungeon/func_80094C70 3 pins (2.95.2-G0 -fno-schedule-insns -> 2.7.2-cdk-G0); town/func_8087514C 1 pins (2.7.2 -fno-schedule-insns -fno-schedule-insns2 -O1 -> 2.6.3); town/func_808135E0 1 pins (2.7.2-G0 -fno-cse-skip-blocks -> 2.6.3-G0); main/func_800219C4 1 pins (2.8.0 -> 2.7.2-cdk-G0); dungeon/func_813274E4 1 pins (2.8.1-G0 -> 2.7.2-cdk-G0); dungeon/func_800CDFD8 1 pins (2.7.2-cdk-G0 -fno-rerun-cse-after-loop -fno-strength-reduce -> 2.7.2-cdk-G0).

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 20.

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,557,924 | 100.0% |
| L1 | 2,557,924 | 100.0% |
| L2 | 2,557,924 | 100.0% |
| L3 | 2,556,864 | 100.0% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 808 rows, 473,492 bytes (18.5%); records used: 101.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 103 rows (148,408 B), tail_jump 8 rows (3,332 B), not_in_module 6,745 rows (2,555,072 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
