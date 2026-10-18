#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Forwards the value to card_boot_create_or_reset_message_dialog with code 12 and two zero arguments. */
void card_boot_show_format_failure_notice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 0xc, zero, zero);
}
