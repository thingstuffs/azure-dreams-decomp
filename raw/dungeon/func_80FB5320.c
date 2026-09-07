#include "common.h"

extern void func_80174B54(void) __attribute__((noreturn));
extern s32 D_800814A0;

void func_80174B20(void *arg0, s32 arg1, void *arg2)
{
    s16 value;

    value = *(s16 *)((u8 *)arg0 + 0x96);
    if (value < 16) {
        s8 color = value * 3;

        *(s8 *)((u8 *)arg2 + 0xE) = color;
        *(s8 *)((u8 *)arg2 + 0xD) = color;
        *(s8 *)((u8 *)arg2 + 0xC) = color;
        func_80174B54();
        return;
    }

    ASM_SCHED_BARRIER();
    *(s32 *)((u8 *)arg2 + 0xC) = 0x808080;
    value = *(u16 *)((u8 *)arg0 + 0x96) - 1;
    *(s16 *)((u8 *)arg0 + 0x96) = value;
    if (value <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The seed's frameless leaf shape and narrow color live range are retained.
   ASM_SCHED_BARRIER at the else seam blocks the constant-page lui delay-slot steal,
   allowing the fall-through sll to fill the conditional branch slot exactly. */
