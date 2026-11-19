#include "common.h"
#include "engine/menu.h"
#include "town/shop.h"

/* Fills ten output slots from the current page of records, zeroing unused slots. */
void fill_ten_paged_output_slots(void *part_table, StoragePage *page_info, DungeonItemEntry **record_table) {
    s32 slot;
    s32 page;
    s32 record_index;
    ItemMenuPart **output_ptr;
    ItemMenuPart **outputs;
    DungeonItemEntry *record;

    slot = 0;
    page = page_info->current;
    output_ptr = part_table;
    record_index = page * 10;

    for (; slot < 10 && record_index < page_info->count; record_index++) {
        slot++;
        record = record_table[record_index];
        (*output_ptr)->handler = (void *)(long)lookup_item_category_mapped_value(record->kind, record->unk_00);
        output_ptr++;
    }
    outputs = part_table;
    for (; slot < 10; slot++) {
        outputs[slot]->handler = 0;
    }
}
