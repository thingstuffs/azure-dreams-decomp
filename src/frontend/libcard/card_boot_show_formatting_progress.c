#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Start operation 4 in mode 2 with the owner and status flag. */
void card_boot_show_formatting_progress(ObjectNodeHeader *owner, s32 *result) {
    card_boot_create_or_reset_message_dialog(owner, 4, 2, result);
}
