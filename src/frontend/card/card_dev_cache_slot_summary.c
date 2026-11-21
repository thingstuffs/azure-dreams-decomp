#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/service.h"
#include "main/data.h"

/* Store the entry ID and its associated value in the selected slot. */
void card_dev_cache_slot_summary(void) {
    s32 slot_index;
    s32 entry_id;

    slot_index = card_selected_channel != 0;
    entry_id = count_dev_card_entries_matching_search_path();
    dev_card_directory_counts[slot_index] = entry_id;
    dev_card_remaining_8k_blocks[slot_index] = card_dev_calc_remaining_8k_blocks(entry_id);
}
