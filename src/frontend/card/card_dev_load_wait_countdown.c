#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void card_dev_load_wait_countdown(void *record_data) {
    s32 counter;

    counter = ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown - 1;
    ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown = counter;
    if (counter < 0) {
        ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_80406AA8;
    }
}
