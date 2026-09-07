#include "common.h"

typedef struct {
    u8 pad00[0x3A];
    u16 count;
    s16 divisor;
} Work;

typedef struct {
    u8 pad00[0x0C];
    s8 c0;
    s8 c1;
    s8 c2;
    u8 pad0F[0x0B];
    u16 angle;
} Obj;

extern s16 D_800261B0[];
extern s32 D_800814A0[];

void func_819A13D0(Work *arg0, s32 arg1, Obj *arg2) {
    s32 quotient;
    u16 count;
    u16 angle;

    count = arg0->count - 1;
    quotient = (s32)((s32)(count << 16) >> 9) / arg0->divisor;
    arg0->count = count;
    angle = arg2->angle;
    D_800261B0[0] = 1;
    arg2->angle = angle + 0x190;
    arg2->c2 = quotient;
    arg2->c1 = quotient;
    arg2->c0 = quotient;
    if ((s16)arg0->count > 0) {
        return;
    }
    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
