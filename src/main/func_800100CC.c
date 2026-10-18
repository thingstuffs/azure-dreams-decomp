#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Initialize the owner's request with type 0xf, mode 2, and its data. */
void card_boot_show_copying_progress(M2C_UNK owner, M2C_UNK data) {
    card_boot_create_or_reset_message_dialog(owner, 0xf, 2, data);
}
