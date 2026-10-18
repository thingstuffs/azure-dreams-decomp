#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Starts mode 8 for the owner with no additional parameters. */
void card_boot_show_overwrite_failure_notice(s32 owner) {
    card_boot_create_or_reset_message_dialog(owner, 8, 0, 0);
}
