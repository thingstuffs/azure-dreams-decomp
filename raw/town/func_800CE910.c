#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C2E84(void *, s32, void *);
extern s32 D_800D6ABC;
extern s32 D_800D6AD0;

void func_800CC070(void *arg0, void *arg1, s32 arg2, s16 arg3)
{
    s16 state;

    state = FIELD(arg0, s16, 0x6A);
    switch (state) {
    case 0:
        func_800C2E84(arg0, arg2, &D_800D6ABC);
        FIELD(arg1, s16, 0x16) = arg3;
        FIELD(arg0, u16, 0x6A)++;
        break;

    case 1:
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        func_80095388(arg1);
        if (FIELD(arg1, s32, 0x14) >= 0) {
            func_800C2E84(arg0, arg2, &D_800D6AD0);
            FIELD(arg0, u16, 0x6A)++;
        }
        break;

    case 2:
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        if (func_800C2AE8(arg1) < FIELD(arg1, s16, 0xA)) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s16, 0xA) = func_800C2AE8(arg1);
            FIELD(arg0, s16, 0x6A) = 0;
            FIELD(arg0, u16, 0x68)++;
        } else {
            func_80095388(arg1);
        }
        break;
    }
}

/* MECHANISM: The true-space definition turns all in-range jumps into switch joins and one epilogue.
   Four live arguments force the 0x28 frame and s1/s0/s3/s2 hold set; field widths follow lh/lhu/sh. */
