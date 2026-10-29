#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"



/* Checks whether D_8001E950's unk_04 field equals 6. */
s32 is_event_state_six(void) {
    return town_event_state->selected_entry == 6;
}
