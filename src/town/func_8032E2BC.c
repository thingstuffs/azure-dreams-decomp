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

s32 func_80018ABC(TownInput *arg0)
{
    TownState *state = D_80016000[0]->state;
    s32 value = arg0->value;

    value &= 0x3F;
    return state->value == value;
}
