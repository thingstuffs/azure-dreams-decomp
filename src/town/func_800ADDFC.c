#include "town.h"
/* Recovered retail twin. */
#include "common.h"
#include "town/person.h"
#include "town/person/motion.h"

/* Changes the handler below value 100 and on timer expiry; otherwise turns field +0x72 by -0x400. */
void update_timed_state_transition(TownObjectRecord *state) {
    u16 timer;

    if (state->unk_90 < 100) {
        state->state_callback.as_pm = move_person_toward_sample;
    }
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16) timer < 0) {
        state->state_callback.as_pm = update_person_coordinates;
        state->timer = 150;
        return;
    }
    state->heading -= 0x400;
}
