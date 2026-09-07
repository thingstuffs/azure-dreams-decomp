#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800478B8(void *);
extern s32 D_800814A0;
extern s32 D_80083460;

void func_800C5A64(void *arg0, s32 *arg1, void *arg2)
{
    s16 remaining;
    u8 *counter_base;

    arg1[0] += arg1[3];
    arg1[1] += arg1[4];
    arg1[2] += arg1[5];
    arg1[3] -= arg1[3] >> 3;
    arg1[4] -= arg1[4] >> 3;

    func_800478B8(arg2);

    FIELD(arg2, u8, 0xC) -= FIELD(arg2, u8, 0xC) / FIELD(arg0, s16, 0x10);
    FIELD(arg2, u8, 0xD) -= FIELD(arg2, u8, 0xD) / FIELD(arg0, s16, 0x10);
    FIELD(arg2, u8, 0xE) -= FIELD(arg2, u8, 0xE) / FIELD(arg0, s16, 0x10);

    remaining = FIELD(arg0, u16, 0x10) - 1;
    FIELD(arg0, s16, 0x10) = remaining;
    if ((remaining << 16) <= 0) {
        if ((FIELD(arg0, s16, 0xC) == 0) &&
            (FIELD(arg0, s16, 0x1C) == 0)) {
            counter_base = (u8 *)&D_80083460;
            FIELD(counter_base, u16, 0xA)--;
        }
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The two call-crossing arguments naturally occupy s1/s0, producing
   the retail 0x20 frame and save order; the one-argument callee contract leaves
   the final arg1[4] store available for the jal delay slot. */
