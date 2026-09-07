#include "common.h"

#define FIELD(p, t, n) (*(t *)((u8 *)(p) + (n)))

extern struct S_80083178 D_80083178;
extern s32 D_800814A0;
extern s32 D_80083460;

void func_800C4C00(void *arg0)
{
    u8 *state;
    u16 *counter;
    u16 left;

    state = (u8 *)&D_80083178;
    if (FIELD(arg0, s16, 4) == 0) {
        FIELD(state, u8, 0x90) +=
            (FIELD(arg0, u8, 0) - FIELD(state, u8, 0x90)) /
            FIELD(arg0, s16, 6);
        FIELD(state, u8, 0x91) +=
            (FIELD(arg0, u8, 1) - FIELD(state, u8, 0x91)) /
            FIELD(arg0, s16, 6);
        FIELD(state, u8, 0x92) +=
            (FIELD(arg0, u8, 2) - FIELD(state, u8, 0x92)) /
            FIELD(arg0, s16, 6);
        left = FIELD(arg0, u16, 6) - 1;
        FIELD(arg0, u16, 6) = left;
        if ((s16)left <= 0) {
            FIELD(arg0, s16, 6) = 0x10;
            FIELD(arg0, u16, 4)++;
        }
    } else {
        FIELD(state, u8, 0x90) +=
            (0x80 - FIELD(state, u8, 0x90)) /
            FIELD(arg0, s16, 6);
        FIELD(state, u8, 0x91) +=
            (0x80 - FIELD(state, u8, 0x91)) /
            FIELD(arg0, s16, 6);
        FIELD(state, u8, 0x92) +=
            (0x80 - FIELD(state, u8, 0x92)) /
            FIELD(arg0, s16, 6);
        left = FIELD(arg0, u16, 6) - 1;
        FIELD(arg0, u16, 6) = left;
        if ((s16)left <= 0) {
            FIELD(state, u8, 0x90) = 0x80;
            FIELD(state, u8, 0x91) = 0x80;
            FIELD(state, u8, 0x92) = 0x80;
            counter = (u16 *)&D_80083460;
            counter[5]--;
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}

/* MECHANISM: Retail is a frameless leaf; the input and one D_80083178 base stay live
   across both CFG arms. The +0x90 color bytes use one held struct base, while the
   counter uses symbolic base indexing to preserve its separate lui/addiu pair; the
   final two flags remain direct halfword/word read-modify-writes. */
