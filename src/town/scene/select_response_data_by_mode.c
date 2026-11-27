#include "common.h"
#include "town/scene.h"
#include "town/scene/event.h"
#include "town/data.h"

extern u8 home_default_event_response[];
extern u8 D_8001EEA7[];
extern u8 home_ending_event_response[];

/* Select data by mode, initializing the data for mode 0. */
u8 *select_response_data_by_mode(s32 unused_0, s32 unused_1, s32 mode) {
    u8 *data;

    if (mode == 4) {
        return D_8001EEA7;
    }
    if (mode == 5) {
        return scene_mode_response_data;
    }
    if (mode != 0) {
        data = home_default_event_response;
    } else {
        set_ending_event_state();
        data = home_ending_event_response;
    }
    return data;
}
