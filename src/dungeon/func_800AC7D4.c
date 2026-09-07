#include "common.h"

typedef struct S_800B1F34_0 {
    s16 * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u16 unk_06;
} S_800B1F34_0;   /* arg0 in func_800B1F34 */

typedef struct S_800B1F34_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B1F34_1;   /* arg1 in func_800B1F34 */

typedef struct S_800B1F34_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B1F34_2;   /* global in func_800B1F34 */



extern void *D_800814A8;

void func_800B1F34(S_800B1F34_0 *arg0, S_800B1F34_1 *arg1)
{
    s16 state;
    u16 countdown;
    S_800B1F34_2 *global;

    state = arg0->unk_04.s;
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
    arg0->unk_06 = 0x10;
    arg0->unk_04.u++;

state_1:
    arg1->unk_14 -= 0x4000;
    countdown = arg0->unk_06 - 1;
    arg0->unk_06 = countdown;
    if ((s16)countdown >= 0) {
        goto common;
    }
    arg0->unk_06 = 0x40;
    arg0->unk_04.u++;
    goto common;

state_2:
    arg1->unk_14 += 0x6000;
    countdown = arg0->unk_06 - 1;
    arg0->unk_06 = countdown;
    if ((s16)countdown < 0) {
        arg0->unk_06 = 0x3C;
        arg0->unk_04.u++;
    }

state_3:
    countdown = arg0->unk_06 - 1;
    arg0->unk_06 = countdown;
    if ((s16)countdown < 0) {
        arg1->unk_14 = 0;
        arg0->unk_06 = 0x3C;
        arg0->unk_04.u++;
    }

common:
    global = D_800814A8;
    arg1->unk_08.at00.v -= arg1->unk_14;
    global->unk_1C |= 0x40000000;
    *arg0->unk_00 = 0x20 - arg1->unk_08.at02.v;
}

/* MECHANISM: The retail row is frameless: its apparent 0x800B2028/0x800B2038
   callees are true-space local joins. Signed countdown casts select sll/bgez,
   and one shared global tail keeps the D_800814A8 page live across all joins. */
