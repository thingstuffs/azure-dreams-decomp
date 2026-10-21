#include "common.h"
#include "engine/script/vm.h"

typedef struct RuntimeState {
    u8 pad0[0x1C];
    u8 *input;
    u8 pad20[0x68];
    u8 current;
} RuntimeState;

/* Consume one event-script byte and store it as the current value. */
void vm_op_84_set_loop_counter(RuntimeState *state)
{
    u8 *input = state->input;
    u8 current = *input;

    state->input = input + 1;
    state->current = current;
}
