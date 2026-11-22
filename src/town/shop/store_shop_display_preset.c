#include "common.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "town/shop.h"
#include "town/data.h"

/* Store the table index and its two byte values in the object. */
void store_shop_display_preset(ItemMenuInputObject *object, s32 index) {
    u8 *table;
    u8 *entry;

    table = shop_display_presets;
    object->preset = index;
    entry = table + index * 2;
    object->source_index = entry[0];
    object->destination_index = entry[1];
}
