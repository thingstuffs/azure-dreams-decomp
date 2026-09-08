#include "common.h"

typedef struct S_800BC290_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
} S_800BC290_0;   /* arg0 in func_800BC290 */

typedef struct S_800BC290_1 {
    u8 pad_00[0xC];
    union { s32 s32; u8 u8; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    s16 unk_14;
} S_800BC290_1;   /* arg2 in func_800BC290 */



extern void func_8004E994(void *);
extern u8 D_80111FB0[8];
extern u32 D_800814A0;

void func_800BC290(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    s32 counter;
    u16 next_state;

    state = ((S_800BC290_0 *)arg0)->unk_00.s;
    counter = ((S_800BC290_0 *)arg0)->unk_02.u - 1;
    ((S_800BC290_0 *)arg0)->unk_02.u = counter;

    switch (state) {
    case 0:
        if ((counter << 16) <= 0) {
            ((S_800BC290_1 *)arg2)->unk_14 = 12;
            ((S_800BC290_1 *)arg2)->unk_0C.s32 = 0xC0C0C0;
            next_state = ((S_800BC290_0 *)arg0)->unk_00.u;
            ((S_800BC290_0 *)arg0)->unk_02.u = 12;
            goto increment_state;
        }
        break;

    case 1: {
        s32 color;
        register s32 adjustment ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        if (((S_800BC290_1 *)arg2)->unk_0C.u8 < 0x10U) {
            goto color_done;
        }
        color = ((S_800BC290_1 *)arg2)->unk_0C.s32;
        adjustment = 0xFFEFEFF0;
        color = color + adjustment;
        ((S_800BC290_1 *)arg2)->unk_0C.s32 = color;
color_done:
        if (((S_800BC290_0 *)arg0)->unk_02.s <= 0) {
            func_8004E994(D_80111FB0);
            next_state = ((S_800BC290_0 *)arg0)->unk_00.u;
increment_state:
            ((S_800BC290_0 *)arg0)->unk_00.u = next_state + 1;
        }
        break;
    }

    case 2:
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}

/* MECHANISM: The true-space three-argument ABI holds arg0 in s0 and keeps arg2 in a2;
   in-range jump targets are CFG joins, with predecessor-local next_state loads.
   Guarded v0/v1 pins give the color load and 0xFFEFEFF0 adjustment retail's roles. */
