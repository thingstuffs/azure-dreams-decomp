#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Forwards value to card_boot_create_or_reset_message_dialog with code 0x10 and two zero arguments. */
void card_boot_show_copy_failure_notice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, (void *)(0x10), (void *)(zero), zero);
}
