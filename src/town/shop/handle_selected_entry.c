#include "common.h"

extern void submit_script_with_registered_context(s32 context);
extern void SD_Call(s32 flags);
extern void toggle_selected_entry_flag(void *state);
extern void store_record_check_result(void *record);
extern s32 check_entry_limit_or_combined_value(void *entry);
extern void close_twin_shop(void *shop);
extern void process_shop_object_data(s32 object_addr);

extern s32 D_800D1558;
extern s32 D_800D155C;

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
