#include "common.h"

typedef struct S_func_819A0FC0_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    s16 unk_3C;
} S_func_819A0FC0_0;

typedef struct S_func_819A0FC0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_func_819A0FC0_1;

typedef struct S_func_819A0FC0_2 {
    u16 unk_00;
} S_func_819A0FC0_2;

extern s16 D_800261B0;
extern s32 D_800814A0;

// Decrement the fade timer, update the primitive's brightness, and flag completion.
void func_819A0FC0(S_func_819A0FC0_0 *fadeState, void *unused, S_func_819A0FC0_1 *primitive)
{
    s32 brightness;
    u16 remainingTicks;

    remainingTicks = fadeState->unk_3A - 1;
    brightness = (s32)((s32)(remainingTicks << 0x10) >> 9) /
                 (s16)fadeState->unk_3C;
    D_800261B0 = 1;
    fadeState->unk_3A = remainingTicks;
    primitive->unk_0E = (s8)brightness;
    primitive->unk_0D = (s8)brightness;
    primitive->unk_0C = (s8)brightness;
    if ((s16)fadeState->unk_3A <= 0) {
        *(u16 *)((u8 *)fadeState - 2) =
            (u16)(((S_func_819A0FC0_2 *)((u8 *)fadeState - 2))->unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
