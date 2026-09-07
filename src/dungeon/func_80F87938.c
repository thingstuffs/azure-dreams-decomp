#include "common.h"

typedef struct S_80171138_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x4];
    s16 unk_A0;
} S_80171138_0;   /* arg0 in func_80171138 */

typedef struct S_80171138_1 {
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
} S_80171138_1;   /* arg3 in func_80171138 */

typedef struct S_80171138_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171138_2;   /* arg2 in func_80171138 */

typedef struct S_80171138_3 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80171138_3;   /* D_800814A8 in func_80171138 */

typedef struct S_80171138_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171138_4;   /* coord_origin in func_80171138 */

typedef struct S_80171138_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171138_5;   /* player in func_80171138 */

typedef struct S_80171138_6 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171138_6;   /* origin in func_80171138 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171670(void);
extern void func_8017182C(void *, void *, void *, void *);
extern s32 func_80171F74(void *, void *, void *, void *);
extern void func_80172138(void *, void *, void *, void *);
extern s32 func_80172258(void *, void *, void *, s32);
extern void func_80173D38(void *, void *, void *, void *);
extern void func_801740F4(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *const D_80170808[];
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174ADC[];
extern u8 D_80174AEC[];
extern u8 D_80174AF4[];
extern u8 D_80174AFC[];

void func_80171138(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const sw_keep[] = {
        &&case_1, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8,
        &&case_9, &&case_10, &&case_11, &&case_12,
    };
    void *arg0;
    void *arg1;
    void *arg2;
    void *arg3;
    s32 scratch;
    s32 flags;
    s8 tile;
    u16 state;
    u32 initial_flags = D_80083462;

    arg0 = arg0_;
    arg1 = arg1_;
    arg2 = arg2_;
    arg3 = arg3_;

    if (initial_flags & 0x1000) {
        ((S_80171138_0 *)arg0)->unk_9A = 0xE;
        func_80171670();
        return;
    }

    
    
    
    

    if (((S_80171138_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80171138_2 *)arg2)->unk_2C == D_80174AFC) {
            return;
        }
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AF4;
        func_80047784(arg2,
            D_80174AF4[((D_80083228 + ((S_80171138_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171138_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80171138_2 *)arg2)->unk_2C == D_80174AFC) {
            ((S_80171138_0 *)arg0)->unk_9A = 0xD;
            ((S_80171138_0 *)arg0)->unk_9B = 1;
            ((S_80171138_0 *)arg0)->unk_8C = 0;
            ((S_80171138_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174AF4) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80171138_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((S_80171138_0 *)arg0)->unk_9A != 0xE) {
            ((S_80171138_0 *)arg0)->unk_9A = 0xE;
        }

        if (((S_80171138_2 *)arg2)->unk_2C != D_80174AD4) {
            ((S_80171138_0 *)arg0)->unk_A0 = 0;
            (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AD4;
            func_80047784(arg2,
                D_80174AD4[((D_80083228 + ((S_80171138_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                ((S_80171138_0 *)arg0)->unk_A0);
        }

        ((S_80171138_1 *)arg3)->unk_1C |= 0x40000;
        ((S_80171138_0 *)arg0)->unk_98 &= 0xFFF7;

        if (((S_80171138_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174ADC) != 0) {
                return;
            }
        }

        if (((S_80171138_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            ((S_80171138_0 *)arg0)->unk_A0 = 0;
            func_80173D38(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(((S_80171138_2 *)arg2)->unk_24.at00.v, ((S_80171138_2 *)arg2)->unk_24.at01.v);
    ((S_80171138_2 *)arg2)->unk_26 = tile;

    if (((S_80171138_1 *)arg3)->unk_6D > 0) {
        if (((S_80171138_1 *)arg3)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_80171138_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto default_case;
        }
        state = ((S_80171138_1 *)arg3)->unk_46;
        if (!(state & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((S_80171138_3 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172258(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((S_80171138_1 *)arg3)->unk_46 | 0x4000;
            ((S_80171138_1 *)arg3)->unk_46 = state;
            if (!(state & 0x8000)) {
                goto default_case;
            }
        }

        {
            u32 swi = (((S_80171138_1 *)arg3)->unk_46 & 0x3FFF) - 1;

            if (swi >= 12) {
                goto default_case;
            }
            (void)sw_keep;
            goto *D_80170808[swi];
        }

case_8:
        func_801740F4(arg0, arg1, arg2, arg3);
        return;

case_9:
        if ((func_80171F74(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172138(arg0, arg1, arg2, arg3);
        return;

case_5:
case_6:
case_7:
        {
            u8 *coord_origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_80171138_2 *)arg2)->unk_24.at00.v, ((S_80171138_2 *)arg2)->unk_24.at01.v,
                ((S_80171138_4 *)coord_origin)->unk_24, ((S_80171138_4 *)coord_origin)->unk_25,
                &scratch);
            player = D_800814A8;
#ifndef __mips__
            
#endif
            ((S_80171138_1 *)arg3)->unk_2A = coordinate;
            if (((S_80171138_5 *)player)->unk_9A == 0x11) {
                goto call_aaf;
            }
        }

case_12:
        func_800A9A0C(arg3);
        return;

case_1:
case_2:
case_3:
call_aaf:
        func_800AAF00(arg0, arg1, arg2, D_80174AEC, D_80171138);
        return;

case_4:
case_10:
case_11:
default_case:
        func_8017182C(arg0, arg1, arg2, arg3);
        return;
    }

    flags = ((S_80171138_1 *)arg3)->unk_1C;
    if (flags & 0x2000) {
        return;
    }
    if (tile >= 0) {
        if (((DungeonRecord *)D_800E2970)[tile].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    {
        u8 *origin = D_80082E80;

        if ((func_8009FD7C(
                ((S_80171138_2 *)arg2)->unk_24.at00.v, ((S_80171138_2 *)arg2)->unk_24.at01.v,
                ((S_80171138_6 *)origin)->unk_24, ((S_80171138_6 *)origin)->unk_25) << 16) != 0) {
            ((S_80171138_1 *)arg3)->unk_2A = func_800A0818(
                ((S_80171138_2 *)arg2)->unk_24.at00.v, ((S_80171138_2 *)arg2)->unk_24.at01.v,
                ((S_80171138_6 *)origin)->unk_24, ((S_80171138_6 *)origin)->unk_25, &scratch);
        }
    }
    return;
}

/* MECHANISM: The 0x38 frame holds a sibling s32 scratch at sp+0x18 and args in s1/s3/s2/s0.
   A short-lived symbolic origin=D_80082E80 naturally reuses dead s1; a pinned 0x80080000 base does not.
   That held-base idiom puts &scratch in the branch slot and arg5's store before the last two loads. */
