#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801714B8;
extern u8 D_801760BC;
extern u8 D_801760C4;

void func_80172AD8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 state;
    s32 remaining;
    s32 tile;
    s32 current;
    s32 sum;
    s32 velocity;
    s32 counter;
    s32 timer;
    s32 flags;
    u8 *global_base;
    u8 *map_base;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto decrement_timer;
    }
    FIELD(arg2, u8 *, 0x2C) = &D_801760BC;
    func_80047784(
        arg2,
        *(&D_801760BC +
          (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
        0);
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, s16, 0x9E) = 5;
    FIELD(arg0, s32, 0xA4) = 0;
    FIELD(arg0, u8, 0x9B)++;

state_one:
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA4);
    FIELD(arg2, s16, 0x1C) = 0xC00;
    FIELD(arg2, s16, 0x1E) = 0x1400;
    remaining = FIELD(arg0, s16, 0x9E);
    if (remaining != 0) {
        tile = FIELD(arg2, u8, 0x24);
        current = FIELD(arg1, s16, 2);
        tile <<= 6;
        current -= 0x20;
        FIELD(arg1, s32, 0xC) = ((tile - current) << 16) / remaining;

        current = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) - current) << 16) /
            FIELD(arg0, s16, 0x9E);
        FIELD(arg0, s32, 0xA4) =
            (-func_800644B8(FIELD(arg0, s16, 0x9E) * 0x199)) << 9;
    }

    sum = FIELD(arg0, s32, 0x90);
    velocity = FIELD(arg0, s32, 0xA4);
    counter = FIELD(arg0, u16, 0x9E);
    sum += velocity;
    counter -= 1;
    FIELD(arg0, u16, 0x9E) = counter;
    FIELD(arg0, s32, 0x90) = sum;
    if ((counter << 16) >= 0) {
        goto state_two;
    }

    FIELD(arg0, s32, 0x90) = 0;
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, s32, 0x1C) |= 0x08000000;
    FIELD(arg0, u8, 0x9B)++;

state_two:
    if (FIELD(arg3, s32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg2, s16, 0x1C) = 0x1400;
        FIELD(arg2, s16, 0x1E) = 0xC00;
        FIELD(arg2, u8 *, 0x2C) = &D_801760C4;
        func_80047784(
            arg2,
            *(&D_801760C4 +
              (((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7)),
            0);
        FIELD(arg0, u8, 0x9B)++;
        goto decrement_timer;
    }
    goto decrement_timer;

state_three:
    FIELD(arg2, s16, 0x1C) = 0x1000;
    FIELD(arg2, s16, 0x1E) = 0x1000;

decrement_timer:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) > 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg2, s16, 0x1C) = 0x1000;
    FIELD(arg2, s16, 0x1E) = 0x1000;
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, s16, 8) != 0) {
        FIELD(global_base, u16, 8)--;
    }

    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x2000) {
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
        goto collision_check;
    }
    if (flags & 0x410) {
        goto collision_check;
    }
    if (!(flags & 0x20000)) {
        goto collision_check;
    }
    map_base = D_80082E80;
    FIELD(arg3, s16, 0x2A) = func_800A0818(
        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
        FIELD(map_base, u8, 0x24), FIELD(map_base, u8, 0x25), &sp18);

collision_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        FIELD(arg0, void *, 0x8C) = &D_801714B8;
        func_800A9A04(arg3);
    }
}
