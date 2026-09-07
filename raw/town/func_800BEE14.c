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

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BC6CC;
extern M2C_UNK D_800F15E4;

s32 func_800BC574(void *arg0, s32 arg1) {
    s32 copy_value;
    void *temp_s2;
    void *temp_v0;
    void *held_arg0 = arg0;
    u8 *held_base = (u8 *) &D_80083160;
    register void *copy_dst ASM_REG("$3");
    register s32 held_arg1 ASM_REG("$19") = arg1;

    temp_v0 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800BC6CC;
        func_8004491C(temp_v0, &D_80045340);
        temp_s2 = M2C_FIELD(temp_v0, void **, 0xC);
        copy_dst = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(copy_dst, s32 *, 0) = (s32) M2C_FIELD(held_arg0, s32 *, 0);
        copy_dst = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(copy_dst, s32 *, 4) = (s32) M2C_FIELD(held_arg0, s32 *, 4);
        copy_dst = M2C_FIELD(temp_v0, void **, 8);
        copy_value = M2C_FIELD(held_arg0, s32 *, 8);
        {
            register s32 narrowed_arg1 ASM_REG("$16");

            ASM_KEEP(held_arg1);
            narrowed_arg1 = (s16) held_arg1;
            M2C_FIELD(copy_dst, s32 *, 8) = copy_value;
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32) (func_80064584(narrowed_arg1 + M2C_FIELD(held_base, s16 *, 0xC8)) * 0x30);
            M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32) (func_800644B8(narrowed_arg1 + M2C_FIELD(held_base, s16 *, 0xC8)) * 0x30);
            ASM_SCHED_BARRIER();
        }
        {
            register s32 tail_v0 ASM_REG("$2");

            tail_v0 = 0x1000;
            M2C_FIELD(temp_s2, s16 *, 0x1E) = tail_v0;
            M2C_FIELD(temp_s2, s16 *, 0x1C) = tail_v0;
            tail_v0 = (s32) M2C_FIELD(temp_v0, void **, 8);
            tail_v0 = M2C_FIELD((void *) tail_v0, s32 *, 0xC);
            if (tail_v0 > 0) {
                M2C_FIELD(temp_s2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s2, u16 *, 0x14) | 1);
            }
            tail_v0 = 0x808080;
            copy_dst = &D_800F15E4;
            M2C_FIELD(temp_s2, M2C_UNK **, 0) = copy_dst;
            copy_dst = (void *) M2C_FIELD(copy_dst, s32 *, 4);
            M2C_FIELD(temp_s2, s8 *, 4) = 0;
            M2C_FIELD(temp_s2, s8 *, 5) = 0;
            M2C_FIELD(temp_s2, s32 *, 0xC) = tail_v0;
            ASM_KEEP(tail_v0);
            M2C_FIELD(temp_s2, s32 *, 8) = (s32) copy_dst;
        }
    }
    return 0;
}
/* MECHANISM: Split full-width and narrowed arg1 live ranges let dead s0 be reused after the three-word copy while s4 holds D_80083160.
   Guarded v1/v0 overwrite chains reproduce the copy and tail loads; a zero-word fence keeps the second scaled-result store ordered.
   The rebuilt shape is exact at 2.7.2-cdk-G0; 2.95.2-G0 retained six pure-reorder divergences. */
