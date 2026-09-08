#include "common.h"

typedef struct Func800391ECState {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[8];
    u8 value;
} Func800391ECState;

/* Read the next event-script byte into the state's value and advance the read pointer. */
void func_800391EC(Func800391ECState *state) {
    u8 *script_ptr = state->read_ptr;
    u8 value = *script_ptr;

    script_ptr++;
    state->read_ptr = script_ptr;
    state->value = value;
}
