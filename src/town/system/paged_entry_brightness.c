/* Paged entry brightness and its file-private helper. */
#include "common.h"
#include "m2c_compat.h"
#include "engine/item.h"
#include "engine/util.h"
#include "town/shop/storage_menu.h"

/* Loads up to ten item displays for the current page, dimming entries of type 0x13. */
static void populate_paged_entries_with_brightness(ItemMenuPart **entries, StoragePage *page_info, DungeonItemEntry **source_table) {
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
        (*entry)->handler = create_label_glyph_entries(select_item_data(*source, &lookup_param), lookup_param);
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

extern void func_800B39E4(void *);

/* Refresh the alternate storage menu's ten text parts. */
void populate_record_page_entries(AlternateStorageOwner *record) {
    AlternateStorageSource *source;

    func_800B39E4(record->parts);
    source = record->source;
    populate_paged_entries_with_brightness(&record->parts[16], &source->page, source->entries);
}
