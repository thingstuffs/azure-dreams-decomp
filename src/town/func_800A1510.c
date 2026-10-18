#include "common.h"

extern s32 get_nearest_unflagged_s_result_n_1_none_available(s32 record_set, void *target);
extern void select_a_town_entry_writes_root_relative_coordinates_output(s32 entryIndex);
extern s32 find_target_byte_index_in_list(void);
extern s32 D_8009ED7C;
extern u8 D_80100B3B;

/* Resets object state and passes the selected result to select_a_town_entry_writes_root_relative_coordinates_output. */
void reset_object_state_passes_selected_result_callee_800_a_00_e_8(void *object, void *status, void *context) {
    s32 result;
    *((s8 *)status + 0x15) = 0;
    *(s32 *)((u8 *)context + 0xC) = 0;
    *(s32 *)((u8 *)context + 0x10) = 0;
    *(s32 *)((u8 *)context + 0x14) = 0;
    *(s32 **)((u8 *)object + 0x50) = &D_8009ED7C;
    *(s16 *)((u8 *)object + 0x6C) = 0xA;
    if (*((u8 *)object + 0x4D) == 0x13) {
        result = D_80100B3B;
    } else {
        result = get_nearest_unflagged_s_result_n_1_none_available(find_target_byte_index_in_list(), context);
    }
    select_a_town_entry_writes_root_relative_coordinates_output(result);
}
