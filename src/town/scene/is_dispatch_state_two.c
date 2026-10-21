#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"



/* Returns whether the current record's unk_01 field is 2. */
s32 is_dispatch_state_two(void) {
    return town_event_state->dispatchState == 2;
}
