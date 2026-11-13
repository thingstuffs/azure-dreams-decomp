#include "common.h"
#include "m2c_compat.h"
#include "slus.h"
#include "town/shop.h"
#include "town/shop/shop_window_layout_g00610.h"


extern M2C_UNK D_80071244;


/* Apply D_800792DC using the linked value and set the linked target to D_80071244. */
void apply_linked_record_defaults(void *record_arg) {
    ShopRecordResetObject *record = record_arg;

    initialize_scaled_entry_cursor(&record->stream_state, &shop_cursor_template, (s32 *)record->record_resources[4]);
    record->record_resources[5]->handler = &D_80071244;
}
