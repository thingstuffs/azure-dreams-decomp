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

void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_800644B8();
s32 func_80064584();
extern M2C_UNK D_80024888;
extern u8 D_80020000[];
extern M2C_UNK D_800269EC;
extern M2C_UNK D_80045340;

void *func_80024938(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s5;
    register s32 temp_v1_color ASM_REG("$3");
    s32 var_s4;
    register void *temp_a0 ASM_REG("$4");
    void *temp_s2;
    void *temp_v0;
    void *temp_v1;
    u8 *page_base;

    var_s4 = 0;
    temp_s5 = arg3 + 0x400;
    do {
        temp_v0 = func_8003FC64(0x202);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024888;
            func_8004491C(temp_v0, &D_80045340);
            temp_s2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_s2, s16 *, 2) = arg0;
            M2C_FIELD(temp_s2, s16 *, 6) = arg1;
            M2C_FIELD(temp_s2, s16 *, 0xA) = arg2;
            temp_s1 = var_s4 << 7;
            temp_s0 = func_80064584(temp_s5);
            M2C_FIELD(temp_s2, s32 *, 0xC) = (s32) ((s32) (temp_s0 * func_80064584(temp_s1)) >> 6);
            temp_s0_2 = func_800644B8(temp_s5);
            M2C_FIELD(temp_s2, s32 *, 0x10) = (s32) ((s32) (temp_s0_2 * func_80064584(temp_s1)) >> 6);
            M2C_FIELD(temp_s2, s32 *, 0x14) = (s32) (func_800644B8(temp_s1) << 6);
            temp_v1_color = 0x808080;
            ASM_KEEP(temp_v1_color);
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x400;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x400;
            page_base = (u8 *) 0x80020000;
            ASM_KEEP(page_base);
            ASM_SCHED_BARRIER();
            M2C_FIELD(temp_a0, s32 *, 0xC) = temp_v1_color;
            temp_v1_color = M2C_FIELD(temp_a0, u16 *, 0x14);
            M2C_FIELD(temp_a0, M2C_UNK **, 8) = page_base + 0x69EC;
            ASM_SCHED_BARRIER();
            M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (temp_v1_color | 0xC);
            ASM_KEEP_NV(temp_a0);
            temp_v1 = temp_v0 + 0x20;
            M2C_FIELD(temp_v1, s16 *, 0x30) = 0xC;
            M2C_FIELD(temp_v1, u16 *, 0x36) = (u16) arg3;
        }
        var_s4 += 1;
    } while (var_s4 < 0x20);
    return temp_v0;
}
