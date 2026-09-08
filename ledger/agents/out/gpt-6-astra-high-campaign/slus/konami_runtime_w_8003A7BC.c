#include "common.h"

#include "common.h"

typedef struct Func8003A7BCState {
    u8 pad00[0x1C];
    u8 *input;
    u8 pad20[0x60];
    s32 *table;
} Func8003A7BCState;

/* Copies an event-script table value using destination and source indices read from the script. */
void func_8003A7BC(Func8003A7BCState *state)
{
    u8 *script_ptr = state->input;
    u8 destination = *script_ptr;

    state->input = script_ptr + 1;
    script_ptr = state->input;

    {
        u8 source = *script_ptr;
        state->input = script_ptr + 1;
        state->table[destination + 0x12] = state->table[source + 0x12];
    }
}
