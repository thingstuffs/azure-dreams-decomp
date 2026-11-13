#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Calls card_boot_create_or_reset_message_dialog with selector 9 and two zero arguments. */
void card_boot_show_no_space_overwrite_notice(ObjectNodeHeader *value) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(value, 9, zero, NULL);
}
