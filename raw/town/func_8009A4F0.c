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

void func_80097C50(void *arg0, s32 arg1)
{
    UnkStackData sp10;
    u16 temp_v0;

    sp10 = D_80088D60;
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x6C) - 1;
    *(u16 *)((u8 *)arg0 + 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        *(u16 *)((u8 *)arg0 + 0x6C) = (u16)(func_800374F4(0xA) + 5);
        func_80097AD0(arg1, &sp10, (func_800374F4(2) & 0xFFFF) + 1);
    }
}

/* MECHANISM: A 24-byte struct local keeps the six-word global copy observable and forces the 0x38 frame.
   Its address remains live in s1 across calls, while arg0 and arg1 naturally occupy s0 and s2.
   Typed one-argument RNG calls preserve the retail call setup and scheduling. */
