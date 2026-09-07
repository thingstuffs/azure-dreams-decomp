#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;

void func_80170920(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s32 quotient;
    u8 color;

    state = FIELD(arg0, s16, 0x1C);
    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto check_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto shared;

check_2:
    if (state == 2) {
        goto state_2;
    }
    goto shared;

state_0:
    FIELD(arg2, u16, 0x1C) += 0x258;
    FIELD(arg2, u16, 0x1E) += 0x258;
    color = FIELD(arg2, u8, 0xE) + 0xC;
    FIELD(arg2, u8, 0xE) = color;
    FIELD(arg2, u8, 0xD) = color;
    FIELD(arg2, u8, 0xC) = color;
    if (FIELD(arg2, u16, 0x1C) < 0x1770) {
        goto shared;
    }
    goto increment;

state_1:
    FIELD(arg2, s16, 0x10) = 0x20;
    FIELD(arg2, u8, 0xE) = 0x50;
    FIELD(arg2, u8, 0xD) = 0x50;
    FIELD(arg2, u8, 0xC) = 0x50;

increment:
    FIELD(arg0, u16, 0x1C)++;
    goto shared;

state_2:
    FIELD(arg2, s16, 0x10) = 0x60;
    FIELD(arg0, u16, 0x24)--;
    FIELD(arg2, u16, 0x1C) -= 0x190;
    FIELD(arg2, u16, 0x1E) -= 0x190;
    quotient = (FIELD(arg0, s16, 0x24) << 7) /
               FIELD(arg0, s16, 0x26);
    FIELD(arg2, u8, 0xE) = quotient;
    FIELD(arg2, u8, 0xD) = quotient;
    FIELD(arg2, u8, 0xC) = quotient;

shared:
    FIELD(arg2, u16, 0x1A) += 0x190;
    if (FIELD(arg0, s16, 0x24) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Rowbase recovery makes both apparent func_8017xxxx targets local CFG joins,
   leaving a frameless leaf with arg2 resident in $a2. Explicit labels preserve the
   retail block order; direct scalar RMW preserves the D_800814A0 tail shape. */
