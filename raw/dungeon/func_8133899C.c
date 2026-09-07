#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0[3];
extern void *D_801649E8[];
extern void *D_80175D58[];
extern void *D_80175D5C[];

void func_8016F99C(void *arg0, void *arg1)
{
    s32 state;
    u16 timer;
    register u32 next_state ASM_REG("$2");
    register u32 next_timer ASM_REG("$3");

    state = FIELD(arg0, s16, 0x12);
    switch (state) {
    case 1:
        goto case_1;
    case 2:
        goto case_2;
    case 3:
        goto case_3;
    case 4:
        goto case_4;
    case 10:
        goto case_10;
    case 11:
        goto case_11;
    case 0:
    default:
        goto done;
    }

case_1:
    FIELD(arg1, u16, 0x0A) = 1;
    goto done;

case_2:
    next_state = FIELD(arg0, u16, 0x12);
    next_timer = 0x11;
    goto advance_state;

case_3:
    FIELD(arg1, u16, 0x06) = FIELD(arg1, u16, 0x06) - 8;
    timer = FIELD(arg0, u16, 0x18) - 1;
    FIELD(arg0, u16, 0x18) = timer;
    if ((timer << 16) > 0) {
        goto done;
    }
    FIELD(arg0, u16, 0x18) = 0x11;
    FIELD(arg0, u16, 0x12) = FIELD(arg0, u16, 0x12) + 1;
    FIELD(arg1, u16, 0x0A) = 3;
    goto done;

case_4:
    FIELD(arg1, u16, 0x06) = FIELD(arg1, u16, 0x06) + 8;
    timer = FIELD(arg0, u16, 0x18) - 1;
    FIELD(arg0, u16, 0x18) = timer;
    if ((timer << 16) > 0) {
        goto done;
    }
    if (FIELD(arg0, s16, 0x1C) == 0) {
        goto clear_58;
    }
    next_state = 0x80170000;
    ASM_KEEP(next_state);
    *(void **)(next_state + 0x5D5C) = 0;
    goto finish;

case_10:
    next_state = FIELD(arg0, u16, 0x12);
    next_timer = 0x14;
advance_state:
    ASM_KEEP(next_timer);
    FIELD(arg0, u16, 0x18) = next_timer;
    ASM_KEEP(next_state);
    FIELD(arg0, u16, 0x12) = next_state + 1;
    goto done;

case_11:
    FIELD(arg1, u16, 0x06) = FIELD(arg1, u16, 0x06) - 8;
    timer = FIELD(arg0, u16, 0x18) - 1;
    FIELD(arg0, u16, 0x18) = timer;
    if ((timer << 16) > 0) {
        goto done;
    }
    if (FIELD(arg0, s16, 0x1C) != 0) {
        goto clear_5C;
    }
clear_58:
    next_state = 0x80170000;
    ASM_KEEP(next_state);
    *(void **)(next_state + 0x5D58) = 0;
    goto finish;
clear_5C:
    next_state = 0x80170000;
    ASM_KEEP(next_state);
    *(void **)(next_state + 0x5D5C) = 0;
finish:
    FIELD(arg0, u16, -2) |= 0x8000;
    next_timer = 0x80080000;
    ASM_KEEP(next_timer);
    *(s32 *)(next_timer + 0x14A0) |= 0x8000;
done:
    return;
}

/* MECHANISM: Frameless leaf recovers every apparent 0x8016FAxx call as a local CFG join.
   A direct 0..11 switch and shared advance/clear/finish labels restore retail layout.
   Guarded $v0/$v1 lifetimes serve both advance values and late page bases; placing the
   page births after flag branches produces the exact delay-slot luis and stores. */
