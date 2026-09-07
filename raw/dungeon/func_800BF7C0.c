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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern void *D_800893E4[];
s32 func_800644B8();
s32 func_80064584();
s32 func_80069EF8();
M2C_UNK func_800A56E0();
extern void func_800C5254(void) __attribute__((noreturn));
extern void func_800C5344(void) __attribute__((noreturn));
extern void func_800C539C(void) __attribute__((noreturn));
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083780;

void func_800C4F20(void *arg0, void *arg1, void *arg2_in) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17 };
    register void *arg2 ASM_REG("$20") = arg2_in;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_a0_6;
    s16 temp_a1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s32 temp_v1;
    s16 temp_v1_5;
    s16 var_v1;
    s32 temp_a0_3;
    s32 temp_a1_3;
    s32 temp_s0;
    s32 temp_v0_8;
    s32 var_s0;
    u16 temp_a0;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1_2;
    u16 temp_v1_3;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u16 temp_v1_8;
    void *temp_a0_7;
    void *temp_a1_2;
    void *temp_a1_4;
    void *temp_s3;
    void *temp_v1_4;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x28);
    if ((u32) temp_v1 >= 0x12U) {
        goto block_24;
    }
    (void)jt_keep; goto *D_800893E4[(u32)(temp_v1)];
jt_c0:
    temp_a1 = M2C_FIELD(arg0, s16 *, 0x2A);
    if (temp_a1 == 0) {
        goto block_4;
    }
    temp_a0 = M2C_FIELD(arg2, u16 *, 0x1E);
    temp_a0_2 = temp_a0 + ((s32) (0x1000 - temp_a0) / temp_a1);
    temp_v0 = M2C_FIELD(arg2, u16 *, 0x20);
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_a0_2;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_a0_2;
    M2C_FIELD(arg2, u16 *, 0x20) = (u16) (temp_v0 + ((s32) (0x1000 - temp_v0) / (s16) M2C_FIELD(arg0, s16 *, 0x2A)));
    temp_a1_2 = M2C_FIELD(arg0, void **, 0x20);
    temp_v1_2 = M2C_FIELD(temp_a1_2, u16 *, 0x1E);
    temp_v1_3 = temp_v1_2 + ((s32) (0x400 - temp_v1_2) / (s16) M2C_FIELD(arg0, s16 *, 0x2A));
    M2C_FIELD(temp_a1_2, u16 *, 0x1E) = temp_v1_3;
    M2C_FIELD(temp_a1_2, u16 *, 0x1C) = temp_v1_3;
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x32) - ((s16) M2C_FIELD(arg0, s16 *, 0x32) / (s16) M2C_FIELD(arg0, s16 *, 0x2A)));
block_4:
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x2A) - 1;
    M2C_FIELD(arg0, s16 *, 0x2A) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_24;
    }
    M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
    M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
    M2C_FIELD(arg2, u16 *, 0x20) = 0x1000U;
    {
        register void *tail_ptr ASM_REG("$3") = M2C_FIELD(arg0, void **, 0x20);
        M2C_FIELD(tail_ptr, u16 *, 0x1E) = 0x800U;
        M2C_FIELD(tail_ptr, u16 *, 0x1C) = 0x800U;
    }
    {
        register u16 tail_v0 ASM_REG("$2");
        register u32 tail_v1 ASM_REG("$3");
        tail_v0 = M2C_FIELD(arg0, u16 *, 0x28);
        ASM_SCHED_BARRIER();
        tail_v1 = 0x20;
        ASM_KEEP(tail_v1);
        ASM_KEEP(tail_v0);
        M2C_FIELD(arg0, s16 *, 0x32) = 0;
        func_800C5254();
    }
jt_c1:
    temp_v0_8 = func_80064584(M2C_FIELD(arg0, s16 *, 0x2E));
    temp_s3 = &D_80083780;
    temp_s0 = M2C_FIELD(temp_s3, s16 *, 2) + (temp_v0_8 >> 6);
    temp_a1_3 = M2C_FIELD(temp_s3, s16 *, 6) + (func_800644B8(M2C_FIELD(arg0, s16 *, 0x2E)) >> 6);
    var_s0 = temp_s0 - M2C_FIELD(arg1, s16 *, 2);
    if (var_s0 >= 0) {
        goto block_8;
    }
    var_s0 += 3;
block_8:
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + (var_s0 >> 2));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (temp_a1_3 - M2C_FIELD(arg1, s16 *, 6)) / 4));
    temp_v0_8 = (func_800644B8(M2C_FIELD(arg0, s16 *, 0x2C) << 5, temp_a1_3) >> 6) + 0x40;
    temp_a0_3 = M2C_FIELD(temp_s3, s16 *, 0xA) - M2C_FIELD(arg1, s16 *, 0xA);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (temp_a0_3 - temp_v0_8) / 4));
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2E) + 0x40 + (func_80069EF8(temp_a0_3) & 0x1F));
    temp_a0_4 = M2C_FIELD(arg0, s16 *, 0x36);
    if (temp_a0_4 == 0) {
        goto block_24;
    }
    temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x2A) - 1;
    M2C_FIELD(arg0, s16 *, 0x2A) = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_24;
    }
    temp_v1 = temp_a0_4;
    if (temp_v1 == 1) {
        goto block_16;
    }
    if (temp_v1 == 3) {
        goto block_16;
    }
    M2C_FIELD(arg0, s16 *, 0x2A) = 0x20;
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x28) + 0x10);
    func_800A56E0(0x518);
    func_800C539C();
