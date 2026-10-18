#include "common.h"
extern u8 D_8006E240[];

extern s32 lookup_item_category_mapped_value(s32, s32);

/* Resolve the item's description: kind 0x12 uses the fixed table, everything else is looked up. */
s32 get_item_category_value(u8 *item)
{
    s32 result;

    if (item[1] == 0x12) {

        result = D_8006E240;
    } else {
        result = lookup_item_category_mapped_value(item[1], item[0]);
    }
    return result;
}
