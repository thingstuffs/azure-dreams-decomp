#include "common.h"

typedef struct S_801712C4_0 {
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0xB];
    u8 unk_17;
    u8 pad_18[0x1A];
    union { u16 u; s16 s; } unk_32;   /* accessed as both */
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
} S_801712C4_0;   /* arg0 in func_801712C4 */

typedef struct S_801712C4_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801712C4_1;   /* arg1 in func_801712C4 */



extern void func_801710B8(void *, void *, s32);
extern s32 D_800814A0;

void func_801712C4(void *arg0, void *arg1, s32 arg2)
{
    s32 state;

    state = ((S_801712C4_0 *)arg0)->unk_17;
    ((S_801712C4_0 *)arg0)->unk_32.u = ((S_801712C4_0 *)arg0)->unk_32.u - 1;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_801710B8(arg0, arg1, arg2);
    func_801710B8(arg0, arg1, arg2);
    if (((S_801712C4_0 *)arg0)->unk_32.s == 0) {
        ((S_801712C4_0 *)arg0)->unk_32.u = 0x10;
        ((S_801712C4_0 *)arg0)->unk_34 = 0x10;
        ((S_801712C4_0 *)arg0)->unk_17++;
    }
    ((S_801712C4_0 *)arg0)->unk_08 = ((S_801712C4_0 *)arg0)->unk_00.at00.v;
    goto done;

state_one:
    ((S_801712C4_1 *)arg1)->unk_00 += ((S_801712C4_0 *)arg0)->unk_40;
    ((S_801712C4_1 *)arg1)->unk_04 += ((S_801712C4_0 *)arg0)->unk_44;
    ((S_801712C4_1 *)arg1)->unk_08 += ((S_801712C4_0 *)arg0)->unk_48;
    ((S_801712C4_1 *)arg1)->unk_00 += ((S_801712C4_0 *)arg0)->unk_40;
    ((S_801712C4_1 *)arg1)->unk_04 += ((S_801712C4_0 *)arg0)->unk_44;
    ((S_801712C4_1 *)arg1)->unk_08 += ((S_801712C4_0 *)arg0)->unk_48;

    ((S_801712C4_0 *)arg0)->unk_04.at00.v =
        (((S_801712C4_0 *)arg0)->unk_00.at00u.v * ((S_801712C4_0 *)arg0)->unk_32.s) /
        ((S_801712C4_0 *)arg0)->unk_34;
    ((S_801712C4_0 *)arg0)->unk_04.at01.v =
        (((S_801712C4_0 *)arg0)->unk_00.at01.v * ((S_801712C4_0 *)arg0)->unk_32.s) /
        ((S_801712C4_0 *)arg0)->unk_34;
    ((S_801712C4_0 *)arg0)->unk_04.at02.v =
        (((S_801712C4_0 *)arg0)->unk_00.at02.v * ((S_801712C4_0 *)arg0)->unk_32.s) /
        ((S_801712C4_0 *)arg0)->unk_34;
    ((S_801712C4_0 *)arg0)->unk_08 = ((S_801712C4_0 *)arg0)->unk_04.at00u.v;

    if (((S_801712C4_0 *)arg0)->unk_32.s <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: The true-space function uses two local epilogue edges, not calls.
   Three arguments stay live in s0/s1/s2 across the zero-state calls; direct
   scalar RMW preserves D_800814A0's retail hi/lo access shape. */
