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

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() 0
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

extern void func_80091B3C(void);
extern void func_80096088(void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_800BCFBC(s32, s32);
extern u16 D_80083460[8];
extern s32 *D_800DD6B8[];

void func_80091A38(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 *sp;
    u8 state;
    register s32 **table ASM_REG("$3");
    s32 *row;
    u32 idx1;
    register u32 idx0 ASM_REG("$4");
    u32 val;
    u32 bank;
    register u32 mask ASM_REG("$5");
    s32 (*fn)(s32, void *, s32, s32);

    state = *((u8 *)arg0 + 0x9B);
    if (state == 0 || state == 16) {
        sp = *(u8 **)((u8 *)arg0 + 0x110);
        table = D_800DD6B8;
        mask = 0xFFFFFF;
        idx1 = sp[1] - 1;
        idx0 = sp[0] - 1;
        row = table[idx1];
        val = (u32)row[idx0];
        bank = val >> 0x18;
        fn = (s32 (*)(s32, void *, s32, s32))((val & mask) | 0x80000000);
        if (bank != 0) {
            func_800BCFBC(--bank, mask);
        }
        if (fn((s32)arg3 | 0xA0000000, sp, 0, 0) != 0) {
            *(void **)((u8 *)arg0 + 0x110) = NULL;
            *((u8 *)arg0 + 0x9B) += 1;
            func_80091B3C();
        }
        return;
    }
    if (state == 1) {
        func_80099F70(*(s32 *)((u8 *)arg3 + 0x5C));
        func_80099F04(*(s32 *)((u8 *)arg3 + 0x5C));
        D_80083460[1] |= 0x812;
        func_80096088(arg0, arg3);
    }
}
