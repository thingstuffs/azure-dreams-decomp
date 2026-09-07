#include "common.h"

#include "common.h"

typedef struct Func8003A7BCState {
    u8 pad00[0x1C];
    u8 *input;
    u8 pad20[0x60];
    s32 *table;
} Func8003A7BCState;

void func_8003A7BC(Func8003A7BCState *state)
{
    u8 *input = state->input;
    u8 first = *input;

    state->input = input + 1;
    input = state->input;

    {
        u8 second = *input;
        state->input = input + 1;
        state->table[first + 0x12] = state->table[second + 0x12];
    }
}
