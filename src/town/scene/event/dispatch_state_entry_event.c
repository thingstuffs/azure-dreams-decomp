#include "common.h"
#include "town/scene.h"

extern s32 scene_dispatch_mode_index;
extern s32 D_800196F4[];

/* Dispatch the current state entry when the event code is 8. */
s32 dispatch_state_entry_event_8(s32 unused_arg_0, s32 unused_arg_1, s32 event_code) {
    s32 result = 0;

    if (event_code == 8) {
        result = select_fallback_when_below_threshold(D_800196F4[scene_dispatch_mode_index]);
    }
    return result;
}
