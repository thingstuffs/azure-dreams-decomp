#include "common.h"

extern s16 D_80025E80[5];
extern s32 D_800814A0[3];

/* Decrement the countdown, reset scale, and flag completion when it expires. */
void func_818FEEF8(void *state_data, s32 unused, void *scale_data)
{
    u8 *state = state_data;
    s32 remaining_ticks;
    u8 *scale = scale_data;

    
    *(u16 *)(state + 2) = *(u16 *)(state + 2) - 1;
    *(s16 *)(scale + 0x1C) = 0x1000;
    *(s16 *)(scale + 0x1E) = 0x1000;
    remaining_ticks = *(s16 *)(state + 2);
    D_80025E80[0] = 1;
    if (remaining_ticks <= 0) {
        *(u16 *)(state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

/* MECHANISM: Frameless leaf; pin the persistent arg0 pointer in $a1.
   Hold the signed halfword reload in a pinned s32 $a0 local: this selects
   retail's direct lh/bgtz and avoids the s16 pin's extra lhu/sll pair. */
