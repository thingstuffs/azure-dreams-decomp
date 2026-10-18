#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Forward the target and value to card_boot_create_or_reset_message_dialog with fixed parameters 6 and 2. */
void card_boot_show_saving_progress(M2C_UNK target, M2C_UNK value) {
    card_boot_create_or_reset_message_dialog(target, 6, 2, value);
}
