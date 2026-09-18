#include "common.h"

typedef struct {
    u8 pad[0xC4];
    u16 x;
    u16 y;
} Data83160;

extern Data83160 D_80083160;
extern void func_800BC4D4();

/* Sets the scratchpad offset to the negated global coordinates before forwarding the call. */
void func_80026F1C(s32 call_value, s32 call_option, s16 call_mode, s32 call_extra)
{
    s16 *scratch = (s16 *)0x1F800000;
    u16 x;
    u32 state;

    scratch[0x104 / 2] = 0;
    state = (u32)&D_80083160;
    x = *(u16 *)(state + 0xC4);
    state = *(u16 *)(state + 0xC6);
    scratch[0x100 / 2] = -x;
    scratch[0x102 / 2] = -state;
    func_800BC4D4(call_value, call_option, call_mode, call_extra);
}

