#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Initialize the owner's request with type 0xf, mode 2, and its data. */
void card_boot_show_copying_progress(s32 owner, s32 data) {
    card_boot_create_or_reset_message_dialog(owner, (void *)(0xf), (void *)(2), data);
}
