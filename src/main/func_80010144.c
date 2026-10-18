#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Initialize operation 0x12 for the owner with the supplied data. */
void card_boot_show_delete_confirmation(M2C_UNK owner, M2C_UNK data) {
    card_boot_create_or_reset_message_dialog(owner, 0x12, 1, data);
}
