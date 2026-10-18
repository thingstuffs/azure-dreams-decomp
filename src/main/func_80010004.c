#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Passes value, 11, and two zero arguments to card_boot_create_or_reset_message_dialog. */
void card_boot_show_load_failure_notice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 0xb, zero, zero);
}
