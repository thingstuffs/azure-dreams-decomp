#include "common.h"

typedef struct TownInput {
    u8 pad0[3];
    s8 value;
} TownInput;

typedef struct TownState {
    u8 pad0[0x3188];
    s32 value;
} TownState;

typedef struct TownRoot {
    u8 pad0[0x38];
    TownState *state;
} TownRoot;

extern TownRoot *D_80016000[3];

/* Check whether the low six input bits match the town state value. */
s32 func_80018ABC(TownInput *input)
{
    TownState *state = D_80016000[0]->state;
    s32 value = input->value;

    value &= 0x3F;
    return state->value == value;
}
