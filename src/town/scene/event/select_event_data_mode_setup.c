#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/event.h"

extern M2C_UNK scene_event_data;
extern u8 scene_mode_event_data[];
extern M2C_UNK D_8002576F;

/* Select data by mode, calling advance_dispatch_state_to_two for modes other than four and five. */
s32 *select_event_data_with_mode_setup(s32 setup_value, s32 setup_option, s32 mode) {
    s32 *selected_data;

    if (mode == 5) {
        selected_data = (s32 *)scene_mode_event_data;
        return selected_data;
    }
    if (mode != 4) {
        advance_dispatch_state_to_two();
        selected_data = &D_8002576F;
    } else {
        selected_data = &scene_event_data;
    }
    return selected_data;
}
