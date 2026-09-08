#include "common.h"

extern s32 func_80049004(s32 *a0, s32 a1, s32 a2);
extern s32 *func_80049150(s32 *a0, u32 a1, s32 a2);
extern s32 func_80050A58(s32 *a0, s32 a1);
extern s32 func_80048FBC(s32 *a0, s32 a1);

typedef struct S_80050AF0 {
    u8 pad_00[0x2C];
    s32 unk2C;
    u8 pad_30[0x68 - 0x30];
    s32 unk68;
    s32 unk6C[3];
} S_80050AF0;

/* Allocates and initializes sub-buffers, returning 1 if all steps succeed. */
s32 func_80050AF0(S_80050AF0 *state, s32 allocation_arg)
{
    s32 *sub_buffers = state->unk6C;
    s32 success = 0;
    s32 step_result;

    step_result = func_80049004(sub_buffers, allocation_arg, 0xC);
    state->unk68 = step_result;
    if (step_result != 0) {
        step_result = (s32)func_80049150(sub_buffers, 9, 0xC);
        if (step_result != 0) {
            func_80050A58((s32 *)state->unk68, step_result);
            step_result = func_80048FBC(sub_buffers, 0xC);
            success = (step_result != 0);
            state->unk2C = step_result;
        }
    }
    return success;
}
