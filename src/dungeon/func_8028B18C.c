#include "dungeon/level/spawn.h"

void populate_floor_item_records(void)
{
    u8 tile_x;
    u8 tile_y;
    u8 item_category;
    u8 item_subtype;
    s32 count;
    s32 found_status;
    s32 crystal_pending;
    s16 category18_pending;
    s32 slot_limit;
    s32 spawn_index;
    s32 special_flag;
    s32 spawn_check;
    floor_spawns_isolated_8028B18C_DungeonGroup *item_category_table;
    floor_spawns_isolated_8028B18C_DungeonRecord *item_record;
    DungeonItemEntry *item_state;
    floor_spawns_isolated_8028B18C_DungeonRecord *saved_record;
    floor_spawns_isolated_8028B18C_DungeonRecord *spawn_records;
    u8 *setup_globals;
    if (D_800E3D6C[0] & 2) {
        count = 0;
        saved_record = (floor_spawns_isolated_8028B18C_DungeonRecord *)((u8 *)D_800E36C8);
        item_state = (DungeonItemEntry *)((u8 *)D_800E3548);
        do {
            if (item_state->unk_00 != 0) {
                cycle_map_cell_flags(saved_record->x, saved_record->y, 0x800);
            }
            saved_record++;
            count++;
            item_state++;
        } while (count < 0x40);
        return;
    }

    setup_globals = (u8 *)0x80010000;
    *(u16 *)(setup_globals + 0x3626) = *(u16 *)(setup_globals + 0x3624);
    *(u16 *)(setup_globals + 0x209E) = *(u16 *)(setup_globals + 0x209C);
    ((s8 *)D_8001F6F0)[0] = 0;
    *(u16 *)(setup_globals + 0x3626) += (generate_random_value() & 3) + 0x33;
    *(u16 *)(setup_globals + 0x209E) += (generate_random_value() & 3) + 0x33;

    if (D_80081468[3] == 1) {
        s32 limit_roll;

        crystal_pending = 0;
        limit_roll = generate_random_value() & 7;
        slot_limit = limit_roll + 8;
    } else {
        s32 limit_roll;
        s32 base_limit;

        crystal_pending = 0;
        limit_roll = generate_random_value() & 3;
        base_limit = (s16)D_80081468[3] / 2;
        slot_limit = base_limit + limit_roll;
    }

    if ((generate_random_value() & 3) == 0) {
        crystal_pending = *(s16 *)0x8001209E >= 0x101;
    }
    category18_pending = 0;
    if ((generate_random_value() & 3) == 0) {
        category18_pending = *(s16 *)0x80013626 >= 0x101;
    }

    if (*(s32 *)0x80012090 == 0) {
        spawn_check = count_matching_packed_entity_keys(6, 3);
        if ((s16)spawn_check < 2) {
            if ((generate_random_value() & 3) == 0) {
                spawn_index = (s16)find_first_empty_floor_item_slot();
                if (spawn_index >= 0) {
                    do {
                        do {
                        } while ((s16)select_dungeon_spawn_tile(&tile_x, &tile_y) < 0);
                    } while (is_floor_item_tile_occupied(spawn_index, tile_x, tile_y) != 0);

                    {
                        s32 *spawn_table = (s32 *)((u8 *)D_800E3548);
                        spawn_table[spawn_index] = 0x603;
                    }
                    spawn_records = (floor_spawns_isolated_8028B18C_DungeonRecord *)((u8 *)D_800E36C8);
                    spawn_records[spawn_index].x = tile_x;
                    spawn_records[spawn_index].y = tile_y;
                    cycle_map_cell_flags(spawn_records[spawn_index].x,
                                  spawn_records[spawn_index].y, 0x800);
                }
            }
        }
    }

    count = 0;
    spawn_check = (s32)((u8 *)0x80010000);
    item_category_table = ((floor_spawns_isolated_8028B18C_DungeonGroup *)D_80073414);
    item_state = (DungeonItemEntry *)((u8 *)D_800E3548);
    item_record = (floor_spawns_isolated_8028B18C_DungeonRecord *)((u8 *)D_800E36C8);
main_loop:
    if (item_state->kind == 0) {
        if (count >= slot_limit) {
            goto cleanup;
        }

        found_status = (s16)select_floor_item_with_special_overrides(&item_category, &item_subtype, 0, 0);
        if (found_status != 0 || item_category != 0) {
            if (found_status == 0) {
                special_flag = crystal_pending;
                if (special_flag != 0) {
                    s32 page_value;

                    page_value = ((generate_random_value() & 0xF) == 0) ? 2 : 1;
                    item_subtype = page_value;
                    crystal_pending = 0;
                    page_value = *(u16 *)(((u8 *)spawn_check) + 0x209E);
                    item_category = 2;
                    page_value &= 0xF;
                    *(u16 *)(((u8 *)spawn_check) + 0x209E) = page_value;
                } else {
                    special_flag = category18_pending;
                    if (special_flag != 0) {
                        u32 item_flags;

                        item_category = 0x12;
                        item_subtype = D_800DDC9C[generate_random_value() & 0x1F];
                        item_flags = item_category_table[18].entries[item_subtype].flags;
                        if ((item_flags & 0x10) != 0 &&
                            (item_category_table[19].entries[item_subtype].flags & 0x80) != 0 &&
                            item_subtype >= 2) {
                            item_subtype++;
                        }
                        category18_pending = 0;
                        *(u16 *)(((u8 *)spawn_check) + 0x3626) &= 0x3F;
                    }
                }
            }

            item_state->kind = item_category;
            item_state->unk_00 = item_subtype;
            init_random_floor_item_parameters(item_state);

            do {
            } while ((s16)select_dungeon_spawn_tile(&tile_x, &tile_y) < 0);

            if (is_floor_item_tile_occupied(count, tile_x, tile_y) != 0) {
                item_state->kind = 0;
            } else {
                item_record->x = tile_x;
                item_record->y = tile_y;
                item_record->field4 = get_surface_height_at_coordinates((tile_x << 6) | 0x20,
                                                    (tile_y << 6) | 0x20);
                item_record->field7 = 0;
                cycle_map_cell_flags(tile_x, tile_y, 0x800);
                item_record->field8 = get_item_category_value(item_state);
            }
        }
    } else {
        tile_x = item_record->x;
        tile_y = item_record->y;
        init_random_floor_item_parameters(item_state);
        item_record->field4 = get_surface_height_at_coordinates((tile_x << 6) | 0x20,
                                            (tile_y << 6) | 0x20);
        item_record->field7 = 0;
        cycle_map_cell_flags(tile_x, tile_y, 0x800);
        item_record->field8 = get_item_category_value(item_state);
    }

    item_state++;
    count++;
    item_record++;
    if (count < 0x40) {
        goto main_loop;
    }

cleanup:
    if (count < 0x40) {
        DungeonItemEntry *cleanup_base;
        DungeonItemEntry *cleanup_state;

        cleanup_base = (DungeonItemEntry *)((u8 *)D_800E3548);
        cleanup_state = cleanup_base + count;
cleanup_loop:
            cleanup_state->kind = 0;
            (cleanup_state++)->unk_00 = 0;
            count++;
        if (count < 0x40) {
            goto cleanup_loop;
        }
    }
    generate_random_dungeon_item_drops();

    return;
}
