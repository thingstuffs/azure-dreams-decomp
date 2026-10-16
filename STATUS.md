# azure-dreams-decomp status

Generated 2026-10-16T01:20:16Z. Pin `82f20568` (82f20568997a, raw/ frozen at 2026-09-07T12:42:23Z).

## Denominator (rows matched at the pin)

| container | rows | bytes | stock rows | stock bytes | baseline exact | exact bytes | unverified |
|---|---:|---:|---:|---:|---:|---:|---:|
| slus | 884 | 473,788 | 884 | 473,788 | 884 | 473,788 | 0 |
| main | 422 | 62,736 | 422 | 62,736 | 422 | 62,736 | 0 |
| town | 2803 | 467,892 | 2803 | 467,892 | 2803 | 467,892 | 0 |
| dungeon | 3880 | 1,943,704 | 3880 | 1,943,704 | 3880 | 1,943,704 | 0 |
| ovmovie | 28 | 5,516 | 28 | 5,516 | 28 | 5,516 | 0 |
| ALL | 8017 | 2,953,636 | 8017 | 2,953,636 | 8017 | 2,953,636 | 0 |

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
| dungeon_ovl_18d6800 | 12 | current: complete TU + all windows + genuine |
| dungeon_ovl_18ee800 | 8 | current: complete TU + all windows + genuine |
| dungeon_ovl_18e8800 | 4 | current: complete TU + all windows + genuine |
| dungeon_ovl_18b2800 | 11 | current: complete TU + all windows + genuine |
| ovmovie_libpress | 17 | current: complete TU + all windows + genuine |
| dungeon_engine_dungeon_util | 43 | current: complete TU + all windows + genuine |
| dungeon_engine_experience | 17 | current: complete TU + all windows + genuine |
| dungeon_engine_transition_effects | 12 | current: complete TU + all windows + genuine |
| dungeon_engine_entity_effects | 21 | current: complete TU + all windows + genuine |
| dungeon_engine_tile_map | 25 | current: complete TU + all windows + genuine |
| dungeon_engine_entity_panel | 21 | current: complete TU + all windows + genuine |
| dungeon_engine_particle_effects | 11 | current: complete TU + all windows + genuine |
| dungeon_engine_screen_effects | 4 | current: complete TU + all windows + genuine |
| dungeon_engine_trap_effects | 38 | current: complete TU + all windows + genuine |
| dungeon_engine_menu_effects | 38 | current: complete TU + all windows + genuine |
| dungeon_engine_effect_dispatch | 18 | current: complete TU + all windows + genuine |
| town_door_22f08 | 25 | current: complete TU + all windows + genuine |
| town_player_init_12868 | 12 | current: complete TU + all windows + genuine |
| town_town_windows_1f5b8 | 36 | current: complete TU + all windows + genuine |
| dungeon_town_load | 5 | current: complete TU + all windows + genuine |
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
| dungeon_ovl_12c50ac | 2 | current: complete TU + all windows + genuine |
| dungeon_ovl_e0365c | 38 | current: complete TU + all windows + genuine |
| dungeon_ovl_be1084 | 6 | current: complete TU + all windows + genuine |
| dungeon_ovl_cb3000 | 39 | current: complete TU + all windows + genuine |
| dungeon_ovl_9950e8 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_d5b0b8 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_cb9000 | 39 | current: complete TU + all windows + genuine |
| dungeon_ovl_cc5000 | 39 | current: complete TU + all windows + genuine |
| dungeon_ovl_ccb000 | 39 | current: complete TU + all windows + genuine |
| dungeon_ovl_cd7000 | 39 | current: complete TU + all windows + genuine |
| dungeon_ovl_18be820 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e705800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_194286c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e711800 | 2 | current: complete TU + all windows + genuine |
| dungeon_ovl_1966800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e765800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e67b800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e71d800 | 4 | current: complete TU + all windows + genuine |
| dungeon_ovl_193c848 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_1954800 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e6b7800 | 8 | current: complete TU + all windows + genuine |
| dungeon_ovl_7e6e1800 | 9 | current: complete TU + all windows + genuine |
| dungeon_ovl_19c088c | 11 | current: complete TU + all windows + genuine |
| dungeon_ovl_1936800 | 16 | current: complete TU + all windows + genuine |
| dungeon_ovl_190d6a4 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_190081c | 2 | current: complete TU + all windows + genuine |
| dungeon_ovl_1906f98 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_190681c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_191284c | 4 | current: complete TU + all windows + genuine |
| dungeon_ovl_19134e4 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_18c4828 | 9 | current: complete TU + all windows + genuine |
| dungeon_ovl_190c800 | 2 | current: complete TU + all windows + genuine |
| dungeon_ovl_191e87c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_191eef8 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_be7084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bf3084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bf9084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c05084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a130dc | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a190dc | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a250dc | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a2b0dc | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a370dc | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c3b09c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c4709c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c4d09c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bbd094 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bc9094 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bcf094 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bdb094 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f559800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f535800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f51d800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_bb1054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_9ef054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_9fb054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a01054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_a0d054 | 1 | current: complete TU + all windows + genuine |
| dungeon_resource03_slot0 | 28 | current: complete TU + all windows + genuine |
| dungeon_resource17_slot0 | 26 | current: complete TU + all windows + genuine |
| dungeon_resource07_slot0 | 28 | current: complete TU + all windows + genuine |
| dungeon_resource08_slot0 | 36 | current: complete TU + all windows + genuine |
| dungeon_resource10_slot0 | 41 | current: complete TU + all windows + genuine |
| dungeon_resource12_slot0 | 39 | current: complete TU + all windows + genuine |
| dungeon_resource16_slot0 | 32 | current: complete TU + all windows + genuine |
| dungeon_resource06_slot0 | 38 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f0f7800_p01 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f0f7800_p03 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f0f7800_p04 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f0f7800_p05 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f0f7800_p07 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f1d5800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f1ed800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f211800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f217800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f223800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f23b800 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f43f800_p01 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f43f800_p02 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f469800_p01 | 12 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f469800_p03 | 5 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f469800_p04 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f469800_p06 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f469800_p07 | 3 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f511800_p01 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_7f511800_p03 | 2 | current: complete TU + all windows + genuine |
| dungeon_ovl_c5909c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c89084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c8f084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_c9b084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_ca1084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_cad084 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_d10bc4_p02 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_d16bc4_p02 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_d1cbc4_p02 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_d28bc4_p02 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_d2ebc4_p02 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_dd9000_p03 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_e09000_code | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_e15054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_e1b054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_e27054 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_edb06c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_ee706c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_eed06c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_ef906c | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_f7d070_p01 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_f8f070 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_f95070 | 1 | current: complete TU + all windows + genuine |
| dungeon_ovl_fa1070 | 1 | current: complete TU + all windows + genuine |
| town_ovl_79dd70 | 1 | current: complete TU + all windows + genuine |
| town_ovl_6490c0 | 1 | current: complete TU + all windows + genuine |
| town_ovl_64b0c0 | 1 | current: complete TU + all windows + genuine |
| town_ovl_64f0c0 | 1 | current: complete TU + all windows + genuine |
| town_ovl_64f118 | 1 | current: complete TU + all windows + genuine |
| town_ovl_6510c0 | 1 | current: complete TU + all windows + genuine |
| town_ovl_480100 | 2 | current: complete TU + all windows + genuine |
| town_ovl_4f9100 | 1 | current: complete TU + all windows + genuine |
| town_ovl_629100 | 1 | current: complete TU + all windows + genuine |
| town_ovl_47027c | 1 | current: complete TU + all windows + genuine |
| town_ovl_5c7308 | 1 | current: complete TU + all windows + genuine |
| town_ovl_65b134 | 2 | current: complete TU + all windows + genuine |
| town_ovl_64d298 | 1 | current: complete TU + all windows + genuine |
| town_ovl_450958 | 1 | current: complete TU + all windows + genuine |
| town_ovl_4d9100 | 1 | current: complete TU + all windows + genuine |
| town_ovl_71a1ec | 1 | current: complete TU + all windows + genuine |
| town_ovl_8d2114 | 1 | current: complete TU + all windows + genuine |

