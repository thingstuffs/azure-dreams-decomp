#include "common.h"
#include "m2c_compat.h"

u8 *card_boot_create_or_reset_message_dialog();   /* extern */

/* Initialize the context in mode 1 with zero optional arguments. */
void card_boot_show_no_memory_card_notice(s32 context) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(context, 1, zero, zero);
}
