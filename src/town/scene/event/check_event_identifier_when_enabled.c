#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"
#include "town/data.h"
#include "town/player/state.h"

/* Return whether the identifier check passes when the state permits it. */
s32 check_event_identifier_when_enabled(void) {
    s32 check_passed;

    check_passed = 0;
    if (town_event_state->selected_entry != 1) {
        check_passed = get_script_flag_mask(scene_event_test_id) != 0;
    }
    return check_passed;
}
