#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s32 func_800A0818(u8, u8, u8, u8, void *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);
extern void func_801708B8(void *, void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E23E0[];
extern u8 D_800E2458[];
extern u8 D_800E2460[];
extern u8 D_80171A80[];

void func_801730C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto done;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto done;
    }
    {
        u8 *model = D_800E2458;

        FIELD(arg2, u8 *, 0x2C) = model;
        func_80047784(arg2,
            model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            1);
    }
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s16, 0xA8) = 5;
    FIELD(arg0, s32, 0xA4) = 0;
    FIELD(arg0, u8, 0x9B)++;

state_one:
    {
        s32 initial_timer;
        s16 next_timer;

        initial_timer = FIELD(arg0, s16, 0xA8);
        FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA4);
        if (initial_timer != 0) {
            s32 delta;
            s32 position;

            delta = FIELD(arg2, u8, 0x24) << 6;
            position = FIELD(arg1, s16, 2);
            position -= 0x20;
            delta -= position;
            FIELD(arg1, s32, 0x0C) = (delta << 16) / initial_timer;

            position = FIELD(arg1, s16, 6);
            delta = FIELD(arg2, u8, 0x25) << 6;
            position -= 0x20;
            delta -= position;
            FIELD(arg1, s32, 0x10) =
                (delta << 16) / FIELD(arg0, s16, 0xA8);
            FIELD(arg0, s32, 0xA4) =
                -func_800644B8(FIELD(arg0, s16, 0xA8) * 0x199) << 9;
        }

        FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA4);
        next_timer = (u16)FIELD(arg0, s16, 0xA8) - 1;
        FIELD(arg0, s16, 0xA8) = next_timer;
        if (next_timer >= 0) {
            goto state_two;
        }
    }
    FIELD(arg0, s16, 0x92) = -0x10;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x08000000;
    FIELD(arg0, u8, 0x9B)++;

state_two:
    if (!(FIELD(arg3, u32, 0x1C) & 0x08000000)) {
        goto done;
    }
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    {
        u8 *model = D_800E2460;

        FIELD(arg2, u8 *, 0x2C) = model;
        func_80047784(arg2,
            model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_three:
    {
        u8 *model = D_800E23E0;

        if (FIELD(arg2, u8 *, 0x2C) == model) {
            goto done;
        }
        FIELD(arg2, u8 *, 0x2C) = model;
        func_80047784(arg2,
            model[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
    if (FIELD(arg0, u8, 0xB0) != 0) {
        goto done;
    }
    func_801708B8(arg0, arg1, arg2);

done:
    {
        u16 timer;

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((timer << 16) > 0) {
            return;
        }
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x10);
    func_800A4ACC(arg3);
    {
        u8 *global = (u8 *)&D_80083460;

        if (FIELD(global, s16, 8) != 0) {
            FIELD(global, s16, 8) = (u16)FIELD(global, s16, 8) - 1;
        }
    }
    {
        s32 flags = FIELD(arg3, s32, 0x1C);

        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
            goto call_actor;
        }
        if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                FIELD(arg3, s16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    D_80082E80[0x24], D_80082E80[0x25], &sp18);
            }
        }
    }

call_actor:
    if ((func_800AD9B4(arg2, arg3) << 16) <= 0) {
        return;
    }
    FIELD(arg0, void *, 0x8C) = D_80171A80;
    func_800A9A04(arg3);
}
