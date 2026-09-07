#include "common.h"

#define F8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 D_800814A0;
extern void func_80173CFC(void *, s32 *, s32, s32);

void func_80174374(u8 *p, s32 *arg1, s32 arg2)
{
    s16 state;
    s16 count;
    s16 limit;
    s16 red;
    s16 held_limit;
    s16 i;
    s32 delta;
    s32 magic;
    u16 next;
    u8 green;
    u8 blue;

    state = F16(p, 0x1C);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto finish;
    }
    if (state == 2) {
        goto state_two;
    }
    goto finish;

state_zero:
    next = FU16(p, 0x26) + 1;
    FU16(p, 0x26) = next;
    if ((s16)next >= F16(p, 0x2C)) {
        magic = 0x2AAA0000;
        if ((s16)next - F16(p, 0x2C) < 7) {
            magic = 0x2AAAAAAB;
            red = (F8(p, 0) * ((s16)next - F16(p, 0x2C))) / 6;
            F8(p, 0x10) = red;
            F8(p, 0x0C) = red;
            F8(p, 0x08) = red;
            F8(p, 0x04) = red;
            green = (F8(p, 1) * (F16(p, 0x26) - F16(p, 0x2C))) / 6;
            F8(p, 0x11) = green;
            F8(p, 0x0D) = green;
            F8(p, 0x09) = green;
            F8(p, 0x05) = green;
            blue = (F8(p, 2) * (F16(p, 0x26) - F16(p, 0x2C))) / 6;
            F8(p, 0x12) = blue;
            F8(p, 0x0E) = blue;
            F8(p, 0x0A) = blue;
            F8(p, 0x06) = blue;
        }
    }
    if (F16(p, 0x26) >= 0x22) {
        FU16(p, 0x1C) = FU16(p, 0x1C) + 1;
    }
    goto finish;

state_one:
    if (F16(p, 0x2A) < 4) {
        next = FU16(p, 0x26) + 1;
        FU16(p, 0x26) = next;
        if ((s16)next + F16(p, 0x2A) == 0x2D) {
            F8(p, 0x12) = 0x80;
            F8(p, 0x0E) = 0x80;
            F8(p, 0x0A) = 0x80;
            F8(p, 0x06) = 0x80;
            F8(p, 0x11) = 0x80;
            F8(p, 0x0D) = 0x80;
            F8(p, 0x09) = 0x80;
            F8(p, 0x05) = 0x80;
            F8(p, 0x10) = 0x80;
            F8(p, 0x0C) = 0x80;
            F8(p, 0x08) = 0x80;
            F8(p, 0x04) = 0x80;
        } else {
            u8 r = F8(p, 0);
            u8 g = F8(p, 1);
            u8 b = F8(p, 2);
            F8(p, 0x10) = r;
            F8(p, 0x0C) = r;
            F8(p, 0x08) = r;
            F8(p, 0x04) = r;
            F8(p, 0x11) = g;
            F8(p, 0x0D) = g;
            F8(p, 0x09) = g;
            F8(p, 0x05) = g;
            F8(p, 0x12) = b;
            F8(p, 0x0E) = b;
            F8(p, 0x0A) = b;
            F8(p, 0x06) = b;
        }
    }

state_one_common:
    if (F16(p, 0x24) < 0x0C) {
        FU16(p, 0x1C) = FU16(p, 0x1C) + 1;
        F32(p, 0x94) = (F16(p, 0x44) + F16(p, 0x56)) << 15;
        F32(p, 0x98) = (F16(p, 0x46) + F16(p, 0x58)) << 15;
        F32(p, 0x9C) = (F16(p, 0x48) + F16(p, 0x5A) + 0x40) << 15;
        if (F16(p, 0x2A) == 0) {
            i = 1;
            do {
                func_80173CFC(p, arg1, arg2, (i << 26) >> 16);
                i++;
            } while (i < 8);
        }
    }
    goto finish;

state_two:
    blue = (F8(p, 0) * F16(p, 0x24)) / 10;
    F8(p, 0x12) = blue;
    F8(p, 0x0E) = blue;
    F8(p, 0x0A) = blue;
    F8(p, 0x06) = blue;
    F8(p, 0x11) = blue;
    F8(p, 0x0D) = blue;
    F8(p, 0x09) = blue;
    F8(p, 0x05) = blue;
    F8(p, 0x10) = blue;
    F8(p, 0x0C) = blue;
    F8(p, 0x08) = blue;
    F8(p, 0x04) = blue;
    arg1[0] += F32(p, 0x94);
    arg1[1] += F32(p, 0x98);
    arg1[2] += F32(p, 0x9C);

finish:
    count = FU16(p, 0x24) - 1;
    F16(p, 0x24) = count;
    if ((count << 16) <= 0) {
        FU16(p, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: The true-space u8 * parameter yields retail's 0x28 frame and
   s0/s2/s3/s1 save order; direct signed 0x2C reads preserve the reload and
   branch-delay division shape, with 2.7.2-cdk-G0 closing temp coloring. */
