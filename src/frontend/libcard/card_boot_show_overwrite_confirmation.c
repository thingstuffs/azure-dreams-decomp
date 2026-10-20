#include "common.h"
#include "frontend/libcard/interfaces.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Initialize a type-5, mode-1 context with the supplied owner and data. */
void card_boot_show_overwrite_confirmation(s32 owner, s32 data) {
    card_boot_create_or_reset_message_dialog(owner, (void *)(5), (void *)(1), data);
}
