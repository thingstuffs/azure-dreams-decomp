#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct TownInput {
    u8 pad0[3];
    s8 value;
} TownInput;

typedef struct TownState {
    u8 pad0[0x3188];
    s32 value;
} TownState;


/* Check whether the low six input bits match the town state value. */
s32 func_80018ABC(TownInput *input)
{
    TownState *state = ((TownState *)D_80016000->unk_38);
    s32 value = input->value;

    value &= 0x3F;
    return state->value == value;
}
