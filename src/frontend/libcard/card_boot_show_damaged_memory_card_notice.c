#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Forwards the value to card_boot_create_or_reset_message_dialog with mode 3 and zeroed trailing arguments. */
void card_boot_show_damaged_memory_card_notice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 3, zero, zero);
}
