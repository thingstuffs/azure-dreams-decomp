#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

void func_801733F0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
    {
        u8 *global;

        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        global = (u8 *)&D_80083460;
        FIELD(global, u16, 0xA)--;
        if (FIELD(arg0, u8, 0xA7) != 0) {
            FIELD(arg2, void *, 0x2C) = D_80176360;
        } else {
            FIELD(arg2, void *, 0x2C) = D_80176300;
        }
        func_80047784(
            arg2,
            ((u8 *)FIELD(arg2, void *, 0x2C))[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        goto increment_state;
    }

    case 1:
        if (FIELD(arg3, u8, 0x25) != 0) {
            if (FIELD(arg0, u8, 0xA7) != 0) {
                FIELD(arg2, void *, 0x2C) = D_80176368;
            } else {
                FIELD(arg2, void *, 0x2C) = D_80176308;
            }
        } else {
            if (D_80083462 & 0x1000) {
                return;
            }

            if ((FIELD(arg3, s16, 0x64) != 0) &&
                func_800AA6B4(arg0, arg1, arg2, 0)) {
                return;
            }

            if ((s16)func_800A2C34(arg3) != 0) {
                return;
            }

            if (FIELD(arg3, u32, 0x1C) & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                return;
            }

            if (FIELD(arg3, u32, 0x1C) & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_80173720(arg0, arg1, arg2, arg3);
                return;
            }

            if (FIELD(arg3, s8, 0x6D) == 0) {
                return;
            }

            if ((s16)func_800A2C34(arg3) != 0) {
                void *owner;

                owner = D_800814A8;
                if ((s16)func_8009A180(
                        arg3, (u8 *)FIELD(owner, void *, 0x58) + 0x20) != 0) {
                    return;
                }
            }

            func_800A9A0C(arg3);
            func_800A9A04(arg3);
            if (FIELD(arg3, u8, 0x25) == 0) {
                return;
            }

            if (FIELD(arg0, u8, 0xA7) != 0) {
                FIELD(arg2, void *, 0x2C) = D_80176368;
            } else {
                FIELD(arg2, void *, 0x2C) = D_80176308;
            }
        }
        func_80047784(
            arg2,
            ((u8 *)FIELD(arg2, void *, 0x2C))[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        {
            u8 *global;

            global = (u8 *)&D_80083460;
            FIELD(global, u16, 0xA)++;
        }

increment_state:
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
    {
        u8 *global;

        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        global = (u8 *)&D_80083460;
        FIELD(global, u16, 0xA)--;
        FIELD(arg3, u32, 0x1C) &= ~0x200;
        if (FIELD(arg0, u8, 0xA7) != 0) {
            FIELD(arg0, void *, 0x8C) = D_80173B98;
        } else {
            FIELD(arg0, void *, 0x8C) = D_80170F20;
        }
        return;
    }
    }
}

/* MECHANISM: A 0x28 frame naturally holds arg0/arg1/arg2/arg3 in s2/s3/s1/s0.
   Duplicating the state-1 palette selector restores the retail six-word CFG edge.
   Inline palette indexing keeps the shifted index in v0 and its base in v1. */
