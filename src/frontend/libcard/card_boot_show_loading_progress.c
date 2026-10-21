#include "common.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Dispatches request 14 with parameter 2 for the parent and its status pointer. */
void card_boot_show_loading_progress(s32 parent, s32 status) {
    card_boot_create_or_reset_message_dialog(parent, (void *)(0xe), (void *)(2), status);
}
