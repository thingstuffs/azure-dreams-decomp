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
#define ARM_RRX(x, shift) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern u8 D_8008333C[];
extern s32 func_80033BC0();
extern u8 D_800E3548[];

s32 func_800F6598(void) {
    const s32 temp_a0_1 = 0x1F;
    const s32 temp_a0_2 = 0x20;
    const s32 temp_a0_3 = 0x21;
    register s32 temp_v1_value ASM_REG("$3");
    s32 temp_v0_value;
    u8 *temp_s1;
    s32 temp_s0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;
    void *temp_v1_ptr;
    register u8 *temp_early_ptr ASM_REG("$3");
    register s32 temp_return ASM_REG("$2");

    /* D_8008333C is the pointer-bearing global itself; the old draft
     * accidentally added 0x333c twice. */
    temp_s1 = D_8008333C;
    temp_s0 = *(s32 *)temp_s1;
    if (func_80033BC0(0xA2) != 0) {
    temp_v1_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0 = ((temp_a0_1 << temp_v1_value) * 6) + temp_s0 + 0xBA;
    M2C_FIELD(temp_v0, u16 *, 4) = (u16)(M2C_FIELD(temp_v0, u16 *, 4) & 0x7FFF);
    temp_v1_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_2 = ((temp_a0_1 << temp_v1_value) * 6) + temp_s0 + 0xC0;
    M2C_FIELD(temp_v0_2, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_2, u16 *, 4) & 0x7FFF);
    temp_v0_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_3 = ((temp_a0_1 << temp_v0_value) * 6) + temp_s0 + 0xC6;
    M2C_FIELD(temp_v0_3, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_3, u16 *, 4) & 0x7FFF);
    temp_v1_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_4 = ((temp_a0_2 << temp_v1_value) * 6) + temp_s0 + 0xBA;
    M2C_FIELD(temp_v0_4, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_4, u16 *, 4) & 0x7FFF);
    temp_v1_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_5 = ((temp_a0_2 << temp_v1_value) * 6) + temp_s0 + 0xC0;
    M2C_FIELD(temp_v0_5, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_5, u16 *, 4) & 0x7FFF);
    temp_v0_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_6 = ((temp_a0_2 << temp_v0_value) * 6) + temp_s0 + 0xC6;
    M2C_FIELD(temp_v0_6, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_6, u16 *, 4) & 0x7FFF);
    temp_v1_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_7 = ((temp_a0_3 << temp_v1_value) * 6) + temp_s0 + 0xBA;
    M2C_FIELD(temp_v0_7, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_7, u16 *, 4) & 0x7FFF);
    temp_v1_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v0_8 = ((temp_a0_3 << temp_v1_value) * 6) + temp_s0 + 0xC0;
    M2C_FIELD(temp_v0_8, u16 *, 4) = (u16)(M2C_FIELD(temp_v0_8, u16 *, 4) & 0x7FFF);
    temp_v0_value = M2C_FIELD(temp_s1, s16 *, 0x14);
    temp_v1_ptr = ((temp_a0_3 << temp_v0_value) * 6) + temp_s0 + 0xC6;
    M2C_FIELD(temp_v1_ptr, u16 *, 4) = (u16)(M2C_FIELD(temp_v1_ptr, u16 *, 4) & 0x7FFF);
    return 1;
    }
    temp_return = 0;
    ASM_KEEP(temp_return);
    temp_early_ptr = D_800E3548;
    ASM_KEEP(temp_early_ptr);
    temp_early_ptr[1] = 0;
    D_800E3548[0] = 0;
    return temp_return;
}
