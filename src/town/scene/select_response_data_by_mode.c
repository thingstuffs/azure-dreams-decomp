#include "common.h"
#include "town/scene.h"
#include "town/scene/event.h"

extern u8 scene_mode_response_data[];
extern u8 D_8001914C[];
extern u8 D_8001EEA7[];
extern u8 D_8001F0AA[];

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
        data = D_8001914C;
    } else {
        set_event_state_and_dispatch_a_2();
        data = D_8001F0AA;
    }
    return data;
}
