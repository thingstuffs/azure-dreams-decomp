#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_8004491C(void *, void *);
extern void func_80044A50(void *);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A32A4(void *);
extern s32 D_800814A0;
extern s32 D_80083460;
extern s32 D_800C6AEC;

void func_800ACBE4(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 actor_status;
    s32 actor_flags;
    s32 effect_size;
    s32 *global_base;
    u8 state;
    u8 level;
    u8 effect_x;
    u8 effect_y;
    void *actor;

    state = FIELD(arg0, u8, 0x9B);
    actor = arg3;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    actor = (u8 *)arg0 - 0x20;
    func_80044A50(actor);
    FIELD(arg2, u16, 0x12) -= 0x80;
    FIELD(arg2, u16, 0x14) |= 0xC;
    func_8004491C(actor, &D_800C6AEC);
    FIELD(arg2, u8, 0xF) = 0;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_one:
    if (FIELD(arg2, u8, 0xF) < 8) {
        level = FIELD(arg2, u8, 0xE);
        FIELD(arg2, u8, 0xF)++;
        level += -level / FIELD(arg2, volatile u8, 0xF);
        FIELD(arg2, u8, 0xE) = level;
        FIELD(arg2, u8, 0xD) = level;
        FIELD(arg2, u8, 0xC) = level;
        goto done;
    }

    global_base = &D_80083460;
    if (global_base[4] == (s32)((u8 *)actor - 0x20)) {
        global_base[4] &= 0x7FFFFFFF;
    }
    func_800A32A4(actor);
    actor_status = FIELD(actor, s32, 0x1C);
    effect_x = FIELD(arg2, u8, 0x24);
    effect_y = FIELD(arg2, u8, 0x25);
    effect_size = 0x3000;
    if (actor_status & 0x2000) {
        effect_size = 0x300;
    }
    func_8009A3D0(effect_x, effect_y, effect_size);
    actor_flags = FIELD(actor, s32, 0x14);
    if (actor_flags & 0x400000) {
        FIELD(actor, s32, 0x14) = actor_flags & 0xFFBFFFFF;
        FIELD(actor, s32, 0x1C) |= 0x400000;
    }
    func_8009A028(actor);
    FIELD(actor, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: The four-slot ABI holds a0/a2/a3 in s2/s1/s0, while true-space
   epilogue targets remain local CFG edges under the 0x20-byte frame.
   A volatile post-store byte reload and separate status/effect/flag lifetimes
   reproduce the retail div roles, load-delay fill, and a0/a1/a2 call setup. */
