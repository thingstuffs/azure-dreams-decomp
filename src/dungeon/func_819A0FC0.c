#include "common.h"

#define FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern s16 D_800261B0;
extern s32 D_800814A0;

// Decrement the fade timer, update the primitive's brightness, and flag completion.
void func_819A0FC0(void *fadeState, void *unused, void *primitive)
{
    s32 brightness;
    u16 remainingTicks;

    remainingTicks = FIELD(fadeState, u16 *, 0x3A) - 1;
    brightness = (s32)((s32)(remainingTicks << 0x10) >> 9) /
                 (s16)FIELD(fadeState, s16 *, 0x3C);
    D_800261B0 = 1;
    FIELD(fadeState, u16 *, 0x3A) = remainingTicks;
    FIELD(primitive, s8 *, 0xE) = (s8)brightness;
    FIELD(primitive, s8 *, 0xD) = (s8)brightness;
    FIELD(primitive, s8 *, 0xC) = (s8)brightness;
    if ((s16)FIELD(fadeState, u16 *, 0x3A) <= 0) {
        FIELD(fadeState, u16 *, -2) =
            (u16)(FIELD(fadeState, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
