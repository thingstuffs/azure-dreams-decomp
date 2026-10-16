/* Relink of matched town/func_800D0638; every changed retail word is a paired relocation. */
#define D_800CD650 D_800CD9F4
#include "common.h"

typedef s32 M2C_UNK;

extern s32 scaleRandomToUnsignedHalfwordLimit();
extern void townInitializeObjectEntries();
extern M2C_UNK D_800CD9F4;
extern M2C_UNK D_800D7284;

// Initializes an object with shared data and a generated value scaled in units of 21.
void func_800CDE9C(void *object, M2C_UNK unusedArg, M2C_UNK initValue) {
    townInitializeObjectEntries(object, initValue, &D_800D7284);
    *(M2C_UNK **)((u8 *)object + 0x50) = &D_800CD9F4;
    *(s16 *)((u8 *)object + 0x6C) = (s16)(((scaleRandomToUnsignedHalfwordLimit(4) & 0xFFFF) * 0x15) + 0x15);
}
