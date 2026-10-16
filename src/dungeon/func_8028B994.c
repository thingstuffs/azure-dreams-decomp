#include "modules/dungeon_floor_spawns.h"

void buildCumulativeItemWeights(void)
{
    s32 total_weight;
    s32 category_index;
    s32 item_index;
    s32 item_flags;
    s32 item_weight;
    s32 weight_bits;
    s32 weight_kind;

    total_weight = 0;
    for (category_index = 1; category_index < 0x13; category_index++) {
        for (item_index = 1; item_index < ((floor_spawns_isolated_8028B994_DungeonGroup *)D_80073414)[category_index].count; item_index++) {
            item_flags = ((floor_spawns_isolated_8028B994_DungeonGroup *)D_80073414)[category_index].entries[item_index].flags;
            if (item_flags & 0x10) {
                continue;
            }
            if ((item_flags & 0x40) && *(s32 *)0x80012090 != 2) {
                continue;
            }
            weight_bits = ((floor_spawns_isolated_8028B994_DungeonGroup *)((u8 *)((floor_spawns_isolated_8028B994_DungeonGroup *)D_80073414) + (((category_index << 3) + (category_index << 1)) << 1)))->entries[item_index].flags & 0x3000;
            weight_kind = (weight_bits / 0x1000) & 3;
            item_weight = 0x80;
            if (weight_kind != 0) {
                item_weight = 0x55;
                if (weight_kind != 1) {
                    item_weight = 1;
                    if (weight_kind == 2) {
                        item_weight = 0x20;
                    }
                }
            }
            total_weight += item_weight;
        }
        D_8001F6F8[category_index] = total_weight;
    }
    D_8001F6F8[category_index] = total_weight;
}
