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

extern u8 D_80700000[];

void func_8087514C(void) {
    register s32 zero ASM_REG("$0");
    register s32 var_a2 ASM_REG("$6");
    register s32 var_t1 ASM_REG("$9");
    register s16 *var_t0 ASM_REG("$8");

    ASM_UNDEF(zero);
    var_a2 = zero | 1;
    ASM_UNDEF(zero);
    var_t1 = zero | 1;
    var_t0 = (s16 *)(D_80700000 + 0xBAE);
    ASM_KEEP(var_a2);
    ASM_KEEP(var_t1);
    ASM_KEEP(var_t0);
    do {
        register s32 temp_a1 ASM_REG("$5");
        register s32 var_v0 ASM_REG("$2");
        register s32 var_a3 ASM_REG("$7");
        s32 temp_a0_offset;
        s32 temp_word;
        s32 temp_word_2;
        register s32 *temp_a0 ASM_REG("$4");

        temp_a1 = *var_t0;
        var_a3 = var_a2 << 1;
        ASM_KEEP(temp_a1);
        ASM_KEEP(var_a3);
        var_v0 = temp_a1;
        if (temp_a1 < 0) {
            var_v0 = temp_a1 + 0x1F;
        }
        var_v0 >>= 5;
        temp_a0_offset = var_v0 << 2;
        var_v0 = temp_a1 - (var_v0 << 5);
        {
            register s32 page ASM_REG("$3");
            page = 0x80700000;
            ASM_KEEP(page);
            page = *(s32 *)(page + 0x1968);
            ASM_KEEP(page);
            var_v0 = var_t1 << var_v0;
            ASM_KEEP(temp_a0_offset);
            temp_a0_offset = temp_a0_offset + page;
            temp_a0 = (s32 *)temp_a0_offset;
            ASM_KEEP(temp_a0);
        }
        temp_word = *temp_a0;
        var_v0 = ~var_v0;
        var_v0 = var_v0 & temp_word;
        *temp_a0 = var_v0;

        temp_a1 = *(s16 *)(D_80700000 + var_a3 + 0xBA4);
        var_v0 = temp_a1;
        if (temp_a1 < 0) {
            var_v0 = temp_a1 + 0x1F;
        }
        var_a2 += 1;
        var_v0 >>= 5;
        temp_a0_offset = var_v0 << 2;
        var_v0 = temp_a1 - (var_v0 << 5);
        {
            register s32 page ASM_REG("$3");
            page = 0x80700000;
            ASM_KEEP(page);
            page = *(s32 *)(page + 0x1968);
            ASM_KEEP(page);
            var_v0 = var_t1 << var_v0;
            ASM_KEEP(temp_a0_offset);
            temp_a0_offset = temp_a0_offset + page;
            temp_a0 = (s32 *)temp_a0_offset;
            ASM_KEEP(temp_a0);
        }
        temp_word_2 = *temp_a0;
        ASM_KEEP(temp_word_2);
        var_v0 = ~var_v0;
        var_v0 = var_v0 & temp_word_2;
        *temp_a0 = var_v0;
        var_t0 += 1;
    } while (var_a2 < 4);
}
