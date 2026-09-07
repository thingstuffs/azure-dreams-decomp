/* cfail-repair: tf7-phase1-cache-v3 */
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

int func_80049E6C();
s32 func_8004DC14();
s32 func_800AE4E4();
M2C_UNK func_800AE854();
extern u8 D_80077E84[12];
extern u8 D_80077EF0[12];
extern u8 D_80077EFC[12];

void func_800AECA4(void *arg0) {
    s16 var_s2;
    s16 var_s4;
    s32 temp_s0;
    s32 var_s3;

    *M2C_FIELD(M2C_FIELD(arg0, void **, 0xD8), M2C_UNK ***, 4) = &D_80077E84;
    var_s3 = 0;
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0xD8), s32 **, 0) = func_80049E6C(M2C_FIELD(arg0, s32 *, 0x28));
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0xD8), s32 **, 0), void **, 4), s16 *, 0xA) = (s16) ((M2C_FIELD(arg0, s32 *, 0x28) * 8) + 2);
    if (M2C_FIELD(arg0, s32 *, 0x28) > 0) {
        u8 *var_s6 = D_80077EF0;
        u8 *var_s5 = D_80077EFC;
        var_s4 = 0x82;
        var_s2 = 0xA;
        do {
            temp_s0 = var_s3 * 4;
            {
                register u8 *base ASM_REG("$2") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                M2C_FIELD(M2C_FIELD(M2C_FIELD(base, void **, 0x38), void **, 4), s16 *, 0xA) = var_s2;
            }
            {
                register u8 *base ASM_REG("$2") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                *M2C_FIELD(base, void ***, 0x38) = arg0 + 0x40;
            }
            {
                register u8 *base ASM_REG("$2") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                M2C_FIELD(M2C_FIELD(M2C_FIELD(base, void **, 8), void **, 4), s16 *, 0xA) = var_s2;
            }
            {
                register u8 *base ASM_REG("$2") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                *M2C_FIELD(base, M2C_UNK ***, 8) = var_s6;
            }
            {
                register u8 *base ASM_REG("$2") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                M2C_FIELD(M2C_FIELD(M2C_FIELD(base, void **, 0x20), void **, 4), s16 *, 0xA) = var_s2;
            }
            {
                register u8 *base ASM_REG("$2") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                *M2C_FIELD(base, M2C_UNK ***, 0x20) = var_s5;
            }
            var_s2 += 0x10;
            {
                s32 result = func_8004DC14(func_800AE4E4(*(M2C_FIELD(arg0, u8 **, 0x38) + var_s3)), 1);
                register u8 *base ASM_REG("$3") = M2C_FIELD(arg0, void **, 0xD8);
                base = (u8 *)(temp_s0 + (s32)base);
                *M2C_FIELD(base, s32 **, 0x50) = result;
            }
            var_s3 += 1;
            temp_s0 = temp_s0 + M2C_FIELD(arg0, void **, 0xD8);
            M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x50), void **, 4), s16 *, 0xA) = var_s4;
            var_s4 += 0x10;
        } while (var_s3 < M2C_FIELD(arg0, s32 *, 0x28));
    }
    M2C_FIELD(arg0, s32 *, 4) = 1;
    M2C_FIELD(arg0, s32 *, 8) = 1;
    func_800AE854(arg0);
}
