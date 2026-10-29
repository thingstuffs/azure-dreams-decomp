#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Increment the record counter if it is below two. */
void advance_dispatch_state_to_two(void) {
    u8 counter;

    counter = town_event_state->dispatchState;
    if (counter < 2U) {
        town_event_state->dispatchState = (u8) (counter + 1);
    }
}
