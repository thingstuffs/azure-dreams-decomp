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

s32 func_800A2000();
extern void func_800A2154(void) __attribute__((noreturn));
extern M2C_UNK D_800A2180;
extern M2C_UNK D_800A21EC;

s32 func_800A20D8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    register s32 held_arg0 ASM_REG("$19") = arg0;
    register M2C_UNK held_arg1 ASM_REG("$20") = arg1;
    register M2C_UNK held_arg2 ASM_REG("$21") = arg2;
    register s32 var_s0 ASM_REG("$16") = arg3;
    M2C_UNK *ptr_2180;
    M2C_UNK *ptr_21EC;

    ptr_2180 = &D_800A2180;
    ptr_21EC = &D_800A21EC;
    ASM_KEEP(var_s0);
    var_s0 -= 1;
    ASM_SCHED_BARRIER();
loop_1:
    ASM_KEEP(held_arg0);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);
    if (func_800A2000(held_arg0, held_arg1, held_arg2, var_s0, ptr_2180, ptr_21EC) != 0) {
        goto call_succeeded;
    }
    var_s0 += 1;
    ASM_TAILSLOT_PIN(var_s0);
    func_800A2154();
call_succeeded:
    if (var_s0 != 0) {
        var_s0 -= 1;
        goto loop_1;
    }
    ASM_CLOBBER("$16");
    var_s0 += 1;
    ASM_KEEP(var_s0);
    return var_s0;
}
