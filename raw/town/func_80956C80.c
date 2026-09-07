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

extern s32 D_800814A0;

void func_80023C80(void *arg0) {
    void *obj;
    s32 temp_v1;
    s32 var_v0_3;
    u16 temp_a1;

    obj = arg0;
    
    temp_v1 = M2C_FIELD(obj, s16 *, 0);
    temp_a1 = (u16) M2C_FIELD(obj, s16 *, 0);

    if (temp_v1 == 1) {
        goto case1;
    }
    if (temp_v1 >= 2) {
        goto check2;
    }
    if (temp_v1 == 0) {
        goto case0;
    }
    goto end;

check2:
    if (temp_v1 == 2) {
        goto case2;
    }
    goto end;

case0:
    M2C_FIELD(obj, u16 *, 0) = temp_a1 + 1;
    goto end;

case1:
{
    void **temp_v1_2;
    s32 work;
    s32 var_a1;

    temp_v1_2 = M2C_FIELD(obj, void ***, 4);
    ASM_KEEP_NV(temp_v1_2);
    work = (s32)*temp_v1_2;
    ASM_KEEP_NV(work);
    work = M2C_FIELD((void *)work, s16 *, 2);
    ASM_KEEP_NV(work);
    if (work < 0) {
        work += 0x1F;
    }
    M2C_FIELD(obj, u16 *, 0xC) = (u16) ((work >> 5) + 0x94);
    work = (s32)*temp_v1_2;
    ASM_KEEP_NV(work);
    work = M2C_FIELD((void *)work, s16 *, 6);
    ASM_KEEP_NV(work);
    if (work < 0) {
        work += 0x1F;
    }
    M2C_FIELD(obj, u16 *, 0xE) = (u16) ((work >> 5) + 0x75);
    work = (s32)*temp_v1_2;
    ASM_KEEP_NV(work);
    work = M2C_FIELD((void *)work, s16 *, 0xA);
    ASM_KEEP_NV(work);
    work = 0 - work;
    var_a1 = work >> 6;
    if (work < 0) {
        var_a1 = (s32) (work + 0x3F) >> 6;
    }
    var_v0_3 = var_a1 + 3;
    if (var_a1 < 0) {
        var_a1 = 0;
        ASM_KEEP_NV(var_a1);
        var_v0_3 = var_a1 + 3;
    }
    M2C_FIELD(obj, s16 *, 0x12) = var_v0_3;
    M2C_FIELD(obj, s16 *, 0x10) = var_v0_3;
    M2C_FIELD(obj, u16 *, 0xC) =
        (u16) (M2C_FIELD(obj, volatile u16 *, 0xC) - var_a1);
    M2C_FIELD(obj, u16 *, 0xE) =
        (u16) (M2C_FIELD(obj, volatile u16 *, 0xE) - var_a1);
    goto end;
}

case2:
    M2C_FIELD(obj, u16 *, -2) =
        (u16) (M2C_FIELD(obj, u16 *, -2) | 0x8000);
    D_800814A0 |= 0x8000;

end:
    
}

/* MECHANISM: The signed 0/1/2 dispatch is laid out in retail block order and
   joins the true-space epilogue at 0x80023D98, so the leaf stays frameless.
   ABI $a0 holds the object; $v1/$v0 carry the two-level pointer loads. */
