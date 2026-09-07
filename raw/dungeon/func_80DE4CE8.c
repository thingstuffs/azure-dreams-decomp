#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80174520[];

void func_801724E8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s32 timer;
    s16 next_timer;
    u16 countdown;
    s32 state;
    s32 flags;
    s32 delta;
    s16 *global;
    u8 *map;

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
    goto update_countdown;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto update_countdown;

state_zero:
    if (((FIELD(arg2, s8, 4) == 2) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, s16, 0x9E) = 5;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B)++;
        goto state_one;
    }
    goto update_countdown;

state_one:
    timer = FIELD(arg0, s16, 0x9E);
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    if (timer != 0) {
        FIELD(arg1, s32, 0xC) =
            (((FIELD(arg2, u8, 0x24) << 6) - ({ FIELD(arg1, s16, 2) - 0x20; })) << 16) / timer;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) - (delta = FIELD(arg1, s16, 6) - 0x20)) << 16) /
            FIELD(arg0, s16, 0x9E);
        FIELD(arg0, s32, 0xA0) =
            (-func_800644B8(FIELD(arg0, s16, 0x9E) * 0x199)) << 9;
    }

    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    next_timer = FIELD(arg0, u16, 0x9E) - 1;
    FIELD(arg0, s16, 0x9E) = next_timer;
    if (next_timer < 0) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

state_two:
    if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg2, void *, 0x2C) = D_80174520;
        func_80047784(
            arg2,
            D_80174520[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B)++;
    }

update_countdown:
    countdown = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = countdown;
    if ((s16)countdown <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        global = (s16 *)&D_80083460;
        if (global[4] != 0) {
            global[4]--;
        }

        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
        } else {
            if (flags & 0x410) {
                goto check_collision;
            }
            if (!(flags & 0x20000)) {
                goto check_collision;
            }
            map = D_80082E80;
            FIELD(arg3, s16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                map[0x24], map[0x25], &scratch);
        }

check_collision:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, void *, 0x8C) = D_80170E5C;
            func_800A9A04(arg3);
        }
    }
}
