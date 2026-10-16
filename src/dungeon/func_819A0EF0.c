#include "modules/dungeon_ovl_19c088c.h"

void func_800246F0(void *effect, Row_819A0EF0_S_800246F0_2 *motion, Rec_D_80082E80 *primitive)
{
    s32 brightness;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 ticks_left;

    ticks_left = ((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.s;
    ((s16 *)D_800261B0)[0] = 1;
    ((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.s = ticks_left - 1;
    func_800478B8(primitive);
    brightness = ((s16)((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.s << 7) /
            ((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3C;
    primitive->unk_0C.at02_s8.v = brightness;
    primitive->unk_0C.at01_s8.v = brightness;
    primitive->unk_0C.at00_s8.v = brightness;
    x = motion->unk_00;
    dx = motion->unk_0C;
    y = motion->unk_04;
    dy = motion->unk_10;
    motion->unk_00 = x + dx;
    motion->unk_04 = y + dy;
    if (((Row_819A0EF0_S_800246F0_0 *)effect)->unk_3A.u <= 0) {
        ((Row_819A0EF0_S_800246F0_0_pre *)effect)[-1].unk_00 |= 0x8000;
        ((Row_819A0EF0_S_800246F0_3 *)((u8 *)(&objectFlagBlock)))->unk_00 |= 0x8000;
    }
}