Placement alone does not override any lower-level or source-residue guard.

## Shape census: pinned raw text vs current clean tree (files / bytes carrying each defect)

| defect | files (pin) | bytes (pin) | % bytes | files (clean) | bytes (clean) | % bytes |
|---|---:|---:|---:|---:|---:|---:|
| m2c boilerplate block | 2331 | 510,576 | 17.3% | 0 | 0 | 0.0% |
| M2C_FIELD raw offsets | 2950 | 1,449,308 | 49.1% | 0 | 0 | 0.0% |
| m2c local names | 5181 | 2,162,116 | 73.2% | 7 | 25,812 | 0.9% |
| ASM_ pins | 2135 | 1,456,292 | 49.3% | 0 | 0 | 0.0% |
| goto | 1545 | 1,312,068 | 44.4% | 271 | 326,328 | 11.0% |
| computed-goto jump table | 317 | 436,504 | 14.8% | 1 | 16 | 0.0% |
| inline asm outside macros (clean: minus the composite-row carve debt, counted on its own line below) | 360 | 242,072 | 8.2% | 7 | 8,984 | 0.3% |
| fidelity blocking site, LABEL_AS_CALL/PASSTHRU_NO_ARGS (pin: baseline audit of the frozen text; clean: live, L5 predicate) | 1489 | 676,096 | 22.9% | 0 | 0 | 0.0% |
| any fidelity site (pin: any baseline audit class; clean: live L5 `fidelity_site` predicate, = levels.py) | 2654 | 1,280,740 | 43.4% | 9 | 24,496 | 0.8% |
| any live audit site, unnarrowed (clean column only; pin column repeats the row above) | 2654 | 1,280,740 | 43.4% | 1647 | 892,864 | 30.2% |
| noreturn tail-call spelling (scaffolding, docs/FIDELITY.md) | 668 | 489,140 | 16.6% | 0 | 0 | 0.0% |
| maspsx marker pins (scaffolding) | 394 | 347,664 | 11.8% | 0 | 0 | 0.0% |
| do{}while(0) scheduling barrier (scaffolding, pure C) | 227 | 156,008 | 5.3% | 14 | 20,140 | 0.7% |
| fake dependency x=(e)+a;x-=a / arg+v-v (scaffolding, pure C) | 1 | 408 | 0.0% | 1 | 408 | 0.0% |
| local address-named struct | 633 | 346,824 | 11.7% | 2616 | 1,307,120 | 44.3% |
| clean shape (none of boiler/M2C_FIELD/pins/goto/m2c names) | 631 | 154,308 | 5.2% | 7739 | 2,601,496 | 88.1% |

