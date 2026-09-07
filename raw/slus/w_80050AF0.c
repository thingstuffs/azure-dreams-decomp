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

/* Allocates/initializes a0's sub-buffer array starting at offset 0x6C (size 0xC),
 * stashing its 0x68-offset pointer and 0x2C-offset scratch word along the way.
 * Returns 1 on full success, 0 if any allocation step failed. */
s32 func_80050AF0(S_80050AF0 *a0, s32 a1)
{
    s32 *field6C = a0->unk6C;
    s32 result = 0;
    s32 v0;

    v0 = func_80049004(field6C, a1, 0xC);
    a0->unk68 = v0;
    if (v0 != 0) {
        v0 = (s32)func_80049150(field6C, 9, 0xC);
        if (v0 != 0) {
            func_80050A58((s32 *)a0->unk68, v0);
            v0 = func_80048FBC(field6C, 0xC);
            result = (v0 != 0);
            a0->unk2C = v0;
        }
    }
    return result;
}
