#include "modules/dungeon_resource08_slot0.h"

void func_80174318(void *effect, s32 x, s32 y)
{
    s32 ticks_left = *(s16 *)((u8 *)effect + 0x1A);

    if (ticks_left >= 16) {
        func_801741D0(effect, x, y,(s8)(0x70), 16);
    } else {
        func_801741D0(effect, x, y,(s8)(0x70),
                      ((15 - ticks_left) * 6 + 16) & 0xFF);
    }

    {
        s32 next_ticks;

        next_ticks = (u16)*(s16 *)((u8 *)effect + 0x1A) - 1;
        *(s16 *)((u8 *)effect + 0x1A) = next_ticks;
        if ((next_ticks << 16) <= 0) {
            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
