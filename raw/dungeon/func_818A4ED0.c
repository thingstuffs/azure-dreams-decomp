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

void func_800247B8(void) __attribute__((noreturn));  /* extern -- frame-live dispatcher */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern u8 D_80024674[];
extern u8 D_80025214[];
extern u8 D_80045340[];

s32 func_818A4ED0(s32 arg0, void *arg1) {
    s32 temp_v1;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = D_80024674;
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, M2C_UNK **, 8) = D_80025214;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E07;
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0;
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x60);
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x10C);
        temp_v1 = rand();
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (temp_v1 % 0x1000);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0;
        func_8004491C(temp_v0, D_80045340);
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
        {
            register s32 rng_v0 ASM_REG("$2");
            rng_v0 = rand();
            ASM_KEEP(rng_v0);
        }
        M2C_FIELD(temp_s0_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_s0_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        {
            u16 final_z = M2C_FIELD(arg1, u16 *, 0xA);
            ASM_KEEP(final_z);
#ifndef NON_MATCHING
            __asm__ __volatile__("" : : : "$2");
#endif
            {
                register s32 v0pin ASM_REG("$2");
                v0pin = (s32) temp_v0;
                ASM_KEEP(v0pin);
                M2C_FIELD(temp_s0_2, u16 *, 0xA) = final_z;
                func_800247B8();
            }
        }
    }
    {
        register s32 zero_v0 ASM_REG("$2");
        zero_v0 = 0;
        ASM_KEEP(zero_v0);
        return zero_v0;
    }
}
