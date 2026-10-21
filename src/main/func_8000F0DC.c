#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"







/* Store a value and its converted result in the selected state slot. */
void card_boot_refresh_directory_summary(void) {
    s32 state_index;
    s32 source_value;

    state_index = (*(s32 *)(&card_selected_channel_alias)) != 0;
    source_value = count_entries_matching_search_path();
    card_directory_counts[state_index] = source_value;
    card_remaining_block_counts[state_index] = card_boot_calc_remaining_8k_blocks(source_value);
}
