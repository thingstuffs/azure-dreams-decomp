#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Start operation 4 in mode 2 with the owner and status flag. */
void card_boot_show_formatting_progress(s32 owner, s32 status_flag) {
    card_boot_create_or_reset_message_dialog(owner, (void *)(4), (void *)(2), status_flag);
}
