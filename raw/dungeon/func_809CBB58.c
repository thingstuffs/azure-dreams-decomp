#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173A30(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E54[];
extern u8 D_80173CDC[];
extern u8 D_80173CE4[];

void func_80173358(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    register void *arg0 ASM_REG("$18") = in_arg0;
    register void *arg1 ASM_REG("$19") = in_arg1;
    register void *arg2 ASM_REG("$17") = in_arg2;
    register void *arg3 ASM_REG("$16") = in_arg3;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    return;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_80173CDC;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        system_base = (u8 *)&D_80083460;
        FIELD(system_base, u16, 0xA)--;
        FIELD(arg0, u8, 0x9B)++;
    }
    return;

state_one:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        s32 flags;
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        if (FIELD(system_base, u16, 2) & 0x1000) {
            return;
        }

        if ((FIELD(arg3, s16, 0x64) != 0) &&
            (func_800AA6B4(arg0, arg1, arg2, 0) != 0)) {
            return;
        }

        if (FIELD(arg3, u8, 0x25) == 0) {
            if (FIELD(system_base, u16, 2) & 0x2008) {
                return;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            return;
        }

        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173A30(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg3, s8, 0x6D) == 0) {
            return;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);

        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = FIELD(arg2, s8, 0x26);
            if ((((coordinate == FIELD(origin, s8, 0x26)) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, arg2) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(arg3, 1);
            }
        }

        if ((func_80042900(arg3, 1) << 16) != 0) {
            return;
        }
    }

    {
        u8 *table;

        table = D_80173CE4;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        u8 *system_base = (u8 *)&D_80083460;

        FIELD(system_base, u16, 0xA)++;
        FIELD(arg0, u8, 0x9B)++;
        return;
    }
    goto finish;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    {
        u8 *system_base = (u8 *)&D_80083460;
        FIELD(system_base, u16, 0xA)--;
    }

finish:
    FIELD(arg3, s32, 0x1C) &= ~0x200;
    FIELD(arg0, void *, 0x8C) = D_80170E54;
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
}
