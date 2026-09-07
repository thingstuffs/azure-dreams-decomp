#include "common.h"

typedef struct S_800CC070_0 {
    u8 pad_00[0x68];
    u16 unk_68;
    union { s16 s; u16 u; } unk_6A;   /* accessed as both */
} S_800CC070_0;   /* arg0 in func_800CC070 */

typedef struct S_800CC070_1 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800CC070_1;   /* arg1 in func_800CC070 */



extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C2E84(void *, s32, void *);
extern s32 D_800D6ABC;
extern s32 D_800D6AD0;

void func_800CC070(S_800CC070_0 *arg0, S_800CC070_1 *arg1, s32 arg2, s16 arg3)
{
    s16 state;

    state = arg0->unk_6A.s;
    switch (state) {
    case 0:
        func_800C2E84(arg0, arg2, &D_800D6ABC);
        arg1->unk_14.at02.v = arg3;
        arg0->unk_6A.u++;
        break;

    case 1:
        arg1->unk_08.at00.v += arg1->unk_14.at00.v;
        func_80095388(arg1);
        if (arg1->unk_14.at00.v >= 0) {
            func_800C2E84(arg0, arg2, &D_800D6AD0);
            arg0->unk_6A.u++;
        }
        break;

    case 2:
        arg1->unk_08.at00.v += arg1->unk_14.at00.v;
        if (func_800C2AE8(arg1) < arg1->unk_08.at02.v) {
            arg1->unk_14.at00.v = 0;
            arg1->unk_08.at02.v = func_800C2AE8(arg1);
            arg0->unk_6A.s = 0;
            arg0->unk_68++;
        } else {
            func_80095388(arg1);
        }
        break;
    }
}

/* MECHANISM: The true-space definition turns all in-range jumps into switch joins and one epilogue.
   Four live arguments force the 0x28 frame and s1/s0/s3/s2 hold set; field widths follow lh/lhu/sh. */
