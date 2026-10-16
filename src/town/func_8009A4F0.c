#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} UnkStackData;

extern s32 scaleRandomToUnsignedHalfwordLimit(s32);
extern void townSpawnRadialObjects(s32, UnkStackData *, s32);
extern UnkStackData D_80088D60;

/* Decrements an object's countdown and triggers a randomized update when it expires. */
void func_80097C50(void *object, s32 target)
{
    UnkStackData update_data;
    u16 ticks_left;

    update_data = D_80088D60;
    ticks_left = *(u16 *)((u8 *)object + 0x6C) - 1;
    *(u16 *)((u8 *)object + 0x6C) = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        *(u16 *)((u8 *)object + 0x6C) = (u16)(scaleRandomToUnsignedHalfwordLimit(0xA) + 5);
        townSpawnRadialObjects(target, &update_data, (scaleRandomToUnsignedHalfwordLimit(2) & 0xFFFF) + 1);
    }
}
