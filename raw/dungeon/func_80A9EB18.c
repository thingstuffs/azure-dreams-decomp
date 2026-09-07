#include "common.h"

extern void func_801741D0(void *, s32, s32, s8, s32);
extern s32 D_800814A0;

void func_80174318(void *arg0, s32 arg1, s32 arg2)
{
    s32 value = *(s16 *)((u8 *)arg0 + 0x1A);

    if (value >= 16) {
        func_801741D0(arg0, arg1, arg2, 0x70, 16);
    } else {
        func_801741D0(arg0, arg1, arg2, 0x70,
                      ((15 - value) * 6 + 16) & 0xFF);
    }

    {
        s32 new_value;

        new_value = (u16)*(s16 *)((u8 *)arg0 + 0x1A) - 1;
        *(volatile s16 *)((u8 *)arg0 + 0x1A) = new_value;
        if ((new_value << 16) <= 0) {
            *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}

/* MECHANISM: Duplicated semantic call arms preserve retail's constant-first CFG;
   CDK tail-merges them and anchors the fifth-arg stack store before the a0 move.
   Scalar D_800814A0 under -G0 supplies the held page base in the branch slot. */
