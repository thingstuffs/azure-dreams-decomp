#include "common.h"

typedef struct {
    u8 pad00[0x38];
    s32 unk38[3];
    u8 pad44[0x54 - 0x44];
    s32 unk54;
    s32 unk58[7];
    s32 unk74;
} Unk818110CC;

extern s32 func_80049004(s32 *arg0, s32 arg1, s32 arg2);
extern s32 func_80048FBC(s32 *arg0, s32 arg1);
extern void func_800491CC(s32 arg0, s32 *arg1, s32 arg2);
extern s32 D_8002E5E8[3];

/* Copies and updates the state vector when both buffer operations succeed. */
s32 func_800260CC(Unk818110CC *state, s32 input)
{
    s32 success = 0;
    s32 *buffer = state->unk58;
    s32 call_result;

    call_result = func_80049004(buffer, input, 6);
    state->unk54 = call_result;
    if (call_result != 0) {
        call_result = func_80048FBC(buffer, 6);
        state->unk74 = call_result;
        if (call_result != 0) {
            state->unk38[0] = D_8002E5E8[0];
            state->unk38[1] = D_8002E5E8[1];
            state->unk38[2] = D_8002E5E8[2];
            func_800491CC(state->unk54, state->unk38, 13);
            success = 1;
        }
    }
    return success;
}
