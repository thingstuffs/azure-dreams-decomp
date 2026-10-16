# azure-dreams-decomp status

Generated 2026-10-16T14:37:51Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 446 | 64,920 | 446 | 64,920 | 446 | 64,920 | 0 |
| town | 3233 | 487,496 | 3233 | 487,496 | 3233 | 487,496 | 0 |
| dungeon | 6250 | 3,100,152 | 6250 | 3,100,152 | 6250 | 3,100,152 | 0 |
| ovmovie | 28 | 5,516 | 28 | 5,516 | 28 | 5,516 | 0 |
| ALL | 10841 | 4,131,872 | 10841 | 4,131,872 | 10841 | 4,131,872 | 0 |

Data rows: 503 (13,692 B); stale-image residue DATA: 1 (488 B).

Placement unproven (excluded from L4 module placement): 6 rows (1,688 B): town/D_802F100C, town/D_802F1074, town/D_802F11AC, dungeon/func_80921000, dungeon/D_808CB000, dungeon/D_80921000


No container is parked (ovmovie unparked by the owner 2026-10-14). Ordinary SLUS rows use pinned-TU object verification; grouped module candidates use the full SLUS image gate, including sibling functions and owned data. Historical raw baselines stay per row. Overlay rows use retail-slice comparison through the per-row scorer, with the window gate as the fallback of record. Non-stock rows (bridge cells, per-row assembler dials, platform asm) would be excluded; there are none at the pin.

Baseline NOT exact: 0 rows

## SLUS modules

| module | logical rows | placement evidence | shared headers |
|---|---:|---|---|
| runtime_directory | 3 | unproved: module sources, headers or manifest changed | include/common.h, include/slus/runtime_directory.h |
| entry_words | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/entry_words.h |
| render_words | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/records/Rec_func_80034F58_arg0.h, include/slus/render_words.h |
| owned_80035484 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_80035484.h |
| owned_80038A10 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_80038A10.h |
| owned_80044698 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_80044698.h |
| owned_800448BC | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_800448BC.h |
| owned_8004713C | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_8004713C.h |
| owned_80047338 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_80047338.h |
| owned_80047468 | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/owned_80047468.h |
| state_defaults | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/state_defaults.h |
| slot_transition | 4 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/slot_transition.h |
| slot_transition_secondary | 4 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/slot_transition.h |
| konami_runtime_gp_count | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/konami_runtime_gp_count.h |
| gp_shared_slots | 2 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_slots.h |
| gp_split_storage | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_split_storage.h |
| gp_shared_81510 | 2 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_81510.h, include/shared/scratchpad.h |
| gp_shared_8099c | 2 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/gp_shared_8099c.h |
| cache_afe | 1 | not certified | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/cache_afe.h |
| list_cursor_e0 | 1 | unproved: certificate physical contributors or destination changed | include/common.h, include/game.h, include/globals.h, include/include_asm.h, include/slus/list_cursor_e0.h |
| saved_value_b98 | 2 | not certified | include/common.h, include/slus/saved_value_b98.h |
| sort_rank_81540 | 1 | not certified | include/common.h, include/slus/sort_rank_81540.h |
| command_slots_81554 | 4 | not certified | include/common.h, include/slus/command_slots_81554.h |
| address_slot | 1 | not certified | include/common.h, include/slus/address_slot.h |
| command_words | 1 | not certified | include/common.h, include/slus/command_words.h |
| gp_shared_8152c | 3 | not certified | include/common.h, include/slus/gp_shared_8152c.h |
| gp_d92c_owned | 1 | not certified | include/common.h, include/slus/gp_d92c_owned.h |
| gp_order_bytes_owner | 1 | not certified | include/common.h, include/slus/gp_order_bytes_owner.h |
| gp_af3_pair | 2 | not certified | include/common.h, include/slus/gp_af3_pair.h |
| message_mode_81550 | 3 | not certified | include/common.h, include/slus/message_mode_81550.h |
| cd_command_state | 7 | not certified | include/common.h, include/slus/cd_state.h, include/slus/cd_cohort_types.h |
| accessors_814c8 | 0 | not applicable (partition owner) | include/common.h |
| table_counters_b1b_b1c | 0 | not applicable (partition owner) | include/common.h |
| jtbl_80054F9C | 1 | not certified | include/common.h, include/slus/jtbl_80054F9C.h |
| jtbl_80041344 | 1 | not certified | include/common.h, include/slus/jtbl_80041344.h |
| jtbl_80057A94 | 1 | not certified | include/common.h, include/slus/jtbl_80057A94.h |
| jtbl_80052CE0 | 1 | not certified | include/common.h, include/slus/jtbl_80052CE0.h |
| jtbl_800517CC | 1 | not certified | include/common.h, include/slus/jtbl_800517CC.h |
| jtbl_8004CECC | 1 | not certified | include/common.h, include/slus/jtbl_8004CECC.h |
| jtbl_80042BDC | 1 | not certified | include/common.h, include/slus/jtbl_80042BDC.h |
| jtbl_8005F134 | 3 | not certified | include/common.h, include/slus/jtbl_8005F134.h, include/shared/spu_voice.h |
| jtbl_8005EDA0 | 2 | not certified | include/common.h, include/slus/jtbl_8005EDA0.h |
| jtbl_80052144 | 1 | not certified | include/common.h, include/slus/jtbl_80052144.h |
| jtbl_80057D20 | 1 | not certified | include/common.h, include/slus/jtbl_80057D20.h |
| sound_tu_code | 0 | not applicable (partition owner) | include/common.h |
| jtbl_80041588 | 1 | not certified | include/common.h |
| jtbl_800595C0 | 1 | not certified | include/common.h |
| sound_pitch_conversions | 3 | not certified | include/common.h, include/slus/sound_pitch_conversions.h |
| sound_register_helpers | 3 | not certified | include/common.h, include/slus/sound_register_helpers.h |
| sound_range_records | 3 | not certified | include/common.h, include/slus/sound_range_records.h |
| sound_transfer_helpers | 3 | not certified | include/common.h, include/slus/sound_transfer_helpers.h |
| sound_streaming_transfer | 1 | not certified | include/common.h, include/slus/sound_streaming_transfer.h |
| sound_key_buffer | 2 | not certified | include/common.h, include/slus/sound_key_buffer.h |
| sound_dma_lifecycle | 6 | not certified | include/common.h, include/slus/sound_dma_lifecycle.h |
| sound_reset_state | 2 | not certified | include/common.h, include/slus/sound_reset_state.h, include/slus/sound_range_records.h |
| sound_transfer_frontends | 2 | not certified | include/common.h, include/slus/sound_transfer_frontends.h |
| sound_event_start | 1 | not certified | include/common.h, include/slus/sound_event_service.h, include/slus/sound_dma_lifecycle.h |
| sound_register_value | 1 | not certified | include/common.h, include/slus/sound_register_helpers.h |
| sound_reverb_writer | 1 | not certified | include/common.h, include/slus/sound_dma_lifecycle.h, include/slus/sound_reverb.h |

Not certified means no placement certificate has been issued; ownership and retail-byte proofs are separate. Partition owners do not grant whole-row placement.

Module placement preserves logical row IDs. The existing L4/L5 pin, tail-jump and fidelity requirements still apply; changed shared inputs invalidate placement evidence.

## Overlay modules

