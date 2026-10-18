#include "modules/dungeon_floor_generate.h"

s32 setup_dungeon_floor_encounters(void)
{
    s32 floor_event;
    s32 skip_floor_setup;
    s32 state;
    s32 floor_group;
    s32 encounter_status;
    s16 *floor_data;
    s32 final_floor;
    s32 monster_id;
    s32 level;
    u8 *base;

    floor_event = 0;
    skip_floor_setup = 0;
    state = floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_022c;
    if (state == 1) {
        if (((s16 *)D_8008146C)[0] < 2) {
            floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090 = state;
            convert_valid_entry_code_2_to_39();
        } else if (floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090 == state) {
            floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090 = 0;
        }
    }

    state = D_80082E6B[0];
    if (state < 0x16) {
        if (state >= 0x12) {
            floor_event = 0;
            goto final;
        }
    }

    state = floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090;
    if (state == 0) {
        floor_group = (s16)(((s16 *)D_8008146C)[0] / 5);
        if (((s16 *)D_8008146C)[0] >= 0x28) {
            skip_floor_setup = 1;
            D_800E296C |= 0x10000000;
        }

        if (((s16 *)D_8008146C)[0] == 0x28) {
            floor_event = 1;
            if (func_80033BC0(0xA2) != 0) {
                floor_group = 7;
            } else {
                floor_group = -1;
                set_first_table_entry_active();
            }
            skip_floor_setup = 1;
        } else if (((s16 *)D_8008146C)[0] < 2) {
            floor_event = (generate_random_value() & 3) + 3;
        } else if (((s16 *)D_8008146C)[0] == 2 && floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_022c != 1) {
            floor_event = 2;
            D_800E296C |= 0x10000000;
        } else if (((s16 *)D_8008146C)[0] == 0x1F && func_80033BC0(0x1389) == 0) {
            D_800E39C8[6] = 1;
            D_800E39C8[7] = 1;
            ((u8 *)D_800E3648)[0] = 0x37;
            ((u8 *)D_800E3648)[1] = 0x13;
            ((u8 *)D_800E3648)[3] = 0;
            ((u8 *)D_800E3648)[2] = 0x63;
            D_800E296C |= 0x10000000;
        }

        if (floor_group >= 0) {
            encounter_status = load_object_into_alternate_buffer((s16)(floor_group + 1), 1, 1);
            if (encounter_status == 0) {
                D_80080A88[0] = 0;
            }
            if (D_80080A88[0] == 0) {
                func_80044698();
                D_80080A88[0] = 1;
                SD_Call(0x200);
                func_800542BC();
            }
            if (encounter_status == 0) {
                load_object_into_alternate_buffer(0, 1, 0);
            }
        } else {
            load_object_into_alternate_buffer(0, 1, 0);
            load_object_into_alternate_buffer(0x29, 1, 1);
            SD_Call(0x200);
            func_800542BC();
            load_and_upload_sprite_resource(0x38);
        }

        if (skip_floor_setup == 0) {
            load_floor_spawn_tables(((s16 *)D_8008146C)[0]);
        }
    } else {
        skip_floor_setup = 1;
        if (state == 1) {
            floor_event = 9;
            D_800E296C |= 0x10000000;
            load_object_into_alternate_buffer(1, 1, 1);
            SD_Call(0x200);
            func_800542BC();
            load_object_into_alternate_buffer(0, 1, 0);
        } else if (state == 2) {
            s32 i_m;
            floor_group = generate_random_value() & 7;
            encounter_status = load_object_into_alternate_buffer(floor_group + 1, 1, 1);
            if (encounter_status == 0) {
                func_80044698();
                SD_Call(0x200);
                func_800542BC();
                load_object_into_alternate_buffer(0, 1, 0);
            }

            floor_data = (s16 *)((u8 *)D_80081468);
            if (floor_data[2] == 1) {
                s32 i;
                {

                    u8 *even_ids;
                    u8 *odd_ids;
                    floor_generate_isolated_80285E80_DungeonState80285E80 *ds;

                    monster_id = random_dungeon_range_16(3, 0x2D) & 0xFFFF;
                    level = floor_data[2] + (generate_random_value() & 1);
                    if (level >= 100) {
                        level = 99;
                    }
                    i = 0;
                    ds = ((floor_generate_isolated_80285E80_DungeonState80285E80 *)&g_dungeon_status);
                    base = ((u8 (*)[8])D_800DDC9C)[0];
                    even_ids = base;
                    odd_ids = even_ids + 1;
                    do {
                        ds->records[i].value = monster_id;
                        ds->records[i].level = level;
                        i++;
                        *odd_ids = monster_id;
                        *even_ids = monster_id;
                        even_ids += 2;
                        odd_ids += 2;
                    } while (i < 4);
                }

                {

                    u8 *even_ids;
                    u8 *odd_ids;
                    floor_generate_isolated_80285E80_DungeonState80285E80 *ds;

                    monster_id = random_dungeon_range_16(3, 0x2D) & 0xFFFF;
                    level = ((s16 *)D_8008146C)[0] + (generate_random_value() & 1);
                    if (level >= 100) {
                        level = 99;
                    }
                    i = 0;
                    ds = ((floor_generate_isolated_80285E80_DungeonState80285E80 *)&g_dungeon_status);
                    base = ((u8 (*)[8])D_800DDC9C)[1];
                    even_ids = base;
                    odd_ids = even_ids + 1;
                    do {
                        ds->records[i + 4].value = monster_id;
                        ds->records[i + 4].level = level;
                        i++;
                        *odd_ids = monster_id;
                        *even_ids = monster_id;
                        even_ids += 2;
                        odd_ids += 2;
                    } while (i < 4);
                }
            } else {
                *(floor_generate_isolated_80285E80_Packed16_80285E80 *)g_dungeon_status.unk_18 =
                    *(floor_generate_isolated_80285E80_Packed16_80285E80 *)(g_dungeon_status.unk_18 + 0x10);
                *(floor_generate_isolated_80285E80_Packed16_80285E80 *)((u8 (*)[8])D_800DDC9C)[0] =
                    *(floor_generate_isolated_80285E80_Packed16_80285E80 *)((u8 (*)[8])D_800DDC9C)[2];
            }

            {

                s32 level_bonus;
                u8 *even_ids;
                u8 *odd_ids;
                floor_generate_isolated_80285E80_DungeonState80285E80 *ds;

                monster_id = random_dungeon_range_16(3, 0x2D) & 0xFFFF;
                level_bonus = generate_random_value() & 1;
                i_m = 0;
                base = ((floor_generate_isolated_80285E80_DungeonState80285E80 *)&g_dungeon_status);
                ds = base;
                final_floor = (s32)((u8 (*)[8])D_800DDC9C)[2];
                even_ids = (u8 *)final_floor;
                odd_ids = even_ids + 1;
                final_floor = ((s16 *)D_8008146C)[0];
                level = final_floor + level_bonus;
                do {
                    ds->records[i_m + 8].value = monster_id;
                    ds->records[i_m + 8].level = level;
                    i_m++;
                    *odd_ids = monster_id;
                    *even_ids = monster_id;
                    even_ids += 2;
                    odd_ids += 2;
                } while (i_m < 4);
            }

            {

                s32 level_bonus;
                u8 *even_ids;
                u8 *odd_ids;
                floor_generate_isolated_80285E80_DungeonState80285E80 *ds;

                monster_id = random_dungeon_range_16(3, 0x2D) & 0xFFFF;
                level_bonus = generate_random_value() & 1;
                i_m = 0;
                ds = ((floor_generate_isolated_80285E80_DungeonState80285E80 *)&g_dungeon_status);
                final_floor = (s32)((u8 (*)[8])D_800DDC9C)[3];
                even_ids = (u8 *)final_floor;
                odd_ids = even_ids + 1;
                final_floor = ((s16 *)D_8008146C)[0];
                level = final_floor + level_bonus;
                do {
                    ds->records[i_m + 12].value = monster_id;
                    ds->records[i_m + 12].level = level;
                    i_m++;
                    *odd_ids = monster_id;
                    *even_ids = monster_id;
                    even_ids += 2;
                    odd_ids += 2;
                } while (i_m < 4);
            }
        }
    }

final:
    final_floor = ((s16 *)D_8008146C)[0];
    floor_generate_isolated_80285E80_DUNGEON_GLOBALS->floor_0234 = final_floor;
    return floor_event;
}
