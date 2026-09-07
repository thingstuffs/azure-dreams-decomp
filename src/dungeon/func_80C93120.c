#include "common.h"

typedef struct S_80170920_0 {
    u8 pad_00[0x1C];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x6];
    union { u16 s; s16 u; } unk_24;   /* accessed as both */
    s16 unk_26;
} S_80170920_0;   /* arg0 in func_80170920 */

typedef struct S_80170920_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x8];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80170920_1;   /* arg2 in func_80170920 */



extern s32 D_800814A0;

void func_80170920(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s32 quotient;
    u8 color;

    state = ((S_80170920_0 *)arg0)->unk_1C.s;
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
    ((S_80170920_1 *)arg2)->unk_1C += 0x258;
    ((S_80170920_1 *)arg2)->unk_1E += 0x258;
    color = ((S_80170920_1 *)arg2)->unk_0E + 0xC;
    ((S_80170920_1 *)arg2)->unk_0E = color;
    ((S_80170920_1 *)arg2)->unk_0D = color;
    ((S_80170920_1 *)arg2)->unk_0C = color;
    if (((S_80170920_1 *)arg2)->unk_1C < 0x1770) {
        goto shared;
    }
    goto increment;

state_1:
    ((S_80170920_1 *)arg2)->unk_10 = 0x20;
    ((S_80170920_1 *)arg2)->unk_0E = 0x50;
    ((S_80170920_1 *)arg2)->unk_0D = 0x50;
    ((S_80170920_1 *)arg2)->unk_0C = 0x50;

increment:
    ((S_80170920_0 *)arg0)->unk_1C.u++;
    goto shared;

state_2:
    ((S_80170920_1 *)arg2)->unk_10 = 0x60;
    ((S_80170920_0 *)arg0)->unk_24.s--;
    ((S_80170920_1 *)arg2)->unk_1C -= 0x190;
    ((S_80170920_1 *)arg2)->unk_1E -= 0x190;
    quotient = (((S_80170920_0 *)arg0)->unk_24.u << 7) /
               ((S_80170920_0 *)arg0)->unk_26;
    ((S_80170920_1 *)arg2)->unk_0E = quotient;
    ((S_80170920_1 *)arg2)->unk_0D = quotient;
    ((S_80170920_1 *)arg2)->unk_0C = quotient;

shared:
    ((S_80170920_1 *)arg2)->unk_1A += 0x190;
    if (((S_80170920_0 *)arg0)->unk_24.u <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Rowbase recovery makes both apparent func_8017xxxx targets local CFG joins,
   leaving a frameless leaf with arg2 resident in $a2. Explicit labels preserve the
   retail block order; direct scalar RMW preserves the D_800814A0 tail shape. */
