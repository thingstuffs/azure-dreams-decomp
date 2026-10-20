#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */

/* Initializes a request with selector 0 and mode 1. */
void card_boot_show_format_confirmation(s32 request_id, s32 request_value) {
    card_boot_create_or_reset_message_dialog(request_id, 0, (void *)(1), request_value);
}
