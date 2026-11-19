#include "common.h"
#include "m2c_compat.h"
#include "engine/item.h"
#include "town/shop.h"


/* Convert up to ten entries from the selected page into the output slots. */
void fill_ten_paged_entry_slots(ItemMenuPart **outputs, StoragePage *page_info, DungeonItemEntry **entries_base) {
    ItemMenuPart **output_slot;
    DungeonItemEntry *entry;
    s32 page;
    s32 entry_index;
    s32 count;

    count = 0;
    page = page_info->current;
    output_slot = outputs;
    entry_index = page * 0xA;
    for (;;) {
        count += 1;
        if (entry_index < page_info->count) {
            entry = entries_base[entry_index];
            entry_index += 1;
            (*output_slot)->handler = create_item_label(entry);
            output_slot += 1;
            if (count < 0xA) {
                continue;
            }
        }
        break;
    }
}
