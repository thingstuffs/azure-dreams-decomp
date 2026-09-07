#include "common.h"

extern void func_800478B8(void *);
extern s16 D_800261B0[8];
extern u8 D_800814A0[];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_800246F0(void *arg0, void *arg1, void *arg2)
{
    s32 value;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 count;

    count = FIELD(arg0, u16, 0x3A);
    D_800261B0[0] = 1;
    FIELD(arg0, u16, 0x3A) = count - 1;
    func_800478B8(arg2);
    value = ((s16)FIELD(arg0, u16, 0x3A) << 7) /
            FIELD(arg0, s16, 0x3C);
    FIELD(arg2, s8, 0xE) = value;
    FIELD(arg2, s8, 0xD) = value;
    FIELD(arg2, s8, 0xC) = value;
    x = FIELD(arg1, s32, 0);
    dx = FIELD(arg1, s32, 0xC);
    y = FIELD(arg1, s32, 4);
    dy = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 0) = x + dx;
    FIELD(arg1, s32, 4) = y + dy;
    if (FIELD(arg0, s16, 0x3A) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        FIELD(D_800814A0, s32, 0) |= 0x8000;
    }
}
