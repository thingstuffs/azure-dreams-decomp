#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard/card_boot_create_or_reset_message_dialog_api.h"   /* extern */
#include "frontend/libcard.h"

/* Initialize the context in mode 1 with zero optional arguments. */
void card_boot_show_no_memory_card_notice(s32 context) {
    s32 zero = 0;
    card_boot_create_or_reset_message_dialog(context, (void *)(1), (void *)(zero), zero);
}
