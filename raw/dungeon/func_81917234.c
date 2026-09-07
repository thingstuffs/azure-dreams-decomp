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

extern s32 D_800814A0[3];
extern s32 D_800DEDB0[3];
M2C_UNK func_80024600();
s32 func_8003DB94();
s32 func_800644B8();
s32 func_80064584();
s32 rand();

void func_80024A34(void *arg0, void *arg1, void *arg2) {
    s16 temp_s1;
    s16 temp_s2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s32 *flags_base;
    void **var_a1;
    void *temp_a0;

    var_a2 = 0;
    flags_base = (s32 *)(u32)0x80080000;
    var_a1 = (void **)arg0;
    do {
        if ((temp_a0 = var_a1[5]) != NULL) {
            u16 node_flags;
            s32 global_flags;
            node_flags = M2C_FIELD(temp_a0, u16 *, 0x1E);
            global_flags = flags_base[0x528];
            node_flags = (u16)(node_flags | 0x8000);
            global_flags = global_flags | 0x8000;
            M2C_FIELD(temp_a0, u16 *, 0x1E) = node_flags;
            flags_base[0x528] = global_flags;
        }
        var_a2 += 1;
        var_a1 += 1;
    } while (var_a2 < 3);
    func_8003DB94(arg2, D_800DEDB0, 0, flags_base);
    M2C_FIELD(arg2, u8 *, 0xE) = 0xC0;
    M2C_FIELD(arg2, u8 *, 0xD) = 0xC0;
    M2C_FIELD(arg2, u8 *, 0xC) = 0xC0;
    M2C_FIELD(arg2, s16 *, 0x1E) = 0x800;
    M2C_FIELD(arg2, s16 *, 0x1C) = 0x800;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
    M2C_FIELD(arg2, u16 *, 0x10) = (u16) (M2C_FIELD(arg2, u16 *, 0x10) | 0x20);
    var_v0 = rand();
    temp_v0 = var_v0;
    if (temp_v0 < 0) {
        var_v0 = (s32) (temp_v0 + 0xFFF);
    }
    var_v0 >>= 0xC;
    M2C_FIELD(arg2, s16 *, 0x1A) = (s16) (temp_v0 - (var_v0 << 0xC));
    temp_v0_2 = rand();
    var_v0_2 = temp_v0_2;
    if (temp_v0_2 < 0) {
        var_v0_2 = temp_v0_2 + 0xFFF;
    }
    var_v0_2 >>= 0xC;
    temp_s2 = temp_v0_2 - (var_v0_2 << 0xC);
    temp_v0_3 = rand();
    var_s1 = temp_v0_3;
    if (temp_v0_3 < 0) {
        var_s1 = temp_v0_3 + 0xFFF;
    }
    temp_s1 = temp_v0_3 - ((var_s1 >> 0xC) << 0xC);
    temp_s0 = func_800644B8(temp_s2);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + ((temp_s0 >> 4) * (func_800644B8(temp_s1) >> 4) * 0x10));
    temp_s0_2 = func_800644B8(temp_s2);
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + ((temp_s0_2 >> 4) * (func_80064584(temp_s1) >> 4) * 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + ((func_80064584(temp_s2) >> 4) << 0xC));
    func_80024600(arg0, arg1);
}
