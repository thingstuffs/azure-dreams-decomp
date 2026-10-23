#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

/* Decrement the record's countdown and switch its pointer when the count goes negative. */
void card_dev_menu_wait_countdown(void *record_data) {
    s32 countdown;

    countdown = ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown - 1;
    ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown = countdown;
    if (countdown < 0) {
        ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_80405DE0;
    }
}
