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

extern u8 D_800AB50C[];
extern u8 D_800AB708[];

/* Update the state from its value and countdown, advancing unk72 until timeout. */
void func_800AB4A8(State *state) {
    u16 timer;

    if (state->value < 100) {
        state->state = D_800AB708;
    }
    timer = state->timer - 1;
    state->timer = timer;
    if ((s16) timer < 0) {
        state->state = D_800AB50C;
        state->timer = 20;
        return;
    }
    state->unk72 += 0x200;
}
