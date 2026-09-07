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

extern s16 D_80027156;
extern s16 D_80027158;
extern s16 D_8002715A;
extern u16 D_8002715C;
extern s8 D_8006CCD8[];
extern s8 D_8006CCE8[];
extern s8 D_80083160[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

void func_80025C94(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0_2;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s8 temp_a0;
    s8 temp_v0;
    s8 temp_v1;
    u16 temp_s4;
    u16 temp_counter;
    u8 temp_v0_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    u16 *temp_table;
    register void *temp_a3 ASM_REG("$7");
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;
    void *temp_s5;
    void *var_a0;

    temp_counter = D_8002715C;
    var_a0 = arg0;
    temp_a3 = var_a0;
    temp_s2 = arg1;
    temp_s1 = arg2;
    temp_s0 = temp_a3;
    D_8002715C = temp_counter + 1;
    temp_s5 = D_80083160;
    temp_v1 = M2C_FIELD(temp_s0, s8 *, 0x72);
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto block_state0;
        }
        M2C_FIELD(temp_a3, s16 *, 0x96) = 0;
        goto block_epilogue;
    }
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_state3;
    }
    M2C_FIELD(temp_a3, s16 *, 0x96) = 0;
    goto block_epilogue;
block_state0:
    M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s1, u8 *, 0xE) = 0U;
    M2C_FIELD(temp_s1, u8 *, 0xD) = 0U;
    M2C_FIELD(temp_s1, u8 *, 0xC) = 0U;
    M2C_FIELD(temp_s0, s8 *, 0x73) = 8;
    M2C_FIELD(temp_s0, s16 *, 0x2A) = 0x400;
    temp_table = (u16 *)0x80010000;
    temp_v1_2 = (M2C_FIELD((s8 *)temp_table + (M2C_FIELD(temp_s0, s16 *, 0x6A) * 2), u16 *, 0x2094) + 2) & 7;
    M2C_FIELD(temp_s2, u16 *, 2) = D_800DCEAC[temp_v1_2];
    temp_v0_3 = D_800DCEBC[temp_v1_2];
    M2C_FIELD(temp_s2, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s2, u16 *, 6) = temp_v0_3;
    M2C_FIELD(temp_s1, u8 *, 0x24) = (u8) (D_8006CCD8[temp_v1_2 * 2] + 1);
    M2C_FIELD(temp_s1, u8 *, 0x25) = (u8) (D_8006CCE8[temp_v1_2 * 2] + 1);
    M2C_FIELD(temp_s0, s8 *, 0x72) = (s8) ((u8) M2C_FIELD(temp_s0, s8 *, 0x72) + 1);
block_10:
    var_a0 = (void *) M2C_FIELD(temp_s0, s8 *, 0x73);
    if (var_a0 != NULL) {
        temp_v1_5 = M2C_FIELD(temp_s1, u8 *, 0xE);
        temp_v1_6 = temp_v1_5 + ((s32) (0x80 - temp_v1_5) / (s32) var_a0);
        M2C_FIELD(temp_s1, u8 *, 0xE) = temp_v1_6;
        M2C_FIELD(temp_s1, u8 *, 0xD) = temp_v1_6;
        M2C_FIELD(temp_s1, u8 *, 0xC) = temp_v1_6;
    }
    temp_v0_2 = M2C_FIELD(temp_s0, u8 *, 0x73) - 1;
    M2C_FIELD(temp_s0, u8 *, 0x73) = temp_v0_2;
    if ((temp_v0_2 << 0x18) > 0) {
        goto block_14;
    }
    M2C_FIELD(temp_s1, u8 *, 0xE) = 0x80U;
    M2C_FIELD(temp_s1, u8 *, 0xD) = 0x80U;
    M2C_FIELD(temp_s1, u8 *, 0xC) = 0x80U;
    M2C_FIELD(temp_s0, u8 *, 0x73) = 0U;
    M2C_FIELD(temp_s0, u8 *, 0x72) = (u8) (M2C_FIELD(temp_s0, u8 *, 0x72) + 1);
block_14:
    if (D_8002715A == 0) {
        goto block_22;
    }
    M2C_FIELD(temp_s0, u8 *, 0x73) = 8U;
    M2C_FIELD(temp_s2, s16 *, 0x16) = 8;
    goto block_advance_state;
block_state3:
    temp_a0 = M2C_FIELD(temp_s0, s8 *, 0x73);
    if (temp_a0 != 0) {
        temp_v1_3 = M2C_FIELD(temp_s1, u8 *, 0xE);
        temp_v1_4 = temp_v1_3 + ((s32) (0 - temp_v1_3) / temp_a0);
        M2C_FIELD(temp_s1, u8 *, 0xE) = temp_v1_4;
        M2C_FIELD(temp_s1, u8 *, 0xD) = temp_v1_4;
        M2C_FIELD(temp_s1, u8 *, 0xC) = temp_v1_4;
    }
    temp_v0 = (u8) M2C_FIELD(temp_s0, s8 *, 0x73) - 1;
    M2C_FIELD(temp_s0, s8 *, 0x73) = temp_v0;
    if ((temp_v0 << 0x18) > 0) {
        goto block_22;
    }
