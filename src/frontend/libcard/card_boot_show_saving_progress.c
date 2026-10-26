#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Forward the target and value to card_boot_create_or_reset_message_dialog with fixed parameters 6 and 2. */
void card_boot_show_saving_progress(s32 target, s32 value) {
    card_boot_create_or_reset_message_dialog(target, 6, 2, value);
}
