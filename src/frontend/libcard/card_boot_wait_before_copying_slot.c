#include "common.h"
#include "shared/widget_views.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void card_boot_wait_before_copying_slot(void *record_data) {
    s32 counter;

    counter = ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown - 1;
    ((CardCallbackState *)((u8 *)record_data - 0x10))->countdown = counter;
    if (counter < 0) {
        ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_80025398;
    }
}
