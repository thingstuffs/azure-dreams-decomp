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

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80016000[];
M2C_UNK func_8001CEC0();                 /* extern */
M2C_UNK func_8001CFB8();                 /* extern */
M2C_UNK func_8001D0F4();                 /* extern */
M2C_UNK func_8001D328();                 /* extern */
M2C_UNK func_8001D5C0() __attribute__((noreturn));  /* extern */
s32 func_800A6D30();                                /* extern */
extern M2C_UNK D_8001F670;

void func_8001D4AC(void *arg0, s16 arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    u32 temp_v1;

    M2C_FIELD(arg0, s16 *, 0xA) = 1;
    temp_v1 = func_800A6D30() & 0xFF;
    if (temp_v1 >= 0xDU) {
        goto block_14;
    }
    (void)jt_keep; goto *D_80016000[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, s16 *, 0xA) = 2;
    func_8001D5C0();
    return;
jt_c1:
    if (M2C_FIELD(&D_8001F670, s32 *, 0) != 0) {
        goto block_14;
    }
    M2C_FIELD(arg0, s16 *, 0xA) = 3;
    D_8001F670 = 1;
    func_8001CFB8(arg0, arg1);
    func_8001D5C0();
    return;
jt_c2:
    if (M2C_FIELD(&D_8001F670, s32 *, 0) != 0) {
        goto block_14;
    }
    D_8001F670 = 1;
    M2C_FIELD(arg0, s16 *, 0xA) = 2;
    func_8001D328(arg0, arg1);
    func_8001D5C0();
    return;
jt_c4:
    if (M2C_FIELD(&D_8001F670, s32 *, 0) != 0) {
        goto block_14;
    }
    D_8001F670 = 1;
    M2C_FIELD(arg0, s16 *, 0xA) = 4;
    func_8001D0F4(arg0, arg1);
    func_8001D5C0();
    return;
jt_c5:
jt_c6:
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
    func_8001CEC0(arg0, arg1);
block_14:
jt_c3:
    return;
}
