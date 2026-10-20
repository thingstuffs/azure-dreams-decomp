#include "common.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Initialize operation 0x12 for the owner with the supplied data. */
void card_boot_show_delete_confirmation(s32 owner, s32 data) {
    card_boot_create_or_reset_message_dialog(owner, 0x12, 1, data);
}
