#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80165A0C;

void func_80166204(void *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    register s32 held_arg4 ASM_REG("$19") = arg4;
    register s32 held_arg5 ASM_REG("$20") = arg5;
    register s32 byte_value ASM_REG("$3");
    u16 temp_v0_2;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80165A0C;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + arg3);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + held_arg4);
        ASM_KEEP(held_arg4);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + held_arg5);
        ASM_KEEP(held_arg5);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x42) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 0x44) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(temp_s0, u16 *, 0x46) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = arg6;
        M2C_FIELD(temp_s0, s16 *, 0x14) = arg1;
        M2C_FIELD(temp_s0, s16 *, 0x32) = 8;
        M2C_FIELD(temp_s0, s16 *, 0x34) = 8;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x2AA;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x2AA;
        M2C_FIELD(temp_a0, u8 *, 0xC) = 0xFF;
        byte_value = 0x20;
        M2C_FIELD(temp_a0, s8 *, 0xE) = byte_value;
        M2C_FIELD(temp_a0, s8 *, 0xD) = byte_value;
        ASM_KEEP_NV(byte_value);
        M2C_FIELD(temp_a0, s16 *, 0x12) = 0x7DCF;
        temp_v0_2 = M2C_FIELD(temp_a0, u16 *, 0x14) & 0xFFF3;
        temp_v0_2 |= 2;
        ASM_KEEP_NV(temp_v0_2);
        M2C_FIELD(temp_a0, volatile u16 *, 0x14) = temp_v0_2;
        temp_v0_2 |= 0x100;
        M2C_FIELD(temp_a0, u16 *, 0x14) = temp_v0_2;
        func_8003DB94(temp_a0, &D_800DE870, 0);
    }
}

/* MECHANISM: Seven ABI arguments preserve the unused a2 slot; guarded s3/s4
   locals hold stack inputs arg4/arg5 across the allocator-crossing first call.
   A v1 byte-value pin plus volatile midpoint and tied keep preserve the v0 RMW chain. */
