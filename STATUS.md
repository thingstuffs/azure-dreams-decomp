# azure-dreams-decomp status

Generated 2026-10-12T23:43:26Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 422 | 62,736 | 422 | 62,736 | 422 | 62,736 | 0 |
| town | 2706 | 457,832 | 2706 | 457,832 | 2706 | 457,832 | 0 |
| dungeon | 3442 | 1,789,004 | 3442 | 1,789,004 | 3441 | 1,787,204 | 1 |
| ovmovie | 22 | 2,852 | 22 | 2,852 | 22 | 2,852 | 0 |
| ALL | 7454 | 2,783,360 | 7454 | 2,783,360 | 7453 | 2,781,560 | 1 |

Data rows: 498 (13,584 B); stale-image residue DATA: 1 (488 B).

Placement unproven (excluded from L4 module placement): 6 rows (1,688 B): town/D_802F100C, town/D_802F1074, town/D_802F11AC, dungeon/func_80921000, dungeon/D_808CB000, dungeon/D_80921000


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
| list_cursor_e0 | 1 | unproved: certificate physical contributors or destination changed | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/list_cursor_e0.h |
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
| dungeon_ovl_1858800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_1840800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_185e800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_18ac800 | 2 | current: complete TU + all windows + genuine |
| dungeon_ovl_18fa800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_19ba800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_199c800 | 4 | current: complete TU + all windows + genuine |
| dungeon_ovl_18f4800 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_19a8800 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_189a800 | 13 | current: complete TU + all windows + genuine |
| dungeon_ovl_188e800 | 6 | current: complete TU + all windows + genuine |
| dungeon_ovl_198a800 | 17 | current: complete TU + all windows + genuine |
| dungeon_ovl_1876800 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_1894800 | 11 | current: complete TU + all windows + genuine |
| dungeon_ovl_18a6800 | 15 | current: complete TU + all windows + genuine |
| dungeon_ovl_19d2800 | 6 | current: complete TU + all windows + genuine |
| dungeon_ovl_197281c | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_1990800 | 13 | current: complete TU + all windows + genuine |
| dungeon_ovl_1960800 | 11 | current: complete TU + all windows + genuine |
| dungeon_ovl_183a800 | 10 | current: complete TU + all windows + genuine |
| dungeon_ovl_18a0800 | 15 | current: complete TU + all windows + genuine |
| dungeon_ovl_19c6800 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_19cc800 | 22 | current: complete TU + all windows + genuine |
| dungeon_ovl_192a800 | 7 | current: complete TU + all windows + genuine |
| dungeon_ovl_1918800 | 11 | current: complete TU + all windows + genuine |
| dungeon_ovl_19de800 | 22 | current: complete TU + all windows + genuine |
| dungeon_ovl_7ce800 | 30 | current: complete TU + all windows + genuine |
| dungeon_ovl_fa7000 | 28 | current: complete TU + all windows + genuine |
| dungeon_ovl_1924800 | 11 | current: complete TU + all windows + genuine |
| dungeon_ovl_19b4800 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_184c800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_1864800 | 4 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e6a5800 | 23 | current: complete TU + all windows + genuine |

Placement alone does not override any lower-level or source-residue guard.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2331 | 510,568 | 18.3% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,448,168 | 52.0% | 0 | 0 | 0.0% |
| m2c local names | 5181 | 2,160,832 | 77.6% | 19 | 32,796 | 1.2% |
| ASM_ pins | 2135 | 1,455,340 | 52.2% | 24 | 32,172 | 1.2% |
| goto | 1545 | 1,311,404 | 47.1% | 273 | 328,096 | 11.8% |
| computed-goto jump table | 317 | 436,404 | 15.7% | 4 | 7,008 | 0.3% |
| inline asm outside macros (clean: minus the composite-row carve debt, counted on its own line below) | 360 | 242,072 | 8.7% | 24 | 21,880 | 0.8% |
| fidelity blocking site, LABEL_AS_CALL/PASSTHRU_NO_ARGS (pin: baseline audit of the frozen text; clean: live, L5 predicate) | 1489 | 675,960 | 24.3% | 0 | 0 | 0.0% |
| any fidelity site (pin: any baseline audit class; clean: live L5 `fidelity_site` predicate, = levels.py) | 2654 | 1,280,480 | 46.0% | 13 | 27,180 | 1.0% |
| any live audit site, unnarrowed (clean column only; pin column repeats the row above) | 2654 | 1,280,480 | 46.0% | 1650 | 893,352 | 32.1% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 668 | 488,888 | 17.5% | 6 | 1,876 | 0.1% |
| maspsx marker pins (scaffolding) | 394 | 347,512 | 12.5% | 0 | 0 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,008 | 5.6% | 9 | 14,008 | 0.5% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 1 | 408 | 0.0% |
| local address-named struct | 633 | 346,872 | 12.4% | 2885 | 1,502,528 | 53.9% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 631 | 154,308 | 5.5% | 7149 | 2,408,856 | 86.5% |

