#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Checks whether the current record's unk_04 field equals one. */
s32 is_first_entry_selected(void) {
    return town_event_state->selected_entry == 1;
}
