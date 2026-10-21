#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"



/* Returns whether D_8001E950->unk_04 equals 3. */
s32 is_event_state_three(void) {
    return town_event_state->unk_04 == 3;
}
