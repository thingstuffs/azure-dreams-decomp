#include "common.h"

extern void apply_entry_position(void *, void *, s32, s32);
extern s32 D_8001B920;
extern u8 D_8001B924[];
extern u8 D_8001B944[];
extern s32 scene_dispatch_context;

// Dispatches a value and code with state-selected data, setting the state for codes other than 0x2D.
void dispatch_state_selected_code(s32 value, s32 unused, s32 code) {
    void *selectedData;

    if (D_8001B920 != 0) {
        selectedData = D_8001B944;
    } else {
        selectedData = D_8001B924;
    }
    if (code != 0x2D) {
        D_8001B920 = 1;
    }
    apply_entry_position(selectedData, &scene_dispatch_context, value, code);
}
