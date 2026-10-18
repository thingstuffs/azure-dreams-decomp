#include "modules/dungeon_floor_spawns.h"

void generate_random_dungeon_item_drops(void)
{
    u8 x;
    u8 y;
    register s32 budget;
    s32 index;
    s32 decrement;
    s32 amount;
    s32 flag;
    s32 type;
    s32 cell_index;
    s32 scan_x;
    s32 scan_y;
    s32 scaled;
    u8 *mode_page;
    s32 entry_state;
    DungeonItemEntry *entry;
    floor_spawns_isolated_8028BC54_DungeonCell *cell;
    DungeonItemEntry *entry_scan;
    floor_spawns_isolated_8028BC54_DungeonCell *cell_scan;
    DungeonItemEntry *entry_base;
    u8 *cell_page;
    floor_spawns_isolated_8028BC54_DungeonCell *cell_base = 0;

    mode_page = D_80010000;
    if (*(s32 *)(mode_page + 0x2090) == 2) {
        mode_page = (u8 *)(*(s16 *)D_8008146C);
        scaled = ((s32)mode_page) * 25;
        budget = scaled << 3;
    } else {
        budget = 75;
        if ((*(s16 *)D_8008146C) >= 12) {
            budget = 700;
            if ((*(s16 *)D_8008146C) < 22) {
                budget = 200;
            }
        }
    }

    if (generate_random_value() & 1) {
        budget += (u16)random_dungeon_range_16(0, (budget / 2) & 0xFFFF);
    } else {
        budget -= (u16)random_dungeon_range_16(0, (budget / 2) & 0xFFFF);
    }

    if (budget >= 0) {
        entry_base = (DungeonItemEntry *)((u8 *)D_800E3548);
        cell_page = (u8 *)0x800E0000;
        do {
        cell_index = (s16)find_first_empty_floor_item_slot();
        if (cell_index < 0) {
            return;
        }

        if (budget >= 301) {
            decrement = (u16)random_dungeon_range_16(160, 240);
            flag = 1;
            type = 3;
            amount = (decrement / 10 + (decrement >> 31)) & 0x3FFFFFFF;
        } else if (budget >= 151) {
            decrement = (u16)random_dungeon_range_16(80, 120);
            amount = decrement;
            flag = 0;
            type = 2;
        } else {
            decrement = (u16)random_dungeon_range_16(16, 24);
            amount = decrement;
            flag = 0;
            type = 1;
        }

        do {
        } while ((select_dungeon_spawn_tile(&x, &y) << 16) < 0);

        scan_x = x;
        scan_y = y;
        for (index = 0, cell_scan = (floor_spawns_isolated_8028BC54_DungeonCell *)((u8 *)D_800E36C8), entry_scan = entry_base;
             index < 64;
             cell_scan++, index++, entry_scan++) {
            if (!(entry_scan->kind == 0 || cell_scan->x != scan_x || cell_scan->y != scan_y)) {
                break;
            }
        }

        if (index == 64) {
            entry = (DungeonItemEntry *)((cell_index << 2) + (unsigned long)entry_base);
            cell_base = (floor_spawns_isolated_8028BC54_DungeonCell *)(cell_page + 0x36C8);
            entry->unk_00 = type;
            entry->kind = 14;
            entry->unk_03 = flag;
            entry->unk_02 = amount;
            cell = (floor_spawns_isolated_8028BC54_DungeonCell *)((cell_index * 12) +
                                            (unsigned long)cell_base);
            cell->x = x;
            cell->y = y;
            ((floor_spawns_isolated_8028BC54_DungeonCell *)cell)->height = get_surface_height_at_coordinates((x << 6) | 32, (y << 6) | 32);
            cell->flag7 = 0;
            cycle_map_cell_flags(x, y, 0x800);
            cell->object = get_item_category_value((void *)entry);
        }

        budget -= decrement;
        } while (budget >= 0);
    }
    return;
}
