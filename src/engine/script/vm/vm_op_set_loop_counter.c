#include "common.h"
#include "engine/script/vm.h"

typedef struct RuntimeState {
    u8 pad0[0x1C];
    u8 *input;
    u8 pad20[0x68];
    u8 current;
} RuntimeState;

/* Opcode 0x54: Set the loop counter (+0x88) to u8. */
void script_set_loop_counter(RuntimeState *state)
{
    u8 *input = state->input;
    u8 current = *input;

    state->input = input + 1;
    state->current = current;
}
