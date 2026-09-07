#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_800814A8;

void func_800B1F34(void *arg0, void *arg1)
{
    s16 state;
    u16 countdown;
    void *global;

    state = FIELD(arg0, s16, 4);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto common;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto common;

state_0:
    FIELD(arg0, u16, 6) = 0x10;
    FIELD(arg0, u16, 4)++;

state_1:
    FIELD(arg1, s32, 0x14) -= 0x4000;
    countdown = FIELD(arg0, u16, 6) - 1;
    FIELD(arg0, u16, 6) = countdown;
    if ((s16)countdown >= 0) {
        goto common;
    }
    FIELD(arg0, u16, 6) = 0x40;
    FIELD(arg0, u16, 4)++;
    goto common;

state_2:
    FIELD(arg1, s32, 0x14) += 0x6000;
    countdown = FIELD(arg0, u16, 6) - 1;
    FIELD(arg0, u16, 6) = countdown;
    if ((s16)countdown < 0) {
        FIELD(arg0, u16, 6) = 0x3C;
        FIELD(arg0, u16, 4)++;
    }

state_3:
    countdown = FIELD(arg0, u16, 6) - 1;
    FIELD(arg0, u16, 6) = countdown;
    if ((s16)countdown < 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg0, u16, 6) = 0x3C;
        FIELD(arg0, u16, 4)++;
    }

common:
    global = D_800814A8;
    FIELD(arg1, s32, 8) -= FIELD(arg1, s32, 0x14);
    FIELD(global, s32, 0x1C) |= 0x40000000;
    *FIELD(arg0, s16 *, 0) = 0x20 - FIELD(arg1, u16, 0xA);
}

/* MECHANISM: The retail row is frameless: its apparent 0x800B2028/0x800B2038
   callees are true-space local joins. Signed countdown casts select sll/bgez,
   and one shared global tail keeps the D_800814A8 page live across all joins. */
