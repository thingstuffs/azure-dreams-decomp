#include "common.h"

typedef struct {
    u16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[2];
    u8 count;
    u8 pad3[9];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern s16 D_8001F6F8[];
extern DungeonGroup D_80073414[];

/* Build cumulative weights for eligible items in each item category. */
void func_8001E994(void)
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
        for (item_index = 1; item_index < D_80073414[category_index].count; item_index++) {
            item_flags = D_80073414[category_index].entries[item_index].flags;
            if (item_flags & 0x10) {
                continue;
            }
            if ((item_flags & 0x40) && *(s32 *)0x80012090 != 2) {
                continue;
            }
            weight_bits = ((DungeonGroup *)((u8 *)D_80073414 + (((category_index << 3) + (category_index << 1)) << 1)))->entries[item_index].flags & 0x3000;
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
