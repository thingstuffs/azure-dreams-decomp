#include "common.h"

extern s32 initialize_floor_generation_state();
extern s32 set_selected_entry_state_3(s32);
typedef struct {
    s32 value;
    s32 pad[2];
} Global32;

extern Global32 scene_dispatch_mode_index;
extern Global32 scene_cell_dispatch_code;

/* Set the mode to two and dispatch according to the current state. */
void dispatch_mode_two_by_state(s32 state_input) {
    scene_dispatch_mode_index.value = 2;
    if (3 == scene_cell_dispatch_code.value) {
        set_selected_entry_state_3(state_input);
        return;
    }
    initialize_floor_generation_state();
}
