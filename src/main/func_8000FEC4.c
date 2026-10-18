#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Forwards the input and value with both middle arguments set to 2. */
void card_boot_show_please_wait_notice(M2C_UNK input, M2C_UNK value) {
    card_boot_create_or_reset_message_dialog(input, 2, 2, value);
}
