#include "town/person/state_callbacks_api.h"
#include "common.h"
#include "town/person/motion.h"
#include "town/person/state.h"

/* Update the state from its value and countdown, advancing unk72 until timeout. */
void advance_person_state_value(TownObjectRecord *state) {
    u16 timer;

    if (state->unk_90 < 100) {
        state->unk_50.as_pm = move_person_toward_sample;
    }
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16) timer < 0) {
        state->unk_50.as_pm = update_person_countdown_state;
        state->timer = 20;
        return;
    }
    state->heading += 0x200;
}
