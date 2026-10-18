#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Initializes a request with selector 0 and mode 1. */
void card_boot_show_format_confirmation(M2C_UNK request_id, M2C_UNK request_value) {
    card_boot_create_or_reset_message_dialog(request_id, 0, 1, request_value);
}
