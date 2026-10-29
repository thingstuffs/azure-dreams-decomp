#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene/event.h"

extern s32 scene_event_data;
extern u8 scene_mode_event_data[];
extern s32 D_80017FD4[];
extern s32 town_indexed_event_values[];

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
        return town_indexed_event_values[town_event_state->selected_entry];
    }
    if (town_event_state->response_latch == 0) {
        town_event_state->response_latch = 1;
        return D_80017FD4[town_event_state->selected_entry];
    }
    return town_indexed_event_values[town_event_state->selected_entry];
}
