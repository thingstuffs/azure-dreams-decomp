#include "common.h"

extern void func_800478B8(void *arg0);
extern s16 D_80025924[5];
extern s32 D_800814A0[3];

void func_818CEC78(void *arg0, void *arg1, void *arg2)
{
    s32 third;
    s32 delta;
    u16 value;

    *(s32 *)((u8 *)arg1 + 0) += *(s32 *)((u8 *)arg0 + 0x4C);
    *(s32 *)((u8 *)arg1 + 4) += *(s32 *)((u8 *)arg0 + 0x50);
    third = *(s32 *)((u8 *)arg1 + 8);
    delta = *(s32 *)((u8 *)arg0 + 0x54);
    D_80025924[0] = 1;
    *(s32 *)((u8 *)arg1 + 8) = third + delta;
    func_800478B8(arg2);

    *(u16 *)((u8 *)arg2 + 0x1C) += 0x80;
    *(u16 *)((u8 *)arg2 + 0x1E) += 0x80;

    value = *(u16 *)((u8 *)arg0 + 2) - 1;
    *(u16 *)((u8 *)arg0 + 2) = value;
    if ((s16)value <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x8000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: arg0/arg2 become the retail cross-call s0/s1 held bases in a
   0x20-byte frame; exact-width u16 updates preserve both flag-setting blocks.
   Split third-accumulator preloads span the independent global halfword store,
   reproducing retail's v1/a0 live ranges and interleaved pre-call emission. */
