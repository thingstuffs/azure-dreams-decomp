#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Calls card_boot_create_or_reset_message_dialog with selector 9 and two zero arguments. */
void card_boot_show_insufficient_space_overwrite_advice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 9, zero, zero);
}
