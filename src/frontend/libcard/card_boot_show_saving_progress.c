#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Forward the target and value to card_boot_create_or_reset_message_dialog with fixed parameters 6 and 2. */
void card_boot_show_saving_progress(s32 target, s32 value) {
    card_boot_create_or_reset_message_dialog(target, (void *)(6), (void *)(2), value);
}