jt_c2:
    temp_a0_5 = M2C_FIELD(arg0, s16 *, 0x2A);
    if (temp_a0_5 == 0) {
        goto block_15;
    }
    {
        register s32 c2_v0 ASM_REG("$2");
        register s32 c2_v1 ASM_REG("$3");

        c2_v0 = (s32) M2C_FIELD(arg0, void **, 0x20);
        c2_v1 = M2C_FIELD((void *) c2_v0, u8 *, 0x24);
        ASM_KEEP(c2_v1);
        c2_v0 = M2C_FIELD(arg1, s16 *, 2);
        ASM_KEEP(c2_v0);
        c2_v1 <<= 6;
        c2_v0 -= 0x20;
        ASM_KEEP(c2_v0);
        c2_v1 -= c2_v0;
        ASM_KEEP(c2_v1);
        c2_v1 /= temp_a0_5;
        ASM_KEEP(c2_v1);
        ASM_MEM_BARRIER();
        M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + c2_v1);
    }
    {
        register s32 c2_v0 ASM_REG("$2");
        register s32 c2_v1 ASM_REG("$3");
        register s32 c2_a0 ASM_REG("$4");

        c2_v0 = (s32) M2C_FIELD(arg0, void **, 0x20);
        c2_a0 = M2C_FIELD(arg0, s16 *, 0x2A);
        c2_v1 = M2C_FIELD((void *) c2_v0, u8 *, 0x25);
        ASM_KEEP(c2_v1);
        c2_v0 = M2C_FIELD(arg1, s16 *, 6);
        ASM_KEEP(c2_v0);
        c2_v1 <<= 6;
        c2_v0 -= 0x20;
        ASM_KEEP(c2_v0);
        c2_v1 -= c2_v0;
        ASM_KEEP(c2_v1);
        c2_v1 /= c2_a0;
        ASM_KEEP(c2_v1);
        ASM_MEM_BARRIER();
        M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + c2_v1);
    }
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s16 *, 0x88) - M2C_FIELD(arg1, s16 *, 0xA)) / (s16) M2C_FIELD(arg0, s16 *, 0x2A)));
block_15:
    temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0x2A) - 1;
    M2C_FIELD(arg0, s16 *, 0x2A) = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_24;
    }
block_16:
    var_v1 = 0x10;
block_17:
    M2C_FIELD(arg0, s16 *, 0x2A) = var_v1;
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x28) + 1);
    goto block_24;
jt_c3:
    temp_v1_5 = M2C_FIELD(arg0, s16 *, 0x2A);
    if (temp_v1_5 == 0) {
        goto block_22;
    }
    temp_v0_5 = M2C_FIELD(arg2, u16 *, 0x1E);
    temp_v0_6 = temp_v0_5 - ((s32) temp_v0_5 / temp_v1_5);
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_6;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_6;
    temp_v1_6 = M2C_FIELD(arg2, u16 *, 0x20);
    M2C_FIELD(arg2, u16 *, 0x20) = (u16) (temp_v1_6 + ((s32) (0x2000 - temp_v1_6) / (s16) M2C_FIELD(arg0, s16 *, 0x2A)));
    temp_a1_4 = M2C_FIELD(arg0, void **, 0x20);
    temp_v1_7 = M2C_FIELD(temp_a1_4, u16 *, 0x1E);
    temp_v1_8 = temp_v1_7 + ((s32) (0x1000 - temp_v1_7) / (s16) M2C_FIELD(arg0, s16 *, 0x2A));
    M2C_FIELD(temp_a1_4, u16 *, 0x1E) = temp_v1_8;
    M2C_FIELD(temp_a1_4, u16 *, 0x1C) = temp_v1_8;
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x32) + ((s32) (0x400 - M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x2A)));
    func_800C5344();
jt_c17:
    temp_a0_6 = M2C_FIELD(arg0, s16 *, 0x2A);
    if (temp_a0_6 == 0) {
        goto block_22;
    }
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (-0x400 - M2C_FIELD(arg1, s16 *, 0xA)) / temp_a0_6));
block_22:
    temp_v0_7 = (u16) M2C_FIELD(arg0, s16 *, 0x2A) - 1;
    M2C_FIELD(arg0, s16 *, 0x2A) = temp_v0_7;
    if ((temp_v0_7 << 0x10) > 0) {
        goto block_24;
    }
    temp_a0_7 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(temp_a0_7, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0_7, s32 *, 0x14) & 0xFFEFFFFF);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    return;
jt_c4:
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c16:
block_24:
    if (!(M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x14) & 0x100000)) {
        goto block_26;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u16 *, 2) = (u16) M2C_FIELD(arg1, s16 *, 2);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u16 *, 6) = (u16) M2C_FIELD(arg1, s16 *, 6);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x1C), u16 *, 0xA) = (u16) M2C_FIELD(arg1, s16 *, 0xA);
block_26:
    M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) - 0x80);
    return;
}
