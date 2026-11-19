#include "common.h"
#include "m2c_compat.h"
#include "engine/item.h"
#include "engine/util.h"
#include "town.h"

#include "town/shop/storage_menu.h"

/* Populate up to ten page entries and set their type-dependent brightness. */
void populate_paged_entries_with_brightness(ItemMenuPart **entries, StoragePage *page_info, DungeonItemEntry **source_table) {
    s32 lookup_param;
    s32 page_index;
    s32 source_index;
    s32 entry_count;
    s32 normal_shade;
    s32 dim_shade;
    ItemMenuPart **entry;
    DungeonItemEntry **source;

    entry_count = 0;
    dim_shade = 0x40;
    normal_shade = 0x80;
    page_index = page_info->current;
    entry = entries;
    source_index = page_index * 0xA;
    source = (DungeonItemEntry **)((source_index * sizeof(*source_table)) + (unsigned long)source_table);
    while (entry_count < 0xA && source_index < page_info->count) {
        (*entry)->handler = func_8004DC14(select_item_data(*source, &lookup_param), lookup_param);
        if ((*source)->kind == 0x13) {
            (*entry)->position->color.c.r = dim_shade;
            (*entry)->position->color.c.g = dim_shade;
            (*entry)->position->color.c.b = dim_shade;
        } else {
            (*entry)->position->color.c.r = normal_shade;
            (*entry)->position->color.c.g = normal_shade;
            (*entry)->position->color.c.b = normal_shade;
        }
        entry += 1;
        entry_count += 1;
        source += 1;
        source_index += 1;
    }
}
