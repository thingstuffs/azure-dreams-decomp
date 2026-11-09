#include "town/person/state_callbacks_api.h"
#include "common.h"
#include "town/person/motion.h"
#include "town/person/state.h"

typedef struct town_person_value_state {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[4];
    u16 unk72;
    u8 pad_74[0x1C];
    s16 value;
} State;




/* Update the state from its value and countdown, advancing unk72 until timeout. */
void advance_person_state_value(State *state) {
    u16 timer;

    if (state->value < 100) {
        state->state = move_person_toward_sample;
    }
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16) timer < 0) {
        state->state = update_person_countdown_state;
        state->timer = 20;
        return;
    }
    state->unk72 += 0x200;
}
