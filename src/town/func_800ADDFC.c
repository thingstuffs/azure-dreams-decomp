#include "town_callbacks_api.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/person.h"
#include "town/person/motion.h"

typedef struct town_timed_transition_state {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[4];
    u16 unk72;
    u8 pad_74[0x1C];
    s16 value;
} State;




/* Changes the handler below value 100 and on timer expiry; otherwise turns field +0x72 by -0x400. */
void update_timed_state_transition(State *state) {
    u16 timer;

    if (state->value < 100) {
        state->state = move_person_toward_sample;
    }
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16) timer < 0) {
        state->state = update_person_coordinates;
        state->timer = 150;
        return;
    }
    state->unk72 -= 0x400;
}
