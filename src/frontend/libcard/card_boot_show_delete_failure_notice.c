#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Dispatches command 0x13 with the supplied argument and two zero arguments. */
void card_boot_show_delete_failure_notice(s32 command_arg) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(command_arg, 0x13, zero, zero);
}
