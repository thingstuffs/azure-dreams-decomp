#include "common.h"

typedef unsigned long long u64;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_80083460;

extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

s32 func_8016B954(void *arg0, s32 arg1, void *arg2, void *arg3) {
    volatile u64 frame_pad;
    s32 result;
    s32 *flags;

    FIELD(arg3, u8, 0x71) &= 0x7F;
    flags = &D_80083460;

    if (FIELD(flags, u16, 2) & 0x2000) {
        goto shared_failure;
    }

    result = func_800A04F0(
        arg3,
        FIELD(arg2, u8, 0x24),
        FIELD(arg2, u8, 0x25),
        FIELD(arg3, s16, 0x2A));

    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }

    if (FIELD(flags, u16, 2) & 0x2000) {
        return -1;
    }

    if (!(FIELD(arg3, u16, 0x46) & 0x8000) &&
        (FIELD(flags, u16, 2) & 8)) {
        return -1;
    }

    if ((u32)(((0 - func_800A0134(result, arg3)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }

    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);

    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto success;
    }

shared_failure:
    return -1;

success:
    FIELD(arg0, s8, 0x9A) = 0x11;
    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg3, u8, 0x84) = 0x80;
    FIELD(arg3, s8, 0x85) = 32;
    FIELD(arg3, u8, 0x6D)--;

    func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile u64 frame object plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   A shared mid-function failure block restores both branch targets and polarity;
   explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */
