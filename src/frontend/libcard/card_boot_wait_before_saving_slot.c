#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Decrement the record's countdown and reset its pointer when it becomes negative. */
void card_boot_wait_before_saving_slot(void *record_data) {
    s32 countdown;

    countdown = ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown - 1;
    ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown = countdown;
    if (countdown < 0) {
        ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_800262BC;
    }
}
