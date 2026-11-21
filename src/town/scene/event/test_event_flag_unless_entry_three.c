#include "common.h"
#include "shared/town_event_state.h"
#include "town/scene/event.h"
#include "town/player/script_flags.h"

extern s16 D_80017944;

s32 test_event_flag_unless_entry_three(void) {
    s32 passed = 0;
    if (town_event_state->selected_entry != 3) {
        passed = get_script_flag_mask(D_80017944) != 0;
    }
    return passed;
}
