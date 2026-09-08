#include "common.h"

typedef struct {
    u8 pad[0xC4];
    u16 x;
    u16 y;
} Data83160;

extern Data83160 D_80083160;
extern void func_800BC4D4();

/* Sets the scratchpad offset to the negated global coordinates before forwarding the call. */
void func_80026F1C(s32 call_value, s32 call_option, s16 call_mode)
{
    register s16 *scratch ASM_REG("$8") = (s16 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 x;
    u32 state;

    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch[0x104 / 2] = 0;
    state = (u32)&D_80083160;
    x = *(u16 *)(state + 0xC4);
    state = *(u16 *)(state + 0xC6);
    scratch[0x100 / 2] = -x;
    scratch[0x102 / 2] = -state;
    func_800BC4D4(call_value, call_option, call_mode);
}

/* MECHANISM: The three-argument call naturally gives a 0x18 frame with only the ra save.
   Splitting x while overwriting the held state base with y makes the final lhu reuse v0.
   A first-use nonvolatile keep pins the runtime scratch pointer in t0 and restores prelude order. */
