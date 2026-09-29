#include "common.h"
#include "shared/object_flags.h"

typedef struct S_8016F99C_0_pre {
    u16 unk_00;
} S_8016F99C_0_pre;   /* the 0x2 bytes before arg0 in func_8016F99C, addressed as arg0[-1] */

typedef struct S_8016F99C_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
} S_8016F99C_0;   /* arg0 in func_8016F99C */

typedef struct S_8016F99C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016F99C_1;   /* arg1 in func_8016F99C */


extern void *D_801649E8[];
extern void *D_80175D58[];
extern void *D_80175D5C[];

/* Advances a timed transition, updates its target, and marks completion. */
void func_8016F99C(void *transition, S_8016F99C_1 *target)
{
    s32 state;
    u16 timer;
    u32 next_state;
    u32 next_timer;

    state = ((S_8016F99C_0 *)transition)->unk_12.s;
    switch (state) {
    case 0:
    default:
        return;

    case 1:
        target->unk_0A = 1;
        return;

    case 2:
        next_state = ((S_8016F99C_0 *)transition)->unk_12.u;
        next_timer = 0x11;
        ((S_8016F99C_0 *)transition)->unk_18 = next_timer;
        ((S_8016F99C_0 *)transition)->unk_12.u = next_state + 1;
        return;

    case 3:
        target->unk_06 = target->unk_06 - 8;
        timer = ((S_8016F99C_0 *)transition)->unk_18 - 1;
        ((S_8016F99C_0 *)transition)->unk_18 = timer;
        if ((timer << 16) > 0) {
            return;
        }
        ((S_8016F99C_0 *)transition)->unk_18 = 0x11;
        ((S_8016F99C_0 *)transition)->unk_12.u = ((S_8016F99C_0 *)transition)->unk_12.u + 1;
        target->unk_0A = 3;
        return;

    case 4:
        target->unk_06 = target->unk_06 + 8;
        timer = ((S_8016F99C_0 *)transition)->unk_18 - 1;
        ((S_8016F99C_0 *)transition)->unk_18 = timer;
        if ((timer << 16) > 0) {
            return;
        }
        if (((S_8016F99C_0 *)transition)->unk_1C == 0) {
            *(void **)D_80175D58 = 0;
        } else {
            *(void **)D_80175D5C = 0;
        }
        goto finish;

    case 10:
        next_state = ((S_8016F99C_0 *)transition)->unk_12.u;
        next_timer = 0x14;
        ((S_8016F99C_0 *)transition)->unk_18 = next_timer;
        ((S_8016F99C_0 *)transition)->unk_12.u = next_state + 1;
        return;

    case 11:
        target->unk_06 = target->unk_06 - 8;
        timer = ((S_8016F99C_0 *)transition)->unk_18 - 1;
        ((S_8016F99C_0 *)transition)->unk_18 = timer;
        if ((timer << 16) > 0) {
            return;
        }
        if (((S_8016F99C_0 *)transition)->unk_1C == 0) {
            *(void **)D_80175D58 = 0;
        } else {
            *(void **)D_80175D5C = 0;
        }
finish:
        ((S_8016F99C_0_pre *)transition)[-1].unk_00 |= 0x8000;
        next_timer = 0x80080000;
        *(s32 *)(next_timer + 0x14A0) |= 0x8000;
        return;
    }
}

/* MECHANISM: Frameless leaf recovers every apparent 0x8016FAxx call as a local CFG join.
   A direct 0..11 switch and shared advance/clear/finish labels restore retail layout.
   Guarded $v0/$v1 lifetimes serve both advance values and late page bases; placing the
   page births after flag branches produces the exact delay-slot luis and stores. */
