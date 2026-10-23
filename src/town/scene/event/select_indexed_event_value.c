#include "shared/town_event_state.h"
#include "common.h"

extern s32 scene_event_data;
extern u8 scene_mode_event_data[];
extern s32 D_80017FD4[];
extern s32 D_80017FF4[];

/* Returns a fixed address or a state-indexed value, marking the first table lookup. */
s32 select_indexed_event_value(s32 unused_arg0, s32 unused_arg1, s32 selector)
{
    if (selector == 5) {
        return scene_mode_event_data;
    }
    if (selector == 4) {
        return &scene_event_data;
    }
    if (selector == 1) {
        return D_80017FF4[town_event_state->unk_04];
    }
    if (town_event_state->unk_06 == 0) {
        town_event_state->unk_06 = 1;
        return D_80017FD4[town_event_state->unk_04];
    }
    return D_80017FF4[town_event_state->unk_04];
}
