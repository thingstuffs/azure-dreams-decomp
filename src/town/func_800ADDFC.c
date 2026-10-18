/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

typedef struct {
    u8 pad_00[0x50];
    void *state;
    u8 pad_54[0x18];
    u16 timer;
    u8 pad_6E[4];
    u16 unk72;
    u8 pad_74[0x1C];
    s16 value;
} State;

extern u8 D_800AB408[];
extern u8 D_800AB708[];

void update_timed_state_transition(State *state) {
    u16 timer;

    if (state->value < 100) {
        state->state = D_800AB708;
    }
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16) timer < 0) {
        state->state = D_800AB408;
        state->timer = 150;
        return;
    }
    state->unk72 -= 0x400;
}
