#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80089474[];
void func_800478B8(void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 func_80064710(s32);
s32 func_80069EF8(void);
extern M2C_UNK D_800814A0;

void func_800D81D4(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    s32 temp_v1;
    M2C_UNK temp_v0;
    register u16 phase ASM_REG("$2");
    register void *p1 ASM_REG("$18") = arg1;
    register void *p2 ASM_REG("$17") = arg2;
    ASM_KEEP(p1);

    M2C_FIELD(arg0, u16 *, 0x48) = (s16) (M2C_FIELD(arg0, u16 *, 0x48) - 1);
    func_800478B8(p2);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x4C);
    if ((u32) temp_v1 >= 7U) {
        goto block_15;
    }
    (void)jt_keep; goto *D_80089474[temp_v1];
jt_c0:
    M2C_FIELD(arg0, u16 *, 0x48) = 0x10U;
    temp_v0 = (func_80069EF8() % 96) - 0x30;
    M2C_FIELD(p1, s32 *, 0x14) = (s32) ((s32) (temp_v0 << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x48));
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) ((s32) (func_80064710(0x900 - (temp_v0 * temp_v0)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x48));
    M2C_FIELD(arg0, u16 *, 0x18) = func_80069EF8();
    M2C_FIELD(arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x4C) + 1);
jt_c1: {
    register s32 pos ASM_REG("$2");
    register s32 speed ASM_REG("$3");
    register s32 color ASM_REG("$4");

    M2C_FIELD(p1, s32 *, 8) = (s32) (M2C_FIELD(p1, s32 *, 8) + M2C_FIELD(p1, s32 *, 0x14));
    ASM_SCHED_BARRIER();
    pos = M2C_FIELD(arg0, s32 *, 0x1C);
    speed = M2C_FIELD(arg0, s32 *, 0x28);
    ASM_SCHED_BARRIER();
    color = 0x40000;
    ASM_KEEP_NV(color);
    ASM_KEEP_NV(pos);
    ASM_KEEP_NV(speed);
    M2C_FIELD(arg0, s32 *, 0x1C) = pos + speed;
    pos = M2C_FIELD(p2, s32 *, 0xC);
    ASM_SCHED_BARRIER();
    color |= 0x404;
    M2C_FIELD(p2, s32 *, 0xC) = pos + color;
    speed = M2C_FIELD(arg0, s16 *, 0x48);
    pos = 0x20 - speed;
    speed = M2C_FIELD(arg0, s16 *, 0x4A);
    ASM_SCHED_BARRIER();
    pos <<= 3;
    ASM_KEEP_NV(pos);
    ASM_KEEP_NV(speed);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + (pos * speed));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) >= 0) {
        goto block_15;
    }
}
    phase = M2C_FIELD(arg0, u16 *, 0x4C);
    M2C_FIELD(arg0, u16 *, 0x48) = 0x14U;
    goto block_13;
jt_c2:
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + (M2C_FIELD(arg0, s16 *, 0x4A) * 0x140));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) > 0) {
        goto block_15;
    }
    phase = M2C_FIELD(arg0, u16 *, 0x4C);
    M2C_FIELD(arg0, u16 *, 0x48) = 0x1CU;
    goto block_13;
jt_c3:
    M2C_FIELD(p1, s32 *, 8) = (s32) (M2C_FIELD(p1, s32 *, 8) - ((s32) M2C_FIELD(p1, s32 *, 0x14) >> 1));
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) - ((s32) M2C_FIELD(arg0, s32 *, 0x28) >> 1));
    M2C_FIELD(p2, s32 *, 0xC) = (s32) (M2C_FIELD(p2, s32 *, 0xC) + 0x30303);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + ((((0x1C - (s16) M2C_FIELD(arg0, u16 *, 0x48)) * 8) + 0x140) * M2C_FIELD(arg0, s16 *, 0x4A)));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x48) > 0) {
        goto block_15;
    }
    phase = M2C_FIELD(arg0, u16 *, 0x4C);
    M2C_FIELD(arg0, u16 *, 0x48) = 0U;
    goto block_13;
jt_c4:
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + ((((0 - (s16) M2C_FIELD(arg0, u16 *, 0x48)) * 0x10) + 0x1E0) * M2C_FIELD(arg0, s16 *, 0x4A)));
    M2C_FIELD(p2, s32 *, 0xC) = (s32) (M2C_FIELD(p2, s32 *, 0xC) + 0x40404);
    if ((u8) M2C_FIELD(p2, s32 *, 0xC) < 0xF1U) {
        goto block_15;
    }
    M2C_FIELD(p2, s16 *, 0x10) = 0x60;
    M2C_FIELD(p1, s16 *, 0x16) = (s16) (0 - (func_80069EF8() & 3));
    goto block_12;
jt_c5:
    M2C_FIELD(p1, s32 *, 8) = (s32) (M2C_FIELD(p1, s32 *, 8) + M2C_FIELD(p1, s32 *, 0x14));
    M2C_FIELD(p1, s32 *, 0x14) = (s32) (M2C_FIELD(p1, s32 *, 0x14) - ((func_80069EF8() & 0xFFF) << 6));
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) - 0x8000);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + ((((0 - (s16) M2C_FIELD(arg0, u16 *, 0x48)) * 0x10) + 0x1E0) * M2C_FIELD(arg0, s16 *, 0x4A)));
    M2C_FIELD(p2, s32 *, 0xC) = (s32) (M2C_FIELD(p2, s32 *, 0xC) + 0xFFE7E7E8);
    if ((u8) M2C_FIELD(p2, s32 *, 0xC) >= 0x18U) {
        goto block_15;
    }
block_12:
    phase = M2C_FIELD(arg0, u16 *, 0x4C);
block_13:
    ASM_KEEP_NV(phase);
    M2C_FIELD(arg0, s16 *, 0x4C) = (s16) (phase + 1);
    goto block_15;
jt_c6:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
block_15:
    M2C_FIELD(p1, s16 *, 2) = (s16) (M2C_FIELD(arg0, u16 *, 0xC) + ((s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x18)) * M2C_FIELD(arg0, s16 *, 0x1E)) >> 0xC));
    M2C_FIELD(p1, s16 *, 6) = (s16) (M2C_FIELD(arg0, u16 *, 0xE) + ((s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x18)) * M2C_FIELD(arg0, s16 *, 0x1E)) >> 0xC));
    return;
}