Pin sites now: 40 in 24 rows; REG 18, KEEP 10, KEEP_NV 6, USE_NV 2, UNDEF 1, USE2_NV 1, MEM_BARRIER 1, SCHED_BARRIER 1.  At the pin: 25,901; REG 12,800, KEEP 6,935, KEEP_NV 2,505, SCHED_BARRIER 1,355, TAILSLOT_PIN 506, USE 294, USE_NV 260, KEEP_DEP_NV 190.

Tracked, not pins (owner 2026-10-06): oddities 1 (ledger/oddities.jsonl - zero-byte fences retail needs, curiosities, not removal targets: dungeon/func_8196096C); one-trip barrier rows 2 (ledger/onetrip_barrier_rows.jsonl); load-bearing one-trip rows 85 (ledger/onetrip_loadbearing.jsonl, statement-macro bodies, not counted in the do{}while(0) row above).
Carve debt - composite rows (r95 decisions item 8 kept the spelling for bytes; r99: it is an artifact of one-row-per-function carving, owned by module placement): the `asm("func_X")` data prefix (another function's jump table / overlay data that retail places before this row's code) and its `.globl/.type/.size func_X` stamp (`pin_census.composite_asm_spans`), 2 statements in 1 rows - counted here, not in the inline-asm row above; still L5 `inline_asm` residue in levels.py until the module TU owns the data.
Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 0, calls of local asm wrappers 0, hand-written asm in function bodies 0 (C that is missing); symbol aliases 11 (a second typed name for one symbol: a missing type); file-scope asm directives 6; file-scope global register variables 4 (`register T g asm("$R")`).

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 93 rows carry one flag, 1 carry two or more.


## Likely incorrect compiler (registered recipe vs the real build)

The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects (r84_fable_build). A row listed here carries a recipe its module's pin-free rows do not use - usually pins fitted at the wrong compiler. Module recipe = ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.

| class | rows | dungeon / town / main | pinned rows | pins |
|---|---:|---|---:|---:|
| late cell (2.8.x / egcs / 2.95.2: fitted) | 1 | 1 / 0 / 0 | 1 | 4 |
| cdk cell + crutch flags, module is plain | 1 | 1 / 0 / 0 | 0 | 0 |
| stock cell inside a cdk module | 0 | 0 / 0 / 0 | 0 | 0 |
| other mismatch with the module recipe (-G, stock flavour, -O1) | 0 | 0 / 0 / 0 | 0 | 0 |
| **total** | **2** | | **1** | **4** |

Rows at a registered recipe backed by per-row compiler evidence (ledger/recipe_evidence.jsonl, not listed above): town/func_806D30B4 2.6.3-G0 (confirmed), town/func_808B2B04 2.6.3-G0 (confirmed).

Sony SDK library objects (ledger/sdk_objects.jsonl, whole-object byte match; not listed above): main/func_800219C4.

SLUS rows off their region's build (game image = 2.7.2-cdk, sound TU = stock 2.7.2; module members included): 7 rows, 1 pinned / 1 pins.

Most-pinned rows off their build recipe: dungeon/func_80DE48EC 4 pins (2.8.0-G0 -> 2.7.2-cdk-G0).

Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 24.

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,784,412 | 99.9% |
| L1 | 2,784,412 | 99.9% |
| L2 | 2,784,412 | 99.9% |
| L3 | 2,770,828 | 99.4% |
| L4 | 217,052 | 7.8% |
| L5 | 212,432 | 7.6% |

On shared record headers (T7, `include/records/`): 903 rows, 577,664 bytes (20.7%); records used: 98.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 24 rows (32,172 B), tail_jump 8 rows (4,884 B), not_in_module 7,098 rows (2,564,416 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 21 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 137 / 18,196 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
