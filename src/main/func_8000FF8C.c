#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Dispatches request 14 with parameter 2 for the parent and its status pointer. */
void card_boot_show_loading_progress(M2C_UNK parent, M2C_UNK status) {
    card_boot_create_or_reset_message_dialog(parent, 0xe, 2, status);
}
