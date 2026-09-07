#include "common.h"

extern s32 D_800814A0;
extern void *D_80164900[];

extern s32 rand(void);
extern void func_800A56E0(s32);
extern void func_801656F8(void *, s32, s32, s32, s32, s32, s32);
extern void func_8016583C(void *, s32, s32, s32, s32, s32, s32);
extern void func_80165D0C(void *, s32, s32, s32, s32, s32, s32);
extern void func_80165F00(void *);
extern void func_8016604C(void *);
extern void func_80166204(void *, s32, s32, s32, s32, s32, s32);

/* Updates a timed particle effect, advancing its phases and marking completion. */
void func_80169754(void *effectData)
{
    u8 *effectBytes = effectData;
    s32 particleIndex;
    s32 effectState;

    static void *const retainedStateTargets[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c34, &&jt_c34
    };
    (void)retainedStateTargets;

    effectState = *(s16 *)(effectBytes + 0x12);
    if ((u32)effectState >= 5) {
        goto done;
    }
    goto *D_80164900[(u32)effectState];

jt_c0:
        *(u16 *)(effectBytes + 0x12) += 1;
        *(s32 *)(effectBytes + 0x64) = (s32)0xFFE80000;

jt_c1:
    {
        u16 frameCounter;
        s32 nextFrameCounter;
        s32 withinPhaseDuration;

        for (particleIndex = 0; particleIndex < 3; particleIndex++) {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_801656F8(effectBytes - 0x20, 0, 0x2040F0, randomX, randomY,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effectBytes + 0x64));
        }

        for (particleIndex = 0; particleIndex < 5; particleIndex++) {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_8016583C(effectBytes - 0x20, 0, 0x2020F0, randomX, randomY,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effectBytes + 0x64));
        }

        for (particleIndex = 0; particleIndex < 4; particleIndex++) {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_80166204(effectBytes - 0x20, 0, 0x2020F0, randomX, randomY,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effectBytes + 0x64));
        }

        *(s32 *)(effectBytes + 0x64) += 0xA000;
        {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_80165D0C(effectBytes - 0x20, 0, 0x2020F0, randomX, randomY,
                         ~((~(rand() & 0xF)) & 0x3F),
                         *(s32 *)(effectBytes + 0x64));
        }

        if ((*(u16 *)(effectBytes + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        frameCounter = *(u16 *)(effectBytes + 0x18);
        nextFrameCounter = frameCounter + 1;
        withinPhaseDuration = (s16)frameCounter < 0x14;
        goto increment_common;

jt_c2:
        for (particleIndex = 0; particleIndex < 2; particleIndex++) {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_8016583C(effectBytes - 0x20, 0, 0x2020F0, randomX, randomY,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effectBytes + 0x64));
        }
        for (particleIndex = 0; particleIndex < 2; particleIndex++) {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_80166204(effectBytes - 0x20, 0, 0x2020F0, randomX, randomY,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effectBytes + 0x64));
        }
        *(s32 *)(effectBytes + 0x64) += 0x2000;
        if ((u16)(*(u16 *)(effectBytes + 0x18) - 0xF) < 0xB) {
            func_8016604C(effectBytes - 0x20);
        }
        if (*(s16 *)(effectBytes + 0x18) == 0xF ||
            *(s16 *)(effectBytes + 0x18) == 0x14 ||
            *(s16 *)(effectBytes + 0x18) == 0x19) {
            func_80165F00(effectBytes - 0x20);
        }
        if (*(s16 *)(effectBytes + 0x18) < 0x1F &&
            (*(u16 *)(effectBytes + 0x18) & 1) == 0) {
            s32 randomX;
            s32 randomY;
            randomX = (s16)((rand() & 0xF) - 8);
            randomY = (s16)((rand() & 0xF) - 8);
            func_80165D0C(effectBytes - 0x20, 0, 0x2020F0, randomX, randomY,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(effectBytes + 0x64));
        }
        if ((*(u16 *)(effectBytes + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        frameCounter = *(u16 *)(effectBytes + 0x18);
        nextFrameCounter = frameCounter + 1;
        withinPhaseDuration = (s16)frameCounter < 0x28;

increment_common:
        *(u16 *)(effectBytes + 0x18) = nextFrameCounter;
        if (withinPhaseDuration) {
            goto done;
        }
        *(u16 *)(effectBytes + 0x18) = 0;
        *(u16 *)(effectBytes + 0x12) += 1;
        goto done;
    }

jt_c34:
    {
        u16 frameCounter;
        s32 nextFrameCounter;
        s32 withinPhaseDuration;

        frameCounter = *(u16 *)(effectBytes + 0x18);
        nextFrameCounter = frameCounter + 1;
        withinPhaseDuration = (s16)frameCounter < 0xA;
        goto increment_short;

increment_short:
        *(u16 *)(effectBytes + 0x18) = nextFrameCounter;
        if (!withinPhaseDuration) {
            *(u16 *)(effectBytes - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

done:
        return;
}
