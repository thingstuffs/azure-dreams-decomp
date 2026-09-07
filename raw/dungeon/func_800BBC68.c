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

M2C_UNK func_8008D344(); /* extern */
void func_80098864(s32, s32);           /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A6480();            /* extern */
s32 func_800AD6FC();                /* extern */
s32 func_800BBA40(); /* extern */
s32 func_800C1508();                                /* extern */
s32 func_800C1514();                       /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800C135C;
extern u16 D_800DDE84[];
extern M2C_UNK D_800DEAE0;
extern M2C_UNK D_800E1482;
extern void *D_800E3D7C[];

s32 func_800C13C8(void *arg0, s32 arg1, s16 arg2, M2C_UNK arg3) {
    void *temp_v0;
    void *state;
    s32 result;

    if (arg2 == 0xD) {
        func_80098864(arg1, arg3);
        return func_800C1514();
    }
    if (arg0 == D_800E3D7C[0]) {
        M2C_FIELD(arg0, s32 *, 0x110) = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, 0);
        func_800C1514();
        ASM_SCHED_BARRIER();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A6480(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, D_800DDE84[M2C_FIELD(arg0, u8 *, 0x13)] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C1514();
            return 1;
        }
        state = &D_80083460;
        
        M2C_FIELD(state, u16 *, 0xA)--;
        return func_800C1508();
    }
    temp_v0 = M2C_FIELD(arg0, void **, -0x14);
    if (func_800BBA40(M2C_FIELD(temp_v0, u8 *, 0x24), M2C_FIELD(temp_v0, u8 *, 0x25), M2C_FIELD(arg0, s16 *, 0x88), &D_800DEAE0, 0x5000, 0x202080, &D_800C135C) != 0) {
        goto success;
    }
    func_800C1514();
    result = 0;
    goto done;
success:
    func_800997FC(&D_800E1482);
    func_80098B38(arg1);
    result = 1;
done:
    return result;
}

/* MECHANISM: The natural arg0/arg1 lifetimes produce the retail 0x30 frame and s0/s1 saves.
   Exact callee arity, u16 table indexing, and a kept D_80083460 base restore the body.
   Ordered result labels form the final bnez/fallthrough CFG; a one-sided schedule barrier
   prevents cross-jump merging of the distinct constant-zero func_800C1514 tail site. */
