/* cfail-repair: tf7-phase1-cache-v3 */
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

__asm__(".set D_80080000, 0x80080000");

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
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

void func_800489F4(); /* extern */
extern s32 D_800814A0[3];
extern void *D_800814A8[3];
extern u8 D_80082E80[];
extern s16 D_80083228[5];
extern u8 D_80080000[];

void func_80170A54(void *arg0) {
    register s32 state_value ASM_REG("$3") = 2;
    register u8 *page_a8 ASM_REG("$4") = (u8 *)0x80080000;
    register u8 *base = D_80082E80;
    register void *object ASM_REG("$4");

    ASM_KEEP(page_a8);
    ASM_KEEP(base);

    {
        register u8 item;
        object = *(void **)(page_a8 + 0x14A8);
        if (M2C_FIELD(base, s8 *, 4) != state_value)
            goto done;
        item = ((u8 **)base)[0xB][
                 (((s32) (D_80083228[0] +
                          M2C_FIELD(object, s16 *, 0x2A) +
                          0x100) >> 9) & 7)];
        func_800489F4(base, item,
            4, 1);
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
done:
    ;
}
