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

extern s32 func_8004A658();
extern M2C_UNK func_800AF554();

void func_800AF520(void *arg0) {
    s32 *temp_v0_2;
    void *temp_a0;
    register s32 temp_s1;
    s32 temp_index;
    register s32 temp_product ASM_REG("$2");
    s32 temp_result;
    register s32 temp_cond ASM_REG("$2");
    register s32 var_s0 ASM_REG("$16");
    register s32 cleanup_offset ASM_REG("$2");
    register s32 var_v0 ASM_REG("$2");
    void *temp_v0;
    s32 *temp_v1;
    register void *temp_addr ASM_REG("$2");
    register void *temp_struct ASM_REG("$3");
    register void *ctx ASM_REG("$18") = arg0;

    ASM_KEEP(ctx);
    temp_index = M2C_FIELD(M2C_FIELD(ctx, void **, 0), s32 *, 0x10);
    ASM_KEEP(temp_index);
    ASM_MEM_BARRIER();
    var_s0 = 6;
    ASM_KEEP(var_s0);
    temp_product = temp_index << 2;
    temp_product += temp_index;
    temp_s1 = temp_product << 1;
    ASM_MEM_BARRIER();
    temp_struct = M2C_FIELD(ctx, void **, 0);
    temp_cond = temp_s1 < M2C_FIELD(temp_struct, s32 *, 0x1C);
    ASM_KEEP(temp_cond);
    if (temp_cond == 0) {
        goto block_5;
    }
    temp_product = temp_s1 << 2;
    temp_addr = (void *)(temp_product + M2C_FIELD(temp_struct, s32 *, 0x20));
    ASM_KEEP(temp_addr);
    temp_v0 = *(void **)temp_addr;
    temp_result = func_8004A658(M2C_FIELD(temp_v0, u8 *, 1), M2C_FIELD(temp_v0, u8 *, 0));
    temp_s1 += 1;
    ASM_USE(temp_s1);
    temp_a0 = (void *)M2C_FIELD(ctx, s32 *, 0xA8);
    temp_v1 = *((s32 **)((var_s0 * 4) + (u8 *)temp_a0));
    var_s0 += 1;
    *temp_v1 = temp_result;
    ASM_SCHED_BARRIER();
    var_v0 = var_s0 < 0x10;
    if (var_v0 == 0) {
        goto block_5;
    }
    func_800AF554(temp_a0);
    return;
block_4:
    cleanup_offset = var_s0 << 2;
    temp_addr = (void *)(cleanup_offset + M2C_FIELD(ctx, s32 *, 0xA8));
    ASM_KEEP(temp_addr);
    temp_v0_2 = *(s32 **)temp_addr;
    var_s0 += 1;
    *temp_v0_2 = 0;
block_5:
    var_v0 = var_s0 < 0x10;
block_6:
    if (var_v0 != 0) {
        goto block_4;
    }
    return;
}
