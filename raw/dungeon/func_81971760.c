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

extern u8 D_80045340[];
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800249E0;
extern M2C_UNK D_80025FE8;

void func_81971760(void *unused0, void *arg1, s32 unused2, s32 arg3, s32 arg4, s32 arg5) {
    register u16 temp_a0 ASM_REG("$4");
    register void *temp_call_a0 ASM_REG("$4");
    register u16 temp_v1 ASM_REG("$3");
    register u16 temp_sum ASM_REG("$2");
    s32 temp_rand;
    register void *temp_a3 ASM_REG("$7");
    register void *temp_s0 ASM_REG("$16");
    void *temp_s1;
    register void *temp_v0 ASM_REG("$18");
    void *temp_arg1 = arg1;
    register s32 temp_arg3 ASM_REG("$17") = arg3;
    register s32 temp_s3 ASM_REG("$19") = *(volatile s32 *)&arg4;
    register s32 temp_s4 ASM_REG("$20") = *(volatile s32 *)&arg5;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_call_a0 = temp_v0;
        ASM_KEEP_NV(temp_v0);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x38) = 0x1E;
        M2C_FIELD(temp_s0, s16 *, 0x3A) = 0x1E;
        ASM_KEEP4_NV(temp_arg3, temp_s0, temp_s3, temp_s4);
        M2C_FIELD(temp_s0, u16 *, 0x44) = temp_arg3;
        M2C_FIELD(temp_s0, u16 *, 0x46) = (u16) temp_s3;
        M2C_FIELD(temp_s0, u16 *, 0x48) = (u16) temp_s4;
        M2C_FIELD(temp_s0, void **, 0x40) = temp_arg1;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800249E0;
        func_8004491C(temp_call_a0, D_80045340);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a3, s16 *, 6) = 6;
        M2C_FIELD(temp_a3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a3, u16 *, 0x14) | 0xC);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        temp_rand = func_80069EF8();
        temp_v1 = M2C_FIELD(temp_s0, u16 *, 0x44);
        temp_v1 -= 0x10;
        M2C_FIELD(temp_s0, u16 *, 0x44) = temp_v1 + (temp_rand & 0x1F);
        temp_rand = func_80069EF8();
        temp_v1 = M2C_FIELD(temp_s0, u16 *, 0x46);
        temp_v1 -= 0x10;
        M2C_FIELD(temp_s0, u16 *, 0x46) = temp_v1 + (temp_rand & 0x1F);
        temp_rand = func_80069EF8();
        temp_v1 = M2C_FIELD(temp_s0, u16 *, 0x48);
        temp_a0 = M2C_FIELD(temp_s0, u16 *, 0x44);
        temp_v1 -= 0x10;
        M2C_FIELD(temp_s0, u16 *, 0x48) = temp_v1 + (temp_rand & 0x1F);
        M2C_FIELD(temp_s1, u16 *, 2) = temp_a0;
        M2C_FIELD(temp_s1, u16 *, 6) = (u16) M2C_FIELD(temp_s0, u16 *, 0x46);
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) M2C_FIELD(temp_s0, u16 *, 0x48);
        temp_v1 = M2C_FIELD(temp_arg1, u16 *, 2);
        ASM_KEEP(temp_v1);
        temp_sum = temp_a0;
        ASM_KEEP(temp_sum);
        temp_sum = (u16) (temp_sum + temp_v1);
        M2C_FIELD(temp_s1, u16 *, 2) = temp_sum;
        M2C_FIELD(temp_s1, u16 *, 6) = (u16) (M2C_FIELD(temp_s1, u16 *, 6) + M2C_FIELD(temp_arg1, u16 *, 6));
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xA) + M2C_FIELD(temp_arg1, u16 *, 0xA));
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a3, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a3, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a3, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a3, u8 *, 0xC) = 0x80;
        memcpy((u8 *) temp_v0 + 0xA2, (u8 *) &D_80025FE8, 12);
        M2C_FIELD(temp_a3, void **, 8) = (void *) (temp_v0 + 0xA2);
        ASM_USE(temp_v0);
    }
}
