#include "modules/main_server_ship.h"
#include "common.h"




/* Returns the first or second word according to (*(s32 *)(&D_800287CC)). */
s32 card_boot_get_remaining_block_summary(void) {
    s32 *selected_word;

    selected_word = &(*(u8 *)(&D_80084120));
    if ((*(s32 *)(&D_800287CC)) != 0) {
        selected_word = &(*(u8 *)(&D_80084120)) + 4;
    }
    return *selected_word;
}
