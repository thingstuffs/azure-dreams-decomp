#include "common.h"

#include "common.h"
#include "engine/script.h"

typedef struct Func8003A7BCState {
    u8 pad00[0x1C];
    u8 *input;
    u8 pad20[0x60];
    s32 *table;
} Func8003A7BCState;

/* Opcode 0x44: Copy variable: v[dst] = v[src] (same as opcode 0x33). */
void script_copy_variable_b(Func8003A7BCState *state)
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
