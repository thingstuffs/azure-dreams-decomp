#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s16, s16);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_80171738(void) __attribute__((noreturn));
extern void func_8017178C(void) __attribute__((noreturn));
extern void func_80171EFC(void *, s32, void *, void *);

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174138[];

void func_80171570(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register void *state ASM_REG("$17") = arg3;
    s32 mode;
    s16 result;
    s16 next;
    s32 x;
    s32 y;
    s32 count;
    u8 a24;
    u8 a25;

    if (FIELD(state, s8, 0x71) <= 0) {
        return;
    }
    if (FIELD(state, u8, 0x71) <= FIELD(state, s16, 0x8A)) {
        return;
    }

    if (FIELD(arg2, u8 *, 0x2C) != D_80174138) {
        FIELD(arg2, u8 *, 0x2C) = D_80174138;
        func_80047784(
            arg2,
            D_80174138[((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(state, s32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(x, y, mode);

    next = func_800A0818(
        x,
        y,
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74),
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C),
        (u8 *)arg0 + 0x98);
    result = func_8009A66C(next, arg2, state, 0x20);

    FIELD(arg2, u8, 0x24) =
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74);
    mode = 0x3000;
    FIELD(arg2, u8, 0x25) =
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C);
    FIELD(state, s16, 0x8A) = (u16)FIELD(state, s16, 0x8A) + 1;

    a24 = FIELD(arg2, u8, 0x24);
    a25 = FIELD(arg2, u8, 0x25);
    if (FIELD(state, s32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(a24, a25, mode);
    FIELD(state, s16, 0x2A) = next;

    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            func_80171EFC(arg0, arg1, arg2, state);
            FIELD(arg0, s32, 0x8C) = 0;
            return func_80171738();
        }
    }

    FIELD(arg0, u8, 0x9A) = 0x0F;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(state, s32, 0x1C) |= 0x40000000;
    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        return func_8017178C();
    }

    FIELD(arg0, s16, 0x96) = 8;
    count = FIELD(state, u8, 0x71);
    if (count > 0) {
        FIELD(arg0, s16, 0x96) = 8 / count;
    }
}

/* MECHANISM: The pinned state base supplies retail's long-lived $s1 role and exact 0x38 frame/save contract.
   Defaulting mode before each flags test, with the second default between the coordinate stores,
   reproduces the flags-load schedule, $a2 constant lifetime, and delayed $v0-to-$s0 result save. */
