#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "main/data.h"

s32 func_80400908(void);

/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_save_slot_selection(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    func_80400908();
    ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_80406368;
}