Pin sites now: 0 in 0 rows; .  At the pin: 25,918; REG 12,816, KEEP 6,936, KEEP_NV 2,505, SCHED_BARRIER 1,355, TAILSLOT_PIN 506, USE 294, USE_NV 260, KEEP_DEP_NV 190.

Tracked, not pins (owner 2026-10-06): oddities 0 (ledger/oddities.jsonl - zero-byte fences retail needs, curiosities, not removal targets: -); one-trip barrier rows 2 (ledger/onetrip_barrier_rows.jsonl); load-bearing one-trip rows 85 (ledger/onetrip_loadbearing.jsonl, statement-macro bodies, not counted in the do{}while(0) row above).
Carve debt - composite rows (r95 decisions item 8 kept the spelling for bytes; r99: it is an artifact of one-row-per-function carving, owned by module placement): the `asm("func_X")` data prefix (another function's jump table / overlay data that retail places before this row's code) and its `.globl/.type/.size func_X` stamp (`pin_census.composite_asm_spans`), 2 statements in 1 rows - counted here, not in the inline-asm row above; still L5 `inline_asm` residue in levels.py until the module TU owns the data.
Hidden scaffolding, not in the pin count (`pin_census.hidden_asm`): raw asm statements 0, calls of local asm wrappers 0, hand-written asm in function bodies 0 (C that is missing); symbol aliases 7 (a second typed name for one symbol: a missing type); file-scope asm directives 4; file-scope global register variables 0 (`register T g asm("$R")`).

