#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/card/save.h"
#include "main/data.h"

/* Process the record data and set its preceding header pointer. */
void invoke_callback_with_zero(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_80406368;
}
