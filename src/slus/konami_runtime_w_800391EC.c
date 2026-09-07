#include "common.h"

typedef struct Func800391ECState {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[8];
    u8 value;
} Func800391ECState;

void func_800391EC(Func800391ECState *state) {
    u8 *ptr = state->read_ptr;
    u8 value = *ptr;

    ptr++;
    state->read_ptr = ptr;
    state->value = value;
}