| module | rows | placement proof |
|---|---:|---|
| dungeon_cd_control_d79c4 | 3 | source/recipe/graph/tool/review/window inputs changed |
| town_minigame_dispatch_44b44 | 13 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1852800 | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1870800 | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1858800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1840800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_185e800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18ac800 | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18fa800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19ba800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_199c800 | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18f4800 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19a8800 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_189a800 | 13 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_188e800 | 6 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_198a800 | 17 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1876800 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1894800 | 11 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18a6800 | 15 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19d2800 | 6 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_197281c | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1990800 | 13 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1960800 | 11 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_183a800 | 10 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18a0800 | 15 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19c6800 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19cc800 | 22 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_192a800 | 7 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1918800 | 11 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19de800 | 22 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7ce800 | 30 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_fa7000 | 28 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1924800 | 11 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19b4800 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_184c800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1864800 | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e6a5800 | 23 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18d6800 | 12 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18ee800 | 8 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18e8800 | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18b2800 | 11 | source/recipe/graph/tool/review/window inputs changed |
| ovmovie_libpress | 17 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_dungeon_util | 43 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_experience | 17 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_transition_effects | 12 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_entity_effects | 21 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_tile_map | 25 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_entity_panel | 21 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_particle_effects | 11 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_screen_effects | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_trap_effects | 38 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_menu_effects | 38 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_engine_effect_dispatch | 18 | source/recipe/graph/tool/review/window inputs changed |
| town_door_22f08 | 25 | source/recipe/graph/tool/review/window inputs changed |
| town_player_init_12868 | 12 | source/recipe/graph/tool/review/window inputs changed |
| town_town_windows_1f5b8 | 36 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_town_load | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_town_map | 16 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_town_map.json' |
| dungeon_ovl_d54c | 10 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_d54c.json' |
| dungeon_dungeon_setup | 14 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_dungeon_setup.json' |
| dungeon_ovl_16b08_local | 16 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_16b08_local.json' |
| dungeon_ovl_16b08_f6a8 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_16b08_f6a8.json' |
| dungeon_ovl_1831370 | 23 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_1831370.json' |
| dungeon_ovl_1831cd8 | 50 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_1831cd8.json' |
| dungeon_ovl_1830850 | 26 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_1830850.json' |
| dungeon_ovl_9c32d4 | 5 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_9c32d4.json' |
| dungeon_ovl_19a332c | 19 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_19a332c.json' |
| dungeon_ovl_1930844 | 10 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_1930844.json' |
| dungeon_ovl_18d0850 | 12 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_18d0850.json' |
| dungeon_ovl_188898c | 9 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_188898c.json' |
| dungeon_ovl_188298c | 7 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_188298c.json' |
| dungeon_ovl_18ca83c | 4 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_18ca83c.json' |
| dungeon_ovl_18b8824 | 9 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_18b8824.json' |
| dungeon_floor_spawns | 12 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_floor_spawns.json' |
| dungeon_floor_generate | 50 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_floor_generate.json' |
| dungeon_ovl_12c50ac | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_e0365c | 38 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_be1084 | 6 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_cb3000 | 39 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_9950e8 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_d5b0b8 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_cb9000 | 39 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_cc5000 | 39 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_ccb000 | 39 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_cd7000 | 39 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18be820 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e705800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_194286c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e711800 | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1966800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e765800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e67b800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e71d800 | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_193c848 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1954800 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e6b7800 | 8 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7e6e1800 | 9 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19c088c | 11 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1936800 | 16 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_190d6a4 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_190081c | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_1906f98 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_190681c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_191284c | 4 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_19134e4 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_18c4828 | 9 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_190c800 | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_191e87c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_191eef8 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_be7084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bf3084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bf9084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c05084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a130dc | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a190dc | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a250dc | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a2b0dc | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a370dc | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c3b09c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c4709c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c4d09c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bbd094 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bc9094 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bcf094 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bdb094 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f559800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f535800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f51d800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_bb1054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_9ef054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_9fb054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a01054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_a0d054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource03_slot0 | 28 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource17_slot0 | 26 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource07_slot0 | 28 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource08_slot0 | 36 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource10_slot0 | 41 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource12_slot0 | 39 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource16_slot0 | 32 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_resource06_slot0 | 38 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f0f7800_p01 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f0f7800_p03 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f0f7800_p04 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f0f7800_p05 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f0f7800_p07 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f1d5800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f1ed800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f211800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f217800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f223800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f23b800 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f43f800_p01 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f43f800_p02 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f469800_p01 | 12 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f469800_p03 | 5 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f469800_p04 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f469800_p06 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f469800_p07 | 3 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f511800_p01 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_7f511800_p03 | 2 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c5909c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c89084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c8f084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_c9b084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_ca1084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_cad084 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_d10bc4_p02 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_d16bc4_p02 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_d1cbc4_p02 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_d28bc4_p02 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_d2ebc4_p02 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_dd9000_p03 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_e09000_code | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_e15054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_e1b054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_e27054 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_edb06c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_ee706c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_eed06c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_ef906c | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_f7d070_p01 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_f8f070 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_f95070 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_fa1070 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_79dd70 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_6490c0 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_64b0c0 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_64f0c0 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_64f118 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_6510c0 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_480100 | 2 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_4f9100 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_629100 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_47027c | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_5c7308 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_65b134 | 2 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_64d298 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_450958 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_4d9100 | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_71a1ec | 1 | source/recipe/graph/tool/review/window inputs changed |
| town_ovl_8d2114 | 1 | source/recipe/graph/tool/review/window inputs changed |
| dungeon_ovl_51e800 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_51e800.json' |
| town_ovl_2d3f0c | 3 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_town_ovl_2d3f0c.json' |
| town_ovl_2da5e4 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_town_ovl_2da5e4.json' |
| dungeon_ovl_7f43f800_p04 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_7f43f800_p04.json' |
| dungeon_ovl_7f43f800_p05 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_7f43f800_p05.json' |
| dungeon_ovl_7f43f800_p06 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_7f43f800_p06.json' |
| dungeon_ovl_7f43f800_p08 | 2 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_7f43f800_p08.json' |
| dungeon_ovl_7f511800_p04 | 4 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_7f511800_p04.json' |
| dungeon_ovl_1829800 | 12 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_dungeon_ovl_1829800.json' |
| town_ovl_6f48d0 | 1 | certificate missing/invalid: FileNotFoundError: [Errno 2] No such file or directory: 'ledger/modules/overlay_town_ovl_6f48d0.json' |

Placement alone does not override any lower-level or source-residue guard.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2331 | 510,576 | 12.4% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,449,308 | 35.1% | 9 | 2,132 | 0.1% |
| m2c local names | 5181 | 2,162,116 | 52.3% | 65 | 29,660 | 0.7% |
| ASM_ pins | 2135 | 1,456,292 | 35.2% | 0 | 0 | 0.0% |
| goto | 1545 | 1,312,068 | 31.8% | 324 | 400,040 | 9.7% |
| computed-goto jump table | 317 | 436,504 | 10.6% | 1 | 16 | 0.0% |
| inline asm outside macros (clean: minus the composite-row carve debt, counted on its own line below) | 360 | 242,072 | 5.9% | 7 | 8,984 | 0.2% |
| fidelity blocking site, LABEL_AS_CALL/PASSTHRU_NO_ARGS (pin: baseline audit of the frozen text; clean: live, L5 predicate) | 1489 | 676,096 | 16.4% | 0 | 0 | 0.0% |
| any fidelity site (pin: any baseline audit class; clean: live L5 `fidelity_site` predicate, = levels.py) | 2654 | 1,280,740 | 31.0% | 3 | 23,788 | 0.6% |
| any live audit site, unnarrowed (clean column only; pin column repeats the row above) | 2654 | 1,280,740 | 31.0% | 1647 | 892,864 | 21.6% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 668 | 489,140 | 11.8% | 0 | 0 | 0.0% |
| maspsx marker pins (scaffolding) | 394 | 347,664 | 8.4% | 0 | 0 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,008 | 3.8% | 38 | 36,844 | 0.9% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 1 | 408 | 0.0% |
| local address-named struct | 633 | 346,824 | 8.4% | 3862 | 2,159,628 | 52.3% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 631 | 154,308 | 3.7% | 10448 | 3,701,956 | 89.6% |

