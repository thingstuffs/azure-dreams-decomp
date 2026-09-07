#include "common.h"

typedef struct {
    u8 pad[0xC4];
    u16 x;
    u16 y;
} Data83160;

extern Data83160 D_80083160;
extern void func_800BC4D4();

void func_80026F1C(s32 arg0, s32 arg1, s16 arg2)
{
    register s16 *scratch ASM_REG("$8") = (s16 *)0x1F800000;   /* MATCH pin: load-bearing for the whole function shape */
    u16 x;
    u32 state;

    ASM_KEEP_NV(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch[0x104 / 2] = 0;
    state = (u32)&D_80083160;
    x = *(u16 *)(state + 0xC4);
    state = *(u16 *)(state + 0xC6);
    scratch[0x100 / 2] = -x;
    scratch[0x102 / 2] = -state;
    func_800BC4D4(arg0, arg1, arg2);
}

/* MECHANISM: The three-argument call naturally gives a 0x18 frame with only the ra save.
   Splitting x while overwriting the held state base with y makes the final lhu reuse v0.
   A first-use nonvolatile keep pins the runtime scratch pointer in t0 and restores prelude order. */
