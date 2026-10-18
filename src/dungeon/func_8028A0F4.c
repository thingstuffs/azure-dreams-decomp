#include "modules/dungeon_floor_generate.h"

void place_room_trap_records(floor_generate_isolated_8028A0F4_DungeonRect *rect, s32 update_id)
{
    u16 tile_flags;
    s32 slot_limit_calc;
    s16 slot_limit;
    s32 item_kind;
    s16 stored_kind;
    s32 special_roll;
    s32 slot_index;
    u32 kind_roll;
    u16 item_flags;
    floor_generate_isolated_8028A0F4_DungeonGroup *item_category_table;
    u32 x_offset;
    u32 y_offset;

    special_roll = generate_random_value() & 0xFF;
    slot_limit_calc = ((rect->height * rect->width) >> 3) +
                 (generate_random_value() & 7);
    slot_limit = slot_limit_calc;
    if ((s16)slot_limit_calc >= 29) {
        slot_limit = 28;
    }
    slot_index = (s16)slot_limit;

    if (slot_index >= 0) {
        item_category_table = D_80073414;


        for (; slot_index >= 0; slot_index--) {
            x_offset = random_dungeon_range_16(0, (rect->width - 1) & 0xFFFF) & 0xFFFF;
            y_offset = random_dungeon_range_16(0, (rect->height - 1) & 0xFFFF) & 0xFFFF;
            get_offset_map_cell_value_and_flags((s16)(rect->x + x_offset - 1),
                          (s16)(rect->y + y_offset), 0, &tile_flags);
            if (!(tile_flags & 0x8820)) {
                ((floor_generate_isolated_8028A0F4_DungeonSpot *)D_800E39C8)[slot_index].px = (u8)rect->x + x_offset;
                ((floor_generate_isolated_8028A0F4_DungeonSpot *)D_800E39C8)[slot_index].py = (u8)rect->y + y_offset;
                if (special_roll == 0) {
                    ((floor_generate_isolated_8028A0F4_DungeonSlot *)D_800E3648)[slot_index].kind = 7;
                } else {
                    kind_roll = generate_random_value() & 0xFFFF;
                    item_kind = (kind_roll % 19) + 1;
                    item_flags = *(u16 *)(item_category_table[21].entries +
                                          ((s16)item_kind * 12));
                    stored_kind = item_kind;
                    if ((item_flags & 0x3000) == 0x3000) {
                        continue;
                    }
                    ((floor_generate_isolated_8028A0F4_DungeonSlot *)D_800E3648)[slot_index].kind = stored_kind;
                }
                ((floor_generate_isolated_8028A0F4_DungeonSlot *)D_800E3648)[slot_index].f1 = 0x15;
                ((floor_generate_isolated_8028A0F4_DungeonSlot *)D_800E3648)[slot_index].f3 = 0x80;
                ((floor_generate_isolated_8028A0F4_DungeonSlot *)D_800E3648)[slot_index].f2 = 0;
                cycle_map_cell_flags(((floor_generate_isolated_8028A0F4_DungeonSpot *)D_800E39C8)[slot_index].px, ((floor_generate_isolated_8028A0F4_DungeonSpot *)D_800E39C8)[slot_index].py, 0x20);
            }
        }
    }
}
