#include "common.h"
#include "town/scene/mode_data.h"
#include "town/scene.h"
#include "town/scene/entry_requests.h"
#include "town/scene/flags.h"

/* Set the mode to two and dispatch according to the current state. */
void set_dispatch_mode_two(s32 state_input) {
    scene_dispatch_mode_index = 2;
    if (3 == scene_cell_dispatch_code) {
        set_selected_entry_state_3();
        return;
    }
    set_current_entry_flag();
}
