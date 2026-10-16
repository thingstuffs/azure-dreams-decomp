#include "modules/dungeon_ovl_19c088c.h"

void func_800247C0(Row_819A0FC0_S_func_819A0FC0_0 *fadeState, void *unused, Row_819A0FC0_S_func_819A0FC0_1 *primitive)
{
    s32 brightness;
    u16 remainingTicks;

    remainingTicks = fadeState->unk_3A - 1;
    brightness = (s32)((s32)(remainingTicks << 0x10) >> 9) /
                 (s16)fadeState->unk_3C;
    (*(s16 *)D_800261B0) = 1;
    fadeState->unk_3A = remainingTicks;
    primitive->unk_0E = (s8)brightness;
    primitive->unk_0D = (s8)brightness;
    primitive->unk_0C = (s8)brightness;
    if ((s16)fadeState->unk_3A <= 0) {
        *(u16 *)((u8 *)fadeState - 2) =
            (u16)(((Row_819A0FC0_S_func_819A0FC0_2 *)((u8 *)fadeState - 2))->unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
