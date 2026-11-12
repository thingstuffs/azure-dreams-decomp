#include "common.h"
#include "town/scene/mode_data.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/flags.h"


/* Set state 4 and run the transition handler when the mode is 2. */
void enter_mode_4_when_state_2(void) {
    if (scene_cell_dispatch_code == 2) {
        scene_dispatch_mode_index = 4;
        clear_indexed_entry_flag();
    }
}
