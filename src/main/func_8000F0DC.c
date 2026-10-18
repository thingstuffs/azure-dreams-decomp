#include "modules/main_server_ship.h"
#include "common.h"







/* Store a value and its converted result in the selected state slot. */
void card_boot_refresh_directory_summary(void) {
    s32 state_index;
    s32 source_value;

    state_index = (*(s32 *)(&D_800287CC)) != 0;
    source_value = count_entries_matching_search_path();
    D_80084128[state_index] = source_value;
    D_80084120[state_index] = card_boot_calc_remaining_8k_blocks(source_value);
}
