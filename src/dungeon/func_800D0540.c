#include "common.h"

extern s32 D_800814A0;

void func_800D5CA0(u8 *effect, s32 *motion)
{
    s16 timer;

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

    timer = *(u16 *)(effect + 0x32) - 1;
    *(s16 *)(effect + 0x32) = timer;
    *(s32 *)(effect + 8) = *(s32 *)(effect + 4);
    if (timer <= 0) {
        *(u16 *)(effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A frameless leaf with natural array compound updates lets cdk-G0
   retain motion[4] in a2; direct per-channel byte assignments force the three
   scale/divisor reloads, and the scalar global RMW yields the held hi/lo base. */
