#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *stream;
    u8 pad_20[0x60];
    u8 *buffer;
} Func80039AF0State;

extern u8 D_8007216C[];

void func_80039AF0(Func80039AF0State *state) {
    state->buffer[1] = *state->stream++;
    state->buffer[0x3C] = D_8007216C[state->buffer[1]];
}
