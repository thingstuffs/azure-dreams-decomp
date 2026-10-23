#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*Callback)(s32);


extern s32 build_selected_entry_output(s32);
extern s32 build_entry_list(s32);

/* Updates the selected entry using a callback-selected lookup when state is 2. */
s32 store_state_2_entry_by_callback(void *object, s32 entry_index) {
    if (town_event_state->selection_mode == 2) {
        if ((*(Callback *)((s8 *)*(void **)((s8 *)town_scene_root + 0x20) + 0x2D4))(0) == 2) {
            *(s32 *)((entry_index << 4) + *(s32 *)((u8 *)object + 0x10) + 8) =
                build_selected_entry_output(town_event_state->selected_entry);
        } else {
            *(s32 *)((entry_index << 4) + *(s32 *)((u8 *)object + 0x10) + 8) =
                build_entry_list(town_event_state->selected_entry);
        }
        return 0;
    }
    return 1;
}
