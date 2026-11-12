#include "common.h"
#include "town/scene/mode_data.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern s32 set_selected_entry_state_3(s32);

/* Set the mode to two and dispatch according to the current state. */
void dispatch_mode_two_by_state(s32 state_input) {
    scene_dispatch_mode_index = 2;
    if (3 == scene_cell_dispatch_code) {
        set_selected_entry_state_3(state_input);
        return;
    }
    set_indexed_entry_flag_b();
}
