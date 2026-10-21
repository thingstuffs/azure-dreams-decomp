#include "common.h"

extern s32 check_inputs_after_threshold_two(s32);
extern s32 scene_dispatch_mode_index;
extern s32 D_800196F4[];

/* Dispatch the current state entry when the event code is 8. */
s32 dispatch_state_entry_event_8(s32 unused_arg_0, s32 unused_arg_1, s32 event_code) {
    s32 result = 0;

    if (event_code == 8) {
        result = check_inputs_after_threshold_two(D_800196F4[scene_dispatch_mode_index]);
    }
    return result;
}
