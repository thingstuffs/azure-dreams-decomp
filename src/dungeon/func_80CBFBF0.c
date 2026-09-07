#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801733F0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0xB];
    u8 unk_A7;
} S_801733F0_0;   /* arg0 in func_801733F0 */


typedef struct S_801733F0_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801733F0_2;   /* global in func_801733F0 */


typedef struct S_801733F0_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801733F0_4;   /* owner in func_801733F0 */



extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173720(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_80176300[];
extern u8 D_80176308[];
extern u8 D_80176360[];
extern u8 D_80176368[];

void func_801733F0(S_801733F0_0 *arg0, void *arg1, Rec_func_800AA258_arg2 *arg2, Rec_D_800E3D7C *arg3)
{
    u8 state;

    state = arg0->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *global;

        if ((arg2->unk_14 & 0xE000) == 0) {
            return;
        }

        global = (u8 *)&D_80083460;
        ((S_801733F0_2 *)global)->unk_0A--;
        if (arg0->unk_A7 != 0) {
            arg2->unk_2C.as_pv = D_80176360;
        } else {
            arg2->unk_2C.as_pv = D_80176300;
        }
        func_80047784(
            arg2,
            ((u8 *)arg2->unk_2C.as_pv)[
                ((D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

    case 1:
        if (arg3->unk_24.at01_u8.v != 0) {
            if (arg0->unk_A7 != 0) {
                arg2->unk_2C.as_pv = D_80176368;
            } else {
                arg2->unk_2C.as_pv = D_80176308;
            }
        } else {
            if (D_80083462 & 0x1000) {
                return;
            }

            if ((arg3->unk_64.as_s16 != 0) &&
                func_800AA6B4(arg0, arg1, arg2, 0)) {
                return;
            }

            if ((s16)func_800A2C34(arg3) != 0) {
                return;
            }

            if (arg3->unk_1C.as_u32 & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                return;
            }

            if (arg3->unk_1C.as_u32 & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_80173720(arg0, arg1, arg2, arg3);
                return;
            }

            if (arg3->unk_6D.as_s8 == 0) {
                return;
            }

            if ((s16)func_800A2C34(arg3) != 0) {
                S_801733F0_4 *owner;

                owner = D_800814A8;
                if ((s16)func_8009A180(
                        arg3, (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            func_800A9A0C(arg3);
            func_800A9A04(arg3);
            if (arg3->unk_24.at01_u8.v == 0) {
                return;
            }

            if (arg0->unk_A7 != 0) {
                arg2->unk_2C.as_pv = D_80176368;
            } else {
                arg2->unk_2C.as_pv = D_80176308;
            }
        }
        func_80047784(
            arg2,
            ((u8 *)arg2->unk_2C.as_pv)[
                ((D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        {
            u8 *global;

            global = (u8 *)&D_80083460;
            ((S_801733F0_2 *)global)->unk_0A++;
        }

increment_state:
        arg0->unk_9B++;
        return;

    case 2:
    {
        u8 *global;

        if ((arg2->unk_14 & 0xE000) == 0) {
            return;
        }

        global = (u8 *)&D_80083460;
        ((S_801733F0_2 *)global)->unk_0A--;
        arg3->unk_1C.as_u32 &= ~0x200;
        if (arg0->unk_A7 != 0) {
            arg0->unk_8C = D_80173B98;
        } else {
            arg0->unk_8C = D_80170F20;
        }
        return;
    }
    }
}

/* MECHANISM: A 0x28 frame naturally holds arg0/arg1/arg2/arg3 in s2/s3/s1/s0.
   Duplicating the state-1 palette selector restores the retail six-word CFG edge.
   Inline palette indexing keeps the shifted index in v0 and its base in v1. */
