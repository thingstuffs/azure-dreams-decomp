#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Forwards the input and value with both middle arguments set to 2. */
void card_boot_show_please_wait_notice(s32 input, s32 value) {
    card_boot_create_or_reset_message_dialog(input, (void *)(2), (void *)(2), value);
}
