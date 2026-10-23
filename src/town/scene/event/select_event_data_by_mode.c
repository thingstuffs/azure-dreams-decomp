#include "shared/town_event_state.h"
#include "common.h"

extern s8 scene_event_data[];
extern u8 scene_mode_event_data[];
extern void *D_80018034[];

/* Select fixed data by mode or look up data using the current table index. */
void *select_event_data_by_mode(s32 unused_value, s32 unused_option, s32 mode)
{
    if (mode == 4) {
        return scene_event_data;
    } else if (mode == 5) {
        return scene_mode_event_data;
    } else {
        return D_80018034[town_event_state->unk_03];
    }
}
