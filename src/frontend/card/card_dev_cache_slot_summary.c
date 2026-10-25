#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

s32 count_entries_for_selected_card_path(void);                                /* extern */
s32 func_80401A50(s32 entry_count);                             /* extern */

extern s32 card_selected_channel[];

/* Store the entry ID and its associated value in the selected slot. */
void card_dev_cache_slot_summary(void) {
    s32 slot_index;
    s32 entry_id;

    slot_index = card_selected_channel[0] != 0;
    entry_id = count_entries_for_selected_card_path();
    dev_card_directory_counts[slot_index] = entry_id;
    D_8009EB58[slot_index] = func_80401A50(entry_id);
}
