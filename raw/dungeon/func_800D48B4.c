#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_8003DB94(void *, s32, s32);
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
extern void func_800DA660(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800D8C64[];
extern u8 D_800E262C[];

void func_800DA014(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    s32 state;

    state = FIELD(in_arg0, u8, 0x9B);
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
    if (FIELD(in_arg2, u16, 0x14) & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_800E262C;
        FIELD(in_arg2, void *, 0x2C) = table;
        func_8003DB94(in_arg2,
            *(void **)(table + (((D_80083228 + FIELD(in_arg3, s16, 0x2A) + 0x100) >> 7) & 28)),
            0);
        system_base = (u8 *)&D_80083460;
        FIELD(system_base, u16, 0xA)--;
        FIELD(in_arg0, u8, 0x9B)++;
    }
    return;

state_one:
    {
        s32 flags;
        u8 *system_base;

        system_base = (u8 *)&D_80083460;
        if (FIELD(system_base, u16, 2) & 0x1000) {
            return;
        }

        if ((FIELD(in_arg3, s16, 0x64) != 0) &&
            (func_800AA6B4(in_arg0, in_arg1, in_arg2, 0) != 0)) {
            return;
        }

        if (FIELD(in_arg3, u8, 0x25) == 0) {
            if (FIELD(system_base, u16, 2) & 0x2008) {
                return;
            }
            func_800AA79C(in_arg0, in_arg1, in_arg2, in_arg3);
            return;
        }

        if ((func_800A2C34(in_arg3) << 16) != 0) {
            return;
        }

        flags = FIELD(in_arg3, s32, 0x1C);
        if (flags & 0x100) {
            func_800AA258(in_arg0, in_arg1, in_arg2, in_arg3);
            return;
        }

        if (flags & 0x80000) {
            func_800AA888(in_arg0, in_arg1, in_arg2, in_arg3);
            func_800DA660(in_arg0, in_arg1, in_arg2, in_arg3);
            return;
        }

        if (FIELD(in_arg3, s8, 0x6D) == 0) {
            return;
        }

        if ((func_800A2C34(in_arg3) << 16) != 0) {
            if ((func_8009A180(in_arg3,
                    (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(in_arg3);
        func_800A9A04(in_arg3);

        if ((func_80042900(in_arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = FIELD(in_arg2, s8, 0x26);
            if ((((coordinate == FIELD(origin, s8, 0x26)) &&
                        (coordinate >= 0)) ||
                    (func_8009FD40(origin, in_arg2) < 2)) &&
                ((func_800A6D30() & 7) == 0)) {
                func_80042B68(in_arg3, 1);
            }
        }

        if ((func_80042900(in_arg3, 1) << 16) == 0) {
        u8 *table;

        table = D_800E262C;
        FIELD(in_arg2, void *, 0x2C) = table;
        func_8003DB94(in_arg2,
            *(void **)(table + (((D_80083228 + FIELD(in_arg3, s16, 0x2A) + 0x100) >> 7) & 28)),
            0);
        } else {
            return;
        }
    }

    if (!(FIELD(in_arg2, u16, 0x14) & 0x8000)) {
        u8 *system_base = (u8 *)&D_80083460;

        FIELD(system_base, u16, 0xA)++;
        FIELD(in_arg0, u8, 0x9B)++;
        return;
    }
    goto finish;

state_two:
    if (!(FIELD(in_arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    {
        u8 *system_base = (u8 *)&D_80083460;
        FIELD(system_base, u16, 0xA)--;
    }

finish:
    FIELD(in_arg3, s32, 0x1C) &= ~0x200;
    FIELD(in_arg0, void *, 0x8C) = D_800D8C64;
}
