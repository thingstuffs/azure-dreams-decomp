#include "common.h"
#include "town/scene.h"
#include "town/scene/event.h"

extern u8 scene_event_data[];
extern u8 scene_mode_event_data[];
extern u8 D_80022E7E[];

/* Select data by mode, calling advance_event_dispatch_state for mode one. */
void *select_event_data_advancing_on_mode_one(s32 setup_value, s32 setup_option, s32 mode) {
    if (mode == 1) {
        advance_event_dispatch_state();
        return D_80022E7E;
    } else if (mode == 4) {
        return scene_event_data;
    } else {
        return scene_mode_event_data;
    }
}
