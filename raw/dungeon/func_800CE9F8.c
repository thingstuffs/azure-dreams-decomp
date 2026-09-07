#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef void (*Func4)(void *, void *, void *, void *);
extern u16 D_80083462[5];
extern Func4 D_800E22E0[];
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_800BCB04();

void func_800D4158(void *arg0, void *arg1, void *arg2) {
    void *s0 = arg0;
    u16 flags;
    u32 flags32;
    s16 dist16;
    s32 raw;
    s16 phase;
    s32 color;

    if (*D_80083462 & 0x2000) {
        M2C_FIELD(s0, u8 *, 0x71) = M2C_FIELD(s0, u8 *, 0x71) & 0x7f;
        goto epilogue;
    }
    if (M2C_FIELD(s0, Func4 *, 0x8c) != NULL) {
        ((Func4)M2C_FIELD(s0, Func4 *, 0x8c))(s0, arg1, arg2, s0);
    }
    D_800E22E0[M2C_FIELD(s0, u8 *, 0x9a)](s0, arg1, arg2, s0);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
            func_800478B8(arg2);
        }
    }
    M2C_FIELD(arg1, s32 *, 0) += M2C_FIELD(arg1, s32 *, 0xc);
    M2C_FIELD(arg1, s32 *, 4) += M2C_FIELD(arg1, s32 *, 0x10);
    flags = M2C_FIELD(arg0, u16 *, 0x98);
    if (flags & 8) {
        M2C_FIELD(arg0, u8 *, 0x9d) = 0;
        goto step_done;
    }
    M2C_FIELD(arg1, s32 *, 0x14) += M2C_FIELD(arg0, s8 *, 0x9d) * 0x14000;
    M2C_FIELD(arg0, s8 *, 0x9d) = M2C_FIELD(arg0, u8 *, 0x9d) + 1;
step_done:
    M2C_FIELD(arg0, s32 *, 0x90) += M2C_FIELD(arg1, s32 *, 0x14);
    if (M2C_FIELD(arg0, u16 *, 0x98) & 4) {
        goto clear_flag;
    }
    raw = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6),
                        (s16)(M2C_FIELD(s0, u16 *, 0x88) - 0x20));
    dist16 = (s16)raw;
    if (dist16 >= 0x200) {
        goto clear_flag;
    }
    if (M2C_FIELD(arg0, s16 *, 0x92) + M2C_FIELD(s0, s16 *, 0x88) < dist16) {
        (void)*(volatile u16 *)((s8 *)arg0 + 0x98);
        goto flag_check;
    }
    if (dist16 >= M2C_FIELD(s0, s16 *, 0x88)) {
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
    } else {
        M2C_FIELD(arg0, s16 *, 0x92) = raw - M2C_FIELD(s0, u16 *, 0x88);
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(s0, s32 *, 0x1c) |= 0x08000000;
    M2C_FIELD(arg0, s8 *, 0x9d) = 0;
flag_check:
    flags32 = M2C_FIELD(s0, u32 *, 0x1c);
    if (flags32 & 0x40000000) {
        M2C_FIELD(s0, u32 *, 0x1c) = flags32 & 0xbfffffff;
        raw = func_800BCB04(
        (M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20,
        (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20,
            (s16)(M2C_FIELD(s0, u16 *, 0x88) - 0x20));
        M2C_FIELD(arg0, s16 *, 0x92) += M2C_FIELD(s0, u16 *, 0x88) - raw;
        M2C_FIELD(s0, s16 *, 0x88) = raw;
    }
    goto angle_start;
clear_flag:
    M2C_FIELD(s0, u32 *, 0x1c) &= 0xf7ffffff;
angle_start:
    M2C_FIELD(arg1, s16 *, 0xa) = M2C_FIELD(s0, u16 *, 0x88) +
                                   M2C_FIELD(arg0, s16 *, 0x92);
angle_done:
    phase = M2C_FIELD(arg0, u16 *, 0x9e);
    phase++;
    phase %= 96;
    M2C_FIELD(arg0, u16 *, 0x9e) = phase;
    if ((s16)phase < 0x19) {
        color = (func_800644B8((s16)phase * 0x55) >> 4) * 0x60;
        color = (color >> 8) + 0x80;
        M2C_FIELD(arg2, u8 *, 0xe) = color;
        M2C_FIELD(arg2, u8 *, 0xd) = color;
        M2C_FIELD(arg2, u8 *, 0xc) = color;
    } else {
        M2C_FIELD(arg2, u8 *, 0xe) = 0x80;
        M2C_FIELD(arg2, u8 *, 0xd) = 0x80;
        M2C_FIELD(arg2, u8 *, 0xc) = 0x80;
    }
    M2C_FIELD(arg2, u16 *, 0x14) |= 0x40;
    M2C_FIELD(s0, u32 *, 0x1c) |= 0x200;
epilogue:
    return;
}
