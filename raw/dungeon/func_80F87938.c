#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
        FIELD(arg0, u8, 0x9A) = 0xE;
        func_80171670();
        return;
    }

    
    
    
    

    if (FIELD(arg3, u8, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (FIELD(arg2, void *, 0x2C) == D_80174AFC) {
            return;
        }
        FIELD(arg2, void *, 0x2C) = D_80174AF4;
        func_80047784(arg2,
            D_80174AF4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (FIELD(arg3, u32, 0x1C) & 0x200) {
        if (FIELD(arg2, void *, 0x2C) == D_80174AFC) {
            FIELD(arg0, u8, 0x9A) = 0xD;
            FIELD(arg0, u8, 0x9B) = 1;
            FIELD(arg0, s32, 0x8C) = 0;
            FIELD(arg3, u32, 0x1C) &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174AF4) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg0, u8, 0x9A) != 0xE) {
            FIELD(arg0, u8, 0x9A) = 0xE;
        }

        if (FIELD(arg2, void *, 0x2C) != D_80174AD4) {
            FIELD(arg0, s16, 0xA0) = 0;
            FIELD(arg2, void *, 0x2C) = D_80174AD4;
            func_80047784(arg2,
                D_80174AD4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                FIELD(arg0, s16, 0xA0));
        }

        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174ADC) != 0) {
                return;
            }
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            FIELD(arg0, s16, 0xA0) = 0;
            func_80173D38(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, u8, 0x26) = tile;

    if (FIELD(arg3, s8, 0x6D) > 0) {
        if (FIELD(arg3, u32, 0x1C) & 0x20) {
            goto case_12;
        }
        if (FIELD(arg2, u16, 0x24) == *(u16 *)&D_80082EA4) {
            goto default_case;
        }
        state = FIELD(arg3, u16, 0x46);
        if (!(state & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172258(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = FIELD(arg3, u16, 0x46) | 0x4000;
            FIELD(arg3, u16, 0x46) = state;
            if (!(state & 0x8000)) {
                goto default_case;
            }
        }

        {
            u32 swi = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;

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
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(coord_origin, u8, 0x24), FIELD(coord_origin, u8, 0x25),
                &scratch);
            player = D_800814A8;
#ifndef __mips__
            
#endif
            FIELD(arg3, s16, 0x2A) = coordinate;
            if (FIELD(player, u8, 0x9A) == 0x11) {
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

    flags = FIELD(arg3, u32, 0x1C);
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
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25)) << 16) != 0) {
            FIELD(arg3, s16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(origin, u8, 0x24), FIELD(origin, u8, 0x25), &scratch);
        }
    }
    return;
}

/* MECHANISM: The 0x38 frame holds a sibling s32 scratch at sp+0x18 and args in s1/s3/s2/s0.
   A short-lived symbolic origin=D_80082E80 naturally reuses dead s1; a pinned 0x80080000 base does not.
   That held-base idiom puts &scratch in the branch slot and arg5's store before the last two loads. */