block_advance_state:
    M2C_FIELD(temp_s0, u8 *, 0x72) = (u8) (M2C_FIELD(temp_s0, u8 *, 0x72) + 1);
block_22:
    temp_a0_2 = M2C_FIELD(temp_a3, s16 *, 0x96);
    if (temp_a0_2 != 0) {
        M2C_FIELD(temp_s2, s32 *, 0) = (s32) (M2C_FIELD(temp_s2, s32 *, 0) + ((s32) ((((M2C_FIELD(temp_s1, u8 *, 0x24) - 1) << 6) - (s16) M2C_FIELD(temp_s2, u16 *, 2)) << 0x10) / temp_a0_2));
        M2C_FIELD(temp_s2, s32 *, 4) = (s32) (M2C_FIELD(temp_s2, s32 *, 4) + ((s32) ((((M2C_FIELD(temp_s1, u8 *, 0x25) - 1) << 6) - (s16) M2C_FIELD(temp_s2, u16 *, 6)) << 0x10) / (s16) M2C_FIELD(temp_a3, s16 *, 0x96)));
        temp_v0_3 = (u16) M2C_FIELD(temp_a3, s16 *, 0x96) - 1;
        M2C_FIELD(temp_a3, s16 *, 0x96) = temp_v0_3;
        if ((temp_v0_3 << 0x10) <= 0) {
            M2C_FIELD(temp_a3, s16 *, 0x96) = 0;
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x14) & 0x40000) {
        M2C_FIELD(temp_a3, s16 *, 0x92) = -0x20;
        goto block_after_92;
    }
    M2C_FIELD(temp_a3, s16 *, 0x92) = 0;
block_after_92:
    M2C_FIELD(temp_a3, s8 *, 0x9D) = 0;
    temp_s3 = M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x58), void **, -0x14);
    temp_s4 = M2C_FIELD(temp_s5, u16 *, 0xC8);
    M2C_FIELD(temp_s5, u16 *, 0xC8) = (u16) M2C_FIELD(temp_s3, u16 *, 0x1A);
    M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x14) & 0xFFBF);
    M2C_FIELD(temp_s2, u16 *, 2) = (u16) (M2C_FIELD(temp_s2, u16 *, 2) + 0x100);
    M2C_FIELD(temp_s2, u16 *, 6) = (u16) (M2C_FIELD(temp_s2, u16 *, 6) + 0x100);
    if (D_80027158 == M2C_FIELD(temp_s0, s16 *, 0x6A)) {
        temp_v0_3 = (D_80027156 << 9) + 0x400;
        goto block_store_2a;
    }
    temp_v0_3 = 0x400;
block_store_2a:
    M2C_FIELD(temp_s0, s16 *, 0x2A) = temp_v0_3;
    ASM_SCHED_BARRIER();
    M2C_FIELD(temp_s0, M2C_UNK (**)(void *, void *, void *, void *), 0x5C)(temp_a3, temp_s2, temp_s1, temp_a3);
    M2C_FIELD(temp_s2, u16 *, 2) = (u16) (M2C_FIELD(temp_s2, u16 *, 2) - 0x100);
    M2C_FIELD(temp_s2, u16 *, 6) = (u16) (M2C_FIELD(temp_s2, u16 *, 6) - 0x100);
    M2C_FIELD(temp_s5, u16 *, 0xC8) = temp_s4;
    M2C_FIELD(temp_s0, s16 *, 0x88) = 0;
    var_a0_2 = M2C_FIELD(temp_s3, u8 *, 0xC);
    if (M2C_FIELD(temp_s0, s16 *, 0x6A) != M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x58), s16 *, 0x26)) {
        var_a0_2 = var_a0_2 >> 1;
    }
    M2C_FIELD(temp_s1, u8 *, 0xC) = var_a0_2;
    var_a0_3 = M2C_FIELD(temp_s3, u8 *, 0xD);
    if (M2C_FIELD(temp_s0, s16 *, 0x6A) != M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x58), s16 *, 0x26)) {
        var_a0_3 = var_a0_3 >> 1;
    }
    M2C_FIELD(temp_s1, u8 *, 0xD) = var_a0_3;
    var_a0_4 = M2C_FIELD(temp_s3, u8 *, 0xE);
    if (M2C_FIELD(temp_s0, s16 *, 0x6A) != M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x58), s16 *, 0x26)) {
        var_a0_4 = var_a0_4 >> 1;
    }
    M2C_FIELD(temp_s1, u8 *, 0xE) = var_a0_4;
    goto block_epilogue;
block_epilogue:
    return;
}
