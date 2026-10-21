#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"


extern M2C_UNK D_8001FB20;

/* Increment the record's byte counter and return D_8001FB20. */
s32 *advance_event_state_and_get_resource(void) {
    town_event_state->dispatchState = (u8) (town_event_state->dispatchState + 1);
    return &D_8001FB20;
}
