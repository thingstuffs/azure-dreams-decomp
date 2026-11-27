/* Paged selection refresh. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B03D0, CL:town/func_800B085C. */
#include "town/shop/paged_selection_refresh_g00598.h"
#include "town/shop.h"

/* Counts four-byte entries until an entry's second byte is zero. */
s32 count_leading_typed_records(DungeonItemEntry *entries) {
    s32 count;
    DungeonItemEntry *entry;

    entry = entries;
    count = 0;
    if (entry->kind != 0) {
        do {
            entry++;
            count += 1;
        } while (entry->kind != 0);
    }
    return count;
}

/* Refresh the entry count, clamp the selection, and update five-entry page indices. */
void refresh_paged_selection_state(GridMenuObject *record) {
    if (record != 0) {
        if ((record->entry_count = count_leading_typed_records(record->entry_base)) != 0) {
            record->last_page = (record->entry_count - 1) / 5;
            if (record->selected_index >= record->entry_count) {
                record->selected_index = record->entry_count - 1;
            }
        } else {
            record->selected_index = 0;
            record->last_page = 0;
        }
        record->selected_row = record->selected_index / 5;
    }
}
