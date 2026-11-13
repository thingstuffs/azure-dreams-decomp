#include "common.h"
#include "town/shop.h"
#include "town/data.h"

/* Store the table index and its two byte values in the object. */
void store_shop_display_preset(void *object, s32 index) {
    u8 *table;
    u8 *entry;

    table = shop_display_presets;
    *(s32 *)((s8 *) object + 0xC) = index;
    entry = table + index * 2;
    *(s32 *)((s8 *) object + 0x14) = entry[0];
    *(s32 *)((s8 *) object + 0x18) = entry[1];
}
