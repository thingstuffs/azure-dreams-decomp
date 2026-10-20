#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Forwards the input value with 0xD and two zero arguments to card_boot_create_or_reset_message_dialog. */
void card_boot_show_format_success_notice(s32 input_value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(input_value, (void *)(0xd), (void *)(zero), zero);
}
