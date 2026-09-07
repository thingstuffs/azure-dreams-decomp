#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} UnkStackData;

extern s32 func_800374F4(s32);
extern void func_80097AD0(s32, UnkStackData *, s32);
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
        *(u16 *)((u8 *)object + 0x6C) = (u16)(func_800374F4(0xA) + 5);
        func_80097AD0(target, &update_data, (func_800374F4(2) & 0xFFFF) + 1);
    }
}
