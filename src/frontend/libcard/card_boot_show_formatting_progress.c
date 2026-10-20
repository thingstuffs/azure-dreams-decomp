#include "common.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Start operation 4 in mode 2 with the owner and status flag. */
void card_boot_show_formatting_progress(s32 owner, s32 status_flag) {
    card_boot_create_or_reset_message_dialog(owner, 4, 2, status_flag);
}
