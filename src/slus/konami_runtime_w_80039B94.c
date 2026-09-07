#include "common.h"

typedef void (*Callback)(void);

typedef struct {
    u8 pad_00[0x10];
    Callback callback;
    u8 pad_14[0x8];
    u8 *stream;
    u8 pad_20[0xF];
    u8 value_2F;
} Func80039B94State;

extern void func_800383D4(void);

void func_80039B94(Func80039B94State *state) {
    u8 *stream = state->stream;
    u8 value = *stream;

    state->stream = stream + 1;
    state->callback = func_800383D4;
    state->value_2F = value;
}
