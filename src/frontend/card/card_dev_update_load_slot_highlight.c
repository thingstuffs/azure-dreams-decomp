#include "common.h"
#include "shared/widget_views.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "main/data.h"

void func_80400908(void);                            /* extern */

/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_load_slot_highlight(void *record_data) {
    card_devkit_highlight_selected_load_slot(record_data);
    func_80400908();
    ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = &D_80406DA0;
}