Pin sites now: 0 in 0 rows; .  At the pin: 25,918; REG 12,816, KEEP 6,936, KEEP_NV 2,505, SCHED_BARRIER 1,355, TAILSLOT_PIN 506, USE 294, USE_NV 260, KEEP_DEP_NV 190.

Tracked, not pins (owner 2026-10-06): oddities 0 (ledger/oddities.jsonl - zero-byte fences retail needs, curiosities, not removal targets: -); one-trip barrier rows 2 (ledger/onetrip_barrier_rows.jsonl); load-bearing one-trip rows 85 (ledger/onetrip_loadbearing.jsonl, statement-macro bodies, not counted in the do{}while(0) row above).
Carve debt - composite rows (r95 decisions item 8 kept the spelling for bytes; r99: it is an artifact of one-row-per-function carving, owned by module placement): the `asm("func_X")` data prefix (another function's jump table / overlay data that retail places before this row's code) and its `.globl/.type/.size func_X` stamp (`pin_census.composite_asm_spans`), 0 statements in 0 rows - counted here, not in the inline-asm row above; still L5 `inline_asm` residue in levels.py until the module TU owns the data.
Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 0, calls of local asm wrappers 0, hand-written asm in function bodies 0 (C that is missing); symbol aliases 7 (a second typed name for one symbol: a missing type); file-scope asm directives 2; file-scope global register variables 0 (`register T g asm("$R")`).

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 114 rows carry one flag, 0 carry two or more.


## Likely incorrect compiler (registered recipe vs the real build)

The game is one `2.7.2-cdk -G0 -O2` build plus a town -O1 debug family and stock Sony/devkit/minigame objects (r84_fable_build). A row listed here carries a recipe its module's pin-free rows do not use - usually pins fitted at the wrong compiler. Module recipe = ledger/module_recipe_census.jsonl `best_recipe`; per row see src/<container>/INDEX.md.

| class | rows | slus / ovmovie / dungeon / town / main | pinned rows | pins |
|---|---:|---|---:|---:|
| late cell (2.8.x / egcs / 2.95.2: fitted) | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| cdk cell + crutch flags, module is plain | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| stock cell inside a cdk module | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| other mismatch with the module recipe (-G, stock flavour, -O1) | 0 | 0 / 0 / 0 / 0 / 0 | 0 | 0 |
| **total** | **0** | | **0** | **0** |

Rows at a recipe the module census cannot separate from best_recipe (tie_with; not listed above, text cannot decide): main/func_80019E34 2.7.2-G0 (best 2.7.2), main/func_8001C7F4 2.7.2 (best 2.7.2-G0), main/func_800207D4 2.7.2-G0 (best 2.6.3), main/func_80020F68 2.7.2 (best 2.6.3-G0).

Rows at a registered recipe backed by per-row compiler evidence (ledger/recipe_evidence.jsonl, not listed above): ovmovie/func_800400AC 2.7.2-cdk-G0 (supported), ovmovie/func_800402D8 2.7.2-cdk-G0 (supported), ovmovie/func_8004033C 2.7.2-cdk-G0 (supported), ovmovie/func_80040360 2.7.2-cdk-G0 (supported), ovmovie/func_800403EC 2.7.2-cdk-G0 (supported), ovmovie/func_800404A8 2.7.2-cdk-G0 (supported), ovmovie/func_80040690 2.7.2-cdk-G0 (supported), ovmovie/func_8004072C 2.7.2-cdk-G0 (supported), ovmovie/func_800408BC 2.7.2-cdk-G0 (supported), ovmovie/func_80040954 2.7.2-cdk-G0 (supported), ovmovie/func_8004099C 2.7.2-cdk-G0 (supported), ovmovie/func_80040ED8 2.7.2-G0 (supported), ovmovie/func_80040F10 2.7.2-G0 (supported), ovmovie/func_80040F9C 2.7.2-G0 (supported), ovmovie/func_80041038 2.7.2-G0 (supported), ovmovie/func_80041044 2.7.2-G0 (supported), ovmovie/func_800410C0 2.7.2-G0 (supported), ovmovie/func_800410E0 2.7.2-G0 (supported), ovmovie/func_8004111C 2.7.2-G0 (supported), ovmovie/func_80041158 2.7.2-G0 (supported), ovmovie/func_8004117C 2.7.2-G0 (supported), ovmovie/func_800411A0 2.7.2-G0 (supported), ovmovie/func_8004129C 2.7.2-G0 (supported), ovmovie/func_80041330 2.7.2-G0 (supported), ovmovie/func_800413C0 2.7.2-G0 (supported), ovmovie/func_80041458 2.7.2-G0 (supported), ovmovie/func_800414F0 2.7.2-G0 (supported), ovmovie/func_80041508 2.7.2-G0 (supported), town/func_806D30B4 2.6.3-G0 (confirmed), town/func_808B2B04 2.6.3-G0 (confirmed).

