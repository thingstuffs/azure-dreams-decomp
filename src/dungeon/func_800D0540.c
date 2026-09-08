#include "common.h"

extern s32 D_800814A0;

/* Advance and damp effect motion, fade its colors, and flag expiration. */
void func_800D5CA0(u8 *effect, s32 *motion)
{
    s16 ticks_left;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[3] /= 2;
    motion[4] /= 2;
    motion[5] /= 2;

    effect[4] = (effect[0] * *(s16 *)(effect + 0x32)) /
                *(s16 *)(effect + 0x34);
    effect[5] = (effect[1] * *(s16 *)(effect + 0x32)) /
                *(s16 *)(effect + 0x34);
    effect[6] = (effect[2] * *(s16 *)(effect + 0x32)) /
                *(s16 *)(effect + 0x34);

    ticks_left = *(u16 *)(effect + 0x32) - 1;
    *(s16 *)(effect + 0x32) = ticks_left;
    *(s32 *)(effect + 8) = *(s32 *)(effect + 4);
    if (ticks_left <= 0) {
        *(u16 *)(effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
