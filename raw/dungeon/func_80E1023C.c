#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800A56E0(s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800B8228(s32, s32, s32, void *);
extern s32 func_80042900(void *, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009A028(void *);
extern void func_800ACF88(void *);

extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

void func_80173A3C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    u16 timer;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto update;
    }
    return;

state_zero:
    if (D_8008346A != 0) {
        return;
    }

    FIELD(arg0, u8, 0x9B) = 1;
    FIELD(arg2, s16, 0x10) = 0x20;
    FIELD(arg2, u16, 0x12) -= 0x80;
    FIELD(arg2, u16, 0x14) |= 0xC;
    FIELD(arg3, u32, 0x1C) |= 0x10000000;
    func_800A56E0(0x805);
    FIELD(arg2, u32, 0xC) = 0x00808080;
    FIELD(arg0, s16, 0x96) = 0xC;

update:
    FIELD(arg2, u8, 0xC) -= FIELD(arg2, u8, 0xC) / FIELD(arg0, s16, 0x96);
    FIELD(arg2, u8, 0xD) -= FIELD(arg2, u8, 0xD) / FIELD(arg0, s16, 0x96);
    FIELD(arg2, u8, 0xE) -= FIELD(arg2, u8, 0xE) / FIELD(arg0, s16, 0x96);

    FIELD(arg2, u16, 0x1C) >>= 2;
    FIELD(arg2, u16, 0x1E) >>= 1;
    FIELD(arg2, u16, 0x1C) *= 3;
    FIELD(arg2, u16, 0x1E) *= 3;

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if (((s32)timer << 16) > 0) {
        if ((FIELD(arg2, u16, 0x14) & 0x8000) == 0) {
            return;
        }
    }

    if ((FIELD(arg3, u32, 0x14) & 0x20000000) == 0) {
        u8 *global = (u8 *)&D_80083460;
        if (FIELD(global, void *, 0x10) == (u8 *)arg3 - 0x20) {
            FIELD(global, u32, 0x10) &= 0x7FFFFFFF;
        }
    }

    if ((FIELD(arg3, u32, 0x14) & 0x4000) == 0) {
        func_800A2FE0(arg3);
        func_800A32A4(arg3);
        if (FIELD(arg3, u8, 0x49) != 0 &&
            (FIELD(arg3, u8, 0x4B) & 0x20) == 0) {
            func_800B8228(FIELD(arg1, s16, 2), FIELD(arg1, s16, 6),
                          FIELD(arg3, s16, 0x88), (u8 *)arg3 + 0x48);
        }
        if ((func_80042900(arg3, 0x1B) << 16) == 0) {
            s32 flags = FIELD(arg3, u32, 0x1C);
            s32 color0 = FIELD(arg2, u8, 0x24);
            s32 color1 = FIELD(arg2, u8, 0x25);
            s32 effect = 0x3000;
            if (flags & 0x2000) {
                effect = 0x300;
            }
            func_8009A3D0(color0, color1, effect);
        }
        func_8009A028(arg3);
        FIELD(arg3, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }

    if ((FIELD(arg3, u32, 0x14) & 0x20000000) == 0) {
        func_800ACF88(arg3);
    }
    func_800A2FE0(arg3);
    func_800A32A4(arg3);
    if ((func_80042900(arg3, 0x1B) << 16) == 0) {
        s32 flags = FIELD(arg3, u32, 0x1C);
        s32 color0 = FIELD(arg2, u8, 0x24);
        s32 color1 = FIELD(arg2, u8, 0x25);
        s32 effect = 0x3000;
        if (flags & 0x2000) {
            effect = 0x300;
        }
        func_8009A3D0(color0, color1, effect);
    }
    func_8009A028(arg3);
    FIELD(arg3, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    func_800A56E0(0x609);
}
