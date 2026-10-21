#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"




/* Returns the first or second word according to (*(s32 *)(&D_800287CC)). */
s32 card_boot_get_remaining_block_summary(void) {
    s32 *selected_word;

    selected_word = &(*(u8 *)(&card_remaining_block_counts));
    if ((*(s32 *)(&card_selected_channel_alias)) != 0) {
        selected_word = &(*(u8 *)(&card_remaining_block_counts)) + 4;
    }
    return *selected_word;
}
