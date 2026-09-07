#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_8004E994(void *);
extern u8 D_80111FB0[8];
extern u32 D_800814A0;

void func_800BC290(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    s32 counter;
    u16 next_state;

    state = FIELD(arg0, s16, 0);
    counter = FIELD(arg0, u16, 2) - 1;
    FIELD(arg0, u16, 2) = counter;

    switch (state) {
    case 0:
        if ((counter << 16) <= 0) {
            FIELD(arg2, s16, 0x14) = 12;
            FIELD(arg2, s32, 0xC) = 0xC0C0C0;
            next_state = FIELD(arg0, u16, 0);
            FIELD(arg0, u16, 2) = 12;
            goto increment_state;
        }
        break;

    case 1: {
        register s32 color ASM_REG("$2");
        register s32 adjustment ASM_REG("$3");

        if (FIELD(arg2, u8, 0xC) < 0x10U) {
            goto color_done;
        }
        color = FIELD(arg2, s32, 0xC);
        adjustment = 0xFFEFEFF0;
        color = color + adjustment;
        ASM_KEEP(adjustment);
        ASM_KEEP(color);
        FIELD(arg2, s32, 0xC) = color;
color_done:
        if (FIELD(arg0, s16, 2) <= 0) {
            func_8004E994(D_80111FB0);
            next_state = FIELD(arg0, u16, 0);
increment_state:
            FIELD(arg0, u16, 0) = next_state + 1;
        }
        break;
    }

    case 2:
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}

/* MECHANISM: The true-space three-argument ABI holds arg0 in s0 and keeps arg2 in a2;
   in-range jump targets are CFG joins, with predecessor-local next_state loads.
   Guarded v0/v1 pins give the color load and 0xFFEFEFF0 adjustment retail's roles. */