Unconfirmed compiler attributions (still listed above; ledger/recipe_evidence.jsonl `to_confirm` names the measurement): dungeon/func_7FFEDB5C 2.7.2-cdk-G0, dungeon/func_7FFEDB64 2.7.2-cdk-G0, dungeon/func_7FFEDB6C 2.7.2-cdk-G0, dungeon/func_7FFEDB74 2.7.2-cdk-G0, dungeon/func_7FFEDB7C 2.7.2-cdk-G0, dungeon/func_7FFEDDF0 2.7.2-cdk-G0, dungeon/func_80083D40 2.7.2-cdk-G0, dungeon/func_80085574 2.7.2-cdk-G0, dungeon/func_800BFE40 2.7.2-cdk-G0, dungeon/func_800C38D4 2.7.2-cdk-G0, dungeon/func_800C9794 2.7.2-cdk-G0, dungeon/func_800D1194 2.7.2-cdk-G0, dungeon/func_800D22A4 2.7.2-cdk-G0, dungeon/func_800D22AC 2.7.2-cdk-G0, dungeon/func_800D4F00 2.7.2-cdk-G0, dungeon/func_800D4F64 2.7.2-cdk-G0, dungeon/func_800D4FC8 2.7.2-cdk-G0, dungeon/func_800D5000 2.7.2-cdk-G0, dungeon/func_800D5038 2.7.2-cdk-G0, dungeon/func_800D5070 2.7.2-cdk-G0, dungeon/func_800D50A8 2.7.2-cdk-G0, dungeon/func_80506908 2.7.2-cdk-G0, dungeon/func_809217CC 2.7.2-cdk-G0, dungeon/func_8097DD68 2.7.2-cdk-G0, dungeon/func_80983D68 2.7.2-cdk-G0, dungeon/func_80989D68 2.7.2-cdk-G0, dungeon/func_8098FD68 2.7.2-cdk-G0, dungeon/func_80995D68 2.7.2-cdk-G0, dungeon/func_8099BD68 2.7.2-cdk-G0, dungeon/func_809A25AC 2.7.2-cdk-G0, dungeon/func_809A85AC 2.7.2-cdk-G0, dungeon/func_809AE5AC 2.7.2-cdk-G0, dungeon/func_809B45AC 2.7.2-cdk-G0, dungeon/func_809BA5AC 2.7.2-cdk-G0, dungeon/func_809C05AC 2.7.2-cdk-G0, dungeon/func_809C65AC 2.7.2-cdk-G0, dungeon/func_809D1AC0 2.7.2-cdk-G0, dungeon/func_809D7AC0 2.7.2-cdk-G0, dungeon/func_809DDAC0 2.7.2-cdk-G0, dungeon/func_809E3AC0 2.7.2-cdk-G0, dungeon/func_809E9AC0 2.7.2-cdk-G0, dungeon/func_809EFAC0 2.7.2-cdk-G0, dungeon/func_80A79E5C 2.7.2-cdk-G0, dungeon/func_80A7FE5C 2.7.2-cdk-G0, dungeon/func_80A85E5C 2.7.2-cdk-G0, dungeon/func_80A8BE5C 2.7.2-cdk-G0, dungeon/func_80A91E5C 2.7.2-cdk-G0, dungeon/func_80A97E5C 2.7.2-cdk-G0, dungeon/func_80AA3E88 2.7.2-cdk-G0, dungeon/func_80AA9E88 2.7.2-cdk-G0, dungeon/func_80AAFE88 2.7.2-cdk-G0, dungeon/func_80AB5E88 2.7.2-cdk-G0, dungeon/func_80ABBE88 2.7.2-cdk-G0, dungeon/func_80AC1E88 2.7.2-cdk-G0, dungeon/func_80AC84B4 2.7.2-cdk-G0, dungeon/func_80ACE4B4 2.7.2-cdk-G0, dungeon/func_80AD44B4 2.7.2-cdk-G0, dungeon/func_80ADA4B4 2.7.2-cdk-G0, dungeon/func_80AE04B4 2.7.2-cdk-G0, dungeon/func_80AE64B4 2.7.2-cdk-G0, dungeon/func_80AEC4B4 2.7.2-cdk-G0, dungeon/func_80AF8324 2.7.2-cdk-G0, dungeon/func_80AFE324 2.7.2-cdk-G0, dungeon/func_80B04324 2.7.2-cdk-G0, dungeon/func_80B0A324 2.7.2-cdk-G0, dungeon/func_80B10324 2.7.2-cdk-G0, dungeon/func_80B16324 2.7.2-cdk-G0, dungeon/func_80B1B804 2.7.2-cdk-G0, dungeon/func_80B21804 2.7.2-cdk-G0, dungeon/func_80B27804 2.7.2-cdk-G0, dungeon/func_80B2D804 2.7.2-cdk-G0, dungeon/func_80B33804 2.7.2-cdk-G0, dungeon/func_80B39804 2.7.2-cdk-G0, dungeon/func_80B3F804 2.7.2-cdk-G0, dungeon/func_80B998A4 2.7.2-cdk-G0, dungeon/func_80B9F8A4 2.7.2-cdk-G0, dungeon/func_80BA58A4 2.7.2-cdk-G0, dungeon/func_80BAB8A4 2.7.2-cdk-G0, dungeon/func_80BB18A4 2.7.2-cdk-G0, dungeon/func_80BB78A4 2.7.2-cdk-G0, dungeon/func_80BBD8A4 2.7.2-cdk-G0, dungeon/func_80BCA420 2.7.2-cdk-G0, dungeon/func_80BD0420 2.7.2-cdk-G0, dungeon/func_80BD6420 2.7.2-cdk-G0, dungeon/func_80BDC420 2.7.2-cdk-G0, dungeon/func_80BE2420 2.7.2-cdk-G0, dungeon/func_80BE8420 2.7.2-cdk-G0, dungeon/func_80BF34AC 2.7.2-cdk-G0, dungeon/func_80BF94AC 2.7.2-cdk-G0, dungeon/func_80BFF4AC 2.7.2-cdk-G0, dungeon/func_80C054AC 2.7.2-cdk-G0, dungeon/func_80C0B4AC 2.7.2-cdk-G0, dungeon/func_80C114AC 2.7.2-cdk-G0, dungeon/func_80C6C148 2.7.2-cdk-G0, dungeon/func_80C72148 2.7.2-cdk-G0, dungeon/func_80C78148 2.7.2-cdk-G0, dungeon/func_80C7E148 2.7.2-cdk-G0, dungeon/func_80C84148 2.7.2-cdk-G0, dungeon/func_80C8A148 2.7.2-cdk-G0, dungeon/func_80C90148 2.7.2-cdk-G0, dungeon/func_80CA1B04 2.7.2-cdk-G0, dungeon/func_80CB3B04 2.7.2-cdk-G0, dungeon/func_80CC57A0 2.7.2-cdk-G0, dungeon/func_80CCB7A0 2.7.2-cdk-G0, dungeon/func_80CD17A0 2.7.2-cdk-G0, dungeon/func_80CD77A0 2.7.2-cdk-G0, dungeon/func_80CDD7A0 2.7.2-cdk-G0, dungeon/func_80CE37A0 2.7.2-cdk-G0, dungeon/func_80CEB7B8 2.7.2-cdk-G0, dungeon/func_80CF17B8 2.7.2-cdk-G0, dungeon/func_80CF77B8 2.7.2-cdk-G0, dungeon/func_80CFD7B8 2.7.2-cdk-G0, dungeon/func_80D037B8 2.7.2-cdk-G0, dungeon/func_80D097B8 2.7.2-cdk-G0, dungeon/func_80D0F7B8 2.7.2-cdk-G0, dungeon/func_80D14664 2.7.2-cdk-G0, dungeon/func_80D1A664 2.7.2-cdk-G0, dungeon/func_80D20664 2.7.2-cdk-G0, dungeon/func_80D26664 2.7.2-cdk-G0, dungeon/func_80D2C664 2.7.2-cdk-G0, dungeon/func_80D32664 2.7.2-cdk-G0, dungeon/func_80D38664 2.7.2-cdk-G0, dungeon/func_80D3EB38 2.7.2-cdk-G0, dungeon/func_80D44B38 2.7.2-cdk-G0, dungeon/func_80D4AB38 2.7.2-cdk-G0, dungeon/func_80D50B38 2.7.2-cdk-G0, dungeon/func_80D56B38 2.7.2-cdk-G0, dungeon/func_80D5CB38 2.7.2-cdk-G0, dungeon/func_80D62B38 2.7.2-cdk-G0, dungeon/func_80D918A4 2.7.2-cdk-G0, dungeon/func_80D978A4 2.7.2-cdk-G0, dungeon/func_80D9D8A4 2.7.2-cdk-G0, dungeon/func_80DA38A4 2.7.2-cdk-G0, dungeon/func_80DA98A4 2.7.2-cdk-G0, dungeon/func_80DAF8A4 2.7.2-cdk-G0, dungeon/func_80DB58A4 2.7.2-cdk-G0, dungeon/func_80DBC940 2.7.2-cdk-G0, dungeon/func_80DC2940 2.7.2-cdk-G0, dungeon/func_80DC8940 2.7.2-cdk-G0, dungeon/func_80DCE940 2.7.2-cdk-G0, dungeon/func_80DD4940 2.7.2-cdk-G0, dungeon/func_80DDA940 2.7.2-cdk-G0, dungeon/func_80DE0940 2.7.2-cdk-G0, dungeon/func_80DEB9BC 2.7.2-cdk-G0, dungeon/func_80DF19BC 2.7.2-cdk-G0, dungeon/func_80DF79BC 2.7.2-cdk-G0, dungeon/func_80DFD9BC 2.7.2-cdk-G0, dungeon/func_80E039BC 2.7.2-cdk-G0, dungeon/func_80E099BC 2.7.2-cdk-G0, dungeon/func_80E39884 2.7.2-cdk-G0, dungeon/func_80E3F884 2.7.2-cdk-G0, dungeon/func_80E45884 2.7.2-cdk-G0, dungeon/func_80E4B884 2.7.2-cdk-G0, dungeon/func_80E51884 2.7.2-cdk-G0, dungeon/func_80E57884 2.7.2-cdk-G0, dungeon/func_80E5D884 2.7.2-cdk-G0, dungeon/func_80E643D8 2.7.2-cdk-G0, dungeon/func_80E6A3D8 2.7.2-cdk-G0, dungeon/func_80E703D8 2.7.2-cdk-G0, dungeon/func_80E763D8 2.7.2-cdk-G0, dungeon/func_80E7C3D8 2.7.2-cdk-G0, dungeon/func_80E823D8 2.7.2-cdk-G0, dungeon/func_80E883D8 2.7.2-cdk-G0, dungeon/func_80EE271C 2.7.2-cdk-G0, dungeon/func_80EE871C 2.7.2-cdk-G0, dungeon/func_80EEE71C 2.7.2-cdk-G0, dungeon/func_80EF471C 2.7.2-cdk-G0, dungeon/func_80EFA71C 2.7.2-cdk-G0, dungeon/func_80F0071C 2.7.2-cdk-G0, dungeon/func_80F0671C 2.7.2-cdk-G0, dungeon/func_80F0BAAC 2.7.2-cdk-G0, dungeon/func_80F11AAC 2.7.2-cdk-G0, dungeon/func_80F17AAC 2.7.2-cdk-G0, dungeon/func_80F1DAAC 2.7.2-cdk-G0, dungeon/func_80F23AAC 2.7.2-cdk-G0, dungeon/func_80F29AAC 2.7.2-cdk-G0, dungeon/func_80F2FAAC 2.7.2-cdk-G0, dungeon/func_80F5FA0C 2.7.2-cdk-G0, dungeon/func_80F65A0C 2.7.2-cdk-G0, dungeon/func_80F6BA0C 2.7.2-cdk-G0, dungeon/func_80F71A0C 2.7.2-cdk-G0, dungeon/func_80F77A0C 2.7.2-cdk-G0, dungeon/func_80F7DA0C 2.7.2-cdk-G0, dungeon/func_80F83A0C 2.7.2-cdk-G0, dungeon/func_80FDDB14 2.7.2-cdk-G0, dungeon/func_80FE3B14 2.7.2-cdk-G0, dungeon/func_80FE9B14 2.7.2-cdk-G0, dungeon/func_80FEFB14 2.7.2-cdk-G0, dungeon/func_80FF5B14 2.7.2-cdk-G0, dungeon/func_80FFBB14 2.7.2-cdk-G0, dungeon/func_81001B14 2.7.2-cdk-G0, dungeon/func_81007810 2.7.2-cdk-G0, dungeon/func_8100D810 2.7.2-cdk-G0, dungeon/func_81013810 2.7.2-cdk-G0, dungeon/func_81019810 2.7.2-cdk-G0, dungeon/func_8101F810 2.7.2-cdk-G0, dungeon/func_81025810 2.7.2-cdk-G0, dungeon/func_8102B810 2.7.2-cdk-G0, dungeon/func_810321F8 2.7.2-cdk-G0, dungeon/func_810381F8 2.7.2-cdk-G0, dungeon/func_8103E1F8 2.7.2-cdk-G0, dungeon/func_810441F8 2.7.2-cdk-G0, dungeon/func_8104A1F8 2.7.2-cdk-G0, dungeon/func_810501F8 2.7.2-cdk-G0, dungeon/func_810561F8 2.7.2-cdk-G0, dungeon/func_8105B990 2.7.2-cdk-G0, dungeon/func_81061990 2.7.2-cdk-G0, dungeon/func_81067990 2.7.2-cdk-G0, dungeon/func_8106D990 2.7.2-cdk-G0, dungeon/func_81073990 2.7.2-cdk-G0, dungeon/func_81079990 2.7.2-cdk-G0, dungeon/func_8107F990 2.7.2-cdk-G0, dungeon/func_81085DB4 2.7.2-cdk-G0, dungeon/func_81086878 2.7.2-cdk-G0, dungeon/func_8108BDB4 2.7.2-cdk-G0, dungeon/func_8108C878 2.7.2-cdk-G0, dungeon/func_81091DB4 2.7.2-cdk-G0, dungeon/func_81092878 2.7.2-cdk-G0, dungeon/func_81097DB4 2.7.2-cdk-G0, dungeon/func_81098878 2.7.2-cdk-G0, dungeon/func_8109DDB4 2.7.2-cdk-G0, dungeon/func_8109E878 2.7.2-cdk-G0, dungeon/func_810A3DB4 2.7.2-cdk-G0, dungeon/func_810A4878 2.7.2-cdk-G0, dungeon/func_810A9DB4 2.7.2-cdk-G0, dungeon/func_810AA878 2.7.2-cdk-G0, dungeon/func_810AF96C 2.7.2-cdk-G0, dungeon/func_810B596C 2.7.2-cdk-G0, dungeon/func_810BB96C 2.7.2-cdk-G0, dungeon/func_810C196C 2.7.2-cdk-G0, dungeon/func_810C796C 2.7.2-cdk-G0, dungeon/func_810CD96C 2.7.2-cdk-G0, dungeon/func_810D396C 2.7.2-cdk-G0, dungeon/func_81252B28 2.7.2-cdk-G0, dungeon/func_81253620 2.7.2-cdk-G0, dungeon/func_812540F0 2.7.2-cdk-G0, dungeon/func_812543E8 2.7.2-cdk-G0, dungeon/func_81258B28 2.7.2-cdk-G0, dungeon/func_81259620 2.7.2-cdk-G0, dungeon/func_8125A0F0 2.7.2-cdk-G0, dungeon/func_8125A3E8 2.7.2-cdk-G0, dungeon/func_8125EB28 2.7.2-cdk-G0, dungeon/func_8125F620 2.7.2-cdk-G0, dungeon/func_812600F0 2.7.2-cdk-G0, dungeon/func_812603E8 2.7.2-cdk-G0, dungeon/func_81264B28 2.7.2-cdk-G0, dungeon/func_81265620 2.7.2-cdk-G0, dungeon/func_812660F0 2.7.2-cdk-G0, dungeon/func_812663E8 2.7.2-cdk-G0, dungeon/func_8126AB28 2.7.2-cdk-G0, dungeon/func_8126B620 2.7.2-cdk-G0, dungeon/func_8126C0F0 2.7.2-cdk-G0, dungeon/func_8126C3E8 2.7.2-cdk-G0, dungeon/func_81270B28 2.7.2-cdk-G0, dungeon/func_81271620 2.7.2-cdk-G0, dungeon/func_812720F0 2.7.2-cdk-G0, dungeon/func_812723E8 2.7.2-cdk-G0, dungeon/func_81276B28 2.7.2-cdk-G0, dungeon/func_81277620 2.7.2-cdk-G0, dungeon/func_812780F0 2.7.2-cdk-G0, dungeon/func_812783E8 2.7.2-cdk-G0, dungeon/func_812A90B0 2.7.2-cdk-G0, dungeon/func_812AF0B0 2.7.2-cdk-G0, dungeon/func_812B50B0 2.7.2-cdk-G0, dungeon/func_812BB0B0 2.7.2-cdk-G0, dungeon/func_812C10B0 2.7.2-cdk-G0, dungeon/func_812C70B0 2.7.2-cdk-G0, dungeon/func_812CD0B0 2.7.2-cdk-G0, dungeon/func_8132629C 2.7.2-cdk-G0, dungeon/func_81326484 2.7.2-cdk-G0, dungeon/func_81326708 2.7.2-cdk-G0, dungeon/func_81328A14 2.7.2-cdk-G0, dungeon/func_81328A1C 2.7.2-cdk-G0, dungeon/func_81329544 2.7.2-cdk-G0, dungeon/func_81329928 2.7.2-cdk-G0, dungeon/func_81337BA8 2.7.2-cdk-G0, dungeon/func_81337E44 2.7.2-cdk-G0, dungeon/func_813383A8 2.7.2-cdk-G0, dungeon/func_813383C4 2.7.2-cdk-G0, dungeon/func_813383E8 2.7.2-cdk-G0, dungeon/func_81338408 2.7.2-cdk-G0, dungeon/func_81810530 2.7.2-cdk-G0, dungeon/func_8181053C 2.7.2-cdk-G0, dungeon/func_81811CCC 2.7.2-cdk-G0, dungeon/func_81935128 2.7.2-cdk-G0, dungeon/func_81947288 2.7.2-cdk-G0, dungeon/func_8199AF84 2.7.2-cdk-G0, dungeon/func_8199B124 2.7.2-cdk-G0, main/func_80012358 2.7.2-cdk-G0, main/func_80019E34 2.7.2-G0, main/func_8001C7F4 2.7.2, main/func_8001E3A0 2.6.3-G0, main/func_8001E4E8 2.6.3-G0, main/func_800207D4 2.7.2-G0, main/func_80020F68 2.7.2, main/func_800213A0 2.6.3-G0, main/func_800213FC 2.6.3-G0, main/func_800214DC 2.6.3-G0, main/func_8002155C 2.6.3-G0, main/func_8002159C 2.6.3-G0, main/func_800215DC 2.6.3-G0, main/func_8002161C 2.6.3-G0, main/func_80021684 2.6.3-G0, main/func_800216DC 2.6.3-G0, main/func_80021730 2.6.3-G0, main/func_80021768 2.6.3-G0, slus/code 2.7.2-cdk, town/func_800B29F8 2.7.2-cdk-G0, town/func_800B6108 2.7.2-cdk-G0, town/func_800B6D50 2.7.2-cdk-G0, town/func_800B7738 2.7.2-cdk-G0, town/func_802EE53C 2.6.3-G0, town/func_802EE624 2.6.3-G0, town/func_802EE6CC 2.6.3-G0, town/func_802EE6F4 2.6.3-G0, town/func_802EE7A8 2.6.3-G0, town/func_802EE7B0 2.6.3-G0, town/func_802F1394 2.6.3-G0, town/func_80333574 2.7.2-cdk-G0, town/func_803335A0 2.7.2-cdk-G0, town/func_8046A9C8 2.7.2-cdk-G0, town/func_8046AB24 2.7.2-cdk-G0, town/func_8046AC54 2.7.2-cdk-G0, town/func_804804E4 2.7.2-cdk-G0, town/func_80480530 2.7.2-cdk-G0, town/func_80481244 2.7.2-cdk-G0, town/func_8048189C 2.7.2-cdk-G0, town/func_80481D68 2.7.2-cdk-G0, town/func_8048225C 2.7.2-cdk-G0, town/func_804822EC 2.7.2-cdk-G0, town/func_804B7930 2.7.2-cdk-G0, town/func_804B7950 2.7.2-cdk-G0, town/func_804B7970 2.7.2-cdk-G0, town/func_804B7990 2.7.2-cdk-G0, town/func_804B79B0 2.7.2-cdk-G0, town/func_804B79D0 2.7.2-cdk-G0, town/func_804B7A28 2.7.2-cdk-G0, town/func_804B7A48 2.7.2-cdk-G0, town/func_804B7A68 2.7.2-cdk-G0, town/func_804B9500 2.7.2-cdk-G0, town/func_804B99CC 2.7.2-cdk-G0, town/func_804B9EC0 2.7.2-cdk-G0, town/func_804B9F50 2.7.2-cdk-G0, town/func_804D0FA8 2.7.2-cdk-G0, town/func_804D1474 2.7.2-cdk-G0, town/func_804D1968 2.7.2-cdk-G0, town/func_804D19F8 2.7.2-cdk-G0, town/func_804D887C 2.7.2-cdk-G0, town/func_804D8D48 2.7.2-cdk-G0, town/func_804D923C 2.7.2-cdk-G0, town/func_804D92CC 2.7.2-cdk-G0, town/func_804F08A0 2.7.2-cdk-G0, town/func_804F0D6C 2.7.2-cdk-G0, town/func_804F1260 2.7.2-cdk-G0, town/func_804F12F0 2.7.2-cdk-G0, town/func_80500784 2.7.2-cdk-G0, town/func_80500C50 2.7.2-cdk-G0, town/func_80501144 2.7.2-cdk-G0, town/func_805011D4 2.7.2-cdk-G0, town/func_8050E168 2.7.2-cdk-G0, town/func_8050E82C 2.7.2-cdk-G0, town/func_8050ECF8 2.7.2-cdk-G0, town/func_8050F1EC 2.7.2-cdk-G0, town/func_8050F27C 2.7.2-cdk-G0, town/func_805204E4 2.7.2-cdk-G0, town/func_805209B0 2.7.2-cdk-G0, town/func_80520EA4 2.7.2-cdk-G0, town/func_80520F34 2.7.2-cdk-G0, town/func_805501CC 2.7.2-cdk-G0, town/func_80550698 2.7.2-cdk-G0, town/func_80550B8C 2.7.2-cdk-G0, town/func_80550C1C 2.7.2-cdk-G0, town/func_80559718 2.7.2-cdk-G0, town/func_80559BE4 2.7.2-cdk-G0, town/func_8055A0D8 2.7.2-cdk-G0, town/func_8055A168 2.7.2-cdk-G0, town/func_80579168 2.7.2-cdk-G0, town/func_805797CC 2.7.2-cdk-G0, town/func_80579C98 2.7.2-cdk-G0, town/func_8057A18C 2.7.2-cdk-G0, town/func_8057A21C 2.7.2-cdk-G0, town/func_8059E130 2.7.2-cdk-G0, town/func_8059E188 2.7.2-cdk-G0, town/func_8059E4A0 2.7.2-cdk-G0, town/func_8059E6D0 2.7.2-cdk-G0, town/func_8059E808 2.7.2-cdk-G0, town/func_8059F450 2.7.2-cdk-G0, town/func_8059FB98 2.7.2-cdk-G0, town/func_805A0064 2.7.2-cdk-G0, town/func_805A0558 2.7.2-cdk-G0, town/func_805A05E8 2.7.2-cdk-G0, town/func_805D210C 2.7.2-cdk-G0, town/func_805D211C 2.7.2-cdk-G0, town/func_805D212C 2.7.2-cdk-G0, town/func_805D2174 2.7.2-cdk-G0, town/func_805D2194 2.7.2-cdk-G0, town/func_805D2200 2.7.2-cdk-G0, town/func_805D2228 2.7.2-cdk-G0, town/func_805D2E0C 2.7.2-cdk-G0, town/func_805D2E2C 2.7.2-cdk-G0, town/func_805D4468 2.7.2-cdk-G0, town/func_805D4934 2.7.2-cdk-G0, town/func_805D4E28 2.7.2-cdk-G0, town/func_805D4EB8 2.7.2-cdk-G0, town/func_806011DC 2.7.2-cdk-G0, town/func_80601310 2.7.2-cdk-G0, town/func_80601338 2.7.2-cdk-G0, town/func_80601B6C 2.7.2-cdk-G0, town/func_806022B4 2.7.2-cdk-G0, town/func_80602780 2.7.2-cdk-G0, town/func_80602C74 2.7.2-cdk-G0, town/func_80602D04 2.7.2-cdk-G0, town/func_806156E0 2.7.2-cdk-G0, town/func_80615708 2.7.2-cdk-G0, town/func_80615F3C 2.7.2-cdk-G0, town/func_80616684 2.7.2-cdk-G0, town/func_80616B50 2.7.2-cdk-G0, town/func_80617044 2.7.2-cdk-G0, town/func_806170D4 2.7.2-cdk-G0, town/func_80632100 2.7.2-cdk-G0, town/func_806321D0 2.7.2-cdk-G0, town/func_80632230 2.7.2-cdk-G0, town/func_80632258 2.7.2-cdk-G0, town/func_8063288C 2.7.2-cdk-G0, town/func_80632D58 2.7.2-cdk-G0, town/func_8063324C 2.7.2-cdk-G0, town/func_806332DC 2.7.2-cdk-G0, town/func_8064711C 2.7.2-cdk-G0, town/func_80647190 2.7.2-cdk-G0, town/func_806471E8 2.7.2-cdk-G0, town/func_80647920 2.7.2-cdk-G0, town/func_80647DEC 2.7.2-cdk-G0, town/func_806482E0 2.7.2-cdk-G0, town/func_80648370 2.7.2-cdk-G0, town/func_8065BF68 2.7.2-cdk-G0, town/func_8065BF88 2.7.2-cdk-G0, town/func_8065BFA8 2.7.2-cdk-G0, town/func_8065BFF4 2.7.2-cdk-G0, town/func_8067F74C 2.7.2-cdk-G0, town/func_80680170 2.7.2-cdk-G0, town/func_806807C8 2.7.2-cdk-G0, town/func_80680C94 2.7.2-cdk-G0, town/func_80681188 2.7.2-cdk-G0, town/func_80681218 2.7.2-cdk-G0, town/func_80698240 2.7.2-cdk-G0, town/func_80698898 2.7.2-cdk-G0, town/func_80698D64 2.7.2-cdk-G0, town/func_80699258 2.7.2-cdk-G0, town/func_806992E8 2.7.2-cdk-G0, town/func_806A973C 2.7.2-cdk-G0, town/func_806A9C08 2.7.2-cdk-G0, town/func_806AA0FC 2.7.2-cdk-G0, town/func_806AA18C 2.7.2-cdk-G0, town/func_806C5EDC 2.7.2-cdk-G0, town/func_806C6858 2.7.2-cdk-G0, town/func_806C6FA0 2.7.2-cdk-G0, town/func_806C746C 2.7.2-cdk-G0, town/func_806C7960 2.7.2-cdk-G0, town/func_806C79F0 2.7.2-cdk-G0, town/func_806C9180 2.7.2-cdk-G0, town/func_806C937C 2.7.2-cdk-G0, town/func_806C9388 2.7.2-cdk-G0, town/func_806C9970 2.7.2-cdk-G0, town/func_806C9E3C 2.7.2-cdk-G0, town/func_806CA330 2.7.2-cdk-G0, town/func_806CA3C0 2.7.2-cdk-G0, town/func_806CB180 2.7.2-cdk-G0, town/func_806CB384 2.7.2-cdk-G0, town/func_806CB96C 2.7.2-cdk-G0, town/func_806CBE38 2.7.2-cdk-G0, town/func_806CC32C 2.7.2-cdk-G0, town/func_806CC3BC 2.7.2-cdk-G0, town/func_806CD32C 2.7.2-cdk-G0, town/func_806CD914 2.7.2-cdk-G0, town/func_806CDDE0 2.7.2-cdk-G0, town/func_806CE2D4 2.7.2-cdk-G0, town/func_806CE364 2.7.2-cdk-G0, town/func_806CF0F8 2.7.2-cdk-G0, town/func_806CF190 2.7.2-cdk-G0, town/func_806CF778 2.7.2-cdk-G0, town/func_806CFC44 2.7.2-cdk-G0, town/func_806D0138 2.7.2-cdk-G0, town/func_806D01C8 2.7.2-cdk-G0, town/func_806D1100 2.7.2-cdk-G0, town/func_806D16E8 2.7.2-cdk-G0, town/func_806D1BB4 2.7.2-cdk-G0, town/func_806D20A8 2.7.2-cdk-G0, town/func_806D2138 2.7.2-cdk-G0, town/func_806D561C 2.7.2-cdk-G0, town/func_806D5AE8 2.7.2-cdk-G0, town/func_806D5FDC 2.7.2-cdk-G0, town/func_806D606C 2.7.2-cdk-G0, town/func_806D8580 2.7.2-cdk-G0, town/func_806D8FC8 2.7.2-cdk-G0, town/func_806D9494 2.7.2-cdk-G0, town/func_806D9988 2.7.2-cdk-G0, town/func_806D9A18 2.7.2-cdk-G0, town/func_806DB100 2.7.2-cdk-G0, town/func_806DB114 2.7.2-cdk-G0, town/func_806DB790 2.7.2-cdk-G0, town/func_806DBC5C 2.7.2-cdk-G0, town/func_806DC150 2.7.2-cdk-G0, town/func_806DC1E0 2.7.2-cdk-G0, town/func_806F21C4 2.7.2-cdk-G0, town/func_806F2690 2.7.2-cdk-G0, town/func_806F2B84 2.7.2-cdk-G0, town/func_806F2C14 2.7.2-cdk-G0, town/func_8070E9D4 2.7.2-cdk-G0, town/func_8070E9F4 2.7.2-cdk-G0, town/func_8070F6BC 2.7.2-cdk-G0, town/func_8070F6D0 2.7.2-cdk-G0, town/func_8070F6E4 2.7.2-cdk-G0, town/func_8070F6F8 2.7.2-cdk-G0, town/func_8070F708 2.7.2-cdk-G0, town/func_8070F718 2.7.2-cdk-G0, town/func_8070F740 2.7.2-cdk-G0, town/func_8070F768 2.7.2-cdk-G0, town/func_8070F790 2.7.2-cdk-G0, town/func_8070F854 2.7.2-cdk-G0, town/func_8070F874 2.7.2-cdk-G0, town/func_8070F894 2.7.2-cdk-G0, town/func_8070F8EC 2.7.2-cdk-G0, town/func_8070F90C 2.7.2-cdk-G0, town/func_80710138 2.7.2-cdk-G0, town/func_80710880 2.7.2-cdk-G0, town/func_80710D4C 2.7.2-cdk-G0, town/func_80711240 2.7.2-cdk-G0, town/func_807112D0 2.7.2-cdk-G0, town/func_8072A288 2.7.2-cdk-G0, town/func_8072A2A8 2.7.2-cdk-G0, town/func_8072A308 2.7.2-cdk-G0, town/func_8072AB30 2.7.2-cdk-G0, town/func_8072AFFC 2.7.2-cdk-G0, town/func_8072B4F0 2.7.2-cdk-G0, town/func_8072B580 2.7.2-cdk-G0, town/func_8074C98C 2.7.2-cdk-G0, town/func_8074CF74 2.7.2-cdk-G0, town/func_8074D440 2.7.2-cdk-G0, town/func_8074D934 2.7.2-cdk-G0, town/func_8074D9C4 2.7.2-cdk-G0, town/func_80761AF8 2.7.2-cdk-G0, town/func_80761B50 2.7.2-cdk-G0, town/func_80761C08 2.7.2-cdk-G0, town/func_80761D30 2.7.2-cdk-G0, town/func_807623D0 2.7.2-cdk-G0, town/func_8076289C 2.7.2-cdk-G0, town/func_80762D90 2.7.2-cdk-G0, town/func_80762E20 2.7.2-cdk-G0, town/func_807707C0 2.7.2-cdk-G0, town/func_80770C8C 2.7.2-cdk-G0, town/func_80771180 2.7.2-cdk-G0, town/func_80771210 2.7.2-cdk-G0, town/func_80774928 2.7.2-cdk-G0, town/func_80774F28 2.7.2-cdk-G0, town/func_807753F4 2.7.2-cdk-G0, town/func_807758E8 2.7.2-cdk-G0, town/func_80775978 2.7.2-cdk-G0, town/func_80777128 2.7.2-cdk-G0, town/func_80777728 2.7.2-cdk-G0, town/func_80777BF4 2.7.2-cdk-G0, town/func_807780E8 2.7.2-cdk-G0, town/func_80778178 2.7.2-cdk-G0, town/func_8077E2A4 2.7.2-cdk-G0, town/func_8077E770 2.7.2-cdk-G0, town/func_8077EC64 2.7.2-cdk-G0, town/func_8077ECF4 2.7.2-cdk-G0, town/func_807851EC 2.7.2-cdk-G0, town/func_80785824 2.7.2-cdk-G0, town/func_80785CF0 2.7.2-cdk-G0, town/func_807861E4 2.7.2-cdk-G0, town/func_80786274 2.7.2-cdk-G0, town/func_8079A84C 2.7.2-cdk-G0, town/func_8079AD18 2.7.2-cdk-G0, town/func_8079B20C 2.7.2-cdk-G0, town/func_8079B29C 2.7.2-cdk-G0, town/func_8081AAC0 2.7.2-cdk-G0, town/func_8081AB04 2.7.2-cdk-G0, town/func_808753FC 2.6.3-G0, town/func_80875684 2.6.3-G0, town/func_80875808 2.6.3-G0, town/func_80875858 2.6.3-G0, town/func_808758AC 2.6.3-G0, town/func_8087590C 2.6.3-G0, town/func_80878110 2.6.3-G0, town/func_8087FFD0 2.6.3-G0, town/func_8087FFF0 2.6.3-G0, town/func_80880010 2.6.3-G0, town/func_80880030 2.6.3-G0, town/func_80880050 2.6.3-G0, town/func_80880070 2.6.3-G0, town/func_80880274 2.6.3-G0, town/func_80883524 2.6.3-G0, town/func_808B3104 2.6.3-G0, town/func_808B3374 2.6.3-G0, town/func_808B95EC 2.6.3-G0, town/func_808B960C 2.6.3-G0, town/func_808B962C 2.6.3-G0, town/func_808B964C 2.6.3-G0, town/func_808B966C 2.6.3-G0, town/func_808B968C 2.6.3-G0, town/func_808B98AC 2.6.3-G0, town/func_8094DB74 2.7.2-G0, town/func_8094EB74 2.7.2-G0, town/func_8094FB70 2.7.2-G0, town/func_80950B70 2.7.2-G0, town/func_80951B70 2.7.2-G0, town/func_8095212C 2.7.2-G0, town/func_80952C34 2.7.2-G0, town/func_80956FA8 2.7.2-cdk-G0, town/func_8096AC8C 2.7.2-cdk-G0, town/func_8096AD44 2.7.2-cdk-G0, town/func_8096DB00 2.7.2-cdk-G0, town/func_8096DFCC 2.7.2-cdk-G0, town/func_8096DFEC 2.7.2-cdk-G0.

