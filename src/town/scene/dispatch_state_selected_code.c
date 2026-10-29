#include "common.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern s32 scene_dispatch_started;
extern u8 D_8001B924[];
extern u8 D_8001B944[];
extern s32 scene_dispatch_context;

// Dispatches a value and code with state-selected data, setting the state for codes other than 0x2D.
void dispatch_state_selected_code(s32 value, s32 unused, s32 code) {
    void *selectedData;

    if (scene_dispatch_started != 0) {
        selectedData = D_8001B944;
    } else {
        selectedData = D_8001B924;
    }
    if (code != 0x2D) {
        scene_dispatch_started = 1;
    }
    apply_entry_position(selectedData, &scene_dispatch_context, value, code);
}
