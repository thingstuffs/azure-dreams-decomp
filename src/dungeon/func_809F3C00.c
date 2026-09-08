#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"


typedef struct S_80171400_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171400_1;   /* arg3 in func_80171400 */

typedef struct S_80171400_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171400_2;   /* arg2 in func_80171400 */


typedef struct S_80171400_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171400_4;   /* origin in func_80171400 */

typedef struct S_80171400_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171400_5;   /* player in func_80171400 */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s16 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171960(void *, void *);
extern void func_80171B28(void *, void *, void *, void *);
extern s16 func_80172270(void *, void *, void *, void *);
extern void func_80172434(void *, void *, void *, void *);
extern s16 func_80172554(void *, void *, void *, s32);
extern void func_80174218(void *, void *, void *, void *);
extern void func_80174948(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80175140[];
extern u8 D_80175148[];
extern u8 D_80175150[];
extern u8 D_80175170[];
extern u8 D_80175178[];
extern u8 D_80175180[];
extern u8 D_80175188[];
extern u8 D_80175190[];

void func_80171400(void *arg0, void *arg1, void *in_arg2, void *in_arg3)
{
    register void *arg2 ASM_REG("$18") = in_arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *arg3 ASM_REG("$17") = in_arg3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 scratch;
    s8 result;
    u16 state;
    u32 initial_flags = D_80083462;

#ifndef __mips__
#endif

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        func_80171960(arg0, arg1);
        return;
    }

    ASM_CLOBBER("$6");   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (((S_80171400_1 *)arg3)->unk_25 == 0) {
        u8 *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80171400_2 *)arg2)->unk_2C == D_80175188) {
            return;
        }
        table = D_80175180;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_80171400_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171400_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80171400_2 *)arg2)->unk_2C == D_80175190) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((S_80171400_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80175180) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80171400_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 != 0xE) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        }

        if ((((S_80171400_2 *)arg2)->unk_2C != D_80175140) &&
            (((S_80171400_2 *)arg2)->unk_2C != D_80175148)) {
            u8 *table = D_80175140;

            ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8 = 0;
            (*(void * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(arg2,
                table[((D_80083228 + ((S_80171400_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8);
        }

        ((S_80171400_1 *)arg3)->unk_1C |= 0x40000;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF7;

        if (((S_80171400_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175150) != 0) {
                return;
            }
        }

        if (((S_80171400_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_A8 = 0;
            func_80174218(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            if ((func_800AAB10(arg0, arg1, arg2, arg3) << 16) != 0) {
                func_80174948(arg0, arg1, arg2, arg3);
            }
        }
    }

    result = func_8009FB34(((S_80171400_2 *)arg2)->unk_24.at00.v, ((S_80171400_2 *)arg2)->unk_24.at01.v);
    ((S_80171400_2 *)arg2)->unk_26 = result;

    if (((S_80171400_1 *)arg3)->unk_6D > 0) {
        if (((S_80171400_1 *)arg3)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_80171400_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_80171400_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172554(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((S_80171400_1 *)arg3)->unk_46 | 0x4000;
            ((S_80171400_1 *)arg3)->unk_46 = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const sw_keep[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            u32 swi = (u32)((((S_80171400_1 *)arg3)->unk_46 & 0x3FFF) - 1);

            if (swi >= 12) {
                goto generic;
            }
            (void)sw_keep;
            goto *D_80170808[swi];
        }

sw_case89:
        if ((func_80172270(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172434(arg0, arg1, arg2, arg3);
        return;

sw_case567:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 direction;

            direction = func_800A0818(
                ((S_80171400_2 *)arg2)->unk_24.at00.v, ((S_80171400_2 *)arg2)->unk_24.at01.v,
                ((S_80171400_4 *)origin)->unk_24, ((S_80171400_4 *)origin)->unk_25, &scratch);
            player = D_800814A8;
            ((S_80171400_1 *)arg3)->unk_2A = direction;
            if (((S_80171400_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }
        /* fallthrough */

case_12:
        func_800A9A0C(arg3);
        return;

case_123:
        {
            void *callback;

            if (((S_80171400_2 *)arg2)->unk_2C == D_80175140) {
                callback = D_80175170;
            } else {
                callback = D_80175178;
            }
            func_800AAF00(arg0, arg1, arg2, callback, func_80171400);
            return;
        }

generic:
        func_80171B28(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((S_80171400_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
            if (!(((S_80171400_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171400_2 *)arg2)->unk_24.at00.v, ((S_80171400_2 *)arg2)->unk_24.at01.v,
                        ((S_80171400_4 *)origin)->unk_24, ((S_80171400_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_80171400_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80171400_2 *)arg2)->unk_24.at00.v, ((S_80171400_2 *)arg2)->unk_24.at01.v,
                        ((S_80171400_4 *)origin)->unk_24, ((S_80171400_4 *)origin)->unk_25, &scratch);
                }
            }
        }
    }
}

/* MECHANISM: The 0x38 frame holds arg0/arg1/arg2/arg3 in s0/s3/s2/s1.
   Pre-branch a2/a3 clobbers retain retail's three otherwise-DCE'd call reloads
   while leaving move a0,s0 available for the branch delay slot. */