Per-row optimization flags (weak evidence about the real build; each switch is undone from the `t30_cellpins` journal's `cell_from`): 89 rows carry one flag, 0 carry two or more.


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

Unconfirmed compiler attributions (still listed above; ledger/recipe_evidence.jsonl `to_confirm` names the measurement): main/func_80019E34 2.7.2-G0, main/func_8001C7F4 2.7.2, main/func_800207D4 2.7.2-G0, main/func_80020F68 2.7.2, slus/code 2.7.2-cdk, town/func_80878110 2.6.3-G0.

Sony SDK library objects (ledger/sdk_objects.jsonl, whole-object byte match; not listed above): main/func_800219C4.
Site-for-pin trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"site_for_pin","id":row,"site":"LABEL_AS_CALL|ITC|PASSTHRU","pin":macro,"residue_without_pin":str,"at":iso,"note":str}` -- one pin, or two when one is not enough (owner ruling 2026-09-22 afternoon, "accept 2 pins") -- charter rule 3, "a pin moved elsewhere is not a removal"; the trade is tracked, and L4 is where pins stop counting toward removal regardless): 27.

Dead-initializer trades (`ledger/recipe_trades.jsonl` records shaped `{"kind":"dead_init","id":row,"site":pins,"init":decl,"lane":lane,"at":iso,"note":str}` -- a never-read `= 0` at a declaration makes the variable multi-set; ordinary C by the owner ruling 2026-09-23, tracked as a spelling trade, informational, the pin count is unchanged; appended by tools/apply_candidates.py at landing): 24.

Union trades (`ledger/union_trades.jsonl`, owner 2026-10-13: kept as nicer-than-a-pin but TRACKED - their plausibility as original 1997 code is unproven; census work/native_lane/_r118/union_census): zero-init one-member idiom (accepted trade): 30 sites in 6 rows (6 rows still carry a union; most: func_8180B064 16, func_80098378 9, func_808119EC 2, func_809A38E4 1); host-merge levers (int/pointer share one union variable; owner ruling pending): 11 sites in 10 rows (9 rows still carry a union; most: func_81983138 2, func_800C7F80 1, func_80EF3FB0 1, func_80EF9FB0 1). Resolved by re-spells (original-C shapes, byte-exact): 11 of 52 recorded sites. Refused union levers (float launders, dead-value keepers) are recorded in the hard basket.

Dead-branch trades (decision 45, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_branch - a one-arm `if (value) { local = 0; }` over a retail-evidenced value whose arm sets a never-read local, reconstructing a set-but-unused leftover that jump2 deletes while delete_computation keeps the load): 4 rows (func_800A3D40, func_80B467DC, func_8105A724, func_81339F68).

Dead-arm trades (decision 46, owner 2026-10-13; `ledger/recipe_trades.jsonl` kind dead_arm - a never-taken arm over a never-reassigned local that combine folds after flow counted it, so sched/global/reload still see it and jump2 deletes it; the arm body is a RECONSTRUCTION, only its shape is byte-evidenced): 1 rows (func_80DE48EC).

Void callees (`config/void_callees.txt`, tiers read from its section-header comments -- no per-line marker exists): tier A 30, tier B 1 symbols (matches `census.declared_void_callees()`). Rows whose PASSTHRU_NO_ARGS exemption rests on a tier-B symbol alone (blocked again if tier B were dropped, tier-A/in-tree exemptions do not cover them): 11 rows, 11,864 B.

## Cleanliness levels (bytes at or above each level)

| level | bytes | % |
|---|---:|---:|
| L0 | 2,953,636 | 100.0% |
| L1 | 2,953,636 | 100.0% |
| L2 | 2,953,636 | 100.0% |
| L3 | 2,924,700 | 99.0% |
| L4 | 713,500 | 24.2% |
| L5 | 688,532 | 23.3% |

On shared record headers (T7, `include/records/`): 1839 rows, 949,472 bytes (32.1%); records used: 98.

L4 residue (rows below L4, by blocker; a row can carry more than one; parked containers excluded): pins 0 rows (0 B), tail_jump 0 rows (0 B), not_in_module 6,561 rows (2,239,960 B).

## Naming and module evidence carried per row (docs/EVIDENCE.md, ledger/evidence/rows.jsonl)

| container | assert file:line / expression | developer identifiers | randomizer map (code) | randomizer map (data tables) | resident pointer tables | script function names | prior notes | applied names | any (rows / bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| slus | 0 | 0 | 1 | 0 | 72 | 7 | 408 | 14 | 479 / 328,024 |
| main | 18 | 5 | 1 | 0 | 0 | 0 | 0 | 0 | 19 / 6,420 |
| town | 26 | 8 | 1 | 1 | 0 | 114 | 0 | 0 | 142 / 19,536 |
| dungeon | 0 | 0 | 24 | 21 | 0 | 0 | 0 | 0 | 44 / 35,592 |

Every lane prompt (tools/agent_task.py) carries the row's block; L4 module placement must agree with the assertion source map.
