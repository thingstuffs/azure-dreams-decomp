#include "common.h"

extern void func_8009A028(void *arg0);
extern void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2);
extern void func_800A2FE0(void *arg0);
extern void func_800A32A4(void *arg0);
extern void func_800A56E0(s32 arg0);
extern void func_800ACF88(void *arg0);
extern void func_80173354(void) __attribute__((noreturn));

extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

void func_80173234(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3)
{
    s32 flags;
    s32 actorFlags;
    s32 strength;
    s32 *state;
    s32 x;
    s32 y;
    u8 mode;

    mode = arg0[0x9B];
    if (mode != 0) {
        if (mode != 1) {
            func_80173354();
        }
        goto active;
    }

    if (D_8008346A == 0) {
        flags = *(s32 *)(arg3 + 0x14);
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) {
                func_800ACF88(arg3);
            }
        }

        arg0[0x9B]++;
        func_800A56E0(0x805);

active:
        if (*(u16 *)(arg2 + 0x14) & 0xE000) {
            state = &D_80083460;
            if (state[4] == (s32)(arg3 - 0x20)) {
                state[4] &= 0x7FFFFFFF;
            }

            func_800A2FE0(arg3);
            func_800A32A4(arg3);

            actorFlags = *(s32 *)(arg3 + 0x1C);
            x = arg2[0x24];
            y = arg2[0x25];
            strength = 0x3000;
            if (actorFlags & 0x2000) {
                strength = 0x300;
            }
            func_8009A3D0(x, y, strength);
            func_8009A028(arg3);

            *(u16 *)(arg3 - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}

/* MECHANISM: Direct scalar D_800814A0 RMW restores the retail global displacement.
   Splitting early flags from actorFlags gives the later load/mask its retail v0 role.
   Natural arg lifetimes preserve the 0x20 frame and s1/s2/s0 save contract. */
