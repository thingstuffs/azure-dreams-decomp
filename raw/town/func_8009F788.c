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

M2C_UNK func_8009D808(); /* extern */
M2C_UNK func_8009D940(); /* extern */
M2C_UNK func_8009DA50();    /* extern */
extern u16 D_80082D08[];
extern s32 D_801007F8[];
extern s32 D_80100900[];

void func_8009CEE8(void) {
    register u16 *call_base ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register s32 call_a3 ASM_REG("$7");
    M2C_UNK sp10[2];
    M2C_UNK sp18[2];
    s32 *var_s0;
    s32 temp_a2;
    s32 temp_a3;
    void **var_s1;
    void *temp_v1;
    u16 *base;

    base = D_80082D08;
    func_8009D808(base, sp10, sp18);
    func_8009D940(sp10, sp18, D_80100900, D_801007F8);
    var_s1 = (void **)D_801007F8;
    if (D_801007F8[0] != 0) {
        do {
            temp_v1 = *var_s1;
            var_s0 = M2C_FIELD(temp_v1, s32 **, 0xC);
            if (var_s0 != NULL) {
                temp_a2 = M2C_FIELD(temp_v1, u16 *, 0);
                temp_a3 = M2C_FIELD(temp_v1, u16 *, 2);
                while (*var_s0 != 0) {
                    call_base = base;
                    call_a2 = (s16)temp_a2;
                    call_a3 = (s16)temp_a3;
                    func_8009DA50(*var_s0++, call_base, call_a2, call_a3);
                }
            }
            var_s1 = (void **)((s8 *)((void **)((s8 *)var_s1 + 4)));
        } while (*var_s1 != NULL);
    }
}

/* MECHANISM: Two sibling 8-byte stack arrays force the retail 0x38 frame and save contract.
   Held D_80082D08 plus the split D_801007F8 call/traversal live ranges recover s4/s0/s1.
   Nested guards keep raw u16 coordinates until the sentinel branch, avoiding two load nops.
   Guarded a1/a2/a3 call-register lives pipeline the exact inner-loop argument/delay order. */
