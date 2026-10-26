#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Passes value to card_boot_create_or_reset_message_dialog with 0x11 and two zero arguments. */
void card_boot_show_overwrite_protected_notice(s32 value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 0x11, zero, zero);
}