Sony SDK library objects (ledger/sdk_objects.jsonl, whole-object byte match; not listed above): main/func_80021644, main/func_80021654, main/func_80021664, main/func_80021674, main/func_800216BC, main/func_800216CC, main/func_80021798, main/func_800217A8, main/func_800217B8, main/func_800217C8, main/func_800218A0, main/func_80021958, main/func_800219C4, ovmovie/func_80041638, ovmovie/func_8004166C, town/func_802F1644, town/func_802F1654, town/func_802F1664, town/func_802F1674, town/func_802F16BC, town/func_802F16CC.
Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 24.

Union trades (`ledger/union_trades.jsonl`, owner 2026-10-13: kept as nicer-than-a-pin but TRACKED - their plausibility as original 1997 code is unproven; census work/native_lane/_r118/union_census): zero-init one-member idiom (accepted trade): 30 sites in 6 rows (6 rows still carry a union; most: func_8180B064 16, func_80098378 9, func_808119EC 2, func_809A38E4 1); host-merge levers (int/pointer share one union variable; owner ruling pending): 11 sites in 10 rows (9 rows still carry a union; most: func_81983138 2, func_800C7F80 1, func_80EF3FB0 1, func_80EF9FB0 1). Resolved by re-spells (original-C shapes, byte-exact): 11 of 52 recorded sites. Refused union levers (float launders, dead-value keepers) are recorded in the hard basket.

Dead-branch trades (decision 45, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_branch - a one-arm `if (value) { local = 0; }` over a retail-evidenced value whose arm sets a never-read local, reconstructing a set-but-unused leftover that jump2 deletes while delete_computation keeps the load): 4 rows (func_800A3D40, func_80B467DC, func_8105A724, func_81339F68).

Dead-arm trades (decision 46, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_arm - a never-taken arm over a never-reassigned local that combine folds after flow counted it, so sched/global/reload still see it and jump2 deletes it; the arm body is a RECONSTRUCTION, only its shape is byte-evidenced): 1 rows (func_80DE48EC).

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 4,131,872 | 100.0% |
| L1 | 4,131,872 | 100.0% |
| L2 | 4,129,740 | 99.9% |
| L3 | 4,076,964 | 98.7% |
| L4 | 0 | 0.0% |
| L5 | 0 | 0.0% |

On shared record headers (T7, `include/records/`): 2486 rows, 1,375,492 bytes (33.3%); records used: 98.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 0 rows (0 B), tail_jump 19 rows (14,352 B), not_in_module 10,841 rows (4,131,872 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 26 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 142 / 19,536 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
