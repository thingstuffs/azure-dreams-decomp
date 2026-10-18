#include "modules/dungeon_ovl_19c088c.h"

void choose_random_sign(void *effect, s32 unused, void *primitive)
{
    s32 intensity;
    u16 ticks_left;

    ticks_left = *(u16 *)((u8 *)effect + 0x3A) - 1;
    intensity = ((s32)(ticks_left << 16) >> 9) /
            *(s16 *)((u8 *)effect + 0x3C);
    (*(s16 *)D_800261B0) = 1;
    *(u16 *)((u8 *)effect + 0x3A) = ticks_left;
    *(s8 *)((u8 *)primitive + 0x0E) = intensity;
    *(s8 *)((u8 *)primitive + 0x0D) = intensity;
    *(s8 *)((u8 *)primitive + 0x0C) = intensity;
    *(u8 *)((u8 *)effect + 0x8C) -= 1;
    *(u16 *)((u8 *)primitive + 0x1A) += *(u16 *)((u8 *)effect + 0x40);
    if (*(s16 *)((u8 *)effect + 0x3A) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
