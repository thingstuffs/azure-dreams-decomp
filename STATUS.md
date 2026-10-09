# azure-dreams-decomp status

Generated 2026-10-09T02:36:01Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 423 | 62,760 | 423 | 62,760 | 423 | 62,760 | 0 |
| town | 2695 | 457,832 | 2695 | 457,832 | 2695 | 457,832 | 0 |
| dungeon | 3369 | 1,766,416 | 3369 | 1,766,416 | 2892 | 1,756,324 | 477 |
| ovmovie | 22 | 2,852 | 22 | 2,852 | 22 | 2,852 | 0 |
| ALL | 7371 | 2,760,796 | 7371 | 2,760,796 | 6894 | 2,750,704 | 477 |

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
| jtbl_80041344 | 1 | not certified | include/common.h |
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

## Overlay modules

| module | rows | placement proof |
|---|---:|---|
| dungeon_cd_control_d79c4 | 3 | current: complete TU + all windows + genuine |
| town_minigame_dispatch_44b44 | 13 | current: complete TU + all windows + genuine |
| dungeon_ovl_1852800 | 4 | current: complete TU + all windows + genuine |
| dungeon_ovl_1870800 | 2 | current: complete TU + all windows + genuine |

Placement alone does not override any lower-level or source-residue guard.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2332 | 510,660 | 18.5% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,448,328 | 52.4% | 0 | 0 | 0.0% |
| m2c local names | 5182 | 2,162,220 | 78.2% | 21 | 36,012 | 1.3% |
| ASM_ pins | 2136 | 1,455,364 | 52.7% | 50 | 64,448 | 2.3% |
| goto | 1545 | 1,311,436 | 47.5% | 276 | 331,008 | 12.0% |
| computed-goto jump table | 317 | 436,404 | 15.8% | 4 | 7,008 | 0.3% |
| inline asm outside macros (clean: minus the composite-row carve debt, counted on its own line below) | 361 | 245,564 | 8.9% | 24 | 21,880 | 0.8% |
| fidelity blocking site, LABEL_AS_CALL/PASSTHRU_NO_ARGS (pin: baseline audit of the frozen text; clean: live, L5 predicate) | 1489 | 675,960 | 24.5% | 0 | 0 | 0.0% |
| any fidelity site (pin: any baseline audit class; clean: live L5 `fidelity_site` predicate, = levels.py) | 2654 | 1,281,340 | 46.4% | 10 | 26,316 | 1.0% |
| any live audit site, unnarrowed (clean column only; pin column repeats the row above) | 2654 | 1,281,340 | 46.4% | 1650 | 894,212 | 32.4% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 668 | 488,888 | 17.7% | 6 | 1,876 | 0.1% |
| maspsx marker pins (scaffolding) | 394 | 347,512 | 12.6% | 1 | 1,176 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,008 | 5.6% | 9 | 12,392 | 0.4% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 1 | 408 | 0.0% |
| local address-named struct | 633 | 346,872 | 12.6% | 3020 | 1,686,624 | 61.0% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 632 | 156,436 | 5.7% | 7046 | 2,365,524 | 85.6% |

Pin sites now: 91 in 50 rows; REG 46, KEEP 15, KEEP_NV 13, SCHED_BARRIER 5, USE 3, MEM_BARRIER 2, USE_NV 2, USE2 1.  At the pin: 25,902; REG 12,801, KEEP 6,935, KEEP_NV 2,505, SCHED_BARRIER 1,355, TAILSLOT_PIN 506, USE 294, USE_NV 260, KEEP_DEP_NV 190.

Tracked, not pins (owner 2026-10-06): oddities 1 (ledger/oddities.jsonl - zero-byte fences retail needs, curiosities, not removal targets: dungeon/func_8196096C); one-trip barrier rows 2 (ledger/onetrip_barrier_rows.jsonl); load-bearing one-trip rows 85 (ledger/onetrip_loadbearing.jsonl, statement-macro bodies, not counted in the do{}while(0) row above).
Carve debt - composite rows (r95 decisions item 8 kept the spelling for bytes; r99: it is an artifact of one-row-per-function carving, owned by module placement): the `asm("func_X")` data prefix (another function's jump table / overlay data that retail places before this row's code) and its `.globl/.type/.size func_X` stamp (`pin_census.composite_asm_spans`), 64 statements in 41 rows - counted here, not in the inline-asm row above; still L5 `inline_asm` residue in levels.py until the module TU owns the data.
Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 0, calls of local asm wrappers 0, hand-written asm in function bodies 0 (C that is missing); symbol aliases 29 (a second typed name for one symbol: a missing type); file-scope asm directives 50; file-scope global register variables 4 (`register T g asm("$R")`).

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 98 rows carry one flag, 2 carry two or more.


## Likely incorrect compiler (registered recipe vs the real build)

The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects (r84_fable_build). A row listed here carries a recipe its module's pin-free rows do not use - usually pins fitted at the wrong compiler. Module recipe = ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.

| class | rows | dungeon / town / main | pinned rows | pins |
|---|---:|---|---:|---:|
| late cell (2.8.x / egcs / 2.95.2: fitted) | 2 | 2 / 0 / 0 | 2 | 6 |
| cdk cell + crutch flags, module is plain | 3 | 3 / 0 / 0 | 0 | 0 |
| stock cell inside a cdk module | 0 | 0 / 0 / 0 | 0 | 0 |
| other mismatch with the module recipe (-G, stock flavour, -O1) | 1 | 0 / 1 / 0 | 1 | 1 |
| **total** | **6** | | **3** | **7** |

Rows at a registered recipe backed by per-row compiler evidence (ledger/recipe_evidence.jsonl, not listed above): town/func_806D30B4 2.6.3-G0 (confirmed), town/func_808B2B04 2.6.3-G0 (confirmed).

Sony SDK library objects (ledger/sdk_objects.jsonl, whole-object byte match; not listed above): main/func_800219C4.

SLUS rows off their region's build (game image = 2.7.2-cdk, sound TU = stock 2.7.2; module members included): 9 rows, 1 pinned / 1 pins.

Most-pinned rows off their build recipe: dungeon/func_80DE48EC 5 pins (2.8.0-G0 -> 2.7.2-cdk-G0); town/func_808135E0 1 pins (2.7.2-G0 -fno-cse-skip-blocks -> 2.6.3-G0); dungeon/func_813274E4 1 pins (2.8.1-G0 -> 2.7.2-cdk-G0).

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 24.

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,753,556 | 99.6% |
| L1 | 2,753,556 | 99.6% |
| L2 | 2,753,556 | 99.6% |
| L3 | 2,547,744 | 92.2% |
| L4 | 5,916 | 0.2% |
| L5 | 5,916 | 0.2% |

On shared record headers (T7, `include/records/`): 845 rows, 549,076 bytes (19.9%); records used: 98.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 50 rows (64,448 B), tail_jump 19 rows (23,756 B), not_in_module 6,872 rows (2,744,788 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
