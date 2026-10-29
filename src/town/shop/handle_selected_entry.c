#include "common.h"

#include "slus.h"
#include "town/shop.h"
#include "town/shop/object.h"
#include "town/system.h"

extern s32 check_entry_limit_or_combined_value(void *entry);

extern void *D_800D1558;
extern void *D_800D155C;

/* Handles the selected entry according to its type, flags, and availability. */
void handle_selected_entry(s32 *state) {
    u8 *selected_entry;

    selected_entry = (u8 *) (state[1] * 4 + state[8]);
    if (selected_entry[1] != 0x16) {
        if (!(selected_entry[3] & 0x80)) {
            if (check_entry_limit_or_combined_value(state) != 0) {
                SD_Call(0x503);
                toggle_selected_entry_flag(state);
                process_shop_object_data(state[10]);
                return;
            }
            SD_Call(0x506);
            submit_script_with_registered_context(D_800D1558);
            return;
        }
        SD_Call(0x506);
        if (state[6] == 1) {
            submit_script_with_registered_context(D_800D155C);
            return;
        }
    } else {
        close_twin_shop((s8 *) state - 0x20);
        store_record_check_result(state);
    }
}
