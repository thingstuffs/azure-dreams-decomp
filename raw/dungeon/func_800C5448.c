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

extern void *D_80089440[];
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
extern void func_800CAA94(void *, M2C_UNK, void *);
M2C_UNK func_800CAFDC();
M2C_UNK func_800CB4C0();
extern u16 D_80013714;
extern s32 D_8008346C;
extern u8 D_800C9F34;

void func_800CABA8(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s16 temp_v1_2;
    s16 temp_v1_3;
    register s16 temp_v1_4 ASM_REG("$3");
    s16 var_v1;
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_a2;
    register s32 temp_divisor ASM_REG("$3");
    register s32 temp_v0_2 ASM_REG("$2");
    register s32 temp_v0_3 ASM_REG("$2");
    s32 var_t1;
    u16 temp_v0;
    u16 temp_v0_4;
    u16 temp_flags;
    u8 temp_a1;
    s32 temp_a1_2;
    s32 temp_a3;
    s32 temp_a3_2;
    register u8 temp_t0 ASM_REG("$8");
    u8 temp_v1;
    void *temp_s0;
    void *temp_s2;
    void *var_a3;

    var_a3 = arg3;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_s2 = var_a3;
    if (temp_v1 >= 5U) {
        goto block_23;
    }
    (void)jt_keep; goto *D_80089440[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, s16 *, 0xB8) = 1;
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_4;
    }
    func_8009C12C(temp_s2, arg2, M2C_FIELD(temp_s2, s16 *, 0x2A), 0);
    M2C_FIELD(arg0, u8 *, 0x9B) = 4U;
    return;
block_4:
    M2C_FIELD(arg0, u16 *, 0xB0) = (u16) M2C_FIELD(temp_s2, s16 *, 0x2A);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c1:
    M2C_FIELD(arg0, u16 *, 0x98) |= 8;
    temp_v0 = M2C_FIELD(arg0, u16 *, 0xA2) + 0x10;
    M2C_FIELD(arg0, u16 *, 0xA2) = temp_v0;
    if ((s16) temp_v0 < 0x81) {
        goto block_23;
    }
    M2C_FIELD(arg0, u16 *, 0xA2) = 0x80U;
    ASM_MEM_BARRIER();
    temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x9B);
    ASM_KEEP(temp_v0_2);
    var_v1 = 8;
    goto block_9;
jt_c2:
    temp_s0 = arg0 - 0x20;
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (M2C_FIELD(arg0, s32 *, 0xA0) - (M2C_FIELD(arg0, s32 *, 0xA0) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    func_800CAFDC(temp_s0, M2C_FIELD(temp_s2, s16 *, 0x2A), M2C_FIELD(arg0, s32 *, 0xAC));
    func_800CB4C0(temp_s0, 1);
    temp_t0 = (u8) M2C_FIELD(arg0, s32 *, 0xAC);
    temp_a2 = (s32) (0xE0 - temp_t0) / (s16) M2C_FIELD(arg0, s16 *, 0x96);
    temp_a3 = M2C_FIELD(arg0, u8 *, 0xAD);
    ASM_MEM_BARRIER();
    temp_divisor = M2C_FIELD(arg0, s16 *, 0x96);
    ASM_KEEP(temp_divisor);
    temp_a0 = (s32) (8 - temp_a3) / temp_divisor;
    ASM_MEM_BARRIER();
    temp_a1 = M2C_FIELD(arg0, u8 *, 0xAE);
    temp_v0_3 = (s32) (8 - temp_a1) / (s16) M2C_FIELD(arg0, s16 *, 0x96);
    temp_v1_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v1_2;
    temp_t0 = (u8) (temp_t0 + temp_a2);
    temp_a3 += temp_a0;
    M2C_FIELD(arg0, u8 *, 0xAC) = temp_t0;
    M2C_FIELD(arg0, u8 *, 0xAD) = (u8) temp_a3;
    M2C_FIELD(arg0, u8 *, 0xAE) = (u8) (temp_a1 + temp_v0_3);
    if ((temp_v1_2 << 0x10) > 0) {
        goto block_23;
    }
    func_8009C12C(temp_s2, arg2, M2C_FIELD(temp_s2, s16 *, 0x2A), 0);
    temp_v0_2 = M2C_FIELD(arg0, u8 *, 0x9B);
    ASM_KEEP(temp_v0_2);
    var_v1 = 4;
block_9:
    M2C_FIELD(arg0, s16 *, 0x96) = var_v1;
    ASM_MEM_BARRIER();
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (temp_v0_2 + 1);
    return;
jt_c3:
    if ((s16) M2C_FIELD(arg0, u16 *, 0xB0) == M2C_FIELD(temp_s2, s16 *, 0x2A)) {
        goto block_12;
    }
    M2C_FIELD(temp_s2, s16 *, 0x2A) = (s16) ((u16) M2C_FIELD(temp_s2, s16 *, 0x2A) + 0x200);
    var_t1 = 0;
    goto block_13;
block_12:
    var_t1 = 1;
block_13:
    temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x96);
    if (temp_v1_3 <= 0) {
        goto block_15;
    }
    temp_t0 = (u8) M2C_FIELD(arg0, s32 *, 0xAC);
    temp_a3_2 = M2C_FIELD(arg0, u8 *, 0xAD);
    temp_a1_2 = M2C_FIELD(arg0, u8 *, 0xAE);
    M2C_FIELD(arg0, u8 *, 0xAC) = (u8) (temp_t0 + ((s32) (0x40 - temp_t0) / temp_v1_3));
    var_a3 = temp_a3_2 + ((s32) (0x40 - temp_a3_2) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
    M2C_FIELD(arg0, u8 *, 0xAD) = (u8) var_a3;
    M2C_FIELD(arg0, u8 *, 0xAE) = (u8) (temp_a1_2 + ((s32) (0x40 - temp_a1_2) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
    goto block_16;
block_15:
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
block_16:
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96);
    temp_v1_4 = temp_v0_2 - 1;
    temp_v0_2 = var_t1;
    ASM_KEEP(temp_v0_2);
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v1_4;
    if (temp_v0_2 == 0) {
        goto block_23;
    }
    temp_v0_2 = temp_v1_4 << 0x10;
    if (temp_v0_2 > 0) {
        goto block_23;
    }
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c4:
    M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    D_8008346C = 0;
    M2C_FIELD(temp_s2, u16 *, 0x46) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x46) & 0x7FFF);
    func_800A4ACC(temp_s2);
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0xB6) - 1;
    M2C_FIELD(arg0, u16 *, 0xB6) = temp_v0_4;
    temp_a0 = (s32) arg0;
    if ((temp_v0_4 << 0x10) <= 0) {
        goto block_21;
    }
    if (!(D_80013714 & 8)) {
        goto block_22;
    }
block_21:
    func_800CAA94((void *) temp_a0, arg1, arg2);
    return;
block_22:
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_800C9F34;
block_23:
    return;
}
