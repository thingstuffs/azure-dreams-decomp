#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Start operation 4 in mode 2 with the owner and status flag. */
void card_boot_show_formatting_progress(M2C_UNK owner, M2C_UNK status_flag) {
    card_boot_create_or_reset_message_dialog(owner, 4, 2, status_flag);
}
