#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Passes the value and fixed arguments (7, 0, 0) to card_boot_create_or_reset_message_dialog. */
void card_boot_show_no_saved_game_notice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 7, zero, zero);
}
