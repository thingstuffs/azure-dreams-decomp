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
extern void func_801737DC(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80174520[];
extern u8 D_80174538[];

void func_80173254(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *p1 ASM_REG("$18");
    register void *p2 ASM_REG("$17");
    u8 state;

    p1 = arg1;
    p2 = arg2;
#define arg1 p1
#define arg2 p2

    state = FIELD(arg0, u8, 0x9B);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_80174538;
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
    {
        u8 *system_base;

        if ((func_80042900(arg3, 1) << 16) != 0) {
            s32 flags;

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
                func_801737DC(arg0, arg1, arg2, arg3);
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
    }

    {
        u8 *table;

        table = D_80174520;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg3, s32, 0x1C) &= ~0x200;
        FIELD(arg0, void *, 0x8C) = D_80170E5C;
    }
    ASM_KEEP(p1);
    ASM_KEEP(p2);
}
