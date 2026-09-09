#include "common.h"

typedef struct {
    u8 pad_00[8];
    s32 index;
    u8 pad_0C[0x34];
    u8 *bytes;
} TownState;

extern TownState *D_80016000;
extern void func_80017BA0(s32, s32);

s32 func_804B7AC0(s32 arg0, s32 arg1)
{
    TownState *state_before;
    TownState *state_after;

    state_before = D_80016000;
    if (state_before->bytes[state_before->index * 8] < 2U) {
        return 0;
    }
    func_80017BA0(arg0, arg1);
    state_after = D_80016000;
    state_after->bytes[state_after->index * 8] = 0;
    return 1;
}
