#include "script_symbols.h"
#include "common.h"
#include "town/scene/mode_data.h"
#include "town/scene.h"
#include "town/player/state.h"

void set_selected_entry_state_3(void);                            /* extern */

/* Set state 1, invoke handler 0x632, and run the follow-up handler. */
void set_dispatch_mode_one_and_state_three(void) {
    scene_dispatch_mode_index = 1;
    set_script_flag_bit(F_sbs14_pad14);
    set_selected_entry_state_3();
}
