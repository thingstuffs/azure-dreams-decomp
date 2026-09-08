#include "common.h"

/* D_80083160: shared state table (own view here); only the s16 field at
 * +0xC8 is read via this view. */
struct S_800C56BC {
    char pad0[0xC8];
    s16 unkC8;
};

extern struct S_800C56BC D_80083160;

/* Quantizes the wrapped angle from the shared heading plus a quarter turn into sectors. */
s32 func_800C2E1C(s32 referenceAngle, s16 sectorCount)
{
    struct S_800C56BC *sharedState = &D_80083160;
    s16 effectiveSectorCount;
    s32 sectorAngle;
    s32 roundedAngle;

    effectiveSectorCount = sectorCount;
    if (sectorCount == 0) {
        effectiveSectorCount = 1;
    }
    sectorAngle = 0x1000 / effectiveSectorCount;
    roundedAngle = sharedState->unkC8 + (s16) sectorAngle / 2;
    roundedAngle += 0x400;
    roundedAngle -= referenceAngle;
    return (s32) (roundedAngle & 0xFFF) / (s16) sectorAngle;
}
